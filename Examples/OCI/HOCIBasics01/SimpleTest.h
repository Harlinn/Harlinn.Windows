#pragma once
#ifndef __SIMPLETEST_H__
#define __SIMPLETEST_H__

#include <SimpleTestData.h>
#include <HOCI.h>

using namespace Harlinn;

class SimpleTest
{
    const OCI::ServiceContext& serviceContext_;
public:
    using Map = std::unordered_map<Int64, std::unique_ptr<SimpleTestData> >;
    SimpleTest( const OCI::ServiceContext& serviceContext )
        : serviceContext_( serviceContext )
    { 
    }

    OCI::Transaction BeginTransaction( ) const
    {
        return serviceContext_.BeginTransaction( );
    }

    const OCI::ServiceContext& ServiceContext( ) const noexcept
    {
        return serviceContext_;
    }

    void Clear( ) const
    {
        auto& serviceContext = ServiceContext( );
        auto statement = serviceContext.CreateStatement( L"DELETE FROM SimpleTest1" );
        auto transaction = serviceContext.BeginTransaction( );
        statement.ExecuteNonQuery( );
        transaction.Commit( );
    }



    std::unique_ptr<SimpleTestData> Insert( const WideString& name, 
                        const WideString& description = WideString( ) ) const
    {
        auto& serviceContext = ServiceContext( );
        std::optional<WideString> descr;
        if ( description.size( ) )
        {
            descr = description;
        }

        constexpr wchar_t sql[] = 
            L"INSERT INTO SimpleTest1(Id, OptimisticLock, Name, Description ) " 
            L"VALUES(SimpleTest1Seq.NextVal,0,:1,:2) RETURNING Id INTO :3";

        auto statement = serviceContext.CreateStatement( sql, name, descr );
        auto* idBind = statement.Bind<Int64>( 3 );
        auto transaction = serviceContext.BeginTransaction( );
        statement.ExecuteNonQuery( );
        transaction.Commit( );
        auto id = idBind->AsInt64( );
        return std::make_unique<SimpleTestData>( id, 0, name, description );
    }

    std::unique_ptr<SimpleTestData> Select( Int64 id ) const
    {
        auto& serviceContext = ServiceContext( );
        constexpr wchar_t sql[] = 
            L"SELECT OptimisticLock, Name, Description FROM SimpleTest1 "
            L"WHERE Id = :1";
        auto statement = serviceContext.CreateStatement( sql, id );
        auto reader = statement.ExecuteReader<OCI::DataReader>( );
        if ( reader->Read( ) )
        {
            auto optimisticLock = reader->GetInt64( 0 );
            auto name = reader->GetString( 1 );
            WideString description;
            if ( reader->IsDBNull( 2 ) == false )
            {
                description = reader->GetString( 2 );
            }
            return std::make_unique<SimpleTestData>( id, optimisticLock, 
                name, description );
        }
        else
        {
            return nullptr;
        }
    }

    Map Select( ) const
    {
        Map result;
        auto& serviceContext = ServiceContext( );
        constexpr wchar_t sql[] = 
            L"SELECT Id, OptimisticLock, Name, Description FROM SimpleTest1";
            
        auto statement = serviceContext.CreateStatement( sql );
        auto reader = statement.ExecuteReader<OCI::DataReader>( );
        while ( reader->Read( ) )
        {
            auto id = reader->GetInt64( 0 );
            auto optimisticLock = reader->GetInt64( 1 );
            auto name = reader->GetString( 2 );
            WideString description;
            if ( reader->IsDBNull( 3 ) == false )
            {
                description = reader->GetString( 3 );
            }
            result.emplace(id, std::make_unique<SimpleTestData>( id, optimisticLock, name, description ));
        }
        return result;
    }

