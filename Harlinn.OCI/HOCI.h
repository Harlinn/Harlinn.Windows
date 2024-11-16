#pragma once
#ifndef __HOCI_H__
#define __HOCI_H__
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

#include <HOCIFunctions.h>

//#define HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF 1

#pragma pack(push,8)

namespace Harlinn::OCI
{
    /// <summary>
    /// Base class for OCI handle wrappers 
    /// </summary>
    class HandleBase 
    {
        void* handle_;
        OCI::HandleType handleType_;
        bool ownsHandle_;
    protected:
        /// <summary>
        /// Default constructor.
        /// </summary>
        constexpr HandleBase( ) noexcept
            : handleType_( OCI::HandleType::Unknown ), handle_( nullptr ), ownsHandle_( false )
        {
        }

        /// <summary>
        /// Constructs a new HandleBase object
        /// </summary>
        /// <param name="handleType">The type of the handle wrapped by this object.</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        constexpr HandleBase( OCI::HandleType handleType, void* handle, bool ownsHandle ) noexcept
            : handleType_( handleType ), handle_( handle ), ownsHandle_( ownsHandle )
        {
        }

        HandleBase( const HandleBase& other ) = delete;
        /// <summary>
        /// Move constructor
        /// </summary>
        /// <param name="other">existing object</param>
        constexpr HandleBase( HandleBase&& other ) noexcept
            : handle_( other.handle_ ), handleType_( other.handleType_ ), ownsHandle_( other.ownsHandle_ )
        {
            other.handle_ = nullptr; 
            other.ownsHandle_ = false;
        }
        /// <summary>
        /// Destructor
        /// </summary>
        virtual ~HandleBase( )
        {
            DestroyHandle( );
        }


        /// <summary>
        /// Assigns the handle value and ownership to this object. 
        /// <p>
        /// <em>Warning:</em> Careless use of this function will cause resource leakage.
        /// </p>
        /// </summary>
        /// <param name="newHandleValue">The new handle value</param>
        /// <param name="ownsHandle">Set to true if this object will take owneship of the new handle value</param>
        constexpr void SetHandle( void* newHandleValue, bool ownsHandle ) noexcept
        {
            handle_ = newHandleValue;
            ownsHandle_ = ownsHandle;
        }
        /// <summary>
        /// Returns true if this object is the owner of the handle value
        /// </summary>
        /// <returns>true if this object is the owner of the handle value</returns>
        constexpr bool OwnsHandle( ) const noexcept
        {
            return ownsHandle_;
        }

        /// <summary>
        /// Calls OCIHandleFree to release the handle
        /// </summary>
        /// <param name="handle">The handle to release</param>
        /// <param name="handleType">The type of the handle to release</param>
        /// <returns></returns>
        HO_EXPORT static void HandleFree( void* handle, OCI::HandleType handleType ) noexcept;

        /// <summary>
        /// If this object is the owner of a handle this function
        /// rescinds that ownership, and returns the handle value 
        /// without closing the handle
        /// </summary>
        /// <returns>The value of the handle</returns>
        [[nodiscard]] void* DetachHandle( )
        {
            if ( handle_ && ownsHandle_ )
            {
                auto tmp = handle_;
                handle_ = nullptr;
                ownsHandle_ = false;
                return tmp;
            }
            else
            {
                return nullptr;
            }
        }

        /// <summary>
        /// Destroys the handle if it is owned by this object
        /// </summary>
        void DestroyHandle( )
        {
            auto handle = DetachHandle( );
            if ( handle )
            {
#ifdef HOCI_DEBUG_TRACK_HANDLES_WITH_PRINTF
                printf( "Calling HandleFree for 0x%p\n", handle );
#endif
                HandleFree( handle, handleType_ );
            }
        }
        
        HandleBase& operator = ( const HandleBase& other ) = delete;

        constexpr HandleBase& operator = ( HandleBase&& other ) noexcept
        {
            if ( this != &other )
            {
                handle_ = other.handle_; 
                handleType_ = other.handleType_; 
                ownsHandle_ = other.ownsHandle_;
                other.handle_ = nullptr;
                other.ownsHandle_ = false;
            }
            return *this;
        }
    
        constexpr void swap( HandleBase& other ) noexcept
        {
            std::swap( handle_, other.handle_ );
            std::swap( handleType_,other.handleType_);
            std::swap( ownsHandle_,other.ownsHandle_ );
        }

    
        /// <summary>
        /// Template function used to implement move assignement 
        /// in derived classes.
        /// </summary>
        /// <typeparam name="Derived">The type of the derived class</typeparam>
        /// <param name="derived"></param>
        /// <returns></returns>
        template<typename Derived>
        constexpr void Take( Derived&& derived ) noexcept
        {
            std::swap( handle_, derived.handle_);
            std::swap( handleType_, derived.handleType_ );
            std::swap( ownsHandle_, derived.ownsHandle_ );
        }
    public:
        /// <summary>
        /// Provides access to the value of the handle object
        /// </summary>
        /// <returns>The OCI handle</returns>
        constexpr void* Handle( ) const noexcept
        {
            return handle_;
        }

        /// <summary>
        /// Test if the handle value is assigned
        /// </summary>
        /// <returns>returns true if the value of the handle object is not equal to nullptr</returns>
        constexpr explicit operator bool( ) const noexcept
        {
            return handle_ != nullptr;
        }

        /// <summary>
        /// Test if the handle value is assigned
        /// </summary>
        /// <returns>returns true if the value of the handle object is not equal to nullptr</returns>
        constexpr bool IsValid( ) const noexcept
        {
            return handle_ != nullptr;
        }

        /// <summary>
        /// Returns a value identifying the type of the wrapped handle object
        /// </summary>
        /// <returns></returns>
        constexpr OCI::HandleType HandleType( ) const noexcept
        {
            return handleType_;
        }

        /// <summary>
        /// Provides access to the OCIError that will be used for
        /// OCI calls for this object
        /// </summary>
        /// <returns></returns>
        virtual const OCI::ErrorHandle& Error( ) const noexcept = 0;

    protected:
        /// <summary>
        /// Provides a "safe" mechanism for assigning a handle value.
        /// This functions throws if a handle value is already assigned
        /// to this object.
        /// </summary>
        /// <param name="handle">The OCI handle value</param>
        /// <param name="ownsHandle">true if this object will take ownership of the handle value.</param>
        void InitializeHandle( void* handle, bool ownsHandle )
        {
            if ( handle_ )
            {
                HCC_THROW( Data::OracleClient::OracleException, L"Handle already initialized" );
            }
            handle_ = handle;
            ownsHandle_ = ownsHandle;
        }

        /// <summary>
        /// Gets the value of an attribute from the handle 
        /// </summary>
        /// <param name="buffer">
        /// Pointer to the storage for an attribute value. In EnvironmentMode::UTF16 environment mode, 
        /// the value of a string attribute will be returned as a UTF-16 string.
        /// </param>
        /// <param name="size">
        /// The size of the attribute value, always in bytes. This can be passed as null for most 
        /// attributes because the sizes of non-string attributes are already known by the OCI library. 
        /// For text attributes, a pointer to a UInt32 must be passed in to get the length of the string.
        /// </param>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns></returns>
        HO_EXPORT Int32 GetAttribute( void* buffer, UInt32* size, Attribute attribute ) const;
        /// <summary>
        /// Sets the value of an attribute on the handle
        /// </summary>
        /// <param name="buffer">
        /// Pointer to an attribute value. The attribute value is copied into the target handle. 
        /// If the attribute value is a pointer, then only the pointer is copied, not the contents 
        /// of the pointer. String attributes must be in UTF-16 in OCI_UTF16 environment.
        /// </param>
        /// <param name="size">
        /// The size of an attribute value. This can be passed in as 0 for most attributes as the 
        /// size is already known by the OCI library. 
        /// For text attributes, a UInt32 must be passed in set to the length of the string in bytes, 
        /// regardless of encoding.
        /// </param>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <returns></returns>
        HO_EXPORT Int32 SetAttribute( void* buffer, UInt32 size, Attribute attribute ) const;

        /// <summary>
        /// Gets the value of an attribute from the handle as a DateTime
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a DateTime</returns>
        DateTime GetDateTimeAttribute( Attribute attribute ) const
        {
            OCI::Date ociDate;
            GetAttribute( &ociDate, nullptr, attribute );
            return ociDate.IsEmpty( ) == false ? ociDate.ToDateTime( ) : DateTime( );
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as a DateTime
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as a DateTime</param>
        void SetDateTimeAttribute( Attribute attribute, const DateTime& value ) const
        {
            OCI::Date ociDate( value );
            SetAttribute( &ociDate, sizeof( OCI::Date ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as a WideString
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a WideString</returns>
        template<WideStringLike StringT = WideString>
        StringT GetStringAttribute( Attribute attribute ) const
        {
            wchar_t* buffer = nullptr;
            UInt32 bufferSize = 0;
            GetAttribute( &buffer, &bufferSize, attribute );
            StringT result( buffer, bufferSize / sizeof( wchar_t ) );
            return result;
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as a WideString
        /// For use with attributes that are not returned as UTF-16
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a WideString</returns>
        template<WideStringLike StringT = WideString>
        StringT GetStringAttributeFromByteString( Attribute attribute ) const
        {
            char* buffer = nullptr;
            UInt32 bufferSize = 0;
            GetAttribute( &buffer, &bufferSize, attribute );
            StringT result;
            ToWideString( buffer, bufferSize, result );
            return result;
        }


        /// <summary>
        /// Sets the value of an attribute on the handle as a WideString
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute</param>
        template<WideStringLike StringT>
        void SetStringAttribute( Attribute attribute, const StringT& value ) const
        {
            SetAttribute( (void*)value.c_str( ), static_cast<UInt32>( value.size( ) * sizeof( wchar_t ) ), attribute );
        }
        void SetStringAttribute( Attribute attribute, const wchar_t* value, size_t valueLength ) const
        {
            SetAttribute( ( void* )value, static_cast< UInt32 >( valueLength * sizeof( wchar_t ) ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as a bool
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a bool</returns>
        bool GetBooleanAttribute( Attribute attribute ) const
        {
            Int32 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result != 0 ? true : false;
        }

        /// <summary>
        /// Sets the value of an attribute on the handle as a bool
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as a bool</param>
        void SetBooleanAttribute( Attribute attribute, bool value ) const
        {
            Int32 v = value ? 1 : 0;
            SetAttribute( &v, sizeof( v ), attribute );
        }
        /// <summary>
        /// Gets the value of an attribute from the handle as a Byte
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a Byte</returns>
        Byte GetByteAttribute( Attribute attribute ) const
        {
            Byte result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as a Byte
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as a Byte</param>
        void SetByteAttribute( Attribute attribute, Byte value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as a SByte
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a SByte</returns>
        SByte GetSByteAttribute( Attribute attribute ) const
        {
            SByte result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }

        /// <summary>
        /// Sets the value of an attribute on the handle as a Byte
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as a SByte</param>
        void SetSByteAttribute( Attribute attribute, SByte value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }
        /// <summary>
        /// Gets the value of an attribute from the handle as an Int16
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as an Int16</returns>
        Int16 GetInt16Attribute( Attribute attribute ) const
        {
            Int16 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as an Int16
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as an Int16</param>
        void SetInt16Attribute( Attribute attribute, Int16 value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as an UInt16
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as an UInt16</returns>
        UInt16 GetUInt16Attribute( Attribute attribute ) const
        {
            UInt16 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as an UInt16
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as an UInt16</param>
        void SetUInt16Attribute( Attribute attribute, UInt16 value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }
        /// <summary>
        /// Gets the value of an attribute from the handle as an Int32
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as an Int32</returns>
        Int32 GetInt32Attribute( Attribute attribute ) const
        {
            Int32 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as an Int32
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as an Int32</param>
        void SetInt32Attribute( Attribute attribute, Int32 value ) const
        { 
            SetAttribute( &value, sizeof( value ), attribute );
        }
        /// <summary>
        /// Gets the value of an attribute from the handle as an UInt32
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as an UInt32</returns>
        UInt32 GetUInt32Attribute( Attribute attribute ) const
        {
            UInt32 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as an UInt32
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as an UInt32</param>
        void SetUInt32Attribute( Attribute attribute, UInt32 value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as an Int64
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as an Int64</returns>
        Int64 GetInt64Attribute( Attribute attribute ) const
        {
            Int64 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as an Int64
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as an Int64</param>
        void SetInt64Attribute( Attribute attribute, Int64 value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as an UInt64
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as an UInt64</returns>
        UInt64 GetUInt64Attribute( Attribute attribute ) const
        {
            UInt64 result = 0;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }
        /// <summary>
        /// Sets the value of an attribute on the handle as an UInt64
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as an UInt64</param>
        void SetUInt64Attribute( Attribute attribute, UInt64 value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as a pointer
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>Value of the attribute as a pointer</returns>
        void* GetPointerAttribute( Attribute attribute ) const
        {
            void* result = nullptr;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }

        /// <summary>
        /// Sets the value of an attribute on the handle as a pointer
        /// </summary>
        /// <param name="attribute">Identifies the attribute to assign the value to</param>
        /// <param name="value">Value of the attribute as a pointer</param>
        void SetPointerAttribute( Attribute attribute, void* value ) const
        {
            SetAttribute( &value, sizeof( value ), attribute );
        }

        /// <summary>
        /// Gets the value of an attribute from the handle as a pointer to
        /// an OCI::Number
        /// </summary>
        /// <param name="attribute">Identifies the attribute to retrieve the value for</param>
        /// <returns>A pointer to an OCI::Number</returns>
        OCI::Number* GetNumberAttribute( Attribute attribute ) const
        {
            OCI::Number* result = nullptr;
            GetAttribute( &result, nullptr, attribute );
            return result;
        }

    };


    /// <summary>
    /// The error handle is passed as a parameter to most OCI calls.
    /// </summary>
    /// <remarks>
    /// The error handle maintains information about errors that occur 
    /// during an OCI operation. When an error occurs in a call, the 
    /// error object retrieves the accosiated error message and 
    /// error code and throws an exception.
    /// </remarks>
    class ErrorHandle final : public HandleBase
    {
        using Base = HandleBase;
    private:
        /// <summary>
        /// Pointer to the Environment used to create this ErrorHandle object
        /// </summary>
        const Environment* environment_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Error;

        /// <summary>
        /// Default constructor creates an empty invalid ErrorHandle
        /// that can be used as the target for a move assignment
        /// </summary>
        constexpr ErrorHandle( ) noexcept
            : environment_( nullptr )
        {
        }


        /// <summary>
        /// Constructs a new ErrorHandle object
        /// </summary>
        /// <param name="environment">A reference to the environment used to create the error handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        constexpr ErrorHandle( const OCI::Environment& environment, void* ocierror, bool ownsHandle ) noexcept
            : Base( HandleType::Error, ocierror, ownsHandle ), environment_( &environment )
        {
        }

        ErrorHandle( const ErrorHandle& other ) = delete;
        constexpr ErrorHandle( ErrorHandle&& other ) noexcept
            : Base( std::move( other ) ), environment_( other.environment_ )
        {
            other.environment_ = nullptr;
        }

        ErrorHandle& operator = ( const ErrorHandle& other ) = delete;
        /// <summary>
        /// 
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        constexpr ErrorHandle& operator = ( ErrorHandle&& other ) noexcept
        {
            if ( this != &other )
            {

                Take( std::move(other) );
                std::swap( environment_, other.environment_ );
            }
            return *this;
        }

        constexpr void swap( ErrorHandle& other ) noexcept
        {
            Base::swap( other );
            std::swap( environment_, other.environment_ );
        }

        virtual const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return *this;
        }

        HO_EXPORT Int32 CheckResult( void* errorHandle, OCI::HandleType handleType, Int32 rc ) const;
    public:

        HO_EXPORT Int32 CheckResult( Int32 rc ) const;

        const Environment& Environment( ) const
        {
            return *environment_;
        }

        
        /// <summary>
        /// Returns the offset (into the DML array) at which the error occurred.
        /// </summary>
        /// <returns>The offset at which the error occurred</returns>
        HO_EXPORT UInt32 DMLRowOffset( ) const;
    };



    /// <summary>
    /// EnvironmentOptions
    /// </summary>
    class EnvironmentOptions
    {
    public:

    };


    /// <summary>
    /// The environment handle defines a context in which all OCI functions are invoked.
    /// </summary>
    /// <remarks>
    /// Each environment handle contains a memory cache that enables fast memory access.
    /// All memory allocation under the environment handle is done from this cache. Access
    /// to the cache is serialized when multiple threads try to allocate memory under the same
    /// environment handle. When multiple threads share a single environment handle, they
    /// may block on access to the cache.
    /// </remarks>
    class Environment final : public HandleBase
    {
        using Base = HandleBase;
    private:
        static std::atomic<EnvironmentMode> defaultEnvironmentMode_;
        OCI::ErrorHandle error_;
        HO_EXPORT static void* CreateEnvironment( );
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Environment;

        constexpr Environment() noexcept
            : Base()
        { }

        Environment( const EnvironmentOptions& options )
            : Base( OCI::HandleType::Environment, CreateEnvironment( ), true ), error_( CreateError( ) )
        {
            
        }
        Environment( const Environment& other ) = delete;
        constexpr Environment( Environment&& other ) noexcept
            : Base( std::move( other ) ), error_( std::move( other.error_ ) )
        {
            
        }

        Environment& operator = ( const Environment& other ) = delete;
        constexpr Environment& operator = ( Environment&& other ) noexcept
        {
            if(this != &other)
            { 
                Take( std::move(other) );
                error_.swap( other.error_ );
            }
            return *this;
        }

    public:
        HO_EXPORT static EnvironmentMode DefaultEnvironmentMode( );
        HO_EXPORT static void SetDefaultEnvironmentMode( EnvironmentMode defaultEnvironmentMode );

        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return error_;
        }

        constexpr void swap( Environment& other ) noexcept
        {
            Base::swap( other );
            error_.swap( other.error_ );
        }

        /// <summary>
        /// Creates an ErrorHandle object.
        /// </summary>
        /// <remarks>
        /// An error handle is passed as a parameter to most OCI calls.
        /// The error handle maintains information about errors that 
        /// occur during an OCI operation.
        /// </remarks>
        /// <returns>The newly created ErrorHandle object</returns>
        HO_EXPORT OCI::ErrorHandle CreateError( ) const;
        /// <summary>
        /// Creates a Server object
        /// </summary>
        /// <remarks>
        /// A server handle identifies a connection to a database. It translates into a physical
        /// connection in a connection-oriented transport mechanism.
        /// </remarks>
        /// <returns>The newly created Server object</returns>
        HO_EXPORT OCI::Server CreateServer( ) const;
        /// <summary>
        /// Creates an Session object
        /// </summary>
        /// A user session handle defines a user's roles and privileges (also known as the 
        /// user's security domain), and the operational context in which the calls execute.
        /// <returns>The newly created Session object</returns>
        HO_EXPORT OCI::Session CreateSession( ) const;
        /// <summary>
        /// Creates a ServiceContext object
        /// </summary>
        /// <remarks>
        /// A service context handle defines attributes that determine the operational context 
        /// for OCI calls to a server.
        /// </remarks>
        /// <returns>The newly created ServiceContext object</returns>
        HO_EXPORT OCI::ServiceContext CreateServiceContext( ) const;

        /// <summary>
        /// Creates a TransactionHandle object
        /// </summary>
        /// <returns>The newly created ServiceContext object</returns>
        HO_EXPORT OCI::TransactionHandle CreateTransaction( const OCI::ServiceContext& serviceContext ) const;



        /// <summary>
        /// Creates a Subscription object
        /// </summary>
        /// <remarks>
        /// The subscription handle is used by an OCI client application that registers and
        /// subscribes to receive notifications of database events or events in the AQ namespace.
        /// </remarks>
        /// <returns>The newly created Subscription object</returns>
        HO_EXPORT OCI::Subscription CreateSubscription( ) const;
        /// <summary>
        /// Creates a Subscription object and sets the subscription name
        /// </summary>
        /// <remarks>
        /// The subscription handle is used by an OCI client application that registers and
        /// subscribes to receive notifications of database events or events in the AQ namespace.
        /// </remarks>
        /// <returns>The newly created Subscription object</returns>
        template<WideStringLike StringT>
        inline OCI::Subscription CreateSubscription( const StringT& subscriptionName ) const;

        /// <summary>
        /// The login name (DN) for LDAP connections. 
        /// </summary>
        /// <returns>login name</returns>
        template<WideStringLike StringT = WideString>
        StringT BindDN( ) const
        {
            return GetStringAttribute<StringT>( Attribute::BIND_DN );
        }
        /// <summary>
        /// Sets the login name (DN) for LDAP connections. 
        /// </summary>
        /// <param name="loginName"></param>
        template<WideStringLike StringT>
        void SetBindDN( const StringT& loginName ) const
        {
            SetStringAttribute( Attribute::BIND_DN, loginName );
        }

        /// <summary>
        /// When this attribute is set to TRUE, during OCICacheFlush() the objects 
        /// that belong to the same table are flushed together, which can considerably 
        /// improve performance. This mode should only be used when the order in which 
        /// the objects are flushed is not important. During this mode it is not 
        /// guaranteed that the order in which the objects are marked dirty is preserved.
        /// </summary>
        /// <returns></returns>
        bool CacheArrayFlush( ) const
        {
            return GetBooleanAttribute( Attribute::CACHE_ARRAYFLUSH );
        }
        void SetCacheArrayFlush( bool value ) const
        {
            SetBooleanAttribute( Attribute::CACHE_ARRAYFLUSH, value );
        }

        
        
        /// <summary>
        /// Retrieves the maximum size (high watermark) for the client-side object cache as a 
        /// percentage of the optimal size.
        /// </summary>
        /// <returns></returns>
        UInt32 CacheMaxSize( ) const
        {
            return GetUInt32Attribute( Attribute::CACHE_MAX_SIZE );
        }
        /// <summary>
        /// Sets the maximum size (high watermark) for the client-side object cache as a 
        /// percentage of the optimal size. Set the value at 110% of the optimal size 
        /// (OCI_ATTR_CACHE_OPT_SIZE). 
        ///
        /// The object cache uses the maximum and optimal values for freeing unused 
        /// memory in the object cache.
        /// </summary>
        /// <param name="value">the new value</param>
        void SetCacheMaxSize( UInt32 value ) const
        {
            SetUInt32Attribute( Attribute::CACHE_MAX_SIZE, value );
        }

        
        
        /// <summary>
        /// Retrieves the optimal size for the client-side object cache in bytes.
        /// </summary>
        /// <returns>the optimal size for the client-side object cache in bytes</returns>
        UInt32 CacheOptimalSize( ) const
        {
            return GetUInt32Attribute( Attribute::CACHE_OPT_SIZE );
        }
        /// <summary>
        /// Sets the optimal size for the client-side object cache in bytes. 
        /// The default value is 8M bytes.
        /// </summary>
        /// <param name="value">The new value</param>
        void SetCacheOptimalSize( UInt32 value ) const
        {
            SetUInt32Attribute( Attribute::CACHE_OPT_SIZE, value );
        }

        /// <summary>
        /// Retrieves the local (client-side) national character set ID.
        /// </summary>
        /// <remarks>
        /// Users can update this setting only after creating the environment handle 
        /// but before calling any other OCI functions. This restriction ensures the 
        /// consistency among data and metadata in the same environment handle. 
        /// In UTF-16 mode, an attempt to get this attribute is invalid.
        /// </remarks>
        /// <returns>The local national character set ID</returns>
        UInt16 NationalCharacterSetId( ) const
        {
            return GetUInt16Attribute( Attribute::ENV_NCHARSET_ID );
        }

        /// <summary>
        /// Encoding method is UTF-16
        /// </summary>
        /// <returns>true if the encoding method is UTF-16</returns>
        bool UsesUnicode( ) const
        {
            return GetByteAttribute( Attribute::ENV_UTF16 ) != 0 ? true : false;
        }

        /// <summary>
        /// The authentication mode.
        /// </summary>
        /// <remarks>
        /// The following are the valid values:
        /// <ul>
        ///    <li>0x0 : No authentication; anonymous bind.</li>
        ///    <li>0x1 : Simple authentication; username / password authentication.</li>
        ///    <li>0x5 : SSL connection with no authentication.</li>
        ///    <li>0x6 : SSL : only server authentication required.</li>
        ///    <li>0x7 : SSL : both server authentication and client authentication are required.</li>
        ///    <li>0x8 : Authentication method will be determined at runtime.</li>
        /// </ul>
        /// </remarks>
        UInt16 LDAPAuthenticationMode( ) const
        {
            return GetUInt16Attribute( Attribute::LDAP_AUTH );
        }

        /// <summary>
        /// If the authentication method is "simple authentication" 
        /// ( username / password authentication ), then this attribute 
        /// holds the password to use when connecting to the LDAP server.
        /// </summary>
        /// <returns></returns>
        template<WideStringLike StringT = WideString>
        StringT LDAPCredentials( ) const
        {
            return GetStringAttribute<StringT>( Attribute::LDAP_CRED );
        }

        template<WideStringLike StringT>
        void SetLDAPCredentials( const StringT& credentials ) const
        {
            SetStringAttribute( Attribute::LDAP_CRED, credentials );
        }

        /// <summary>
        /// The administrative context of the client. This is usually the root of the Oracle 
        /// RDBMS LDAP schema in the LDAP server.
        /// </summary>
        template<WideStringLike StringT = WideString>
        StringT LDAPContext( ) const
        {
            return GetStringAttribute<StringT>( Attribute::LDAP_CTX );
        }
        template<WideStringLike StringT>
        void SetLDAPContext( const StringT& context ) const
        {
            SetStringAttribute( Attribute::LDAP_CTX, context );
        }

        /// <summary>
        /// The name of the host on which the LDAP server runs.
        /// </summary>
        template<WideStringLike StringT = WideString>
        StringT LDAPHost( ) const
        {
            return GetStringAttribute<StringT>( Attribute::LDAP_HOST );
        }
        template<WideStringLike StringT>
        void SetLDAPHost( const StringT& host ) const
        {
            SetStringAttribute( Attribute::LDAP_HOST, host );
        }

        /// <summary>
        /// The port on which the LDAP server is listening.
        /// </summary>
        UInt16 LDAPPort( ) const
        {
            return GetUInt16Attribute( Attribute::LDAP_PORT );
        }
        /// <summary>
        /// The port on which the LDAP server is listening.
        /// </summary>
        void SetLDAPPort( UInt16 port ) const
        {
            SetUInt16Attribute( Attribute::LDAP_PORT, port );
        }

        /// <summary>
        /// Returns true if the environment was initialized in object mode
        /// </summary>
        bool ObjectsEnabled( ) const
        {
            return GetBooleanAttribute( Attribute::OBJECT );
        }

        
        
        /// <summary>
        /// Retrieves the value of OCI_PIN_DEFAULT for the application 
        /// associated with the environment handle.
        ///
        /// For example, if DefaultPinOption is set to PinOption::Recent, then if 
        /// OCIObjectPin( ) is called with the pin_option parameter set to 
        /// PinOption::Default, then the object is pinned in PinOption::Recent mode.
        /// </summary>
        PinOption DefaultPinOption( ) const
        {
            return static_cast<PinOption>( GetInt32Attribute( Attribute::PINOPTION ) );
        }
        /// <summary>
        /// Sets the value of OCI_PIN_DEFAULT for the application 
        /// associated with the environment handle.
        ///
        /// For example, if DefaultPinOption is set to PinOption::Recent, then if 
        /// OCIObjectPin( ) is called with the pin_option parameter set to 
        /// PinOption::Default, then the object is pinned in PinOption::Recent mode.
        /// </summary>
        void SetDefaultPinOption( PinOption pinOption ) const
        {
            SetInt32Attribute( Attribute::PINOPTION, static_cast<Int32>( pinOption ) );
        }

        /// <summary>
        /// Retrieves the value of Duration::Default for allocation 
        /// durations for the application associated with the environment handle.
        /// </summary>
        UInt16 DefaultAllocationDuration( ) const
        {
            return GetUInt16Attribute( Attribute::ALLOC_DURATION );
        }

        /// <summary>
        /// Sets the value of Duration::Default for allocation 
        /// durations for the application associated with the environment handle.
        /// </summary>
        /// <param name="durationValue"></param>
        void SetDefaultAllocationDuration( UInt16 durationValue ) const
        {
            SetUInt16Attribute( Attribute::ALLOC_DURATION, durationValue );
        }
        void SetDefaultAllocationDuration( Duration durationValue ) const
        {
            SetDefaultAllocationDuration( static_cast<UInt16>( durationValue ) );
        }

        /// <summary>
        /// Retrieves the value of Duration::Default for pin durations for the 
        /// application associated with the environment handle
        /// </summary>
        UInt16 DefaultPinDuration( ) const
        {
            return GetUInt16Attribute( Attribute::PIN_DURATION );
        }
        /// <summary>
        /// Sets the value of Duration::Default for pin durations for the 
        /// application associated with the environment handle
        /// </summary>
        /// <param name="durationValue">The new value</param>
        void SetDefaultPinDuration( UInt16 durationValue ) const
        {
            SetUInt16Attribute( Attribute::PIN_DURATION, durationValue );
        }
        /// <summary>
        /// Sets the value of Duration::Default for pin durations for the 
        /// application associated with the environment handle
        /// </summary>
        /// <param name="durationValue">The new value</param>
        void SetDefaultPinDuration( Duration durationValue ) const
        {
            SetDefaultPinDuration( static_cast<UInt16>( durationValue ) );
        }

        /// <summary>
        /// Retrieves the current size of the memory allocated from the environment handle. 
        /// This may help you track where memory is being used most in an application.
        /// </summary>
        UInt32 HeapAllocated( ) const
        {
            return GetUInt32Attribute( Attribute::HEAPALLOC );
        }

        /// <summary>
        /// If true, newly created objects have non-NULL attributes
        /// </summary>
        bool AttributesOnNewObjectsIsNotNull( ) const
        {
            return GetBooleanAttribute( Attribute::OBJECT_NEWNOTNULL );
        }
        /// <summary>
        /// If true, newly created objects have non-NULL attributes
        /// </summary>
        /// <param name="value">The new value</param>
        void SetAttributesOnNewObjectsIsNotNull( bool value ) const
        {
            SetBooleanAttribute( Attribute::OBJECT_NEWNOTNULL, value );
        }

        /// <summary>
        /// Returns the size of the memory currently allocated from the shared pool. 
        /// This attribute works on any environment handle but the process must be 
        /// initialized in shared mode to return a meaningful value. 
        /// </summary>
        UInt32 SharedHeapAllocated( ) const
        {
            return GetUInt32Attribute( Attribute::SHARED_HEAPALLOC );
        }

        /// <summary>
        /// If the authentication method is SSL authentication, this attribute 
        /// contains the location of the client wallet.
        /// </summary>
        template<WideStringLike StringT = WideString>
        StringT SSLWalletLocation( ) const
        {
            return GetStringAttribute<StringT>( Attribute::WALL_LOC );
        }
        /// <summary>
        /// If the authentication method is SSL authentication, this attribute 
        /// contains the location of the client wallet.
        /// </summary>
        template<WideStringLike StringT>
        void SetSSLWalletLocation( const StringT& location ) const
        {
            SetStringAttribute( Attribute::WALL_LOC, location );
        }
    };



    


    /// <summary>
    /// A server handle represents a connection between the
    /// client application and the Oracle database server
    /// </summary>
    class Server final : public HandleBase
    {
        using Base = HandleBase;
    public:
        
    private:
        const Environment* environment_;
        OCI::ErrorHandle error_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Server;

        constexpr Server( ) noexcept
            : Base( ), environment_(nullptr)
        {
        }


        /// <summary>
        /// Constructs a new Server object
        /// </summary>
        /// <param name="environment">A reference to the environment used to create the server handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        Server( const OCI::Environment& environment, void* ociserver, bool ownsHandle )
            : Base( HandleType::Server, ociserver, ownsHandle ), environment_( &environment ), error_( environment.CreateError())
        {
        }
        Server( const Server& other ) = delete;
        constexpr Server( Server&& other ) noexcept
            : Base(std::move( other )), environment_( other.environment_ ), error_(std::move( other.error_ ))
        {
            other.environment_ = nullptr;
        }

        Server& operator = ( const Server& other ) = delete;
        Server& operator = ( Server&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move(other) );
                std::swap( environment_, other.environment_ );
                std::swap( error_, other.error_ );
            }
            return *this;
        }


        constexpr void swap( Server& other ) noexcept
        {
            Base::swap( other );
            std::swap( environment_, other.environment_ );
            std::swap( error_, other.error_ );
        }

        const OCI::Environment& Environment( ) const
        {
            return *environment_;
        }

        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return error_;
        }

        HO_EXPORT void Attach( const wchar_t* databaseLink, size_t databaseLinkLength, ServerAttachMode attachMode = ServerAttachMode::Default ) const;

        template<WideStringLike StringT>
        void Attach( const StringT& databaseLink, ServerAttachMode attachMode = ServerAttachMode::Default ) const
        {
            Attach( databaseLink.c_str( ), databaseLink.size( ), attachMode );
        }
        
        HO_EXPORT void Detach( ) const;

        HO_EXPORT ServiceContext CreateServiceContext( ) const;
        HO_EXPORT ServiceContext CreateServiceContext( const wchar_t* username, size_t usernameLength, const wchar_t* password, size_t passwordLength, const wchar_t* databaseLink, size_t databaseLinkLength, ServerAttachMode attachMode = ServerAttachMode::Default ) const;

        template<WideStringLike StringT1, WideStringLike StringT2, WideStringLike StringT3>
        ServiceContext CreateServiceContext( const StringT1& username, const StringT2& password, const StringT3& databaseLink, ServerAttachMode attachMode = ServerAttachMode::Default ) const
        {
            return CreateServiceContext( username.c_str(), username.size(), password.c_str(), password.size(), databaseLink.c_str(), databaseLink.size(), attachMode );
        }

        
        /// <summary>
        /// The external name is the user-friendly global name stored in sys.props$.value$, 
        /// where name = 'GLOBAL_DB_NAME'. It is not guaranteed to be unique unless all 
        /// databases register their names with a network directory service.
        ///
        /// Database names can be exchanged with the server in case of distributed transaction 
        /// coordination.Server database names can only be accessed if the database is open at 
        /// the time the OCISessionBegin( ) call is issued.
        /// </summary>
        template<WideStringLike StringT = WideString>
        StringT ExternalName( ) const
        {
            return GetStringAttribute<StringT>( Attribute::EXTERNAL_NAME );
        }
        template<WideStringLike StringT>
        void SetExternalName( const StringT& externalName ) const
        {
            SetStringAttribute( Attribute::EXTERNAL_NAME, externalName );
        }

        /// <summary>
        /// 
        /// </summary>
        /// <remarks>
        /// Application failover callbacks can be used in the event of the failure 
        /// of one database instance, and failover to another instance. Because of 
        /// the delay which can occur during failover, the application developer 
        /// may want to inform the user that failover is in progress, and request 
        /// that the user stand by. Additionally, the session on the initial instance 
        /// may have received some ALTER SESSION commands. These will not be automatically 
        /// replayed on the second instance. Consequently, the developer may wish to replay 
        /// these ALTER SESSION commands on the second instance.
        ///
        /// To address the problems described above, the application developer can register 
        /// a failover callback function. In the event of failover, the callback 
        /// function is invoked several times during the course of reestablishing the 
        /// user's session.
        ///
        /// The first call to the callback function occurs when Oracle first detects 
        /// an instance connection loss.This callback is intended to allow the 
        /// application to inform the user of an upcoming delay.If failover is successful, 
        /// a second call to the callback function occurs when the connection is reestablished 
        /// and usable.At this time the client may wish to replay ALTER SESSION commands and 
        /// inform the user that failover has happened.If failover is unsuccessful, then the 
        /// callback is called to inform the application that failover will not take place.
        /// Additionally, the callback is called each time a user handle besides the primary 
        /// handle is reauthenticated on the new connection.Since each user handle represents a 
        /// server - side session, the client may wish to replay ALTER SESSION commands for 
        /// that session.
        /// </remarks>
        /// <returns></returns>
        OCI::FailoverCallback* FailoverCallback( ) const
        {
            return static_cast<OCI::FailoverCallback*>( GetPointerAttribute( Attribute::FOCBK ) );
        }
        void SetFailoverCallback( OCI::FailoverCallback* failoverCallback ) const
        {
            SetPointerAttribute( Attribute::FOCBK, failoverCallback );
        }

        /// Sets the client database name that will be recorded when performing global transactions. 
        /// The name can be used by the DBA to track transactions that may be pending in a prepared 
        /// state due to failures.
        template<WideStringLike StringT = WideString>
        StringT InternalName( ) const
        {
            return GetStringAttribute<StringT>( Attribute::INTERNAL_NAME );
        }
        template<WideStringLike StringT>
        void SetInternalName( const StringT& internalName ) const
        {
            SetStringAttribute( Attribute::INTERNAL_NAME, internalName );
        }

        /// Allows you to determine whether an application has switched to Oracle release 7 
        /// mode (for example, through an OCISvcCtxToLda() call). A nonzero (TRUE) 
        /// return value indicates that the application is currently running in Oracle 
        /// release 8 mode, a zero (FALSE) return value indicates that the application 
        /// is currently running in Oracle release 7 mode.
        bool Oracle8Mode( ) const
        {
            return GetByteAttribute( Attribute::IN_V8_MODE ) != 0 ? true : false;
        }

        /// This attribute determines the blocking mode.
        /// When read, the attribute value returns TRUE if the server context 
        /// is in nonblocking mode.When set, it toggles the nonblocking mode attribute.
        bool NonBlocingMode( ) const
        {
            return GetByteAttribute( Attribute::NONBLOCKING_MODE ) != 0 ? true : false;
        }
        void SetNonBlocingMode( bool nonBlocingMode ) const
        {
            SetByteAttribute( Attribute::NONBLOCKING_MODE, nonBlocingMode ? 1 : 0 );
        }

        /// <summary>
        /// An alpha-numeric string not exceeding 30 characters specifying the server group
        /// </summary>
        template<WideStringLike StringT = WideString>
        StringT ServerGroup( ) const
        {
            return GetStringAttribute<StringT>( Attribute::SERVER_GROUP );
        }
        /// <summary>
        /// An alpha-numeric string not exceeding 30 characters specifying the server group
        /// </summary>
        template<WideStringLike StringT>
        void SetServerGroup( const StringT& serverGroup ) const
        {
            SetStringAttribute( Attribute::SERVER_GROUP, serverGroup );
        }

        /// <summary>
        /// Returns the current status of the server handle. Values are:
        ///    1 - There is an active connection to the server. It means that 
        ///        the last call on the connection went through.There is no 
        ///        guarantee that the next call will go through.
        ///    0 - There is no connection to the server.
        /// </summary>
        UInt32 ServerStatus( ) const
        {
            return GetUInt32Attribute( Attribute::SERVER_STATUS );
        }
        /// <summary>
        /// Returns true if there is an active connection to the server.
        /// </summary>
        /// <returns>true if there is an active connection to the server.</returns>
        bool Connected( ) const
        {
            return ServerStatus( ) == 1; //OCI_SERVER_NORMAL 0x1
        }

        template<WideStringLike StringT = WideString>
        StringT DbDomain( ) const
        {
            return GetStringAttribute<StringT>( Attribute::DBDOMAIN );
        }
        template<WideStringLike StringT = WideString>
        StringT DbName( ) const
        {
            return GetStringAttributeFromByteString<StringT>( Attribute::DBNAME );
        }
        template<WideStringLike StringT = WideString>
        StringT InstanceName( ) const
        {
            return GetStringAttribute<StringT>( Attribute::INSTNAME );
        }

        DateTime InstanceStartTime( ) const
        {
            DateTime result;
            OCIDateTime* startTime = (OCIDateTime*)GetPointerAttribute( Attribute::INSTSTARTTIME );
            auto& error = Error( );
            OCI::DateTimeGetDateTime( *this, error, startTime, result );
            return result;
        }

        template<WideStringLike StringT = WideString>
        StringT ServiceName( ) const
        {
            return GetStringAttribute<StringT>( Attribute::SERVICENAME );
        }



    };

    /// <summary>
    /// Session
    /// </summary>
    class Session final : public HandleBase
    {
        using Base = HandleBase;
    public:

    private:
        const Environment* environment_;
        ErrorHandle error_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Session;

        constexpr Session( ) noexcept
            : environment_( nullptr )
        {
        }

        /// <summary>
        /// Constructs a new Session object
        /// </summary>
        /// <param name="environment">A reference to the environment used to create the session handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        Session( const OCI::Environment& environment, void* ocisession, bool ownsHandle )
            : Base( HandleType::Session, ocisession, ownsHandle ), environment_( &environment ), error_( environment.CreateError() )
        {
        }

        constexpr Session( const Session& other ) = delete;
        constexpr Session( Session&& other ) noexcept
            : Base(std::move( other )), environment_(other.environment_ ), error_(std::move( other.error_ ))
        {
            other.environment_ = nullptr;
        }

        constexpr Session& operator = ( const Session& other ) = delete;
        constexpr Session& operator = ( Session&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
                std::swap(environment_,other.environment_); 
                error_.swap( other.error_ );
            }
            return *this;
        }

        constexpr void swap( Session& other ) noexcept
        {
            Base::swap( other );
            std::swap( environment_, other.environment_ );
            error_.swap( other.error_ );
        }


        const Environment& Environment( ) const
        {
            return *environment_;
        }
        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return error_;
        }
        
    public:
        template<WideStringLike StringT = WideString>
        StringT UserName( ) const
        {
            return GetStringAttribute<StringT>( Attribute::USERNAME );
        }
        template<WideStringLike StringT>
        void SetUserName( const StringT& userName ) const
        {
            SetStringAttribute( Attribute::USERNAME, userName );
        }

        void SetUserName( const wchar_t* userName, size_t userNameLength ) const
        {
            SetStringAttribute( Attribute::USERNAME, userName, userNameLength );
        }

        template<WideStringLike StringT>
        void SetPassword( const StringT& password ) const
        {
            SetStringAttribute( Attribute::PASSWORD, password );
        }
        void SetPassword( const wchar_t* password, size_t passwordLength ) const
        {
            SetStringAttribute( Attribute::PASSWORD, password, passwordLength );
        }

    };


    class Transaction
    {
        const OCI::ServiceContext* serviceContext_;
    public:
        Transaction()
            : serviceContext_(nullptr)
        { }

        explicit Transaction( const OCI::ServiceContext* serviceContext )
            : serviceContext_( serviceContext )
        { }

        Transaction( const Transaction& other ) = delete;
        Transaction( Transaction&& other ) noexcept
            : serviceContext_( other.serviceContext_ )
        {
            other.serviceContext_ = nullptr;
        }

        ~Transaction( )
        {
            Rollback( );
        }

        Transaction& operator = ( const Transaction& other ) = delete;
        Transaction& operator = ( Transaction&& other ) noexcept
        {
            std::swap( serviceContext_, other.serviceContext_ );
            return *this;
        }

        void Commit( );
        void Rollback( );
        
    };


    /// <summary>
    /// ServiceContext - A service context handle defines attributes 
    /// that determine the operational context for OCI calls to a server.
    /// </summary>
    class ServiceContext final : public HandleBase
    {
        using Base = HandleBase;
        friend class Ref;
        friend class Object;
    private:
        const OCI::Environment* environment_;
        const OCI::Server* server_;
        OCI::Session session_;
        OCI::ErrorHandle error_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::ServiceContext;

        constexpr ServiceContext() noexcept
            : environment_(nullptr), server_( nullptr ) 
        { 
        }

        /// <summary>
        /// Constructs a new ServiceContext object
        /// </summary>
        /// <param name="environment">A reference to the environment used to create the service context handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        ServiceContext( const OCI::Environment& environment, void* ocisvcctx, bool ownsHandle )
            : Base( HandleType::ServiceContext, ocisvcctx, ownsHandle ), 
              environment_( &environment ), 
              server_( nullptr ),
              error_( environment.CreateError() )
        {

        }

        ServiceContext( const ServiceContext& other ) = delete;
        constexpr ServiceContext( ServiceContext&& other ) noexcept
            : Base(std::move( other )), 
              environment_( other.environment_ ), 
              session_( std::move( other.session_ ) ),
              server_( other.server_  ), 
              error_( std::move( other.error_ ) )
        {
            other.environment_ = nullptr;
            other.server_ = nullptr;
        }

        ServiceContext& operator = ( const ServiceContext& other ) = delete;
        constexpr ServiceContext& operator = ( ServiceContext&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
                std::swap(environment_,other.environment_);
                session_.swap(other.session_);
                std::swap( server_, other.server_);
                error_.swap( other.error_ );
            }
            return *this;
        }

        constexpr void swap( ServiceContext& other ) noexcept
        {
            Base::swap( other );
            std::swap( environment_, other.environment_ );
            session_.swap( other.session_ );
            std::swap( server_, other.server_ );
            error_.swap( other.error_ );
        }

        /// <summary>
        /// Retrieves a reference to the Environment of the ServiceContext
        /// </summary>
        /// <returns>A reference to the Environment of the ServiceContext</returns>
        constexpr const OCI::Environment& Environment( ) const noexcept
        {
            return *environment_;
        }

        /// <summary>
        /// Retrieves a reference to the Session of the ServiceContext
        /// </summary>
        /// <returns></returns>
        constexpr const OCI::Session& Session( ) const noexcept
        {
            return session_;
        }

        /// <summary>
        /// Sets the session attribute of the ServiceContext
        /// </summary>
        /// <param name="authentication">The Session object for the OCISession</param>
        /// <returns></returns>
        HO_EXPORT bool SetSession( OCI::Session&& session );

        /// <summary>
        /// Retrieves a reference to the ErrorHandle object of the ServiceContext
        /// </summary>
        /// <returns></returns>
        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return error_;
        }
    
    public:
        /// <summary>
        /// Sets the beginning of a transaction
        /// </summary>
        /// <param name="flags">
        /// Specifies whether a new transaction is being started or 
        /// an existing transaction is being resumed. Also specifies 
        /// serializability or read-only status. More than a single value 
        /// can be specified. By default, a read/write transaction is started.
        /// <see cref="TransactionStartFlags"/> for possible values.
        /// </param>
        /// <param name="timeoutInSeconds">
        /// The time, in seconds, to wait for a transaction to become available for resumption
        /// when <see cref="TransactionStartFlags::Resume"/> is specified. 
        /// When <see cref="TransactionStartFlags::New"/> is specified, the timeout parameter 
        /// indicates the number of seconds the transaction can be inactive before it is
        /// automatically terminated by the system. A transaction is inactive between the time it is
        /// detached (with OCITransDetach()) and the time it is resumed with OCITransStart().
        /// </param>
        void TransactionStart( TransactionStartFlags flags = TransactionStartFlags::None, UInt16 timeoutInSeconds = 0 ) const
        {
            auto& error = Error( );
            OCI::TransactionStart( *this, error, flags, timeoutInSeconds );
        }
        void TransactionStart( TransactionStartFlags flags, const TimeSpan& timeout ) const
        {
            auto& error = Error( );
            OCI::TransactionStart( *this, error, flags, timeout );
        }

        [[nodiscard]] Transaction BeginTransaction( TransactionStartFlags flags = TransactionStartFlags::None, UInt16 timeoutInSeconds = 0 ) const
        {
            // By default we use the implicit transaction
            if ( flags != TransactionStartFlags::None || timeoutInSeconds != 0 )
            {
                TransactionStart( flags, timeoutInSeconds );
            }
            return Transaction( this );
        }

        void TransactionRollback( ) const
        {
            auto& error = Error( );
            OCI::TransactionRollback( *this, error );
        }

        void TransactionCommit( TransactionEndFlags flags = TransactionEndFlags::None ) const
        {
            auto& error = Error( );
            OCI::TransactionCommit( *this, error, flags );
        }
        void TransactionDetach( ) const
        {
            auto& error = Error( );
            OCI::TransactionDetach( *this, error );
        }
        void TransactionForget( ) const
        {
            auto& error = Error( );
            OCI::TransactionForget( *this, error );
        }
        void TransactionPrepare( ) const
        {
            auto& error = Error( );
            OCI::TransactionPrepare( *this, error );
        }

    private:
        HO_EXPORT void ObjectNew( TypeCode typecode, Duration duration, bool value, void **instance ) const;
        [[nodiscard]] void* ObjectNew( TypeCode typecode, Duration duration, bool value ) const
        {
            void* result = nullptr;
            ObjectNew( typecode, duration, value, &result );
            return result;
        }

        HO_EXPORT void TypeByName( const WideString& schemaName,
                                        const WideString& typeName,
                                        const WideString& versionName,
                                        OCI::Duration pinDuration,
                                        OCI::TypeGetOpt typeGetOption,
                                        OCIType **tdo ) const;
    public:
        std::unique_ptr<OCI::Type> TypeByName( const WideString& schemaName,
                                        const WideString& typeName,
                                        const WideString& versionName,
                                        OCI::Duration pinDuration,
                                        OCI::TypeGetOpt typeGetOption ) const
        {
            OCIType* ociType = nullptr;
            TypeByName( schemaName, typeName, versionName, pinDuration, typeGetOption, &ociType );
            return std::make_unique< OCI::Type >( *this, ociType );
        }

        std::unique_ptr<OCI::Type> TypeByName( const WideString& schemaName, const WideString& typeName, OCI::Duration pinDuration = OCI::Duration::Session, OCI::TypeGetOpt typeGetOption = OCI::TypeGetOpt::Header ) const;
    private:
        HO_EXPORT void TypeByFullName( const WideString& fullName,
                                                const WideString& versionName,
                                                OCI::Duration pinDuration,
                                                OCI::TypeGetOpt typeGetOption,
                                                OCIType ** ociType ) const;
    public:
        std::unique_ptr<OCI::Type> TypeByFullName( const WideString& fullName, const WideString& versionName, OCI::Duration pinDuration, OCI::TypeGetOpt typeGetOption ) const
        {
            OCIType* ociType = nullptr;
            TypeByFullName( fullName, versionName, pinDuration, typeGetOption, &ociType );
            return std::make_unique< OCI::Type >( *this, ociType );
        }
        std::unique_ptr<OCI::Type> TypeByFullName( const WideString& fullName, OCI::Duration pinDuration = OCI::Duration::Session, OCI::TypeGetOpt typeGetOption = OCI::TypeGetOpt::Header ) const;


        HO_EXPORT bool Exists( const WideString& objectName, OCI::ParameterType parameterType = OCI::ParameterType::Unknown ) const;

        bool Exists( const wchar_t* objectName, OCI::ParameterType parameterType = OCI::ParameterType::Unknown ) const
        {
            return Exists( WideString(objectName), parameterType );
        }

        HO_EXPORT OCI::Describe Describe( const WideString& objectName, OCI::ParameterType parameterType = OCI::ParameterType::Unknown, bool showInvisibleColumns = false ) const;
        HO_EXPORT OCI::Describe Describe( const wchar_t* objectName, OCI::ParameterType parameterType = OCI::ParameterType::Unknown, bool showInvisibleColumns = false ) const;

        HO_EXPORT OCI::Describe Describe( const OCI::Type& type ) const;
        HO_EXPORT OCI::Describe Describe( const OCI::Ref& typeRef ) const;
        HO_EXPORT OCI::Describe Describe( OCIType* type ) const;
        HO_EXPORT OCI::Describe Describe( OCIRef* typeRef ) const;

        
        HO_EXPORT const OCI::Session& CreateSession( );
        HO_EXPORT const OCI::Session& CreateSession( const wchar_t* username, size_t usernameLength, const wchar_t* password, size_t passwordLength );

        template<WideStringLike StringT1, WideStringLike StringT2>
        const OCI::Session& CreateSession( const StringT1& username, const StringT2& password )
        {
            return CreateSession( username.c_str( ), username.size( ), password.c_str( ), password.size( ) );
        }


        const OCI::Server* Server( ) const
        {
            return server_;
        }

        HO_EXPORT bool SetServer( const OCI::Server* server );
        bool SetServer( const OCI::Server& server )
        {
            return SetServer( &server );
        }


        HO_EXPORT void SessionBegin( CredidentialType credidentialType = CredidentialType::DatabaseServer, AuthenticationMode authenticationMode = AuthenticationMode::Default ) const;
        HO_EXPORT void SessionEnd( ) const;


        HO_EXPORT OCI::Statement CreateStatement( const wchar_t* sql, size_t sqlLength ) const;

        template<WideStringLike StringT>
        OCI::Statement CreateStatement( const StringT& sql ) const
        {
            return CreateStatement( sql.c_str(), sql.size() );
        }

        inline OCI::Statement CreateStatement( const wchar_t* sql ) const;


        template<WideStringLike StringT, typename ...BindableTypes>
            requires (sizeof...( BindableTypes ) > 0)
        OCI::Statement CreateStatement( const StringT& sql, BindableTypes&& ...bindableArgs ) const;

        HO_EXPORT OCI::Describe CreateDescribe( ) const;
        HO_EXPORT std::vector<WideString> GetDbmsOutput( ) const;

        template<typename T, WideStringLike StringT>
        std::optional<T> ExecuteScalar( const StringT& sql ) const;

        template<WideStringLike StringT, typename ...BindableTypes>
        Int64 ExecuteNonQuery( const StringT& sql, BindableTypes&& ...bindableArgs ) const;

        template<typename ...BindableTypes>
        Int64 ExecuteNonQuery( const wchar_t* sql, BindableTypes&& ...bindableArgs ) const;


        WideString DbName( ) const
        {
            return server_->DbName( );
        }
    };

    inline void Transaction::Commit( )
    {
        if ( serviceContext_ )
        {
            auto tmp = serviceContext_;
            serviceContext_ = nullptr;
            tmp->TransactionCommit( );
        }
    }
    inline void Transaction::Rollback( )
    {
        if ( serviceContext_ )
        {
            auto tmp = serviceContext_;
            serviceContext_ = nullptr;
            tmp->TransactionRollback( );
        }
    }




    /// <summary>
    /// TransactionHandle
    /// </summary>
    class TransactionHandle final : public HandleBase
    {
    public:
        using Base = HandleBase;
    private:
        const OCI::ServiceContext* serviceContext_;
        const OCI::ErrorHandle* error_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Transaction;

        constexpr TransactionHandle( ) noexcept
            : serviceContext_( nullptr ), error_(nullptr)
        {
        }

        TransactionHandle( const TransactionHandle& other ) = delete;
        constexpr TransactionHandle( TransactionHandle&& other ) noexcept
            : Base( std::move( other ) ), serviceContext_( other.serviceContext_ ), error_( other.error_ )
        {
            other.serviceContext_ = nullptr;
            other.error_ = nullptr;
        }

        /// <summary>
        /// Constructs a new TransactionHandle object
        /// </summary>
        /// <param name="serviceContext">A reference to the service context used to create the transaction context handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        TransactionHandle( const OCI::ServiceContext& serviceContext, void* ocitransaction, bool ownsHandle )
            : Base( HandleType::Transaction, ocitransaction, ownsHandle ), serviceContext_( &serviceContext ), error_( &serviceContext.Error() )
        {
        }

        TransactionHandle& operator = ( const TransactionHandle& other ) = delete;
        constexpr TransactionHandle& operator = ( TransactionHandle&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
                std::swap(serviceContext_, other.serviceContext_);
                std::swap( error_, other.error_ );
            }
            return *this;
        }

        constexpr void swap( TransactionHandle& other ) noexcept
        {
            Base::swap( other );
            std::swap( serviceContext_, other.serviceContext_ );
            std::swap( error_, other.error_ );
        }


        const OCI::ServiceContext& ServiceContext( ) const
        {
            return *serviceContext_;
        }

        const OCI::Environment& Environment( ) const
        {
            const auto& context = ServiceContext( );
            return context.Environment( );
        }

        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return *error_;
        }
        
    };

    


    /// <summary>
    /// Subscription
    /// </summary>
    class Subscription final : public HandleBase
    {
    public:
        using Base = HandleBase;
        using CallbackFunc = UInt32 (__cdecl*)( void *ctx, OCISubscription *subscrhp, void *payload, UInt32 payloadSize, void *descriptor, UInt32 mode );

        static constexpr Int32 GroupForever = -1;
        static constexpr Int32 WaitForever = -1;
        static constexpr Int32 NoWait = 0;
    private:
        const OCI::Environment* environment_;
        OCI::ErrorHandle error_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Subscription;

        constexpr Subscription( ) noexcept
            : environment_( nullptr )
        {
        }


        Subscription( const Subscription& other ) = delete;
        Subscription( Subscription&& other ) noexcept
            : Base( std::move( other ) ), environment_( other.environment_ ), error_( std::move( other.error_ ) )
        {
            other.environment_ = nullptr;
        }

        /// <summary>
        /// Constructs a new Subscription object
        /// </summary>
        /// <param name="environment">A reference to the environment used to create the subscription handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        Subscription( const OCI::Environment& environment, void* ocisubscription, bool ownsHandle )
            : Base( HandleType::Subscription, ocisubscription, ownsHandle ), environment_( &environment ), error_( environment.CreateError() )
        {
        }

        Subscription& operator = ( const Subscription& other ) = delete;
        constexpr Subscription& operator = ( Subscription&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) ); 
                std::swap( environment_, other.environment_);
                error_.swap( other.error_ );
            }
            return *this;
        }

        constexpr void swap( Subscription& other ) noexcept
        {
            Base::swap( other );
            std::swap( environment_, other.environment_ );
            error_.swap( other.error_ );
        }


        const OCI::Environment& Environment( ) const
        {
            return *environment_;
        }


        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return error_;
        }


        /// <summary>
        /// The distinguished names of the Oracle database that the client is 
        /// interested in for the registration.
        /// </summary>
        OCIServerDNs* ServerDNs( ) const
        {
            return static_cast<OCIServerDNs*>( GetPointerAttribute( Attribute::SERVER_DNS ) );
        }
        void SetServerDNs( OCIServerDNs* distinguishedNames ) const
        {
            SetPointerAttribute( Attribute::SERVER_DNS, distinguishedNames );
        }

        /// <summary>
        /// Subscription callback. If the attribute OCI_ATTR_SUBSCR_RECPTPROTO is set to OCI_SUBSCR_PROTO_OCI 
        /// or is left not set, then this attribute must be set before the subscription handle can be passed 
        /// into the registration call OCISubscriptionRegister( ).
        /// </summary>
        CallbackFunc Callback( ) const
        {
            return static_cast<Subscription::CallbackFunc>( GetPointerAttribute( Attribute::SUBSCR_CALLBACK ) );
        }
        void SetCallback( CallbackFunc callbackFunction ) const
        {
            SetPointerAttribute( Attribute::SUBSCR_CALLBACK, callbackFunction );
        }

        /// <summary>
        /// Sets QOS (quality of service flags) specific to continuous query (CQ) notifications.
        /// </summary>
        void SetContinuousQueryQOSFlags( SubscriberContinousQueryQOSFlags flags ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_CQ_QOSFLAGS, static_cast<UInt32>( flags ) );
        }

        /// <summary>
        /// Context that the client wants to get passed to the user callback denoted by 
        /// OCI_ATTR_SUBSCR_CALLBACK when it gets invoked by the system.If the attribute 
        /// OCI_ATTR_SUBSCR_RECPTPROTO is set to OCI_SUBSCR_PROTO_OCI or is left not set, 
        /// then this attribute must be set before the subscription handle can be passed 
        /// into the registration call OCISubscriptionRegister( ).
        /// </summary>
        void* Context( ) const
        {
            return GetPointerAttribute( Attribute::SUBSCR_CTX );
        }
        void SetContext( void* data ) const
        {
            SetPointerAttribute( Attribute::SUBSCR_CTX, data );
        }

        /// <summary>
        /// Subscription name. All subscriptions are identified by a subscription name. 
        /// A subscription name consists of a sequence of bytes of specified length. 
        /// The length in bytes of the name must be specified as it is not assumed that 
        /// the name is zero-terminated. This is important because the name could contain 
        /// multibyte characters.
        ///
        /// All of the subscription callbacks need a subscription handle with the 
        /// OCI_ATTR_SUBSCR_NAME and OCI_ATTR_SUBSCR_NAMESPACE attributes set. If the 
        /// attributes are not set, an error is returned.The subscription name that is 
        /// set for the subscription handle must be consistent with its namespace.
        /// </summary>
        template<WideStringLike StringT = WideString>
        StringT Name( ) const
        {
            return GetStringAttribute<StringT>( Attribute::SUBSCR_NAME );
        }
        template<WideStringLike StringT>
        void SetName( const StringT& name ) const
        {
            SetStringAttribute( Attribute::SUBSCR_NAME, name );
        }

        /// <summary>
        /// Namespace in which the subscription handle is used.
        ///
        /// The subscription name that is set for the subscription handle must be consistent 
        /// with its namespace.
        /// </summary>
        SubscriberNamespace Namespace( ) const
        {
            return static_cast<SubscriberNamespace>( GetUInt32Attribute( Attribute::SUBSCR_NAMESPACE ) );
        }
        void SetNamespace( SubscriberNamespace subscriberNamespace ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_NAMESPACE, static_cast<UInt32>( subscriberNamespace ) );
        }

        /// <summary>
        /// Notification grouping class. If set to 0 (the default) all other notification 
        /// grouping attributes must be 0. It is implemented for time in the latest release 
        /// and is the only current criterion for grouping. 
        ///
        /// Can be set to SubscriberNotificationGroupingClass::Time
        /// </summary>
        SubscriberNotificationGroupingClass NotificationGroupingClass( ) const
        {
            return static_cast<SubscriberNotificationGroupingClass>( GetByteAttribute( Attribute::SUBSCR_NTFN_GROUPING_CLASS ) );
        }
        void SetNotificationGroupingClass( SubscriberNotificationGroupingClass notificationGroupingClass ) const
        {
            SetByteAttribute( Attribute::SUBSCR_NTFN_GROUPING_CLASS, static_cast<Byte>( notificationGroupingClass ) );
        }
        

        /// <summary>
        /// How many times to do the grouping. Notification repeat count. Positive integer. 
        /// Can be set to Subscription::GroupForever to send grouping notifications forever.
        /// </summary>
        Int32 NotificationGroupingRepeatCount( ) const
        {
            return GetInt32Attribute( Attribute::SUBSCR_NTFN_GROUPING_REPEAT_COUNT );
        }
        void SetNotificationGroupingRepeatCount( Int32 value ) const
        {
            SetInt32Attribute( Attribute::SUBSCR_NTFN_GROUPING_REPEAT_COUNT, value );
        }

        /// <summary>
        /// The format of the grouping notification: whether a summary of all events in 
        /// the group or just the last event in the group.
        /// </summary>
        SubscriberNotificationGroupingType NotificationGroupingType( ) const
        {
            return static_cast<SubscriberNotificationGroupingType>( GetByteAttribute( Attribute::SUBSCR_NTFN_GROUPING_TYPE ) );
        }
        void SetNotificationGroupingType( SubscriberNotificationGroupingType notificationGroupingType ) const
        {
            SetByteAttribute( Attribute::SUBSCR_NTFN_GROUPING_TYPE, static_cast<Byte>( notificationGroupingType ) );
        }

        /// <summary>
        /// Specifies the value for the grouping class. For time, this is the time-period of 
        /// grouping notifications specified in seconds, that is, the time after which grouping 
        /// notification is sent periodically until OCI_ATTR_SUBSCR_NTFN_GROUPING_REPEAT_COUNT 
        /// is exhausted.
        /// </summary>
        UInt32 NotificationGroupingValue( ) const
        {
            return GetUInt32Attribute( Attribute::SUBSCR_NTFN_GROUPING_VALUE );
        }
        void SetNotificationGroupingValue( UInt32 value ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_NTFN_GROUPING_VALUE, value );
        }

        /// <summary>
        /// Quality of service levels of the server.
        /// </summary>
        SubscriberQOSFlags QOSFlags( ) const
        {
            return static_cast<SubscriberQOSFlags>( GetUInt32Attribute( Attribute::SUBSCR_QOSFLAGS ) );
        }
        void SetQOSFlags( SubscriberQOSFlags qosFlags ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_QOSFLAGS, static_cast<UInt32>( qosFlags ) );
        }

