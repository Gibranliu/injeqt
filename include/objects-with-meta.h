/*
 * %injeqt copyright begin%
 * Copyright 2014 Rafał Malinowski (rafal.przemyslaw.malinowski@gmail.com)
 * %injeqt copyright end%
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include "injeqt-global.h"
#include "sorted-unique-vector.h"

namespace injeqt { namespace v1 {

class object_with_meta;

class objects_with_meta final
{
	static bool less_than_object_with_meta(const object_with_meta &left, const object_with_meta &right);
	static bool equal_object_with_meta(const object_with_meta &left, const object_with_meta &right);

public:
	using storage_type = sorted_unique_vector<object_with_meta, less_than_object_with_meta, equal_object_with_meta>::storage_type;

	objects_with_meta(std::vector<object_with_meta> objects_with_meta);

	storage_type::const_iterator begin() const;
	storage_type::const_iterator end() const;

	bool empty() const;
	bool contains(const object_with_meta &d) const;
	typename storage_type::size_type size() const;

private:
	storage_type _content;

};

inline typename objects_with_meta::storage_type::const_iterator begin(const object_with_meta &d)
{
	return d.begin();
}

inline typename objects_with_meta::storage_type::const_iterator end(const object_with_meta &d)
{
	return d.end();
}

}}
