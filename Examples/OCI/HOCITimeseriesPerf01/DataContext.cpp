#include <DataContext.h>


std::unique_ptr<OwnedObjectTypeData> DataContext::CreateOwnedObjectType( const std::wstring& name, const std::wstring& description ) const
{
    auto& serviceContext = ServiceContext( );

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObjectType(Id, Name, OptimisticLock, Created, Description ) "
        L"VALUES(SYS_GUID(),:1,0,SYSTIMESTAMP,:2) RETURNING Id, Created INTO :3, :4";

    auto statement = serviceContext.CreateStatement( sql, name, desc );
    auto* idBind = statement.Bind<Guid>( 3 );
    auto* createdBind = statement.Bind<DateTime>( 4 );

    statement.ExecuteNonQuery( );

    auto id = idBind->AsGuid( );
    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectTypeData>( id, name, 0, created, std::optional<DateTime>(), description );

}
std::unique_ptr<OwnedObjectTypeData> DataContext::CreateOwnedObjectType( const Guid& id, const std::wstring& name, const std::wstring& description ) const
{
    auto& serviceContext = ServiceContext( );

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObjectType(Id, Name, OptimisticLock, Created, Description ) "
        L"VALUES(:1,:2,0,SYSTIMESTAMP,:3) RETURNING Created INTO :4";

    auto statement = serviceContext.CreateStatement( sql, id, name, desc );
    auto* createdBind = statement.Bind<DateTime>( 4 );

    statement.ExecuteNonQuery( );

    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectTypeData>( id, name, 0, created, std::optional<DateTime>( ), description );
}
std::unique_ptr<OwnedObjectTypeData> DataContext::FindOwnedObjectType( const Guid& id ) const
{
    auto& serviceContext = ServiceContext( );
    std::wstring sql = Format( L"%s WHERE Id=:1", OwnedObjectTypeDataReader::SQL );
    auto statement = serviceContext.CreateStatement( sql, id );

    auto reader = statement.ExecuteReader<OwnedObjectTypeDataReader>( 1 );
    if ( reader->Read( ) )
    {
        return reader->GetDataObject( );
    }
    return nullptr;
}
std::unique_ptr<OwnedObjectTypeData> DataContext::FindOwnedObjectType( const std::wstring& name ) const
{
    auto& serviceContext = ServiceContext( );
    std::wstring sql = Format( L"%s WHERE Name=:1", OwnedObjectTypeDataReader::SQL );
    auto statement = serviceContext.CreateStatement( sql, name );

    auto reader = statement.ExecuteReader<OwnedObjectTypeDataReader>( 1 );
    if ( reader->Read( ) )
    {
        return reader->GetDataObject( );
    }
    return nullptr;
}
std::unordered_map<Guid, std::unique_ptr<OwnedObjectTypeData> > DataContext::ReadOwnedObjectTypes( ) const
{
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectTypeData> > result;
    auto& serviceContext = ServiceContext( );
    auto statement = serviceContext.CreateStatement( OwnedObjectTypeDataReader::SQL );

    auto reader = statement.ExecuteReader<OwnedObjectTypeDataReader>( 1 );
    while( reader->Read( ) )
    {
        auto data = reader->GetDataObject( );
        result.emplace( data->Id, std::move(data) );
    }
    return result;
}
void DataContext::ClearOwnedObjectTypes( ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"DELETE FROM OwnedObjectType";
    auto statement = serviceContext.CreateStatement( sql );
    statement.ExecuteNonQuery( );
}
bool DataContext::UpdateOwnedObjectType( std::unique_ptr<OwnedObjectTypeData>& data ) const
{
    auto& serviceContext = ServiceContext( );

    std::optional<std::wstring> desc;
    if ( data->Description.empty( ) == false )
    {
        desc = data->Description;
    }

    constexpr wchar_t sql[] = L"UPDATE OwnedObjectType SET Name=:1, Description=:2 WHERE Id=:3 AND OptimisticLock=:4";
    auto statement = serviceContext.CreateStatement( sql, data->Name, desc, data->Id, data->OptimisticLock );
    auto count = statement.ExecuteNonQuery( );
    if ( count > 0 )
    {
        data->OptimisticLock++;
        return true;
    }
    else
    {
        return false;
    }
}
bool DataContext::DeleteOwnedObjectType( const Guid& id, Int64 optimisticLock ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"DELETE FROM OwnedObjectType WHERE Id=:1 AND OptimisticLock=:2";
    auto statement = serviceContext.CreateStatement( sql, id, optimisticLock );
    auto count = statement.ExecuteNonQuery( );
    return count > 0;
}


