#pragma once
#ifndef HCCESEOPTIONS_H_
#define HCCESEOPTIONS_H_
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

#include "HCCEse.h"
#include "HCCXml.h"
#include "HCCEnvironment.h"

namespace Harlinn::Common::Core::Ese
{
    class InitializedInstanceOptions : public std::enable_shared_from_this<InitializedInstanceOptions>
    {
    public:
        using Element = Xml::Dom::Element;
    private:
        std::optional<TimeSpan> snapshotTimeout_;
        std::optional<Int32> dbExtensionSize_;
        std::optional<OnlineDefragFlags> enableOnlineDefrag_;
        std::optional<long> recordUpgradeDirtyLevel_;
        std::optional<TimeSpan> accessDeniedRetryPeriod_;
        std::optional<Int32> ioPriorityLow_;
        std::optional<UInt64> cacheSize_;
        std::optional<UInt64> cacheSizeMin_;
        std::optional<UInt64> cacheSizeMax_;
        std::optional<UInt64> checkpointDepthMax_;
        std::optional<UInt64> checkpointIOMax_;
        std::optional<UInt64> startFlushThreshold_;
        std::optional<UInt64> stopFlushThreshold_;
        std::optional<TransactionFlags> commitDefault_;
    public:
        InitializedInstanceOptions( )
        {

        }

        void ReadFrom( const Element& element )
        {
            snapshotTimeout_ = element.Read<std::optional<TimeSpan>>( L"SnapshotTimeout" );
            dbExtensionSize_ = element.Read<std::optional<Int32>>( L"DbExtensionSize" );
            enableOnlineDefrag_ = element.Read<std::optional<OnlineDefragFlags>>( L"EnableOnlineDefrag" );
            recordUpgradeDirtyLevel_ = element.Read<std::optional<Int32>>( L"RecordUpgradeDirtyLevel" );
            accessDeniedRetryPeriod_ = element.Read<std::optional<TimeSpan>>( L"AccessDeniedRetryPeriod" );
            ioPriorityLow_ = element.Read<std::optional<bool>>( L"IOPriorityLow" );
            cacheSize_ = element.Read<std::optional<UInt64>>( L"CacheSize" );
            cacheSizeMin_ = element.Read<std::optional<UInt64>>( L"CacheSizeMin" );
            cacheSizeMax_ = element.Read<std::optional<UInt64>>( L"CacheSizeMax" );
            checkpointDepthMax_ = element.Read<std::optional<UInt64>>( L"CheckpointDepthMax" );
            checkpointIOMax_ = element.Read<std::optional<UInt64>>( L"CheckpointIOMax" );
            startFlushThreshold_ = element.Read<std::optional<UInt64>>( L"StartFlushThreshold" );
            stopFlushThreshold_ = element.Read<std::optional<UInt64>>( L"StopFlushThreshold" );
            commitDefault_ = element.Read<std::optional<TransactionFlags>>( L"CommitDefault" );
        }

        void ApplyTo( const Ese::Instance& instance )
        {
            if ( snapshotTimeout_ ) 
            {
                instance.SetSnapshotTimeout( snapshotTimeout_.value() );
            }
            if ( dbExtensionSize_ ) 
            {
                instance.SetDbExtensionSize( dbExtensionSize_.value() );
            }
            if ( enableOnlineDefrag_ ) 
            {
                instance.SetEnableOnlineDefrag( enableOnlineDefrag_.value() );
            }
            if ( recordUpgradeDirtyLevel_ ) 
            {
                instance.SetRecordUpgradeDirtyLevel( recordUpgradeDirtyLevel_.value() );
            }
            if ( accessDeniedRetryPeriod_ ) 
            {
                instance.SetAccessDeniedRetryPeriod( accessDeniedRetryPeriod_.value() );
            }
            if ( ioPriorityLow_ ) 
            {
                instance.SetIOPriorityLow( ioPriorityLow_.value() );
            }
            if ( cacheSize_ ) 
            {
                instance.SetCacheSize( cacheSize_.value( ) );
            }
            if ( cacheSizeMin_ ) 
            {
                instance.SetCacheSizeMin( cacheSizeMin_.value() );
            }
            if ( cacheSizeMax_ ) 
            {
                instance.SetCacheSizeMax( cacheSizeMax_.value( ) );
            }
            if ( checkpointDepthMax_ ) 
            {
                instance.SetCheckpointDepthMax( checkpointDepthMax_.value() );
            }
            if ( checkpointIOMax_ ) 
            {
                instance.SetCheckpointIOMax( checkpointIOMax_.value() );
            }
            if ( startFlushThreshold_ ) 
            {
                instance.SetStartFlushThreshold( startFlushThreshold_.value() );
            }
            if ( stopFlushThreshold_ ) 
            {
                instance.SetStopFlushThreshold( stopFlushThreshold_.value() );
            }
            if ( commitDefault_ ) 
            {
                instance.SetCommitDefault( commitDefault_.value() );
            }
        }

