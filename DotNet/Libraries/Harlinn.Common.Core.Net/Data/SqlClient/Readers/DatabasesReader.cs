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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class DatabasesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT sd.[name]
                ,sd.[database_id]
                ,sd.[source_database_id]
                ,sd.[owner_sid]
                ,sd.[create_date]
                ,sd.[compatibility_level]
                ,sd.[collation_name]
                ,sd.[user_access]
                ,sd.[user_access_desc]
                ,sd.[is_read_only]
                ,sd.[is_auto_close_on]
                ,sd.[is_auto_shrink_on]
                ,sd.[state]
                ,sd.[state_desc]
                ,sd.[is_in_standby]
                ,sd.[is_cleanly_shutdown]
                ,sd.[is_supplemental_logging_enabled]
                ,sd.[snapshot_isolation_state]
                ,sd.[snapshot_isolation_state_desc]
                ,sd.[is_read_committed_snapshot_on]
                ,sd.[recovery_model]
                ,sd.[recovery_model_desc]
                ,sd.[page_verify_option]
                ,sd.[page_verify_option_desc]
                ,sd.[is_auto_create_stats_on]
                ,sd.[is_auto_create_stats_incremental_on]
                ,sd.[is_auto_update_stats_on]
                ,sd.[is_auto_update_stats_async_on]
                ,sd.[is_ansi_null_default_on]
                ,sd.[is_ansi_nulls_on]
                ,sd.[is_ansi_padding_on]
                ,sd.[is_ansi_warnings_on]
                ,sd.[is_arithabort_on]
                ,sd.[is_concat_null_yields_null_on]
                ,sd.[is_numeric_roundabort_on]
                ,sd.[is_quoted_identifier_on]
                ,sd.[is_recursive_triggers_on]
                ,sd.[is_cursor_close_on_commit_on]
                ,sd.[is_local_cursor_default]
                ,sd.[is_fulltext_enabled]
                ,sd.[is_trustworthy_on]
                ,sd.[is_db_chaining_on]
                ,sd.[is_parameterization_forced]
                ,sd.[is_master_key_encrypted_by_server]
                ,sd.[is_query_store_on]
                ,sd.[is_published]
                ,sd.[is_subscribed]
                ,sd.[is_merge_published]
                ,sd.[is_distributor]
                ,sd.[is_sync_with_backup]
                ,sd.[service_broker_guid]
                ,sd.[is_broker_enabled]
                ,sd.[log_reuse_wait]
                ,sd.[log_reuse_wait_desc]
                ,sd.[is_date_correlation_on]
                ,sd.[is_cdc_enabled]
                ,sd.[is_encrypted]
                ,sd.[is_honor_broker_priority_on]
                ,sd.[replica_id]
                ,sd.[group_database_id]
                ,sd.[resource_pool_id]
                ,sd.[default_language_lcid]
                ,sd.[default_language_name]
                ,sd.[default_fulltext_language_lcid]
                ,sd.[default_fulltext_language_name]
                ,sd.[is_nested_triggers_on]
                ,sd.[is_transform_noise_words_on]
                ,sd.[two_digit_year_cutoff]
                ,sd.[containment]
                ,sd.[containment_desc]
                ,sd.[target_recovery_time_in_seconds]
                ,sd.[delayed_durability]
                ,sd.[delayed_durability_desc]
                ,sd.[is_memory_optimized_elevate_to_snapshot_on]
                ,sd.[is_federation_member]
                ,sd.[is_remote_data_archive_enabled]
                ,sd.[is_mixed_page_allocation_on]
                ,sd.[is_temporal_history_retention_enabled]
                ,sd.[catalog_collation_type]
                ,sd.[catalog_collation_type_desc]
                ,sd.[physical_database_name]
                ,sd.[is_result_set_caching_on]
                ,sd.[is_accelerated_database_recovery_on]
                ,sd.[is_tempdb_spill_to_remote_store]
                ,sd.[is_stale_page_detection_on]
                ,sd.[is_memory_optimized_enabled]
            FROM [sys].[databases] sd
            """;

        public const int NameOrdinal = 0;
        public const int DatabaseIdOrdinal = 1;
        public const int SourceDatabaseIdOrdinal = 2;
        public const int OwnerSidOrdinal = 3;
        public const int CreateDateOrdinal = 4;
        public const int CompatibilityLevelOrdinal = 5;
        public const int CollationNameOrdinal = 6;
        public const int UserAccessOrdinal = 7;
        public const int UserAccessDescOrdinal = 8;
        public const int IsReadOnlyOrdinal = 9;
        public const int IsAutoCloseOnOrdinal = 10;
        public const int IsAutoShrinkOnOrdinal = 11;
        public const int StateOrdinal = 12;
        public const int StateDescOrdinal = 13;
        public const int IsInStandbyOrdinal = 14;
        public const int IsCleanlyShutdownOrdinal = 15;
        public const int IsSupplementalLoggingEnabledOrdinal = 16;
        public const int SnapshotIsolationStateOrdinal = 17;
        public const int SnapshotIsolationStateDescOrdinal = 18;
        public const int IsReadCommittedSnapshotOnOrdinal = 19;
        public const int RecoveryModelOrdinal = 20;
        public const int RecoveryModelDescOrdinal = 21;
        public const int PageVerifyOptionOrdinal = 22;
        public const int PageVerifyOptionDescOrdinal = 23;
        public const int IsAutoCreateStatsOnOrdinal = 24;
        public const int IsAutoCreateStatsIncrementalOnOrdinal = 25;
        public const int IsAutoUpdateStatsOnOrdinal = 26;
        public const int IsAutoUpdateStatsAsyncOnOrdinal = 27;
        public const int IsAnsiNullDefaultOnOrdinal = 28;
        public const int IsAnsiNullsOnOrdinal = 29;
        public const int IsAnsiPaddingOnOrdinal = 30;
        public const int IsAnsiWarningsOnOrdinal = 31;
        public const int IsArithAbortOnOrdinal = 32;
        public const int IsConcatNullYieldsNullOnOrdinal = 33;
        public const int IsNumericRoundAbortOnOrdinal = 34;
        public const int IsQuotedIdentifierOnOrdinal = 35;
        public const int IsRecursiveTriggersOnOrdinal = 36;
        public const int IsCursorCloseOnCommitOnOrdinal = 37;
        public const int IsLocalCursorDefaultOrdinal = 38;
        public const int IsFulltextEnabledOrdinal = 39;
        public const int IsTrustworthyOnOrdinal = 40;
        public const int IsDbChainingOnOrdinal = 41;
        public const int IsParameterizationForcedOrdinal = 42;
        public const int IsMasterKeyEncryptedByServerOrdinal = 43;
        public const int IsQueryStoreOnOrdinal = 44;
        public const int IsPublishedOrdinal = 45;
        public const int IsSubscribedOrdinal = 46;
        public const int IsMergePublishedOrdinal = 47;
        public const int IsDistributorOrdinal = 48;
        public const int IsSyncWithBackupOrdinal = 49;
        public const int ServiceBrokerGuidOrdinal = 50;
        public const int IsBrokerEnabledOrdinal = 51;
        public const int LogReuseWaitOrdinal = 52;
        public const int LogReuseWaitDescOrdinal = 53;
        public const int IsDateCorrelationOnOrdinal = 54;
        public const int IsCdcEnabledOrdinal = 55;
        public const int IsEncryptedOrdinal = 56;
        public const int IsHonorBrokerPriorityOnOrdinal = 57;
        public const int ReplicaIdOrdinal = 58;
        public const int GroupDatabaseIdOrdinal = 59;
        public const int ResourcePoolIdOrdinal = 60;
        public const int DefaultLanguageLcidOrdinal = 61;
        public const int DefaultLanguageNameOrdinal = 62;
        public const int DefaultFulltextLanguageLcidOrdinal = 63;
        public const int DefaultFulltextLanguageNameOrdinal = 64;
        public const int IsNestedTriggersOnOrdinal = 65;
        public const int IsTransformNoiseWordsOnOrdinal = 66;
        public const int TwoDigitYearCutoffOrdinal = 67;
        public const int ContainmentOrdinal = 68;
        public const int ContainmentDescOrdinal = 69;
        public const int TargetRecoveryTimeInSecondsOrdinal = 70;
        public const int DelayedDurabilityOrdinal = 71;
        public const int DelayedDurabilityDescOrdinal = 72;
        public const int IsMemoryOptimizedElevateToSnapshotOnOrdinal = 73;
        public const int IsFederationMemberOrdinal = 74;
        public const int IsRemoteDataArchiveEnabledOrdinal = 75;
        public const int IsMixedPageAllocationOnOrdinal = 76;
        public const int IsTemporalHistoryRetentionEnabledOrdinal = 77;
        public const int CatalogCollationTypeOrdinal = 78;
        public const int CatalogCollationTypeDescOrdinal = 79;
        public const int PhysicalDatabaseNameOrdinal = 80;
        public const int IsResultSetCachingOnOrdinal = 81;
        public const int IsAcceleratedDatabaseRecoveryOnOrdinal = 82;
        public const int IsTempdbSpillToRemoteStoreOrdinal = 83;
        public const int IsStalePageDetectionOnOrdinal = 84;
        public const int IsMemoryOptimizedEnabledOrdinal = 85;


        public DatabasesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public DatabasesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public DatabasesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName()
        {
            return base.GetString(NameOrdinal);
        }

        public int GetDatabaseId()
        {
            return base.GetInt32(DatabaseIdOrdinal);
        }

        public int? GetSourceDatabaseId()
        {
            return base.GetNullableInt32(SourceDatabaseIdOrdinal);
        }

        public byte[] GetOwnerSid()
        {
            return base.GetBinary(OwnerSidOrdinal);
        }

        public DateTime GetCreateDate()
        {
            return base.GetDateTime(CreateDateOrdinal);
        }

        public byte GetCompatibilityLevel()
        {
            return base.GetByte(CompatibilityLevelOrdinal);
        }

        public string? GetCollationName()
        {
            return base.GetNullableString(CollationNameOrdinal);
        }

        public DatabaseUserAccess GetUserAccess()
        {
            return (DatabaseUserAccess)base.GetByte(UserAccessOrdinal);
        }

        public string GetUserAccessDesc()
        {
            return base.GetString(UserAccessDescOrdinal);
        }

        public bool GetIsReadOnly()
        {
            return base.GetBoolean(IsReadOnlyOrdinal);
        }

        public bool GetIsAutoCloseOn()
        {
            return base.GetBoolean(IsAutoCloseOnOrdinal);
        }

        public bool GetIsAutoShrinkOn()
        {
            return base.GetBoolean(IsAutoShrinkOnOrdinal);
        }

        public DatabaseState GetState()
        {
            return (DatabaseState)base.GetByte(StateOrdinal);
        }

        public string GetStateDesc()
        {
            return base.GetString(StateDescOrdinal);
        }

        public bool GetIsInStandby()
        {
            return base.GetBoolean(IsInStandbyOrdinal);
        }

        public bool GetIsCleanlyShutdown()
        {
            return base.GetBoolean(IsCleanlyShutdownOrdinal);
        }

        public bool GetIsSupplementalLoggingEnabled()
        {
            return base.GetBoolean(IsSupplementalLoggingEnabledOrdinal);
        }

        public byte GetSnapshotIsolationState()
        {
            return base.GetByte(SnapshotIsolationStateOrdinal);
        }

        public string GetSnapshotIsolationStateDesc()
        {
            return base.GetString(SnapshotIsolationStateDescOrdinal);
        }

        public bool GetIsReadCommittedSnapshotOn()
        {
            return base.GetBoolean(IsReadCommittedSnapshotOnOrdinal);
        }

        public RecoveryModel GetRecoveryModel()
        {
            return (RecoveryModel)base.GetByte(RecoveryModelOrdinal);
        }

        public string GetRecoveryModelDesc()
        {
            return base.GetString(RecoveryModelDescOrdinal);
        }

        public PageVerifyOption GetPageVerifyOption()
        {
            return (PageVerifyOption)base.GetByte(PageVerifyOptionOrdinal);
        }

        public string GetPageVerifyOptionDesc()
        {
            return base.GetString(PageVerifyOptionDescOrdinal);
        }

        public bool GetIsAutoCreateStatsOn()
        {
            return base.GetBoolean(IsAutoCreateStatsOnOrdinal);
        }

        public bool GetIsAutoCreateStatsIncrementalOn()
        {
            return base.GetBoolean(IsAutoCreateStatsIncrementalOnOrdinal);
        }

        public bool GetIsAutoUpdateStatsOn()
        {
            return base.GetBoolean(IsAutoUpdateStatsOnOrdinal);
        }

        public bool GetIsAutoUpdateStatsAsyncOn()
        {
            return base.GetBoolean(IsAutoUpdateStatsAsyncOnOrdinal);
        }

        public bool GetIsAnsiNullDefaultOn()
        {
            return base.GetBoolean(IsAnsiNullDefaultOnOrdinal);
        }

        public bool GetIsAnsiNullsOn()
        {
            return base.GetBoolean(IsAnsiNullsOnOrdinal);
        }

        public bool GetIsAnsiPaddingOn()
        {
            return base.GetBoolean(IsAnsiPaddingOnOrdinal);
        }

        public bool GetIsAnsiWarningsOn()
        {
            return base.GetBoolean(IsAnsiWarningsOnOrdinal);
        }

        public bool GetIsArithAbortOn()
        {
            return base.GetBoolean(IsArithAbortOnOrdinal);
        }

        public bool GetIsConcatNullYieldsNullOn()
        {
            return base.GetBoolean(IsConcatNullYieldsNullOnOrdinal);
        }

        public bool GetIsNumericRoundAbortOn()
        {
            return base.GetBoolean(IsNumericRoundAbortOnOrdinal);
        }

        public bool GetIsQuotedIdentifierOn()
        {
            return base.GetBoolean(IsQuotedIdentifierOnOrdinal);
        }
        public bool GetIsRecursiveTriggersOn()
        {
            return base.GetBoolean(IsRecursiveTriggersOnOrdinal);
        }

        public bool GetIsCursorCloseOnCommitOn()
        {
            return base.GetBoolean(IsCursorCloseOnCommitOnOrdinal);
        }

        public bool GetIsLocalCursorDefault()
        {
            return base.GetBoolean(IsLocalCursorDefaultOrdinal);
        }

        public bool GetIsFulltextEnabled()
        {
            return base.GetBoolean(IsFulltextEnabledOrdinal);
        }

        public bool GetIsTrustworthyOn()
        {
            return base.GetBoolean(IsTrustworthyOnOrdinal);
        }

        public bool GetIsDbChainingOn()
        {
            return base.GetBoolean(IsDbChainingOnOrdinal);
        }

        public bool GetIsParameterizationForced()
        {
            return base.GetBoolean(IsParameterizationForcedOrdinal);
        }

        public bool GetIsMasterKeyEncryptedByServer()
        {
            return base.GetBoolean(IsMasterKeyEncryptedByServerOrdinal);
        }

        public bool GetIsQueryStoreOn()
        {
            return base.GetBoolean(IsQueryStoreOnOrdinal);
        }

        public bool GetIsPublished()
        {
            return base.GetBoolean(IsPublishedOrdinal);
        }

        public bool GetIsSubscribed()
        {
            return base.GetBoolean(IsSubscribedOrdinal);
        }

        public bool GetIsMergePublished()
        {
            return base.GetBoolean(IsMergePublishedOrdinal);
        }

        public bool GetIsDistributor()
        {
            return base.GetBoolean(IsDistributorOrdinal);
        }

        public bool GetIsSyncWithBackup()
        {
            return base.GetBoolean(IsSyncWithBackupOrdinal);
        }

        public Guid GetServiceBrokerGuid()
        {
            return base.GetGuid(ServiceBrokerGuidOrdinal);
        }

        public bool GetIsBrokerEnabled()
        {
            return base.GetBoolean(IsBrokerEnabledOrdinal);
        }

        public short GetLogReuseWait()
        {
            return base.GetInt16(LogReuseWaitOrdinal);
        }

        public string GetLogReuseWaitDesc()
        {
            return base.GetString(LogReuseWaitDescOrdinal);
        }

        public bool GetIsDateCorrelationOn()
        {
            return base.GetBoolean(IsDateCorrelationOnOrdinal);
        }

        public bool GetIsCdcEnabled()
        {
            return base.GetBoolean(IsCdcEnabledOrdinal);
        }

        public bool GetIsEncrypted()
        {
            return base.GetBoolean(IsEncryptedOrdinal);
        }

        public bool GetIsHonorBrokerPriorityOn()
        {
            return base.GetBoolean(IsHonorBrokerPriorityOnOrdinal);
        }

        public Guid? GetReplicaId()
        {
            return base.GetNullableGuid(ReplicaIdOrdinal);
        }

        public Guid? GetGroupDatabaseId()
        {
            return base.GetNullableGuid(GroupDatabaseIdOrdinal);
        }

        public int GetResourcePoolId()
        {
            return base.GetInt32(ResourcePoolIdOrdinal);
        }

        public short GetDefaultLanguageLcid()
        {
            return base.GetInt16(DefaultLanguageLcidOrdinal);
        }

        public string? GetDefaultLanguageName()
        {
            return base.GetNullableString(DefaultLanguageNameOrdinal);
        }

        public int? GetDefaultFulltextLanguageLcid()
        {
            return base.GetNullableInt32(DefaultFulltextLanguageLcidOrdinal);
        }

        public string? GetDefaultFulltextLanguageName()
        {
            return base.GetNullableString(DefaultFulltextLanguageNameOrdinal);
        }

        public bool GetIsNestedTriggersOn()
        {
            return base.GetBoolean(IsNestedTriggersOnOrdinal);
        }

        public bool GetIsTransformNoiseWordsOn()
        {
            return base.GetBoolean(IsTransformNoiseWordsOnOrdinal);
        }

        public short GetTwoDigitYearCutoff()
        {
            return base.GetInt16(TwoDigitYearCutoffOrdinal);
        }

        public byte GetContainment()
        {
            return base.GetByte(ContainmentOrdinal);
        }

        public string GetContainmentDesc()
        {
            return base.GetString(ContainmentDescOrdinal);
        }

        public int? GetTargetRecoveryTimeInSeconds()
        {
            return base.GetNullableInt32(TargetRecoveryTimeInSecondsOrdinal);
        }

        public byte GetDelayedDurability()
        {
            return base.GetByte(DelayedDurabilityOrdinal);
        }

        public string GetDelayedDurabilityDesc()
        {
            return base.GetString(DelayedDurabilityDescOrdinal);
        }

        public bool GetIsMemoryOptimizedElevateToSnapshotOn()
        {
            return base.GetBoolean(IsMemoryOptimizedElevateToSnapshotOnOrdinal);
        }

        public bool GetIsFederationMember()
        {
            return base.GetBoolean(IsFederationMemberOrdinal);
        }

        public bool GetIsRemoteDataArchiveEnabled()
        {
            return base.GetBoolean(IsRemoteDataArchiveEnabledOrdinal);
        }

        public bool GetIsMixedPageAllocationOn()
        {
            return base.GetBoolean(IsMixedPageAllocationOnOrdinal);
        }

        public bool GetIsTemporalHistoryRetentionEnabled()
        {
            return base.GetBoolean(IsTemporalHistoryRetentionEnabledOrdinal);
        }

        public int GetCatalogCollationType()
        {
            return base.GetInt32(CatalogCollationTypeOrdinal);
        }

        public string GetCatalogCollationTypeDesc()
        {
            return base.GetString(CatalogCollationTypeDescOrdinal);
        }

        public string GetPhysicalDatabaseName()
        {
            return base.GetString(PhysicalDatabaseNameOrdinal);
        }

        public bool GetIsResultSetCachingOn()
        {
            return base.GetBoolean(IsResultSetCachingOnOrdinal);
        }

        public bool GetIsAcceleratedDatabaseRecoveryOn()
        {
            return base.GetBoolean(IsAcceleratedDatabaseRecoveryOnOrdinal);
        }

        public bool GetIsTempdbSpillToRemoteStore()
        {
            return base.GetBoolean(IsTempdbSpillToRemoteStoreOrdinal);
        }

        public bool GetIsStalePageDetectionOn()
        {
            return base.GetBoolean(IsStalePageDetectionOnOrdinal);
        }

        public bool GetIsMemoryOptimizedEnabled()
        {
            return base.GetBoolean(IsMemoryOptimizedEnabledOrdinal);
        }




        
        public Types.Database GetDatabase()
        {
            string name = GetName();
            int databaseId = GetDatabaseId();
            int? sourceDatabaseId = GetSourceDatabaseId();
            byte[] ownerSid = GetOwnerSid();
            DateTime createDate = GetCreateDate();
            byte compatibilityLevel = GetCompatibilityLevel();
            string collationName = GetCollationName();
            DatabaseUserAccess userAccess = GetUserAccess();
            string userAccessDesc = GetUserAccessDesc();
            bool isReadOnly = GetIsReadOnly();
            bool isAutoCloseOn = GetIsAutoCloseOn();
            bool isAutoShrinkOn = GetIsAutoShrinkOn();
            DatabaseState state = GetState();
            string stateDesc = GetStateDesc();
            bool isInStandby = GetIsInStandby();
            bool isCleanlyShutdown = GetIsCleanlyShutdown();
            bool isSupplementalLoggingEnabled = GetIsSupplementalLoggingEnabled();
            byte snapshotIsolationState = GetSnapshotIsolationState();
            string snapshotIsolationStateDesc = GetSnapshotIsolationStateDesc();
            bool isReadCommittedSnapshotOn = GetIsReadCommittedSnapshotOn();
            RecoveryModel recoveryModel = GetRecoveryModel();
            string recoveryModelDesc = GetRecoveryModelDesc();
            PageVerifyOption pageVerifyOption = GetPageVerifyOption();
            string pageVerifyOptionDesc = GetPageVerifyOptionDesc();
            bool isAutoCreateStatsOn = GetIsAutoCreateStatsOn();
            bool isAutoCreateStatsIncrementalOn = GetIsAutoCreateStatsIncrementalOn();
            bool isAutoUpdateStatsOn = GetIsAutoUpdateStatsOn();
            bool isAutoUpdateStatsAsyncOn = GetIsAutoUpdateStatsAsyncOn();
            bool isAnsiNullDefaultOn = GetIsAnsiNullDefaultOn();
            bool isAnsiNullsOn = GetIsAnsiNullsOn();
            bool isAnsiPaddingOn = GetIsAnsiPaddingOn();
            bool isAnsiWarningsOn = GetIsAnsiWarningsOn();
            bool isArithAbortOn = GetIsArithAbortOn();
            bool isConcatNullYieldsNullOn = GetIsConcatNullYieldsNullOn();
            bool isNumericRoundAbortOn = GetIsNumericRoundAbortOn();
            bool isQuotedIdentifierOn = GetIsQuotedIdentifierOn();
            bool isRecursiveTriggersOn = GetIsRecursiveTriggersOn();
            bool isCursorCloseOnCommitOn = GetIsCursorCloseOnCommitOn();
            bool isLocalCursorDefault = GetIsLocalCursorDefault();
            bool isFulltextEnabled = GetIsFulltextEnabled();
            bool isTrustworthyOn = GetIsTrustworthyOn();
            bool isDbChainingOn = GetIsDbChainingOn();
            bool isParameterizationForced = GetIsParameterizationForced();
            bool isMasterKeyEncryptedByServer = GetIsMasterKeyEncryptedByServer();
            bool isQueryStoreOn = GetIsQueryStoreOn();
            bool isPublished = GetIsPublished();
            bool isSubscribed = GetIsSubscribed();
            bool isMergePublished = GetIsMergePublished();
            bool isDistributor = GetIsDistributor();
            bool isSyncWithBackup = GetIsSyncWithBackup();
            Guid serviceBrokerGuid = GetServiceBrokerGuid();
            bool isBrokerEnabled = GetIsBrokerEnabled();
            short logReuseWait = GetLogReuseWait();
            string logReuseWaitDesc = GetLogReuseWaitDesc();
            bool isDateCorrelationOn = GetIsDateCorrelationOn();
            bool isCdcEnabled = GetIsCdcEnabled();
            bool isEncrypted = GetIsEncrypted();
            bool isHonorBrokerPriorityOn = GetIsHonorBrokerPriorityOn();
            Guid? replicaId = GetReplicaId();
            Guid? groupDatabaseId = GetGroupDatabaseId();
            int resourcePoolId = GetResourcePoolId();
            short defaultLanguageLcid = GetDefaultLanguageLcid();
            string defaultLanguageName = GetDefaultLanguageName();
            int? defaultFulltextLanguageLcid = GetDefaultFulltextLanguageLcid();
            string defaultFulltextLanguageName = GetDefaultFulltextLanguageName();
            bool isNestedTriggersOn = GetIsNestedTriggersOn();
            bool isTransformNoiseWordsOn = GetIsTransformNoiseWordsOn();
            short twoDigitYearCutoff = GetTwoDigitYearCutoff();
            byte containment = GetContainment();
            string containmentDesc = GetContainmentDesc();
            int? targetRecoveryTimeInSeconds = GetTargetRecoveryTimeInSeconds();
            byte delayedDurability = GetDelayedDurability();
            string delayedDurabilityDesc = GetDelayedDurabilityDesc();
            bool isMemoryOptimizedElevateToSnapshotOn = GetIsMemoryOptimizedElevateToSnapshotOn();
            bool isFederationMember = GetIsFederationMember();
            bool isRemoteDataArchiveEnabled = GetIsRemoteDataArchiveEnabled();
            bool isMixedPageAllocationOn = GetIsMixedPageAllocationOn();
            bool isTemporalHistoryRetentionEnabled = GetIsTemporalHistoryRetentionEnabled();
            int catalogCollationType = GetCatalogCollationType();
            string catalogCollationTypeDesc = GetCatalogCollationTypeDesc();
            string physicalDatabaseName = GetPhysicalDatabaseName();
            bool isResultSetCachingOn = GetIsResultSetCachingOn();
            bool isAcceleratedDatabaseRecoveryOn = GetIsAcceleratedDatabaseRecoveryOn();
            bool isTempdbSpillToRemoteStore = GetIsTempdbSpillToRemoteStore();
            bool isStalePageDetectionOn = GetIsStalePageDetectionOn();
            bool isMemoryOptimizedEnabled = GetIsMemoryOptimizedEnabled();

            return new Types.Database(
                name,
                databaseId,
                sourceDatabaseId,
                ownerSid,
                createDate,
                compatibilityLevel,
                collationName,
                userAccess,
                userAccessDesc,
                isReadOnly,
                isAutoCloseOn,
                isAutoShrinkOn,
                state,
                stateDesc,
                isInStandby,
                isCleanlyShutdown,
                isSupplementalLoggingEnabled,
                snapshotIsolationState,
                snapshotIsolationStateDesc,
                isReadCommittedSnapshotOn,
                recoveryModel,
                recoveryModelDesc,
                pageVerifyOption,
                pageVerifyOptionDesc,
                isAutoCreateStatsOn,
                isAutoCreateStatsIncrementalOn,
                isAutoUpdateStatsOn,
                isAutoUpdateStatsAsyncOn,
                isAnsiNullDefaultOn,
                isAnsiNullsOn,
                isAnsiPaddingOn,
                isAnsiWarningsOn,
                isArithAbortOn,
                isConcatNullYieldsNullOn,
                isNumericRoundAbortOn,
                isQuotedIdentifierOn,
                isRecursiveTriggersOn,
                isCursorCloseOnCommitOn,
                isLocalCursorDefault,
                isFulltextEnabled,
                isTrustworthyOn,
                isDbChainingOn,
                isParameterizationForced,
                isMasterKeyEncryptedByServer,
                isQueryStoreOn,
                isPublished,
                isSubscribed,
                isMergePublished,
                isDistributor,
                isSyncWithBackup,
                serviceBrokerGuid,
                isBrokerEnabled,
                logReuseWait,
                logReuseWaitDesc,
                isDateCorrelationOn,
                isCdcEnabled,
                isEncrypted,
                isHonorBrokerPriorityOn,
                replicaId,
                groupDatabaseId,
                resourcePoolId,
                defaultLanguageLcid,
                defaultLanguageName,
                defaultFulltextLanguageLcid,
                defaultFulltextLanguageName,
                isNestedTriggersOn,
                isTransformNoiseWordsOn,
                twoDigitYearCutoff,
                containment,
                containmentDesc,
                targetRecoveryTimeInSeconds,
                delayedDurability,
                delayedDurabilityDesc,
                isMemoryOptimizedElevateToSnapshotOn,
                isFederationMember,
                isRemoteDataArchiveEnabled,
                isMixedPageAllocationOn,
                isTemporalHistoryRetentionEnabled,
                catalogCollationType,
                catalogCollationTypeDesc,
                physicalDatabaseName,
                isResultSetCachingOn,
                isAcceleratedDatabaseRecoveryOn,
                isTempdbSpillToRemoteStore,
                isStalePageDetectionOn,
                isMemoryOptimizedEnabled);
        }

        
        public IReadOnlyList<Database> GetDatabases()
        {
            var databases = new List<Database>();
            while (Read())
            {
                databases.Add(GetDatabase());
            }
            return databases;
        }
        
    }

}