std::unique_ptr<OwnedObjectData> DataContext::CreateOwnedObject( const Guid& type, const std::wstring& name, const std::wstring& description ) const
{
    auto& serviceContext = ServiceContext( );

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObject(Id, Tp, Name, OptimisticLock, Created, Description ) "
        L"VALUES(SYS_GUID(),:1,:2,0,SYSTIMESTAMP,:3) RETURNING Id, Created INTO :4, :5";

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    auto statement = serviceContext.CreateStatement( sql, type, name, desc );
    auto* idBind = statement.Bind<Guid>( 4 );
    auto* createdBind = statement.Bind<DateTime>( 5 );

    statement.ExecuteNonQuery( );

    auto id = idBind->AsGuid( );
    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectData>( id, type, Guid() ,name, 0, created, std::optional<DateTime>( ), description, IO::MemoryStream() );

}
std::unique_ptr<OwnedObjectData> DataContext::CreateOwnedObject( const Guid& type, const std::wstring& name, const std::wstring& description, const IO::MemoryStream& data ) const
{
    auto& serviceContext = ServiceContext( );

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObject(Id, Tp, Name, OptimisticLock, Created, Description ) "
        L"VALUES(SYS_GUID(),:1,:2,0,SYSTIMESTAMP,:3, :4) RETURNING Id, Created INTO :5, :6";

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    auto statement = serviceContext.CreateStatement( sql, type, name, desc );

    auto* dataBind = statement.Bind<OCI::BinaryBind>( 4 );
    dataBind->Write( data );

    auto* idBind = statement.Bind<Guid>( 5 );
    auto* createdBind = statement.Bind<DateTime>( 6 );

    statement.ExecuteNonQuery( );

    auto id = idBind->AsGuid( );
    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectData>( id, type, Guid( ), name, 0, created, std::optional<DateTime>( ), description, data );
}
std::unique_ptr<OwnedObjectData> DataContext::CreateOwnedObject( const Guid& id, const Guid& type, const std::wstring& name, const std::wstring& description ) const
{
    auto& serviceContext = ServiceContext( );

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObject(Id, Tp, Name, OptimisticLock, Created, Description ) "
        L"VALUES(:1,:2,:3,0,SYSTIMESTAMP,:4) RETURNING Created INTO :5";

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    auto statement = serviceContext.CreateStatement( sql, id, type, name, desc );
    auto* createdBind = statement.Bind<DateTime>( 5 );

    statement.ExecuteNonQuery( );

    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectData>( id, type, Guid( ), name, 0, created, std::optional<DateTime>( ), description, IO::MemoryStream( ) );
}
std::unique_ptr<OwnedObjectData> DataContext::CreateOwnedObject( const Guid& id, const Guid& owner, const Guid& type, const std::wstring& name, const std::wstring& description ) const
{
    auto& serviceContext = ServiceContext( );

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObject(Id, Tp, Owner, Name, OptimisticLock, Created, Description ) "
        L"VALUES(:1,:2,:3,:4,0,SYSTIMESTAMP,:5) RETURNING Created INTO :6";

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    auto statement = serviceContext.CreateStatement( sql, id, type, owner, name, desc );
    auto* createdBind = statement.Bind<DateTime>( 6 );

    statement.ExecuteNonQuery( );

    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectData>( id, type, owner, name, 0, created, std::optional<DateTime>( ), description, IO::MemoryStream( ) );

}
std::unique_ptr<OwnedObjectData> DataContext::CreateOwnedObject( const Guid& id, const Guid& type, const std::wstring& name, const std::wstring& description, const IO::MemoryStream& data ) const
{
    auto& serviceContext = ServiceContext( );

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObject(Id, Tp, Name, OptimisticLock, Created, Description, Data ) "
        L"VALUES(:1,:2,:3,0,SYSTIMESTAMP,:4,:5) RETURNING Created INTO :6";

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    auto statement = serviceContext.CreateStatement( sql, id, type, name, desc );

    auto* dataBind = statement.Bind<OCI::BinaryBind>( 5 );
    if ( data.Size( ) > 0 )
    {
        dataBind->Write( data );
    }
    else
    {
        dataBind->SetDBNull( );
    }

    auto* createdBind = statement.Bind<DateTime>( 6 );

    statement.ExecuteNonQuery( );

    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectData>( id, type, Guid( ), name, 0, created, std::optional<DateTime>( ), description, data );
}

