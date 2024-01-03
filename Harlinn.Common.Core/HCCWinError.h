#pragma once
#ifndef HARLINN_COMMON_CORE_HCCWINERROR_H_
#define HARLINN_COMMON_CORE_HCCWINERROR_H_
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

#ifndef _WINERROR_
#include <winerror.h>
#endif

#ifndef STATUS_CANCELLED
#define STATUS_CANCELLED                 ((long)0xC0000120L)
#endif

#ifndef STATUS_LOCAL_DISCONNECT
#define STATUS_LOCAL_DISCONNECT          ((long)0xC000013BL)
#endif

#ifndef STATUS_REMOTE_DISCONNECT
#define STATUS_REMOTE_DISCONNECT         ((long)0xC000013CL)
#endif


namespace Harlinn::Common::Core
{
    enum class WinError : unsigned int
    {
        None = 0,
        Success = 0,
        NoError = 0,
        /// <summary>
        /// Incorrect function.
        /// </summary>
        InvalidFunction = ERROR_INVALID_FUNCTION,
        /// <summary>
        /// The system cannot find the file specified.
        /// </summary>
        FileNotFound = ERROR_FILE_NOT_FOUND,

        /// <summary>
        /// The system cannot find the path specified.
        /// </summary>
        PathNotFound = ERROR_PATH_NOT_FOUND,

        /// <summary>
        /// The system cannot open the file.
        /// </summary>
        TooManyOpenFiles = ERROR_TOO_MANY_OPEN_FILES,

        /// <summary>
        /// Access is denied.
        /// </summary>
        AccessDenied = ERROR_ACCESS_DENIED,

        /// <summary>
        /// The handle is invalid.
        /// </summary>
        InvalidHandle = ERROR_INVALID_HANDLE,

        /// <summary>
        /// The storage control blocks were destroyed.
        /// </summary>
        ArenaTrashed = ERROR_ARENA_TRASHED,

        /// <summary>
        /// Not enough memory resources are available to process this command.
        /// </summary>
        NotEnoughMemory = ERROR_NOT_ENOUGH_MEMORY,

        /// <summary>
        /// The storage control block address is invalid.
        /// </summary>
        InvalidBlock = ERROR_INVALID_BLOCK,

        /// <summary>
        /// The environment is incorrect.
        /// </summary>
        BadEnvironment = ERROR_BAD_ENVIRONMENT,

        /// <summary>
        /// An attempt was made to load a program with an incorrect format.
        /// </summary>
        BadFormat = ERROR_BAD_FORMAT,

        /// <summary>
        /// The access code is invalid.
        /// </summary>
        InvalidAccess = ERROR_INVALID_ACCESS,

        /// <summary>
        /// The data is invalid.
        /// </summary>
        InvalidData = ERROR_INVALID_DATA,

        /// <summary>
        /// Not enough memory resources are available to complete this operation.
        /// </summary>
        OutOfMemory = ERROR_OUTOFMEMORY,

        /// <summary>
        /// The system cannot find the drive specified.
        /// </summary>
        InvalidDrive = ERROR_INVALID_DRIVE,

        /// <summary>
        /// The directory cannot be removed.
        /// </summary>
        CurrentDirectory = ERROR_CURRENT_DIRECTORY,

        /// <summary>
        /// The system cannot move the file to a different disk drive.
        /// </summary>
        NotSameDevice = ERROR_NOT_SAME_DEVICE,

        /// <summary>
        /// There are no more files.
        /// </summary>
        NoMoreFiles = ERROR_NO_MORE_FILES,

        /// <summary>
        /// The media is write protected.
        /// </summary>
        WriteProtect = ERROR_WRITE_PROTECT,

        /// <summary>
        /// The system cannot find the device specified.
        /// </summary>
        BadUnit = ERROR_BAD_UNIT,
        /// <summary>
        /// The device is not ready.
        /// </summary>
        NotReady = ERROR_NOT_READY,

        /// <summary>
        /// The device does not recognize the command.
        /// </summary>
        BadCommand = ERROR_BAD_COMMAND,

        /// <summary>
        /// Data error (cyclic redundancy check).
        /// </summary>
        CyclicRedundancyCheck = ERROR_CRC,

        /// <summary>
        /// The program issued a command but the command length is incorrect.
        /// </summary>
        BadLength = ERROR_BAD_LENGTH,

        /// <summary>
        /// The drive cannot locate a specific area or track on the disk.
        /// </summary>
        Seek = ERROR_SEEK,

        /// <summary>
        /// The specified disk or diskette cannot be accessed.
        /// </summary>
        NotDosDisk = ERROR_NOT_DOS_DISK,

        /// <summary>
        /// The drive cannot find the sector requested.
        /// </summary>
        SectorNotFound = ERROR_SECTOR_NOT_FOUND,