        const std::optional<TimeSpan>& SnapshotTimeout() const
        { 
            return snapshotTimeout_; 
        }
        InitializedInstanceOptions& SetSnapshotTimeout( TimeSpan snapshotTimeout )
        {
            snapshotTimeout_ = snapshotTimeout;
            return *this;
        }
        InitializedInstanceOptions& SetSnapshotTimeout( const std::optional<TimeSpan>& snapshotTimeout )
        {
            snapshotTimeout_ = snapshotTimeout;
            return *this;
        }

        const std::optional<Int32>& DbExtensionSize() const
        { 
            return dbExtensionSize_; 
        }
        InitializedInstanceOptions& SetDbExtensionSize( Int32 dbExtensionSize )
        {
            dbExtensionSize_ = dbExtensionSize;
            return *this;
        }
        InitializedInstanceOptions& SetDbExtensionSize( const std::optional<Int32>& dbExtensionSize )
        {
            dbExtensionSize_ = dbExtensionSize;
            return *this;
        }

        const std::optional<OnlineDefragFlags>& EnableOnlineDefrag() const 
        { 
            return enableOnlineDefrag_; 
        }
        InitializedInstanceOptions& SetEnableOnlineDefrag( OnlineDefragFlags onlineDefragFlags )
        {
            enableOnlineDefrag_ = onlineDefragFlags;
            return *this;
        }
        InitializedInstanceOptions& SetEnableOnlineDefrag( const std::optional<OnlineDefragFlags>& onlineDefragFlags )
        {
            enableOnlineDefrag_ = onlineDefragFlags;
            return *this;
        }

        const std::optional<Int32>& RecordUpgradeDirtyLevel() const 
        { 
            return recordUpgradeDirtyLevel_; 
        }

        InitializedInstanceOptions& SetRecordUpgradeDirtyLevel( Int32 recordUpgradeDirtyLevel )
        {
            recordUpgradeDirtyLevel_ = recordUpgradeDirtyLevel;
            return *this;
        }
        InitializedInstanceOptions& SetRecordUpgradeDirtyLevel( const std::optional<Int32>& recordUpgradeDirtyLevel )
        {
            recordUpgradeDirtyLevel_ = recordUpgradeDirtyLevel;
            return *this;
        }

        const std::optional<TimeSpan>& AccessDeniedRetryPeriod() const 
        { 
            return accessDeniedRetryPeriod_; 
        }
        InitializedInstanceOptions& SetAccessDeniedRetryPeriod( TimeSpan accessDeniedRetryPeriod )
        {
            accessDeniedRetryPeriod_ = accessDeniedRetryPeriod;
            return *this;
        }
        InitializedInstanceOptions& SetAccessDeniedRetryPeriod( const std::optional<TimeSpan>& accessDeniedRetryPeriod )
        {
            accessDeniedRetryPeriod_ = accessDeniedRetryPeriod;
            return *this;
        }


        const std::optional<bool>& IOPriorityLow() const 
        { 
            return ioPriorityLow_; 
        }
        InitializedInstanceOptions& SetIOPriorityLow( bool ioPriorityLow )
        {
            ioPriorityLow_ = ioPriorityLow;
            return *this;
        }
        InitializedInstanceOptions& SetIOPriorityLow( const std::optional<bool>& ioPriorityLow )
        {
            ioPriorityLow_ = ioPriorityLow;
            return *this;
        }

        const std::optional<UInt64>& CacheSize() const 
        { 
            return cacheSize_; 
        }
        InitializedInstanceOptions& SetCacheSize( UInt64 cacheSize )
        {
            cacheSize_ = cacheSize;
            return *this;
        }
        InitializedInstanceOptions& SetCacheSize( const std::optional<UInt64>& cacheSize )
        {
            cacheSize_ = cacheSize;
            return *this;
        }


        const std::optional<UInt64>& CacheSizeMin() const 
        { 
            return cacheSizeMin_; 
        }
        InitializedInstanceOptions& SetCacheSizeMin( UInt64 cacheSizeMin )
        {
            cacheSizeMin_ = cacheSizeMin;
            return *this;
        }
        InitializedInstanceOptions& SetCacheSizeMin( const std::optional<UInt64>& cacheSizeMin )
        {
            cacheSizeMin_ = cacheSizeMin;
            return *this;
        }

        const std::optional<UInt64>& CacheSizeMax() const 
        { 
            return cacheSizeMax_; 
        }
        InitializedInstanceOptions& SetCacheSizeMax( UInt64 cacheSizeMax )
        {
            cacheSizeMax_ = cacheSizeMax;
            return *this;
        }
        InitializedInstanceOptions& SetCacheSizeMax( const std::optional<UInt64>& cacheSizeMax )
        {
            cacheSizeMax_ = cacheSizeMax;
            return *this;
        }

