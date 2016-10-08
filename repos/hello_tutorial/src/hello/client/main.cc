/*
 * \brief  Test client for the Hello RPC interface
 * \author Björn Döbel
 * \author Norman Feske
 * \date   2008-03-20
 */

/*
 * Copyright (C) 2008-2016 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#include <base/component.h>
#include <base/log.h>
#include <hello_session/connection.h>


Genode::size_t Component::stack_size() { return 64*1024; }


void Component::construct(Genode::Env &env)
{
	Hello::Connection hello(env);

	hello.say_hello();

	int const sum = hello.add(2, 5);
	Genode::log("added 2 + 5 = ", sum);

	Genode::log("Test is successful if all numbers between 1 and 10 are printed");

	Hello::Nodef x( 1 ), y( 2 ), z( 3 );
	Hello::Nodef ret = hello.test_nodef( x, &y, z );
	ret.print(); //4
	y.print(); //5
	z.print(); //6

	Hello::Nodef arg( 6 );
	try {
		hello.test_nodef_exc( &arg );
		Genode::log( "Fail" );
		return;
	} catch ( Hello::Test_exception ) {}
	arg.print(); //7
	arg._content++;
	ret = hello.test_nodef_exc( &arg ); 
	arg.print(); //9
	ret.print(); //10

	Genode::log("hello test completed");
}
