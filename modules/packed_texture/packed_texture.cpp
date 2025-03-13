/**************************************************************************/
/*  packed_texture.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "packed_texture.h"
#include "core/error/error_list.h"
#include "core/error/error_macros.h"
#include "core/io/compression.h"
#include "core/io/dir_access.h"
#include "core/io/file_access.h"
#include "core/io/marshalls.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/string/print_string.h"
#include "core/string/ustring.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"
#include "scene/resources/atlas_texture.h"
#include "scene/resources/texture.h"
#include <cstdint>

void ResourceFormatLoaderPackedTexture::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("binatlas");
}

bool ResourceFormatLoaderPackedTexture::handles_type(const String &p_type) const {
	return true;
}

String ResourceFormatLoaderPackedTexture::get_resource_type(const String &p_path) const {
	return "PackedTexture";
}

void ResourceFormatLoaderPackedTexture::get_dependencies(const String &p_path, List<String> *p_dependencies, bool p_add_types) {
	String file_name = p_path.get_file().get_basename();
	String file_dir = p_path.get_base_dir();
	PackedStringArray dependency_candidate_names = DirAccess::get_files_at(file_dir);
	for (const String &candidate_name : dependency_candidate_names) {
		if (candidate_name == file_name) {
			continue;
		}
		if (!candidate_name.ends_with(".png")) {
			continue;
		}
		if (!candidate_name.begins_with(file_name)) {
			continue;
		}
		String candidate_num_str = candidate_name.substr(file_name.length(), candidate_name.length() - file_name.length() - 4);
		if (!candidate_num_str.is_valid_int()) {
			continue;
		}
		String file_path = file_dir.path_join(candidate_name);
		if (p_add_types) {
			file_path += "::Texture2D";
		}
		p_dependencies->push_back(file_path);
	}
	p_dependencies->sort();
}

Ref<Resource> ResourceFormatLoaderPackedTexture::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, CacheMode p_cache_mode) {
	Ref<PackedTexture> packed_texture;
	packed_texture.instantiate();
	TypedArray<Texture2D> texture_dependencies;

	List<String> dependencies;
	get_dependencies(p_path, &dependencies);
	for (const String &dependency : dependencies) {
		Ref<Texture2D> texture = ResourceLoader::load(dependency, "Texture2D");
		if (texture.is_null()) {
			continue;
		}
		texture_dependencies.push_back(texture);
	}

	Error err;
	Vector<uint8_t> file_content = FileAccess::get_file_as_bytes(p_path, &err);
	if (err != OK) {
		if (r_error) {
			*r_error = err;
		}
		return Ref<Resource>();
	}

	packed_texture->initialize_data(file_content.to_byte_array(), texture_dependencies);

	return packed_texture;
}

void PackedTexture::initialize_data(const PackedByteArray &p_slice_data, const TypedArray<Texture2D> &p_textures_dependencies) {
	slice_data = p_slice_data;
	textures_dependencies = p_textures_dependencies;
}

static inline int32_t decode_int32_and_advance(const uint8_t *&p_arr) {
	int32_t ret = int32_t(decode_uint32(p_arr));
	p_arr += sizeof(uint32_t);
	return ret;
}

static inline uint16_t decode_uint16_and_advance(const uint8_t *&p_arr) {
	uint16_t ret = decode_uint16(p_arr);
	p_arr += sizeof(uint16_t);
	return ret;
}

static String decode_utf8_and_advance(const uint8_t *&p_arr) {
	uint16_t length = decode_uint16_and_advance(p_arr);
	ERR_FAIL_COND_V_MSG(length <= 0, String(), vformat("Invalid UTF8 string length (%s).", length));
	String ret = String::utf8((char *)p_arr, length);
	p_arr += length * sizeof(uint8_t);
	return ret;
}

TypedDictionary<AtlasTexture, Texture2D> PackedTexture::load_texture_slices(const int padding) {
	ERR_FAIL_COND_V(slice_data.size() == 0, (TypedDictionary<AtlasTexture, Texture2D>()));
	ERR_FAIL_COND_V(textures_dependencies.size() == 0, (TypedDictionary<AtlasTexture, Texture2D>()));

	Vector<uint8_t> decompressed_slice_data;
	int result = Compression::decompress_dynamic(&decompressed_slice_data, -1, slice_data.ptr(), slice_data.size(), Compression::MODE_GZIP);
	ERR_FAIL_COND_V_MSG(result != 0, (TypedDictionary<AtlasTexture, Texture2D>()), vformat("Failed to decompress slice data(%s).", result));

	const uint8_t *ptr = decompressed_slice_data.ptr();

	uint32_t slice_count = decode_int32_and_advance(ptr);
	uint32_t slice_num = 0;

	HashMap<uint32_t, Ref<Texture2D>> texture_map;
	TypedDictionary<AtlasTexture, Texture2D> loaded_atlas_textures;

	while (slice_count > 0) {
		int32_t atlas_id = decode_int32_and_advance(ptr);
		int32_t slice_x = decode_int32_and_advance(ptr);
		int32_t slice_y = decode_int32_and_advance(ptr);
		int32_t slice_w = decode_int32_and_advance(ptr);
		int32_t slice_h = decode_int32_and_advance(ptr);
		int32_t left = decode_int32_and_advance(ptr);
		int32_t top = decode_int32_and_advance(ptr);
		int32_t right = decode_int32_and_advance(ptr);
		int32_t bottom = decode_int32_and_advance(ptr);
		String slice_name = decode_utf8_and_advance(ptr);

		if (slice_name == "") {
			print_line(vformat("Slice %s has no name.", slice_num));
			return TypedDictionary<AtlasTexture, Texture2D>();
		}

		Ref<Texture2D> source_texture;
		if (!texture_map.has(atlas_id)) {
			ERR_FAIL_COND_V_MSG((int)atlas_id >= textures_dependencies.size(), (TypedDictionary<AtlasTexture, Texture2D>()), vformat("Slice %s is requesting atlas %s where the total atlas count is %s", slice_num, atlas_id, textures_dependencies.size()));
			source_texture = textures_dependencies[atlas_id];
			texture_map.insert(atlas_id, source_texture);
		} else {
			source_texture = texture_map[atlas_id];
		}

		Ref<AtlasTexture> atlas_texture;
		atlas_texture.instantiate();
		atlas_texture->set_atlas(source_texture);
		atlas_texture->set_filter_clip(true);
		atlas_texture->set_margin(Rect2i(left, top, left + right, top + bottom));
		atlas_texture->set_region(Rect2i(slice_x - padding, slice_y - padding, slice_w + padding * 2, slice_h + padding * 2));
		atlas_texture->set_name(slice_name);
		loaded_atlas_textures.get_or_add(atlas_texture, source_texture);

		slice_num++;
		slice_count--;
	}

	return loaded_atlas_textures;
}

PackedByteArray PackedTexture::get_slice_data() const {
	return slice_data;
}

TypedArray<Texture2D> PackedTexture::get_texture_dependencies() const {
	return textures_dependencies;
}

void PackedTexture::set_slice_data(const PackedByteArray value) {
	slice_data = value;
}

void PackedTexture::set_texture_dependencies(const TypedArray<Texture2D> value) {
	textures_dependencies = value;
}

void PackedTexture::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_texture_slices", "padding"), &PackedTexture::load_texture_slices, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("get_slice_data"), &PackedTexture::get_slice_data);
	ClassDB::bind_method(D_METHOD("set_slice_data", "value"), &PackedTexture::set_slice_data);
	ClassDB::bind_method(D_METHOD("get_texture_dependencies"), &PackedTexture::get_texture_dependencies);
	ClassDB::bind_method(D_METHOD("set_texture_dependencies", "value"), &PackedTexture::set_texture_dependencies);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "slice_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_READ_ONLY), "set_slice_data", "get_slice_data");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "texture_dependencies", PROPERTY_HINT_RESOURCE_TYPE, "PackedTexture", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_READ_ONLY), "set_texture_dependencies", "get_texture_dependencies");
}
