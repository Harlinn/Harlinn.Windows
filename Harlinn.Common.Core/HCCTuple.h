#pragma once
#ifndef __HCCTUPLE_H__
#define __HCCTUPLE_H__
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    // std::tuple is fine for most purposes, but it is not packed, and:
    // 
    //          using TupleType = std::tuple<int, double>;
    // 
    //          TupleType value( 1, 2.0 );
    //          int* intValuePtr = std::addressof( std::get<0>( value ) );
    //          double* doubleValuePtr = std::addressof( std::get<1>( value ) );
    // 
    //          if ( reinterpret_cast<Byte*>( intValuePtr ) > reinterpret_cast<Byte*>( doubleValuePtr ) )
    //          {
    //              puts( "std::tuple has reverse order\n" );
    //          }
    // 
    //   will write "std::tuple has reverse order" to the console, while:
    // 
    //          using TupleType = Tuple<int, double>;
    //
    //          TupleType value( 1, 2.0 );
    //          int* intValuePtr = std::addressof( get<0>( value ) );
    //          double* doubleValuePtr = std::addressof( get<1>( value ) );
    //
    //          if ( reinterpret_cast<Byte*>( intValuePtr ) > reinterpret_cast<Byte*>( doubleValuePtr ) )
    //          {
    //              puts( "Tuple has reverse order\n" );
    //          }
    // 
    //   will not write anything.
    // 
    // The goal is not to create a replacement for std::tuple, just
    // something similar that can be used by Harlinn::Common::Core::Persistent
    // which requires a packed tuple type.
