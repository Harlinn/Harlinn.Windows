#pragma once
#ifndef __HCCSECURITY_H__
#define __HCCSECURITY_H__

#include <HCCDef.h>
#include <HCCGuid.h>
#include <HCCDateTime.h>
#include <HCCCrypto.h>

#pragma comment(lib,"Secur32.lib")

namespace Harlinn::Common::Core::Security
{
    /// <summary>
    /// The standard object types that can be secured
    /// using the Windows API
    /// </summary>
    enum class ObjectType : int
    {
        /// <summary>
        /// Unknown object type
        /// </summary>
        Unknown = SE_UNKNOWN_OBJECT_TYPE,
        /// <summary>
        /// Indicates a file or directory. 
        /// The name string that identifies a file or directory 
        /// object can be in one of the following formats:
        /// <ul>
        /// <li>A relative path, such as <emp>FileName.dat</emp> or <emp>..\FileName</emp> </li>
        /// <li>An absolute path, such as <emp>FileName.dat</emp>, <emp>C:\DirectoryName\FileName.dat</emp>, or <emp>G:\RemoteDirectoryName\FileName.dat</emp>.</li>
        /// <li>A UNC name, such as <emp>\\ComputerName\ShareName\FileName.dat</emp></li>
        /// </ul>
        /// </summary>
        FileObject = SE_FILE_OBJECT,
        /// <summary>
        /// Indicates a Windows service. A service object can be a local service, such as <emp>ServiceName</emp>, or a remote service, such as <emp>\\ComputerName\ServiceName</emp>.
        /// </summary>
        Service = SE_SERVICE,
        /// <summary>
        /// Indicates a printer. A printer object can be a local printer, such as <emp>PrinterName</emp>, or a remote printer, such as <emp>\\ComputerName\PrinterName</emp>.
        /// </summary>
        Printer = SE_PRINTER,
        /// <summary>
        /// <p>
        /// Indicates a registry key. A registry key object can be in the local registry, such as <emp>CLASSES_ROOT\SomePath</emp> or in a remote registry, such as <emp>\\ComputerName\CLASSES_ROOT\SomePath</emp>.
        /// </p>
        /// <p>
        /// The names of registry keys must use the following literal strings to identify the predefined registry keys: "CLASSES_ROOT", "CURRENT_USER", "MACHINE", and "USERS".
        /// </p>
        /// </summary>
        RegistryKey = SE_REGISTRY_KEY,
        /// <summary>
        /// Indicates a network share. A share object can be local, such as <emp>ShareName</emp>, or remote, such as <emp>\\ComputerName\ShareName</emp>.
        /// </summary>
        NetworkShare = SE_LMSHARE,
        /// <summary>
        /// Indicates a local kernel object.
        /// </summary>
        /// <remarks>
        /// 
        /// </remarks>
        KernelObject = SE_KERNEL_OBJECT,
        WindowObject = SE_WINDOW_OBJECT,
        DirectoryServiceObject = SE_DS_OBJECT,
        CompleteDirectoryServiceObject = SE_DS_OBJECT_ALL,
        ProviderDefinedObject = SE_PROVIDER_DEFINED_OBJECT,
        WMIGuidObject = SE_WMIGUID_OBJECT,
        RegistryWOW64_32Key = SE_REGISTRY_WOW64_32KEY,
        RegistryWOW64_64Key = SE_REGISTRY_WOW64_64KEY

    };

    /// <summary>
    /// The SecurityInformation enumeration identifies the object-related 
    /// security information being set or queried.
    /// </summary>
    /// <remarks>
    /// This security information includes:
    /// <ul>
    /// <li>The owner of an object</li>
    /// <li>The primary group of an object</li>
    /// <li>The discretionary access control list (DACL) of an object</li>
    /// <li>The system access control list (SACL) of an object</li>
    /// </ul>
    /// </remarks>
    enum class SecurityInformation : DWORD
    { 
        None = 0,
        /// <summary>
        /// The owner identifier of the object is being referenced
        /// </summary>
        Owner = OWNER_SECURITY_INFORMATION,
        /// <summary>
        /// The primary group identifier of the object is being referenced.
        /// </summary>
        Group = GROUP_SECURITY_INFORMATION,
        /// <summary>
        /// The DACL of the object is being referenced
        /// </summary>
        DACL = DACL_SECURITY_INFORMATION,
        /// <summary>
        /// The SACL of the object is being referenced
        /// </summary>
        SACL = SACL_SECURITY_INFORMATION,
        /// <summary>
        /// The mandatory integrity label is being referenced. 
        /// The mandatory integrity label is an ACE in the SACL of the object.
        /// </summary>
        Label = LABEL_SECURITY_INFORMATION,
        /// <summary>
        /// 
        /// </summary>
        Attribute = ATTRIBUTE_SECURITY_INFORMATION,
        Scope = SCOPE_SECURITY_INFORMATION,
        ProcessTrustLabel = PROCESS_TRUST_LABEL_SECURITY_INFORMATION,
        AccessFilter = ACCESS_FILTER_SECURITY_INFORMATION,
        Backup = BACKUP_SECURITY_INFORMATION,
        ProtectedDACL = PROTECTED_DACL_SECURITY_INFORMATION,
        ProtectedSACL = PROTECTED_SACL_SECURITY_INFORMATION,
        UnprotectedDACL = UNPROTECTED_DACL_SECURITY_INFORMATION,
        UnprotectedSACL = UNPROTECTED_SACL_SECURITY_INFORMATION
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SecurityInformation, DWORD );

    /// <summary>
    /// Identifies the type of an access control entry
    /// </summary>
    enum class AccessControlEntryType : Byte
    {
        Minimum = 0,
        /// <summary>
        /// 
        /// </summary>
        AccessAllowed = ACCESS_ALLOWED_ACE_TYPE,
        AccessDenied = ACCESS_DENIED_ACE_TYPE,
        SystemAudit = SYSTEM_AUDIT_ACE_TYPE,
        SystemAlarm = SYSTEM_ALARM_ACE_TYPE,
        MaximumV2 = ACCESS_MAX_MS_V2_ACE_TYPE,

        CompoundAccessAllowed = ACCESS_ALLOWED_COMPOUND_ACE_TYPE,
        AccessAllowedCompound = ACCESS_ALLOWED_COMPOUND_ACE_TYPE,
        MaximumV3 = ACCESS_MAX_MS_V3_ACE_TYPE,

        MinimumObject = ACCESS_MIN_MS_OBJECT_ACE_TYPE,
        AccessAllowedObject = ACCESS_ALLOWED_OBJECT_ACE_TYPE,
        AccessDeniedObject = ACCESS_DENIED_OBJECT_ACE_TYPE,
        SystemAuditObject = SYSTEM_AUDIT_OBJECT_ACE_TYPE,
        SystemAlarmObject = SYSTEM_ALARM_OBJECT_ACE_TYPE,
        MaximumObject = ACCESS_MAX_MS_OBJECT_ACE_TYPE,

        MaximumV4 = ACCESS_MAX_MS_V4_ACE_TYPE,
        MaximumAccess = ACCESS_MAX_MS_ACE_TYPE,

        AccessAllowedCallback = ACCESS_ALLOWED_CALLBACK_ACE_TYPE,
        AccessDeniedCallback = ACCESS_DENIED_CALLBACK_ACE_TYPE,
        AccessAllowedCallbackObject = ACCESS_ALLOWED_CALLBACK_OBJECT_ACE_TYPE,
        AccessDeniedCallbackObject = ACCESS_DENIED_CALLBACK_OBJECT_ACE_TYPE,
        SystemAuditCallback = SYSTEM_AUDIT_CALLBACK_ACE_TYPE,
        SystemAlarmCallback = SYSTEM_ALARM_CALLBACK_ACE_TYPE,
        SystemAuditCallbackObject = SYSTEM_AUDIT_CALLBACK_OBJECT_ACE_TYPE,
        SystemAlarmCallbackObject = SYSTEM_ALARM_CALLBACK_OBJECT_ACE_TYPE,

        SystemMandatoryLabel = SYSTEM_MANDATORY_LABEL_ACE_TYPE,
        SystemResourceAttribute = SYSTEM_RESOURCE_ATTRIBUTE_ACE_TYPE,
        SystemScopedPolicyId = SYSTEM_SCOPED_POLICY_ID_ACE_TYPE,
        SystemProcessTrustLabel = SYSTEM_PROCESS_TRUST_LABEL_ACE_TYPE,
        SystemAccessFilter = SYSTEM_ACCESS_FILTER_ACE_TYPE,
        MaximumV5 = ACCESS_MAX_MS_V5_ACE_TYPE,
        Maximum = ACCESS_MAX_MS_V5_ACE_TYPE
    };

    /// <summary>
    /// Specifies a set of ACE type-specific control flags. 
    /// </summary>
    enum class AccessControlEntryFlags : Byte
    {
        None = 0,
        /// <summary>
        /// Noncontainer child objects inherit the ACE as an effective ACE.
        /// For child objects that are containers, the ACE is inherited as an 
        /// inherit-only ACE unless the NoPropagateInherit bit flag is also set.
        /// </summary>
        ObjectInherit = OBJECT_INHERIT_ACE,
        /// <summary>
        /// Child objects that are containers, such as directories, inherit the 
        /// ACE as an effective ACE. The inherited ACE is inheritable unless 
        /// the NoPropagateInherit bit flag is also set.
        /// </summary>
        ContainerInherit = CONTAINER_INHERIT_ACE,
        /// <summary>
        /// <p>
        /// If the ACE is inherited by a child object, the system clears the 
        /// ObjectInherit and ContainerInherit flags in the inherited ACE. 
        /// </p>
        /// <p>
        /// This prevents the ACE from being inherited by subsequent generations 
        /// of objects.
        /// </p>
        /// </summary>
        NoPropagateInherit = NO_PROPAGATE_INHERIT_ACE,
        /// <summary>
        /// <p>
        /// Indicates an inherit-only ACE, which does not control access to the 
        /// object to which it is attached. If this flag is not set, the ACE is 
        /// an effective ACE which controls access to the object to which it is 
        /// attached.
        /// </p>
        /// <p>
        /// Both effectiveand inherit - only ACEs can be inherited depending on 
        /// the state of the other inheritance flags.
        /// </p>
        /// </summary>
        InheritOnly = INHERIT_ONLY_ACE,
        /// <summary>
        /// Indicates that the ACE was inherited. The system sets this bit when 
        /// it propagates an inherited ACE to a child object.
        /// </summary>
        Inherited = INHERITED_ACE,
        InheritMask = VALID_INHERIT_FLAGS,
        /// <summary>
        /// Controls whether the ACE is critical and cannot be removed.
        /// </summary>
        /// <remarks>
        /// Only used with access allowed ACE types to indicate that 
        /// the ACE is critical and cannot be removed.
        /// </remarks>
        Critical = CRITICAL_ACE_FLAG,
        /// <summary>
        /// Only used with system audit and alarm ACE types to indicate that a message is generated for successful accesses.
        /// </summary>
        SuccessfulAccess = SUCCESSFUL_ACCESS_ACE_FLAG,
        /// <summary>
        /// Only used with system audit and alarm ACE types to indicate that a message is generated for failed accesses.
        /// </summary>
        FailedAccess = FAILED_ACCESS_ACE_FLAG,
        /// <summary>
        /// Only used with AccessControlEntryType::SystemFiltering ACEs to indicate that this 
        /// ACE may not be deleted/modified except when the, the current Trust Level dominates 
        /// the one specified in the Ace SID. If this flag is set then the SID in the ACE should 
        /// be a valid TrustLevelSid.
        /// </summary>
        TrustProtectedFilter = TRUST_PROTECTED_FILTER_ACE_FLAG
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AccessControlEntryFlags, Byte );


    /// <summary>
    /// A set of bit flags that indicate whether the ObjectType and InheritedObjectType members are present.
    /// </summary>
    enum class ObjectAccessControlEntryFlags : DWORD
    {
        /// <summary>
        /// Neither ObjectType nor InheritedObjectType are present. The SidStart member 
        /// follows immediately after the Flags member.
        /// </summary>
        None = 0,
        /// <summary>
        /// ObjectType is present and contains a GUID.
        /// If this value is not specified, the InheritedObjectType member follows immediately after the Flags member.
        /// </summary>
        ObjectTypePresent = ACE_OBJECT_TYPE_PRESENT,
        /// <summary>
        /// InheritedObjectType is present and contains a GUID.
        /// If this value is not specified, all types of child objects can inherit the ACE.
        /// </summary>
        InheritedObjectTypePresent = ACE_INHERITED_OBJECT_TYPE_PRESENT,

        Both = ObjectTypePresent | InheritedObjectTypePresent
    };

    /// <summary>
    /// The TrusteeForm enumeration contains values that indicate 
    /// the type of data pointed to by the ptstrName member of 
    /// the TRUSTEE structure
    /// </summary>
    enum class TrusteeForm : Int32
    {
        SecurityId = TRUSTEE_IS_SID,
        Name = TRUSTEE_IS_NAME,
        Invalid = TRUSTEE_BAD_FORM,
        ObjectsAndSid = TRUSTEE_IS_OBJECTS_AND_SID,
        ObjectsAndName = TRUSTEE_IS_OBJECTS_AND_NAME
    };

    /// <summary>
    /// The object types that can be identified
    /// by a Trustee object
    /// </summary>
    enum class TrusteeType : Int32
    {
        Unknown = TRUSTEE_IS_UNKNOWN,
        User = TRUSTEE_IS_USER,
        Group = TRUSTEE_IS_GROUP,
        Domain = TRUSTEE_IS_DOMAIN,
        Alias = TRUSTEE_IS_ALIAS,
        WellKnownGroup = TRUSTEE_IS_WELL_KNOWN_GROUP,
        Deleted = TRUSTEE_IS_DELETED,
        Invalid = TRUSTEE_IS_INVALID,
        Computer = TRUSTEE_IS_COMPUTER
    };


    enum class AccessMode : Int32
    {
        NotUsed = NOT_USED_ACCESS,
        Grant = GRANT_ACCESS,
        Set = SET_ACCESS,
        Deny = DENY_ACCESS,
        Revoke = REVOKE_ACCESS,
        AuditSuccess = SET_AUDIT_SUCCESS,
        AuditFailure = SET_AUDIT_FAILURE
    };

    /// <summary>
    /// Contains values that specify security impersonation levels. 
    /// Security impersonation levels govern the degree to which a 
    /// server process can act on behalf of a client process.
    /// </summary>
    enum class ImpersonationLevel : Int32
    {
        /// <summary>
        /// The server process cannot obtain identification 
        /// information about the client, and it cannot 
        /// impersonate the client. 
        /// </summary>
        Anonymous = SecurityAnonymous,
        /// <summary>
        /// The server process can obtain information about the 
        /// client, such as security identifiers and privileges, 
        /// but it cannot impersonate the client. This is useful 
        /// for servers that export their own objects, for example, 
        /// database products that export tables and views. Using 
        /// the retrieved client-security information, the server 
        /// can make access-validation decisions without being 
        /// able to use other services that are using the client's 
        /// security context.
        /// </summary>
        Identification = SecurityIdentification,
        /// <summary>
        /// The server process can impersonate the client's security 
        /// context on its local system. The server cannot impersonate 
        /// the client on remote systems.
        /// </summary>
        Impersonation = SecurityImpersonation,
        /// <summary>
        /// The server process can impersonate the client's security 
        /// context on remote systems.
        /// </summary>
        Delegation = SecurityDelegation
    };


    /// <summary>
    /// contains values that differentiate between a primary 
    /// token and an impersonation token.
    /// </summary>
    enum class TokenType : Int32
    {
        Unknown = 0,
        /// <summary>
        /// Indicates a primary token.
        /// </summary>
        Primary = TokenPrimary,
        /// <summary>
        /// Indicates an impersonation token
        /// </summary>
        Impersonation = TokenImpersonation
    };

    /// <summary>
    /// Privilege levels
    /// </summary>
    enum class UserPrivilege : DWORD
    {
        None = 0,
        Guest = USER_PRIV_GUEST,
        User = USER_PRIV_USER,
        Admin = USER_PRIV_ADMIN
    };


    /// <summary>
    /// Bit masks for User attributes
    /// </summary>
    enum class UserFlags : DWORD
    {
        None = 0,
        /// <summary>
        /// The logon script executed. This value must be set.
        /// </summary>
        Script = UF_SCRIPT,
        /// <summary>
        /// The user's account is disabled.
        /// </summary>
        AccountDisabled = UF_ACCOUNTDISABLE,
        /// <summary>
        /// The home directory is required. This value is ignored.
        /// </summary>
        HomeDirectoryRequired = UF_HOMEDIR_REQUIRED,
        /// <summary>
        /// The account is currently locked out. You can call the 
        /// NetUserSetInfo function and clear this value to unlock 
        /// a previously locked account. You cannot use this value 
        /// to lock a previously unlocked account.
        /// </summary>
        Lockout = UF_LOCKOUT,
        /// <summary>
        /// No password is required.
        /// </summary>
        PasswordNotRequired = UF_PASSWD_NOTREQD,
        /// <summary>
        /// The user cannot change the password.
        /// </summary>
        PasswordCannotChange = UF_PASSWD_CANT_CHANGE,
        /// <summary>
        /// The user's password is stored under reversible 
        /// encryption in the Active Directory.
        /// </summary>
        EncryptedTextPasswordAllowed = UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED,
        /// <summary>
        /// This is an account for users whose primary 
        /// account is in another domain. This account 
        /// provides user access to this domain, but not 
        /// to any domain that trusts this domain. The 
        /// User Manager refers to this account type as 
        /// a local user account.
        /// </summary>
        TemporaryDuplicateAccount = UF_TEMP_DUPLICATE_ACCOUNT,
        /// <summary>
        /// This is a default account type that represents a typical user.
        /// </summary>
        NormalAccount = UF_NORMAL_ACCOUNT,
        /// <summary>
        /// This is a permit to trust account for a domain 
        /// that trusts other domains.
        /// </summary>
        InterdomainTrustAccount = UF_INTERDOMAIN_TRUST_ACCOUNT,
        /// <summary>
        /// This is a computer account for a computer that is 
        /// a member of this domain.
        /// </summary>
        WorkstationTrustAccount = UF_WORKSTATION_TRUST_ACCOUNT,
        /// <summary>
        /// This is a computer account for a backup domain 
        /// controller that is a member of this domain.
        /// </summary>
        ServerTrustAccount = UF_SERVER_TRUST_ACCOUNT,
        /// <summary>
        /// The password should never expire on the account.
        /// </summary>
        PasswordNeverExpires = UF_DONT_EXPIRE_PASSWD,
        /// <summary>
        /// A Majority Node Set (MNS) account, such account 
        /// are required for the operation of cluster nodes 
        /// for Windows Server 2003 (and newer), in which 
        /// the quorum data is not stored on a shared media 
        /// drive. This flag should never be set for a user 
        /// account.
        /// </summary>
        MajorityNodeSetAccount = UF_MNS_LOGON_ACCOUNT,
        /// <summary>
        /// Requires the user to log on to the user account 
        /// with a smart card.
        /// </summary>
        SmartcardRequired = UF_SMARTCARD_REQUIRED,
        /// <summary>
        /// The account is enabled for delegation. This is a 
        /// security-sensitive setting; accounts with this 
        /// option enabled should be tightly controlled. This 
        /// setting allows a service running under the account 
        /// to assume a client's identity and authenticate as 
        /// that user to other remote servers on the network.
        /// </summary>
        TrustedForDelegation = UF_TRUSTED_FOR_DELEGATION,
        /// <summary>
        /// Marks the account as "sensitive"; other users 
        /// cannot act as delegates of this user account.
        /// </summary>
        NotDelegated = UF_NOT_DELEGATED,
        /// <summary>
        /// Restrict this principal to use only Data 
        /// Encryption Standard (DES) encryption types for 
        /// keys.
        /// </summary>
        UseDESKeyOnly = UF_USE_DES_KEY_ONLY,
        /// <summary>
        /// This account does not require Kerberos 
        /// preauthentication for logon.
        /// </summary>
        DontRequirePreAuthentication = UF_DONT_REQUIRE_PREAUTH,
        /// <summary>
        /// The user's password has expired.
        /// </summary>
        PasswordExpired = UF_PASSWORD_EXPIRED,
        /// <summary>
        /// The account is trusted to authenticate a user outside 
        /// of the Kerberos security package and delegate that 
        /// user through constrained delegation. This is a 
        /// security-sensitive setting; accounts with this option 
        /// enabled should be tightly controlled. This setting 
        /// allows a service running under the account to assert 
        /// a client's identity and authenticate as that user to 
        /// specifically configured services on the network.
        /// </summary>
        TrustedToAuthenticateForDelegation = UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION,
        /// <summary>
        /// Indicates that the regarding account can request a ticket 
        /// in the Kerberos ticketing process without sending the 
        /// so-called Privilege Attribute Certificate (PAC) data. 
        /// The PAC data structure is a Microsoft-specific Kerberos 
        /// extension and contains information about the security ID 
        /// of the user and the groups in which it is member. This 
        /// bit is only relevant if the account in question logs in 
        /// from a foreign non-Windows machine at the domain and 
        /// it does not support PAC.
        /// </summary>
        NoAuthDataRequired = UF_NO_AUTH_DATA_REQUIRED,
        /// <summary>
        /// Indicates that this is a ReadOnly domain controller account. 
        /// </summary>
        PartialSecretsAccount = UF_PARTIAL_SECRETS_ACCOUNT,
        /// <summary>
        /// Use AES keys for encryption
        /// </summary>
        UseAESKeys = UF_USE_AES_KEYS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( UserFlags, DWORD );

    /// <summary>
    /// Bit mask for group attributes
    /// </summary>
    enum class GroupFlags : DWORD
    {
        None = 0,
        /// <summary>
        /// The group is mandatory.
        /// </summary>
        Mandatory = SE_GROUP_MANDATORY,
        /// <summary>
        /// The group is enabled for access checks by default.
        /// </summary>
        EnabledByDefault = SE_GROUP_ENABLED_BY_DEFAULT,
        /// <summary>
        /// The group is enabled for access checks.
        /// </summary>
        Enabled = SE_GROUP_ENABLED,
        /// <summary>
        /// The group identifies a group account for which 
        /// the user of the token is the owner of the group.
        /// </summary>
        Owner = SE_GROUP_OWNER,
        /// <summary>
        /// The group is used for deny only purposes. When 
        /// this attribute is set, the Enabled flag must not be set.
        /// </summary>
        UseForDenyOnly = SE_GROUP_USE_FOR_DENY_ONLY,
        /// <summary>
        /// The group is used for integrity. This attribute 
        /// is available on Windows Vista and later.
        /// </summary>
        Integrity = SE_GROUP_INTEGRITY,
        /// <summary>
        /// The group is enabled for integrity level. This 
        /// attribute is available on Windows Vista and later.
        /// </summary>
        IntegrityEnabled = SE_GROUP_INTEGRITY_ENABLED,
        /// <summary>
        /// The group is used to identify a logon session 
        /// associated with an access token.
        /// </summary>
        LogonId = SE_GROUP_LOGON_ID,
        /// <summary>
        /// The group identifies a domain-local group.
        /// </summary>
        Resource = SE_GROUP_RESOURCE
    };

    /// <summary>
    /// Contains the values that specifies the 
    /// type of a security identifier
    /// </summary>
    enum class SecurityIdType
    {
        /// <summary>
        /// User
        /// </summary>
        User = SidTypeUser,
        /// <summary>
        /// Group
        /// </summary>
        Group = SidTypeGroup,
        /// <summary>
        /// Domain
        /// </summary>
        Domain = SidTypeDomain,
        Alias = SidTypeAlias,
        WellKnownGroup = SidTypeWellKnownGroup,
        DeletedAccount = SidTypeDeletedAccount,
        Invalid = SidTypeInvalid,
        Unknown = SidTypeUnknown,
        Computer = SidTypeComputer,
        /// <summary>
        /// A mandatory integrity label SID
        /// </summary>
        Label = SidTypeLabel,
        LogonSession = SidTypeLogonSession
    };


    

    namespace Internal
    {
        HCC_EXPORT void ThrowOwnershipRequiredException( const wchar_t* message, const wchar_t* function, const wchar_t* file, int lineNumber );
        HCC_EXPORT void ThrowInvalidOperationException( const wchar_t* message, const wchar_t* function, const wchar_t* file, int lineNumber );
    }





    class SecurityId;
    /// <summary>
    /// A Trustee object identifies a user account, group account, or 
    /// logon session to which an access control entry (ACE) applies. 
    /// The object can use a name or a security identifier (SecurityId/SID) 
    /// to identify the trustee.
    /// </summary>
    class Trustee
    {
        TRUSTEEW* trustee_;
        bool ownsTrustee_;

    public:
        
        // Base{nullptr,NO_MULTIPLE_TRUSTEE, TRUSTEE_BAD_FORM, TRUSTEE_IS_UNKNOWN, nullptr }
        constexpr Trustee() noexcept
            : trustee_(nullptr), ownsTrustee_(false)
        { }

        constexpr Trustee( TRUSTEEW* trustee, bool ownsTrustee = false ) noexcept
            : trustee_( trustee ), ownsTrustee_( ownsTrustee )
        {
        }

        explicit Trustee( const wchar_t* trusteeName ) noexcept
            : trustee_( new TRUSTEEW{ nullptr,NO_MULTIPLE_TRUSTEE, TRUSTEE_BAD_FORM, TRUSTEE_IS_UNKNOWN, nullptr } ), ownsTrustee_(true)
        {
            BuildTrusteeWithNameW( trustee_, const_cast<LPWSTR>(trusteeName) );
        }
        explicit Trustee( const Security::SecurityId& sid ) noexcept;
        explicit Trustee( PSID sid ) noexcept;
        ~Trustee( )
        {
            if ( trustee_ && ownsTrustee_ )
            {
                delete trustee_;
            }
        }
    private:
        void ReleaseTrustee( )
        {
            if ( trustee_ && ownsTrustee_ )
            {
                delete trustee_;
                trustee_ = nullptr;
            }
        }
    public:

        void Assign( TRUSTEEW* trustee, bool ownsTrustee = false )
        {
            if ( trustee != trustee_ )
            {
                ReleaseTrustee( );
                trustee_ = trustee;
            }
            ownsTrustee_ = ownsTrustee;
        }

        constexpr bool IsValid( ) const noexcept
        {
            return trustee_ != nullptr;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }

        constexpr bool operator == ( const TRUSTEEW* other ) const noexcept
        {
            return trustee_ == other;
        }
        constexpr bool operator != ( const TRUSTEEW* other ) const noexcept
        {
            return trustee_ != other;
        }




        Security::TrusteeForm Form( ) const noexcept
        {
            return trustee_? static_cast<Security::TrusteeForm>( trustee_->TrusteeForm ): Security::TrusteeForm::Invalid;
        }

        Security::TrusteeType Type( ) const noexcept
        {
            return trustee_ ? static_cast<Security::TrusteeType>( trustee_->TrusteeType ) : Security::TrusteeType::Invalid;
        }

        Security::SecurityId SecurityId( ) const;

        const wchar_t* Name( ) const
        {
            return trustee_ ? trustee_->ptstrName : nullptr;
        }


    };

    /// <summary>
    /// An ExplicitAccess object defines access control information for a 
    /// specified trustee. 
    /// </summary>
    class ExplicitAccess : public EXPLICIT_ACCESS
    {
    public:
        using Base = EXPLICIT_ACCESS;


        /// <summary>
        /// Returns a reference to the Trustee object that identifies the user, 
        /// group, or program (such as a Windows service) to which the ACE applies
        /// </summary>
        /// <returns>A reference to the requested Trustee object.</returns>
        Security::Trustee Trustee( ) noexcept
        {
            return Security::Trustee(&(static_cast<EXPLICIT_ACCESS*>(this)->Trustee));
        }
        /// <summary>
        /// Returns a reference to the Trustee object that identifies the user, 
        /// group, or program (such as a Windows service) to which the ACE applies
        /// </summary>
        /// <returns>A reference to the requested Trustee object.</returns>
        const Security::Trustee Trustee( ) const noexcept
        {
            return Security::Trustee( &( const_cast<EXPLICIT_ACCESS*>( static_cast<const EXPLICIT_ACCESS*>( this ))->Trustee )  );
        }

    };

    namespace Internal
    {
        /// <summary>
        /// Indicates how resources are released
        /// when the managing object goes out of 
        /// scope.
        /// </summary>
        enum class ReleaseMethod
        {
            /// <summary>
            /// No action is taken to release the resource
            /// </summary>
            None = 0,
            /// <summary>
            /// LocalFree is called to release the
            /// memory for the resource
            /// </summary>
            LocalFree,
            /// <summary>
            /// The resource is a SID and FreeSid
            /// is called to relese the memory for 
            /// the SID.
            /// </summary>
            FreeSid,
            /// <summary>
            /// The memory was allocated using <emp>new Byte[size]</emp>
            /// and is released using delete.
            /// </summary>
            Delete,
            /// <summary>
            /// The memory will be released using DestroyPrivateObjectSecurity
            /// </summary>
            DestroyPrivateObjectSecurity

        };
    }

    
    struct SecurityIdInfo
    {
        std::wstring Name;
        std::wstring Domain;
        SecurityIdType Type;
    };

    /// <summary>
    /// A security identifier (SID) is a unique value of variable length used 
    /// to identify a trustee.
    /// The SecurityId class is used to manage SIDs. 
    /// </summary>
    /// <remarks>
    /// <p>
    /// SecurityId objects are move constructible and move assignable, but not
    /// copy constructible and copy assignable.
    /// </p>
    /// <p>
    /// Each account has a unique SID issued by an authority, such as a Windows 
    /// domain controller, and stored in a security database. Each time a user 
    /// logs on, the system retrieves the SID for that user from the database and 
    /// places it in the access token for that user. The system uses the SID in the 
    /// access token to identify the user in all subsequent interactions with Windows 
    /// security. When a SID has been used as the unique identifier for a user or group, 
    /// it cannot ever be used again to identify another user or group.
    /// </p>
    /// <p>
    /// Windows security uses SIDs in the following security elements:
    /// <ul>
    /// <li>In security descriptors to identify the owner of an object and primary group</li>
    /// <li>In access control entries, to identify the trustee for whom access is allowed, denied, or audited</li>
    /// <li>In access tokens, to identify the user and the groups to which the user belongs</li>
    /// </ul>
    /// </p>
    /// <p>
    /// In addition to the uniquely created, domain-specific SIDs assigned to specific 
    /// users and groups, there are well-known SIDs that identify generic groups and 
    /// generic users. For example, the well-known SIDs, Everyone and World, 
    /// identify a group that includes all users.
    /// </p>
    /// <p>
    /// Because the names of well-known SIDs can vary, you should use the functions 
    /// to build the SID from predefined constants rather than using the name of the 
    /// well-known SID. 
    /// </p>
    /// </remarks>
    class SecurityId
    { 
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;

    protected:
        /// <summary>
        /// Pointer to the SID managed by this SecurityId.
        /// </summary>
        SID* sid_;
        /// <summary>
        /// The length of the SID managed by this SecurityId.
        /// </summary>
        DWORD size_;
        /// <summary>
        /// Indicates the release method used to discard the
        /// SID managed by this SecurityId.
        /// </summary>
        ReleaseMethod releaseMethod_;
    public:
        
        // The constant SECURITY_MAX_SID_SIZE defines the maximum size of a SID
        static constexpr DWORD MaxSize = SECURITY_MAX_SID_SIZE;
        static constexpr DWORD MaxCharacters = SECURITY_MAX_SID_STRING_CHARACTERS;
        using WellKnownSIDType = WELL_KNOWN_SID_TYPE;