        /// <summary>
        /// The printer is out of paper.
        /// </summary>
        OutOfPaper = ERROR_OUT_OF_PAPER,

        /// <summary>
        /// The system cannot write to the specified device.
        /// </summary>
        WriteFault = ERROR_WRITE_FAULT,

        /// <summary>
        /// The system cannot read from the specified device.
        /// </summary>
        ReadFault = ERROR_READ_FAULT,

        /// <summary>
        /// A device attached to the system is not functioning.
        /// </summary>
        Failure = ERROR_GEN_FAILURE,

        /// <summary>
        /// The process cannot access the file because it is being used by another process.
        /// </summary>
        SharingViolation = ERROR_SHARING_VIOLATION,

        /// <summary>
        /// The process cannot access the file because another process has locked a portion of the file.
        /// </summary>
        LockViolation = ERROR_LOCK_VIOLATION,

        /// <summary>
        /// The wrong diskette is in the drive.
        /// Insert %2 (Volume Serial Number: %3) into drive %1.
        /// </summary>
        WrongDisk = ERROR_WRONG_DISK,

        /// <summary>
        /// Too many files opened for sharing.
        /// </summary>
        SharingBufferExceeded = ERROR_SHARING_BUFFER_EXCEEDED,

        /// <summary>
        /// Reached the end of the file.
        /// </summary>
        HandleEndOfFile = ERROR_HANDLE_EOF,

        /// <summary>
        /// The disk is full.
        /// </summary>
        HandleDiskFull = ERROR_HANDLE_DISK_FULL,

        /// <summary>
        /// The request is not supported.
        /// </summary>
        NotSupported = ERROR_NOT_SUPPORTED,

        /// <summary>
        /// Windows cannot find the network path. Verify that the network 
        /// path is correct and the destination computer is not busy or 
        /// turned off. If Windows still cannot find the network path, 
        /// contact your network administrator.
        /// </summary>
        RemNotList = ERROR_REM_NOT_LIST,

        /// <summary>
        /// You were not connected because a duplicate name exists on the network. 
        /// If joining a domain, go to System in Control Panel to change the computer 
        /// name and try again. If joining a workgroup, choose another workgroup name.
        /// </summary>
        DuplicateName = ERROR_DUP_NAME,

        /// <summary>
        /// The network path was not found.
        /// </summary>
        BadNetworkPath = ERROR_BAD_NETPATH,

        /// <summary>
        /// The network is busy.
        /// </summary>
        NetworkBusy = ERROR_NETWORK_BUSY,

        /// <summary>
        /// The specified network resource or device is no longer available.
        /// </summary>
        DeviceNotExist = ERROR_DEV_NOT_EXIST,

        /// <summary>
        /// The network BIOS command limit has been reached.
        /// </summary>
        TooManyCommands = ERROR_TOO_MANY_CMDS,

        /// <summary>
        /// A network adapter hardware error occurred.
        /// </summary>
        AdapterHardwareError = ERROR_ADAP_HDW_ERR,

        /// <summary>
        /// The specified server cannot perform the requested operation.
        /// </summary>
        BadNetworkResponse = ERROR_BAD_NET_RESP,

        /// <summary>
        /// An unexpected network error occurred.
        /// </summary>
        UnexpectedNetworkError = ERROR_UNEXP_NET_ERR,

        /// <summary>
        /// The remote adapter is not compatible.
        /// </summary>
        BadRemoteAdapter = ERROR_BAD_REM_ADAP,

        /// <summary>
        /// The printer queue is full.
        /// </summary>
        PrinterQueueIsFull = ERROR_PRINTQ_FULL,

        /// <summary>
        /// Space to store the file waiting to be printed is not available on the server.
        /// </summary>
        NoSpoolSpace = ERROR_NO_SPOOL_SPACE,

        /// <summary>
        /// Your file waiting to be printed was deleted.
        /// </summary>
        PrintCancelled = ERROR_PRINT_CANCELLED,

        /// <summary>
        /// The specified network name is no longer available.
        /// </summary>
        NetworkNameDeleted = ERROR_NETNAME_DELETED,

        /// <summary>
        /// Network access is denied.
        /// </summary>
        NetworkAccessDenied =  ERROR_NETWORK_ACCESS_DENIED,

        /// <summary>
        /// The network resource type is not correct.
        /// </summary>
        BadDeviceType =  ERROR_BAD_DEV_TYPE,

        /// <summary>
        /// The network name cannot be found.
        /// </summary>
        BadNetworkName = ERROR_BAD_NET_NAME,

        /// <summary>
        /// The name limit for the local computer network adapter card was exceeded.
        /// </summary>
        TooManyNames = ERROR_TOO_MANY_NAMES,

