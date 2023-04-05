#pragma once
#ifndef __DATACONTEXT_H__
#define __DATACONTEXT_H__

#include <DataReaders.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn;

class Session;
class Engine;

class DataContext
{
    const Session* session_;
public:
    DataContext( Session& session )
        : session_( &session )
    { }
    const OCI::ServiceContext& ServiceContext( ) const;

    std::unique_ptr<OwnedObjectTypeData> CreateOwnedObjectType( const std::wstring& name, const std::wstring& description ) const;
    std::unique_ptr<OwnedObjectTypeData> CreateOwnedObjectType( const Guid& id, const std::wstring& name, const std::wstring& description ) const;
    std::unique_ptr<OwnedObjectTypeData> FindOwnedObjectType( const Guid& id ) const;
    std::unique_ptr<OwnedObjectTypeData> FindOwnedObjectType( const std::wstring& name ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectTypeData> > ReadOwnedObjectTypes( ) const;
    void ClearOwnedObjectTypes( ) const;
    bool UpdateOwnedObjectType( std::unique_ptr<OwnedObjectTypeData>& data ) const;
    bool DeleteOwnedObjectType( const Guid& id, Int64 optimisticLock ) const;
    

    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& type, const std::wstring& name, const std::wstring& description ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& type, const std::wstring& name, const std::wstring& description, const IO::MemoryStream& data ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& type, const std::wstring& name, const std::wstring& description ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& owner, const Guid& type, const std::wstring& name, const std::wstring& description ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& type, const std::wstring& name, const std::wstring& description, const IO::MemoryStream& data ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& owner, const Guid& type, const std::wstring& name, const std::wstring& description, const IO::MemoryStream& data ) const;
    std::unique_ptr<OwnedObjectData> FindOwnedObject( const Guid& id ) const;
    std::unique_ptr<OwnedObjectData> FindOwnedObject( const Guid& owner, const std::wstring& name ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjects( ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjectsByOwner( const Guid& owner ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjectsByType( const Guid& type ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjectsByOwnerAndType( const Guid& owner, const Guid& type ) const;
    void ClearOwnedObjects( ) const;
    bool UpdateOwnedObject( std::unique_ptr<OwnedObjectData>& data ) const;
    bool DeleteOwnedObject( const Guid& id, Int64 optimisticLock ) const;

    void InsertTimeseriesPointSegment( const Guid& owner, const TimeseriesPointSegment& segment ) const;
    TimeseriesPoints ReadSegments( const Guid& owner ) const;
    void ClearTimeseriesPointSegments( ) const;


};

class Session
{
    const Engine* engine_;
    OCI::Server server_;
    OCI::ServiceContext serviceContext_;
public:
    Session( const Engine& engine, const std::wstring& userId, const std::wstring& password, const std::wstring& alias );
    ~Session( )
    {
        serviceContext_.SessionEnd( );
    }
        
    const OCI::Server& Server( ) const
    {
        return server_;
    }
    const OCI::ServiceContext& ServiceContext( ) const
    {
        return serviceContext_;
    }
    void Commit( OCI::TransactionEndFlags flags = OCI::TransactionEndFlags::WriteImmediately ) const
    {
        serviceContext_.TransactionCommit( );
    }

};

inline const OCI::ServiceContext& DataContext::ServiceContext( ) const
{
    return session_->ServiceContext( );
}

class Engine
{
    OCI::Environment environment_;
public:
    Engine( )
        : environment_( OCI::EnvironmentOptions() )
    { }

    const OCI::Environment& Environment( ) const
    {
        return environment_;
    }



};

inline Session::Session( const Engine& engine, const std::wstring& userId, const std::wstring& password, const std::wstring& alias )
    : engine_( &engine )
{
    const auto& environment = engine.Environment( );
    server_ = environment.CreateServer( );
    serviceContext_ = server_.CreateServiceContext( userId, password, alias );
    serviceContext_.SessionBegin( );
}


#endif
