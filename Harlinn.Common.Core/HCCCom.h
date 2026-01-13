#pragma once
#ifndef __HCCCOM_H__
#define __HCCCOM_H__
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
#include <HCCException.h>
#include <HCCGuid.h>
#include <HCCString.h>
#include <HCCComInterfaces.h>
#include <HCCHandle.h>

namespace Harlinn::Common::Core
{
    
    enum class ThreadModel : DWORD
    {
        Unknown = 0,
        ApartmentThreaded = COINIT_APARTMENTTHREADED,
        MultiThreaded = COINIT_MULTITHREADED,
        DisableDDE = COINIT_DISABLE_OLE1DDE,
        SpeedOverMemory = COINIT_SPEED_OVER_MEMORY
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS(ThreadModel, DWORD);

    /// <summary>
    /// Initializes the COM library for use by the calling thread, 
    /// sets the thread's concurrency model, and creates a new apartment 
    /// for the thread if one is required. Calls CoUninitialize() in
    /// the destructor.
    /// </summary>
    class ComInitialize
    {
        Core::ThreadModel threadModel_;
        HRESULT result_ = S_OK;
    public:
        ComInitialize(Core::ThreadModel threadModel = Core::ThreadModel::MultiThreaded)
            : threadModel_(threadModel)
        {
            result_ = CoInitializeEx(nullptr, static_cast<DWORD>(threadModel));
        }
        ~ComInitialize()
        {
            CoUninitialize();
        }
        ComInitialize(const ComInitialize&) = delete;
        ComInitialize& operator = (const ComInitialize&) = delete;
        ComInitialize(ComInitialize&&) = delete;
        ComInitialize& operator = (ComInitialize&&) = delete;

        HRESULT Result() const noexcept
        {
            return result_;
        }

        Core::ThreadModel ThreadModel() const noexcept
        {
            return threadModel_;
        }


    };
    


    template<typename T>
    class ComPtr;

    /// <summary>
    /// Base wrapper for a COM interface pointer.
    /// </summary>
    /// <remarks>
    /// This class manages the lifetime of an underlying COM interface pointer
    /// by calling AddRef/Release where appropriate. It is intended to be used
    /// as a base class for strongly-typed COM interface wrappers in the library.
    /// Derived types typically expose typed accessors and convenience methods.
    /// </remarks>
    class Unknown 
    {
    protected:
        IUnknown* unknown_;
    public:
        /// <summary>
        /// Every derived class defines InterfaceType as the type of the interface
        /// wrapped by the derived class.
        /// </summary>
        using InterfaceType = IUnknown;
        /// <summary>
        /// The default constructor ensures that 
        /// the internal pointer to IUnknown
        /// is set to <c>nullptr</c>.
        /// </summary>
        constexpr Unknown( ) noexcept
            : unknown_( nullptr )
        {
        }

        /// <summary>
        /// Constructs a new <c>Unknown</c>, taking
        /// ownership of the interface pointer held
        /// by <c>unknown</c>.
        /// </summary>
        /// <param name="unknown">
        /// A pointer to an <c>IUnknown</c> interface,
        /// or an interface derived from <c>IUnknown</c>.
        /// </param>
        /// <param name="addref">
        /// If <c>true</c>, the constructor
        /// calls <c>AddRef</c> on the interface pointer held
        /// by <c>unknown</c>.
        /// </param>
        explicit Unknown( IUnknown* unknown, bool addref = false ) noexcept
            : unknown_( unknown )
        {
            if ( addref && ( unknown_ != nullptr ) )
            {
                unknown_->AddRef( );
            }
        }

        /// <summary>
        /// Initializes the new object to the interface identified
        /// by the <c>iid</c> parameter by querying the interface
        /// held by <c>unknown</c> for the requested interface.
        /// </summary>
        /// <param name="iid">
        /// The identifier of the requested interface.
        /// </param>
        /// <param name="unknown">
        /// The interface wrapper object that will be queried
        /// for the requested interface.
        /// </param>
        /// <param name="throwIfNoInterface">
        /// Set to <c>false</c> to prevent the constructor
        /// from throwing an exception if the requested interface
        /// is not supported. 
        /// </param>
        Unknown( REFIID iid, const Unknown& unknown, bool throwIfNoInterface = true )
            : unknown_( nullptr )
        {
            if ( unknown )
            {
                IUnknown* pInterface = nullptr;
                auto hr = unknown.unknown_->QueryInterface( iid, (void**)&pInterface );
                if ( FAILED( hr ) )
                {
                    if ( throwIfNoInterface == false && hr == E_NOINTERFACE )
                    {
                        return;
                    }
                    CheckHRESULT( hr );
                }
                unknown_ = pInterface;
            }
        }

        /// <summary>
        /// Copy constructor, calls <c>AddRef</c> on the interface pointer held
        /// by <c>other</c>.
        /// </summary>
        /// <param name="other">
        /// Const reference to the <c>Unknown</c> object that will be copied.
        /// </param>
        Unknown( const Unknown& other ) noexcept
            : unknown_( other.unknown_ )
        {
            if ( unknown_ )
            {
                unknown_->AddRef( );
            }
        }

        /// <summary>
        /// Move constructor takes ownership of
        /// the interface pointer held by <c>other</c>.
        /// </summary>
        /// <param name="other">
        /// The object to transfer the ownership of
        /// the interface pointer from.
        /// </param>
        Unknown( Unknown&& other ) noexcept
            : unknown_( other.unknown_ )
        {
            if ( unknown_ )
            {
                other.unknown_ = nullptr;
            }
        }

        /// <summary>
        /// Destructor, calling <c>Release</c> on the wrapped interface.
        /// </summary>
        ~Unknown( ) noexcept
        {
            IUnknown* tmp = unknown_;
            unknown_ = nullptr;
            if ( tmp )
            {
                tmp->Release( );
            }
        }

        /// <summary>
        /// Returns <c>true</c> if this object references an interface.
        /// </summary>
        constexpr operator bool( ) const noexcept
        {
            return unknown_ != nullptr;
        }

        /// <summary>
        /// Copy assignment, which does nothing if <c>other</c>
        /// holds the same interface pointer as this object; and 
        /// if not, calls <c>Release</c> on the currently 
        /// held interface pointer, then copying the
        /// interface pointer from <c>other</c>, calling
        /// <c>AddRef</c> on the newly assigned interface pointer.
        /// </summary>
        /// <param name="other">
        /// The source of the copy assignment.
        /// </param>
        /// <returns>
        /// A reference to the object.
        /// </returns>
        Unknown& operator = ( const Unknown& other ) noexcept
        {
            if ( unknown_ != other.unknown_ )
            {
                if ( unknown_ )
                {
                    unknown_->Release( );
                }
                unknown_ = other.unknown_;
                if ( unknown_ )
                {
                    unknown_->AddRef( );
                }
            }
            return *this;
        }

        /// <summary>
        /// Move assignment exchanges the current interface pointer,
        /// with the interface pointer held by <c>other</c>.
        /// </summary>
        /// <param name="other">
        /// The source of the move assignment.
        /// </param>
        /// <returns>
        /// A reference to the object.
        /// </returns>
        Unknown& operator = ( Unknown&& other ) noexcept
        {
            std::swap( unknown_, other.unknown_ );
            return *this;
        }

        /// <summary>
        /// Exchanges the current interface pointer,
        /// with the interface pointer held by <c>other</c>.
        /// </summary>
        /// <param name="other">
        /// The object to exchange interface pointer with.
        /// </param>
        void swap( Unknown& other ) noexcept
        {
            std::swap( unknown_, other.unknown_ );
        }

        /// <summary>
        /// Exchanges the current interface pointers between two
        /// <c>Unknown</c> objects.
        /// </summary>
        /// <param name="first">
        /// The first <c>Unknown</c> object.
        /// </param>
        /// <param name="second">
        /// The second <c>Unknown</c> object.
        /// </param>
        friend void swap( Unknown& first, Unknown& second ) noexcept
        {
            first.swap( second );
        }

        /// <summary>
        /// Calls <c>Release</c> on the currently held interface pointer
        /// if the interface pointer held by <c>other</c> points
        /// to a different interface.
        /// </summary>
        /// <param name="other">
        /// An optional interface pointer to assign to the current
        /// object.
        /// </param>
        /// <param name="addRef">
        /// if <c>true</c>, and <c>other</c> is not <c>nullptr</c>,
        /// <c>ResetPtr</c> will call <c>AddRef</c> on the newly
        /// assigned interface pointer.
        /// </param>
        void ResetPtr( IUnknown* other = nullptr, bool addRef = false ) noexcept
        {
            if ( unknown_ != other )
            {
                if ( unknown_ )
                {
                    unknown_->Release( );
                }
                unknown_ = other;
                if ( addRef && ( unknown_ != nullptr ) )
                {
                    unknown_->AddRef( );
                }
            }
        }

        /// <summary>
        /// Assigning <c>nullptr</c> to the object, releases the
        /// currently held interface pointer, and sets the
        /// interface pointer to <c>nullptr</c>.
        /// </summary>
        /// <param name="">
        /// <c>nullptr</c>
        /// </param>
        /// <returns>
        /// A reference to the object.
        /// </returns>
        Unknown& operator = ( nullptr_t )
        {
            if ( unknown_ )
            {
                auto tmp = unknown_;
                unknown_ = nullptr;
                tmp->Release( );
            }
            return *this;
        }


        /// <summary>
        /// Releases ownership of the wrapped interface pointer and returns it.
        /// </summary>
        /// <returns>
        /// The raw interface pointer previously held; caller takes ownership and must Release it.
        /// </returns>
        IUnknown* Detach( )
        {
            auto tmp = unknown_;
            unknown_ = nullptr;
            return tmp;
        }

        /// <summary>
        /// Creates an instance of the interface 
        /// wrapper class T, by querying the interface
        /// pointer for the interface type wrapped by
        /// T
        /// </summary>
        /// <typeparam name="T">
        /// An interface wrapper class derived from Unknown.
        /// </typeparam>
        /// <returns>
        /// Returns an instance of T, initialized to the interface
        /// wrapped by T, or <c>nullptr</c> if the interface is
        /// not supported.
        /// </returns>
        template<typename T>
            requires std::is_base_of_v<Unknown, T > 
        T As( ) const
        {
            const Unknown& self = *this;
            T result( __uuidof(T::InterfaceType), self, false );
            return result;
        }

        /// <summary>
        /// Returns <c>true</c> if the interface
        /// can successfully be queried for the interface
        /// wrapped by T
        /// </summary>
        /// <typeparam name="T">
        /// An interface wrapper class derived from Unknown.
        /// </typeparam>
        /// <returns>
        /// <c>true</c> if the interface is supported, otherwise <c>false</c>.
        /// </returns>
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        bool Is( ) const noexcept
        {
            if ( unknown_ )
            {
                typename T::InterfaceType* pInterface = nullptr;
                auto hr = unknown_->QueryInterface( __uuidof( typename T::InterfaceType ), (void**)&pInterface );
                if ( hr == S_OK )
                {
                    pInterface->Release( );
                    return true;
                }
            }
            return false;
        }


        /// <summary>
        /// Creates an instance of the interface 
        /// smart pointer ComPtr&lt;T&gt; for the interface T, by querying the interface
        /// pointer for the interface type T
        /// </summary>
        /// <typeparam name="T">
        /// An interface type derived from <c>IUnknown</c>.
        /// </typeparam>
        /// <returns>
        /// Returns an instance of the interface smart pointer 
        /// ComPtr&lt;T&gt; for the interface T, or <c>nullptr</c> if the interface is
        /// not supported.
        /// </returns>
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        ComPtr<T> As( ) const
        {
            ComPtr<T> result;

            if ( unknown_ )
            {
                T* pInterface = nullptr;
                auto hr = unknown_->QueryInterface( __uuidof( T ), (void**)&pInterface );
                if ( hr == S_OK )
                {
                    result.ResetPtr( pInterface );
                }
            }
            return result;
        }