        /// <summary>
        /// The network BIOS session limit was exceeded.
        /// </summary>
        TooManySessions = ERROR_TOO_MANY_SESS,

        /// <summary>
        /// The remote server has been paused or is in the process of being started.
        /// </summary>
        SharingPaused = ERROR_SHARING_PAUSED,

        /// <summary>
        /// No more connections can be made to this remote computer at this time 
        /// because there are already as many connections as the computer can accept.
        /// </summary>
        RequestNotAccepted = ERROR_REQ_NOT_ACCEP,

        /// <summary>
        /// The specified printer or disk device has been paused.
        /// </summary>
        RedirectPaused = ERROR_REDIR_PAUSED,

        /// <summary>
        /// The file exists.
        /// </summary>
        FileExists = ERROR_FILE_EXISTS,

        /// <summary>
        /// The directory or file cannot be created.
        /// </summary>
        CannotMake = ERROR_CANNOT_MAKE,

        /// <summary>
        /// Fail on INT 24.
        /// </summary>
        Int24Failure = ERROR_FAIL_I24,

        /// <summary>
        /// Storage to process this request is not available.
        /// </summary>
        OutOfStructures = ERROR_OUT_OF_STRUCTURES,

        /// <summary>
        /// The local device name is already in use.
        /// </summary>
        AlreadyAssigned = ERROR_ALREADY_ASSIGNED,

        /// <summary>
        /// The specified network password is not correct.
        /// </summary>
        InvalidPassword = ERROR_INVALID_PASSWORD,

        /// <summary>
        /// The parameter is incorrect.
        /// </summary>
        InvalidParameter = ERROR_INVALID_PARAMETER,

        /// <summary>
        /// A write fault occurred on the network.
        /// </summary>
        NetworkWriteFault =  ERROR_NET_WRITE_FAULT,

        /// <summary>
        /// The system cannot start another process at this time.
        /// </summary>
        NoProcessSlots = ERROR_NO_PROC_SLOTS,

        /// <summary>
        /// Cannot create another system semaphore.
        /// </summary>
        TooManySemaphores = ERROR_TOO_MANY_SEMAPHORES,

        /// <summary>
        /// The exclusive semaphore is owned by another process.
        /// </summary>
        ExclusiveSemaphoreAlreadyOwned = ERROR_EXCL_SEM_ALREADY_OWNED,

        /// <summary>
        /// The semaphore is set and cannot be closed.
        /// </summary>
        SemaphoreIsSet = ERROR_SEM_IS_SET,

        /// <summary>
        /// The semaphore cannot be set again.
        /// </summary>
        TooManySemaphoreRequests = ERROR_TOO_MANY_SEM_REQUESTS,

        /// <summary>
        /// Cannot request exclusive semaphores at interrupt time.
        /// </summary>
        InvalidAtInterruptTime = ERROR_INVALID_AT_INTERRUPT_TIME,

        /// <summary>
        /// The previous ownership of this semaphore has ended.
        /// </summary>
        SemaphoreOwnerDied = ERROR_SEM_OWNER_DIED,

        /// <summary>
        /// 
        /// </summary>
        SemaphoreUserLimit = ERROR_SEM_USER_LIMIT,

        /// <summary>
        /// The program stopped because an alternate diskette was not inserted.
        /// </summary>
        DiskChange = ERROR_DISK_CHANGE,

        /// <summary>
        /// The disk is in use or locked by another process.
        /// </summary>
        DriveLocked = ERROR_DRIVE_LOCKED,

        /// <summary>
        /// The pipe has been ended.
        /// </summary>
        BrokenPipe = ERROR_BROKEN_PIPE,

        /// <summary>
        /// The system cannot open the device or file specified.
        /// </summary>
        OpenFailed = ERROR_OPEN_FAILED,

        /// <summary>
        /// The file name is too long.
        /// </summary>
        BufferOverflow = ERROR_BUFFER_OVERFLOW,
        /// <summary>
        /// There is not enough space on the disk.
        /// </summary>
        DiskFull = ERROR_DISK_FULL,

        /// <summary>
        /// No more internal file identifiers available.
        /// </summary>
        NoMoreSearchHandles = ERROR_NO_MORE_SEARCH_HANDLES,

        /// <summary>
        /// The target internal file identifier is incorrect.
        /// </summary>
        InvalidTargetHandle = ERROR_INVALID_TARGET_HANDLE,

        /// <summary>
        /// The IOCTL call made by the application program is not correct.
        /// </summary>
        InvalidCategory = ERROR_INVALID_CATEGORY,

        /// <summary>
        /// The verify-on-write switch parameter value is not correct.
        /// </summary>
        InvalidVerifySwitch = ERROR_INVALID_VERIFY_SWITCH,

