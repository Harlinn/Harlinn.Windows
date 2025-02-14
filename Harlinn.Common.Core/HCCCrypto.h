#pragma once
#ifndef __HCCCRYPTO_H__
#define __HCCCRYPTO_H__
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

#include <HCCString.h>
#include <HCCBinary.h>

#pragma comment(lib, "Crypt32.lib")

// Acronyms:
//  ASN: Abstract syntax notation one: https://en.wikipedia.org/wiki/ASN.1
//  NDR: Network Data Representation: https://pubs.opengroup.org/onlinepubs/9629399/chap14.htm
//  PKCS: Public Key Cryptography Standards: https://en.wikipedia.org/wiki/PKCS


namespace Harlinn::Common::Core::Crypto
{
    enum class CryptStringFlags : DWORD
    {
        /// <summary>
        /// Base64, with certificate beginning and ending headers.
        /// </summary>
        Base64Header = CRYPT_STRING_BASE64HEADER,
        /// <summary>
        /// Base64, without headers.
        /// </summary>
        Base64 = CRYPT_STRING_BASE64,
        /// <summary>
        /// Pure binary copy.
        /// </summary>
        Binary = CRYPT_STRING_BINARY,
        /// <summary>
        /// Base64, with request beginning and ending headers.
        /// </summary>
        Base64RequestHeader = CRYPT_STRING_BASE64REQUESTHEADER,
        /// <summary>
        /// Hexadecimal only format
        /// </summary>
        Hex = CRYPT_STRING_HEX,
        /// <summary>
        /// Hexadecimal format with ASCII character display
        /// </summary>
        HexAscii = CRYPT_STRING_HEXASCII,
        /// <summary>
        /// Tries the following, in order:
        /// <ul>
        /// <li>Base64Header</li>
        /// <li>Base64</li>
        /// </ul>
        /// </summary>
        Base64Any = CRYPT_STRING_BASE64_ANY,
        /// <summary>
        /// Tries the following, in order:
        /// <ul>
        /// <li>Base64Header</li>
        /// <li>Base64</li>
        /// <li>Binary</li>
        /// </ul>
        /// </summary>
        Any = CRYPT_STRING_ANY,
        /// <summary>
        /// Tries the following, in order:
        /// <ul>
        /// <li>HexAddr</li>
        /// <li>HexAsciiAddr</li>
        /// <li>Hex</li>
        /// <li>HexRaw</li>
        /// <li>HexAscii</li>
        /// </ul>
        /// </summary>
        HexAny = CRYPT_STRING_HEX_ANY,
        /// <summary>
        /// Base64, with X.509 certificate revocation list (CRL) beginning and ending headers
        /// </summary>
        Base64X509CrlHeader = CRYPT_STRING_BASE64X509CRLHEADER,
        /// <summary>
        /// Hex, with address display
        /// </summary>
        HexAddr = CRYPT_STRING_HEXADDR,
        /// <summary>
        /// Hex, with ASCII character and address display
        /// </summary>
        HexAsciiAddr = CRYPT_STRING_HEXASCIIADDR,
        /// <summary>
        /// A raw hexadecimal string
        /// </summary>
        HexRaw = CRYPT_STRING_HEXRAW,

        Base64Uri = CRYPT_STRING_BASE64URI,

        /// <summary>
        /// Encoding flags mask
        /// </summary>
        EncodeMask = CRYPT_STRING_ENCODEMASK,
        Reserved100 = CRYPT_STRING_RESERVED100,
        Reserved200 = CRYPT_STRING_RESERVED200,
        PercentEscape = CRYPT_STRING_PERCENTESCAPE,
        HashData = CRYPT_STRING_HASHDATA,
        /// <summary>
        /// Set this flag for Base64 data to specify that the end of 
        /// the binary data contain only white space and at most three 
        /// equals "=" signs
        /// </summary>
        Strict = CRYPT_STRING_STRICT,
        /// <summary>
        /// Do not append any new line characters to the encoded string. The default behavior 
        /// is to use a carriage return/line feed (CR/LF) pair (0x0D/0x0A) to represent a new line.
        /// </summary>
        NoCRLF = CRYPT_STRING_NOCRLF,
        /// <summary>
        /// Only use the line feed (LF) character (0x0A) for a new line. The default behavior 
        /// is to use a CR/LF pair (0x0D/0x0A) to represent a new line
        /// </summary>
        NoCR = CRYPT_STRING_NOCR
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CryptStringFlags, DWORD );


