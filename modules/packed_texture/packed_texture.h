/**************************************************************************/
/*  packed_texture.h                                                      */
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

#ifndef PACKED_TEXTURE_H
#define PACKED_TEXTURE_H

#include "core/io/resource.h"
#include "core/io/resource_loader.h"
#include "core/variant/typed_array.h"
#include "core/variant/typed_dictionary.h"
#include "core/variant/variant.h"
#include "scene/resources/3d/primitive_meshes.h"
#include "scene/resources/atlas_texture.h"
#include "scene/resources/texture.h"

class PackedTexture : public Resource {
	GDCLASS(PackedTexture, Resource);

	friend class ResourceFormatLoaderPackedTexture;

	PackedByteArray slice_data;
	TypedArray<Texture2D> textures_dependencies;

	void initialize_data(const PackedByteArray &p_slice_data, const TypedArray<Texture2D> &p_textures_dependencies);

protected:
	static void _bind_methods();

public:
	TypedDictionary<AtlasTexture, Texture2D> load_texture_slices(const int padding);
	PackedByteArray get_slice_data() const;
	TypedArray<Texture2D> get_texture_dependencies() const;
	void set_slice_data(const PackedByteArray value);
	void set_texture_dependencies(const TypedArray<Texture2D> value);

	PackedTexture() {}
	~PackedTexture() {}
};

class ResourceFormatLoaderPackedTexture : public ResourceFormatLoader {
	GDCLASS(ResourceFormatLoaderPackedTexture, ResourceFormatLoader);

public:
	Ref<Resource> load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_use_sub_threads = false, float *r_progress = nullptr, CacheMode p_cache_mode = CACHE_MODE_REUSE) override;
	void get_recognized_extensions(List<String> *p_extensions) const override;
	bool handles_type(const String &p_type) const override;
	String get_resource_type(const String &p_path) const override;
	void get_dependencies(const String &p_path, List<String> *p_dependencies, bool p_add_types = false) override;
};

#endif // PACKED_TEXTURE_H