    bool Update( SimpleTestData& data )
    {
        auto id = data.Id();
        auto optimisticLock = data.OptimisticLock();
        auto& name = data.Name();
        auto& description = data.Description();

        auto& serviceContext = ServiceContext( );
        std::optional<WideString> descr;
        if ( description.size( ) )
        {
            descr = description;
        }
        constexpr wchar_t sql[] = L"UPDATE SimpleTest1 " 
            L"SET OptimisticLock=OptimisticLock+1, Name=:1, Description=:2 " 
            L"WHERE Id=:3 AND OptimisticLock=:4";

        auto statement = serviceContext.CreateStatement( sql, name, descr, 
                                        id, optimisticLock );
        if ( statement.ExecuteNonQuery( ) > 0 )
        {
            data.SetOptimisticLock( optimisticLock + 1 );
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Update( const std::unique_ptr<SimpleTestData>& data )
    {
        return Update( *data );
    }


    bool Delete( const SimpleTestData& data )
    {
        auto id = data.Id( );
        auto optimisticLock = data.OptimisticLock( );
        auto& serviceContext = ServiceContext( );
        constexpr wchar_t sql[] = L"DELETE FROM SimpleTest1 "
            L"WHERE Id=:1 AND OptimisticLock=:2";

        auto statement = serviceContext.CreateStatement( sql, id, optimisticLock );
        if ( statement.ExecuteNonQuery( ) > 0 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Delete( const std::unique_ptr<SimpleTestData>& data )
    {
        return Delete( *data );
    }
    bool Delete( const SimpleTestData* data )
    {
        return Delete( *data );
    }


    void Execute( )
    {
        Clear( );
        Map originalItems;
        constexpr int RowCount = 100;
        auto& serviceContext = ServiceContext( );
        auto transaction = serviceContext.BeginTransaction( );
        
        
        for ( int i = 0; i < RowCount; ++i )
        {
            auto name = Format(L"Name%d", i + 1);
            auto description = i % 2 == 0 ? WideString() : Format( L"Description%d", i + 1 );
            auto data = Insert( name, description );
            originalItems.emplace( data->Id(), std::move(data) );
        }
        transaction.Commit( );
        

        auto databaseItems = Select( );

        for( auto& entry : originalItems )
        {
            auto& originalItem = entry.second;
            if ( databaseItems.contains( originalItem->Id() ) )
            {
                auto& databaseItem = databaseItems[originalItem->Id()];
                if ( originalItem->Equals( databaseItem ) == false )
                {
                    auto original = originalItem->ToString( );
                    auto database = databaseItem->ToString( );
                    auto message = Format( L"The original item %s "
                        L"is not equal to the item %s "
                        L"retrieved from the database.", original.c_str( ), database.c_str( ) );

                    throw Exception( message );
                }
            }
            else
            {
                auto original = originalItem->ToString( );
                auto message = Format( L"Did not retrieve %s from "
                    L"the database.", original.c_str( ) );
                throw Exception( message );
            }
        }

        transaction = serviceContext.BeginTransaction( );
        
        for( auto& entry : originalItems )
        {
            auto& data = entry.second;
            if ( data->Description().length() == 0  )
            {
                data->SetDescription( L"Updated Description" );
                if ( Update( data ) == false )
                {
                    auto changedData = Select( data->Id() );
                    if ( changedData != nullptr )
                    {
                        auto original = data->ToString( );
                        auto database = changedData->ToString( );
                        auto message = Format( L"Unable to update %s, the " 
                            L"row has been updated by another user %s",
                            original.c_str( ), database.c_str( ) );

                        throw Exception( message );
                    }
                    else
                    {
                        auto original = data->ToString( );
                        auto message = Format( L"Unable to update %s, the "
                            L"row has been deleted by another user", original.c_str( ) );
                        throw Exception( message );
                    }
                }
            }
        }
        transaction.Commit( );

        constexpr int rowsToDeleteCount = RowCount / 3;
        std::vector<SimpleTestData*> itemsToDelete;
        auto it = originalItems.begin( );
        for ( int i = 0; i < rowsToDeleteCount; ++i )
        {
            itemsToDelete.emplace_back( it->second.get() );
            it++;
        }
        transaction = serviceContext.BeginTransaction( );

        for( auto* item : itemsToDelete )
        {
            if ( Delete( item ) == false )
            {
                auto original = item->ToString( );
                auto message = Format( L"Unable to update %s, the "
                    L"row has been deleted by another user", original.c_str( ) );

                throw Exception( message );
            }
        }
        transaction.Commit( );

        for ( auto* item : itemsToDelete )
        {

            if ( Delete( item ) )
            {
                auto original = item->ToString( );
                auto message = Format( L"It appears %s, "
                    L"was not deleted", original.c_str( ) );

                throw Exception( message );
            }
        }
    }


};


#endif
