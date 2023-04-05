#pragma once
#ifndef HARLINN_COMMON_CORE_HCCREFERENCE_H_
#define HARLINN_COMMON_CORE_HCCREFERENCE_H_

#include <HCCDef.h>
#include <atomic>

namespace Harlinn::Common::Core
{
    template<typename DerivedT>
    class ReferenceCountedBase
    {
        mutable std::atomic<UInt32> referenceCount_;
    public:
        constexpr ReferenceCountedBase( ) noexcept
            : referenceCount_( 1 )
        { }
    private:
        // Neither move nor copy ...
        ReferenceCountedBase( ReferenceCountedBase&& ) = delete;
        ReferenceCountedBase( const ReferenceCountedBase& ) = delete;
        ReferenceCountedBase& operator=( ReferenceCountedBase&& ) = delete;
        ReferenceCountedBase& operator=( const ReferenceCountedBase& ) = delete;
    protected:
        ~ReferenceCountedBase( ) noexcept
        { }
    public:
        UInt32 AddRef( ) const noexcept
        {
            return referenceCount_.fetch_add( 1, std::memory_order_relaxed ) + 1;
        }
        void ref( ) const
        {
            (void)referenceCount_.fetch_add( 1, std::memory_order_relaxed );
        }

        UInt32 Release( ) const noexcept
        {
            auto result = referenceCount_.fetch_sub( 1, std::memory_order_acq_rel );
            if ( result == 1)
            {
                auto* ptr = static_cast<DerivedT*>( const_cast<ReferenceCountedBase<DerivedT>*>( this ) );
                delete ptr;
            }
            return result;
        }

        void deref( ) const
        {
            Release( );
        }
        void unref( ) const
        {
            Release( );
        }

        bool unique( ) const
        {
            return referenceCount_.load( std::memory_order_acquire ) == 1;
        }

        UInt32 refCount( ) const
        {
            return referenceCount_.load( std::memory_order_acquire );
        }
    };


    class ReferenceCounted : public ReferenceCountedBase<ReferenceCounted>
    {
    public:
        using Base = ReferenceCountedBase;

        constexpr ReferenceCounted( ) = default;
        virtual ~ReferenceCounted( )
        { }
    };


    template <typename T> 
    class Reference
    {
    public:
        using element_type = T;
    private:
        T* referenced_ = nullptr;

        template<typename U>
        static U* AddRef( U* referenced )
        {
            if ( referenced )
            {
                referenced->AddRef( );
            }
            return referenced;
        }
        template<typename U>
        static U* AddRef( U* referenced, bool addReference )
        {
            if ( referenced && addReference )
            {
                referenced->AddRef( );
            }
            return referenced;
        }

        template<typename U>
        static void Release( U* referenced )
        {
            if ( referenced )
            {
                referenced->Release( );
            }
        }
    public:

        constexpr Reference( ) 
        {}
        constexpr Reference( std::nullptr_t ) 
        {}

        Reference( const Reference<T>& other ) 
            : referenced_( AddRef( other.get( ) ) )
        {}

        template <typename U>
            requires std::is_convertible_v<U*, T*>
        Reference( const Reference<U>& other ) 
            : referenced_( AddRef( other.get( ) ) )
        {}

        Reference( Reference<T>&& other )
            : referenced_( other.release( ) )
        {}

        template <typename U>
            requires std::is_convertible_v<U*, T*>
        Reference( Reference<U>&& other )
            : referenced_( other.release( ) )
        {}

        explicit Reference( T* referenced, bool addRef = false )
            : referenced_( AddRef( referenced, addRef ) )
        {}

        ~Reference( )
        {
            Release( referenced_ );
        }

        Reference<T>& operator=( std::nullptr_t ) 
        { 
            reset( );
            return *this; 
        }

        Reference<T>& operator=( const Reference<T>& other )
        {
            if ( this != &other )
            {
                reset( AddRef( other.get( ) ) );
            }
            return *this;
        }
        template <typename U>
            requires std::is_convertible_v<U*, T*>
        Reference<T>& operator=( const Reference<U>& other )
        {
            reset( AddRef( other.get( ) ) );
            return *this;
        }

        Reference<T>& operator=( Reference<T>&& other )
        {
            reset( other.release( ) );
            return *this;
        }
        template <typename U>
            requires std::is_convertible_v<U*, T*>
        Reference<T>& operator=( Reference<U>&& other )
        {
            reset( other.release( ) );
            return *this;
        }

        T& operator*( ) const
        {
            return *get( );
        }

        explicit operator bool( ) const 
        { 
            return this->get( ) != nullptr; 
        }

        T* get( ) const 
        { 
            return referenced_; 
        }
        T* operator->( ) const 
        { 
            return referenced_; 
        }

        void reset( T* ptr = nullptr )
        {
            T* tmp = referenced_;
            referenced_ = ptr;
            Release( tmp );
        }

        [[nodiscard]]
        constexpr T* release( ) noexcept
        {
            T* result = referenced_;
            referenced_ = nullptr;
            return result;
        }

        constexpr void swap( Reference<T>& other ) noexcept
        {
            using std::swap;
            swap( referenced_, other.referenced_ );
        }
    };

    template <typename T> 
    inline constexpr void swap( Reference<T>& first, Reference<T>& second ) noexcept
    {
        first.swap( second );
    }

    template <typename T, typename U> 
    inline constexpr bool operator==( const Reference<T>& lhs, const Reference<U>& rhs ) noexcept
    {
        return lhs.get( ) == rhs.get( );
    }
    template <typename T> 
    inline constexpr bool operator==( const Reference<T>& lhs, std::nullptr_t ) noexcept
    {
        return !lhs;
    }
    template <typename T> 
    inline constexpr bool operator==( std::nullptr_t, const Reference<T>& rhs ) noexcept
    {
        return !rhs;
    }

    template <typename T, typename U> 
    inline constexpr bool operator!=( const Reference<T>& lhs, const Reference<U>& rhs ) noexcept
    {
        return lhs.get( ) != rhs.get( );
    }
    template <typename T> 
    inline constexpr bool operator!=( const Reference<T>& lhs, std::nullptr_t ) noexcept
    {
        return static_cast<bool>( lhs );
    }
    template <typename T> 
    inline constexpr bool operator!=( std::nullptr_t, const Reference<T>& rhs ) noexcept
    {
        return static_cast<bool>( rhs );
    }

    template <typename T, typename... Args>
    Reference<T> MakeReference( Args&&... args )
    {
        return Reference<T>( new T( std::forward<Args>( args )... ) );
    }

    template <typename CharT, typename CharTraitsT, typename T>
    auto operator<<( std::basic_ostream<CharT, CharTraitsT>& ostream, const Reference<T>& reference ) -> decltype( ostream << reference.get( ) )
    {
        return ostream << reference.get( );
    }




}

#endif
