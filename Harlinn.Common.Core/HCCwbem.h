#pragma once
#ifndef HARLINN_COMMON_CORE_HCCWBEM_H_
#define HARLINN_COMMON_CORE_HCCWBEM_H_
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

#include <HCCObj.h>
#include <HCCComImpl.h>

#pragma comment(lib,"wbemuuid.lib")

namespace Harlinn::Common::Core
{
    class WbemProperty;
    class WbemClassObject;
    class WbemMethodSignature;
    class WbemMethod;
    class WbemObjectAccess;
    class WbemQualifierSet;
    class WbemServices;
    class WbemLocator;
    class WbemObjectSink;
    class EnumWbemClassObject;
    class WbemCallResult;
    class WbemContext;
    class UnsecuredApartment;
    class WbemUnsecuredApartment;
    class WbemStatusCodeText;
    class WbemBackupRestore;
    class WbemBackupRestoreEx;
    class WbemRefresher;
    class WbemHiPerfEnum;
    class WbemConfigureRefresher;
    class WbemObjectSinkEx;
    class WbemShutdown;
    class WbemObjectTextSrc;
    class MofCompiler;
    class WbemPropertyProvider;
    class WbemUnboundObjectSink;
    class WbemEventProvider;
    class WbemEventProviderQuerySink;
    class WbemEventProviderSecurity;
    class WbemEventConsumerProvider;
    class WbemProviderInitSink;
    class WbemProviderInit;
    class WbemHiPerfProvider;
    class WbemDecoupledRegistrar;
    class WbemProviderIdentity;
    class WbemDecoupledBasicEventProvider;
    class WbemEventSink;
    class WbemTransport;
    class WbemLevel1Login;
    class WbemConnectorLogin;
    class WbemAddressResolution;
    class WbemClientTransport;
    class WbemClientConnectionTransport;
    class WbemConstructClassObject;

    namespace Wbem
    {
        /// <summary>
        /// Contains constants used to distinguish between classes and instances.
        /// </summary>
        enum class GenusType
        {
            Class = WBEM_GENUS_CLASS,
            Instance = WBEM_GENUS_INSTANCE
        };

        /// <summary>
        /// Method parameter flags.
        /// </summary>
        enum class ChangeFlagType : LONG
        {
            /// <summary>
            /// The class is created if it does not exist, or overwritten if it exists already.
            /// </summary>
            CreateOrUpdate = WBEM_FLAG_CREATE_OR_UPDATE,
            /// <summary>
            /// The class is overwritten if it exists already, but will not be created if it does 
            /// not exist. The class must exist for the call to be successful.
            /// </summary>
            UpdateOnly = WBEM_FLAG_UPDATE_ONLY,
            /// <summary>
            /// This flag is used for creation only. The call fails if the class already exists.
            /// </summary>
            CreateOnly = WBEM_FLAG_CREATE_ONLY,
            /// <summary>
            /// This flag allows a class to be updated if there are no derived classes and there 
            /// are no instances for that class. It also allows updates in all cases if the change 
            /// is just to non-important qualifiers (for example, the Description qualifier). This 
            /// is the default behavior for this call and is used for compatibility with previous 
            /// versions of Windows Management. If the class has instances or changes are to important 
            /// qualifiers, the update fails.
            /// </summary>
            UpdateCompatible = WBEM_FLAG_UPDATE_COMPATIBLE,
            /// <summary>
            /// This flag allows updates of classes even if there are child classes as long as the 
            /// change does not cause any conflicts with child classes. An example of an update this 
            /// flag would allow would be to add a new property to the base class that was not 
            /// previously mentioned in any of the child classes. If the class has instances, the 
            /// update fails.
            /// </summary>
            UpdateSafeMode = WBEM_FLAG_UPDATE_SAFE_MODE,
            /// <summary>
            /// This flag forces updates of classes when conflicting child classes exist. An example 
            /// of an update this flag would force would be if a class qualifier were defined in a 
            /// child class, and the base class tried to add the same qualifier which conflicted with 
            /// the existing one. In force mode, this conflict would be resolved by deleting the 
            /// conflicting qualifier in the child class.
            /// </summary>
            UpdateForceMode = WBEM_FLAG_UPDATE_FORCE_MODE,
            /// <summary>
            /// A mask value that can be used to simplify testing for the other flag values.
            /// </summary>
            UpdateModeMask = WBEM_MASK_UPDATE_MODE,
            /// <summary>
            /// Reserved for future use.
            /// </summary>
            Advisory = WBEM_FLAG_ADVISORY
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( ChangeFlagType, LONG );

        /// <summary>
        /// General-purpose method parameter flags
        /// </summary>
        enum class GenericFlagType : LONG
        {
            ReturnImmediately = WBEM_FLAG_RETURN_IMMEDIATELY,
            ReturnWbemComplete = WBEM_FLAG_RETURN_WBEM_COMPLETE,
            Bidirectional = WBEM_FLAG_BIDIRECTIONAL,
            ForwardOnly = WBEM_FLAG_FORWARD_ONLY,
            NoErrorObject = WBEM_FLAG_NO_ERROR_OBJECT,
            ReturnErrorObject = WBEM_FLAG_RETURN_ERROR_OBJECT,
            SendStatus = WBEM_FLAG_SEND_STATUS,
            DontSendStatus = WBEM_FLAG_DONT_SEND_STATUS,
            EnsureLocatable = WBEM_FLAG_ENSURE_LOCATABLE,
            DirectRead = WBEM_FLAG_DIRECT_READ,
            SendOnlySelected = WBEM_FLAG_SEND_ONLY_SELECTED,
            ReturnWhenComplete = WBEM_RETURN_WHEN_COMPLETE,
            ReservedFlagsMask = WBEM_MASK_RESERVED_FLAGS,
            UseAmendedQualifiers = WBEM_FLAG_USE_AMENDED_QUALIFIERS,
            StrongValidation = WBEM_FLAG_STRONG_VALIDATION,
            Prototype = WBEM_FLAG_PROTOTYPE,
            Deep = WBEM_FLAG_DEEP,
            Shallow = WBEM_FLAG_SHALLOW
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( GenericFlagType, LONG );

        /// <summary>
        /// Describes the status of an asynchronous operation.
        /// </summary>
        enum class StatusType : LONG
        {
            /// <summary>
            /// The operation has completed.
            /// </summary>
            Complete = WBEM_STATUS_COMPLETE,
            /// <summary>
            /// Used in activating post-filtering.
            /// </summary>
            Requirements = WBEM_STATUS_REQUIREMENTS,
            /// <summary>
            /// The operation is still in progress.
            /// </summary>
            Progress = WBEM_STATUS_PROGRESS,
            /// <summary>
            /// Reserved for future use.
            /// </summary>
            LoggingInformation = WBEM_STATUS_LOGGING_INFORMATION,
            /// <summary>
            /// Reserved for future use.
            /// </summary>
            LoggingInformationProvider = WBEM_STATUS_LOGGING_INFORMATION_PROVIDER,
            /// <summary>
            /// Reserved for future use.
            /// </summary>
            LoggingInformationHost = WBEM_STATUS_LOGGING_INFORMATION_HOST,
            /// <summary>
            /// Reserved for future use.
            /// </summary>
            LoggingInformationRepository = WBEM_STATUS_LOGGING_INFORMATION_REPOSITORY,
            /// <summary>
            /// Reserved for future use.
            /// </summary>
            LoggingInformationEss = WBEM_STATUS_LOGGING_INFORMATION_ESS
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( StatusType, LONG );


        /// <summary>
        /// Contains values used to specify the timeout for the EnumWbemClassObject::Next function.
        /// </summary>
        enum class TimeoutType
        {
            NoWait = WBEM_NO_WAIT,
            Infinite = WBEM_INFINITE
        };

        /// <summary>
        /// Flags for the WbemClassObject::GetNames method.
        /// </summary>
        enum class ConditionFlags : LONG
        {
            Always = WBEM_FLAG_ALWAYS,
            OnlyIfTrue = WBEM_FLAG_ONLY_IF_TRUE,
            OnlyIfFalse = WBEM_FLAG_ONLY_IF_FALSE,
            OnlyIfIdentical = WBEM_FLAG_ONLY_IF_IDENTICAL,
            PrimaryConditionMask = WBEM_MASK_PRIMARY_CONDITION,
            KeysOnly = WBEM_FLAG_KEYS_ONLY,
            RefsOnly = WBEM_FLAG_REFS_ONLY,
            LocalOnly = WBEM_FLAG_LOCAL_ONLY,
            PropagatedOnly = WBEM_FLAG_PROPAGATED_ONLY,
            SystemOnly = WBEM_FLAG_SYSTEM_ONLY,
            NonSystemOnly = WBEM_FLAG_NONSYSTEM_ONLY,
            OriginConditionMask = WBEM_MASK_CONDITION_ORIGIN,
            ClassOverridesOnly = WBEM_FLAG_CLASS_OVERRIDES_ONLY,
            ClassLocalAndOverrides = WBEM_FLAG_CLASS_LOCAL_AND_OVERRIDES,
            ClassConditionMask = WBEM_MASK_CLASS_CONDITION
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( ConditionFlags, LONG );

        /// <summary>
        ///  Qualifier flavors.
        /// </summary>
        enum class FlavorType : LONG
        {
            /// <summary>
            /// The qualifier is not propagated to instances or derived classes.
            /// </summary>
            DontPropagate = WBEM_FLAVOR_DONT_PROPAGATE,
            /// <summary>
            /// The qualifier is propagated to instances.
            /// </summary>
            PropagateToInstance = WBEM_FLAVOR_FLAG_PROPAGATE_TO_INSTANCE,
            /// <summary>
            /// The qualifier is propagated to derived classes. This flavor is only appropriate 
            /// for qualifiers defined for a class and cannot be attached to a qualifier describing 
            /// a class instance.
            /// </summary>
            PropagateToDerivedClass = WBEM_FLAVOR_FLAG_PROPAGATE_TO_DERIVED_CLASS,
            /// <summary>
            /// Propagation mask value
            /// </summary>
            PropagationMask = WBEM_FLAVOR_MASK_PROPAGATION,
            /// <summary>
            /// When propagated to a derived class or instance, the value of the qualifier can be 
            /// overridden. Setting EnableOverride is optional because being able to override the 
            /// qualifier value is the default functionality for propagated qualifiers.
            /// </summary>
            Overridable = WBEM_FLAVOR_OVERRIDABLE,
            /// <summary>
            /// The qualifier cannot be overridden in a derived class or instance. Note that being 
            /// able to override a propagated qualifier is the default.
            /// </summary>
            NotOverridable = WBEM_FLAVOR_NOT_OVERRIDABLE,
            /// <summary>
            /// Permissions mask value
            /// </summary>
            PermissionsMask = WBEM_FLAVOR_MASK_PERMISSIONS,
            /// <summary>
            /// <p>
            /// For a class: the property belongs to the derived-most class.
            /// </p>
            /// <p>
            /// For an instance: the property is modified at the instance level (that is, 
            /// either a value was supplied or a qualifier was added/modified).
            /// </p>
            /// </summary>
            OriginLocal = WBEM_FLAVOR_ORIGIN_LOCAL,
            /// <summary>
            /// <p>
            /// For a class: The property was inherited from the parent class.
            /// </p>
            /// <p>
            /// For an instance: The property, while inherited from the parent class, has not 
            /// been modified at the instance level.
            /// </p>
            /// </summary>
            OriginPropagated = WBEM_FLAVOR_ORIGIN_PROPAGATED,
            /// <summary>
            /// The property is a standard system property.
            /// </summary>
            OriginSystem = WBEM_FLAVOR_ORIGIN_SYSTEM,
            /// <summary>
            /// Origin mask value
            /// </summary>
            OriginMask = WBEM_FLAVOR_MASK_ORIGIN,
            /// <summary>
            /// 
            /// </summary>
            NotAmended = WBEM_FLAVOR_NOT_AMENDED,
            /// <summary>
            /// The qualifier is not required in the basic class definition and can be moved 
            /// to the amendment to be localized.
            /// </summary>
            Amended = WBEM_FLAVOR_AMENDED,
            /// <summary>
            /// Amended mask value
            /// </summary>
            AmendedMask = WBEM_FLAVOR_MASK_AMENDED
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( FlavorType, LONG );

        /// <summary>
        /// Flags used to define a query or enumerator.
        /// </summary>
        enum class QueryFlagType : LONG
        {
            /// <summary>
            /// Include the specified class and all subclasses.
            /// </summary>
            Deep = WBEM_FLAG_DEEP,
            /// <summary>
            /// Include only the specified class, not any subclasses.
            /// </summary>
            Shallow = WBEM_FLAG_SHALLOW,
            /// <summary>
            /// Used for prototyping. It does not execute the query and 
            /// instead returns an object that looks like a typical result object.
            /// </summary>
            Prototype = WBEM_FLAG_PROTOTYPE
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( QueryFlagType, LONG );