        const std::optional<UInt64>& CheckpointDepthMax() const 
        { 
            return checkpointDepthMax_; 
        }
        InitializedInstanceOptions& SetCheckpointDepthMax( UInt64 checkpointDepthMax )
        {
            checkpointDepthMax_ = checkpointDepthMax;
            return *this;
        }
        InitializedInstanceOptions& SetCheckpointDepthMax( const std::optional<UInt64>& checkpointDepthMax )
        {
            checkpointDepthMax_ = checkpointDepthMax;
            return *this;
        }

        const std::optional<UInt64>& CheckpointIOMax() const 
        { 
            return checkpointIOMax_; 
        }
        InitializedInstanceOptions& SetCheckpointIOMax( UInt64 checkpointIOMax )
        {
            checkpointIOMax_ = checkpointIOMax;
            return *this;
        }
        InitializedInstanceOptions& SetCheckpointIOMax( const std::optional<UInt64>& checkpointIOMax )
        {
            checkpointIOMax_ = checkpointIOMax;
            return *this;
        }


        const std::optional<UInt64>& StartFlushThreshold() const 
        { 
            return startFlushThreshold_; 
        }
        InitializedInstanceOptions& SetStartFlushThreshold( UInt64 startFlushThreshold )
        {
            startFlushThreshold_ = startFlushThreshold;
            return *this;
        }
        InitializedInstanceOptions& SetStartFlushThreshold( const std::optional<UInt64>& startFlushThreshold )
        {
            startFlushThreshold_ = startFlushThreshold;
            return *this;
        }

        const std::optional<UInt64>& StopFlushThreshold() const 
        { 
            return stopFlushThreshold_; 
        }
        InitializedInstanceOptions& SetStopFlushThreshold( UInt64 stopFlushThreshold )
        {
            stopFlushThreshold_ = stopFlushThreshold;
            return *this;
        }
        InitializedInstanceOptions& SetStopFlushThreshold( const std::optional<UInt64>& stopFlushThreshold )
        {
            stopFlushThreshold_ = stopFlushThreshold;
            return *this;
        }

        const std::optional<TransactionFlags>& CommitDefault( ) const 
        { 
            return commitDefault_; 
        }

        InitializedInstanceOptions& SetCommitDefault( TransactionFlags transactionFlags )
        {
            commitDefault_ = transactionFlags;
            return *this;
        }
        InitializedInstanceOptions& SetCommitDefault( const std::optional<TransactionFlags>& transactionFlags )
        {
            commitDefault_ = transactionFlags;
            return *this;
        }


    };


    class UninitializedInstanceOptions : public std::enable_shared_from_this<UninitializedInstanceOptions>
    {
        std::optional<WideString> alternateDatabaseRecoveryPath_;
        std::optional<bool> cleanupMismatchedLogFiles_;
        std::optional<bool> deleteOutOfRangeLogs_;
        std::optional<bool> zeroDatabaseDuringBackup_;
        std::optional<Int32> databasePageSize_;
        std::optional<bool> enableIndexCleanup_;
        std::optional<Int32> pageFragment_;
        std::optional<Int32> waypointLatency_;
        std::optional<bool> defragmentSequentialBTrees_;
        std::optional<Int32> defragmentSequentialBTreesDensityCheckFrequency_;
        std::optional<TimeSpan> ioThrottlingTimeQuanta_;
        std::optional<bool> createPathIfNotExist_;
        std::optional<UInt64> maxCoalesceReadSize_;
        std::optional<UInt64> maxCoalesceWriteSize_;
        std::optional<UInt64> maxCoalesceReadGapSize_;
        std::optional<UInt64> maxCoalesceWriteGapSize_;
        std::optional<bool> disableCallbacks_;
        std::optional<bool> enablePersistedCallbacks_;
        std::optional<WideString> baseName_;
        std::optional<bool> circularLog_;
        std::optional<bool> deleteOldLogs_;
        std::optional<bool> ignoreLogVersion_;
        std::optional<bool> legacyFileNames_;
        std::optional<Int32> logBuffers_;
        std::optional<bool> logFileCreateAsynch_;
        std::optional<WideString> logFilePath_;
        std::optional<Int32> logFileSize_;
        std::optional<WideString> systemPath_;
        std::optional<Int32> numberOfCachedClosedTables_;
        std::optional<Int32> maxCursorCount_;
        std::optional<Int32> maxOpenTableCount_;
        std::optional<Int32> maxSessionCount_;
        std::optional<Int32> maxTemporaryTableCount_;
        std::optional<Int32> maxVersionPageCount_;
    public:
        using Element = Xml::Dom::Element;
        UninitializedInstanceOptions( ) = default;

