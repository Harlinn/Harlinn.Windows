#pragma once
#ifndef COMMONESENTJETRESULT_H__
#define COMMONESENTJETRESULT_H__

#include <HCCDef.h>

#define JET_UNICODE
#define JET_VERSION 0x0A00
#include <esent.h>


namespace Harlinn::Common::Core::Ese
{
enum class Result : JET_ERR
{
    // Successful Operation 
    Success = JET_errSuccess,

    // Function Not Yet Implemented 
    WarningNyi = JET_wrnNyi,

    //	SYSTEM errors
    // Resource Failure Simulator failure 
    ErrorRfsFailure = JET_errRfsFailure,
    // Resource Failure Simulator not initialized 
    ErrorRfsNotArmed = JET_errRfsNotArmed,
    // Could not close file 
    ErrorFileClose = JET_errFileClose,
    // Could not start thread 
    ErrorOutOfThreads = JET_errOutOfThreads,
    // System busy due to too many IOs 
    ErrorTooManyIO = JET_errTooManyIO,
    // A requested async task could not be executed 
    ErrorTaskDropped = JET_errTaskDropped,
    // Fatal internal error 
    ErrorInternalError = JET_errInternalError,

    //	BUFFER MANAGER errors
    // Buffer dependencies improperly set. Recovery failure 
    ErrorDatabaseBufferDependenciesCorrupted = JET_errDatabaseBufferDependenciesCorrupted,

    //	DIRECTORY MANAGER errors

    // The version store is still active 
    WarningRemainingVersions = JET_wrnRemainingVersions,
    // Version already existed. Recovery failure 
    ErrorPreviousVersion = JET_errPreviousVersion,
    // Reached Page Boundary 
    ErrorPageBoundary = JET_errPageBoundary,
    // Reached Key Boundary 
    ErrorKeyBoundary = JET_errKeyBoundary,
    // Database corrupted 
    ErrorBadPageLink = JET_errBadPageLink,
    // Bookmark has no corresponding address in database 
    ErrorBadBookmark = JET_errBadBookmark,
    // A call to the operating system failed
    ErrorNTSystemCallFailed = JET_errNTSystemCallFailed,
    // Database corrupted
    ErrorBadParentPageLink = JET_errBadParentPageLink,
    // AvailExt cache doesn't match btree
    ErrorSPAvailExtCacheOutOfSync = JET_errSPAvailExtCacheOutOfSync,
    // AvailExt space tree is corrupt
    ErrorSPAvailExtCorrupted = JET_errSPAvailExtCorrupted,
    // Out of memory allocating an AvailExt cache node
    ErrorSPAvailExtCacheOutOfMemory = JET_errSPAvailExtCacheOutOfMemory,
    // OwnExt space tree is corrupt
    ErrorSPOwnExtCorrupted = JET_errSPOwnExtCorrupted,
    // Dbtime on current page is greater than global database dbtime
    ErrorDbTimeCorrupted = JET_errDbTimeCorrupted,
    // seek on non-unique index yielded a unique key
    WarningUniqueKey = JET_wrnUniqueKey,
    // key truncated on index that disallows key truncation
    ErrorKeyTruncated = JET_errKeyTruncated,
    // Some database pages have become unreachable even from the avail tree, only an offline defragmentation can return the lost space.
    ErrorDatabaseLeakInSpace = JET_errDatabaseLeakInSpace,
    // Database corrupted. Searching an unexpectedly empty page.
    ErrorBadEmptyPage = JET_errBadEmptyPage,

    // Exact match not found during seek 
    WarningSeekNotEqual = JET_wrnSeekNotEqual,

    //	RECORD MANAGER errors
    // Column is a separated long-value 
    WarningSeparateLongValue = JET_wrnSeparateLongValue,
    WarningRecordFoundGreater = WarningSeekNotEqual,
    WarningRecordFoundLess = WarningSeekNotEqual,
    WarningColumnIllegalNull = JET_errColumnIllegalNull,
    // Key is too large 
    ErrorKeyTooBig = JET_errKeyTooBig,
    // Operation not supported on separated long-value 
    ErrorSeparatedLongValue = JET_errSeparatedLongValue,
    // Can only preread long value columns that can be separate, e.g. not size constrained so that they are fixed or variable columns 
    ErrorMustBeSeparateLongValue = JET_errMustBeSeparateLongValue,
    // Cannot preread long values when current index secondary 
    ErrorInvalidPreread = JET_errInvalidPreread,

    //	LOGGING/RECOVERY errors

