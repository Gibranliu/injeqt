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

#include "provider-ready-configuration.h"

#include "provider-ready.h"

#include <cassert>

namespace injeqt { namespace internal {

provider_ready_configuration::provider_ready_configuration(type object_type, QObject *object) :
	_object_type{std::move(object_type)},
	_object{object}
{
	assert(!_object_type.is_empty());
}

provider_ready_configuration::~provider_ready_configuration()
{
}

std::unique_ptr<provider> provider_ready_configuration::create_provider() const
{
	auto i = internal::make_implementation(_object_type, _object);
	return std::unique_ptr<provider>{new provider_ready{i}};
}

}}
