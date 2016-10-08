/*
 * \brief  Interface definition of the Hello service
 * \author Björn Döbel
 * \date   2008-03-20
 */

/*
 * Copyright (C) 2008-2016 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _INCLUDE__HELLO_SESSION__HELLO_SESSION_H_
#define _INCLUDE__HELLO_SESSION__HELLO_SESSION_H_

#include <session/session.h>
#include <base/rpc.h>

#include "nodef.h"

namespace Hello { struct Session; }


struct Hello::Session : Genode::Session
{
	static const char *service_name() { return "Hello"; }

	virtual void say_hello() = 0;
	virtual int add(int a, int b) = 0;
	virtual Nodef test_nodef( Nodef x, Nodef *y, Nodef &z ) =0;
	virtual Nodef test_nodef_exc( Nodef *a ) =0;


	/*******************
	 ** RPC interface **
	 *******************/

	GENODE_RPC(Rpc_say_hello, void, say_hello);
	GENODE_RPC(Rpc_add, int, add, int, int);
	GENODE_RPC(Rpc_test_nodef, Nodef, test_nodef, Nodef, Nodef*, Nodef& );
	GENODE_RPC_THROW(Rpc_test_nodef_exc, Nodef, test_nodef_exc,
	           GENODE_TYPE_LIST( Test_exception ), Nodef * );

	GENODE_RPC_INTERFACE(Rpc_say_hello, Rpc_add,
	                     Rpc_test_nodef, Rpc_test_nodef_exc );
};

#endif /* _INCLUDE__HELLO_SESSION__HELLO_SESSION_H_ */
