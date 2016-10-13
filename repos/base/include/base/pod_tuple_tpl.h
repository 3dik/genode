/*
 * \brief  Implementation of the Pod_tuple constructors
 */

#pragma once

#include <base/ipc.h>
#include <base/rpc.h>

namespace Genode {

	namespace Meta {

		using namespace Trait;

		template <typename HEAD, typename TAIL>
		Pod_tuple<HEAD,TAIL>::Pod_tuple( Ipc_unmarshaller &msg,
		                                 Overload_selector<Rpc_arg_in> )
			: _1( msg.extract( Overload_selector<typename Pod<HEAD>::Type>() ) ),
			  _2( msg, Overload_selector<
			           typename Rpc_direction<typename TAIL::Head>::Type>() )
		{}

		template <typename HEAD, typename TAIL>
		Pod_tuple<HEAD,TAIL>::Pod_tuple( Ipc_unmarshaller &msg,
		                                 Overload_selector<Rpc_arg_out> )
			: _2( msg, Overload_selector<
			           typename Rpc_direction<typename TAIL::Head>::Type>() )
		{}


		template <typename HEAD, typename TAIL>
		Pod_tuple<HEAD *,TAIL>::Pod_tuple( Ipc_unmarshaller &msg,
		                                 Overload_selector<Rpc_arg_in> )
			: _1( msg.extract(
			      Overload_selector<typename Non_reference<HEAD>::Type>() ) ),
			  _2( msg, Overload_selector<
			           typename Rpc_direction<typename TAIL::Head>::Type>() )
		{}

		template <typename HEAD, typename TAIL>
		Pod_tuple<HEAD *,TAIL>::Pod_tuple( Ipc_unmarshaller &msg,
		                                 Overload_selector<Rpc_arg_out> )
			: _2( msg, Overload_selector<
			           typename Rpc_direction<typename TAIL::Head>::Type>() )
		{}

	}

}