        void ReadFrom( const Element& element )
        {
            alternateDatabaseRecoveryPath_ = Environment::Expand( element.Read<std::optional<WideString>>( L"AlternateDatabaseRecoveryPath" ) );
            cleanupMismatchedLogFiles_ = element.Read<std::optional<bool>>( L"CleanupMismatchedLogFiles" );
            deleteOutOfRangeLogs_ = element.Read<std::optional<bool>>( L"DeleteOutOfRangeLogs" );
            zeroDatabaseDuringBackup_ = element.Read<std::optional<bool>>( L"ZeroDatabaseDuringBackup" );
            databasePageSize_ = element.Read<std::optional<Int32>>( L"DatabasePageSize" );
            enableIndexCleanup_ = element.Read<std::optional<bool>>( L"EnableIndexCleanup" );
            pageFragment_ = element.Read<std::optional<Int32>>( L"PageFragment" );
            waypointLatency_ = element.Read<std::optional<Int32>>( L"WaypointLatency" );
            defragmentSequentialBTrees_ = element.Read<std::optional<bool>>( L"DefragmentSequentialBTrees" );
            defragmentSequentialBTreesDensityCheckFrequency_ = element.Read<std::optional<Int32>>( L"DefragmentSequentialBTreesDensityCheckFrequency" );
            ioThrottlingTimeQuanta_ = element.Read<std::optional<TimeSpan>>( L"IOThrottlingTimeQuanta" );
            createPathIfNotExist_ = element.Read<std::optional<bool>>( L"CreatePathIfNotExist" );
            maxCoalesceReadSize_ = element.Read<std::optional<UInt64>>( L"MaxCoalesceReadSize" );
            maxCoalesceWriteSize_ = element.Read<std::optional<UInt64>>( L"MaxCoalesceWriteSize" );
            maxCoalesceReadGapSize_ = element.Read<std::optional<UInt64>>( L"MaxCoalesceReadGapSize" );
            maxCoalesceWriteGapSize_ = element.Read<std::optional<UInt64>>( L"MaxCoalesceWriteGapSize" );
            disableCallbacks_ = element.Read<std::optional<bool>>( L"DisableCallbacks" );
            enablePersistedCallbacks_ = element.Read<std::optional<bool>>( L"EnablePersistedCallbacks" );
            baseName_ = element.Read<std::optional<WideString>>( L"BaseName" );
            circularLog_ = element.Read<std::optional<bool>>( L"CircularLog" );
            deleteOldLogs_ = element.Read<std::optional<bool>>( L"DeleteOldLogs" );
            ignoreLogVersion_ = element.Read<std::optional<bool>>( L"IgnoreLogVersion" );
            legacyFileNames_ = element.Read<std::optional<bool>>( L"LegacyFileNames" );
            logBuffers_ = element.Read<std::optional<Int32>>( L"LogBuffers" );
            logFileCreateAsynch_ = element.Read<std::optional<bool>>( L"LogFileCreateAsynch" );
            logFilePath_ = Environment::Expand( element.Read<std::optional<WideString>>( L"LogFilePath" ) );
            logFileSize_ = element.Read<std::optional<Int32>>( L"LogFileSize" );
            systemPath_ = Environment::Expand( element.Read<std::optional<WideString>>( L"SystemPath" ) );
            numberOfCachedClosedTables_ = element.Read<std::optional<Int32>>( L"NumberOfCachedClosedTables" );
            maxCursorCount_ = element.Read<std::optional<Int32>>( L"MaxCursorCount" );
            maxOpenTableCount_ = element.Read<std::optional<Int32>>( L"MaxOpenTableCount" );
            maxSessionCount_ = element.Read<std::optional<Int32>>( L"MaxSessionCount" );
            maxTemporaryTableCount_ = element.Read<std::optional<Int32>>( L"MaxTemporaryTableCount" );
            maxVersionPageCount_ = element.Read<std::optional<Int32>>( L"MaxVersionPageCount" );
        }