        /// <summary>
        /// IdentifierAuthority represents the top-level authority of a SecurityId
        /// </summary>
        class IdentifierAuthority : public SID_IDENTIFIER_AUTHORITY
        {
            static constexpr size_t ValueSize = sizeof( SID_IDENTIFIER_AUTHORITY );
        public:
            using Base = SID_IDENTIFIER_AUTHORITY;
            constexpr IdentifierAuthority( ) noexcept
                : Base{}
            {
            }
            constexpr IdentifierAuthority( const SID_IDENTIFIER_AUTHORITY& other ) noexcept
                : Base( other )
            {
            }
            constexpr IdentifierAuthority& operator = ( const SID_IDENTIFIER_AUTHORITY& other ) noexcept
            {
                for ( size_t i = 0; i < ValueSize; ++i )
                {
                    Value[i] = other.Value[i];
                }
                return *this;
            }


            static constexpr SID_IDENTIFIER_AUTHORITY Null =  { 0, 0, 0, 0, 0, 0 };
            static constexpr SID_IDENTIFIER_AUTHORITY World = { 0, 0, 0, 0, 0, 1 };
            static constexpr SID_IDENTIFIER_AUTHORITY Local = { 0, 0, 0, 0, 0, 2 };
            static constexpr SID_IDENTIFIER_AUTHORITY Creator = { 0,0,0,0,0,3 };
            static constexpr SID_IDENTIFIER_AUTHORITY NonUnique = { 0,0,0,0,0,4 };
            static constexpr SID_IDENTIFIER_AUTHORITY ResourceManager = { 0,0,0,0,0,9 };

        };

        /// <summary>
        /// Constructs an empty SecurityId
        /// </summary>
        constexpr SecurityId( ) noexcept
            : sid_( nullptr ), size_(0), releaseMethod_( ReleaseMethod::None )
        {
        }

        /// <summary>
        /// Constructs a SecurityId for managing the argument SID
        /// </summary>
        /// <param name="sid">
        /// A pointer to the SID that will be managed by the new SecurityId object.
        /// </param>
        /// <param name="releaseMethod">
        /// Specifies how the memory occupied by the SID will be released.
        /// </param>
        explicit SecurityId( PSID sid, ReleaseMethod releaseMethod = ReleaseMethod::None ) noexcept
            : sid_( ( SID* )sid ), size_( sid? GetLengthSid( sid ) : 0 ), releaseMethod_( releaseMethod )
        {
        }

        /// <summary>
        /// Construct a SecurityId object for a well-known SID
        /// </summary>
        /// <param name="wellKnownSIDType">
        /// Member of the WellKnownSIDType enumeration that 
        /// specifies what the SID will identify.
        /// </param>
        /// <param name="domainSID">
        /// A pointer to a SID that identifies the domain to use when creating the SID. 
        /// Pass nullptr to use the local computer.
        /// </param>
        explicit SecurityId( WellKnownSIDType wellKnownSIDType, PSID domainSID = nullptr ) noexcept
            : sid_( nullptr ), size_( 0 ), releaseMethod_( ReleaseMethod::None )
        {
            std::array<Byte, MaxSize> buffer{};
            DWORD sidSize = MaxSize;
            auto rc = CreateWellKnownSid( wellKnownSIDType, domainSID, buffer.data( ), &sidSize );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            sid_ = ( SID* )new Byte[sidSize];
            releaseMethod_ = ReleaseMethod::Delete;
            size_ = sidSize;
            memcpy( sid_, buffer.data( ), sidSize );
        }

        



        SecurityId( const SecurityId& other ) = delete;
        constexpr SecurityId( SecurityId&& other ) noexcept
            : sid_( other.sid_ ), size_( other.size_ ), releaseMethod_(other.releaseMethod_)
        {
            other.sid_ = nullptr;
            other.size_ = 0;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~SecurityId( )
        {
            ReleaseSID( );
        }

        SecurityId& operator = ( const SecurityId& other ) = delete;
        constexpr SecurityId& operator = ( SecurityId&& other ) noexcept
        {
            std::swap( sid_, other.sid_ );
            std::swap( size_, other.size_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }

        SecurityId Clone( ) const
        {
            DWORD sz = Length( );
            if ( sz )
            {
                PSID pSID = ( PSID )new Byte[sz];
                auto rc = CopySid( sz, pSID, sid_ );
                if ( !rc )
                {
                    delete[]( Byte* )pSID;
                    ThrowLastOSError( );
                }
                return SecurityId( pSID, ReleaseMethod::Delete );
            }
            else
            {
                return SecurityId( );
            }
        }
        static SecurityId Clone( PSID sid )
        {
            DWORD sz = GetLengthSid( sid );
            if ( sz )
            {
                PSID pSID = ( PSID )new Byte[sz];
                auto rc = CopySid( sz, pSID, sid );
                if ( !rc )
                {
                    delete[]( Byte* )pSID;
                    ThrowLastOSError( );
                }
                return SecurityId( pSID, ReleaseMethod::Delete );
            }
            else
            {
                return SecurityId( );
            }
        }


        
    private:
        void ReleaseSID( )
        {
            if ( sid_ )
            {
                switch ( releaseMethod_ )
                {
                    case ReleaseMethod::LocalFree:
                    {
                        LocalFree( sid_ );
                    }
                    break;
                    case ReleaseMethod::FreeSid:
                    {
                        FreeSid( sid_ );
                    }
                    break;
                    case ReleaseMethod::Delete:
                    {
                        delete[] (Byte*)sid_;
                    }
                    break;
                }
            }
            sid_ = nullptr;
            releaseMethod_ = ReleaseMethod::None;
        }
    public:
        void Assign( PSID sid, ReleaseMethod releaseMethod ) noexcept
        {
            if ( sid_ != sid )
            {
                ReleaseSID( );
            }
            sid_ = (SID*)sid;
            size_ = sid != nullptr ? GetLengthSid( sid ) : 0;
            releaseMethod_ = releaseMethod;

        }

        constexpr const SID* Value( ) const noexcept
        {
            return sid_;
        }
        constexpr SID* Value( ) noexcept
        {
            return sid_;
        }


        bool IsEqual( const SecurityId& sid ) const
        {
            return EqualSid( sid_, sid.sid_ ) != 0;
        }

        friend bool operator == ( PSID psid, const SecurityId& sid )
        {
            return EqualSid( psid, sid.sid_ ) != 0;
        }

        friend bool operator != ( PSID psid, const SecurityId& sid )
        {
            return EqualSid( psid, sid.sid_ ) == 0;
        }

        bool operator == ( const SecurityId& sid ) const noexcept
        {
            return EqualSid( sid_, sid.sid_ ) != 0;
        }

        bool operator != ( const SecurityId& sid ) const noexcept
        {
            return EqualSid( sid_, sid.sid_ ) == 0;
        }

        bool operator == ( PSID psid ) const noexcept
        {
            return EqualSid( sid_, psid ) != 0;
        }

        bool operator != ( PSID psid ) const noexcept
        {
            return EqualSid( sid_, psid ) == 0;
        }



        DWORD Length( ) const
        {
            if ( sid_ )
            {
                return GetLengthSid( sid_ );
            }
            else
            {
                return 0;
            }
        }

        bool IsValid( ) const noexcept
        {
            if ( sid_ )
            {
                return IsValidSid( sid_ ) != 0;
            }
            else
            {
                return false;
            }
        }

        explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }


        std::wstring ToString( ) const
        {
            LPWSTR stringSid = nullptr;
            auto rc = ConvertSidToStringSidW( sid_, &stringSid );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            std::wstring result( stringSid );
            LocalFree( stringSid );
            return result;
        }

        std::wstring Name( const wchar_t* serverName = nullptr ) const
        {
            SID_NAME_USE accountType{};
            std::array<wchar_t, 260> buffer;
            std::array<wchar_t, 260> domain;
            DWORD bufferSize = static_cast<DWORD>(buffer.size( ));
            DWORD domainSize = static_cast<DWORD>( domain.size( ) );
            auto rc = LookupAccountSidW( serverName, sid_, buffer.data( ), &bufferSize, domain.data(), &domainSize, &accountType );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            std::wstring result( buffer.data( ), bufferSize );
            return result;
        }

        SecurityIdInfo Info( const wchar_t* serverName = nullptr ) const
        {
            SID_NAME_USE accountType{};
            std::array<wchar_t, 260> buffer;
            std::array<wchar_t, 260> domain;
            DWORD bufferSize = static_cast<DWORD>( buffer.size( ) );
            DWORD domainSize = static_cast<DWORD>( domain.size( ) );
            auto rc = LookupAccountSidW( serverName, sid_, buffer.data( ), &bufferSize, domain.data( ), &domainSize, &accountType );
            if ( !rc )
            {
                ThrowLastOSError( );
            }

            SecurityIdInfo result{ {buffer.data( ), bufferSize},{domain.data( ),domainSize}, static_cast<SecurityIdType>( accountType ) };
            return result;
        }




        

    };


    inline Trustee::Trustee( const Security::SecurityId& sid ) noexcept
        : trustee_( new TRUSTEEW{ nullptr,NO_MULTIPLE_TRUSTEE, TRUSTEE_BAD_FORM, TRUSTEE_IS_UNKNOWN, nullptr } ), ownsTrustee_( true )
    {
        BuildTrusteeWithSidW( trustee_, (PSID)sid.Value( ) );
    }

    inline Trustee::Trustee( PSID sid ) noexcept
        : trustee_( new TRUSTEEW{ nullptr,NO_MULTIPLE_TRUSTEE, TRUSTEE_BAD_FORM, TRUSTEE_IS_UNKNOWN, nullptr } ), ownsTrustee_( true )
    {
        BuildTrusteeWithSidW( trustee_, sid );
    }


    inline Security::SecurityId Trustee::SecurityId( ) const
    {
        return trustee_? Security::SecurityId( (PSID)trustee_->ptstrName ): Security::SecurityId( );
    }


    class SecurityIdAndDomain
    {
    public:
        using StringType = std::wstring;
        using SecurityIdType = SID_NAME_USE;
    private:
        Security::SecurityId securityId_;
        std::wstring domainName_;
        SecurityIdType securityIdType_;
    public:
        SecurityIdAndDomain()
            : securityIdType_( SecurityIdType::SidTypeInvalid )
        { }

        explicit SecurityIdAndDomain( const wchar_t* accountName, const wchar_t* systemName = nullptr )
            : securityIdType_( SecurityIdType::SidTypeInvalid )
        {
            std::array<Byte, Security::SecurityId::MaxSize> sidBuffer{};
            DWORD sidBufferSize = static_cast<DWORD>( sidBuffer.size( ) );
            std::array<wchar_t, 512> domainNameBuffer{};
            DWORD domainNameBufferSize = static_cast<DWORD>( domainNameBuffer.size( ) );

            auto rc = LookupAccountNameW( systemName, accountName, (PSID)sidBuffer.data( ), &sidBufferSize, domainNameBuffer.data( ), &domainNameBufferSize, &securityIdType_ );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            domainName_.assign( domainNameBuffer.data( ), domainNameBufferSize );
            PSID pSID = new Byte[sidBufferSize];
            rc = CopySid( sidBufferSize, pSID, sidBuffer.data( ) );
            if ( !rc )
            {
                delete[] (Byte*)pSID;
                ThrowLastOSError( );
            }
            securityId_.Assign( pSID, Security::SecurityId::ReleaseMethod::Delete );

        }


        SecurityIdAndDomain( const SecurityIdAndDomain& other ) = delete;
        SecurityIdAndDomain( SecurityIdAndDomain&& other ) noexcept
            : securityId_( std::move( other.securityId_ ) ), domainName_( std::move( other.domainName_ ) ), securityIdType_( other.securityIdType_ )
        { }

        SecurityIdAndDomain& operator = ( const SecurityIdAndDomain& other ) = delete;
        SecurityIdAndDomain& operator = ( SecurityIdAndDomain&& other ) noexcept
        {
            std::swap( securityId_, other.securityId_ );
            std::swap( domainName_, other.domainName_ );
            std::swap( securityIdType_, other.securityIdType_ );
            return *this;
        }

        constexpr const Security::SecurityId& SecurityId( ) const noexcept
        {
            return securityId_;
        }
        constexpr const std::wstring& DomainName( ) const noexcept
        {
            return domainName_;
        }

        constexpr SecurityIdType Type( ) const noexcept
        {
            return securityIdType_;
        }
    };


    class SecurityIdAndFlags
    {
        PSID sid_;
        GroupFlags flags_;
    public:
        constexpr SecurityIdAndFlags() noexcept
            : sid_(nullptr), flags_( GroupFlags::None )
        { }

        constexpr SecurityIdAndFlags( PSID sid, GroupFlags flags ) noexcept
            : sid_( sid ), flags_( flags )
        {
        }

        Security::SecurityId SecurityId( ) const
        {
            Security::SecurityId result( sid_, Security::SecurityId::ReleaseMethod::None );
            return result;
        }

        constexpr PSID SID( ) const noexcept
        {
            return sid_;
        }
        constexpr void SetSID( PSID sid ) noexcept
        {
            sid_ = sid;
        }

        constexpr GroupFlags Flags( ) const noexcept
        {
            return flags_;
        }
        constexpr void SetFlags( GroupFlags flags ) noexcept
        {
            flags_ = flags;
        }

    };
    static_assert( sizeof( SecurityIdAndFlags ) == sizeof( SID_AND_ATTRIBUTES ), "Do not add any new data members to the SecurityIdAndFlags class" );




    /// <summary>
    /// An LocalUniqueId is a 64-bit value guaranteed to be unique 
    /// only on the system on which it was generated. The uniqueness 
    /// of a locally unique identifier (LUID) is guaranteed only until 
    /// the system is restarted.
    /// </summary>
    class LocalUniqueId
    {
    public:
        using size_type = DWORD;
        static constexpr size_type Size = sizeof( LUID );
    private:
        Int64 data_;
    public:
        constexpr LocalUniqueId() noexcept
            : data_(0)
        { }

        constexpr LocalUniqueId( Int64 data ) noexcept
            : data_( data )
        {
        }

        constexpr LocalUniqueId( LUID data ) noexcept
            : data_( std::bit_cast<Int64>(data) )
        {
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return data_ != 0;
        }


        auto operator <=> ( const LocalUniqueId& other ) const noexcept = default;

        auto operator <=> ( Int64 other ) const noexcept
        {
            return data_ <=> other;
        }
        auto operator <=> ( LUID other ) const noexcept
        {
            return data_ <=> std::bit_cast<Int64>( other );
        }

        constexpr LUID Value( ) const
        {
            return std::bit_cast<LUID>( data_ );
        }

        static LocalUniqueId New( )
        {
            LUID value;
            auto rc = AllocateLocallyUniqueId( &value );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return value;
        }
        /// <summary>
        /// Retrieves the locally unique identifier used on a specified 
        /// system to locally represent the specified privilege name.
        /// </summary>
        /// <param name="privilegeName">
        /// A pointer to a null-terminated string that specifies the name of 
        /// the privilege, as defined in the Winnt.h header file. For example, 
        /// this parameter could specify the constant, SE_SECURITY_NAME, or its 
        /// corresponding string, L"SeSecurityPrivilege".
        /// </param>
        /// <param name="systemName">
        /// A pointer to a null-terminated string that specifies the name 
        /// of the system on which the privilege name is retrieved. If a 
        /// null string is specified, the function attempts to find the 
        /// privilege name on the local system.
        /// </param>
        /// <returns>
        /// The LocalUniqueId by which the privilege is known on the 
        /// system specified by the systemName parameter
        /// </returns>
        static LocalUniqueId FromPrivilegeName( const wchar_t* privilegeName, const wchar_t* systemName = nullptr )
        {
            LUID value{};
            auto rc = LookupPrivilegeValueW( systemName, privilegeName, &value );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return value;
        }
        /// <summary>
        /// Retrieves the locally unique identifier used on a specified 
        /// system to locally represent the specified privilege name.
        /// </summary>
        /// <param name="privilegeName">
        /// A pointer to a null-terminated string that specifies the name of 
        /// the privilege, as defined in the Winnt.h header file. For example, 
        /// this parameter could specify the constant, SE_SECURITY_NAME, or its 
        /// corresponding string, L"SeSecurityPrivilege".
        /// </param>
        /// <param name="systemName">
        /// A pointer to a null-terminated string that specifies the name 
        /// of the system on which the privilege name is retrieved. If a 
        /// null string is specified, the function attempts to find the 
        /// privilege name on the local system.
        /// </param>
        /// <returns>
        /// The LocalUniqueId by which the privilege is known on the 
        /// system specified by the systemName parameter
        /// </returns>
        static LocalUniqueId FromPrivilegeName( const char* privilegeName, const char* systemName = nullptr )
        {
            LUID value{};
            auto rc = LookupPrivilegeValueA( systemName, privilegeName, &value );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return value;
        }


        /// <summary>
        /// Retrieves the name that corresponds to the privilege represented on a 
        /// specific system by this LocalUniqueId. 
        /// </summary>
        /// <param name="systemName">
        /// A pointer to a null-terminated string that specifies the name of the 
        /// system on which the privilege name is retrieved. If a null string is 
        /// specified, the function attempts to find the privilege name on the local 
        /// system.
        /// </param>
        /// <param name="buffer">
        /// A pointer to a buffer that receives a null-terminated string that represents 
        /// the privilege name. 
        /// </param>
        /// <param name="bufferSize">
        /// A pointer to a variable that specifies the size, in a wchar_t value, of the buffer. 
        /// When the function returns, this parameter contains the length of the privilege name, 
        /// not including the terminating null character. If the buffer pointed is too small, 
        /// this variable contains the required size.
        /// </param>
        /// <returns>true if the function succeeds, false if the buffer where too small</returns>
        bool QueryPrivilegeName( const wchar_t* systemName, wchar_t* buffer, DWORD* bufferSize ) const
        {
            auto rc = LookupPrivilegeNameW( systemName, (LUID*)&data_, buffer, bufferSize );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error != ERROR_INSUFFICIENT_BUFFER )
                {
                    ThrowOSError( error );
                }
            }
            return rc != 0;
        }
        /// <summary>
        /// Retrieves the name that corresponds to the privilege represented on a 
        /// specific system by this LocalUniqueId. 
        /// </summary>
        /// <param name="systemName">
        /// A pointer to a null-terminated string that specifies the name of the 
        /// system on which the privilege name is retrieved. If a null string is 
        /// specified, the function attempts to find the privilege name on the local 
        /// system.
        /// </param>
        /// <param name="buffer">
        /// A pointer to a buffer that receives a null-terminated string that represents 
        /// the privilege name. 
        /// </param>
        /// <param name="bufferSize">
        /// A pointer to a variable that specifies the size, in a wchar_t value, of the buffer. 
        /// When the function returns, this parameter contains the length of the privilege name, 
        /// not including the terminating null character. If the buffer pointed is too small, 
        /// this variable contains the required size.
        /// </param>
        /// <returns>true if the function succeeds, false if the buffer where too small</returns>
        bool QueryPrivilegeName( const char* systemName, char* buffer, DWORD* bufferSize ) const
        {
            auto rc = LookupPrivilegeNameA( systemName, (LUID*)&data_, buffer, bufferSize );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error != ERROR_INSUFFICIENT_BUFFER )
                {
                    ThrowOSError( error );
                }
            }
            return rc != 0;
        }
        /// <summary>
        /// Retrieves the name that corresponds to the privilege represented on a 
        /// specific system by this LocalUniqueId. 
        /// </summary>
        /// <param name="systemName">
        /// A pointer to a null-terminated string that specifies the name of the 
        /// system on which the privilege name is retrieved. If a null string is 
        /// specified, the function attempts to find the privilege name on the local 
        /// system.
        /// </param>
        /// <returns>The name of the privilege.</returns>
        std::wstring QueryPrivilegeName( const wchar_t* systemName = nullptr ) const
        {
            std::array<wchar_t, 512> buffer;
            size_type bufferLength = static_cast<size_type>( buffer.size( ) );
            auto rc = QueryPrivilegeName( systemName, buffer.data( ), &bufferLength );
            if ( !rc )
            {
                std::wstring result;
                result.resize( bufferLength - 1 );
                rc = QueryPrivilegeName( systemName, result.data( ), &bufferLength );
                if ( !rc )
                {
                    ThrowOSError( ERROR_INSUFFICIENT_BUFFER );
                }
                return result;
            }
            else
            {
                std::wstring result( buffer.data( ), bufferLength );
                return result;
            }
        }
        /// <summary>
        /// Retrieves the name that corresponds to the privilege represented on a 
        /// specific system by this LocalUniqueId. 
        /// </summary>
        /// <param name="systemName">
        /// A pointer to a null-terminated string that specifies the name of the 
        /// system on which the privilege name is retrieved. If a null string is 
        /// specified, the function attempts to find the privilege name on the local 
        /// system.
        /// </param>
        /// <returns>The name of the privilege.</returns>
        std::string QueryPrivilegeName( const char* systemName ) const
        {
            std::array<char, 512> buffer;
            size_type bufferLength = static_cast<size_type>( buffer.size( ) );
            auto rc = QueryPrivilegeName( systemName, buffer.data( ), &bufferLength );
            if ( !rc )
            {
                std::string result;
                result.resize( bufferLength - 1 );
                rc = QueryPrivilegeName( systemName, result.data( ), &bufferLength );
                if ( !rc )
                {
                    ThrowOSError( ERROR_INSUFFICIENT_BUFFER );
                }
                return result;
            }
            else
            {
                std::string result( buffer.data( ), bufferLength );
                return result;
            }
        }
    };

