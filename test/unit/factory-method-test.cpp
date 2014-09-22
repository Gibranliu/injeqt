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

#include "exception/exception.cpp"
#include "extract-interfaces.cpp"
#include "factory-method.cpp"
#include "type.cpp"

#include "expect.h"
#include "utils.h"

#include <QtTest/QtTest>
#include <string>

using namespace injeqt::internal;
using namespace injeqt::v1;

class result_object : public QObject
{
	Q_OBJECT
};

class other_object : public QObject
{
	Q_OBJECT
};

class no_factory : public QObject
{
	Q_OBJECT

public slots:
	void regular_method() {}

};

class factory_invalid_result_type : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE int create_result_object() {}

};

class factory_not_invokable : public QObject
{
	Q_OBJECT

public:
	result_object * create_result_object() {}

};

class non_unique_factory : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE result_object * create_result_object_1() {}
	Q_INVOKABLE result_object * create_result_object_2() {}

};

class valid_factory : public QObject
{
	Q_OBJECT

public slots:
	Q_INVOKABLE result_object * create_result_object() { return new result_object{}; }

};

class factory_method_test : public QObject
{
	Q_OBJECT

private slots:
	void should_throw_when_created_with_empty_method();
	void should_throw_when_created_with_regular_method();
	void should_throw_when_created_with_no_factory_method();
	void should_throw_when_created_with_not_invokable_factory_method();
	void should_throw_when_created_with_non_unique_factory_method();
	void should_throw_when_created_with_different_type_factory_method();
	void should_create_valid_with_invokable_factory_method();
	void should_create_object_with_factory_method();

};

void factory_method_test::should_throw_when_created_with_empty_method()
{
	expect<invalid_type_exception>([&]{
		make_validated<factory_method>(QMetaMethod{});
	});
}

void factory_method_test::should_throw_when_created_with_regular_method()
{
	expect<invalid_type_exception>([&]{
		make_validated<factory_method>(make_method<no_factory>("regular_method()"));
	});
}

void factory_method_test::should_throw_when_created_with_no_factory_method()
{
	expect<invalid_type_exception>([&]{
		make_validated<factory_method>(make_method<factory_invalid_result_type>("create_result_object()"));
	});
}

void factory_method_test::should_throw_when_created_with_not_invokable_factory_method()
{
	expect<method_not_found_exception>([&]{
		make_validated<factory_method>(make_method<factory_not_invokable>("create_result_object()"));
	});
	expect<no_factory_method_exception>([&]{
		make_factory_method<result_object, factory_not_invokable>();
	});
	expect<no_factory_method_exception>([&]{
		make_factory_method(make_validated_type<result_object>(), make_validated_type<factory_not_invokable>());
	});
}

void factory_method_test::should_throw_when_created_with_non_unique_factory_method()
{
	expect<non_unique_factory_exception>([&]{
		make_factory_method<result_object, non_unique_factory>();
	});
	expect<non_unique_factory_exception>([&]{
		make_factory_method(make_validated_type<result_object>(), make_validated_type<non_unique_factory>());
	});
}

void factory_method_test::should_throw_when_created_with_different_type_factory_method()
{
	expect<no_factory_method_exception>([&]{
		make_factory_method<other_object, valid_factory>();
	});
}

void factory_method_test::should_create_valid_with_invokable_factory_method()
{
	auto c1 = factory_method{make_method<valid_factory>("create_result_object()")};
	QCOMPARE(c1.object_type(), make_validated_type<valid_factory>());
	QCOMPARE(c1.result_type(), make_validated_type<result_object>());

	auto c2 = make_factory_method<result_object, valid_factory>();
	QCOMPARE(c2.object_type(), make_validated_type<valid_factory>());
	QCOMPARE(c2.result_type(), make_validated_type<result_object>());

	auto c3 = make_factory_method(make_validated_type<result_object>(), make_validated_type<valid_factory>());
	QCOMPARE(c3.object_type(), make_validated_type<valid_factory>());
	QCOMPARE(c3.result_type(), make_validated_type<result_object>());

	QCOMPARE(c1, c2);
	QCOMPARE(c2, c3);
	QCOMPARE(c1, c3);
}

void factory_method_test::should_create_object_with_factory_method()
{
	auto factory = make_factory_method<result_object, valid_factory>();
	auto factory_object = make_object<valid_factory>();
	auto object = factory.invoke(factory_object.get());
	auto cast = qobject_cast<result_object *>(object.get());

	QVERIFY(cast != nullptr);
}

QTEST_APPLESS_MAIN(factory_method_test)
#include "factory-method-test.moc"