        void ApplyTo( const Ese::Instance& instance )
        {
            if ( alternateDatabaseRecoveryPath_ )
            {
                instance.SetAlternateDatabaseRecoveryPath( alternateDatabaseRecoveryPath_.value( ) );
            }
            if ( cleanupMismatchedLogFiles_ )
            {
                instance.SetCleanupMismatchedLogFiles( cleanupMismatchedLogFiles_.value( ) );
            }
            if ( deleteOutOfRangeLogs_ )
            {
                instance.SetDeleteOutOfRangeLogs( deleteOutOfRangeLogs_.value( ) );
            }
            if ( zeroDatabaseDuringBackup_ )
            {
                instance.SetZeroDatabaseDuringBackup( zeroDatabaseDuringBackup_.value( ) );
            }
            if ( databasePageSize_ )
            {
                instance.SetDatabasePageSize( databasePageSize_.value( ) );
            }
            if ( enableIndexCleanup_ )
            {
                instance.SetEnableIndexCleanup( enableIndexCleanup_.value( ) );
            }
            if ( pageFragment_ )
            {
                instance.SetPageFragment( pageFragment_.value( ) );
            }
            if ( waypointLatency_ )
            {
                instance.SetWaypointLatency( waypointLatency_.value( ) );
            }
            if ( defragmentSequentialBTrees_ )
            {
                instance.SetDefragmentSequentialBTrees( defragmentSequentialBTrees_.value( ) );
            }
            if ( defragmentSequentialBTreesDensityCheckFrequency_ )
            {
                instance.SetDefragmentSequentialBTreesDensityCheckFrequency( defragmentSequentialBTreesDensityCheckFrequency_.value( ) );
            }
            if ( ioThrottlingTimeQuanta_ )
            {
                instance.SetIOThrottlingTimeQuanta( ioThrottlingTimeQuanta_.value( ) );
            }
            if ( createPathIfNotExist_ )
            {
                instance.SetCreatePathIfNotExist( createPathIfNotExist_.value( ) );
            }
            if ( maxCoalesceReadSize_ )
            {
                instance.SetMaxCoalesceReadSize( maxCoalesceReadSize_.value( ) );
            }
            if ( maxCoalesceWriteSize_ )
            {
                instance.SetMaxCoalesceWriteSize( maxCoalesceWriteSize_.value( ) );
            }
            if ( maxCoalesceReadGapSize_ )
            {
                instance.SetMaxCoalesceReadGapSize( maxCoalesceReadGapSize_.value( ) );
            }
            if ( maxCoalesceWriteGapSize_ )
            {
                instance.SetMaxCoalesceWriteGapSize( maxCoalesceWriteGapSize_.value( ) );
            }
            if ( disableCallbacks_ )
            {
                instance.SetDisableCallbacks( disableCallbacks_.value( ) );
            }
            if ( enablePersistedCallbacks_ )
            {
                instance.SetEnablePersistedCallbacks( enablePersistedCallbacks_.value( ) );
            }
            if ( baseName_ )
            {
                instance.SetBaseName( baseName_.value( ) );
            }
            if ( circularLog_ )
            {
                instance.SetCircularLog( circularLog_.value( ) );
            }
            if ( deleteOldLogs_ )
            {
                instance.SetDeleteOldLogs( deleteOldLogs_.value( ) );
            }
            if ( ignoreLogVersion_ )
            {
                instance.SetIgnoreLogVersion( ignoreLogVersion_.value( ) );
            }
            if ( legacyFileNames_ )
            {
                instance.SetLegacyFileNames( legacyFileNames_.value( ) );
            }
            if ( logBuffers_ )
            {
                instance.SetLogBuffers( logBuffers_.value( ) );
            }
            if ( logFileCreateAsynch_ )
            {
                instance.SetLogFileCreateAsynch( logFileCreateAsynch_.value( ) );
            }
            if ( logFilePath_ )
            {
                instance.SetLogFilePath( logFilePath_.value( ) );
            }
            if ( logFileSize_ )
            {
                instance.SetLogFileSize( logFileSize_.value( ) );
            }
            if ( systemPath_ )
            {
                instance.SetSystemPath( systemPath_.value( ) );
            }
            if ( numberOfCachedClosedTables_ )
            {
                instance.SetNumberOfCachedClosedTables( numberOfCachedClosedTables_.value( ) );
            }
            if ( maxCursorCount_ )
            {
                instance.SetMaxCursorCount( maxCursorCount_.value( ) );
            }
            if ( maxOpenTableCount_ )
            {
                instance.SetMaxOpenTableCount( maxOpenTableCount_.value( ) );
            }
            if ( maxSessionCount_ )
            {
                instance.SetMaxSessionCount( maxSessionCount_.value( ) );
            }
            if ( maxTemporaryTableCount_ )
            {
                instance.SetMaxTemporaryTableCount( maxTemporaryTableCount_.value( ) );
            }
            if ( maxVersionPageCount_ )
            {
                instance.SetMaxVersionPageCount( maxVersionPageCount_.value( ) );
            }

        }

    };

    class GlobalOptions : public std::enable_shared_from_this<GlobalOptions>
    {
        std::optional<bool> enableIndexChecking_;
        std::optional<bool> oneDatabasePerSession_;
        std::optional<Int32> batchIOBufferMax_;
        std::optional<bool> enableFileCache_;
        std::optional<UInt32> outstandingIOMax_;
        std::optional<bool> enableViewCache_;
        std::optional<TimeSpan> lrukCorrInterval_;
        std::optional<UInt64> lrukHistoryMax_;
        std::optional<UInt32> lrukPolicy_;
        std::optional<TimeSpan> lrukTimeout_;
        std::optional<ExceptionAction> exceptionAction_;
        std::optional<UInt64> eventLogCacheSize_;
        std::optional<bool> monitoringPerformance_;
        std::optional<Int32> globalMinimumVersionPageCount_;
        std::optional<Int32> maximumInstanceCount_;
    public:
        using Element = Xml::Dom::Element;
        GlobalOptions( ) = default;

