#pragma once
#ifndef __HCCCOM_H__
#define __HCCCOM_H__
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
    /// Base class for COM interface wrappers
    /// </summary>
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
        /// Returns the currently held interface pointer,
        /// setting the interface pointer of the object to
        /// <c>nullptr</c>.
        /// </summary>
        /// <returns></returns>
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
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromClassId( const WideString& clsid, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            return CoCreateInstanceFromClassId( clsid.c_str( ), classContext );
        }

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
        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromProgId( const WideString& progId, DWORD classContext = CLSCTX_INPROC_SERVER )
        {
            return CoCreateInstanceFromProgId( progId, classContext );
        }

        template<typename T = Unknown>
            requires std::is_base_of_v<Unknown, T>
        static T CoCreateInstanceFromDll( const ModuleHandle& dll, const CLSID& clsid );


    };

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

#define HCC_COM_STANDARD_METHODS_IMPL2( classType, baseClassType ) HCC_COM_STANDARD_METHODS_IMPL(classType, baseClassType,I##classType, I##baseClassType)

#define HCC_COM_CHECK_HRESULT( hr ) if ( FAILED( hr ) ) do { CheckHRESULT( hr, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); } while(false)

#define HCC_COM_CHECK_HRESULT2( hr, itf ) if ( FAILED( hr ) ) do { CheckHRESULT( hr, itf, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); } while(false)


    /// <summary>
    /// A generic smart pointer for managing COM interfaces.
    /// </summary>
    /// <typeparam name="T">
    /// The type of the COM interface
    /// </typeparam>
    template<typename T>
    class ComPtr : public Unknown
    {
    public:
        using Base = Unknown;
        using InterfaceType = T;
        constexpr ComPtr( ) noexcept
            : Base( nullptr )
        {
        }

        explicit ComPtr( T* unknown ) noexcept
            : Base( unknown )
        {
        }

        ComPtr( const ComPtr& other ) noexcept
            : Base( other )
        {
        }

        ComPtr( ComPtr&& other ) noexcept
            : Base( std::move(static_cast< Unknown&& >(other)) )
        {
        }


        ComPtr& operator = ( const ComPtr& other ) noexcept
        {
            Base::operator=( other );
            return *this;
        }

        ComPtr& operator = ( ComPtr&& other ) noexcept
        {
            Base::operator=( std::move( static_cast< Unknown&& >( other ) ) );
            return *this;
        }


        T* operator -> ( ) const noexcept
        {
            return (T*)unknown_;
        }
        std::add_lvalue_reference_t<T> operator* ( ) const noexcept
        {
            return *unknown_;
        }


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
        /// Disables calls to AddRef and Release.
        /// </summary>
        /// <typeparam name="T">
        /// Any class derived from Unknown.
        /// </typeparam>
        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        class Attached : public T
        { 
        public:
            using Base = T;
            using InterfaceType = typename Base::InterfaceType;
        protected:
            using Base::unknown_;
        public:
            Attached()
                : Base()
            { }

            explicit Attached( InterfaceType* itf  )
                : Base( itf, false )
            {
            }

            Attached( const Attached& other )
            {
                unknown_ = other.unknown_;
            }

            Attached( Attached&& other ) noexcept
            {
                std::swap(unknown_, other.unknown_);
            }

            Attached( const Base& other )
            {
                unknown_ = other.unknown_;
            }

            ~Attached( )
            {
                unknown_ = nullptr;
            }


            Attached& operator = ( const Attached& other )
            {
                unknown_ = other.unknown_;
                return *this;
            }

            Attached& operator = ( Attached&& other ) noexcept
            {
                std::swap( unknown_, other.unknown_ );
                return *this;
            }

            Attached& operator = ( const Base& other )
            {
                unknown_ = other.unknown_;
                return *this;
            }

            constexpr bool operator == ( const Attached& other ) const noexcept
            {
                return unknown_ == other.unknown_;
            }
            constexpr bool operator == ( const Base& other ) const noexcept
            {
                return unknown_ == other.unknown_;
            }
            constexpr bool operator == ( const InterfaceType* other ) const noexcept
            {
                return unknown_ == other;
            }
        };
    }

    

    class AsyncUnknown : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( AsyncUnknown, Unknown, AsyncIUnknown, IUnknown )

        void Begin_QueryInterface( REFIID riid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Begin_QueryInterface( riid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Finish_QueryInterface( void** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Finish_QueryInterface( result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Begin_AddRef( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Begin_AddRef( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        ULONG Finish_AddRef( ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->Finish_AddRef( );
        }

        void Begin_Release( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Begin_Release( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        ULONG Finish_Release( ) const
        {
            auto pInterface = GetInterface( );
            return pInterface->Finish_Release( );
        }

    };


    /// <summary>
    /// Enables a class of objects to be created.
    /// </summary>
    class ClassFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ClassFactory,Unknown, IClassFactory, IUnknown )

        void CreateInstance( IUnknown* outerUnknown, REFIID riid, void** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( outerUnknown, riid, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateInstance( const Unknown& outerUnknown, REFIID riid, void** result ) const
        {
            CreateInstance( outerUnknown.GetInterfacePointer(), riid, result );
        }
        void CreateInstance( REFIID riid, void** result ) const
        {
            CreateInstance( nullptr, riid, result );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown,T>
        void CreateInstance( IUnknown* outerUnknown, T** result ) const
        {
            CreateInstance( outerUnknown, __uuidof( T ), reinterpret_cast<void**>( result ) );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstance( const Unknown& outerUnknown, T** result ) const
        {
            CreateInstance( outerUnknown.GetInterfacePointer( ), result );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void CreateInstance( T** result ) const
        {
            CreateInstance( nullptr, __uuidof( T ), reinterpret_cast<void**>( result ) );
        }

        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        T CreateInstance( IUnknown* outerUnknown ) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            CreateInstance( outerUnknown, reinterpret_cast<void**>( &ptr ) );
            return T( ptr );
        }

        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        T CreateInstance( ) const
        {
            return CreateInstance( nullptr );
        }

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
    /// Enumerate strings. LPOLESTR is the type that indicates a pointer to a zero-terminated string of wide, or Unicode, characters.
    /// </summary>
    class EnumString : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( EnumString, Unknown, IEnumString, IUnknown )

        HCC_EXPORT bool Next( WideString& result ) const;
        HCC_EXPORT bool Next( ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched ) const;
        HCC_EXPORT bool Next( ULONG celt, std::vector<WideString>& result ) const;
        HCC_EXPORT void All( std::vector<WideString>& result ) const;
        HCC_EXPORT void Skip( ULONG celt ) const;
        HCC_EXPORT void Reset( ) const;
        HCC_EXPORT EnumString Clone( ) const;

    };

    /// <summary>
    /// A movable buffer class the handles
    /// memory management using CoTaskMemAlloc,
    /// CoTaskMemFree and CoTaskMemRealloc   
    /// </summary>
    class ComBuffer
    {
        size_t size_ = 0;
        Byte* data_ = nullptr;
    public:
        constexpr ComBuffer( ) noexcept = default;

        explicit ComBuffer( size_t size )
        {
            if ( size )
            {
                data_ = reinterpret_cast<Byte*>( CoTaskMemAlloc( size ) );
                size_ = size;
            }
        }

        explicit ComBuffer( Byte* data, size_t size )
            : size_( size ), data_( data )
        {
        }

        ComBuffer( const ComBuffer& other ) = delete;
        ComBuffer( ComBuffer&& other ) noexcept
            : size_( other.size_ ), data_( other.data_ )
        { 
            other.size_ = 0;
            other.data_ = nullptr;
        }

        ComBuffer& operator = ( const ComBuffer& other ) = delete;
        ComBuffer& operator = ( ComBuffer&& other ) noexcept
        {
            std::swap( size_, other.size_ );
            std::swap( data_, other.data_ );
            return *this;
        }

        ~ComBuffer( )
        {
            if ( data_ )
            {
                CoTaskMemFree( data_ );
            }
        }

        constexpr size_t size( ) const
        {
            return size_;
        }
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

        Byte* data( )
        {
            return data_;
        }
        const Byte* data( ) const
        {
            return data_;
        }
    };

    /// <summary>
    /// A C++ allocator that uses CoTaskMemAlloc and CoTaskMemFree
    /// </summary>
    /// <typeparam name="T">
    /// </typeparam>
    template <class T>
    class ComAllocator
    {
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        using propagate_on_container_move_assignment = std::true_type;

        constexpr ComAllocator( ) noexcept
        {
        }

        constexpr ComAllocator( const ComAllocator& ) noexcept = default;

        template <class U>
        constexpr ComAllocator( const ComAllocator<U>& ) noexcept
        { }
        constexpr ~ComAllocator( ) = default;
        constexpr ComAllocator& operator=( const ComAllocator& ) = default;

        void deallocate( T* const ptr, const size_t count )
        {
            CoTaskMemFree( ptr );
        }

        [[nodiscard]] __declspec( allocator ) T* allocate( const size_t count )
        {
            auto ptr = CoTaskMemAlloc( count * sizeof( T ) );
            if ( !ptr )
            {
                ThrowOSError( ERROR_OUTOFMEMORY );
            }
            return reinterpret_cast<T*>( ptr );
        }


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
        /// Initializes the COM library for use by the calling thread, sets the thread's 
        /// concurrency model, and creates a new apartment for the thread if one is required.
        /// </summary>
        /// <param name="apartmentModel">
        /// The thread's concurrency model
        /// </param>
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
        inline void Uninitialize( )
        {
            CoUninitialize( );
        }

        /// <summary>
        /// Registers security and sets the default security values for the process.
        /// </summary>
        /// <param name="securityDescriptor">
        /// 
        /// </param>
        /// <param name="authenticationServicesSize">
        /// </param>
        /// <param name="authenticationServices">
        /// </param>
        /// <param name="authenticationLevel">
        /// </param>
        /// <param name="impersonationLevel">
        /// </param>
        /// <param name="authenticationList">
        /// </param>
        /// <param name="authenticationCapabilities">
        /// </param>
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
        /// Retrieves the names of supported known interfaces.
        /// </summary>
        /// <param name="unknown">
        /// The pointer to the IUnknown interface that will be interrogated.
        /// </param>
        /// <returns>
        /// The names of the interfaces the function was able to identify.
        /// </returns>
        HCC_EXPORT std::vector<WideString> GetSupportedKnownInterfaces(IUnknown* unknown);
        
        inline void PrintSupportedKnownInterfaces( IUnknown* unknown )
        {
            auto comInterfaces = GetSupportedKnownInterfaces( unknown );
            for ( auto& comInterface : comInterfaces )
            {
                _putws( comInterface.c_str() );
            }
        }

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
