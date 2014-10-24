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

#include <injeqt/module.h>

#include <injeqt/exception/default-constructor-not-found.h>
#include <injeqt/exception/empty-type.h>
#include <injeqt/exception/interface-not-implemented.h>
#include <injeqt/exception/invalid-qobject.h>
#include <injeqt/exception/qobject-type.h>
#include <injeqt/exception/unique-factory-method-not-found.h>

#include "default-constructor-method.h"
#include "implementation.h"
#include "interfaces-utils.h"
#include "module-impl.h"
#include "provider-by-default-constructor.h"
#include "provider-by-factory.h"
#include "provider-ready.h"

#include <QtCore/QMetaObject>
#include <cassert>

namespace injeqt { namespace v1 {

module::module() :
	_pimpl{new injeqt::internal::module_impl{}}
{
}

module::~module()
{
}

void module::add_ready_object(type t, QObject *object)
{
	assert(!t.is_empty());

	auto i = internal::make_implementation(std::move(t), object);
	auto p = std::unique_ptr<internal::provider_ready>{new internal::provider_ready{std::move(i)}};
	_pimpl->add_provider(std::move(p));
}

void module::add_type(type t)
{
	assert(!t.is_empty());

	if (t.is_qobject())
		throw exception::qobject_type();

	auto c = internal::make_default_constructor_method(t);
	if (c.is_empty())
		throw exception::default_constructor_not_found{t.name()};

	auto p = std::unique_ptr<internal::provider_by_default_constructor>{new internal::provider_by_default_constructor{std::move(c)}};
	_pimpl->add_provider(std::move(p));
}

void module::add_factory(type t, type f)
{
	assert(!t.is_empty());
	assert(!f.is_empty());

	if (t.is_qobject())
		throw exception::qobject_type();
	if (f.is_qobject())
		throw exception::qobject_type();

	auto fm = internal::make_factory_method(t, f);
	if (fm.is_empty())
		throw exception::unique_factory_method_not_found{t.name() + " in " + f.name()};

	auto p = std::unique_ptr<internal::provider_by_factory>{new internal::provider_by_factory{std::move(fm)}};
	_pimpl->add_provider(std::move(p));
}

}}