        /// <summary>
        /// The system does not support the command requested.
        /// </summary>
        BadDriverLevel = ERROR_BAD_DRIVER_LEVEL,

        /// <summary>
        /// This function is not supported on this system.
        /// </summary>
        CallNotImplemented = ERROR_CALL_NOT_IMPLEMENTED,

        /// <summary>
        /// The semaphore timeout period has expired.
        /// </summary>
        SemaphoreTimeout = ERROR_SEM_TIMEOUT,

        /// <summary>
        /// The data area passed to a system call is too small.
        /// </summary>
        InsufficientBuffer = ERROR_INSUFFICIENT_BUFFER,

        /// <summary>
        /// The filename, directory name, or volume label syntax is incorrect.
        /// </summary>
        InvalidName = ERROR_INVALID_NAME,

        /// <summary>
        /// The system call level is not correct.
        /// </summary>
        InvalidLevel = ERROR_INVALID_LEVEL,

        /// <summary>
        /// The disk has no volume label.
        /// </summary>
        NoVolumeLabel = ERROR_NO_VOLUME_LABEL,

        /// <summary>
        /// The specified module could not be found.
        /// </summary>
        ModuleNotFound = ERROR_MOD_NOT_FOUND,

        /// <summary>
        /// The specified procedure could not be found.
        /// </summary>
        ProcedureNotFound = ERROR_PROC_NOT_FOUND,

        /// <summary>
        /// There are no child processes to wait for.
        /// </summary>
        WaitNoChildren = ERROR_WAIT_NO_CHILDREN,

        /// <summary>
        /// The %1 application cannot be run in Win32 mode.
        /// </summary>
        ChildNotComplete = ERROR_CHILD_NOT_COMPLETE,

        /// <summary>
        /// Attempt to use a file handle to an open disk partition for an operation other than raw disk I/O.
        /// </summary>
        DirectAccessHandle = ERROR_DIRECT_ACCESS_HANDLE,

        /// <summary>
        /// An attempt was made to move the file pointer before the beginning of the file.
        /// </summary>
        NegativeSeek = ERROR_NEGATIVE_SEEK,

        /// <summary>
        /// The file pointer cannot be set on the specified device or file.
        /// </summary>
        SeekOnDevice = ERROR_SEEK_ON_DEVICE,

        /// <summary>
        /// A JOIN or SUBST command cannot be used for a drive that contains previously joined drives.
        /// </summary>
        IsJoinTarget = ERROR_IS_JOIN_TARGET,

        /// <summary>
        /// An attempt was made to use a JOIN or SUBST command on a drive that has already been joined.
        /// </summary>
        IsJoined = ERROR_IS_JOINED,

        /// <summary>
        /// An attempt was made to use a JOIN or SUBST command on a drive that has already been substituted.
        /// </summary>
        IsSubsted = ERROR_IS_SUBSTED,

        /// <summary>
        /// The system tried to delete the JOIN of a drive that is not joined.
        /// </summary>
        NotJoined = ERROR_NOT_JOINED,

        /// <summary>
        /// The system tried to delete the substitution of a drive that is not substituted.
        /// </summary>
        NotSubsted = ERROR_NOT_SUBSTED,

        /// <summary>
        /// The system tried to join a drive to a directory on a joined drive.
        /// </summary>
        JoinToJoin = ERROR_JOIN_TO_JOIN,

        /// <summary>
        /// The system tried to substitute a drive to a directory on a substituted drive.
        /// </summary>
        SubstToSubst = ERROR_SUBST_TO_SUBST,

        /// <summary>
        /// The system tried to join a drive to a directory on a substituted drive.
        /// </summary>
        JoinToSubst = ERROR_JOIN_TO_SUBST,

        /// <summary>
        /// The system tried to SUBST a drive to a directory on a joined drive.
        /// </summary>
        SubstToJoin = ERROR_SUBST_TO_JOIN,

        /// <summary>
        /// The system cannot perform a JOIN or SUBST at this time.
        /// </summary>
        BusyDrive = ERROR_BUSY_DRIVE,

        /// <summary>
        /// The system cannot join or substitute a drive to or for a directory on the same drive.
        /// </summary>
        SameDrive = ERROR_SAME_DRIVE,

        /// <summary>
        /// The directory is not a subdirectory of the root directory.
        /// </summary>
        DirectoryNotRoot = ERROR_DIR_NOT_ROOT,

        /// <summary>
        /// The directory is not empty.
        /// </summary>
        DirectoryNotEmpty = ERROR_DIR_NOT_EMPTY,

        /// <summary>
        /// The path specified is being used in a substitute.
        /// </summary>
        IsSubstPath = ERROR_IS_SUBST_PATH,

        /// <summary>
        /// Not enough resources are available to process this command.
        /// </summary>
        IsJoinPath = ERROR_IS_JOIN_PATH,

