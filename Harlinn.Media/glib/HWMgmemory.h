#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGMEMORY_H_
#define HARLINN_MEDIA_GLIB_HWMGMEMORY_H_

/*
   Copyright 2024 Espen Harlinn

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


#include <HWMDef.h>
namespace Harlinn::Media::GLib
{


    // The purpose of the FreeMemoryDeleter is to
    // call FreeMemory - it will *not* run any destructor code
    // and should only be used to release memory allocated
    // by GStreamer and related dll's for objects that
    // do not have their own g_xxx_free/g_xxx_unref or similar
    // functionality implemented for them by those dlls.  
    template<typename T>
    struct FreeMemoryDeleter 
    {
        FreeMemoryDeleter( ) = default;
        template <typename T2, std::enable_if_t<std::is_convertible_v<T2*, T*>, int> = 0>
        FreeMemoryDeleter( const FreeMemoryDeleter<T2>& ) noexcept
        {}

        void operator()( T* ptr ) const noexcept 
        { 
            if ( ptr )
            {
                g_free( ptr );
            }
        }
    };
    template<typename T>
    struct FreeMemoryDeleter<T[]>
    {
        FreeMemoryDeleter( ) = default;
        
        template <typename T2, std::enable_if_t<std::is_convertible_v<T2( * )[ ], T( * )[ ]>, int> = 0>
        FreeMemoryDeleter( const FreeMemoryDeleter<T2[ ]>& ) noexcept
        {
        }

        template <typename T2, std::enable_if_t<std::is_convertible_v<T2( * )[ ], T( * )[ ]>, int> = 0>
        void operator()( T2* ptr ) const noexcept
        { 
            if ( ptr )
            {
                g_free( ptr );
            }
        }
    };

    template<typename T>
    using FreeMemoryPtr = std::unique_ptr<T, FreeMemoryDeleter<T>>;

    template<typename T>
    struct ObjectTraits : std::false_type
    {
        using WrappedType = void;
    };


    template<typename DerivedTraitsT, typename T>
    struct SimpleObjectTraits : public std::true_type
    {
        using DerivedTraitsType = DerivedTraitsT;
        using WrappedType = T;

        static constexpr bool IsFloating( WrappedType* wrapped )
        {
            return false;
        }

        static constexpr WrappedType* RefSink( WrappedType* wrapped )
        {
            return wrapped;
        }

        static constexpr WrappedType* TakeRef( WrappedType* wrapped )
        {
            return DerivedTraitsType::Ref( wrapped );
        }

        static constexpr WrappedType* Ref( WrappedType* wrapped )
        {
            return wrapped;
        }


        static constexpr void Unref( WrappedType* wrapped )
        {
            
        }
    };

    template<>
    struct ObjectTraits<GObject> : std::true_type
    {
        using WrappedType = GObject;

        static bool IsFloating( WrappedType* wrapped )
        {
            return g_object_is_floating( wrapped ) != 0;
        }

        static WrappedType* RefSink( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_ref_sink( wrapped ) );
        }

        static WrappedType* TakeRef( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_take_ref( wrapped ) );
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_object_unref( wrapped );
        }
    };

    

    template<>
    struct ObjectTraits<GBinding> : public SimpleObjectTraits< ObjectTraits<GBinding>, GBinding >
    {
        static void Unref( WrappedType* wrapped )
        {
            g_binding_unbind( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GClosure> : public SimpleObjectTraits< ObjectTraits<GClosure>, GClosure >
    {
        static WrappedType* RefSink( WrappedType* wrapped )
        {
            if ( wrapped )
            {
                g_closure_ref( wrapped );
                g_closure_sink( wrapped );
            }
            return wrapped;
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_closure_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_closure_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GParamSpec> : public SimpleObjectTraits< ObjectTraits<GParamSpec>, GParamSpec >
    {
        static WrappedType* RefSink( WrappedType* wrapped )
        {
            if ( wrapped )
            {
                return g_param_spec_ref_sink( wrapped );
            }
            return wrapped;
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_param_spec_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_param_spec_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GMainContext> : public SimpleObjectTraits< ObjectTraits<GMainContext>, GMainContext >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_main_context_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_main_context_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GMainLoop> : public SimpleObjectTraits< ObjectTraits<GMainLoop>, GMainLoop >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_main_loop_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_main_loop_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GSource> : public SimpleObjectTraits< ObjectTraits<GSource>, GSource >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_source_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_source_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstIterator> : public SimpleObjectTraits< ObjectTraits<GstIterator>, GstIterator >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_iterator_free( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GThread> : public SimpleObjectTraits< ObjectTraits<GThread>, GThread >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_thread_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_thread_unref( wrapped );
        }
    };


    template<typename T>
    constexpr bool ObjectTraits_v = ObjectTraits<T>::value;

    enum class ReferenceType
    {
        None,
        Ref,
        RefSink,
        TakeRef
    };


    template<typename DerivedT, typename WrappedT, typename WrappedTraitsT = ObjectTraits<WrappedT> >
    class ReferenceBase
    {
    public:
        using DerivedType = DerivedT;
        using WrappedType = WrappedT;
        using WrappedTraits = WrappedTraitsT;
    private:
        WrappedType* wrapped_ = nullptr;
    public:
        ReferenceBase( ) = default;
        ReferenceBase( WrappedType* wrapped, ReferenceType referenceType = ReferenceType::None )
            : wrapped_( wrapped )
        { 
            if ( wrapped_ )
            {
                switch ( referenceType )
                {
                    case ReferenceType::Ref:
                        WrappedTraits::Ref( wrapped_ );
                        break;
                    case ReferenceType::RefSink:
                        WrappedTraits::RefSink( wrapped_ );
                        break;
                    case ReferenceType::TakeRef:
                        WrappedTraits::TakeRef( wrapped_ );
                        break;
                }
            }
        }
        ReferenceBase( const ReferenceBase& other ) = delete;
        ReferenceBase( ReferenceBase&& other ) noexcept
            : wrapped_( other.wrapped_ )
        {
            other.wrapped_ = nullptr;
        }

        ~ReferenceBase( )
        {
            if ( wrapped_ )
            {
                WrappedTraits::Unref( wrapped_ );
            }
        }

        ReferenceBase& operator = ( const ReferenceBase& other ) = delete;

        ReferenceBase& operator = ( ReferenceBase&& other ) noexcept
        {
            std::swap( wrapped_, other.wrapped_ );
            return *this;
        }

        void Assign( WrappedType* wrapped, ReferenceType referenceType = ReferenceType::None )
        {
            if ( wrapped_ != wrapped )
            {
                if ( wrapped_ )
                {
                    WrappedTraits::Unref( wrapped_ );
                }
                wrapped_ = wrapped;
                if ( wrapped_ )
                {
                    switch ( referenceType )
                    {
                        case ReferenceType::Ref:
                            WrappedTraits::Ref( wrapped_ );
                            break;
                        case ReferenceType::RefSink:
                            WrappedTraits::RefSink( wrapped_ );
                            break;
                        case ReferenceType::TakeRef:
                            WrappedTraits::TakeRef( wrapped_ );
                            break;
                    }
                }
            }
        }

        ReferenceBase& operator = ( WrappedType* wrapped ) noexcept
        {
            Assign( wrapped );
            return *this;
        }

        [[nodiscard]]
        WrappedType* get( ) const
        {
            return wrapped_;
        }

        [[nodiscard]]
        explicit operator bool( ) const noexcept
        {
            return wrapped_ != nullptr;
        }

        [[nodiscard]]
        WrappedType* Detach( )
        {
            WrappedType* tmp = wrapped_;
            wrapped_ = nullptr;
            return tmp;
        }

        [[nodiscard]]
        operator WrappedType* ( ) const
        {
            return wrapped_;
        }
    };

    template<typename T>
    class Attached : public T
    {
    public:
        using Base = T;
        using WrappedType = typename T::WrappedType;
        using WrappedTraits = typename T::WrappedTraits;

        template<typename ... Args>
            requires std::is_constructible_v<T, Args...>
        Attached( Args&& ... args )
            : Base( std::forward<Args>( args ) ... )
        { }


        ~Attached( )
        {
            (void)Base::Detach( );
        }

    };

}

#endif