        /// <summary>
        /// Flags used for setting security access levels.
        /// </summary>
        enum class SecurityFlags : LONG
        {
            None = 0,
            /// <summary>
            /// Enables the account and grants the user read permissions. This is a default 
            /// access right for all users and corresponds to the Enable Account permission 
            /// on the Security tab of the WMI Control.
            /// </summary>
            Enable = WBEM_ENABLE,
            /// <summary>
            /// <p>
            /// Allows the execution of methods.
            /// </p>
            /// <p>
            /// Providers can perform additional access checks. This is a default access right 
            /// for all users and corresponds to the Execute Methods permission on the Security 
            /// tab of the WMI Control.
            /// </p>
            /// </summary>
            MethodExecute = WBEM_METHOD_EXECUTE,
            /// <summary>
            /// Allows a user account to write to classes in the WMI repository as well as instances. 
            /// A user cannot write to system classes. Only members of the Administrators group have 
            /// this permission. FullWriteRep corresponds to the Full Write permission on the Security 
            /// tab of the WMI Control.
            /// </summary>
            FullWriteRep = WBEM_FULL_WRITE_REP,
            /// <summary>
            /// Allows you to write data to instances only, not classes. A user cannot write classes to 
            /// the WMI repository. Only members of the Administrators group have this right. 
            /// PartialWriteRep corresponds to the Partial Write permission on the Security tab of 
            /// the WMI Control.
            /// </summary>
            PartialWriteRep = WBEM_PARTIAL_WRITE_REP,
            /// <summary>
            /// Allows writing classes and instances to providers. Note that providers can do additional 
            /// access checks when impersonating a user. This is a default access right for all users and 
            /// corresponds to the Provider Write permission on the Security tab of the WMI Control.
            /// </summary>
            WriteProvider = WBEM_WRITE_PROVIDER,
            /// <summary>
            /// Allows a user account to remotely perform any operations allowed by the permissions described 
            /// above. Only members of the Administrators group have this right. RemoteAccess corresponds to 
            /// the Remote Enable permission on the Security tab of the WMI Control.
            /// </summary>
            RemoteAccess = WBEM_REMOTE_ACCESS,
            /// <summary>
            /// Specifies that a consumer can subscribe to the events delivered to a sink. Used in 
            /// WbemEventSink::SetSinkSecurity.
            /// </summary>
            RightSubscribe = WBEM_RIGHT_SUBSCRIBE,
            /// <summary>
            /// Specifies that the account can publish events to the instance of __EventFilter that defines 
            /// the event filter for a permanent consumer.
            /// </summary>
            RightPublish = WBEM_RIGHT_PUBLISH
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( SecurityFlags, LONG );

        enum class LimitationFlagType : LONG
        {
            None = 0,
            ExcludeObjectQualifiers = WBEM_FLAG_EXCLUDE_OBJECT_QUALIFIERS,
            ExcludePropertyQualifiers = WBEM_FLAG_EXCLUDE_PROPERTY_QUALIFIERS
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( LimitationFlagType, LONG );

        /// <summary>
        /// Flags controlling the execution of the WbemClassObject::GetObjectText method.
        /// </summary>
        enum class TextFlagType : LONG
        {
            None = 0,
            /// <summary>
            /// Present qualifiers without propagation or flavor information.
            /// </summary>
            NoFlavors = WBEM_FLAG_NO_FLAVORS
        };

        /// <summary>
        /// Flags that define the comparison to perform when using the WbemClassObject::CompareTo method.
        /// </summary>
        enum class ComparisonFlags : LONG
        {
            /// <summary>
            /// Compare all features.
            /// </summary>
            IncludeAll = WBEM_COMPARISON_INCLUDE_ALL,
            /// <summary>
            /// Ignore all qualifiers (including Key and Dynamic) in comparison.
            /// </summary>
            IgnoreQualifiers = WBEM_FLAG_IGNORE_QUALIFIERS,
            /// <summary>
            /// Ignore the source of the objects, namely the server and the namespace they came from, 
            /// in comparison to other objects.
            /// </summary>
            IgnoreObjectSource = WBEM_FLAG_IGNORE_OBJECT_SOURCE,
            /// <summary>
            /// Ignore default values of properties. This flag is only meaningful when comparing classes.
            /// </summary>
            IgnoreDefaultValues = WBEM_FLAG_IGNORE_DEFAULT_VALUES,
            /// <summary>
            /// Assume that the objects being compared are instances of the same class. Consequently, 
            /// this flag compares instance-related information only. Use this flag to optimize 
            /// performance. If the objects are not of the same class, the results are undefined.
            /// </summary>
            IgnoreClass = WBEM_FLAG_IGNORE_CLASS,
            /// <summary>
            /// Compare string values in a case-insensitive manner. This applies both to strings and 
            /// to qualifier values. Property and qualifier names are always compared in a case-insensitive 
            /// manner whether this flag is specified or not.
            /// </summary>
            IgnoreCase = WBEM_FLAG_IGNORE_CASE,
            /// <summary>
            /// Ignore qualifier flavors. This flag still takes qualifier values into account, but 
            /// ignores flavor distinctions such as propagation rules and override restrictions.
            /// </summary>
            IgnoreFlavor = WBEM_FLAG_IGNORE_FLAVOR
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( ComparisonFlags, LONG );

        enum class Locking : LONG
        {
            None = 0,
            AllowRead = WBEM_FLAG_ALLOW_READ
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( Locking, LONG );

        enum class CimType : LONG
        {
            Illegal = CIM_ILLEGAL,
            Empty = CIM_EMPTY,
            SByte = CIM_SINT8,
            Byte = CIM_UINT8,
            Int16 = CIM_SINT16,
            UInt16 = CIM_UINT16,
            Int32 = CIM_SINT32,
            UInt32 = CIM_UINT32,
            Int64 = CIM_SINT64,
            UInt64 = CIM_UINT64,
            Single = CIM_REAL32,
            Double = CIM_REAL64,
            Boolean = CIM_BOOLEAN,
            String = CIM_STRING,
            DateTime = CIM_DATETIME,
            Reference = CIM_REFERENCE,
            WChar = CIM_CHAR16,
            Object = CIM_OBJECT,
            ArrayFlag = CIM_FLAG_ARRAY
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( CimType, LONG );

        enum class BackupRestoreFlags : LONG
        {
            Default = WBEM_FLAG_BACKUP_RESTORE_DEFAULT,
            ForceShutdown = WBEM_FLAG_BACKUP_RESTORE_FORCE_SHUTDOWN
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( BackupRestoreFlags, LONG );

        enum class RefresherFlags : LONG
        {
            AutoReconnect = WBEM_FLAG_REFRESH_AUTO_RECONNECT,
            NoAutoReconnect = WBEM_FLAG_REFRESH_NO_AUTO_RECONNECT
        };
        HCC_DEFINE_ENUM_FLAG_OPERATORS( RefresherFlags, LONG );

        enum class ShutdownFlags : LONG
        {
            UnloadComponent = WBEM_SHUTDOWN_UNLOAD_COMPONENT,
            WMI = WBEM_SHUTDOWN_WMI,
            OS = WBEM_SHUTDOWN_OS
        };

        enum class StatusFormat : LONG
        {
            Newline = WBEMSTATUS_FORMAT_NEWLINE,
            NoNewline = WBEMSTATUS_FORMAT_NO_NEWLINE
        };

        namespace Limits
        {
            constexpr LONG MaxIdentifier = WBEM_MAX_IDENTIFIER;
            constexpr LONG MaxQuery = WBEM_MAX_QUERY;
            constexpr LONG MaxPath = WBEM_MAX_PATH;
            constexpr LONG MaxObjectNesting = WBEM_MAX_OBJECT_NESTING;
            constexpr LONG MaxUserProperties = WBEM_MAX_USER_PROPERTIES;
        }
    }


    class WbemProperty
    {
        struct Data
        {
            SysString name_;
            Variant value_;
            Wbem::CimType type_;
            Wbem::FlavorType flavor_;

            Data( const SysString& name, const Variant& value, Wbem::CimType type, Wbem::FlavorType flavor )
                : name_(name), value_( value ), type_( type ), flavor_( flavor )
            { }
            Data( SysString&& name, Variant&& value, Wbem::CimType type, Wbem::FlavorType flavor )
                : name_( std::move(name) ), value_( std::move( value ) ), type_( type ), flavor_( flavor )
            { }
        };
        std::unique_ptr<Data> data_;
    public:
        constexpr WbemProperty( ) noexcept = default;

        WbemProperty( const SysString& name, const Variant& value, Wbem::CimType type, Wbem::FlavorType flavor )
            : data_( std::make_unique<Data>( name, value, type, flavor ) )
        { }
        WbemProperty( SysString&& name, Variant&& value, Wbem::CimType type, Wbem::FlavorType flavor )
            : data_( std::make_unique<Data>( std::move(name), std::move( value ), type, flavor ) )
        { }

        WbemProperty( const WbemProperty& other ) = delete;
        WbemProperty& operator = ( const WbemProperty& other ) = delete;

        WbemProperty( WbemProperty&& other ) noexcept
            : data_( std::move( other.data_ ) )
        { }
        WbemProperty& operator = ( WbemProperty&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }
        void swap( WbemProperty& other ) noexcept
        {
            std::swap( data_, other.data_ );
        }

        explicit operator bool( ) const
        {
            return data_ != nullptr;
        }
        bool IsValid( ) const noexcept
        {
            return data_ != nullptr;
        }

        const SysString& Name( ) const noexcept
        {
            return data_->name_;
        }
        const Variant& Value( ) const noexcept
        {
            return data_->value_;
        }
        Wbem::CimType Type( ) const noexcept
        {
            return data_->type_;
        }
        Wbem::FlavorType Flavor( ) const noexcept
        {
            return data_->flavor_;
        }
    };

    /// <summary>
    /// The WbemClassObject contains and manipulates both class definitions and class object instances.
    /// </summary>
    class WbemClassObject : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemClassObject, Unknown )

