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

#include "object-with-meta.h"
#include "resolved-dependency.h"

namespace injeqt { namespace v1 {

resolve_dependencies_result dependency_resolver::resolve_dependencies(
	const dependencies &to_resolve,
	const objects_with_meta &objects) const
{
	auto match_result = match(to_resolve.content(), objects.content());
	auto resolved = std::vector<resolved_dependency>{};

	for (auto &&match : match_result.matched)
		if (match.second)
			resolved.emplace_back(match.first, *match.second);

	return
	{
		dependencies{match_result.unmatched_1},
		resolved
	};
}

}}
