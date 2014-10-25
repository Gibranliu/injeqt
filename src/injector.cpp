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

#include <injeqt/injector.h>

#include <injeqt/exception/empty-type.h>
#include <injeqt/exception/qobject-type.h>
#include <injeqt/module.h>

#include "injector-impl.h"
#include "module-impl.h"
#include "provider.h"

#include <cassert>

using namespace injeqt::internal;

namespace injeqt { namespace v1 {

injector::injector() :
	_pimpl{new ::injeqt::internal::injector_impl{}}
{
}

injector::injector(std::vector<std::unique_ptr<module>> modules) :
	_pimpl{new ::injeqt::internal::injector_impl{std::move(modules)}}
{
}

injector::injector(injector &&x) :
	_pimpl{std::move(x._pimpl)}
{
}

injector::~injector()
{
}

injector & injector::operator = (injector &&x)
{
	_pimpl = std::move(x._pimpl);
	return *this;
}

QObject * injector::get(const type &interface_type)
{
	assert(!interface_type.is_empty());

	if (interface_type.is_qobject())
		throw exception::qobject_type{};

	return _pimpl->get(interface_type);
}

}}