        /// <summary>
        /// The path specified cannot be used at this time.
        /// </summary>
        PathBusy = ERROR_PATH_BUSY,

        /// <summary>
        /// An attempt was made to join or substitute a drive for which a directory on the drive is the target of a previous substitute.
        /// </summary>
        IsSubstTarget = ERROR_IS_SUBST_TARGET,

        /// <summary>
        /// System trace information was not specified in your 
        /// CONFIG.SYS file, or tracing is disallowed.
        /// </summary>
        SystemTrace = ERROR_SYSTEM_TRACE,

        /// <summary>
        /// The number of specified semaphore events for DosMuxSemWait is not correct.
        /// </summary>
        InvalidEventCount = ERROR_INVALID_EVENT_COUNT,

        /// <summary>
        /// DosMuxSemWait did not execute; too many semaphores are already set.
        /// </summary>
        TooManyMuxWaiters = ERROR_TOO_MANY_MUXWAITERS,

        /// <summary>
        /// The DosMuxSemWait list is not correct.
        /// </summary>
        InvalidListFormat = ERROR_INVALID_LIST_FORMAT,

        /// <summary>
        /// The volume label you entered exceeds the label character limit of the target file system.
        /// </summary>
        LabelTooLong = ERROR_LABEL_TOO_LONG,

        /// <summary>
        /// Cannot create another thread.
        /// </summary>
        TooManyThreadControlBlocks = ERROR_TOO_MANY_TCBS,

        /// <summary>
        /// The recipient process has refused the signal.
        /// </summary>
        SignalRefused = ERROR_SIGNAL_REFUSED,

        /// <summary>
        /// The segment is already discarded and cannot be locked.
        /// </summary>
        Discarded = ERROR_DISCARDED,

        /// <summary>
        /// The segment is already unlocked.
        /// </summary>
        NotLocked = ERROR_NOT_LOCKED,

        /// <summary>
        /// The address for the thread ID is not correct.
        /// </summary>
        BadThreadIdAddress = ERROR_BAD_THREADID_ADDR,

        /// <summary>
        /// One or more arguments are not correct.
        /// </summary>
        BadArguments = ERROR_BAD_ARGUMENTS,

        /// <summary>
        /// The specified path is invalid.
        /// </summary>
        BadPathname = ERROR_BAD_PATHNAME,

        /// <summary>
        /// A signal is already pending.
        /// </summary>
        SignalPending = ERROR_SIGNAL_PENDING,

        /// <summary>
        /// No more threads can be created in the system.
        /// </summary>
        MaxThreadsReached = ERROR_MAX_THRDS_REACHED,

        /// <summary>
        /// Unable to lock a region of a file.
        /// </summary>
        LockFailed = ERROR_LOCK_FAILED,

        /// <summary>
        /// The requested resource is in use.
        /// </summary>
        Busy = ERROR_BUSY,

        /// <summary>
        /// Device's command support detection is in progress.
        /// </summary>
        DeviceSupportInProgress = ERROR_DEVICE_SUPPORT_IN_PROGRESS,

        /// <summary>
        /// A lock request was not outstanding for the supplied cancel region.
        /// </summary>
        CancelViolation = ERROR_CANCEL_VIOLATION,

        /// <summary>
        /// The file system does not support atomic changes to the lock type.
        /// </summary>
        AtomicLocksNotSupported = ERROR_ATOMIC_LOCKS_NOT_SUPPORTED,

        /// <summary>
        /// The system detected a segment number that was not correct.
        /// </summary>
        InvalidSegmentNumber = ERROR_INVALID_SEGMENT_NUMBER,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InvalidOrdinal = ERROR_INVALID_ORDINAL,

        /// <summary>
        /// Cannot create a file when that file already exists.
        /// </summary>
        AlreadyExists = ERROR_ALREADY_EXISTS,

        /// <summary>
        /// The flag passed is not correct.
        /// </summary>
        InvalidFlagNumber = ERROR_INVALID_FLAG_NUMBER,

        /// <summary>
        /// The specified system semaphore name was not found.
        /// </summary>
        SemaphoreNotFound = ERROR_SEM_NOT_FOUND,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InvalidStartingCodeSegment = ERROR_INVALID_STARTING_CODESEG,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InvalidStackSegment = ERROR_INVALID_STACKSEG,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InvalidModuleType = ERROR_INVALID_MODULETYPE,

        /// <summary>
        /// Cannot run %1 in Win32 mode.
        /// </summary>
        InvalidExeSignature = ERROR_INVALID_EXE_SIGNATURE,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        ExeMarkedInvalid = ERROR_EXE_MARKED_INVALID,