        void ReadFrom( const Element& element )
        {
            enableIndexChecking_ = element.Read<std::optional<bool>>( L"EnableIndexChecking" );
            oneDatabasePerSession_ = element.Read<std::optional<bool>>( L"OneDatabasePerSession" );
            batchIOBufferMax_ = element.Read<std::optional<Int32>>( L"BatchIOBufferMax" );
            enableFileCache_ = element.Read<std::optional<bool>>( L"EnableFileCache" );
            outstandingIOMax_ = element.Read<std::optional<UInt32>>( L"OutstandingIOMax" );
            enableViewCache_ = element.Read<std::optional<bool>>( L"EnableViewCache" );
            lrukCorrInterval_ = element.Read<std::optional<TimeSpan>>( L"LRUKCorrInterval" );
            lrukHistoryMax_ = element.Read<std::optional<UInt64>>( L"LRUKHistoryMax" );
            lrukPolicy_ = element.Read<std::optional<UInt32>>( L"LRUKPolicy" );
            lrukTimeout_ = element.Read<std::optional<TimeSpan>>( L"LRUKTimeout" );
            exceptionAction_ = element.Read<std::optional<ExceptionAction>>( L"ExceptionAction" );
            eventLogCacheSize_ = element.Read<std::optional<UInt64>>( L"EventLogCacheSize" );
            monitoringPerformance_ = element.Read<std::optional<bool>>( L"MonitoringPerformance" );
            globalMinimumVersionPageCount_ = element.Read<std::optional<Int32>>( L"GlobalMinimumVersionPageCount" );
            maximumInstanceCount_ = element.Read<std::optional<Int32>>( L"MaximumInstanceCount" );
        }

        void Apply( )
        {
            if ( enableIndexChecking_ )
            {
                Ese::Instance::SetEnableIndexChecking( enableIndexChecking_.value() );
            }
            if ( oneDatabasePerSession_ ) 
            { 
                Ese::Instance::SetOneDatabasePerSession( oneDatabasePerSession_.value( ) );
            }
            if ( batchIOBufferMax_ ) 
            { 
                Ese::Instance::SetBatchIOBufferMax( batchIOBufferMax_.value( ) );
            }
            if ( enableFileCache_ ) 
            { 
                Ese::Instance::SetEnableFileCache( enableFileCache_.value( ) );
            }
            if ( outstandingIOMax_ ) 
            { 
                Ese::Instance::SetOutstandingIOMax( outstandingIOMax_.value( ) );
            }
            if ( enableViewCache_ ) 
            { 
                Ese::Instance::SetEnableViewCache( enableViewCache_.value( ) );
            }
            if ( lrukCorrInterval_ ) 
            { 
                Ese::Instance::SetLRUKCorrInterval( lrukCorrInterval_.value( ) );
            }
            if ( lrukHistoryMax_ ) 
            { 
                Ese::Instance::SetLRUKHistoryMax( lrukHistoryMax_.value( ) );
            }
            if ( lrukPolicy_ ) 
            { 
                Ese::Instance::SetLRUKPolicy( lrukPolicy_.value( ) );
            }
            if ( lrukTimeout_ ) 
            { 
                Ese::Instance::SetLRUKTimeout( lrukTimeout_.value( ) );
            }
            if ( exceptionAction_ ) 
            { 
                Ese::Instance::SetExceptionAction( exceptionAction_.value( ) );
            }
            if ( eventLogCacheSize_ ) 
            { 
                Ese::Instance::SetEventLogCacheSize( eventLogCacheSize_.value( ) );
            }
            if ( monitoringPerformance_ ) 
            { 
                Ese::Instance::SetMonitoringPerformance( monitoringPerformance_.value( ) );
            }
            if ( globalMinimumVersionPageCount_ ) 
            { 
                Ese::Instance::SetGlobalMinimumVersionPageCount( globalMinimumVersionPageCount_.value( ) );
            }
            if ( maximumInstanceCount_ ) 
            { 
                Ese::Instance::SetMaximumInstanceCount( maximumInstanceCount_.value( ) );
            }
        }

    };


    class InstanceOptions : public std::enable_shared_from_this<InstanceOptions>
    {
        std::shared_ptr<Ese::InitializedInstanceOptions> initializedInstanceOptions_;
        std::shared_ptr<Ese::UninitializedInstanceOptions> uninitializedInstanceOptions_;
        std::optional<bool> enableBackup_;
        std::optional<WideString> backupDirectory_;
        WideString name_{ L"Default" };
        WideString displayName_{ L"Default" };
        std::optional<Ese::InitFlags> initFlags_;
    public:
        using Element = Xml::Dom::Element;
        InstanceOptions()
            : initializedInstanceOptions_(std::make_shared<Ese::InitializedInstanceOptions>()), uninitializedInstanceOptions_( std::make_shared<Ese::UninitializedInstanceOptions>() )
        { }

        const std::shared_ptr<Ese::InitializedInstanceOptions>& InitializedInstanceOptions( ) const
        {
            return initializedInstanceOptions_;
        }
        const std::shared_ptr<Ese::UninitializedInstanceOptions>& UninitializedInstanceOptions( ) const
        {
            return uninitializedInstanceOptions_;
        }