#pragma pack(push,1)

    namespace Internal
    {
        template <std::size_t index, typename T>
        class TupleValue
        {
            T value_;
        public:
            using ValueType = T;
            constexpr TupleValue( ) noexcept
                : value_{}
            {
            }
            constexpr TupleValue( const T& value ) noexcept
                : value_( value )
            {

            }

            constexpr TupleValue( const TupleValue& other ) = default;
            constexpr TupleValue( TupleValue&& other ) noexcept = default;

            template<typename U>
                requires ( std::is_same_v< TupleValue<index, T>, std::remove_cvref_t<U> > == false )
            constexpr TupleValue( U&& value ) noexcept
                : value_( std::forward<U>( value ) )
            {

            }

            constexpr TupleValue& operator = ( const TupleValue& other ) = default;
            constexpr TupleValue& operator = ( TupleValue&& other ) noexcept = default;

            constexpr T& get( ) noexcept
            {
                return value_;
            }

            constexpr const T& get( ) const noexcept
            {
                return value_;
            }

            auto operator<=>( const TupleValue& ) const = default;
        };

        template <std::size_t index, typename... types>
        class TupleBase
        {
        public:
            auto operator<=>( const TupleBase& ) const = default;
        };

        template <std::size_t index, typename T, typename... types>
        class TupleBase<index, T, types...> : public TupleValue<index, T>, public TupleBase<index + 1, types...>
        {
        public:

            constexpr TupleBase( ) noexcept
            {
            }

            template <typename Arg, typename... Args>
            constexpr TupleBase( Arg&& arg, Args &&... args ) noexcept
                : TupleValue<index, T>( std::forward<Arg>( arg ) ),
                TupleBase<index + 1, types...>( std::forward<Args>( args )... )
            {
            }

            auto operator<=>( const TupleBase& ) const = default;
        };
    }

    template<typename ...Types>
    class Tuple;


    template<typename T, typename ...Types>
    class Tuple<T, Types...> : public Internal::TupleBase<0, T, Types...>
    {
    public:
        using Base = Internal::TupleBase<0, T, Types...>;
        static constexpr size_t Size = 1 + sizeof...( Types );

        constexpr Tuple( ) noexcept
        {
        }

        constexpr Tuple( const Tuple& other ) noexcept = default;
        constexpr Tuple( Tuple&& other ) noexcept = default;


        template <typename Arg, typename... Args>
            requires ( std::is_same_v<std::remove_cvref_t<Arg>, Tuple<T, Types...>> == false )
        constexpr Tuple( Arg&& arg, Args&&... args ) noexcept
            : Base( std::forward<Arg>( arg ), std::forward<Args>( args )... )
        {
        }

        constexpr Tuple& operator = ( const Tuple& other ) = default;
        constexpr Tuple& operator = ( Tuple&& other ) noexcept = default;

        auto operator<=>( const Tuple& ) const = default;

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        constexpr size_t ByteSize( ) const noexcept
        {
            return sizeof( Internal::TupleBase<0, T, Types...> );
        }
    };

    template<>
    class Tuple<>
    {
    public:
        static constexpr size_t Size = 0;

        constexpr Tuple( ) noexcept = default;
        constexpr Tuple( const Tuple& ) noexcept
        {
        }

        auto operator<=>( const Tuple& ) const = default;

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        constexpr size_t ByteSize( ) const noexcept
        {
            return sizeof( Tuple<> );
        }

        constexpr Tuple& operator = ( const Tuple& other ) = default;
        constexpr Tuple& operator = ( Tuple&& other ) noexcept = default;

    };


    template <typename... Args>
    Tuple( Args... args )->Tuple<Args...>;

    template <typename... Args>
    Tuple( const Tuple<Args...>& args )->Tuple<Args...>;





    template<std::size_t index, typename... Args>
    struct TupleElement
    {
        using Types = TypeList<Args...>;
        using type = typename Meta::At<Types, index>;
    };

    template<std::size_t index, typename... Args>
    using TupleElement_t = typename TupleElement<index, Args...>::type;


    template <std::size_t index, typename... Args>
    constexpr TupleElement_t<index, Args...>& get( Tuple<Args...>& tuple )
    {
        static_assert( index < Tuple<Args...>::Size );
        return ( static_cast<Internal::TupleValue<index, Meta::At<Tuple<Args...>, index> >&>( tuple ) ).get( );
    }
    template <std::size_t index, typename... Args>
    constexpr const TupleElement_t<index, Args...>& get( const Tuple<Args...>& tuple )
    {
        static_assert( index < Tuple<Args...>::Size );
        return ( static_cast<const Internal::TupleValue<index, Meta::At<Tuple<Args...>, index> >&>( tuple ) ).get( );
    }

    template <std::size_t index, typename... Args>
    constexpr TupleElement_t<index, Args...>&& get( Tuple<Args...>&& tuple )
    {
        static_assert( index < Tuple<Args...>::Size );
        return static_cast<TupleElement_t<index, Args...>&&>( ( static_cast<Internal::TupleValue<index, Meta::At<Tuple<Args...>, index> >&>( tuple ) ).get( ) );
    }
    template <std::size_t index, typename... Args>
    constexpr const TupleElement_t<index, Args...>&& get( const Tuple<Args...>&& tuple )
    {
        static_assert( index < Tuple<Args...>::Size );
        return static_cast<const TupleElement_t<index, Args...>&&>( ( static_cast<Internal::TupleValue<index, Meta::At<Tuple<Args...>, index> >&>( tuple ) ).get( ) );
    }

    namespace Internal
    {
        template <class CallableT, class TupleT, size_t... indices>
        constexpr decltype( auto ) ApplyImpl( CallableT&& callable, TupleT&& tuple, std::index_sequence<indices...> )
        {
            return std::invoke( std::forward<CallableT>( callable ), get<indices>( std::forward<TupleT>( tuple ) )... );
        }
    }

    template <class CallableT, class TupleT>
    constexpr decltype( auto ) Apply( CallableT&& callable, TupleT&& tuple )
    {
        return Internal::ApplyImpl( std::forward<CallableT>( callable ), std::forward<TupleT>( tuple ), std::make_index_sequence< std::remove_cvref_t<TupleT>::Size >{} );
    }

    namespace Internal
    {
        template<typename ...Types>
        struct TupleTypeFor
        {
            using type = Tuple<Types...>;
        };

        template<typename ...Types>
        struct TupleTypeForDecay
        {
            using type = Tuple<std::decay_t<Types>...>;
        };

        template<typename ...Types>
        constexpr auto MakeTupleDecayTypeHelper( Types&&... args )
        {
            using TupleType = Tuple<std::decay_t<Types>...>;
            TupleType* result = nullptr;
            return result;
        }
    }


    /// <summary>
    /// Creates a Tuple from the arguments
    /// </summary>
    template <class... Args>
    [[nodiscard]] constexpr Tuple<Internal::ToReferenceIfReferenceWrapper_t<Args>...> MakeTuple( Args&&... args )
    {
        using TupleType = Tuple<Internal::ToReferenceIfReferenceWrapper_t<Args>...>;
        return TupleType( std::forward<Args>( args )... );
    }

    /// <summary>
    /// Creates a Tuple of references from arguments
    /// </summary>
    template <class... Args>
    [[nodiscard]] constexpr Tuple<Args&...> Tie( Args&... args ) noexcept
    {
        using TupleType = Tuple<Args&...>;
        return TupleType( args... );
    }



    template <class... Args>
    [[nodiscard]] constexpr Tuple<Args&&...> ForwardAsTuple( Args&&... args ) noexcept
    {
        return Tuple<Args&&...>( std::forward<Args>( args )... );
    }



    namespace Internal
    {
        template <typename T1, typename T2>
        struct MergeSequences;

        // merges two std::index_sequence types
        template <size_t... firstIndexes, size_t... secondIndexes>
        struct MergeSequences<std::index_sequence<firstIndexes...>, std::index_sequence<secondIndexes...>>
        {
            using type = std::index_sequence<firstIndexes..., secondIndexes...>;
        };

        template <typename Type, typename... Types>
        struct AsTuple
        {
            // TupleCat() supports only tuples (std::tuple and Tuple), pairs, and arrays
            static_assert( False_v<Type>, "Unsupported TupleCat arguments." );
        };

        template <typename... Types>
        struct AsTuple<std::tuple<Types...>>
        {
            // std::tuple as a Tuple
            using type = Tuple<Types...>;
        };

        template <typename... Types>
        struct AsTuple<Tuple<Types...>>
        {
            // Tuple as a Tuple
            using type = Tuple<Types...>;
        };

        template <typename... Types>
        struct AsTuple<TypeList<Types...>>
        {
            // TypeList as a Tuple
            using type = Tuple<Types...>;
        };


        template <typename T1, typename T2>
        struct AsTuple<std::pair<T1, T2>>
        {
            // std::pair as a tuple
            using type = Tuple<T1, T2>;
        };

        // std::array as a tuple; ends recursion at 0
        template <typename T, typename... Types>
        struct AsTuple<std::array<T, 0>, Types...>
        {
            using type = Tuple<Types...>;
        };

        // std::array as a tuple; counts down to 0
        template <typename T, size_t N, typename... Types>
        struct AsTuple<std::array<T, N>, Types...>
            : AsTuple<std::array<T, N - 1>, T, Types...>
        {
        };

        // repeats _Nx for each _Ty in a parameter pack
        template <size_t _Nx, typename T>
        struct _Repeat_for : std::integral_constant<size_t, _Nx>
        {
        };

        template <typename TupleType, typename I_arg, typename J_arg, size_t J_next, typename... Tuples>
        struct TupleCat2
        {
            // determine tuple_cat's return type and I/J indices
            static_assert( sizeof...( Tuples ) == 0, "Unsupported TupleCat arguments." );
            using type = TupleType;
            using I_arg_seq = I_arg;
            using J_arg_seq = J_arg;
        };

        template <typename... Types1, typename I_arg, size_t... J, size_t J_next, typename... Types2, typename... Rest>
        struct TupleCat2<Tuple<Types1...>, I_arg, std::index_sequence<J...>, J_next, Tuple<Types2...>, Rest...>
            : TupleCat2<Tuple<Types1..., Types2...>,
            typename MergeSequences<I_arg, std::index_sequence_for<Types2...>>::type,
            std::index_sequence<J..., _Repeat_for<J_next, Types2>::value...>, J_next + 1, Rest...>
        {
            // determine tuple_cat's return type and I/J indices
        };

        template <typename... Tuples>
        struct TupleCatTraits : TupleCat2<Tuple<>, std::index_sequence<>, std::index_sequence<>, 0,
            typename AsTuple<std::decay_t<Tuples>>::type...>
        {
        };

        template <typename ResultType, size_t... I, size_t... J, typename T>
        constexpr ResultType TupleCatImpl( std::index_sequence<I...>, std::index_sequence<J...>, T&& arg )
        {
            using namespace std;
            // concatenate tuples
            return ResultType( get<I>( get<J>( forward<T>( arg ) ) )... );
        }

    }

    template <typename... Tuples>
    [[nodiscard]] constexpr typename Core::Internal::TupleCatTraits<Tuples...>::type TupleCat( Tuples&&... tuples )
    {
        using TupleCatTraits = Core::Internal::TupleCatTraits<Tuples...>;
        return Core::Internal::TupleCatImpl<typename TupleCatTraits::type>( typename TupleCatTraits::I_arg_seq( ), typename TupleCatTraits::J_arg_seq( ), ForwardAsTuple( std::forward<Tuples>( tuples )... ) );
    }

#pragma pack(pop)
}

#endif
