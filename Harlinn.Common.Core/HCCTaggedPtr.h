#pragma once
#ifndef HARLINN_COMMON_CORE_HCCTAGGEDPTR_H_
#define HARLINN_COMMON_CORE_HCCTAGGEDPTR_H_

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


#include <HCCDef.h>

namespace Harlinn::Common::Core
{
    namespace Internal
    {
        template <typename... Ts>
        struct unique_type_count;

        template <>
        struct unique_type_count<>
        {
            static constexpr std::size_t value = 0;
        };

        template <typename T, typename... Rest>
        struct unique_type_count<T, Rest...>
        {
            // If T is in Rest, add 0; otherwise, add 1
            static constexpr bool is_new = ( !std::is_same_v<T, Rest> && ... );
            static constexpr std::size_t value =
                ( is_new ? 1 : 0 ) + unique_type_count<Rest...>::value;
        };

        // Helper variable template
        template <typename... Ts>
        inline constexpr std::size_t unique_type_count_v = unique_type_count<Ts...>::value;


        // Utility template to find the index of a type within a type pack (the Tag ID)
        template <typename T, typename... Types>
        struct TypeIndex;

        // Base case: Type not found (should trigger static_assert or compilation error)
        template <typename T>
        struct TypeIndex<T> : std::integral_constant<std::uint16_t, 0>
        {
            static_assert( sizeof( T ) == 0, "Type not found in AllowedTypes" );
        };

        template <typename T, typename... Types>
        struct TypeIndex<T, T, Types...> : std::integral_constant<std::uint16_t, 0> {};

        template <typename T, typename First, typename... Types>
        struct TypeIndex<T, First, Types...> : std::integral_constant<std::uint16_t, 1 + TypeIndex<T, Types...>::value> {};
    }

    /// <summary>
    /// A type-safe tagged pointer that can hold a pointer to one of the specified types.
    /// </summary>
    /// <typeparam name="...AllowedTypes">The types that the tagged pointer can hold.</typeparam>
    /// <remarks>
    /// See the <a href="https://en.wikipedia.org/wiki/Tagged_pointer">Wikipedia 
    /// article on tagged pointers</a> for more information.
    /// </remarks>
    template <typename... AllowedTypes>
    class TaggedPtr
    {
    private:
        static constexpr std::uintptr_t PtrMask = 0x01FFFFFFFFFFFFFFULL;
        static constexpr int TagShift = 57;

        std::uintptr_t encoded_{ 0 };

        // Safely strip the tag and cast back to the target type
        template <typename T>
        constexpr [[nodiscard]] T* UncheckedGet( ) const noexcept
        {
            return std::bit_cast<T*>( encoded_ & PtrMask );
        }

        
        static_assert( sizeof...( AllowedTypes ) == Internal::unique_type_count_v<AllowedTypes...>, "AllowedTypes must be unique" );
        static_assert( sizeof...( AllowedTypes ) <= ( ( 1u << ( 64 - TagShift ) ) ), "Too many AllowedTypes for the available tag bits." );
    public:

        /// <summary>
        /// Default constructor
        /// </summary>
        constexpr TaggedPtr( ) noexcept = default;

        /// <summary>
        /// Type-safe conversion constructor
        /// </summary>
        /// <typeparam name="T">
        /// The type of the pointer being wrapped. Must be one of the AllowedTypes.
        /// </typeparam>
        /// <param name="ptr">The pointer to wrap.</param>
        template <typename T >
            requires ( ( std::is_same_v<std::remove_cv_t<T>, AllowedTypes> || ... ) )
        constexpr TaggedPtr( T* ptr ) noexcept
        {
            if ( ptr )
            {
                std::uintptr_t rawPtr = std::bit_cast< std::uintptr_t >( ptr );
                assert( ( rawPtr & ~PtrMask ) == 0 && "Pointer overflows 57-bit address space!" );

                // Auto-resolve the exact tag ID at compile-time based on the class type
                constexpr std::uint16_t tag_id = Internal::TypeIndex<std::remove_cv_t<T>, AllowedTypes...>::value;
                encoded_ = ( static_cast< std::uintptr_t >( tag_id ) << TagShift ) | ( rawPtr & PtrMask );
            }
        }

        /// <summary>
        /// Constructor for nullptr
        /// </summary>
        /// <param name="np">A nullptr value</param>
        constexpr TaggedPtr( std::nullptr_t np ) noexcept 
        { };


        constexpr [[nodiscard]] bool operator==( const TaggedPtr& other ) const noexcept
        {
            return encoded_ == other.encoded_;
        };

        constexpr [[nodiscard]] bool operator!=( const TaggedPtr& other ) const noexcept
        {
            return encoded_ != other.encoded_;
        };

        constexpr [[nodiscard]] bool operator > ( const TaggedPtr& other ) const noexcept
        {
            return encoded_ > other.encoded_;
        };

