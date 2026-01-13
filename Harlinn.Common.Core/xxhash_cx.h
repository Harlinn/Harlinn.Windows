/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
//	xxhash_cx
//	xxHash 32/64 - C++14 constexpr version.
//	https://github.com/masyos/xxhash_cx
//
//	Copyright(c) 2018, YOSHIDA Masahiro
//	MIT License
//
// xxHash document: https://github.com/Cyan4973/xxHash/wiki/xxHash-specification-(draft)
//

/*
The MIT License (MIT)

Copyright (c) 2018 YOSHIDA, Masahiro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

#ifndef	XXHASH_CX_H
#define	XXHASH_CX_H

#include <cstdint>
#include <array>
#include <string>
#include <limits>

#if defined(_MSC_VER)
// Microsoft Visual C++
#if (_MSC_VER < 1910)
#error no support.
#endif // (_MSC_VER < 1910)
#elif defined(__clang__)
// clang
#if (__clang_major__ < 5)
#error no support.
#endif // (__clang_major__ < 5)
#elif defined(__GNUC__)
// gcc
#if (__GNUC__ < 6)
#error no support.
#elif ((__GNUC__ == 6)&&(__GNUC_MINOR__ < 2))
#error no support.
#endif // (__GNUC__ < 6)
#endif 



#ifndef	XXHASH_CX_XXH32_SEED
///	@brief	user defined literals - default xxHash32 seed. 
#define	XXHASH_CX_XXH32_SEED	(20180101UL)
#endif
#ifndef	XXHASH_CX_XXH64_SEED	
///	@brief	user defined literals - default xxHash64 seed. 
#define	XXHASH_CX_XXH64_SEED	(201801011200ULL)
#endif

///	@brief	xxhash namespace.
namespace xxhash
{


	namespace details
	{

		template <class T>
		constexpr T rotl( T n, std::size_t shift )
		{
			static_assert( std::numeric_limits<T>::is_integer, "integer only." );
			return ( ( n << shift ) | ( n >> ( std::numeric_limits<T>::digits - shift ) ) );
		}
		template <class T>
		constexpr T read( const char* p )
		{
			return static_cast<T>( *p );
		}
		template <>
		constexpr std::uint8_t read( const char* p )
		{
			return std::uint8_t( p[0] );
		}
		template <>
		constexpr std::uint16_t read( const char* p )
		{
			return ( ( static_cast<std::uint16_t>( std::uint8_t( p[0] ) ) << 0 )
				| ( static_cast<std::uint16_t>( std::uint8_t( p[1] ) ) << 8 ) );
		}
		template <>
		constexpr std::uint32_t read( const char* p )
		{
			return ( ( static_cast<std::uint32_t>( std::uint8_t( p[0] ) ) << 0 )
				| ( static_cast<std::uint32_t>( std::uint8_t( p[1] ) ) << 8 )
				| ( static_cast<std::uint32_t>( std::uint8_t( p[2] ) ) << 16 )
				| ( static_cast<std::uint32_t>( std::uint8_t( p[3] ) ) << 24 ) );
		}
		template <>
		constexpr std::uint64_t read( const char* p )
		{
			return ( ( static_cast<std::uint64_t>( std::uint8_t( p[0] ) ) << 0 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[1] ) ) << 8 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[2] ) ) << 16 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[3] ) ) << 24 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[4] ) ) << 32 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[5] ) ) << 40 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[6] ) ) << 48 )
				| ( static_cast<std::uint64_t>( std::uint8_t( p[7] ) ) << 56 ) );
		}
	}

	///	@brief	xxHash.
	template <int N>
	class hash
	{
	public:
	};


	///	@brief	xxHash32
	template<>
	class hash<32>
	{
	public:
		///	@brief	xxHash32 data.
		using hash_type = std::uint32_t;
		using long_type = std::uint64_t;

		///	@brief	xxHash32.
		///	@param	buf		data.
		///	@param	len		data length(byte).
		///	@param	seed	seed.
		///	@return	xxHash32
		constexpr static hash_type xxh( const char* input, std::size_t len, hash_type seed )
		{
			hash_type acc = 0;
			if ( input == nullptr )
			{
				len = 0;
				// step 1.
				acc = static_cast<hash_type>( seed + static_cast<long_type>( prime( 4 ) ) );
				// step 4.
				acc = static_cast<hash_type>( static_cast<long_type>( acc ) + static_cast<long_type>( len ) );
				// step 6.
				acc = final_mix( acc );
				// step 7.
				return acc;
			}
			const char* src{ input };
			const char* end{ src + len };
			// step 1.
			if ( len >= 16 )
			{
				const char* limit{ end - 16 };
				hash_type acc0 = static_cast<hash_type>( seed + static_cast<long_type>( prime( 0 ) ) + static_cast<long_type>( prime( 1 ) ) );
				hash_type acc1 = static_cast<hash_type>( seed + static_cast<long_type>( prime( 1 ) ) );
				hash_type acc2 = seed + 0;
				hash_type acc3 = seed - prime( 0 );
				// step 2.
				do
				{
					acc0 = round( acc0, details::read<std::uint32_t>( src ) );
					src += sizeof( std::uint32_t );
					acc1 = round( acc1, details::read<std::uint32_t>( src ) );
					src += sizeof( std::uint32_t );
					acc2 = round( acc2, details::read<std::uint32_t>( src ) );
					src += sizeof( std::uint32_t );
					acc3 = round( acc3, details::read<std::uint32_t>( src ) );
					src += sizeof( std::uint32_t );
				} while ( src <= limit );
				// step 3.
				acc = convergence( acc0, acc1, acc2, acc3 );
			}
			else
			{
				acc = static_cast<hash_type>( seed + static_cast<long_type>( prime( 4 ) ) );
			}
			// step 4.
			acc = static_cast<hash_type>( static_cast<long_type>( acc ) + static_cast<long_type>( len ) );
			// step 5.
			if ( len >= 4 )
			{
				const char* limit{ end - 4 };
				while ( src <= limit )
				{
					acc = static_cast<hash_type>(
						details::rotl<hash_type>(
							static_cast<hash_type>(
								static_cast<long_type>( acc )
								+ static_cast<long_type>( ( details::read<std::uint32_t>( src ) )
									* static_cast<long_type>( prime( 2 ) ) ) )
							, 17 )
						* static_cast<long_type>( prime( 3 ) )
						);
					src += sizeof( std::uint32_t );
				}
			}
			if ( input != nullptr )
			{
				while ( src < end )
				{
					acc = static_cast<hash_type>(
						details::rotl<hash_type>(
							static_cast<long_type>( acc )
							+ static_cast<long_type>( details::read<std::uint8_t>( src ) )
							* static_cast<long_type>( prime( 4 ) )
							, 11 )
						* static_cast<long_type>( prime( 0 ) )
						);
					++src;
				}
			}
			// step 6.
			acc = final_mix( acc );
			// step 7.
			return acc;
		}

	private:
		constexpr static std::array<hash_type, 5> primes{ {
			2654435761U, 2246822519U, 3266489917U, 668265263U, 374761393U
		} };
		constexpr static hash_type prime( int i ) { return primes[i]; }

		constexpr static hash_type round( hash_type acc, hash_type input )
		{
			return static_cast<hash_type>(
				details::rotl<hash_type>(
					static_cast<hash_type>( static_cast<long_type>( static_cast<long_type>( acc ) + ( static_cast<long_type>( input ) * static_cast<long_type>( prime( 1 ) ) ) ) )
					, 13 )
				* static_cast<long_type>( prime( 0 ) )
				);
		}

		constexpr static hash_type convergence( hash_type acc0, hash_type acc1, hash_type acc2, hash_type acc3 )
		{
			return static_cast<hash_type>(
				static_cast<long_type>( details::rotl( acc0, 1 ) )
				+ static_cast<long_type>( details::rotl( acc1, 7 ) )
				+ static_cast<long_type>( details::rotl( acc2, 12 ) )
				+ static_cast<long_type>( details::rotl( acc3, 18 ) )
				);
		}

		constexpr static hash_type final_mix( hash_type acc )
		{
			acc = static_cast<hash_type>( ( acc ^ ( acc >> 15 ) ) * static_cast<long_type>( prime( 1 ) ) );
			acc = static_cast<hash_type>( ( acc ^ ( acc >> 13 ) ) * static_cast<long_type>( prime( 2 ) ) );
			acc = acc ^ ( acc >> 16 );
			return acc;
		}
	};


	///	@brief	xxHash64.
	template <>
	class hash<64>
	{
	public:
		///	@brief	xxHash64 data.
		using hash_type = std::uint64_t;
#if defined(XXHASH_CX_SUPPORT_NATIVE_INT128)
		using long_type = unsigned __int128_t;
#else
		using long_type = std::uintmax_t;
#endif // defined(XXHASH_CX_SUPPORT_INT128)

		///	@brief	xxHash64
		///	@param	buf		data.
		///	@param	len		data length(byte).
		///	@param	seed	seed.
		///	@return	xxHash64
		constexpr static hash_type xxh( const char* input, std::size_t len, hash_type seed )
		{
			hash_type acc = 0;
			if ( input == nullptr )
			{
				len = 0;
				// step 1.
				acc = static_cast<hash_type>( seed + static_cast<long_type>( prime( 4 ) ) );
				// step 4.
				acc += len;
				// step 6.
				acc = final_mix( acc );
				// step 7.
				return acc;
			}
			const char* src{ input };
			const char* end{ src + len };
			// step 1.
			if ( len >= 32 )
			{
				const char* limit{ end - 32 };
				hash_type acc0 = static_cast<hash_type>( seed + static_cast<long_type>( prime( 0 ) ) + static_cast<long_type>( prime( 1 ) ) );
				hash_type acc1 = static_cast<hash_type>( seed + static_cast<long_type>( prime( 1 ) ) );
				hash_type acc2 = seed + 0;
				hash_type acc3 = seed - prime( 0 );
				// step 2.
				do
				{
					acc0 = round( acc0, details::read<std::uint64_t>( src ) );
					src += sizeof( std::uint64_t );
					acc1 = round( acc1, details::read<std::uint64_t>( src ) );
					src += sizeof( std::uint64_t );
					acc2 = round( acc2, details::read<std::uint64_t>( src ) );
					src += sizeof( std::uint64_t );
					acc3 = round( acc3, details::read<std::uint64_t>( src ) );
					src += sizeof( std::uint64_t );
				} while ( src <= limit );
				// step 3.
				acc = convergence( acc0, acc1, acc2, acc3 );
			}
			else
			{
				acc = static_cast<hash_type>( seed + static_cast<long_type>( prime( 4 ) ) );
			}
			// step 4.
			acc += len;
			// step 5.
			if ( len >= 8 )
			{
				const char* limit{ end - 8 };
				while ( src <= limit )
				{
					acc = static_cast<hash_type>(
						details::rotl<std::uint64_t>( acc ^ round( 0, details::read<std::uint64_t>( src ) ), 27 )
						* static_cast<long_type>( prime( 0 ) ) + static_cast<long_type>( prime( 3 ) ) );
					src += sizeof( std::uint64_t );
				}
			}
			if ( len >= 4 )
			{
				const char* limit{ end - 4 };
				while ( src <= limit )
				{
					acc = static_cast<hash_type>(
						details::rotl<hash_type>( acc ^ static_cast<hash_type>( ( details::read<std::uint32_t>( src ) * static_cast<long_type>( prime( 0 ) ) ) ), 23 )
						* static_cast<long_type>( prime( 1 ) ) + static_cast<long_type>( prime( 2 ) ) );
					src += sizeof( std::uint32_t );
				}
			}
			if ( input != nullptr )
			{
				while ( src < end )
				{
					acc = static_cast<hash_type>(
						details::rotl<hash_type>( acc ^ ( details::read<std::uint8_t>( src ) * static_cast<long_type>( prime( 4 ) ) ), 11 )
						* static_cast<long_type>( prime( 0 ) ) );
					++src;
				}
			}
			// step 6.
			acc = final_mix( acc );
			// step 7.
			return acc;
		}

	private:
		constexpr static std::array<hash_type, 5> primes{ {
			11400714785074694791ULL, 14029467366897019727ULL, 1609587929392839161ULL, 9650029242287828579ULL, 2870177450012600261ULL
		} };
		constexpr static hash_type prime( int i ) { return primes[i]; }

		constexpr static hash_type round( hash_type acc, hash_type input )
		{
			acc = static_cast<hash_type>( acc + ( static_cast<long_type>( input ) * static_cast<long_type>( prime( 1 ) ) ) );
			acc = details::rotl( acc, 31 );
			return static_cast<hash_type>( acc * static_cast<long_type>( prime( 0 ) ) );
		}

		constexpr static hash_type mearge_accumulator( hash_type acc, hash_type acc_n )
		{
			return static_cast<hash_type>(
				( ( acc ^ round( 0, acc_n ) ) * static_cast<long_type>( prime( 0 ) ) )
				+ static_cast<long_type>( prime( 3 ) )
				);
		}

		constexpr static hash_type convergence( hash_type acc0, hash_type acc1, hash_type acc2, hash_type acc3 )
		{
			hash_type acc = static_cast<hash_type>(
				static_cast<long_type>( details::rotl( acc0, 1 ) )
				+ static_cast<long_type>( details::rotl( acc1, 7 ) )
				+ static_cast<long_type>( details::rotl( acc2, 12 ) )
				+ static_cast<long_type>( details::rotl( acc3, 18 ) )
				);
			acc = mearge_accumulator( acc, acc0 );
			acc = mearge_accumulator( acc, acc1 );
			acc = mearge_accumulator( acc, acc2 );
			acc = mearge_accumulator( acc, acc3 );
			return acc;
		}

		constexpr static hash_type final_mix( hash_type acc )
		{
			acc = static_cast<hash_type>( ( acc ^ ( acc >> 33 ) ) * static_cast<long_type>( prime( 1 ) ) );
			acc = static_cast<hash_type>( ( acc ^ ( acc >> 29 ) ) * static_cast<long_type>( prime( 2 ) ) );
			acc = ( acc ^ ( acc >> 32 ) );
			return acc;
		}

	};


	///	@brief	xxHash32.
	///	@param	buf		data.
	///	@param	len		data length(byte).
	///	@param	seed	seed.
	///	@return	xxHash32
	constexpr hash<32>::hash_type xxh32( const char* buf, std::size_t len, hash<32>::hash_type seed )
	{
		return hash<32>::xxh( buf, len, seed );
	}

	///	@brief	xxHash64.
	///	@param	buf		data.
	///	@param	len		data length(byte).
	///	@param	seed	seed.
	///	@return	xxHash64
	constexpr hash<64>::hash_type xxh64( const char* buf, std::size_t len, hash<64>::hash_type seed )
	{
		return hash<64>::xxh( buf, len, seed );
	}

	///	@brief	literals namespace.
	inline namespace literals
	{

		///	@brief	user defined literals - xxHash32.
		constexpr hash<32>::hash_type operator"" _xxh32( const char* str, std::size_t len )
		{
			return xxh32( str, len, XXHASH_CX_XXH32_SEED );
		}

		///	@brief	user defined literals - xxHash64.
		constexpr hash<64>::hash_type operator"" _xxh64( const char* str, std::size_t len )
		{
			return xxh64( str, len, XXHASH_CX_XXH64_SEED );
		}

	}	// inline namespace literals.

}	// namespace xxhash.

#endif