        /// <summary>
        /// The name of the recipient of the notification
        /// </summary>
        WideString Recipient( ) const
        {
            return GetStringAttribute( Attribute::SUBSCR_RECPT );
        }
        void SetRecipient( const WideString& recipientName ) const
        {
            SetStringAttribute( Attribute::SUBSCR_RECPT, recipientName );
        }

        /// <summary>
        /// The presentation with which the client wants to receive the notification.
        /// </summary>
        SubscriberRecipientFormat RecipientFormat( ) const
        {
            return static_cast<SubscriberRecipientFormat>( GetUInt32Attribute( Attribute::SUBSCR_RECPTPRES ) );
        }
        void SetRecipientFormat( SubscriberRecipientFormat recipientFormat ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_RECPTPRES, static_cast<UInt32>( recipientFormat ) );
        }

        /// <summary>
        /// The protocol with which the client wants to receive the notification.
        /// </summary>
        SubscriberRecipientProtocol RecipientProtocol( ) const
        {
            return static_cast<SubscriberRecipientProtocol>( GetUInt32Attribute( Attribute::SUBSCR_RECPTPROTO ) );
        }
        void SetRecipientProtocol( SubscriberRecipientProtocol recipientProtocol ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_RECPTPROTO, static_cast<UInt32>( recipientProtocol ) );
        }

        /// <summary>
        /// Registration timeout interval in seconds. If 0 or not specified, then the 
        /// registration is active until the subscription is explicitly unregistered.
        /// </summary>
        UInt32 TimeoutInSeconds( ) const
        {
            return GetUInt32Attribute( Attribute::SUBSCR_TIMEOUT );
        }
        void SetTimeoutInSeconds( UInt32 timeoutInSeconds ) const
        {
            SetUInt32Attribute( Attribute::SUBSCR_TIMEOUT, timeoutInSeconds );
        }

        TimeSpan Timeout( ) const
        {
            TimeSpan result( static_cast<Int64>( TimeoutInSeconds( ) ) * TimeSpan::TicksPerSecond );
            return result;
        }
        void SetTimeout( const TimeSpan& timeout ) const
        {
            auto v = static_cast<UInt32>( static_cast<Int64>( timeout.TotalSeconds( ) ) );
            SetTimeoutInSeconds( v );
        }


        /// <summary>
        /// Used to filter notifications based on operation type.
        /// </summary>
        void SetChangeNotificationFilter( OperationCode operationCodeFlags ) const
        { 
            SetUInt32Attribute( Attribute::CHNF_OPERATIONS, static_cast<UInt32>( operationCodeFlags ) );
        }

        /// <summary>
        /// If true, the continuous query notification message includes row-level 
        /// details, such as operation type and ROWID.
        /// 
        /// The default is false
        /// </summary>
        void EnableRowLevelChangeNotifications( bool enable = true ) const
        {
            SetBooleanAttribute( Attribute::CHNF_ROWIDS, enable );
        }

        // Attributes used for continuous query notification 

        /// <summary>
        /// Name of the database
        /// </summary>
        WideString ContinuousQueryNotificationDatabaseName( ) const
        {
            return GetStringAttribute( Attribute::CHDES_DBNAME );
        }

        /// <summary>
        /// Flags describing the notification type
        /// </summary>
        UInt32 ContinuousQueryNotificationType( ) const
        {
            return GetUInt32Attribute( Attribute::CHDES_NFYTYPE );
        }

        /// <summary>
        /// Operation type: INSERT, UPDATE, DELETE, or OTHER.
        /// </summary>
        UInt32 ContinuousQueryNotificationOperationType( ) const
        {
            return GetUInt32Attribute( Attribute::CHDES_ROW_OPFLAGS );
        }

        WideString ContinuousQueryNotificationRowId( ) const
        {
            return GetStringAttribute( Attribute::CHDES_ROW_ROWID );
        }
    };

    template<WideStringLike StringT>
    inline Subscription Environment::CreateSubscription( const StringT& subscriptionName ) const
    {
        auto result = CreateSubscription( );
        result.SetName( subscriptionName );
        return result;
    }




    class DataReader;
    class ArrayDataReader;

    /// <summary>
    /// Statement, the context that identifies a SQL or PL/SQL statement and its
    /// associated attributes.
    /// </summary>
    class Statement final : public HandleBase
    {
        using Base = HandleBase;
    public:
        
    private:
        const OCI::ServiceContext* serviceContext_;
        const OCI::ErrorHandle* error_;
        OCI::Subscription changeNotification_;
        mutable std::vector<std::unique_ptr<OCI::BindBase>> binds_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Statement;

        Statement( ) noexcept
            : serviceContext_( nullptr ), error_(nullptr)
        {
        }

        Statement( const Statement& other ) = delete;
        Statement( Statement&& other ) noexcept;


        /// <summary>
        /// Constructs a new Statement object
        /// </summary>
        /// <param name="serviceContext">A reference to the service context used to create the statement handle</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        Statement( const OCI::ServiceContext& serviceContext, void* ocistmt, bool ownsHandle )
            : Base( HandleType::Statement, ocistmt, ownsHandle ), serviceContext_( &serviceContext ), error_( &serviceContext.Error() )
        { 
            
        }

        HO_EXPORT ~Statement( );

        Statement& operator = ( const Statement& other ) = delete;
        Statement& operator = ( Statement&& other ) noexcept;

        void swap( Statement& other ) noexcept
        {
            Base::swap( other );
            std::swap( serviceContext_, other.serviceContext_ );
            std::swap( error_, other.error_ );
            changeNotification_.swap( other.changeNotification_ );
            std::swap( binds_, other.binds_ );
        }


        constexpr const OCI::ServiceContext& ServiceContext( ) const noexcept
        {
            return *serviceContext_;
        }

        const OCI::Environment& Environment( ) const noexcept
        {
            const auto& serviceContext = ServiceContext( );
            return serviceContext.Environment( );
        }


        

        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return *error_;
        }

        template <typename BindType, typename ...ArgTypes>
            requires std::is_base_of_v<BindBase, BindType>
        BindType* Bind( UInt32 position, ArgTypes&&... args ) const;
        template <typename T, typename ...ArgTypes>
            requires Internal::HasTraits<T>
        typename Internal::Traits<T>::BindType* Bind( UInt32 position, ArgTypes&&... args ) const;

        template <typename BindType, typename ...ArgTypes >
            requires std::is_base_of_v<BindBase, BindType>
        BindType* Bind( const WideString& name, ArgTypes&&... args ) const;
        template <typename T, typename ...ArgTypes >
            requires Internal::HasTraits<T>
        typename Internal::Traits<T>::BindType* Bind( const WideString& name, ArgTypes&&... args ) const;

        const std::vector<std::unique_ptr<OCI::BindBase>>& Binds( ) const
        {
            return binds_;
        }

    public:

        /// <summary>
        /// Returns the type of statement associated with the handle
        /// </summary>
        OCI::StatementType StatementType( ) const
        {
            return static_cast<OCI::StatementType>( GetUInt32Attribute( Attribute::STMT_TYPE ) );
        }

        /// <summary>
        /// Returns the number of bind positions on the statement handle.
        /// </summary>
        UInt32 BindCount( ) const
        {
            return GetUInt32Attribute( Attribute::BIND_COUNT );
        }

        /// <summary>
        /// Obtains the query ID of a registered query
        /// </summary>
        UInt64 ContinuousQueryId( ) const
        {
            return GetUInt64Attribute( Attribute::CQ_QUERYID );
        }


        /// <summary>
        /// Indicates the current position in the result set.
        /// </summary>
        UInt32 CurrentPosition( ) const
        {
            return GetUInt32Attribute( Attribute::CURRENT_POSITION );
        }

        /// <summary>
        /// Returns the number of errors in the DML operation.
        /// </summary>
        UInt32 NumDMLErrors( ) const
        {
            return GetUInt32Attribute( Attribute::NUM_DML_ERRORS );
        }

        /// <summary>
        /// Specifies that the ROWIDs are fetched after doing a define at position 0, and a
        /// SELECT...FOR UPDATE statement.
        /// </summary>
        bool FetchRowId( ) const
        {
            return GetBooleanAttribute( Attribute::FETCH_ROWID );
        }
        /// <summary>
        /// Specifies that the ROWIDs are fetched after doing a define at position 0, and a
        /// SELECT...FOR UPDATE statement.
        /// </summary>
        void SetFetchRowId( bool value ) const
        {
            SetBooleanAttribute( Attribute::FETCH_ROWID, value );
        }

        /// <summary>
        /// Returns the total number of implicit results available on 
        /// the top-level OCI statement handle.
        /// </summary>
        UInt32 ImplicitResultCount( ) const
        {
            return GetUInt32Attribute( Attribute::IMPLICIT_RESULT_COUNT );
        }

        /// <summary>
        /// Gets the number of columns in the select-list for the 
        /// statement associated with the statement handle.
        /// </summary>
        UInt32 ParamCount( ) const
        {
            return GetUInt32Attribute( Attribute::PARAM_COUNT );
        }
        
        /// <summary>
        /// Returns the parse error offset for a statement.
        /// </summary>
        UInt32 ParseErrorOffset( ) const
        {
            return GetUInt16Attribute( Attribute::PARSE_ERROR_OFFSET );
        }

        /// <summary>
        /// Sets the memory level for top-level rows to be prefetched.
        /// </summary>
        /// <remarks>
        /// Rows up to the specified top-level row count are fetched 
        /// if the memory level occupies no more than the specified 
        /// memory usage limit. The default value is 0, which means 
        /// that memory size is not included in computing the number 
        /// of rows to prefetch.
        /// </remarks>
        /// <param name="size">memory limit</param>
        void SetPrefetchMemory( UInt32 size ) const
        {
            SetUInt32Attribute( Attribute::PREFETCH_MEMORY, static_cast<UInt32>( size ) );
        }

        /// <summary>
        /// Sets the number of top-level rows to be prefetched. The default value is 1 row.
        /// </summary>
        /// <param name="count">number of rows to be prefetched</param>
        void SetPrefetchRows( UInt32 count ) const
        {
            SetUInt32Attribute( Attribute::PREFETCH_ROWS, count );
        }

        /// <summary>
        /// Returns the number of rows processed so far after SELECT statements.
        /// </summary>
        UInt64 RowCount( ) const
        {
            return GetUInt64Attribute( Attribute::UB8_ROW_COUNT );
        }

        /// <summary>
        /// Indicates the number of rows that were successfully 
        /// fetched into the user's buffers in the last fetch or 
        /// execute with nonzero iterations. It can be used for 
        /// both scrollable and nonscrollable statement handles.
        /// </summary>
        /// <returns></returns>
        UInt32 RowsFetched( ) const
        {
            return GetUInt32Attribute( Attribute::ROWS_FETCHED );
        }

        /// <summary>
        /// Returns the function code of the SQL command associated with the statement.
        /// </summary>
        UInt16 SqlFunctionCode( ) const
        {
            return GetUInt16Attribute( Attribute::SQLFNCODE );
        }

        /// <summary>
        /// Returns the text of the SQL statement prepared in a statement handle. 
        /// In UTF-16 mode, the returned statement is in UTF-16 encoding.
        /// </summary>
        WideString Text( ) const
        {
            return GetStringAttribute( Attribute::STATEMENT );
        }

        /// <summary>
        /// Returns true if the SQL Statement has a RETURNING INTO clause
        /// </summary>
        /// <returns></returns>
        bool IsReturning( ) const
        {
            return GetUInt16Attribute( Attribute::STMT_IS_RETURNING );
        }

        /// <summary>
        /// Returns the fetch state of that statement.
        /// </summary>
        StatementState State( ) const
        {
            return static_cast<StatementState>( GetUInt32Attribute( Attribute::STMT_STATE ) );
        }

        /// <summary>
        /// Returns a reference to the registered continous query notification handler
        /// </summary>
        /// <returns></returns>
        const OCI::Subscription& ChangeNotification( ) const
        {
            return changeNotification_;
        }

        /// <summary>
        /// When this attribute is set to the appropriate subscription handle, execution of the
        /// query also creates the registration of the query for continuous query notification.
        /// </summary>
        /// <param name="subscription">subscription</param>
        void SetChangeNotification( Subscription&& changeNotification )
        {
            if ( changeNotification )
            {
                auto notificationHandle = changeNotification.Handle( );
                if ( notificationHandle )
                {
                    SetAttribute( &notificationHandle, 0, Attribute::CHNF_REGHANDLE );
                }
            }
            changeNotification_ = std::move(changeNotification);
        }


        HO_EXPORT Int32 Execute( UInt32 iters = 1, StatementExecuteMode executeMode = StatementExecuteMode::Default, UInt32 rowoff = 0 );

        template<typename DataReaderType = OCI::DataReader>
            requires std::is_base_of_v<OCI::DataReader, DataReaderType>
        std::unique_ptr<DataReaderType> ExecuteReader( StatementExecuteMode executeMode = StatementExecuteMode::Default );

        template<typename DataReaderType>
            requires std::is_base_of_v<OCI::ArrayDataReader, DataReaderType>
        std::unique_ptr<DataReaderType> ExecuteReader( size_t defineSize = 1000,StatementExecuteMode executeMode = StatementExecuteMode::Default );

        template<typename T>
        std::optional<T> ExecuteScalar( );

        Int64 ExecuteNonQuery( UInt32 iters = 1, StatementExecuteMode executeMode = StatementExecuteMode::Default, UInt32 rowoff = 0 )
        {
            Execute( iters, executeMode, rowoff );
            return RowCount( );
        }

        HO_EXPORT Int32 Fetch( UInt32 numberOfRows = 1, FetchOrientation orientation = FetchOrientation::Next, long fetchOffset = 0 ) const;

        UInt32 DescriptorCount( ) const
        {
            return GetUInt32Attribute( Attribute::PARAM_COUNT );
        }
        HO_EXPORT std::unique_ptr<ParameterDescriptor> Descriptor( UInt32 descriptorIndex ) const;

        HO_EXPORT void GetDescriptors( std::vector< std::unique_ptr<ParameterDescriptor> >& descriptors ) const;

        HO_EXPORT std::unique_ptr<OCI::Define> Define( UInt32 descriptorIndex ) const;
        HO_EXPORT std::unique_ptr<OCI::Define> Define( UInt32 descriptorIndex, const OCI::ColumnDescriptor& columnDescriptor ) const;

        HO_EXPORT std::unique_ptr<OCI::ArrayDefine> Define( size_t defineSize, UInt32 descriptorIndex ) const;
        HO_EXPORT std::unique_ptr<OCI::ArrayDefine> Define( size_t defineSize, UInt32 descriptorIndex, const OCI::ColumnDescriptor& columnDescriptor ) const;


    };


    template<WideStringLike StringT, typename ...BindableTypes>
    inline Int64 ServiceContext::ExecuteNonQuery( const StringT& sql, BindableTypes&& ...bindableArgs ) const
    {
        auto statement = CreateStatement( sql, std::forward<BindableTypes>( bindableArgs )... );
        return statement.ExecuteNonQuery( );
    }

    template<typename ...BindableTypes>
    inline Int64 ServiceContext::ExecuteNonQuery( const wchar_t* sql, BindableTypes&& ...bindableArgs ) const
    {
        WideString wsql( sql );
        return ExecuteNonQuery( wsql, std::forward<BindableTypes>( bindableArgs )... );
    }


    /// <summary>
    /// Descriptor, base class for all the descriptors
    /// </summary>
    class Descriptor : public HandleBase
    {
        using Base = HandleBase;
        const OCI::ServiceContext* serviceContext_;
    public:
        constexpr Descriptor( ) noexcept
            : serviceContext_( nullptr )
        {
        }

        Descriptor( const Descriptor& other ) = delete;
        constexpr Descriptor( Descriptor&& other ) noexcept
            : Base( std::move( other ) ), serviceContext_( other.serviceContext_ )
        {
            other.serviceContext_ = nullptr;
        }


        /// <summary>
        /// Constructs a new Descriptor object
        /// </summary>
        /// <param name="serviceContext">A reference to the service context used to create the descriptor handle</param>
        /// <param name="handleType">The handle type for the descriptor.</param>
        /// <param name="handle">The handle wrapped by this object.</param>
        /// <param name="ownsHandle">Set to true if the new object will take owneship of the handle value</param>
        constexpr Descriptor( const OCI::ServiceContext& serviceContext, OCI::HandleType handleType, void* handle, bool ownsHandle = true ) noexcept
            : Base( handleType, handle, ownsHandle ), serviceContext_( &serviceContext )
        {
        }

        /// <summary>
        /// Allocates a descriptor of the specified type and constructs a new Descriptor object
        /// </summary>
        /// <param name="serviceContext">A reference to the service context used to create the descriptor handle</param>
        /// <param name="handleType">The handle type for the descriptor that will be allocated.</param>
        Descriptor( const OCI::ServiceContext& serviceContext, OCI::HandleType handleType )
            : Base( handleType, DescriptorAlloc( serviceContext, handleType ), true ), serviceContext_( &serviceContext )
        {
        }

        HO_EXPORT ~Descriptor( );


        Descriptor& operator = ( const Descriptor& other ) = delete;
        Descriptor& operator = ( Descriptor&& other ) noexcept
        {
            if ( this != &other )
            {

                Base::Take( std::move( other ) ); 
                serviceContext_ = other.serviceContext_; 
                other.serviceContext_ = nullptr;
            }
            return *this;
        }

    protected:
        template<typename T>
        constexpr void Take( T&& other ) noexcept
        {
            Base::Take( std::move( other ) );
            serviceContext_ = other.serviceContext_;
            other.serviceContext_ = nullptr;
        }

        WideString GetStringAttribute( DescribeAttribute attributeId ) const
        {
            return Base::GetStringAttribute( static_cast<Attribute>( attributeId ) );
        }
        using Base::GetStringAttribute;
        void SetStringAttribute( DescribeAttribute attribute, const WideString& value ) const
        {
            Base::SetStringAttribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetStringAttribute;

        bool GetBooleanAttribute( DescribeAttribute attribute ) const
        {
            return Base::GetBooleanAttribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetBooleanAttribute;
        void SetBooleanAttribute( DescribeAttribute attribute, bool value ) const
        {
            Base::SetBooleanAttribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetBooleanAttribute;
        
        Byte GetByteAttribute( DescribeAttribute attribute ) const
        {
            return Base::GetByteAttribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetByteAttribute;
        void SetByteAttribute( DescribeAttribute attribute, Byte value ) const
        {
            Base::SetByteAttribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetByteAttribute;

        SByte GetSByteAttribute( DescribeAttribute attribute ) const
        {
            return Base::GetSByteAttribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetSByteAttribute;
        void SetSByteAttribute( DescribeAttribute attribute, SByte value ) const
        {
            Base::SetSByteAttribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetSByteAttribute;

        Int16 GetInt16Attribute( DescribeAttribute attribute ) const
        {
            return Base::GetInt16Attribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetInt16Attribute;
        void SetInt16Attribute( DescribeAttribute attribute, Int16 value ) const
        {
            Base::SetInt16Attribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetInt16Attribute;

        UInt16 GetUInt16Attribute( DescribeAttribute attribute ) const
        {
            return Base::GetUInt16Attribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetUInt16Attribute;
        void SetUInt16Attribute( DescribeAttribute attribute, UInt16 value ) const
        {
            Base::SetUInt16Attribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetUInt16Attribute;

        Int32 GetInt32Attribute( DescribeAttribute attribute ) const
        {
            return Base::GetInt32Attribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetInt32Attribute;
        void SetInt32Attribute( DescribeAttribute attribute, Int32 value ) const
        {
            Base::SetInt32Attribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetInt32Attribute;

        UInt32 GetUInt32Attribute( DescribeAttribute attribute ) const
        {
            return Base::GetUInt32Attribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetUInt32Attribute;
        void SetUInt32Attribute( DescribeAttribute attribute, UInt32 value ) const
        {
            Base::SetUInt32Attribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetUInt32Attribute;

        void* GetPointerAttribute( DescribeAttribute attribute ) const
        {
            return Base::GetPointerAttribute( static_cast<Attribute>( attribute ) );
        }
        using Base::GetPointerAttribute;
        void SetPointerAttribute( DescribeAttribute attribute, void* value ) const
        {
            Base::SetPointerAttribute( static_cast<Attribute>( attribute ), value );
        }
        using Base::SetPointerAttribute;


    public:

        const OCI::ServiceContext& ServiceContext( ) const
        {
            return *serviceContext_;
        }

        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            auto& serviceContext = ServiceContext( );
            return serviceContext.Error( );
        }
        const OCI::Environment& Environment( ) const
        {
            auto& serviceContext = ServiceContext( );
            return serviceContext.Environment( );
        }


        HO_EXPORT static void* DescriptorAlloc( const OCI::ServiceContext& serviceContext, OCI::HandleType handleType );
        HO_EXPORT static void DescriptorFree( void* handle, OCI::HandleType handleType );

        /// <summary>
        /// Object or schema ID
        /// </summary>
        /// <returns>The object or schema ID</returns>
        UInt32 Id( ) const
        {
            return GetUInt32Attribute( Attribute::OBJ_ID );
        }

        /// <summary>
        /// Database name or object name in a schema
        /// </summary>
        /// <returns>The database name or object name in a schema</returns>
        WideString Name( ) const
        {
            return GetStringAttribute( Attribute::OBJ_NAME );
        }

        /// <summary>
        /// Schema name where the object is located
        /// </summary>
        /// <returns>The schema name where the object is located</returns>
        WideString Schema( ) const
        {
            return GetStringAttribute( Attribute::OBJ_SCHEMA );
        }

        OCI::ParameterType ParameterType( ) const
        {
            return static_cast<OCI::ParameterType>(GetByteAttribute( Attribute::PTYPE ));
        }
    };


    /// <summary>
    /// TimestampBaseDescriptor
    /// </summary>
    template<OCI::HandleType ociHandleType>
    class TimestampBaseDescriptor : public Descriptor
    {
    public:
        using Base = Descriptor;
        static constexpr OCI::HandleType OCIHandleType = ociHandleType;
    
        constexpr TimestampBaseDescriptor() noexcept
        { }

        constexpr TimestampBaseDescriptor( const OCI::ServiceContext& serviceContext, OCIDateTime* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        {
        }
        explicit TimestampBaseDescriptor( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        {
        }

        void Assign( const DateTime& dateTime ) const
        {
            auto& error = Error( );
            auto& environment = Environment( );
            DateTimeConstruct( environment, error, (OCIDateTime*)Handle( ), dateTime );
        }

        DateTime AsDateTime( ) const
        {
            auto& error = Error( );
            auto& environment = Environment( );
            return DateTimeGetDateTime( environment, error, (OCIDateTime*)Handle( ) );
        }
    };

    /// <summary>
    /// AnsiDateDescriptor
    /// </summary>
    using AnsiDateDescriptor = TimestampBaseDescriptor<OCI::HandleType::DATE>;

    /// <summary>
    /// TimestampDescriptor
    /// </summary>
    using TimestampDescriptor = TimestampBaseDescriptor<OCI::HandleType::TIMESTAMP>;

    /// <summary>
    /// TimestampTZDescriptor
    /// </summary>
    using TimestampTZDescriptor = TimestampBaseDescriptor<OCI::HandleType::TIMESTAMP_TZ>;

    /// <summary>
    /// TimestampLTZDescriptor
    /// </summary>
    using TimestampLTZDescriptor = TimestampBaseDescriptor<OCI::HandleType::TIMESTAMP_LTZ>;


    /// <summary>
    /// IntervalBaseDescriptor
    /// </summary>
    template<OCI::HandleType ociHandleType>
    class IntervalBaseDescriptor : public Descriptor
    {
    public:
        using Base = Descriptor;
        static constexpr OCI::HandleType OCIHandleType = ociHandleType;

        constexpr IntervalBaseDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr IntervalBaseDescriptor( const OCI::ServiceContext& serviceContext, OCIInterval* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        { }
        explicit IntervalBaseDescriptor( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        { }

        void Assign( const TimeSpan& timeSpan ) const
        {
            auto& error = Error( );
            auto& environment = Environment( );
            IntervalSetTimeSpan( environment, error, timeSpan, (OCIInterval*)Handle( ) );
        }

        TimeSpan AsTimeSpan( ) const
        {
            auto& error = Error( );
            auto& environment = Environment( );
            return IntervalGetTimeSpan( environment, error, (OCIInterval*)Handle( ) );
        }
    
    };

    /// <summary>
    /// IntervalYMDescriptor
    /// </summary>
    using IntervalYMDescriptor = IntervalBaseDescriptor<OCI::HandleType::INTERVAL_YM>;
    
    /// <summary>
    /// IntervalDSDescriptor
    /// </summary>
    using IntervalDSDescriptor = IntervalBaseDescriptor<OCI::HandleType::INTERVAL_DS>;

    /// <summary>
    /// SnapshotDescriptor
    /// </summary>
    class SnapshotDescriptor final : public Descriptor
    {
        using Base = Descriptor;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::SNAP;

        constexpr SnapshotDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr SnapshotDescriptor( const OCI::ServiceContext& serviceContext, OCISnapshot* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        { }
        explicit SnapshotDescriptor( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        {
        }
    };

    /// <summary>
    /// ResultSetDescriptor
    /// </summary>
    class ResultSetDescriptor final : public Descriptor
    {
        using Base = Descriptor;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::RSET;

        constexpr ResultSetDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr ResultSetDescriptor( const OCI::ServiceContext& serviceContext, OCIResult* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        {
        }
        explicit ResultSetDescriptor( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        {
        }
    };

    /// <summary>
    /// LOBLocatorBase
    /// </summary>
    class LOBLocatorBase : public Descriptor
    {
        using Base = Descriptor;
    public:
        constexpr LOBLocatorBase( ) noexcept
            : Base( )
        {
        }

        constexpr LOBLocatorBase( const OCI::ServiceContext& serviceContext, OCI::HandleType handleType, OCILobLocator* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, handleType, handle, ownsHandle )
        { }

        LOBLocatorBase( const OCI::ServiceContext& serviceContext, OCI::HandleType handleType )
            : Base( serviceContext, handleType )
        {
        }


        HO_EXPORT void Append( const LOBLocatorBase& source ) const;

        HO_EXPORT void Close( ) const;

        HO_EXPORT void Copy( UInt64 destinationOffset, const LOBLocatorBase& source, UInt64 sourceOffset, UInt64 count ) const;

        HO_EXPORT void DisableBuffering( ) const;

        HO_EXPORT void EnableBuffering( ) const;

        HO_EXPORT UInt64 Erase( UInt64 offset, UInt64 count ) const;

        HO_EXPORT void FlushBuffer( bool releaseResources = false ) const;

    };

    /// <summary>
    /// LOBLocator
    /// </summary>
    class LOBLocator : public LOBLocatorBase
    {
        using Base = LOBLocatorBase;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::LOB;

        constexpr LOBLocator( ) noexcept
            : Base( )
        {
        }

        constexpr LOBLocator( const OCI::ServiceContext& serviceContext, OCILobLocator* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        {
        }

        explicit LOBLocator( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        {
        }

    };


    /// <summary>
    /// BFILELocator
    /// </summary>
    class BFILELocator : public LOBLocatorBase
    {
        using Base = LOBLocatorBase;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::FILE;

        constexpr BFILELocator( ) noexcept
            : Base( )
        {
        }

        constexpr BFILELocator( const OCI::ServiceContext& serviceContext, OCILobLocator* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        {
        }

        explicit BFILELocator( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        {
        }


        HO_EXPORT void FileClose( ) const;
        HO_EXPORT bool FileExists( ) const;
        HO_EXPORT bool FileIsOpen( ) const;
        HO_EXPORT void FileOpen( ) const;
        HO_EXPORT WideString FileGetName( WideString& directoryAlias ) const;
        HO_EXPORT void FileSetName( const WideString& directoryAlias, const WideString& filename );

    };


    /// <summary>
    /// RowIdDescriptor
    /// </summary>
    class RowIdDescriptor final : public Descriptor
    {
        using Base = Descriptor;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::ROWID;

        constexpr RowIdDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr RowIdDescriptor( const OCI::ServiceContext& serviceContext, OCIRowid* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCIHandleType, handle, ownsHandle )
        {
        }

        explicit RowIdDescriptor( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCIHandleType )
        {
        }


    };



    /// <summary>
    /// BindBase, base class for binds
    /// </summary>
    class BindBase : public HandleBase
    {
        friend class Statement;
        using Base = HandleBase;
        OCI::Statement* statement_;
        UInt32 position_;
        WideString name_;
    protected:
        BindBase( ) noexcept
            : Base( ), statement_(nullptr), position_(0)
        { }
    private:
        void EnsureStatementIsValid( const OCI::Statement& statement )
        {
            if ( !statement )
            {
                HCC_THROW( ArgumentException, L"Statement handle is not valid", L"statement" );
            }
        }
    public:

        BindBase( const OCI::Statement& statement )
            : Base( OCI::HandleType::Bind, nullptr, false ), 
              statement_( const_cast<OCI::Statement*>(&statement) ), 
              position_(0)
        {
            EnsureStatementIsValid( statement );
        }
        BindBase( const OCI::Statement& statement, UInt32 position )
            : Base( OCI::HandleType::Bind, nullptr, false ), 
              statement_( const_cast<OCI::Statement*>( &statement ) ), 
              position_( position )
        {
            EnsureStatementIsValid( statement );
        }
        BindBase( const OCI::Statement& statement, const WideString& name )
            : Base( OCI::HandleType::Bind, nullptr, false ), 
              statement_( const_cast<OCI::Statement*>( &statement ) ), 
              position_( 0 ), 
              name_( name )
        {
            EnsureStatementIsValid( statement );
        }
    public:
        const OCI::Environment& Environment( ) const
        {
            return statement_->Environment( );
        }
        const OCI::ErrorHandle & Error( ) const noexcept final override
        {
            return statement_->Error( );
        }

        HO_EXPORT void BindByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* actualLengths = nullptr, UInt16* returnCodes = nullptr, UInt32 plsqlMaxArrayLength = 0, UInt32* plsqlArrayLength = nullptr, UInt32 mode = 0 );
        HO_EXPORT void BindByName( const WideString& name, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* actualLengths = nullptr, UInt16* returnCodes = nullptr, UInt32 plsqlMaxArrayLength = 0, UInt32* plsqlArrayLength = nullptr, UInt32 mode = 0 );


    protected:
        bool IsPlSQL( ) const
        {
            auto& statement = Statement( );
            auto stmtType = statement.StatementType( );
            return stmtType == OCI::StatementType::Begin || stmtType == OCI::StatementType::Declare;
        }
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters );
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters );
    public:
        void OnExecute( UInt32 iters )
        {
            if ( IsBindByPosition( ) )
            {
                this->Bind( Position( ), iters );
            }
            else
            {
                this->Bind( Name( ), iters );
            }
        }

        constexpr const OCI::Statement& Statement( ) const
        {
            return *statement_;
        }


        const OCI::ServiceContext& ServiceContext( ) const
        {
            const auto& statement = Statement( );
            return statement.ServiceContext( );
        }


        UInt32 Position( ) const
        {
            return position_;
        }
        void SetPosition( UInt32 position )
        {
            position_ = position;
        }

        bool IsBindByPosition( ) const
        {
            return position_ > 0;
        }

        const WideString& Name( ) const
        {
            return name_;
        }
        WideString Name( )
        {
            return name_;
        }

        void SetName( const WideString& name )
        {
            name_ = name;
        }

        /// <summary>
        /// Sets the number of characters in character type data. (OCI_ATTR_CHAR_COUNT)
        /// </summary>
        /// <param name="charCount"></param>
        void SetCharCount( UInt32 charCount )
        {
            SetUInt32Attribute( Attribute::CHAR_COUNT, charCount );
        }

        /// <summary>
        /// Sets the number of characters that an application reserves on the server to 
        /// store the data being bound.
        /// </summary>
        /// <remarks>
        /// SetMaxCharSize enables processing to work with data in terms of number of
        /// characters, rather than number of bytes. SetMaxCharSize sets the number of 
        /// characters reserved in the Oracle database to store the bind data.
        /// For example, if SetMaxDataSize is with the argument set to 100, and
        /// SetMaxCharSize is called with the argument set to 0, then the maximum possible 
        /// size of the data in the Oracle database after conversion is 100 bytes. However, 
        /// if SetMaxDataSize iscalled with the argument set to 300, and SetMaxCharSize is 
        /// with the argument set to 100, then if the character set has 2 bytes/character, 
        /// the maximum possible allocated size is 200 bytes.
        /// </remarks>
        /// <param name="maxCharSize">character count</param>
        void SetMaxCharSize( Int32 maxCharSize )
        {
            SetInt32Attribute( Attribute::MAXCHAR_SIZE, maxCharSize );
        }

        /// <summary>
        /// Sets the maximum number of bytes allowed in the buffer on the server side to
        /// accommodate client-side bind data after character set conversions.
        /// </summary>
        /// <param name="maxDataSize">byte count</param>
        void SetMaxDataSize( Int32 maxDataSize )
        {
            SetInt32Attribute( Attribute::MAXDATA_SIZE, maxDataSize );
        }

        /// <summary>
        /// Retrieves the derived collation of a placeholder expression corresponding to this bind
        /// handle in a SQL statement. The value is relevant only for bind variables with
        /// character data types.
        /// </summary>
        /// <returns>The collation id</returns>
        UInt32 CollationId( ) const
        {
            return GetUInt32Attribute( Attribute::COLLATION_ID );
        }
        /// <summary>
        /// Sets the derived collation of a placeholder expression corresponding to this bind
        /// handle in a SQL statement.The attribute is relevant only for bind variables with
        /// character data types.
        /// </summary>
        /// <remarks>
        /// the collation id can be set on a bind variable handle to any of the 
        /// supported collation IDs. Collation IDs of both named collations and pseudocollations
        /// are allowed. The attribute value is passed to the server with other bind
        /// information and the corresponding bind variable reference, formally known as SQL
        /// placeholder expression, assumes the provided collation at the coercibility level 0. 
        /// If the attribute value is Collation::None (the default value), the collation of 
        /// the bind variable is USING_NLS_COMP at the coercibility level 4.
        /// OCI does not check whether the collation is valid for a given data type of a bind
        /// variable. If the collation id is set for a non-character data type variable, it is
        /// ignored by the server.
        /// Collation of bind variables is currently ignored in PL/SQL expressions. For forward
        /// compatibility reasons, the collation id should not be set for bind
        /// variables passed to an anonymous PL/SQL block, unless the variables are referenced
        /// exclusively in SQL statements.
        /// </remarks>
        /// <param name="collationId">The collation id</param>
        void SetCollationId( UInt32 collationId ) const
        {
            SetUInt32Attribute( Attribute::COLLATION_ID, collationId );
        }

        
        /// <summary>
        /// Retrives the character set ID of the bind handle
        /// </summary>
        /// <returns>the character set ID of the bind handle</returns>
        UInt16 CharacterSet( ) const
        {
            return GetUInt16Attribute( Attribute::CHARSET_ID );
        }
        /// <summary>
        /// Sets the character set ID of the bind handle
        /// </summary>
        /// <remarks>
        /// If SetCharacterSetForm will be called for this handle it must be called
        /// before calling SetCharacterSet. Setting the character set ID before 
        /// setting the character set form causes unexpected results. 
        /// </remarks>
        /// <param name="characterSetId">The new character set ID for the bind handle</param>
        void SetCharacterSet( UInt16 characterSetId ) const
        {
            SetUInt16Attribute( Attribute::CHARSET_ID, characterSetId );
        }


        /// <summary>
        /// Character set form of the bind handle.The default form is OCI::CharacterSetForm::Implicit.Setting
        /// this attribute causes the bind handle to use the database or national character set on
        /// the client side.Set this attribute to OCI::CharacterSetForm::NChar for the national character set 
        /// or OCI::CharacterSetForm::Implicit for the database character set
        /// </summary>
        OCI::CharacterSetForm CharacterSetForm( ) const
        {
            return static_cast<OCI::CharacterSetForm>( GetByteAttribute( Attribute::CHARSET_FORM ) );
        }
        void SetCharacterSetForm( OCI::CharacterSetForm charsetForm )
        {
            SetByteAttribute( Attribute::CHARSET_FORM, static_cast<Byte>( charsetForm ) );
        }

        

        /// <summary>
        /// Returns the number of rows that will be returned in the current iteration
        /// when you are in the OUT callback function for binding a DML statement with a
        /// RETURNING clause. (OCI_ATTR_ROWS_RETURNED)
        /// </summary>
        UInt32 RowsReturned( ) const
        {
            return GetUInt32Attribute( Attribute::ROWS_RETURNED );
        }
    };

    inline Statement::Statement( Statement&& other ) noexcept
        : Base( std::move( other ) ),
        serviceContext_( other.serviceContext_ ),
        error_( other.error_ ),
        changeNotification_( std::move( other.changeNotification_ ) ),
        binds_( std::move( other.binds_ ) )
    {
        other.serviceContext_ = nullptr;
        other.error_ = nullptr;
        for ( const auto& bind : binds_ )
        {
            bind->statement_ = this;
        }
    }

    inline Statement& Statement::operator = ( Statement&& other ) noexcept
    {
        if ( this != &other )
        {
            Take( std::move( other ) );
            std::swap( serviceContext_, other.serviceContext_ );
            std::swap( error_, other.error_ );
            changeNotification_.swap( other.changeNotification_ );
            std::swap( binds_, other.binds_ );
            for ( const auto& bind : binds_ )
            {
                bind->statement_ = this;
            }
            for ( const auto& bind : other.binds_ )
            {
                bind->statement_ = &other;
            }
        }
        return *this;
    }

    
    /// <summary>
    /// Bind, base class for binding a single value
    /// </summary>
    class Bind : public BindBase
    {
        using Base = BindBase;
    protected:
        Int16 indicator_;
    public:
        Bind( ) noexcept
            : Base( ), indicator_( -1 )
        {
        }

        Bind( const OCI::Statement& statement )
            : Base( statement ), indicator_( -1 )
        { }

        Bind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), indicator_( -1 )
        { }

        Bind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), indicator_( -1 )
        { }

        void SimpleBindByPos( UInt32 positon, OraType dataType, void* dataAddress, Int32 dataSize )
        {
            Base::BindByPos( positon, dataType, dataAddress, dataSize, &indicator_ );
        }
        void SimpleBindByName( const WideString& name, OraType dataType, void* dataAddress, Int32 dataSize )
        {
            Base::BindByName( name, dataType, dataAddress, dataSize, &indicator_ );
        }
    public:

        Int16 Indicator( ) const
        {
            return indicator_;
        }

        void SetIndicator( Int16 value )
        {
            indicator_ = value;
        }

        void SetDBNull( )
        {
            SetIndicator( static_cast<Int16>(-1) );
        }
        void SetDBNotNull( )
        {
            SetIndicator( static_cast<Int16>( 0 ) );
        }

        virtual void* Data( ) const
        {
            HCC_THROW( NotImplementedException );
        }

        virtual bool AsBoolean( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( bool newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Byte AsByte( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( Byte newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual SByte AsSByte( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( SByte newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual std::vector<Byte> AsBytes( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( const std::vector<Byte>& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Int16 AsInt16( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( Int16 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual UInt16 AsUInt16( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( UInt16 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Int32 AsInt32( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( Int32 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual UInt32 AsUInt32( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( UInt32 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Int64 AsInt64( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( Int64 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual UInt64 AsUInt64( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( UInt64 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual float AsSingle( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( float newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual double AsDouble( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( double newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual DateTime AsDateTime( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( const DateTime& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual TimeSpan AsTimeSpan( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( const TimeSpan& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual WideString AsString( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( const WideString& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Guid AsGuid( ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( const Guid& newValue )
        {
            HCC_THROW( NotImplementedException );
        }

        template<typename T>
        T As() const;
        
        template<>
        bool As( ) const
        {
            return this->AsBoolean( );
        }
        template<>
        SByte As( ) const
        {
            return this->AsSByte( );
        }
        template<>
        Byte As( ) const
        {
            return this->AsByte( );
        }
        template<>
        Int16 As( ) const
        {
            return this->AsInt16( );
        }
        template<>
        UInt16 As( ) const
        {
            return this->AsUInt16( );
        }
        template<>
        Int32 As( ) const
        {
            return this->AsInt32( );
        }
        template<>
        UInt32 As( ) const
        {
            return this->AsUInt32( );
        }
        template<>
        Int64 As( ) const
        {
            return this->AsInt64( );
        }
        template<>
        UInt64 As( ) const
        {
            return this->AsUInt64( );
        }
        template<>
        Single As( ) const
        {
            return this->AsSingle( );
        }
        template<>
        Double As( ) const
        {
            return this->AsDouble( );
        }
        template<>
        DateTime As( ) const
        {
            return this->AsDateTime( );
        }
        template<>
        TimeSpan As( ) const
        {
            return this->AsTimeSpan( );
        }
        template<>
        Guid As( ) const
        {
            return this->AsGuid( );
        }
        template<>
        WideString As( ) const
        {
            return this->AsString( );
        }




    };


    /// <summary>
    /// ArrayBind, base class for binding an array of values
    /// </summary>
    class ArrayBind : public BindBase
    {
        using Base = BindBase;
    protected:
        std::vector<Int16> indicator_;
    public:
        ArrayBind( ) noexcept
            : Base( )
        { }

        ArrayBind( const OCI::Statement& statement )
            : Base( statement )
        { }

        ArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        { }

        ArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        { }

    protected:
        void SimpleBindByPos( UInt32 positon, OraType dataType, void* dataAddress, Int32 dataSize, UInt32 maximumNumberOfElements, UInt32* currentNumberOfElements )
        {
            Base::BindByPos( positon, dataType, dataAddress, dataSize, indicator_.data( ), nullptr, nullptr, maximumNumberOfElements, currentNumberOfElements );
        }
        void SimpleBindByName( const WideString& name, OraType dataType, void* dataAddress, Int32 dataSize, UInt32 maximumNumberOfElements, UInt32* currentNumberOfElements )
        {
            Base::BindByName( name, dataType, dataAddress, dataSize, indicator_.data( ), nullptr, nullptr, maximumNumberOfElements, currentNumberOfElements );
        }
        void resize( size_t newSize )
        {
            indicator_.resize( newSize, -1 );
        }
    public:
        Int16 Indicator( size_t index ) const
        {
            return indicator_[index];
        }

        void SetIndicator( size_t index, Int16 value )
        {
            if ( index >= indicator_.size( ) )
            {
                indicator_.resize( index + 1, 0 );
            }
            indicator_[index] = value;
        }

        void SetDBNull( size_t index )
        {
            SetIndicator( index, static_cast<Int16>( -1 ) );
        }
        void SetDBNotNull( size_t index )
        {
            SetIndicator( index, static_cast<Int16>( 0 ) );
        }

        virtual void* Data( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }

        virtual bool AsBoolean( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, bool newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Byte AsByte( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, Byte newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual SByte AsSByte( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, SByte newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual std::vector<Byte> AsBytes( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, const std::vector<Byte>& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Int16 AsInt16( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, Int16 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual UInt16 AsUInt16( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, UInt16 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Int32 AsInt32( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, Int32 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual UInt32 AsUInt32( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, UInt32 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Int64 AsInt64( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, Int64 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual UInt64 AsUInt64( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, UInt64 newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual float AsSingle( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, float newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual double AsDouble( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, double newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual DateTime AsDateTime( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, const DateTime& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual TimeSpan AsTimeSpan( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, const TimeSpan& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual WideString AsString( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, const WideString& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
        virtual Guid AsGuid( size_t index ) const
        {
            HCC_THROW( NotImplementedException );
        }
        virtual void Assign( size_t index, const Guid& newValue )
        {
            HCC_THROW( NotImplementedException );
        }
    };


    /// <summary>
    /// DynamicBind
    /// </summary>
    class DynamicBind : public BindBase
    {
        using Base = BindBase;
    public:
        DynamicBind( ) noexcept
            : Base( )
        { }

        DynamicBind( const OCI::Statement& statement )
            : Base( statement )
        { }

        DynamicBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        { }

        DynamicBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        { }

    
    private:
        HO_EXPORT static Int32 HandleInDataCallback( void *ctxp, OCIBind *bindp, UInt32 iter, UInt32 index, void **bufpp, UInt32 *alenpp, Byte* piecep, void **indpp );
        HO_EXPORT static Int32 HandleOutDataCallback( void *ctxp, OCIBind *bindp, UInt32 iter, UInt32 index, void **bufpp, UInt32 **alenp, Byte* piecep, void **indpp, UInt16 **rcodepp );
    protected:
        HO_EXPORT virtual Int32 HandleInData( UInt32 iter, UInt32 index, void **bufpp, UInt32 *alenpp, Byte* piecep, void **indpp );
        HO_EXPORT virtual Int32 HandleOutData( UInt32 iter, UInt32 index, void **bufpp, UInt32 **alenp, Byte* piecep, void **indpp, UInt16 **rcodepp );

        HO_EXPORT void RegisterCallbacks( );
        HO_EXPORT void BindByPos( UInt32 positon, OraType dataType, Int32 dataSize  );
        HO_EXPORT void BindByName( const WideString& name, OraType dataType, Int32 dataSize  );
    };



    /// <summary>
    /// SimpleBind, template for binding a single basic data type  
    /// </summary>
    template < typename BT, OCI::OraType externalType, typename IT >
    class SimpleBind : public Bind
    {
    public:
        using Base = Bind;
        static constexpr OCI::OraType ExternalType = externalType;
        using BoundType = BT;
        using IntermediateType = IT;
    private:
        IntermediateType data_;
    public:
        constexpr SimpleBind( ) noexcept
            : Base( ), data_( IntermediateType{} )
        { }

        SimpleBind( const OCI::Statement& statement )
            : Base( statement ), data_( IntermediateType{} )
        { }

        SimpleBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), data_( IntermediateType{} )
        { }

        SimpleBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), data_( IntermediateType{} )
        { }
    protected:
        virtual void Bind( UInt32 positon, UInt32 iters ) final override
        {
            SimpleBindByPos( positon, ExternalType, &data_, sizeof( data_ ) );
        }
        virtual void Bind( const WideString& name, UInt32 iters ) final override
        {
            SimpleBindByName( name, ExternalType, &data_, sizeof( data_ ) );
        }
    public:
        virtual void* Data( ) const final override
        {
            return ( void* )&data_;
        }
        virtual bool AsBoolean( ) const final override
        {
            return ConvertTo<bool>( data_ );
        }
        virtual void Assign( bool newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>(newValue);
            SetDBNotNull( );
        }
        virtual SByte AsSByte( ) const final override
        {
            return ConvertTo<SByte>( data_ );
        }
        virtual void Assign( SByte newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual Byte AsByte( ) const final override
        {
            return ConvertTo<Byte>( data_ );
        }
        virtual void Assign( Byte newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual Int16 AsInt16( ) const final override
        {
            return ConvertTo<Int16>( data_ );
        }
        virtual void Assign( Int16 newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            return ConvertTo<UInt16>( data_ );
        }
        virtual void Assign( UInt16 newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( data_ );
        }
        virtual void Assign( Int32 newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( data_ );
        }
        virtual void Assign( UInt32 newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual Int64 AsInt64( ) const final override
        {
            return ConvertTo<Int64>( data_ );
        }
        virtual void Assign( Int64 newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            return ConvertTo<UInt64>( data_ );
        }
        virtual void Assign( UInt64 newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual float AsSingle( ) const final override
        {
            return ConvertTo<float>( data_ );
        }
        virtual void Assign( float newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
        virtual double AsDouble( ) const final override
        {
            return ConvertTo<double>( data_ );
        }
        virtual void Assign( double newValue ) final override
        {
            data_ = ConvertTo<IntermediateType>( newValue );
            SetDBNotNull( );
        }
    };

    /// <summary>
    /// SimpleArrayBind, template for binding an array of a basic data type
    /// </summary>
    template < typename BT, OCI::OraType externalType, typename IT >
    class SimpleArrayBind : public ArrayBind
    {
    public:
        using Base = ArrayBind;
        static constexpr OCI::OraType ExternalType = externalType;
        using BoundType = BT;
        using IntermediateType = IT;

        using ArrayType = std::vector<IntermediateType>;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using size_type = typename ArrayType::size_type;
    private:
        ArrayType data_;
        UInt32 actualSize_;
    public:
        constexpr SimpleArrayBind( ) noexcept
            : Base( ), actualSize_( 0 )
        { }

        SimpleArrayBind( const OCI::Statement& statement )
            : Base( statement ), actualSize_( 0 )
        { }

        SimpleArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), actualSize_( 0 )
        { }

        SimpleArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), actualSize_( 0 )
        { }

        void Assign( const ArrayType& data )
        {
            indicator_.clear( );
            indicator_.resize( data.size( ) );
            data_ = data;
        }

        void Assign( ArrayType&& data )
        {
            indicator_.clear( );
            indicator_.resize( data.size( ), static_cast<Int16>( 0 ) );
            data_ = std::move( data );
        }

        void Assign( const std::initializer_list<BoundType>& data )
        {
            indicator_.clear( );
            indicator_.resize( data.size( ), static_cast<Int16>( 0 ) );
            data_.clear( );
            data_ = data;
        }

        void AssignNull( size_t size )
        {
            indicator_.clear( );
            indicator_.resize( size, static_cast<Int16>( -1 ) );
            data_.clear( );
            data_.resize( size );
        }


        iterator begin( ) noexcept
        {
            return data_.begin( );
        }

        const_iterator begin( ) const noexcept
        {
            return data_.begin( );
        }

        iterator end( ) noexcept
        {
            return data_.end( );
        }

        const_iterator end( ) const noexcept
        {
            return data_.end( );
        }

        size_type size( ) const noexcept
        {
            return data_.size( );
        }


        void resize( size_type count )
        {
            indicator_.resize( count, -1 );
            data_.resize( count );
        }





    protected:
        virtual void Bind( UInt32 positon, UInt32 iters ) override
        {
            auto dataSize = data_.size( );
            actualSize_ = static_cast< UInt32 >( dataSize );
            if ( this->IsPlSQL() == false )
            {
                indicator_.resize( dataSize );
            }
            if ( IsPlSQL( ) == false )
            {
                Base::BindByPos( positon, ExternalType, data_.data( ), sizeof( BoundType ), indicator_.data( ), nullptr, nullptr, 0, nullptr );
            }
            else
            {
                SimpleBindByPos( positon, ExternalType, data_.data( ), sizeof( BoundType ), actualSize_, &actualSize_ );
            }
        }
        virtual void Bind( const WideString& name, UInt32 iters )
        {
            auto dataSize = data_.size( );
            actualSize_ = static_cast<UInt32>( dataSize );
            if ( this->IsPlSQL( ) == false )
            {
                indicator_.resize( dataSize );
            }
            if ( IsPlSQL( ) == false )
            {
                Base::BindByName( name, ExternalType, data_.data( ), sizeof( BoundType ), indicator_.data( ), nullptr, nullptr, 0, nullptr );
            }
            else
            {
                SimpleBindByName( name, ExternalType, data_.data( ), sizeof( BoundType )*iters, actualSize_, &actualSize_ );
            }
        }
    public:
        virtual void* Data( size_t index ) const override
        {
            return ( void* )std::addressof( data_[index] );
        }
        virtual bool AsBoolean( size_t index ) const override
        {
            return ConvertTo<bool>( data_[index] );
        }
        virtual void Assign( size_t index, bool newValue ) override
        {
            data_[index] = ConvertTo<BoundType>( newValue );
            SetDBNotNull( index );
        }
        virtual Byte AsByte( size_t index ) const override
        {
            return ConvertTo< Byte >( data_[index] );
        }
        virtual void Assign( size_t index, Byte newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual SByte AsSByte( size_t index ) const override
        {
            return ConvertTo< SByte >( data_[index] );
        }
        virtual void Assign( size_t index, SByte newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual Int16 AsInt16( size_t index ) const override
        {
            return ConvertTo< Int16 >( data_[index] );
        }
        virtual void Assign( size_t index, Int16 newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual UInt16 AsUInt16( size_t index ) const override
        {
            return ConvertTo< UInt16 >( data_[index] );
        }
        virtual void Assign( size_t index, UInt16 newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual Int32 AsInt32( size_t index ) const override
        {
            return ConvertTo< Int32 >( data_[index] );
        }
        virtual void Assign( size_t index, Int32 newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual UInt32 AsUInt32( size_t index ) const override
        {
            return ConvertTo< UInt32 >( data_[index] );
        }
        virtual void Assign( size_t index, UInt32 newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual Int64 AsInt64( size_t index ) const override
        {
            return ConvertTo< Int64 >( data_[index] );
        }
        virtual void Assign( size_t index, Int64 newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual UInt64 AsUInt64( size_t index ) const override
        {
            return ConvertTo< UInt64 >( data_[index] );
        }
        virtual void Assign( size_t index, UInt64 newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual float AsSingle( size_t index ) const override
        {
            return ConvertTo< float >( data_[index] );
        }
        virtual void Assign( size_t index, float newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }
        virtual double AsDouble( size_t index ) const override
        {
            return ConvertTo< double >( data_[index] );
        }
        virtual void Assign( size_t index, double newValue ) override
        {
            data_[index] = ConvertTo< BoundType >( newValue );
            SetDBNotNull( index );
        }

    };

    
    
    /// <summary>
    /// CStringBind, a bind type for a zero terminated wide c string
    /// </summary>
    class CStringBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::STR;
        using BoundType = WideString;
    private:
        size_t allocated_;
        wchar_t* string_;
    public:
        CStringBind( ) noexcept
            : Base( ), allocated_(0), string_(nullptr)
        {
        }

        CStringBind( const OCI::Statement& statement )
            : Base( statement ), allocated_( 0 ), string_( nullptr )
        { }

        CStringBind( const OCI::Statement& statement, UInt32 position, size_t maximumColumnSize = 0 )
            : Base( statement, position ), allocated_( 0 ), string_( nullptr )
        {
            Require( maximumColumnSize );
        }

        CStringBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), allocated_( 0 ), string_( nullptr )
        { }

        CStringBind( const OCI::Statement& statement, UInt32 position, const WideString& value, size_t maximumColumnSize = 0 )
            : Base( statement, position ), allocated_( 0 ), string_( nullptr )
        {
            Require( maximumColumnSize );
            Assign( value );
        }

        CStringBind( const OCI::Statement& statement, const WideString& name, const WideString& value, size_t maximumColumnSize = 0 )
            : Base( statement, name ), allocated_( 0 ), string_( nullptr )
        {
            Assign( value );
        }

        virtual ~CStringBind( )
        {
            if ( string_ )
            {
                free( string_ );
            }
        }
    private:
        static constexpr size_t BytesRequired( size_t maxColumnSize )
        {
            return ( maxColumnSize + 1 ) * sizeof( wchar_t );
        }
    public:
    
        HO_EXPORT void Reserve( size_t maximumColumnSize );
        HO_EXPORT void Require( size_t maximumColumnSize );
    protected:
        virtual void Bind( UInt32 positon, UInt32 iters ) final override
        {
            Base::BindByPos( positon, ExternalType, string_, static_cast<Int32>( allocated_ ), &indicator_, nullptr, nullptr, 0, nullptr );
        }
        virtual void Bind( const WideString& name, UInt32 iters ) final override
        {
            Base::BindByName( name, ExternalType, string_, static_cast<Int32>( allocated_ ), &indicator_, nullptr, nullptr, 0, nullptr );
        }
    public:
        virtual void* Data( ) const final override
        {
            return (void*)string_;
        }
        virtual bool AsBoolean( ) const final override
        {
            return ConvertTo<bool>( AsString() );
        }
        virtual void Assign( bool newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual Byte AsByte( ) const final override
        {
            return ConvertTo<Byte>( AsString( ) );
        }
        virtual void Assign( Byte newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual SByte AsSByte( ) const final override
        {
            return ConvertTo<SByte>( AsString( ) );
        }
        virtual void Assign( SByte newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual Int16 AsInt16( ) const final override
        {
            return ConvertTo<Int16>( AsString( ) );
        }
        virtual void Assign( Int16 newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            return ConvertTo<UInt16>( AsString( ) );
        }
        virtual void Assign( UInt16 newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( AsString( ) );
        }
        virtual void Assign( Int32 newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( AsString( ) );
        }
        virtual void Assign( UInt32 newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual Int64 AsInt64( ) const final override
        {
            return ConvertTo<Int64>( AsString( ) );
        }
        virtual void Assign( Int64 newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            return ConvertTo<UInt64>( AsString( ) );
        }
        virtual void Assign( UInt64 newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual float AsSingle( ) const final override
        {
            return ConvertTo<Single>( AsString( ) );
        }
        virtual void Assign( float newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual double AsDouble( ) const final override
        {
            return ConvertTo<Double>( AsString( ) );
        }
        virtual void Assign( double newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }

        virtual DateTime AsDateTime( ) const final override
        {
            return ConvertTo<DateTime>( AsString( ) );
        }
        virtual void Assign( const DateTime& newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
        virtual TimeSpan AsTimeSpan( ) const final override
        {
            return ConvertTo<TimeSpan>( AsString( ) );
        }
        virtual void Assign( const TimeSpan& newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue.Ticks( ) ) );
        }
        virtual WideString AsString( ) const final override
        {
            if ( indicator_ != -1 && string_ )
            {
                return WideString( string_ );
            }
            return WideString( );
        }
        virtual void Assign( const WideString& newValue ) final override
        {
            auto length = newValue.length( );
            Require( length );
            wmemcpy( string_, newValue.c_str( ), static_cast<size_t>( length ) );
            SetDBNotNull( );
        }

        void Assign( const wchar_t* newValue )
        {
            auto length = wcslen(newValue);
            Require( length );
            wmemcpy( string_, newValue, static_cast<size_t>( length ) );
            SetDBNotNull( );
        }
        virtual Guid AsGuid( ) const final override
        {
            return ConvertTo<Guid>( AsString( ) );
        }
        virtual void Assign( const Guid& newValue ) final override
        {
            Assign( ConvertTo<WideString>( newValue ) );
        }
    };

    /// <summary>
    /// CStringArrayBind
    /// </summary>
    class CStringArrayBind : public ArrayBind
    {
        using Base = ArrayBind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::STR;
        using BoundType = WideString;
    private:
        UInt32 arraySize_;
        UInt32 arrayMaxSize_;
        size_t maxColumnDataSize_;
        wchar_t* data_;
        std::vector<UInt32> dataSizes_;
    public:
        CStringArrayBind( ) noexcept
            : Base( ), arraySize_( 0 ), arrayMaxSize_( 0 ), maxColumnDataSize_( 0 ), data_( nullptr )
        {
        }

        CStringArrayBind( const OCI::Statement& statement, size_t arraySize, size_t maximumArraySize, size_t maximumColumnSize )
            : Base( statement ), arraySize_( 0 ), arrayMaxSize_( 0 ), maxColumnDataSize_( 0 ), data_( nullptr )
        {
        }
        CStringArrayBind( const OCI::Statement& statement, UInt32 position, size_t arraySize, size_t maximumArraySize, size_t maximumColumnSize )
            : Base( statement, position ), arraySize_( 0 ), arrayMaxSize_( 0 ), maxColumnDataSize_( 0 ), data_( nullptr )
        { 
        }
        CStringArrayBind( const OCI::Statement& statement, const WideString& name, size_t arraySize, size_t maximumArraySize, size_t maximumColumnSize )
            : Base( statement, name ), arraySize_( 0 ), arrayMaxSize_( 0 ), maxColumnDataSize_( 0 ), data_( nullptr )
        { 
        }

        HO_EXPORT ~CStringArrayBind( );
    private:
        HO_EXPORT void Resize( size_t arraySize, size_t maximumArraySize, size_t elementSize );
    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters ) override;
    public:

        HO_EXPORT virtual void* Data( size_t index ) const override;

        HO_EXPORT virtual bool AsBoolean( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, bool newValue ) override;
        HO_EXPORT virtual Byte AsByte( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, Byte newValue ) override;
        HO_EXPORT virtual SByte AsSByte( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, SByte newValue ) override;
        HO_EXPORT virtual Int16 AsInt16( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, Int16 newValue ) override;
        HO_EXPORT virtual UInt16 AsUInt16( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, UInt16 newValue ) override;
        HO_EXPORT virtual Int32 AsInt32( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, Int32 newValue ) override;
        HO_EXPORT virtual UInt32 AsUInt32( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, UInt32 newValue ) override;
        HO_EXPORT virtual Int64 AsInt64( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, Int64 newValue ) override;
        HO_EXPORT virtual UInt64 AsUInt64( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, UInt64 newValue ) override;
        HO_EXPORT virtual float AsSingle( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, float newValue ) override;
        HO_EXPORT virtual double AsDouble( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, double newValue ) override;

        HO_EXPORT virtual DateTime AsDateTime( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const DateTime& newValue ) override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const TimeSpan& newValue ) override;
        HO_EXPORT virtual WideString AsString( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const WideString& newValue ) override;
        HO_EXPORT void Assign( size_t index, const wchar_t* newValue );
        HO_EXPORT virtual Guid AsGuid( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const Guid& newValue ) override;

    };


    /// <summary>
    /// StringBind
    /// </summary>
    class StringBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::ORA_OCIString;
        using BoundType = WideString;
    private:
        OCIString* string_;
    public:

        StringBind( ) noexcept
            : Base( ), string_(nullptr)
        {
        }

        StringBind( const OCI::Statement& statement )
            : Base( statement ), string_( nullptr )
        { }

        StringBind( const OCI::Statement& statement, UInt32 position, size_t maximumColumnSize = 0 )
            : Base( statement, position ), string_( nullptr )
        { }

        StringBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), string_( nullptr )
        { }

        StringBind( const OCI::Statement& statement, UInt32 position, const WideString& value, size_t maximumColumnSize = 0 )
            : Base( statement, position ), string_( nullptr )
        { }

        StringBind( const OCI::Statement& statement, const WideString& name, const WideString& value, size_t maximumColumnSize = 0 )
            : Base( statement, name ), string_( nullptr )
        { }

        HO_EXPORT virtual ~StringBind( );

    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters ) override;
    public:
        HO_EXPORT virtual void* Data( ) const override;
        HO_EXPORT virtual bool AsBoolean( ) const override;
        HO_EXPORT virtual void Assign( bool newValue ) override;
        HO_EXPORT virtual Byte AsByte( ) const override;
        HO_EXPORT virtual void Assign( Byte newValue ) override;
        HO_EXPORT virtual SByte AsSByte( ) const override;
        HO_EXPORT virtual void Assign( SByte newValue ) override;
        HO_EXPORT virtual Int16 AsInt16( ) const override;
        HO_EXPORT virtual void Assign( Int16 newValue ) override;
        HO_EXPORT virtual UInt16 AsUInt16( ) const override;
        HO_EXPORT virtual void Assign( UInt16 newValue ) override;
        HO_EXPORT virtual Int32 AsInt32( ) const override;
        HO_EXPORT virtual void Assign( Int32 newValue ) override;
        HO_EXPORT virtual UInt32 AsUInt32( ) const override;
        HO_EXPORT virtual void Assign( UInt32 newValue ) override;
        HO_EXPORT virtual Int64 AsInt64( ) const override;
        HO_EXPORT virtual void Assign( Int64 newValue ) override;
        HO_EXPORT virtual UInt64 AsUInt64( ) const override;
        HO_EXPORT virtual void Assign( UInt64 newValue ) override;
        HO_EXPORT virtual float AsSingle( ) const override;
        HO_EXPORT virtual void Assign( float newValue ) override;
        HO_EXPORT virtual double AsDouble( ) const override;
        HO_EXPORT virtual void Assign( double newValue ) override;

        HO_EXPORT virtual DateTime AsDateTime( ) const override;
        HO_EXPORT virtual void Assign( const DateTime& newValue ) override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( ) const override;
        HO_EXPORT virtual void Assign( const TimeSpan& newValue ) override;
        HO_EXPORT virtual WideString AsString( ) const override;
        HO_EXPORT virtual void Assign( const WideString& newValue ) override;
        HO_EXPORT virtual Guid AsGuid( ) const override;
        HO_EXPORT virtual void Assign( const Guid& newValue ) override;
    };


    /// <summary>
    /// DateBind
    /// </summary>
    class DateBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::ORA_OCIDate;
    private:
        OCI::Date ocidate_;
    public:
        DateBind( ) noexcept
            : Base( )
        {
        }

        DateBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        DateBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }

        DateBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters ) override;
    public:

        HO_EXPORT virtual void* Data( ) const override;

        HO_EXPORT void GetTime( Byte& hour, Byte& minute, Byte& second ) const;
        HO_EXPORT void SetTime( Byte hour, Byte minute, Byte second );

        HO_EXPORT void GetDate( Int16& year, Byte& month, Byte& day ) const;
        HO_EXPORT void SetDate( Int16 year, Byte month, Byte day );

        HO_EXPORT void GetDateTime( Int16& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second ) const;
        HO_EXPORT void SetDateTime( Int16 year, Byte month, Byte day, Byte hour, Byte minute, Byte second );

        HO_EXPORT virtual Int32 AsInt32( ) const override;
        HO_EXPORT virtual void Assign( Int32 newValue ) override;
        HO_EXPORT virtual UInt32 AsUInt32( ) const override;
        HO_EXPORT virtual void Assign( UInt32 newValue ) override;
        HO_EXPORT virtual Int64 AsInt64( ) const override;
        HO_EXPORT virtual void Assign( Int64 newValue ) override;
        HO_EXPORT virtual UInt64 AsUInt64( ) const override;
        HO_EXPORT virtual void Assign( UInt64 newValue ) override;
        HO_EXPORT virtual float AsSingle( ) const override;
        HO_EXPORT virtual void Assign( float newValue ) override;
        HO_EXPORT virtual double AsDouble( ) const override;
        HO_EXPORT virtual void Assign( double newValue ) override;

        HO_EXPORT virtual DateTime AsDateTime( ) const override;
        HO_EXPORT virtual void Assign( const DateTime& newValue ) override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( ) const override;
        HO_EXPORT virtual void Assign( const TimeSpan& newValue ) override;
        HO_EXPORT WideString AsString( const WideString& format ) const;
        HO_EXPORT virtual WideString AsString( ) const override;
        HO_EXPORT virtual void Assign( const WideString& newValue ) override;
        HO_EXPORT void Assign( const WideString& format, const WideString& newValue );
    };

    /// <summary>
    /// DateArrayBind
    /// </summary>
    class DateArrayBind : public ArrayBind
    {
        using Base = ArrayBind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::ORA_OCIDate;
    private:
        std::vector<OCI::Date> data_;
        UInt32 actualSize_;
    public:
        DateArrayBind( ) noexcept
            : Base( ), actualSize_( 0 )
        {
        }

        DateArrayBind( const OCI::Statement& statement )
            : Base( statement ), actualSize_(0)
        {
        }

        DateArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), actualSize_( 0 )
        {
        }

        DateArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), actualSize_( 0 )
        {
        }

    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters ) override;
    public:

        HO_EXPORT virtual void* Data( size_t index ) const override;

        HO_EXPORT void GetTime( size_t index, Byte& hour, Byte& minute, Byte& second ) const;
        HO_EXPORT void SetTime( size_t index, Byte hour, Byte minute, Byte second );

        HO_EXPORT void GetDate( size_t index, Int16& year, Byte& month, Byte& day ) const;
        HO_EXPORT void SetDate( size_t index, Int16 year, Byte month, Byte day );

        HO_EXPORT void GetDateTime( size_t index, Int16& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second ) const;
        HO_EXPORT void SetDateTime( size_t index, Int16 year, Byte month, Byte day, Byte hour, Byte minute, Byte second );

        HO_EXPORT virtual Int32 AsInt32( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, Int32 newValue ) override;
        HO_EXPORT virtual UInt32 AsUInt32( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, UInt32 newValue ) override;
        HO_EXPORT virtual Int64 AsInt64( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, Int64 newValue ) override;
        HO_EXPORT virtual UInt64 AsUInt64( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, UInt64 newValue ) override;
        HO_EXPORT virtual float AsSingle( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, float newValue ) override;
        HO_EXPORT virtual double AsDouble( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, double newValue ) override;

        HO_EXPORT virtual DateTime AsDateTime( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const DateTime& newValue ) override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const TimeSpan& newValue ) override;
        HO_EXPORT WideString AsString( size_t index, const WideString& format ) const;
        HO_EXPORT virtual WideString AsString( size_t index ) const override;
        HO_EXPORT virtual void Assign( size_t index, const WideString& newValue ) override;
        HO_EXPORT void Assign( size_t index, const WideString& format, const WideString& newValue );
    };


    /// <summary>
    /// DescriptorBaseBind
    /// </summary>
    class DescriptorBaseBind : public Bind
    {
    public:
        using Base = Bind;
    protected:
        DescriptorBaseBind( ) noexcept
            : Base( )
        { }

        DescriptorBaseBind( const OCI::Statement& statement )
            : Base( statement )
        { }

        DescriptorBaseBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        { }

        DescriptorBaseBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        { }

        HO_EXPORT void* DescriptorAlloc( OCI::HandleType handleType );
        HO_EXPORT void DescriptorFree( void* handle, OCI::HandleType handleType );
        
    };

    /// <summary>
    /// DescriptorArrayBaseBind
    /// </summary>
    class DescriptorArrayBaseBind : public ArrayBind
    {
    public:
        using Base = ArrayBind;
    protected:
        DescriptorArrayBaseBind( ) noexcept
            : Base( )
        {
        }

        DescriptorArrayBaseBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        DescriptorArrayBaseBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }

        DescriptorArrayBaseBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

        HO_EXPORT void* DescriptorAlloc( OCI::HandleType handleType );
        HO_EXPORT void DescriptorFree( void* handle, OCI::HandleType handleType );

    };


    /// <summary>
    /// DescriptorBind
    /// </summary>
    /// <typeparam name="OracleT"></typeparam>
    template <typename OracleT, OCI::HandleType handleType, OCI::OraType externalType >
    class DescriptorBind : public DescriptorBaseBind
    {
    public:
        using Base = DescriptorBaseBind;
        using OracleType = OracleT;
        static constexpr OCI::HandleType HandleType = handleType;
        static constexpr OCI::OraType ExternalType = externalType;
    protected:
        OracleType* data_;
    public:
        DescriptorBind( ) noexcept
            : Base( ), data_( nullptr )
        {
        }

        DescriptorBind( const OCI::Statement& statement )
            : Base( statement ), data_( reinterpret_cast<OracleType*>( DescriptorAlloc( HandleType ) ) )
        { 
        }
        DescriptorBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), data_( reinterpret_cast<OracleType*>( DescriptorAlloc( HandleType ) ) )
        {
        }
        DescriptorBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), data_( reinterpret_cast<OracleType*>( DescriptorAlloc( HandleType ) ) )
        {
        }
        ~DescriptorBind( )
        {
            if ( data_ )
            {
                DescriptorFree( data_, HandleType );
            }
        }

        void Bind( UInt32 positon, UInt32 iters ) final override
        {
            SimpleBindByPos( positon, ExternalType, &data_, sizeof( data_ ) );
        }

        void Bind( const WideString& name, UInt32 iters ) final override
        {
            SimpleBindByName( name, ExternalType, &data_, sizeof( data_ ) );
        }

        void* Data( ) const final override
        {
            return (void*)&data_;
        }
    };


    /// <summary>
    /// DescriptorArrayBind
    /// </summary>
    /// <typeparam name="OracleT"></typeparam>
    template <typename OracleT, OCI::HandleType handleType, OCI::OraType externalType >
    class DescriptorArrayBind : public DescriptorArrayBaseBind
    {
    public:
        using Base = DescriptorArrayBaseBind;
        using OracleType = OracleT;
        static constexpr OCI::HandleType HandleType = handleType;
        static constexpr OCI::OraType ExternalType = externalType;
    protected:
        std::vector<OracleType*> data_;
        UInt32 actualSize_;
    public:
        DescriptorArrayBind( ) noexcept
            : Base( ), actualSize_(0)
        {
        }

        DescriptorArrayBind( const OCI::Statement& statement )
            : Base( statement ), actualSize_( 0 )
        {
        }
        DescriptorArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), actualSize_( 0 )
        {
        }
        DescriptorArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), actualSize_( 0 )
        {
        }
        ~DescriptorArrayBind( )
        {
            for ( OracleType* handle : data_ )
            {
                DescriptorFree( handle, HandleType );
            }
        }

        void Bind( UInt32 positon, UInt32 iters ) final override
        {
            auto dataSize = data_.size( );
            actualSize_ = static_cast<UInt32>( dataSize );
            if ( indicator_.size( ) < dataSize )
            {
                indicator_.resize( dataSize );
            }
            if ( IsPlSQL( ) == false )
            {
                Base::BindByPos( positon, ExternalType, data_.data( ), sizeof( OracleType* ), indicator_.data( ), nullptr, nullptr, 0, nullptr );
            }
            else
            {
                SimpleBindByPos( positon, ExternalType, data_.data( ), sizeof( OracleType* ), actualSize_, &actualSize_ );
            }
        }

        void Bind( const WideString& name, UInt32 iters ) final override
        {
            SimpleBindByName( name, ExternalType, &data_, sizeof( data_ ), actualSize_, &actualSize_ );
        }

        void* Data( ) const
        {
            return (void*)data_.data( );
        }

        void resize( size_t newSize )
        {
            Base::resize( newSize );
            if ( data_.size( ) == 0 )
            {
                if ( newSize )
                {
                    data_.resize( newSize );
                    for ( size_t i = 0; i < newSize; i++ )
                    {
                        data_[i] = reinterpret_cast<OracleType*>(DescriptorAlloc( HandleType ));
                    }
                }
            }
            else
            {
                if ( newSize > data_.size( ) )
                {
                    auto oldSize = data_.size( );
                    data_.resize( newSize );
                    for ( size_t i = oldSize; i < newSize; i++ )
                    {
                        data_[i] = reinterpret_cast<OracleType*>( DescriptorAlloc( HandleType ) );
                    }
                }
                else if ( newSize < data_.size( ) )
                {
                    auto oldSize = data_.size( );
                    for ( size_t i = newSize; i < oldSize; i++ )
                    {
                        DescriptorFree( data_[i], HandleType );
                    }
                    data_.resize( newSize );
                }
            }
            actualSize_ = static_cast<UInt32>(data_.size( ));
        }


    };


    /// <summary>
    /// TimeStampBaseBind
    /// </summary>
    template<OCI::HandleType handleType, OCI::OraType externalType>
    class TimestampBaseBind : public DescriptorBind<OCIDateTime, handleType, externalType>
    {
    public:
        using Base = DescriptorBind<OCIDateTime, handleType, externalType>;
        using Base::Environment;
        using Base::Statement;
        using Base::Error;
    protected:
        using Base::data_;
        
    public:
        TimestampBaseBind( ) noexcept
            : Base( )
        {
        }

        TimestampBaseBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        TimestampBaseBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }
        TimestampBaseBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

        void GetTime( Byte& hour, Byte& minute, Byte& second, UInt32& fractionalSecond ) const
        {
            auto& environment = Environment( );
            auto& error = Base::Statement( ).Error( );
            DateTimeGetTime( environment, error, data_, &hour, &minute, &second, &fractionalSecond );
        }

        void GetDate( Int16& year, Byte& month, Byte& day ) const
        {
            auto& environment = Environment( );
            auto& error = Base::Statement( ).Error( );
            DateTimeGetDate( environment, error, data_, &year, &month, &day );
        }

        void GetDateTime( Int16& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second, UInt32& fractionalSecond ) const
        {
            auto& environment = Environment( );
            auto& error = Base::Statement( ).Error( );

            DateTimeGetDate( environment, error, data_, &year, &month, &day );
            DateTimeGetTime( environment, error, data_, &hour, &minute, &second, &fractionalSecond );
        }
        void SetDateTime( Int16 year, Byte month, Byte day, Byte hour, Byte minute, Byte second, UInt32 fractionalSecond, const wchar_t* langName = nullptr, size_t langLength = 0 )
        {
            auto& environment = Environment( );
            auto& error = Base::Statement( ).Error( );

            DateTimeConstruct( environment, error, data_, year, month, day, hour, minute, second, fractionalSecond, langName, langLength );
        }

        void SetDateTime( Int16 year, Byte month, Byte day, Byte hour, Byte minute, Byte second, UInt32 fractionalSecond, const WideString& langName )
        {
            SetDateTime( year, month, day, hour, minute, second, fractionalSecond, langName.c_str( ), langName.length( ) * sizeof( wchar_t ) );
        }


        Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( AsDateTime( ) );
        }
        void Assign( Int32 newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }
        UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( AsDateTime( ) );
        }
        void Assign( UInt32 newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }
        Int64 AsInt64( ) const final override
        {
            return ConvertTo<Int64>( AsDateTime( ) );
        }
        void Assign( Int64 newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }
        UInt64 AsUInt64( ) const final override
        {
            return ConvertTo<UInt64>( AsDateTime( ) );
        }
        void Assign( UInt64 newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }
        float AsSingle( ) const final override
        {
            return ConvertTo<Single>( AsDateTime( ) );
        }
        void Assign( float newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }
        double AsDouble( ) const final override
        {
            return ConvertTo<Double>( AsDateTime( ) );
        }
        void Assign( double newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }

        DateTime AsDateTime( ) const final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTime result;
            DateTimeGetDateTime( environment, error, data_, result );
            return result;
        }
        void Assign( const DateTime& newValue ) final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeConstruct( environment, error, data_, newValue );
            Base::SetDBNotNull( );
        }
        TimeSpan AsTimeSpan( ) const final override
        {
            return ConvertTo<TimeSpan>( AsDateTime( ) );
        }
        void Assign( const TimeSpan& newValue ) final override
        {
            Assign( ConvertTo<DateTime>( newValue ) );
        }
        WideString AsString( const WideString& format ) const
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            return DateTimeToText( environment, error, data_, format );
        }
        WideString AsString( ) const final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            return DateTimeToText( environment, error, data_ );
        }
        void Assign( const WideString& newValue ) final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeFromText( environment, error, newValue, data_ );
            Base::SetDBNotNull( );
        }
        void Assign( const WideString& format, const WideString& newValue )
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeFromText( environment, error, newValue, format, data_ );
            Base::SetDBNotNull( );
        }
    };


    template<OCI::HandleType handleType, OCI::OraType externalType>
    class TimestampBaseArrayBind : public DescriptorArrayBind<OCIDateTime, handleType, externalType>
    {
    public:
        using Base = DescriptorArrayBind<OCIDateTime, handleType, externalType>;
        using Base::Environment;
        using Base::Statement;
        using Base::Error;
    protected:
        using Base::data_;

    public:
        TimestampBaseArrayBind( ) noexcept
            : Base( )
        {
        }

        TimestampBaseArrayBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        TimestampBaseArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }
        TimestampBaseArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

        void GetTime( size_t index, Byte& hour, Byte& minute, Byte& second, UInt32& fractionalSecond ) const
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );
            DateTimeGetTime( environment, error, data_[index], &hour, &minute, &second, &fractionalSecond );
        }

        void GetDate( size_t index, Int16& year, Byte& month, Byte& day ) const
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );
            DateTimeGetDate( environment, error, data_[index], &year, &month, &day );
        }

        void GetDateTime( size_t index, Int16& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second, UInt32& fractionalSecond ) const
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeGetDate( environment, error, data_[index], &year, &month, &day );
            DateTimeGetTime( environment, error, data_[index], &hour, &minute, &second, &fractionalSecond );
        }
        void SetDateTime( size_t index, Int16 year, Byte month, Byte day, Byte hour, Byte minute, Byte second, UInt32 fractionalSecond, const wchar_t* langName = nullptr, size_t langLength = 0 )
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeConstruct( environment, error, data_[index], year, month, day, hour, minute, second, fractionalSecond, langName, langLength );
        }

        void SetDateTime( size_t index, Int16 year, Byte month, Byte day, Byte hour, Byte minute, Byte second, UInt32 fractionalSecond, const WideString& langName )
        {
            SetDateTime( index ,year, month, day, hour, minute, second, fractionalSecond, langName.c_str( ), langName.length( ) * sizeof( wchar_t ) );
        }


        Int32 AsInt32( size_t index ) const final override
        {
            return ConvertTo<Int32>( AsDateTime( index ) );
        }
        void Assign( size_t index, Int32 newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }
        UInt32 AsUInt32( size_t index ) const final override
        {
            return ConvertTo<UInt32>( AsDateTime( index ) );
        }
        void Assign( size_t index, UInt32 newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }
        Int64 AsInt64( size_t index ) const final override
        {
            return ConvertTo<Int64>( AsDateTime( index ) );
        }
        void Assign( size_t index, Int64 newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }
        UInt64 AsUInt64( size_t index ) const final override
        {
            return ConvertTo<UInt64>( AsDateTime( index ) );
        }
        void Assign( size_t index, UInt64 newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }
        float AsSingle( size_t index ) const final override
        {
            return ConvertTo<Single>( AsDateTime( index ) );
        }
        void Assign( size_t index, float newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }
        double AsDouble( size_t index ) const final override
        {
            return ConvertTo<Double>( AsDateTime( index ) );
        }
        void Assign( size_t index, double newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }

        DateTime AsDateTime( size_t index ) const final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTime result;
            DateTimeGetDateTime( environment, error, data_[index], result );
            return result;
        }
        void Assign( size_t index, const DateTime& newValue ) final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeConstruct( environment, error, data_[index], newValue );
        }

        void Assign( const std::vector<DateTime>& newValues )
        {
            Base::resize( newValues.size( ) );
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );
            for ( size_t i = 0; i < newValues.size( ); ++i )
            {
                DateTimeConstruct( environment, error, data_[i], newValues[i] );
                Base::SetDBNotNull( i );
            }
        }

        TimeSpan AsTimeSpan( size_t index ) const final override
        {
            return ConvertTo<TimeSpan>( AsDateTime( index ) );
        }
        void Assign( size_t index, const TimeSpan& newValue ) final override
        {
            Assign( index, ConvertTo<DateTime>( newValue ) );
        }
        WideString AsString( size_t index, const WideString& format ) const
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            return DateTimeToText( environment, error, data_[index], format );
        }
        WideString AsString( size_t index ) const final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            return DateTimeToText( environment, error, data_[index] );
        }
        void Assign( size_t index, const WideString& newValue ) final override
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeFromText( environment, error, newValue, data_[index] );
        }
        void Assign( size_t index, const WideString& format, const WideString& newValue )
        {
            auto& environment = Environment( );
            auto& error = Statement( ).Error( );

            DateTimeFromText( environment, error, newValue, format, data_[index] );
        }
    };


    


    /// <summary>
    /// FixedBinaryBind
    /// </summary>
    template<size_t size_>
    class FixedBinaryBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::BIN;
        using BoundType = std::array<Byte, size_>;
    protected:
        BoundType data_;
    public:
        constexpr FixedBinaryBind( ) noexcept
            : Base( ), data_{}
        {
        }

        FixedBinaryBind( const OCI::Statement& statement )
            : Base( statement ), data_{}
        {
        }

        FixedBinaryBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), data_{}
        {
        }

        FixedBinaryBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), data_{}
        {
        }
    protected:
        virtual void Bind( UInt32 positon, UInt32 iters ) override
        {
            SimpleBindByPos( positon, ExternalType, data_.data( ), static_cast<Int32>( size_ ) );
        }
        virtual void Bind( const WideString& name, UInt32 iters ) override
        {
            SimpleBindByName( name, ExternalType, data_.data( ), static_cast<Int32>( size_ ) );
        }
    };

    /// <summary>
    /// FixedBinaryArrayBind
    /// </summary>
    template<size_t size_>
    class FixedBinaryArrayBind : public ArrayBind
    {
        using Base = ArrayBind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::BIN;
        using BoundType = std::array<Byte, size_>;
    protected:
        std::vector<BoundType> data_;
        UInt32 actualSize_;
    public:
        constexpr FixedBinaryArrayBind( ) noexcept
            : Base( )
        {
        }

        FixedBinaryArrayBind( const OCI::Statement& statement )
            : Base( statement ), actualSize_(0)
        {
        }

        FixedBinaryArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), actualSize_( 0 )
        {
        }

        FixedBinaryArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), actualSize_( 0 )
        {
        }
    protected:
        virtual void Bind( UInt32 positon, UInt32 iters ) override
        {
            auto dataSize = data_.size( );
            actualSize_ = static_cast<UInt32>( dataSize );
            if ( indicator_.size( ) < dataSize )
            {
                indicator_.resize( dataSize );
            }
            if ( IsPlSQL( ) == false )
            {
                Base::BindByPos( positon, ExternalType, data_.data( ), static_cast<Int32>( size_ ), indicator_.data( ), nullptr, nullptr, 0, nullptr );
            }
            else
            {
                SimpleBindByPos( positon, ExternalType, data_.data( ), static_cast<Int32>( size_ ), actualSize_, &actualSize_ );
            }
        }
        virtual void Bind( const WideString& name, UInt32 iters ) override
        {
            auto dataSize = data_.size( );
            actualSize_ = static_cast<UInt32>( dataSize );
            if ( indicator_.size( ) < dataSize )
            {
                indicator_.resize( dataSize );
            }
            SimpleBindByName( name, ExternalType, data_.data( ), static_cast<Int32>( size_ ), actualSize_, &actualSize_ );
        }
    };


    /// <summary>
    /// GuidBind
    /// </summary>
    class GuidBind : public FixedBinaryBind<sizeof( Guid )>
    {
        using Base = FixedBinaryBind<sizeof( Guid )>;
    public:
        constexpr GuidBind( ) noexcept
            : Base( )
        {
        }

        GuidBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        GuidBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }

        GuidBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

        virtual Guid AsGuid( ) const override
        {
            Guid result( data_ );
            return result;
        }

        virtual void Assign( const Guid& newValue ) override
        {
            data_ = newValue.ToBytes( );
            indicator_ = 0;
        }

        virtual WideString AsString( ) const override
        {
            return AsGuid( ).ToString( );
        }

        virtual void Assign( const WideString& newValue ) override
        {
            Guid guid( newValue );
            Assign( guid );
        }
    };

    /// <summary>
    /// GuidArrayBind
    /// </summary>
    class GuidArrayBind : public FixedBinaryArrayBind<sizeof(Guid)>
    {
        using Base = FixedBinaryArrayBind<sizeof(Guid)>;
    public:
        constexpr GuidArrayBind( ) noexcept
            : Base( )
        {
        }

        GuidArrayBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        GuidArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
            
        }

        GuidArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
            
        }

        void reserve( size_t size )
        {
            data_.reserve( size );
            indicator_.reserve( size );
        }

        void push_back( const Guid& value )
        {
            data_.push_back( value.ToBytes( ) );
            if ( value.IsEmpty( ) == false )
            {
                indicator_.push_back( 0 );
            }
            else
            {
                indicator_.push_back( -1 );
            }
        }

        void push_back( nullptr_t )
        {
            data_.push_back( std::array<Byte, 16>{} );
            indicator_.push_back( -1 );
        }


        virtual Guid AsGuid( size_t index ) const override
        {
            //Guid* ptr = ( Guid* )data_[index].data( );
            //return *ptr;
            Guid result( data_[index] );
            return result;
        }

        virtual void Assign( size_t index, const Guid& newValue ) override
        {
            //Guid* ptr = ( Guid* )data_[index].data( );
            //*ptr = newValue;
            data_[index] = newValue.ToBytes( );
        }

        virtual WideString AsString( size_t index ) const override
        {
            return AsGuid( index ).ToString( );
        }

        virtual void Assign( size_t index, const WideString& newValue ) override
        {
            Guid guid( newValue );
            Assign( index, guid );
        }
    };

    /// <summary>
    /// LobStream
    /// </summary>
    class LobStream
    {
        const OCI::ServiceContext* serviceContext_;
        OCILobLocator* locator_;
        Int64 position_;
    public:
        LobStream( const OCI::ServiceContext& serviceContext, OCILobLocator* lobLocator )
            : serviceContext_( &serviceContext ), locator_( lobLocator ), position_( 0 )
        { }

        OCILobLocator* Handle( ) const
        {
            return locator_;
        }

        const OCI::ServiceContext& ServiceContext( ) const
        {
            return *serviceContext_;
        }
        const OCI::ErrorHandle& Error( ) const noexcept
        {
            return serviceContext_->Error( );
        }
    public:
        constexpr Int64 Position( ) const noexcept
        {
            return position_;
        }
        constexpr void SetPosition( Int64 position ) noexcept
        {
            position_ = position;
        }

        Int64 Size( ) const
        {
            auto& serviceContext = ServiceContext( );
            auto& error = Error( );
            UInt64 result = 0;
            LobGetLength2( serviceContext, error, Handle( ), &result );
            return result;
        }
        void SetSize( Int64 size )
        {
            auto& serviceContext = ServiceContext( );
            auto& error = Error( );
            LobTrim2( serviceContext, error, Handle( ), size );
        }

        void Flush( )
        {
            auto& serviceContext = ServiceContext( );
            auto& error = Error( );
            LobFlushBuffer( serviceContext, error, Handle( ), 0 );
        }

        constexpr bool CanRead( ) const noexcept
        {
            return true;
        }

        constexpr bool CanSeek( ) const noexcept
        {
            return true;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return true;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            return true;
        }

        Int64 Read( void* buffer, size_t numberOfBytesToRead )
        {
            auto& serviceContext = ServiceContext( );
            auto& error = Error( );
            auto numberOfBytesRead = LobRead( serviceContext, error, Handle( ), position_, buffer, numberOfBytesToRead );
            position_ += numberOfBytesRead;
            return numberOfBytesRead;
        }
        Int64 Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            auto& serviceContext = ServiceContext( );
            auto& error = Error( );
            auto numberOfBytesWritten = LobWrite( serviceContext, error, Handle( ), position_, buffer, numberOfBytesToWrite );
            position_ += numberOfBytesWritten;
            return numberOfBytesWritten;
        }
        Int64 Seek( Int64 offset, IO::SeekOrigin seekOrigin )
        {
            long long newPosition = 0;
            switch ( seekOrigin )
            {
                case IO::SeekOrigin::StartOfFile:
                {
                    if ( offset > 0 )
                    {
                        newPosition = offset;
                    }
                }
                break;
                case IO::SeekOrigin::CurrentPosition:
                {
                    newPosition = position_ + offset;
                }
                break;
                case IO::SeekOrigin::EndOfFile:
                {
                    auto size = Size( );
                    newPosition = size + offset;
                }
                break;
            }
            if ( newPosition < 0 )
            {
                newPosition = 0;
            }
            position_ = newPosition;
            return newPosition;
        }
    };


    /// <summary>
    /// LobBaseBind
    /// </summary>
    template<OCI::OraType externalType>
    class LobBaseBind : public DescriptorBind<OCILobLocator, OCI::HandleType::LOB, externalType>
    {
    public:
        using Base = DescriptorBind<OCILobLocator, OCI::HandleType::LOB, externalType>;
        using Base::Environment;
        using Base::Error;
    protected:
        using Base::data_;

    public:
        LobBaseBind( ) noexcept
            : Base( )
        {
        }

        LobBaseBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        LobBaseBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }
        LobBaseBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

        UInt64 Length( ) const
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return LobGetLength2( serviceContext, error, data_ );
        }
    protected:
        


    };

    /// <summary>
    /// CLobBaseBind
    /// </summary>
    template<OCI::OraType externalType, CharacterSetForm characterSetFormDefault >
    class CLobBaseBind : public LobBaseBind<externalType>
    {
    public:
        using Base = LobBaseBind<externalType>;
        using Base::Environment;
        using Base::Error;
        static constexpr CharacterSetForm CharacterSetFormDefault = characterSetFormDefault;
    protected:
        using Base::data_;

    public:
        CLobBaseBind( ) noexcept
            : Base( )
        {
        }

        CLobBaseBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        CLobBaseBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }
        CLobBaseBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }


        virtual WideString AsString( ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return LobReadWideString( serviceContext, error, data_, CharacterSetFormDefault );
        }

        virtual void Assign( const WideString& newValue ) override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            LobWriteWideString( serviceContext, error, newValue, CharacterSetFormDefault, data_ );
            Base::SetDBNotNull( );
        }
    };

    using CLobBind = CLobBaseBind<OCI::OraType::CLOB, CharacterSetForm::Implicit>;
    using NCLobBind = CLobBaseBind<OCI::OraType::CLOB, CharacterSetForm::NChar>;



    /// <summary>
    /// LobBaseArrayBind
    /// </summary>
    template<OCI::OraType externalType>
    class LobBaseArrayBind : public DescriptorArrayBind<OCILobLocator, OCI::HandleType::LOB, externalType>
    {
    public:
        using Base = DescriptorArrayBind<OCILobLocator, OCI::HandleType::LOB, externalType>;
        using Base::Environment;
        using Base::Error;
    protected:
        using Base::data_;

    public:
        LobBaseArrayBind( ) noexcept
            : Base( )
        {
        }

        LobBaseArrayBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        LobBaseArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }
        LobBaseArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }

    };

    /// <summary>
    /// CLobBaseBind
    /// </summary>
    template<OCI::OraType externalType, CharacterSetForm characterSetFormDefault >
    class CLobBaseArrayBind : public LobBaseArrayBind<externalType>
    {
    public:
        using Base = LobBaseArrayBind<externalType>;
        using Base::Environment;
        using Base::Error;
        static constexpr CharacterSetForm CharacterSetFormDefault = characterSetFormDefault;
    protected:
        using Base::data_;

    public:
        CLobBaseArrayBind( ) noexcept
            : Base( )
        {
        }

        CLobBaseArrayBind( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        CLobBaseArrayBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position )
        {
        }
        CLobBaseArrayBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name )
        {
        }


        virtual WideString AsString( size_t index ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return LobReadWideString( serviceContext, error, data_[index], CharacterSetFormDefault );
        }

        virtual void Assign( size_t index, const WideString& newValue ) final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            LobWriteWideString( serviceContext, error, newValue, CharacterSetFormDefault, data_[index] );
            Base::SetDBNotNull( index );
        }
    };

    using CLobArrayBind = CLobBaseArrayBind<OCI::OraType::CLOB, CharacterSetForm::Implicit>;
    using NCLobArrayBind = CLobBaseArrayBind<OCI::OraType::CLOB, CharacterSetForm::NChar>;


    /// <summary>
    /// BlobBind
    /// </summary>
    class BlobBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::BLOB;
        using BoundType = OCILobLocator*;
    protected:
        BoundType data_;
    public:
        BlobBind( ) noexcept
            : Base( ), data_(nullptr)
        {
        }

        HO_EXPORT BlobBind( const OCI::Statement& statement );
        HO_EXPORT BlobBind( const OCI::Statement& statement, UInt32 position );
        HO_EXPORT BlobBind( const OCI::Statement& statement, const WideString& name );
        HO_EXPORT ~BlobBind( );

    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters );
    public:
    };

    /// <summary>
    /// BinaryBind
    /// </summary>
    class BinaryBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::BIN;
    private:
        UInt32 size_;
        Byte* data_;
    public:
        BinaryBind( ) noexcept
            : Base( ), size_(0), data_( nullptr )
        {
        }

        BinaryBind( const OCI::Statement& statement )
            : Base( statement ), size_( 0 ), data_( nullptr )
        { }
        BinaryBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), size_( 0 ), data_( nullptr )
        { }
        BinaryBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), size_( 0 ), data_( nullptr )
        { }
        HO_EXPORT ~BinaryBind( );

    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters );
    public:
        HO_EXPORT size_t Size( ) const;
        HO_EXPORT void*  Data( ) const;
        HO_EXPORT void Resize( size_t newSize );
        HO_EXPORT void Write( const IO::MemoryStream& stream );
        HO_EXPORT void Write( void* data, size_t dataSize );
    };


    /// <summary>
    /// LargeBinaryRefBind
    /// </summary>
    class LargeBinaryRefBind : public Bind
    {
        using Base = Bind;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::LBI;
    private:
        UInt32 size_;
        const Byte* data_;
    public:
        LargeBinaryRefBind( ) noexcept
            : Base( ), size_( 0 ), data_( nullptr )
        {
        }

        LargeBinaryRefBind( const OCI::Statement& statement )
            : Base( statement ), size_( 0 ), data_( nullptr )
        {
        }
        LargeBinaryRefBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), size_( 0 ), data_( nullptr )
        {
        }
        LargeBinaryRefBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), size_( 0 ), data_( nullptr )
        {
        }
        

    protected:
        virtual void Bind( UInt32 positon, UInt32 iters ) override
        {
            SimpleBindByPos( positon, ExternalType, Data( ), size_ );
        }
        virtual void Bind( const WideString& name, UInt32 iters ) override
        {
            SimpleBindByName( name, ExternalType, Data( ), size_ );
        }
    public:
        size_t Size( ) const
        {
            return size_;
        }
        void* Data( ) const override
        {
            return const_cast<Byte*>(data_);
        }
        void Assign( const Byte* data, UInt32 size )
        {
            data_ = data;
            size_ = size;
            indicator_ = 0;
        }
    };



    /// <summary>
    /// BinaryDynamicBind
    /// </summary>
    class BinaryDynamicBind : public DynamicBind
    {
        using Base = DynamicBind;
    public:
        struct Info
        {
            size_t position_;
            size_t bufferSize_;
            const Byte* buffer_;

            Info()
                : position_( 0 ), bufferSize_( 0 ), buffer_( nullptr )
            { }

            Info( const Byte* buffer, size_t bufferSize )
                : position_( 0 ), bufferSize_( bufferSize ), buffer_( buffer )
            {
            }
        };

    private:
        size_t blockSize_;
        std::vector<Info> data_;
    public:
        static constexpr OCI::OraType ExternalType = OCI::OraType::LBI;

        BinaryDynamicBind( ) noexcept
            : Base( ), blockSize_( 0 )
        {
        }

        BinaryDynamicBind( const OCI::Statement& statement )
            : Base( statement ), blockSize_( 4096 )
        { }
        BinaryDynamicBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), blockSize_( 4096 )
        { }
        BinaryDynamicBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), blockSize_( 4096 )
        { }
        HO_EXPORT ~BinaryDynamicBind( );

        void reserve( size_t numberOfElements )
        {
            data_.reserve( numberOfElements );
        }

        void push_back( const void* buffer, size_t bufferSize )
        {
            data_.push_back( Info( static_cast<const Byte*>(buffer), bufferSize ) );
        }

    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters );
        HO_EXPORT virtual Int32 HandleInData( UInt32 iter, UInt32 index, void **bufpp, UInt32 *alenpp, Byte* piecep, void **indpp );
    public:

    };



    /// <summary>
    /// RefCursorBind
    /// </summary>
    class RefCursorBind : public Bind
    {
        using Base = Bind;
        void* boundStatementhandle_;
        OCI::Statement cursorStatement_;
    public:
        RefCursorBind( ) noexcept
            : Base( ), boundStatementhandle_(nullptr)
        {
        }

        RefCursorBind( const OCI::Statement& statement )
            : Base( statement ), boundStatementhandle_( nullptr )
        { }
        RefCursorBind( const OCI::Statement& statement, UInt32 position )
            : Base( statement, position ), boundStatementhandle_( nullptr )
        { }
        RefCursorBind( const OCI::Statement& statement, const WideString& name )
            : Base( statement, name ), boundStatementhandle_( nullptr )
        { }
        HO_EXPORT ~RefCursorBind( );
    protected:
        HO_EXPORT virtual void Bind( UInt32 positon, UInt32 iters ) override;
        HO_EXPORT virtual void Bind( const WideString& name, UInt32 iters );
    public:
        HO_EXPORT const OCI::Statement& CursorStatement( );

        template< typename RT > 
        RT CreateReader( size_t size )
        {
            auto& cursorStatement = CursorStatement( );
            RT reader( cursorStatement, size );
            reader.InitializeDefines( );
            return reader;
        }
    };


    namespace Internal
    {
        template<typename Arg, typename ...OtherArgsTypes>
        void BindArgs( OCI::Statement& statement, UInt32 position, 
            const Arg& arg, OtherArgsTypes&& ...otherArgsTypes )
        {
            if constexpr ( IsAnyOf_v<Arg, WideString, std::wstring> )
            {
                auto newBind = statement.Bind<Arg>( position, arg.length( ) );
                newBind->Assign( arg );
            }
            else if constexpr ( IsSpecializationOf<Arg, std::optional> )
            {
                using BintT = typename Arg::value_type;
                if ( arg.has_value( ) )
                {
                    if constexpr ( IsAnyOf_v< BintT, WideString, std::wstring> )
                    {
                        auto newBind = statement.Bind<BintT>( position, arg.value( ).length( ) );
                        newBind->Assign( arg.value() );
                    }
                    else
                    {
                        auto newBind = statement.Bind<BintT>( position );
                        newBind->Assign( arg.value( ) );
                    }
                }
                else
                {
                    if constexpr ( IsAnyOf_v<BintT, WideString, std::wstring> )
                    {
                        auto newBind = statement.Bind<BintT>( position, static_cast<size_t>(0) );
                        newBind->SetDBNull( );
                    }
                    else
                    {
                        auto newBind = statement.Bind<BintT>( position );
                        newBind->SetDBNull( );
                    }
                }
            }
            else
            {
                auto newBind = statement.Bind<Arg>( position );
                newBind->Assign( arg );
            }
            if constexpr ( sizeof...( otherArgsTypes ) > 0 )
            {
                BindArgs( statement, position + 1, std::forward<OtherArgsTypes>( otherArgsTypes )... );
            }
        }
    }

    inline OCI::Statement ServiceContext::CreateStatement( const wchar_t* sql ) const
    {
        auto sqlLength = LengthOf( sql );
        return CreateStatement( sql, sqlLength );
    }


    template<WideStringLike StringT, typename ...BindableTypes>
        requires ( sizeof...( BindableTypes ) > 0 )
    inline OCI::Statement ServiceContext::CreateStatement( const StringT& sql,
        BindableTypes&& ...bindableArgs ) const
    {
        auto result = CreateStatement( sql );
        Internal::BindArgs( result, 1, 
            std::forward<BindableTypes>( bindableArgs )... );
        return result;
    }

    /// <summary>
    /// DefineBase, base class for all defines
    /// </summary>
    class DefineBase : public HandleBase
    {
        using Base = HandleBase;

        OCI::Statement *statement_;
    protected:
        DefineBase( const OCI::Statement& statement )
            : Base( OCI::HandleType::Define, nullptr, false ), statement_( const_cast<OCI::Statement*>(&statement) )
        {
            
        }
        constexpr DefineBase( ) noexcept
            : Base( ), statement_( nullptr )
        {
        }

    public:
        

        HO_EXPORT void DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32 *returnLengths = nullptr, UInt16 *returnCodes = nullptr, UInt32 mode = 0 );
    public:
        virtual void Initialize( UInt32 positon ) = 0;

        const OCI::Statement& Statement( ) const noexcept
        {
            return *statement_;
        }

        const OCI::ErrorHandle & Error( ) const noexcept final override
        {
            return statement_->Error();
        }


        const OCI::ServiceContext& ServiceContext( ) const
        {
            return statement_->ServiceContext( );
        }

        const OCI::Environment& Environment( ) const
        {
            return statement_->Environment( );
        }

       
        HO_EXPORT void SetLOBPrefetchSize( UInt32 lobPrefetchSize );
        HO_EXPORT UInt32 LOBPrefetchSize( ) const;

       
        HO_EXPORT void SetLOBPrefetchLength( bool value = true );
        HO_EXPORT bool LOBPrefetchLength( ) const;

    };


    /// <summary>
    /// Define, base class for defines for use with the DataReader class
    /// </summary>
    class Define : public DefineBase
    {
        using Base = DefineBase;
        friend class DataReader;

    protected:
        Int16 indicator_;
    protected:
        constexpr Define( ) noexcept
            : Base( ), indicator_( -1 )
        {
        }

        Define( const OCI::Statement& statement )
            : Base( statement ), indicator_( -1 )
        { }

        void DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32 *returnLengths = nullptr, UInt16 *returnCodes = nullptr, UInt32 mode = 0 )
        {
            Base::DefineByPos( positon, dataType, dataAddress, dataSize, indicators, returnLengths, returnCodes, mode );
        }
        HO_EXPORT void DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, UInt32* rowLengths = nullptr, UInt16* rowReturnCodes = nullptr, UInt32 mode = 0 );
    public:
        virtual void Initialize( UInt32 positon )
        {
            HCC_THROW( NotImplementedException );
        }

        constexpr Int16 Indicator( ) const noexcept
        {
            return indicator_;
        }


        HO_EXPORT static std::unique_ptr<Define> CreateDefine( const OCI::Statement& statement, const ColumnDescriptor& columnDescriptor, UInt32 positon );

        virtual const void* Data( ) const noexcept = 0;

        //HO_EXPORT virtual void WriteTo( IO::BinaryWriter& writer ) const;
        //HO_EXPORT virtual void WriteNullableTo( IO::BinaryWriter& writer ) const;

        HO_EXPORT virtual bool AsBoolean( ) const;
        HO_EXPORT virtual Byte AsByte( ) const;
        HO_EXPORT virtual std::vector<Byte> AsBytes( ) const;
        HO_EXPORT virtual SByte AsSByte( ) const;
        HO_EXPORT virtual Int16 AsInt16( ) const;
        HO_EXPORT virtual UInt16 AsUInt16( ) const;
        HO_EXPORT virtual Int32 AsInt32( ) const;
        HO_EXPORT virtual UInt32 AsUInt32( ) const;
        HO_EXPORT virtual Int64 AsInt64( ) const;
        HO_EXPORT virtual UInt64 AsUInt64( ) const;
        HO_EXPORT virtual float AsSingle( ) const;
        HO_EXPORT virtual double AsDouble( ) const;
        HO_EXPORT virtual DateTime AsDateTime( ) const;
        HO_EXPORT virtual TimeSpan AsTimeSpan( ) const;
        HO_EXPORT virtual WideString AsString( ) const;
        HO_EXPORT virtual Guid AsGuid( ) const;
        HO_EXPORT virtual OCI::Object* AsObject( ) const;
        HO_EXPORT virtual OCI::Collection* AsCollection( ) const;
        HO_EXPORT virtual LobStream AsStream( ) const;
    };

    /// <summary>
    /// ArrayDefine, base class for defines for use with the ArrayDataReader class
    /// </summary>
    class ArrayDefine : public DefineBase
    {
        using Base = DefineBase;

        friend class ArrayDataReader;

    protected:
        std::vector<Int16> indicator_;
    protected:
        ArrayDefine( ) noexcept
            : Base( )
        {
        }

        ArrayDefine( const OCI::Statement& statement, size_t arraySize )
            : Base( statement )
        {
            indicator_.resize( arraySize );
        }

        void DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32 *returnLengths, UInt16 *returnCodes, UInt32 mode )
        {
            Base::DefineByPos( positon, dataType, dataAddress, dataSize, indicators, returnLengths, returnCodes, mode );
        }
        HO_EXPORT void DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, UInt32 *returnLengths = nullptr, UInt16 *returnCodes = nullptr, UInt32 mode = 0 );

    public:
        size_t Count( ) const
        {
            return indicator_.size( );
        }
    
        Int16 Indicator( size_t index ) const
        {
            return indicator_[index];
        }

        HO_EXPORT static std::unique_ptr<ArrayDefine> CreateDefine( const OCI::Statement& statement, size_t defineSize, const ColumnDescriptor& columnDescriptor, UInt32 positon );


        virtual const void* Data( size_t index ) const noexcept = 0;

        //HO_EXPORT virtual void WriteTo( size_t index, IO::BinaryWriter& writer ) const;
        //HO_EXPORT virtual void WriteNullableTo( size_t index, IO::BinaryWriter& writer ) const;

        HO_EXPORT virtual bool AsBoolean( size_t index ) const;
        HO_EXPORT virtual Byte AsByte( size_t index ) const;
        HO_EXPORT virtual SByte AsSByte( size_t index ) const;
        HO_EXPORT virtual std::vector<Byte> AsBytes( size_t index ) const;
        HO_EXPORT virtual Int16 AsInt16( size_t index ) const;
        HO_EXPORT virtual UInt16 AsUInt16( size_t index ) const;
        HO_EXPORT virtual Int32 AsInt32( size_t index ) const;
        HO_EXPORT virtual UInt32 AsUInt32( size_t index ) const;
        HO_EXPORT virtual Int64 AsInt64( size_t index ) const;
        HO_EXPORT virtual UInt64 AsUInt64( size_t index ) const;
        HO_EXPORT virtual float AsSingle( size_t index ) const;
        HO_EXPORT virtual double AsDouble( size_t index ) const;
        HO_EXPORT virtual DateTime AsDateTime( size_t index ) const;
        HO_EXPORT virtual TimeSpan AsTimeSpan( size_t index ) const;
        HO_EXPORT virtual WideString AsString( size_t index ) const;
        HO_EXPORT virtual Guid AsGuid( size_t index ) const;
        HO_EXPORT virtual OCI::Object* AsObject( size_t index ) const;
        HO_EXPORT virtual OCI::Collection* AsCollection( size_t index ) const;
        HO_EXPORT virtual LobStream AsStream( size_t index ) const;

    };


    /// <summary>
    /// DynamicDefine
    /// </summary>
    class DynamicDefine : public ArrayDefine
    {
        using Base = ArrayDefine;

    public:
        DynamicDefine( ) noexcept
            : Base( )
        {
        }

        DynamicDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
        }

        
    private:
        HO_EXPORT static Int32 DynamicDefineCallback( void  *octxp, OCIDefine *defnp, UInt32 iter, void** bufpp, UInt32** alenp, Byte* piecep, void** indp, UInt16** rcodep );
    protected:
        HO_EXPORT virtual Int32 HandleData( UInt32 iter, void** bufpp, UInt32** alenp, Byte* piecep, void** indp, UInt16** rcodep );
        HO_EXPORT void RegisterCallback( );
    public:
        

    };

    /// <summary>
    /// DynamicLongRawDefine
    /// </summary>
    class DynamicLongRawDefine : public DynamicDefine
    {
        using Base = DynamicDefine;
        //std::vector<std::unique_ptr<IO::StreamBase>> data_;
    public:
        DynamicLongRawDefine( ) noexcept
            : Base( )
        {
        }

        HO_EXPORT DynamicLongRawDefine( const OCI::Statement& statement, size_t size );

        HO_EXPORT ~DynamicLongRawDefine( );

        HO_EXPORT virtual void Initialize( UInt32 positon ) override;
    protected:
        HO_EXPORT virtual Int32 HandleData( UInt32 iter, void** bufpp, UInt32** alenp, Byte* piecep, void** indp, UInt16** rcodep ) override;
    public:
        //HO_EXPORT virtual LobStream AsStream( size_t index ) const override;

    };



    /// <summary>
    /// SimpleDefine, template used to implement defines for basic data types for the DataReader
    /// </summary>
    /// <typeparam name="BT"></typeparam>
    template < typename BT, OCI::OraType externalType >
    class SimpleDefine : public Define
    {
        using Base = Define;
    public:
        static constexpr OCI::OraType ExternalType = externalType;
        using BoundType = BT;
    protected:
        BoundType data_;
    public:
        constexpr SimpleDefine( ) noexcept
            : Base( ), data_{}
        {
        }

        SimpleDefine( const OCI::Statement& statement )
            : Base( statement ), data_{}
        {
        }

        virtual void Initialize( UInt32 positon ) override
        {
            DefineByPos( positon, ExternalType, &data_, sizeof( data_ ) );
        }
        virtual const void* Data( ) const noexcept final override
        {
            return &data_;
        }

        virtual bool AsBoolean( ) const final override
        {
            return ConvertTo<bool>( data_ );
        }
        virtual Byte AsByte( ) const final override
        {
            return ConvertTo<Byte>( data_ );
        }
        virtual SByte AsSByte( ) const final override
        {
            return ConvertTo<SByte>( data_ );
        }
        virtual std::vector<Byte> AsBytes( ) const final override
        {
            return BitConverter::GetBytes( data_ );
        }

        virtual Int16 AsInt16( ) const final override
        {
            return ConvertTo<Int16>( data_ );
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            return ConvertTo<UInt16>( data_ );
        }
        virtual Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( data_ );
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( data_ );
        }
        virtual Int64 AsInt64( ) const final override
        {
            return ConvertTo<Int64>( data_ );
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            return ConvertTo<UInt64>( data_ );
        }
        virtual float AsSingle( ) const final override
        {
            return ConvertTo<float>( data_ );
        }
        virtual double AsDouble( ) const final override
        {
            return ConvertTo<double>( data_ );
        }

        virtual DateTime AsDateTime( ) const final override
        {
            return ConvertTo<DateTime>( data_ );
        }
        virtual TimeSpan AsTimeSpan( ) const final override
        {
            return ConvertTo<TimeSpan>( data_ );
        }
        virtual WideString AsString( ) const final override
        {
            return ConvertTo<WideString>( data_ );
        }
    };

    /// <summary>
    /// SimpleArrayDefine, template used to implement defines for basic data types for the ArrayDataReader
    /// </summary>
    /// <typeparam name="BT"></typeparam>
    template < typename BT, OCI::OraType externalType >
    class SimpleArrayDefine : public ArrayDefine
    {
        using Base = ArrayDefine;
    public:
        static constexpr OCI::OraType ExternalType = externalType;
        using BoundType = BT;
    protected:
        std::vector<BoundType> data_;
    public:
        constexpr SimpleArrayDefine( ) noexcept
            : Base( )
        { }

        SimpleArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
            data_.resize( size );
        }

        virtual void Initialize( UInt32 positon ) override
        {
            DefineByPos( positon, ExternalType, data_.data(), sizeof( BoundType ) );
        }

        const std::vector<BoundType>& Values( ) const noexcept
        {
            return data_;
        }

        const BoundType& Value( size_t index ) const noexcept
        {
            return data_[index];
        }


        virtual const void* Data( size_t index ) const noexcept final override
        {
            return std::addressof( data_[index] );
        }

        virtual bool AsBoolean( size_t index ) const final override
        {
            return ConvertTo<bool>( data_[index] );
        }
        virtual Byte AsByte( size_t index ) const final override
        {
            return ConvertTo<Byte>( data_[index] );
        }
        virtual SByte AsSByte( size_t index ) const final override
        {
            return ConvertTo<SByte>( data_[index] );
        }

        virtual std::vector<Byte> AsBytes( size_t index ) const final override
        {
            return BitConverter::GetBytes( data_[index] );
        }

        virtual Int16 AsInt16( size_t index ) const final override
        {
            return ConvertTo<Int16>( data_[index] );
        }
        virtual UInt16 AsUInt16( size_t index ) const final override
        {
            return ConvertTo<UInt16>( data_[index] );
        }
        virtual Int32 AsInt32( size_t index ) const final override
        {
            return ConvertTo<Int32>( data_[index] );
        }
        virtual UInt32 AsUInt32( size_t index ) const final override
        {
            return ConvertTo<UInt32>( data_[index] );
        }
        virtual Int64 AsInt64( size_t index ) const final override
        {
            return ConvertTo<Int64>( data_[index] );
        }
        virtual UInt64 AsUInt64( size_t index ) const final override
        {
            return ConvertTo<UInt64>( data_[index] );
        }
        virtual float AsSingle( size_t index ) const final override
        {
            return ConvertTo<float>( data_[index] );
        }
        virtual double AsDouble( size_t index ) const final override
        {
            return ConvertTo<double>( data_[index] );
        }

        virtual DateTime AsDateTime( size_t index ) const final override
        {
            return ConvertTo<DateTime>( data_[index] );
        }
        virtual TimeSpan AsTimeSpan( size_t index ) const final override
        {
            return ConvertTo<TimeSpan>( data_[index] );
        }
        virtual WideString AsString( size_t index ) const final override
        {
            return ConvertTo<WideString>( data_[index] );
        }

    };

    


    
    /// <summary>
    /// CStringDefine
    /// </summary>
    class CStringDefine : public Define
    {
        using Base = Define;
        std::vector<wchar_t> data_;
        UInt32 actualSize_;
    public:
        CStringDefine( ) noexcept
            : Base( ), actualSize_(0)
        {
        }
        HO_EXPORT CStringDefine( const OCI::Statement& statement, size_t size );
        HO_EXPORT CStringDefine( const OCI::Statement& statement, const OCI::ColumnDescriptor& columnDescriptor );
        HO_EXPORT ~CStringDefine( );



        HO_EXPORT void Initialize( UInt32 positon );

        virtual const void* Data( ) const noexcept override
        {
            return data_.data( );
        }

        HO_EXPORT virtual bool AsBoolean( ) const override;
        HO_EXPORT virtual Byte AsByte( ) const override;
        HO_EXPORT virtual SByte AsSByte( ) const override;
        HO_EXPORT virtual std::vector<Byte> AsBytes( ) const override;
        HO_EXPORT virtual Int16 AsInt16( ) const override;
        HO_EXPORT virtual UInt16 AsUInt16( ) const override;
        HO_EXPORT virtual Int32 AsInt32( ) const override;
        HO_EXPORT virtual UInt32 AsUInt32( ) const override;
        HO_EXPORT virtual Int64 AsInt64( ) const override;
        HO_EXPORT virtual UInt64 AsUInt64( ) const override;
        HO_EXPORT virtual float AsSingle( ) const override;
        HO_EXPORT virtual double AsDouble( ) const override;
        HO_EXPORT virtual DateTime AsDateTime( ) const override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( ) const override;
        HO_EXPORT virtual WideString AsString( ) const override;
        HO_EXPORT virtual Guid AsGuid( ) const;
    };


    /// <summary>
    /// CStringArrayDefine
    /// </summary>
    class CStringArrayDefine : public ArrayDefine
    {
        using Base = ArrayDefine;

        size_t maxColumnDataSize_;
        wchar_t* data_;
        std::vector<UInt32> dataSizes_;

    public:
        CStringArrayDefine( ) noexcept
            : Base( ), maxColumnDataSize_( 0 ), data_( nullptr)
        {
        }
        HO_EXPORT CStringArrayDefine( const OCI::Statement& statement, size_t size, size_t maximumColumnSize );
        HO_EXPORT CStringArrayDefine( const OCI::Statement& statement, size_t size, const OCI::ColumnDescriptor& columnDescriptor );
        HO_EXPORT ~CStringArrayDefine( );

        HO_EXPORT void Initialize( UInt32 positon );

        virtual const void* Data( size_t index ) const noexcept override
        {
            const wchar_t* result = &data_[index * maxColumnDataSize_];
            return result;
        }

        HO_EXPORT virtual bool AsBoolean( size_t index ) const override;
        HO_EXPORT virtual Byte AsByte( size_t index ) const override;
        HO_EXPORT virtual SByte AsSByte( size_t index ) const override;
        HO_EXPORT virtual std::vector<Byte> AsBytes( size_t index ) const override;
        HO_EXPORT virtual Int16 AsInt16( size_t index ) const override;
        HO_EXPORT virtual UInt16 AsUInt16( size_t index ) const override;
        HO_EXPORT virtual Int32 AsInt32( size_t index ) const override;
        HO_EXPORT virtual UInt32 AsUInt32( size_t index ) const override;
        HO_EXPORT virtual Int64 AsInt64( size_t index ) const override;
        HO_EXPORT virtual UInt64 AsUInt64( size_t index ) const override;
        HO_EXPORT virtual float AsSingle( size_t index ) const override;
        HO_EXPORT virtual double AsDouble( size_t index ) const override;
        HO_EXPORT virtual DateTime AsDateTime( size_t index ) const override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( size_t index ) const override;
        HO_EXPORT virtual WideString AsString( size_t index ) const override;
        HO_EXPORT virtual Guid AsGuid( size_t index ) const;

    };

    /// <summary>
    /// NumberBaseDefine
    /// </summary>
    template<OraType externalType >
    class NumberBaseDefine : public Define
    {
    public:
        using Base = Define;
        static constexpr OraType ExternalType = externalType;
    private:
        OCI::Number data_;
    public:
        constexpr NumberBaseDefine( ) noexcept
            : Base( )
        {
        }
        NumberBaseDefine( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        void Initialize( UInt32 positon ) override
        {
            DefineByPos( positon, ExternalType, &data_, 22 );
        }

        virtual const void* Data( ) const noexcept override
        {
            return &data_;
        }

        virtual bool AsBoolean( ) const final override
        {
            bool isZero = false;
            auto& error = Error( );
            OCI::NumberIsZero( error, &data_, &isZero );
            return isZero == false;
        }
        virtual Byte AsByte( ) const final override
        {
            Byte result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual SByte AsSByte( ) const final override
        {
            SByte result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual std::vector<Byte> AsBytes( ) const final override
        {
            auto s = this->AsString( );
            std::vector<Byte> result;
            result.resize( s.length( ) );
            memcpy( result.data( ), s.c_str( ), s.length( ) );
            return result;
        }
        virtual Int16 AsInt16( ) const final override
        {
            Int16 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            UInt16 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual Int32 AsInt32( ) const final override
        {
            Int32 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            UInt32 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual Int64 AsInt64( ) const final override
        {
            long long result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            UInt64 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_, sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual float AsSingle( ) const final override
        {
            Single result = 0;
            auto& error = Error( );
            OCI::NumberToReal( error, &data_, sizeof( result ), &result );
            return result;
        }
        virtual double AsDouble( ) const final override
        {
            double result = 0;
            auto& error = Error( );
            OCI::NumberToReal( error, &data_, sizeof( result ), &result );
            return result;
        }
        virtual DateTime AsDateTime( ) const final override
        {
            DateTime result( AsInt64( ) );
            return result;
        }
        virtual TimeSpan AsTimeSpan( ) const final override
        {
            TimeSpan result( AsInt64( ) );
            return result;
        }

        virtual WideString AsString( ) const final override
        {
            return AsString( L"TM", 2 );
        }

        WideString AsString(const wchar_t* fmt, UInt32 fmtLength ) const
        {
            wchar_t buffer[256];
            UInt32 bufferSize = sizeof( buffer );
            auto& error = Error( );
            OCI::NumberToText( error, &data_, fmt, fmtLength, nullptr, 0, &bufferSize, buffer );
            return WideString( buffer );
        }
    };

    using NumberDefine = NumberBaseDefine<OraType::NUM>;
    using VarNumberDefine = NumberBaseDefine<OraType::VNU>;



    /// <summary>
    /// NumberArrayBaseDefine
    /// </summary>
    template<OraType externalType >
    class NumberArrayBaseDefine : public ArrayDefine
    {
    public:
        using Base = ArrayDefine;
        static constexpr OraType ExternalType = externalType;
    private:
        std::vector<OCI::Number> data_;
    public:
        NumberArrayBaseDefine( ) noexcept
            : Base( )
        {
        }
        NumberArrayBaseDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
            data_.resize( size );
        }
        void Initialize( UInt32 positon ) final override
        {
            DefineByPos( positon, ExternalType, data_.data( ), 22 );
        }

        virtual const void* Data( size_t index ) const noexcept override
        {
            return std::addressof( data_[index] );
        }

        virtual bool AsBoolean( size_t index ) const final override
        {
            bool isZero = false;
            auto& error = Error( );
            OCI::NumberIsZero( error, &data_[index], &isZero );
            return isZero == false;
        }
        virtual Byte AsByte( size_t index ) const final override
        {
            Byte result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual SByte AsSByte( size_t index ) const final override
        {
            SByte result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual std::vector<Byte> AsBytes( size_t index ) const final override
        {
            auto s = this->AsString( index );
            std::vector<Byte> result;
            result.resize( s.length( ) );
            memcpy( result.data( ), s.c_str( ), s.length( ) );
            return result;
        }
        virtual Int16 AsInt16( size_t index ) const final override
        {
            Int16 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual UInt16 AsUInt16( size_t index ) const final override
        {
            UInt16 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual Int32 AsInt32( size_t index ) const final override
        {
            Int32 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual UInt32 AsUInt32( size_t index ) const final override
        {
            UInt32 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual Int64 AsInt64( size_t index ) const final override
        {
            Int64 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Signed, &result );
            return result;
        }
        virtual UInt64 AsUInt64( size_t index ) const final override
        {
            UInt64 result = 0;
            auto& error = Error( );
            OCI::NumberToInt( error, &data_[index], sizeof( result ), NumberToIntFlags::Unsigned, &result );
            return result;
        }
        virtual float AsSingle( size_t index ) const final override
        {
            Single result = 0;
            auto& error = Error( );
            OCI::NumberToReal( error, &data_[index], sizeof( result ), &result );
            return result;
        }
        virtual double AsDouble( size_t index ) const final override
        {
            double result = 0;
            auto& error = Error( );
            OCI::NumberToReal( error, &data_[index], sizeof( result ), &result );
            return result;
        }
        virtual DateTime AsDateTime( size_t index ) const final override
        {
            DateTime result( AsInt64( index ) );
            return result;
        }
        virtual TimeSpan AsTimeSpan( size_t index ) const final override
        {
            TimeSpan result( AsInt64( index ) );
            return result;
        }
        virtual WideString AsString( size_t index ) const final override
        {
            return AsString( index, L"TM", 2 );
        }

        WideString AsString( size_t index, const wchar_t* fmt, UInt32 fmtLength ) const
        {
            wchar_t buffer[256];
            UInt32 bufferSize = sizeof( buffer );
            auto& error = Error( );
            OCI::NumberToText( error, &data_[index], fmt, fmtLength, nullptr, 0, &bufferSize, buffer );
            return WideString( buffer );
        }
    };

    using NumberArrayDefine = NumberArrayBaseDefine<OraType::NUM>;
    using VarNumberArrayDefine = NumberArrayBaseDefine<OraType::VNU>;



    namespace Internal
    {
#pragma warning(push)
#pragma warning(disable:4200)
#pragma pack(push,1)
        struct VarBinaryDataType
        {
            UInt16 size;
            Byte data[0];
        };
        constexpr UInt32 VarBinaryDataTypeSize = sizeof( VarBinaryDataType );
        struct LongVarBinaryDataType
        {
            UInt32 size;
            Byte data[0];
        };
        constexpr UInt32 LongVarBinaryDataTypeSize = sizeof( LongVarBinaryDataType );
#pragma pack(pop)
#pragma warning(pop)
    }

    /// <summary>
    /// VarBinaryDefine
    /// </summary>
    class VarBinaryDefine : public Define
    {
    public:
        using Base = Define;
        using DataType = Internal::VarBinaryDataType;
        static constexpr UInt32 DataTypeSize = Internal::VarBinaryDataTypeSize;


    private:
        DataType* data_;
        UInt32 columnDataSize_;
    public:
        constexpr VarBinaryDefine( ) noexcept
            : Base( ), data_( nullptr ), columnDataSize_( 0 )
        {
        }
        HO_EXPORT VarBinaryDefine( const OCI::Statement& statement, UInt32 columnDataSize );
        HO_EXPORT VarBinaryDefine( const OCI::Statement& statement, const OCI::ColumnDescriptor& columnDescriptor );

        HO_EXPORT ~VarBinaryDefine( );

        HO_EXPORT void Initialize( UInt32 positon );

    protected:
        DataType* ColumnData( ) const noexcept
        {
            return data_;
        }
    public:
        virtual const void* Data( ) const noexcept override
        {
            auto rowData = ColumnData( );
            return rowData->data;
        }

        HO_EXPORT virtual bool AsBoolean( ) const final override;
        HO_EXPORT virtual Byte AsByte( ) const final override;
        HO_EXPORT virtual std::vector<Byte> AsBytes( ) const final override;
        HO_EXPORT virtual SByte AsSByte( ) const final override;
        HO_EXPORT virtual Int16 AsInt16( ) const final override;
        HO_EXPORT virtual UInt16 AsUInt16( ) const final override;
        HO_EXPORT virtual Int32 AsInt32( ) const final override;
        HO_EXPORT virtual UInt32 AsUInt32( ) const final override;
        HO_EXPORT virtual Int64 AsInt64( ) const final override;
        HO_EXPORT virtual UInt64 AsUInt64( ) const final override;
        HO_EXPORT virtual float AsSingle( ) const final override;
        HO_EXPORT virtual double AsDouble( ) const final override;
        HO_EXPORT virtual DateTime AsDateTime( ) const final override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( ) const final override;
        HO_EXPORT virtual WideString AsString( ) const final override;
        HO_EXPORT virtual Guid AsGuid( ) const final override;
    };

    /// <summary>
    /// VarBinaryArrayDefine
    /// </summary>
    class VarBinaryArrayDefine : public ArrayDefine
    {
    public:
        using Base = ArrayDefine;
        using DataType = Internal::VarBinaryDataType;
        static constexpr UInt32 DataTypeSize = Internal::VarBinaryDataTypeSize;
    private:
        DataType* data_;
        UInt32 columnDataSize_;
    public:
        VarBinaryArrayDefine( ) noexcept
            : Base( ), data_(nullptr), columnDataSize_(0)
        {
        }
        HO_EXPORT VarBinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, UInt32 columnDataSize );
        HO_EXPORT VarBinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, const OCI::ColumnDescriptor& columnDescriptor );

        HO_EXPORT ~VarBinaryArrayDefine( );

        HO_EXPORT virtual void Initialize( UInt32 positon ) override;

    protected:
        DataType* ColumnData( size_t index ) const noexcept
        {
            DataType* rowData = (DataType*)( ( (Byte*)data_ ) + ( static_cast<size_t>(DataTypeSize) + static_cast<size_t>( columnDataSize_ ) ) * index );
            return rowData;
        }
    public:
        virtual const void* Data( size_t index ) const noexcept override
        {
            DataType* columnData = ColumnData( index );
            return columnData->data;
        }

        HO_EXPORT virtual bool AsBoolean( size_t index ) const final override;
        HO_EXPORT virtual Byte AsByte( size_t index ) const final override;
        HO_EXPORT virtual std::vector<Byte> AsBytes( size_t index ) const final override;
        HO_EXPORT virtual SByte AsSByte( size_t index ) const final override;
        HO_EXPORT virtual Int16 AsInt16( size_t index ) const final override;
        HO_EXPORT virtual UInt16 AsUInt16( size_t index ) const final override;
        HO_EXPORT virtual Int32 AsInt32( size_t index ) const final override;
        HO_EXPORT virtual UInt32 AsUInt32( size_t index ) const final override;
        HO_EXPORT virtual Int64 AsInt64( size_t index ) const final override;
        HO_EXPORT virtual UInt64 AsUInt64( size_t index ) const final override;
        HO_EXPORT virtual float AsSingle( size_t index ) const final override;
        HO_EXPORT virtual double AsDouble( size_t index ) const final override;
        HO_EXPORT virtual DateTime AsDateTime( size_t index ) const final override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( size_t index ) const final override;
        HO_EXPORT virtual WideString AsString( size_t index ) const final override;
        HO_EXPORT virtual Guid AsGuid( size_t index ) const final override;

    };


    /// <summary>
    /// LongVarBinaryDefine
    /// </summary>
    class LongVarBinaryDefine : public Define
    {
        using Base = Define;
        void* ociraw_;
    public:
        constexpr LongVarBinaryDefine( ) noexcept
            : Base( ), ociraw_( nullptr )
        {
        }
        LongVarBinaryDefine( const OCI::Statement& statement )
            : Base( statement ), ociraw_( nullptr )
        {
        }
        void Initialize( UInt32 positon )
        {
            DefineByPos( positon, OCI::OraType::LBI, &ociraw_, sizeof( ociraw_ ) );
        }

        virtual const void* Data( ) const noexcept override
        {
            return ociraw_;
        }
    };



    /// <summary>
    /// BinaryDefine
    /// </summary>
    class BinaryDefine : public Define
    {
    public:
        using Base = Define;

    private:
        Byte* data_;
        UInt32 columnDataSize_;
    public:
        constexpr BinaryDefine( ) noexcept
            : Base( ), data_( nullptr ), columnDataSize_( 0 )
        {
        }
        HO_EXPORT BinaryDefine( const OCI::Statement& statement, UInt32 columnDataSize );
        HO_EXPORT BinaryDefine( const OCI::Statement& statement, const OCI::ColumnDescriptor& columnDescriptor );

        HO_EXPORT ~BinaryDefine( );

        HO_EXPORT void Initialize( UInt32 positon );

    protected:
        Byte* ColumnData( ) const noexcept
        {
            return data_;
        }
    public:
        virtual const void* Data( ) const noexcept override
        {
            return ColumnData( );
        }

        HO_EXPORT virtual bool AsBoolean( ) const final override;
        HO_EXPORT virtual Byte AsByte( ) const final override;
        HO_EXPORT virtual std::vector<Byte> AsBytes( ) const final override;
        HO_EXPORT virtual SByte AsSByte( ) const final override;
        HO_EXPORT virtual Int16 AsInt16( ) const final override;
        HO_EXPORT virtual UInt16 AsUInt16( ) const final override;
        HO_EXPORT virtual Int32 AsInt32( ) const final override;
        HO_EXPORT virtual UInt32 AsUInt32( ) const final override;
        HO_EXPORT virtual Int64 AsInt64( ) const final override;
        HO_EXPORT virtual UInt64 AsUInt64( ) const final override;
        HO_EXPORT virtual float AsSingle( ) const final override;
        HO_EXPORT virtual double AsDouble( ) const final override;
        HO_EXPORT virtual DateTime AsDateTime( ) const final override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( ) const final override;
        HO_EXPORT virtual WideString AsString( ) const final override;
        HO_EXPORT virtual Guid AsGuid( ) const final override;
    };

    /// <summary>
    /// BinaryArrayDefine
    /// </summary>
    class BinaryArrayDefine : public ArrayDefine
    {
    public:
        using Base = ArrayDefine;
        using DataType = Byte;
    private:
        DataType* data_;
        UInt32 columnDataSize_;
    public:
        BinaryArrayDefine( ) noexcept
            : Base( ), data_( nullptr ), columnDataSize_( 0 )
        {
        }
        HO_EXPORT BinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, UInt32 columnDataSize );
        HO_EXPORT BinaryArrayDefine( const OCI::Statement& statement, size_t arraySize, const OCI::ColumnDescriptor& columnDescriptor );

        HO_EXPORT ~BinaryArrayDefine( );

        HO_EXPORT virtual void Initialize( UInt32 positon ) override;

    protected:
        DataType* ColumnData( size_t index ) const
        {
            DataType* rowData = (DataType*)( ( (Byte*)data_ ) + (static_cast<size_t>( columnDataSize_ ) * index) );
            return rowData;
        }
    public:
        virtual const void* Data( size_t index ) const noexcept override
        {
            return ColumnData( index );
        }

        HO_EXPORT virtual bool AsBoolean( size_t index ) const final override;
        HO_EXPORT virtual Byte AsByte( size_t index ) const final override;
        HO_EXPORT virtual std::vector<Byte> AsBytes( size_t index ) const final override;
        HO_EXPORT virtual SByte AsSByte( size_t index ) const final override;
        HO_EXPORT virtual Int16 AsInt16( size_t index ) const final override;
        HO_EXPORT virtual UInt16 AsUInt16( size_t index ) const final override;
        HO_EXPORT virtual Int32 AsInt32( size_t index ) const final override;
        HO_EXPORT virtual UInt32 AsUInt32( size_t index ) const final override;
        HO_EXPORT virtual Int64 AsInt64( size_t index ) const final override;
        HO_EXPORT virtual UInt64 AsUInt64( size_t index ) const final override;
        HO_EXPORT virtual float AsSingle( size_t index ) const final override;
        HO_EXPORT virtual double AsDouble( size_t index ) const final override;
        HO_EXPORT virtual DateTime AsDateTime( size_t index ) const final override;
        HO_EXPORT virtual TimeSpan AsTimeSpan( size_t index ) const final override;
        HO_EXPORT virtual WideString AsString( size_t index ) const final override;
        HO_EXPORT virtual Guid AsGuid( size_t index ) const final override;

    };



    /// <summary>
    /// FixedBinaryDefine
    /// </summary>
    template<size_t binarySize>
    class FixedBinaryDefine : public Define
    {
    public:
        using Base = Define;
        constexpr static size_t BinarySize = binarySize;
        using value_type = std::array<Byte, BinarySize>;
    protected:
        value_type data_;
    public:
        constexpr FixedBinaryDefine( ) noexcept
            : Base( ), data_{}
        {
        }
        FixedBinaryDefine( const OCI::Statement& statement )
            : Base( statement ), data_{}
        { }

        virtual void Initialize( UInt32 positon ) override
        {
            DefineByPos( positon, OCI::OraType::BIN, data_.data( ), static_cast<Int32>( data_.size() ) );
        }

        virtual const void* Data( ) const noexcept final override
        {
            return (void*)data_.data( );
        }
    };

    /// <summary>
    /// FixedBinaryArrayDefine
    /// </summary>
    template<UInt64 binarySize>
    class FixedBinaryArrayDefine : public ArrayDefine
    {
    public:
        using Base = ArrayDefine;
        constexpr static size_t BinarySize = binarySize;
        using value_type = std::array<Byte, BinarySize>;

    protected:
        std::vector<value_type> data_;
    public:
        constexpr FixedBinaryArrayDefine( ) noexcept
            : Base( )
        {
        }
        FixedBinaryArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
            data_.resize( size );
        }

        virtual void Initialize( UInt32 positon ) override
        {
            if constexpr ( BinarySize <= 2000 )
            {
                DefineByPos( positon, OCI::OraType::BIN, data_.data( ), static_cast<Int64>( BinarySize ) );
            }
            else
            {
                DefineByPos( positon, OCI::OraType::LBI, data_.data( ), static_cast<Int64>( BinarySize ) );
            }
        }

        virtual const void* Data( size_t index ) const noexcept final override
        {
            return (void*)data_[index].data( );
        }

    };


    /// <summary>
    /// FixedStringDefine
    /// </summary>
    template<size_t fixedStringSize>
    class FixedStringDefine : public Define
    {
        
    public:
        using Base = Define;
        constexpr static size_t FixedStringSize = fixedStringSize;
        using value_type = std::array<wchar_t, FixedStringSize>;
    protected:
        value_type data_;
    public:
        constexpr FixedStringDefine( ) noexcept
            : Base( ), data_{}
        {
        }
        FixedStringDefine( const OCI::Statement& statement )
            : Base( statement ), data_{}
        {
        }

        virtual void Initialize( UInt32 positon ) override
        {
            InternalDefineByPos( positon, OCI::OraType::ORA_CHARN, data_.data( ), static_cast<Int64>( FixedStringSize*sizeof(wchar_t) ) );
        }

        virtual const void* Data( ) const noexcept final override
        {
            return data_.data( );
        }
    };


    /// <summary>
    /// FixedStringArrayDefine
    /// </summary>
    template<size_t fixedStringSize>
    class FixedStringArrayDefine : public ArrayDefine
    {

    public:
        using Base = ArrayDefine;
        constexpr static size_t FixedStringSize = fixedStringSize;
        using value_type = std::array<wchar_t, FixedStringSize>;
    protected:
        std::vector<value_type> data_;
    public:
        FixedStringArrayDefine( ) noexcept
            : Base( )
        {
        }
        FixedStringArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
            data_.resize( size );
        }

        virtual void Initialize( UInt32 positon ) override
        {
            InternalDefineByPos( positon, OCI::OraType::ORA_CHARN, data_.data( ), static_cast<Int64>( FixedStringSize * sizeof( wchar_t ) ) );
        }

        virtual const void* Data( size_t index ) const noexcept final override
        {
            return data_[index].data( );
        }
    };



    /// <summary>
    /// GuidDefine
    /// </summary>
    class GuidDefine : public FixedBinaryDefine<sizeof(Guid)>
    {
        using Base = FixedBinaryDefine<sizeof(Guid)>;
    public:
        constexpr GuidDefine( ) noexcept
            : Base( )
        {
        }
        GuidDefine( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        virtual bool AsBoolean( ) const final override
        {
            Guid guid( data_ );
            return guid.IsEmpty( ) == false;
        }

        virtual Guid AsGuid( ) const override
        {
            Guid result( data_ );
            return result;
        }

        virtual WideString AsString( ) const override
        {
            return AsGuid( ).ToString( );
        }
    };

    /// <summary>
    /// GuidArrayDefine
    /// </summary>
    class GuidArrayDefine : public FixedBinaryArrayDefine<sizeof(Guid)>
    {
        using Base = FixedBinaryArrayDefine<sizeof(Guid)>;
    public:
        constexpr GuidArrayDefine( ) noexcept
            : Base( )
        {
        }
        GuidArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
        }

        virtual bool AsBoolean( size_t index ) const final override
        {
            Guid guid( data_[index] );
            return guid.IsEmpty() == false;
        }

        virtual Guid AsGuid( size_t index ) const final override
        {
            Guid result( data_[index] );
            return result;
        }

        virtual WideString AsString( size_t index ) const final override
        {
            return AsGuid( index ).ToString( );
        }
    };


    /// <summary>
    /// DateDefine
    /// </summary>
    class DateDefine : public Define
    {
        using Base = Define;
        OCI::Date date_;
    public:
        constexpr DateDefine( ) noexcept
            : Base( )
        {
        }
        DateDefine( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        virtual void Initialize( UInt32 positon ) final override
        {
            DefineByPos( positon, OCI::OraType::ODT, &date_, sizeof( OCI::Date ) );
        }

        constexpr const OCI::Date& Date( ) const noexcept
        {
            return date_;
        }

        virtual const void* Data( ) const noexcept override
        {
            return &date_;
        }

        virtual bool AsBoolean( ) const final override
        {
            return AsInt64( ) != 0;
        }
        virtual Byte AsByte( ) const final override
        {
            return ConvertTo<Byte>( AsInt64( ) );
        }
        virtual SByte AsSByte( ) const final override
        {
            return ConvertTo<SByte>( AsInt64( ) );
        }
        virtual std::vector<Byte> AsBytes( ) const final override
        {
            return BitConverter::GetBytes( AsInt64( ) );
        }
        virtual Int16 AsInt16( ) const final override
        {
            return ConvertTo<Int16>( AsInt64( ) );
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            return ConvertTo<UInt16>( AsInt64( ) );
        }
        virtual Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( AsInt64( ) );
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( AsInt64( ) );
        }
        virtual Int64 AsInt64( ) const final override
        {
            return date_.Ticks( );
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            return static_cast<UInt64>( AsInt64( ) );
        }
        virtual float AsSingle( ) const final override
        {
            return static_cast<float>(AsDateTime( ).ToOADate( ));
        }
        virtual double AsDouble( ) const final override
        {
            return AsDateTime( ).ToOADate( );
        }
        virtual DateTime AsDateTime( ) const final override
        {
            return date_.ToDateTime( );
        }
        virtual TimeSpan AsTimeSpan( ) const final override
        {
            return ConvertTo<TimeSpan>( AsInt64( ) );
        }
        virtual WideString AsString( ) const final override
        {
            static WideString fmt( L"YYYY/MM/DD HH24:MI:SS" );
            return AsString( fmt );
        }
        WideString AsString( const WideString& fmt ) const
        {
            wchar_t buffer[256];
            UInt32 bufferSize = sizeof( buffer );
            auto& error = Error( );
            OCI::DateToText( error, &date_, fmt.c_str( ), static_cast<Byte>( fmt.length( ) ), nullptr, 0, &bufferSize, buffer );

            return WideString( (WideString::value_type*)buffer, static_cast<WideString::size_type>( bufferSize ) );
        }
    };

    /// <summary>
    /// DateArrayDefine
    /// </summary>
    class DateArrayDefine : public ArrayDefine
    {
        using Base = ArrayDefine;
    public:
        typedef OCI::Date value_type;
    private:
        std::vector<value_type> data_;
    public:
        DateArrayDefine( ) noexcept
            : Base( )
        {
        }
        DateArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        { 
            data_.resize( size );
        }

        void Initialize( UInt32 positon ) final override
        {
            DefineByPos( positon, OCI::OraType::ODT, data_.data( ), sizeof( OCI::Date ) );
        }

        const OCI::Date& Date( size_t index ) const noexcept
        {
            return data_[index];
        }

        virtual const void* Data( size_t index ) const noexcept override
        {
            return std::addressof( data_[index] );
        }

        virtual bool AsBoolean( size_t index ) const final override
        {
            return AsInt64( index ) != 0;
        }
        virtual Byte AsByte( size_t index ) const final override
        {
            return ConvertTo<Byte>( AsInt64( index ) );
        }
        virtual SByte AsSByte( size_t index ) const final override
        {
            return ConvertTo<SByte>( AsInt64( index ) );
        }
        virtual std::vector<Byte> AsBytes( size_t index ) const final override
        {
            return BitConverter::GetBytes( AsInt64( index ) );
        }
        virtual Int16 AsInt16( size_t index ) const final override
        {
            return ConvertTo<Int16>( AsInt64( index ) );
        }
        virtual UInt16 AsUInt16( size_t index ) const final override
        {
            return ConvertTo<UInt16>( AsInt64( index ) );
        }
        virtual Int32 AsInt32( size_t index ) const final override
        {
            return ConvertTo<Int32>( AsInt64( index ) );
        }
        virtual UInt32 AsUInt32( size_t index ) const final override
        {
            return ConvertTo<UInt32>( AsInt64( index ) );
        }
        virtual Int64 AsInt64( size_t index ) const final override
        {
            return data_[index].Ticks( );
        }
        virtual UInt64 AsUInt64( size_t index ) const final override
        {
            return static_cast<UInt64>( AsInt64( index ) );
        }
        virtual float AsSingle( size_t index ) const final override
        {
            return static_cast<float>( AsDateTime( index ).ToOADate( ) );
        }
        virtual double AsDouble( size_t index ) const final override
        {
            return AsDateTime( index ).ToOADate( );
        }
        virtual DateTime AsDateTime( size_t index ) const final override
        {
            return data_[index].ToDateTime( );
        }
        virtual TimeSpan AsTimeSpan( size_t index ) const final override
        {
            return ConvertTo<TimeSpan>( AsInt64( index ) );
        }
        virtual WideString AsString( size_t index ) const final override
        {
            static WideString fmt( L"YYYY/MM/DD HH24:MI:SS" );
            return AsString( index, fmt );
        }
        WideString AsString( size_t index, const WideString& fmt ) const
        {
            wchar_t buffer[256];
            UInt32 bufferSize = sizeof( buffer );
            auto& error = Error( );
            OCI::DateToText( error, &data_[index], fmt.c_str( ), static_cast<Byte>( fmt.length( ) ), nullptr, 0, &bufferSize, buffer );

            return WideString( (WideString::value_type*)buffer, static_cast<WideString::size_type>( bufferSize ) );
        }

    };


    /// <summary>
    /// DescriptorBaseDefine
    /// </summary>
    class DescriptorBaseDefine : public Define
    {
    public:
        using Base = Define;
    public:
        constexpr DescriptorBaseDefine( ) noexcept
            : Base( )
        {
        }

        DescriptorBaseDefine( const OCI::Statement& statement ) noexcept
            : Base( statement )
        {
        }
    protected:
        HO_EXPORT static void* DescriptorAlloc( const OCI::Statement& statement, OCI::HandleType descriptorType );
        HO_EXPORT void DescriptorFree( void* descriptor, OCI::HandleType descriptorType );
    };

    /// <summary>
    /// DescriptorBaseDefine
    /// </summary>
    class DescriptorBaseArrayDefine : public ArrayDefine
    {
    public:
        using Base = ArrayDefine;
    public:
        DescriptorBaseArrayDefine( ) noexcept
            : Base( )
        {
        }

        DescriptorBaseArrayDefine( const OCI::Statement& statement, size_t size ) noexcept
            : Base( statement, size )
        {
        }
    protected:
        HO_EXPORT static void ArrayDescriptorAlloc( const OCI::Statement& statement, OCI::HandleType descriptorType, size_t size, void** descriptors );
        HO_EXPORT void ArrayDescriptorFree( void** descriptors, OCI::HandleType descriptorType );
    };


    /// <summary>
    /// DescriptorDefine, maintains the descriptor for derived types
    /// </summary>
    template<typename VT, OCI::HandleType descriptorType, OCI::OraType oracleType>
    class DescriptorDefine : public DescriptorBaseDefine
    {
    public:
        using Base = DescriptorBaseDefine;
        using ValueType = VT;
        constexpr static OCI::HandleType DescriptorType = descriptorType;
        constexpr static OCI::OraType OracleType = oracleType;
    private:
        ValueType* data_;
    protected:
        constexpr DescriptorDefine()
            : Base(), data_(nullptr)
        { }

        DescriptorDefine( const OCI::Statement& statement )
            : Base( statement ), data_( (ValueType*)DescriptorAlloc( statement, DescriptorType ) )
        {
        }

        ~DescriptorDefine( )
        {
            if ( data_ )
            {
                DescriptorFree( data_, DescriptorType );
                data_ = nullptr;
            }
        }
    public:
        void Initialize( UInt32 positon ) final override
        {
            DefineByPos( positon, OracleType, &data_, sizeof( void* ) );
        }

    protected:
        ValueType* Value( ) const
        {
            return data_;
        }
    public:
        virtual const void* Data( ) const noexcept override
        {
            return &data_;
        }

    };

    /// <summary>
    /// DescriptorArrayDefine, maintains a vector of descriptors on behalf of derived types.
    /// </summary>
    template<typename VT, OCI::HandleType descriptorType, OCI::OraType oracleType>
    class DescriptorArrayDefine : public DescriptorBaseArrayDefine
    {
    public:
        using Base = DescriptorBaseArrayDefine;
        using ValueType = VT;
        constexpr static OCI::HandleType DescriptorType = descriptorType;
        constexpr static OCI::OraType OracleType = oracleType;
    private:
        std::vector<ValueType*> data_;
    protected:
        constexpr DescriptorArrayDefine( )
            : Base( )
        {
        }

        DescriptorArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
            data_.resize( size );
            ArrayDescriptorAlloc( statement, DescriptorType, size, (void**)data_.data( ) );
        }

        ~DescriptorArrayDefine( )
        {
            if ( data_.size() )
            {
                ArrayDescriptorFree( (void**)data_.data(), DescriptorType );
            }
        }
    public:
        void Initialize( UInt32 positon ) final override
        {
            DefineByPos( positon, OracleType, data_.data( ), static_cast<Int32>( sizeof( void* ) * data_.size( ) ) );
        }
    protected:
        ValueType* Value( size_t index ) const
        {
            return data_[index];
        }
    public:
        virtual const void* Data( size_t index ) const noexcept override
        {
            return std::addressof( data_[index] );
        }

    };




    /// <summary>
    /// TimestampBaseDefine, template used to implement TimestampDefine, TimestampTZDefine and TimestampLTZDefine
    /// </summary>
    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class TimestampBaseDefine : public DescriptorDefine<OCIDateTime, descriptorType, oracleType>
    {
    public:
        using Base = DescriptorDefine<OCIDateTime, descriptorType, oracleType>;
    public:
        constexpr TimestampBaseDefine( ) noexcept
            : Base( )
        {
        }
        TimestampBaseDefine( const OCI::Statement& statement )
            : Base( statement )
        { }

        virtual bool AsBoolean( ) const final override
        {
            return ConvertTo<bool>( AsDateTime( ) );
        }
        virtual Byte AsByte( ) const final override
        {
            return ConvertTo<Byte>( AsDateTime( ) );
        }
        virtual SByte AsSByte( ) const final override
        {
            return ConvertTo<SByte>( AsDateTime( ) );
        }
        virtual std::vector<Byte> AsBytes( ) const final override
        {
            return BitConverter::GetBytes( AsDateTime( ).Ticks() );
        }
        virtual Int16 AsInt16( ) const final override
        {
            return ConvertTo<Int16>( AsDateTime( ) );
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            return ConvertTo<UInt16>( AsDateTime( ) );
        }
        virtual Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( AsDateTime( ) );
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( AsDateTime( ) );
        }
        virtual Int64 AsInt64( ) const final override
        {
            return ConvertTo<Int64>( AsDateTime( ) );
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            return ConvertTo<UInt64>( AsDateTime( ) );
        }
        virtual float AsSingle( ) const final override
        {
            return ConvertTo<Single>( AsDateTime( ) );
        }
        virtual double AsDouble( ) const final override
        {
            return ConvertTo<Double>( AsDateTime( ) );
        }
        virtual DateTime AsDateTime( ) const final override
        {
            auto& environment = Base::Environment( );
            auto& error = Base::Error( );
            DateTime result;
            DateTimeGetDateTime( environment, error, Base::Value( ), result );
            return result;
        }
        virtual TimeSpan AsTimeSpan( ) const final override
        {
            return ConvertTo<TimeSpan>( AsDateTime( ) );
        }
        virtual WideString AsString( ) const final override
        {
            auto& environment = Base::Environment( );
            auto& error = Base::Error( );
            return DateTimeToText( environment, error, Base::Value( ) );
        }
        WideString AsString( const WideString& fmt, Byte fractionalSecondPrecision = 2 ) const
        {
            auto& environment = Base::Environment( );
            auto& error = Base::Error( );
            return DateTimeToText( environment, error, Base::Value( ), fmt, fractionalSecondPrecision );
        }

    };

    /// <summary>
    /// TimestampBaseArrayDefine, template used to implement TimestampArrayDefine, TimestampTZArrayDefine and TimestampLTZArrayDefine
    /// </summary>
    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class TimestampBaseArrayDefine : public DescriptorArrayDefine<OCIDateTime, descriptorType, oracleType>
    {
    public:
        using Base = DescriptorArrayDefine<OCIDateTime, descriptorType, oracleType>;
    public:
        constexpr TimestampBaseArrayDefine( ) noexcept
            : Base( )
        {
        }
        TimestampBaseArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
        }

        virtual bool AsBoolean( size_t index ) const final override
        {
            return ConvertTo<bool>( AsDateTime( index ) );
        }
        virtual Byte AsByte( size_t index ) const final override
        {
            return ConvertTo<Byte>( AsDateTime( index ) );
        }
        virtual SByte AsSByte( size_t index ) const final override
        {
            return ConvertTo<SByte>( AsDateTime( index ) );
        }
        virtual std::vector<Byte> AsBytes( size_t index ) const final override
        {
            return BitConverter::GetBytes( AsDateTime( index ).Ticks() );
        }
        virtual Int16 AsInt16( size_t index ) const final override
        {
            return ConvertTo<Int16>( AsDateTime( index ) );
        }
        virtual UInt16 AsUInt16( size_t index ) const final override
        {
            return ConvertTo<UInt16>( AsDateTime( index ) );
        }
        virtual Int32 AsInt32( size_t index ) const final override
        {
            return ConvertTo<Int32>( AsDateTime( index ) );
        }
        virtual UInt32 AsUInt32( size_t index ) const final override
        {
            return ConvertTo<UInt32>( AsDateTime( index ) );
        }
        virtual Int64 AsInt64( size_t index ) const final override
        {
            return ConvertTo<Int64>( AsDateTime( index ) );
        }
        virtual UInt64 AsUInt64( size_t index ) const final override
        {
            return ConvertTo<UInt64>( AsDateTime( index ) );
        }
        virtual float AsSingle( size_t index ) const final override
        {
            return ConvertTo<Single>( AsDateTime( index ) );
        }
        virtual double AsDouble( size_t index ) const final override
        {
            return ConvertTo<Double>( AsDateTime( index ) );
        }
        virtual DateTime AsDateTime( size_t index ) const final override
        {
            auto& environment = Base::Environment( );
            auto& error = Base::Error( );
            DateTime result;
            DateTimeGetDateTime( environment, error, Base::Value( index ), result );
            return result;
        }
        virtual TimeSpan AsTimeSpan( size_t index ) const final override
        {
            return ConvertTo<TimeSpan>( AsDateTime( index ) );
        }
        virtual WideString AsString( size_t index ) const final override
        {
            auto& environment = Base::Environment( );
            auto& error = Base::Error( );
            return DateTimeToText( environment, error, Base::Value( index ) );
        }
        WideString AsString( size_t index, const WideString& fmt, Byte fractionalSecondPrecision = 2 ) const
        {
            auto& environment = Base::Environment( );
            auto& error = Base::Error( );
            return DateTimeToText( environment, error, Base::Value( index ), fmt, fractionalSecondPrecision );
        }

    };


    


    /// <summary>
    /// IntervalBaseDefine, template used to implement IntervalDSDefine and IntervalYMDefine
    /// </summary>
    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class IntervalBaseDefine : public DescriptorDefine<OCIInterval, descriptorType, oracleType>
    {
    public:
        using Base = DescriptorDefine<OCIInterval, descriptorType, oracleType>;
    public:
        constexpr IntervalBaseDefine( ) noexcept
            : Base( )
        {
        }
        IntervalBaseDefine( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        virtual bool AsBoolean( ) const final override
        {
            return ConvertTo<bool>( AsTimeSpan( ) );
        }
        virtual Byte AsByte( ) const final override
        {
            return ConvertTo<Byte>( AsTimeSpan( ) );
        }
        virtual SByte AsSByte( ) const final override
        {
            return ConvertTo<SByte>( AsTimeSpan( ) );
        }
        virtual std::vector<Byte> AsBytes( ) const final override
        {
            return BitConverter::GetBytes( AsTimeSpan( ).Ticks() );
        }
        virtual Int16 AsInt16( ) const final override
        {
            return ConvertTo<Int16>( AsTimeSpan( ) );
        }
        virtual UInt16 AsUInt16( ) const final override
        {
            return ConvertTo<UInt16>( AsTimeSpan( ) );
        }
        virtual Int32 AsInt32( ) const final override
        {
            return ConvertTo<Int32>( AsTimeSpan( ) );
        }
        virtual UInt32 AsUInt32( ) const final override
        {
            return ConvertTo<UInt32>( AsTimeSpan( ) );
        }
        virtual Int64 AsInt64( ) const final override
        {
            return ConvertTo<Int64>( AsTimeSpan( ) );
        }
        virtual UInt64 AsUInt64( ) const final override
        {
            return ConvertTo<UInt64>( AsTimeSpan( ) );
        }
        virtual float AsSingle( ) const final override
        {
            return ConvertTo<Single>( AsTimeSpan( ) );
        }
        virtual double AsDouble( ) const final override
        {
            return ConvertTo<Double>( AsTimeSpan( ) );
        }
        virtual DateTime AsDateTime( ) const final override
        {
            return ConvertTo<DateTime>( AsTimeSpan( ) );
        }
        virtual TimeSpan AsTimeSpan( ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return IntervalGetTimeSpan( serviceContext, error, Base::Value( ) );
        }
        virtual WideString AsString( ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return IntervalToText( serviceContext, error, Base::Value( ), 14, 2 );
        }

    };

    /// <summary>
    /// IntervalBaseArrayDefine - template used to implement IntervalDSArrayDefine and IntervalYMArrayDefine
    /// </summary>
    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class IntervalBaseArrayDefine : public DescriptorArrayDefine<OCIInterval, descriptorType, oracleType>
    {
    public:
        using Base = DescriptorArrayDefine<OCIInterval, descriptorType, oracleType>;
    public:
        constexpr IntervalBaseArrayDefine( ) noexcept
            : Base( )
        {
        }
        IntervalBaseArrayDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
        }

        virtual bool AsBoolean( size_t index ) const final override
        {
            return ConvertTo<bool>( AsTimeSpan( index ) );
        }
        virtual Byte AsByte( size_t index ) const final override
        {
            return ConvertTo<Byte>( AsTimeSpan( index ) );
        }
        virtual SByte AsSByte( size_t index ) const final override
        {
            return ConvertTo<SByte>( AsTimeSpan( index ) );
        }
        virtual std::vector<Byte> AsBytes( size_t index ) const final override
        {
            return BitConverter::GetBytes( AsTimeSpan( index ).Ticks() );
        }
        virtual Int16 AsInt16( size_t index ) const final override
        {
            return ConvertTo<Int16>( AsTimeSpan( index ) );
        }
        virtual UInt16 AsUInt16( size_t index ) const final override
        {
            return ConvertTo<UInt16>( AsTimeSpan( index ) );
        }
        virtual Int32 AsInt32( size_t index ) const final override
        {
            return ConvertTo<Int32>( AsTimeSpan( index ) );
        }
        virtual UInt32 AsUInt32( size_t index ) const final override
        {
            return ConvertTo<UInt32>( AsTimeSpan( index ) );
        }
        virtual Int64 AsInt64( size_t index ) const final override
        {
            return ConvertTo<Int64>( AsTimeSpan( index ) );
        }
        virtual UInt64 AsUInt64( size_t index ) const final override
        {
            return ConvertTo<UInt64>( AsTimeSpan( index ) );
        }
        virtual float AsSingle( size_t index ) const final override
        {
            return ConvertTo<Single>( AsTimeSpan( index ) );
        }
        virtual double AsDouble( size_t index ) const final override
        {
            return ConvertTo<Double>( AsTimeSpan( index ) );
        }
        virtual DateTime AsDateTime( size_t index ) const final override
        {
            return ConvertTo<DateTime>( AsTimeSpan( index ) );
        }
        virtual TimeSpan AsTimeSpan( size_t index ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return IntervalGetTimeSpan( serviceContext, error, Base::Value( index ) );
        }
        virtual WideString AsString( size_t index ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return IntervalToText( serviceContext, error, Base::Value( index ), 14, 2 );
        }

    };


    



    /// <summary>
    /// ObjectDefine
    /// </summary>
    class ObjectDefine : public Define
    {
        using Base = Define;
        const OCI::Type* type_;
        void* handle_;
    public:
        constexpr ObjectDefine( ) noexcept
            : Base( ), type_(nullptr), handle_(nullptr)
        {
        }
        HO_EXPORT ObjectDefine( const OCI::Statement& statement, const OCI::Type& type );

        HO_EXPORT void Initialize( UInt32 positon ) override;

        HO_EXPORT virtual OCI::Object* AsObject( ) const override;
        
    };

    /// <summary>
    /// CollectionDefine
    /// </summary>
    class CollectionDefine : public Define
    {
        using Base = Define;
        const OCI::Type* type_;
        void* handle_;
    public:
        constexpr CollectionDefine( ) noexcept
            : Base( ), type_(nullptr), handle_(nullptr)
        {
        }
        HO_EXPORT CollectionDefine( const OCI::Statement& statement, const OCI::Type& type );

        HO_EXPORT void Initialize( UInt32 positon ) override;

        HO_EXPORT virtual OCI::Collection* AsCollection( ) const override;
    };

    

    /// <summary>
    /// LobDefine
    /// </summary>
    template<OCI::OraType oracleType>
    class LobBaseDefine : public DescriptorDefine< OCILobLocator, OCI::HandleType::LOB, oracleType>
    {
    public:
        using Base = DescriptorDefine< OCILobLocator, OCI::HandleType::LOB, oracleType>;
    private:
        
    public:
        constexpr LobBaseDefine( ) noexcept
            : Base( )
        {
        }

        explicit LobBaseDefine( const OCI::Statement& statement )
            : Base( statement )
        {
        }
        
        virtual LobStream AsStream( ) const final override
        {
            return LobStream( ServiceContext( ), Base::Value( ) );
        }
        
    };

    /// <summary>
    /// CLobBaseDefine
    /// </summary>
    template<OCI::OraType oracleType,OCI::CharacterSetForm characterSetFormDefault>
    class CLobBaseDefine : public LobBaseDefine<oracleType>
    {
    public:
        using Base = LobBaseDefine<oracleType>;
        static constexpr OCI::CharacterSetForm CharacterSetFormDefault = characterSetFormDefault;

        constexpr CLobBaseDefine( ) noexcept
            : Base( )
        {
        }

        explicit CLobBaseDefine( const OCI::Statement& statement )
            : Base( statement )
        {
        }

        virtual WideString AsString( ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return LobReadWideString( serviceContext, error, Base::Value( ), CharacterSetFormDefault );
        }

    };


    using CLOBDefine = CLobBaseDefine<OraType::CLOB, OCI::CharacterSetForm::Implicit>;
    using CFileDefine = CLobBaseDefine<OraType::CFILEE, OCI::CharacterSetForm::Implicit>;
    using NCLOBDefine = CLobBaseDefine<OraType::CLOB, OCI::CharacterSetForm::NChar>;

    using BLOBDefine = LobBaseDefine<OraType::BLOB>;
    using BFileDefine = LobBaseDefine<OraType::BFILEE>;
    


    /// <summary>
    /// LobArrayBaseDefine
    /// </summary>
    template<OCI::OraType oracleType>
    class LobArrayBaseDefine : public DescriptorArrayDefine< OCILobLocator, OCI::HandleType::LOB, oracleType>
    {
        using Base = DescriptorArrayDefine< OCILobLocator, OCI::HandleType::LOB, oracleType>;
    public:
        LobArrayBaseDefine( ) noexcept
            : Base( )
        {
        }
        LobArrayBaseDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
            
        }
        
        virtual LobStream AsStream( size_t index ) const final override
        {
            return LobStream( Base::ServiceContext( ), Base::Value( index ) );
        }
        
    };

    template<OCI::OraType oracleType, OCI::CharacterSetForm characterSetFormDefault>
    class CLobArrayBaseDefine : public LobArrayBaseDefine<oracleType>
    {
    public:
        using Base = LobArrayBaseDefine<oracleType>;
        static constexpr OCI::CharacterSetForm CharacterSetFormDefault = characterSetFormDefault;
    public:

        CLobArrayBaseDefine( ) noexcept
            : Base( )
        {
        }
        CLobArrayBaseDefine( const OCI::Statement& statement, size_t size )
            : Base( statement, size )
        {
        }
            

        virtual WideString AsString( size_t index ) const final override
        {
            auto& serviceContext = Base::ServiceContext( );
            auto& error = Base::Error( );
            return LobReadWideString( serviceContext, error, Base::Value( index ), CharacterSetFormDefault );
        }
    };

    using CLOBArrayDefine = CLobArrayBaseDefine<OraType::CLOB,OCI::CharacterSetForm::Implicit>;
    using NCLOBArrayDefine = CLobArrayBaseDefine<OraType::CLOB, OCI::CharacterSetForm::NChar>;
    using CFileArrayDefine = CLobArrayBaseDefine<OraType::CFILEE, OCI::CharacterSetForm::Implicit>;

    using BLOBArrayDefine = LobArrayBaseDefine<OraType::BLOB>;
    using BFileArrayDefine = LobArrayBaseDefine<OraType::BFILEE>;
    


    /// <summary>
    /// DataReaderBase
    /// Implements functionality common to DataReader and ArrayDataReader
    /// </summary>
    /// <typeparam name="DerivedT">The derived implementation</typeparam>
    /// <typeparam name="DefineT">The base class for the defines allowed by the derived implementation</typeparam>
    template<typename DerivedT, typename DefineT>
    class DataReaderBase
    {
    public:
        using DefineType = DefineT;
        using DerivedType = DerivedT;
    protected:
        const OCI::Statement* statement_;
        std::vector< std::unique_ptr< DefineType > > defines_;
        size_t currentRowIndex_;
        size_t rowsFetched_;
        bool noMoreData_;
    
        DataReaderBase( const OCI::Statement& statement ) noexcept
            : statement_( &statement ), currentRowIndex_( 0 ), rowsFetched_( 0 ), noMoreData_( false )
        {
        }

        const OCI::Statement& Statement( ) const noexcept
        {
            return *statement_;
        }
        const OCI::ServiceContext& ServiceContext( ) const noexcept
        {
            return statement_->ServiceContext( );;
        }
        const OCI::ErrorHandle& Error( ) const noexcept
        {
            return statement_->Error( );
        }
        const OCI::Environment& Environment( ) const
        {
            return statement_->Environment( );
        }

    public:
        size_t CurrentRowIndex( ) const noexcept
        {
            return currentRowIndex_;
        }
        size_t RowsFetched( ) const noexcept
        {
            return rowsFetched_;
        }

        DefineType* GetDefine( UInt32 index ) const noexcept
        {
            return defines_[index].get( );
        }

        bool Read( )
        {
            currentRowIndex_++;
            if ( currentRowIndex_ >= rowsFetched_ )
            {
                if ( noMoreData_ )
                {
                    return false;
                }
                static_cast<DerivedType*>(this)->Fetch( );
                currentRowIndex_++;
                return rowsFetched_ > 0 ? true : false;
            }
            return true;
        }

    private:
        [[nodiscard]] bool IsDBNull( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->IsDBNull( index );
        }
    public:


        template<typename T>
        [[nodiscard]] T As(UInt32 i) const;
        
        template<>
        [[nodiscard]] bool As<bool>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>(this)->GetBoolean( index );
        }
        template<>
        [[nodiscard]] std::optional<bool> As<std::optional<bool>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetBoolean( index ) ) 
                : std::optional<bool>( );
        }

        template<>
        [[nodiscard]] SByte As<SByte>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetSByte( index );
        }
        template<>
        [[nodiscard]] std::optional<SByte> As<std::optional<SByte>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetSByte( index ) )
                : std::optional<SByte>( );
        }

        template<>
        [[nodiscard]] Byte As<Byte>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetByte( index );
        }
        template<>
        [[nodiscard]] std::optional<Byte> As<std::optional<Byte>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetByte( index ) )
                : std::optional<Byte>( );
        }

        template<>
        [[nodiscard]] Int16 As<Int16>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetInt16( index );
        }
        template<>
        [[nodiscard]] std::optional<Int16> As<std::optional<Int16>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetInt16( index ) )
                : std::optional<Int16>( );
        }

        template<>
        [[nodiscard]] UInt16 As<UInt16>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetUInt16( index );
        }
        template<>
        [[nodiscard]] std::optional<UInt16> As<std::optional<UInt16>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetUInt16( index ) )
                : std::optional<UInt16>( );
        }

        template<>
        [[nodiscard]] Int32 As<Int32>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetInt32( index );
        }
        template<>
        [[nodiscard]] std::optional<Int32> As<std::optional<Int32>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetInt32( index ) )
                : std::optional<Int32>( );
        }

        template<>
        [[nodiscard]] UInt32 As<UInt32>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetUInt32( index );
        }
        template<>
        [[nodiscard]] std::optional<UInt32> As<std::optional<UInt32>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetUInt32( index ) )
                : std::optional<UInt32>( );
        }

        template<>
        [[nodiscard]] Int64 As<Int64>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetInt64( index );
        }
        template<>
        [[nodiscard]] std::optional<Int64> As<std::optional<Int64>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetInt64( index ) )
                : std::optional<Int64>( );
        }

        template<>
        [[nodiscard]] UInt64 As<UInt64>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetUInt64( index );
        }
        template<>
        [[nodiscard]] std::optional<UInt64> As<std::optional<UInt64>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetUInt64( index ) )
                : std::optional<UInt64>( );
        }

        template<>
        [[nodiscard]] Single As<Single>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetSingle( index );
        }
        template<>
        [[nodiscard]] std::optional<Single> As<std::optional<Single>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetSingle( index ) )
                : std::optional<Single>( );
        }

        template<>
        [[nodiscard]] Double As<Double>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetDouble( index );
        }
        template<>
        [[nodiscard]] std::optional<Double> As<std::optional<Double>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetDouble( index ) )
                : std::optional<Double>( );
        }

        template<>
        [[nodiscard]] DateTime As<DateTime>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetDateTime( index );
        }
        template<>
        [[nodiscard]] std::optional<DateTime> As<std::optional<DateTime>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetDateTime( index ) )
                : std::optional<DateTime>( );
        }

        template<>
        [[nodiscard]] TimeSpan As<TimeSpan>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetTimeSpan( index );
        }
        template<>
        [[nodiscard]] std::optional<TimeSpan> As<std::optional<TimeSpan>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetTimeSpan( index ) )
                : std::optional<TimeSpan>( );
        }

        template<>
        [[nodiscard]] Guid As<Guid>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetGuid( index );
        }
        template<>
        [[nodiscard]] std::optional<Guid> As<std::optional<Guid>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetGuid( index ) )
                : std::optional<Guid>( );
        }

        template<>
        [[nodiscard]] WideString As<WideString>( UInt32 index ) const
        {
            return static_cast<const DerivedType*>( this )->GetString( index );
        }
        template<>
        [[nodiscard]] std::optional<WideString> As<std::optional<WideString>>( UInt32 index ) const
        {
            return IsDBNull( index ) == false ?
                std::optional( static_cast<const DerivedType*>( this )->GetString( index ) )
                : std::optional<WideString>( );
        }
    };



    /// <summary>
    /// Provides access to the column values within each row
    /// </summary>
    class DataReader : public DataReaderBase<DataReader, OCI::Define>
    {
        friend class Statement;

        template<typename DerivedT, typename DefineT>
        friend class DataReaderBase;
    public:
        using Base = DataReaderBase<DataReader, OCI::Define>;
    public:
        DataReader( const OCI::Statement& statement ) noexcept
            : Base( statement )
        { }

        template<typename DT, typename ...ArgTypes>
            requires std::is_base_of_v<OCI::Define, DefineType>
        DT* Define( UInt32 position, ArgTypes&&... args )
        {
            auto define = std::make_unique<DT>( *statement_, std::forward<ArgTypes>(args)... );
            define->Initialize( position );
            auto* result = define.get( );
            defines_.emplace_back( std::move(define) );
            return result;
        }

        template<typename DefineType, typename ...ArgTypes>
            requires Internal::HasTraits<DefineType>
        typename Internal::Traits<DefineType>::DefineType* Define( UInt32 position, ArgTypes... args )
        {
            return Define<typename Internal::Traits<DefineType>::DefineType>( position, std::forward<ArgTypes>( args )... );
        }

    protected:
        HO_EXPORT virtual void InitializeDefines( );


        void Fetch( )
        {
            auto rc = statement_->Fetch( static_cast<UInt32>( 1 ) );
            rowsFetched_ = statement_->RowsFetched( );
            currentRowIndex_ = static_cast<size_t>( -1 );
            noMoreData_ = rc == Result::NoData ? true : false;
        }
        void Prefetch( Int32 executeResult )
        {
            rowsFetched_ = statement_->RowsFetched( );
            currentRowIndex_ = static_cast<size_t>( -1 );
            noMoreData_ = executeResult == Result::NoData ? true : false;
        }
    public:    
        /// <summary>
        /// Return whether the specified field is set to null.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>true if the specified field is set to null; otherwise, false.</returns>
        [[nodiscard]] bool IsDBNull( UInt32 index ) const
        {
            auto define = GetDefine( index );
            return define->Indicator( ) == -1;
        }

        /// <summary>
        /// Gets the value of the specified column as a bool.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] bool GetBoolean( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsBoolean( );
        }
        /// <summary>
        /// Gets the value of the specified column as a Byte.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Byte GetByte( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsByte( );
        }

        /// <summary>
        /// Gets the value of the specified column as a SByte.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] SByte GetSByte( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsSByte( );
        }

        /// <summary>
        /// Gets the value of the specified column as a Int16.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Int16 GetInt16( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsInt16( );
        }
        /// <summary>
        /// Gets the value of the specified column as a UInt16.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] UInt16 GetUInt16( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsUInt16( );
        }

        /// <summary>
        /// Gets the value of the specified column as a Int32.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Int32 GetInt32( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsInt32( );
        }
        /// <summary>
        /// Gets the value of the specified column as a UInt32.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] UInt32 GetUInt32( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsUInt32( );
        }
        /// <summary>
        /// Gets the value of the specified column as a Int64.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Int64 GetInt64( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsInt64( );
        }
        /// <summary>
        /// Gets the value of the specified column as a UInt64.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] UInt64 GetUInt64( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsUInt64( );
        }
        /// <summary>
        /// Gets the value of the specified column as a float.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] float GetSingle( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsSingle( );
        }
        /// <summary>
        /// Gets the value of the specified column as a double.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] double GetDouble( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsDouble( );
        }
        /// <summary>
        /// Gets the value of the specified column as a DateTime.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] DateTime GetDateTime( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsDateTime( );
        }
        /// <summary>
        /// Gets the value of the specified column as a TimeSpan.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] TimeSpan GetTimeSpan( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsTimeSpan( );
        }
        /// <summary>
        /// Gets the value of the specified column as a Guid.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Guid GetGuid( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsGuid( );
        }
        /// <summary>
        /// Gets the value of the specified column as a WideString.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] WideString GetString( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsString( );
        }

        [[nodiscard]] OCI::Object* GetObject( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsObject( );
        }
        [[nodiscard]] OCI::Collection* GetCollection( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsCollection( );
        }
        
        [[nodiscard]] LobStream GetStream( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsStream( );
        }
        
    };

    namespace Internal
    {
        template<typename T>
        class ScalarDataReader : public DataReader
        {
        public:
            using Base = DataReader;
            using DefineType = typename Traits<T>::DefineType;
            constexpr static UInt32 FieldId = 0;
        public:
            ScalarDataReader( const OCI::Statement& statement )
                : Base( statement )
            {
            }

            virtual void InitializeDefines( ) override
            {
                Define<DefineType>( FieldId + 1 );
            }
        };
    }

    template<typename T, WideStringLike StringT>
    inline std::optional<T> ServiceContext::ExecuteScalar( const StringT& sql ) const
    {
        auto statement = CreateStatement( sql );
        auto reader = statement.ExecuteReader<Internal::ScalarDataReader<T>>( );
        if ( reader->Read( ) )
        {
            return reader->As<std::optional<T>>( Internal::ScalarDataReader<T>::FieldId );
        }
        return std::optional<T>( );
    }

    template<typename T>
    inline std::optional<T> Statement::ExecuteScalar( )
    {
        auto reader = ExecuteReader<Internal::ScalarDataReader<T>>( );
        if ( reader->Read( ) )
        {
            return reader->As<std::optional<T>>( Internal::ScalarDataReader<T>::FieldId );
        }
        return std::optional<T>( );
    }


    /// <summary>
    /// Provides access to the column values within each row
    /// </summary>
    /// <remarks>
    /// Internally ArrayDataReader retrieves multiple rows from the database on each fetch
    /// significantly improving read performance. 
    /// </remarks>
    class ArrayDataReader : public DataReaderBase<ArrayDataReader,OCI::ArrayDefine>
    {
        friend class Statement;
        template<typename DerivedT, typename DefineT>
        friend class DataReaderBase;
    public:
        using Base = DataReaderBase<ArrayDataReader, OCI::ArrayDefine>;
    private:
        size_t rowCount_;
    public:
        ArrayDataReader( const OCI::Statement& statement, size_t rowCount )
            : Base( statement ), rowCount_( rowCount )
        { }

        template<typename DefineType, typename ...ArgTypes>
            requires std::is_base_of_v<ArrayDefine, DefineType>
        DefineType* Define( UInt32 position, ArgTypes... args )
        {
            auto define = std::make_unique<DefineType>( *statement_, rowCount_, std::forward<ArgTypes>( args )... );
            define->Initialize( position );
            auto* result = define.get( );
            defines_.emplace_back( std::move(define) );
            return result;
        }

        template<typename DefineType, typename ...ArgTypes>
            requires Internal::HasTraits<DefineType>
        typename Internal::Traits<DefineType>::ArrayDefineType* Define( UInt32 position, ArgTypes... args )
        {
                return Define<typename Internal::Traits<DefineType>::ArrayDefineType>( position, std::forward<ArgTypes>( args )... );
        }

    protected:
        void Fetch( )
        {
            auto rc = statement_->Fetch( static_cast<UInt32>( rowCount_ ) );
            rowsFetched_ = statement_->RowsFetched( );
            currentRowIndex_ = static_cast<size_t>( -1 );
            noMoreData_ = rc == Result::NoData ? true : false;
        }
        void Prefetch( Int32 executeResult )
        {
            rowsFetched_ = statement_->RowsFetched( );
            currentRowIndex_ = static_cast<size_t>( -1 );
            noMoreData_ = executeResult == Result::NoData ? true : false;
        }


        HO_EXPORT virtual void InitializeDefines( );
    public:
        /// <summary>
        /// Return whether the specified field is set to null.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>true if the specified field is set to null; otherwise, false.</returns>
        [[nodiscard]] bool IsDBNull( UInt32 index ) const
        {
            auto define = GetDefine( index );
            return define->Indicator( currentRowIndex_ ) == -1;
        }

        const void* GetData( UInt32 index ) const noexcept
        {
            auto define = GetDefine( index );
            return define->Data( currentRowIndex_ );
        }

        /// <summary>
        /// Gets the value of the specified column as a bool.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] bool GetBoolean( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsBoolean( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a Byte.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Byte GetByte( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsByte( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a SByte.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] SByte GetSByte( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsSByte( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as an Int16.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Int16 GetInt16( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsInt16( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as an UInt16.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] UInt16 GetUInt16( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsUInt16( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as an Int32.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Int32 GetInt32( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsInt32( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as an UInt32.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] UInt32 GetUInt32( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsUInt32( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as an Int64.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Int64 GetInt64( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsInt64( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as an UInt64.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] UInt64 GetUInt64( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsUInt64( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a float.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] float GetSingle( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsSingle( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a double.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] double GetDouble( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsDouble( currentRowIndex_ );
        }

        /// <summary>
        /// Gets the value of the specified column as a DateTime.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] DateTime GetDateTime( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsDateTime( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a TimeSpan.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] TimeSpan GetTimeSpan( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsTimeSpan( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a Guid.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] Guid GetGuid( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsGuid( currentRowIndex_ );
        }
        /// <summary>
        /// Gets the value of the specified column as a std::wsrting.
        /// </summary>
        /// <param name="index">The index of the field to find.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] WideString GetString( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsString( currentRowIndex_ );
        }
        [[nodiscard]] OCI::Object* GetObject( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsObject( currentRowIndex_ );
        }
        [[nodiscard]] OCI::Collection* GetCollection( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsCollection( currentRowIndex_ );
        }
        
        [[nodiscard]] LobStream GetStream( UInt32 i ) const
        {
            auto define = GetDefine( i );
            return define->AsStream( currentRowIndex_ );
        }
        
    };

	
    /// <summary>
    /// ParameterDescriptor
    /// </summary>
    class ParameterDescriptor : public Descriptor
    {
        using Base = Descriptor;
    public:
        constexpr ParameterDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr ParameterDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, OCI::HandleType::PARAM, handle, ownsHandle )
        {
        }
        explicit ParameterDescriptor( const OCI::ServiceContext& serviceContext )
            : Base( serviceContext, OCI::HandleType::PARAM )
        {
        }


        HO_EXPORT static std::unique_ptr<ParameterDescriptor> CreateParameter( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle = true );

    protected:
        /// <summary>
        /// Retrieves the ParameterDescriptor at index
        /// </summary>
        /// <param name="index">*note* index is 1 based</param>
        /// <returns></returns>
        HO_EXPORT std::unique_ptr<ParameterDescriptor> GetChildDescriptor( size_t index ) const;
        HO_EXPORT std::unique_ptr<ParameterDescriptor> GetChildDescriptor( void* listHandle ,size_t index ) const;
    public:

        /// <summary>
        /// The timestamp of the object on which the description is based
        /// </summary>
        DateTime Timestamp( ) const
        {
            return GetDateTimeAttribute( Attribute::TIMESTAMP );
        }
    };

    /// <summary>
    /// ListDescriptor
    /// </summary>
    class ListDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr ListDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr ListDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        /// <summary>
        /// Retrieves the type of the list
        /// </summary>
        /// <returns>Type of the list</returns>
        ParameterListType Type( ) const
        {
            return static_cast<ParameterListType>( GetByteAttribute( Attribute::LTYPE ) );
        }

        /// <summary>
        /// Returns the number of elements in the list
        /// </summary>
        UInt32 NumParams( ) const
        {
            return GetUInt32Attribute( Attribute::NUM_PARAMS );
        }
    private:
        HO_EXPORT std::unique_ptr<ParameterDescriptor> _Parameter( UInt32 index ) const;
    public:

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T">Type of parameter to retrieve</typeparam>
        /// <param name="index">index of parameter to retrive (Depending on the type of the list this can be 0 or 1 based)</param>
        /// <returns>The requested parameter</returns>
        template<typename T>
        requires std::is_base_of_v<ParameterDescriptor, T>
            std::unique_ptr<T> Parameter( UInt32 index ) const
        {
            auto param = _Parameter( index );
            return std::unique_ptr<T>( static_cast<T*>( param.release( ) ) );
        }


    };

    
    /// <summary>
    /// TableViewBaseDescriptor
    /// </summary>
    class TableViewBaseDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr TableViewBaseDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr TableViewBaseDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle = true ) noexcept
            : Base( serviceContext, handle, ownsHandle )
        {
        }

        /// <summary>
        /// Number of columns
        /// </summary>
        /// <returns>The number of columns</returns>
        UInt16 NumberOfColumns( ) const
        {
            return GetUInt16Attribute( OCI::Attribute::NUM_COLS );
        }

        /// <summary>
        /// Column list
        /// </summary>
        /// <returns>The column list</returns>
        HO_EXPORT std::vector<std::unique_ptr<OCI::ColumnDescriptor>> Columns( ) const;

        /// <summary>
        /// Indicates that the table is temporary
        /// </summary>
        /// <returns>true if the table is temporary</returns>
        bool IsTemporary( ) const
        {
            return GetBooleanAttribute( Attribute::IS_TEMPORARY );
        }

        /// <summary>
        /// Indicates that the table is typed
        /// </summary>
        /// <returns>true if the table is typed</returns>
        bool IsTyped( ) const
        {
            return GetBooleanAttribute( Attribute::IS_TYPED );
        }

        /// <summary>
        /// Duration of a temporary table.
        /// </summary>
        /// <returns>The duration of a temporary table.</returns>
        OCI::Duration Duration( ) const
        {
            return static_cast<OCI::Duration>(GetUInt16Attribute( Attribute::DURATION ));
        }



    };
	
    /// <summary>
    /// TableDescriptor
    /// </summary>
    class TableDescriptor : public TableViewBaseDescriptor
    {
        using Base = TableViewBaseDescriptor;
    public:
        constexpr TableDescriptor( ) noexcept
            : Base( )
        {
        }
        TableDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle = true )
            : Base( serviceContext, handle, ownsHandle )
        { }

        /// <summary>
        /// Indicates that the table is clustered
        /// </summary>
        /// <returns>true if the table is clustered</returns>
        bool IsClustered( ) const
        {
            return GetBooleanAttribute( Attribute::CLUSTERED );
        }

        /// <summary>
        /// Indicates that the table is partitioned
        /// </summary>
        /// <returns>true the table is partitioned</returns>
        bool IsPartitioned( ) const
        {
            return GetBooleanAttribute( Attribute::PARTITIONED );
        }

        /// <summary>
        /// Indicates that the table is index-only
        /// </summary>
        /// <returns>true the table is index-only</returns>
        bool IsIndexOnly( ) const
        {
            return GetBooleanAttribute( Attribute::INDEX_ONLY );
        }


    };

    /// <summary>
    /// ViewDescriptor
    /// </summary>
    class ViewDescriptor : public TableViewBaseDescriptor
    {
        using Base = TableViewBaseDescriptor;
    public:
        constexpr ViewDescriptor( ) noexcept
            : Base( )
        {
        }

        ViewDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle = true )
            : Base( serviceContext, handle, ownsHandle )
        { }
    };
	
    /// <summary>
    /// ColumnDescriptor
    /// </summary>
    class ColumnDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr ColumnDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr ColumnDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle = true )
            : Base( serviceContext, handle, ownsHandle )
        { }

        /// <summary>
        /// Returns the type of length semantics of the column. Zero (0) means
        /// byte-length semantics and 1 means character-length semantics.
        /// </summary>
        bool UsesCharacterLength( ) const
        {
            return GetByteAttribute( Attribute::CHAR_USED ) != 0;
        }

        /// <summary>
        /// Returns the column character length that is the number of characters
        /// allowed in the column.
        /// </summary>
        UInt16 CharacterLength( ) const
        {
            return GetUInt16Attribute( Attribute::CHAR_SIZE );
        }

        

        /// <summary>
        /// The maximum size of the column. This length is returned in bytes and 
        /// not characters for strings and raws. It returns 22 for NUMBERs.
        /// (OCI_ATTR_DATA_SIZE)
        /// </summary>
        UInt16 Length( ) const
        {
            return GetUInt16Attribute( static_cast<Attribute>( DescribeAttribute::DATA_SIZE ) );
        }

        /// <summary>
        /// Returns describe data regarding certain column properties
        /// </summary>
        /// <returns>The ColumnProperties for the column</returns>
        ColumnProperties Properties( ) const
        {
            return static_cast<ColumnProperties>( GetUInt64Attribute( static_cast<Attribute>( Attribute::COL_PROPERTIES ) ) );
        }

        /// <summary>
        /// Returns whether a column is invisible or not.
        /// </summary>
        /// <returns>true if the column is invisible</returns>
        bool IsInvisible( ) const
        {
            return GetBooleanAttribute( Attribute::INVISIBLE_COL );
        }

        /// <summary>
        /// The datatype of the column. (OCI_ATTR_DATA_TYPE)
        /// </summary>
        OraType DataType( ) const
        {
            return static_cast<OraType>( GetUInt16Attribute( DescribeAttribute::DATA_TYPE ) );
        }

        /// <summary>
        /// the column name (OCI_ATTR_NAME)
        /// </summary>
        WideString Name( ) const
        {
            return GetStringAttribute( static_cast<Attribute>( DescribeAttribute::NAME ) );
        }

        /// <summary>
        /// The precision of numeric columns. If the precision is nonzero and scale 
        /// is -127, then it is a FLOAT, else it is a NUMBER(precision, scale). 
        /// For the case when precision is 0, NUMBER(precision, scale) can be 
        /// represented simply as NUMBER. (OCI_ATTR_PRECISION)
        /// </summary>
        Int16 Precision( bool implicitDescribe = true ) const
        {
            if ( implicitDescribe )
            {
                return GetInt16Attribute( DescribeAttribute::PRECISION );
            }
            else
            {
                return GetSByteAttribute( DescribeAttribute::PRECISION );
            }
        }

        

        /// <summary>
        /// The scale of numeric columns. If the precision is nonzero and 
        /// scale is -127, then it is a FLOAT, else it is a NUMBER(precision, scale). 
        /// For the case when precision is 0, NUMBER(precision, scale) can be 
        /// represented simply as NUMBER. (OCI_ATTR_SCALE)
        /// </summary>
        SByte Scale( ) const
        {
            return GetSByteAttribute( DescribeAttribute::SCALE );
        }

        /// <summary>
        /// Returns false if null values are not permitted for the column. Does not
        /// return a correct value for a CUBE or ROLLUP operation. (OCI_ATTR_IS_NULL)
        /// </summary>
        bool IsNull( ) const
        {
            return GetByteAttribute( DescribeAttribute::IS_NULL );
        }
        bool Nullable( ) const
        {
            return IsNull( );
        }

        /// <summary>
        /// Returns a string that is the type name. The returned value contains
        /// the type name if the data type is SQLT_NTY or SQLT_REF.If the data
        /// type is SQLT_NTY, the name of the named data type's type is returned.
        /// If the data type is SQLT_REF, the type name of the named data type
        /// pointed to by the REF is returned. (OCI_ATTR_TYPE_NAME)
        /// </summary>
        WideString TypeName( ) const
        {
            return GetStringAttribute( DescribeAttribute::TYPE_NAME );
        }

        /// <summary>
        /// Returns a string with the schema name under which the type has
        /// been created (OCI_ATTR_SCHEMA_NAME)
        /// </summary>
        WideString SchemaName( ) const
        {
            return GetStringAttribute( DescribeAttribute::SCHEMA_NAME );
        }

        /// <summary>
        /// Character set form of the handle.
        /// </summary>
        OCI::CharacterSetForm CharacterSetForm( ) const
        {
            return static_cast<OCI::CharacterSetForm>( GetByteAttribute(Attribute::CHARSET_FORM) );
        }



    };

    /// <summary>
    /// ArgumentDescriptor
    /// </summary>
    class ArgumentDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr ArgumentDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr ArgumentDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        /// <summary>
        /// Retrieves the argument name
        /// </summary>
        WideString Name( ) const
        {
            return GetStringAttribute( DescribeAttribute::NAME );
        }

        /// <summary>
        /// Retreives the Typecode of the argument
        /// </summary>
        OCI::TypeCode TypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( Attribute::TYPECODE ) );
        }

        /// <summary>
        /// Retreives the datatype of the argument
        /// </summary>
        OCI::OraType DataType( ) const
        {
            return static_cast<OCI::OraType>( GetUInt16Attribute( DescribeAttribute::DATA_TYPE ) );
        }

        /// <summary>
        /// The size of the data type of the argument. This length is returned in bytes
        /// and not characters for strings and raws.It returns 22 for NUMBERs.
        /// </summary>
        UInt16 Length( ) const
        {
            GetUInt16Attribute( DescribeAttribute::DATA_SIZE );
        }

        /// <summary>
        /// The precision of numeric arguments. If the precision is nonzero and scale
        /// is -127, then it is a FLOAT; otherwise, it is a NUMBER(precision,
        /// scale). When precision is 0, NUMBER(precision, scale) can be
        /// represented simply as NUMBER.
        /// </summary>
        /// <param name="implicitDescribe"></param>
        /// <returns></returns>
        Int16 Precision( bool implicitDescribe = true ) const
        {
            if ( implicitDescribe )
            {
                return GetInt16Attribute( DescribeAttribute::PRECISION );
            }
            else
            {
                return GetSByteAttribute( DescribeAttribute::PRECISION );
            }
        }

        /// <summary>
        /// The scale of numeric arguments. If the precision is nonzero and scale is
        /// -127, then it is a FLOAT; otherwise, it is a NUMBER(precision, scale).
        /// When precision is 0, NUMBER(precision, scale) can be represented
        /// simply as NUMBER.
        /// </summary>
        SByte Scale( ) const
        {
            return GetSByteAttribute( DescribeAttribute::SCALE );
        }


        /// <summary>
        /// Indicates whether an argument has a default
        /// </summary>
        bool HasDefault( ) const
        {
            return GetBooleanAttribute( Attribute::HAS_DEFAULT );
        }

        /// <summary>
        /// The list of arguments at the next level (when the argument is of a 
        /// record or table type)
        /// </summary>
        std::unique_ptr<ListDescriptor> ListArguments( ) const
        {
            OCIParam* listDescriptorHandle = (OCIParam*)GetPointerAttribute( Attribute::LIST_ARGUMENTS );
            auto& serviceContext = this->ServiceContext( );
            std::unique_ptr<ListDescriptor> result( static_cast<ListDescriptor*>( CreateParameter( serviceContext, listDescriptorHandle, false ).release( ) ) );
            return result;
        }

        /// <summary>
        /// Indicates the argument In/Out/InOut mode
        /// </summary>
        TypeParamMode InOutMode( ) const
        {
            return static_cast<TypeParamMode>( GetInt32Attribute( Attribute::IOMODE ) );
        }

        /// <summary>
        /// Returns a radix (if number type)
        /// </summary>
        Byte Radix( ) const
        {
            return GetByteAttribute( Attribute::RADIX );
        }

        /// <summary>
        /// Returns false if null values are not permitted for the column
        /// </summary>
        /// <returns></returns>
        bool IsNull( ) const
        {
            GetBooleanAttribute( DescribeAttribute::IS_NULL );
        }
        /// <summary>
        /// Returns false if null values are not permitted for the column
        /// </summary>
        /// <returns></returns>
        bool Nullable( ) const
        {
            IsNull( );
        }

        /// <summary>
        /// Returns a string that is the type name or the package name for package
        /// local types. The returned value contains the type name if the data type is
        /// SQLT_NTY or SQLT_REF. If the data type is SQLT_NTY, the name of the
        /// named data type's type is returned. If the data type is SQLT_REF, the type
        /// name of the named data type pointed to by the REF is returned.
        /// </summary>
        WideString TypeName( ) const
        {
            return GetStringAttribute( DescribeAttribute::TYPE_NAME );
        }

        /// <summary>
        /// For SQLT_NTY or SQLT_REF, returns a string with the schema name
        /// under which the type was created, or under which the package was
        /// created for package local types
        /// </summary>
        WideString SchemaName( ) const
        {
            return GetStringAttribute( DescribeAttribute::SCHEMA_NAME );
        }

        /// <summary>
        /// For SQLT_NTY or SQLT_REF, returns a string with the type name, 
        /// for package local types
        /// </summary>
        WideString SubName( ) const
        {
            return GetStringAttribute( DescribeAttribute::SUB_NAME );
        }

        /// <summary>
        /// For SQLT_NTY or SQLT_REF, returns a string with the database link name
        /// of the database on which the type exists.This can happen only for
        /// package local types, when the package is remote.
        /// </summary>
        WideString Link( ) const
        {
            return GetStringAttribute( Attribute::LINK );
        }

        /// <summary>
        /// Character set form.
        /// </summary>
        OCI::CharacterSetForm CharacterSetForm( ) const
        {
            return static_cast<OCI::CharacterSetForm>( GetByteAttribute( Attribute::CHARSET_FORM ) );
        }

    };

	
    /// <summary>
    /// ProcedureOrFunctionDescriptor
    /// </summary>
    class ProcedureOrFunctionDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr ProcedureOrFunctionDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr ProcedureOrFunctionDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        std::unique_ptr<ListDescriptor> ArgumentList( ) const
        {
            OCIParam* listDescriptorHandle = (OCIParam*)GetPointerAttribute( Attribute::LIST_ARGUMENTS );
            auto& serviceContext = this->ServiceContext( );
            std::unique_ptr<ListDescriptor> result( static_cast<ListDescriptor*>( CreateParameter( serviceContext, listDescriptorHandle, false ).release( ) ) );
            return result;
        }

        std::vector< std::unique_ptr<ArgumentDescriptor>> Arguments( ) const
        {
            auto argumentList = ArgumentList( );
            auto argumentListSize = argumentList->NumParams( );
            std::vector< std::unique_ptr<ArgumentDescriptor>> result;
            result.reserve( argumentListSize );
            for ( UInt32 i = 0; i < argumentListSize; i++ )
            {
                auto argumentDescriptor = argumentList->Parameter<ArgumentDescriptor>( i );
                result.emplace_back( std::move( argumentDescriptor ) );
            }
            return result;
        }


    };

    /// <summary>
    /// ProcedureDescriptor
    /// </summary>
    class ProcedureDescriptor : public ProcedureOrFunctionDescriptor
    {
        using Base = ProcedureOrFunctionDescriptor;
    public:
        constexpr ProcedureDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr ProcedureDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        { }
    };

    /// <summary>
    /// FunctionDescriptor
    /// </summary>
    class FunctionDescriptor : public ProcedureOrFunctionDescriptor
    {
        using Base = ProcedureOrFunctionDescriptor;
    public:
        constexpr FunctionDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr FunctionDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// PackageDescriptor
    /// </summary>
    class PackageDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr PackageDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr PackageDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// TypeAttributeInfo
    /// </summary>
    class TypeAttributeInfo
    {
        OCI::TypeCode typeCode_;
        UInt16 precision_;
        char scale_;
        size_t dataSize_;
        size_t offset_;
        OCIRef* type_;
    public:
        constexpr TypeAttributeInfo( ) noexcept
            : typeCode_( OCI::TypeCode::Unknown ), precision_( 0 ), scale_( 0 ), dataSize_( 0 ), offset_( 0 ), type_(nullptr)
        { }

        constexpr TypeAttributeInfo( OCI::TypeCode typeCode, UInt16 precision, char scale, size_t dataSize, size_t offset, OCIRef* type ) noexcept
            : typeCode_( typeCode ), precision_( precision ), scale_( scale ), dataSize_( dataSize ), offset_( offset ), type_( type )
        { }

        constexpr TypeAttributeInfo( OCI::TypeCode typeCode, UInt16 precision, char scale, size_t dataSize, size_t offset ) noexcept
            : typeCode_( typeCode ), precision_( precision ), scale_( scale ), dataSize_( dataSize ), offset_( offset ), type_( nullptr )
        {
        }

        constexpr TypeAttributeInfo( OCI::TypeCode typeCode, size_t dataSize, size_t offset ) noexcept
            : typeCode_( typeCode ), precision_( 0 ), scale_( 0 ), dataSize_( dataSize ), offset_( offset ), type_( nullptr )
        {
        }

        constexpr OCI::TypeCode TypeCode( ) const noexcept
        {
            return typeCode_;
        }
        constexpr UInt16 Precision( ) const noexcept
        {
            return precision_;
        }
        constexpr char Scale( ) const noexcept
        {
            return scale_;
        }
        constexpr size_t DataSize( ) const noexcept
        {
            return dataSize_;
        }
        constexpr size_t Offset( ) const noexcept
        {
            return offset_;
        }
        constexpr OCIRef* Type( ) const noexcept
        {
            return type_;
        }
    };
	
    /// <summary>
    /// TypeInfo
    /// </summary>
    class TypeInfo : public std::vector< TypeAttributeInfo >
    {
        size_t dataSize_;
    public:
        using Base = std::vector< TypeAttributeInfo >;
        HO_EXPORT TypeInfo( const TypeDescriptor* type );

        static constexpr size_t DataSizeOf( OCI::TypeCode typeCode, size_t ociDatasize ) noexcept
        {
            if ( ociDatasize )
            {
                return ociDatasize;
            }
            auto result = 8;
            switch ( typeCode )
            {
                case TypeCode::Time:
                    result = sizeof( OCI::Time );
                    break;
                case TypeCode::Date:
                    result = sizeof( OCI::Date );
                    break;
                case TypeCode::Integer:
                case TypeCode::BinaryFloat:
                    result = 4;
                    break;
            }
            return result;
        }

        static constexpr size_t AlignmentOf( TypeCode typeCode ) noexcept
        {
            size_t result = 8;
            switch ( typeCode )
            {
                case TypeCode::Byte:
                case TypeCode::SByte:
                result = 1;
                break;
                case TypeCode::Date:
                result = 2;
                break;
                case TypeCode::Integer:
                case TypeCode::BinaryFloat:
                result = 4;
                break;
            }
            return result;
        }


        static constexpr size_t Padding( size_t align, size_t offset ) noexcept
        {
            auto result = ( align - ( offset % align ) ) % align;
            return result;
        }
        static constexpr size_t Offset( size_t align, size_t offset ) noexcept
        {
            auto result = offset + Padding( align, offset );
            return result;
        }
        static constexpr size_t Offset( TypeCode typeCode, size_t offset ) noexcept
        {
            auto align = AlignmentOf( typeCode );
            auto result = offset + Padding( align, offset );
            return result;
        }

        constexpr size_t DataSize( ) const noexcept
        {
            return dataSize_;
        }


        OCI::TypeCode TypeCodeOf( size_t index ) const noexcept
        {
            return ( *this )[index].TypeCode( );
        }

        UInt16 PrecisionOf( size_t index ) const noexcept
        {
            return ( *this )[index].Precision( );
        }

        char ScaleOf( size_t index ) const noexcept
        {
            return ( *this )[index].Scale( );
        }

        size_t DataSizeOf( size_t index ) const noexcept
        {
            return ( *this )[index].DataSize( );
        }

        size_t OffsetOf( size_t index ) const noexcept
        {
            return ( *this )[index].Offset( );
        }

        constexpr size_t IndicatorIndexOf( size_t index ) const noexcept
        {
            return index;
        }

    };
	
    /// <summary>
    /// TypeDescriptor
    /// </summary>
    class TypeDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr TypeDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr TypeDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        OCI::TypeInfo TypeInfo( ) const
        {
            OCI::TypeInfo result( this );
            return result;
        }

        

        /// <summary>
        /// Returns the in-memory REF of the type descriptor object( TDO ) for the type, if the 
        /// column type is an object type.If space has not been reserved for the OCIRef, then it 
        /// is allocated implicitly in the cache. The caller can then pin the TDO with OCIObjectPin( ).
        /// (OCI_ATTR_REF_TDO)
        /// </summary>
        Ref TypeDescriptorObject( ) const;
        OCIRef* TDO( ) const
        {
            return (OCIRef*)GetPointerAttribute( Attribute::REF_TDO );
        }

        /// <summary>
        /// Returns either OCI::TypeCode::Object or OCI::TypeCode::NamedCollection
        /// </summary>
        OCI::TypeCode TypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( Attribute::TYPECODE ) );
        }

        /// <summary>
        /// Returns the Typecode of the collection if the type is a collection.
        /// Can be OCI::TypeCode::VArray or OCI::TypeCode::Table
        /// </summary>
        OCI::TypeCode CollectionTypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( Attribute::COLLECTION_TYPECODE ) );
        }

        /// <summary>
        /// Indicates this is an incomplete type
        /// </summary>
        bool IsIncompleteType( ) const
        {
            return GetByteAttribute( Attribute::IS_INCOMPLETE_TYPE ) ? true : false;
        }

        /// <summary>
        /// Indicates this is a system type
        /// </summary>
        bool IsSystemType( ) const
        {
            return GetByteAttribute( Attribute::IS_SYSTEM_TYPE ) ? true : false;
        }

        /// <summary>
        /// Indicates this is a predefined type
        /// </summary>
        bool IsPredefinedType( ) const
        {
            return GetByteAttribute( Attribute::IS_PREDEFINED_TYPE ) ? true : false;
        }

        /// <summary>
        /// Indicates this is a transient type
        /// </summary>
        bool IsTransientType( ) const
        {
            return GetByteAttribute( Attribute::IS_TRANSIENT_TYPE ) ? true : false;
        }

        /// <summary>
        /// Indicates this is a system-generated type
        /// </summary>
        bool IsSystemGeneratedType( ) const
        {
            return GetByteAttribute( Attribute::IS_SYSTEM_GENERATED_TYPE ) ? true : false;
        }

        /// <summary>
        /// This type contains a nested table attribute
        /// </summary>
        /// <returns></returns>
        bool HasNestedTable( ) const
        {
            return GetByteAttribute( Attribute::HAS_NESTED_TABLE ) ? true : false;
        }

        /// <summary>
        /// This type contains a LOB attribute
        /// </summary>
        bool HasLOBAttribute( ) const
        {
            return GetByteAttribute( Attribute::HAS_LOB ) ? true : false;
        }

        /// <summary>
        /// This type contains a BFILE attribute
        /// </summary>
        bool HasBFILEAttribute( ) const
        {
            return GetByteAttribute( Attribute::HAS_FILE ) ? true : false;
        }

        /// <summary>
        /// Handle to collection element
        /// </summary>
        std::unique_ptr<CollectionDescriptor> CollectionElement( );

        /// <summary>
        /// Number of type attributes
        /// </summary>
        size_t NumberOfTypeAttributes( ) const
        {
            return GetUInt16Attribute( Attribute::NUM_TYPE_ATTRS );
        }

        std::unique_ptr<OCI::TypeAttributeDescriptor> Attribute( size_t index ) const;
        std::vector<std::unique_ptr<OCI::TypeAttributeDescriptor>> Attributes( ) const;

        /// <summary>
        /// List of type attributes
        /// </summary>
        std::unique_ptr<ListDescriptor> AttributeList( ) const
        {
            OCIParam* listDescriptorHandle = (OCIParam*)GetPointerAttribute( Attribute::LIST_TYPE_ATTRS );
            auto& serviceContext = this->ServiceContext( );
            std::unique_ptr<ListDescriptor> result( static_cast<ListDescriptor*>( CreateParameter( serviceContext, listDescriptorHandle, false ).release( ) ) );
            return result;
        }



    };

    /// <summary>
    /// SynonymDescriptor
    /// </summary>
    class SynonymDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr SynonymDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr SynonymDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// SequenceDescriptor
    /// </summary>
    class SequenceDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr SequenceDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr SequenceDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };



    


    /// <summary>
    /// TypeAttributeDescriptor
    /// </summary>
    class TypeAttributeDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr TypeAttributeDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr TypeAttributeDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        /// <summary>
        /// The maximum size of the type attribute.This length is returned in bytes 
        /// and not characters for strings and raws.It returns 22 for NUMBERs.
        /// </summary>
        size_t DataSize( ) const
        {
            return GetUInt16Attribute( DescribeAttribute::DATA_SIZE );
        }

        /// <summary>
        /// Typecode
        /// </summary>
        OCI::TypeCode TypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( Attribute::TYPECODE ) );
        }

        /// <summary>
        /// The data type of the type attribute.
        /// </summary>
        OCI::TypeCode DataTypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( DescribeAttribute::DATA_TYPE ) );
        }

        /// <summary>
        /// type attribute name
        /// </summary>
        WideString Name( ) const
        {
            return GetStringAttribute( DescribeAttribute::NAME );
        }

        /// <summary>
        /// The precision of numeric type attributes. If the precision is nonzero and 
        /// scale is - 127, then it is a FLOAT; otherwise, it is a NUMBER( precision, scale ).
        /// When precision is 0, NUMBER( precision, scale ) can be represented simply as NUMBER.
        /// </summary>
        Int16 Precision( ) const
        {
            return GetByteAttribute( DescribeAttribute::PRECISION );
        }

        /// <summary>
        /// The scale of numeric type attributes.If the precision is nonzero and scale is 
        /// -127, then it is a FLOAT; otherwise, it is a NUMBER( precision, scale ).
        /// When precision is 0, NUMBER( precision, scale ) can be represented simply as NUMBER.
        /// </summary>
        char Scale( ) const
        {
            return GetSByteAttribute( DescribeAttribute::SCALE );
        }

        /// <summary>
        /// the package name of a type if it is a package type
        /// </summary>
        WideString PackageName( ) const
        {
            return GetStringAttribute( DescribeAttribute::PACKAGE_NAME );
        }

        /// <summary>
        /// A string that is the type name. The returned value contains the type name 
        /// if the data type is SQLT_NTY or SQLT_REF.If the data type is SQLT_ NTY, 
        /// the name of the named data type's type is returned. If the data type is 
        /// SQLT_REF, the type name of the named data type pointed to by the REF is returned.
        /// </summary>
        WideString TypeName( ) const
        {
            return GetStringAttribute( DescribeAttribute::TYPE_NAME );
        }

        /// <summary>
        /// A string with the schema name under which the type has been created
        /// </summary>
        WideString SchemaName( ) const
        {
            return GetStringAttribute( DescribeAttribute::SCHEMA_NAME );
        }

        /// <summary>
        /// Returns the in-memory REF of the TDO for the type, if the column type is an object 
        /// type. If space has not been reserved for the OCIRef, then it is allocated implicitly 
        /// in the cache.
        /// </summary>
        OCI::Ref TypeDescriptorObject( ) const;
        OCIRef* TDO( ) const
        {
            return (OCIRef*)GetPointerAttribute( Attribute::REF_TDO );
        }
    };


    inline std::unique_ptr<OCI::TypeAttributeDescriptor> TypeDescriptor::Attribute( size_t index ) const
    {
        void* listDescriptorHandle = GetPointerAttribute( Attribute::LIST_TYPE_ATTRS );
        auto& serviceContext = this->ServiceContext( );
        std::unique_ptr<OCI::TypeAttributeDescriptor> result( static_cast<OCI::TypeAttributeDescriptor*>( GetChildDescriptor( listDescriptorHandle, index ).release( ) ) );
        return result;
    }
    inline std::vector<std::unique_ptr<OCI::TypeAttributeDescriptor>> TypeDescriptor::Attributes( ) const
    {
        std::vector<std::unique_ptr<OCI::TypeAttributeDescriptor>> result;
        auto numberOfTypeAttributes = NumberOfTypeAttributes( );
        if ( numberOfTypeAttributes )
        {
            void* listDescriptorHandle = GetPointerAttribute( Attribute::LIST_TYPE_ATTRS );
            result.reserve( numberOfTypeAttributes );
            for ( size_t i = 1; i <= numberOfTypeAttributes; i++ )
            {
                std::unique_ptr<OCI::TypeAttributeDescriptor> element( static_cast<OCI::TypeAttributeDescriptor*>( GetChildDescriptor( listDescriptorHandle, i ).release( ) ) );
                result.emplace_back( std::move( element ) );
            }
        }
        return result;
    }

    /// <summary>
    /// CollectionDescriptor
    /// </summary>
    class CollectionDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr CollectionDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr CollectionDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
        

        /// <summary>
        /// The maximum size of the type attribute. This length is 
        /// returned in bytes and not characters for strings and raws.
        /// It returns 22 for NUMBERs.
        /// </summary>
        size_t DataSize( ) const
        {
            return GetUInt16Attribute( DescribeAttribute::DATA_SIZE );
        }

        /// <summary>
        /// Typecode
        /// </summary>
        OCI::TypeCode TypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( Attribute::TYPECODE ) );
        }

        /// <summary>
        /// The data type of the type attribute.
        /// </summary>
        OCI::TypeCode DataTypeCode( ) const
        {
            return static_cast<OCI::TypeCode>( GetUInt16Attribute( DescribeAttribute::DATA_TYPE ) );
        }

        /// <summary>
        /// The number of elements in an array. It is only valid for collections that are arrays.
        /// </summary>
        size_t ArraySize( ) const
        {
            return GetUInt32Attribute( Attribute::NUM_ELEMS );
        }

        /// <summary>
        /// Type attribute name
        /// </summary>
        WideString Name( ) const
        {
            return GetStringAttribute( DescribeAttribute::NAME );
        }

        /// <summary>
        /// The precision of numeric type attributes. If the precision is nonzero and 
        /// scale is - 127, then it is a FLOAT; otherwise, it is a NUMBER( precision, scale ).
        /// When precision is 0, NUMBER( precision, scale ) can be represented simply as NUMBER.
        /// </summary>
        Int16 Precision( ) const
        {
            return GetByteAttribute( DescribeAttribute::PRECISION );
        }

        /// <summary>
        /// The scale of numeric type attributes.If the precision is nonzero and scale is 
        /// - 127, then it is a FLOAT; otherwise, it is a NUMBER( precision, scale ).
        /// When precision is 0, NUMBER( precision, scale ) can be represented simply as NUMBER.
        /// </summary>
        char Scale( ) const
        {
            return GetSByteAttribute( DescribeAttribute::SCALE );
        }

        /// <summary>
        /// the package name of a type if it is a package type
        /// </summary>
        WideString PackageName( ) const
        {
            return GetStringAttribute( DescribeAttribute::PACKAGE_NAME );
        }

        /// <summary>
        /// A string that is the type name. The returned value contains the type name 
        /// if the data type is SQLT_NTY or SQLT_REF.If the data type is SQLT_ NTY, 
        /// the name of the named data type's type is returned. If the data type is 
        /// SQLT_REF, the type name of the named data type pointed to by the REF is returned.
        /// </summary>
        WideString TypeName( ) const
        {
            return GetStringAttribute( DescribeAttribute::TYPE_NAME );
        }

        /// <summary>
        /// A string with the schema name under which the type has been created
        /// </summary>
        WideString SchemaName( ) const
        {
            return GetStringAttribute( DescribeAttribute::SCHEMA_NAME );
        }

        /// <summary>
        /// Returns the in - memory REF of the type descriptor object( TDO ) for the 
        /// type, if the column type is an object type.If space has not been reserved 
        /// for the OCIRef, then it is allocated implicitly in the cache. The caller 
        /// can then pin the TDO with OCIObjectPin( ).
        /// </summary>
        Ref TypeDescriptorObject( ) const;

        OCI::Describe Describe( ) const;

    };

    inline std::unique_ptr<CollectionDescriptor> TypeDescriptor::CollectionElement( )
    {
        OCIParam* collectionDescriptorHandle = (OCIParam*)GetPointerAttribute( Attribute::COLLECTION_ELEMENT );
        auto& serviceContext = this->ServiceContext( );
        std::unique_ptr<CollectionDescriptor> result( static_cast<CollectionDescriptor*>( CreateParameter( serviceContext, collectionDescriptorHandle ).release( ) ) );
        return result;
    }


    /// <summary>
    /// MethodDescriptor
    /// </summary>
    class MethodDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr MethodDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr MethodDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// MethodArgumentDescriptor
    /// </summary>
    class MethodArgumentDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr MethodArgumentDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr MethodArgumentDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// MethodResultDescriptor
    /// </summary>
    class MethodResultDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr MethodResultDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr MethodResultDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// SchemaDescriptor
    /// </summary>
    class SchemaDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr SchemaDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr SchemaDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        /// <summary>
        /// Retrieves the descriptor for the schema object list
        /// </summary>
        HO_EXPORT std::unique_ptr<ListDescriptor> ObjectList( ) const;

        std::vector< std::unique_ptr<ParameterDescriptor>> Objects( ) const
        {
            auto objectList = ObjectList( );
            auto objectListSize = objectList->NumParams( );
            std::vector< std::unique_ptr<ParameterDescriptor>> result;
            result.reserve( objectListSize );
            for ( UInt32 i = 0; i < objectListSize; i++ )
            {
                auto parameterDescriptor = objectList->Parameter<ParameterDescriptor>( i );
                result.emplace_back( std::move( parameterDescriptor ) );
            }
            return result;
        }

    };

    /// <summary>
    /// DatabaseDescriptor
    /// </summary>
    class DatabaseDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr DatabaseDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr DatabaseDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }

        /// <summary>
        /// Database version
        /// </summary>
        WideString Version( ) const
        {
            return GetStringAttribute( Attribute::VERSION );
        }

        /// <summary>
        /// Database character set ID from the server handle
        /// </summary>
        UInt16 CharacterSet( ) const
        {
            return GetUInt16Attribute( Attribute::CHARSET_ID );
        }

        /// <summary>
        /// Database national character set ID from the server handle
        /// </summary>
        UInt16 NationalCharacterSet( ) const
        {
            return GetUInt16Attribute( Attribute::NCHARSET_ID );
        }

        /// <summary>
        /// Retrieves the descriptor for the database schema list
        /// </summary>
        HO_EXPORT std::unique_ptr<ListDescriptor> SchemaList( ) const;

        /// <summary>
        /// Retrives a vector of pointers to SchemaDescriptor
        /// objects for each schema in the database
        /// </summary>
        std::vector< std::unique_ptr<SchemaDescriptor>> Schemas( ) const
        {
            auto schemaList = SchemaList( );
            auto schemaListSize = schemaList->NumParams( );
            std::vector< std::unique_ptr<SchemaDescriptor>> result;
            result.reserve( schemaListSize );
            for ( UInt32 i = 0; i < schemaListSize; i++ )
            {
                auto schemaDescriptor = schemaList->Parameter<SchemaDescriptor>( i );
                result.emplace_back( std::move( schemaDescriptor ) );
            }
            return result;
        }

        /// <summary>
        /// Maximum length of a procedure name
        /// </summary>
        UInt32 MaxProcedureNameLength( ) const
        {
            return GetUInt32Attribute( Attribute::MAX_PROC_LEN );
        }

        /// <summary>
        /// Maximum length of a column name
        /// </summary>
        UInt32 MaxColumnNameLength( ) const
        {
            return GetUInt32Attribute( Attribute::MAX_COLUMN_LEN );
        }



    };

    /// <summary>
    /// RuleDescriptor
    /// </summary>
    class RuleDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr RuleDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr RuleDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// RuleSetDescriptor
    /// </summary>
    class RuleSetDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr RuleSetDescriptor( ) noexcept
            : Base( )
        {
        }

        constexpr RuleSetDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// EvaluationContextDescriptor
    /// </summary>
    class EvaluationContextDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr EvaluationContextDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr EvaluationContextDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// TableAliasDescriptor
    /// </summary>
    class TableAliasDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr TableAliasDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr TableAliasDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// VariableTypeDescriptor
    /// </summary>
    class VariableTypeDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr VariableTypeDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr VariableTypeDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };

    /// <summary>
    /// NameValuePairDescriptor
    /// </summary>
    class NameValuePairDescriptor : public ParameterDescriptor
    {
        using Base = ParameterDescriptor;
    public:
        constexpr NameValuePairDescriptor( ) noexcept
            : Base( )
        {
        }
        constexpr NameValuePairDescriptor( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHande = true )
            : Base( serviceContext, handle, ownsHande )
        {
        }
    };
	
    template<typename DataReaderType>
        requires std::is_base_of_v<OCI::DataReader, DataReaderType>
    inline std::unique_ptr<DataReaderType> Statement::ExecuteReader( StatementExecuteMode executeMode )
    {
        auto result = std::make_unique<DataReaderType>( *this );
        result->InitializeDefines( );
        auto rc = Execute( 1, executeMode );
        result->Prefetch( rc );
        return result;
    }

    template<typename DataReaderType>
        requires std::is_base_of_v<OCI::ArrayDataReader, DataReaderType>
    inline std::unique_ptr<DataReaderType> Statement::ExecuteReader( size_t defineSize, StatementExecuteMode executeMode )
    {
        auto result = std::make_unique<DataReaderType>( *this, defineSize );
        result->InitializeDefines( );
        auto rc = Execute( static_cast<UInt32>(defineSize), executeMode );
        result->Prefetch( rc );
        return result;
    }

	template <typename BindType, typename ...ArgTypes>
        requires std::is_base_of_v<BindBase, BindType>
    inline BindType* Statement::Bind( UInt32 position, ArgTypes&&... args ) const
    {
        auto bind = std::make_unique<BindType>( *this, position, std::forward<ArgTypes>(args)... );
        auto* result = bind.get( );
        binds_.emplace_back( std::move( bind ) );
        return result;
    }

    template <typename T, typename ...ArgTypes>
        requires Internal::HasTraits<T>
    inline typename Internal::Traits<T>::BindType* Statement::Bind( UInt32 position, ArgTypes&&... args ) const
    {
        return Bind<typename Internal::Traits<T>::BindType>( position, std::forward<ArgTypes>( args )... );
    }

    template <typename BindType, typename ...ArgTypes>
        requires std::is_base_of_v<BindBase, BindType>
    inline BindType* Statement::Bind( const WideString& name, ArgTypes&&... args ) const
    {
        auto bind = std::make_unique<BindType>( *this, name, std::forward<ArgTypes>( args )... );
        auto* result = bind.get( );
        binds_.emplace_back( std::move( bind ) );
        return result;
    }

    template <typename T, typename ...ArgTypes>
        requires Internal::HasTraits<T>
    inline typename Internal::Traits<T>::BindType* Statement::Bind( const WideString& name, ArgTypes&&... args ) const
    {
        return Bind<typename Internal::Traits<T>::BindType>( name, std::forward<ArgTypes>( args )... );
    }
	
    /// <summary>
    /// Describe
    /// </summary>
    class Describe : public HandleBase
    {
        using Base = HandleBase;
    private:
        const OCI::ServiceContext* serviceContext_;
    public:
        static constexpr OCI::HandleType OCIHandleType = OCI::HandleType::Describe;

        constexpr Describe( ) noexcept
            : Base( ), serviceContext_(nullptr)
        {
        }

        constexpr Describe( const OCI::ServiceContext& serviceContext, void* ociDescribe, bool ownsHandle = true ) noexcept
            : Base( HandleType::Describe, ociDescribe, ownsHandle ), serviceContext_( &serviceContext )
        {
            auto& environment = serviceContext_->Environment( );
        }

        Describe( const Describe& other ) = delete;
        constexpr Describe( Describe&& other ) noexcept
            : Base( std::move( other ) ), serviceContext_( other.serviceContext_ )
        {
            other.serviceContext_ = nullptr;
        }

        Describe& operator = ( const Describe& other ) = delete;
        constexpr Describe& operator = ( Describe&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) ); 
                serviceContext_ = other.serviceContext_; 
                other.serviceContext_ = nullptr;
            }
            return *this;
        }


        const OCI::Environment& Environment( ) const
        {
            return serviceContext_->Environment( );
        }


        const OCI::ServiceContext& ServiceContext( ) const noexcept
        {
            return *serviceContext_;
        }

        const OCI::ErrorHandle& Error( ) const noexcept final override
        {
            return serviceContext_->Error( );
        }
    public:
        

        

        HO_EXPORT void DescribeAny( const WideString& objectName, OCI::ParameterType parameterType = OCI::ParameterType::Unknown ) const;
        HO_EXPORT void DescribeAny( const OCI::Type& type ) const;
        HO_EXPORT void DescribeAny( OCIType* type ) const;
        HO_EXPORT void DescribeAny( const OCI::Ref& typeRef ) const;
        HO_EXPORT void DescribeAny( OCIRef* typeRef ) const;

        
        /// <summary>
        /// Return a ParameterDescriptor that points to the root of the description.
        /// </summary>
        /// <returns>The root ParameterDescriptor</returns>
        HO_EXPORT std::unique_ptr<ParameterDescriptor> _Descriptor() const;

        /// <summary>
        /// Return a ParameterDescriptor that points to the root of the description.
        /// </summary>
        /// <returns>The root ParameterDescriptor</returns>
        template<typename T>
            requires std::is_base_of_v<ParameterDescriptor,T>
        std::unique_ptr<T> Descriptor( ) const
        {
            std::unique_ptr<ParameterDescriptor> descriptor = _Descriptor( );
            return std::unique_ptr<T>( static_cast<T*>( descriptor.release() ) );
        }
        /// <summary>
        /// Return a ParameterDescriptor that points to the root of the description.
        /// </summary>
        /// <returns>The root ParameterDescriptor</returns>
        template<typename T>
            requires std::is_base_of_v<ParameterDescriptor, T>
        std::unique_ptr<ParameterDescriptor> Param( ) const
        {
            std::unique_ptr<ParameterDescriptor> descriptor = _Descriptor( );
            return std::unique_ptr<T>( static_cast<T*>( descriptor.release( ) ) );
        }

        /// <summary>
        /// Returns the number of parameters in the describe handle. When the describe handle
        /// is a description of the select list, this refers to the number of columns in the select list.
        /// </summary>
        /// <returns>the number of parameters in the describe handle</returns>
        UInt32 ParamCount( ) const
        {
            return GetUInt32Attribute( Attribute::PARAM_COUNT );
        }

        /// <summary>
        /// This attribute requests the Describe to also get the metadata for invisible columns.
        /// </summary>
        /// <param name="value"></param>
        void ShowInvisibleColumns( bool value )
        {
            SetBooleanAttribute( Attribute::SHOW_INVISIBLE_COLUMNS, value );
        }
    };


    inline OCI::Describe CollectionDescriptor::Describe( ) const
    {
        OCIRef* ref = (OCIRef*)GetPointerAttribute( Attribute::REF_TDO );
        auto& serviceContext = this->ServiceContext( );
        auto result = serviceContext.Describe( ref );
        return result;
    }



    /// <summary>
    /// ObjectBase
    /// </summary>
    class ObjectBase
    {
        const OCI::ServiceContext* serviceContext_;
        void* object_;
        ObjectReleaseMethod objectReleaseMethod_;
    public:
        constexpr ObjectBase() noexcept
            : serviceContext_(nullptr), object_(nullptr), objectReleaseMethod_( ObjectReleaseMethod::None )
        { }

        ObjectBase( const ObjectBase& other ) = delete;
        constexpr ObjectBase( ObjectBase&& other ) noexcept
            : serviceContext_( other.serviceContext_ ), object_( other.object_ ), objectReleaseMethod_( other.objectReleaseMethod_ )
        { 
            other.serviceContext_ = nullptr;
            other.object_ = nullptr;
            other.objectReleaseMethod_ = ObjectReleaseMethod::None;
        }


        constexpr ObjectBase( const OCI::ServiceContext& serviceContext, void* object, ObjectReleaseMethod objectReleaseMethod = ObjectReleaseMethod::ObjectUnpin ) noexcept
            : serviceContext_( &serviceContext ), object_( object ), objectReleaseMethod_( objectReleaseMethod )
        { }

        HO_EXPORT virtual ~ObjectBase( );

        ObjectBase& operator = ( const ObjectBase& other ) = delete;
        constexpr ObjectBase& operator = ( ObjectBase&& other ) noexcept
        {
            if ( this != &other )
            {
                serviceContext_ = other.serviceContext_; 
                object_ = other.object_; 
                objectReleaseMethod_ = other.objectReleaseMethod_;

                other.serviceContext_ = nullptr;
                other.object_ = nullptr;
                other.objectReleaseMethod_ = ObjectReleaseMethod::None;
            }
            return *this;
        }
    protected:
        template<typename T>
        constexpr void Take( T&& other ) noexcept
        {
            serviceContext_ = other.serviceContext_;
            object_ = other.object_;
            objectReleaseMethod_ = other.objectReleaseMethod_;

            other.serviceContext_ = nullptr;
            other.object_ = nullptr;
            other.objectReleaseMethod_ = ObjectReleaseMethod::None;
        }
    public:

        void* Handle( ) const
        {
            return object_;
        }

        constexpr const OCI::ServiceContext& ServiceContext( ) const noexcept
        {
            return *serviceContext_;
        }
        const OCI::ErrorHandle& Error( ) const noexcept
        {
            auto& serviceContext = ServiceContext( );
            return serviceContext.Error( );
        }
        const OCI::Environment& Environment( ) const
        {
            auto& serviceContext = ServiceContext( );
            return serviceContext.Environment( );
        }
    };

    /// <summary>
    /// Ref
    /// </summary>
    class Ref : public ObjectBase
    {
        using Base = ObjectBase;
    public:
        constexpr Ref() noexcept
        { }

        Ref( const Ref& other ) = delete;
        constexpr Ref( Ref&& other ) noexcept
            : Base(std::move( other ))
        { }

        Ref( const OCI::ServiceContext& serviceContext, Duration duration = Duration::Session )
            : Base( serviceContext, CreateRef( serviceContext, duration ), ObjectReleaseMethod::ObjectFree )
        { }
        constexpr Ref( const OCI::ServiceContext& serviceContext, OCIRef* ref, ObjectReleaseMethod objectReleaseMethod = ObjectReleaseMethod::ObjectUnpin )
            : Base( serviceContext, ref, objectReleaseMethod )
        { }

        Ref& operator = ( const Ref& other ) = delete;
        constexpr Ref& operator = ( Ref&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
            }
            return *this;
        }


    private:
        static OCIRef* CreateRef( const OCI::ServiceContext& serviceContext, Duration duration )
        {
            auto ref = (OCIRef*)serviceContext.ObjectNew( TypeCode::Ref, duration, true );
            return ref;
        }
    public:
        ~Ref( )
        { }
    };

    inline Ref TypeDescriptor::TypeDescriptorObject( ) const
    {
        OCIRef* ref = (OCIRef*)GetPointerAttribute( Attribute::REF_TDO );
        auto& serviceContext = this->ServiceContext( );
        Ref result( serviceContext, ref, ObjectReleaseMethod::None );
        return result;
    }

    inline OCI::Ref TypeAttributeDescriptor::TypeDescriptorObject( ) const
    {
        OCIRef* ref = (OCIRef*)GetPointerAttribute( Attribute::REF_TDO );
        auto& serviceContext = this->ServiceContext( );
        return Ref( serviceContext, ref, ObjectReleaseMethod::None );
    }

    inline Ref CollectionDescriptor::TypeDescriptorObject( ) const
    {
        OCIRef* ref = (OCIRef*)GetPointerAttribute( Attribute::REF_TDO );
        auto& serviceContext = this->ServiceContext( );
        return Ref( serviceContext, ref, ObjectReleaseMethod::None );
    }


    /// <summary>
    /// Object
    /// </summary>
    class Object : public ObjectBase
    {
    public:
        using Base = ObjectBase;
        constexpr Object( ) noexcept
        {
        }

        Object( const Object& other ) = delete;
        Object( Object&& other ) noexcept
            : Base( std::move( other ) )
        {
        }

        Object( const OCI::ServiceContext& serviceContext, void* ociObject, ObjectReleaseMethod objectReleaseMethod = ObjectReleaseMethod::ObjectUnpin )
            : Base( serviceContext, ociObject, objectReleaseMethod )
        { }
        virtual ~Object( )
        { }

        Object& operator = ( const Object& other ) = delete;
        Object& operator = ( Object&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
            }
            return *this;
        }


    };

    /// <summary>
    /// Type
    /// </summary>
    class Type : public ObjectBase
    {
    public:
        using Base = ObjectBase;
        constexpr Type( ) noexcept
        {
        }

        Type( const Type& other ) = delete;
        Type( Type&& other ) noexcept
            : Base( std::move( other ) )
        {
        }

        Type( const OCI::ServiceContext& serviceContext, void* ociType, ObjectReleaseMethod objectReleaseMethod = ObjectReleaseMethod::ObjectUnpin )
            : Base( serviceContext, ociType, objectReleaseMethod )
        { }
        virtual ~Type( )
        { }

        Type& operator = ( const Type& other ) = delete;
        Type& operator = ( Type&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
            }
            return *this;
        }

    };

    inline std::unique_ptr<OCI::Type> ServiceContext::TypeByName( const WideString& schemaName, const WideString& typeName, OCI::Duration pinDuration, OCI::TypeGetOpt typeGetOption ) const
    {
        return TypeByName( schemaName, typeName, WideString( ), pinDuration, typeGetOption );
    }
    inline std::unique_ptr<OCI::Type> ServiceContext::TypeByFullName( const WideString& fullName, OCI::Duration pinDuration, OCI::TypeGetOpt typeGetOption ) const
    {
        return TypeByFullName( fullName, WideString( ), pinDuration, typeGetOption );
    }
	    
    /// <summary>
    /// Collection
    /// </summary>
    class Collection : public ObjectBase
    {
        using Base = ObjectBase;
    public:
        constexpr Collection( ) noexcept
        {
        }

        Collection( const Collection& other ) = delete;
        Collection( Collection&& other ) noexcept
            : Base( std::move( other ) )
        {
        }

        Collection( const OCI::ServiceContext& serviceContext, OCIColl* ocicollection, ObjectReleaseMethod objectReleaseMethod = ObjectReleaseMethod::ObjectUnpin )
            : Base( serviceContext, ocicollection, objectReleaseMethod )
        { }
        ~Collection( )
        { }

        Collection& operator = ( const Collection& other ) = delete;
        Collection& operator = ( Collection&& other ) noexcept
        {
            if ( this != &other )
            {
                Take( std::move( other ) );
            }
            return *this;
        }

        void Append( const void* elem, const void* elemind ) const
        {
            CollectionAppend( Environment( ), Error( ), elem, elemind, (OCIColl*)Handle( ) );
        }
        void Assign( Int32 index, const void* elem, const void* elemind ) const
        {
            CollectionAssignElement( Environment( ), Error( ), index, elem, elemind, (OCIColl*)Handle( ) );
        }
        void GetAt( Int32 index, bool* exists, void** elem, void** elemind ) const
        {
            CollectionGetElement( Environment( ), Error( ), (OCIColl*)Handle( ), index, exists, elem, elemind );
        }
        void GetAt( Int32 index, bool* exists, void** elem, void** elemind, UInt32* nelems ) const
        {
            CollectionGetElementArray( Environment( ), Error( ), (OCIColl*)Handle( ), index, exists, elem, elemind, nelems );
        }
        bool IsLocator( ) const
        {
            bool result = false;
            CollectionIsLocator( Environment( ), Error( ), (OCIColl*)Handle( ), &result );
            return result;
        }
        Int32 MaxSize( ) const
        {
            return CollectionMax( Environment( ), (OCIColl*)Handle( ) );
        }
        Int32 Size( ) const
        {
            Int32 result = 0;
            CollectionSize( Environment( ), Error( ), (OCIColl*)Handle( ), &result );
            return result;
        }
        void Trim( Int32 numberOfElementsToRemove ) const
        {
            CollectionTrim( Environment( ), Error( ), numberOfElementsToRemove, (OCIColl*)Handle( ) );
        }
        Iterator CreateIterator( ) const;

    };

    /// <summary>
    /// Iterator
    /// </summary>
    class Iterator
    {
        const OCI::Environment* environment_;
        OCIIter* iterator_;
    public:
        constexpr Iterator() noexcept
            : environment_(nullptr), iterator_( nullptr )
        { }

        Iterator( const Iterator& other ) = delete;
        constexpr Iterator( Iterator&& other ) noexcept
            : environment_( other.environment_ ), iterator_( other.iterator_ )
        { }

        Iterator( const OCI::Environment& environment, OCIIter* ociiterator )
            : environment_( &environment ), iterator_( ociiterator )
        { }
        virtual ~Iterator( )
        {
            if ( iterator_ && environment_ )
            {
                IteratorDelete( *environment_, Error( ), &iterator_ );
            }
        }

        const OCI::ErrorHandle& Error( ) const noexcept
        {
            return environment_->Error( );
        }


        Iterator& operator = ( const Iterator& other ) = delete;
        constexpr Iterator& operator = ( Iterator&& other ) noexcept
        {
            if ( this != &other )
            {
                environment_ = other.environment_;
                iterator_ = other.iterator_;
            }
            return *this;
        }

        void Current( void** elem, void** elemind )
        {
            IteratorGetCurrent( *environment_, Error( ), iterator_, elem, elemind );
        }
        bool Next( void** elem, void** elemind )
        {
            bool result = false;
            IteratorNext( *environment_, Error( ), iterator_, elem, elemind, &result );
            return result;
        }
        bool Previous( void** elem, void** elemind )
        {
            bool result = false;
            IteratorPrev( *environment_, Error( ), iterator_, elem, elemind, &result );
            return result;
        }

    };


    inline Iterator Collection::CreateIterator( ) const
    {
        OCIIter* ociiterator = nullptr;
        auto& environment = Environment( );
        IteratorCreate( environment, Error( ), (OCIColl*)Handle( ), &ociiterator );
        Iterator result( environment, ociiterator );
        return result;
    }

    namespace Metadata
    {

        enum class Kind
        {
            Unknown,
            Argument,
            Result,
            Procedure,
            Function,
            SchemaObject,
            Column,
            Table,
            View,
            TypeAttribute,
            Type,
            Package,
            Synonym,
            Sequence,
            Schema,
            Database
        };

        class MetadataObject
        {
            const OCI::ServiceContext* serviceContext_;
            const MetadataObject* owner_;
            WideString name_;
        protected:
            HO_EXPORT MetadataObject( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const OCI::ParameterDescriptor* descriptor );
            HO_EXPORT MetadataObject( const OCI::ServiceContext* serviceContext, const WideString& name );
            HO_EXPORT MetadataObject( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const WideString& name );
        public:
            HO_EXPORT virtual ~MetadataObject( );
        protected:
            const OCI::ServiceContext* ServiceContext( ) const noexcept
            {
                return serviceContext_;
            }
        public:
            const MetadataObject* Owner( ) const noexcept
            {
                return owner_;
            }
            const WideString& Name( ) const noexcept
            {
                return name_;
            }
            virtual Metadata::Kind Kind( ) const noexcept = 0;

            virtual WideString QualifiedName( ) const
            {
                if ( owner_ )
                {
                    auto qualifiedNameOfOwner = owner_->QualifiedName( );
                    size_t resultSize = qualifiedNameOfOwner.size( ) + 1 + name_.size( );
                    WideString result;
#ifndef HCC_WITH_BASIC_STRING
                    result.reserve( resultSize );
#endif
                    result += qualifiedNameOfOwner;
                    result += L'.';
                    result += name_;
                    return result;
                }
                else
                {
                    return name_;
                }
            }
            virtual WideString QuotedQualifiedName( ) const
            {
                WideString result;
                if ( owner_ )
                {
                    auto qualifiedNameOfOwner = owner_->QuotedQualifiedName( );
                    size_t resultSize = qualifiedNameOfOwner.size( ) + 3 + name_.size( );
                    WideString result;
#ifndef HCC_WITH_BASIC_STRING
                    result.reserve( resultSize );
#endif
                    result += qualifiedNameOfOwner;
                    result += L'.';
                    result += L'\"';
                    result += name_;
                    result += L'\"';
                    return result;
                }
                else
                {
                    size_t resultSize = 2 + name_.size( );
#ifndef HCC_WITH_BASIC_STRING
                    result.reserve( resultSize );
#endif
                    result += L'\"';
                    result += name_;
                    result += L'\"';
                    return result;
                }
            }


        };


        class ArgumentOrResult : public MetadataObject
        {
        public:
            using Base = MetadataObject;
        private:
        public:
            ArgumentOrResult( const OCI::ServiceContext* serviceContext, const ProcedureOrFunction* owner, const OCI::ArgumentDescriptor* descriptor );
        };

        class Argument : public ArgumentOrResult
        {
        public:
            using Base = ArgumentOrResult;
        private:
        public:
            Argument( const OCI::ServiceContext* serviceContext, const ProcedureOrFunction* owner, const OCI::ArgumentDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }
            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Argument; }
        };

        class Result : public ArgumentOrResult
        {
        public:
            using Base = ArgumentOrResult;
        private:
        public:
            Result( const OCI::ServiceContext* serviceContext, const Function* owner, const OCI::ArgumentDescriptor* descriptor );

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Result; }
        };



        class ProcedureOrFunction : public MetadataObject
        {
        public:
            using Base = MetadataObject;
            ProcedureOrFunction( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const OCI::ParameterDescriptor * descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }
        };

        inline ArgumentOrResult::ArgumentOrResult( const OCI::ServiceContext* serviceContext, const ProcedureOrFunction* owner, const OCI::ArgumentDescriptor* descriptor )
            : Base( serviceContext, owner, descriptor )
        {
        }


        class Procedure : public ProcedureOrFunction
        {
        public:
            using Base = ProcedureOrFunction;
            Procedure( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const OCI::ProcedureDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Procedure; }
        };

        class Function : public ProcedureOrFunction
        {
        public:
            using Base = ProcedureOrFunction;
            Function( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const OCI::FunctionDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Function; }
        };

        inline Result::Result( const OCI::ServiceContext* serviceContext, const Function* owner, const OCI::ArgumentDescriptor* descriptor )
            : Base( serviceContext, owner, descriptor )
        {
        }



        class SchemaObject : public MetadataObject
        {
        public:
            using Base = MetadataObject;
        private:
            WideString schemaName_;
        public:
            SchemaObject( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::ParameterDescriptor* descriptor );

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::SchemaObject; }

            virtual WideString QualifiedName( ) const override
            {
                const auto& name = Name( );

                size_t resultLength = schemaName_.size( ) + 1 + name.size( );
                WideString result;
#ifndef HCC_WITH_BASIC_STRING
                result.reserve( resultLength );
#endif
                result = schemaName_;
                result += L'.';
                result += name;
                return result;
            }

            virtual WideString QuotedQualifiedName( ) const override
            {
                const auto& name = Name( );

                size_t resultLength = schemaName_.size( ) + 5 + name.size( );
                WideString result;
#ifndef HCC_WITH_BASIC_STRING
                result.reserve( resultLength );
#endif
                result += L'\"';
                result += schemaName_;
                result += L'\"';
                result += L'.';
                result += L'\"';
                result += name;
                result += L'\"';
                return result;
            }



        };


        class Column : public MetadataObject
        {
        public:
            using Base = MetadataObject;
        private:
            bool usesCharacterLength_;
            UInt16 characterLength_;
            UInt16 length_;
            ColumnProperties properties_;
            bool isInvisible_;
            OraType dataType_;
            Int16 precision_;
            SByte scale_;
            bool nullable_;
            WideString typeName_;
            WideString schemaName_;
            OCI::CharacterSetForm characterSetForm_;
        public:
            HO_EXPORT Column( const OCI::ServiceContext* serviceContext, const TableOrView* owner, const OCI::ColumnDescriptor* descriptor );

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Column; }

            /// <summary>
            /// Returns the type of length semantics of the column. Zero (0) means
            /// byte-length semantics and 1 means character-length semantics.
            /// </summary>
            bool UsesCharacterLength( ) const
            {
                return usesCharacterLength_;
            }

            /// <summary>
            /// Returns the column character length that is the number of characters
            /// allowed in the column.
            /// </summary>
            UInt16 CharacterLength( ) const
            {
                return characterLength_;
            }

            /// <summary>
            /// The maximum size of the column. This length is returned in bytes and 
            /// not characters for strings and raws. It returns 22 for NUMBERs.
            /// </summary>
            UInt16 Length( ) const
            {
                return length_;
            }

            /// <summary>
            /// Returns describe data regarding certain column properties
            /// </summary>
            /// <returns>The ColumnProperties for the column</returns>
            ColumnProperties Properties( ) const
            {
                return properties_;
            }

            /// <summary>
            /// Returns whether a column is invisible or not.
            /// </summary>
            /// <returns>true if the column is invisible</returns>
            bool IsInvisible( ) const
            {
                return isInvisible_;
            }

            /// <summary>
            /// The datatype of the column. (OCI_ATTR_DATA_TYPE)
            /// </summary>
            OraType DataType( ) const
            {
                return dataType_;
            }

            /// <summary>
            /// The precision of numeric columns. If the precision is nonzero and scale 
            /// is -127, then it is a FLOAT, else it is a NUMBER(precision, scale). 
            /// For the case when precision is 0, NUMBER(precision, scale) can be 
            /// represented simply as NUMBER.
            /// </summary>
            Int16 Precision( ) const
            {
                return precision_;
            }

            /// <summary>
            /// The scale of numeric columns. If the precision is nonzero and 
            /// scale is -127, then it is a FLOAT, else it is a NUMBER(precision, scale). 
            /// For the case when precision is 0, NUMBER(precision, scale) can be 
            /// represented simply as NUMBER.
            /// </summary>
            SByte Scale( ) const
            {
                return scale_;
            }

            /// <summary>
            /// Returns false if null values are not permitted for the column. Does not
            /// return a correct value for a CUBE or ROLLUP operation.
            /// </summary>
            bool IsNull( ) const
            {
                return nullable_;
            }
            bool Nullable( ) const
            {
                return nullable_;
            }

            /// <summary>
            /// Returns a string that is the type name. The returned value contains
            /// the type name if the data type is SQLT_NTY or SQLT_REF.If the data
            /// type is SQLT_NTY, the name of the named data type's type is returned.
            /// If the data type is SQLT_REF, the type name of the named data type
            /// pointed to by the REF is returned.
            /// </summary>
            WideString TypeName( ) const
            {
                return typeName_;
            }

            /// <summary>
            /// Returns a string with the schema name under which the type has
            /// been created
            /// </summary>
            WideString SchemaName( ) const
            {
                return schemaName_;
            }

            /// <summary>
            /// Character set form of the column.
            /// </summary>
            OCI::CharacterSetForm CharacterSetForm( ) const
            {
                return characterSetForm_;
            }

        };


        class TableOrView : public SchemaObject
        {
        public:
            using Base = SchemaObject;
            using ColumnContainer = std::vector< std::unique_ptr<Column> >;
        private:
        protected:
            TableOrView( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::TableViewBaseDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            { 
            }
        public:
            HO_EXPORT ColumnContainer Columns( ) const;

        };

        


        class Table : public TableOrView
        {
        public:
            using Base = TableOrView;
        private:
        public:
            Table( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::TableDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Table; }
        };

        class View : public TableOrView
        {
        public:
            using Base = TableOrView;
        private:
        public:
            View( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::ViewDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::View; }
        };

        class TypeObject : public MetadataObject
        {
        public:
            using Base = MetadataObject;
            TypeObject( const OCI::ServiceContext* serviceContext, const Type* owner, const OCI::ParameterDescriptor* descriptor );
        };

        class TypeAttribute : public TypeObject
        {
        public:
            using Base = TypeObject;
            TypeAttribute( const OCI::ServiceContext* serviceContext, const Type* owner, const OCI::TypeAttributeDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::TypeAttribute; }
        };

        class Type : public MetadataObject
        {
        public:
            using Base = MetadataObject;
            Type( const OCI::ServiceContext* serviceContext, const MetadataObject* owner, const OCI::TypeDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Type; }

        };

        inline TypeObject::TypeObject( const OCI::ServiceContext* serviceContext, const Type* owner, const OCI::ParameterDescriptor* descriptor )
            : Base( serviceContext, owner, descriptor )
        {
        }


        class Package : public SchemaObject
        {
        public:
            using Base = SchemaObject;
            Package( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::PackageDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Package; }

        };

        class Synonym : public SchemaObject
        {
        public:
            using Base = SchemaObject;
            Synonym( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::SynonymDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Synonym; }
        };

        class Sequence : public SchemaObject
        {
        public:
            using Base = SchemaObject;
            Sequence( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::SequenceDescriptor* descriptor )
                : Base( serviceContext, owner, descriptor )
            {
            }

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Sequence; }
        };

        /*
        class Sequence : public SchemaObject
        {
        public:
            using Base = SchemaObject;
        };
        */



        class Schema : public MetadataObject
        {
        public:
            using Base = MetadataObject;
            using SchemaObjectContainer = std::unordered_map<WideString, std::unique_ptr<MetadataObject>>;
        private:
        public:
            HO_EXPORT Schema( const OCI::ServiceContext* serviceContext, const Database* owner, const OCI::SchemaDescriptor* descriptor );
            HO_EXPORT ~Schema( );

            HO_EXPORT SchemaObjectContainer Objects( ) const;

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Schema; }

            virtual WideString QualifiedName( ) const override
            {
                return Name( );
            }

            virtual WideString QuotedQualifiedName( ) const override
            {
                auto& name = Name( );
                WideString result;
#ifndef HCC_WITH_BASIC_STRING
                result.reserve( name.size() + 2 );
#endif
                result += '\"';
                result += name;
                result += '\"';
                return result;
            }

        };

        inline SchemaObject::SchemaObject( const OCI::ServiceContext* serviceContext, const Schema* owner, const OCI::ParameterDescriptor* descriptor )
            : Base( serviceContext, owner, descriptor ), schemaName_( descriptor->Schema() )
        {
        }


        class Database : public MetadataObject
        {
        public:
            using Base = MetadataObject;
            using SchemaContainer = std::unordered_map<WideString, std::unique_ptr<Schema>>;
        private:
        public:
            HO_EXPORT Database( const OCI::ServiceContext* serviceContext );
            HO_EXPORT Database( const OCI::ServiceContext& serviceContext );

            HO_EXPORT ~Database( );

            HO_EXPORT SchemaContainer Schemas( ) const;

            virtual Metadata::Kind Kind( ) const noexcept override { return Metadata::Kind::Database; }

        };
    }
}