std::unique_ptr<OwnedObjectData> DataContext::CreateOwnedObject( const Guid& id, const Guid& owner, const Guid& type, const std::wstring& name, const std::wstring& description, const IO::MemoryStream& data ) const
{
    auto& serviceContext = ServiceContext( );

    constexpr wchar_t sql[] =
        L"INSERT INTO OwnedObject(Id, Tp, Owner ,Name, OptimisticLock, Created, Description, Data ) "
        L"VALUES(:1,:2,:3,0,SYSTIMESTAMP,:4,:5) RETURNING Created INTO :6";

    std::optional<std::wstring> desc;
    if ( description.empty( ) == false )
    {
        desc = description;
    }

    auto statement = serviceContext.CreateStatement( sql, id, type, owner, name, desc );

    auto* dataBind = statement.Bind<OCI::BinaryBind>( 5 );
    if ( data.Size( ) > 0 )
    {
        dataBind->Write( data );
    }
    else
    {
        dataBind->SetDBNull( );
    }

    auto* createdBind = statement.Bind<DateTime>( 6 );

    statement.ExecuteNonQuery( );

    auto created = createdBind->AsDateTime( );

    return std::make_unique<OwnedObjectData>( id, type, owner, name, 0, created, std::optional<DateTime>( ), description, data );
}

