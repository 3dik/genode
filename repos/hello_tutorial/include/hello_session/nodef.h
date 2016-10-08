/*
 * \brief  Dummy class without a default-constructor
 * \author Edgard Schmidt
 * \date   2016-10-08
 */

#pragma once

namespace Hello
{

	struct Test_exception {};

	struct Nodef
	{
			int _content;

			//Comment out to delete the default constructor
			//Nodef() : _content( 1337 ) {}

			Nodef( int content )
				: _content( content )
			{
			}

			void print()
			{
				Genode::log( "Nodef value: ", _content );
			}
	};

}