        /// <summary>
        /// %1 is not a valid Win32 application.
        /// </summary>
        BadExeFormat = ERROR_BAD_EXE_FORMAT,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        IteratedDataExceeds64k = ERROR_ITERATED_DATA_EXCEEDS_64k,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InvalidMinAllocSize = ERROR_INVALID_MINALLOCSIZE,

        /// <summary>
        /// The operating system cannot run this application program.
        /// </summary>
        DynlinkFromInvalidRing = ERROR_DYNLINK_FROM_INVALID_RING,

        /// <summary>
        /// The operating system is not presently configured to run this application.
        /// </summary>
        IoplNotEnabled = ERROR_IOPL_NOT_ENABLED,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InvalidSegDpl = ERROR_INVALID_SEGDPL,

        /// <summary>
        /// The operating system cannot run this application program.
        /// </summary>
        AutoDataSegExceeds64k = ERROR_AUTODATASEG_EXCEEDS_64k,

        /// <summary>
        /// The code segment cannot be greater than or equal to 64K.
        /// </summary>
        Ring2SegMustBeMovable = ERROR_RING2SEG_MUST_BE_MOVABLE,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        RelocChainXeedsSegLim = ERROR_RELOC_CHAIN_XEEDS_SEGLIM,

        /// <summary>
        /// The operating system cannot run %1.
        /// </summary>
        InfLoopInRelocChain = ERROR_INFLOOP_IN_RELOC_CHAIN,

        /// <summary>
        /// The system could not find the environment option that was entered.
        /// </summary>
        EnvVarNotFound = ERROR_ENVVAR_NOT_FOUND,

        /// <summary>
        /// No process in the command subtree has a signal handler.
        /// </summary>
        NoSignalSent = ERROR_NO_SIGNAL_SENT,

        /// <summary>
        /// The filename or extension is too long.
        /// </summary>
        FilenameExcedRange = ERROR_FILENAME_EXCED_RANGE,

        /// <summary>
        /// The ring 2 stack is in use.
        /// </summary>
        Ring2StackInUse = ERROR_RING2_STACK_IN_USE,

        /// <summary>
        /// The global filename characters, * or ?, are entered incorrectly or too many global filename characters are specified.
        /// </summary>
        MetaExpansionTooLong = ERROR_META_EXPANSION_TOO_LONG,

        /// <summary>
        /// The signal being posted is not correct.
        /// </summary>
        InvalidSignalNumber = ERROR_INVALID_SIGNAL_NUMBER,

        /// <summary>
        /// The signal handler cannot be set.
        /// </summary>
        Thread1Inactive = ERROR_THREAD_1_INACTIVE,

        /// <summary>
        /// The segment is locked and cannot be reallocated.
        /// </summary>
        Locked = ERROR_LOCKED,

        /// <summary>
        /// Too many dynamic-link modules are attached to this program or dynamic-link module.
        /// </summary>
        TooManyModules = ERROR_TOO_MANY_MODULES,

        /// <summary>
        /// Cannot nest calls to LoadModule.
        /// </summary>
        NestingNotAllowed = ERROR_NESTING_NOT_ALLOWED,

        /// <summary>
        /// This version of %1 is not compatible with the version of Windows 
        /// you're running. Check your computer's system information and then 
        /// contact the software publisher.
        /// </summary>
        ExeMachineTypeMismatch = ERROR_EXE_MACHINE_TYPE_MISMATCH,