    // Logged operation cannot be redone 
    ErrorInvalidLoggedOperation = JET_errInvalidLoggedOperation,
    // Log file is corrupt 
    ErrorLogFileCorrupt = JET_errLogFileCorrupt,
    // No backup directory given 
    ErrorNoBackupDirectory = JET_errNoBackupDirectory,
    // The backup directory is not emtpy 
    ErrorBackupDirectoryNotEmpty = JET_errBackupDirectoryNotEmpty,
    // Backup is active already 
    ErrorBackupInProgress = JET_errBackupInProgress,
    // Restore in progress 
    ErrorRestoreInProgress = JET_errRestoreInProgress,
    // Missing the log file for check point 
    ErrorMissingPreviousLogFile = JET_errMissingPreviousLogFile,
    // Failure writing to log file 
    ErrorLogWriteFail = JET_errLogWriteFail,
    // Try to log something after recovery faild 
    ErrorLogDisabledDueToRecoveryFailure = JET_errLogDisabledDueToRecoveryFailure,
    // Try to log something during recovery redo 
    ErrorCannotLogDuringRecoveryRedo = JET_errCannotLogDuringRecoveryRedo,
    // Name of logfile does not match internal generation number 
    ErrorLogGenerationMismatch = JET_errLogGenerationMismatch,
    // Version of log file is not compatible with Jet version 
    ErrorBadLogVersion = JET_errBadLogVersion,
    // Timestamp in next log does not match expected 
    ErrorInvalidLogSequence = JET_errInvalidLogSequence,
    // Log is not active 
    ErrorLoggingDisabled = JET_errLoggingDisabled,
    // Log buffer is too small for recovery 
    ErrorLogBufferTooSmall = JET_errLogBufferTooSmall,
    // Maximum log file number exceeded 
    ErrorLogSequenceEnd = JET_errLogSequenceEnd,
    // No backup in progress 
    ErrorNoBackup = JET_errNoBackup,
    // Backup call out of sequence 
    ErrorInvalidBackupSequence = JET_errInvalidBackupSequence,
    // Cannot do backup now 
    ErrorBackupNotAllowedYet = JET_errBackupNotAllowedYet,
    // Could not delete backup file 
    ErrorDeleteBackupFileFail = JET_errDeleteBackupFileFail,
    // Could not make backup temp directory 
    ErrorMakeBackupDirectoryFail = JET_errMakeBackupDirectoryFail,
    // Cannot perform incremental backup when circular logging enabled 
    ErrorInvalidBackup = JET_errInvalidBackup,
    // Restored with errors 
    ErrorRecoveredWithErrors = JET_errRecoveredWithErrors,
    // Current log file missing 
    ErrorMissingLogFile = JET_errMissingLogFile,
    // Log disk full 
    ErrorLogDiskFull = JET_errLogDiskFull,
    // Bad signature for a log file 
    ErrorBadLogSignature = JET_errBadLogSignature,
    // Bad signature for a db file 
    ErrorBadDbSignature = JET_errBadDbSignature,
    // Bad signature for a checkpoint file 
    ErrorBadCheckpointSignature = JET_errBadCheckpointSignature,
    // Checkpoint file not found or corrupt
    ErrorCheckpointCorrupt = JET_errCheckpointCorrupt,
    // Patch file page not found during recovery 
    ErrorMissingPatchPage = JET_errMissingPatchPage,
    // Patch file page is not valid 
    ErrorBadPatchPage = JET_errBadPatchPage,
    // Redo abruptly ended due to sudden failure in reading logs from log file 
    ErrorRedoAbruptEnded = JET_errRedoAbruptEnded,
    // Hard restore detected that patch file is missing from backup set 
    ErrorPatchFileMissing = JET_errPatchFileMissing,
    // Database does not belong with the current set of log files 
    ErrorDatabaseLogSetMismatch = JET_errDatabaseLogSetMismatch,
    // Database and streaming file do not match each other 
    ErrorDatabaseStreamingFileMismatch = JET_errDatabaseStreamingFileMismatch,
    // actual log file size does not match JET_paramLogFileSize 
    ErrorLogFileSizeMismatch = JET_errLogFileSizeMismatch,
    // Could not locate checkpoint file 
    ErrorCheckpointFileNotFound = JET_errCheckpointFileNotFound,
    // The required log files for recovery is missing. 
    ErrorRequiredLogFilesMissing = JET_errRequiredLogFilesMissing,
    // Soft recovery is intended on a backup database. Restore should be used instead 
    ErrorSoftRecoveryOnBackupDatabase = JET_errSoftRecoveryOnBackupDatabase,
    // databases have been recovered, but the log file size used during recovery does not match JET_paramLogFileSize 
    ErrorLogFileSizeMismatchDatabasesConsistent = JET_errLogFileSizeMismatchDatabasesConsistent,
    // the log file sector size does not match the current volume's sector size 
    ErrorLogSectorSizeMismatch = JET_errLogSectorSizeMismatch,
    // databases have been recovered, but the log file sector size (used during recovery) does not match the current volume's sector size 
    ErrorLogSectorSizeMismatchDatabasesConsistent = JET_errLogSectorSizeMismatchDatabasesConsistent,
    // databases have been recovered, but all possible log generations in the current sequence are used; delete all log files and the checkpoint file and backup the databases before continuing 
    ErrorLogSequenceEndDatabasesConsistent = JET_errLogSequenceEndDatabasesConsistent,
    // Illegal attempt to replay a streaming file operation where the data wasn't logged. Probably caused by an attempt to roll-forward with circular logging enabled 
    ErrorStreamingDataNotLogged = JET_errStreamingDataNotLogged,

    // Database was not shutdown cleanly. Recovery must first be run to properly complete database operations for the previous shutdown. 
    ErrorDatabaseDirtyShutdown = JET_errDatabaseDirtyShutdown,
    // Database last consistent time unmatched 
    ErrorConsistentTimeMismatch = JET_errConsistentTimeMismatch,
    // Patch file is not generated from this backup 
    ErrorDatabasePatchFileMismatch = JET_errDatabasePatchFileMismatch,
    // The starting log number too low for the restore 
    ErrorEndingRestoreLogTooLow = JET_errEndingRestoreLogTooLow,
    // The starting log number too high for the restore 
    ErrorStartingRestoreLogTooHigh = JET_errStartingRestoreLogTooHigh,
    // Restore log file has bad signature 
    ErrorGivenLogFileHasBadSignature = JET_errGivenLogFileHasBadSignature,
    // Restore log file is not contiguous 
    ErrorGivenLogFileIsNotContiguous = JET_errGivenLogFileIsNotContiguous,
    // Some restore log files are missing 
    ErrorMissingRestoreLogFiles = JET_errMissingRestoreLogFiles,
    // Existing log file has bad signature 
    WarningExistingLogFileHasBadSignature = JET_wrnExistingLogFileHasBadSignature,
    // Existing log file is not contiguous 
    WarningExistingLogFileIsNotContiguous = JET_wrnExistingLogFileIsNotContiguous,
    // The database missed a previous full backup before incremental backup 
    ErrorMissingFullBackup = JET_errMissingFullBackup,
    // The backup database size is not in 4k 
    ErrorBadBackupDatabaseSize = JET_errBadBackupDatabaseSize,
    // Attempted to upgrade a database that is already current 
    ErrorDatabaseAlreadyUpgraded = JET_errDatabaseAlreadyUpgraded,
    // Attempted to use a database which was only partially converted to the current format -- must restore from backup 
    ErrorDatabaseIncompleteUpgrade = JET_errDatabaseIncompleteUpgrade,
    // INTERNAL ERROR 
    WarningSkipThisRecord = JET_wrnSkipThisRecord,
    // Some current log files are missing for continuous restore 
    ErrorMissingCurrentLogFiles = JET_errMissingCurrentLogFiles,