        constexpr [[nodiscard]] bool operator < ( const TaggedPtr& other ) const noexcept
        {
            return encoded_ < other.encoded_;
        };

        
        /// <summary>
        /// Equality comparison operator for nullptr
        /// </summary>
        /// <param name="np">A nullptr value</param>
        /// <returns>True if the tagged pointer is null, false otherwise.</returns>
        constexpr [[nodiscard]] bool operator==( std::nullptr_t ) const noexcept
        {
            return ( encoded_ & PtrMask ) == 0;
        }

        /// <summary>
        /// Inequality comparison operator for nullptr
        /// </summary>
        /// <param name="np">A nullptr value</param>
        /// <returns>True if the tagged pointer is not null, false otherwise.</returns>
        constexpr [[nodiscard]] bool operator!=( std::nullptr_t ) const noexcept
        {
            return ( encoded_ & PtrMask ) != 0;
        }


        template <typename U>
            requires ( ( std::is_same_v<std::remove_cv_t<U>, AllowedTypes> || ... ) )
        constexpr [[nodiscard]] bool operator==( const U* other ) const noexcept
        {
            if ( other == nullptr )
            {
                return ( encoded_ & PtrMask ) == 0;
            }
            constexpr std::uint16_t tagId = Internal::TypeIndex<std::remove_cv_t<U>, AllowedTypes...>::value;
            const std::uintptr_t expected = ( static_cast< std::uintptr_t >( tagId ) << TagShift ) | ( std::bit_cast< std::uintptr_t >( other ) & PtrMask );
            return encoded_ == expected;
        }

        template <typename U>
            requires ( ( std::is_same_v<std::remove_cv_t<U>, AllowedTypes> || ... ) )
        constexpr [[nodiscard]] bool operator!=( const U* other ) const noexcept
        {
            if ( other == nullptr )
            {
                return ( encoded_ & PtrMask ) != 0;
            }
            constexpr std::uint16_t tagId = Internal::TypeIndex<std::remove_cv_t<U>, AllowedTypes...>::value;
            const std::uintptr_t expected = ( static_cast< std::uintptr_t >( tagId ) << TagShift ) | ( std::bit_cast< std::uintptr_t >( other ) & PtrMask );
            return encoded_ != expected;
        }
        

        /// <summary>
        /// Gets the index of the currently active tag.
        /// </summary>
        /// <returns>The index of the active tag.</returns>
        [[nodiscard]] constexpr std::uint16_t TagIndex( ) const noexcept
        {
            return static_cast< std::uint16_t >( encoded_ >> TagShift );
        }

        /// <summary>
        /// Checks if the tagged pointer is not null.
        /// </summary>
        [[nodiscard]] explicit constexpr operator bool( ) const noexcept
        { 
            return ( encoded_ & PtrMask ) != 0; 
        }

        /// <summary>
        /// Checks if the tagged pointer is null.
        /// </summary>
        /// <returns>True if the tagged pointer is null, false otherwise.</returns>
        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return ( encoded_ & PtrMask ) == 0;
        }

        /// <summary>
        /// Checks if the tagged pointer is assigned (not null).
        /// </summary>
        /// <returns>True if the tagged pointer is assigned, false otherwise.</returns>
        [[nodiscard]] constexpr bool IsAssigned( ) const noexcept
        {
            return ( encoded_ & PtrMask ) != 0;
        }

        /// <summary>
        /// Checks if the tagged pointer is of the specified type.
        /// </summary>
        template <typename T>
        [[nodiscard]] constexpr bool Is( ) const noexcept
        {
            static_assert( ( std::is_same_v<std::remove_cv_t<T>, AllowedTypes> || ... ), "Requested type is not in the allowed list." );
            if ( IsAssigned( ) )
            {
                return TagIndex( ) == Internal::TypeIndex<std::remove_cv_t<T>, AllowedTypes...>::value;
            }
            return false;
        }

        /// <summary>
        /// Checks if the tagged pointer is of the specified type.
        /// </summary>
        template <typename T>
        [[nodiscard]] constexpr bool is( ) const noexcept
        {
            return Is<T>( );
        }

        /// <summary>
        /// Casts the tagged pointer to a pointer of the specified type.
        /// </summary>
        /// <typeparam name="T">
        /// The target type. Must be one of the AllowedTypes and must match the active tag.
        /// </typeparam>
        /// <typeparam name="Self">
        /// Deduced explicit object parameter type; propagates const-qualification of the
        /// tagged pointer to the returned pointer.
        /// </typeparam>
        /// <param name="self">The explicit object parameter (deducing this).</param>
        /// <returns>
        /// A pointer to <typeparamref name="T"/>. The pointee is const-qualified when the
        /// tagged pointer is const.
        /// </returns>
        /// <remarks>
        /// The active tag MUST match <typeparamref name="T"/>. This precondition is checked
        /// with an assertion in debug builds via Is&lt;T&gt;().
        /// </remarks>
        template <typename T, typename Self>
        [[nodiscard]] constexpr auto Cast( this Self&& self ) noexcept
        {
            // Preserve const-qualification of *this in the returned pointer type.
            using Result = std::conditional_t<std::is_const_v<std::remove_reference_t<Self>>, const T*, T*>;
            assert( self.template Is<T>( ) );
            return std::bit_cast< Result >( self.template UncheckedGet<T>( ) );
        }