        /// <summary>
        /// This function can be used to detect if
        /// an object supports a particular COM interface
        /// derived from IUnknown.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the interface you want to retrieve.
        /// </typeparam>
        /// <returns>
        /// <p>
        /// returns true if the interface is supported, otherwise false.
        /// </p>
        /// <p>
        /// If the object does not hold a pointer to a COM
        /// interface, then this function will always return false.
        /// </p>
        /// </returns>
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        bool Is( ) const noexcept
        {
            if ( unknown_ )
            {
                T* pInterface = nullptr;
                auto hr = unknown_->QueryInterface( __uuidof( T ), (void**)&pInterface );
                if ( hr == S_OK )
                {
                    pInterface->Release( );
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Retrieves a pointer to the interface wrapped by
        /// this object.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        template<typename T = IUnknown>
        T* GetInterfacePointer( ) const noexcept
        {
            return reinterpret_cast<T*>( unknown_ );
        }

        /// <summary>
        /// Queries a COM object for a pointer to one of its interface; 
        /// identifying the interface by a reference to its interface identifier (IID). 
        /// </summary>
        /// <param name="riid">IID identifying the requested interface.</param>
        /// <param name="itf">
        /// The address of a pointer to an interface with 
        /// the IID specified in the riid parameter. Because you 
        /// pass the address of an interface pointer, the method 
        /// can overwrite that address with the pointer to the 
        /// interface being queried for. Upon successful return, *itf (the 
        /// dereferenced address) contains a pointer to the requested 
        /// interface. If the object doesn't support the interface, the 
        /// function sets *itf (the dereferenced address) to nullptr.
        /// </param>
        /// <returns>
        /// true if the funtion was able to retrive the requested interface, otherwise false.
        /// </returns>
        bool QueryInterface( REFIID riid, void** itf ) const
        {
            auto hr = unknown_->QueryInterface( riid, itf );
            if ( hr == S_OK )
            {
                return true;
            }
            else
            {
                if ( hr != E_NOINTERFACE )
                {
                    CheckHRESULT( hr, unknown_ );
                }
                *itf = nullptr;
                return false;
            }
        }

        /// <summary>
        /// Queries the interface for an interface pointer of type T
        /// </summary>
        /// <typeparam name="T">
        /// An interface type derived from <c>IUnknown</c>.
        /// </typeparam>
        /// <param name="itf">
        /// A pointer to an interface pointer that will
        /// be assigned the requested interface pointer if
        /// supported by the object.
        /// </param>
        /// <returns>
        /// <c>true</c> if the query succeeded, otherwise <c>false</c>.
        /// </returns>
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        bool QueryInterface( T** itf ) const
        {
            return QueryInterface( __uuidof( T ), reinterpret_cast< void** >( itf ) );
        }


        
        /// <summary>
        /// Returns <c>true</c> if the interface pointer held by this
        /// object is the same as the interface pointer held by the <c>other</c>
        /// object.
        /// </summary>
        /// <param name="other">
        /// the <c>other</c> object.
        /// </param>
        /// <returns>
        /// <c>true</c> if equal, otherwise <c>false</c>.
        /// </returns>
        constexpr bool operator == ( const Unknown& other ) const noexcept
        {
            return unknown_ == other.unknown_;
        }
        /// <summary>
        /// Returns <c>true</c> if the interface pointer held by this
        /// object is not the same as the interface pointer held by the <c>other</c>
        /// object.
        /// </summary>
        /// <param name="other">
        /// the <c>other</c> object.
        /// </param>
        /// <returns>
        /// <c>true</c> if not equal, otherwise <c>false</c>.
        /// </returns>
        constexpr bool operator != ( const Unknown& other ) const noexcept
        {
            return unknown_ != other.unknown_;
        }

        /// <summary>
        /// Returns <c>true</c> if the interface pointer held by this
        /// object is the same as the interface pointer held by <c>other</c>.
        /// </summary>
        /// <param name="other">
        /// the <c>other</c> interface pointer.
        /// </param>
        /// <returns>
        /// <c>true</c> if equal, otherwise <c>false</c>.
        /// </returns>
        constexpr bool operator == ( const IUnknown* other ) const noexcept
        {
            return unknown_ == other;
        }

        /// <summary>
        /// Returns <c>true</c> if the interface pointer held by this
        /// object is not the same as the interface pointer held by <c>other</c>.
        /// </summary>
        /// <param name="other">
        /// the <c>other</c> interface pointer.
        /// </param>
        /// <returns>
        /// <c>true</c> if not equal, otherwise <c>false</c>.
        /// </returns>
        constexpr bool operator != ( const IUnknown* other ) const noexcept
        {
            return unknown_ != other;
        }

        /// <summary>
        /// Creates and default-initializes a single object of the class associated with a specified CLSID.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the wrapper class derived from Unknown.
        /// </typeparam>
        /// <param name="clsid">
        /// The CLSID associated with the data and code that will be used to create the object.
        /// </param>
        /// <param name="classContext">
        /// Context in which the code that manages the newly created object will run. 
        /// </param>
        /// <returns>
        /// An initialized instance of T
        /// </returns>
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromClassId( const CLSID& clsid, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            typename T::InterfaceType* result = nullptr;
            auto hr = CoCreateInstance( clsid, NULL, classContext, __uuidof( typename T::InterfaceType ), (void**)&result );
            CheckHRESULT( hr );
            return T( result );
        }

        /// <summary>
        /// Creates an instance of a COM object identified by a string CLSID and returns it
        /// wrapped in a C++ wrapper type derived from <c>Unknown</c>.
        /// </summary>
        /// <typeparam name="T">
        /// The wrapper class type to construct and return. This type must be derived from
        /// <c>Unknown</c> and must define <c>InterfaceType</c> as the COM interface type
        /// that the wrapper encapsulates.
        /// </typeparam>
        /// <param name="clsid">
        /// A null-terminated wide-character string containing the CLSID in registry/string
        /// format (for example: <c>"{000209FF-0000-0000-C000-000000000046}"</c>).
        /// </param>
        /// <param name="classContext">
        /// The context in which the code that manages the newly created object will run.
        /// Specify CLSCTX flags such as <c>CLSCTX_INPROC_SERVER</c> (the default),
        /// <c>CLSCTX_LOCAL_SERVER</c>, etc.
        /// </param>
        /// <returns>
        /// An instance of <typeparamref name="T"/> initialized to the interface returned by
        /// <c>CoCreateInstance</c>. The returned wrapper takes ownership of the interface
        /// pointer and follows the wrapper's ownership semantics.
        /// </returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when conversion of the string to a CLSID fails or when <c>CoCreateInstance</c>
        /// returns a failure HRESULT. CheckHRESULT is used to validate HRESULT values and
        /// will raise the appropriate Harlinn exception on failure.
        /// </exception>
        /// <remarks>
        /// The function first converts the provided string CLSID to a <c>CLSID</c> using
        /// <c>CLSIDFromString</c>. It then calls <c>CoCreateInstance</c> to instantiate the
        /// COM object and requests the interface identified by <c>T::InterfaceType</c>.
        /// If successful, the raw interface pointer is wrapped in an instance of <c>T</c>
        /// and returned. Any COM failure results in an exception thrown by <c>CheckHRESULT</c>.
        /// </remarks>
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromClassId( const wchar_t* clsid, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            CLSID CLSID_ = { 0, };
            auto hr = CLSIDFromString( clsid, &CLSID_ );
            CheckHRESULT( hr );
            typename T::InterfaceType* result = nullptr;
            hr = CoCreateInstance( CLSID_, NULL, classContext, __uuidof( typename T::InterfaceType ), (void**)&result );
            CheckHRESULT( hr );
            return T( result );
        }

        /// <summary>
        /// Creates an instance of a COM object identified by a string CLSID and returns it
        /// wrapped in a C++ wrapper type derived from <c>Unknown</c>.
        /// </summary>
        /// <typeparam name="T">
        /// The wrapper class type to construct and return. This type must be derived from
        /// <c>Unknown</c> and must define <c>InterfaceType</c> as the COM interface type
        /// that the wrapper encapsulates.
        /// </typeparam>
        /// <param name="clsid">
        /// A null-terminated wide-character string containing the CLSID in registry/string
        /// format (for example: <c>"{000209FF-0000-0000-C000-000000000046}"</c>), provided as a <c>WideString</c>.
        /// </param>
        /// <param name="classContext">
        /// Context in which the code that manages the newly created object will run.
        /// Specify CLSCTX flags such as <c>CLSCTX_INPROC_SERVER</c> (the default),
        /// <c>CLSCTX_LOCAL_SERVER</c>, etc.
        /// </param>
        /// <returns>
        /// An instance of <typeparamref name="T"/> initialized to the interface returned by
        /// <c>CoCreateInstance</c>. The returned wrapper takes ownership of the interface
        /// pointer and follows the wrapper's ownership semantics.
        /// </returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when conversion of the string to a CLSID fails or when <c>CoCreateInstance</c>
        /// returns a failure HRESULT. CheckHRESULT is used to validate HRESULT values and
        /// will raise the appropriate Harlinn exception on failure.
        /// </exception>
        /// <remarks>
        /// This overload forwards to the <c>wchar_t*</c> overload by calling <c>clsid.c_str()</c>.
        /// Use the <c>const wchar_t*</c> overload when you already have a null-terminated string.
        /// </remarks>
        /// <seealso cref="CoCreateInstanceFromClassId(const wchar_t*, DWORD)"/>
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromClassId( const WideString& clsid, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            return CoCreateInstanceFromClassId( clsid.c_str( ), classContext );
        }

        /// <summary>
        /// Creates an instance of a COM object identified by a ProgID and returns it wrapped
        /// in a C++ wrapper type derived from <c>Unknown</c>.
        /// </summary>
        /// <typeparam name="T">
        /// The wrapper class type to construct and return. This type must be derived from
        /// <c>Unknown</c> and must define <c>InterfaceType</c> as the COM interface type
        /// that the wrapper encapsulates.
        /// </typeparam>
        /// <param name="progId">
        /// A null-terminated wide-character string containing the ProgID of the COM class
        /// (for example: <c>L&quot;Word.Application&quot;</c>).
        /// </param>
        /// <param name="classContext">
        /// Context in which the code that manages the newly created object will run.
        /// Specify CLSCTX flags such as <c>CLSCTX_INPROC_SERVER</c> (the default),
        /// <c>CLSCTX_LOCAL_SERVER</c>, etc.
        /// </param>
        /// <returns>
        /// An instance of <typeparamref name="T"/> initialized to the interface returned by
        /// <c>CoCreateInstance</c>. The returned wrapper takes ownership of the interface
        /// pointer and follows the wrapper's ownership semantics.
        /// </returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when conversion of the ProgID to a <c>CLSID</c> fails or when
        /// <c>CoCreateInstance</c> returns a failure HRESULT. <c>CheckHRESULT</c> is used to
        /// validate HRESULT values and will raise the appropriate Harlinn exception on failure.
        /// </exception>
        /// <remarks>
        /// The function resolves the ProgID to a CLSID using <c>CLSIDFromProgIDEx</c> and then
        /// calls <c>CoCreateInstance</c> to instantiate the object and request the interface
        /// identified by <c>T::InterfaceType</c>. On success a wrapper of type <c>T</c> is
        /// returned; on failure an exception is thrown.
        /// </remarks>
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromProgId( const wchar_t* progId, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            CLSID CLSID_ = { 0, };
            auto hr = CLSIDFromProgIDEx( progId, &CLSID_ );
            CheckHRESULT( hr );
            typename T::InterfaceType* result = nullptr;
            hr = CoCreateInstance( CLSID_, NULL, classContext, __uuidof( typename T::InterfaceType ), (void**)&result );
            CheckHRESULT( hr );
            return T( result );
        }
        /// <summary>
        /// Creates an instance of a COM object identified by a ProgID and returns it wrapped
        /// in a C++ wrapper type derived from <c>Unknown</c>. This overload accepts a
        /// <c>WideString</c> and forwards the call to the overload that accepts a
        /// <c>const wchar_t*</c>.
        /// </summary>
        /// <typeparam name="T">
        /// The wrapper class type to construct and return. This type must be derived from
        /// <c>Unknown</c> and must define <c>InterfaceType</c> as the COM interface type
        /// that the wrapper encapsulates.
        /// </typeparam>
        /// <param name="progId">
        /// A null-terminated wide-character string containing the ProgID of the COM class
        /// (for example: <c>L"Word.Application"</c>).
        /// </param>
        /// <param name="classContext">
        /// Context in which the code that manages the newly created object will run.
        /// Specify CLSCTX flags such as <c>CLSCTX_INPROC_SERVER</c> (the default),
        /// <c>CLSCTX_LOCAL_SERVER</c>, etc.
        /// </param>
        /// <returns>
        /// An instance of <typeparamref name="T"/> initialized to the interface returned by
        /// <c>CoCreateInstance</c>. The returned wrapper takes ownership of the interface
        /// pointer and follows the wrapper's ownership semantics.
        /// </returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when conversion of the ProgID to a <c>CLSID</c> fails or when
        /// <c>CoCreateInstance</c> returns a failure HRESULT. <c>CheckHRESULT</c> is used
        /// to validate HRESULT values and will raise the appropriate Harlinn exception on failure.
        /// </exception>
        /// <remarks>
        /// This function simply forwards to the <c>const wchar_t*</c> overload by calling
        /// <c>progId.c_str()</c>. Use the <c>const wchar_t*</c> overload when you already have
        /// a null-terminated string to avoid an extra indirection.
        /// </remarks>
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromProgId( const WideString& progId, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            return CoCreateInstanceFromProgId( progId.c_str(), classContext );
        }

        
        /// <summary>
        /// Creates an instance of a COM object from a loaded module (DLL) by calling the module's
        /// exported <c>DllGetClassObject</c> function to obtain an <c>IClassFactory</c> and then
        /// calling the factory's <c>CreateInstance</c> to instantiate the requested class.
        /// The resulting raw interface pointer is wrapped in an instance of the specified wrapper
        /// type <c>T</c> and returned. The wrapper takes ownership of the interface pointer.
        /// </summary>
        /// <typeparam name="T">
        /// The wrapper class type to construct and return. This type must be derived from
        /// <c>Unknown</c> and must define <c>InterfaceType</c> as the COM interface type that the
        /// wrapper encapsulates.
        /// </typeparam>
        /// <param name="dll">
        /// A reference to a loaded module (see <c>ModuleHandle</c>) that implements the COM class and
        /// exports <c>DllGetClassObject</c>. Must be a valid module handle; passing an empty handle
        /// results in an invalid-argument error.
        /// </param>
        /// <param name="clsid">
        /// The class identifier (CLSID) of the COM class to create.
        /// </param>
        /// <returns>
        /// An instance of <c>T</c> initialized to the interface returned by the class factory.
        /// On success the returned wrapper owns the interface pointer. On failure an exception is raised.
        /// </returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the <c>dll</c> argument is invalid, when the module does not export
        /// <c>DllGetClassObject</c>, or when any COM call (such as obtaining the class factory or
        /// creating the instance) returns a failing HRESULT. The implementation uses
        /// <c>CheckHRESULT</c> to validate HRESULT values and will raise the appropriate Harlinn exception.
        /// </exception>
        /// <remarks>
        /// This routine:
        ///  - Queries the module for the exported function named "DllGetClassObject".
        ///  - Calls that function to obtain an <c>IClassFactory</c>.
        ///  - Uses the class factory to call <c>CreateInstance</c> requesting the interface type
        ///    defined by <c>T::InterfaceType</c>.
        /// If the module export is missing, <c>E_NOTIMPL</c> is signaled. The caller must ensure
        /// the module remains loaded while the returned object is used.
        /// </remarks>
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromDll( const ModuleHandle& dll, const CLSID& clsid );


    };

    /// <summary>
    /// Implements a set of standard methods, typedefs and operators for a COM wrapper class.
    /// </summary>
    /// <param name="classType">
    /// The wrapper class type being defined. The macro generates constructors, assignment
    /// operators and conversions for this class.
    /// </param>
    /// <param name="baseClassType">
    /// The wrapper class' immediate base type. Many generated members forward to or reuse
    /// functionality provided by this base type (for example reference counting and QueryInterface).
    /// </param>
    /// <param name="interfaceType">
    /// The concrete COM interface type implemented by the wrapper (for example <c>IExample</c>).
    /// The macro exposes this type as <c>InterfaceType</c> and emits casts and overloads using it.
    /// </param>
    /// <param name="baseInterfaceType">
    /// The COM interface type corresponding to the base wrapper. This type is used when forwarding
    /// raw pointers to the base class constructors or helper methods.
    /// </param>
    /// <remarks>
    /// Use this macro inside a wrapper class declaration to automatically add a consistent set of:
    /// - typedefs: <c>InterfaceType</c>, <c>BaseInterfaceType</c>
    /// - a private helper <c>GetInterface()</c> that validates the internal pointer and returns
    ///   an <c>InterfaceType *</c>
    /// - constructors: default, explicit(raw pointer), copy, move, and QI-based constructors
    /// - assignment operators: copy, move, assign-from-pointer, assign-nullptr
    /// - pointer conversion operator to <c>interfaceType*</c>
    /// - <c>ResetPtr</c>, <c>Detach</c> and comparison operators
    ///
    /// The generated members follow the project's ownership semantics:
    /// - When constructed or assigned from a raw pointer using the provided constructors/operators,
    ///   ownership semantics (AddRef/Release) are delegated to the base implementation when requested.
    /// - When converting or detaching raw pointers the macro uses reinterpret_cast on the underlying
    ///   <c>unknown_</c> member maintained by the base class.
    /// </remarks>
    /// <example>
    /// class MyExample : public Unknown
    /// {
    ///     HCC_COM_STANDARD_METHODS_IMPL( MyExample, Unknown, IMyExample, IUnknown )
    ///     // Now MyExample has standard ctor/assign/operators for IMyExample.
    /// };
    /// </example>

#define HCC_COM_STANDARD_METHODS_IMPL( classType, baseClassType , interfaceType, baseInterfaceType ) \
public: \
typedef interfaceType InterfaceType; \
typedef baseInterfaceType BaseInterfaceType; \
private: \
    InterfaceType * GetInterface() const { if(!unknown_) { ThrowNoInterface(); } return reinterpret_cast< InterfaceType *>( unknown_ ); } \
public: \
    using Base = baseClassType; \
    classType ( ) noexcept \
        : Base ( ) \
    {} \
    explicit classType (interfaceType * itf, bool addref = false ) \
        : Base ( reinterpret_cast< baseInterfaceType *>( itf ), addref ) \
    {  } \
public: \
    classType (REFIID iid, const Unknown& unknown, bool throwIfNoInterface = true ) \
        : Base( iid, reinterpret_cast< const baseClassType & > (unknown), throwIfNoInterface ) \
    {  } \
public: \
    classType ( const Unknown& unknown, bool throwIfNoInterface = true ) \
        : Base ( __uuidof(interfaceType), reinterpret_cast< const baseClassType & > (unknown), throwIfNoInterface ) \
    {  } \
    classType (const classType & other) noexcept\
        : Base( reinterpret_cast< const baseClassType & > (other) ) \
    {  } \
    classType (classType && other) noexcept\
        : Base( reinterpret_cast< baseClassType && >( other ) ) \
    {  } \
    classType & operator = (const classType & other) noexcept\
    { \
        baseClassType :: operator = ( reinterpret_cast< const baseClassType & > (other) ); \
        return *this; \
    } \
    classType & operator = (classType && other)  noexcept\
    { \
        baseClassType :: operator = ( reinterpret_cast< baseClassType && > (other) ); \
        return *this; \
    } \
    classType & operator = (nullptr_t) noexcept\
    { \
        baseClassType :: operator = ( nullptr_t() ); \
        return *this; \
    } \
    operator interfaceType * ( ) const noexcept\
    { \
        return reinterpret_cast< interfaceType * >( unknown_ ); \
    } \
    void ResetPtr( interfaceType* itf = nullptr, bool addRef = false ) noexcept \
    { \
        baseClassType :: ResetPtr(reinterpret_cast< baseInterfaceType *>( itf ), addRef); \
    } \
    classType& operator = (interfaceType* itf) noexcept\
    { \
        if( reinterpret_cast< interfaceType * >( unknown_ ) != itf ) \
        { \
            ResetPtr( itf, true ); \
        } \
        return *this; \
    } \
    interfaceType* Detach( ) \
    { \
        return reinterpret_cast<interfaceType*>( baseClassType :: Detach( )); \
    } \
    constexpr bool operator == ( const classType& other ) const noexcept \
    { \
        return unknown_ == other.unknown_; \
    } \
    constexpr bool operator != ( const classType& other ) const noexcept \
    { \
        return unknown_ != other.unknown_; \
    } \
    constexpr bool operator == ( interfaceType* other ) const noexcept \
    { \
        return unknown_ == other; \
    } \
    constexpr bool operator != ( interfaceType* other ) const noexcept \
    { \
        return unknown_ != other; \
    } 

/*
    constexpr bool operator == ( nullptr_t ) const noexcept \
    { \
        return unknown_ == nullptr; \
    } \
    constexpr bool operator != ( nullptr_t ) const noexcept \
    { \
        return unknown_ != nullptr; \
    }
*/


/// <summary>
/// Convenience macro that defines the standard set of wrapper methods and typedefs for a COM wrapper class,
/// assuming the corresponding COM interface types follow the naming convention of prefixing the class
/// name with 'I' (for example: class <c>MyExample</c> corresponds to interface <c>IMyExample</c>).
/// </summary>
/// <param name="classType">
/// The C++ wrapper class type to generate standard methods for (e.g. <c>MyExample</c>).
/// </param>
/// <param name="baseClassType">
/// The immediate base wrapper class type (e.g. <c>Unknown</c>).
/// </param>
/// <remarks>
/// This macro expands to <c>HCC_COM_STANDARD_METHODS_IMPL(classType, baseClassType, I##classType, I##baseClassType)</c>.
/// Use this when your COM interface types are named by prefixing 'I' to the class type and base class type.
/// The expansion generates typedefs, constructors, assignment operators, conversion operators, and helper
/// methods that follow the project's ownership and interface-wrapping semantics.
/// </remarks>
/// <example>
/// // Declares standard methods for MyExample which wraps IMyExample and derives from Unknown:
/// HCC_COM_STANDARD_METHODS_IMPL2( MyExample, Unknown )
/// </example>
/// <seealso cref="HCC_COM_STANDARD_METHODS_IMPL"/>
#define HCC_COM_STANDARD_METHODS_IMPL2( classType, baseClassType ) HCC_COM_STANDARD_METHODS_IMPL(classType, baseClassType,I##classType, I##baseClassType)

/// <summary>
/// Helper macro that validates an HRESULT returned by a COM or Win32 API call.
/// </summary>
/// <param name="hr">The HRESULT value to check.</param>
/// <remarks>
/// If <paramref name="hr"/> indicates failure (macro <c>FAILED(hr)</c>), this macro invokes
/// <c>CheckHRESULT</c> with the HRESULT and the current source location information
/// (the project-specific macros <c>CURRENT_FUNCTION</c>, <c>CURRENT_FILE</c> and <c>__LINE__</c>).
/// The call is wrapped in a <c>do { ... } while(false)</c> to provide single-statement semantics
/// so the macro can be safely used in conditional statements and other contexts.
/// 
/// Use this macro after COM/Win32 calls to convert failing HRESULTs into the library's
/// exception type via <c>CheckHRESULT</c>. Note that <c>CheckHRESULT</c> throws an exception if <c>FAILED(hr)</c> is true,
/// so callers should use it where exceptions are acceptable or handle exceptions accordingly.
/// </remarks>
/// <example>
/// HRESULT hr = CoCreateInstance(...);
/// HCC_COM_CHECK_HRESULT(hr); // throws on failure with source information
/// </example>
#define HCC_COM_CHECK_HRESULT( hr ) if ( FAILED( hr ) ) do { CheckHRESULT( hr, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); } while(false)

/// <summary>
/// Checks an HRESULT returned from a COM or Win32 call and invokes <c>CheckHRESULT</c> if it indicates failure.
/// </summary>
/// <param name="hr">The HRESULT value to evaluate.</param>
/// <param name="itf">
/// Optional interface pointer passed to <c>CheckHRESULT</c> to provide contextual information about the
/// COM object that produced the HRESULT. May be <c>nullptr</c> if no interface context is available.
/// </param>
/// <remarks>
/// If <c>FAILED(hr)</c> evaluates to true, this macro calls <c>CheckHRESULT(hr, itf, CURRENT_FUNCTION, CURRENT_FILE, __LINE__)</c>.
/// The call is wrapped in a <c>do { ... } while(false)</c> to provide single-statement semantics so the macro can
/// be used safely in conditional blocks. <c>CheckHRESULT</c> performs error translation and will throw an
/// exception when the HRESULT indicates failure; callers should be prepared to handle exceptions.
/// </remarks>
/// <example>
/// HRESULT hr = pSomeItf->SomeMethod();
/// HCC_COM_CHECK_HRESULT2(hr, pSomeItf); // throws on failure and includes pSomeItf in error context
/// </example>
#define HCC_COM_CHECK_HRESULT2( hr, itf ) if ( FAILED( hr ) ) do { CheckHRESULT( hr, itf, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); } while(false)


    /// <summary>
    /// A generic smart pointer for managing COM interfaces.
    /// </summary>
    /// <typeparam name="T">
    /// The COM interface type managed by this smart pointer. Must derive from <c>IUnknown</c>.
    /// </typeparam>
    /// <remarks>
    /// This class derives from <c>Unknown</c> and follows the ownership semantics
    /// defined by the base class. Copying will call <c>AddRef</c> via the base copy
    /// semantics; destruction will call <c>Release</c>. Use <c>operator&</c> to obtain
    /// a pointer-to-pointer suitable for out parameters from COM APIs; the operator will
    /// release any currently held interface before returning the address.
    /// </remarks>
    template<typename T>
    class ComPtr : public Unknown
    {
    public:
        using Base = Unknown;
        using InterfaceType = T;

        /// <summary>
        /// Default constructs an empty smart pointer.
        /// </summary>
        /// <returns>
        /// An instance holding no interface (nullptr).
        /// </returns>
        constexpr ComPtr( ) noexcept
            : Base( nullptr )
        {
        }

        
         
        /// <summary>
        /// Constructs a smart pointer that wraps the provided raw interface pointer.
        /// </summary>
        /// <param name="unknown">
        /// Raw interface pointer to wrap. Ownership semantics: the pointer is assigned 
        /// as-is to the wrapper. No AddRef is performed by this constructor.
        /// </param>
        explicit ComPtr( T* unknown ) noexcept
            : Base( unknown )
        {
        }

        /// <summary>
        /// Copy constructor. The copied object will hold the same interface pointer
        /// and an AddRef is performed via the base class copy constructor.
        /// </summary>
        /// <param name="other">The source smart pointer to copy from.</param>
        ComPtr( const ComPtr& other ) noexcept
            : Base( other )
        {
        }

        /// <summary>
        /// Move constructor. Takes ownership of the interface pointer held by <paramref name="other"/>.
        /// After the move, <paramref name="other"/> will not hold a reference.
        /// </summary>
        /// <param name="other">The source smart pointer to move from.</param>
        ComPtr( ComPtr&& other ) noexcept
            : Base( std::move(static_cast< Unknown&& >(other)) )
        {
        }


        /// <summary>
        /// Copy assignment operator. Releases the current interface (if any) and
        /// acquires a reference to the interface held by <paramref name="other"/>.
        /// </summary>
        /// <param name="other">The source smart pointer to assign from.</param>
        /// <returns>Reference to this object.</returns>
        ComPtr& operator = ( const ComPtr& other ) noexcept
        {
            Base::operator=( other );
            return *this;
        }

        /// <summary>
        /// Move assignment operator. Exchanges the internal pointer with <paramref name="other"/>,
        /// transferring ownership without AddRef/Release overhead.
        /// </summary>
        /// <param name="other">The source smart pointer to move from.</param>
        /// <returns>Reference to this object.</returns>
        ComPtr& operator = ( ComPtr&& other ) noexcept
        {
            Base::operator=( std::move( static_cast< Unknown&& >( other ) ) );
            return *this;
        }


        /// <summary>
        /// Pointer access operator.
        /// </summary>
        /// <returns>The managed interface pointer (may be nullptr).</returns>
        T* operator -> ( ) const noexcept
        {
            return (T*)unknown_;
        }
        
        /// <summary>
        /// Dereference operator.
        /// </summary>
        /// <returns>Reference to the underlying interface object. Behavior is undefined if the pointer is null.</returns>
        std::add_lvalue_reference_t<T> operator* ( ) const noexcept
        {
            return *unknown_;
        }


        /// <summary>
        /// Returns the address of the internal interface pointer for use with COM out-parameters.
        /// </summary>
        /// <remarks>
        /// If this smart pointer currently holds an interface, it will Release() that interface
        /// and reset to null before returning the address. Use this when passing the address
        /// to functions that expect a T** for output (for example CoCreateInstance, QueryInterface).
        /// </remarks>
        /// <returns>
        /// A pointer to the internal T* member suitable for receiving an out-parameter.
        /// </returns>
        T** operator& ( ) noexcept
        {
            if ( unknown_ )
            {
                unknown_->Release( );
                unknown_ = nullptr;
            }
            return (T**)&unknown_;
        }


    };

    

    namespace Com
    {
        /// <summary>
        /// Template wrapper that attaches to an existing COM wrapper type without participating
        /// in COM reference counting (does not call <c>AddRef</c> or <c>Release</c>).
        /// </summary>
        /// <typeparam name="T">
        /// The COM wrapper type to attach to. This type is required to derive from
        /// <c>Harlinn::Common::Core::Unknown</c> and to expose <c>InterfaceType</c>.
        /// </typeparam>
        /// <remarks>
        /// <para>
        /// Instances of <c>Com::Attached&lt;T&gt;</c> provide a lightweight, non-owning view
        /// of the underlying COM interface pointer managed by another wrapper. Because the
        /// class does not adjust the reference count, the caller is responsible for ensuring
        /// that the lifetime of the underlying object exceeds the lifetime of the
        /// <c>Attached</c> instance.
        /// </para>
        /// <para>
        /// Use this class when you need temporary, efficient access to a wrapped interface
        /// without incurring AddRef/Release overhead. Do not use it as an ownership holder.
        /// </para>
        /// </remarks>
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        class Attached : public T
        { 
        public:
            /// <summary>
            /// Alias for the base wrapper type.
            /// </summary>
            using Base = T;
            /// <summary>
            /// Alias for the concrete COM interface type exposed by the base wrapper.
            /// </summary>
            using InterfaceType = typename Base::InterfaceType;
        protected:
            /// <summary>
            /// Import base class' protected member pointer to the wrapped IUnknown.
            /// </summary>
            using Base::unknown_;
        public:
            /// <summary>
            /// Default constructs an empty <c>Attached</c> instance that holds no interface.
            /// </summary>
            /// <remarks>
            /// The constructed object does not own or reference any COM interface.
            /// </remarks>
            Attached()
                : Base()
            { }

            /// <summary>
            /// Constructs an <c>Attached</c> that references the provided raw interface pointer.
            /// </summary>
            /// <param name="itf">
            /// Raw pointer to the COM interface of type <c>InterfaceType</c>. The pointer
            /// is attached as-is; this constructor does NOT call <c>AddRef</c>.
            /// </param>
            explicit Attached( InterfaceType* itf  )
                : Base( itf, false )
            {
            }

            /// <summary>
            /// Copy constructor that attaches to the same underlying interface pointer as <paramref name="other"/>.
            /// </summary>
            /// <param name="other">The source <c>Attached</c> to copy from. No AddRef is performed.</param>
            Attached( const Attached& other )
            {
                unknown_ = other.unknown_;
            }

            /// <summary>
            /// Move constructor. Transfers the attached pointer from <paramref name="other"/> to this instance.
            /// </summary>
            /// <param name="other">The source <c>Attached</c> to move from.</param>
            /// <remarks>
            /// The operation is <c>noexcept</c> and leaves <paramref name="other"/> in an empty state.
            /// </remarks>
            Attached( Attached&& other ) noexcept
            {
                std::swap(unknown_, other.unknown_);
            }

            /// <summary>
            /// Constructs an <c>Attached</c> by attaching to the pointer held by an existing base wrapper.
            /// </summary>
            /// <param name="other">A reference to a base wrapper instance. No AddRef is performed.</param>
            Attached( const Base& other )
            {
                unknown_ = other.unknown_;
            }

            /// <summary>
            /// Destructor. Clears the internal pointer without calling <c>Release</c>.
            /// </summary>
            /// <remarks>
            /// Because <c>Attached</c> does not own the reference, it must not call <c>Release</c>.
            /// The underlying COM object must remain valid while this instance exists.
            /// </remarks>
            ~Attached( )
            {
                unknown_ = nullptr;
            }


            /// <summary>
            /// Copy-assignment operator. Attaches to the pointer held by <paramref name="other"/>
            /// without changing COM reference counts.
            /// </summary>
            /// <param name="other">The source <c>Attached</c> to assign from.</param>
            /// <returns>Reference to this instance.</returns>
            Attached& operator = ( const Attached& other )
            {
                unknown_ = other.unknown_;
                return *this;
            }

            /// <summary>
            /// Move-assignment operator. Exchanges the internal pointer with <paramref name="other"/>.
            /// </summary>
            /// <param name="other">The source <c>Attached</c> to move from.</param>
            /// <returns>Reference to this instance.</returns>
            Attached& operator = ( Attached&& other ) noexcept
            {
                std::swap( unknown_, other.unknown_ );
                return *this;
            }

            /// <summary>
            /// Assignment from a base wrapper. Attaches to the base wrapper's pointer without AddRef.
            /// </summary>
            /// <param name="other">The base wrapper to attach to.</param>
            /// <returns>Reference to this instance.</returns>
            Attached& operator = ( const Base& other )
            {
                unknown_ = other.unknown_;
                return *this;
            }

            /// <summary>
            /// Equality comparison between two <c>Attached</c> instances. Compares underlying pointers.
            /// </summary>
            /// <param name="other">The other <c>Attached</c> to compare to.</param>
            /// <returns><c>true</c> if both reference the same underlying interface pointer; otherwise <c>false</c>.</returns>
            constexpr bool operator == ( const Attached& other ) const noexcept
            {
                return unknown_ == other.unknown_;
            }

            /// <summary>
            /// Equality comparison between <c>Attached</c> and a base wrapper. Compares underlying pointers.
            /// </summary>
            /// <param name="other">The base wrapper to compare to.</param>
            /// <returns><c>true</c> if both reference the same underlying interface pointer; otherwise <c>false</c>.</returns>
            constexpr bool operator == ( const Base& other ) const noexcept
            {
                return unknown_ == other.unknown_;
            }
            /// <summary>
            /// Equality comparison between <c>Attached</c> and a raw interface pointer.
            /// </summary>
            /// <param name="other">Raw interface pointer to compare to.</param>
            /// <returns><c>true</c> if the internal pointer equals <paramref name="other"/>; otherwise <c>false</c>.</returns>
            constexpr bool operator == ( const InterfaceType* other ) const noexcept
            {
                return unknown_ == other;
            }
        };
    }

    
    /// <summary>
    /// Wrapper for the asynchronous <c>IAsyncIUnknown</c> interface.
    /// </summary>
    /// <remarks>
    /// <para>
    /// This class exposes the standard asynchronous IUnknown operations
    /// using a synchronous C++ wrapper that forwards to the underlying
    /// <c>IAsyncIUnknown</c> implementation. Each call uses the helper
    /// <c>GetInterface()</c> to validate the wrapped pointer and
    /// <c>HCC_COM_CHECK_HRESULT2</c> to translate failing HRESULTs into
    /// the project's exception type.
    /// </para>
    /// <para>
    /// Use this wrapper when interacting with COM objects that implement
    /// asynchronous IUnknown operations to keep call sites concise and
    /// to ensure consistent error handling and diagnostics.
    /// </para>
    /// </remarks>
    class AsyncUnknown : public Unknown
    {
    public:
        /// <summary>
        /// Generates the standard wrappers, typedefs and operators for this COM wrapper type.
        /// </summary>
        HCC_COM_STANDARD_METHODS_IMPL( AsyncUnknown, Unknown, AsyncIUnknown, IUnknown )

        /// <summary>
        /// Begins an asynchronous QueryInterface operation for the specified interface identifier.
        /// </summary>
        /// <param name="riid">The interface identifier (IID) of the interface to query.</param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying <c>Begin_QueryInterface</c> call returns a failing HRESULT.
        /// </exception>
        void Begin_QueryInterface( REFIID riid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Begin_QueryInterface( riid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Completes a previously started asynchronous QueryInterface operation.
        /// </summary>
        /// <param name="result">
        /// Receives the pointer to the requested interface on success.
        /// The caller takes ownership of the returned interface pointer and
        /// is responsible for calling Release() when done.
        /// </param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying <c>Finish_QueryInterface</c> call returns a failing HRESULT.
        /// </exception>
        void Finish_QueryInterface( void** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Finish_QueryInterface( result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        /// <summary>
        /// Begins an asynchronous AddRef operation.
        /// </summary>
        /// <remarks>
        /// After calling <c>Begin_AddRef</c> you must call <c>Finish_AddRef</c>
        /// to obtain the resulting reference count (or to complete the operation).
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying <c>Begin_AddRef</c> call returns a failing HRESULT.
        /// </exception>
        void Begin_AddRef( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Begin_AddRef( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Completes a previously started asynchronous AddRef operation and returns the new reference count.
        /// </summary>
        /// <returns>The reference count returned by the <c>Finish_AddRef</c> call.</returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Although <c>Finish_AddRef</c> returns a count, any internal errors will be converted
        /// to exceptions by the project's error handling mechanisms if necessary.
        /// </exception>
        ULONG Finish_AddRef( ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->Finish_AddRef( );
        }

        /// <summary>
        /// Begins an asynchronous Release operation.
        /// </summary>
        /// <remarks>
        /// After calling <c>Begin_Release</c> you must call <c>Finish_Release</c>
        /// to obtain the resulting reference count (or to complete the operation).
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying <c>Begin_Release</c> call returns a failing HRESULT.
        /// </exception>
        void Begin_Release( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Begin_Release( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Completes a previously started asynchronous Release operation and returns the new reference count.
        /// </summary>
        /// <returns>The reference count returned by the <c>Finish_Release</c> call.</returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Although <c>Finish_Release</c> returns a count, any internal errors will be converted
        /// to exceptions by the project's error handling mechanisms if necessary.
        /// </exception>
        ULONG Finish_Release( ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->Finish_Release( );
        }

    };


    /// <summary>
    /// Enables creation of COM objects through the standard COM class factory interface.
    /// </summary>
    /// <remarks>
    /// The ClassFactory wrapper provides a convenient C++ interface around the COM
    /// <c>IClassFactory</c> interface. It uses the project's ownership semantics for
    /// COM pointers and converts failing HRESULTs to the library's exception type
    /// using <c>HCC_COM_CHECK_HRESULT2</c>.
    /// </remarks>
    class ClassFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ClassFactory,Unknown, IClassFactory, IUnknown )

        /// <summary>
        /// Creates an instance of the class implemented by the factory.
        /// </summary>
        /// <param name="outerUnknown">
        /// Optional pointer to the controlling <c>IUnknown</c> for aggregation.
        /// Pass <c>nullptr</c> when aggregation is not required.
        /// </param>
        /// <param name="riid">
        /// The interface identifier that the caller requests for the new object.
        /// </param>
        /// <param name="result">
        /// Out parameter that receives the requested interface pointer on success.
        /// The caller receives ownership and is responsible for calling <c>Release</c>.
        /// </param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call returns a failing HRESULT. The macro
        /// <c>HCC_COM_CHECK_HRESULT2</c> is used to translate and throw.
        /// </exception>
        void CreateInstance( IUnknown* outerUnknown, REFIID riid, void** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( outerUnknown, riid, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        
        /// <summary>
        /// Creates an instance of the class implemented by the factory using an Unknown wrapper.
        /// </summary>
        /// <param name="outerUnknown">
        /// Wrapper that provides the controlling <c>IUnknown</c> for aggregation.
        /// Use <c>Unknown::GetInterfacePointer()</c> to obtain the raw pointer.
        /// </param>
        /// <param name="riid">The requested interface identifier.</param>
        /// <param name="result">Receives the requested interface pointer on success.</param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        void CreateInstance( const Unknown& outerUnknown, REFIID riid, void** result ) const
        {
            CreateInstance( outerUnknown.GetInterfacePointer(), riid, result );
        }
        
        /// <summary>
        /// Creates an instance of the class implemented by the factory and returns the requested interface.
        /// </summary>
        /// <param name="riid">The requested interface identifier.</param>
        /// <param name="result">Receives the requested interface pointer on success.</param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        void CreateInstance( REFIID riid, void** result ) const
        {
            CreateInstance( nullptr, riid, result );
        }


        /// <summary>
        /// Template overload that creates an instance and returns a typed interface pointer.
        /// </summary>
        /// <typeparam name="T">The COM interface type to request. Must derive from <c>IUnknown</c>.</typeparam>
        /// <param name="outerUnknown">Optional outer unknown for aggregation.</param>
        /// <param name="result">Receives a pointer to the requested interface on success.</param>
        /// <remarks>
        /// This overload forwards to the non-template <c>CreateInstance</c> by providing
        /// the IID for <typeparamref name="T"/> and casting the out parameter.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        template<typename T>
            requires std::is_base_of_v<IUnknown,T>
        void CreateInstance( IUnknown* outerUnknown, T** result ) const
        {
            CreateInstance( outerUnknown, __uuidof( T ), reinterpret_cast<void**>( result ) );
        }

        /// <summary>
        /// Template overload that creates an instance and returns a typed interface pointer, using an Unknown wrapper.
        /// </summary>
        /// <typeparam name="T">The COM interface type to request. Must derive from <c>IUnknown</c>.</typeparam>
        /// <param name="outerUnknown">An <c>Unknown</c> wrapper used for aggregation.</param>
        /// <param name="result">Receives a pointer to the requested interface on success.</param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstance( const Unknown& outerUnknown, T** result ) const
        {
            CreateInstance( outerUnknown.GetInterfacePointer( ), result );
        }


        /// <summary>
        /// Template overload that creates an instance and returns a typed interface pointer with no aggregation.
        /// </summary>
        /// <typeparam name="T">The COM interface type to request. Must derive from <c>IUnknown</c>.</typeparam>
        /// <param name="result">Receives a pointer to the requested interface on success.</param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstance( T** result ) const
        {
            CreateInstance( nullptr, __uuidof( T ), reinterpret_cast<void**>( result ) );
        }

        /// <summary>
        /// Template convenience that creates an instance of a wrapper type derived from <c>Unknown</c>.
        /// </summary>
        /// <typeparam name="T">
        /// The wrapper class type to construct. Must derive from <c>Unknown</c> and expose <c>InterfaceType</c>.
        /// </typeparam>
        /// <param name="outerUnknown">Optional outer unknown raw pointer for aggregation.</param>
        /// <returns>
        /// An instance of the wrapper type <typeparamref name="T"/> initialized with the created interface.
        /// </returns>
        /// <remarks>
        /// The returned wrapper takes ownership of the created interface pointer. Exceptions are
        /// thrown via the project's HRESULT-to-exception conversion on failure.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when creation or QueryInterface fails.
        /// </exception>
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        T CreateInstance( IUnknown* outerUnknown ) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            CreateInstance( outerUnknown, reinterpret_cast<void**>( &ptr ) );
            return T( ptr );
        }

        /// <summary>
        /// Template convenience that creates an instance of a wrapper type derived from <c>Unknown</c> with no aggregation.
        /// </summary>
        /// <typeparam name="T">The wrapper class type to construct. Must derive from <c>Unknown</c>.</typeparam>
        /// <returns>An initialized instance of <typeparamref name="T"/>.</returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when creation fails.
        /// </exception>
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        T CreateInstance( ) const
        {
            return CreateInstance( nullptr );
        }

        /// <summary>
        /// Locks or unlocks the class factory's server.
        /// </summary>
        /// <param name="lock">
        /// Pass <c>true</c> to increment the server lock count; <c>false</c> to decrement it.
        /// </param>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        void LockServer( bool lock ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->LockServer( lock ? TRUE : FALSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

#pragma warning( push ) 
#pragma warning( disable: 4191 ) 
    template<typename T>
        requires std::is_base_of_v<Unknown, T>
    inline T Unknown::CoCreateInstanceFromDll( const ModuleHandle& dll, const CLSID& clsid )
    {
        typename T::InterfaceType* result = nullptr;

        if ( !dll )
        {
            CheckHRESULT( E_INVALIDARG );
        }
        using GetClassObject = HRESULT( WINAPI* )( const CLSID& clsid, const IID& iid, void** object );

        GetClassObject dllGetClassObject = reinterpret_cast< GetClassObject >( dll.GetProcAddress( L"DllGetClassObject" ) );
        if ( dllGetClassObject == nullptr )
        {
            CheckHRESULT( E_NOTIMPL );
        }

        IClassFactory factoryPtr = nullptr;
        HRESULT hr = dllGetClassObject( clsid, __uuidof( IClassFactory ), (void**)&factoryPtr );
        CheckHRESULT( hr );
        ClassFactory factory( factoryPtr );

        hr = factory.CreateInstance( NULL, __uuidof( typename T::InterfaceType ), ( void** )&result );
        CheckHRESULT( hr );
        return T( result );
    }
#pragma warning( pop ) 

    /// <summary>
    /// <para>
    /// Enumerate strings. LPOLESTR is the type that indicates a pointer to a zero-terminated string of wide, or Unicode, characters.
    /// </para>
    /// <para>
    /// Wrapper for the COM <c>IEnumString</c> enumeration interface.
    /// </para>
    /// </summary>
    /// <remarks>
    /// <para>
    /// The <c>EnumString</c> class wraps an <c>IEnumString</c> pointer and provides
    /// convenient C++ style methods for iterating over enumerated strings returned
    /// by COM components. The wrapper follows the project's ownership semantics
    /// (derived from <c>Unknown</c>) and converts COM HRESULT failures into the
    /// project's exception type using the standard helper macros.
    /// </para>
    /// <para>
    /// Use the <c>Next</c> overloads to retrieve the next one or more strings,
    /// <c>All</c> to collect all remaining strings, <c>Skip</c> to advance the
    /// enumeration without retrieving values, <c>Reset</c> to restart the enumeration,
    /// and <c>Clone</c> to create an independent enumerator positioned at the same place.
    /// </para>
    /// </remarks>
    class EnumString : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( EnumString, Unknown, IEnumString, IUnknown )

        /// <summary>
        /// Retrieves the next string from the enumeration.
        /// </summary>
        /// <param name="result">
        /// Receives the next wide string from the enumeration on success.
        /// The returned <c>WideString</c> will be assigned to <c>result</c>.
        /// </param>
        /// <returns>
        /// <c>true</c> if a string was retrieved; <c>false</c> if the enumeration
        /// has been exhausted (S_FALSE).
        /// </returns>
        /// <remarks>
        /// This is a convenience overload that returns a single string. It wraps
        /// the underlying <c>IEnumString::Next</c> invocation and performs error
        /// handling via the project's HRESULT check helpers.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if the underlying COM call returns a failing HRESULT.
        /// </exception>
        HCC_EXPORT bool Next( WideString& result ) const;

        /// <summary>
        /// Retrieves up to <c>celt</c> strings from the enumeration.
        /// </summary>
        /// <param name="celt">The maximum number of elements to retrieve.</param>
        /// <param name="rgelt">
        /// Array of <c>LPOLESTR</c> pointers that receives the returned strings.
        /// The caller is responsible for freeing any returned BSTR/allocated strings
        /// according to the COM contract used by the provider.
        /// </param>
        /// <param name="pceltFetched">
        /// Receives the actual number of strings fetched. May be <c>nullptr</c>
        /// when <c>celt</c> is 1, following the COM convention.
        /// </param>
        /// <returns>
        /// <c>true</c> if the requested number of strings (<c>celt</c>) were
        /// retrieved; <c>false</c> if fewer elements were available (S_FALSE).
        /// </returns>
        /// <remarks>
        /// Use this overload when you need multiple strings in a single call.
        /// The method forwards to <c>IEnumString::Next</c> and translates errors.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if the underlying COM call returns a failing HRESULT.
        /// </exception>
        HCC_EXPORT bool Next( ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched ) const;
        
        /// <summary>
        /// Retrieves up to <c>celt</c> strings and appends them to a <c>std::vector</c>.
        /// </summary>
        /// <param name="celt">The maximum number of elements to retrieve.</param>
        /// <param name="result">
        /// A vector that will receive the retrieved <c>WideString</c> elements.
        /// </param>
        /// <returns>
        /// <c>true</c> if <c>celt</c> elements were retrieved; <c>false</c> if fewer
        /// elements were available (S_FALSE).
        /// </returns>
        /// <remarks>
        /// This overload allocates and converts received OLE strings into the project's
        /// <c>WideString</c> instances and appends them to <c>result</c>. It ensures
        /// correct cleanup on failure and propagates COM errors as exceptions.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if a COM call fails or if string conversion/allocation fails.
        /// </exception>
        HCC_EXPORT bool Next( ULONG celt, std::vector<WideString>& result ) const;
        
        /// <summary>
        /// Retrieves all remaining strings from the enumeration and appends them to <c>result</c>.
        /// </summary>
        /// <param name="result">
        /// A vector that will receive all remaining <c>WideString</c> values.
        /// </param>
        /// <remarks>
        /// Continues calling <c>Next</c> until the enumeration is exhausted.
        /// Useful when the caller needs the complete set of values.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if any underlying COM call returns a failing HRESULT.
        /// </exception>
        HCC_EXPORT void All( std::vector<WideString>& result ) const;
        
        /// <summary>
        /// Advances the enumeration by <c>celt</c> elements without retrieving them.
        /// </summary>
        /// <param name="celt">The number of elements to skip.</param>
        /// <remarks>
        /// Equivalent to calling <c>IEnumString::Skip</c>. After skipping, enumeration
        /// state is advanced by the specified count or to the end.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if the underlying COM call returns a failing HRESULT.
        /// </exception>
        HCC_EXPORT void Skip( ULONG celt ) const;
        
        /// <summary>
        /// Resets the enumeration sequence to the beginning.
        /// </summary>
        /// <remarks>
        /// Invokes <c>IEnumString::Reset</c> on the wrapped enumerator. After this
        /// call, subsequent <c>Next</c> calls will return elements from the start.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if the underlying COM call returns a failing HRESULT.
        /// </exception>
        HCC_EXPORT void Reset( ) const;
        
        /// <summary>
        /// Creates a new enumerator that contains the same enumeration state as this one.
        /// </summary>
        /// <returns>
        /// A new <c>EnumString</c> instance positioned at the same point in the sequence.
        /// The returned object owns its own COM enumerator and follows the wrapper's ownership semantics.
        /// </returns>
        /// <remarks>
        /// The clone operation calls <c>IEnumString::Clone</c> and wraps the returned
        /// interface in a new <c>EnumString</c> instance. Use this to snapshot enumeration state
        /// for parallel iteration or to save/restore position.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown if the underlying COM call returns a failing HRESULT.
        /// </exception>
        HCC_EXPORT EnumString Clone( ) const;

    };

    /// <summary>
    /// A movable buffer that manages memory using COM task allocator functions.
    /// </summary>
    /// <remarks>
    /// <para>
    /// The buffer uses <c>CoTaskMemAlloc</c>, <c>CoTaskMemRealloc</c> and <c>CoTaskMemFree</c>
    /// for allocation, reallocation and release respectively. This class is movable but not copyable.
    /// Use this class when you need a binary buffer whose lifetime and allocation are compatible with
    /// COM APIs that require memory allocated with the task allocator (for example when returning
    /// memory to callers expecting memory allocated by the COM allocator).
    /// </para>
    /// <para>
    /// Ownership semantics:
    /// - Constructing from a raw pointer (see <c>ComBuffer(Byte*, size_t)</c>) takes ownership of the provided pointer.
    /// - Move operations transfer ownership without additional allocation or release.
    /// - Destruction frees the owned memory (if any) with <c>CoTaskMemFree</c>.
    /// </para>
    /// </remarks>
    class ComBuffer
    {
        size_t size_ = 0;
        Byte* data_ = nullptr;
    public:
        /// <summary>
        /// Default constructs an empty buffer (no allocation).
        /// </summary>
        constexpr ComBuffer( ) noexcept = default;

        /// <summary>
        /// Allocates a buffer of the specified size using <c>CoTaskMemAlloc</c>.
        /// </summary>
        /// <param name="size">Number of bytes to allocate. If zero no allocation is performed.</param>
        /// <remarks>
        /// On success the buffer owns the allocated memory and <see cref="size()"/> returns the requested size.
        /// The caller must ensure COM task allocator is available on the current thread.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown indirectly by <c>ThrowOSError</c> if subsequent operations fail (e.g. out of memory).
        /// </exception>
        explicit ComBuffer( size_t size )
        {
            if ( size )
            {
                data_ = reinterpret_cast<Byte*>( CoTaskMemAlloc( size ) );
                size_ = size;
            }
        }

        /// <summary>
        /// Constructs the buffer by taking ownership of an existing COM task-allocated pointer.
        /// </summary>
        /// <param name="data">Pointer previously allocated with the COM task allocator.</param>
        /// <param name="size">Size in bytes of the provided buffer.</param>
        /// <remarks>
        /// The constructed object will free the pointer using <c>CoTaskMemFree</c> on destruction.
        /// </remarks>
        explicit ComBuffer( Byte* data, size_t size )
            : size_( size ), data_( data )
        {
        }

        /// <summary>
        /// Copy construction is deleted to avoid accidental duplicate ownership.
        /// </summary>
        ComBuffer( const ComBuffer& other ) = delete;

        /// <summary>
        /// Move constructor transfers ownership from <paramref name="other"/> to this instance.
        /// </summary>
        /// <param name="other">Source buffer to move from.</param>
        ComBuffer( ComBuffer&& other ) noexcept
            : size_( other.size_ ), data_( other.data_ )
        { 
            other.size_ = 0;
            other.data_ = nullptr;
        }

        /// <summary>
        /// Copy assignment is deleted to avoid accidental duplicate ownership.
        /// </summary>
        ComBuffer& operator = ( const ComBuffer& other ) = delete;


        /// <summary>
        /// Move assignment transfers ownership from <paramref name="other"/> to this instance.
        /// </summary>
        /// <param name="other">Source buffer to move from.</param>
        /// <returns>Reference to this instance.</returns>
        ComBuffer& operator = ( ComBuffer&& other ) noexcept
        {
            std::swap( size_, other.size_ );
            std::swap( data_, other.data_ );
            return *this;
        }

        /// <summary>
        /// Releases owned memory (if any) using <c>CoTaskMemFree</c>.
        /// </summary>
        ~ComBuffer( )
        {
            if ( data_ )
            {
                CoTaskMemFree( data_ );
            }
        }

        /// <summary>
        /// Returns the size of the buffer in bytes.
        /// </summary>
        /// <returns>The number of bytes currently allocated or 0 if empty.</returns>
        constexpr size_t size( ) const
        {
            return size_;
        }


        /// <summary>
        /// Resize the buffer to <paramref name="newSize"/> bytes.
        /// </summary>
        /// <param name="newSize">Requested new size in bytes. If zero the buffer is freed.</param>
        /// <remarks>
        /// - If <paramref name="newSize"/> is non-zero and different from the current size, the buffer
        ///   is reallocated using <c>CoTaskMemRealloc</c>. On failure, <c>ThrowOSError(ERROR_OUTOFMEMORY)</c> is called.
        /// - If <paramref name="newSize"/> is zero the buffer is freed and the object becomes empty.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown via <c>ThrowOSError</c> when reallocation fails (out of memory).
        /// </exception>
        void resize( size_t newSize )
        {
            if ( newSize )
            {
                if ( newSize != size_ )
                {
                    Byte* ptr = reinterpret_cast<Byte*>( CoTaskMemRealloc( data_, newSize ) );
                    if ( !ptr )
                    {
                        ThrowOSError( ERROR_OUTOFMEMORY );
                    }
                    data_ = ptr;
                    size_ = newSize;
                }
            }
            else
            {
                if ( data_ )
                {
                    CoTaskMemFree( data_ );
                    data_ = nullptr;
                }
                size_ = 0;
            }
        }

        /// <summary>
        /// Provides mutable indexed access to the buffer.
        /// </summary>
        /// <param name="index">Zero-based index into the buffer.</param>
        /// <returns>Reference to the byte at the requested index.</returns>
        /// <remarks>
        /// In debug builds this method checks bounds and will call <c>ThrowOSError(ERROR_INDEX_OUT_OF_BOUNDS)</c>
        /// if the index is out of range. Behavior is undefined in release builds for out-of-range access.
        /// </remarks>
        Byte& operator[]( size_t index )
        {
#ifdef _DEBUG
            if ( index >= size_ )
            {
                ThrowOSError( ERROR_INDEX_OUT_OF_BOUNDS );
            }
#endif
            return data_[index];
        }
        
        /// <summary>
        /// Provides read-only indexed access to the buffer.
        /// </summary>
        /// <param name="index">Zero-based index into the buffer.</param>
        /// <returns>Const reference to the byte at the requested index.</returns>
        /// <remarks>
        /// In debug builds this method checks bounds and will call <c>ThrowOSError(ERROR_INDEX_OUT_OF_BOUNDS)</c>
        /// if the index is out of range. Behavior is undefined in release builds for out-of-range access.
        /// </remarks>
        const Byte& operator[]( size_t index ) const
        {
#ifdef _DEBUG
            if ( index >= size_ )
            {
                ThrowOSError( ERROR_INDEX_OUT_OF_BOUNDS );
            }
#endif
            return data_[index];
        }

        /// <summary>
        /// Returns a mutable pointer to the underlying buffer memory.
        /// </summary>
        /// <returns>Pointer to allocated memory or <c>nullptr</c> when empty.</returns>
        Byte* data( )
        {
            return data_;
        }
        
        /// <summary>
        /// Returns a const pointer to the underlying buffer memory.
        /// </summary>
        /// <returns>Const pointer to allocated memory or <c>nullptr</c> when empty.</returns>
        const Byte* data( ) const
        {
            return data_;
        }
    };

    /// <summary>
    /// A C++ allocator that uses the COM task allocator functions (<c>CoTaskMemAlloc</c> and <c>CoTaskMemFree</c>)
    /// to allocate memory that is compatible with COM APIs and the COM task allocator contract.
    /// </summary>
    /// <typeparam name="T">
    /// The element type this allocator manages. Memory returned from <c>allocate</c> and
    /// <c>allocate_at_least</c> is suitable for storing objects of type <c>T</c>.
    /// </typeparam>
    /// <remarks>
    /// This allocator is intended for use with standard library containers and other code that
    /// accepts a C++ Allocator. It ensures that memory is allocated with the COM task allocator,
    /// which is required when memory will be returned to COM callers or used by COM APIs that
    /// expect memory allocated with <c>CoTaskMemAlloc</c>.
    ///
    /// Ownership and lifetime:
    /// - <c>allocate</c> returns a pointer to memory that the caller owns and must not free directly;
    ///   the container or caller should call <c>deallocate</c>, which delegates to <c>CoTaskMemFree</c>.
    /// - The allocator is trivially copyable and supports move semantics via the propagate traits.
    /// </remarks>
    /// <seealso cref="CoTaskMemAlloc"/>
    /// <seealso cref="CoTaskMemFree"/>
    template <class T>
    class ComAllocator
    {
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        /// <summary>
        /// Indicates that the allocator should propagate on container move assignment.
        /// </summary>
        using propagate_on_container_move_assignment = std::true_type;

        /// <summary>
        /// Default constructs the allocator. No allocation is performed.
        /// </summary>
        constexpr ComAllocator( ) noexcept
        {
        }

        /// <summary>
        /// Copy constructible and noexcept.
        /// </summary>
        constexpr ComAllocator( const ComAllocator& ) noexcept = default;

        /// <summary>
        /// Converting constructor from an allocator of a different type.
        /// Provided for allocator compatibility with standard containers.
        /// </summary>
        /// <typeparam name="U">Other allocator value type.</typeparam>
        template <class U>
        constexpr ComAllocator( const ComAllocator<U>& ) noexcept
        { }
        constexpr ~ComAllocator( ) = default;
        constexpr ComAllocator& operator=( const ComAllocator& ) = default;

        /// <summary>
        /// Frees memory previously allocated by this allocator using <c>CoTaskMemFree</c>.
        /// </summary>
        /// <param name="ptr">Pointer to memory block to free (may be nullptr).</param>
        /// <param name="count">Number of elements that were allocated (not used by COM allocator).</param>
        /// <remarks>
        /// The COM task allocator does not need the byte count to free memory, so <c>count</c> is unused.
        /// </remarks>
        void deallocate( T* const ptr, const size_t count )
        {
            CoTaskMemFree( ptr );
        }

        /// <summary>
        /// Allocates memory for <paramref name="count"/> elements of type <c>T</c> using <c>CoTaskMemAlloc</c>.
        /// </summary>
        /// <param name="count">The number of elements to allocate.</param>
        /// <returns>
        /// Pointer to the allocated memory. The returned pointer is suitably aligned for objects of type <c>T</c>.
        /// </returns>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown indirectly via <c>ThrowOSError(ERROR_OUTOFMEMORY)</c> if allocation fails.
        /// </exception>
        [[nodiscard]] __declspec( allocator ) T* allocate( const size_t count )
        {
            auto ptr = CoTaskMemAlloc( count * sizeof( T ) );
            if ( !ptr )
            {
                ThrowOSError( ERROR_OUTOFMEMORY );
            }
            return reinterpret_cast<T*>( ptr );
        }

        /// <summary>
        /// Allocates at least <paramref name="count"/> elements and returns the
        /// pointer together with the number of elements actually allocated.
        /// </summary>
        /// <param name="count">The requested minimum number of elements to allocate.</param>
        /// <returns>
        /// An <c>std::allocation_result&lt;T*&gt;</c> containing the pointer to allocated memory
        /// and the number of elements allocated (equal to the requested <paramref name="count"/> on success).
        /// </returns>
        [[nodiscard]] __declspec( allocator ) std::allocation_result<T*> allocate_at_least( const size_t count )
        {
            return { allocate( count ), count };
        }
    };


    /// <summary>
    /// A simple string class that uses CoTaskMemAlloc and CoTaskMemFree
    /// </summary>



    class ComString
    {
        wchar_t* data_ = nullptr;
    public:
        constexpr ComString( ) noexcept = default;

        explicit ComString( wchar_t* data ) noexcept
            : data_( data )
        { }

        explicit ComString( size_t size ) noexcept
        {
            if ( size )
            {
                auto ptr = CoTaskMemAlloc( (size + 1 )*sizeof(wchar_t) );
                if ( !ptr )
                {
                    ThrowOSError( ERROR_OUTOFMEMORY );
                }
                data_ = reinterpret_cast<wchar_t*>( ptr );
#pragma warning(push)
#pragma warning(disable:6011)
                data_[size] = L'\x0';
#pragma warning(pop)
            }
        }


        ComString( const ComString& other ) = delete;
        ComString( ComString&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }

        ~ComString( ) noexcept
        {
            if ( data_ )
            {
                CoTaskMemFree( data_ );
            }
        }

        ComString& operator = ( const ComString& other ) = delete;
        ComString& operator = ( ComString&& other ) noexcept
        {
            std::swap( data_, other.data_ );
        }

        size_t size( ) const
        {
            return data_ ? wcslen( data_ ) : 0;
        }

        void resize( size_t newSize )
        {
            if ( newSize )
            {
                if ( data_ )
                {
                    auto ptr = CoTaskMemRealloc( data_, ( newSize + 1 ) * sizeof( wchar_t ) );
                    if ( !ptr )
                    {
                        ThrowOSError( ERROR_OUTOFMEMORY );
                    }
                    data_ = reinterpret_cast<wchar_t*>( ptr );
                }
                else
                {
                    auto ptr = CoTaskMemAlloc( ( newSize + 1 ) * sizeof( wchar_t ) );
                    if ( !ptr )
                    {
                        ThrowOSError( ERROR_OUTOFMEMORY );
                    }
                    data_ = reinterpret_cast<wchar_t*>( ptr );
                }
#pragma warning(push)
#pragma warning(disable:6011)
                data_[newSize] = L'\x0';
#pragma warning(pop)
            }
            else
            {
                if ( data_ )
                {
                    CoTaskMemFree( data_ );
                    data_ = nullptr;
                }
            }
        }


        wchar_t& operator[]( size_t index )
        {
            return data_[index];
        }
        const wchar_t& operator[]( size_t index ) const
        {
            return data_[index];
        }

        WideString ToString( ) const
        {
            return WideString( data_ );
        }

        wchar_t* c_str( )
        {
            return data_;
        }
        const wchar_t* c_str( ) const
        {
            return data_;
        }
        wchar_t* data( )
        {
            return data_;
        }
        const wchar_t* data( ) const
        {
            return data_;
        }



    };


    namespace Com
    {
        /// <summary>
        /// Determines the concurrency model used for incoming calls to objects 
        /// created by this thread. This concurrency model can be either 
        /// apartment-threaded or multithreaded.
        /// </summary>
        /// <remarks>
        /// <para>
        /// When a thread is initialized through a call to Com::Initialize, you choose 
        /// whether to initialize it as apartment-threaded or multithreaded by 
        /// designating one of the members of ApartmentModel as its second parameter. 
        /// This designates how incoming calls to any object created by that thread 
        /// are handled, that is, the object's concurrency.
        /// </para>
        /// <para>
        /// Apartment-threading, while allowing for multiple threads of execution, 
        /// serializes all incoming calls by requiring that calls to methods of 
        /// objects created by this thread always run on the same thread, i.e. the 
        /// apartment/thread that created them. In addition, calls can arrive only 
        /// at message-queue boundaries. Because of this serialization, it is not 
        /// typically necessary to write concurrency control into the code for the 
        /// object, other than to avoid calls to PeekMessage and SendMessage during 
        /// processing that must not be interrupted by other method invocations or 
        /// calls to other objects in the same apartment/thread.
        /// </para>
        /// <para>
        /// Multi-threading (also called free-threading) allows calls to methods of 
        /// objects created by this thread to be run on any thread. There is no 
        /// serialization of calls, i.e. many calls may occur to the same method or 
        /// to the same object or simultaneously. Multi-threaded object concurrency 
        /// offers the highest performance and takes the best advantage of multiprocessor 
        /// hardware for cross-thread, cross-process, and cross-machine calling, since 
        /// calls to objects are not serialized in any way. This means, however, 
        /// that the code for objects must enforce its own concurrency model, typically 
        /// through the use of synchronization primitives, such as critical sections, 
        /// semaphores, or mutexes.
        /// </para>
        /// </remarks>
        enum class ApartmentModel : DWORD
        {
            /// <summary>
            /// Initializes the thread for apartment-threaded object concurrency
            /// </summary>
            ApartmentThreaded = COINIT_APARTMENTTHREADED,
            /// <summary>
            /// Initializes the thread for multithreaded object concurrency
            /// </summary>
            MultiThreaded = COINIT_MULTITHREADED,
            /// <summary>
            /// Disables DDE for OLE1 support.
            /// </summary>
            DisableOle1Dde = COINIT_DISABLE_OLE1DDE,
            /// <summary>
            /// Increase memory usage in an attempt to increase performance.
            /// </summary>
            SpeedOverMemory = COINIT_SPEED_OVER_MEMORY,
            Default = MultiThreaded | SpeedOverMemory
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( ApartmentModel, DWORD );

        /// <summary>
        /// The authentication-level constants represent authentication levels passed to 
        /// various run-time functions. These levels are listed in order of increasing 
        /// authentication. Each new level adds to the authentication provided by the 
        /// previous level. If the RPC run-time library does not support the specified 
        /// level, it automatically upgrades to the next higher supported level.
        /// </summary>
        enum class AuthenticationLevel : DWORD
        {
            /// <summary>
            /// Uses the default authentication level for the specified authentication service.
            /// </summary>
            Default = RPC_C_AUTHN_LEVEL_DEFAULT,
            /// <summary>
            /// Performs no authentication.
            /// </summary>
            None = RPC_C_AUTHN_LEVEL_NONE,
            /// <summary>
            /// Authenticates only when the client establishes a relationship with a server.
            /// </summary>
            Connect = RPC_C_AUTHN_LEVEL_CONNECT,
            /// <summary>
            /// Authenticates only at the beginning of each remote procedure call when the 
            /// server receives the request. Does not apply to remote procedure calls made 
            /// using the connection-based protocol sequences (those that start with the 
            /// prefix "ncacn"). If the protocol sequence in a binding handle is a 
            /// connection-based protocol sequence and you specify this level, this routine 
            /// instead uses the AuthenticationLevel::Packet constant.
            /// </summary>
            Call = RPC_C_AUTHN_LEVEL_CALL,
            /// <summary>
            /// Authenticates only that all data received is from the expected client. Does 
            /// not validate the data itself.
            /// </summary>
            Packet = RPC_C_AUTHN_LEVEL_PKT,
            /// <summary>
            /// Authenticates and verifies that none of the data transferred between 
            /// client and server has been modified.
            /// </summary>
            PacketIntegrity = RPC_C_AUTHN_LEVEL_PKT_INTEGRITY,
            /// <summary>
            /// Includes all previous levels, and ensures clear text data can only be seen 
            /// by the sender and the receiver. In the local case, this involves using a 
            /// secure channel. In the remote case, this involves encrypting the argument 
            /// value of each remote procedure call.
            /// </summary>
            PacketPrivacy = RPC_C_AUTHN_LEVEL_PKT_PRIVACY
        };
        

        /// <summary>
        /// Specifies an impersonation level, which indicates the amount of 
        /// authority given to the server when it is impersonating the client.
        /// </summary>
        enum class ImpersonationLevel : DWORD
        {
            /// <summary>
            /// DCOM can choose the impersonation level using its normal 
            /// security blanket negotiation algorithm.
            /// </summary>
            Default = RPC_C_IMP_LEVEL_DEFAULT,
            /// <summary>
            /// The client is anonymous to the server. The server process can impersonate 
            /// the client, but the impersonation token will not contain any information 
            /// and cannot be used.
            /// </summary>
            Anonymous  = RPC_C_IMP_LEVEL_ANONYMOUS,
            /// <summary>
            /// The server can obtain the client's identity. The server can impersonate the 
            /// client for ACL checking, but it cannot access system objects as the client.
            /// </summary>
            Identify = RPC_C_IMP_LEVEL_IDENTIFY,
            /// <summary>
            /// The server process can impersonate the client's security context while acting 
            /// on behalf of the client. This level of impersonation can be used to access 
            /// local resources such as files. When impersonating at this level, the 
            /// impersonation token can only be passed across one machine boundary. The 
            /// Schannel authentication service only supports this level of impersonation.
            /// </summary>
            Impersonate = RPC_C_IMP_LEVEL_IMPERSONATE,
            /// <summary>
            /// The server process can impersonate the client's security context while 
            /// acting on behalf of the client. The server process can also make outgoing 
            /// calls to other servers while acting on behalf of the client, using cloaking. 
            /// The server may use the client's security context on other machines to 
            /// access local and remote resources as the client. When impersonating at 
            /// this level, the impersonation token can be passed across any number of 
            /// computer boundaries.
            /// </summary>
            Delegate = RPC_C_IMP_LEVEL_DELEGATE
        };

        /// <summary>
        /// Specifies various capabilities for InitializeSecurity
        /// </summary>
        /// <remarks>
        /// 
        /// </remarks>
        enum class AuthenticationCapabilities : DWORD
        {
            /// <summary>
            /// Indicates that no capability flags are set.
            /// </summary>
            None = EOAC_NONE,
            /// <summary>
            /// If this flag is specified, it will be ignored. Support for mutual 
            /// authentication is automatically provided by some authentication services.
            /// </summary>
            MutualAuthentication = EOAC_MUTUAL_AUTH,
            /// <summary>
            /// <p>
            /// Sets static cloaking. When this flag is set, DCOM uses the thread token 
            /// (if present) when determining the client's identity. However, the client's 
            /// identity is determined on the first call on each proxy (if SetBlanket is 
            /// not called) and each time CoSetProxyBlanket is called on the proxy.
            /// </p>
            /// <p>
            /// CoInitializeSecurity and IClientSecurity::SetBlanket return errors if 
            /// both cloaking flags are set or if either flag is set when Schannel is 
            /// the authentication service.
            /// </p>
            /// </summary>
            StaticCloaking = EOAC_STATIC_CLOAKING,
            /// <summary>
            /// Sets dynamic cloaking. When this flag is set, DCOM uses the thread token 
            /// (if present) when determining the client's identity. On each call to a proxy, 
            /// the current thread token is examined to determine whether the client's identity 
            /// has changed (incurring an additional performance cost) and the client is 
            /// authenticated again only if necessary. Dynamic cloaking can be set by clients only.
            /// </summary>
            DynamicCloaking = EOAC_DYNAMIC_CLOAKING,
            /// <summary>
            /// This flag is obsolete.
            /// </summary>
            AnyAuthority = EOAC_ANY_AUTHORITY,
            /// <summary>
            /// Causes DCOM to send Schannel server principal names in fullsic format to 
            /// clients as part of the default security negotiation. The name is extracted 
            /// from the server certificate.
            /// </summary>
            MakeFullsic = EOAC_MAKE_FULLSIC,
            /// <summary>
            /// Tells DCOM to use the valid capabilities from the call to CoInitializeSecurity. 
            /// If CoInitializeSecurity was not called, EOAC_NONE will be used for the capabilities 
            /// flag. This flag can be set only by clients in a call to IClientSecurity::SetBlanket 
            /// or CoSetProxyBlanket.
            /// </summary>
            Default = EOAC_DEFAULT,
            /// <summary>
            /// <p>
            /// Authenticates distributed reference count calls to prevent malicious users from 
            /// releasing objects that are still being used. If this flag is set, which can be 
            /// done only in a call to CoInitializeSecurity by the client, the authentication 
            /// level (in dwAuthnLevel) cannot be set to none.
            /// </p>
            /// <p>
            /// The server always authenticates Release calls. Setting this flag prevents an 
            /// authenticated client from releasing the objects of another authenticated client. 
            /// It is recommended that clients always set this flag, although performance is 
            /// affected because of the overhead associated with the extra security.
            /// </p>
            /// </summary>
            SecureRefs = EOAC_SECURE_REFS,
            /// <summary>
            /// <p>
            /// Indicates that the pSecDesc parameter to CoInitializeSecurity is a pointer to an 
            /// IAccessControl interface on an access control object. When DCOM makes security 
            /// checks, it calls IAccessControl::IsAccessAllowed. This flag is set only by the 
            /// server.
            /// </p>
            /// <p>
            /// CoInitializeSecurity returns an error if both the AppId and AccessControl flags 
            /// are set.
            /// </p>
            /// </summary>
            AccessControl = EOAC_ACCESS_CONTROL,
            /// <summary>
            /// Indicates that the pSecDesc parameter to CoInitializeSecurity is a pointer to a 
            /// GUID that is an AppID. The CoInitializeSecurity function looks up the AppID in 
            /// the registry and reads the security settings from there. If this flag is set, 
            /// all other parameters to CoInitializeSecurity are ignored and must be zero. 
            /// Only the server can set this flag. 
            /// </summary>
            AppId = EOAC_APPID,
            /// <summary>
            /// Reserved.
            /// </summary>
            Dynamic = EOAC_DYNAMIC,
            /// <summary>
            /// Causes DCOM to fail CoSetProxyBlanket calls where an Schannel principal name 
            /// is specified in any format other than fullsic. This flag is currently for 
            /// clients only.
            /// </summary>
            RequireFullsic = EOAC_REQUIRE_FULLSIC,
            /// <summary>
            /// Reserved.
            /// </summary>
            AutoImpersonate = EOAC_AUTO_IMPERSONATE,
            /// <summary>
            /// <p>
            /// Causes any activation where a server process would be launched under the caller's 
            /// identity (activate-as-activator) to fail with E_ACCESSDENIED. This value, which 
            /// can be specified only in a call to CoInitializeSecurity by the client, allows an 
            /// application that runs under a privileged account (such as LocalSystem) to help 
            /// prevent its identity from being used to launch untrusted components.
            /// </p>
            /// </summary>
            DisableActivateAsActivator = EOAC_DISABLE_AAA,
            /// <summary>
            /// Specifying this flag helps protect server security when using DCOM or COM+. 
            /// It reduces the chances of executing arbitrary DLLs because it allows the 
            /// marshaling of only CLSIDs that are implemented in Ole32.dll, ComAdmin.dll, 
            /// ComSvcs.dll, or Es.dll, or that implement the CATID_MARSHALER category ID. 
            /// Any service that is critical to system operation should set this flag.
            /// </summary>
            NoCustomMarshal = EOAC_NO_CUSTOM_MARSHAL,
            Reserved1 = EOAC_RESERVED1
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( AuthenticationCapabilities, DWORD );

        /// <summary>
        /// Defines authentication services by identifying the security package that 
        /// provides the service, such as NTLMSSP, Kerberos, or Schannel.
        /// </summary>
        enum class AuthenticationService : DWORD
        {
            None = RPC_C_AUTHN_NONE,
            /// <summary>
            /// DCE private key authentication.
            /// </summary>
            DcePrivate = RPC_C_AUTHN_DCE_PRIVATE,
            /// <summary>
            /// DCE public key authentication.
            /// </summary>
            DcePublic = RPC_C_AUTHN_DCE_PUBLIC,
            /// <summary>
            /// DEC public key authentication. Reserved for future use.
            /// </summary>
            DecPublic = RPC_C_AUTHN_DEC_PUBLIC,
            /// <summary>
            /// Snego security support provider.
            /// </summary>
            GssNegotiate = RPC_C_AUTHN_GSS_NEGOTIATE,
            /// <summary>
            /// NTLMSSP
            /// </summary>
            WinNT = RPC_C_AUTHN_WINNT,
            /// <summary>
            /// Schannel security support provider. This authentication service supports SSL 2.0, SSL 3.0, TLS, and PCT.
            /// </summary>
            GssSchannel = RPC_C_AUTHN_GSS_SCHANNEL,
            /// <summary>
            /// Kerberos security support provider.
            /// </summary>
            GssKerberos = RPC_C_AUTHN_GSS_KERBEROS,
            /// <summary>
            /// DPA security support provider.
            /// </summary>
            Dpa = RPC_C_AUTHN_DPA,
            /// <summary>
            /// MSN security support provider.
            /// </summary>
            Msn = RPC_C_AUTHN_MSN,
            /// <summary>
            /// Digest security support provider.
            /// </summary>
            Digest = RPC_C_AUTHN_DIGEST,
            /// <summary>
            /// Kernel security support provider.
            /// </summary>
            Kernel = RPC_C_AUTHN_KERNEL,
            /// <summary>
            /// NEGO extender security support provider.
            /// </summary>
            NegoExtender = RPC_C_AUTHN_NEGO_EXTENDER,
            /// <summary>
            /// PKU2U security support provider.
            /// </summary>
            Pku2u = RPC_C_AUTHN_PKU2U,
            LiveSsp = RPC_C_AUTHN_LIVE_SSP,
            LiveXPSsp = RPC_C_AUTHN_LIVEXP_SSP,
            CloudAP = RPC_C_AUTHN_CLOUD_AP,
            MsOnline = RPC_C_AUTHN_MSONLINE,
            /// <summary>
            /// MQ security support provider.
            /// </summary>
            MQ = RPC_C_AUTHN_MQ,
            /// <summary>
            /// The system default authentication service. When this value is specified, 
            /// COM uses its normal security blanket negotiation algorithm to pick an 
            /// authentication service.
            /// </summary>
            Default = RPC_C_AUTHN_DEFAULT
        };

        /// <summary>
        /// The authorization service constants represent the authorization services 
        /// passed to various run-time functions.
        /// </summary>
        enum class Authorization : DWORD
        {
            /// <summary>
            /// Server performs no authorization.
            /// </summary>
            None = RPC_C_AUTHZ_NONE,
            /// <summary>
            /// Server performs authorization based on the client's principal name.
            /// </summary>
            Name = RPC_C_AUTHZ_NAME,
            /// <summary>
            /// Server performs authorization checking using the client's DCE privilege 
            /// attribute certificate (PAC) information, which is sent to the server 
            /// with each remote procedure call made using the binding handle. 
            /// Generally, access is checked against DCE access control lists
            /// </summary>
            DCE = RPC_C_AUTHZ_DCE,
            /// <summary>
            /// Server uses the default authorization service for the current SSP.
            /// </summary>
            Default = RPC_C_AUTHZ_DEFAULT,
        };

        /// <summary>
        /// Initializes the COM library for use by the calling thread and sets the thread's concurrency model.
        /// </summary>
        /// <param name="apartmentModel">
        /// The concurrency model for the calling thread. Defaults to <see cref="ApartmentModel::Default"/>.
        /// </param>
        /// <remarks>
        /// This function calls <c>CoInitializeEx</c> with the specified apartment model and converts any failing
        /// HRESULT into the project's exception type via <c>HCC_COM_CHECK_HRESULT</c>.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when <c>CoInitializeEx</c> returns a failing HRESULT.
        /// </exception>

        inline void Initialize( ApartmentModel apartmentModel = ApartmentModel::Default )
        {
            auto hr = CoInitializeEx( 0, static_cast<DWORD>( apartmentModel ) );
            HCC_COM_CHECK_HRESULT( hr );
        }

        /// <summary>
        /// Closes the COM library on the current thread, unloads all DLLs loaded by the 
        /// thread, frees any other resources that the thread maintains, and forces all 
        /// RPC connections on the thread to close.
        /// </summary>
        /// <remarks>
        /// This function calls <c>CoUninitialize</c>. It complements a prior call to <see cref="Initialize"/>.
        /// No exceptions are thrown from this function.
        /// </remarks> 
        inline void Uninitialize( )
        {
            CoUninitialize( );
        }

		/// <summary>
        /// Registers process-wide COM security and sets default security values for the process.
        /// </summary>
        /// <param name="securityDescriptor">
        /// Optional pointer to a security descriptor that specifies the access control for COM objects.
        /// May be <c>nullptr</c> to use default security.
        /// </param>
        /// <param name="authenticationServicesSize">
        /// Number of authentication services provided in <paramref name="authenticationServices"/>.
        /// </param>
        /// <param name="authenticationServices">
        /// Optional array of <c>SOLE_AUTHENTICATION_SERVICE</c> entries describing authentication services.
        /// May be <c>nullptr</c> when no explicit authentication services are provided.
        /// </param>
        /// <param name="authenticationLevel">
        /// The authentication level to use for COM calls. See <see cref="AuthenticationLevel"/>.
        /// </param>
        /// <param name="impersonationLevel">
        /// The impersonation level to use for COM calls. See <see cref="ImpersonationLevel"/>.
        /// </param>
        /// <param name="authenticationList">
        /// Optional pointer to a <c>SOLE_AUTHENTICATION_LIST</c> structure specifying additional authentication info.
        /// May be <c>nullptr</c>.
        /// </param>
        /// <param name="authenticationCapabilities">
        /// Additional flags that control COM authentication capabilities. See <see cref="AuthenticationCapabilities"/>.
        /// </param>
        /// <remarks>
        /// This wrapper forwards to <c>CoInitializeSecurity</c> and uses <c>HCC_COM_CHECK_HRESULT</c> to
        /// translate failing HRESULTs into the project's exception type. Callers should ensure the security
        /// parameters are valid for the process and understand that CoInitializeSecurity may only be called once
        /// per process in many scenarios.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when <c>CoInitializeSecurity</c> returns a failing HRESULT.
        /// </exception>
        inline void InitializeSecurity( _In_opt_ PSECURITY_DESCRIPTOR securityDescriptor,
            _In_ LONG authenticationServicesSize,
            _In_reads_opt_( authenticationServicesSize ) SOLE_AUTHENTICATION_SERVICE* authenticationServices,
            _In_ AuthenticationLevel authenticationLevel,
            _In_ ImpersonationLevel impersonationLevel,
            _In_opt_ PSOLE_AUTHENTICATION_LIST authenticationList,
            _In_ AuthenticationCapabilities authenticationCapabilities )
        {
            auto hr = CoInitializeSecurity( securityDescriptor, authenticationServicesSize, authenticationServices, nullptr, static_cast<DWORD>( authenticationLevel ), static_cast<DWORD>( impersonationLevel ), authenticationList, static_cast<DWORD>( authenticationCapabilities ), nullptr );
            HCC_COM_CHECK_HRESULT( hr );
        }

        /// <summary>
        /// Convenience wrapper to initialize client-side COM security with common defaults.
        /// </summary>
        /// <param name="securityDescriptor">Optional security descriptor (default: <c>nullptr</c>).</param>
        /// <param name="authenticationServicesSize">Size of <paramref name="authenticationServices"/> (default: -1).</param>
        /// <param name="authenticationServices">Optional authentication services (default: <c>nullptr</c>).</param>
        /// <param name="authenticationLevel">Requested authentication level (default: <see cref="AuthenticationLevel::Default"/>).</param>
        /// <param name="impersonationLevel">Requested impersonation level (default: <see cref="ImpersonationLevel::Impersonate"/>).</param>
        /// <param name="authenticationList">Optional authentication list (default: <c>nullptr</c>).</param>
        /// <param name="authenticationCapabilities">Authentication capability flags (default: <see cref="AuthenticationCapabilities::None"/>).</param>
        /// <remarks>
        /// This helper forwards to <see cref="InitializeSecurity"/> using the configured defaults suitable for clients.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when underlying security initialization fails.
        /// </exception>
        inline void InitializeClientSecurity( _In_opt_ PSECURITY_DESCRIPTOR securityDescriptor = nullptr,
            _In_ LONG authenticationServicesSize = -1,
            _In_reads_opt_( authenticationServicesSize ) SOLE_AUTHENTICATION_SERVICE* authenticationServices = nullptr,
            _In_ AuthenticationLevel authenticationLevel = AuthenticationLevel::Default,
            _In_ ImpersonationLevel impersonationLevel = ImpersonationLevel::Impersonate,
            _In_opt_ PSOLE_AUTHENTICATION_LIST authenticationList = nullptr,
            _In_ AuthenticationCapabilities authenticationCapabilities = AuthenticationCapabilities::None )
        {
            InitializeSecurity( securityDescriptor, authenticationServicesSize, authenticationServices, authenticationLevel, impersonationLevel, authenticationList, authenticationCapabilities );
        }


        /// <summary>
        /// Configures the authentication information for a proxy by calling <c>CoSetProxyBlanket</c>.
        /// </summary>
        /// <param name="proxy">The proxy <c>IUnknown</c> for which to set the blanket.</param>
        /// <param name="authenticationService">Authentication service to use. See <see cref="AuthenticationService"/>.</param>
        /// <param name="authorization">Authorization service to use. See <see cref="Authorization"/>.</param>
        /// <param name="serverPrincipalName">Optional server principal name (SPN) for the target server, or <c>nullptr</c>.</param>
        /// <param name="authenticationLevel">Authentication level to request. See <see cref="AuthenticationLevel"/>.</param>
        /// <param name="impersonationLevel">Impersonation level to request. See <see cref="ImpersonationLevel"/>.</param>
        /// <param name="authInfo">Optional pointer to credentials (RPC_AUTH_IDENTITY_HANDLE) for the call, or <c>nullptr</c>.</param>
        /// <param name="authenticationCapabilities">Additional authentication capability flags. See <see cref="AuthenticationCapabilities"/>.</param>
        /// <remarks>
        /// The function forwards the call to <c>CoSetProxyBlanket</c> and throws on failure via <c>HCC_COM_CHECK_HRESULT</c>.
        /// Use the <c>SetClientProxyBlanket</c> overloads to apply common client-side defaults.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when <c>CoSetProxyBlanket</c> returns a failing HRESULT.
        /// </exception>
        inline void SetProxyBlanket( _In_ IUnknown* proxy,
            _In_ AuthenticationService authenticationService,
            _In_ Authorization authorization,
            _In_opt_ OLECHAR* serverPrincipalName,
            _In_ AuthenticationLevel authenticationLevel,
            _In_ ImpersonationLevel impersonationLevel,
            _In_opt_ RPC_AUTH_IDENTITY_HANDLE authInfo,
            _In_ AuthenticationCapabilities authenticationCapabilities )
        {
            auto hr = CoSetProxyBlanket( proxy, static_cast<DWORD>( authenticationService ), static_cast<DWORD>( authorization ), serverPrincipalName, static_cast<DWORD>( authenticationLevel ), static_cast<DWORD>( impersonationLevel ), authInfo, static_cast<DWORD>( authenticationCapabilities ) );
            HCC_COM_CHECK_HRESULT( hr );
        }


        /// <summary>
        /// Convenience overload that sets a client proxy blanket with typical defaults.
        /// </summary>
        /// <param name="proxy">The proxy <c>IUnknown</c> to configure.</param>
        /// <param name="authenticationService">Authentication service (default: <see cref="AuthenticationService::WinNT"/>).</param>
        /// <param name="authorization">Authorization service (default: <see cref="Authorization::None"/>).</param>
        /// <param name="serverPrincipalName">Optional server principal name (default: <c>nullptr</c>).</param>
        /// <param name="authenticationLevel">Authentication level (default: <see cref="AuthenticationLevel::Call"/>).</param>
        /// <param name="impersonationLevel">Impersonation level (default: <see cref="ImpersonationLevel::Impersonate"/>).</param>
        /// <param name="authInfo">Optional credentials (default: <c>nullptr</c>).</param>
        /// <param name="authenticationCapabilities">Authentication capability flags (default: <see cref="AuthenticationCapabilities::None"/>).</param>
        /// <remarks>
        /// This overload forwards to <see cref="SetProxyBlanket"/> using commonly used client defaults.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        inline void SetClientProxyBlanket( _In_ IUnknown* proxy,
            _In_ AuthenticationService authenticationService = AuthenticationService::WinNT,
            _In_ Authorization authorization = Authorization::None,
            _In_opt_ OLECHAR* serverPrincipalName = nullptr,
            _In_ AuthenticationLevel authenticationLevel = AuthenticationLevel::Call,
            _In_ ImpersonationLevel impersonationLevel = ImpersonationLevel::Impersonate,
            _In_opt_ RPC_AUTH_IDENTITY_HANDLE authInfo = nullptr,
            _In_ AuthenticationCapabilities authenticationCapabilities = AuthenticationCapabilities::None )
        {
            SetProxyBlanket( proxy, authenticationService, authorization, serverPrincipalName, authenticationLevel, impersonationLevel, authInfo, authenticationCapabilities );
        }
        
        /// <summary>
        /// Convenience overload that sets a client proxy blanket using an <see cref="Unknown"/> wrapper.
        /// </summary>
        /// <param name="proxy">The <see cref="Unknown"/> wrapper for the proxy to configure.</param>
        /// <param name="authenticationService">Authentication service (default: <see cref="AuthenticationService::WinNT"/>).</param>
        /// <param name="authorization">Authorization service (default: <see cref="Authorization::None"/>).</param>
        /// <param name="serverPrincipalName">Optional server principal name (default: <c>nullptr</c>).</param>
        /// <param name="authenticationLevel">Authentication level (default: <see cref="AuthenticationLevel::Call"/>).</param>
        /// <param name="impersonationLevel">Impersonation level (default: <see cref="ImpersonationLevel::Impersonate"/>).</param>
        /// <param name="authInfo">Optional credentials (default: <c>nullptr</c>).</param>
        /// <param name="authenticationCapabilities">Authentication capability flags (default: <see cref="AuthenticationCapabilities::None"/>).</param>
        /// <remarks>
        /// Forwards to <see cref="SetClientProxyBlanket(IUnknown*, ...)"/> using the raw pointer obtained from the wrapper.
        /// </remarks>
        /// <exception cref="Harlinn::Common::Core::Exception">
        /// Thrown when the underlying COM call fails.
        /// </exception>
        inline void SetClientProxyBlanket( const Unknown& proxy,
            _In_ AuthenticationService authenticationService = AuthenticationService::WinNT,
            _In_ Authorization authorization = Authorization::None,
            _In_opt_ OLECHAR* serverPrincipalName = nullptr,
            _In_ AuthenticationLevel authenticationLevel = AuthenticationLevel::Call,
            _In_ ImpersonationLevel impersonationLevel = ImpersonationLevel::Impersonate,
            _In_opt_ RPC_AUTH_IDENTITY_HANDLE authInfo = nullptr,
            _In_ AuthenticationCapabilities authenticationCapabilities = AuthenticationCapabilities::None )
        {
            SetProxyBlanket( proxy.GetInterfacePointer(), authenticationService, authorization, serverPrincipalName, authenticationLevel, impersonationLevel, authInfo, authenticationCapabilities );
        }

        /// <summary>
        /// Returns the set of known COM interface names that the supplied COM object supports.
        /// </summary>
        /// <param name="unknown">
        /// Pointer to a COM object implementing <c>IUnknown</c>. If <c>null</c>, the function returns an empty vector.
        /// </param>
        /// <returns>
        /// A <c>std::vector&lt;WideString&gt;</c> containing the friendly names of each known interface for which
        /// <c>QueryInterface</c> succeeds. The returned list includes an entry for <c>"IUnknown"</c> when supported,
        /// and one entry per interface defined by the <c>HCCComInterfaces.xm</c> include macro expansion.
        /// </returns>
        /// <remarks>
        /// The function performs a series of temporary <c>QueryInterface</c> calls � each successful call will acquire
        /// a reference which is immediately released by this routine. The caller is responsible for COM initialization
        /// on the calling thread (for example, by calling <c>CoInitializeEx</c> or equivalent) before invoking this function.
        /// This routine does not throw on COM failure; it simply omits interfaces that fail the <c>QueryInterface</c> call.
        /// </remarks>
        /// <exception cref="std::bad_alloc">
        /// Thrown if memory allocation for the returned vector or for any contained <c>WideString</c> fails.
        /// </exception>
        /// <example>
        /// std::vector&lt;WideString&gt; supported = Com::GetSupportedKnownInterfaces(pUnknown);
        /// for (const auto&amp; name : supported)
        /// {
        ///     wprintf(L"%ls\n", name.c_str());
        /// }
        /// </example>
        HCC_EXPORT std::vector<WideString> GetSupportedKnownInterfaces(IUnknown* unknown);
        
        /// <summary>
        /// Writes the names of supported known interfaces for the specified IUnknown to the standard output.
        /// </summary>
        /// <param name="unknown">Pointer to an <c>IUnknown</c> to be examined.</param>
        /// <remarks>
        /// This helper calls <see cref="GetSupportedKnownInterfaces(IUnknown*)"/>, iterates the returned list
        /// of interface names and prints each on a separate line using <c>_putws</c>. It is intended as a
        /// debugging aid and not for production-localization-sensitive logging.
        /// </remarks>
        inline void PrintSupportedKnownInterfaces( IUnknown* unknown )
        {
            auto comInterfaces = GetSupportedKnownInterfaces( unknown );
            for ( auto& comInterface : comInterfaces )
            {
                _putws( comInterface.c_str() );
            }
        }

        /// <summary>
        /// Writes the names of supported known interfaces for the specified Unknown wrapper to the standard output.
        /// </summary>
        /// <param name="unknown">Reference to an <see cref="Unknown"/> wrapper to be examined.</param>
        /// <remarks>
        /// Overload that forwards to <see cref="PrintSupportedKnownInterfaces(IUnknown*)"/>.
        /// </remarks>
        inline void PrintSupportedKnownInterfaces( const Unknown& unknown )
        {
            PrintSupportedKnownInterfaces( unknown.GetInterfacePointer( ) );
        }

        /// <summary>
        /// Retrieves the Guids of supported known interfaces.
        /// </summary>
        /// <param name="unknown">
        /// The pointer to the IUnknown interface that will be interrogated.
        /// </param>
        /// <returns>
        /// The Guids of the interfaces the function was able to identify.
        /// </returns>
        HCC_EXPORT std::vector<Guid> GetSupportedKnownInterfaceIds(IUnknown* unknown);

    }
}

namespace std
{
    template<>
    inline void swap<Harlinn::Common::Core::Unknown>( Harlinn::Common::Core::Unknown& first, Harlinn::Common::Core::Unknown& second ) noexcept
    {
        first.swap( second );
    }
}


#endif