    // dbtime on page smaller than dbtimeBefore in record 
    ErrorDbTimeTooOld = JET_errDbTimeTooOld,
    // dbtime on page in advance of the dbtimeBefore in record 
    ErrorDbTimeTooNew = JET_errDbTimeTooNew,
    // Some log or patch files are missing during backup 
    ErrorMissingFileToBackup = JET_errMissingFileToBackup,

    // torn-write was detected in a backup set during hard restore 
    ErrorLogTornWriteDuringHardRestore = JET_errLogTornWriteDuringHardRestore,
    // torn-write was detected during hard recovery (log was not part of a backup set) 
    ErrorLogTornWriteDuringHardRecovery = JET_errLogTornWriteDuringHardRecovery,
    // corruption was detected in a backup set during hard restore 
    ErrorLogCorruptDuringHardRestore = JET_errLogCorruptDuringHardRestore,
    // corruption was detected during hard recovery (log was not part of a backup set) 
    ErrorLogCorruptDuringHardRecovery = JET_errLogCorruptDuringHardRecovery,
    // Cannot have logging enabled while attempting to upgrade db 
    ErrorMustDisableLoggingForDbUpgrade = JET_errMustDisableLoggingForDbUpgrade,
    // TargetInstance specified for restore is not found or log files don't match 
    ErrorBadRestoreTargetInstance = JET_errBadRestoreTargetInstance,
    // TargetInstance specified for restore is running 
    WarningTargetInstanceRunning = JET_wrnTargetInstanceRunning,
    // Soft recovery successfully replayed all operations, but the Undo phase of recovery was skipped 
    ErrorRecoveredWithoutUndo = JET_errRecoveredWithoutUndo,
    // Databases to be restored are not from the same shadow copy backup 
    ErrorDatabasesNotFromSameSnapshot = JET_errDatabasesNotFromSameSnapshot,
    // Soft recovery on a database from a shadow copy backup set 
    ErrorSoftRecoveryOnSnapshot = JET_errSoftRecoveryOnSnapshot,
    // One or more logs that were committed to this database, are missing.  These log files are required to maintain durable ACID semantics, but not required to maintain consistency if the JET_bitReplayIgnoreLostLogs bit is specified during recovery. 
    ErrorCommittedLogFilesMissing = JET_errCommittedLogFilesMissing,
    // The physical sector size reported by the disk subsystem, is unsupported by ESE for a specific file type. 
    ErrorSectorSizeNotSupported = JET_errSectorSizeNotSupported,
    // Soft recovery successfully replayed all operations and intended to skip the Undo phase of recovery, but the Undo phase was not required 
    ErrorRecoveredWithoutUndoDatabasesConsistent = JET_errRecoveredWithoutUndoDatabasesConsistent,
    // One or more logs that were committed to this database, were not recovered.  The database is still clean/consistent, as though the lost log's transactions were committed lazily (and lost). 
    WarningCommittedLogFilesLost = JET_wrnCommittedLogFilesLost,
    // One or more logs were found to be corrupt during recovery.  These log files are required to maintain durable ACID semantics, but not required to maintain consistency if the JET_bitIgnoreLostLogs bit and JET_paramDeleteOutOfRangeLogs is specified during recovery. 
    ErrorCommittedLogFileCorrupt = JET_errCommittedLogFileCorrupt,
    // One or more logs that were committed to this database, were no recovered.  The database is still clean/consistent, as though the corrupted log's transactions were committed lazily (and lost). 
    WarningCommittedLogFilesRemoved = JET_wrnCommittedLogFilesRemoved,
    // Signal used by clients to indicate JetInit() finished with undo 
    WarningFinishWithUndo = JET_wrnFinishWithUndo,
    // Database corruption has been repaired 
    WarningDatabaseRepaired = JET_wrnDatabaseRepaired,

    // Unicode translation buffer too small 
    ErrorUnicodeTranslationBufferTooSmall = JET_errUnicodeTranslationBufferTooSmall,
    // Unicode normalization failed 
    ErrorUnicodeTranslationFail = JET_errUnicodeTranslationFail,
    // OS does not provide support for Unicode normalisation (and no normalisation callback was specified) 
    ErrorUnicodeNormalizationNotSupported = JET_errUnicodeNormalizationNotSupported,
    // Can not validate the language 
    ErrorUnicodeLanguageValidationFailure = JET_errUnicodeLanguageValidationFailure,
    // Existing log file has bad signature 
    ErrorExistingLogFileHasBadSignature = JET_errExistingLogFileHasBadSignature,
    // Existing log file is not contiguous 
    ErrorExistingLogFileIsNotContiguous = JET_errExistingLogFileIsNotContiguous,
    // Checksum error in log file during backup 
    ErrorLogReadVerifyFailure = JET_errLogReadVerifyFailure,
    //	too many outstanding generations between checkpoint and current generation
    ErrorCheckpointDepthTooDeep = JET_errCheckpointDepthTooDeep,
    //	hard recovery attempted on a database that wasn't a backup database
    ErrorRestoreOfNonBackupDatabase = JET_errRestoreOfNonBackupDatabase,
    //	log truncation attempted but not all required logs were copied
    ErrorLogFileNotCopied = JET_errLogFileNotCopied,
    // Invalid flags parameter 
    ErrorInvalidGrbit = JET_errInvalidGrbit,