        void ReadFrom( const Element& element )
        {
            initializedInstanceOptions_->ReadFrom( element );
            uninitializedInstanceOptions_->ReadFrom( element );
            enableBackup_ = element.Read<std::optional<bool>>( L"EnableBackup" );
            backupDirectory_ = Environment::Expand( element.Read<std::optional<WideString>>( L"BackupDirectory" ) );
            if(element.HasAttribute( L"Name" ))
            {
                name_ = element.Read<WideString>( L"Name" );
            }
            if ( element.HasAttribute( L"DisplayName" ) )
            {
                displayName_ = element.Read<WideString>( L"DisplayName" );
            }
            initFlags_ = element.Read<std::optional<Ese::InitFlags>>( L"InitFlags" );
        }

        const std::optional<bool>& EnableBackup( ) const 
        { 
            return enableBackup_; 
        }
        const std::optional<WideString>& BackupDirectory( ) const 
        { 
            return backupDirectory_; 
        }
        const WideString& Name( ) const 
        { 
            return name_; 
        }
        const WideString& DisplayName( ) const 
        { 
            return displayName_; 
        }
        const std::optional<Ese::InitFlags>& InitFlags( ) const 
        { 
            return initFlags_; 
        }

    };

    inline Instance::Instance( const InstanceOptions& instanceOptions )
        : Instance( instanceOptions.Name(), instanceOptions.DisplayName(), instanceOptions.InitFlags().value_or( InitFlags::None ) )
    { 
        auto uninitializedInstanceOptions = instanceOptions.UninitializedInstanceOptions( );
        auto initializedInstanceOptions = instanceOptions.InitializedInstanceOptions( );
        BeforeInit.connect( [ uninitializedInstanceOptions ]( const Instance* instance )
            {
                uninitializedInstanceOptions->ApplyTo( *instance );
            } );
        AfterInit.connect( [ initializedInstanceOptions ]( const Instance* instance )
            {
                initializedInstanceOptions->ApplyTo( *instance );
            } );
    }



    class DatabaseOptions : public std::enable_shared_from_this<DatabaseOptions>
    {
        WideString name_;
        WideString filename_;
        WideString seed_;
        std::optional<UInt32> databaseSizeMax_;
        std::optional<Ese::CreateDatabaseFlags> createDatabaseFlags_;
        
    public:
        using Element = Xml::Dom::Element;
        DatabaseOptions( ) = default;
        DatabaseOptions( const WideString& name, const WideString& filename, Ese::CreateDatabaseFlags createDatabaseFlags )
            : name_( name ), filename_( filename ), createDatabaseFlags_( createDatabaseFlags )
        { }


        void ReadFrom( const Element& element )
        {
            name_ = element.Read<WideString>( L"Name" );
            filename_ = Environment::Expand( element.Read<WideString>( L"Filename" ) );
            seed_ = Environment::Expand( element.Read<WideString>( L"Seed" ) );
            databaseSizeMax_ = element.Read< std::optional<UInt32>>( L"DatabaseSizeMax" );
            createDatabaseFlags_ = element.Read<std::optional<Ese::CreateDatabaseFlags>>( L"CreateDatabaseFlags" );
        }

        const WideString& Name() const 
        { 
            return name_; 
        }
        DatabaseOptions& SetName( const WideString& name )
        {
            name_ = name;
            return *this;
        }

        bool Exist( ) const
        {
            if ( filename_.empty( ) == false )
            {
                return IO::File::Exist( filename_ );
            }
            return false;
        }

        const WideString& Filename() const 
        { 
            return filename_;
        }
        DatabaseOptions& SetFilename( const WideString& filename )
        {
            filename_ = filename;
            return *this;
        }

        const WideString& Seed( ) const
        {
            return seed_;
        }
        DatabaseOptions& SetSeed( const WideString& seed )
        {
            seed_ = seed;
            return *this;
        }

        const std::optional<UInt32>& DatabaseSizeMax() const 
        { 
            return databaseSizeMax_;
        }
        DatabaseOptions& SetDatabaseSizeMax( Int32 databaseSizeMax )
        {
            databaseSizeMax_ = databaseSizeMax;
            return *this;
        }
        DatabaseOptions& SetDatabaseSizeMax( const std::optional<UInt32>& databaseSizeMax )
        {
            databaseSizeMax_ = databaseSizeMax;
            return *this;
        }

        const std::optional<Ese::CreateDatabaseFlags>& CreateDatabaseFlags( ) const
        { 
            return createDatabaseFlags_;
        }

        DatabaseOptions& SetCreateDatabaseFlags( Ese::CreateDatabaseFlags createDatabaseFlags )
        {
            createDatabaseFlags_ = createDatabaseFlags;
            return *this;
        }
        DatabaseOptions& SetCreateDatabaseFlags( const std::optional<Ese::CreateDatabaseFlags>& createDatabaseFlags )
        {
            createDatabaseFlags_ = createDatabaseFlags;
            return *this;
        }

    };