std::unique_ptr<OwnedObjectData> DataContext::FindOwnedObject( const Guid& id ) const
{
    auto& serviceContext = ServiceContext( );
    std::wstring sql = Format( L"%s WHERE Id=:1", OwnedObjectDataReader::SQL );
    auto statement = serviceContext.CreateStatement( sql, id );

    auto reader = statement.ExecuteReader<OwnedObjectDataReader>( 1 );
    if ( reader->Read( ) )
    {
        return reader->GetDataObject( );
    }
    return nullptr;
}
std::unique_ptr<OwnedObjectData> DataContext::FindOwnedObject( const Guid& owner, const std::wstring& name ) const
{
    auto& serviceContext = ServiceContext( );
    std::wstring sql = Format( L"%s WHERE Owner=:1 AND Name=:2", OwnedObjectDataReader::SQL );
    auto statement = serviceContext.CreateStatement( sql, owner, name );

    auto reader = statement.ExecuteReader<OwnedObjectDataReader>( 1 );
    if ( reader->Read( ) )
    {
        return reader->GetDataObject( );
    }
    return nullptr;
}
std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > DataContext::ReadOwnedObjects( ) const
{
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > result;
    auto& serviceContext = ServiceContext( );
    auto statement = serviceContext.CreateStatement( OwnedObjectDataReader::SQL );

    auto reader = statement.ExecuteReader<OwnedObjectDataReader>( 1 );
    while ( reader->Read( ) )
    {
        auto data = reader->GetDataObject( );
        result.emplace( data->Id, std::move( data ) );
    }
    return result;

}
std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > DataContext::ReadOwnedObjectsByOwner( const Guid& owner ) const
{
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > result;
    auto& serviceContext = ServiceContext( );

    std::wstring sql = Format( L"%s WHERE Owner=:1", OwnedObjectDataReader::SQL );

    auto statement = serviceContext.CreateStatement( sql, owner );

    auto reader = statement.ExecuteReader<OwnedObjectDataReader>( 1 );
    while ( reader->Read( ) )
    {
        auto data = reader->GetDataObject( );
        result.emplace( data->Id, std::move( data ) );
    }
    return result;
}
std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > DataContext::ReadOwnedObjectsByType( const Guid& type ) const
{
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > result;
    auto& serviceContext = ServiceContext( );

    std::wstring sql = Format( L"%s WHERE Tp=:1", OwnedObjectDataReader::SQL );

    auto statement = serviceContext.CreateStatement( sql, type );

    auto reader = statement.ExecuteReader<OwnedObjectDataReader>( 1 );
    while ( reader->Read( ) )
    {
        auto data = reader->GetDataObject( );
        result.emplace( data->Id, std::move( data ) );
    }
    return result;
}
std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > DataContext::ReadOwnedObjectsByOwnerAndType( const Guid& owner, const Guid& type ) const
{
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > result;
    auto& serviceContext = ServiceContext( );

    std::wstring sql = Format( L"%s WHERE Owner=:1 AND Tp=:2", OwnedObjectDataReader::SQL );

    auto statement = serviceContext.CreateStatement( sql, owner, type );

    auto reader = statement.ExecuteReader<OwnedObjectDataReader>( 1 );
    while ( reader->Read( ) )
    {
        auto data = reader->GetDataObject( );
        result.emplace( data->Id, std::move( data ) );
    }
    return result;
}
void DataContext::ClearOwnedObjects( ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"DELETE FROM OwnedObject";
    auto statement = serviceContext.CreateStatement( sql );
    statement.ExecuteNonQuery( );
}
bool DataContext::UpdateOwnedObject( std::unique_ptr<OwnedObjectData>& data ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"UPDATE OwnedObject SET Owner=:1 Name=:2, Description=:3, Data=:4 WHERE Id=:5 AND OptimisticLock=:6";
    std::optional<Guid> owner;
    if ( data->Owner.empty( ) == false )
    {
        owner = data->Owner;
    }
    std::optional<std::wstring> description;
    if ( data->Description.empty( ) == false )
    {
        description = data->Description;
    }
    auto statement = serviceContext.CreateStatement( sql, owner, data->Name, description  );

    auto* dataBind = statement.Bind<OCI::BinaryBind>( 4 );
    if ( data->Data.Size( ) > 0 )
    {
        dataBind->Write( data->Data );
    }
    else
    {
        dataBind->SetDBNull( );
    }
    auto* idBind = statement.Bind<Guid>( 4 );
    idBind->Assign( data->Id );
    auto* optimisticLockBind = statement.Bind<Int64>( 5 );
    optimisticLockBind->Assign( data->OptimisticLock );

    auto count = statement.ExecuteNonQuery( );
    if ( count > 0 )
    {
        data->OptimisticLock++;
        return true;
    }
    else
    {
        return false;
    }
}
bool DataContext::DeleteOwnedObject( const Guid& id, Int64 optimisticLock ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"DELETE FROM OwnedObject WHERE Id=:1 AND OptimisticLock=:2";
    auto statement = serviceContext.CreateStatement( sql, id, optimisticLock );
    auto count = statement.ExecuteNonQuery( );
    return count > 0;
}


void DataContext::InsertTimeseriesPointSegment( const Guid& owner, const TimeseriesPointSegment& segment ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"INSERT INTO TimeseriesSegment(Id, FirstTimestamp, OptimisticLock, Data ) "
                                L"VALUES(:1,:2,0,:3)";
    const DateTime& firstTimestamp = segment.Key( );
    auto statement = serviceContext.CreateStatement( sql, owner, firstTimestamp );
    auto* dataBind = statement.Bind<OCI::LargeBinaryRefBind>( 3 );
    auto* buffer = segment.Buffer( );
    dataBind->Assign( buffer, TimeseriesPointSegment::BufferSize );
    auto count = statement.ExecuteNonQuery( );
}

TimeseriesPoints DataContext::ReadSegments( const Guid& owner ) const
{
    TimeseriesPoints result;
    auto& serviceContext = ServiceContext( );
    std::wstring sql = Format( L"%s WHERE Id=:1 ORDER BY FirstTimestamp", TimeseriesSegmentDataReader::SQL );
    auto statement = serviceContext.CreateStatement( sql, owner );
    auto reader = statement.ExecuteReader<TimeseriesSegmentDataReader>( );
    while ( reader->Read( ) )
    {
        auto segment = reader->GetDataObject( );
        result.Append( segment );
    }
    return result;
}

void DataContext::ClearTimeseriesPointSegments( ) const
{
    auto& serviceContext = ServiceContext( );
    constexpr wchar_t sql[] = L"DELETE FROM TimeseriesSegment";
    auto statement = serviceContext.CreateStatement( sql );
    statement.ExecuteNonQuery( );
}