    // Termination in progress 
    ErrorTermInProgress = JET_errTermInProgress,
    // API not supported 
    ErrorFeatureNotAvailable = JET_errFeatureNotAvailable,
    // Invalid name 
    ErrorInvalidName = JET_errInvalidName,
    // Invalid API parameter 
    ErrorInvalidParameter = JET_errInvalidParameter,
    // Column is NULL-valued 
    WarningColumnNull = JET_wrnColumnNull,
    // Buffer too small for data 
    WarningBufferTruncated = JET_wrnBufferTruncated,
    // Database is already attached 
    WarningDatabaseAttached = JET_wrnDatabaseAttached,
    // Tried to attach a read-only database file for read/write operations 
    ErrorDatabaseFileReadOnly = JET_errDatabaseFileReadOnly,
    // Sort does not fit in memory 
    WarningSortOverflow = JET_wrnSortOverflow,
    // Invalid database id 
    ErrorInvalidDatabaseId = JET_errInvalidDatabaseId,
    // Out of Memory 
    ErrorOutOfMemory = JET_errOutOfMemory,
    // Maximum database size reached 
    ErrorOutOfDatabaseSpace = JET_errOutOfDatabaseSpace,
    // Out of table cursors 
    ErrorOutOfCursors = JET_errOutOfCursors,
    // Out of database page buffers 
    ErrorOutOfBuffers = JET_errOutOfBuffers,
    // Too many indexes 
    ErrorTooManyIndexes = JET_errTooManyIndexes,
    // Too many columns in an index 
    ErrorTooManyKeys = JET_errTooManyKeys,
    // Record has been deleted 
    ErrorRecordDeleted = JET_errRecordDeleted,
    // Checksum error on a database page 
    ErrorReadVerifyFailure = JET_errReadVerifyFailure,
    // Blank database page 
    ErrorPageNotInitialized = JET_errPageNotInitialized,
    // Out of file handles 
    ErrorOutOfFileHandles = JET_errOutOfFileHandles,
    // The OS returned ERROR_CRC from file IO 
    ErrorDiskReadVerificationFailure = JET_errDiskReadVerificationFailure,
    // Disk IO error 
    ErrorDiskIO = JET_errDiskIO,
    // Invalid file path 
    ErrorInvalidPath = JET_errInvalidPath,
    // Invalid system path 
    ErrorInvalidSystemPath = JET_errInvalidSystemPath,
    // Invalid log directory 
    ErrorInvalidLogDirectory = JET_errInvalidLogDirectory,
    // Record larger than maximum size 
    ErrorRecordTooBig = JET_errRecordTooBig,
    // Too many open databases 
    ErrorTooManyOpenDatabases = JET_errTooManyOpenDatabases,
    // Not a database file 
    ErrorInvalidDatabase = JET_errInvalidDatabase,
    // Database engine not initialized 
    ErrorNotInitialized = JET_errNotInitialized,
    // Database engine already initialized 
    ErrorAlreadyInitialized = JET_errAlreadyInitialized,
    // Database engine is being initialized 
    ErrorInitInProgress = JET_errInitInProgress,
    // Cannot access file, the file is locked or in use 
    ErrorFileAccessDenied = JET_errFileAccessDenied,
    // Buffer is too small 
    ErrorBufferTooSmall = JET_errBufferTooSmall,
    // Too many columns defined 
    ErrorTooManyColumns = JET_errTooManyColumns,
    // Container is not empty 
    ErrorContainerNotEmpty = JET_errContainerNotEmpty,
    // Filename is invalid 
    ErrorInvalidFilename = JET_errInvalidFilename,
    // Invalid bookmark 
    ErrorInvalidBookmark = JET_errInvalidBookmark,
    // Column used in an index 
    ErrorColumnInUse = JET_errColumnInUse,
    // Data buffer doesn't match column size 
    ErrorInvalidBufferSize = JET_errInvalidBufferSize,
    // Cannot set column value 
    ErrorColumnNotUpdatable = JET_errColumnNotUpdatable,
    // Index is in use 
    ErrorIndexInUse = JET_errIndexInUse,
    // Link support unavailable 
    ErrorLinkNotSupported = JET_errLinkNotSupported,
    // Null keys are disallowed on index 
    ErrorNullKeyDisallowed = JET_errNullKeyDisallowed,
    // Operation must be within a transaction 
    ErrorNotInTransaction = JET_errNotInTransaction,
    // No extended error information 
    WarningNoErrorInfo = JET_wrnNoErrorInfo,
    // Transaction must rollback because failure of unversioned update 
    ErrorMustRollback = JET_errMustRollback,
    // No idle activity occured 
    WarningNoIdleActivity = JET_wrnNoIdleActivity,
    // Too many active database users 
    ErrorTooManyActiveUsers = JET_errTooManyActiveUsers,
    // Invalid or unknown country/region code 
    ErrorInvalidCountry = JET_errInvalidCountry,
    // Invalid or unknown language id 
    ErrorInvalidLanguageId = JET_errInvalidLanguageId,
    // Invalid or unknown code page 
    ErrorInvalidCodePage = JET_errInvalidCodePage,
    // Invalid flags for LCMapString() 
    ErrorInvalidLCMapStringFlags = JET_errInvalidLCMapStringFlags,
    // Attempted to create a version store entry (RCE) larger than a version bucket 
    ErrorVersionStoreEntryTooBig = JET_errVersionStoreEntryTooBig,
    // Version store out of memory (and cleanup attempt failed to complete) 
    ErrorVersionStoreOutOfMemoryAndCleanupTimedOut = JET_errVersionStoreOutOfMemoryAndCleanupTimedOut,
    // No write lock at transaction level 0 
    WarningNoWriteLock = JET_wrnNoWriteLock,
    // Column set to NULL-value 
    WarningColumnSetNull = JET_wrnColumnSetNull,
    // Version store out of memory (cleanup already attempted) 
    ErrorVersionStoreOutOfMemory = JET_errVersionStoreOutOfMemory,
    // Cannot index escrow column 
    ErrorCannotIndex = JET_errCannotIndex,
    // Record has not been deleted 
    ErrorRecordNotDeleted = JET_errRecordNotDeleted,
    // Too many mempool entries requested 
    ErrorTooManyMempoolEntries = JET_errTooManyMempoolEntries,
    // Out of btree ObjectIDs (perform offline defrag to reclaim freed/unused ObjectIds) 
    ErrorOutOfObjectIDs = JET_errOutOfObjectIDs,
    // Long-value ID counter has reached maximum value. (perform offline defrag to reclaim free/unused LongValueIDs) 
    ErrorOutOfLongValueIDs = JET_errOutOfLongValueIDs,
    // Auto-increment counter has reached maximum value (offline defrag WILL NOT be able to reclaim free/unused Auto-increment values). 
    ErrorOutOfAutoincrementValues = JET_errOutOfAutoincrementValues,
    // Dbtime counter has reached maximum value (perform offline defrag to reclaim free/unused Dbtime values) 
    ErrorOutOfDbtimeValues = JET_errOutOfDbtimeValues,
    // Sequential index counter has reached maximum value (perform offline defrag to reclaim free/unused SequentialIndex values) 
    ErrorOutOfSequentialIndexValues = JET_errOutOfSequentialIndexValues,