    class Options
    {
        std::shared_ptr<Ese::InstanceOptions> instanceOptions_;
        std::shared_ptr<Ese::GlobalOptions> globalOptions_;
        std::map<WideString, std::shared_ptr<DatabaseOptions>> databases_;
        WideString currentDatabaseName_{ L"Default" };
    public:
        using Element = Xml::Dom::Element;
        Options( )
            : instanceOptions_( std::make_shared<Ese::InstanceOptions>() ), globalOptions_(std::make_shared<Ese::GlobalOptions>())
        {
        }

        const std::shared_ptr<Ese::InstanceOptions>& InstanceOptions( ) const
        {
            return instanceOptions_;
        }
        std::shared_ptr<Ese::GlobalOptions> GlobalOptions( )
        {
            return globalOptions_;
        }

        std::map<WideString, std::shared_ptr<DatabaseOptions>>& Databases( )
        {
            return databases_;
        }
        const std::map<WideString, std::shared_ptr<DatabaseOptions>>& Databases( ) const
        {
            return databases_;
        }


        const WideString& CurrentDatabaseName( ) const noexcept
        {
            return currentDatabaseName_;
        }
        Options& SetCurrentDatabaseName( const WideString& currentDatabaseName ) noexcept
        {
            currentDatabaseName_ = currentDatabaseName;
            return *this;
        }

        bool DatabaseExist( const WideString& databaseName ) const
        {
            auto it = databases_.find( databaseName );
            if ( it != databases_.end( ) )
            {
                return it->second->Exist( );
            }
            return false;
        }

        std::shared_ptr<DatabaseOptions> Find( const WideString& databaseName ) const
        {
            auto it = databases_.find( databaseName );
            if ( it != databases_.end( ) )
            {
                return it->second;
            }
            return {};
        }

        std::shared_ptr<DatabaseOptions> CurrentDatabase( ) const noexcept
        {
            return Find( CurrentDatabaseName( ) );
        }


        std::shared_ptr<DatabaseOptions> Add( const WideString& databaseName, const WideString& databaseFilename, Ese::CreateDatabaseFlags createDatabaseFlags = Ese::CreateDatabaseFlags::None )
        {
            auto it = databases_.find( databaseName );
            if ( it == databases_.end( ) )
            {
                auto result = std::make_shared<DatabaseOptions>( databaseName, databaseFilename, createDatabaseFlags );
                databases_.emplace( databaseName, result );
                return result;
            }
            else
            {
                return it->second;
            }
        }


        void ReadFrom( const Element& element )
        {
            instanceOptions_->ReadFrom( element );
            globalOptions_->ReadFrom( element );
            auto databases = element.FindElement( L"Databases" );
            if( databases )
            {
                auto nodes = databases.ElementsByTagName( L"Database" );
                if ( nodes )
                {
                    auto count = nodes.size( );
                    for ( size_t i = 0; i < count; i++ )
                    {
                        auto node = nodes[ i ];
                        auto databaseElement = node.As<Element>( );
                        if ( databaseElement )
                        {
                            auto databaseOptions = std::make_shared<DatabaseOptions>( );
                            databaseOptions->ReadFrom( databaseElement );
                            auto databaseName = databaseOptions->Name( );
                            databases_.emplace( databaseName, databaseOptions );

                        }
                    }
                }
                if ( databases.HasAttribute( L"CurrentDatabaseName" ) )
                {
                    currentDatabaseName_ = databases.Read<WideString>( L"CurrentDatabaseName" );
                }
            }
        }

        static std::shared_ptr<Options> LoadFromFile( const WideString& filename, const WideString& elementTagName = WideString(L"StorageEngine") )
        {
            Xml::Dom::Document document = Xml::Dom::Document::Create( );
            document.SetAsync( false );
            document.SetValidateOnParse( false );
            document.SetResolveExternals( false );
            document.SetPreserveWhiteSpace( false );
            if ( document.Load( filename ) )
            {
                auto documentElement = document.DocumentElement( );
                if ( documentElement )
                {
                    auto element = documentElement.FindElement( elementTagName.c_str() );
                    if ( element )
                    {
                        auto result = std::make_shared<Options>( );
                        result->ReadFrom( element );
                        return result;
                    }
                }
            }
            return {};
        }

        static std::shared_ptr<Options> LoadFromFile( const wchar_t* filename, const WideString& elementTagName = WideString( L"StorageEngine" ) )
        {
            return LoadFromFile( WideString( filename ), elementTagName );
        }
        static std::shared_ptr<Options> LoadFromFile( const wchar_t* filename, const wchar_t* elementTagName )
        {
            return LoadFromFile( WideString( filename ), WideString( elementTagName ) );
        }


    };

}

#endif
