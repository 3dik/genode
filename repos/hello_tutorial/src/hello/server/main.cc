/*
 * \brief  Main program of the Hello server
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
#include <base/heap.h>
#include <root/component.h>
#include <hello_session/hello_session.h>
#include <base/rpc_server.h>

namespace Hello {
	struct Session_component;
	struct Root_component;
	struct Main;
}


struct Hello::Session_component : Genode::Rpc_object<Session>
{
	void say_hello() {
		Genode::log("I am here... Hello."); }

	int add(int a, int b) {
		return a + b; }

	Nodef test_nodef( Nodef x, Nodef *y, Nodef &z ) {
		x.print(); //1
		y->print(); //2
		z.print(); //3
		y->_content = 5;
		z._content  = 6;
		return Nodef( 4 );
	}

	Nodef test_nodef_exc( Nodef *a ) {
		if ( 6 == a->_content )
		{
			a->_content = 7;
			throw Test_exception();
		}
		a->print(); //8
		a->_content++;
		return Nodef( 10 );
	}
};


class Hello::Root_component
:
	public Genode::Root_component<Session_component>
{
	protected:

		Session_component *_create_session(const char *args)
		{
			Genode::log("creating hello session");
			return new (md_alloc()) Session_component();
		}

	public:

		Root_component(Genode::Entrypoint &ep,
		               Genode::Allocator &alloc)
		:
			Genode::Root_component<Session_component>(ep, alloc)
		{
			Genode::log("creating root component");
		}
};


struct Hello::Main
{
	Genode::Env &env;

	/*
	 * A sliced heap is used for allocating session objects - thereby we
	 * can release objects separately.
	 */
	Genode::Sliced_heap sliced_heap { env.ram(), env.rm() };

	Hello::Root_component root { env.ep(), sliced_heap };

	Main(Genode::Env &env) : env(env)
	{
		/*
		 * Create a RPC object capability for the root interface and
		 * announce the service to our parent.
		 */
		env.parent().announce(env.ep().manage(root));
	}
};


Genode::size_t Component::stack_size() { return 64*1024; }


void Component::construct(Genode::Env &env)
{
	static Hello::Main main(env);
}