    // Multi-instance call with single-instance mode enabled 
    ErrorRunningInOneInstanceMode = JET_errRunningInOneInstanceMode,
    // Single-instance call with multi-instance mode enabled 
    ErrorRunningInMultiInstanceMode = JET_errRunningInMultiInstanceMode,
    // Global system parameters have already been set 
    ErrorSystemParamsAlreadySet = JET_errSystemParamsAlreadySet,

    // System path already used by another database instance 
    ErrorSystemPathInUse = JET_errSystemPathInUse,
    // Logfile path already used by another database instance 
    ErrorLogFilePathInUse = JET_errLogFilePathInUse,
    // Temp path already used by another database instance 
    ErrorTempPathInUse = JET_errTempPathInUse,
    // Instance Name already in use 
    ErrorInstanceNameInUse = JET_errInstanceNameInUse,

    // This instance cannot be used because it encountered a fatal error 
    ErrorInstanceUnavailable = JET_errInstanceUnavailable,
    // This database cannot be used because it encountered a fatal error 
    ErrorDatabaseUnavailable = JET_errDatabaseUnavailable,
    // This instance cannot be used because it encountered a log-disk-full error performing an operation (likely transaction rollback) that could not tolerate failure 
    ErrorInstanceUnavailableDueToFatalLogDiskFull = JET_errInstanceUnavailableDueToFatalLogDiskFull,

    // Out of sessions 
    ErrorOutOfSessions = JET_errOutOfSessions,
    // Write lock failed due to outstanding write lock 
    ErrorWriteConflict = JET_errWriteConflict,
    // Transactions nested too deeply 
    ErrorTransTooDeep = JET_errTransTooDeep,
    // Invalid session handle 
    ErrorInvalidSesid = JET_errInvalidSesid,
    // Update attempted on uncommitted primary index 
    ErrorWriteConflictPrimaryIndex = JET_errWriteConflictPrimaryIndex,
    // Operation not allowed within a transaction 
    ErrorInTransaction = JET_errInTransaction,
    // Must rollback current transaction -- cannot commit or begin a new one 
    ErrorRollbackRequired = JET_errRollbackRequired,
    // Read-only transaction tried to modify the database 
    ErrorTransReadOnly = JET_errTransReadOnly,
    // Attempt to replace the same record by two diffrerent cursors in the same session 
    ErrorSessionWriteConflict = JET_errSessionWriteConflict,
    // record would be too big if represented in a database format from a previous version of Jet 
    ErrorRecordTooBigForBackwardCompatibility = JET_errRecordTooBigForBackwardCompatibility,
    // The temp table could not be created due to parameters that conflict with JET_bitTTForwardOnly 
    ErrorCannotMaterializeForwardOnlySort = JET_errCannotMaterializeForwardOnlySort,

    // This session handle can't be used with this table id 
    ErrorSesidTableIdMismatch = JET_errSesidTableIdMismatch,
    // Invalid instance handle 
    ErrorInvalidInstance = JET_errInvalidInstance,
    // The instance was shutdown successfully but all the attached databases were left in a dirty state by request via JET_bitTermDirty 
    ErrorDirtyShutdown = JET_errDirtyShutdown,

    // The database page read from disk had the wrong page number. 
    ErrorReadPgnoVerifyFailure = JET_errReadPgnoVerifyFailure,
    // The database page read from disk had a previous write not represented on the page. 
    ErrorReadLostFlushVerifyFailure = JET_errReadLostFlushVerifyFailure,
    // File system operation failed with an error indicating the file system is corrupt. 
    ErrorFileSystemCorruption = JET_errFileSystemCorruption,
    // Database file could not be shrunk because there is not enough internal free space available or there is unmovable data present. 
    WarningShrinkNotPossible = JET_wrnShrinkNotPossible,
    // One or more database pages read from disk during recovery do not match the expected state. 
    ErrorRecoveryVerifyFailure = JET_errRecoveryVerifyFailure,
    // Attempted to provide a filter to JetSetCursorFilter() in an unsupported scenario. 
    ErrorFilteredMoveNotSupported = JET_errFilteredMoveNotSupported,

    // Database already exists 
    ErrorDatabaseDuplicate = JET_errDatabaseDuplicate,
    // Database in use 
    ErrorDatabaseInUse = JET_errDatabaseInUse,
    // No such database 
    ErrorDatabaseNotFound = JET_errDatabaseNotFound,
    // Invalid database name 
    ErrorDatabaseInvalidName = JET_errDatabaseInvalidName,
    // Invalid number of pages 
    ErrorDatabaseInvalidPages = JET_errDatabaseInvalidPages,
    // Non database file or corrupted db 
    ErrorDatabaseCorrupted = JET_errDatabaseCorrupted,
    // Database exclusively locked 
    ErrorDatabaseLocked = JET_errDatabaseLocked,
    // Cannot disable versioning for this database 
    ErrorCannotDisableVersioning = JET_errCannotDisableVersioning,
    // Database engine is incompatible with database 
    ErrorInvalidDatabaseVersion = JET_errInvalidDatabaseVersion,

    //	The following error code are for NT clients only. It will return such error during
    //	JetInit if JET_paramCheckFormatWhenOpenFail is set.

    // The database is in an older (200) format 
    ErrorDatabase200Format = JET_errDatabase200Format,
    // The database is in an older (400) format 
    ErrorDatabase400Format = JET_errDatabase400Format,
    // The database is in an older (500) format 
    ErrorDatabase500Format = JET_errDatabase500Format,