        IoIncomplete = ERROR_IO_INCOMPLETE,
        IoPending = ERROR_IO_PENDING,
        OperationAborted = ERROR_OPERATION_ABORTED,
        StatusCancelled = std::bit_cast<unsigned int>(STATUS_CANCELLED),
        StatusLocalDisconnect = std::bit_cast<unsigned int>(STATUS_LOCAL_DISCONNECT),
        StatusRemoteDisconnect = std::bit_cast<unsigned int>(STATUS_REMOTE_DISCONNECT),
        /// <summary>
        /// A blocking operation was interrupted by a call to WSACancelBlockingCall.
        /// </summary>
        WsaInterrupted = WSAEINTR,
        /// <summary>
        /// The file handle supplied is not valid.
        /// </summary>
        WsaBadFileHandle = WSAEBADF,
        /// <summary>
        /// An attempt was made to access a socket in a way forbidden by its access permissions.
        /// </summary>
        WsaAccess = WSAEACCES,
        /// <summary>
        /// The system detected an invalid pointer address in attempting to use a pointer argument in a call.
        /// </summary>
        WsaInvalidPointer = WSAEFAULT,
        /// <summary>
        /// An invalid argument was supplied.
        /// </summary>
        WsaInvalidArgument = WSAEINVAL,
        /// <summary>
        /// Too many open sockets.
        /// </summary>
        WsaToManyOpenSockets = WSAEMFILE,
        /// <summary>
        /// A non-blocking socket operation could not be completed immediately.
        /// </summary>
        WsaWouldBlock = WSAEWOULDBLOCK,
        /// <summary>
        /// A blocking operation is currently executing.
        /// </summary>
        WsaInProgress = WSAEINPROGRESS,
        /// <summary>
        /// An operation was attempted on a non-blocking socket that already had an operation in progress.
        /// </summary>
        WsaAlready = WSAEALREADY,
        /// <summary>
        /// An operation was attempted on something that is not a socket.
        /// </summary>
        WsaNotSocket = WSAENOTSOCK,
        /// <summary>
        /// A required address was omitted from an operation on a socket.
        /// </summary>
        WsaDestinationAddressRequired = WSAEDESTADDRREQ,
        /// <summary>
        /// A message sent on a datagram socket was larger than the internal 
        /// message buffer or some other network limit, or the buffer used to 
        /// receive a datagram into was smaller than the datagram itself.
        /// </summary>
        WsaMessageSize = WSAEMSGSIZE,
        /// <summary>
        /// A protocol was specified in the socket function call that does 
        /// not support the semantics of the socket type requested.
        /// </summary>
        WsaProtocolType = WSAEPROTOTYPE,
        /// <summary>
        /// An unknown, invalid, or unsupported option or level was specified 
        /// in a getsockopt or setsockopt call.
        /// </summary>
        WsaInvalidProtocolOptionId = WSAENOPROTOOPT,
        /// <summary>
        /// The requested protocol has not been configured into the system, or 
        /// no implementation for it exists.
        /// </summary>
        WsaProtocolNotSupported = WSAEPROTONOSUPPORT,
        /// <summary>
        /// The support for the specified socket type does not exist in this address family.
        /// </summary>
        WsaSocketTypeNotSupportedByAddressFamily = WSAESOCKTNOSUPPORT,
        /// <summary>
        /// The attempted operation is not supported for the type of object referenced.
        /// </summary>
        WsaOperationNotSupported = WSAEOPNOTSUPP,
        /// <summary>
        /// The protocol family has not been configured into the system or no 
        /// implementation for it exists.
        /// </summary>
        WsaProtocolFamilyNotSupported = WSAEPFNOSUPPORT,

