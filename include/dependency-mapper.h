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

#include <tuple>
#include <unordered_map>
#include <vector>

namespace injeqt { namespace v1 {

class dependency;
class injeqt_object;

class dependency_mapper final
{

public:
	std::tuple<std::unordered_map<dependency, const injeqt_object *>, std::vector<dependency>> map_dependencies(
		const std::vector<dependency> &dependencies,
		const std::vector<const injeqt_object *> &objects) const;
	const injeqt_object * get_dependency(
		const dependency &dependency,
		const std::vector<const injeqt_object *> &objects) const;

};

}}