    // The database page size does not match the engine 
    ErrorPageSizeMismatch = JET_errPageSizeMismatch,
    // Cannot start any more database instances 
    ErrorTooManyInstances = JET_errTooManyInstances,
    // A different database instance is using this database 
    ErrorDatabaseSharingViolation = JET_errDatabaseSharingViolation,
    // An outstanding database attachment has been detected at the start or end of recovery, but database is missing or does not match attachment info 
    ErrorAttachedDatabaseMismatch = JET_errAttachedDatabaseMismatch,
    // Specified path to database file is illegal 
    ErrorDatabaseInvalidPath = JET_errDatabaseInvalidPath,
    // A database is being assigned an id already in use 
    ErrorDatabaseIdInUse = JET_errDatabaseIdInUse,
    // Force Detach allowed only after normal detach errored out 
    ErrorForceDetachNotAllowed = JET_errForceDetachNotAllowed,
    // Corruption detected in catalog 
    ErrorCatalogCorrupted = JET_errCatalogCorrupted,
    // Database is partially attached. Cannot complete attach operation 
    ErrorPartiallyAttachedDB = JET_errPartiallyAttachedDB,
    // Database with same signature in use 
    ErrorDatabaseSignInUse = JET_errDatabaseSignInUse,
    // Corrupted db but repair not allowed 
    ErrorDatabaseCorruptedNoRepair = JET_errDatabaseCorruptedNoRepair,
    // recovery tried to replay a database creation, but the database was originally created with an incompatible (likely older) version of the database engine 
    ErrorInvalidCreateDbVersion = JET_errInvalidCreateDbVersion,


    // Opened an empty table 
    WarningTableEmpty = JET_wrnTableEmpty,
    // Table is exclusively locked 
    ErrorTableLocked = JET_errTableLocked,
    // Table already exists 
    ErrorTableDuplicate = JET_errTableDuplicate,
    // Table is in use, cannot lock 
    ErrorTableInUse = JET_errTableInUse,
    // No such table or object 
    ErrorObjectNotFound = JET_errObjectNotFound,
    // Bad file/index density 
    ErrorDensityInvalid = JET_errDensityInvalid,
    // Table is not empty 
    ErrorTableNotEmpty = JET_errTableNotEmpty,
    // Invalid table id 
    ErrorInvalidTableId = JET_errInvalidTableId,
    // Cannot open any more tables (cleanup already attempted) 
    ErrorTooManyOpenTables = JET_errTooManyOpenTables,
    // Oper. not supported on table 
    ErrorIllegalOperation = JET_errIllegalOperation,
    // Cannot open any more tables (cleanup attempt failed to complete) 
    ErrorTooManyOpenTablesAndCleanupTimedOut = JET_errTooManyOpenTablesAndCleanupTimedOut,
    // Table or object name in use 
    ErrorObjectDuplicate = JET_errObjectDuplicate,
    // Object is invalid for operation 
    ErrorInvalidObject = JET_errInvalidObject,
    // Use CloseTable instead of DeleteTable to delete temp table 
    ErrorCannotDeleteTempTable = JET_errCannotDeleteTempTable,
    // Illegal attempt to delete a system table 
    ErrorCannotDeleteSystemTable = JET_errCannotDeleteSystemTable,
    // Illegal attempt to delete a template table 
    ErrorCannotDeleteTemplateTable = JET_errCannotDeleteTemplateTable,
    // Must have exclusive lock on table.
    ErrorExclusiveTableLockRequired = JET_errExclusiveTableLockRequired,
    // DDL operations prohibited on this table 
    ErrorFixedDDL = JET_errFixedDDL,
    // On a derived table, DDL operations are prohibited on inherited portion of DDL
    ErrorFixedInheritedDDL = JET_errFixedInheritedDDL,
    // Nesting of hierarchical DDL is not currently supported. 
    ErrorCannotNestDDL = JET_errCannotNestDDL,
    // Tried to inherit DDL from a table not marked as a template table. 
    ErrorDDLNotInheritable = JET_errDDLNotInheritable,
    // System cleanup has a cursor open on the table 
    WarningTableInUseBySystem = JET_wrnTableInUseBySystem,
    // System parameters were set improperly 
    ErrorInvalidSettings = JET_errInvalidSettings,
    // Client has requested stop service 
    ErrorClientRequestToStopJetService = JET_errClientRequestToStopJetService,
    // Template table was created with NoFixedVarColumnsInDerivedTables 
    ErrorCannotAddFixedVarColumnToDerivedTable = JET_errCannotAddFixedVarColumnToDerivedTable,

    //	DDL errors

    // Note: Some DDL errors have snuck into other categories.
    // Index build failed 
    ErrorIndexCantBuild = JET_errIndexCantBuild,
    // Primary index already defined 
    ErrorIndexHasPrimary = JET_errIndexHasPrimary,
    // Index is already defined 
    ErrorIndexDuplicate = JET_errIndexDuplicate,
    // No such index
    ErrorIndexNotFound = JET_errIndexNotFound,
    // Cannot delete clustered index 
    ErrorIndexMustStay = JET_errIndexMustStay,
    // Illegal index definition 
    ErrorIndexInvalidDef = JET_errIndexInvalidDef,
    // Invalid create index description 
    ErrorInvalidCreateIndex = JET_errInvalidCreateIndex,
    // Out of index description blocks 
    ErrorTooManyOpenIndexes = JET_errTooManyOpenIndexes,
    // Non-unique inter-record index keys generated for a multivalued index 
    ErrorMultiValuedIndexViolation = JET_errMultiValuedIndexViolation,
    // Failed to build a secondary index that properly reflects primary index 
    ErrorIndexBuildCorrupted = JET_errIndexBuildCorrupted,
    // Primary index is corrupt. The database must be defragmented or the table deleted. 
    ErrorPrimaryIndexCorrupted = JET_errPrimaryIndexCorrupted,
    // Secondary index is corrupt. The database must be defragmented or the affected index must be deleted. If the corrupt index is over Unicode text, a likely cause a sort-order change. 
    ErrorSecondaryIndexCorrupted = JET_errSecondaryIndexCorrupted,
    // Out of date index removed 
    WarningCorruptIndexDeleted = JET_wrnCorruptIndexDeleted,
    // Illegal index id 
    ErrorInvalidIndexId = JET_errInvalidIndexId,
    // The Primary index is created with an incompatible OS sort version. The table can not be safely modified. 
    WarningPrimaryIndexOutOfDate = JET_wrnPrimaryIndexOutOfDate,
    // One or more Secondary index is created with an incompatible OS sort version. Any index over Unicode text should be deleted. 
    WarningSecondaryIndexOutOfDate = JET_wrnSecondaryIndexOutOfDate,