        /// <summary>
        /// Casts the tagged pointer to a pointer of the specified type, or returns nullptr 
        /// if the type does not match.
        /// </summary>
        /// <typeparam name="T">
        /// The target type. Must be one of the AllowedTypes.
        /// </typeparam>
        /// <typeparam name="Self">
        /// Deduced explicit object parameter type; propagates const-qualification of the
        /// tagged pointer to the returned pointer.
        /// </typeparam>
        /// <param name="self">The explicit object parameter (deducing this).</param>
        /// <returns>
        /// A pointer to <typeparamref name="T"/>. The pointee is const-qualified when the
        /// tagged pointer is const. Returns nullptr if the active tag does not match <typeparamref name="T"/>.
        /// </returns>
        template <typename T, typename Self>
        [[nodiscard]] constexpr auto CastOrNullptr( this Self&& self ) noexcept
        {
            using Result = std::conditional_t<std::is_const_v<std::remove_reference_t<Self>>, const T*, T*>;
            if ( self.template Is<T>( ) )
            {
                return std::bit_cast< Result >( self.template UncheckedGet<T>( ) );
            }
            else
            {
                return static_cast< Result >( nullptr );
            }
        }



        /// <summary>
        /// Retrieves a pointer to the specified type if the active tag matches, or nullptr otherwise.
        /// </summary>
        /// <typeparam name="T">The target type. Must be one of the AllowedTypes.</typeparam>
        /// <returns>A pointer to <typeparamref name="T"/> if the active tag matches; otherwise, nullptr.</returns>
        template <typename T, typename Self>
        [[nodiscard]] constexpr auto get( this Self&& self ) noexcept
        {
            using Result = std::conditional_t<std::is_const_v<std::remove_reference_t<Self>>, const T*, T*>;
            return self.template Is<T>( ) ? std::bit_cast< Result >( self.template UncheckedGet<T>( ) ) : static_cast< Result >( nullptr );
        }

        template <typename Self>
        [[nodiscard]] constexpr auto ptr( this Self&& self ) noexcept
        {
            using Result = std::conditional_t<std::is_const_v<std::remove_reference_t<Self>>, const void*, void*>;

            return std::bit_cast< Result >( self.encoded_ & PtrMask );
        }

        /// <summary>
        /// Dispatches the invokable to the appropriate type based on the active tag.
        /// </summary>
        /// <typeparam name="Invokable">The callable to invoke with the active pointer.</typeparam>
        /// <typeparam name="Self">Deduced explicit object parameter; propagates const to the pointee.</typeparam>
        /// <param name="self">The explicit object parameter (deducing this).</param>
        /// <param name="invokable">The callable dispatched on the active alternative.</param>
        /// <returns>The (common) result of invoking <paramref name="invokable"/>.</returns>
        /// <remarks>
        /// The tagged pointer MUST be non-null; checked via assert in debug builds. Implemented as a
        /// switch over the tag index so the compiler may emit a jump table. Does not require the
        /// result type to be default-constructible.
        /// </remarks>
        template <typename Invokable, typename Self>
        constexpr auto Dispatch( this Self&& self, Invokable&& invokable )
        {
            assert( self && "Attempted to visit a null pointer!" );

            constexpr bool isConst = std::is_const_v<std::remove_reference_t<Self>>;

            using R = std::common_type_t<
                std::invoke_result_t<Invokable,
                std::conditional_t<isConst, const AllowedTypes*, AllowedTypes*>>...>;

            auto callAs = [ & ]<std::size_t Index>( ) -> R
            {
                using T = std::tuple_element_t<Index, std::tuple<AllowedTypes...>>;
                using PtrT = std::conditional_t<isConst, const T*, T*>;
                return std::forward<Invokable>( invokable )(
                    static_cast< PtrT >( self.template UncheckedGet<T>( ) ) );
            };

            const std::uint16_t tagIndex = self.TagIndex( );

            return[ & ]<std::size_t I>( this auto&& recurse, std::integral_constant<std::size_t, I> ) -> R
            {
                if constexpr ( I < sizeof...( AllowedTypes ) )
                {
                    switch ( tagIndex )
                    {
                        case I:
                            return callAs.template operator() < I > ( );
                        default:
                            return recurse( std::integral_constant<std::size_t, I + 1>{} );
                    }
                }
                else
                {
                    // tagIndex is always valid for a non-null TaggedPtr
                    std::unreachable( );
                }
            }( std::integral_constant<std::size_t, 0>{} );
        }

    };
}

#endif // HARLINN_COMMON_CORE_HCCTAGGEDPTR_H_