#define HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS \
None = 0, \
Delete = DELETE, \
ReadPermissions = READ_CONTROL, \
Synchronize = SYNCHRONIZE, \
ChangePermissions = WRITE_DAC, \
TakeOwnership = WRITE_OWNER, \
SystemSecurity = ACCESS_SYSTEM_SECURITY, \
MaximumAllowed = MAXIMUM_ALLOWED, \
StandardRightsRequiredMask = STANDARD_RIGHTS_REQUIRED, \
StandardRightsAllMask = STANDARD_RIGHTS_ALL, \
StandardRightsRead = STANDARD_RIGHTS_READ, \
StandardRightsWrite = STANDARD_RIGHTS_WRITE, \
StandardRightsExecute = STANDARD_RIGHTS_EXECUTE
    

    class GenericMapping;
    /// <summary>
    /// An ACCESS_MASK wrapper class.
    /// The ACCESS_MASK data type is a DWORD value that defines 
    /// standard, specific, and generic rights. These rights are 
    /// used in access control entries (ACEs) and are the primary 
    /// means of specifying the requested or granted access to an object.
    /// </summary>
    class AccessMask
    {
    protected:
        ACCESS_MASK mask_;
    public:
        constexpr AccessMask( ) noexcept : mask_( 0 ) {}
        constexpr explicit AccessMask( ACCESS_MASK mask ) noexcept 
            : mask_( mask ) 
        {}
        explicit AccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : mask_( mask )
        {
            ::MapGenericMask( &mask_, const_cast<GENERIC_MAPPING*>(&genericMapping) );
        }
        explicit AccessMask( ACCESS_MASK mask, const GenericMapping& genericMapping ) noexcept;

        constexpr ACCESS_MASK Value( ) const noexcept
        {
            return mask_;
        }

        constexpr AccessMask& operator = ( const ACCESS_MASK& mask )
        {
            mask_ = mask;
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return mask_ != 0;
        }

        /*
        constexpr auto operator <=>( const AccessMask& other ) const noexcept = default;
        constexpr auto operator <=>( const ACCESS_MASK other ) const noexcept
        {
            return mask_ <=> other;
        }
        */


    protected:
        template<ACCESS_MASK bitFlag>
        constexpr void SetBitFlag( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= bitFlag;
            }
            else
            {
                mask_ &= ~bitFlag;
            }
        }
        template<ACCESS_MASK bitFlag>
        constexpr bool CheckAll( ) const noexcept
        {
            return ( mask_ & bitFlag ) == bitFlag;
        }
        template<ACCESS_MASK bitFlag>
        constexpr bool Check( ) const noexcept
        {
            return ( mask_ & bitFlag ) != 0;
        }
    public:
        /// <summary>
        /// Check if the mask contains the right to delete.
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanDelete( ) const noexcept
        {
            return Check<DELETE>( );
        }
        /// <summary>
        /// Sets or clears the the right to delete in the access mask.
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetDelete( bool value = true ) noexcept
        {
            SetBitFlag<DELETE>( value );
        }

        /// <summary>
        /// Check if the mask contains the right to read the information 
        /// in the object's security descriptor, not including the 
        /// information in the system access control list (SACL).
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanReadControl( ) const noexcept
        {
            return Check<READ_CONTROL>( );
        }

        /// <summary>
        /// Sets or clears the right to read the information 
        /// in the object's security descriptor, not including the 
        /// information in the system access control list (SACL).
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetReadControl( bool value = true ) noexcept
        {
            SetBitFlag<READ_CONTROL>( value );
        }
        /// <summary>
        /// Check if the mask contains the right to read the information 
        /// in the object's security descriptor, not including the 
        /// information in the system access control list (SACL).
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanReadPermissions( ) const noexcept
        {
            return Check<READ_CONTROL>( );
        }

        /// <summary>
        /// Sets or clears the right to read the information 
        /// in the object's security descriptor, not including the 
        /// information in the system access control list (SACL).
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetReadPermissions( bool value = true ) noexcept
        {
            SetBitFlag<READ_CONTROL>( value );
        }

        /// <summary>
        /// Check if the mask contains the right to modify the 
        /// discretionary access control list (DACL) in the 
        /// object's security descriptor.
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanWriteDac( ) const noexcept
        {
            return Check<WRITE_DAC>( );
        }

        /// <summary>
        /// Sets or clears the right to modify the 
        /// discretionary access control list (DACL) in the 
        /// object's security descriptor.
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetWriteDac( bool value = true ) noexcept
        {
            SetBitFlag<WRITE_DAC>( value );
        }

        /// <summary>
        /// Check if the mask contains the right to modify the 
        /// discretionary access control list (DACL) in the 
        /// object's security descriptor.
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanChangePermissions( ) const noexcept
        {
            return Check<WRITE_DAC>( );
        }

        /// <summary>
        /// Sets or clears the right to modify the 
        /// discretionary access control list (DACL) in the 
        /// object's security descriptor.
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetChangePermissions( bool value = true ) noexcept
        {
            SetBitFlag<WRITE_DAC>( value );
        }

        /// <summary>
        /// Check if the mask contains the right to change the 
        /// owner in the object's security descriptor.
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanWriteOwner( ) const noexcept
        {
            return Check<WRITE_OWNER>( );
        }

        /// <summary>
        /// Sets or clears the right to change the 
        /// owner in the object's security descriptor.
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetWriteOwner( bool value = true ) noexcept
        {
            SetBitFlag<WRITE_OWNER>( value );
        }

        /// <summary>
        /// Check if the mask contains the right to change the 
        /// owner in the object's security descriptor.
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanTakeOwnership( ) const noexcept
        {
            return Check<WRITE_OWNER>( );
        }

        /// <summary>
        /// Sets or clears the right to change the 
        /// owner in the object's security descriptor.
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetTakeOwnership( bool value = true ) noexcept
        {
            SetBitFlag<WRITE_OWNER>( value );
        }

        /// <summary>
        /// Check if the mask contains the right to use the 
        /// object for synchronization. This enables a thread 
        /// to wait until the object is in the signaled state. 
        /// Some object types do not support this access right.
        /// </summary>
        /// <returns>true if the right is set.</returns>
        constexpr bool CanSynchronize( ) const noexcept
        {
            return Check<SYNCHRONIZE>( );
        }

        /// <summary>
        /// Sets or clears the right to use the object 
        /// for synchronization. This enables a thread 
        /// to wait until the object is in the signaled state. 
        /// Some object types do not support this access right.
        /// </summary>
        /// <param name="value">
        /// <ul>
        /// <li>If <code>value</code> is set to <em>true</em> then the right is set.</li>
        /// <li>If <code>value</code> is set to <em>false</em> then the right is cleared.</li>
        /// </ul>
        /// </param>
        constexpr void SetSynchronize( bool value = true ) noexcept
        {
            SetBitFlag<SYNCHRONIZE>( value );
        }

        template<typename T = AccessMask>
            requires std::is_base_of_v< AccessMask, std::remove_cvref_t<T> >
        constexpr T StandardRightsRequired( ) const noexcept
        {
            using AccessMaskT = std::remove_cvref_t<T>;
            return AccessMaskT( mask_ & STANDARD_RIGHTS_REQUIRED );
        }
        constexpr void SetStandardRightsRequired( ACCESS_MASK standardRightsRequired = STANDARD_RIGHTS_REQUIRED ) noexcept
        {
            mask_ = standardRightsRequired & STANDARD_RIGHTS_REQUIRED;
        }


        constexpr ACCESS_MASK StandardRights( ) const noexcept
        {
            return mask_ & STANDARD_RIGHTS_ALL;
        }
        constexpr void SetStandardRights( ACCESS_MASK standardRights ) noexcept
        {
            mask_ = standardRights & STANDARD_RIGHTS_ALL;
        }

        constexpr void SetStandardRightsAll( ACCESS_MASK standardRights = STANDARD_RIGHTS_ALL ) noexcept
        {
            mask_ = standardRights & STANDARD_RIGHTS_ALL;
        }


        constexpr ACCESS_MASK SpecificRights( ) const noexcept
        {
            return mask_ & SPECIFIC_RIGHTS_ALL;
        }
        constexpr void SetSpecificRights( ACCESS_MASK specificRights ) noexcept
        {
            mask_ = specificRights & SPECIFIC_RIGHTS_ALL;
        }
        constexpr void SetSpecificRightsAll( ACCESS_MASK specificRights = SPECIFIC_RIGHTS_ALL ) noexcept
        {
            mask_ = specificRights & SPECIFIC_RIGHTS_ALL;
        }

        constexpr bool AccessSystemSecurity( ) const noexcept
        {
            return ( mask_ & ACCESS_SYSTEM_SECURITY ) != 0;
        }

        constexpr void SetAccessSystemSecurity( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= ACCESS_SYSTEM_SECURITY;
            }
            else
            {
                mask_ &= ~ACCESS_SYSTEM_SECURITY;
            }
        }

        constexpr bool MaximumAllowed( ) const noexcept
        {
            return ( mask_ & MAXIMUM_ALLOWED ) != 0;
        }

        constexpr void SetMaximumAllowed( bool value = true ) noexcept
        {
            if ( value )
            {
                mask_ |= MAXIMUM_ALLOWED;
            }
            else
            {
                mask_ &= ~MAXIMUM_ALLOWED;
            }
        }


        constexpr bool GenericRead( ) const noexcept
        {
            return (mask_ & GENERIC_READ) != 0;
        }

        constexpr void SetGenericRead( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= GENERIC_READ;
            }
            else
            {
                mask_ &= ~GENERIC_READ;
            }
        }
        constexpr bool GenericWrite( ) const noexcept
        {
            return ( mask_ & GENERIC_WRITE ) != 0;
        }

        constexpr void SetGenericWrite( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= GENERIC_WRITE;
            }
            else
            {
                mask_ &= ~GENERIC_WRITE;
            }
        }
        constexpr bool GenericExecute( ) const noexcept
        {
            return ( mask_ & GENERIC_EXECUTE ) != 0;
        }

        constexpr void SetGenericExecute( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= GENERIC_EXECUTE;
            }
            else
            {
                mask_ &= ~GENERIC_EXECUTE;
            }
        }
        constexpr bool GenericAll( ) const noexcept
        {
            return ( mask_ & GENERIC_ALL ) != 0;
        }

        constexpr void SetGenericAll( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= GENERIC_ALL;
            }
            else
            {
                mask_ &= ~GENERIC_ALL;
            }
        }





        /// <summary>
        /// Maps the generic access rights in the access mask to specific 
        /// and standard access rights. The function applies a mapping supplied 
        /// in a GENERIC_MAPPING structure.
        /// </summary>
        /// <param name="genericMapping">
        /// A reference to a GENERIC_MAPPING structure specifying a mapping of 
        /// generic access types to specific and standard access types.
        /// </param>
        /// <returns>The resulting AccessMask</returns>
        AccessMask MapGenericMask( const GENERIC_MAPPING& genericMapping ) const
        {
            return AccessMask( mask_, genericMapping );
        }
        /// <summary>
        /// Maps the generic access rights in the access mask to specific 
        /// and standard access rights. The function applies a mapping supplied 
        /// in a GENERIC_MAPPING structure.
        /// </summary>
        /// <param name="genericMapping">
        /// A reference to a GENERIC_MAPPING structure specifying a mapping of 
        /// generic access types to specific and standard access types.
        /// </param>
        /// <returns>The resulting AccessMask</returns>
        AccessMask MapGenericMask( const GenericMapping& genericMapping ) const
        {
            return AccessMask( mask_, genericMapping );
        }
    };


    template<typename DerivedT, typename RightsT>
        requires std::is_enum_v<RightsT>
    class AccessMaskT : public AccessMask
    {
    public:
        using Base = AccessMask;
        using DerivedType = DerivedT;
        using Rights = RightsT;

        constexpr AccessMaskT( ) noexcept 
            {}
        constexpr explicit AccessMaskT( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }
        constexpr explicit AccessMaskT( Rights rights ) noexcept
            : Base( static_cast<ACCESS_MASK>( rights ) )
        {
        }
        explicit AccessMaskT( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit AccessMaskT( ACCESS_MASK mask, const GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit AccessMaskT( Rights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( static_cast<ACCESS_MASK>( rights ), genericMapping )
        {
        }
        explicit AccessMaskT( Rights rights, const GenericMapping& genericMapping ) noexcept
            : Base( static_cast<ACCESS_MASK>( rights ), genericMapping )
        {
        }

        /*
        constexpr auto operator <=>( const DerivedType& other ) const noexcept
        {
            return mask_ <=> other.mask_;
        }

        constexpr auto operator <=>( Rights other ) const noexcept
        {
            return mask_ <=> static_cast<ACCESS_MASK>( other );
        }

        constexpr auto operator <=>( ACCESS_MASK other ) const noexcept
        {
            return mask_ <=> other;
        }
        */
        
        // For version 16.8.5 the code below must be used
        // to implement the comparision. Since the code below 
        // *is* working, I would have expected the code above to
        // work too


        
        constexpr bool operator == ( const DerivedType& other ) const noexcept
        {
            return mask_ == other.mask_;
        }
        constexpr bool operator != ( const DerivedType& other ) const noexcept
        {
            return mask_ != other.mask_;
        }
        constexpr bool operator <= ( const DerivedType& other ) const noexcept
        {
            return mask_ <= other.mask_;
        }
        constexpr bool operator >= ( const DerivedType& other ) const noexcept
        {
            return mask_ >= other.mask_;
        }
        constexpr bool operator < ( const DerivedType& other ) const noexcept
        {
            return mask_ < other.mask_;
        }
        constexpr bool operator > ( const DerivedType& other ) const noexcept
        {
            return mask_ > other.mask_;
        }

        constexpr bool operator == ( ACCESS_MASK other ) const noexcept
        {
            return mask_ == other;
        }
        constexpr bool operator != ( ACCESS_MASK other ) const noexcept
        {
            return mask_ != other;
        }
        constexpr bool operator <= ( ACCESS_MASK other ) const noexcept
        {
            return mask_ <= other;
        }
        constexpr bool operator >= ( ACCESS_MASK other ) const noexcept
        {
            return mask_ >= other;
        }
        constexpr bool operator < ( ACCESS_MASK other ) const noexcept
        {
            return mask_ < other;
        }
        constexpr bool operator > ( ACCESS_MASK other ) const noexcept
        {
            return mask_ > other;
        }

        constexpr bool operator == ( Rights other ) const noexcept
        {
            return mask_ == static_cast<ACCESS_MASK>( other );
        }
        constexpr bool operator != ( Rights other ) const noexcept
        {
            return mask_ != static_cast<ACCESS_MASK>( other );
        }
        constexpr bool operator <= ( Rights other ) const noexcept
        {
            return mask_ <= static_cast<ACCESS_MASK>( other );
        }
        constexpr bool operator >= ( Rights other ) const noexcept
        {
            return mask_ >= static_cast<ACCESS_MASK>( other );
        }
        constexpr bool operator < ( Rights other ) const noexcept
        {
            return mask_ < static_cast<ACCESS_MASK>( other );
        }
        constexpr bool operator > ( Rights other ) const noexcept
        {
            return mask_ > static_cast<ACCESS_MASK>( other );
        }
        


        constexpr DerivedType& operator = ( const Rights rights ) noexcept
        {
            mask_ = static_cast<ACCESS_MASK>( rights );
            return static_cast<DerivedType&>( *this );
        }

        constexpr DerivedType& operator &= ( const Rights rights ) noexcept
        {
            mask_ &= static_cast<ACCESS_MASK>( rights );
            return static_cast<DerivedType&>( *this );
        }

        constexpr DerivedType& operator &= ( const ACCESS_MASK mask ) noexcept
        {
            mask_ &= mask;
            return static_cast<DerivedType&>( *this );
        }
        constexpr DerivedType& operator &= ( const DerivedType& mask ) noexcept
        {
            mask_ &= mask.mask_;
            return static_cast<DerivedType&>( *this );
        }

        constexpr DerivedType& operator |= ( const Rights rights ) noexcept
        {
            mask_ |= static_cast<ACCESS_MASK>( rights );
            return static_cast<DerivedType&>( *this );
        }

        constexpr DerivedType& operator += ( const Rights rights ) noexcept
        {
            mask_ |= static_cast<ACCESS_MASK>( rights );
            return static_cast<DerivedType&>( *this );
        }
        constexpr DerivedType& operator -= ( const Rights rights ) noexcept
        {
            mask_ &= ~static_cast<ACCESS_MASK>( rights );
            return static_cast<DerivedType&>( *this );
        }



        constexpr DerivedType& operator |= ( const ACCESS_MASK mask ) noexcept
        {
            mask_ |= mask;
            return static_cast<DerivedType&>(*this);
        }
        constexpr DerivedType& operator |= ( const DerivedType& mask ) noexcept
        {
            mask_ |= mask.mask_;
            return static_cast<DerivedType&>( *this );
        }

        friend constexpr DerivedType operator & ( const DerivedType& first, const ACCESS_MASK second ) noexcept
        {
            auto result = first.Value( ) & second;
            return DerivedType( result );
        }

        friend constexpr DerivedType operator & ( const ACCESS_MASK first, const DerivedType& second ) noexcept
        {
            auto result = first & second.Value();
            return DerivedType( result );
        }

        friend constexpr DerivedType operator & ( const DerivedType& first, const Rights second ) noexcept
        {
            auto result = first.Value( ) & static_cast<ACCESS_MASK>( second );
            return DerivedType( result );
        }

        friend constexpr DerivedType operator & ( const Rights first, const DerivedType& second ) noexcept
        {
            auto result = static_cast<ACCESS_MASK>( first ) & second.Value( );
            return DerivedType( result );
        }


        friend constexpr DerivedType operator | ( const DerivedType& first, const ACCESS_MASK second ) noexcept
        {
            auto result = first.Value( ) | second;
            return DerivedType( result );
        }
        friend constexpr DerivedType operator | ( const ACCESS_MASK first, const DerivedType& second ) noexcept
        {
            auto result = first | second.Value( );
            return DerivedType( result );
        }

        friend constexpr DerivedType operator | ( const DerivedType& first, const Rights second ) noexcept
        {
            auto result = first.Value( ) | static_cast<ACCESS_MASK>( second );
            return DerivedType( result );
        }
        friend constexpr DerivedType operator | ( const Rights first, const DerivedType& second ) noexcept
        {
            auto result = static_cast<ACCESS_MASK>( first ) | second.Value( );
            return DerivedType( result );
        }

        friend constexpr DerivedType operator + ( const DerivedType& first, const Rights second ) noexcept
        {
            auto result = first.Value( ) | static_cast<ACCESS_MASK>( second );
            return DerivedType( result );
        }
        friend constexpr DerivedType operator + ( const Rights first, const DerivedType& second ) noexcept
        {
            auto result = static_cast<ACCESS_MASK>( first ) | second.Value( );
            return DerivedType( result );
        }

        friend constexpr DerivedType operator - ( const DerivedType& first, const Rights second ) noexcept
        {
            auto result = first.Value( ) & (~static_cast<ACCESS_MASK>( second ));
            return DerivedType( result );
        }
        friend constexpr DerivedType operator - ( const Rights first, const DerivedType& second ) noexcept
        {
            auto result = static_cast<ACCESS_MASK>( first ) & (~second.Value( ));
            return DerivedType( result );
        }



    protected:
        using Base::SetBitFlag;
        using Base::CheckAll;
        using Base::Check;

        template<Rights rights>
        constexpr void SetBitFlag( bool value ) noexcept
        {
            if ( value )
            {
                mask_ |= static_cast<ACCESS_MASK>( rights );
            }
            else
            {
                mask_ &= ~static_cast<ACCESS_MASK>( rights );
            }
        }
        template<Rights rights>
        constexpr bool CheckAll( ) const noexcept
        {
            return ( mask_ & static_cast<ACCESS_MASK>( rights ) ) == static_cast<ACCESS_MASK>( rights );
        }
        template<Rights rights>
        constexpr bool Check( ) const noexcept
        {
            return ( mask_ & static_cast<ACCESS_MASK>( rights ) ) != 0;
        }
    public:
        /// <summary>
        /// Maps the generic access rights in the access mask to specific 
        /// and standard access rights. The function applies a mapping supplied 
        /// in a GENERIC_MAPPING structure.
        /// </summary>
        /// <param name="genericMapping">
        /// A reference to a GENERIC_MAPPING structure specifying a mapping of 
        /// generic access types to specific and standard access types.
        /// </param>
        /// <returns>The resulting AccessMask</returns>
        DerivedType MapGenericMask( const GENERIC_MAPPING& genericMapping ) const
        {
            return DerivedType( mask_, genericMapping );
        }
        /// <summary>
        /// Maps the generic access rights in the access mask to specific 
        /// and standard access rights. The function applies a mapping supplied 
        /// in a GENERIC_MAPPING structure.
        /// </summary>
        /// <param name="genericMapping">
        /// A reference to a GENERIC_MAPPING structure specifying a mapping of 
        /// generic access types to specific and standard access types.
        /// </param>
        /// <returns>The resulting AccessMask</returns>
        DerivedType MapGenericMask( const GenericMapping& genericMapping ) const
        {
            return DerivedType( mask_, genericMapping );
        }

    };


    class GenericMapping
    {
        GENERIC_MAPPING data_;
    public:
        constexpr GenericMapping(AccessMask genericRead, AccessMask genericWrite, AccessMask genericExecute, AccessMask genericAll ) noexcept
            : data_{ genericRead.Value(), genericWrite.Value( ), genericExecute.Value( ), genericAll.Value( ) }
        { }
        constexpr GenericMapping( ACCESS_MASK genericRead, ACCESS_MASK genericWrite, ACCESS_MASK genericExecute, ACCESS_MASK genericAll ) noexcept
            : data_{ genericRead, genericWrite, genericExecute, genericAll }
        {
        }

        constexpr const GENERIC_MAPPING& data( ) const noexcept
        {
            return data_;
        }
        constexpr GENERIC_MAPPING& data( ) noexcept
        {
            return data_;
        }
        constexpr const GENERIC_MAPPING* dataPtr( ) const noexcept
        {
            return &data_;
        }
        constexpr GENERIC_MAPPING* dataPtr( ) noexcept
        {
            return &data_;
        }

        constexpr AccessMask GenericRead( ) const noexcept { return AccessMask( data_.GenericRead ); }
        constexpr AccessMask GenericWrite( ) const noexcept { return AccessMask( data_.GenericWrite ); }
        constexpr AccessMask GenericExecute( ) const noexcept { return AccessMask( data_.GenericExecute ); }
        constexpr AccessMask GenericAll( ) const noexcept { return AccessMask( data_.GenericAll ); }

    };

    inline AccessMask::AccessMask( ACCESS_MASK mask, const GenericMapping& genericMapping ) noexcept
        : AccessMask( mask, genericMapping.data() )
    {
    }





#pragma pack(push,1)
    /// <summary>
    /// Base class for the various ACE wrappers
    /// </summary>
    class AccessControlEntry : ACE_HEADER
    {
    public:
        using Base = ACE_HEADER;
        using size_type = WORD;
    protected:

        constexpr AccessControlEntry() noexcept
            : Base{}
        { }

        constexpr AccessControlEntry( AccessControlEntryType type, AccessControlEntryFlags flags, size_type size ) noexcept
            : Base{ static_cast<BYTE>( type ), static_cast<BYTE>( flags ), size }
        {
        }

    public:


        constexpr AccessControlEntryType Type( ) const noexcept
        {
            return static_cast<AccessControlEntryType>( AceType );
        }
        constexpr void SetType( AccessControlEntryType type ) noexcept
        {
            AceType = static_cast<BYTE>( type );
        }
        constexpr AccessControlEntryFlags Flags( ) const noexcept
        {
            return static_cast<AccessControlEntryFlags>( AceFlags );
        }
        constexpr void SetFlags( AccessControlEntryFlags flags ) noexcept
        {
            AceFlags = static_cast<BYTE>( flags );
        }

        constexpr size_type size( ) const noexcept
        {
            return AceSize;
        }





        template<typename T>
        const T* As( ) const noexcept
        {
            const ACE_HEADER* header = this;
            return (const T*)header;
        }
        template<typename T>
        T* As( ) noexcept
        {
            const ACE_HEADER* header = this;
            return (const T*)header;
        }
    };


    template<typename AceT, typename AccessMaskT>
    class AccessControlEntryBase : public AccessControlEntry
    {
    public:
        using Base = AccessControlEntry;
        using AceType = AceT;
        using AccessMaskType = AccessMaskT;
    private:
        AccessMaskType mask_;
        DWORD sidStart_;
    protected:
        constexpr AccessControlEntryBase( ) noexcept
            : Base{}, sidStart_(0)
        {
        }

        constexpr AccessControlEntryBase( AccessControlEntryType type, AccessControlEntryFlags flags, size_type size, AccessMaskType mask ) noexcept
            : Base{ static_cast<BYTE>( type ), static_cast<BYTE>( flags ), size }, mask_( mask ), sidStart_( 0 )
        {
        }


        Security::SecurityId SecurityId( ) const noexcept
        {
            PSID pSID = (PSID)&sidStart_;
            return Security::SecurityId( pSID );
        }

    };


    class AccessAllowedAccessControlEntry : public AccessControlEntryBase<ACCESS_ALLOWED_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<ACCESS_ALLOWED_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:
    
    };

    static_assert( sizeof( AccessAllowedAccessControlEntry ) == sizeof( ACCESS_ALLOWED_ACE ), "The size of AccessAllowedAccessControlEntry must be identical to the size of ACCESS_ALLOWED_ACE." );

    class AccessDeniedAccessControlEntry : public AccessControlEntryBase<ACCESS_ALLOWED_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<ACCESS_ALLOWED_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessDeniedAccessControlEntry ) == sizeof( ACCESS_DENIED_ACE ), "The size of AccessDeniedAccessControlEntry must be identical to the size of ACCESS_DENIED_ACE." );

    class SystemAuditAccessControlEntry : public AccessControlEntryBase<SYSTEM_AUDIT_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_AUDIT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAuditAccessControlEntry ) == sizeof( SYSTEM_AUDIT_ACE ), "The size of SystemAuditAccessControlEntry must be identical to the size of SYSTEM_AUDIT_ACE." );

    class SystemAlarmAccessControlEntry : public AccessControlEntryBase<SYSTEM_ALARM_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_ALARM_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAlarmAccessControlEntry ) == sizeof( SYSTEM_ALARM_ACE ), "The size of SystemAlarmAccessControlEntry must be identical to the size of SYSTEM_ALARM_ACE." );

    class SystemResourceAttributeAccessControlEntry : public AccessControlEntryBase<SYSTEM_RESOURCE_ATTRIBUTE_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_RESOURCE_ATTRIBUTE_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemResourceAttributeAccessControlEntry ) == sizeof( SYSTEM_RESOURCE_ATTRIBUTE_ACE ), "The size of SystemResourceAttributeAccessControlEntry must be identical to the size of SYSTEM_RESOURCE_ATTRIBUTE_ACE." );

    class SystemScopedPolicyIdAccessControlEntry : public AccessControlEntryBase<SYSTEM_SCOPED_POLICY_ID_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_SCOPED_POLICY_ID_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemScopedPolicyIdAccessControlEntry ) == sizeof( SYSTEM_SCOPED_POLICY_ID_ACE ), "The size of SystemScopedPolicyIdAccessControlEntry must be identical to the size of SYSTEM_SCOPED_POLICY_ID_ACE." );


    class SystemMandatoryLabelAccessControlEntry : public AccessControlEntryBase<SYSTEM_MANDATORY_LABEL_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_MANDATORY_LABEL_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemMandatoryLabelAccessControlEntry ) == sizeof( SYSTEM_MANDATORY_LABEL_ACE ), "The size of SystemMandatoryLabelAccessControlEntry must be identical to the size of SYSTEM_MANDATORY_LABEL_ACE." );

    class SystemProcessTrustLabelAccessControlEntry : public AccessControlEntryBase<SYSTEM_PROCESS_TRUST_LABEL_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_PROCESS_TRUST_LABEL_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemProcessTrustLabelAccessControlEntry ) == sizeof( SYSTEM_PROCESS_TRUST_LABEL_ACE ), "The size of SystemProcessTrustLabelAccessControlEntry must be identical to the size of SYSTEM_PROCESS_TRUST_LABEL_ACE." );

    class SystemAccessFilterAccessControlEntry : public AccessControlEntryBase<SYSTEM_ACCESS_FILTER_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_ACCESS_FILTER_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAccessFilterAccessControlEntry ) == sizeof( SYSTEM_ACCESS_FILTER_ACE ), "The size of SystemAccessFilterAccessControlEntry must be identical to the size of SYSTEM_ACCESS_FILTER_ACE." );




    template<typename AceT, typename AccessMaskT>
    class ObjectAccessControlEntryBase : public AccessControlEntry
    {
    public:
        using Base = AccessControlEntry;
        using AceType = AceT;
        using AccessMaskType = AccessMaskT;
    private:
        AccessMaskType mask_;
        ObjectAccessControlEntryFlags objectFlags_;
        union
        {
            struct
            {
                DWORD sidStart_;
            } none_;
            struct
            {
                Guid ObjectType_;
                DWORD sidStart_;
            } ObjectType_;
            struct
            {
                Guid InheritedObjectType_;
                DWORD sidStart_;
            } InheritedObjectType_;
            struct
            {
                Guid ObjectType_;
                Guid InheritedObjectType_;
                DWORD sidStart_;
            } both_;
        };
    protected:
        constexpr ObjectAccessControlEntryBase( ) noexcept
            : Base{}
        {
        }

        constexpr ObjectAccessControlEntryBase( AccessControlEntryType type, AccessControlEntryFlags flags, size_type size, AccessMaskType mask, DWORD sidStart ) noexcept
            : Base{ static_cast<BYTE>( type ), static_cast<BYTE>( flags ), size }
        {
        }

        constexpr AccessMaskType Mask( ) const noexcept
        {
            return mask_;
        }
        constexpr ObjectAccessControlEntryFlags ObjectFlags( ) const noexcept
        {
            return objectFlags_;
        }

        const Guid* ObjectType( ) const noexcept
        {
            if ( (objectFlags_ & ObjectAccessControlEntryFlags::ObjectTypePresent) != ObjectAccessControlEntryFlags::None )
            {
                const Guid* result = &ObjectType_.ObjectType_;
                return result;
            }
            return nullptr;
        }
        const Guid* InheritedObjectType( ) const noexcept
        {
            if ( objectFlags_ == ObjectAccessControlEntryFlags::InheritedObjectTypePresent )
            {
                const Guid* result = &InheritedObjectType_.InheritedObjectType_;
                return result;
            }
            else if ( objectFlags_ == ObjectAccessControlEntryFlags::Both )
            {
                const Guid* result = &both_.InheritedObjectType_;
                return result;
            }
            return nullptr;
        }


        Security::SecurityId SecurityId( ) const noexcept
        {
            switch ( objectFlags_ )
            {
                case ObjectAccessControlEntryFlags::ObjectTypePresent:
                {
                    PSID pSID = (PSID)&ObjectType_.sidStart_;
                    return Security::SecurityId( pSID );
                }
                break;
                case ObjectAccessControlEntryFlags::InheritedObjectTypePresent:
                {
                    PSID pSID = (PSID)&InheritedObjectType_.sidStart_;
                    return Security::SecurityId( pSID );
                }
                break;
                case ObjectAccessControlEntryFlags::Both:
                {
                    PSID pSID = (PSID)&both_.sidStart_;
                    return Security::SecurityId( pSID );
                }
                break;
                default:
                {
                    PSID pSID = (PSID)&none_.sidStart_;
                    return Security::SecurityId( pSID );
                }
                break;
            }
        }


    };


    class AccessAllowedObjectAccessControlEntry : public ObjectAccessControlEntryBase<ACCESS_ALLOWED_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<ACCESS_ALLOWED_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessAllowedObjectAccessControlEntry ) == sizeof( ACCESS_ALLOWED_OBJECT_ACE ), "The size of SystemAccessFilterAccessControlEntry must be identical to the size of ACCESS_ALLOWED_OBJECT_ACE." );


    class AccessDeniedObjectAccessControlEntry : public ObjectAccessControlEntryBase<ACCESS_DENIED_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<ACCESS_DENIED_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessDeniedObjectAccessControlEntry ) == sizeof( ACCESS_DENIED_OBJECT_ACE ), "The size of AccessDeniedObjectAccessControlEntry must be identical to the size of ACCESS_DENIED_OBJECT_ACE." );

    class SystemAuditObjectAccessControlEntry : public ObjectAccessControlEntryBase<SYSTEM_AUDIT_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<SYSTEM_AUDIT_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAuditObjectAccessControlEntry ) == sizeof( SYSTEM_AUDIT_OBJECT_ACE ), "The size of SystemAuditObjectAccessControlEntry must be identical to the size of SYSTEM_AUDIT_OBJECT_ACE." );

    class SystemAlarmObjectAccessControlEntry : public ObjectAccessControlEntryBase<SYSTEM_ALARM_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<SYSTEM_ALARM_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAlarmObjectAccessControlEntry ) == sizeof( SYSTEM_ALARM_OBJECT_ACE ), "The size of SystemAlarmObjectAccessControlEntry must be identical to the size of SYSTEM_ALARM_OBJECT_ACE." );


    class AccessAllowedCallbackAccessControlEntry : public AccessControlEntryBase<ACCESS_ALLOWED_CALLBACK_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<ACCESS_ALLOWED_CALLBACK_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessAllowedCallbackAccessControlEntry ) == sizeof( ACCESS_ALLOWED_CALLBACK_ACE ), "The size of AccessAllowedCallbackAccessControlEntry must be identical to the size of ACCESS_ALLOWED_CALLBACK_ACE." );

    class AccessDeniedCallbackAccessControlEntry : public AccessControlEntryBase<ACCESS_DENIED_CALLBACK_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<ACCESS_DENIED_CALLBACK_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessDeniedCallbackAccessControlEntry ) == sizeof( ACCESS_DENIED_CALLBACK_ACE ), "The size of AccessDeniedCallbackAccessControlEntry must be identical to the size of ACCESS_DENIED_CALLBACK_ACE." );

    class SystemAuditCallbackAccessControlEntry : public AccessControlEntryBase<SYSTEM_AUDIT_CALLBACK_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_AUDIT_CALLBACK_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAuditCallbackAccessControlEntry ) == sizeof( SYSTEM_AUDIT_CALLBACK_ACE ), "The size of SystemAuditCallbackAccessControlEntry must be identical to the size of ACCESS_DENIED_CALLBACK_ACE." );

    class SystemAlarmCallbackAccessControlEntry : public AccessControlEntryBase<SYSTEM_ALARM_CALLBACK_ACE, AccessMask>
    {
    public:
        using Base = AccessControlEntryBase<SYSTEM_ALARM_CALLBACK_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAlarmCallbackAccessControlEntry ) == sizeof( SYSTEM_ALARM_CALLBACK_ACE ), "The size of SystemAlarmCallbackAccessControlEntry must be identical to the size of SYSTEM_ALARM_CALLBACK_ACE." );

    class AccessAllowedCallbackObjectAccessControlEntry : public ObjectAccessControlEntryBase<ACCESS_ALLOWED_CALLBACK_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<ACCESS_ALLOWED_CALLBACK_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessAllowedCallbackObjectAccessControlEntry ) == sizeof( ACCESS_ALLOWED_CALLBACK_OBJECT_ACE ), "The size of AccessAllowedCallbackObjectAccessControlEntry must be identical to the size of ACCESS_ALLOWED_CALLBACK_OBJECT_ACE." );


    class AccessDeniedCallbackObjectAccessControlEntry : public ObjectAccessControlEntryBase<ACCESS_DENIED_CALLBACK_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<ACCESS_DENIED_CALLBACK_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( AccessDeniedCallbackObjectAccessControlEntry ) == sizeof( ACCESS_DENIED_CALLBACK_OBJECT_ACE ), "The size of AccessDeniedCallbackObjectAccessControlEntry must be identical to the size of ACCESS_DENIED_CALLBACK_OBJECT_ACE." );

    class SystemAuditCallbackObjectAccessControlEntry : public ObjectAccessControlEntryBase<SYSTEM_AUDIT_CALLBACK_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<SYSTEM_AUDIT_CALLBACK_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAuditCallbackObjectAccessControlEntry ) == sizeof( SYSTEM_AUDIT_CALLBACK_OBJECT_ACE ), "The size of SystemAuditCallbackObjectAccessControlEntry must be identical to the size of SYSTEM_AUDIT_CALLBACK_OBJECT_ACE." );

    class SystemAlarmCallbackObjectAccessControlEntry : public ObjectAccessControlEntryBase<SYSTEM_ALARM_CALLBACK_OBJECT_ACE, AccessMask>
    {
    public:
        using Base = ObjectAccessControlEntryBase<SYSTEM_ALARM_CALLBACK_OBJECT_ACE, AccessMask>;
        static constexpr DWORD HeaderSize = sizeof( Base ) - sizeof( DWORD );
    private:

    };

    static_assert( sizeof( SystemAlarmCallbackObjectAccessControlEntry ) == sizeof( SYSTEM_ALARM_CALLBACK_OBJECT_ACE ), "The size of SystemAlarmCallbackObjectAccessControlEntry must be identical to the size of SYSTEM_ALARM_CALLBACK_OBJECT_ACE." );


    using AccessAllowedACE = AccessAllowedAccessControlEntry;
    using AccessDeniedACE = AccessDeniedAccessControlEntry;
    using SystemAuditACE = SystemAuditAccessControlEntry;
    using SystemAlarmACE = SystemAlarmAccessControlEntry;
    using SystemResourceAttributeACE = SystemResourceAttributeAccessControlEntry;
    using SystemScopedPolicyIdACE = SystemScopedPolicyIdAccessControlEntry;
    using SystemMandatoryLabelACE = SystemMandatoryLabelAccessControlEntry;
    using SystemProcessTrustLabelACE = SystemProcessTrustLabelAccessControlEntry;
    using SystemAccessFilterACE = SystemAccessFilterAccessControlEntry;
    using AccessAllowedObjectACE = AccessAllowedObjectAccessControlEntry;
    using AccessDeniedObjectACE = AccessDeniedObjectAccessControlEntry;
    using SystemAuditObjectACE = SystemAuditObjectAccessControlEntry;
    using SystemAlarmObjectACE = SystemAlarmObjectAccessControlEntry;
    using AccessAllowedCallbackACE = AccessAllowedCallbackAccessControlEntry;
    using AccessDeniedCallbackACE = AccessDeniedCallbackAccessControlEntry;
    using SystemAuditCallbackACE = SystemAuditCallbackAccessControlEntry;
    using SystemAlarmCallbackACE = SystemAlarmCallbackAccessControlEntry;
    using AccessAllowedCallbackObjectACE = AccessAllowedCallbackObjectAccessControlEntry;
    using AccessDeniedCallbackObjectACE = AccessDeniedCallbackObjectAccessControlEntry;
    using SystemAuditCallbackObjectACE = SystemAuditCallbackObjectAccessControlEntry;
    using SystemAlarmCallbackObjectACE = SystemAlarmCallbackObjectAccessControlEntry;