    //	tuple index can only be on a secondary index
    ErrorIndexTuplesSecondaryIndexOnly = JET_errIndexTuplesSecondaryIndexOnly,
    //	tuple index may only have eleven columns in the index
    ErrorIndexTuplesTooManyColumns = JET_errIndexTuplesTooManyColumns,
    WarningIndexTuplesOneColumnOnly = JET_errIndexTuplesOneColumnOnly,
    //	tuple index must be a non-unique index
    ErrorIndexTuplesNonUniqueOnly = JET_errIndexTuplesNonUniqueOnly,
    //	tuple index must be on a text/binary column
    ErrorIndexTuplesTextBinaryColumnsOnly = JET_errIndexTuplesTextBinaryColumnsOnly,
    WarningIndexTuplesTextColumnsOnly = JET_errIndexTuplesTextColumnsOnly,
    //	tuple index does not allow setting cbVarSegMac
    ErrorIndexTuplesVarSegMacNotAllowed = JET_errIndexTuplesVarSegMacNotAllowed,
    //	invalid min/max tuple length or max characters to index specified
    ErrorIndexTuplesInvalidLimits = JET_errIndexTuplesInvalidLimits,
    //	cannot call RetrieveColumn() with RetrieveFromIndex on a tuple index
    ErrorIndexTuplesCannotRetrieveFromIndex = JET_errIndexTuplesCannotRetrieveFromIndex,
    //	specified key does not meet minimum tuple length
    ErrorIndexTuplesKeyTooSmall = JET_errIndexTuplesKeyTooSmall,

    //	DML errors

    // Note: Some DML errors have snuck into other categories.
    // Note: Some DDL errors have inappropriately snuck in here.

    // Column value is long 
    ErrorColumnLong = JET_errColumnLong,
    // No such chunk in long value 
    ErrorColumnNoChunk = JET_errColumnNoChunk,
    // Field will not fit in record 
    ErrorColumnDoesNotFit = JET_errColumnDoesNotFit,
    // Null not valid 
    ErrorNullInvalid = JET_errNullInvalid,
    // Column indexed, cannot delete 
    ErrorColumnIndexed = JET_errColumnIndexed,
    // Field length is greater than maximum 
    ErrorColumnTooBig = JET_errColumnTooBig,
    // No such column 
    ErrorColumnNotFound = JET_errColumnNotFound,
    // Field is already defined 
    ErrorColumnDuplicate = JET_errColumnDuplicate,
    // Attempted to create a multi-valued column, but column was not Tagged 
    ErrorMultiValuedColumnMustBeTagged = JET_errMultiValuedColumnMustBeTagged,
    // Second autoincrement or version column 
    ErrorColumnRedundant = JET_errColumnRedundant,
    // Invalid column data type 
    ErrorInvalidColumnType = JET_errInvalidColumnType,
    // Max length too big, truncated 
    WarningColumnMaxTruncated = JET_wrnColumnMaxTruncated,
    // No non-NULL tagged columns 
    ErrorTaggedNotNULL = JET_errTaggedNotNULL,
    // Invalid w/o a current index 
    ErrorNoCurrentIndex = JET_errNoCurrentIndex,
    // The key is completely made 
    ErrorKeyIsMade = JET_errKeyIsMade,
    // Column Id Incorrect 
    ErrorBadColumnId = JET_errBadColumnId,
    // Bad itagSequence for tagged column 
    ErrorBadItagSequence = JET_errBadItagSequence,
    // Cannot delete, column participates in relationship 
    ErrorColumnInRelationship = JET_errColumnInRelationship,
    // Single instance column bursted 
    WarningCopyLongValue = JET_wrnCopyLongValue,
    // AutoIncrement and Version cannot be tagged 
    ErrorCannotBeTagged = JET_errCannotBeTagged,
    // Default value exceeds maximum size 
    ErrorDefaultValueTooBig = JET_errDefaultValueTooBig,
    // Duplicate detected on a unique multi-valued column 
    ErrorMultiValuedDuplicate = JET_errMultiValuedDuplicate,
    // Corruption encountered in long-value tree 
    ErrorLVCorrupted = JET_errLVCorrupted,
    // Duplicate detected on a unique multi-valued column after data was normalized, and normalizing truncated the data before comparison 
    ErrorMultiValuedDuplicateAfterTruncation = JET_errMultiValuedDuplicateAfterTruncation,
    // Invalid column in derived table 
    ErrorDerivedColumnCorruption = JET_errDerivedColumnCorruption,
    // Tried to convert column to a primary index placeholder, but column doesn't meet necessary criteria 
    ErrorInvalidPlaceholderColumn = JET_errInvalidPlaceholderColumn,
    // Column value(s) not returned because the corresponding column id or itagSequence requested for enumeration was null 
    WarningColumnSkipped = JET_wrnColumnSkipped,
    // Column value(s) not returned because they could not be reconstructed from the data at hand 
    WarningColumnNotLocal = JET_wrnColumnNotLocal,
    // Column values exist that were not requested for enumeration 
    WarningColumnMoreTags = JET_wrnColumnMoreTags,
    // Column value truncated at the requested size limit during enumeration 
    WarningColumnTruncated = JET_wrnColumnTruncated,
    // Column values exist but were not returned by request 
    WarningColumnPresent = JET_wrnColumnPresent,
    // Column value returned in JET_COLUMNENUM as a result of JET_bitEnumerateCompressOutput 
    WarningColumnSingleValue = JET_wrnColumnSingleValue,
    // Column value(s) not returned because they were set to their default value(s) and JET_bitEnumerateIgnoreDefault was specified 
    WarningColumnDefault = JET_wrnColumnDefault,
    // Only JET_coltypLongText and JET_coltypLongBinary columns can be compressed 
    ErrorColumnCannotBeCompressed = JET_errColumnCannotBeCompressed,
    // Column value(s) not returned because they could not be reconstructed from the data in the record 
    WarningColumnNotInRecord = JET_wrnColumnNotInRecord,
    // The key was not found 
    ErrorRecordNotFound = JET_errRecordNotFound,
    // No working buffer 
    ErrorRecordNoCopy = JET_errRecordNoCopy,
    // Currency not on a record 
    ErrorNoCurrentRecord = JET_errNoCurrentRecord,
    // Primary key may not change 
    ErrorRecordPrimaryChanged = JET_errRecordPrimaryChanged,
    // Illegal duplicate key 
    ErrorKeyDuplicate = JET_errKeyDuplicate,
    // Attempted to update record when record update was already in progress 
    ErrorAlreadyPrepared = JET_errAlreadyPrepared,
    // No call to JetMakeKey 
    ErrorKeyNotMade = JET_errKeyNotMade,
    // No call to JetPrepareUpdate 
    ErrorUpdateNotPrepared = JET_errUpdateNotPrepared,
    // Data has changed 
    WarningDataHasChanged = JET_wrnDataHasChanged,
    // Data has changed, operation aborted 
    ErrorDataHasChanged = JET_errDataHasChanged,
    // Moved to new key 
    WarningKeyChanged = JET_wrnKeyChanged,
    // Windows installation does not support language 
    ErrorLanguageNotSupported = JET_errLanguageNotSupported,
    // Internal error: data could not be decompressed 
    ErrorDecompressionFailed = JET_errDecompressionFailed,
    // No version updates only for uncommitted tables 
    ErrorUpdateMustVersion = JET_errUpdateMustVersion,

