/**************************************************************************/
/*  file_access_obfuscated.cpp                                            */
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

#include "core/io/file_access_obfuscated.h"

#include "core/string/print_string.h"
#include "core/variant/variant.h"

void FileAccessObfuscated::_obfuscate_payload(Vector<uint8_t> &payload) const {
}

void FileAccessObfuscated::_deobfuscate_payload(Vector<uint8_t> &payload) const {
}

Error FileAccessObfuscated::open_and_parse(Ref<FileAccess> p_base, Mode p_mode) {
	ERR_FAIL_COND_V_MSG(file.is_valid(), ERR_ALREADY_IN_USE, vformat("Can't open file while another file from path '%s' is open.", file->get_path_absolute()));

	pos = 0;
	eofed = false;

	if (p_mode == MODE_WRITE) {
		data.clear();
		writing = true;
		file = p_base;
	} else if (p_mode == MODE_READ) {
		writing = false;

		length = p_base->get_64();

		base = p_base->get_position();
		ERR_FAIL_COND_V(p_base->get_length() < base + length, ERR_FILE_CORRUPT);

		data.resize(length);

		uint64_t blen = p_base->get_buffer(data.ptrw(), length);
		ERR_FAIL_COND_V(blen != length, ERR_FILE_CORRUPT);

		_deobfuscate_payload(data);

		file = p_base;
	}

	return OK;
}

Error FileAccessObfuscated::open_internal(const String &p_path, int p_mode_flags) {
	return OK;
}

void FileAccessObfuscated::_close() {
	if (file.is_null()) {
		return;
	}

	if (writing) {
		Vector<uint8_t> obfuscated;
		obfuscated.resize(data.size());

		for (int i = 0; i < data.size(); i++) {
			obfuscated.write[i] = data[i];
		}

		_obfuscate_payload(obfuscated);

		file->store_64(data.size());
		file->store_buffer(obfuscated.ptr(), obfuscated.size());
		data.clear();
	}

	file.unref();
}

bool FileAccessObfuscated::is_open() const {
	return file.is_valid();
}

String FileAccessObfuscated::get_path() const {
	if (file.is_valid()) {
		return file->get_path();
	} else {
		return "";
	}
}

String FileAccessObfuscated::get_path_absolute() const {
	if (file.is_valid()) {
		return file->get_path_absolute();
	} else {
		return "";
	}
}

void FileAccessObfuscated::seek(uint64_t p_position) {
	if (p_position > get_length()) {
		p_position = get_length();
	}

	pos = p_position;
	eofed = false;
}

void FileAccessObfuscated::seek_end(int64_t p_position) {
	seek(get_length() + p_position);
}

uint64_t FileAccessObfuscated::get_position() const {
	return pos;
}

uint64_t FileAccessObfuscated::get_length() const {
	return data.size();
}

bool FileAccessObfuscated::eof_reached() const {
	return eofed;
}

uint64_t FileAccessObfuscated::get_buffer(uint8_t *p_dst, uint64_t p_length) const {
	ERR_FAIL_COND_V_MSG(writing, -1, "File has not been opened in read mode.");

	if (!p_length) {
		return 0;
	}

	ERR_FAIL_NULL_V(p_dst, -1);

	uint64_t to_copy = MIN(p_length, get_length() - pos);

	memcpy(p_dst, data.ptr() + pos, to_copy);
	pos += to_copy;

	if (to_copy < p_length) {
		eofed = true;
	}

	return to_copy;
}

Error FileAccessObfuscated::get_error() const {
	return eofed ? ERR_FILE_EOF : OK;
}

bool FileAccessObfuscated::store_buffer(const uint8_t *p_src, uint64_t p_length) {
	ERR_FAIL_COND_V_MSG(!writing, false, "File has not been opened in write mode.");

	if (!p_length) {
		return true;
	}

	ERR_FAIL_NULL_V(p_src, false);

	if (pos + p_length >= get_length()) {
		ERR_FAIL_COND_V(data.resize(pos + p_length) != OK, false);
	}

	memcpy(data.ptrw() + pos, p_src, p_length);
	pos += p_length;

	return true;
}

void FileAccessObfuscated::flush() {
	ERR_FAIL_COND_MSG(!writing, "File has not been opened in write mode.");

	// obfuscated files keep data in memory till close()
}

bool FileAccessObfuscated::file_exists(const String &p_name) {
	Ref<FileAccess> fa = FileAccess::open(p_name, FileAccess::READ);
	if (fa.is_null()) {
		return false;
	}
	return true;
}

uint64_t FileAccessObfuscated::_get_modified_time(const String &p_file) {
	if (file.is_valid()) {
		return file->get_modified_time(p_file);
	} else {
		return 0;
	}
}

uint64_t FileAccessObfuscated::_get_access_time(const String &p_file) {
	if (file.is_valid()) {
		return file->get_access_time(p_file);
	} else {
		return 0;
	}
}

int64_t FileAccessObfuscated::_get_size(const String &p_file) {
	if (file.is_valid()) {
		return file->get_size(p_file);
	} else {
		return -1;
	}
}

BitField<FileAccess::UnixPermissionFlags> FileAccessObfuscated::_get_unix_permissions(const String &p_file) {
	if (file.is_valid()) {
		return file->_get_unix_permissions(p_file);
	}
	return 0;
}

Error FileAccessObfuscated::_set_unix_permissions(const String &p_file, BitField<FileAccess::UnixPermissionFlags> p_permissions) {
	if (file.is_valid()) {
		return file->_set_unix_permissions(p_file, p_permissions);
	}
	return FAILED;
}

bool FileAccessObfuscated::_get_hidden_attribute(const String &p_file) {
	if (file.is_valid()) {
		return file->_get_hidden_attribute(p_file);
	}
	return false;
}

Error FileAccessObfuscated::_set_hidden_attribute(const String &p_file, bool p_hidden) {
	if (file.is_valid()) {
		return file->_set_hidden_attribute(p_file, p_hidden);
	}
	return FAILED;
}

bool FileAccessObfuscated::_get_read_only_attribute(const String &p_file) {
	if (file.is_valid()) {
		return file->_get_read_only_attribute(p_file);
	}
	return false;
}

Error FileAccessObfuscated::_set_read_only_attribute(const String &p_file, bool p_ro) {
	if (file.is_valid()) {
		return file->_set_read_only_attribute(p_file, p_ro);
	}
	return FAILED;
}

void FileAccessObfuscated::close() {
	_close();
}

FileAccessObfuscated::~FileAccessObfuscated() {
	_close();
}