#pragma pack(pop)

    /// <summary>
    /// A wrapper class for Windows ACLs.
    /// </summary>
    class AccessControlList
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        using size_type = DWORD;
        static constexpr DWORD AllocationGranularity = 4096;
        static constexpr DWORD AclRevision = ACL_REVISION;
        static constexpr DWORD AclRevisionDS = ACL_REVISION_DS;
        static constexpr DWORD AclRevisionDefault = AclRevisionDS;
    private:
        ACL* acl_;
        ReleaseMethod releaseMethod_;
        DWORD revision_;

        static constexpr size_type AllocationByteCount( size_type requiredBufferSize ) noexcept
        {
            return requiredBufferSize ? ( requiredBufferSize + ( AllocationGranularity - 1 ))  & ~( AllocationGranularity - 1 ) : 0;
        }
        constexpr bool OwnsACL( ) const noexcept
        {
            return acl_? releaseMethod_ != ReleaseMethod::None : false;
        }
        void ThrowOwnershipRequiredException( const wchar_t* message, const wchar_t* function, const wchar_t* file, int lineNumber )
        {
            Security::Internal::ThrowOwnershipRequiredException( message, function, file, lineNumber );
        }
        void ThrowInvalidOperationException( const wchar_t* message, const wchar_t* function, const wchar_t* file, int lineNumber )
        {
            Security::Internal::ThrowInvalidOperationException( message, function, file, lineNumber );
        }

    public:
        constexpr AccessControlList( DWORD revision = AclRevisionDefault ) noexcept
            : acl_(nullptr), releaseMethod_( ReleaseMethod::None ), revision_( revision )
        { }

        explicit AccessControlList( ACL* acl, bool ownsACL = false ) noexcept
            : acl_( acl ), releaseMethod_( ownsACL? ReleaseMethod::Delete : ReleaseMethod::None ), revision_( GetRevision( acl ) )
        {
        }

        explicit AccessControlList( ACL* acl, ReleaseMethod releaseMethod ) noexcept
            : acl_( acl ), releaseMethod_( releaseMethod ), revision_( GetRevision( acl ) )
        {
        }

        AccessControlList( const AccessControlList& other ) = delete;
        constexpr AccessControlList( AccessControlList&& other ) noexcept
            : acl_( other.acl_ ), releaseMethod_( other.releaseMethod_ ), revision_( other.revision_ )
        {
            other.acl_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
            revision_ = AclRevisionDefault;
        }


        ~AccessControlList( )
        {
            ReleaseACL( );
        }

        AccessControlList& operator = ( const AccessControlList& other ) = delete;
        constexpr AccessControlList& operator = ( AccessControlList&& other ) noexcept
        {
            std::swap( acl_, other.acl_ );
            std::swap( releaseMethod_, other.releaseMethod_);
            return *this;
        }

        void Assign( ACL* acl, ReleaseMethod releaseMethod = ReleaseMethod::None )
        {
            if ( acl != acl_ )
            {
                ReleaseACL( );
                if ( acl )
                {
                    acl_ = acl;
                    releaseMethod_ = releaseMethod;
                    revision_ = GetRevision( acl );
                }
            }
        }


        ACL_SIZE_INFORMATION GetSizeInformation( ) const
        {
            ACL_SIZE_INFORMATION info{};
            if ( acl_ )
            {
                auto rc = GetAclInformation( acl_, &info, sizeof( ACL_SIZE_INFORMATION ), AclSizeInformation );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
            return info;
        }

        ACL_REVISION_INFORMATION GetRevisionInformation( ) const
        {
            ACL_REVISION_INFORMATION info{};
            if ( acl_ )
            {
                auto rc = GetAclInformation( acl_, &info, sizeof( ACL_REVISION_INFORMATION ), AclRevisionInformation );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
            return info;
        }

        static ACL_REVISION_INFORMATION GetRevisionInformation( PACL acl )
        {
            ACL_REVISION_INFORMATION info{};
            if ( acl )
            {
                auto rc = GetAclInformation( acl, &info, sizeof( ACL_REVISION_INFORMATION ), AclRevisionInformation );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
            return info;
        }


        size_type Count( ) const
        {
            auto info = GetSizeInformation( );
            return info.AceCount;
        }
        size_type size( ) const
        {
            return Count( );
        }

        size_type BytesFree( ) const
        {
            auto info = GetSizeInformation( );
            return info.AclBytesFree;
        }
        size_type BytesInUse( ) const
        {
            auto info = GetSizeInformation( );
            return info.AclBytesInUse;
        }
        constexpr DWORD Revision( ) const noexcept
        {
            return revision_;
        }
        DWORD GetRevision( ) const
        {
            auto info = GetRevisionInformation( );
            return info.AclRevision;
        }
        static DWORD GetRevision( PACL acl )
        {
            auto info = GetRevisionInformation( acl );
            return info.AclRevision;
        }

    private:
        void ReleaseACL( )
        {
            if ( acl_ )
            {
                if ( releaseMethod_ == ReleaseMethod::Delete )
                {
                    delete[] (Byte*)acl_;
                }
                else if ( releaseMethod_ == ReleaseMethod::LocalFree )
                {
                    LocalFree( acl_ );
                }
            }
            acl_ = nullptr;
            releaseMethod_ = ReleaseMethod::None;
            revision_ = AclRevisionDefault;
        }

        size_type BytesRequiredFor( size_type headerSize, const SecurityId& securityId )
        {
            auto sidLength = securityId.Length( );
            auto result = headerSize + sidLength;
            return result;
        }
        void InitACL( size_type minBytesRequired )
        {
            size_type allocationByteCount = AllocationByteCount( minBytesRequired );
            ACL* ptr = ( ACL* )new Byte[allocationByteCount];
            auto rc = InitializeAcl( ptr, allocationByteCount, revision_ );
            if ( !rc )
            {
                delete[] (Byte*)ptr;
                ThrowLastOSError( );
            }
            releaseMethod_ = ReleaseMethod::Delete;
            acl_ = ptr;
        }
        void ReallocateACL( size_type minAdditionalBytesRequired )
        {
            if ( OwnsACL( ) == false )
            {
                ThrowOwnershipRequiredException( L"ReallocateACL cannot resize an ACL that is not owned by the AccessControlList.", CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            minAdditionalBytesRequired = ( minAdditionalBytesRequired + ( sizeof( DWORD ) - 1 ) ) & 0xfffffffc;

            auto sizeInformation = GetSizeInformation( );
            if ( sizeInformation.AclBytesFree < minAdditionalBytesRequired )
            {
                size_type allocationByteCount = AllocationByteCount( sizeInformation.AclBytesInUse + minAdditionalBytesRequired );

                ACL* ptr = ( ACL* )new Byte[allocationByteCount];
                auto rc = InitializeAcl( ptr, allocationByteCount, revision_ );
                if ( !rc )
                {
                    delete[] (Byte*)ptr;
                    ThrowLastOSError( );
                }
                if ( sizeInformation.AceCount )
                {
                    Byte* firstAce = nullptr;
                    rc = GetAce( acl_, 0, (void**)&firstAce );
                    if ( !rc )
                    {
                        delete[] (Byte*)ptr;
                        ThrowLastOSError( );
                    }
                    DWORD acesByteCount = sizeInformation.AclBytesInUse - static_cast<DWORD>( firstAce - reinterpret_cast<Byte*>( acl_ ) );
                    rc = AddAce( ptr, revision_, MAXDWORD, firstAce, acesByteCount );
                    if ( !rc )
                    {
                        delete[] (Byte*)ptr;
                        ThrowLastOSError( );
                    }
                }
                auto tmp = acl_;
                acl_ = ptr;
                delete[] (Byte*)tmp;
            }
        }

    public:
        static AccessControlList Clone( const ACL* acl )
        {
            ACL_SIZE_INFORMATION sizeInfo{};
            ACL_REVISION_INFORMATION revisionInfo{ ACL_REVISION_DS };
            if ( acl )
            {
                auto rc = GetAclInformation( (PACL)acl, &sizeInfo, sizeof( ACL_SIZE_INFORMATION ), AclSizeInformation );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                rc = GetAclInformation( (PACL)acl, &revisionInfo, sizeof( ACL_REVISION_INFORMATION ), AclRevisionInformation );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            
                DWORD requiredSize = AllocationByteCount( sizeInfo.AclBytesInUse );
                auto ptr = std::make_unique<Byte[]>( requiredSize );
                rc = InitializeAcl( (PACL)ptr.get( ), requiredSize, revisionInfo.AclRevision );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                if ( sizeInfo.AceCount )
                {
                    Byte* firstAce = nullptr;
                    rc = GetAce( (PACL)acl, 0, (void**)&firstAce );
                    if ( !rc )
                    {
                        ThrowLastOSError( );
                    }
                    DWORD acesByteCount = sizeInfo.AclBytesInUse - static_cast<DWORD>( firstAce - reinterpret_cast<const Byte*>( acl ) );
                    rc = AddAce( (PACL)ptr.get( ), revisionInfo.AclRevision, MAXDWORD, firstAce, acesByteCount );
                    if ( !rc )
                    {
                        ThrowLastOSError( );
                    }
                }
                AccessControlList result( (ACL*)ptr.release( ), true );
                return result;
            }
            else
            {
                return AccessControlList( );
            }
        }

        AccessControlList Clone( ) const
        {
            return Clone( acl_ );
        }



        void AddAccessAllowed(const SecurityId& securityId, const AccessMask& accessMask )
        {
            using ACEType = AccessAllowedACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAccessAllowedAce( acl_, revision_, accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAccessAllowedAce( acl_, revision_, accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }
        void AddAccessAllowed( const SecurityId& securityId, AccessControlEntryFlags flags, const AccessMask& accessMask )
        {
            using ACEType = AccessAllowedACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAccessAllowedAceEx( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAccessAllowedAceEx( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAccessAllowedObject( const SecurityId& securityId, AccessControlEntryFlags flags, const AccessMask& accessMask, GUID* objectTypeGuid, GUID* inheritedObjectTypeGuid )
        {
            using ACEType = AccessAllowedObjectACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAccessAllowedObjectAce( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), objectTypeGuid, inheritedObjectTypeGuid, const_cast<SID*>( securityId.Value( ) ) );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAccessAllowedObjectAce( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), objectTypeGuid, inheritedObjectTypeGuid, const_cast<SID*>( securityId.Value( ) ) );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAccessDenied( const SecurityId& securityId, const AccessMask& accessMask )
        {
            using ACEType = AccessDeniedACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAccessDeniedAce( acl_, revision_, accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAccessDeniedAce( acl_, revision_, accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAccessDenied( const SecurityId& securityId, AccessControlEntryFlags flags, const AccessMask& accessMask )
        {
            using ACEType = AccessDeniedACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAccessDeniedAceEx( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAccessDeniedAceEx( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ) );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAccessDeniedObject( const SecurityId& securityId, AccessControlEntryFlags flags, const AccessMask& accessMask, GUID* objectTypeGuid, GUID* inheritedObjectTypeGuid )
        {
            using ACEType = AccessDeniedObjectACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAccessDeniedObjectAce( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), objectTypeGuid, inheritedObjectTypeGuid, const_cast<SID*>( securityId.Value( ) ) );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAccessDeniedObjectAce( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), objectTypeGuid, inheritedObjectTypeGuid, const_cast<SID*>( securityId.Value( ) ) );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAuditAccess( const SecurityId& securityId, const AccessMask& accessMask, bool auditSuccess, bool auditFailure )
        {
            using ACEType = SystemAuditACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAuditAccessAce( acl_, revision_, accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ), auditSuccess, auditFailure );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAuditAccessAce( acl_, revision_, accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ), auditSuccess, auditFailure );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAuditAccess( const SecurityId& securityId, AccessControlEntryFlags flags, const AccessMask& accessMask, bool auditSuccess, bool auditFailure )
        {
            using ACEType = SystemAuditACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAuditAccessAceEx( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ), auditSuccess, auditFailure );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAuditAccessAceEx( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), const_cast<SID*>( securityId.Value( ) ), auditSuccess, auditFailure );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void AddAuditAccessObject( const SecurityId& securityId, AccessControlEntryFlags flags, const AccessMask& accessMask, GUID* objectTypeGuid, GUID* inheritedObjectTypeGuid, bool auditSuccess, bool auditFailure )
        {
            using ACEType = SystemAuditObjectACE;
            constexpr size_type headerSize = ACEType::HeaderSize;
            if ( !acl_ )
            {
                size_type bytesRequired = BytesRequiredFor( sizeof( ACL ) + headerSize, securityId );
                InitACL( bytesRequired );
            }
            auto rc = ::AddAuditAccessObjectAce( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), objectTypeGuid, inheritedObjectTypeGuid, const_cast<SID*>( securityId.Value( ) ), auditSuccess, auditFailure );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error == ERROR_ALLOTTED_SPACE_EXCEEDED )
                {
                    size_type additionalBytesRequired = BytesRequiredFor( headerSize, securityId );
                    ReallocateACL( additionalBytesRequired );
                    rc = ::AddAuditAccessObjectAce( acl_, revision_, static_cast<DWORD>( flags ), accessMask.Value( ), objectTypeGuid, inheritedObjectTypeGuid, const_cast<SID*>( securityId.Value( ) ), auditSuccess, auditFailure );
                }
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
        }
    };

    /// <summary>
    /// A wrapper for the Windows PRIVILEGE_SET data type
    /// with a C++ container style interface 
    /// </summary>
    class PrivilegeSet
    {
    public:
        using size_type = DWORD;
        using pointer = LUID_AND_ATTRIBUTES*;
        using const_pointer = const LUID_AND_ATTRIBUTES*;
        using iterator = pointer;
        using const_iterator = const_pointer;
    private:
        static constexpr size_t LuidAndAttributesSize = sizeof( LUID_AND_ATTRIBUTES );
        static constexpr size_t PrivilegeSetSize = sizeof( PRIVILEGE_SET );
        static constexpr size_t HeaderSize = PrivilegeSetSize - LuidAndAttributesSize;
        PRIVILEGE_SET* data_;
        // This must be maintained outside the PRIVILEGE_SET too
        // because functions such as AccessCheck may/will PrivilegeCount 
        // set to the number of entries assigned to the Privilege array.
        // capacity_ is the number of available slots in Privilege array.
        size_type capacity_;
    public:
        constexpr PrivilegeSet( ) noexcept
            : data_( nullptr ), capacity_( 0 )
        {
        }

        PrivilegeSet( size_type privilegeCount ) 
            : data_( Allocate( privilegeCount ) ), capacity_( privilegeCount )
        {
        }

        PrivilegeSet( const PrivilegeSet& other ) = delete;

        constexpr PrivilegeSet( PrivilegeSet&& other ) noexcept
            : data_( other.data_ ), capacity_( other.capacity_ )
        {
            other.data_ = nullptr;
            other.capacity_ = 0;
        }

        ~PrivilegeSet( )
        {
            if ( data_ )
            {
                delete[] (Byte*)data_;
            }
        }

        PrivilegeSet& operator = ( const PrivilegeSet& other ) = delete;
        constexpr PrivilegeSet& operator = ( PrivilegeSet&& other ) noexcept
        {
            std::swap( data_, other.data_ ); 
            std::swap( capacity_, other.capacity_ );
            return *this;
        }


    private:
        static PRIVILEGE_SET* Allocate( size_type privilegeCount )
        {
            PRIVILEGE_SET* result = privilegeCount ? ( PRIVILEGE_SET* )new Byte[BufferSizeFor( privilegeCount )] : nullptr;
            if ( result )
            {
                result->PrivilegeCount = 0;
                result->Control = 0;
            }
            return result;
        }
    public:
        constexpr operator bool( ) const noexcept
        {
            return data_ != nullptr;
        }

        iterator begin( )
        {
            return data_->Privilege;
        }
        iterator end( )
        {
            return &data_->Privilege[data_->PrivilegeCount];
        }
        const_iterator begin( ) const
        {
            return data_->Privilege;
        }
        const_iterator end( ) const
        {
            return &data_->Privilege[data_->PrivilegeCount];
        }
        const_iterator cbegin( ) const
        {
            return data_->Privilege;
        }
        const_iterator cend( ) const
        {
            return &data_->Privilege[data_->PrivilegeCount];
        }

        /// <summary>
        /// Indicates that all of the specified privileges must be 
        /// held by the process requesting access. If this flag is 
        /// not set, the presence of any privileges in the user's 
        /// access token grants the access.
        /// </summary>
        bool AllAreRequired( ) const
        {
            return data_->Control == PRIVILEGE_SET_ALL_NECESSARY;
        }

        /// <summary>
        /// Indicates that all of the specified privileges must be 
        /// held by the process requesting access. If this flag is 
        /// not set, the presence of any privileges in the user's 
        /// access token grants the access.
        /// </summary>
        void SetAllAreRequired( bool value = true )
        {
            data_->Control = value? PRIVILEGE_SET_ALL_NECESSARY : 0;
        }



        const PRIVILEGE_SET* data( ) const
        {
            return data_;
        }
        PRIVILEGE_SET* data( )
        {
            return data_;
        }


        LUID_AND_ATTRIBUTES& operator[]( size_type index )
        {
            return data_->Privilege[index];
        }
        const LUID_AND_ATTRIBUTES& operator[]( size_type index ) const
        {
            return data_->Privilege[index];
        }



        constexpr static size_type BufferSizeFor( size_type privilegeCount ) noexcept
        {
            return HeaderSize + ( privilegeCount * LuidAndAttributesSize );
        }

        constexpr size_type size( ) const noexcept
        {
            return data_? data_->PrivilegeCount:0;
        }

        constexpr size_type capacity( ) const noexcept
        {
            return capacity_;
        }



        constexpr size_type BufferSize( ) const noexcept
        {
            return BufferSizeFor( capacity_ );
        }

    };


    enum class SecurityDescriptorControl : WORD
    {
        None = 0,
        /// <summary>
        /// This boolean flag, when set, indicates that the
        /// SID pointed to by the Owner field was provided by a
        /// defaulting mechanism rather than explicitly provided by the
        /// original provider of the security descriptor.  This may
        /// affect the treatment of the SID with respect to inheritence
        /// of an owner.
        /// </summary>
        OwnerDefaulted = SE_OWNER_DEFAULTED,
        /// <summary>
        /// This boolean flag, when set, indicates that the
        /// SID in the Group field was provided by a defaulting mechanism
        /// rather than explicitly provided by the original provider of
        /// the security descriptor.  This may affect the treatment of
        /// the SID with respect to inheritence of a primary group.
        /// </summary>
        GroupDefaulted = SE_GROUP_DEFAULTED,
        /// <summary>
        /// This boolean flag, when set, indicates that the
        /// security descriptor contains a discretionary ACL.  If this
        /// flag is set and the Dacl field of the SECURITY_DESCRIPTOR is
        /// null, then a null ACL is explicitly being specified.
        /// </summary>
        DaclPresent = SE_DACL_PRESENT,
        /// <summary>
        /// This boolean flag, when set, indicates that the
        /// ACL pointed to by the Dacl field was provided by a defaulting
        /// mechanism rather than explicitly provided by the original
        /// provider of the security descriptor.  This may affect the
        /// treatment of the ACL with respect to inheritence of an ACL.
        /// This flag is ignored if the DaclPresent flag is not set.
        /// </summary>
        DaclDefaulted = SE_DACL_DEFAULTED,
        /// <summary>
        /// This boolean flag, when set,  indicates that the
        /// security descriptor contains a system ACL pointed to by the
        /// Sacl field.  If this flag is set and the Sacl field of the
        /// SECURITY_DESCRIPTOR is null, then an empty (but present)
        /// ACL is being specified.
        /// </summary>
        SaclPresent = SE_SACL_PRESENT,
        /// <summary>
        /// This boolean flag, when set, indicates that the
        /// ACL pointed to by the Sacl field was provided by a defaulting
        /// mechanism rather than explicitly provided by the original
        /// provider of the security descriptor.  This may affect the
        /// treatment of the ACL with respect to inheritence of an ACL.
        /// This flag is ignored if the SaclPresent flag is not set.
        /// </summary>
        SaclDefaulted = SE_SACL_DEFAULTED,
        /// <summary>
        /// Indicates a required security descriptor in which the discretionary 
        /// access control list (DACL) is set up to support automatic propagation 
        /// of inheritable access control entries (ACEs) to existing child objects.
        /// </summary>
        DaclAutoInheritRequired = SE_DACL_AUTO_INHERIT_REQ,
        /// <summary>
        /// Indicates a required security descriptor in which the system access 
        /// control list (SACL) is set up to support automatic propagation of 
        /// inheritable ACEs to existing child objects.
        /// </summary>
        SaclAutoInheritRequired = SE_SACL_AUTO_INHERIT_REQ,
        DaclAutoInherited = SE_DACL_AUTO_INHERITED,
        SaclAutoInherited = SE_SACL_AUTO_INHERITED,
        DaclProtected = SE_DACL_PROTECTED,
        SaclProtected = SE_SACL_PROTECTED,
        /// <summary>
        /// The resource manager control bits are eight bits in the Sbz1 
        /// member of the SECURITY_DESCRIPTOR structure that contains 
        /// information specific to the resource manager accessing the structure.
        /// </summary>
        ResourceManagerControlValid = SE_RM_CONTROL_VALID,
        /// <summary>
        /// Indicates a self-relative security descriptor. If this flag is 
        /// not set, the security descriptor is in absolute format.
        /// </summary>
        SelfRelative = SE_SELF_RELATIVE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SecurityDescriptorControl, WORD );



    class Token;
    /// <summary>
    /// A wrapper for the Windows SECURITY_DESCRIPTOR/SECURITY_DESCRIPTOR_RELATIVE
    /// structures.
    /// </summary>
    class SecurityDescriptor
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
    private:
        union
        {
            SECURITY_DESCRIPTOR* securityDescriptor_;
            SECURITY_DESCRIPTOR_RELATIVE* securityDescriptorRelative_;
        };
        ReleaseMethod releaseMethod_;
        UInt32 size_;
    public:
        constexpr SecurityDescriptor() noexcept
            : securityDescriptor_(nullptr), releaseMethod_( ReleaseMethod::None ), size_(0)
        { }

        constexpr SecurityDescriptor( SECURITY_DESCRIPTOR* securityDescriptor, ReleaseMethod releaseMethod, UInt32 size ) noexcept
            : securityDescriptor_( securityDescriptor ), releaseMethod_( releaseMethod ), size_( size )
        {
        }


        SecurityDescriptor( const SecurityDescriptor& other ) = delete;
        SecurityDescriptor( SecurityDescriptor&& other ) noexcept
            : securityDescriptor_( other.securityDescriptor_ ), releaseMethod_( other.releaseMethod_ ), size_( other.size_ )
        {
            other.securityDescriptor_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
            other.size_ = 0;
        }
        ~SecurityDescriptor( )
        {
            FreeSecurityDescriptor( );
        }
    private:
        void FreeSecurityDescriptor( )
        {
            if ( securityDescriptor_ )
            {
                switch ( releaseMethod_ )
                {
                    case ReleaseMethod::LocalFree:
                        LocalFree( securityDescriptor_ );
                        break;
                    case ReleaseMethod::Delete:
                        delete[] (Byte*)securityDescriptor_;
                        break;
                    case ReleaseMethod::DestroyPrivateObjectSecurity:
                        DestroyPrivateObjectSecurity( (PSECURITY_DESCRIPTOR*)&securityDescriptor_ );
                        break;
                }
            }
            securityDescriptor_ = nullptr;
        }
        
    public:
        SecurityDescriptor& operator = ( const SecurityDescriptor& other ) = delete;
        SecurityDescriptor& operator = ( SecurityDescriptor&& other ) noexcept
        {
            std::swap( securityDescriptor_, other.securityDescriptor_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            std::swap( size_, other.size_ );
            return* this;
        }

        /// <summary>
        /// retrieves a security descriptor control
        /// </summary>
        /// <returns>security descriptor control</returns>
        SecurityDescriptorControl Control( ) const
        {
            if ( securityDescriptor_ )
            {
                return static_cast<SecurityDescriptorControl>(securityDescriptor_->Control);
            }
            else
            {
                return SecurityDescriptorControl::None;
            }
        }
        void SetControl( SecurityDescriptorControl controlBitsOfInterest, SecurityDescriptorControl controlBitsToSet )
        {
            auto rc = SetSecurityDescriptorControl( securityDescriptor_, static_cast<SECURITY_DESCRIPTOR_CONTROL>( controlBitsOfInterest ), static_cast<SECURITY_DESCRIPTOR_CONTROL>( controlBitsToSet ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        void SetControl( SecurityDescriptorControl control )
        {
            SetControl( control, control );
        }

        /// <summary>
        /// Returns the length, in bytes, of a structurally valid security 
        /// descriptor. The length includes the length of all associated structures.
        /// </summary>
        /// <returns>the length</returns>
        DWORD Length( ) const
        {
            if ( securityDescriptor_ )
            {
                return GetSecurityDescriptorLength( securityDescriptor_ );
            }
            else
            {
                return 0;
            }
        }

        bool IsEmpty( ) const
        {
            return Length( ) <= SECURITY_DESCRIPTOR_MIN_LENGTH;
        }


        /// <summary>
        /// Retrieves the owner information from the security descriptor.
        /// </summary>
        /// <returns>The SecurityId of the owner</returns>
        Security::SecurityId Owner( ) const
        {
            if ( securityDescriptor_ )
            {
                BOOL ownerDefaulted = FALSE;
                PSID owner = nullptr;
                auto rc = GetSecurityDescriptorOwner( securityDescriptor_, &owner, &ownerDefaulted );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                return Security::SecurityId( owner );
            }
            else
            {
                return Security::SecurityId( );
            }
        }

        /// <summary>
        /// Retrieves the primary group information from the security descriptor.
        /// </summary>
        /// <returns>The SecurityId of the primary group</returns>
        Security::SecurityId Group( ) const
        {
            if ( securityDescriptor_ )
            {
                BOOL groupDefaulted = FALSE;
                PSID group = nullptr;
                auto rc = GetSecurityDescriptorGroup( securityDescriptor_, &group, &groupDefaulted );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                return Security::SecurityId( group );
            }
            else
            {
                return Security::SecurityId( );
            }
        }


        bool GetDacl( Security::AccessControlList& accessControlList, bool* daclDefaulted = nullptr ) const
        {
            if ( securityDescriptor_ )
            {
                BOOL hasDacl = FALSE;
                BOOL bDaclDefaulted = FALSE;
                PACL acl = nullptr;
                auto rc = GetSecurityDescriptorDacl( securityDescriptor_, &hasDacl, &acl, &bDaclDefaulted );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                if ( hasDacl )
                {
                    accessControlList.Assign( acl );
                    if ( daclDefaulted )
                    {
                        *daclDefaulted = bDaclDefaulted;
                    }
                    return true;
                }
                else
                {
                    accessControlList.Assign( nullptr );
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        Security::AccessControlList Dacl( ) const
        {
            Security::AccessControlList result;
            GetDacl( result );
            return result;
        }

        bool GetSacl( Security::AccessControlList& accessControlList, bool* saclDefaulted = nullptr ) const
        {
            if ( securityDescriptor_ )
            {
                BOOL hasSacl = FALSE;
                BOOL bSaclDefaulted = FALSE;
                PACL acl = nullptr;
                auto rc = GetSecurityDescriptorSacl( securityDescriptor_, &hasSacl, &acl, &bSaclDefaulted );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                if ( hasSacl )
                {
                    accessControlList.Assign( acl );
                    if ( saclDefaulted )
                    {
                        *saclDefaulted = bSaclDefaulted;
                    }
                    return true;
                }
                else
                {
                    accessControlList.Assign( nullptr );
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        Security::AccessControlList Sacl( ) const
        {
            Security::AccessControlList result;
            GetSacl( result );
            return result;
        }


        template<typename Reader>
        void Read( Reader& reader )
        {
            FreeSecurityDescriptor( );
            auto size = reader.ReadUInt32( );
            if ( size )
            {
                Byte* buffer = new Byte[size];
                reader.Read( buffer, size );
                releaseMethod_ = ReleaseMethod::Delete;
                size_ = size;
                securityDescriptor_ = (SECURITY_DESCRIPTOR*)buffer;
            }
        }

        template<typename Writer>
        void Write( Writer& writer ) const
        {
            if ( securityDescriptor_ )
            {
                if ( IsRelative( ) )
                {
                    UInt32 size = size_;
                    writer.Write( size );
                    if ( size )
                    {
                        writer.Write( securityDescriptor_, size );
                    }
                }
                else
                {
                    auto selfRelative = this->ToSelfRelative( );
                    selfRelative.Write( writer );
                }
            }
            else
            {
                writer.Write( static_cast<UInt32>( 0 ) );
            }
        }

        SecurityDescriptor Clone( ) const
        {
            if ( securityDescriptor_ )
            {
                if ( IsRelative( ) )
                {
                    auto newBufferPtr = new Byte[size_];
                    memcpy( newBufferPtr, securityDescriptor_, size_ );
                    SecurityDescriptor result( (SECURITY_DESCRIPTOR*)newBufferPtr, ReleaseMethod::Delete, size_ );
                    return result;
                }
                else
                {
                    return ToSelfRelative( );
                }
            }
            else
            {
                return SecurityDescriptor( );
            }
        }


        bool IsRelative( ) const
        {
            if ( securityDescriptor_ )
            {
                auto control = Control( );
                return (control & SecurityDescriptorControl::SelfRelative) != SecurityDescriptorControl::None;
            }
            else
            {
                return false;
            }
        }

        constexpr SECURITY_DESCRIPTOR* Descriptor( ) noexcept
        {
            return securityDescriptor_;
        }

        constexpr const SECURITY_DESCRIPTOR* Descriptor( ) const noexcept
        {
            return securityDescriptor_;
        }

        constexpr SECURITY_DESCRIPTOR_RELATIVE* DescriptorRelative( ) noexcept
        {
            return securityDescriptorRelative_;
        }
        constexpr const SECURITY_DESCRIPTOR_RELATIVE* DescriptorRelative( ) const noexcept
        {
            return securityDescriptorRelative_;
        }

        SecurityDescriptor ToSelfRelative( ) const
        {
            if ( securityDescriptor_ )
            {
                char buffer[4096];
                DWORD bufferSize = 4096;
                SECURITY_DESCRIPTOR* selfRelative = (SECURITY_DESCRIPTOR*)(char*)buffer;

                auto rc = MakeSelfRelativeSD( securityDescriptor_, selfRelative, &bufferSize );
                if ( !rc )
                {
                    auto error = GetLastError( );
                    if ( error != ERROR_INSUFFICIENT_BUFFER )
                    {
                        ThrowOSError( error );
                    }
                    selfRelative = (SECURITY_DESCRIPTOR*)new Byte[bufferSize];
                    if ( !selfRelative )
                    {
                        ThrowLastOSError( );
                    }
                    rc = MakeSelfRelativeSD( securityDescriptor_, selfRelative, &bufferSize );
                    if ( !rc )
                    {
                        ThrowLastOSError( );
                    }
                    SecurityDescriptor result( selfRelative, ReleaseMethod::Delete, bufferSize );
                    return result;
                }
                else
                {
                    auto length = GetSecurityDescriptorLength( selfRelative );
                    auto newSelfRelative = (SECURITY_DESCRIPTOR*)new Byte[bufferSize];
                    if ( !newSelfRelative )
                    {
                        ThrowLastOSError( );
                    }
                    memcpy( newSelfRelative, selfRelative, length );
                    SecurityDescriptor result( newSelfRelative, ReleaseMethod::Delete, length );
                    return result;
                }
            }
            else
            {
                return SecurityDescriptor( );
            }
        }

    private:
        HANDLE HandleOf( const Token& clientToken ) const;
    public:

        /// <summary>
        /// The AccessCheck function determines whether a security descriptor 
        /// grants a specified set of access rights to the client identified by 
        /// an access token. Typically, server applications use this function 
        /// to check access to a private object.
        /// </summary>
        /// <param name="clientToken">
        /// A handle to an impersonation token that represents the client that 
        /// is attempting to gain access. The handle must have TOKEN_QUERY 
        /// access to the token; otherwise, the function fails with ERROR_ACCESS_DENIED.</param>
        /// <param name="desiredAccessMask">
        /// <p>
        /// Access mask that specifies the access rights to check. This mask must 
        /// have been mapped by the MapGenericMask function to contain no generic 
        /// access rights.
        /// </p>
        /// <p>
        /// If this parameter is MAXIMUM_ALLOWED, the function sets the GrantedAccess 
        /// access mask to indicate the maximum access rights the security 
        /// descriptor allows the client.
        /// </p>
        /// </param>
        /// <param name="genericMapping">
        /// A reference to the GenericMapping object matching with the object for 
        /// which access is being checked.
        /// </param>
        /// <param name="privilegeSet">
        /// A reference to a PrivilegeSet object that receives the privileges used 
        /// to perform the access validation. If no privileges were used, the 
        /// function sets the PrivilegeCount to zero.
        /// </param>
        /// <param name="grantedAccess">
        /// A reference to an access mask that receives the granted access rights. 
        /// If the function return false, the function sets the access mask to zero. 
        /// </param>
        /// <returns>true if the access check succeeded.</returns>
        bool AccessCheck( const Token& clientToken, const AccessMask& desiredAccessMask, const GenericMapping& genericMapping, PrivilegeSet& privilegeSet, AccessMask& grantedAccess ) const
        {
            BOOL accessStatus = FALSE;
            BOOL rc = 0;
            DWORD grantedAccessValue = 0;

            if ( privilegeSet )
            {
                auto privilegeSetBufferSize = privilegeSet.BufferSize( );
                rc = ::AccessCheck( securityDescriptor_, HandleOf( clientToken ), desiredAccessMask.Value( ), const_cast<GENERIC_MAPPING*>( genericMapping.dataPtr( ) ), privilegeSet.data( ), &privilegeSetBufferSize, &grantedAccessValue, &accessStatus );
            }
            else
            {
                auto privilegeSetBufferSize = privilegeSet.BufferSize( );
                rc = ::AccessCheck( securityDescriptor_, HandleOf( clientToken ), desiredAccessMask.Value( ), const_cast<GENERIC_MAPPING*>( genericMapping.dataPtr( ) ), nullptr, nullptr, &grantedAccessValue, &accessStatus );
            }
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            grantedAccess = grantedAccessValue;
            return accessStatus != 0;
        }

    };

    /// <summary>
    /// A wrapper for the Windows SECURITY_ATTRIBUTES
    /// struc.
    /// </summary>
    class SecurityAttributes : public SECURITY_ATTRIBUTES
    {
    public:
        using Base = SECURITY_ATTRIBUTES;

        constexpr SecurityAttributes( bool inheritHandle = false ) noexcept
            : Base{ sizeof( SECURITY_ATTRIBUTES ), nullptr, inheritHandle }
        {
        }

        constexpr SecurityAttributes( const SECURITY_DESCRIPTOR& securityDescriptor, bool inheritHandle = false ) noexcept
            : Base{ sizeof( SECURITY_ATTRIBUTES ), const_cast<SECURITY_DESCRIPTOR*>(&securityDescriptor ), inheritHandle }
        {
        }

        constexpr SecurityAttributes( const SecurityDescriptor& securityDescriptor, bool inheritHandle = false ) noexcept
            : Base{ sizeof( SECURITY_ATTRIBUTES ), const_cast<SECURITY_DESCRIPTOR*>( securityDescriptor.Descriptor( ) ), inheritHandle }
        {
        }



    };

    /// <summary>
    /// Specifies the access rights for a Windows access token.
    /// </summary>
    enum class TokenAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        AssignPrimary = TOKEN_ASSIGN_PRIMARY,
        Duplicate = TOKEN_DUPLICATE,
        Impersonate = TOKEN_IMPERSONATE,
        Query = TOKEN_QUERY,
        QuerySource = TOKEN_QUERY_SOURCE,
        AdjustPrivileges = TOKEN_ADJUST_PRIVILEGES,
        AdjustGroups = TOKEN_ADJUST_GROUPS,
        AdjustDefault = TOKEN_ADJUST_DEFAULT,
        AdjustSessionId = TOKEN_ADJUST_SESSIONID,
        AccessPseudoHandle = TOKEN_ACCESS_PSEUDO_HANDLE,
        Read = TOKEN_READ,
        Write = TOKEN_WRITE,
        Execute = TOKEN_EXECUTE,
        FullControl = TOKEN_ALL_ACCESS
    };

    /// <summary>
    /// An access mask implmentation for the access rights of
    /// a Windows access token
    /// </summary>
    class TokenAccessMask : public Security::AccessMaskT<TokenAccessMask, TokenAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<TokenAccessMask, TokenAccessRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( TokenAccessRights::Read ) ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( TokenAccessRights::Write ) ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( TokenAccessRights::Execute ) ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( TokenAccessRights::FullControl ) ) };

        constexpr TokenAccessMask( ) noexcept
        {
        }
        constexpr explicit TokenAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit TokenAccessMask( TokenAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit TokenAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit TokenAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit TokenAccessMask( const TokenAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit TokenAccessMask( const TokenAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit TokenAccessMask( TokenAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit TokenAccessMask( TokenAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }


        constexpr bool CanAssignPrimary( ) const noexcept
        {
            return Check<TokenAccessRights::AssignPrimary>( );
        }
        constexpr void SetAssignPrimary( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::AssignPrimary>( value );
        }

        constexpr bool CanDuplicate( ) const noexcept
        {
            return Check<TokenAccessRights::Duplicate>( );
        }
        constexpr void SetDuplicate( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::Duplicate>( value );
        }

        constexpr bool CanImpersonate( ) const noexcept
        {
            return Check<TokenAccessRights::Impersonate>( );
        }
        constexpr void SetImpersonate( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::Impersonate>( value );
        }

        constexpr bool CanQuery( ) const noexcept
        {
            return Check<TokenAccessRights::Query>( );
        }
        constexpr void SetQuery( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::Query>( value );
        }

        constexpr bool CanQuerySource( ) const noexcept
        {
            return Check<TokenAccessRights::QuerySource>( );
        }
        constexpr void SetQuerySource( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::QuerySource>( value );
        }

        constexpr bool CanAdjustPrivileges( ) const noexcept
        {
            return Check<TokenAccessRights::AdjustPrivileges>( );
        }
        constexpr void SetAdjustPrivileges( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::AdjustPrivileges>( value );
        }

        constexpr bool CanAdjustGroups( ) const noexcept
        {
            return Check<TokenAccessRights::AdjustGroups>( );
        }
        constexpr void SetAdjustGroups( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::AdjustGroups>( value );
        }

        constexpr bool CanAdjustDefault( ) const noexcept
        {
            return Check<TokenAccessRights::AdjustDefault>( );
        }
        constexpr void SetAdjustDefault( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::AdjustDefault>( value );
        }

        constexpr bool CanAdjustSessionId( ) const noexcept
        {
            return Check<TokenAccessRights::AdjustSessionId>( );
        }
        constexpr void SetAdjustSessionId( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::AdjustSessionId>( value );
        }

        constexpr bool CanAccessPseudoHandle( ) const noexcept
        {
            return Check<TokenAccessRights::AccessPseudoHandle>( );
        }
        constexpr void SetAccessPseudoHandle( bool value = true ) noexcept
        {
            SetBitFlag<TokenAccessRights::AccessPseudoHandle>( value );
        }
    };


    struct TokenUser : TOKEN_USER
    {
        using Base = TOKEN_USER;
    };

#pragma pack(push,8)
    /// <summary>
    /// A binary compatibel replacement for SID_AND_ATTRIBUTES
    /// for the TokenGroups implementation
    /// </summary>
    struct TokenGroup
    {
        PSID Sid;
        GroupFlags Flags;

        TokenGroup()
            : Sid( nullptr ), Flags( GroupFlags::None )
        { }

        Security::SecurityId SecurityId( ) const
        {
            return Security::SecurityId( Sid );
        }

    };

    static_assert( sizeof( TokenGroup ) == sizeof( SID_AND_ATTRIBUTES ), "Do not add any data members to TokenGroup" );

    /// <summary>
    /// A wrapper/binary compatible replacement 
    /// for the Windows TOKEN_GROUPS type with
    /// a C++ container style interface
    /// </summary>
    class TokenGroups
    { 
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        using pointer = TokenGroup*;
        using reference = TokenGroup&;
        using const_pointer = const TokenGroup*;
        using const_reference = const TokenGroup&;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using size_type = size_t;

        struct Data
        {
            using pointer = TokenGroup*;
            using reference = TokenGroup&;
            using const_pointer = const TokenGroup*;
            using const_reference = const TokenGroup&;
            using iterator = pointer;
            using const_iterator = const_pointer;
            using size_type = size_t;

            DWORD GroupCount;
            TokenGroup Groups[ANYSIZE_ARRAY];

            size_t size( ) const
            {
                return GroupCount;
            }

            iterator begin( )
            {
                return (iterator)Groups;
            }
            const_iterator begin( ) const
            {
                return (const_iterator)Groups;
            }
            const_iterator cbegin( ) const
            {
                return (const_iterator)Groups;
            }

            iterator end( )
            {
                return (iterator)&Groups[GroupCount];
            }
            const_iterator end( ) const
            {
                return (const_iterator)&Groups[GroupCount];
            }
            const_iterator cend( ) const
            {
                return static_cast<const_iterator>( &Groups[GroupCount] );
            }

            reference at( size_t index )
            {
                return Groups[index];
            }
            const_reference at( size_t index ) const
            {
                return Groups[index];
            }

        };
    private:
        Data* data_;
        ReleaseMethod releaseMethod_;
    public:
        constexpr TokenGroups( ) noexcept
            : data_(nullptr), releaseMethod_( ReleaseMethod::None )
        { }

        constexpr TokenGroups( Data* data, ReleaseMethod releaseMethod = ReleaseMethod::Delete ) noexcept
            : data_( data ), releaseMethod_( releaseMethod )
        {
        }

        TokenGroups( const TokenGroups& other ) = delete;
        TokenGroups( TokenGroups&& other ) noexcept
            : data_( other.data_ ), releaseMethod_(other.releaseMethod_)
        {
            other.data_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~TokenGroups( )
        {
            if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
            {
                delete[] (Byte*) data_;
            }
        }

        TokenGroups& operator = ( const TokenGroups& other ) = delete;
        TokenGroups& operator = ( TokenGroups&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }

        size_type size( ) const
        {
            return data_ ? data_->size( ) : 0;
        }

        iterator begin( )
        {
            return data_ ? data_->begin( ) : nullptr;
        }
        const_iterator begin( ) const
        {
            return data_ ? data_->begin( ) : nullptr;
        }
        const_iterator cbegin( ) const
        {
            return data_ ? data_->cbegin( ) : nullptr;
        }
        iterator end( )
        {
            return data_ ? data_->end( ) : nullptr;
        }
        const_iterator end( ) const
        {
            return data_ ? data_->end( ) : nullptr;
        }
        const_iterator cend( ) const
        {
            return data_ ? data_->cend( ) : nullptr;
        }

        reference at( size_type index )
        {
            return data_->at( index );
        }
        const_reference at( size_type index ) const
        {
            return data_->at( index );
        }
        reference operator[]( size_type index )
        {
            return data_->at( index );
        }
        const_reference operator[]( size_type index ) const
        {
            return data_->at( index );
        }


    };
#pragma pack(pop)
    static_assert( sizeof( TokenGroups::Data ) == sizeof( TOKEN_GROUPS ), "Do not add any data members to TokenGroups::Data" );

    /// <summary>
    /// The attributes of a privilege can be a combination of the following values.
    /// </summary>
    enum class TokenPrivilegeFlags : DWORD
    {
        /// <summary>
        /// The privilege is enabled by default.
        /// </summary>
        EnabledByDefault = SE_PRIVILEGE_ENABLED_BY_DEFAULT,
        Enabled = SE_PRIVILEGE_ENABLED,
        Removed = SE_PRIVILEGE_REMOVED,
        UsedForAccess = SE_PRIVILEGE_USED_FOR_ACCESS,
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TokenPrivilegeFlags, DWORD );

#pragma pack(push,4)
    /// <summary>
    /// A binary compatible replacement for the
    /// Windows LUID_AND_ATTRIBUTES for use with
    /// the TokenPrivileges class.
    /// </summary>
    struct TokenPrivilege
    {
        LocalUniqueId Privilege;
        TokenPrivilegeFlags Flags;
    };

    static_assert( sizeof( TokenPrivilege ) == sizeof( LUID_AND_ATTRIBUTES ), "Do not add any new data members to the TokenPrivilege class" );

    /// <summary>
    /// A wrapper/binary compatible replacement for
    /// the TOKEN_PRIVILEGES type with a C++ container
    /// style interface.
    /// </summary>
    class TokenPrivileges
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        using pointer = TokenPrivilege*;
        using reference = TokenPrivilege&;
        using const_pointer = const TokenPrivilege*;
        using const_reference = const TokenPrivilege&;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using size_type = size_t;

        struct Data
        { 
            DWORD PrivilegeCount;
            TokenPrivilege Privileges[ANYSIZE_ARRAY];
        public:
            size_t size( ) const
            {
                return PrivilegeCount;
            }

            iterator begin( )
            {
                return (iterator)Privileges;
            }
            const_iterator begin( ) const
            {
                return (const_iterator)Privileges;
            }
            const_iterator cbegin( ) const
            {
                return (const_iterator)Privileges;
            }

            iterator end( )
            {
                return (iterator)&Privileges[PrivilegeCount];
            }
            const_iterator end( ) const
            {
                return (const_iterator)&Privileges[PrivilegeCount];
            }
            const_iterator cend( ) const
            {
                return static_cast<const_iterator>( &Privileges[PrivilegeCount] );
            }

            reference at( size_t index )
            {
                return Privileges[index];
            }
            const_reference at( size_t index ) const
            {
                return Privileges[index];
            }

        };
    private:
        Data* data_;
        ReleaseMethod releaseMethod_;
    public:
        constexpr TokenPrivileges( ) noexcept
            : data_( nullptr ), releaseMethod_( ReleaseMethod::None )
        {
        }

        constexpr TokenPrivileges( Data* data, ReleaseMethod releaseMethod = ReleaseMethod::Delete ) noexcept
            : data_( data ), releaseMethod_( releaseMethod )
        {
        }

        TokenPrivileges( const TokenPrivileges& other ) = delete;
        TokenPrivileges( TokenPrivileges&& other ) noexcept
            : data_( other.data_ ), releaseMethod_(other.releaseMethod_)
        {
            other.data_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~TokenPrivileges( )
        {
            if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
            {
                delete[]( Byte* ) data_;
            }
        }

        TokenPrivileges& operator = ( const TokenPrivileges& other ) = delete;
        TokenPrivileges& operator = ( TokenPrivileges&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }

        Data* data( )
        {
            return data_;
        }
        const Data* data( ) const
        {
            return data_;
        }
        void Assign( Data* data, ReleaseMethod releaseMethod = ReleaseMethod::Delete )
        {
            if ( data != data_ )
            {
                if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
                {
                    delete[]( Byte* ) data_;
                }
            }
            data_ = data;
            releaseMethod_ = releaseMethod;
        }




        size_type size( ) const
        {
            return data_ ? data_->size( ) : 0;
        }

        iterator begin( )
        {
            return data_ ? data_->begin( ) : nullptr;
        }
        const_iterator begin( ) const
        {
            return data_ ? data_->begin( ) : nullptr;
        }
        const_iterator cbegin( ) const
        {
            return data_ ? data_->cbegin( ) : nullptr;
        }
        iterator end( )
        {
            return data_ ? data_->end( ) : nullptr;
        }
        const_iterator end( ) const
        {
            return data_ ? data_->end( ) : nullptr;
        }
        const_iterator cend( ) const
        {
            return data_ ? data_->cend( ) : nullptr;
        }

        reference at( size_type index )
        {
            return data_->at( index );
        }
        const_reference at( size_type index ) const
        {
            return data_->at( index );
        }
        reference operator[]( size_type index )
        {
            return data_->at( index );
        }
        const_reference operator[]( size_type index ) const
        {
            return data_->at( index );
        }
    };
    static_assert( sizeof( TokenPrivileges::Data ) == sizeof( TOKEN_PRIVILEGES ), "Do not add any new data members to the TokenPrivileges::Data class" );

    struct TokenSource
    {
        std::array<char, TOKEN_SOURCE_LENGTH> SourceName;
        LocalUniqueId SourceIdentifier;
    };
    static_assert( sizeof( TokenSource ) == sizeof( TOKEN_SOURCE ), "Do not add any new data members to the TokenSource struct" );

    /// <summary>
    /// A binary compatible replacement for
    /// the Windows TOKEN_STATISTICS type using
    /// the types defined here.
    /// </summary>
    struct TokenStatistics
    {
        LocalUniqueId TokenId;
        LocalUniqueId AuthenticationId;
        Int64 ExpirationTime;
        TokenType TokenType;
        Security::ImpersonationLevel ImpersonationLevel;
        DWORD DynamicCharged;
        DWORD DynamicAvailable;
        DWORD GroupCount;
        DWORD PrivilegeCount;
        LocalUniqueId ModifiedId;
    };
    static_assert( sizeof( TokenStatistics ) == sizeof( TOKEN_STATISTICS ), "Do not add any new data members to the TokenStatistics struct" );

    /// <summary>
    /// A Wrapper/binary compatible replacement for
    /// the Windows TOKEN_GROUPS_AND_PRIVILEGES type.
    /// </summary>
    class TokenGroupsAndPrivileges
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        struct Data
        {
            DWORD SidCount;
            DWORD SidLength;
            SecurityIdAndFlags* Sids;
            DWORD RestrictedSidCount;
            DWORD RestrictedSidLength;
            SecurityIdAndFlags* RestrictedSids;
            DWORD PrivilegeCount;
            DWORD PrivilegeLength;
            TokenPrivilege* Privileges;
            LocalUniqueId AuthenticationId;
        };

        using SecurityIdAndFlagsContainer = std::span<SecurityIdAndFlags>;
        using TokenPrivilegeContainer = std::span<TokenPrivilege>;
        

    private:
        Data* data_;
        ReleaseMethod releaseMethod_;
    public:
        TokenGroupsAndPrivileges()
            : data_(nullptr), releaseMethod_( ReleaseMethod::None )
        { }

        /// <summary>
        /// Initializes a new TokenGroupsAndPrivileges object,
        /// taking ownership of the TOKEN_GROUPS_AND_PRIVILEGES
        /// structure.
        /// </summary>
        /// <param name="pTOKEN_GROUPS_AND_PRIVILEGES">
        /// Pointer to the TOKEN_GROUPS_AND_PRIVILEGES structure
        /// </param>
        /// <remarks>
        /// The memory allocated for the TOKEN_GROUPS_AND_PRIVILEGES structure
        /// will be released using <code>delete[] (Byte*) data_;</code>
        /// </remarks>
        TokenGroupsAndPrivileges( TOKEN_GROUPS_AND_PRIVILEGES* pTOKEN_GROUPS_AND_PRIVILEGES, ReleaseMethod releaseMethod = ReleaseMethod::Delete )
            : data_( reinterpret_cast<Data*>( pTOKEN_GROUPS_AND_PRIVILEGES ) ), releaseMethod_( releaseMethod )
        {
        }

        TokenGroupsAndPrivileges( const TokenGroupsAndPrivileges& other ) = delete;
        TokenGroupsAndPrivileges( TokenGroupsAndPrivileges&& other ) noexcept
            : data_( other.data_ ), releaseMethod_( other.releaseMethod_ )
        {
            other.data_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~TokenGroupsAndPrivileges( )
        {
            if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
            {
                delete[]( Byte* ) data_;
            }
        }

        TokenGroupsAndPrivileges& operator = ( const TokenGroupsAndPrivileges& other ) = delete;
        TokenGroupsAndPrivileges& operator = ( TokenGroupsAndPrivileges&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }


        DWORD SidCount( ) const noexcept
        {
            return data_ ? data_->SidCount : 0;
        }
        DWORD SidLength( ) const noexcept
        {
            return data_ ? data_->SidLength : 0;
        }
        SecurityIdAndFlagsContainer Sids( ) const noexcept
        {
            return data_ ? SecurityIdAndFlagsContainer( data_->Sids , data_->SidCount ) : SecurityIdAndFlagsContainer();
        }
        DWORD RestrictedSidCount( ) const noexcept
        {
            return data_ ? data_->RestrictedSidCount : 0;
        }
        DWORD RestrictedSidLength( ) const noexcept
        {
            return data_ ? data_->RestrictedSidLength : 0;
        }
        SecurityIdAndFlagsContainer RestrictedSids( ) const noexcept
        {
            return data_ ? SecurityIdAndFlagsContainer( data_->RestrictedSids, data_->RestrictedSidCount ) : SecurityIdAndFlagsContainer( );
        }
        DWORD PrivilegeCount( ) const noexcept
        {
            return data_ ? data_->PrivilegeCount : 0;
        }
        DWORD PrivilegeLength( ) const noexcept
        {
            return data_ ? data_->PrivilegeLength : 0;
        }
        TokenPrivilegeContainer Privileges( ) const noexcept
        {
            return data_ ? TokenPrivilegeContainer( data_->Privileges, data_->PrivilegeCount ) : TokenPrivilegeContainer( );
        }
        LocalUniqueId AuthenticationId( ) const noexcept
        {
            return data_ ? data_->AuthenticationId : LocalUniqueId();
        }


    };

    static_assert( sizeof( TokenGroupsAndPrivileges::Data ) == sizeof( TOKEN_GROUPS_AND_PRIVILEGES ), "Do not add any new data members to the TokenGroupsAndPrivileges::Data struct" );


#pragma pack(pop)


    /// <summary>
    /// Additional privilege options used when creating a 
    /// restricted token.
    /// </summary>
    enum class TokenFlags : DWORD
    {
        /// <summary>
        /// Disables all privileges in the new token except the 
        /// SeChangeNotifyPrivilege privilege. If this value is 
        /// specified, the DeletePrivilegeCount and PrivilegesToDelete 
        /// parameters are ignored.
        /// </summary>
        DisableMaxPrivilege = DISABLE_MAX_PRIVILEGE,
        /// <summary>
        /// If this value is used, the system does not 
        /// check AppLocker rules or apply Software Restriction Policies. 
        /// For AppLocker, this flag disables checks for all four rule 
        /// collections: Executable, Windows Installer, Script, and DLL.
        /// 
        /// When creating a setup program that must run extracted DLLs 
        /// during installation, use the flag SAFER_TOKEN_MAKE_INERT in 
        /// the SaferComputeTokenFromLevel function.
        /// 
        /// A token can be queried for existence of this flag by using 
        /// the Token::SandboxInert() function.
        /// </summary>
        SandboxInert = SANDBOX_INERT,
        LuaToken = LUA_TOKEN,
        WriteRestricted = WRITE_RESTRICTED
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TokenFlags, DWORD );

    /// <summary>
    /// Indicates the elevation type of token
    /// </summary>
    enum class TokenElevationType
    {
        Unknown = 0,
        /// <summary>
        /// The token does not have a linked token.
        /// </summary>
        Default = TokenElevationTypeDefault,
        /// <summary>
        /// The token is an elevated token.
        /// </summary>
        Full = TokenElevationTypeFull,
        /// <summary>
        /// The token is a limited token.
        /// </summary>
        Limited = TokenElevationTypeLimited
    };


    /// <summary>
    /// A wrapper for the Windows PSID_AND_ATTRIBUTES_HASH type.
    /// </summary>
    class SecurityIdsAndFlagsWithHash
    {
        PSID_AND_ATTRIBUTES_HASH data_;
    public:
        using pointer = SecurityIdAndFlags*;
        using const_pointer = const SecurityIdAndFlags*;
        using reference = SecurityIdAndFlags&;
        using const_reference = const SecurityIdAndFlags&;
        using size_type = DWORD;

        constexpr SecurityIdsAndFlagsWithHash() noexcept
            : data_(nullptr)
        { }

        constexpr SecurityIdsAndFlagsWithHash(PSID_AND_ATTRIBUTES_HASH data ) noexcept
            : data_( data )
        {
        }

        size_type size( ) const
        {
            return data_ ? data_->SidCount : 0;
        }

    };


    /// <summary>
    /// The mandatory integrity access policy for the associated token.
    /// </summary>
    enum class TokenMandatoryPolicy : DWORD
    {
        /// <summary>
        /// No mandatory integrity policy is enforced for the token.
        /// </summary>
        Off = TOKEN_MANDATORY_POLICY_OFF,
        /// <summary>
        /// A process associated with the token cannot write to 
        /// objects that have a greater mandatory integrity level.
        /// </summary>
        NoWriteUp = TOKEN_MANDATORY_POLICY_NO_WRITE_UP,
        /// <summary>
        /// A process created with the token has an integrity 
        /// level that is the lesser of the parent-process 
        /// integrity level and the executable-file integrity level.
        /// </summary>
        NewProcessMin = TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN
    };


    /// <summary>
    /// A wrapper/binary compatible replacement for
    /// the Windows TOKEN_ACCESS_INFORMATION type.
    /// </summary>
    class TokenAccessInformation
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        struct Data
        {
            PSID_AND_ATTRIBUTES_HASH SidHash;
            PSID_AND_ATTRIBUTES_HASH RestrictedSidHash;
            PTOKEN_PRIVILEGES Privileges;
            LUID AuthenticationId;
            TOKEN_TYPE TokenType;
            SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
            TOKEN_MANDATORY_POLICY MandatoryPolicy;
            DWORD Flags;
            DWORD AppContainerNumber;
            PSID PackageSid;
            PSID_AND_ATTRIBUTES_HASH CapabilitiesHash;
            PSID TrustLevelSid;
            PSECURITY_ATTRIBUTES SecurityAttributes;
        };
    private:
        Data* data_;
        ReleaseMethod releaseMethod_;
    public:
        TokenAccessInformation( )
            : data_( nullptr ), releaseMethod_( ReleaseMethod::None )
        {
        }

        TokenAccessInformation( TOKEN_ACCESS_INFORMATION* pTOKEN_ACCESS_INFORMATION, ReleaseMethod releaseMethod = ReleaseMethod::Delete )
            : data_( reinterpret_cast<Data*>( pTOKEN_ACCESS_INFORMATION ) ), releaseMethod_( releaseMethod )
        {
        }

        TokenAccessInformation( const TokenAccessInformation& other ) = delete;
        TokenAccessInformation( TokenAccessInformation&& other ) noexcept
            : data_( other.data_ ), releaseMethod_( other.releaseMethod_ )
        {
            other.data_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~TokenAccessInformation( )
        {
            if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
            {
                delete[]( Byte* ) data_;
            }
        }

        TokenAccessInformation& operator = ( const TokenAccessInformation& other ) = delete;
        TokenAccessInformation& operator = ( TokenAccessInformation&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }

        /// <summary>
        /// Retrieves SecurityIdsAndFlagsWithHash object that specifies 
        /// a hash of the token's security identifier (SID)
        /// </summary>
        /// <returns>A Security::SecurityIdsAndFlagsWithHash object</returns>
        Security::SecurityIdsAndFlagsWithHash SidHash( ) const
        {
            return data_ ? Security::SecurityIdsAndFlagsWithHash( data_->SidHash ) : Security::SecurityIdsAndFlagsWithHash( );
        }

        /// <summary>
        /// Retrieves SecurityIdsAndFlagsWithHash object that specifies 
        /// a hash of the token's restricted SID
        /// </summary>
        /// <returns>A Security::SecurityIdsAndFlagsWithHash object</returns>
        SecurityIdsAndFlagsWithHash RestrictedSidHash( ) const
        {
            return data_ ? Security::SecurityIdsAndFlagsWithHash( data_->RestrictedSidHash ) : Security::SecurityIdsAndFlagsWithHash( );
        }

        /// <summary>
        /// Returns that TokenPrivileges object that provides 
        /// access to information about the token's privileges.
        /// </summary>
        /// <returns>A Security::TokenPrivileges object</returns>
        Security::TokenPrivileges Privileges( ) const
        {
            return data_ ? Security::TokenPrivileges( (Security::TokenPrivileges::Data*)data_->Privileges ) : Security::TokenPrivileges();
        }

        /// <summary>
        /// Returns LocalUniqueId that represents 
        /// the token's identity.
        /// </summary>
        /// <returns></returns>
        LocalUniqueId AuthenticationId( ) const
        {
            return data_ ? LocalUniqueId( data_->AuthenticationId ): LocalUniqueId();
        }

        /// <summary>
        /// A value of the Security::TokenType enumeration that 
        /// specifies the token's type
        /// </summary>
        /// <returns>A Security::TokenType value</returns>
        Security::TokenType TokenType( ) const
        {
            return data_ ? static_cast<Security::TokenType>( data_->TokenType ) : Security::TokenType::Unknown;
        }

        /// <summary>
        /// A value of the Security::ImpersonationLevel enumeration 
        /// that specifies the token's impersonation level.
        /// </summary>
        /// <returns>A Security::ImpersonationLevel value</returns>
        Security::ImpersonationLevel ImpersonationLevel( ) const
        {
            return data_ ? static_cast<Security::ImpersonationLevel>( data_->ImpersonationLevel ) : Security::ImpersonationLevel::Anonymous;
        }


        /// <summary>
        /// Returns the token's mandatory integrity policy.
        /// </summary>
        /// <returns></returns>
        Security::TokenMandatoryPolicy MandatoryPolicy( ) const
        {
            return data_ ? static_cast<Security::TokenMandatoryPolicy>( data_->MandatoryPolicy.Policy ) : Security::TokenMandatoryPolicy::Off;
        }


        DWORD Flags( ) const
        {
            return data_ ? data_->Flags : 0;
        }

        /// <summary>
        /// The app container number for the token or zero 
        /// if this is not an app container token.
        /// </summary>
        DWORD AppContainerNumber() const
        {
            return data_ ? data_->AppContainerNumber : 0;
        }

        /// <summary>
        /// The app container SID or NULL if 
        /// this is not an app container token
        /// </summary>
        SecurityId PackageSid() const
        {
            return data_ ? SecurityId( data_->PackageSid, Internal::ReleaseMethod::None ) : SecurityId();
        }

        /// <summary>
        /// Retrieves SecurityIdsAndFlagsWithHash object that specifies 
        /// a hash of the token's capability SIDs.
        /// </summary>
        /// <returns>A Security::SecurityIdsAndFlagsWithHash object</returns>
        Security::SecurityIdsAndFlagsWithHash CapabilitiesHash( ) const
        {
            return data_ ? Security::SecurityIdsAndFlagsWithHash( data_->CapabilitiesHash ) : Security::SecurityIdsAndFlagsWithHash( );
        }

        /// <summary>
        /// The protected process trust level of the token.
        /// </summary>
        SecurityId TrustLevelSid( ) const
        {
            return data_ ? SecurityId( data_->TrustLevelSid, Internal::ReleaseMethod::None ) : SecurityId( );
        }


    };
    static_assert( sizeof( TokenAccessInformation::Data ) == sizeof( TOKEN_ACCESS_INFORMATION ), "Do not add any new data members to the TokenAccessInformation::Data struct" );



    /// <summary>
    /// A wrapper for the Windows TOKEN_MANDATORY_LABEL type.
    /// </summary>
    class TokenMandatoryLabel
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        using Data = TOKEN_MANDATORY_LABEL;
    private:
        Data* data_;
        ReleaseMethod releaseMethod_;
    public:
        TokenMandatoryLabel( )
            : data_( nullptr ), releaseMethod_( ReleaseMethod::None )
        {
        }

        TokenMandatoryLabel( TOKEN_MANDATORY_LABEL* pTOKEN_MANDATORY_LABEL, ReleaseMethod releaseMethod = ReleaseMethod::Delete )
            : data_( reinterpret_cast<Data*>( pTOKEN_MANDATORY_LABEL ) ), releaseMethod_( releaseMethod )
        {
        }

        TokenMandatoryLabel( const TokenMandatoryLabel& other ) = delete;
        TokenMandatoryLabel( TokenMandatoryLabel&& other ) noexcept
            : data_( other.data_ ), releaseMethod_( other.releaseMethod_ )
        {
            other.data_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~TokenMandatoryLabel( )
        {
            if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
            {
                delete[]( Byte* ) data_;
            }
        }

        TokenMandatoryLabel& operator = ( const TokenMandatoryLabel& other ) = delete;
        TokenMandatoryLabel& operator = ( TokenMandatoryLabel&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }

        Security::SecurityId SecurityId( ) const
        {
            return data_? Security::SecurityId( data_->Label.Sid, Security::SecurityId::ReleaseMethod::None ): Security::SecurityId( );
        }

        constexpr PSID SID( ) const noexcept
        {
            return data_ ? data_->Label.Sid : nullptr;
        }

        constexpr GroupFlags Flags( ) const noexcept
        {
            return data_ ? static_cast<GroupFlags>( data_->Label.Attributes ) : GroupFlags::None;
        }

    };


    /// <summary>
    /// A wrapper for the Windows CLAIM_SECURITY_ATTRIBUTES_INFORMATION type
    /// </summary>
    class ClaimSecurityAttributesInformation
    {
    public:
        using ReleaseMethod = Security::Internal::ReleaseMethod;
        using Data = CLAIM_SECURITY_ATTRIBUTES_INFORMATION;
        using size_type = DWORD;
    private:
        Data* data_;
        ReleaseMethod releaseMethod_;
    public:
        ClaimSecurityAttributesInformation( )
            : data_( nullptr ), releaseMethod_( ReleaseMethod::None )
        {
        }

        ClaimSecurityAttributesInformation( CLAIM_SECURITY_ATTRIBUTES_INFORMATION* pCLAIM_SECURITY_ATTRIBUTES_INFORMATION, ReleaseMethod releaseMethod = ReleaseMethod::Delete )
            : data_( reinterpret_cast<Data*>( pCLAIM_SECURITY_ATTRIBUTES_INFORMATION ) ), releaseMethod_( releaseMethod )
        {
        }

        ClaimSecurityAttributesInformation( const ClaimSecurityAttributesInformation& other ) = delete;
        ClaimSecurityAttributesInformation( ClaimSecurityAttributesInformation&& other ) noexcept
            : data_( other.data_ ), releaseMethod_( other.releaseMethod_ )
        {
            other.data_ = nullptr;
            other.releaseMethod_ = ReleaseMethod::None;
        }

        ~ClaimSecurityAttributesInformation( )
        {
            if ( data_ && releaseMethod_ == ReleaseMethod::Delete )
            {
                delete[]( Byte* ) data_;
            }
        }

        ClaimSecurityAttributesInformation& operator = ( const ClaimSecurityAttributesInformation& other ) = delete;
        ClaimSecurityAttributesInformation& operator = ( ClaimSecurityAttributesInformation&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( releaseMethod_, other.releaseMethod_ );
            return *this;
        }

        size_type size( ) const
        {
            return data_ ? data_->AttributeCount : 0;
        }
    };


    enum class TokenMembershipFlags : DWORD
    {
        None = 0,
        IncludeAppcontainer = CTMF_INCLUDE_APPCONTAINER,
        IncludeLPAC = CTMF_INCLUDE_LPAC
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TokenMembershipFlags, DWORD );


    /// <summary>
    /// Represents a Windows access token 
    /// </summary>
    class Token
    {
        HANDLE handle_;
    public:
        static constexpr HANDLE InvalidHandle = 0;
        constexpr Token( ) noexcept
            : handle_( InvalidHandle )
        {
        }

        constexpr explicit Token( HANDLE handle ) noexcept
            : handle_( handle )
        {
        }

        Token( const Token& other ) = delete;
        constexpr Token( Token&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = InvalidHandle;
        }

        ~Token( )
        {
            Close( );
        }


        Token& operator = ( const Token& other ) = delete;
        Token& operator = ( Token&& other ) noexcept
        {
            std::swap( handle_, other.handle_ );
            return *this;
        }

        void Close( )
        {
            if ( handle_ != InvalidHandle )
            {
                CloseHandle( handle_ );
                handle_ = InvalidHandle;
            }
        }

        HANDLE Release( )
        {
            auto result = handle_;
            handle_ = InvalidHandle;
            return result;
        }

        HANDLE Handle( ) const
        {
            return handle_;
        }

        /// <summary>
        /// Determines whether the specified SecurityId is enabled in the token.
        /// </summary>
        /// <param name="securityId">
        /// The function checks for the presence of this SecurityId in the token.
        /// </param>
        /// <returns>true if the specified SecurityId was found.</returns>
        bool CheckMembership( const SecurityId& securityId ) const
        {
            BOOL isMember = 0;
            auto rc = CheckTokenMembership( handle_, (PSID)securityId.Value( ), &isMember );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return isMember;
        }

        /// <summary>
        /// Determines whether the specified SecurityId is enabled in the token.
        /// </summary>
        /// <param name="securityId">
        /// The function checks for the presence of this SecurityId in the token.
        /// </param>
        /// <param name="includeAppcontainer">
        /// Flag that affect the behavior of the function.
        /// </param>
        /// <returns>true if the specified SecurityId was found.</returns>
        bool CheckMembership( const SecurityId& securityId, bool includeAppcontainer ) const
        {
            BOOL isMember = 0;
            auto rc = CheckTokenMembershipEx( handle_, (PSID)securityId.Value( ), includeAppcontainer? CTMF_INCLUDE_APPCONTAINER:0,&isMember );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return isMember;
        }
        /// <summary>
        /// Determines whether the specified SecurityId is enabled in the token.
        /// </summary>
        /// <param name="securityId">
        /// The function checks for the presence of this SecurityId in the token.
        /// </param>
        /// <param name="flags">
        /// Flags that affect the behavior of the function
        /// </param>
        /// <returns></returns>
        bool CheckMembership( const SecurityId& securityId, TokenMembershipFlags flags ) const
        {
            BOOL isMember = 0;
            auto rc = CheckTokenMembershipEx( handle_, (PSID)securityId.Value( ), static_cast<DWORD>( flags ), &isMember );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return isMember;
        }

        /*
        void AdjustPrivileges( bool disableAllPrivileges, const Security::TokenPrivileges& newTokenPrivileges, Security::TokenPrivileges& previousTokenPrivileges ) const
        {
            auto rc = AdjustTokenPrivileges(handle_, disableAllPrivileges, (TOKEN_PRIVILEGES*)newTokenPrivileges.data(), )
        }
        */


        /// <summary>
        /// Creates a new access token that duplicates an existing token. 
        /// </summary>
        /// <param name="impersonationLevel"></param>
        /// <returns></returns>
        Token Duplicate( ImpersonationLevel impersonationLevel ) const
        {
            HANDLE duplicatedHandle = InvalidHandle;
            auto rc = DuplicateToken( handle_, static_cast<SECURITY_IMPERSONATION_LEVEL>( impersonationLevel ), &duplicatedHandle );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Token( duplicatedHandle );
        }
        /// <summary>
        /// Creates a new access token that duplicates an existing token. 
        /// This function can create either a primary token or an 
        /// impersonation token.
        /// </summary>
        /// <param name="desiredAccess">
        /// Specifies the requested access rights for the new token. Windows 
        /// compares the requested access rights with the existing token's 
        /// discretionary access control list (DACL) to determine which rights 
        /// are granted or denied. To request the same access rights as the 
        /// existing token, specify TokenAccessRights::None. To request all 
        /// access rights that are valid for the caller, specify 
        /// TokenAccessRights::MaximumAllowed
        /// </param>
        /// <param name="securityAttributes">
        /// A reference to a SECURITY_ATTRIBUTES structure that specifies a 
        /// security descriptor for the new token and determines whether 
        /// child processes can inherit the token. If the security descriptor 
        /// contains a system access control list (SACL), the token gets 
        /// TokenAccessRights::SystemSecurity access right, even if it was 
        /// not requested in desiredAccess.
        /// 
        /// To set the owner in the security descriptor for the new token, the 
        /// caller's process token must have the SE_RESTORE_NAME privilege set.
        /// </param>
        /// <param name="impersonationLevel">Specifies the implersonation level of the new token</param>
        /// <param name="tokenType">Specifies the tokentype of the new token</param>
        /// <returns>The new token</returns>
        Token Duplicate( TokenAccessMask desiredAccess, const SECURITY_ATTRIBUTES& securityAttributes, ImpersonationLevel impersonationLevel, TokenType tokenType ) const
        {
            
            HANDLE duplicatedHandle = InvalidHandle;
            const SECURITY_ATTRIBUTES* pSECURITY_ATTRIBUTES = &securityAttributes;
            auto rc = DuplicateTokenEx( handle_, desiredAccess.Value(), const_cast<SECURITY_ATTRIBUTES*>(pSECURITY_ATTRIBUTES), static_cast<SECURITY_IMPERSONATION_LEVEL>( impersonationLevel ), static_cast<TOKEN_TYPE>( tokenType ) ,&duplicatedHandle );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Token( duplicatedHandle );
        }
        /// <summary>
        /// Creates a new access token that duplicates an existing token. 
        /// This function can create either a primary token or an 
        /// impersonation token.
        /// </summary>
        /// <param name="desiredAccess">
        /// Specifies the requested access rights for the new token. Windows 
        /// compares the requested access rights with the existing token's 
        /// discretionary access control list (DACL) to determine which rights 
        /// are granted or denied. To request the same access rights as the 
        /// existing token, specify TokenAccessRights::None. To request all 
        /// access rights that are valid for the caller, specify 
        /// TokenAccessRights::MaximumAllowed
        /// </param>
        /// <param name="securityAttributes">
        /// A pointer to a SECURITY_ATTRIBUTES structure that specifies a 
        /// security descriptor for the new token and determines whether 
        /// child processes can inherit the token. If securityAttributes is 
        /// NULL, the token gets a default security descriptor and the 
        /// handle cannot be inherited. If the security descriptor 
        /// contains a system access control list (SACL), the token gets 
        /// TokenAccessRights::SystemSecurity access right, even if it was 
        /// not requested in desiredAccess.
        /// 
        /// To set the owner in the security descriptor for the new token, the 
        /// caller's process token must have the SE_RESTORE_NAME privilege set.
        /// </param>
        /// <param name="impersonationLevel">Specifies the implersonation level of the new token</param>
        /// <param name="tokenType">Specifies the tokentype of the new token</param>
        /// <returns>The new token</returns>
        Token Duplicate( TokenAccessMask desiredAccess, const SECURITY_ATTRIBUTES* securityAttributes, ImpersonationLevel impersonationLevel, TokenType tokenType ) const
        {
            
            HANDLE duplicatedHandle = InvalidHandle;
            auto rc = DuplicateTokenEx( handle_, desiredAccess.Value( ), const_cast<SECURITY_ATTRIBUTES*>( securityAttributes ), static_cast<SECURITY_IMPERSONATION_LEVEL>( impersonationLevel ), static_cast<TOKEN_TYPE>( tokenType ), &duplicatedHandle );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Token( duplicatedHandle );
        }


        /// <summary>
        /// The IsRestricted function indicates whether a token contains 
        /// a list of restricted security identifiers (SIDs).
        /// </summary>
        /// <returns>true if the token contains a list of restricting SIDs</returns>
        bool IsRestricted( ) const
        {
            auto rc = IsTokenRestricted( handle_ );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error )
                {
                    ThrowOSError( error );
                }
            }
            return rc != 0;
        }

        /// <summary>
        /// The IsUntrusted function indicates whether a token 
        /// is untrusted
        /// </summary>
        /// <returns>true id the token is untrusted</returns>
        bool IsUntrusted( ) const
        {
            auto rc = IsTokenUntrusted( handle_ );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error )
                {
                    ThrowOSError( error );
                }
            }
            return rc != 0;
        }

        /// <summary>
        /// Lets the calling thread impersonate the security context 
        /// of the user represented by the token.
        /// </summary>
        void Impersonate( ) const
        {
            auto rc = ImpersonateLoggedOnUser( handle_ );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


        size_t GetTokenInformation( TOKEN_INFORMATION_CLASS tokenInformationClass, void* buffer, size_t bufferSize ) const
        {
            DWORD returnLength = 0;
            auto rc = ::GetTokenInformation( handle_, tokenInformationClass, buffer, static_cast<DWORD>( bufferSize ), &returnLength );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return returnLength;
        }

        size_t GetTokenInformationSize( TOKEN_INFORMATION_CLASS tokenInformationClass ) const
        {
            DWORD returnLength = 0;
            auto rc = ::GetTokenInformation( handle_, tokenInformationClass, nullptr, 0, &returnLength );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error != ERROR_INSUFFICIENT_BUFFER )
                {
                    ThrowOSError( error );
                }
            }
            return returnLength;
        }

        /// <summary>
        /// Retrieves the SecurityId of the user account of the token
        /// </summary>
        /// <returns>A SecurityId object.</returns>
        Security::SecurityId User( ) const
        {
            constexpr size_t bufferSize = Security::SecurityId::MaxSize + sizeof( TOKEN_USER );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenUser, buffer.data( ), bufferSize );
            auto tokenUser = ( TokenUser* )buffer.data( );
            auto result = Security::SecurityId::Clone( tokenUser->User.Sid );
            return result;
        }

        /// <summary>
        /// Retrieves a TokenGroups object that contains the 
        /// group accounts associated with the token.
        /// </summary>
        /// <returns>A TokenGroups object</returns>
        Security::TokenGroups Groups( ) const
        {
            Security::TokenGroups::Data* data = nullptr;
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenGroups );
            data = ( Security::TokenGroups::Data* )new Byte[requiredSize];
            Security::TokenGroups result( data );
            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenGroups, data, requiredSize );
            return result;
        }


        /// <summary>
        /// Retrieves a TokenPrivileges object that 
        /// provides access to information about the 
        /// privileges of the token.
        /// </summary>
        /// <returns></returns>
        Security::TokenPrivileges Privileges( ) const
        {
            Security::TokenPrivileges::Data* data = nullptr;
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenPrivileges );
            data = ( Security::TokenPrivileges::Data* )new Byte[requiredSize];
            Security::TokenPrivileges result( data );
            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenPrivileges, data, requiredSize );
            return result;
        }

        /// <summary>
        /// Returns a SecurityId representing the user who will 
        /// become the owner of any objects created by a process 
        /// using this access token.
        /// </summary>
        /// <returns></returns>
        Security::SecurityId Owner( ) const
        {
            constexpr size_t bufferSize = Security::SecurityId::MaxSize + sizeof( TOKEN_OWNER );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenOwner, buffer.data( ), bufferSize );
            auto tokenOwner = (TOKEN_OWNER*)buffer.data( );
            auto result = Security::SecurityId::Clone( tokenOwner->Owner );
            return result;
        }

        /// <summary>
        /// Returns a SecurityId representing the group 
        /// that will become the primary group of any 
        /// objects created by a process using this access token.
        /// </summary>
        /// <returns></returns>
        Security::SecurityId PrimaryGroup( ) const
        {
            constexpr size_t bufferSize = Security::SecurityId::MaxSize + sizeof( TOKEN_PRIMARY_GROUP );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenPrimaryGroup, buffer.data( ), bufferSize );
            auto tokenPrimaryGroup = (TOKEN_PRIMARY_GROUP*)buffer.data( );
            auto result = Security::SecurityId::Clone( tokenPrimaryGroup->PrimaryGroup );
            return result;
        }

        /// <summary>
        /// Retrieves an AccessControlList object that contains 
        /// the default DACL for newly created objects
        /// </summary>
        /// <returns></returns>
        AccessControlList DefaultAccessControlList( ) const
        {
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenDefaultDacl );
            auto buffer = std::make_unique<Byte[]>( requiredSize );

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenDefaultDacl, buffer.get(), requiredSize );
            auto tokenDefaultDacl = (TOKEN_DEFAULT_DACL*)buffer.get( );
            AccessControlList result = AccessControlList::Clone( (ACL*)tokenDefaultDacl->DefaultDacl );

            return result;
        }
        AccessControlList DefaultDACL( ) const
        {
            return DefaultAccessControlList( );
        }

        /// <summary>
        /// Retrieves a TokenSource object that
        /// provides information about the source 
        /// of the token
        /// </summary>
        /// <returns></returns>
        TokenSource Source( ) const
        {
            constexpr size_t bufferSize = sizeof( TOKEN_SOURCE );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenSource, buffer.data( ), bufferSize );
            auto pTokenSource = (TokenSource*)buffer.data( );
            auto result = *pTokenSource;
            return result;
        }


        /// <summary>
        /// Retrieves the type of the token
        /// </summary>
        /// <returns></returns>
        TokenType Type( ) const
        {
            constexpr size_t bufferSize = sizeof( TOKEN_TYPE );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenType, buffer.data( ), bufferSize );
            auto pTokenType = (TokenType*)buffer.data( );
            auto result = *pTokenType;
            return result;
        }

        /// <summary>
        /// Returns true if this is a primary token
        /// </summary>
        /// <returns></returns>
        bool IsPrimaryToken( ) const
        {
            auto type = Type( );
            return type == TokenType::Primary;
        }

        /// <summary>
        /// Returns true if this is an impersonation token
        /// </summary>
        /// <returns></returns>
        bool IsImpersonationToken( ) const
        {
            auto type = Type( );
            return type == TokenType::Impersonation;
        }

        /// <summary>
        /// Retrives a value from the ImpersonationLevel enumeration
        /// that indicates the impersonation level of the token.
        /// 
        /// </summary>
        /// <returns>An ImpersonationLevel value</returns>
        Security::ImpersonationLevel ImpersonationLevel( ) const
        {
            constexpr size_t bufferSize = sizeof( SECURITY_IMPERSONATION_LEVEL );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenImpersonationLevel, buffer.data( ), bufferSize );
            auto pImpersonationLevel = (Security::ImpersonationLevel*)buffer.data( );
            auto result = *pImpersonationLevel;
            return result;
        }

        TokenStatistics Statistics( ) const
        {
            constexpr size_t bufferSize = sizeof( TokenStatistics );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenStatistics, buffer.data( ), bufferSize );
            auto pTokenStatistics = (Security::TokenStatistics*)buffer.data( );
            auto result = *pTokenStatistics;
            return result;
        }

        Security::TokenGroups RestrictedSecurityIds( ) const
        {
            Security::TokenGroups::Data* data = nullptr;
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenRestrictedSids );
            data = ( Security::TokenGroups::Data* )new Byte[requiredSize];
            Security::TokenGroups result( data );
            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenRestrictedSids, data, requiredSize );
            return result;
        }
        Security::TokenGroups RestrictedSids( ) const
        {
            return RestrictedSecurityIds( );
        }


        DWORD SessionId( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenSessionId, buffer.data( ), bufferSize );
            auto pSessionId = (DWORD*)buffer.data( );
            auto result = *pSessionId;
            return result;
        }

        TokenGroupsAndPrivileges GroupsAndPrivileges( ) const
        {
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenGroupsAndPrivileges );
            auto buffer = std::make_unique<Byte[]>( requiredSize );

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenGroupsAndPrivileges, buffer.get( ), requiredSize );
            TokenGroupsAndPrivileges result = TokenGroupsAndPrivileges( (TOKEN_GROUPS_AND_PRIVILEGES*)buffer.release( ) );

            return result;
        }

        bool SandBoxInert( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenSandBoxInert, buffer.data( ), bufferSize );
            auto pSandBoxInert = (DWORD*)buffer.data( );
            bool result = (*pSandBoxInert) != 0;
            return result;
        }

        /// <summary>
        /// Locally unique identifier (LUID) for the logon session. 
        /// If the token resulted from a logon using explicit credentials, 
        /// such as passing name, domain, and password to the LogonUser 
        /// function, then this member will contain the ID of the logon 
        /// session that created it. If the token resulted from network 
        /// authentication, such as a call to AcceptSecurityContext, or a 
        /// call to LogonUser with dwLogonType set to LOGON32_LOGON_NETWORK 
        /// or LOGON32_LOGON_NETWORK_CLEARTEXT, then value of the returned 
        /// LocalUniqueId will be zero.
        /// </summary>
        /// <returns>LocalUniqueId for the originating logon session</returns>
        LocalUniqueId OriginatingLogonSession( ) const
        {
            constexpr size_t bufferSize = sizeof( TOKEN_ORIGIN );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenOrigin, buffer.data( ), bufferSize );
            auto pTOKEN_ORIGIN = (TOKEN_ORIGIN*)buffer.data( );
            LocalUniqueId result( pTOKEN_ORIGIN->OriginatingLogonSession );
            return result;
        }

        /// <summary>
        /// Retrieves the elevation level of the token.
        /// </summary>
        /// <returns>The TokenElevationType indicating the elevation level of the token</returns>
        TokenElevationType ElevationType( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenElevationType, buffer.data( ), bufferSize );
            auto pTokenElevationType = (TokenElevationType*)buffer.data( );
            auto result = *pTokenElevationType;
            return result;
        }

        /// <summary>
        /// Retrives a token that is linked to this token.
        /// </summary>
        /// <returns>The linked token</returns>
        Security::Token LinkedToken( ) const
        {
            constexpr size_t bufferSize = sizeof( HANDLE );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenLinkedToken, buffer.data( ), bufferSize );
            auto pHANDLE = (HANDLE*)buffer.data( );
            auto handle = *pHANDLE;
            Security::Token result( handle );
            return result;
        }

        /// <summary>
        /// Checks whether the token is elevated.
        /// </summary>
        /// <returns>true if the token is elevated.</returns>
        bool IsElevated( ) const
        {
            constexpr size_t bufferSize = sizeof( TOKEN_ELEVATION );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenElevation, buffer.data( ), bufferSize );
            auto pTOKEN_ELEVATION = (TOKEN_ELEVATION*)buffer.data( );
            bool result = ( pTOKEN_ELEVATION->TokenIsElevated ) != 0;
            return result;
        }

        /// <summary>
        /// Checks if the token has been filtered.
        /// </summary>
        /// <returns>true if the token has been filtered.</returns>
        bool HasRestrictions( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenHasRestrictions, buffer.data( ), bufferSize );
            auto pTokenHasRestrictions = (DWORD*)buffer.data( );
            bool result = ( *pTokenHasRestrictions ) != 0;
            return result;
        }
        bool IsFiltered( ) const
        {
            return HasRestrictions( );
        }

        /// <summary>
        /// Retrieves a TokenAccessInformation object that specifies 
        /// security information contained in the token.
        /// </summary>
        /// <returns>A TokenAccessInformation object</returns>
        TokenAccessInformation AccessInformation( ) const
        {
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenAccessInformation );
            auto buffer = std::make_unique<Byte[]>( requiredSize );

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenAccessInformation, buffer.get( ), requiredSize );
            TokenAccessInformation result = TokenAccessInformation( (TOKEN_ACCESS_INFORMATION*)buffer.release( ) );
            return result;
        }

        /// <summary>
        /// Returns true if virtualization is allowed for the token.
        /// </summary>
        /// <remarks>
        /// Virtualization is a feature of User Account Control (UAC) 
        /// that allows per-machine file and registry operations to 
        /// target virtual, per-user file and registry locations rather 
        /// than the actual per-machine locations.
        /// </remarks>
        bool IsVirtualizationAllowed( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenVirtualizationAllowed, buffer.data( ), bufferSize );
            auto pValue = (DWORD*)buffer.data( );
            bool result = ( *pValue ) != 0;
            return result;
        }

        /// <summary>
        /// Returns true if virtualization is enabled for the token.
        /// </summary>
        /// <remarks>
        /// Virtualization is a feature of User Account Control (UAC) 
        /// that allows per-machine file and registry operations to 
        /// target virtual, per-user file and registry locations rather 
        /// than the actual per-machine locations.
        /// </remarks>
        bool IsVirtualizationEnabled( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenVirtualizationEnabled, buffer.data( ), bufferSize );
            auto pValue = (DWORD*)buffer.data( );
            bool result = ( *pValue ) != 0;
            return result;
        }

        /// <summary>
        /// Retrieves a TokenMandatoryLabel object that 
        /// specifies the token's integrity level.
        /// </summary>
        /// <returns>a TokenMandatoryLabel object</returns>
        TokenMandatoryLabel IntegrityLevel( ) const
        {
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenIntegrityLevel );
            auto buffer = std::make_unique<Byte[]>( requiredSize );

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenIntegrityLevel, buffer.get( ), requiredSize );
            TokenMandatoryLabel result = TokenMandatoryLabel( (TOKEN_MANDATORY_LABEL*)buffer.release( ) );
            return result;
        }

        /// <summary>
        /// Returns true if the token has the UIAccess flag set.
        /// </summary>
        /// <returns></returns>
        bool HasUIAccess( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenUIAccess, buffer.data( ), bufferSize );
            auto pValue = (DWORD*)buffer.data( );
            bool result = ( *pValue ) != 0;
            return result;
        }

        /// <summary>
        /// Returns a value from the Security::TokenMandatoryPolicy that 
        /// specifies the token's mandatory integrity policy.
        /// </summary>
        /// <returns></returns>
        Security::TokenMandatoryPolicy MandatoryPolicy( ) const
        {
            constexpr size_t bufferSize = sizeof( TOKEN_MANDATORY_POLICY );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenMandatoryPolicy, buffer.data( ), bufferSize );
            auto pValue = (TOKEN_MANDATORY_POLICY*)buffer.data( );
            auto result = static_cast<Security::TokenMandatoryPolicy>( pValue->Policy );
            return result;
        }

        /// <summary>
        /// Returns a Security::TokenGroups object that specifies the token's logon SID
        /// </summary>
        /// <returns></returns>
        Security::TokenGroups LogonSid( ) const
        {
            Security::TokenGroups::Data* data = nullptr;
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenLogonSid );
            data = ( Security::TokenGroups::Data* )new Byte[requiredSize];
            Security::TokenGroups result( data );
            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenLogonSid, data, requiredSize );
            return result;
        }

        /// <summary>
        /// Returns true if the token is an app container token. Any 
        /// callers who check the IsAppContainer and have it return false should 
        /// also verify that the caller token is not an identify level impersonation 
        /// token. If the current token is not an app container but is an identity 
        /// level token, you should return AccessDenied.
        /// </summary>
        /// <returns></returns>
        bool IsAppContainer( ) const
        {
            constexpr size_t bufferSize = sizeof( DWORD );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenIsAppContainer, buffer.data( ), bufferSize );
            auto pValue = (DWORD*)buffer.data( );
            bool result = ( *pValue ) != 0;
            return result;
        }

        /// <summary>
        /// Returns a Security::TokenGroups object that contains the 
        /// capabilities associated with the token.
        /// </summary>
        /// <returns></returns>
        Security::TokenGroups Capabilities( ) const
        {
            Security::TokenGroups::Data* data = nullptr;
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenCapabilities );
            data = ( Security::TokenGroups::Data* )new Byte[requiredSize];
            Security::TokenGroups result( data );
            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenCapabilities, data, requiredSize );
            return result;
        }

        /// <summary>
        /// Returns the Security::SecurityId for the AppContainerSid associated 
        /// with the token. If the token is not associated with an app container
        /// the Security::SecurityId is empty.
        /// </summary>
        /// <returns></returns>
        Security::SecurityId AppContainerSid( ) const
        {
            constexpr size_t bufferSize = Security::SecurityId::MaxSize + sizeof( TOKEN_APPCONTAINER_INFORMATION );
            using BufferType = std::array<Byte, bufferSize >;
            BufferType buffer;

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenAppContainerSid, buffer.data( ), bufferSize );
            auto pTOKEN_APPCONTAINER_INFORMATION = (TOKEN_APPCONTAINER_INFORMATION*)buffer.data( );
            auto result = Security::SecurityId::Clone( pTOKEN_APPCONTAINER_INFORMATION->TokenAppContainer );
            return result;
        }


        ClaimSecurityAttributesInformation UserClaimAttributes( ) const
        {
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenUserClaimAttributes );
            auto buffer = std::make_unique<Byte[]>( requiredSize );

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenUserClaimAttributes, buffer.get( ), requiredSize );
            ClaimSecurityAttributesInformation result = ClaimSecurityAttributesInformation( (CLAIM_SECURITY_ATTRIBUTES_INFORMATION*)buffer.release( ) );
            return result;
        }

        ClaimSecurityAttributesInformation DeviceClaimAttributes( ) const
        {
            size_t requiredSize = GetTokenInformationSize( TOKEN_INFORMATION_CLASS::TokenDeviceClaimAttributes );
            auto buffer = std::make_unique<Byte[]>( requiredSize );

            GetTokenInformation( TOKEN_INFORMATION_CLASS::TokenDeviceClaimAttributes, buffer.get( ), requiredSize );
            ClaimSecurityAttributesInformation result = ClaimSecurityAttributesInformation( (CLAIM_SECURITY_ATTRIBUTES_INFORMATION*)buffer.release( ) );
            return result;
        }




    };
    inline HANDLE SecurityDescriptor::HandleOf( const Token& clientToken ) const
    {
        return clientToken.Handle( );
    }


    



    enum class SecurityPackageFlags : UInt32
    {
        None = 0,
        // The security package supports the MakeSignature and VerifySignature functions
        Integrity = SECPKG_FLAG_INTEGRITY,
        // The security package supports the EncryptMessage and DecryptMessage functions.
        Privacy = SECPKG_FLAG_PRIVACY,
        // The package is interested only in the security-token portion of messages, and 
        // will ignore any other buffers. This is a performance-related issue.
        TokenOnly = SECPKG_FLAG_TOKEN_ONLY,
        // Supports datagram-style authentication. A datagram-oriented context has extra 
        // support for DCE-style datagram communication. It can also be used generically 
        // for a datagram-oriented transport application.
        // 
        // Important  The Microsoft Kerberos package does not support datagram contexts in 
        // user-to-user mode.
        Datagram = SECPKG_FLAG_DATAGRAM,
        // A connection-oriented context is the most common security context, and the simplest 
        // to use. The caller is responsible for the overall message format and for the location 
        // of the data in the message. The caller is also responsible for the location of the 
        // security-relevant fields within a message, such as the location of the signature data.
        Connection = SECPKG_FLAG_CONNECTION,
        // Multiple legs are required for authentication.
        MultiRequired = SECPKG_FLAG_MULTI_REQUIRED,
        // Server side functionality not available
        ClientOnly = SECPKG_FLAG_CLIENT_ONLY,
        // Supports extended error msgs
        ExtendedError = SECPKG_FLAG_EXTENDED_ERROR,
        // Supports impersonation
        Impersonation = SECPKG_FLAG_IMPERSONATION,
        // Understands Windows principal and target names.
        AcceptWindowsNames = SECPKG_FLAG_ACCEPT_WIN32_NAME,
        // Supports stream semantics
        Stream = SECPKG_FLAG_STREAM,
        // Can be used by the negotiate package
        Negotiable = SECPKG_FLAG_NEGOTIABLE,
        // GSS Compatibility Available
        GSSCompatible = SECPKG_FLAG_GSS_COMPATIBLE,
        // Supports common LsaLogonUser
        Logon = SECPKG_FLAG_LOGON,
        // Token Buffers are in ASCII
        AsciiBuffers = SECPKG_FLAG_ASCII_BUFFERS,
        // Supports separating large tokens into smaller buffers so 
        // that applications can make repeated calls to InitializeSecurityContext 
        // and AcceptSecurityContext with the smaller buffers to complete authentication.
        Fragment = SECPKG_FLAG_FRAGMENT,
        // Package can perform mutual authentication
        MutualAuthentication = SECPKG_FLAG_MUTUAL_AUTH,
        // Package can delegate
        Delegation = SECPKG_FLAG_DELEGATION,
        // The security package supports using a checksum instead of in-place 
        // encryption when calling the EncryptMessage function.
        ReadonlyWithChecksum = SECPKG_FLAG_READONLY_WITH_CHECKSUM,
        // Package supports restricted callers
        RestrictedTokens = SECPKG_FLAG_RESTRICTED_TOKENS,
        // this package extends SPNEGO, there is at most one
        NegoExtender = SECPKG_FLAG_NEGO_EXTENDER,
        // this package is negotiated under the NegoExtender
        Negotiable2 = SECPKG_FLAG_NEGOTIABLE2,
        // this package receives all calls from appcontainer apps
        AppcontainerPassthrough = SECPKG_FLAG_APPCONTAINER_PASSTHROUGH,
        // This package receives calls from app container apps if one of the following checks succeeds.
        // 
        //   * Caller has default credentials capability.
        //   * The target is a proxy server.
        //   * The caller has supplied credentials.
        AppcontainerChecks = SECPKG_FLAG_APPCONTAINER_CHECKS,
        // this package is running with Credential Guard enabled
        CredentialIsolationEnabled = SECPKG_FLAG_CREDENTIAL_ISOLATION_ENABLED,
        // this package supports reliable detection of loopback
        // 1.) The client and server see the same sequence of tokens
        // 2.) The server enforces a unique exchange for each
        //     non-anonymous authentication. (Replay detection)
        ApplyLoopback = SECPKG_FLAG_APPLY_LOOPBACK
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SecurityPackageFlags, UInt32 );

    /// <summary>
    /// Provides access to information about a
    /// Windows security package.
    /// </summary>
    class SecurityPackage
    {
    public:
        

        static constexpr UInt16 RpcIdNone = 0xFFFF;

        // These are name that can be used to refer to the builtin packages
        static constexpr wchar_t NTLM[] = NTLMSP_NAME;
        static constexpr wchar_t Kerberos[] = MICROSOFT_KERBEROS_NAME_W;
        static constexpr wchar_t Negotiate[] = NEGOSSP_NAME_W;
        static constexpr wchar_t Schannel[] = L"Schannel";
        static constexpr wchar_t CloudAP[] = CLOUDAP_NAME_W;
        static constexpr wchar_t CredSSP[] = L"CREDSSP";
        static constexpr wchar_t PKU2U[] = L"pku2u";
    private:
        // flags that describes the capabilities of the security package. 
        SecurityPackageFlags flags_;
        // Specifies a DCE RPC identifier, if appropriate.If the package 
        // does not implement one of the DCE registered security systems, 
        // the reserved value RpcIdNone is used.
        UInt16 rpcId_;
        // Specifies the maximum size, in bytes, of the token
        UInt32 maxTokenSize_;
        // The name of the security package
        std::wstring name_;
        // Additional information about the security package
        std::wstring comment_;

        PSecurityFunctionTableW functionTable_ = nullptr;

    public:
        explicit SecurityPackage( const wchar_t* packageName )
            : flags_( SecurityPackageFlags::None ), rpcId_( 0 ), maxTokenSize_( 0 )
        {
            PSecPkgInfoW package = nullptr;
            auto rc = QuerySecurityPackageInfoW( (LPWSTR)packageName, &package );
            if ( rc != SEC_E_OK )
            {
                ThrowOSError( rc );
            }
            flags_ = static_cast<SecurityPackageFlags>( package->fCapabilities );
            rpcId_ = package->wRPCID;
            maxTokenSize_ = package->cbMaxToken;
            name_ = package->Name;
            comment_ = package->Comment;

            FreeContextBuffer( package );
        }

        SecurityPackage( SecurityPackageFlags flags, UInt16 rpcId, UInt32 maxTokenSize, const std::wstring& name, const std::wstring& comment )
            : flags_( flags ), rpcId_( rpcId ), maxTokenSize_( maxTokenSize ), name_( name ), comment_( comment )
        {
        }

        SecurityPackage( const SecurityPackage& other ) = delete;
        SecurityPackage( SecurityPackage&& other ) noexcept
            : flags_( other.flags_ ), rpcId_( other.rpcId_ ), maxTokenSize_( other.maxTokenSize_ ), name_( std::move(other.name_) ), comment_( std::move( other.comment_ ) )
        {
        }
        SecurityPackage& operator = ( const SecurityPackage& other ) = delete;
        SecurityPackage& operator = ( SecurityPackage&& other ) noexcept
        {
            std::swap( flags_, other.flags_ );
            std::swap( rpcId_, other.rpcId_ );
            std::swap( maxTokenSize_, other.maxTokenSize_ );
            std::swap( name_, other.name_ );
            std::swap( comment_, other.comment_ );
            std::swap( functionTable_, other.functionTable_ );
            return *this;
        }


        // flags that describes the capabilities of the security package. 
        SecurityPackageFlags Flags( ) const noexcept
        {
            return flags_;
        }
        // Specifies a DCE RPC identifier, if appropriate.If the package 
        // does not implement one of the DCE registered security systems, 
        // the reserved value RpcIdNone is used.
        UInt16 RpcId( ) const noexcept
        {
            return rpcId_;
        }
        // Specifies the maximum size, in bytes, of the token
        UInt32 MaxTokenSize( ) const noexcept
        {
            return maxTokenSize_;
        }
        // The name of the security package
        const std::wstring& Name( ) const noexcept
        {
            return name_;
        }
        // Additional information about the security package
        const std::wstring& Comment( ) const noexcept
        {
            return comment_;
        }
    };


    /// <summary>
    /// An std::unordered_map of information about the 
    /// security packages installed on the system.
    /// </summary>
    class SecurityPackages : public std::unordered_map<std::wstring, SecurityPackage>
    {
    public:
        using Base = std::unordered_map<std::wstring, SecurityPackage>;

        SecurityPackages( )
        {
            ULONG count = 0;
            PSecPkgInfoW packages = nullptr;
            auto rc = EnumerateSecurityPackagesW( &count, &packages );
            if ( rc != SEC_E_OK )
            {
                ThrowOSError( rc );
            }
            for ( ULONG i = 0; i < count; i++ )
            {
                SecPkgInfoW& current = packages[i];
                SecurityPackageFlags flags = static_cast<SecurityPackageFlags>( current.fCapabilities );
                UInt16 rpcId = current.wRPCID;
                UInt32 maxTokenSize = current.cbMaxToken;
                std::wstring name( current.Name );
                std::wstring comment( current.Comment );
                emplace( name, SecurityPackage( flags, rpcId, maxTokenSize, name, comment ) );
            }
            FreeContextBuffer( packages );
        }

        SecurityPackages( const SecurityPackages& other ) = delete;
        SecurityPackages( SecurityPackages&& other ) = delete;

        SecurityPackages& operator = ( const SecurityPackages& other ) = delete;
        SecurityPackages& operator = ( SecurityPackages&& other ) = delete;


    };


    /// <summary>
    /// A tiny wrapper for the Windows SEC_WINNT_AUTH_IDENTITY_W
    /// type.
    /// </summary>
    class AuthenticationIdentity : public SEC_WINNT_AUTH_IDENTITY_W
    {
    public:
        using Base = SEC_WINNT_AUTH_IDENTITY_W;

        AuthenticationIdentity( )
            : Base{0,0,0,0,0,0,SEC_WINNT_AUTH_IDENTITY_UNICODE }
        {
        }

    };


    /// <summary>
    /// Flags indicating how the credentials will/can be used
    /// </summary>
    enum class CredentialsHandleFlags : UInt32
    {
        Inbound = SECPKG_CRED_INBOUND,
        Outbound = SECPKG_CRED_OUTBOUND,
        Both = SECPKG_CRED_BOTH,
        Default = SECPKG_CRED_DEFAULT,
        AutologonRestricted = SECPKG_CRED_AUTOLOGON_RESTRICTED,
        ProcessPolicyOnly = SECPKG_CRED_PROCESS_POLICY_ONLY
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CredentialsHandleFlags, UInt32 );

    /// <summary>
    /// A wrapper for the Windows CredHandle type.
    /// </summary>
    class CredentialsHandle
    {
        TimeStamp expiry_;
        CredHandle handle_;
    public:
        static constexpr CredHandle InvalidHandle = { ( (ULONG_PTR)( (INT_PTR)-1 ) ),( (ULONG_PTR)( (INT_PTR)-1 ) ) };
        using Flags = CredentialsHandleFlags;

        CredentialsHandle( )
            : expiry_{}, handle_( InvalidHandle )
        {
        }

        
        CredentialsHandle( const wchar_t* principal, const wchar_t* securityPackageName, Flags flags, CREDSSP_CRED* authenticationData, LocalUniqueId* logonId = nullptr )
            : expiry_{}, handle_( InvalidHandle )
        {
            TimeStamp expiry{};
            CredHandle handle = InvalidHandle;
            auto rc = AcquireCredentialsHandleW( (LPWSTR)principal,
                (LPWSTR)securityPackageName,
                static_cast<unsigned long>( flags ),
                logonId, authenticationData,
                nullptr, nullptr,
                &handle, &expiry );
            if ( rc != SEC_E_OK )
            {
                ThrowOSError( rc );
            }
            expiry_ = expiry;
            handle_ = handle;
        }

        CredentialsHandle( const wchar_t* securityPackageName, Flags flags, CREDSSP_CRED* authenticationData, LocalUniqueId* logonId = nullptr )
            : CredentialsHandle(nullptr, securityPackageName, flags, authenticationData, logonId )
        {
        }


        explicit CredentialsHandle( CredHandle& handle )
            : handle_( handle )
        {
        }

        CredentialsHandle( const CredentialsHandle& other ) = delete;
        CredentialsHandle( CredentialsHandle&& other )
            : handle_( other.handle_ )
        {
            other.handle_ = InvalidHandle;
        }


        CredentialsHandle& operator = ( const CredentialsHandle& other ) = delete;
        CredentialsHandle& operator = ( CredentialsHandle&& other )
        {
            if ( &other != this )
            {
                Close( );
                handle_ = other.handle_;
                other.handle_ = InvalidHandle;
            }
            return *this;
        }

        static CredentialsHandle Schannel( CREDSSP_CRED* authenticationData, LocalUniqueId* logonId = nullptr, Flags flags = Flags::Both )
        {
            CredentialsHandle result( SecurityPackage::Schannel, flags, authenticationData, logonId );
            return result;
        }

        static CredentialsHandle Kerberos( LocalUniqueId* logonId = nullptr, Flags flags = Flags::Both )
        {
            CredentialsHandle result( SecurityPackage::Kerberos, flags, nullptr, logonId );
            return result;
        }

        static CredentialsHandle CredSSP( LocalUniqueId* logonId = nullptr, Flags flags = Flags::Both )
        {
            CredentialsHandle result( SecurityPackage::CredSSP, flags, nullptr, logonId );
            return result;
        }

        static CredentialsHandle NTLM( LocalUniqueId* logonId = nullptr, Flags flags = Flags::Both )
        {
            CredentialsHandle result( SecurityPackage::NTLM, flags, nullptr, logonId );
            return result;
        }
        static CredentialsHandle CloudAP( CREDSSP_CRED* authenticationData, LocalUniqueId* logonId = nullptr, Flags flags = Flags::Both )
        {
            CredentialsHandle result( SecurityPackage::CloudAP, flags, authenticationData, logonId );
            return result;
        }



        static CredentialsHandle Negotiate( CREDSSP_CRED* authenticationData, LocalUniqueId* logonId = nullptr, Flags flags = Flags::Both )
        {
            CredentialsHandle result( SecurityPackage::Negotiate, flags, authenticationData, logonId );
            return result;
        }



        void Close( )
        {
            if ( SecIsValidHandle( &handle_) )
            {
                FreeCredentialsHandle( &handle_ );
                handle_ = InvalidHandle;
            }
        }

        CredHandle Release( )
        {
            auto result = handle_;
            handle_ = InvalidHandle;
            return result;
        }

        const CredHandle* Value( ) const
        {
            return &handle_;
        }
    };

    /// <summary>
    /// Indicating the type of a SecurityBuffer
    /// </summary>
    enum class SecurityBufferType : UInt32
    {
        // This is a placeholder in the buffer array. The caller can 
        // supply several such entries in the array, and the security 
        // package can return information in them.
        Empty = SECBUFFER_EMPTY,
        // The buffer contains common data. The security package can 
        // read and write this data, for example, to encrypt some or all of it.
        Data = SECBUFFER_DATA,
        // The buffer contains the security token portion of the message. 
        // This is read-only for input parameters or read/write for output 
        // parameters.
        Token = SECBUFFER_TOKEN,
        // These are transport-to-package–specific parameters. For example, 
        // the NetWare redirector may supply the server object identifier, 
        // while DCE RPC can supply an association UUID, and so on.
        PackageParameters =  SECBUFFER_PKG_PARAMS,
        // The security package uses this value to indicate the number of 
        // missing bytes in a particular message. The pvBuffer member is 
        // ignored in this type.
        Missing = SECBUFFER_MISSING,
        // The security package uses this value to indicate the number 
        // of extra or unprocessed bytes in a message.
        Extra = SECBUFFER_EXTRA,
        // The buffer contains a protocol-specific trailer for a particular 
        // record. It is not usually of interest to callers.
        StreamTrailer = SECBUFFER_STREAM_TRAILER,
        // The buffer contains a protocol-specific header for a particular 
        // record. It is not usually of interest to callers.
        StreamHeader = SECBUFFER_STREAM_HEADER,
        // Hints from the negotiation pkg
        NegotiationInfo = SECBUFFER_NEGOTIATION_INFO,
        // non-data padding
        Padding = SECBUFFER_PADDING,
        // whole encrypted message
        Stream = SECBUFFER_STREAM,
        // The buffer contains a protocol-specific list of object identifiers 
        // (OIDs). It is not usually of interest to callers.
        MechList = SECBUFFER_MECHLIST,
        // The buffer contains a signature of a SECBUFFER_MECHLIST buffer. 
        // It is not usually of interest to callers.
        MechListSignature  = SECBUFFER_MECHLIST_SIGNATURE,
        // This flag is reserved. Do not use it.
        Target = SECBUFFER_TARGET,
        // The buffer contains channel binding information.
        ChannelBindings = SECBUFFER_CHANNEL_BINDINGS,
        // The buffer contains a DOMAIN_PASSWORD_INFORMATION structure.
        ChangePasswordResponse = SECBUFFER_CHANGE_PASS_RESPONSE,
        // The buffer specifies the service principal name (SPN) of the target.
        // This value is supported by the Digest security package when used 
        // with channel bindings.
        TargetHost = SECBUFFER_TARGET_HOST,
        // The buffer contains an alert message.
        Alert = SECBUFFER_ALERT,
        // The buffer contains a list of application protocol IDs, one list 
        // per application protocol negotiation extension type to be enabled.
        ApplicationProtocols = SECBUFFER_APPLICATION_PROTOCOLS,
        // The buffer contains the list of SRTP protection profiles, 
        // in descending order of preference.
        SRTPProtectionProfiles=  SECBUFFER_SRTP_PROTECTION_PROFILES,
        // The buffer contains the SRTP master key identifier.
        SRTPMasterKeyIdentifier = SECBUFFER_SRTP_MASTER_KEY_IDENTIFIER,
        // The buffer contains the supported token binding protocol 
        // version and key parameters, in descending order of preference.
        TokenBinding = SECBUFFER_TOKEN_BINDING,
        // The buffer contains the preshared key. The maximum allowed PSK 
        // buffer size is 256 bytes.
        PresharedKey = SECBUFFER_PRESHARED_KEY,
        // The buffer contains the preshared key identity.
        PresharedKeyIdentity = SECBUFFER_PRESHARED_KEY_IDENTITY,
        // The buffer contains the setting for the maximum transmission unit 
        // (MTU) size for DTLS only. The default value is 1096 and the valid 
        // configurable range is between 200 and 64*1024.
        DtlsMtu = SECBUFFER_DTLS_MTU,
        // Buffer for sending generic TLS extensions.
        SendGenericTlsExtension = SECBUFFER_SEND_GENERIC_TLS_EXTENSION,
        // Buffer for subscribing to generic TLS extensions.
        SubscribeGenericTlsExtension = SECBUFFER_SUBSCRIBE_GENERIC_TLS_EXTENSION,
        // ISC/ASC REQ Flags
        ReqFlags = SECBUFFER_FLAGS,
        // Message sequence lengths and corresponding traffic secrets.
        TrafficSecrets = SECBUFFER_TRAFFIC_SECRETS

    };

    /// <summary>
    /// A wrapper for the Windows SecBuffer type
    /// </summary>
    class SecurityBuffer : public SecBuffer
    {
    public:
        static constexpr UInt32 TypeMask = ~static_cast<UInt32>(SECBUFFER_ATTRMASK);
        static constexpr UInt32 AttributeMask = SECBUFFER_ATTRMASK;

        using Base = SecBuffer;

        SecurityBuffer( )
            : Base{ 0, static_cast<unsigned long>( SecurityBufferType::Empty ), nullptr }
        {
        }


        SecurityBufferType Type( ) const noexcept
        {
            return static_cast<SecurityBufferType>( BufferType & TypeMask );
        }

        bool IsReadOnly( ) const noexcept
        {
            return (BufferType & SECBUFFER_READONLY) != 0;
        }

        bool IsReadOnlyWithChecksum( ) const noexcept
        {
            return (BufferType & SECBUFFER_READONLY_WITH_CHECKSUM) != 0;
        }



    };

    static_assert( sizeof( SecBuffer ) == sizeof( SecurityBuffer ), "Do not add any new data members to the SecurityBuffer class" );


    /// <summary>
    /// A wrapper for the Windows SecBufferDesc type
    /// </summary>
    class SecurityBufferArray : public SecBufferDesc
    {
    public:
        using Base = SecBufferDesc;
        using size_type = size_t;

        SecurityBufferArray( )
            : Base{ SECBUFFER_VERSION, 0, nullptr }
        {
        }

        size_t size( ) const noexcept
        {
            return cBuffers;
        }

        SecurityBuffer* data( ) noexcept
        {
            
            return static_cast<SecurityBuffer*>(pBuffers);
        }

        SecurityBuffer& at( size_type index ) noexcept
        {
            return static_cast<SecurityBuffer&>( pBuffers[index] );
        }

        const SecurityBuffer& at( size_type index ) const noexcept
        {
            return static_cast<const SecurityBuffer&>( pBuffers[index] );
        }

        SecurityBuffer& operator[]( size_type index ) noexcept
        {
            return static_cast<SecurityBuffer&>( pBuffers[index] );
        }

        const SecurityBuffer& operator[]( size_type index ) const noexcept
        {
            return static_cast<const SecurityBuffer&>( pBuffers[index] );
        }
    };

    static_assert( sizeof( SecBufferDesc ) == sizeof( SecurityBufferArray ), "Do not add any new data members to the SecurityBufferArray class" );


    /// <summary>
    /// Flags indicating the requested capabilities of a security
    /// context created using the InitializeSecurityContext API
    /// </summary>
    enum class InitializeSecurityContextRequestedFlags : UInt64
    {
        None = 0,
        // The server can use the context to authenticate to other 
        // servers as the client.The ISC_REQ_MUTUAL_AUTH flag must 
        // be set for this flag to work. Valid for Kerberos. Ignore 
        // this flag for constrained delegation.
        Delegate = ISC_REQ_DELEGATE,
        // The mutual authentication policy of the service will be satisfied.
        // Caution  This does not necessarily mean that mutual authentication 
        // is performed, only that the authentication policy of the service 
        // is satisfied. To ensure that mutual authentication is performed, 
        // call the QueryContextAttributes (General) function.
        MutualAuth = ISC_REQ_MUTUAL_AUTH,
        // Detect replayed messages that have been encoded by using the 
        // EncryptMessage or MakeSignature functions.
        ReplayDetect = ISC_REQ_REPLAY_DETECT,
        // Detect messages received out of sequence.
        SequenceDetect = ISC_REQ_SEQUENCE_DETECT,
        // Encrypt messages by using the EncryptMessage function.
        Confidentiality = ISC_REQ_CONFIDENTIALITY,
        // A new session key must be negotiated.
        // This value is supported only by the Kerberos security package.
        UseSessionKey = ISC_REQ_USE_SESSION_KEY,
        // If the client is an interactive user, the package must, if 
        // possible, prompt the user for the appropriate credentials.
        PromptForCreds = ISC_REQ_PROMPT_FOR_CREDS,
        // Schannel must not attempt to supply credentials for the client automatically.
        UseSuppliedCreds = ISC_REQ_USE_SUPPLIED_CREDS,
        // The security package allocates output buffers for you. When 
        // you have finished using the output buffers, free them by 
        // calling the FreeContextBuffer function.
        AllocateMemory = ISC_REQ_ALLOCATE_MEMORY,
        // The caller expects a three-leg mutual authentication transaction.
        UseDceStyle = ISC_REQ_USE_DCE_STYLE,
        // A datagram-type communications channel should be used. For more information
        Datagram = ISC_REQ_DATAGRAM,
        // The security context will not handle formatting messages. 
        // This value is the default for the Kerberos, Negotiate, and 
        // NTLM security packages.
        Connection = ISC_REQ_CONNECTION,

        CallLevel = ISC_REQ_CALL_LEVEL,

        FragmentSupplied = ISC_REQ_FRAGMENT_SUPPLIED,
        ExtendedError = ISC_REQ_EXTENDED_ERROR,
        Stream = ISC_REQ_STREAM,
        Integrity = ISC_REQ_INTEGRITY,
        Identify = ISC_REQ_IDENTIFY,
        NullSession = ISC_REQ_NULL_SESSION,
        ManualCredValidation = ISC_REQ_MANUAL_CRED_VALIDATION,
        Reserved1 = ISC_REQ_RESERVED1,
        FragmentToFit = ISC_REQ_FRAGMENT_TO_FIT,
        ForwardCredentials = ISC_REQ_FORWARD_CREDENTIALS,
        NoIntegrity = ISC_REQ_NO_INTEGRITY,
        UseHttpStyle = ISC_REQ_USE_HTTP_STYLE,
        UnverifiedTargetName = ISC_REQ_UNVERIFIED_TARGET_NAME,
        ConfidentialityOnly = ISC_REQ_CONFIDENTIALITY_ONLY,
        Messages = ISC_REQ_MESSAGES
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( InitializeSecurityContextRequestedFlags, UInt64 );

    /// <summary>
    /// Flags indicating the granted capabilities of a security
    /// context created using the InitializeSecurityContext API
    /// </summary>
    enum class InitializeSecurityContextFlags : UInt64
    {
        Delegate = ISC_RET_DELEGATE,
        MutualAuth = ISC_RET_MUTUAL_AUTH,
        ReplayDetect = ISC_RET_REPLAY_DETECT,
        SequenceDetect = ISC_RET_SEQUENCE_DETECT,
        Confidentiality = ISC_RET_CONFIDENTIALITY,
        UseSessionKey = ISC_RET_USE_SESSION_KEY,
        UsedCollectedCreds = ISC_RET_USED_COLLECTED_CREDS,
        UsedSuppliedCreds = ISC_RET_USED_SUPPLIED_CREDS,
        AllocatedMemory = ISC_RET_ALLOCATED_MEMORY,
        UsedDceStyle = ISC_RET_USED_DCE_STYLE,
        Datagram = ISC_RET_DATAGRAM,
        Connection = ISC_RET_CONNECTION,
        IntermediateReturn = ISC_RET_INTERMEDIATE_RETURN,
        CallLevel = ISC_RET_CALL_LEVEL,
        ExtendedError = ISC_RET_EXTENDED_ERROR,
        Stream = ISC_RET_STREAM,
        Integrity = ISC_RET_INTEGRITY,
        Identify = ISC_RET_IDENTIFY,
        NullSession = ISC_RET_NULL_SESSION,
        ManualCredValidation = ISC_RET_MANUAL_CRED_VALIDATION,
        Reserved1 = ISC_RET_RESERVED1,
        FragmentOnly = ISC_RET_FRAGMENT_ONLY,
        ForwardCredentials = ISC_RET_FORWARD_CREDENTIALS,
        UsedHttpStyle = ISC_RET_USED_HTTP_STYLE,
        NoAdditionalToken = ISC_RET_NO_ADDITIONAL_TOKEN,
        Reauthentication = ISC_RET_REAUTHENTICATION,
        ConfidentialityOnly = ISC_RET_CONFIDENTIALITY_ONLY,
        Messages = ISC_RET_MESSAGES
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( InitializeSecurityContextFlags, UInt64 );

    /// <summary>
    /// Flags indicating the requested capabilities of a security
    /// context created using the AcceptSecurityContext API
    /// </summary>
    enum class AcceptSecurityContextRequestedFlags : UInt64
    {
        Delegate = ASC_REQ_DELEGATE,
        MutualAuth = ASC_REQ_MUTUAL_AUTH,
        ReplayDetect = ASC_REQ_REPLAY_DETECT,
        SequenceDetect = ASC_REQ_SEQUENCE_DETECT,
        Confidentiality = ASC_REQ_CONFIDENTIALITY,
        UseSessionKey = ASC_REQ_USE_SESSION_KEY,
        SessionTicket = ASC_REQ_SESSION_TICKET,
        AllocateMemory = ASC_REQ_ALLOCATE_MEMORY,
        UseDceStyle = ASC_REQ_USE_DCE_STYLE,
        Datagram = ASC_REQ_DATAGRAM,
        Connection = ASC_REQ_CONNECTION,
        CallLevel = ASC_REQ_CALL_LEVEL,
        FragmentSupplied = ASC_REQ_FRAGMENT_SUPPLIED,
        ExtendedError = ASC_REQ_EXTENDED_ERROR,
        Stream = ASC_REQ_STREAM,
        Integrity = ASC_REQ_INTEGRITY,
        Licensing = ASC_REQ_LICENSING,
        Identify = ASC_REQ_IDENTIFY,
        AllowNullSession = ASC_REQ_ALLOW_NULL_SESSION,
        AllowNonUserLogons = ASC_REQ_ALLOW_NON_USER_LOGONS,
        AllowContextReplay = ASC_REQ_ALLOW_CONTEXT_REPLAY,
        FragmentToFit = ASC_REQ_FRAGMENT_TO_FIT,
        NoToken = ASC_REQ_NO_TOKEN,
        ProxyBindings = ASC_REQ_PROXY_BINDINGS,
        Reauthentication = 0x08000000, // SSP_REQ_REAUTHENTICATION
        AllowMissingBindings = ASC_REQ_ALLOW_MISSING_BINDINGS,
        Messages = ASC_REQ_MESSAGES
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AcceptSecurityContextRequestedFlags, UInt64 );

    /// <summary>
    /// Flags indicating the granted capabilities of a security
    /// context created using the AcceptSecurityContext API
    /// </summary>
    enum class AcceptSecurityContextFlags : UInt64
    {
        Delegate = ASC_RET_DELEGATE,
        MutualAuth = ASC_RET_MUTUAL_AUTH,
        ReplayDetect = ASC_RET_REPLAY_DETECT,
        SequenceDetect = ASC_RET_SEQUENCE_DETECT,
        Confidentiality = ASC_RET_CONFIDENTIALITY,
        UseSessionKey = ASC_RET_USE_SESSION_KEY,
        SessionTicket = ASC_RET_SESSION_TICKET,
        AllocatedMemory = ASC_RET_ALLOCATED_MEMORY,
        UsedDceStyle = ASC_RET_USED_DCE_STYLE,
        Datagram = ASC_RET_DATAGRAM,
        Connection = ASC_RET_CONNECTION,
        CallLevel = ASC_RET_CALL_LEVEL,
        ThirdLegFailed = ASC_RET_THIRD_LEG_FAILED,
        ExtendedError = ASC_RET_EXTENDED_ERROR,
        Stream = ASC_RET_STREAM,
        Integrity = ASC_RET_INTEGRITY,
        Licensing = ASC_RET_LICENSING,
        Identify = ASC_RET_IDENTIFY,
        Null_session = ASC_RET_NULL_SESSION,
        AllowNonUserLogons = ASC_RET_ALLOW_NON_USER_LOGONS,
        AllowContextReplay = ASC_RET_ALLOW_CONTEXT_REPLAY,
        FragmentOnly = ASC_RET_FRAGMENT_ONLY,
        NoToken = ASC_RET_NO_TOKEN,
        NoAdditionalToken = ASC_RET_NO_ADDITIONAL_TOKEN,
        Reauthentication  = 0x08000000,//      SSP_RET_REAUTHENTICATION 
        Messages = ASC_RET_MESSAGES
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AcceptSecurityContextFlags, UInt64 );

    

    /// <summary>
    /// The data representation, such as byte ordering, on the target.
    /// </summary>
    enum class SecurityDataRepresentation
    {
        None = 0,
        Native = SECURITY_NATIVE_DREP,
        Network = SECURITY_NETWORK_DREP
    };


    /// <summary>
    /// A wrapper for the Windows CtxtHandle type
    /// </summary>
    class SecurityContext
    {
        CtxtHandle handle_;
    public:
        static constexpr CtxtHandle InvalidHandle = { ( (ULONG_PTR)( (INT_PTR)-1 ) ),( (ULONG_PTR)( (INT_PTR)-1 ) ) };

        SecurityContext( )
            : handle_( InvalidHandle )
        {
        }

        explicit SecurityContext( const CtxtHandle& handle )
            : handle_( handle )
        {
        }

        SecurityContext( const SecurityContext& other ) = delete;
        SecurityContext( SecurityContext&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = InvalidHandle;
        }

        ~SecurityContext( )
        {
            Close( );
        }


        SecurityContext& operator = ( const SecurityContext& other ) = delete;
        SecurityContext& operator = ( SecurityContext&& other ) noexcept
        {
            std::swap( handle_, other.handle_ );
            return *this;
        }

        void Close( )
        {
            if ( SecIsValidHandle( &handle_ ) )
            {
                DeleteSecurityContext( &handle_ );
                handle_ = InvalidHandle;
            }
        }

        /// <summary>
        /// The Initialize function initiates the client side, 
        /// outbound security context from a credential handle. 
        /// The function is used to build a security context between 
        /// the client application and a remote peer.
        /// </summary>
        /// <param name="credentialsHandle">
        /// The CredentialsHandle to initialize the security context from
        /// </param>
        /// <param name="context">
        /// A pointer to a CtxtHandle for a partially initialized security 
        /// context or nullptr if this is the initial call to Initialize.
        /// </param>
        /// <param name="targetName">
        /// A pointer to a null-terminated string that indicates the target 
        /// of the context. The interpretation of this string is determined 
        /// by the security package, like:
        /// <ul>
        /// <li>
        /// Digest: Null-terminated string that uniquely identifies the URI 
        /// of the requested resource. The string must be composed of 
        /// characters that are allowed in a URI and must be representable 
        /// by the US ASCII code set. Percent encoding can be used to 
        /// represent characters outside the US ASCII code set.
        /// </li>
        /// <li>
        /// Kerberos, Negotiate or NTLM: Service principal name (SPN) or 
        /// the security context of the destination server
        /// </li>
        /// <li>
        /// Null-terminated string that uniquely identifies the target 
        /// server. Schannel uses this value to verify the server certificate. 
        /// Schannel also uses this value to locate the session in the session 
        /// cache when reestablishing a connection. The cached session is used 
        /// only if all of the following conditions are met:
        /// <ul>
        /// <li>The target name is the same.</li>
        /// <li>The cache entry has not expired.</li>
        /// <li>The application process that calls the function is the same.</li>
        /// <li>The logon session is the same.</li>
        /// <li>The credential handle is the same.</li>
        /// </ul>
        /// </li>
        /// </ul>
        /// </param>
        /// <param name="contextRequestedFlags">
        /// Values from the InitializeSecurityContextRequestedFlags enumeration
        /// indicating the requested capabilities of the security
        /// context.
        /// </param>
        /// <param name="targetDataRepresentation">
        /// The data representation, such as byte ordering, on the target. 
        /// </param>
        /// <param name="securityPackageInput">
        /// A pointer to a SecBufferDesc structure that contains pointers 
        /// to the buffers supplied as input to the package. Unless the 
        /// client context was initiated by the server, the value of this 
        /// parameter must be NULL on the first call to the function. On 
        /// subsequent calls to the function or when the client context 
        /// was initiated by the server, the value of this parameter is 
        /// a pointer to a buffer allocated with enough memory to hold 
        /// the token returned by the remote computer.
        /// </param>
        /// <param name="newContext">
        /// <p>
        /// A pointer to a CtxtHandle structure. On the first call to 
        /// Initialize, this pointer receives the new context handle. 
        /// On the second call, newContext can be the same as the handle 
        /// specified in the context parameter.
        /// </p>
        /// <p>
        /// When using the Schannel SSP, on calls after the first call, 
        /// pass the handle returned here as the context parameter and 
        /// specify nullptr for newContext.
        /// </p>
        /// </param>
        /// <param name="output">
        /// <p>
        /// A pointer to a SecBufferDesc structure that contains 
        /// pointers to the SecBuffer structure that receives the output 
        /// data. If a buffer was typed as SEC_READWRITE in the input, 
        /// it will be there on output. The system will allocate a buffer 
        /// for the security token if requested (through InitializeSecurityContextRequestedFlags::AllocateMemory) 
        /// and fill in the address in the buffer descriptor for the security token.
        /// </p>
        /// <p>
        /// When using the Microsoft Digest SSP, this parameter receives 
        /// the challenge response that must be sent to the server.
        /// </p>
        /// <p>
        /// When using the Schannel SSP, if the InitializeSecurityContextRequestedFlags::AllocateMemory flag 
        /// is specified, the Schannel SSP will allocate memory for the bufferand 
        /// put the appropriate information in the SecBufferDesc. In addition, the caller 
        /// must pass in a buffer of type SECBUFFER_ALERT.On output, if an alert is 
        /// generated, this buffer contains information about that alert, and the function fails.
        /// </p>
        /// </param>
        /// <param name="contextFlags">
        /// A pointer to a variable to receive a set of bit flags that indicate the attributes of the established context.
        /// </param>
        /// <param name="expiryTimeStamp">
        /// <p>
        /// A pointer to a TimeStamp structure that receives the expiration time of the context. 
        /// It is recommended that the security package always return this value in local time. 
        /// This parameter is optional and NULL should be passed for short-lived clients.
        /// </p>
        /// <p>
        /// There is no expiration time for Microsoft Digest SSP security contexts or credentials.
        /// </p>
        /// </param>
        /// <returns>
        /// If the function succeeds, the function returns one of the following success codes:
        /// <ul>
        /// <li>
        /// SEC_I_COMPLETE_AND_CONTINUE: The client must call CompleteAuthToken and then 
        /// pass the output to the server. The client then waits for a returned token 
        /// and passes it, in another call, to Initialize
        /// </li>
        /// <li>
        /// SEC_I_COMPLETE_NEEDED: The client must finish building the message and 
        /// then call the CompleteAuthToken function.
        /// </li>
        /// <li>
        /// SEC_I_CONTINUE_NEEDED: The client must send the output token to the 
        /// server and wait for a return token. The returned token is then passed 
        /// in another call to Initialize. The output token can be empty.
        /// </li>
        /// <li>
        /// SEC_I_INCOMPLETE_CREDENTIALS: Use with Schannel. The server has requested 
        /// client authentication, and the supplied credentials either do not include 
        /// a certificate or the certificate was not issued by a certification authority 
        /// that is trusted by the server.
        /// </li>
        /// <li>
        /// <p>
        /// SEC_E_INCOMPLETE_MESSAGE: Use with Schannel. Data for the whole message was not read from the wire.
        /// </p>
        /// <p>
        /// When this value is returned, the pInput buffer contains a SecBuffer 
        /// structure with a BufferType member of SECBUFFER_MISSING.The cbBuffer 
        /// member of SecBuffer contains a value that indicates the number of 
        /// additional bytes that the function must read from the client before 
        /// this function succeeds. While this number is not always accurate, using 
        /// it can help improve performance by avoiding multiple calls to this function.
        /// </p>
        /// </li>
        /// <li>SEC_E_OK:
        /// The security context was successfully initialized. There is no need for 
        /// another InitializeSecurityContext (General) call. If the function returns 
        /// an output token, that is, if the SECBUFFER_TOKEN in output is of nonzero 
        /// length, that token must be sent to the server.
        /// </li>
        /// </ul>
        /// </returns>
        static SECURITY_STATUS Initialize( const CredentialsHandle& clientCredentialsHandle, PCtxtHandle context, const wchar_t* targetName, InitializeSecurityContextRequestedFlags contextRequestedFlags,
            SecurityDataRepresentation targetDataRepresentation, PSecBufferDesc securityPackageInput, PCtxtHandle newContext, PSecBufferDesc output, InitializeSecurityContextFlags* contextFlags, PTimeStamp expiryTimeStamp )
        {
            auto rc = InitializeSecurityContextW( const_cast<PCredHandle>( clientCredentialsHandle.Value( ) ), context,
                const_cast<wchar_t*>( targetName ), static_cast<ULONG>( contextRequestedFlags ), 0, static_cast<ULONG>( targetDataRepresentation ), securityPackageInput, 0,
                newContext, output, (ULONG*)contextFlags, expiryTimeStamp );
            switch ( rc )
            {
                case SEC_I_COMPLETE_AND_CONTINUE:
                case SEC_I_COMPLETE_NEEDED:
                case SEC_I_CONTINUE_NEEDED:
                case SEC_I_INCOMPLETE_CREDENTIALS:
                case SEC_E_INCOMPLETE_MESSAGE:
                case SEC_E_OK:
                    break;
                default:
                {
                    ThrowOSError( rc );
                }
                break;
            }
            return rc;
        }

        /// <summary>
        /// The Accept function enables the server component 
        /// of a transport application to establish a security 
        /// context between the server and a remote client.
        /// </summary>
        /// <param name="serverCredentialsHandle">
        /// The credentials of the server. 
        /// </param>
        /// <param name="context">
        /// A pointer to a CtxtHandle for a partially accepted security 
        /// context or nullptr if this is the initial call to Accept.
        /// </param>
        /// <param name="input">
        /// <p>
        /// A pointer to a SecBufferDesc structure generated by a client 
        /// call to InitializeSecurityContext (General) that contains the 
        /// input buffer descriptor.
        /// </p>
        /// <p>
        /// When using the Schannel SSP, the first buffer must be of 
        /// type SECBUFFER_TOKEN and contain the security token received 
        /// from the client. The second buffer should be of type 
        /// SECBUFFER_EMPTY.
        /// </p>
        /// <p>
        /// When using the Negotiate, Kerberos, or NTLM SSPs, channel 
        /// binding information can be specified by passing in a 
        /// SecBuffer structure of type SECBUFFER_CHANNEL_BINDINGS in 
        /// addition to the buffers generated by the call to the Initialize 
        /// function. The channel binding information for the channel 
        /// binding buffer can be obtained by calling the 
        /// QueryContextAttributes function on the Schannel context the 
        /// client used to authenticate.
        /// </p>
        /// </param>
        /// <param name="contextRequestedFlags">
        /// Values from the AcceptSecurityContextRequestedFlags enumeration
        /// indicating the requested capabilities of the security
        /// context.
        /// </param>
        /// <param name="targetDataRepresentation">
        /// The data representation, such as byte ordering, on the target.
        /// </param>
        /// <param name="newContext">
        /// A pointer to a CtxtHandle structure. On the first call to 
        /// Accept, this pointer receives the new context handle. On 
        /// subsequent calls, newContext can be the same as the handle 
        /// specified in the context parameter.
        /// </param>
        /// <param name="output">
        /// <p>
        /// A pointer to a SecBufferDesc structure that contains the 
        /// output buffer descriptor. This buffer is sent to the client 
        /// for input into additional calls to Initialize. An output 
        /// buffer may be generated even if the function returns SEC_E_OK. 
        /// Any buffer generated must be sent back to the client application.
        /// </p>
        /// <p>
        /// When using Schannel, on output, this buffer receives a token 
        /// for the security context. The token must be sent to the client. 
        /// The function can also return a buffer of type SECBUFFER_EXTRA.
        /// In addition, the caller must pass in a buffer of type 
        /// SECBUFFER_ALERT. On output, if an alert is generated, this 
        /// buffer contains information about that alert, and the function fails.
        /// </p>
        /// </param>
        /// <param name="contextFlags">
        /// <p>
        /// A pointer to a variable that receives a set of bit flags that 
        /// indicate the attributes of the established context.
        /// </p>
        /// <p>
        /// Do not check for security-related attributes until the final 
        /// function call returns successfully. Attribute flags not related 
        /// to security, such as the ASC_RET_ALLOCATED_MEMORY flag, can 
        /// be checked before the final return.
        /// </p>
        /// </param>
        /// <param name="expiryTimeStamp">
        /// <p>
        /// A pointer to a TimeStamp structure that receives the expiration 
        /// time of the context. We recommend that the security package always 
        /// return this value in local time.
        /// </p>
        /// <p>
        /// This parameter is set to a constant maximum time. There is no 
        /// expiration time for Digest security contexts or credentials or 
        /// when using the Digest SSP.
        /// </p>
        /// <p>
        /// This is optional when using the Schannel SSP. When the remote 
        /// party has supplied a certificate to be used for authentication, 
        /// this parameter receives the expiration time for that certificate. 
        /// If no certificate was supplied, a maximum time value is returned.
        /// </p>
        /// <p>
        /// Until the last call of the authentication process, the expiration 
        /// time for the context can be incorrect because more information will 
        /// be provided during later stages of the negotiation. Therefore, 
        /// expiryTimeStamp must be NULL until the last call to the function.
        /// </p>
        /// </param>
        /// <returns></returns>
        static SECURITY_STATUS Accept( const CredentialsHandle& serverCredentialsHandle,
            PCtxtHandle context,
            PSecBufferDesc input,
            AcceptSecurityContextRequestedFlags contextRequestedFlags,
            SecurityDataRepresentation targetDataRepresentation,
            PCtxtHandle newContext,
            PSecBufferDesc output,
            AcceptSecurityContextFlags* contextFlags,
            PTimeStamp expiryTimeStamp )
        {
            auto rc = AcceptSecurityContext( const_cast<PCredHandle>( serverCredentialsHandle.Value( ) ), context, input, static_cast<ULONG>( contextRequestedFlags ), static_cast<ULONG>( targetDataRepresentation ),
                newContext, output, (ULONG*)contextFlags, expiryTimeStamp );
            switch ( rc )
            {
                case SEC_I_CONTINUE_NEEDED:
                case SEC_I_COMPLETE_NEEDED:
                case SEC_I_COMPLETE_AND_CONTINUE:
                case SEC_E_INCOMPLETE_MESSAGE:
                case SEC_E_OK:
                    break;
                default:
                {
                    ThrowOSError( rc );
                }
                break;
            }
            return rc;

        }


        void Encrypt( unsigned long qualityOfProtection, PSecBufferDesc message, unsigned long messageSeqNumber ) const
        {
            auto rc = EncryptMessage( const_cast<PCtxtHandle>(&handle_), qualityOfProtection, message, messageSeqNumber );
            if ( rc != SEC_E_OK )
            {
                ThrowOSError( rc );
            }
        }

        bool Decrypt( PSecBufferDesc message, unsigned long messageSeqNumber, unsigned long* qualityOfProtection ) const
        {
            auto rc = DecryptMessage( const_cast<PCtxtHandle>( &handle_ ), message, messageSeqNumber, qualityOfProtection );
            if ( rc != SEC_E_OK )
            {
                if ( rc == SEC_E_INCOMPLETE_MESSAGE )
                {
                    return false;
                }
                ThrowOSError( rc );
            }
            return true;
        }

        SECURITY_STATUS MakeSignature( ULONG qualityOfProtection, PSecBufferDesc message, unsigned long messageSeqNumber ) const
        {
            auto rc = ::MakeSignature( const_cast<PCtxtHandle>( &handle_ ), qualityOfProtection, message, messageSeqNumber );
            return rc;
        }


        SECURITY_STATUS VerifySignature( PSecBufferDesc message, unsigned long messageSeqNumber, unsigned long* qualityOfProtection ) const
        {
            auto rc = ::VerifySignature( const_cast<PCtxtHandle>( &handle_ ), message, messageSeqNumber, qualityOfProtection );
            return rc;
        }




        void CompleteAuthToken( PSecBufferDesc pToken ) const
        {
            auto rc = ::CompleteAuthToken( const_cast<PCtxtHandle>(&handle_), pToken );
            if ( rc != SEC_E_OK )
            {
                ThrowOSError( rc );
            }
        }
    };

    /// <summary>
    /// A security context for NTLM SSPI
    /// </summary>
    class NTLMSecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for NTLM SSPI
    /// </summary>
    class NTLMClientSecurityContext : public NTLMSecurityContext
    {
    public:
        using Base = NTLMSecurityContext;

    };

    /// <summary>
    /// A server security context for NTLM SSPI
    /// </summary>
    class NTLMServerSecurityContext : public NTLMSecurityContext
    {
    public:
        using Base = NTLMSecurityContext;

    };

    /// <summary>
    /// A security context for Kerberos SSPI
    /// </summary>
    class KerberosSecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for Kerberos SSPI
    /// </summary>
    class KerberosClientSecurityContext : public KerberosSecurityContext
    {
    public:
        using Base = KerberosSecurityContext;
    };

    /// <summary>
    /// A server security context for Kerberos SSPI
    /// </summary>
    class KerberosServerSecurityContext : public KerberosSecurityContext
    {
    public:
        using Base = KerberosSecurityContext;
    };

    /// <summary>
    /// A security context for Negotiate SSPI
    /// </summary>
    class NegotiateSecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for Negotiate SSPI
    /// </summary>
    class NegotiateClientSecurityContext : public NegotiateSecurityContext
    {
    public:
        using Base = NegotiateSecurityContext;
    };

    /// <summary>
    /// A server security context for Negotiate SSPI
    /// </summary>
    class NegotiateServerSecurityContext : public NegotiateSecurityContext
    {
    public:
        using Base = NegotiateSecurityContext;
    };

    /// <summary>
    /// A security context for Schannel SSPI
    /// </summary>
    class SchannelSecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for Schannel SSPI
    /// </summary>
    class SchannelClientSecurityContext : public SchannelSecurityContext
    {
    public:
        using Base = SchannelSecurityContext;
    };

    /// <summary>
    /// A server security context for Schannel SSPI
    /// </summary>
    class SchannelServerSecurityContext : public SchannelSecurityContext
    {
    public:
        using Base = SchannelSecurityContext;
    };

    /// <summary>
    /// A security context for CloudAP SSPI
    /// </summary>
    class CloudAPSecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for CloudAP SSPI
    /// </summary>
    class CloudAPClientSecurityContext : public CloudAPSecurityContext
    {
    public:
        using Base = CloudAPSecurityContext;
    };

    /// <summary>
    /// A server security context for CloudAP SSPI
    /// </summary>
    class CloudAPServerSecurityContext : public CloudAPSecurityContext
    {
    public:
        using Base = CloudAPSecurityContext;
    };

    /// <summary>
    /// A security context for CredSSP SSPI
    /// </summary>
    class CredSSPSecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for CredSSP SSPI
    /// </summary>
    class CredSSPClientSecurityContext : public CredSSPSecurityContext
    {
    public:
        using Base = CredSSPSecurityContext;
    };

    /// <summary>
    /// A server security context for CredSSP SSPI
    /// </summary>
    class CredSSPServerSecurityContext : public CredSSPSecurityContext
    {
    public:
        using Base = CredSSPSecurityContext;
    };

    /// <summary>
    /// A security context for PKU2U SSPI
    /// </summary>
    class PKU2USecurityContext : public SecurityContext
    {
    public:
        using Base = SecurityContext;
    };

    /// <summary>
    /// A client security context for PKU2U SSPI
    /// </summary>
    class PKU2UClientSecurityContext : public PKU2USecurityContext
    {
    public:
        using Base = PKU2USecurityContext;
    };

    /// <summary>
    /// A server security context for PKU2U SSPI
    /// </summary>
    class PKU2UServerSecurityContext : public PKU2USecurityContext
    {
    public:
        using Base = PKU2USecurityContext;
    };


    



}

namespace Harlinn::Common::Core::Environment
{
    namespace Internal
    {
        /// <summary>
        /// Memory management for buffers that will be released using
        /// the NetApiBufferFree function. 
        /// </summary>
        /// <remarks>
        /// Several of the Windows API NetXXX functions allocates memory
        /// on behalf of the application. This memory must be released
        /// using NetApiBufferFree function.
        /// </remarks>
        class NetApiBuffer
        {
            LPBYTE data_;
        public:
            constexpr NetApiBuffer() noexcept
                : data_(nullptr)
            { }

            NetApiBuffer( const NetApiBuffer& other ) = delete;
            constexpr NetApiBuffer( NetApiBuffer&& other ) noexcept
                : data_( other.data_ )
            {
                other.data_ = nullptr;
            }

            ~NetApiBuffer( )
            {
                if ( data_ )
                {
                    NetApiBufferFree( data_ );
                }
            }

            void Reset( )
            {
                if ( data_ )
                {
                    NetApiBufferFree( data_ );
                    data_ = nullptr;
                }
            }

            constexpr bool IsValid( ) const noexcept
            {
                return data_ != nullptr;
            }

            constexpr explicit operator bool( ) const noexcept
            {
                return IsValid( );
            }

            constexpr bool operator == ( void* ptr ) const noexcept
            {
                return data_ == ptr;
            }
            constexpr bool operator != ( void* ptr ) const noexcept
            {
                return data_ != ptr;
            }


            NetApiBuffer& operator = ( const NetApiBuffer& other ) = delete;
            constexpr NetApiBuffer& operator = ( NetApiBuffer&& other ) noexcept
            {
                std::swap( data_, other.data_ );
                return *this;
            }

            NetApiBuffer& operator = ( nullptr_t )
            {
                Reset( );
                return *this;
            }
            NetApiBuffer& operator = ( LPBYTE data )
            {
                Reset( );
                data_ = data;
                return *this;
            }

            LPBYTE* dataPtr( ) noexcept
            {
                Reset( );
                return &data_;
            }

            constexpr LPBYTE data( ) const noexcept
            {
                return data_;
            }

            template<typename T>
            T* As( ) const noexcept
            {
                return (T*)data_;
            }

        };
    }

    class DomainObject
    {
        std::wstring name_;
    protected:
        using NetApiBuffer = Environment::Internal::NetApiBuffer;
        DomainObject( )
        {
        }

        DomainObject( const std::wstring& name )
            : name_( name )
        {
        }
        DomainObject( std::wstring&& name )
            : name_( std::move( name ) )
        {
        }

        DomainObject( DomainObject&& other ) noexcept
            : name_( std::move( other.name_ ) )
        {
        }
        DomainObject& operator = ( DomainObject&& other ) noexcept
        {
            std::swap( name_, other.name_ );
            return *this;
        }
        void SetName( const wchar_t* name )
        {
            if ( name && name[0] )
            {
                name_ = name;
            }
            else
            {
                name_.clear( );
            }
        }
        void SetName( const std::wstring& name )
        {
            name_ = name;
        }
        void SetName( std::wstring&& name )
        {
            name_ = std::move( name );
        }
    public:
        DomainObject( const DomainObject& other ) = delete;
        DomainObject& operator = ( const DomainObject& other ) = delete;

        Security::SecurityId SecurityId( const wchar_t* serverName = nullptr ) const
        {
            Security::SecurityIdAndDomain securityIdAndDomain( name_.c_str( ), serverName );
            auto& securityId = securityIdAndDomain.SecurityId( );
            auto result = securityId.Clone( );
            return result;
        }

        constexpr const std::wstring& Name( ) const noexcept
        {
            return name_;
        }



        void swap( DomainObject& other )
        {
            std::swap( name_, other.name_ );
        }

    };


    using UserPrivilege = Security::UserPrivilege;
    using UserFlags = Security::UserFlags;

    class Groups;

    /// <summary>
    /// Represents a local or domain user
    /// </summary>
    class User : public DomainObject
    {
        TimeSpan passwordAge_;
        UserPrivilege privilege_ = UserPrivilege::None;
        std::wstring homeDirectory_;
        std::wstring comment_;
        UserFlags flags_ = UserFlags::None;
        std::wstring scriptPath_;
    public:
        using Base = DomainObject;

        User( )
        {
        }

        User( const std::wstring& name )
            : Base( name )
        {
        }
        User( std::wstring&& name )
            : Base( std::move( name ) )
        {
        }


        User( const wchar_t* serverName, const wchar_t* userName )
        {
            NetApiBuffer buffer;
            auto rc = NetUserGetInfo( serverName, userName, 1, buffer.dataPtr() );
            if ( rc != NERR_Success )
            {
                ThrowOSError( rc );
            }
            else
            {
                const auto* info = buffer.As<USER_INFO_1>();
                SetName( info->usri1_name );
                passwordAge_ = TimeSpan::FromSeconds( info->usri1_password_age );
                privilege_ = static_cast<UserPrivilege>( info->usri1_priv );
                homeDirectory_ = info->usri1_home_dir ? info->usri1_home_dir : L"";
                comment_ = info->usri1_comment ? info->usri1_comment : L"";
                flags_ = static_cast<UserFlags>( info->usri1_flags );
                scriptPath_ = info->usri1_script_path ? info->usri1_script_path : L"";
            }
        }


        User( const USER_INFO_1* info )
            : Base( info->usri1_name ),
              passwordAge_( TimeSpan::FromSeconds( info->usri1_password_age ) ),
              privilege_( static_cast<UserPrivilege>( info->usri1_priv ) ),
              homeDirectory_( info->usri1_home_dir? info->usri1_home_dir:L"" ),
              comment_( info->usri1_comment ? info->usri1_comment : L"" ),
              flags_( static_cast<UserFlags>( info->usri1_flags )),
              scriptPath_( info->usri1_script_path ? info->usri1_script_path : L"" )
        {

        }


        void swap( User& other )
        {
            Base::swap( other );
            std::swap( passwordAge_, other.passwordAge_ );
            std::swap( privilege_, other.privilege_ );
            std::swap( homeDirectory_, other.homeDirectory_ );
            std::swap( comment_, other.comment_ );
            std::swap( flags_, other.flags_ );
            std::swap( scriptPath_, other.scriptPath_ );
        }

        static User AddUser( const wchar_t* serverName, const wchar_t* name, const wchar_t* password, UserFlags userFlags, const wchar_t* homeDirectory, const wchar_t* comment, const wchar_t* scriptPath )
        {
            USER_INFO_1 newUserInfo{};
            newUserInfo.usri1_name = const_cast<LPWSTR>(name);
            newUserInfo.usri1_priv = USER_PRIV_USER;
            newUserInfo.usri1_password = const_cast<LPWSTR>( password );
            newUserInfo.usri1_home_dir = const_cast<LPWSTR>( homeDirectory );
            newUserInfo.usri1_comment = const_cast<LPWSTR>( comment );
            newUserInfo.usri1_flags = static_cast<DWORD>( userFlags );
            newUserInfo.usri1_script_path = const_cast<LPWSTR>( scriptPath );
            DWORD userInfoErrorIndex = 0;
            auto rc = NetUserAdd( serverName, 1, (LPBYTE)&newUserInfo, &userInfoErrorIndex );
            if ( rc != NERR_Success )
            {
                ThrowOSError( rc );
            }
            User result( serverName, name );
            return result;
        }

        Environment::Groups Groups( const wchar_t* serverName = nullptr ) const;


    };

    enum class UserFilter : DWORD
    {
        None = 0,
        /// <summary>
        /// Enumerates account data for users whose primary account 
        /// is in another domain. This account type provides user 
        /// access to this domain, but not to any domain that trusts 
        /// this domain. The User Manager refers to this account type 
        /// as a local user account.
        /// </summary>
        TemporaryDuplicateAccount = FILTER_TEMP_DUPLICATE_ACCOUNT,
        /// <summary>
        /// Enumerates normal user account data. This account type is 
        /// associated with a typical user.
        /// </summary>
        NormalAccount = FILTER_NORMAL_ACCOUNT,
        /// <summary>
        /// Enumerates interdomain trust account data. This account type 
        /// is associated with a trust account for a domain that trusts 
        /// other domains.
        /// </summary>
        Interdomaintrustaccount = FILTER_INTERDOMAIN_TRUST_ACCOUNT,
        /// <summary>
        /// Enumerates workstation or member server trust account data. 
        /// This account type is associated with a machine account for 
        /// a computer that is a member of the domain.
        /// </summary>
        WorkstationtrustAccount = FILTER_WORKSTATION_TRUST_ACCOUNT,
        /// <summary>
        /// Enumerates member server machine account data. This account 
        /// type is associated with a computer account for a backup 
        /// domain controller that is a member of the domain.
        /// </summary>
        ServerTrustAccount = FILTER_SERVER_TRUST_ACCOUNT
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( UserFilter, DWORD );


    class Users : public std::vector<User>
    {
        using NetApiBuffer = Environment::Internal::NetApiBuffer;
    public:
        using Filter = UserFilter;

        Users( const wchar_t* serverName = nullptr, Filter filter = Filter::None, bool forceLocalUsers = false )
        {
            NetApiBuffer buffer;
            NET_API_STATUS rc = 0;
            DWORD entriesRead = 0;
            DWORD totalEntries = 0;
            DWORD resumeHandle = 0;
            do
            {
                rc = NetUserEnum( serverName, 1, static_cast<DWORD>( filter ), buffer.dataPtr(), MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries, &resumeHandle );
                if ( ( rc == NERR_Success ) || ( rc == ERROR_MORE_DATA ) )
                {
                    if ( buffer )
                    {
                        auto requiredCapacity = size( ) + entriesRead;
                        if ( capacity( ) < requiredCapacity )
                        {
                            reserve( requiredCapacity );
                        }
                        auto* userInfo = buffer.As<USER_INFO_1>();
                        for ( DWORD i = 0; i < entriesRead; ++i )
                        {
                            emplace_back( userInfo );
                            userInfo++;
                        }
                    }
                }
                else
                {
                    ThrowOSError( rc );
                }
            } while ( rc == ERROR_MORE_DATA );
        }
    };



    class Computer : public DomainObject
    {
    public:
        using Base = DomainObject;

        Computer( )
        {
        }

        Computer( const std::wstring& name )
            : Base( name )
        {
        }
        Computer( std::wstring&& name )
            : Base( std::move( name ) )
        {
        }

        static std::wstring GetDomainOrWorkgroupName( const wchar_t* serverName = nullptr )
        {
            NetApiBuffer infoPtr;
            auto rc = NetWkstaGetInfo( const_cast<wchar_t*>(serverName), 100, infoPtr.dataPtr() );
            if ( rc == NERR_Success )
            {
                WKSTA_INFO_100* info = infoPtr.As<WKSTA_INFO_100>();
                std::wstring result = info->wki100_langroup;
                return result;
            }
            else
            {
                return std::wstring( );
            }

        }

    };

    using GroupFlags = Security::GroupFlags;
    

    /// <summary>
    /// Represents a local or domain group
    /// </summary>
    class Group : public DomainObject
    {
        std::wstring comment_;
        GroupFlags flags_ = GroupFlags::None;
        Security::SecurityId securityId_;
    public:
        using Base = DomainObject;

        Group( )
        {
        }

        Group( const std::wstring& name )
            : Base( name )
        {
        }
        Group( std::wstring&& name )
            : Base( std::move( name ) )
        {
        }

        Group( const wchar_t* serverName, const wchar_t* groupName )
        {
            NetApiBuffer buffer;
            auto rc = NetUserGetInfo( serverName, groupName, 3, buffer.dataPtr() );
            if ( rc != NERR_Success )
            {
                ThrowOSError( rc );
            }
            else
            {
                const auto* info = (const GROUP_INFO_3*)buffer.As<const GROUP_INFO_3>();
                SetName( info->grpi3_name );
                comment_ = info->grpi3_comment ? info->grpi3_comment : L"";
                if ( info->grpi3_group_sid )
                {
                    Security::SecurityId securityId( info->grpi3_group_sid );
                    securityId_ = securityId.Clone( );
                }
                flags_ = static_cast<GroupFlags>( info->grpi3_attributes );
                
            }
        }

        Group( const GROUP_INFO_3* info )
            : Base( std::wstring( info->grpi3_name&& info->grpi3_name[0] ? info->grpi3_name : L"" ) )
        {
            comment_ = info->grpi3_comment ? info->grpi3_comment : L"";
            if ( info->grpi3_group_sid )
            {
                Security::SecurityId securityId( info->grpi3_group_sid );
                securityId_ = securityId.Clone( );
            }
            flags_ = static_cast<GroupFlags>( info->grpi3_attributes );
        }

        Group( const LOCALGROUP_INFO_1* info )
            : Base( std::wstring( info->lgrpi1_name&& info->lgrpi1_name[0] ? info->lgrpi1_name : L"" ) )
        {
            comment_ = info->lgrpi1_comment ? info->lgrpi1_comment : L"";
            Security::SecurityIdAndDomain securityIdAndDomain( info->lgrpi1_name );
            const Security::SecurityId& securityId = securityIdAndDomain.SecurityId( );
            securityId_ = securityId.Clone( );
            flags_ = static_cast<GroupFlags>( 0 ); //static_cast<GroupFlags>( info->grpi3_attributes );
        }


    };


    class Groups : public std::vector<Group>
    {
        using NetApiBuffer = Environment::Internal::NetApiBuffer;
    public:
        
        Groups( const wchar_t* serverName = nullptr, bool forceLocalGroups = false )
        {
            bool performGlobalSearch = IsComputerDomainJoined( );
            NetApiBuffer buffer;
            NET_API_STATUS rc = 0;
            DWORD entriesRead = 0;
            DWORD totalEntries = 0;
            DWORD_PTR resumeHandle = 0;
            if ( performGlobalSearch )
            {
                do
                {
                    rc = NetGroupEnum( serverName, 3, buffer.dataPtr(), MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries, &resumeHandle );
                    if ( ( rc == NERR_Success ) || ( rc == ERROR_MORE_DATA ) )
                    {
                        if ( buffer )
                        {
                            auto requiredCapacity = size( ) + entriesRead;
                            if ( capacity( ) < requiredCapacity )
                            {
                                reserve( requiredCapacity );
                            }
                            const auto* groupInfo = buffer.As<GROUP_INFO_3>();
                            for ( DWORD i = 0; i < entriesRead; ++i )
                            {
                                emplace_back( groupInfo );
                                groupInfo++;
                            }
                            buffer.Reset();
                        }
                    }
                    else
                    {
                        ThrowOSError( rc );
                    }
                } while ( rc == ERROR_MORE_DATA );
            }
            else
            {
                do
                {
                    rc = NetLocalGroupEnum( serverName, 1, buffer.dataPtr(), MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries, &resumeHandle );
                    if ( ( rc == NERR_Success ) || ( rc == ERROR_MORE_DATA ) )
                    {
                        if ( buffer )
                        {
                            auto requiredCapacity = size( ) + entriesRead;
                            if ( capacity( ) < requiredCapacity )
                            {
                                reserve( requiredCapacity );
                            }
                            const auto* groupInfo = buffer.As<LOCALGROUP_INFO_1>();
                            for ( DWORD i = 0; i < entriesRead; ++i )
                            {
                                emplace_back( groupInfo );
                                groupInfo++;
                            }
                            buffer.Reset( );
                        }
                    }
                    else
                    {
                        ThrowOSError( rc );
                    }
                } while ( rc == ERROR_MORE_DATA );
            }
        }

        Groups( const wchar_t* serverName, const User& user )
        {
            NetApiBuffer buffer;
            NET_API_STATUS rc = 0;
            DWORD entriesRead = 0;
            DWORD totalEntries = 0;
            do
            {
                auto& userName = user.Name( );
                rc = NetUserGetGroups( serverName, userName.c_str(),0, buffer.dataPtr(), MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries );
                if ( ( rc == NERR_Success ) || ( rc == ERROR_MORE_DATA ) )
                {
                    if ( buffer )
                    {
                        auto requiredCapacity = size( ) + entriesRead;
                        if ( capacity( ) < requiredCapacity )
                        {
                            reserve( requiredCapacity );
                        }
                        const auto* groupInfo = buffer.As<GROUP_INFO_0>();
                        for ( DWORD i = 0; i < entriesRead; ++i )
                        {
                            emplace_back( serverName, groupInfo->grpi0_name );
                            groupInfo++;
                        }
                        buffer.Reset( );
                    }
                }
                else
                {
                    ThrowOSError( rc );
                }
            } while ( rc == ERROR_MORE_DATA );
        }
    };

    inline Environment::Groups User::Groups( const wchar_t* serverName ) const
    {
        Environment::Groups result( serverName, *this );
        return std::move( result );
    }


}

#endif

