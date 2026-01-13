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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public class Database
    {
        readonly string _name;
        readonly int _databaseId;
        readonly int? _sourceDatabaseId;
        readonly byte[] _ownerSid;
        readonly DateTime _createDate;
        readonly byte _compatibilityLevel;
        readonly string _collationName;
        readonly DatabaseUserAccess _userAccess;
        readonly string _userAccessDesc;
        readonly bool _isReadOnly;
        readonly bool _isAutoCloseOn;
        readonly bool _isAutoShrinkOn;
        readonly DatabaseState _state;
        readonly string _stateDesc;
        readonly bool _isInStandby;
        readonly bool _isCleanlyShutdown;
        readonly bool _isSupplementalLoggingEnabled;
        readonly byte _snapshotIsolationState;
        readonly string _snapshotIsolationStateDesc;
        readonly bool _isReadCommittedSnapshotOn;
        readonly RecoveryModel _recoveryModel;
        readonly string _recoveryModelDesc;
        readonly PageVerifyOption _pageVerifyOption;
        readonly string _pageVerifyOptionDesc;
        readonly bool _isAutoCreateStatsOn;
        readonly bool _isAutoCreateStatsIncrementalOn;
        readonly bool _isAutoUpdateStatsOn;
        readonly bool _isAutoUpdateStatsAsyncOn;
        readonly bool _isAnsiNullDefaultOn;
        readonly bool _isAnsiNullsOn;
        readonly bool _isAnsiPaddingOn;
        readonly bool _isAnsiWarningsOn;
        readonly bool _isArithAbortOn;
        readonly bool _isConcatNullYieldsNullOn;
        readonly bool _isNumericRoundAbortOn;
        readonly bool _isQuotedIdentifierOn;
        readonly bool _isRecursiveTriggersOn;
        readonly bool _isCursorCloseOnCommitOn;
        readonly bool _isLocalCursorDefault;
        readonly bool _isFulltextEnabled;
        readonly bool _isTrustworthyOn;
        readonly bool _isDbChainingOn;
        readonly bool _isParameterizationForced;
        readonly bool _isMasterKeyEncryptedByServer;
        readonly bool _isQueryStoreOn;
        readonly bool _isPublished;
        readonly bool _isSubscribed;
        readonly bool _isMergePublished;
        readonly bool _isDistributor;
        readonly bool _isSyncWithBackup;
        readonly Guid _serviceBrokerGuid;
        readonly bool _isBrokerEnabled;
        readonly short _logReuseWait;
        readonly string _logReuseWaitDesc;
        readonly bool _isDateCorrelationOn;
        readonly bool _isCdcEnabled;
        readonly bool _isEncrypted;
        readonly bool _isHonorBrokerPriorityOn;
        readonly Guid? _replicaId;
        readonly Guid? _groupDatabaseId;
        readonly int _resourcePoolId;
        readonly short _defaultLanguageLcid;
        readonly string _defaultLanguageName;
        readonly int? _defaultFulltextLanguageLcid;
        readonly string _defaultFulltextLanguageName;
        readonly bool _isNestedTriggersOn;
        readonly bool _isTransformNoiseWordsOn;
        readonly short _twoDigitYearCutoff;
        readonly byte _containment;
        readonly string _containmentDesc;
        readonly int? _targetRecoveryTimeInSeconds;
        readonly byte _delayedDurability;
        readonly string _delayedDurabilityDesc;
        readonly bool _isMemoryOptimizedElevateToSnapshotOn;
        readonly bool _isFederationMember;
        readonly bool _isRemoteDataArchiveEnabled;
        readonly bool _isMixedPageAllocationOn;
        readonly bool _isTemporalHistoryRetentionEnabled;
        readonly int _catalogCollationType;
        readonly string _catalogCollationTypeDesc;
        readonly string _physicalDatabaseName;
        readonly bool _isResultSetCachingOn;
        readonly bool _isAcceleratedDatabaseRecoveryOn;
        readonly bool _isTempdbSpillToRemoteStore;
        readonly bool _isStalePageDetectionOn;
        readonly bool _isMemoryOptimizedEnabled;

        public Database(string name, int databaseId, int? sourceDatabaseId, byte[] ownerSid, DateTime createDate, byte compatibilityLevel, string collationName, DatabaseUserAccess userAccess, string userAccessDesc, bool isReadOnly, bool isAutoCloseOn, bool isAutoShrinkOn, DatabaseState state, string stateDesc, bool isInStandby, bool isCleanlyShutdown, bool isSupplementalLoggingEnabled, byte snapshotIsolationState, string snapshotIsolationStateDesc, bool isReadCommittedSnapshotOn, RecoveryModel recoveryModel, string recoveryModelDesc, PageVerifyOption pageVerifyOption, string pageVerifyOptionDesc, bool isAutoCreateStatsOn, bool isAutoCreateStatsIncrementalOn, bool isAutoUpdateStatsOn, bool isAutoUpdateStatsAsyncOn, bool isAnsiNullDefaultOn, bool isAnsiNullsOn, bool isAnsiPaddingOn, bool isAnsiWarningsOn, bool isArithAbortOn, bool isConcatNullYieldsNullOn, bool isNumericRoundAbortOn, bool isQuotedIdentifierOn, bool isRecursiveTriggersOn, bool isCursorCloseOnCommitOn, bool isLocalCursorDefault, bool isFulltextEnabled, bool isTrustworthyOn, bool isDbChainingOn, bool isParameterizationForced, bool isMasterKeyEncryptedByServer, bool isQueryStoreOn, bool isPublished, bool isSubscribed, bool isMergePublished, bool isDistributor, bool isSyncWithBackup, Guid serviceBrokerGuid, bool isBrokerEnabled, short logReuseWait, string logReuseWaitDesc, bool isDateCorrelationOn, bool isCdcEnabled, bool isEncrypted, bool isHonorBrokerPriorityOn, Guid? replicaId, Guid? groupDatabaseId, int resourcePoolId, short defaultLanguageLcid, string defaultLanguageName, int? defaultFulltextLanguageLcid, string defaultFulltextLanguageName, bool isNestedTriggersOn, bool isTransformNoiseWordsOn, short twoDigitYearCutoff, byte containment, string containmentDesc, int? targetRecoveryTimeInSeconds, byte delayedDurability, string delayedDurabilityDesc, bool isMemoryOptimizedElevateToSnapshotOn, bool isFederationMember, bool isRemoteDataArchiveEnabled, bool isMixedPageAllocationOn, bool isTemporalHistoryRetentionEnabled, int catalogCollationType, string catalogCollationTypeDesc, string physicalDatabaseName, bool isResultSetCachingOn, bool isAcceleratedDatabaseRecoveryOn, bool isTempdbSpillToRemoteStore, bool isStalePageDetectionOn, bool isMemoryOptimizedEnabled)
        {
            _name = name;
            _databaseId = databaseId;
            _sourceDatabaseId = sourceDatabaseId;
            _ownerSid = ownerSid;
            _createDate = createDate;
            _compatibilityLevel = compatibilityLevel;
            _collationName = collationName;
            _userAccess = userAccess;
            _userAccessDesc = userAccessDesc;
            _isReadOnly = isReadOnly;
            _isAutoCloseOn = isAutoCloseOn;
            _isAutoShrinkOn = isAutoShrinkOn;
            _state = state;
            _stateDesc = stateDesc;
            _isInStandby = isInStandby;
            _isCleanlyShutdown = isCleanlyShutdown;
            _isSupplementalLoggingEnabled = isSupplementalLoggingEnabled;
            _snapshotIsolationState = snapshotIsolationState;
            _snapshotIsolationStateDesc = snapshotIsolationStateDesc;
            _isReadCommittedSnapshotOn = isReadCommittedSnapshotOn;
            _recoveryModel = recoveryModel;
            _recoveryModelDesc = recoveryModelDesc;
            _pageVerifyOption = pageVerifyOption;
            _pageVerifyOptionDesc = pageVerifyOptionDesc;
            _isAutoCreateStatsOn = isAutoCreateStatsOn;
            _isAutoCreateStatsIncrementalOn = isAutoCreateStatsIncrementalOn;
            _isAutoUpdateStatsOn = isAutoUpdateStatsOn;
            _isAutoUpdateStatsAsyncOn = isAutoUpdateStatsAsyncOn;
            _isAnsiNullDefaultOn = isAnsiNullDefaultOn;
            _isAnsiNullsOn = isAnsiNullsOn;
            _isAnsiPaddingOn = isAnsiPaddingOn;
            _isAnsiWarningsOn = isAnsiWarningsOn;
            _isArithAbortOn = isArithAbortOn;
            _isConcatNullYieldsNullOn = isConcatNullYieldsNullOn;
            _isNumericRoundAbortOn = isNumericRoundAbortOn;
            _isQuotedIdentifierOn = isQuotedIdentifierOn;
            _isRecursiveTriggersOn = isRecursiveTriggersOn;
            _isCursorCloseOnCommitOn = isCursorCloseOnCommitOn;
            _isLocalCursorDefault = isLocalCursorDefault;
            _isFulltextEnabled = isFulltextEnabled;
            _isTrustworthyOn = isTrustworthyOn;
            _isDbChainingOn = isDbChainingOn;
            _isParameterizationForced = isParameterizationForced;
            _isMasterKeyEncryptedByServer = isMasterKeyEncryptedByServer;
            _isQueryStoreOn = isQueryStoreOn;
            _isPublished = isPublished;
            _isSubscribed = isSubscribed;
            _isMergePublished = isMergePublished;
            _isDistributor = isDistributor;
            _isSyncWithBackup = isSyncWithBackup;
            _serviceBrokerGuid = serviceBrokerGuid;
            _isBrokerEnabled = isBrokerEnabled;
            _logReuseWait = logReuseWait;
            _logReuseWaitDesc = logReuseWaitDesc;
            _isDateCorrelationOn = isDateCorrelationOn;
            _isCdcEnabled = isCdcEnabled;
            _isEncrypted = isEncrypted;
            _isHonorBrokerPriorityOn = isHonorBrokerPriorityOn;
            _replicaId = replicaId;
            _groupDatabaseId = groupDatabaseId;
            _resourcePoolId = resourcePoolId;
            _defaultLanguageLcid = defaultLanguageLcid;
            _defaultLanguageName = defaultLanguageName;
            _defaultFulltextLanguageLcid = defaultFulltextLanguageLcid;
            _defaultFulltextLanguageName = defaultFulltextLanguageName;
            _isNestedTriggersOn = isNestedTriggersOn;
            _isTransformNoiseWordsOn = isTransformNoiseWordsOn;
            _twoDigitYearCutoff = twoDigitYearCutoff;
            _containment = containment;
            _containmentDesc = containmentDesc;
            _targetRecoveryTimeInSeconds = targetRecoveryTimeInSeconds;
            _delayedDurability = delayedDurability;
            _delayedDurabilityDesc = delayedDurabilityDesc;
            _isMemoryOptimizedElevateToSnapshotOn = isMemoryOptimizedElevateToSnapshotOn;
            _isFederationMember = isFederationMember;
            _isRemoteDataArchiveEnabled = isRemoteDataArchiveEnabled;
            _isMixedPageAllocationOn = isMixedPageAllocationOn;
            _isTemporalHistoryRetentionEnabled = isTemporalHistoryRetentionEnabled;
            _catalogCollationType = catalogCollationType;
            _catalogCollationTypeDesc = catalogCollationTypeDesc;
            _physicalDatabaseName = physicalDatabaseName;
            _isResultSetCachingOn = isResultSetCachingOn;
            _isAcceleratedDatabaseRecoveryOn = isAcceleratedDatabaseRecoveryOn;
            _isTempdbSpillToRemoteStore = isTempdbSpillToRemoteStore;
            _isStalePageDetectionOn = isStalePageDetectionOn;
            _isMemoryOptimizedEnabled = isMemoryOptimizedEnabled;
        }

        public string Name => _name;

        public int DatabaseId => _databaseId;

        public int? SourceDatabaseId => _sourceDatabaseId;

        public byte[] OwnerSid => _ownerSid;

        public DateTime CreateDate => _createDate;

        public byte CompatibilityLevel => _compatibilityLevel;

        public string CollationName => _collationName;

        public DatabaseUserAccess UserAccess => _userAccess;

        public string UserAccessDesc => _userAccessDesc;

        public bool IsReadOnly => _isReadOnly;

        public bool IsAutoCloseOn => _isAutoCloseOn;

        public bool IsAutoShrinkOn => _isAutoShrinkOn;

        public DatabaseState State => _state;

        public string StateDesc => _stateDesc;

        public bool IsInStandby => _isInStandby;

        public bool IsCleanlyShutdown => _isCleanlyShutdown;

        public bool IsSupplementalLoggingEnabled => _isSupplementalLoggingEnabled;

        public byte SnapshotIsolationState => _snapshotIsolationState;

        public string SnapshotIsolationStateDesc => _snapshotIsolationStateDesc;

        public bool IsReadCommittedSnapshotOn => _isReadCommittedSnapshotOn;

        public RecoveryModel RecoveryModel => _recoveryModel;

        public string RecoveryModelDesc => _recoveryModelDesc;

        public PageVerifyOption PageVerifyOption => _pageVerifyOption;

        public string PageVerifyOptionDesc => _pageVerifyOptionDesc;

        public bool IsAutoCreateStatsOn => _isAutoCreateStatsOn;

        public bool IsAutoCreateStatsIncrementalOn => _isAutoCreateStatsIncrementalOn;

        public bool IsAutoUpdateStatsOn => _isAutoUpdateStatsOn;

        public bool IsAutoUpdateStatsAsyncOn => _isAutoUpdateStatsAsyncOn;

        public bool IsAnsiNullDefaultOn => _isAnsiNullDefaultOn;

        public bool IsAnsiNullsOn => _isAnsiNullsOn;

        public bool IsAnsiPaddingOn => _isAnsiPaddingOn;

        public bool IsAnsiWarningsOn => _isAnsiWarningsOn;

        public bool IsArithAbortOn => _isArithAbortOn;

        public bool IsConcatNullYieldsNullOn => _isConcatNullYieldsNullOn;

        public bool IsNumericRoundAbortOn => _isNumericRoundAbortOn;

        public bool IsQuotedIdentifierOn => _isQuotedIdentifierOn;

        public bool IsRecursiveTriggersOn => _isRecursiveTriggersOn;

        public bool IsCursorCloseOnCommitOn => _isCursorCloseOnCommitOn;

        public bool IsLocalCursorDefault => _isLocalCursorDefault;

        public bool IsFulltextEnabled => _isFulltextEnabled;

        public bool IsTrustworthyOn => _isTrustworthyOn;

        public bool IsDbChainingOn => _isDbChainingOn;

        public bool IsParameterizationForced => _isParameterizationForced;

        public bool IsMasterKeyEncryptedByServer => _isMasterKeyEncryptedByServer;

        public bool IsQueryStoreOn => _isQueryStoreOn;

        public bool IsPublished => _isPublished;

        public bool IsSubscribed => _isSubscribed;

        public bool IsMergePublished => _isMergePublished;

        public bool IsDistributor => _isDistributor;

        public bool IsSyncWithBackup => _isSyncWithBackup;

        public Guid ServiceBrokerGuid => _serviceBrokerGuid;

        public bool IsBrokerEnabled => _isBrokerEnabled;

        public short LogReuseWait => _logReuseWait;

        public string LogReuseWaitDesc => _logReuseWaitDesc;

        public bool IsDateCorrelationOn => _isDateCorrelationOn;

        public bool IsCdcEnabled => _isCdcEnabled;

        public bool IsEncrypted => _isEncrypted;

        public bool IsHonorBrokerPriorityOn => _isHonorBrokerPriorityOn;

        public Guid? ReplicaId => _replicaId;

        public Guid? GroupDatabaseId => _groupDatabaseId;

        public int ResourcePoolId => _resourcePoolId;

        public short DefaultLanguageLcid => _defaultLanguageLcid;

        public string DefaultLanguageName => _defaultLanguageName;

        public int? DefaultFulltextLanguageLcid => _defaultFulltextLanguageLcid;

        public string DefaultFulltextLanguageName => _defaultFulltextLanguageName;

        public bool IsNestedTriggersOn => _isNestedTriggersOn;

        public bool IsTransformNoiseWordsOn => _isTransformNoiseWordsOn;

        public short TwoDigitYearCutoff => _twoDigitYearCutoff;

        public byte Containment => _containment;

        public string ContainmentDesc => _containmentDesc;

        public int? TargetRecoveryTimeInSeconds => _targetRecoveryTimeInSeconds;

        public byte DelayedDurability => _delayedDurability;

        public string DelayedDurabilityDesc => _delayedDurabilityDesc;

        public bool IsMemoryOptimizedElevateToSnapshotOn => _isMemoryOptimizedElevateToSnapshotOn;

        public bool IsFederationMember => _isFederationMember;

        public bool IsRemoteDataArchiveEnabled => _isRemoteDataArchiveEnabled;

        public bool IsMixedPageAllocationOn => _isMixedPageAllocationOn;

        public bool IsTemporalHistoryRetentionEnabled => _isTemporalHistoryRetentionEnabled;

        public int CatalogCollationType => _catalogCollationType;

        public string CatalogCollationTypeDesc => _catalogCollationTypeDesc;

        public string PhysicalDatabaseName => _physicalDatabaseName;

        public bool IsResultSetCachingOn => _isResultSetCachingOn;

        public bool IsAcceleratedDatabaseRecoveryOn => _isAcceleratedDatabaseRecoveryOn;

        public bool IsTempdbSpillToRemoteStore => _isTempdbSpillToRemoteStore;

        public bool IsStalePageDetectionOn => _isStalePageDetectionOn;

        public bool IsMemoryOptimizedEnabled => _isMemoryOptimizedEnabled;
    }


}