    template<WideStringLike StringT>
    inline void BinaryToString( const Byte* inputBuffer, size_t inputBufferSize, CryptStringFlags flags, StringT& result )
    {
        DWORD requiredStringBufferSize = 0;
        auto rc = CryptBinaryToStringW( inputBuffer, static_cast<DWORD>(inputBufferSize), static_cast<DWORD>( flags ), nullptr, &requiredStringBufferSize );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        if ( requiredStringBufferSize > 1 )
        {
            result.resize( requiredStringBufferSize - 1 );

            rc = CryptBinaryToStringW( inputBuffer, static_cast<DWORD>( inputBufferSize ), static_cast<DWORD>( flags ), result.data( ), &requiredStringBufferSize );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        else
        {
            result.clear( );
        }
    }

    template<AnsiStringLike StringT>
    inline void BinaryToString( const Byte* inputBuffer, size_t inputBufferSize, CryptStringFlags flags, StringT& result )
    {
        DWORD requiredStringBufferSize = 0;
        auto rc = CryptBinaryToStringA( inputBuffer, static_cast<DWORD>( inputBufferSize ), static_cast<DWORD>(flags), nullptr, &requiredStringBufferSize );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        if ( requiredStringBufferSize > 1 )
        {
            result.resize( requiredStringBufferSize - 1 );

            rc = CryptBinaryToStringA( inputBuffer, static_cast<DWORD>( inputBufferSize ), static_cast<DWORD>( flags ), result.data( ), &requiredStringBufferSize );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        else
        {
            result.clear( );
        }
    }

    template<SimpleByteSpanLike SpanT, StringLike ResultT>
    inline void BinaryToString( const SpanT& inputBuffer, CryptStringFlags flags, ResultT& result )
    {
        BinaryToString( inputBuffer.data( ), inputBuffer.size( ), flags, result );
    }

    inline size_t StringToBinary(const wchar_t* inputString, size_t inputStringLength, CryptStringFlags requestedConversionFlags, std::unique_ptr<Byte[]>& result, UInt32* skipCount = nullptr, CryptStringFlags* actualConversionFlags = nullptr )
    {
        DWORD requiredBufferSize = 0;
        auto rc = CryptStringToBinaryW( inputString, static_cast<DWORD>( inputStringLength ), static_cast<DWORD>( requestedConversionFlags ), nullptr, &requiredBufferSize, (DWORD*)skipCount, (DWORD*)actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }

        result = std::make_unique<Byte[]>( requiredBufferSize );

        rc = CryptStringToBinaryW( inputString, static_cast<DWORD>( inputStringLength ), static_cast<DWORD>( requestedConversionFlags ), result.get(), &requiredBufferSize, (DWORD*)skipCount, (DWORD*)actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return requiredBufferSize;
    }
    inline size_t StringToBinary( const char* inputString, size_t inputStringLength, CryptStringFlags requestedConversionFlags, std::unique_ptr<Byte[ ]>& result, UInt32* skipCount = nullptr, CryptStringFlags* actualConversionFlags = nullptr )
    {
        DWORD requiredBufferSize = 0;
        auto rc = CryptStringToBinaryA( inputString, static_cast< DWORD >( inputStringLength ), static_cast< DWORD >( requestedConversionFlags ), nullptr, &requiredBufferSize, ( DWORD* )skipCount, ( DWORD* )actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }

        result = std::make_unique<Byte[ ]>( requiredBufferSize );

        rc = CryptStringToBinaryA( inputString, static_cast< DWORD >( inputStringLength ), static_cast< DWORD >( requestedConversionFlags ), result.get( ), &requiredBufferSize, ( DWORD* )skipCount, ( DWORD* )actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return requiredBufferSize;
    }

    template<SimpleCharSpanLike StringT>
    inline size_t StringToBinary( const StringT& inputString, CryptStringFlags requestedConversionFlags, std::unique_ptr<Byte[]>& result, UInt32* skipCount = nullptr, CryptStringFlags* actualConversionFlags = nullptr )
    {
        return StringToBinary( inputString.data( ), inputString.size( ), requestedConversionFlags, result, skipCount, actualConversionFlags );
    }

    template<BinaryLike ResultT>
    inline void StringToBinary( const wchar_t* inputString, size_t inputStringLength, CryptStringFlags requestedConversionFlags, ResultT& result, UInt32* skipCount = nullptr, CryptStringFlags* actualConversionFlags = nullptr )
    {
        DWORD requiredBufferSize = 0;
        auto rc = CryptStringToBinaryW( inputString, static_cast<DWORD>( inputStringLength ), static_cast<DWORD>( requestedConversionFlags ), nullptr, &requiredBufferSize, (DWORD*)skipCount, (DWORD*)actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }

        result.resize( requiredBufferSize );

        rc = CryptStringToBinaryW( inputString, static_cast<DWORD>( inputStringLength ), static_cast<DWORD>( requestedConversionFlags ), result.data( ), &requiredBufferSize, (DWORD*)skipCount, (DWORD*)actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }

    template<BinaryLike ResultT>
    inline void StringToBinary( const char* inputString, size_t inputStringLength, CryptStringFlags requestedConversionFlags, ResultT& result, UInt32* skipCount = nullptr, CryptStringFlags* actualConversionFlags = nullptr )
    {
        DWORD requiredBufferSize = 0;
        auto rc = CryptStringToBinaryA( inputString, static_cast< DWORD >( inputStringLength ), static_cast< DWORD >( requestedConversionFlags ), nullptr, &requiredBufferSize, ( DWORD* )skipCount, ( DWORD* )actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }

        result.resize( requiredBufferSize );

        rc = CryptStringToBinaryA( inputString, static_cast< DWORD >( inputStringLength ), static_cast< DWORD >( requestedConversionFlags ), result.data( ), &requiredBufferSize, ( DWORD* )skipCount, ( DWORD* )actualConversionFlags );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }



    template<SimpleCharSpanLike StringT, BinaryLike ResultT>
    inline void StringToBinary( const StringT& inputString, CryptStringFlags requestedConversionFlags, ResultT& result, UInt32* skipCount = nullptr, CryptStringFlags* actualConversionFlags = nullptr )
    {
        StringToBinary( inputString.data( ), inputString.size( ), requestedConversionFlags, result, skipCount, actualConversionFlags );
    }


    class Blob
    {
    protected:
        DWORD blobSize_;
        Byte* data_;
    public:

        constexpr Blob() noexcept
            : blobSize_(0), data_(nullptr)
        { }

        constexpr Blob( Byte* data, DWORD blobSize ) noexcept
            : blobSize_( blobSize ), data_( data )
        {
        }

        constexpr void Assign( Byte* data, DWORD blobSize ) noexcept
        {
            blobSize_ = blobSize; 
            data_ = data;
        }

        constexpr Byte* data( ) noexcept
        {
            return data_;
        }
        constexpr const Byte* data( ) const noexcept
        {
            return data_;
        }

        constexpr DWORD BlobSize( ) const noexcept
        {
            return blobSize_;
        }
    };

    static_assert( sizeof( Blob ) == sizeof( _CRYPTOAPI_BLOB ), "Do not add any new data members to the Blob class" );

    template<typename T>
    class BlobT : Blob
    {
    public:
        using Base = Blob;
        using size_type = DWORD;
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = pointer;
        using const_iterator = const_pointer;

        constexpr BlobT( ) noexcept
        { }

        constexpr BlobT(T* items, size_type count ) noexcept
            : Base( std::bit_cast<Byte*>( items ), static_cast<size_type>( count*sizeof(T) ) )
        {
        }

        constexpr size_type size( ) const noexcept
        {
            return static_cast<size_type>( blobSize_ / sizeof( T ) );
        }

        constexpr iterator begin( ) noexcept
        {
            return std::bit_cast<iterator>(data_);
        }
        constexpr const_iterator begin( ) noexcept
        {
            return std::bit_cast<const_iterator>(data_);
        }
        constexpr const_iterator cbegin( ) noexcept
        {
            return std::bit_cast<const_iterator>( data_ );
        }

        constexpr iterator end( ) noexcept
        {
            return std::bit_cast<iterator>( data_ + blobSize_ );
        }
        constexpr const_iterator end( ) noexcept
        {
            return std::bit_cast<const_iterator>( data_ + blobSize_ );
        }
        constexpr const_iterator cend( ) noexcept
        {
            return std::bit_cast<const_iterator>( data_ + blobSize_ );
        }


        constexpr T* data( ) noexcept
        {
            return std::bit_cast<T*>( data_ );
        }
        constexpr const T* data( ) const noexcept
        {
            return std::bit_cast<const T*>( data_ );
        }
    };



    /// <summary>
    /// EncodingType represents the eoncoding type for
    /// certificates and messages. The idea is just to
    /// make it harder to make trivial programming errors.
    /// </summary>
    class EncodingType
    {
        DWORD value_;
    public:
        static constexpr DWORD CertificateEncodingTypeMask = CERT_ENCODING_TYPE_MASK;
        static constexpr DWORD MessageEncodingTypeMask = CMSG_ENCODING_TYPE_MASK;

        static constexpr DWORD CryptAsnEncoding = CRYPT_ASN_ENCODING;
        static constexpr DWORD CryptNdrEncoding = CRYPT_NDR_ENCODING;
        static constexpr DWORD X509AsnEncoding = X509_ASN_ENCODING;
        static constexpr DWORD X509NdrEncoding = X509_NDR_ENCODING;
        static constexpr DWORD Pkcs7AsnEncoding =  PKCS_7_ASN_ENCODING;
        static constexpr DWORD Pkcs7NdrEncoding = PKCS_7_NDR_ENCODING;



        constexpr EncodingType() noexcept
            : value_(0)
        { 
        }

        constexpr explicit EncodingType( DWORD value ) noexcept
            : value_( value )
        {
        }

        constexpr DWORD Value( ) const noexcept
        {
            return value_;
        }

        constexpr EncodingType& operator = ( DWORD value ) noexcept
        {
            value_ = value;
            return *this;
        }

    };  


    //-------------------------------------------------------------------------
    // constants for dwFormatType of function CryptFormatObject
    // when format X509_NAME or X509_UNICODE_NAME
    //-------------------------------------------------------------------------
    enum class FormatType : DWORD
    {
        None = 0,
        // Just get the simple string
        Simple = CRYPT_FORMAT_SIMPLE,

        //Put an attribute name infront of the attribute
        //such as "O=Microsoft,DN=xiaohs"
        X509 = CRYPT_FORMAT_X509,

        //Put an OID infront of the simple string, such as
        //"2.5.4.22=Microsoft,2.5.4.3=xiaohs"
        OID = CRYPT_FORMAT_OID,

        //Put a ";" between each RDN.  The default is ","
        RDNSemicolon = CRYPT_FORMAT_RDN_SEMICOLON,

        //Put a "\n" between each RDN.
        RDNCRLF = CRYPT_FORMAT_RDN_CRLF,


        //Unquote the DN value, which is quoated by default va the following
        //rules: if the DN contains leading or trailing
        //white space or one of the following characters: ",", "+", "=",
        //""", "\n",  "<", ">", "#" or ";". The quoting character is ".
        //If the DN Value contains a " it is double quoted ("").
        RDNUnquote = CRYPT_FORMAT_RDN_UNQUOTE,

        //reverse the order of the RDNs before converting to the string
        RDNReverse = CRYPT_FORMAT_RDN_REVERSE,


        //-------------------------------------------------------------------------
        //  contants dwFormatType of function CryptFormatObject when format a DN.:
        //
        //  The following three values are defined in the section above:
        //  CRYPT_FORMAT_SIMPLE:    Just a simple string
        //                          such as  "Microsoft+xiaohs+NT"
        //  CRYPT_FORMAT_X509       Put an attribute name infront of the attribute
        //                          such as "O=Microsoft+xiaohs+NT"
        //
        //  CRYPT_FORMAT_OID        Put an OID infront of the simple string,
        //                          such as "2.5.4.22=Microsoft+xiaohs+NT"
        //
        //  Additional values are defined as following:
        //----------------------------------------------------------------------------
        //Put a "," between each value.  Default is "+"
        Comma = CRYPT_FORMAT_COMMA,

        //Put a ";" between each value
        Semicolon = CRYPT_FORMAT_SEMICOLON,

        //Put a "\n" between each value
        CRLF = CRYPT_FORMAT_CRLF
    };

    enum class FormatStringType : DWORD
    {
        /// <summary>
        /// Format the data in a single line. Each subfield is concatenated with a comma
        /// </summary>
        SingleLine = 0,
        /// <summary>
        /// the data in multiple lines rather than single line
        /// </summary>
        MultiLine = CRYPT_FORMAT_STR_MULTI_LINE,
        /// <summary>
        /// Disables the hexadecimal dump
        /// </summary>
        NoHex = CRYPT_FORMAT_STR_NO_HEX
    };


    

    inline void FormatObject( const EncodingType& certEncodingType, FormatType formatType, FormatStringType formatStringType, const char* structType, const Byte* encodedBuffer, size_t encodedBufferLength, WideString& result )
    {
        DWORD requiredSizeInBytes = 0;
        auto rc = CryptFormatObject( certEncodingType.Value( ), static_cast<DWORD>( formatType ), static_cast<DWORD>( formatStringType ), nullptr, structType, encodedBuffer, static_cast<DWORD>( encodedBufferLength ), nullptr, &requiredSizeInBytes );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        result.resize( ( requiredSizeInBytes / 2 ) - 1 );

        rc = CryptFormatObject( certEncodingType.Value( ), static_cast<DWORD>( formatType ), static_cast<DWORD>( formatStringType ), nullptr, structType, encodedBuffer, static_cast<DWORD>( encodedBufferLength ), result.data(), &requiredSizeInBytes );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        result.resize( ( requiredSizeInBytes / 2 ) - 1 );
    }

    enum class CertificateRetrievalType : size_t
    {
        IssuerLogo = (size_t)CERT_RETRIEVE_ISSUER_LOGO,
        SubjectLogo = (size_t)CERT_RETRIEVE_SUBJECT_LOGO,
        CommunityLogo = (size_t)CERT_RETRIEVE_COMMUNITY_LOGO,
        BiometricPicture = 1000, //(size_t)CERT_RETRIEVE_BIOMETRIC_PICTURE_TYPE,
        BiometricSignature = 1001, //(size_t)CERT_RETRIEVE_BIOMETRIC_SIGNATURE_TYPE
    };


    /// <summary>
    /// ContextObjectType for use with RetrieveObjectByUrl
    /// </summary>
    enum class ContextObjectType : size_t
    {
        Blob = 0,
        Certificate = (size_t)CONTEXT_OID_CERTIFICATE,
        CertificateRevocationList = (size_t)CONTEXT_OID_CRL,
        CertificateTrustList = (size_t)CONTEXT_OID_CTL,
        Pkcs7 = (size_t)CONTEXT_OID_PKCS7,
        CApi2Any = (size_t)CONTEXT_OID_CAPI2_ANY,
        OcspResponse = (size_t)CONTEXT_OID_OCSP_RESP
    };


    /// <summary>
    /// RetrievalFlags for use with RetrieveObjectByUrl
    /// </summary>
    enum class RetrievalFlags : DWORD
    {
        None = 0,
        /// <summary>
        /// Retrieves multiple objects if available. All objects must be of a homogeneous object type as determined by the value of objectOid, unless the object identifier (OID) value is CONTEXT_OID_CAPI2_ANY.
        /// </summary>
        RetrieveMultipleObjects = CRYPT_RETRIEVE_MULTIPLE_OBJECTS,
        CacheOnly = CRYPT_CACHE_ONLY_RETRIEVAL,
        WireOnly = CRYPT_WIRE_ONLY_RETRIEVAL,
        DontCacheResult = CRYPT_DONT_CACHE_RESULT,
        Async = CRYPT_ASYNC_RETRIEVAL,
        StickyCache = CRYPT_STICKY_CACHE_RETRIEVAL,
        LDAPScopeBaseOnly = CRYPT_LDAP_SCOPE_BASE_ONLY_RETRIEVAL,
        OfflineCheck = CRYPT_OFFLINE_CHECK_RETRIEVAL,

        /// <summary>
        /// When the following flag is set, the following 2 NULL terminated ascii
        /// strings are inserted at the beginning of each returned blob:
        ///  "%d\0%s\0", dwEntryIndex, pszAttribute
        ///
        ///  The first dwEntryIndex is 0, "0\0".
        ///
        /// When set, pszObjectOid must be NULL, so that a PCRYPT_BLOB_ARRAY is returned.
        /// </summary>
        LDAPInsertEntryAttribute = CRYPT_LDAP_INSERT_ENTRY_ATTRIBUTE,
        /// <summary>
        /// Set this flag to digitally sign all of the ldap traffic to and from a
        /// Windows 2000 LDAP server using the Kerberos authentication protocol.
        /// This feature provides integrity required by some applications.
        /// </summary>
        LDAPSign = CRYPT_LDAP_SIGN_RETRIEVAL,
        /// <summary>
        /// Set this flag to inhibit automatic authentication handling. See the
        /// wininet flag, INTERNET_FLAG_NO_AUTH, for more details.
        /// </summary>
        #define CRYPT_NO_AUTH_RETRIEVAL                 0x00020000

        /// <summary>
        /// Performs an A-Record only DNS lookup on the supplied host string.
        /// This prevents bogus DNS queries from being generated when resolving host
        /// names. Use this flag whenever passing a hostname as opposed to a
        /// domain name for the hostname parameter.
        ///
        /// See LDAP_OPT_AREC_EXCLUSIVE defined in winldap.h for more details.
        /// </summary>
        #define CRYPT_LDAP_AREC_EXCLUSIVE_RETRIEVAL     0x00040000


        /// <summary>
        /// Apply AIA URL restrictions, such as, validate 
        /// retrieved content before writing to cache.
        /// </summary>
        AIA = CRYPT_AIA_RETRIEVAL,

    };





    class CertificateStore;
    /// <summary>
    /// A wrapper for the Windows PCCERT_CONTEXT type.
    /// provides access to a X.509 certificate
    /// </summary>
    class CertificateContext
    {
        PCCERT_CONTEXT context_;
    public:
        constexpr CertificateContext( ) noexcept
            : context_(nullptr)
        { }

        constexpr explicit CertificateContext( PCCERT_CONTEXT context ) noexcept
            : context_( context )
        {
        }

        explicit CertificateContext( const EncodingType& encodingType, const Byte* encodedCertificateBuffer, size_t encodedCertificateBufferSize ) noexcept
            : context_( nullptr )
        {
            context_ = CertCreateCertificateContext( encodingType.Value( ), encodedCertificateBuffer, static_cast<DWORD>(encodedCertificateBufferSize) );
            if ( context_ == nullptr && encodedCertificateBuffer != nullptr )
            {
                ThrowLastOSError( );
            }
        }
        


        CertificateContext( const CertificateContext& other ) = delete;
        constexpr CertificateContext( CertificateContext&& other ) noexcept
            : context_( other.context_ )
        {
            other.context_ = nullptr;
        }

        ~CertificateContext( )
        {
            if ( context_ )
            {
                CertFreeCertificateContext( context_ );
            }
        }


        CertificateContext& operator = ( const CertificateContext& other ) = delete;
        constexpr CertificateContext& operator = ( CertificateContext&& other ) noexcept
        {
            std::swap( context_, other.context_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return context_ != nullptr;
        }

        constexpr PCCERT_CONTEXT Handle( ) const noexcept
        {
            return context_;
        }


        CertificateContext Clone( ) const
        {
            if ( context_ ) [[likely]]
            {
                auto context = CertDuplicateCertificateContext( context_ );
                CertificateContext result( context );
                return result;
            }
            else
            {
                return CertificateContext( );
            }
        }

        [[nodiscard]] PCCERT_CONTEXT Release( )
        {
            auto tmp = context_;
            context_ = nullptr;
            return tmp;
        }

        void Assign( PCCERT_CONTEXT context, bool clone = true )
        {
            if ( context_ != context )
            {
                if ( context_ )
                {
                    CertFreeCertificateContext( context_ );
                }
                if ( context && clone )
                {
                    context_ = CertDuplicateCertificateContext( context );
                }
                else
                {
                    context_ = context;
                }
            }
        }

        CertificateContext& operator = ( PCCERT_CONTEXT context )
        {
            Assign( context );
            return *this;
        }


        /// <summary>
        /// Adds a usage identifier object identifier (OID) to the enhanced key usage (EKU) extended property of the certificate.
        /// </summary>
        /// <param name="usageIdentifier">
        /// Specifies the usage identifier OID to add.
        /// </param>
        void AddEnhancedKeyUsageIdentifier(const char* usageIdentifier ) const
        {
            auto rc = CertAddEnhancedKeyUsageIdentifier( context_, usageIdentifier );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        void DeleteFromStore( ) const
        {
            auto rc = CertDeleteCertificateFromStore( context_ );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /*
        void RetrieveLogoOrBiometricInfo( CertificateRetrievalType certificateRetrievalType, RetrievalFlags retrievalFlags ) const
        {
            auto rc = CertRetrieveLogoOrBiometricInfo( context_, (LPCSTR)certificateRetrievalType, );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        */
    };


    /// <summary>
    /// 
    /// </summary>
    /// <param name="url">
    /// </param>
    /// <param name="contextObjectType">
    /// </param>
    /// <param name="retrievalFlags">
    /// </param>
    /// <param name="timeoutInMillis">
    /// </param>
    /// <param name="ppvObject">
    /// </param>
    /// <param name="certificateContext">
    /// </param>
    /// <param name="pRETRIEVE_AUX_INFO">
    /// </param>
    /// <returns></returns>
    inline bool RetrieveObjectByUrl( const wchar_t* url, ContextObjectType contextObjectType, RetrievalFlags retrievalFlags, DWORD timeoutInMillis, LPVOID* ppvObject, const CertificateContext& certificateContext = CertificateContext( ), PCRYPT_RETRIEVE_AUX_INFO pRETRIEVE_AUX_INFO = nullptr )
    {
        auto rc = CryptRetrieveObjectByUrlW( url, (LPCSTR)contextObjectType, static_cast<DWORD>( retrievalFlags ), timeoutInMillis, ppvObject, 0 ,nullptr, (LPVOID)certificateContext.Handle(), pRETRIEVE_AUX_INFO );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return true;
    }


    /// <summary>
    /// A wrapper for the Windows PCCERT_CHAIN_CONTEXT type
    /// which contains an array of simple certificate chains 
    /// and a trust status structure that indicates summary 
    /// validity data on all of the connected simple chains.
    /// </summary>
    class CertificateChain
    {
        PCCERT_CHAIN_CONTEXT context_;
    public:
        constexpr CertificateChain( ) noexcept
            : context_( nullptr )
        {
        }

        constexpr explicit CertificateChain( PCCERT_CHAIN_CONTEXT context ) noexcept
            : context_( context )
        {
        }


        CertificateChain( const CertificateChain& other ) = delete;
        constexpr CertificateChain( CertificateChain&& other ) noexcept
            : context_( other.context_ )
        {
            other.context_ = nullptr;
        }

        ~CertificateChain( )
        {
            if ( context_ )
            {
                CertFreeCertificateChain( context_ );
            }
        }


        CertificateChain& operator = ( const CertificateChain& other ) = delete;
        constexpr CertificateChain& operator = ( CertificateChain&& other ) noexcept
        {
            std::swap( context_, other.context_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return context_ != nullptr;
        }

        constexpr PCCERT_CHAIN_CONTEXT Handle( ) const noexcept
        {
            return context_;
        }


        CertificateChain Clone( ) const
        {
            if ( context_ ) [[likely]]
            {
                auto context = CertDuplicateCertificateChain( context_ );
                CertificateChain result( context );
                return result;
            }
            else
            {
                return CertificateChain( );
            }
        }

        [[nodiscard]] PCCERT_CHAIN_CONTEXT Release( )
        {
            auto tmp = context_;
            context_ = nullptr;
            return tmp;
        }

        void Assign( PCCERT_CHAIN_CONTEXT context, bool clone = true )
        {
            if ( context_ != context )
            {
                if ( context_ )
                {
                    CertFreeCertificateChain( context_ );
                }
                if ( context && clone )
                {
                    context_ = CertDuplicateCertificateChain( context );
                }
                else
                {
                    context_ = context;
                }
            }
        }

        CertificateChain& operator = ( PCCERT_CHAIN_CONTEXT context )
        {
            Assign( context );
            return *this;
        }
    };


    /// <summary>
    /// Contains an encoded OCSP response.
    /// </summary>
    class ServerOcspResponseContext
    {
        CERT_SERVER_OCSP_RESPONSE_CONTEXT* context_;
    public:
        constexpr ServerOcspResponseContext( ) noexcept
            : context_( nullptr )
        {
        }

        constexpr explicit ServerOcspResponseContext( CERT_SERVER_OCSP_RESPONSE_CONTEXT* context ) noexcept
            : context_( context )
        {
        }


        ServerOcspResponseContext( const ServerOcspResponseContext& other ) = delete;
        constexpr ServerOcspResponseContext( ServerOcspResponseContext&& other ) noexcept
            : context_( other.context_ )
        {
            other.context_ = nullptr;
        }

        ~ServerOcspResponseContext( )
        {
            if ( context_ )
            {
                CertFreeServerOcspResponseContext( context_ );
            }
        }


        ServerOcspResponseContext& operator = ( const ServerOcspResponseContext& other ) = delete;
        constexpr ServerOcspResponseContext& operator = ( ServerOcspResponseContext&& other ) noexcept
        {
            std::swap( context_, other.context_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return context_ != nullptr;
        }

        constexpr CERT_SERVER_OCSP_RESPONSE_CONTEXT* Handle( ) const noexcept
        {
            return context_;
        }



        [[nodiscard]] CERT_SERVER_OCSP_RESPONSE_CONTEXT* Release( )
        {
            auto tmp = context_;
            context_ = nullptr;
            return tmp;
        }

        void Assign( CERT_SERVER_OCSP_RESPONSE_CONTEXT* context )
        {
            if ( context_ != context )
            {
                if ( context_ )
                {
                    CertFreeServerOcspResponseContext( context_ );
                }
                context_ = context;
            }
        }

        ServerOcspResponseContext& operator = ( CERT_SERVER_OCSP_RESPONSE_CONTEXT* context )
        {
            Assign( context );
            return *this;
        }
    };


    /// <summary>
    /// Represents a handle to an OCSP response associated 
    /// with a server certificate chain.
    /// </summary>
    class ServerOcspResponse
    {
        HCERT_SERVER_OCSP_RESPONSE response_;
    public:
        constexpr ServerOcspResponse( ) noexcept
            : response_( nullptr )
        {
        }

        constexpr explicit ServerOcspResponse( HCERT_SERVER_OCSP_RESPONSE response ) noexcept
            : response_( response )
        {
        }


        ServerOcspResponse( const ServerOcspResponse& other ) = delete;
        constexpr ServerOcspResponse( ServerOcspResponse&& other ) noexcept
            : response_( other.response_ )
        {
            other.response_ = nullptr;
        }

        ~ServerOcspResponse( )
        {
            if ( response_ )
            {
                CertCloseServerOcspResponse( response_, 0 );
            }
        }


        ServerOcspResponse& operator = ( const ServerOcspResponse& other ) = delete;
        constexpr ServerOcspResponse& operator = ( ServerOcspResponse&& other ) noexcept
        {
            std::swap( response_, other.response_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return response_ != nullptr;
        }

        constexpr HCERT_SERVER_OCSP_RESPONSE Handle( ) const noexcept
        {
            return response_;
        }


        ServerOcspResponse Clone( ) const
        {
            if ( response_ ) [[likely]]
            {
                CertAddRefServerOcspResponse( response_ );
                ServerOcspResponse result( response_ );
                return result;
            }
            else
            {
                return ServerOcspResponse( );
            }
        }

        [[nodiscard]] HCERT_SERVER_OCSP_RESPONSE Release( )
        {
            auto tmp = response_;
            response_ = nullptr;
            return tmp;
        }

        void Assign( HCERT_SERVER_OCSP_RESPONSE response, bool clone = true )
        {
            if ( response_ != response )
            {
                if ( response_ )
                {
                    CertCloseServerOcspResponse( response_, 0 );
                }
                if ( response && clone )
                {
                    CertAddRefServerOcspResponse( response );
                    response_ = response;
                }
                else
                {
                    response_ = response;
                }
            }
        }

        ServerOcspResponse& operator = ( HCERT_SERVER_OCSP_RESPONSE response )
        {
            Assign( response );
            return *this;
        }
    };


    /// <summary>
    /// Represents a chain engine for an application. A chain 
    /// engine restricts the certificates in the root store 
    /// that can be used for verification, restricts the certificate 
    /// stores to be searched for certificates and certificate trust 
    /// lists (CTLs), sets a time-out limit for searches that involve 
    /// URLs, and limits the number of certificates checked between 
    /// checking for a certificate cycle.
    /// </summary>
    class CertificateChainEngine
    {
        HCERTCHAINENGINE engine_;
    public:
        constexpr CertificateChainEngine( ) noexcept
            : engine_( nullptr )
        {
        }

        constexpr explicit CertificateChainEngine( HCERTCHAINENGINE engine ) noexcept
            : engine_( engine )
        {
        }


        CertificateChainEngine( const CertificateChainEngine& other ) = delete;
        constexpr CertificateChainEngine( CertificateChainEngine&& other ) noexcept
            : engine_( other.engine_ )
        {
            other.engine_ = nullptr;
        }

        ~CertificateChainEngine( )
        {
            if ( engine_ )
            {
                CertFreeCertificateChainEngine( engine_ );
            }
        }


        CertificateChainEngine& operator = ( const CertificateChainEngine& other ) = delete;
        constexpr CertificateChainEngine& operator = ( CertificateChainEngine&& other ) noexcept
        {
            std::swap( engine_, other.engine_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return engine_ != nullptr;
        }

        constexpr HCERTCHAINENGINE Handle( ) const noexcept
        {
            return engine_;
        }



        [[nodiscard]] HCERTCHAINENGINE Release( )
        {
            auto tmp = engine_;
            engine_ = nullptr;
            return tmp;
        }

        void Assign( HCERTCHAINENGINE engine, bool clone = true )
        {
            if ( engine_ != engine )
            {
                if ( engine_ )
                {
                    CertFreeCertificateChainEngine( engine_ );
                }
                engine_ = engine;
            }
        }

        CertificateChainEngine& operator = ( HCERTCHAINENGINE engine )
        {
            Assign( engine );
            return *this;
        }
    };



    /// <summary>
    /// A wrapper for the Windows PCCTL_CONTEXT type 
    /// which contains both the encoded and decoded 
    /// representations of a CTL. It also contains an 
    /// opened HCRYPTMSG handle to the decoded, 
    /// cryptographically signed message containing the 
    /// CTL_INFO as its inner content.
    /// </summary>
    class CertificateTrustList
    {
        PCCTL_CONTEXT context_;
    public:
        constexpr CertificateTrustList( ) noexcept
            : context_( nullptr )
        {
        }

        constexpr explicit CertificateTrustList( PCCTL_CONTEXT context ) noexcept
            : context_( context )
        {
        }


        CertificateTrustList( const CertificateTrustList& other ) = delete;
        constexpr CertificateTrustList( CertificateTrustList&& other ) noexcept
            : context_( other.context_ )
        {
            other.context_ = nullptr;
        }

        ~CertificateTrustList( )
        {
            if ( context_ )
            {
                CertFreeCTLContext( context_ );
            }
        }


        CertificateTrustList& operator = ( const CertificateTrustList& other ) = delete;
        constexpr CertificateTrustList& operator = ( CertificateTrustList&& other ) noexcept
        {
            std::swap( context_, other.context_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return context_ != nullptr;
        }

        constexpr PCCTL_CONTEXT Handle( ) const noexcept
        {
            return context_;
        }


        CertificateTrustList Clone( ) const
        {
            if ( context_ ) [[likely]]
            {
                auto context = CertDuplicateCTLContext( context_ );
                CertificateTrustList result( context );
                return result;
            }
            else
            {
                return CertificateTrustList( );
            }
        }

        [[nodiscard]] PCCTL_CONTEXT Release( )
        {
            auto tmp = context_;
            context_ = nullptr;
            return tmp;
        }

        void Assign( PCCTL_CONTEXT context, bool clone = true )
        {
            if ( context_ != context )
            {
                if ( context_ )
                {
                    CertFreeCTLContext( context_ );
                }
                if ( context && clone )
                {
                    context_ = CertDuplicateCTLContext( context );
                }
                else
                {
                    context_ = context;
                }
            }
        }

        CertificateTrustList& operator = ( PCCTL_CONTEXT context )
        {
            Assign( context );
            return *this;
        }
    };



    /// <summary>
    /// Contains both the encoded and decoded 
    /// representations of a certificate revocation 
    /// list (CRL)
    /// </summary>
    class CertificateRevocationList
    {
        PCCRL_CONTEXT context_;
    public:
        constexpr CertificateRevocationList( ) noexcept
            : context_( nullptr )
        {
        }

        constexpr explicit CertificateRevocationList( PCCRL_CONTEXT context ) noexcept
            : context_( context )
        {
        }




        CertificateRevocationList( const CertificateRevocationList& other ) = delete;
        constexpr CertificateRevocationList( CertificateRevocationList&& other ) noexcept
            : context_( other.context_ )
        {
            other.context_ = nullptr;
        }

        ~CertificateRevocationList( )
        {
            if ( context_ )
            {
                CertFreeCRLContext( context_ );
            }
        }


        CertificateRevocationList& operator = ( const CertificateRevocationList& other ) = delete;
        constexpr CertificateRevocationList& operator = ( CertificateRevocationList&& other ) noexcept
        {
            std::swap( context_, other.context_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return context_ != nullptr;
        }

        constexpr PCCRL_CONTEXT Handle( ) const noexcept
        {
            return context_;
        }


        CertificateRevocationList Clone( ) const
        {
            if ( context_ ) [[likely]]
            {
                auto context = CertDuplicateCRLContext( context_ );
                CertificateRevocationList result( context );
                return result;
            }
            else
            {
                return CertificateRevocationList( );
            }
        }

        [[nodiscard]] PCCRL_CONTEXT Release( )
        {
            auto tmp = context_;
            context_ = nullptr;
            return tmp;
        }

        void Assign( PCCRL_CONTEXT context, bool clone = true )
        {
            if ( context_ != context )
            {
                if ( context_ )
                {
                    CertFreeCRLContext( context_ );
                }
                if ( context && clone )
                {
                    context_ = CertDuplicateCRLContext( context );
                }
                else
                {
                    context_ = context;
                }
            }
        }

        CertificateRevocationList& operator = ( PCCRL_CONTEXT context )
        {
            Assign( context );
            return *this;
        }
    };

    /// <summary>
    /// Specifies the action to take if a matching certificate 
    /// or a link to a matching certificate already exists in the 
    /// store.
    /// </summary>
    enum class CertificateStoreAddFlags : DWORD
    {
        /// <summary>
        /// If a matching certificate or a link to a matching 
        /// certificate exists, the operation fails.
        /// </summary>
        New = CERT_STORE_ADD_NEW,
        /// <summary>
        /// If a matching certificate or a link to a matching 
        /// certificate exists, that existing certificate or link 
        /// is used and properties from the new certificate are 
        /// added. The function does not fail, but it does not 
        /// add a new context.
        /// </summary>
        UseExisting = CERT_STORE_ADD_USE_EXISTING,
        /// <summary>
        /// If a link to a matching certificate exists, that existing 
        /// certificate or link is deleted and a new certificate is 
        /// created and added to the store. If a matching certificate 
        /// or a link to a matching certificate does not exist, a 
        /// new link is added.
        /// </summary>
        ReplaceExisting = CERT_STORE_ADD_REPLACE_EXISTING,
        /// <summary>
        /// The function makes no check for an existing matching 
        /// certificate or link to a matching certificate. A new 
        /// certificate is always added to the store. This can 
        /// lead to duplicates in a store.
        /// </summary>
        Always = CERT_STORE_ADD_ALWAYS,
        /// <summary>
        /// If a matching certificate exists in the store, the 
        /// existing context is not replaced. The existing 
        /// context inherits properties from the new certificate.
        /// </summary>
        ReplaceExistingInheritProperties = CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES,
        /// <summary>
        /// <p>
        /// If a matching certificate or a link to a matching 
        /// certificate exists and the NotBefore time of the 
        /// existing context is equal to or greater than the 
        /// NotBefore time of the new context being added, the 
        /// operation fails and GetLastError returns the 
        /// CRYPT_E_EXISTS code.
        /// </p>
        /// <p>
        /// If the NotBefore time of the existing context is less 
        /// than the NotBefore time of the new context being added, 
        /// the existing certificate or link is deleted and a new 
        /// certificate is created and added to the store. If a 
        /// matching certificate or a link to a matching certificate 
        /// does not exist, a new link is added.
        /// </p>
        /// <p>
        /// If certificate revocation lists( CRLs ) or certificate trust 
        /// list( CTLs ) are being compared, the ThisUpdate time is used.
        /// </p>
        /// </summary>
        Newer = CERT_STORE_ADD_NEWER,
        /// <summary>
        /// <p>
        /// If a matching certificate or a link to a matching 
        /// certificate exists and the NotBefore time of the existing 
        /// context is equal to or greater than the NotBefore time 
        /// of the new context being added, the operation fails and 
        /// GetLastError returns the CRYPT_E_EXISTS code.
        /// </p>
        /// <p>
        /// If the NotBefore time of the existing context is less than 
        /// the NotBefore time of the new context being added, the existing 
        /// context is deleted before creatingand adding the new context. 
        /// The new added context inherits properties from the existing 
        /// certificate.
        /// </p>
        /// <p>
        /// If CRLs or CTLs are being compared, the ThisUpdate time is used.
        /// </p>
        /// </summary>
        NewerInheritProperties = CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES
    };

    enum class CertificateStoreProperties : DWORD
    {
        LocalizedName = CERT_STORE_LOCALIZED_NAME_PROP_ID
    };


    enum class CertificateStoreCloseFlags : DWORD
    {
        None = 0,
        Check = CERT_CLOSE_STORE_CHECK_FLAG,
        Force = CERT_CLOSE_STORE_FORCE_FLAG
    };


    enum class CertificateStoreLocation : DWORD
    { 
        CurrentUser = CERT_SYSTEM_STORE_CURRENT_USER,
        CurrentService = CERT_SYSTEM_STORE_CURRENT_SERVICE,
        LocalMachine = CERT_SYSTEM_STORE_LOCAL_MACHINE,
        LocalMachineGroupPolicy = CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY,
        CurrentUserGroupPolicy = CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY,
        Services = CERT_SYSTEM_STORE_SERVICES,
        Users = CERT_SYSTEM_STORE_USERS,
        LocalMachineEnterprise = CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE
    };


    /// <summary>
    /// A storage for certificates, certificate revocation 
    /// lists (CRLs), and certificate trust lists (CTLs).
    /// </summary>
    class CertificateStore
    {
        HCERTSTORE store_;
    public:
        constexpr CertificateStore() noexcept
            : store_(nullptr)
        { }

        constexpr explicit CertificateStore( HCERTSTORE store ) noexcept
            : store_( store )
        {
        }

        CertificateStore( const CertificateStore& other ) = delete;
        constexpr CertificateStore( CertificateStore&& other ) noexcept
            : store_( other.store_ )
        {
            other.store_ = nullptr;
        }

        ~CertificateStore( )
        {
            if ( store_ )
            {
                CertCloseStore( store_, 0 );
            }
        }

        void Close( CertificateStoreCloseFlags flags )
        {
            if ( store_ )
            {
                auto rc = CertCloseStore( store_, static_cast<DWORD>( flags ) );
                store_ = nullptr;
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                
            }
        }


        CertificateStore& operator = ( const CertificateStore& other ) = delete;
        constexpr CertificateStore& operator = ( CertificateStore&& other ) noexcept
        {
            std::swap( store_, other.store_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return store_ != nullptr;
        }

        constexpr HCERTSTORE Handle( ) const noexcept
        {
            return store_;
        }


        CertificateStore Clone( ) const
        {
            if ( store_ )[[likely]]
            {
                auto store = CertDuplicateStore( store_ );
                CertificateStore result( store );
                return result;
            }
            else
            {
                return CertificateStore( );
            }
        }

        [[nodiscard]] HCERTSTORE Release( )
        {
            auto tmp = store_;
            store_ = nullptr;
            return tmp;
        }

        void Assign( HCERTSTORE store, bool clone = true )
        {
            if ( store_ != store )
            {
                if ( store_ )
                {
                    CertCloseStore( store_, 0 );
                    
                }
                if ( store && clone )
                {
                    store_ = CertDuplicateStore( store );
                }
                else
                {
                    store_ = store;
                }
            }
        }

        CertificateStore& operator = ( HCERTSTORE store )
        {
            Assign( store );
            return *this;
        }

        /// <summary>
        /// Opens a common certificate store
        /// </summary>
        /// <param name="systemStoreName">The name of the certificate store</param>
        /// <returns>The opened CertificateStore</returns>
        static [[nodiscard]] CertificateStore OpenSystemStore( const char* systemStoreName )
        {
            auto store = CertOpenSystemStoreA( 0, systemStoreName );
            if ( !store )
            {
                ThrowLastOSError( );
            }
            CertificateStore result( store );
            return result;
        }

        
        /// <summary>
        /// Retrives the list of system certificate store 
        /// names assocciated with the specified certificate store
        /// location.
        /// </summary>
        /// <param name="certificateStoreLocation">The identifier for the certificate store location</param>
        /// <param name="result">
        /// A reference to a std::vector&ltstd::wstring&gt that
        /// will be filled with the names of the requested 
        /// certificate stores.
        /// </param>
        static void GetSystemStoreNames( CertificateStoreLocation certificateStoreLocation, std::vector<WideString>& result )
        {
            auto rc = CertEnumSystemStore( static_cast<DWORD>( certificateStoreLocation ), nullptr,
                &result,
                []( const void* pvSystemStore,
                    DWORD dwFlags,
                    PCERT_SYSTEM_STORE_INFO pStoreInfo,
                    void* pvReserved,
                    void* pvArg )->BOOL
            {
                auto* vector = ( std::vector<WideString>* )pvArg;
                const wchar_t* storeName = (const wchar_t*)pvSystemStore;
                if ( storeName && storeName[0] )
                {
                    vector->emplace_back( storeName );
                }
                return TRUE;
            });

            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


        void GetCertificates( std::vector<CertificateContext>& result ) const
        {
            PCCERT_CONTEXT certContext = nullptr;
            PCCERT_CONTEXT prevCertContext = nullptr;
            do
            {
                certContext = CertEnumCertificatesInStore( store_, prevCertContext );
                if ( certContext )
                {
                    auto ctx = CertDuplicateCertificateContext( certContext );
                    result.emplace_back( CertificateContext( ctx ) );
                }
                prevCertContext = certContext;
            } while ( certContext != nullptr );
        }
        std::vector<CertificateContext> GetCertificates( ) const
        {
            std::vector<CertificateContext> result;
            GetCertificates( result );
            return result;
        }



        void GetCertificateRevocationLists( std::vector<CertificateRevocationList>& result ) const
        {
            PCCRL_CONTEXT context = nullptr;
            PCCRL_CONTEXT prevContext = nullptr;
            do
            {
                context = CertEnumCRLsInStore( store_, prevContext );
                if ( context )
                {
                    auto ctx = CertDuplicateCRLContext( context );
                    result.emplace_back( CertificateRevocationList( ctx ) );
                }
                prevContext = context;
            } while ( context != nullptr );
        }
        std::vector<CertificateRevocationList> GetCertificateRevocationLists( ) const
        {
            std::vector<CertificateRevocationList> result;
            GetCertificateRevocationLists( result );
            return result;
        }


        void GetCertificateTrustLists( std::vector<CertificateTrustList>& result ) const
        {
            PCCTL_CONTEXT context = nullptr;
            PCCTL_CONTEXT prevContext = nullptr;
            do
            {
                context = CertEnumCTLsInStore( store_, prevContext );
                if ( context )
                {
                    auto ctx = CertDuplicateCTLContext( context );
                    result.emplace_back( CertificateTrustList( ctx ) );
                }
                prevContext = context;
            } while ( context != nullptr );
        }
        std::vector<CertificateTrustList> GetCertificateTrustLists( ) const
        {
            std::vector<CertificateTrustList> result;
            GetCertificateTrustLists( result );
            return result;
        }






        /// <summary>
        /// Adds a certificate context to the certificate store.
        /// </summary>
        /// <param name="certificateContext">
        /// The constext of the certificate to be added to the store
        /// </param>
        /// <param name="flags">
        /// Specifies the action to take if a matching certificate 
        /// or a link to a matching certificate already exists in 
        /// the store.
        /// </param>
        /// <returns>The constext of the certificate added to the store</returns>
        CertificateContext Add( CertificateContext certificateContext, CertificateStoreAddFlags flags )
        {
            PCCERT_CONTEXT context = nullptr;
            auto rc = CertAddCertificateContextToStore( store_, certificateContext.Handle( ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateContext result( context );
            return result;
        }

        /// <summary>
        /// Adds a link in a certificate store to a certificate 
        /// context in a different store. Instead of creating and 
        /// adding a duplicate of the certificate context, this 
        /// function adds a link to the original certificate.
        /// </summary>
        /// <param name="certificateContext">
        /// The constext of the certificate to link to the store
        /// </param>
        /// <param name="flags">
        /// Specifies the action to take if a matching certificate 
        /// or a link to a matching certificate already exists in 
        /// the store.
        /// </param>
        /// <returns>The constext of the certificate added to the store</returns>
        CertificateContext AddLink( CertificateContext certificateContext, CertificateStoreAddFlags flags )
        {
            PCCERT_CONTEXT context = nullptr;
            auto rc = CertAddCertificateLinkToStore( store_, certificateContext.Handle( ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateContext result( context );
            return result;
        }

        /// <summary>
        /// Adds a certificate revocation list (CRL) context to the store
        /// </summary>
        /// <param name="certificateRevocationList">
        /// The certificate revocation list to be added
        /// </param>
        /// <param name="flags">
        /// Specifies the action to take if a matching 
        /// certificate revocation list or a link to a matching 
        /// certificate revocation list already exists in the store.
        /// </param>
        /// <returns>The CertificateRevocationList added to the store.</returns>
        CertificateRevocationList Add( CertificateRevocationList certificateRevocationList, CertificateStoreAddFlags flags )
        {
            PCCRL_CONTEXT context = nullptr;
            auto rc = CertAddCRLContextToStore( store_, certificateRevocationList.Handle( ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateRevocationList result( context );
            return result;
        }

        CertificateRevocationList AddLink( CertificateRevocationList certificateRevocationList, CertificateStoreAddFlags flags )
        {
            PCCRL_CONTEXT context = nullptr;
            auto rc = CertAddCRLLinkToStore( store_, certificateRevocationList.Handle( ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateRevocationList result( context );
            return result;
        }


        CertificateTrustList Add( CertificateTrustList certificateTrustList, CertificateStoreAddFlags flags )
        {
            PCCTL_CONTEXT context = nullptr;
            auto rc = CertAddCTLContextToStore( store_, certificateTrustList.Handle( ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateTrustList result( context );
            return result;
        }

        CertificateTrustList AddLink( CertificateTrustList certificateTrustList, CertificateStoreAddFlags flags )
        {
            PCCTL_CONTEXT context = nullptr;
            auto rc = CertAddCTLLinkToStore( store_, certificateTrustList.Handle( ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateTrustList result( context );
            return result;
        }

        CertificateContext AddEncodedCertificate( const EncodingType& encodingType, const Byte* encodedBuffer, size_t encodedBufferLength, CertificateStoreAddFlags flags )
        {
            PCCERT_CONTEXT context = nullptr;
            auto rc = CertAddEncodedCertificateToStore( store_, encodingType.Value(), encodedBuffer, static_cast<DWORD>( encodedBufferLength ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateContext result( context );
            return result;
        }

        CertificateRevocationList AddEncodedCertificateRevocationList( const EncodingType& encodingType, const Byte* encodedBuffer, size_t encodedBufferLength, CertificateStoreAddFlags flags )
        {
            PCCRL_CONTEXT context = nullptr;
            auto rc = CertAddEncodedCRLToStore( store_, encodingType.Value( ), encodedBuffer, static_cast<DWORD>( encodedBufferLength ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateRevocationList result( context );
            return result;
        }

        CertificateTrustList AddEncodedCertificateTrustList( const EncodingType& encodingType, const Byte* encodedBuffer, size_t encodedBufferLength, CertificateStoreAddFlags flags )
        {
            PCCTL_CONTEXT context = nullptr;
            auto rc = CertAddEncodedCTLToStore( store_, encodingType.Value( ), encodedBuffer, static_cast<DWORD>( encodedBufferLength ), static_cast<DWORD>( flags ), &context );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            CertificateTrustList result( context );
            return result;
        }

        static void AddEncodedCertificateToSystemStore(const char* certificateStoreName, const Byte* encodedBuffer, size_t encodedBufferLength )
        {
            auto rc = CertAddEncodedCertificateToSystemStoreA( certificateStoreName, encodedBuffer, static_cast<DWORD>(encodedBufferLength) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        static void AddEncodedCertificateToSystemStore( const wchar_t* certificateStoreName, const Byte* encodedBuffer, size_t encodedBufferLength )
        {
            auto rc = CertAddEncodedCertificateToSystemStoreW( certificateStoreName, encodedBuffer, static_cast<DWORD>( encodedBufferLength ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }




    };



}

#endif
