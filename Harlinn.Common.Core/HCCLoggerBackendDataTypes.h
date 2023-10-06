#pragma once
#ifndef __HCCLOGGERBACKENDDATATYPES_H__
#define __HCCLOGGERBACKENDDATATYPES_H__

#include <HCCDateTime.h>
#include <HCCGuid.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::Logging
{

    template<typename DerivedT>
    class BackendObject
    {
    public:
        using DerivedType = DerivedT;

        BackendObject( )
        { }

        const DerivedType& Derived( ) const noexcept
        {
            return static_cast<const DerivedType&>( *this );
        }
        DerivedType& Derived( ) noexcept
        {
            return static_cast<DerivedType&>( *this );
        }


        template<typename ReaderT>
        void Read( ReaderT& reader )
        {
            auto& derived = static_cast<DerivedT&>( *this );
            derived.ReadKey( reader );
            derived.ReadData( reader );
        }

        template<typename WriterT>
        void Write( WriterT& writer ) const
        {
            auto& derived = static_cast<const DerivedT&>( *this );
            derived.WriteKey( writer );
            derived.WriteData( writer );
        }
    };

    template<typename DerivedT>
    class Identified : public BackendObject< DerivedT >
    {
    public:
        using Base = BackendObject< DerivedT >;
    private:
        Guid id_;
    public:
        using PrimaryKeyType = Guid;

        Identified( )
        {
        }

        Identified( const Guid& id )
            : id_( id )
        {
        }


        void Assign( const Guid& id )
        {
            id_ = id;
        }

        template<typename ReaderT>
        void ReadKey( ReaderT& reader )
        {
            reader.Read( id_ );
        }

        template<typename WriterT>
        void WriteKey( WriterT& writer ) const
        {
            writer.Write( id_ );
        }

        const PrimaryKeyType& PrimaryKey( ) const noexcept
        {
            return id_;
        }
        void SetPrimaryKey( const PrimaryKeyType& id ) noexcept
        {
            id_ = id;
        }


        const Guid& Id( ) const noexcept
        {
            return id_;
        }
        void SetId( const Guid& id ) noexcept
        {
            id_ = id;
        }
    };




    class BackendDomainObject : public Identified<BackendDomainObject>
    {
    public:
        using Base = Identified<BackendDomainObject>;
    private:
        WideString domainName_;
        WideString name_;
    public:
        BackendDomainObject( )
        {
        }

        BackendDomainObject( const Guid& id, const WideString& domainName, const WideString& name )
            : Base( id ), domainName_( domainName ), name_( name )
        {
        }

        template<typename ReaderT>
        void ReadData( ReaderT& reader )
        {
            reader.Read( domainName_ );
            reader.Read( name_ );
        }

        template<typename WriterT>
        void WriteData( WriterT& writer ) const
        {
            writer.Write( domainName_ );
            writer.Write( name_ );
        }

        void AddTo( XXH64Hasher& hasher ) const noexcept
        {
            hasher.Add( domainName_.c_str(), domainName_.size() );
            hasher.Add( name_.c_str( ), name_.size( ) );
        }

        size_t Hash( ) const noexcept
        {
            XXH64Hasher hasher;
            AddTo( hasher );
            auto result = hasher.Digest( );
            return result;
        }


        void Assign( const Guid& id, const WideString& domainName, const WideString& name )
        {
            Base::Assign( id );
            domainName_ = domainName;
            name_ = name;
        }

        const WideString& DomainName( ) const noexcept
        {
            return domainName_;
        }
        void SetDomainName( const WideString& domainName )
        {
            domainName_ = domainName;
        }

        const WideString& Name( ) const noexcept
        {
            return name_;
        }
        void SetName( const WideString& name )
        {
            name_ = name;
        }
    };
    using BackendComputerInfo = BackendDomainObject;
    using BackendUserInfo = BackendDomainObject;

    HCC_EXPORT BackendComputerInfo GetBackendComputerInfo( );
    HCC_EXPORT BackendUserInfo GetBackendUserInfo( );


    class BackendExecutableInfo : public Identified<BackendExecutableInfo>
    {
    public:
        using Base = Identified<BackendExecutableInfo>;
    private:
        WideString path_;
    public:
        BackendExecutableInfo()
        { }

        BackendExecutableInfo( const Guid& id, const WideString& path )
            : Base(id), path_( path )
        {
        }


        void Assign( const Guid& id, const WideString& path )
        {
            Base::Assign( id );
            path_ = path;
        }

        template<typename ReaderT>
        void ReadData( ReaderT& reader )
        {
            reader.Read( path_ );
        }

        template<typename WriterT>
        void WriteData( WriterT& writer ) const
        {
            writer.Write( path_ );
        }

        void AddTo( XXH64Hasher& hasher ) const noexcept
        {
            hasher.Add( path_.c_str(), path_.size() * sizeof(WideString::value_type) );
        }

        size_t Hash( ) const noexcept
        {
            XXH64Hasher hasher;
            AddTo( hasher );
            auto result = hasher.Digest( );
            return result;
        }

        const WideString& Path( ) const noexcept
        {
            return path_;
        }
        void SetPath( const WideString& path )
        {
            path_ = path;
        }
    };

    HCC_EXPORT BackendExecutableInfo GetBackendExecutableInfo( );




    class BackendConfigurationFileInfo : public Identified<BackendConfigurationFileInfo>
    {
    public:
        using Base = Identified<BackendConfigurationFileInfo>;
    private:
        WideString path_;
        WideString data_;
    public:
        BackendConfigurationFileInfo( )
        {
        }

        BackendConfigurationFileInfo( const Guid& id, const WideString& path, const WideString& data )
            : Base( id ), path_( path ), data_( data )
        {
        }


        void Assign( const Guid& id, const WideString& path, const WideString& data )
        {
            Base::Assign( id );
            path_ = path;
            data_ = data;
        }

        template<typename ReaderT>
        void ReadData( ReaderT& reader )
        {
            reader.Read( path_ );
            reader.Read( data_ );
        }

        template<typename WriterT>
        void WriteData( WriterT& writer ) const
        {
            writer.Write( path_ );
            writer.Write( data_ );
        }

        void AddTo( XXH64Hasher& hasher ) const noexcept
        {
            hasher.Add( path_.c_str(), path_.size() * sizeof(WideString::value_type) );
            hasher.Add( data_.c_str( ), data_.size( ) * sizeof( WideString::value_type ) );
        }

        size_t Hash( ) const noexcept
        {
            XXH64Hasher hasher;
            AddTo( hasher );
            auto result = hasher.Digest( );
            return result;
        }

        const WideString& Path( ) const noexcept
        {
            return path_;
        }
        void SetPath( const WideString& path )
        {
            path_ = path;
        }

        const WideString& Data( ) const noexcept
        {
            return data_;
        }
        void SetData( const WideString& data )
        {
            data_ = data;
        }

    };



    class BackendWindowsVersionInfoKey
    {
        Guid id_;
        DateTime timeStamp_;
    public:
        BackendWindowsVersionInfoKey()
        { }

        BackendWindowsVersionInfoKey( const Guid& id, const DateTime& timeStamp )
            : id_( id ), timeStamp_( timeStamp )
        {
        }

        auto operator<=>( const BackendWindowsVersionInfoKey& ) const = default;

        void Assign( Guid id, const DateTime& timeStamp )
        {
            id_ = id;
            timeStamp_ = timeStamp;
        }


        template<typename ReaderT>
        void Read( ReaderT& reader )
        {
            reader.Read( id_ );
            reader.Read( timeStamp_ );
        }

        template<typename WriterT>
        void Write( WriterT& writer ) const
        {
            writer.Write( id_ );
            writer.Write( timeStamp_ );
        }

        constexpr const Guid& Id( ) const noexcept
        {
            return id_;
        }
        constexpr void SetId( const Guid& id ) noexcept
        {
            id_ = id;
        }

        constexpr DateTime TimeStamp( ) const noexcept
        {
            return timeStamp_;
        }
        constexpr void SetTimeStamp( const DateTime& timeStamp ) noexcept
        {
            timeStamp_ = timeStamp;
        }

    };

    class BackendWindowsVersionInfo : public BackendObject<BackendWindowsVersionInfo>
    {
    public:
        using PrimaryKeyType = BackendWindowsVersionInfoKey;
    private:
        PrimaryKeyType primaryKey_;
        UInt32 majorVersion_ = 0;
        UInt32 minorVersion_ = 0;
        UInt32 buildNumber_ = 0;
        UInt32 platformId_ = 0;
        WideString csdVersion_;
        UInt16 servicePackMajor_ = 0;
        UInt16 servicePackMinor_ = 0;
        UInt16 suiteMask_ = 0;
        Byte  productType_ = 0;
    public:
        using PrimaryKeyType = BackendWindowsVersionInfoKey;


        BackendWindowsVersionInfo( )
        { }

        BackendWindowsVersionInfo( Guid id, const DateTime& timeStamp, UInt32 majorVersion, UInt32 minorVersion, UInt32 buildNumber, UInt32 platformId, WideString csdVersion, UInt16 servicePackMajor, UInt16 servicePackMinor, UInt16 suiteMask, Byte  productType )
            : primaryKey_( id, timeStamp ), majorVersion_( majorVersion ), minorVersion_( minorVersion ), buildNumber_( buildNumber ), platformId_( platformId ), csdVersion_( csdVersion ), servicePackMajor_( servicePackMajor ), servicePackMinor_( servicePackMinor ), suiteMask_( suiteMask ), productType_( productType )
        {}

        BackendWindowsVersionInfo( const OSVERSIONINFOEXW& info )
            : majorVersion_( info.dwMajorVersion ), minorVersion_( info.dwMinorVersion ), buildNumber_( info.dwBuildNumber ), platformId_( info.dwPlatformId ), csdVersion_( info.szCSDVersion ), servicePackMajor_( info.wServicePackMajor ), servicePackMinor_( info.wServicePackMinor ), suiteMask_( info.wSuiteMask ), productType_( info.wProductType )
        {
        }

        void Assign( Guid id, const DateTime& timeStamp, UInt32 majorVersion, UInt32 minorVersion, UInt32 buildNumber, UInt32 platformId, WideString csdVersion, UInt16 servicePackMajor, UInt16 servicePackMinor, UInt16 suiteMask, Byte  productType )
        {
            primaryKey_.Assign( id, timeStamp );
            majorVersion_ = majorVersion;
            minorVersion_ = minorVersion;
            buildNumber_ = buildNumber;
            platformId_ = platformId;
            csdVersion_ = csdVersion;
            servicePackMajor_ = servicePackMajor;
            servicePackMinor_ = servicePackMinor;
            suiteMask_ = suiteMask;
            productType_ = productType;
        }

        void Assign( Guid id, const DateTime& timeStamp, const OSVERSIONINFOEXW& info )
        {
            primaryKey_.Assign( id, timeStamp );
            majorVersion_ = info.dwMajorVersion;
            minorVersion_ = info.dwMinorVersion;
            buildNumber_ = info.dwBuildNumber;
            platformId_ = info.dwPlatformId;
            csdVersion_ = info.szCSDVersion;
            servicePackMajor_ = info.wServicePackMajor;
            servicePackMinor_ = info.wServicePackMinor;
            suiteMask_ = info.wSuiteMask;
            productType_ = info.wProductType;
        }



        template<typename ReaderT>
        void ReadKey( ReaderT& reader )
        {
            primaryKey_.Read( reader );
        }

        template<typename ReaderT>
        void ReadData( ReaderT& reader )
        {
            reader.Read( majorVersion_ );
            reader.Read( minorVersion_ );
            reader.Read( buildNumber_ );
            reader.Read( platformId_ );
            reader.Read( csdVersion_ );
            reader.Read( servicePackMajor_ );
            reader.Read( servicePackMinor_ );
            reader.Read( suiteMask_ );
            reader.Read( productType_ );
        }

        template<typename WriterT>
        void WriteKey( WriterT& writer ) const
        {
            primaryKey_.Write( writer );
        }

        template<typename WriterT>
        void WriteData( WriterT& writer ) const
        {
            writer.Write( majorVersion_ );
            writer.Write( minorVersion_ );
            writer.Write( buildNumber_ );
            writer.Write( platformId_ );
            writer.Write( csdVersion_ );
            writer.Write( servicePackMajor_ );
            writer.Write( servicePackMinor_ );
            writer.Write( suiteMask_ );
            writer.Write( productType_ );
        }

        void AddTo( XXH64Hasher& hasher ) const noexcept
        {
            hasher.Add( majorVersion_ );
            hasher.Add( minorVersion_ );
            hasher.Add( buildNumber_ );
            hasher.Add( platformId_ );
            hasher.Add( csdVersion_.c_str( ), csdVersion_.size( ) * sizeof( WideString::value_type ) );
            hasher.Add( servicePackMajor_ );
            hasher.Add( servicePackMinor_ );
            hasher.Add( suiteMask_ );
            hasher.Add( productType_ );
        }

        size_t Hash( ) const noexcept
        {
            XXH64Hasher hasher;
            AddTo( hasher );
            auto result = hasher.Digest( );
            return result;
        }

        const PrimaryKeyType& PrimaryKey( ) const noexcept
        {
            return primaryKey_;
        }
        void SetPrimaryKey( const PrimaryKeyType& primaryKey ) noexcept
        {
            primaryKey_ = primaryKey;
        }


        constexpr const Guid& Id( ) const noexcept
        {
            return primaryKey_.Id();
        }
        constexpr void SetId( const Guid& id ) noexcept
        {
            primaryKey_.SetId( id );
        }

        constexpr DateTime TimeStamp( ) const noexcept
        {
            return primaryKey_.TimeStamp( );
        }
        constexpr void SetTimeStamp( const DateTime& timeStamp )
        {
            primaryKey_.SetTimeStamp( timeStamp );
        }


        constexpr UInt32 MajorVersion( ) const noexcept
        {
            return majorVersion_;
        }
        constexpr UInt32 MinorVersion( ) const noexcept
        {
            return minorVersion_;
        }
        constexpr UInt32 BuildNumber( ) const noexcept
        {
            return buildNumber_;
        }
        constexpr UInt32 PlatformId( ) const noexcept
        {
            return platformId_;
        }
        constexpr const WideString& CSDVersion( ) const noexcept
        {
            return csdVersion_;
        }
        constexpr UInt16 ServicePackMajor( ) const noexcept
        {
            return servicePackMajor_;
        }
        constexpr UInt16 ServicePackMinor( ) const noexcept
        {
            return servicePackMinor_;
        }
        constexpr UInt16 SuiteMask( ) const noexcept
        {
            return suiteMask_;
        }
        constexpr Byte ProductType( ) const noexcept
        {
            return productType_;
        }


    };



    class BackendProcessInfo : Identified<BackendProcessInfo>
    {
    public:
        using Base = Identified<BackendProcessInfo>;
    private:
        DateTime startTime_;
        UInt32 processId_;
        Guid computerId_;
        Guid userId_;
        Guid windowsVersionId_;
        Guid configurationFileId_;
        WideString commandlineArguments_;
    public:
        BackendProcessInfo( )
            : processId_( 0 )
        {
        }

        BackendProcessInfo( const Guid& id, const DateTime& startTime, UInt32 processId, const Guid& computerId, const Guid& userId, const Guid& windowsVersionId, const Guid& configurationFileId, const WideString& commandlineArguments )
            : Base( id ), startTime_( startTime ), processId_( processId ), computerId_( computerId ), userId_( userId ), windowsVersionId_( windowsVersionId ), configurationFileId_( configurationFileId ), commandlineArguments_( commandlineArguments )
        {
        }


        static HCC_EXPORT BackendProcessInfo Create( );



        template<typename ReaderT>
        void ReadData( ReaderT& reader )
        {
            reader.Read( startTime_ );
            reader.Read( processId_ );
            reader.Read( computerId_ );
            reader.Read( userId_ );
            reader.Read( windowsVersionId_ );
            reader.Read( configurationFileId_ );
            reader.Read( commandlineArguments_ );
        }

        template<typename WriterT>
        void WriteData( WriterT& writer ) const
        {
            writer.Write( startTime_ );
            writer.Write( processId_ );
            writer.Write( computerId_ );
            writer.Write( userId_ );
            writer.Write( windowsVersionId_ );
            writer.Write( configurationFileId_ );
            writer.Write( commandlineArguments_ );
        }

        void AddTo( XXH64Hasher& hasher ) const noexcept
        {
            hasher.Add( startTime_ );
            hasher.Add( processId_ );
            hasher.Add( computerId_ );
            hasher.Add( userId_ );
            hasher.Add( windowsVersionId_ );
            hasher.Add( configurationFileId_ );
            hasher.Add( commandlineArguments_.c_str( ), commandlineArguments_.size( ) * sizeof( WideString::value_type ) );
        }

        size_t Hash( ) const noexcept
        {
            XXH64Hasher hasher;
            AddTo( hasher );
            auto result = hasher.Digest( );
            return result;
        }


        constexpr const DateTime& StartTime( ) const noexcept
        {
            return startTime_;
        }
        void SetStartTime( const DateTime& startTime ) noexcept
        {
            startTime_ = startTime;
        }

        constexpr UInt32 ProcessId( ) const noexcept
        {
            return processId_;
        }
        void SetProcessId( UInt32 processId ) noexcept
        {
            processId_ = processId;
        }


        constexpr const Guid& ComputerId( ) const noexcept
        {
            return computerId_;
        }
        void SetComputerId( const Guid& computerId )
        {
            computerId_ = computerId;
        }

        constexpr const Guid& UserId( ) const noexcept
        {
            return userId_;
        }
        void SetUserId( const Guid& userId ) noexcept
        {
            userId_ = userId;
        }

        constexpr const Guid& WindowsVersionId( ) const noexcept
        {
            return windowsVersionId_;
        }
        constexpr const Guid& ConfigurationFileId( ) const noexcept
        {
            return configurationFileId_;
        }
        constexpr const WideString& CommandlineArguments( ) const noexcept
        {
            return commandlineArguments_;
        }


    };

}

#endif