    //	Sort Table errors

    // Too many sort processes 
    ErrorTooManySorts = JET_errTooManySorts,
    // Invalid operation on Sort 
    ErrorInvalidOnSort = JET_errInvalidOnSort,

    //	Other errors

    // Temp file could not be opened 
    ErrorTempFileOpenError = JET_errTempFileOpenError,
    // Too many open databases 
    ErrorTooManyAttachedDatabases = JET_errTooManyAttachedDatabases,
    // No space left on disk 
    ErrorDiskFull = JET_errDiskFull,
    // Permission denied 
    ErrorPermissionDenied = JET_errPermissionDenied,
    // File not found 
    ErrorFileNotFound = JET_errFileNotFound,
    // Invalid file type 
    ErrorFileInvalidType = JET_errFileInvalidType,
    // Database file is read only 
    WarningFileOpenReadOnly = JET_wrnFileOpenReadOnly,


    // Cannot Restore after init.
    ErrorAfterInitialization = JET_errAfterInitialization,
    // Logs could not be interpreted 
    ErrorLogCorrupted = JET_errLogCorrupted,

    // Invalid operation 
    ErrorInvalidOperation = JET_errInvalidOperation,
    // Access denied 
    ErrorAccessDenied = JET_errAccessDenied,
    // Idle registry full 
    WarningIdleFull = JET_wrnIdleFull,
    // Infinite split 
    ErrorTooManySplits = JET_errTooManySplits,
    // Multiple threads are using the same session 
    ErrorSessionSharingViolation = JET_errSessionSharingViolation,
    // An entry point in a DLL we require could not be found 
    ErrorEntryPointNotFound = JET_errEntryPointNotFound,
    // Specified session already has a session context set 
    ErrorSessionContextAlreadySet = JET_errSessionContextAlreadySet,
    // Tried to reset session context, but current thread did not orignally set the session context 
    ErrorSessionContextNotSetByThisThread = JET_errSessionContextNotSetByThisThread,
    // Tried to terminate session in use 
    ErrorSessionInUse = JET_errSessionInUse,
    // Internal error during dynamic record format conversion 
    ErrorRecordFormatConversionFailed = JET_errRecordFormatConversionFailed,
    // Just one open user database per session is allowed (JET_paramOneDatabasePerSession) 
    ErrorOneDatabasePerSession = JET_errOneDatabasePerSession,
    // error during rollback 
    ErrorRollbackError = JET_errRollbackError,


    // Online defrag already running on specified database 
    WarningDefragAlreadyRunning = JET_wrnDefragAlreadyRunning,
    // Online defrag not running on specified database 
    WarningDefragNotRunning = JET_wrnDefragNotRunning,
    // The operation did not complete successfully because the database is already running maintenance on specified database 
    ErrorDatabaseAlreadyRunningMaintenance = JET_errDatabaseAlreadyRunningMaintenance,

    // Unregistered a non-existant callback function 
    WarningCallbackNotRegistered = JET_wrnCallbackNotRegistered,
    // A callback failed 
    ErrorCallbackFailed = JET_errCallbackFailed,
    // A callback function could not be found 
    ErrorCallbackNotResolved = JET_errCallbackNotResolved,

    // An element of the JET space hints structure was not correct or actionable. 
    ErrorSpaceHintsInvalid = JET_errSpaceHintsInvalid,

    // OS Shadow copy API used in an invalid sequence 
    ErrorOSSnapshotInvalidSequence = JET_errOSSnapshotInvalidSequence,
    // OS Shadow copy ended with time-out 
    ErrorOSSnapshotTimeOut = JET_errOSSnapshotTimeOut,
    // OS Shadow copy not allowed (backup or recovery in progress) 
    ErrorOSSnapshotNotAllowed = JET_errOSSnapshotNotAllowed,
    // invalid JET_OSSNAPID 
    ErrorOSSnapshotInvalidSnapId = JET_errOSSnapshotInvalidSnapId,

    // Attempted to use Local Storage without a callback function being specified 
    ErrorLSCallbackNotSpecified = JET_errLSCallbackNotSpecified,
    // Attempted to set Local Storage for an object which already had it set 
    ErrorLSAlreadySet = JET_errLSAlreadySet,
    // Attempted to retrieve Local Storage from an object which didn't have it set 
    ErrorLSNotSet = JET_errLSNotSet,

    // FILE and DISK ERRORS

    // an I/O was issued to a location that was sparse 
    ErrorFileIOSparse = JET_errFileIOSparse,
    // a read was issued to a location beyond EOF (writes will expand the file) 
    ErrorFileIOBeyondEOF = JET_errFileIOBeyondEOF,
    // instructs the JET_ABORTRETRYFAILCALLBACK caller to abort the specified I/O 
    ErrorFileIOAbort = JET_errFileIOAbort,
    // instructs the JET_ABORTRETRYFAILCALLBACK caller to retry the specified I/O 
    ErrorFileIORetry = JET_errFileIORetry,
    // instructs the JET_ABORTRETRYFAILCALLBACK caller to fail the specified I/O 
    ErrorFileIOFail = JET_errFileIOFail,
    // read/write access is not supported on compressed files 
    ErrorFileCompressed = JET_errFileCompressed

};

}

#endif