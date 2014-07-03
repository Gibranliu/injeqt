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

#include "dependency-resolver.h"

#include "dependency.h"
#include "dependency-apply-method.h"
#include "injeqt-object.h"

namespace injeqt { namespace v1 {

const std::vector<dependency> dependency_resolver::resolve_dependencies(
	injeqt_object &object,
	const std::vector<dependency> &dependencies,
	const std::vector<injeqt_object> &objects) const
{
	auto result = std::vector<dependency>{};
	for (auto &&dependency : dependencies)
		if (!resolve_dependency(object, dependency, objects))
			result.push_back(dependency);

	return result;
}

bool dependency_resolver::resolve_dependency(
	injeqt_object &object,
	const dependency &dependency,
	const std::vector<injeqt_object> &objects) const
{
	if (dependency.apply_method() != dependency_apply_method::setter)
		return false;

	for (auto &&object2 : objects)
	{
		if (object2.meta().implements(dependency.type()))
		{
			dependency.setter_method().invoke(object.object(), Q_ARG(QObject *, object2.object()));
			return true;
		}
	}

	return false;
}

}}