namespace std
{
    /*
    template<>
    constexpr void swap( Harlinn::OCI::ErrorHandle& first, Harlinn::OCI::ErrorHandle& second ) noexcept
    {
        first.swap( second );
    }*/
    template<>
    constexpr void swap( Harlinn::OCI::Environment& first, Harlinn::OCI::Environment& second ) noexcept
    {
        first.swap( second );
    }
    template<>
    constexpr void swap( Harlinn::OCI::Server& first, Harlinn::OCI::Server& second ) noexcept
    {
        first.swap( second );
    }
    template<>
    constexpr void swap( Harlinn::OCI::Session& first, Harlinn::OCI::Session& second ) noexcept
    {
        first.swap( second );
    }
    template<>
    constexpr void swap( Harlinn::OCI::ServiceContext& first, Harlinn::OCI::ServiceContext& second ) noexcept
    {
        first.swap( second );
    }
    template<>
    constexpr void swap( Harlinn::OCI::TransactionHandle& first, Harlinn::OCI::TransactionHandle& second ) noexcept
    {
        first.swap( second );
    }
    template<>
    constexpr void swap( Harlinn::OCI::Subscription& first, Harlinn::OCI::Subscription& second ) noexcept
    {
        first.swap( second );
    }

}

#pragma pack(pop)

#endif 