        /// <summary>
        /// An address incompatible with the requested protocol was used.
        /// </summary>
        WsaAddressIncompatibleWithProtocol = WSAEAFNOSUPPORT,
        /// <summary>
        /// Only one usage of each socket address (protocol/network address/port) 
        /// is normally permitted.
        /// </summary>
        WsaAddressInUse = WSAEADDRINUSE,
        /// <summary>
        /// The requested address is not valid in its context.
        /// </summary>
        WsaAddressNotAvailable = WSAEADDRNOTAVAIL,
        /// <summary>
        /// A socket operation encountered a dead network.
        /// </summary>
        WsaNetworkDown = WSAENETDOWN,
        /// <summary>
        /// A socket operation was attempted to an unreachable network.
        /// </summary>
        WsaNetworkUnreachable = WSAENETUNREACH,
        /// <summary>
        /// The connection has been broken due to keep-alive activity 
        /// detecting a failure while the operation was in progress.
        /// </summary>
        WsaNetworkReset = WSAENETRESET,
        /// <summary>
        /// An established connection was aborted by the software in your host machine.
        /// </summary>
        WsaConnectionAborted = WSAECONNABORTED,
        /// <summary>
        /// An existing connection was forcibly closed by the remote host.
        /// </summary>
        WsaConnectionReset = WSAECONNRESET,
        /// <summary>
        /// An operation on a socket could not be performed because the system 
        /// lacked sufficient buffer space or because a queue was full.
        /// </summary>
        WsaNoBuffers = WSAENOBUFS,
        /// <summary>
        /// A connect request was made on an already connected socket.
        /// </summary>
        WsaIsConnected = WSAEISCONN,
        /// <summary>
        /// A request to send or receive data was disallowed because the socket is not 
        /// connected and (when sending on a datagram socket using a sendto call) no 
        /// address was supplied.
        /// </summary>
        WsaNotConnected = WSAENOTCONN,
        /// <summary>
        /// A request to send or receive data was disallowed because the socket had 
        /// already been shut down in that direction with a previous shutdown call.
        /// </summary>
        WsaShutdown = WSAESHUTDOWN,
        /// <summary>
        /// Too many references to some kernel object.
        /// </summary>
        WsaTooManyReferences = WSAETOOMANYREFS,
        /// <summary>
        /// A connection attempt failed because the connected party did not properly 
        /// respond after a period of time, or established connection failed because 
        /// connected host has failed to respond.
        /// </summary>
        WsaTimedout = WSAETIMEDOUT,
        /// <summary>
        /// No connection could be made because the target machine actively refused it.
        /// </summary>
        WsaConnectionRefused = WSAECONNREFUSED,
        /// <summary>
        /// Cannot translate name.
        /// </summary>
        /// <remarks>
        /// An odd one ... perhaps it actually has a different meaning
        /// </remarks>
        WsaLoop = WSAELOOP,
        /// <summary>
        /// Name component or name was too long.
        /// </summary>
        WsaNameTooLong = WSAENAMETOOLONG,
        /// <summary>
        /// A socket operation failed because the destination host was down.
        /// </summary>
        WsaHostIsDown = WSAEHOSTDOWN,
        /// <summary>
        /// A socket operation was attempted to an unreachable host.
        /// </summary>
        WsaHostUnreachable = WSAEHOSTUNREACH,
        /// <summary>
        /// Cannot remove a directory that is not empty.
        /// </summary>
        WsaNotEmpty = WSAENOTEMPTY,
        /// <summary>
        /// A Windows Sockets implementation may have a limit on the 
        /// number of applications that may use it simultaneously.
        /// </summary>
        WsaProcessLimit = WSAEPROCLIM,
        /// <summary>
        /// Ran out of quota.
        /// </summary>
        WsaUsers = WSAEUSERS,
        /// <summary>
        /// Ran out of disk quota.
        /// </summary>
        WsaDiskQuota = WSAEDQUOT,
        /// <summary>
        /// File handle reference is no longer available.
        /// </summary>
        WsaStale = WSAESTALE,
        /// <summary>
        /// Item is not available locally.
        /// </summary>
        WsaRemote = WSAEREMOTE,
        /// <summary>
        /// WSAStartup cannot function at this time because the underlying system 
        /// it uses to provide network services is currently unavailable.
        /// </summary>
        WsaSystemNotReady = WSASYSNOTREADY,
        /// <summary>
        /// The Windows Sockets version requested is not supported.
        /// </summary>
        WsaVersionNotSupported = WSAVERNOTSUPPORTED,
        /// <summary>
        /// Either the application has not called WSAStartup, or WSAStartup failed.
        /// </summary>
        WsaNotInitialised = WSANOTINITIALISED,
        /// <summary>
        /// Returned by WSARecv or WSARecvFrom to indicate the remote party has 
        /// initiated a graceful shutdown sequence.
        /// </summary>
        WsaDisconnected = WSAEDISCON,
        /// <summary>
        /// No more results can be returned by WSALookupServiceNext.
        /// </summary>
        WsaNoMore = WSAENOMORE,
        WsaNoMore2 = WSA_E_NO_MORE,
        /// <summary>
        /// A call to WSALookupServiceEnd was made while this call 
        /// was still processing. The call has been canceled.
        /// </summary>
        WsaCancelled = WSAECANCELLED,
        /// <summary>
        /// A call to WSALookupServiceEnd was made while this call 
        /// was still processing. The call has been canceled.
        /// </summary>
        WsaCancelled2 = WSA_E_CANCELLED,
        /// <summary>
        /// The procedure call table is invalid.
        /// </summary>
        WsaInvalidProcedureCallTable = WSAEINVALIDPROCTABLE,
        /// <summary>
        /// The requested service provider is invalid.
        /// </summary>
        WsaInvalidServiceProvider = WSAEINVALIDPROVIDER,
        /// <summary>
        /// The requested service provider could not be loaded or initialized.
        /// </summary>
        WsaProviderInitializationFailed = WSAEPROVIDERFAILEDINIT,
        /// <summary>
        /// A system call has failed.
        /// </summary>
        WsaSystemCallFailure = WSASYSCALLFAILURE,
        /// <summary>
        /// No such service is known. The service cannot be found in the specified name space.
        /// </summary>
        WsaServiceNotFound = WSASERVICE_NOT_FOUND,
        /// <summary>
        /// The specified class was not found.
        /// </summary>
        WsaTypeNotFound = WSATYPE_NOT_FOUND,
        /// <summary>
        /// A database query failed because it was actively refused.
        /// </summary>
        WsaRefused = WSAEREFUSED,
        /// <summary>
        /// No such host is known.
        /// </summary>
        WsaHostNotFound = WSAHOST_NOT_FOUND,
        /// <summary>
        /// This is usually a temporary error during hostname resolution 
        /// and means that the local server did not receive a response 
        /// from an authoritative server.
        /// </summary>
        WsaTryAgain = WSATRY_AGAIN,
        /// <summary>
        /// A non-recoverable error occurred during a database lookup.
        /// </summary>
        WsaNoRecovery = WSANO_RECOVERY,
        /// <summary>
        /// The requested name is valid, but no data of the requested type was found.
        /// </summary>
        WsaNoData = WSANO_DATA,



    };
}

#endif