        /// <summary>
        /// Returns an interface pointer that allows read and write operations on the set 
        /// of qualifiers for the entire class object, whether the object is an instance or 
        /// a class definition. Any qualifiers added, deleted, or edited using the returned 
        /// pointer apply to the entire instance or class definition.
        /// </summary>
        /// <param name="qualifierSet">
        /// Receives the interface pointer that allows access to the qualifiers for the class object. 
        /// The returned object has a positive reference count upon return from the call. The caller 
        /// must call IWbemQualifierSet::Release when the object is no longer needed. This parameter 
        /// cannot be NULL. On error, a new object is not returned and the pointer is left unmodified.
        /// </param>
        void GetQualifierSet( IWbemQualifierSet** qualifierSet ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetQualifierSet( qualifierSet );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns an object that allows read and write operations on the set 
        /// of qualifiers for the entire class object, whether the object is an instance or 
        /// a class definition. Any qualifiers added, deleted, or edited using the returned 
        /// pointer apply to the entire instance or class definition.
        /// </summary>
        /// <returns>
        /// A WbemQualifierSet that allows read and write operations on the set of qualifiers 
        /// for the entire class object. 
        /// </returns>
        inline WbemQualifierSet GetQualifierSet( ) const;

        /// <summary>
        /// Retrieves the specified property value, if it exists. This method can also return system properties.
        /// </summary>
        /// <param name="name">Name of the desired property. It is treated as read-only.</param>
        /// <param name="flags">Reserved. This parameter must be 0 (zero).</param>
        /// <param name="value">
        /// When successful, this parameter is assigned the correct type and value for the qualifier, 
        /// and the VariantInit function is called on pVal. It is the responsibility of the caller to 
        /// call VariantClear on pVal when the value is not needed. If there is an error, the value 
        /// that pVal points to is not modified. If an uninitialized pVal value is passed to the method, 
        /// then the caller must check the return value of the method, and call VariantClear only when 
        /// the method succeeds.
        /// </param>
        /// <param name="type">
        /// Can be NULL. If it is not NULL, it receives the CIM type of the property, that is, one of 
        /// the CIM-type constants, such as CIM_SINT32, CIM_STRING, and so on. This indicates the CIM 
        /// semantics of the property value packed into VARIANT.
        /// </param>
        /// <param name="flavor">
        /// Can be NULL. If not NULL, the LONG value pointed to receives information about the origin of the property.
        /// </param>
        void Get( LPCWSTR name, long flags, VARIANT* value, CIMTYPE* type, long* flavor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Get( name, flags, value, type, flavor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Get( LPCWSTR name, VARIANT* value, CIMTYPE* type = nullptr, long* flavor = nullptr ) const
        {
            Get( name, 0, value, type, flavor );
        }

        Variant Get( LPCWSTR name ) const
        {
            Variant result;
            Get( name, &result );
            return result;
        }


        template<WideStringType T>
        void Get( const T& name, long flags, VARIANT* value, CIMTYPE* type, long* flavor ) const
        {
            Get( name.c_str(), flags, value, type, flavor );
        }

        /// <summary>
        /// <p>
        /// The Put method sets a named property to a new value. This method always overwrites the 
        /// current value with a new one. When WbemClassObject references a CIM class definition, 
        /// Put creates or updates the property value. When the WbemClassObject references a CIM 
        /// instance, Put updates a property value only. Put cannot create a property value.
        /// </p>
        /// <p>
        /// A user cannot create properties with names that begin or end with an underscore (_). This 
        /// is reserved for system classes and properties.
        /// </p>
        /// </summary>
        /// <param name="name">A parameter that must point to a valid property name. This parameter cannot be NULL.</param>
        /// <param name="flags">Reserved. This parameter must be 0 (zero).</param>
        /// <param name="value">
        /// A parameter that must point to a valid VARIANT, which becomes the new property value. If pVal is 
        /// NULL or points to a VARIANT of type VT_NULL, the property is set to NULL, that is, no value.
        /// </param>
        /// <param name="type">
        /// <p>
        /// A type of VARIANT pointed to by pVal.
        /// </p>
        /// <p>
        /// The NULL value for a property designated by a VARIANT of type VT_NULL is distinguished 
        /// from a property of type VT_I4 with a 0 (zero) value.
        /// </p>
        /// <p>
        /// When creating new properties, if value is NULL or points to a VT_NULL, the type of the 
        /// property is determined from the type parameter.
        /// </p>
        /// <p>
        /// If value is to contain an embedded IWbemClassObject, the caller must call IWbemClassObject::QueryInterface 
        /// for IID_IUnknown and place the resulting pointer in the VARIANT using a type of VT_UNKNOWN. The original 
        /// embedded object is copied during the Put operation, and so cannot be modified by the operation.
        /// </p>
        /// <p>
        /// The pointer is treated as read-only. The caller must call VariantClear after this call is complete.
        /// </p>
        /// <p>
        /// Use this parameter only when creating new properties in a CIM class definition and value is NULL or 
        /// points to a VARIANT of type VT_NULL. In such a case, the type parameter specifies the CIM type of 
        /// the property. In every other case, type must be 0 (zero). Also, type must be 0 (zero) when the 
        /// underlying object is an instance (even if value is NULL), because the type of the property is fixed 
        /// and cannot be changed. In other words, use type if, and only if, value is NULL or points to a 
        /// VT_NULLVARIANT, and the underlying object is a CIM class.
        /// </p>
        /// <p>
        /// When using IWbemClassObject::Put to assign empty array values to a property, you do not need to 
        /// specify the exact VT type; you can assign a value to pVal that is a VARIANT with a variant type of 
        /// VT_ARRAY|VT_VARIANT.
        /// </p>
        /// </param>
        /// <remarks>
        /// <p>
        /// If the property set by the Put method exists in the parent class, the default value of the property 
        /// is changed unless the property type does not match the parent class type. If the property does not 
        /// exist and it is not a type mismatch, the property is created.
        /// </p>
        /// <p>
        /// When executing this method on an instance, an overwrite always occurs, because the property always exists.
        /// </p>
        /// <p>
        /// When creating a new class and the underlying type of the property is an object reference, date/time string, 
        /// or other special type, you might need to modify the CIM type parameter for the property to indicate the 
        /// special new class. The CIMType qualifier on instance properties is read-only and inherited from the class object.
        /// </p>
        /// <p>
        /// If the variant type specified in value does not match the CIM type of the property, WMI attempts to change 
        /// the variant to the appropriate variant type, using the normal variant coercion rules. If the variant cannot 
        /// be coerced, a COMException for WBEM_E_TYPE_MISMATCH is thrown.
        /// </p>
        /// <p>
        /// The __CLASS system property is only writable during class creation, when it may not be left blank. All other 
        /// system properties are read-only.
        /// </p>
        /// </remarks>
        void Put( LPCWSTR name, long flags, VARIANT* value, CIMTYPE type ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Put( name, flags, value, type );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<WideStringType T>
        void Put( const T& name, long flags, VARIANT* value, CIMTYPE type ) const
        {
            Put( name.c_str(), flags, value, type );
        }

        /// <summary>
        /// <p>
        /// The Delete method deletes the specified property from a CIM class definition and all of 
        /// its qualifiers. Because instances cannot have contents that are different from the owning 
        /// class, delete operations for properties are only possible on class definitions. If you 
        /// invoke Delete on a property in an instance, the operation succeeds; however, rather than 
        /// removing the value, it is simply reset to the default value for the class.
        /// </p>
        /// <p>
        /// It is not possible to delete a property inherited from a parent class. However, if an 
        /// override default value for a property inherited from a parent class was specified, it is 
        /// possible to revert to the parent's default value by invoking this method. In this case, true is returned.
        /// </p>
        /// <p>
        /// System properties cannot be deleted.
        /// </p>
        /// </summary>
        /// <param name="name"></param>
        /// <returns>
        /// Returns true if the Delete method on the interface returned WBEM_S_RESET_TO_DEFAULT.
        /// </returns>
        bool Delete( LPCWSTR name ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Delete( name );
            if ( hr != WBEM_S_RESET_TO_DEFAULT )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr == WBEM_S_RESET_TO_DEFAULT ? true : false;
        }
        template<WideStringType T>
        bool Delete( const T& name ) const
        {
            return Delete( name.c_str() );
        }

        /// <summary>
        /// <p>
        /// Retrieves the names of the properties in the object. Furthermore, depending on 
        /// user-supplied selection criteria, it can retrieve all or a subset of the 
        /// properties. These properties can then be accessed by using Get for each name. 
        /// </p>
        /// <p>
        /// This method can also return system properties.
        /// </p>
        /// </summary>
        /// <param name="qualifierName">
        /// A parameter that can be NULL. If not NULL, it must point to a valid LPCWSTR 
        /// specifying a qualifier name which operates as part of a filter. This is 
        /// handled as read-only.
        /// </param>
        /// <param name="flags">For more information, see Remarks.</param>
        /// <param name="qualifierValue">
        /// A parameter that can be NULL. If not NULL, it must point to a valid VARIANT structure 
        /// initialized to a filter value. This VARIANT is handled as read-only by the method. 
        /// Thus, the caller must call VariantClear on it, if required. For more information, see Remarks.
        /// </param>
        /// <param name="names">
        /// A parameter that cannot be NULL, but on entry this parameter must point to NULL. A new 
        /// SAFEARRAY structure is always allocated, and the pointer is set to point to it. The returned 
        /// array can have 0 elements, but is always allocated when WBEM_S_NO_ERROR returns. On error, a new 
        /// SAFEARRAY structure is not returned.
        /// </param>
        /// <remarks>
        /// 
        /// </remarks>
        void GetNames( LPCWSTR qualifierName, long flags, VARIANT* qualifierValue, SAFEARRAY** names ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNames( qualifierName, flags, qualifierValue, names );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        SafeArray GetNames( LPCWSTR qualifierName, long flags, VARIANT* qualifierValue = nullptr ) const
        {
            SAFEARRAY* ptr;
            GetNames( qualifierName, flags, qualifierValue, &ptr );
            return SafeArray( ptr );
        }

        template<WideStringType T>
        void GetNames( const T& qualifierName, long flags, VARIANT* qualifierValue, SAFEARRAY** names ) const
        {
            GetNames( qualifierName.c_str(), flags, qualifierValue, names );
        }
        template<WideStringType T>
        SafeArray GetNames( const T& qualifierName, long flags, VARIANT* qualifierValue ) const
        {
            return GetNames( qualifierName.c_str( ), flags, qualifierValue );
        }


        /// <summary>
        /// The BeginEnumeration method resets an enumeration back to the beginning of the enumeration. 
        /// The caller must call this method prior to the first call to Next to enumerate all of the 
        /// properties on an object. The order in which properties are enumerated is guaranteed to be 
        /// invariant for a given instance.
        /// </summary>
        /// <param name="enumFlags"></param>
        void BeginEnumeration( Wbem::ConditionFlags enumFlags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BeginEnumeration( static_cast<long>( enumFlags ) );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// <p>
        /// The Next method retrieves the next property in an enumeration that started with BeginEnumeration. 
        /// This should be called repeatedly to enumerate all the properties until Next returns false. If the 
        /// enumeration is to be terminated early, then EndEnumeration should be called.
        /// </p>
        /// </summary>
        /// <param name="flags">Reserved. This parameter must be 0.</param>
        /// <param name="name">
        /// Receives a new BSTR that contains the property name. To prevent memory leaks in the client process, 
        /// the caller must call SysFreeString when the name is no longer required. You can set this parameter 
        /// to NULL if the name is not required.
        /// </param>
        /// <param name="value">
        /// <p>
        /// This VARIANT is filled with the value of the property. The method calls VariantInit on this VARIANT, 
        /// so the caller should ensure that the VARIANT is not active prior to the call. The caller must use 
        /// VariantClear when the value is no longer required.
        /// </p>
        /// <p>
        /// You can set this parameter to NULL if the value is not required. If an error code is returned, 
        /// the VARIANT pointed to by value is left unmodified.
        /// </p>
        /// </param>
        /// <param name="type">
        /// This parameter can be NULL. If it is not NULL, it must point to a CIMTYPE variable (a LONG) into 
        /// which the type of the property is placed. It is possible that the value of this property can be a 
        /// VT_NULL VARIANT, in which case it is necessary to determine the actual type of the property.
        /// </param>
        /// <param name="flavor">
        /// <p>
        /// Can be NULL. If not NULL, the LONG value pointed to receives information from the Webm::FlavorType
        /// enumeration.
        /// </param>
        /// <returns>
        /// false if there are no more properties left to enumerate, true otherwise. 
        /// </returns>
        bool Next( long flags, BSTR* name, VARIANT* value, CIMTYPE* type, long* flavor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Next( flags, name, value, type, flavor );
            if ( hr != WBEM_S_NO_MORE_DATA )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != WBEM_S_NO_MORE_DATA;
        }
        bool Next( BSTR* name, VARIANT* value, CIMTYPE* type, long* flavor ) const
        {
            return Next( 0, name, value, type, flavor );
        }

        WbemProperty Next( ) const
        {
            BSTR name = nullptr; 
            Variant value; 
            CIMTYPE type; 
            long flavor;
            if ( Next( &name, &value, &type, &flavor ) )
            {
                return WbemProperty(SysString(name,true),std::move(value),static_cast<Wbem::CimType>(type), static_cast<Wbem::FlavorType>( flavor ) );
            }
            else
            {
                return WbemProperty( );
            }
        }



        /// <summary>
        /// The EndEnumeration function terminates an enumeration sequence started with BeginEnumeration. 
        /// This call is not required, but it is recommended to developers because it releases resources 
        /// associated with the enumeration. However, the resources are deallocated automatically when 
        /// the next enumeration is started or the object is released.
        /// </summary>
        void EndEnumeration( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EndEnumeration( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// The GetPropertyQualifierSet function retrieves the qualifier set for a particular property in 
        /// the class object. You can use this method with properties that are a member of an instance or 
        /// a class definition.
        /// </summary>
        /// <param name="propertyName">
        /// Property for which the qualifier set is requested. This cannot be NULL and must point to a valid 
        /// LPCWSTR. The property can be local or propagated from the parent class. Note that system properties 
        /// have no qualifiers so this method returns false if you attempt to obtain the IWbemQualifierSet 
        /// pointer for a system property.
        /// </param>
        /// <param name="qualifierSet">
        /// Receives an interface pointer that allows access to the qualifiers for the named property. The 
        /// caller must call IWbemQualifierSet::Release on the pointer when access to the object is no longer 
        /// required. The property is set to point to NULL when there are error conditions. A new object is 
        /// not returned.
        /// </param>
        /// <returns>
        /// true if the function was able to retrieve a qualifier set for the requested property, and otherwise false.
        /// <returns>
        bool GetPropertyQualifierSet( LPCWSTR propertyName, IWbemQualifierSet** qualifierSet ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyQualifierSet( propertyName, qualifierSet );
            if ( hr != WBEM_E_SYSTEM_PROPERTY )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != WBEM_E_SYSTEM_PROPERTY;
        }
        template<WideStringType T>
        bool GetPropertyQualifierSet( const T& propertyName, IWbemQualifierSet** qualifierSet ) const
        {
            return GetPropertyQualifierSet( propertyName.c_str( ), qualifierSet );
        }

        inline WbemQualifierSet GetPropertyQualifierSet( LPCWSTR propertyName ) const;
        template<WideStringType T>
        inline WbemQualifierSet GetPropertyQualifierSet( const T& propertyName ) const;

        /// <summary>
        /// The Clone method returns a new object that is a complete clone of the current object. The new object 
        /// has a COM reference count of 1.
        /// </summary>
        /// <param name="copy">
        /// This parameter cannot be NULL. It receives the copy of the current object. You must call 
        /// IWbemClassObject::Release on this object when it is no longer required.
        /// </param>
        void Clone( IWbemClassObject** copy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clone( copy );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        WbemClassObject Clone( ) const
        {
            IWbemClassObject* ptr = nullptr;
            Clone( &ptr );
            return WbemClassObject( ptr );
        }


        /// <summary>
        /// The GetObjectText method returns a textual rendering of the object in the MOF syntax. 
        /// Notice that the MOF text returned does not contain all the information about the object, 
        /// but only enough information for the MOF compiler to be able to re-create the original 
        /// object. For instance, no propagated qualifiers or parent class properties are displayed.
        /// </summary>
        /// <param name="flags">
        /// Normally 0 (or TextFlagType::None). If TextFlagType::NoFlavors is specified, qualifiers 
        /// will be presented without propagation or flavor information.
        /// </param>
        /// <param name="objectText">
        /// This must point to NULL on entry. This parameter receives from Windows Management a newly 
        /// allocated BSTR that was initialized with SysAllocString. You must call SysFreeString on the 
        /// pointer when the string is no longer required. This pointer points to a MOF syntax rendering 
        /// of the object upon return from the call. Because this is an out parameter, the pointer must 
        /// not point to a string that is valid before this method is called, because the pointer will 
        /// not be deallocated.
        /// </param>
        void GetObjectText( long flags, BSTR* objectText ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObjectText( flags, objectText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetObjectText( Wbem::TextFlagType flags, BSTR* objectText ) const
        {
            GetObjectText( static_cast<long>(flags), objectText );
        }

        SysString GetObjectText( long flags ) const
        {
            BSTR ptr = nullptr;
            GetObjectText( flags, &ptr );
            return SysString( ptr, true );
        }
        SysString GetObjectText( Wbem::TextFlagType flags ) const
        {
            return GetObjectText( static_cast<long>( flags ) );
        }

        /// <summary>
        /// Use the SpawnDerivedClass function to create a newly derived class object from 
        /// the current object. The current object must be a class definition that becomes 
        /// the parent class of the spawned object. The returned object becomes a subclass 
        /// of the current object.
        /// </summary>
        /// <param name="flags">Reserved. This parameter must be 0.</param>
        /// <param name="newClass">
        /// Cannot be NULL. This receives the pointer to the new class definition object. 
        /// The caller must invoke IWbemClassObject::Release when the object is no longer 
        /// required, typically after you have invoked WbemServices::PutClass to write the 
        /// class definition. On error, a new object is not returned, and newClass is left 
        /// unmodified.
        /// </param>
        /// <remarks>
        /// <p>
        /// The new object returned in newClass automatically becomes a subclass of the current 
        /// object. This behavior cannot be overridden. There is no other method by which 
        /// subclasses (derived classes) can be created.
        /// </p>
        /// <p>
        /// You cannot create a derived class from a class that is local to your own client process. 
        /// The parent class (base class) must be created and registered with Windows Management 
        /// using WbemServices::PutClass, and then retrieved using WbemServices::GetObject before 
        /// this method can be used to create a derived class.
        /// </p>
        /// <p>
        /// To create a class hierarchy, you must create the initial class with WbemServices::PutClass, 
        /// retrieve it using WbemServices::GetObject, and use the retrieved object to create the 
        /// newly derived class. Then, this newly derived class must be created using WbemServices::PutClass. 
        /// To create other derived classes, you must call WbemServices::GetObject, then call 
        /// WbemClassObject::SpawnDerivedClass, and so on, in a cycle for each new derivation level. 
        /// You must follow this procedure to prevent version errors and concurrency conflicts.
        /// </p>
        /// </remarks>
        void SpawnDerivedClass( long flags, IWbemClassObject** newClass ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SpawnDerivedClass( flags, newClass );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SpawnDerivedClass( IWbemClassObject** newClass ) const
        {
            SpawnDerivedClass( 0, newClass );
        }
        WbemClassObject SpawnDerivedClass( ) const
        {
            IWbemClassObject* ptr = nullptr;
            SpawnDerivedClass( &ptr );
            return WbemClassObject( ptr );
        }


        /// <summary>
        /// <p>
        /// Use the SpawnInstance method to create a new instance of a class. The current object 
        /// must be a class definition obtained from Windows Management using WbemServices::GetObject, 
        /// WbemServices::CreateClassEnum, or WbemServices::CreateClassEnumAsync Then, use this 
        /// class definition to create new instances.
        /// </p>
        /// <p>
        /// A call to WbemServices::PutInstance is required to actually write the instance to 
        /// Windows Management. If you intend to discard the object before calling WbemServices::PutInstance, 
        /// simply make a call to IWbemClassObject::Release.
        /// </p>
        /// </summary>
        /// <param name="flags">Reserved. This parameter must be 0.</param>
        /// <param name="newInstance">
        /// Cannot be NULL. It receives a new instance of the class. The caller must invoke 
        /// IWbemClassObject::Release when the pointer is no longer required. On error, a new 
        /// object is not returned and the pointer is left unmodified.
        /// </param>
        void SpawnInstance( long flags, IWbemClassObject** newInstance ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SpawnInstance( flags, newInstance );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SpawnInstance( IWbemClassObject** newInstance ) const
        {
            SpawnInstance( 0, newInstance );
        }
        WbemClassObject SpawnInstance( ) const
        {
            IWbemClassObject* ptr = nullptr;
            SpawnInstance( &ptr );
            return WbemClassObject( ptr );
        }


        /// <summary>
        /// The CompareTo method compares an object to another Windows Management object. Note that there are certain constraints in this comparison process.
        /// </summary>
        /// <param name="flags">See Wbem::ComparisonFlags for details.</param>
        /// <param name="compareTo">
        /// Object in comparison. This pointer must point to a valid IWbemClassObject instance. It cannot be NULL.
        /// </param>
        /// <returns>true if the objects compare as equal, false otherwise.</returns>
        bool CompareTo( long flags, IWbemClassObject* compareTo ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CompareTo( flags, compareTo );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }
        bool CompareTo( Wbem::ComparisonFlags flags, IWbemClassObject* compareTo ) const
        {
            return CompareTo( static_cast<long>( flags ), compareTo );
        }

        bool CompareTo( Wbem::ComparisonFlags flags, const WbemClassObject& compareTo ) const
        {
            return CompareTo( flags, compareTo.GetInterfacePointer<IWbemClassObject>() );
        }


        /// <summary>
        /// The GetPropertyOrigin function retrieves the name of the class in which 
        /// a particular property was introduced. For classes with deep inheritance 
        /// hierarchies, it is often desirable to know which properties were declared 
        /// in which classes. If the object does not inherit from a parent class, as 
        /// in the case of a base class, for example, then the current class name is returned.
        /// </summary>
        /// <param name="name">
        /// Property name for which the owning class name is desired. This must point to a 
        /// valid LPCWSTR, which is treated as read-only.
        /// </param>
        /// <param name="className">
        /// Pointer to the address of a new BSTR that receives the parent class name. To 
        /// prevent memory leaks in the client process, the caller must call SysFreeString 
        /// when the name is no longer required. This parameter must not point to a valid 
        /// string before the method is called because this is an output parameter, and 
        /// this pointer is not deallocated after the call is complete.
        /// </param>
        void GetPropertyOrigin( LPCWSTR name, BSTR* className ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyOrigin( name, className );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<WideStringType T>
        void GetPropertyOrigin( const T& name, BSTR* className ) const
        {
            GetPropertyOrigin( name.c_str(), className );
        }
        SysString GetPropertyOrigin( LPCWSTR name ) const
        {
            BSTR ptr = nullptr;
            GetPropertyOrigin( name, &ptr );
            return SysString( ptr, true );
        }
        template<WideStringType T>
        SysString GetPropertyOrigin( const T& name ) const
        {
            return GetPropertyOrigin( name.c_str() );
        }

        /// <summary>
        /// The InheritsFrom function determines if the current class or instance 
        /// derives from the specified parent class.
        /// </summary>
        /// <param name="ancestor">
        /// Cannot be NULL. It contains the class name that is being tested. If the 
        /// current object has this class for one of its ancestor classes, the function returns true. 
        /// This must point to a valid LPCWSTR, which is treated as read-only.
        /// </param>
        /// <returns>
        /// true if the current class or instance derives from the specified parent class, false otherwise.
        /// </returns>
        bool InheritsFrom( LPCWSTR ancestor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->InheritsFrom( ancestor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }
        template<WideStringType T>
        bool InheritsFrom( const T& name ) const
        {
            return InheritsFrom( name.c_str( ) );
        }

        /// <summary>
        /// The GetMethod function returns information about the requested method. 
        /// This call is only supported if the current object is a CIM class definition. 
        /// Method information is not available from IWbemClassObject pointers and 
        /// WbemClassObject objects which point to CIM instances.
        /// </summary>
        /// <param name="name">The method name. This cannot be NULL, and must point to a valid LPCWSTR.</param>
        /// <param name="flags">Reserved. This parameter must be 0.</param>
        /// <param name="inSignature">
        /// A pointer that receives an IWbemClassObject pointer which describes the in 
        /// parameters to the method. This parameter is ignored if set to NULL. Be aware 
        /// that Windows Management can set the IWbemClassObject pointer to NULL if this 
        /// method has no in parameters.
        /// </param>
        /// <param name="outSignature">
        /// A pointer that receives an IWbemClassObject pointer which describes the out-parameters 
        /// to the method. This parameter will be ignored if set to NULL.
        /// </param>
        /// <remarks>
        /// <p>
        /// For a method, the in and out parameters are described as properties in an IWbemClassObject, 
        /// an instance of the system class __Parameters.
        /// </p>
        /// <p>
        /// For example, consider the following method:
        /// </p>
        /// <code>
        /// Class MyClass{
        /// [key] string KeyVal;
        /// sint32 PropVal;
        /// sint32 ExampleMethod( [in] sint32 Parm1, [in] uint32 Parm2,
        ///     [out] string Parm3 );
        /// };
        /// </code>
        /// <p>
        /// In this example, the class has a single method. When the user calls GetMethod, the inSignature 
        /// parameter receives an IWbemClassObject object, which contains two properties: Parm1 and Parm2. 
        /// The outSignature parameter contains two properties, Parm3 and ReturnValue.
        /// </p>
        /// <p>
        /// After filling in the property values of the inSignature object, the caller can use the object 
        /// to execute the method by calling WbemServices::ExecMethod or WbemServices::ExecMethodAsync.
        /// </p>
        /// </remarks>
        void GetMethod( LPCWSTR name, long flags, IWbemClassObject** inSignature, IWbemClassObject** outSignature ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMethod( name, flags, inSignature, outSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetMethod( LPCWSTR name, IWbemClassObject** inSignature, IWbemClassObject** outSignature ) const
        {
            GetMethod( name, 0, inSignature, outSignature );
        }
        template<WideStringType T>
        void GetMethod( const T& name, long flags, IWbemClassObject** inSignature, IWbemClassObject** outSignature ) const
        {
            GetMethod( name.c_str( ), flags, inSignature, outSignature );
        }
        template<WideStringType T>
        void GetMethod( const T& name, IWbemClassObject** inSignature, IWbemClassObject** outSignature ) const
        {
            GetMethod( name.c_str( ), 0, inSignature, outSignature );
        }

        inline WbemMethodSignature GetMethod( LPCWSTR name ) const;
        template<WideStringType T>
        inline WbemMethodSignature GetMethod( const T& name ) const;

        /// <summary>
        /// <p>
        /// The PutMethod function is used to create a method. This call is 
        /// only supported if the current object is a CIM class definition. 
        /// Method manipulation is not available from WbemClassObject objects 
        /// that references CIM instances.
        /// </p>
        /// <p>
        /// The user cannot create methods with names that begin or end with 
        /// an underscore. This is reserved for system classes and properties.
        /// </p>
        /// </summary>
        /// <param name="name">The method name that is created.</param>
        /// <param name="flags">Reserved. This parameter must be 0 (zero).</param>
        /// <param name="inSignature">
        /// A pointer to a copy of the __Parameters system class that contains the 
        /// in parameters for the method. This parameter is ignored if set to NULL.
        /// </param>
        /// <param name="outSignature">
        /// A pointer to a copy of the __Parameters system class that contains the 
        /// out parameters for the object. This parameter is ignored if set to NULL.
        /// </param>
        void PutMethod( LPCWSTR name, long flags, IWbemClassObject* inSignature, IWbemClassObject* outSignature ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutMethod( name, flags, inSignature, outSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutMethod( LPCWSTR name, IWbemClassObject* inSignature, IWbemClassObject* outSignature ) const
        {
            PutMethod( name, 0, inSignature, outSignature );
        }
        template<WideStringType T>
        void PutMethod( const T& name, long flags, IWbemClassObject* inSignature, IWbemClassObject* outSignature ) const
        {
            PutMethod( name.c_str(), flags, inSignature, outSignature );
        }
        template<WideStringType T>
        void PutMethod( const T& name, IWbemClassObject* inSignature, IWbemClassObject* outSignature ) const
        {
            PutMethod( name.c_str( ), 0, inSignature, outSignature );
        }

        /// <summary>
        /// Use the DeleteMethod function to delete a method. This call is supported 
        /// only if the current object is a CIM class definition. Method manipulation 
        /// is not available from WbemClassObject objects referencing CIM instances.
        /// </summary>
        /// <param name="name">Method name to be removed from the class definition.</param>
        void DeleteMethod( LPCWSTR name ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteMethod( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<WideStringType T>
        void DeleteMethod( const T& name ) const
        {
            DeleteMethod( name.c_str() );
        }

        /// <summary>
        /// <p>
        /// Use the BeginMethodEnumeration function call to begin an 
        /// enumeration of the methods available for the object.
        /// </p>
        /// <p>
        /// This call is only supported if the current object is a CIM class 
        /// definition. Method manipulation is not available from WbemClassObject 
        /// objects referencing CIM instances. The order in which methods are 
        /// enumerated is guaranteed to be invariant for a given instance of WbemClassObject.
        /// </p>
        /// </summary>
        /// <param name="enumFlags">
        /// <p>
        /// Specifies the scope of the enumeration.
        /// </p>
        /// Possible values:
        /// <p>
        /// </p>
        /// <ul>
        ///     <li>
        ///         <h4>Wbem::ConditionFlags::LocalOnly (WBEM_FLAG_LOCAL_ONLY)</h4>
        ///         <p>
        ///         Include methods that are defined in the class itself.
        ///         </p>
        ///     </li>
        ///     <li>
        ///         <h4>Wbem::ConditionFlags::PropagatedOnly (WBEM_FLAG_PROPAGATED_ONLY)</h4>
        ///         <p>
        ///         Include methods that are inherited from parent classes.
        ///         </p>
        ///     </li>
        /// </ul>
        /// </param>
        void BeginMethodEnumeration( long enumFlags ) const
        {
            
            auto pInterface = GetInterface( );
            auto hr = pInterface->BeginMethodEnumeration( enumFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// <p>
        /// The NextMethod function is used to retrieve the next method in a 
        /// method enumeration sequence that starts with a call to BeginMethodEnumeration.
        /// </p>
        /// <p>
        /// This call is only supported if the current object is a CIM class definition. 
        /// Method manipulation is not available from WbemClassObject objects referencing 
        /// CIM instances.
        /// </p>
        /// </summary>
        /// <param name="flags">Reserved. This parameter must be 0 (zero).</param>
        /// <param name="name">
        /// A pointer that should point to NULL prior to the call. This parameter 
        /// receives the address of a BSTR value containing the method name. The 
        /// caller must release the string using SysFreeString when it is no longer 
        /// required.
        /// </param>
        /// <param name="inSignature">
        /// A pointer that receives a pointer to an IWbemClassObject containing the 
        /// in parameters for the method.
        /// </param>
        /// <param name="outSignature">
        /// A pointer that receives a pointer to an IWbemClassObject containing the 
        /// out parameters for the method.
        /// </param>
        /// <returns>false if all methods have been enumerated, true otherwise.</returns>
        /// <remarks>
        /// The caller begins the enumeration sequence using BeginMethodEnumeration, 
        /// and then calls NextMethod until it returns false. The caller, optionally, 
        /// finishes the sequence with EndMethodEnumeration. The caller may terminate 
        /// the enumeration early by calling EndMethodEnumeration at any time.
        /// </remarks>
        bool NextMethod( long flags, BSTR* name, IWbemClassObject** inSignature, IWbemClassObject** outSignature ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->NextMethod( flags, name, inSignature, outSignature );
            if ( hr != WBEM_S_NO_MORE_DATA )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != WBEM_S_NO_MORE_DATA;
        }

        bool NextMethod( BSTR* name, IWbemClassObject** inSignature, IWbemClassObject** outSignature ) const
        {
            return NextMethod( 0, name, inSignature, outSignature );
        }

        inline WbemMethod NextMethod( ) const;

        /// <summary>
        /// <p>
        /// The EndMethodEnumeration function is used to terminate a method 
        /// enumeration sequence started with BeginMethodEnumeration.
        /// </p>
        /// <p>
        /// This call is only supported if the current object is a CIM class 
        /// definition. Method manipulation is not available from WbemClassObject 
        /// objects referencing CIM instances.
        /// </p>
        /// </summary>
        void EndMethodEnumeration( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EndMethodEnumeration( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// <p>
        /// The GetMethodQualifierSet is used to retrieve the qualifier set for a particular method.
        /// </p>
        /// <p>
        /// This call is supported only if the current object is a CIM class definition. Method 
        /// manipulation is not available for WbemClassObject objects referencing CIM instances.
        /// </p>
        /// </summary>
        /// <param name="methodName"></param>
        /// <param name="qualifierSet"></param>
        void GetMethodQualifierSet( LPCWSTR methodName, IWbemQualifierSet** qualifierSet ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMethodQualifierSet( methodName, qualifierSet );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<WideStringType T>
        void GetMethodQualifierSet( const T& methodName, IWbemQualifierSet** qualifierSet ) const
        {
            GetMethodQualifierSet( methodName.c_str( ), qualifierSet );
        }

        inline WbemQualifierSet GetMethodQualifierSet( LPCWSTR methodName ) const;
        template<WideStringType T>
        void GetMethodQualifierSet( const T& methodName ) const;

        /// <summary>
        /// <p>
        /// The GetMethodOrigin function is used to determine the class for 
        /// which a method was declared.
        /// </p>
        /// <p>
        /// This call is only supported if the current object is a CIM class 
        /// definition. Method manipulation is not available for WbemClassObject 
        /// objects referencing CIM instances.
        /// </p>
        /// </summary>
        /// <param name="methodName">
        /// Name of the method for the object whose owning class is being requested.
        /// </param>
        /// <param name="className">
        /// Receives the name of the class which owns the method. The user must call 
        /// SysFreeString on the returned BSTR when it is no longer required.
        /// </param>
        void GetMethodOrigin( LPCWSTR methodName, BSTR* className ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetMethodOrigin( methodName, className );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<WideStringType T>
        void GetMethodOrigin( const T& methodName, BSTR* className ) const
        {
            GetMethodOrigin( methodName.c_str( ), className );
        }

        SysString GetMethodOrigin( LPCWSTR methodName ) const
        {
            BSTR ptr = nullptr;
            GetMethodOrigin( methodName, &ptr );
            return SysString( ptr, true );
        }
        template<WideStringType T>
        SysString GetMethodOrigin( const T& methodName ) const
        {
            return GetMethodOrigin( methodName.c_str() );
        }
    };


    class WbemMethodSignature
    {
        struct Data
        {
            WbemClassObject in_;
            WbemClassObject out_;
            Data( IWbemClassObject* in, IWbemClassObject* out )
                : in_(in), out_(out)
            { }
            Data( WbemClassObject&& in, WbemClassObject&& out )
                : in_( std::move( in ) ), out_( std::move( out ) )
            { }
            Data( const WbemClassObject& in, const WbemClassObject& out )
                : in_( in ), out_( out )
            { }
        };
        std::unique_ptr<Data> data_;
    public:
        constexpr WbemMethodSignature( ) noexcept = default;
        WbemMethodSignature( IWbemClassObject* in, IWbemClassObject* out )
            : data_( std::make_unique<Data>(in,out) )
        { }
        WbemMethodSignature( WbemClassObject&& in, WbemClassObject&& out )
            : data_( std::make_unique<Data>( std::move( in ), std::move( out ) ) )
        { }
        WbemMethodSignature( const WbemClassObject& in, const WbemClassObject& out )
            : data_( std::make_unique<Data>( in, out ) )
        { }

        WbemMethodSignature( const WbemMethodSignature& other ) = delete;
        WbemMethodSignature& operator = ( const WbemMethodSignature& other ) = delete;

        WbemMethodSignature( WbemMethodSignature&& other ) noexcept
            : data_( std::move( other.data_ ) )
        { }
        WbemMethodSignature& operator = ( WbemMethodSignature&& other )  noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        explicit operator bool( ) const
        {
            return data_ != nullptr;
        }
        bool IsValid( ) const
        {
            return data_ != nullptr;
        }
        void swap( WbemMethodSignature& other ) noexcept
        {
            std::swap( data_, other.data_ );
        }

        const WbemClassObject& In( ) const
        {
            return data_->in_;
        }
        const WbemClassObject& Out( ) const
        {
            return data_->out_;
        }
    };

    inline WbemMethodSignature WbemClassObject::GetMethod( LPCWSTR name ) const
    {
        IWbemClassObject* inSignature = nullptr; 
        IWbemClassObject* outSignature = nullptr;
        GetMethod( name, 0, &inSignature, &outSignature );
        return WbemMethodSignature( inSignature, outSignature );
    }
    template<WideStringType T>
    inline WbemMethodSignature WbemClassObject::GetMethod( const T& name ) const
    {
        return GetMethod( name.c_str() );
    }

    class WbemMethod
    {
        struct Data
        { 
            SysString name_;
            WbemMethodSignature signature_;

            Data( const SysString& name, WbemMethodSignature&& signature )
                : name_(name), signature_( std::move( signature ) )
            { }
            Data( BSTR name, IWbemClassObject* in, IWbemClassObject* out )
                : name_( name, true ), signature_( in, out )
            { }

        };
        std::unique_ptr<Data> data_;
    public:
        constexpr WbemMethod( ) noexcept = default;
        WbemMethod( BSTR name, IWbemClassObject * in, IWbemClassObject * out )
            : data_( std::make_unique<Data>( name, in, out ) )
        {
        }

        WbemMethod( const WbemMethod& other ) = delete;
        WbemMethod& operator = ( const WbemMethod& other ) = delete;

        WbemMethod( WbemMethod&& other ) noexcept
            : data_( std::move( other.data_ ) )
        {
        }
        WbemMethod& operator = ( WbemMethod&& other )  noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        explicit operator bool( ) const
        {
            return data_ != nullptr;
        }
        bool IsValid( ) const
        {
            return data_ != nullptr;
        }
        void swap( WbemMethod& other ) noexcept
        {
            std::swap( data_, other.data_ );
        }

        const SysString& Name( ) const
        {
            return data_->name_;
        }
        const WbemMethodSignature& Signature( ) const
        {
            return data_->signature_;
        }

    };

    inline WbemMethod WbemClassObject::NextMethod( ) const
    {
        BSTR name = nullptr;
        IWbemClassObject* inSignature = nullptr;
        IWbemClassObject* outSignature = nullptr;
        if ( NextMethod( &name, &inSignature, &outSignature ) )
        {
            return WbemMethod( name, inSignature, outSignature );
        }
        else
        {
            return WbemMethod( );
        }
    }




    class WbemObjectAccess : public WbemClassObject
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemObjectAccess, WbemClassObject )

        void GetPropertyHandle( LPCWSTR propertyName, CIMTYPE* type, long* handle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyHandle( propertyName, type, handle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WritePropertyValue( long handle, long bufferSize, const byte* buffer ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WritePropertyValue( handle, bufferSize, buffer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReadPropertyValue( long handle, long bufferSize, long* numberOfBytesRetrieved, byte* buffer ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReadPropertyValue( handle, bufferSize, numberOfBytesRetrieved, buffer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReadDWORD( long handle, DWORD* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReadDWORD( handle, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteDWORD( long handle, DWORD value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteDWORD( handle, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReadQWORD( long handle, unsigned __int64* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ReadQWORD( handle, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteQWORD( long handle, unsigned __int64 value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteQWORD( handle, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPropertyInfoByHandle( long handle, BSTR* propertyName, CIMTYPE* propertyType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyInfoByHandle( handle, propertyName, propertyType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Lock( long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Lock( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Unlock( long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Unlock( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemQualifierSet : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemQualifierSet, Unknown )

        void Get( LPCWSTR qualifierName, long flags, VARIANT* value, long* flavor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Get( qualifierName, flags, value, flavor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Put( LPCWSTR qualifierName, VARIANT* value, long flavor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Put( qualifierName, value, flavor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Delete( LPCWSTR qualifierName ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Delete( qualifierName );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetNames( long flags, SAFEARRAY** names ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNames( flags, names );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BeginEnumeration( long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BeginEnumeration( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Next( long flags, BSTR* qualifierName, VARIANT* value, long* flavor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Next( flags, qualifierName, value, flavor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EndEnumeration( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EndEnumeration( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// The WbemServices is used by clients and providers to access WMI services. 
    /// The interface is implemented by WMI and WMI providers, and is the primary 
    /// WMI interface.
    /// </summary>
    class WbemServices : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemServices, Unknown )

        void OpenNamespace( __RPC__in const BSTR namespaceName, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_opt_inout_opt IWbemServices** workingNamespace, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OpenNamespace( namespaceName, flags, context, workingNamespace, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        WbemServices OpenNamespace( __RPC__in const BSTR namespaceName, long flags = 0, __RPC__in_opt IWbemContext* context = nullptr ) const
        {
            IWbemServices* ptr = nullptr;
            OpenNamespace( namespaceName, flags, context, &ptr, nullptr );
            return WbemServices( ptr );
        }

        WbemServices OpenNamespace( LPCWSTR namespaceName, long flags = 0, __RPC__in_opt IWbemContext* context = nullptr ) const
        {
            return OpenNamespace( ( const BSTR ) namespaceName, flags, context );
        }

        WbemServices OpenNamespace( const WideString& namespaceName, long flags = 0, __RPC__in_opt IWbemContext* context = nullptr ) const
        {
            return OpenNamespace( (const BSTR)namespaceName.c_str(), flags, context );
        }



        void CancelAsyncCall( __RPC__in_opt IWbemObjectSink* sink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CancelAsyncCall( sink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void QueryObjectSink( long flags, __RPC__deref_out_opt IWbemObjectSink** responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryObjectSink( flags, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetObject( __RPC__in const BSTR objectPath, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_opt_inout_opt IWbemClassObject** object, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObject( objectPath, flags, context, object, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetObjectAsync( __RPC__in const BSTR objectPath, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObjectAsync( objectPath, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutClass( __RPC__in_opt IWbemClassObject* object, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutClass( object, flags, context, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutClassAsync( __RPC__in_opt IWbemClassObject* object, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutClassAsync( object, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteClass( __RPC__in const BSTR className, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteClass( className, flags, context, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteClassAsync( __RPC__in const BSTR className, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteClassAsync( className, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateClassEnum( __RPC__in const BSTR superClassName, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_out_opt IEnumWbemClassObject** enumObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateClassEnum( superClassName, flags, context, enumObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline EnumWbemClassObject CreateClassEnum( __RPC__in const BSTR superClassName = nullptr, long flags = WBEM_FLAG_DEEP | WBEM_FLAG_FORWARD_ONLY, __RPC__in_opt IWbemContext* context = nullptr ) const;


        void CreateClassEnumAsync( __RPC__in const BSTR superClassName, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateClassEnumAsync( superClassName, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutInstance( __RPC__in_opt IWbemClassObject* instance, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutInstance( instance, flags, context, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutInstanceAsync( __RPC__in_opt IWbemClassObject* instance, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutInstanceAsync( instance, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteInstance( __RPC__in const BSTR objectPath, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteInstance( objectPath, flags, context, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteInstanceAsync( __RPC__in const BSTR objectPath, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteInstanceAsync( objectPath, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateInstanceEnum( __RPC__in const BSTR filter, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_out_opt IEnumWbemClassObject** enumObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateInstanceEnum( filter, flags, context, enumObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline EnumWbemClassObject CreateInstanceEnum( const BSTR filter, long flags, __RPC__in_opt IWbemContext* context = nullptr ) const;


        void CreateInstanceEnumAsync( __RPC__in const BSTR filter, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateInstanceEnumAsync( filter, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// The ExecQuery method executes a query to retrieve objects.
        /// </summary>
        /// <param name="queryLanguage">
        /// Valid BSTR that contains one of the query languages supported by Windows Management. 
        /// This must be "WQL", the acronym for WMI Query Language.
        /// </param>
        /// <param name="query">
        /// Valid BSTR that contains the text of the query. This parameter cannot be NULL.
        /// </param>
        /// <param name="flags">
        /// The following flags affect the behavior of this method. The suggested value 
        /// for this parameter is WBEM_FLAG_RETURN_IMMEDIATELY and WBEM_FLAG_FORWARD_ONLY 
        /// for best performance.
        /// </param>
        /// <param name="context">
        /// Typically NULL. Otherwise, this is a pointer to an IWbemContext object that 
        /// can be used by the provider that is providing the requested classes or instances. 
        /// The values in the context object must be specified in the documentation for the 
        /// provider in question.
        /// </param>
        /// <param name="enumObject">
        /// If no error occurs, this receives the enumerator that allows the caller to 
        /// retrieve the instances in the result set of the query. It is not an error 
        /// for the query to have a result set with 0 instances. This is determined only 
        /// by attempting to iterate through the instances. This object returns with a 
        /// positive reference count. The caller must call Release when the object is no 
        /// longer required.
        /// </param>
        void ExecQuery( __RPC__in const BSTR queryLanguage, __RPC__in const BSTR query, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_out_opt IEnumWbemClassObject** enumObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ExecQuery( queryLanguage, query, flags, context, enumObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline EnumWbemClassObject ExecQuery( __RPC__in const BSTR queryLanguage, __RPC__in const BSTR query, long flags = WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, __RPC__in_opt IWbemContext* context = nullptr ) const;
        inline EnumWbemClassObject ExecQuery( __RPC__in const BSTR query, long flags = WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, __RPC__in_opt IWbemContext* context = nullptr ) const;

        inline EnumWbemClassObject ExecQuery( __RPC__in LPCWSTR query, long flags = WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, __RPC__in_opt IWbemContext* context = nullptr ) const;



        /// <summary>
        /// The ExecQueryAsync function executes a query to retrieve objects asynchronously.
        /// </summary>
        /// <param name="queryLanguage">
        /// Valid BSTR that contains one of the query languages that Windows Management 
        /// Instrumentation (WMI) supports. This must be L"WQL".
        /// </param>
        /// <param name="query">
        /// Valid BSTR that contains the text of the query. This cannot be NULL. When you 
        /// implement an instance provider, your provider can refuse the query because it 
        /// is too complex. When a provider determines that a query is too complex, WMI can 
        /// retry the provider with a simple query, or choose to retrieve and enumerate the 
        /// superset of the query instances.
        /// </param>
        /// <param name="flags">
        /// This parameter can be one of the following values:
        /// <ul>
        ///     <li>
        ///     <p>
        ///     <b>Wbem::GenericFlagType::UseAmendedQualifiers (WBEM_FLAG_USE_AMENDED_QUALIFIERS)</b>
        ///     </p>
        ///     <p>
        ///     If this flag is set, WMI retrieves the amended qualifiers stored in the localized namespace of the current connection's locale. If not set, only the qualifiers stored in the immediate namespace are retrieved.
        ///     </p>
        ///     </li>
        ///     <li>
        ///     <p>
        ///     <b>Wbem::GenericFlagType::Bidirectional (WBEM_FLAG_BIDIRECTIONAL)</b>
        ///     </p>
        ///     <p>
        ///     This flag causes WMI to retain pointers to objects of the enumeration until the client releases the enumerator.
        ///     </p>
        ///     </li>
        /// 
        ///     <li>
        ///     <p>
        ///     <b>Wbem::GenericFlagType::SendStatus (WBEM_FLAG_SEND_STATUS)</b>
        ///     </p>
        ///     <p>
        ///     This flag registers a request with WMI to receive intermediate status reports through the client's implementation of IWbemObjectSink::SetStatus. Provider implementation must support intermediate status reporting for this flag to change.
        ///     </p>
        ///     </li>
        /// 
        ///     <li>
        ///     <p>
        ///     <b>Wbem::GenericFlagType::EnsureLocatable (WBEM_FLAG_ENSURE_LOCATABLE)</b>
        ///     </p>
        ///     <p>
        ///     This flag ensures that returned objects have enough information in them so that the system properties, such as __PATH, __RELPATH, and __SERVER, are non - NULL.
        ///     </p>
        ///     </li>
        /// 
        ///     <li>
        ///     <p>
        ///     <b>Wbem::GenericFlagType::Prototype (WBEM_FLAG_PROTOTYPE)</b>
        ///     </p>
        ///     <p>
        ///     This flag is used for prototyping.It does not execute the query, but returns an object that looks like a typical result object.
        ///     </p>
        ///     </li>
        /// 
        ///     <li>
        ///     <p>
        ///     <b>Wbem::GenericFlagType::DirectRead (WBEM_FLAG_DIRECT_READ)</b>
        ///     </p>
        ///     <p>
        ///     This flag causes direct access to the provider for the class specified without regard to its parent class or subclasses.
        ///     </p>
        ///     </li>
        /// </ul>
        /// </param>
        /// <param name="context">
        /// Typically NULL. Otherwise, this is a pointer to an IWbemContext object that 
        /// can be used by the provider that is providing the requested classes or instances. 
        /// The values in the context object must be specified in the documentation for the 
        /// provider in question.
        /// </param>
        /// <param name="responseHandler">
        /// <p>
        /// Pointer to the caller's implementation of IWbemObjectSink. This handler receives 
        /// the objects in the query result set as they become available. If any error code is 
        /// returned, then the supplied IWbemObjectSink pointer is not used. If WBEM_S_NO_ERROR 
        /// is returned, then the user's IWbemObjectSink implementation is called to indicate the 
        /// result of the operation. Windows Management Instrumentation (WMI) calls 
        /// IWbemObjectSink::Indicate with the objects any number of times, followed by a 
        /// single call to IWbemObjectSink::SetStatus to indicate the final status.
        /// </p>
        /// <p>
        /// WMI only calls AddRef to the pointer when WBEM_S_NO_ERROR returns. When an error 
        /// code returns, the reference count is the same as on entry.
        /// </p>
        /// </param>
        void ExecQueryAsync( __RPC__in const BSTR queryLanguage, __RPC__in const BSTR query, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ExecQueryAsync( queryLanguage, query, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ExecQueryAsync( __RPC__in LPCWSTR queryLanguage, __RPC__in LPCWSTR query, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            ExecQueryAsync( (const BSTR)queryLanguage, (const BSTR)query, flags, context, responseHandler );
        }

        void ExecQueryAsync( __RPC__in LPCWSTR query, IWbemObjectSink* responseHandler, long flags = 0 ) const
        {
            ExecQueryAsync( (const BSTR)L"WQL", (const BSTR)query, flags, nullptr, responseHandler );
        }



        void ExecNotificationQuery( __RPC__in const BSTR queryLanguage, __RPC__in const BSTR query, long flags, __RPC__in_opt IWbemContext* context, __RPC__deref_out_opt IEnumWbemClassObject** enumObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ExecNotificationQuery( queryLanguage, query, flags, context, enumObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ExecNotificationQueryAsync( __RPC__in const BSTR queryLanguage, __RPC__in const BSTR query, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ExecNotificationQueryAsync( queryLanguage, query, flags, context, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ExecMethod( __RPC__in const BSTR objectPath, __RPC__in const BSTR methodName, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemClassObject* inParams, __RPC__deref_opt_inout_opt IWbemClassObject** outParams, __RPC__deref_opt_inout_opt IWbemCallResult** callResult ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ExecMethod( objectPath, methodName, flags, context, inParams, outParams, callResult );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ExecMethodAsync( __RPC__in const BSTR objectPath, __RPC__in const BSTR methodName, long flags, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemClassObject* inParams, __RPC__in_opt IWbemObjectSink* responseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ExecMethodAsync( objectPath, methodName, flags, context, inParams, responseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// <p>
    /// Use the WbemLocator to obtain the initial namespace pointer to 
    /// the IWbemServices interface for WMI on a specific host computer. 
    /// You can access Windows Management itself using the IWbemServices 
    /// pointer, which is returned by the IWbemLocator::ConnectServer method.
    /// </p>
    /// <p>
    /// A client or provider that requires Windows Management services first 
    /// obtains a pointer to the locator using CoCreateInstance or CoCreateInstanceEx, 
    /// as specified in the COM documentation in the Microsoft Windows Software 
    /// Development Kit (SDK). The WbemLocator object is always an in-process 
    /// COM server. The interface pointer to the desired namespace on the 
    /// desired target computer is then obtained through the ConnectServer function, 
    /// which is the only method on this interface.
    /// </p>
    /// </summary>
    class WbemLocator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemLocator, Unknown )

        static WbemLocator Create()
        { 
            return CoCreateInstanceFromClassId<WbemLocator>( CLSID_WbemLocator );
        }


        void ConnectServer( const BSTR networkResource, const BSTR userName, const BSTR password, const BSTR locale, long securityFlags, const BSTR authority, IWbemContext* context, IWbemServices** namespaceObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ConnectServer( networkResource, userName, password, locale, securityFlags, authority, context, namespaceObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ConnectServer( LPCWSTR networkResource, LPCWSTR userName, LPCWSTR password, LPCWSTR locale, long securityFlags, LPCWSTR authority, IWbemContext* context, IWbemServices** namespaceObject ) const
        {
            ConnectServer( (const BSTR)networkResource, (const BSTR)userName, (const BSTR)password, (const BSTR)locale, securityFlags, (const BSTR)authority, context, namespaceObject );
        }


        WbemServices ConnectServer( const BSTR networkResource, const BSTR userName = nullptr, const BSTR password = nullptr, const BSTR locale = nullptr, long securityFlags = 0, const BSTR authority = nullptr, IWbemContext* context = nullptr) const
        {
            IWbemServices* ptr = nullptr;
            ConnectServer( networkResource, userName, password, locale, securityFlags, authority, context, &ptr );
            return WbemServices( ptr );
        }

        WbemServices ConnectServer( LPCWSTR networkResource, LPCWSTR userName = nullptr, LPCWSTR password = nullptr, LPCWSTR locale = nullptr, long securityFlags = 0, LPCWSTR authority = nullptr, IWbemContext* context = nullptr ) const
        {
            return ConnectServer( (const BSTR)networkResource, (const BSTR)userName, (const BSTR)password, (const BSTR)locale, securityFlags, (const BSTR)authority, context );
        }

    };

    /// <summary>
    /// The IWbemObjectSink interface creates a sink interface that can receive all 
    /// types of notifications within the WMI programming model. Clients must implement 
    /// this interface to receive both the results of the asynchronous methods of 
    /// WbemServices, and specific types of event notifications. Providers use, but 
    /// do not implement this interface to provide events and objects to WMI.
    /// </summary>
    class WbemObjectSink : public Unknown
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL2( WbemObjectSink, Unknown )

        void Indicate( long objectCount, __RPC__in_ecount_full( objectCount ) IWbemClassObject** objectArray ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Indicate( objectCount, objectArray );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStatus( long flags, HRESULT hResult, __RPC__in_opt BSTR param, __RPC__in_opt IWbemClassObject* objectParam ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetStatus( flags, hResult, param, objectParam );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    template<typename DerivedT, typename InterfaceT = IWbemObjectSink, typename ContainerT = boost::container::small_vector<WbemClassObject, 64> >
    class IWbemObjectSinkImplementationBase : public Com::ObjectBase<DerivedT, InterfaceT>
    {
    public:
        using Base = Com::ObjectBase<DerivedT, InterfaceT>;
        using DerivedType = DerivedT;
        using InterfaceType = InterfaceT;
        using ContainerType = ContainerT;
    private:
        virtual HRESULT STDAPICALLTYPE Indicate( long objectCount, __RPC__in_ecount_full( objectCount ) IWbemClassObject** objectArray ) override
        {
            bool failed = true;
            try
            {
                ContainerType objects;
                for ( long i = 0; i < objectCount; i++ )
                {
                    auto ptr = objectArray[i];
                    objects.emplace_back( WbemClassObject( ptr, true ) );
                }
                auto* self = static_cast<DerivedType*>( this );
                self->HandleIndicate( objects );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            return failed == false ? S_OK : E_FAIL;
        }
        virtual HRESULT STDAPICALLTYPE SetStatus( long flags, HRESULT hResult, __RPC__in_opt BSTR param, __RPC__in_opt IWbemClassObject* objectParam ) override
        {
            bool failed = true;
            WbemClassObject object( objectParam );
            SysString str( param, true );
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetStatus( flags, hResult, str, object );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            object.Detach( );
            (void)str.Detach( );
            return failed == false ? S_OK : E_FAIL;
        }
    protected:
        void HandleIndicate( const ContainerType& objects )
        {

        }

        void HandleSetStatus( long flags, HRESULT hResult, const SysString& paramName, const WbemClassObject& paramObject )
        {

        }
    };

    template<typename DerivedT, typename InterfaceT = IWbemObjectSink, typename ContainerT = boost::container::small_vector<WbemClassObject, 64> >
    class IWbemObjectSinkDispatcherBase : public IWbemObjectSinkImplementationBase<DerivedT,InterfaceT, ContainerT>
    {
        template<typename DerivedT, typename InterfaceT, typename ContainerT>
        friend class IWbemObjectSinkImplementationBase;
    public:
        using Base = IWbemObjectSinkImplementationBase<DerivedT, InterfaceT, ContainerT>;

        using InterfaceType = Base::InterfaceType;
        using ContainerType = Base::ContainerType;

        boost::signals2::signal<void( const ContainerType& objects )> OnIndicate;
        boost::signals2::signal<void( long flags, HRESULT hResult, const SysString& paramName, const WbemClassObject& paramObject )> OnSetStatus;
    protected:
        void HandleIndicate( const ContainerType& objects )
        {
            OnIndicate( objects );
        }

        void HandleSetStatus( long flags, HRESULT hResult, const SysString& paramName, const WbemClassObject& paramObject )
        {
            OnSetStatus( flags, hResult, paramName, paramObject );
        }
    };

    //template<typename ContainerT = boost::container::small_vector<WbemClassObject, 64> >
    class IWbemObjectSinkDispatcher : public IWbemObjectSinkDispatcherBase< IWbemObjectSinkDispatcher, IWbemObjectSink, boost::container::small_vector<WbemClassObject, 64> >
    {
    public:
        using Base = IWbemObjectSinkDispatcherBase< IWbemObjectSinkDispatcher, IWbemObjectSink, boost::container::small_vector<WbemClassObject, 64> >;
    };





    /// <summary>
    /// <p>
    /// The EnumWbemClassObject interface is used to enumerate Common Information Model 
    /// (CIM) objects and is similar to a standard COM enumerator.
    /// </p>
    /// <p>
    /// An object of type EnumWbemClassObject is received from calls to the following WbemServices functions:
    /// </p>
    /// <ul>
    ///     <li>ExecQuery</li>
    ///     <li>CreateInstanceEnum</li>
    ///     <li>CreateClassEnum</li>
    ///     <li>ExecNotificationQuery</li>
    /// </ul>
    /// <p>
    /// CIM objects are retrieved from an enumeration as objects of type WbemClassObject by calling the 
    /// Next function. You can reset an enumeration back to the beginning by calling the Reset function.
    /// </p>
    /// </summary>
    class EnumWbemClassObject : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( EnumWbemClassObject, Unknown )

        void Reset( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool Next( long timeout, ULONG count, __RPC__out_ecount_part( count, *returnedCount ) IWbemClassObject** objects, __RPC__out ULONG* returnedCount ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Next( timeout, count, objects, returnedCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr != WBEM_S_FALSE;
        }

        WbemClassObject Next( long timeout = WBEM_INFINITE ) const
        {
            IWbemClassObject* ptr = nullptr;
            ULONG count = 0;
            if ( Next( timeout, 1, &ptr, &count ) )
            {
                if ( count )
                {
                    return WbemClassObject( ptr );
                }
            }
            return WbemClassObject( );
        }



        void NextAsync( ULONG count, __RPC__in_opt IWbemObjectSink* sink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->NextAsync( count, sink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Clone( __RPC__deref_out_opt IEnumWbemClassObject** enumObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clone( enumObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Skip( long timeout, ULONG count ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Skip( timeout, count );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    inline EnumWbemClassObject WbemServices::CreateClassEnum( __RPC__in const BSTR superClassName, long flags, __RPC__in_opt IWbemContext* context ) const
    {
        IEnumWbemClassObject* ptr;
        CreateClassEnum( superClassName, flags, context, &ptr );
        return EnumWbemClassObject( ptr );
    }


    inline EnumWbemClassObject WbemServices::CreateInstanceEnum( const BSTR filter, long flags, __RPC__in_opt IWbemContext* context ) const
    {
        IEnumWbemClassObject* ptr;
        CreateInstanceEnum( filter, flags, context, &ptr );
        return EnumWbemClassObject( ptr );
    }

    inline EnumWbemClassObject WbemServices::ExecQuery( __RPC__in const BSTR queryLanguage, __RPC__in const BSTR query, long flags, __RPC__in_opt IWbemContext* context ) const
    {
        IEnumWbemClassObject* ptr = nullptr;
        ExecQuery( queryLanguage, query, flags, context, &ptr );
        return EnumWbemClassObject( ptr );
    }

    inline EnumWbemClassObject WbemServices::ExecQuery( __RPC__in const BSTR query, long flags, __RPC__in_opt IWbemContext* context ) const
    {
        return ExecQuery( (const BSTR)L"WQL", query, flags, context );
    }

    inline EnumWbemClassObject WbemServices::ExecQuery( __RPC__in LPCWSTR query, long flags, __RPC__in_opt IWbemContext* context ) const
    {
        return ExecQuery( (const BSTR)query, flags, context );
    }



    /// <summary>
    /// <p>
    /// The WbemCallResult objects are used for semisynchronous calls of 
    /// WbemServices functions. When making such calls, the called WbemServices functions returns 
    /// immediately, along with a WbemCallResult (IWbemCallResult) object. Periodically, you can 
    /// poll the returned WbemCallResult object to determine the status of the call. You can obtain 
    /// the result of the original WbemServices call after it is complete by calling 
    /// WbemCallResult::GetCallStatus.
    /// </p>
    /// <p>
    /// This call-return paradigm is useful in cases where a thread cannot afford to be blocked for 
    /// more than a few seconds because it is servicing other tasks, such as processing window messages.
    /// </p>
    /// <p>
    /// Not all WbemServices methods support this interface because it is not required for all of them. 
    /// The intent is to allow nonblocking, synchronous operation (semisynchronous operation) for all 
    /// relevant operations. Because many of the WbemServices methods are already nonblocking due to the 
    /// use of enumerators or other constructs, only the following methods need this helper interface to 
    /// support semisynchronous operation:
    /// </p>
    /// <ul>
    ///     <li>OpenNamespace</li>
    ///     <li>GetObject</li>
    ///     <li>PutInstance</li>
    ///     <li>PutClass</li>
    ///     <li>DeleteClass</li>
    ///     <li>DeleteInstance</li>
    ///     <li>ExecMethod</li>
    /// </ul>
    /// </summary>
    class WbemCallResult : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemCallResult, Unknown )

        void GetResultObject( long timeout, __RPC__deref_out_opt IWbemClassObject** resultObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetResultObject( timeout, resultObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetResultString( long timeout, __RPC__deref_out_opt BSTR* resultString ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetResultString( timeout, resultString );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetResultServices( long timeout, __RPC__deref_out_opt IWbemServices** services ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetResultServices( timeout, services );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCallStatus( long timeout, __RPC__out long* status ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCallStatus( timeout, status );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// <p>
    /// The WbemContext objects are used to communicate additional context information 
    /// to providers when submitting WbemServices calls to WMI. All primary calls in 
    /// WbemServices take an optional parameter pointing to an object of this type.
    /// </p>
    /// </summary>
    /// <remarks>
    /// <p>
    /// Often, dynamic providers require more information than is specified in the normal 
    /// parameters of an WbemServices method. For example, to manipulate any WMI schema 
    /// objects that it provides, a provider may need to know a Simple Network Management 
    /// Protocol (SNMP) community name, or a Structured Query Language (SQL) database and 
    /// table name. A client can add this information to an WbemContext object and send the 
    /// WbemContext object along with the call as one of the parameters.
    /// </p>
    /// <p>
    /// Providers should use content objects sparingly. It is recommended that it is never 
    /// required. If a provider requires a large amount of highly specific context information 
    /// to respond to a request, then all clients must be coded to provide this information, 
    /// thus breaking the uniform access model that is the basis of WMI. Nevertheless, 
    /// in some cases it cannot be avoided. Therefore, this mechanism is provided to make 
    /// it possible to access such providers. Developers of such providers should provide 
    /// adequate documentation so that developers of client software can successfully manipulate 
    /// such CIM objects.
    /// </p>
    /// <p>
    /// Providers that support the use of WbemContext to allow clients to specify more information 
    /// in a request should restrict the types of values they support to the types in the following list:
    /// </p>
    /// <ul>
    ///     <li>
    ///         <b>VT_I4</b>
    ///     </li>
    ///     <li>
    ///         <b>VT_R8</b>
    ///     </li>
    ///     <li>
    ///         <b>VT_BOOL</b>
    ///     </li>
    ///     <li>
    ///         <b>VT_BSTR</b>
    ///     </li>
    ///     <li>
    ///         <b>VT_UNKNOWN</b>
    ///     </li>
    ///     <li>
    ///         Any of the above combined with <b>VT_ARRAY</b>
    ///     </li>
    /// </ul>
    /// <p>
    /// <b>Note:</b> Only objects that support IWbemClassObject can marshal their IUnknown methods 
    /// in an WbemContext instance using a variant of type VT_UNKNOWN.
    /// </p>
    /// <p>
    /// A WbemContext object, which is created using CoCreateInstanceEx, is a simple container of 
    /// named values. Access these methods to fill in context information required by a dynamic 
    /// provider. After the call to one of the WbemServices methods, the WbemContext object can 
    /// be reused for another call, or it can be deallocated using Release and another object created 
    /// for other calls to WbemServices methods.
    /// </p>
    /// <p>
    /// The information contained in an WbemContext object is entirely determined by the underlying 
    /// provider. WMI does not use the information, but forwards it to the provider. Providers must 
    /// publish the context information they require for these service requests.
    /// </p>
    /// <p>
    /// The client application calls CoCreateInstanceEx to create a single context object. Then, it 
    /// calls SetValue one or more times to set up context values for the provider. Finally, it submits 
    /// the object to one of the WbemServices methods, which immediately calls Release on the context 
    /// object after the call has returned. The other methods are for use primarily by providers that 
    /// receive the context object and have to extract information.
    /// </p>
    /// </remarks>
    class WbemContext : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemContext, Unknown )

        void Clone( IWbemContext** newCopy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clone( newCopy );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetNames( long flags, SAFEARRAY** names ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetNames( flags, names );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BeginEnumeration( long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->BeginEnumeration( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Next( long flags, BSTR* valueName, VARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Next( flags, valueName, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EndEnumeration( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EndEnumeration( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetValue( LPCWSTR valueName, long flags, VARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetValue( valueName, flags, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetValue( LPCWSTR valueName, long flags, VARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetValue( valueName, flags, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteValue( LPCWSTR valueName, long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteValue( valueName, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DeleteAll( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->DeleteAll( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class UnsecuredApartment : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( UnsecuredApartment, Unknown )

        void CreateObjectStub( __RPC__in_opt IUnknown* object, __RPC__deref_out_opt IUnknown** stub ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateObjectStub( object, stub );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemUnsecuredApartment : public UnsecuredApartment
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemUnsecuredApartment, UnsecuredApartment )

        void CreateSinkStub( __RPC__in_opt IWbemObjectSink* sink, DWORD flags, __RPC__in_opt LPCWSTR reserved, __RPC__deref_out_opt IWbemObjectSink** stub ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateSinkStub( sink, flags, reserved, stub );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemStatusCodeText : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemStatusCodeText, Unknown )

        void GetErrorCodeText( HRESULT hRes, LCID localeId, long flags, BSTR* messageText ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetErrorCodeText( hRes, localeId, flags, messageText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFacilityCodeText( HRESULT hRes, LCID localeId, long flags, BSTR* messageText ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFacilityCodeText( hRes, localeId, flags, messageText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemBackupRestore : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemBackupRestore, Unknown )

        void Backup( __RPC__in_string LPCWSTR backupToFilename, long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Backup( backupToFilename, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Restore( __RPC__in_string LPCWSTR restoreFromFilename, long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Restore( restoreFromFilename, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemBackupRestoreEx : public WbemBackupRestore
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemBackupRestoreEx, WbemBackupRestore )

        void Pause( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Pause( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Resume( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Resume( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemRefresher : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemRefresher, Unknown )

        void Refresh( long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Refresh( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// <p>
    /// The WbemHiPerfEnum objects are used in refresher operations to provide 
    /// rapid access to enumerations of instance objects. WMI provides an implementation 
    /// of this interface, which it passes to providers when IWbemHiPerfProvider::CreateRefreshableEnum 
    /// is called, and it returns to clients when IWbemConfigureRefresher::AddEnum is called.
    /// </p>
    /// <p>
    /// Client applications can call only the GetObjects method of this interface. Attempts by 
    /// client applications to call the other WbemHiPerfEnum methods throws a COMException with hResult 
    /// set to WBEM_E_ACCESS_DENIED. Providers call these other methods to update the enumerators whenever 
    /// a client calls Refresh.
    /// </p>
    /// <p>
    /// This interface is not implemented by the user or by a provider under any circumstances. 
    /// The implementation provided by WMI is the only one supported.
    /// </p>
    /// </summary>
    class WbemHiPerfEnum : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemHiPerfEnum, Unknown )

        /// <summary>
        /// The AddObjects method adds the supplied instance objects to the enumerator.
        /// </summary>
        void AddObjects( long flags, ULONG objectsSize, long* ids, IWbemObjectAccess* objects[] ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddObjects( flags, objectsSize, ids, objects );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveObjects( long flags, ULONG idsSize, long* ids ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveObjects( flags, idsSize, ids );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetObjects( long flags, ULONG objectsSize, IWbemObjectAccess* objects[], ULONG* objectsReturned ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObjects( flags, objectsSize, objects, objectsReturned );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveAll( long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveAll( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// <p>
    /// The WbemConfigureRefresher is used by client code to add enumerators, 
    /// objects, and nested refreshers into a refresher.
    /// </p>
    /// <p>
    /// Users and providers should never implement this interface. The implementation 
    /// provided by WMI is the only one that is supported.
    /// </p>
    /// <p>
    /// By providing a native implementation of this interface, WMI allows client code 
    /// to easily configure refreshers. You can access the IWbemConfigureRefresher 
    /// interface by calling QueryInterface on IID_IWbemConfigureRefresher on the object 
    /// returned by calling CoCreateInstance on CLSID_WbemRefresher.
    /// </p>
    /// </summary>
    class WbemConfigureRefresher : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemConfigureRefresher, Unknown )


        static WbemConfigureRefresher Create( )
        {
            return CoCreateInstanceFromClassId<WbemConfigureRefresher>( CLSID_WbemRefresher );
        }

        /// <summary>
        /// The AddObjectByPath function adds an object to a refresher by 
        /// specifying an object path.
        /// </summary>
        /// <param name="namespaceObject">
        /// An IWbemServices pointer back into Windows Management, which can service any 
        /// request made by the provider. The provider should call AddRef on this pointer 
        /// if it is going to call back into Windows Management during its execution.
        /// </param>
        /// <param name="objectPath">
        /// Constant, null-terminated string of 16-bit Unicode characters that contains 
        /// the object path of the object you add to the refresher.
        /// </param>
        /// <param name="flags">
        /// Bit-mask of flags that modify the behavior of this method. If this parameter is 
        /// set to Wbem::GenericFlagType::UseAmendedQualifiers (WBEM_FLAG_USE_AMENDED_QUALIFIERS), 
        /// the returned instance contain localized qualifiers if available.
        /// </param>
        /// <param name="context">
        /// Typically NULL; otherwise, a pointer to an IWbemContext object that is required by 
        /// one or more dynamic class providers. The values in the context object must be 
        /// specified in the specific provider documentation.
        /// </param>
        /// <param name="refreshableObject">
        /// Pointer to hold the reference to a IWbemClassObject object, which contains the 
        /// refreshable instance object. The client must call Release on the returned object 
        /// when it is no longer required.
        /// </param>
        /// <param name="id">
        /// Pointer to an integer returned by the provider that uniquely identifies the 
        /// refreshable object.
        /// </param>
        void AddObjectByPath( IWbemServices* namespaceObject, LPCWSTR objectPath, long flags, IWbemContext* context, IWbemClassObject** refreshableObject, long* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddObjectByPath( namespaceObject, objectPath, flags, context, refreshableObject, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddObjectByTemplate( IWbemServices* namespaceObject, IWbemClassObject* templateObject, long flags, IWbemContext* context, IWbemClassObject** refreshableObject, long* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddObjectByTemplate( namespaceObject, templateObject, flags, context, refreshableObject, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddRefresher( IWbemRefresher* refresher, long flags, long* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddRefresher( refresher, flags, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Remove( long id, long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Remove( id, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddEnum( IWbemServices* namespaceServices, LPCWSTR className, long flags, IWbemContext* context, IWbemHiPerfEnum** hiPerfEnum, long* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AddEnum( namespaceServices, className, flags, context, hiPerfEnum, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemObjectSinkEx : public WbemObjectSink
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemObjectSinkEx, WbemObjectSink )

        void WriteMessage( ULONG channel, __RPC__in const BSTR messageText ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteMessage( channel, messageText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteError( __RPC__in_opt IWbemClassObject* errorObject, __RPC__out unsigned char* returned ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteError( errorObject, returned );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PromptUser( __RPC__in const BSTR messageText, unsigned char promptType, __RPC__out unsigned char* returned ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PromptUser( messageText, promptType, returned );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteProgress( __RPC__in const BSTR activity, __RPC__in const BSTR currentOperation, __RPC__in const BSTR statusDescription, ULONG percentComplete, ULONG secondsRemaining ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteProgress( activity, currentOperation, statusDescription, percentComplete, secondsRemaining );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteStreamParameter( __RPC__in const BSTR name, __RPC__in VARIANT* value, ULONG type, ULONG flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteStreamParameter( name, value, type, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemShutdown : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemShutdown, Unknown )

        void Shutdown( LONG reason, ULONG maxMilliseconds, __RPC__in_opt IWbemContext* context ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Shutdown( reason, maxMilliseconds, context );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemObjectTextSrc : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemObjectTextSrc, Unknown )

        void GetText( long flags, IWbemClassObject* obj, ULONG objTextFormat, IWbemContext* context, BSTR* text ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetText( flags, obj, objTextFormat, context, text );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateFromText( long flags, BSTR text, ULONG objTextFormat, IWbemContext* context, IWbemClassObject** newObj ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateFromText( flags, text, objTextFormat, context, newObj );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class MofCompiler : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( MofCompiler, Unknown )

        void CompileFile( _In_  LPWSTR fileName, _In_  LPWSTR serverAndNamespace, _In_  LPWSTR user, _In_  LPWSTR authority, _In_  LPWSTR password, _In_  LONG optionFlags, _In_  LONG classFlags, _In_  LONG instanceFlags, _Inout_  WBEM_COMPILE_STATUS_INFO* info ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CompileFile( fileName, serverAndNamespace, user, authority, password, optionFlags, classFlags, instanceFlags, info );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CompileBuffer( _In_  long bufferSize, BYTE* buffer, _In_  LPWSTR serverAndNamespace, _In_  LPWSTR user, _In_  LPWSTR authority, _In_  LPWSTR password, _In_  LONG optionFlags, _In_  LONG classFlags, _In_  LONG instanceFlags, _Inout_  WBEM_COMPILE_STATUS_INFO* info ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CompileBuffer( bufferSize, buffer, serverAndNamespace, user, authority, password, optionFlags, classFlags, instanceFlags, info );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateBMOF( _In_  LPWSTR textFileName, _In_  LPWSTR bmofFileName, _In_  LPWSTR serverAndNamespace, _In_  LONG optionFlags, _In_  LONG classFlags, _In_  LONG instanceFlags, _Inout_  WBEM_COMPILE_STATUS_INFO* info ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateBMOF( textFileName, bmofFileName, serverAndNamespace, optionFlags, classFlags, instanceFlags, info );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemPropertyProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemPropertyProvider, Unknown )

        void GetProperty( long flags, __RPC__in const BSTR locale, __RPC__in const BSTR classMapping, __RPC__in const BSTR instMapping, __RPC__in const BSTR propMapping, __RPC__out VARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetProperty( flags, locale, classMapping, instMapping, propMapping, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PutProperty( long flags, __RPC__in const BSTR locale, __RPC__in const BSTR classMapping, __RPC__in const BSTR instMapping, __RPC__in const BSTR propMapping, __RPC__in const VARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->PutProperty( flags, locale, classMapping, instMapping, propMapping, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemUnboundObjectSink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemUnboundObjectSink, Unknown )

        void IndicateToConsumer( __RPC__in_opt IWbemClassObject* logicalConsumer, long numObjects, __RPC__in_ecount_full( numObjects ) IWbemClassObject** objectArray ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IndicateToConsumer( logicalConsumer, numObjects, objectArray );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemEventProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemEventProvider, Unknown )

        void ProvideEvents( __RPC__in_opt IWbemObjectSink* sink, long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ProvideEvents( sink, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemEventProviderQuerySink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemEventProviderQuerySink, Unknown )

        void NewQuery( unsigned long id, __RPC__in WBEM_WSTR queryLanguage, __RPC__in WBEM_WSTR query ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->NewQuery( id, queryLanguage, query );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CancelQuery( unsigned long id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CancelQuery( id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemEventProviderSecurity : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemEventProviderSecurity, Unknown )

        void AccessCheck( __RPC__in WBEM_CWSTR queryLanguage, __RPC__in WBEM_CWSTR query, long sidLength, __RPC__in_ecount_full_opt( sidLength ) const BYTE* sid ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->AccessCheck( queryLanguage, query, sidLength, sid );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemEventConsumerProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemEventConsumerProvider, Unknown )

        void FindConsumer( __RPC__in_opt IWbemClassObject* logicalConsumer, __RPC__deref_out_opt IWbemUnboundObjectSink** consumer ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->FindConsumer( logicalConsumer, consumer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemProviderInitSink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemProviderInitSink, Unknown )

        void SetStatus( LONG status, LONG flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetStatus( status, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemProviderInit : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemProviderInit, Unknown )

        void Initialize( __RPC__in_opt_string LPWSTR user, LONG flags, __RPC__in_string LPWSTR namespaceName, __RPC__in_opt_string LPWSTR locale, __RPC__in_opt IWbemServices* namespaceServices, __RPC__in_opt IWbemContext* context, __RPC__in_opt IWbemProviderInitSink* initSink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Initialize( user, flags, namespaceName, locale, namespaceServices, context, initSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemHiPerfProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemHiPerfProvider, Unknown )

        void QueryInstances( _In_  IWbemServices* namespaceServices, _In_  WCHAR* className, _In_  long flags, _In_  IWbemContext* context, _Out_  IWbemObjectSink* sink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->QueryInstances( namespaceServices, className, flags, context, sink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateRefresher( _In_  IWbemServices* namespaceServices, _In_  long flags, _Out_  IWbemRefresher** refresher ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateRefresher( namespaceServices, flags, refresher );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateRefreshableObject( _In_  IWbemServices* namespaceServices, _In_  IWbemObjectAccess* templateObject, _In_  IWbemRefresher* refresher, _In_  long flags, _In_  IWbemContext* context, _Out_  IWbemObjectAccess** refreshable, _Out_  long* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateRefreshableObject( namespaceServices, templateObject, refresher, flags, context, refreshable, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void StopRefreshing( _In_  IWbemRefresher* refresher, _In_  long id, _In_  long flags ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->StopRefreshing( refresher, id, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateRefreshableEnum( _In_  IWbemServices* namespaceServices, _In_  LPCWSTR className, _In_  IWbemRefresher* refresher, _In_  long flags, _In_  IWbemContext* context, _In_  IWbemHiPerfEnum* hiPerfEnum, _Out_  long* id ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CreateRefreshableEnum( namespaceServices, className, refresher, flags, context, hiPerfEnum, id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetObjects( _In_  IWbemServices* namespaceServices, _In_  long numObjects, _Out_writes_( numObjects )  IWbemObjectAccess** objecArray, _In_  long flags, _In_  IWbemContext* context ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetObjects( namespaceServices, numObjects, objecArray, flags, context );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    class WbemDecoupledRegistrar : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemDecoupledRegistrar, Unknown )

        void Register( long flags, IWbemContext* context, LPCWSTR user, LPCWSTR locale, LPCWSTR scope, LPCWSTR registration, IUnknown* unknown ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Register( flags, context, user, locale, scope, registration, unknown );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void UnRegister( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UnRegister( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemProviderIdentity : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemProviderIdentity, Unknown )

        void SetRegistrationObject( long flags, __RPC__in_opt IWbemClassObject* registrationObject ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetRegistrationObject( flags, registrationObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemDecoupledBasicEventProvider : public WbemDecoupledRegistrar
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemDecoupledBasicEventProvider, WbemDecoupledRegistrar )

        void GetSink( long flags, IWbemContext* context, IWbemObjectSink** sink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSink( flags, context, sink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetService( long flags, IWbemContext* context, IWbemServices** service ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetService( flags, context, service );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemEventSink : public WbemObjectSink
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemEventSink, WbemObjectSink )

        void SetSinkSecurity( long securityDescriptorSize, __RPC__in_ecount_full( securityDescriptorSize ) BYTE* securityDescriptor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSinkSecurity( securityDescriptorSize, securityDescriptor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsActive( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->IsActive( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }

        void GetRestrictedSink( long lNumQueries, __RPC__in_ecount_full( lNumQueries ) const LPCWSTR* awszQueries, __RPC__in_opt IUnknown* pCallback, __RPC__deref_out_opt IWbemEventSink** ppSink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetRestrictedSink( lNumQueries, awszQueries, pCallback, ppSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetBatchingParameters( LONG flags, DWORD dwMaxBufferSize, DWORD dwMaxSendLatency ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetBatchingParameters( flags, dwMaxBufferSize, dwMaxSendLatency );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemTransport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemTransport, Unknown )

        void Initialize( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Initialize( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemLevel1Login : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemLevel1Login, Unknown )

        void EstablishPosition( __RPC__in_opt_string LPWSTR wszLocaleList, DWORD dwNumLocales, __RPC__out DWORD* reserved ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->EstablishPosition( wszLocaleList, dwNumLocales, reserved );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RequestChallenge( __RPC__in_opt_string LPWSTR wszNetworkResource, __RPC__in_opt_string LPWSTR wszUser, __RPC__out WBEM_128BITS Nonce ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestChallenge( wszNetworkResource, wszUser, Nonce );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WBEMLogin( __RPC__in_opt_string LPWSTR wszPreferredLocale, __RPC__in_opt WBEM_128BITS AccessToken, long flags, __RPC__in_opt IWbemContext* pCtx, __RPC__deref_out_opt IWbemServices** ppNamespace ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WBEMLogin( wszPreferredLocale, AccessToken, flags, pCtx, ppNamespace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void NTLMLogin( __RPC__in_opt_string LPWSTR wszNetworkResource, __RPC__in_opt_string LPWSTR wszPreferredLocale, long flags, __RPC__in_opt IWbemContext* pCtx, __RPC__deref_out_opt IWbemServices** ppNamespace ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->NTLMLogin( wszNetworkResource, wszPreferredLocale, flags, pCtx, ppNamespace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemConnectorLogin : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemConnectorLogin, Unknown )

        void ConnectorLogin( __RPC__in_opt_string LPWSTR wszNetworkResource, __RPC__in_opt_string LPWSTR wszPreferredLocale, long flags, __RPC__in_opt IWbemContext* pCtx, __RPC__in REFIID riid, __RPC__deref_out_opt void** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ConnectorLogin( wszNetworkResource, wszPreferredLocale, flags, pCtx, riid, result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    class WbemAddressResolution : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemAddressResolution, Unknown )

        void Resolve( _In_  LPWSTR wszNamespacePath, _Out_  LPWSTR wszAddressType, _Out_  DWORD* pdwAddressLength, _Out_  BYTE** pabBinaryAddress ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Resolve( wszNamespacePath, wszAddressType, pdwAddressLength, pabBinaryAddress );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemClientTransport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemClientTransport, Unknown )

        void ConnectServer( BSTR strAddressType, DWORD dwBinaryAddressLength, BYTE* abBinaryAddress, BSTR strNetworkResource, BSTR strUser, BSTR strPassword, BSTR strLocale, long lSecurityFlags, BSTR strAuthority, IWbemContext* pCtx, IWbemServices** ppNamespace ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ConnectServer( strAddressType, dwBinaryAddressLength, abBinaryAddress, strNetworkResource, strUser, strPassword, strLocale, lSecurityFlags, strAuthority, pCtx, ppNamespace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemClientConnectionTransport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemClientConnectionTransport, Unknown )

        void Open( BSTR strAddressType, DWORD dwBinaryAddressLength, BYTE* abBinaryAddress, const BSTR strObject, const BSTR strUser, const BSTR strPassword, const BSTR strLocale, long flags, IWbemContext* pCtx, REFIID riid, void** pResult, IWbemCallResult** pCallRes ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Open( strAddressType, dwBinaryAddressLength, abBinaryAddress, strObject, strUser, strPassword, strLocale, flags, pCtx, riid, pResult, pCallRes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OpenAsync( BSTR strAddressType, DWORD dwBinaryAddressLength, BYTE* abBinaryAddress, const BSTR strObject, const BSTR strUser, const BSTR strPassword, const BSTR strLocale, long flags, IWbemContext* pCtx, REFIID riid, IWbemObjectSink* pResponseHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->OpenAsync( strAddressType, dwBinaryAddressLength, abBinaryAddress, strObject, strUser, strPassword, strLocale, flags, pCtx, riid, pResponseHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Cancel( long flags, IWbemObjectSink* pHandler ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Cancel( flags, pHandler );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class WbemConstructClassObject : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2( WbemConstructClassObject, Unknown )

        void SetInheritanceChain( _In_  long lNumAntecedents, _In_reads_bytes_( lNumAntecedents )  LPWSTR* awszAntecedents ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetInheritanceChain( lNumAntecedents, awszAntecedents );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPropertyOrigin( _In_  LPCWSTR wszPropertyName, _In_  long lOriginIndex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetPropertyOrigin( wszPropertyName, lOriginIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetMethodOrigin( _In_  LPCWSTR wszMethodName, _In_  long lOriginIndex ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetMethodOrigin( wszMethodName, lOriginIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetServerNamespace( _In_  LPCWSTR wszServer, _In_  LPCWSTR wszNamespace ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetServerNamespace( wszServer, wszNamespace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    inline WbemQualifierSet WbemClassObject::GetQualifierSet( ) const
    {
        IWbemQualifierSet* ptr = nullptr;
        GetQualifierSet( &ptr );
        return WbemQualifierSet( ptr );
    }

    inline WbemQualifierSet WbemClassObject::GetPropertyQualifierSet( LPCWSTR propertyName ) const
    {
        IWbemQualifierSet* ptr = nullptr;
        if ( GetPropertyQualifierSet( propertyName, &ptr ) )
        {
            return WbemQualifierSet( ptr );
        }
        else
        {
            return WbemQualifierSet( );
        }
    }
    template<WideStringType T>
    inline WbemQualifierSet WbemClassObject::GetPropertyQualifierSet( const T& propertyName ) const
    {
        return GetPropertyQualifierSet( propertyName.c_str( ) );
    }

    inline WbemQualifierSet WbemClassObject::GetMethodQualifierSet( LPCWSTR methodName ) const
    {
        IWbemQualifierSet* ptr;
        GetMethodQualifierSet( methodName, &ptr );
        return WbemQualifierSet( ptr );
    }
    template<WideStringType T>
    void WbemClassObject::GetMethodQualifierSet( const T& methodName ) const
    {
        return GetMethodQualifierSet( methodName.c_str( ) );
    }

}


#endif
