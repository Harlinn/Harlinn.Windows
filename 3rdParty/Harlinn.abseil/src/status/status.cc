// Copyright 2019 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "absl/status/status.h"

#include <errno.h>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <ostream>
#include <string>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/strerror.h"
#include "absl/base/macros.h"
#include "absl/base/no_destructor.h"
#include "absl/base/nullability.h"
#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"
#include "absl/status/internal/status_internal.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

static_assert(
    alignof(status_internal::StatusRep) >= 4,
    "absl::Status assumes it can use the bottom 2 bits of a StatusRep*.");

ABSEIL_EXPORT std::string StatusCodeToString(StatusCode code) {
  switch (code) {
    case StatusCode::kOk:
      return "OK";
    case StatusCode::kCancelled:
      return "CANCELLED";
    case StatusCode::kUnknown:
      return "UNKNOWN";
    case StatusCode::kInvalidArgument:
      return "INVALID_ARGUMENT";
    case StatusCode::kDeadlineExceeded:
      return "DEADLINE_EXCEEDED";
    case StatusCode::kNotFound:
      return "NOT_FOUND";
    case StatusCode::kAlreadyExists:
      return "ALREADY_EXISTS";
    case StatusCode::kPermissionDenied:
      return "PERMISSION_DENIED";
    case StatusCode::kUnauthenticated:
      return "UNAUTHENTICATED";
    case StatusCode::kResourceExhausted:
      return "RESOURCE_EXHAUSTED";
    case StatusCode::kFailedPrecondition:
      return "FAILED_PRECONDITION";
    case StatusCode::kAborted:
      return "ABORTED";
    case StatusCode::kOutOfRange:
      return "OUT_OF_RANGE";
    case StatusCode::kUnimplemented:
      return "UNIMPLEMENTED";
    case StatusCode::kInternal:
      return "INTERNAL";
    case StatusCode::kUnavailable:
      return "UNAVAILABLE";
    case StatusCode::kDataLoss:
      return "DATA_LOSS";
    default:
      return "";
  }
}

ABSEIL_EXPORT std::ostream& operator<<(std::ostream& os, StatusCode code) {
  return os << StatusCodeToString(code);
}

absl::Nonnull<const std::string*> Status::EmptyString() {
  static const absl::NoDestructor<std::string> kEmpty;
  return kEmpty.get();
}

#ifdef ABSL_INTERNAL_NEED_REDUNDANT_CONSTEXPR_DECL
constexpr const char Status::kMovedFromString[];
#endif

absl::Nonnull<const std::string*> Status::MovedFromString() {
  static const absl::NoDestructor<std::string> kMovedFrom(kMovedFromString);
  return kMovedFrom.get();
}

Status::Status(absl::StatusCode code, absl::string_view msg)
    : rep_(CodeToInlinedRep(code)) {
  if (code != absl::StatusCode::kOk && !msg.empty()) {
    rep_ = PointerToRep(new status_internal::StatusRep(code, msg, nullptr));
  }
}

absl::Nonnull<status_internal::StatusRep*> Status::PrepareToModify(
    uintptr_t rep) {
  if (IsInlined(rep)) {
    return new status_internal::StatusRep(InlinedRepToCode(rep),
                                          absl::string_view(), nullptr);
  }
  return RepToPointer(rep)->CloneAndUnref();
}

ABSEIL_EXPORT std::string Status::ToStringSlow(uintptr_t rep, StatusToStringMode mode) {
  if (IsInlined(rep)) {
    return absl::StrCat(absl::StatusCodeToString(InlinedRepToCode(rep)), ": ");
  }
  return RepToPointer(rep)->ToString(mode);
}

ABSEIL_EXPORT std::ostream& operator<<(std::ostream& os, const Status& x) {
  os << x.ToString(StatusToStringMode::kWithEverything);
  return os;
}

ABSEIL_EXPORT Status AbortedError(absl::string_view message) {
  return Status(absl::StatusCode::kAborted, message);
}

ABSEIL_EXPORT Status AlreadyExistsError(absl::string_view message) {
  return Status(absl::StatusCode::kAlreadyExists, message);
}

ABSEIL_EXPORT Status CancelledError(absl::string_view message) {
  return Status(absl::StatusCode::kCancelled, message);
}

ABSEIL_EXPORT Status DataLossError(absl::string_view message) {
  return Status(absl::StatusCode::kDataLoss, message);
}

ABSEIL_EXPORT Status DeadlineExceededError(absl::string_view message) {
  return Status(absl::StatusCode::kDeadlineExceeded, message);
}

ABSEIL_EXPORT Status FailedPreconditionError(absl::string_view message) {
  return Status(absl::StatusCode::kFailedPrecondition, message);
}

ABSEIL_EXPORT Status InternalError(absl::string_view message) {
  return Status(absl::StatusCode::kInternal, message);
}

ABSEIL_EXPORT Status InvalidArgumentError(absl::string_view message) {
  return Status(absl::StatusCode::kInvalidArgument, message);
}

ABSEIL_EXPORT Status NotFoundError(absl::string_view message) {
  return Status(absl::StatusCode::kNotFound, message);
}

ABSEIL_EXPORT Status OutOfRangeError(absl::string_view message) {
  return Status(absl::StatusCode::kOutOfRange, message);
}

ABSEIL_EXPORT Status PermissionDeniedError(absl::string_view message) {
  return Status(absl::StatusCode::kPermissionDenied, message);
}

ABSEIL_EXPORT Status ResourceExhaustedError(absl::string_view message) {
  return Status(absl::StatusCode::kResourceExhausted, message);
}

ABSEIL_EXPORT Status UnauthenticatedError(absl::string_view message) {
  return Status(absl::StatusCode::kUnauthenticated, message);
}

ABSEIL_EXPORT Status UnavailableError(absl::string_view message) {
  return Status(absl::StatusCode::kUnavailable, message);
}

ABSEIL_EXPORT Status UnimplementedError(absl::string_view message) {
  return Status(absl::StatusCode::kUnimplemented, message);
}

ABSEIL_EXPORT Status UnknownError(absl::string_view message) {
  return Status(absl::StatusCode::kUnknown, message);
}

ABSEIL_EXPORT bool IsAborted(const Status& status) {
  return status.code() == absl::StatusCode::kAborted;
}

ABSEIL_EXPORT bool IsAlreadyExists(const Status& status) {
  return status.code() == absl::StatusCode::kAlreadyExists;
}

ABSEIL_EXPORT bool IsCancelled(const Status& status) {
  return status.code() == absl::StatusCode::kCancelled;
}

ABSEIL_EXPORT bool IsDataLoss(const Status& status) {
  return status.code() == absl::StatusCode::kDataLoss;
}

ABSEIL_EXPORT bool IsDeadlineExceeded(const Status& status) {
  return status.code() == absl::StatusCode::kDeadlineExceeded;
}

ABSEIL_EXPORT bool IsFailedPrecondition(const Status& status) {
  return status.code() == absl::StatusCode::kFailedPrecondition;
}

ABSEIL_EXPORT bool IsInternal(const Status& status) {
  return status.code() == absl::StatusCode::kInternal;
}

ABSEIL_EXPORT bool IsInvalidArgument(const Status& status) {
  return status.code() == absl::StatusCode::kInvalidArgument;
}

ABSEIL_EXPORT bool IsNotFound(const Status& status) {
  return status.code() == absl::StatusCode::kNotFound;
}

ABSEIL_EXPORT bool IsOutOfRange(const Status& status) {
  return status.code() == absl::StatusCode::kOutOfRange;
}

ABSEIL_EXPORT bool IsPermissionDenied(const Status& status) {
  return status.code() == absl::StatusCode::kPermissionDenied;
}

ABSEIL_EXPORT bool IsResourceExhausted(const Status& status) {
  return status.code() == absl::StatusCode::kResourceExhausted;
}

ABSEIL_EXPORT bool IsUnauthenticated(const Status& status) {
  return status.code() == absl::StatusCode::kUnauthenticated;
}

ABSEIL_EXPORT bool IsUnavailable(const Status& status) {
  return status.code() == absl::StatusCode::kUnavailable;
}

ABSEIL_EXPORT bool IsUnimplemented(const Status& status) {
  return status.code() == absl::StatusCode::kUnimplemented;
}

ABSEIL_EXPORT bool IsUnknown(const Status& status) {
  return status.code() == absl::StatusCode::kUnknown;
}

ABSEIL_EXPORT StatusCode ErrnoToStatusCode(int error_number) {
  switch (error_number) {
    case 0:
      return StatusCode::kOk;
    case EINVAL:        // Invalid argument
    case ENAMETOOLONG:  // Filename too long
    case E2BIG:         // Argument list too long
    case EDESTADDRREQ:  // Destination address required
    case EDOM:          // Mathematics argument out of domain of function
    case EFAULT:        // Bad address
    case EILSEQ:        // Illegal byte sequence
    case ENOPROTOOPT:   // Protocol not available
    case ENOSTR:        // Not a STREAM
    case ENOTSOCK:      // Not a socket
    case ENOTTY:        // Inappropriate I/O control operation
    case EPROTOTYPE:    // Protocol wrong type for socket
    case ESPIPE:        // Invalid seek
      return StatusCode::kInvalidArgument;
    case ETIMEDOUT:  // Connection timed out
    case ETIME:      // Timer expired
      return StatusCode::kDeadlineExceeded;
    case ENODEV:  // No such device
    case ENOENT:  // No such file or directory
#ifdef ENOMEDIUM
    case ENOMEDIUM:  // No medium found
#endif
    case ENXIO:  // No such device or address
    case ESRCH:  // No such process
      return StatusCode::kNotFound;
    case EEXIST:         // File exists
    case EADDRNOTAVAIL:  // Address not available
    case EALREADY:       // Connection already in progress
#ifdef ENOTUNIQ
    case ENOTUNIQ:  // Name not unique on network
#endif
      return StatusCode::kAlreadyExists;
    case EPERM:   // Operation not permitted
    case EACCES:  // Permission denied
#ifdef ENOKEY
    case ENOKEY:  // Required key not available
#endif
    case EROFS:  // Read only file system
      return StatusCode::kPermissionDenied;
    case ENOTEMPTY:   // Directory not empty
    case EISDIR:      // Is a directory
    case ENOTDIR:     // Not a directory
    case EADDRINUSE:  // Address already in use
    case EBADF:       // Invalid file descriptor
#ifdef EBADFD
    case EBADFD:  // File descriptor in bad state
#endif
    case EBUSY:    // Device or resource busy
    case ECHILD:   // No child processes
    case EISCONN:  // Socket is connected
#ifdef EISNAM
    case EISNAM:  // Is a named type file
#endif
#ifdef ENOTBLK
    case ENOTBLK:  // Block device required
#endif
    case ENOTCONN:  // The socket is not connected
    case EPIPE:     // Broken pipe
#ifdef ESHUTDOWN
    case ESHUTDOWN:  // Cannot send after transport endpoint shutdown
#endif
    case ETXTBSY:  // Text file busy
#ifdef EUNATCH
    case EUNATCH:  // Protocol driver not attached
#endif
      return StatusCode::kFailedPrecondition;
    case ENOSPC:  // No space left on device
#ifdef EDQUOT
    case EDQUOT:  // Disk quota exceeded
#endif
    case EMFILE:   // Too many open files
    case EMLINK:   // Too many links
    case ENFILE:   // Too many open files in system
    case ENOBUFS:  // No buffer space available
    case ENODATA:  // No message is available on the STREAM read queue
    case ENOMEM:   // Not enough space
    case ENOSR:    // No STREAM resources
#ifdef EUSERS
    case EUSERS:  // Too many users
#endif
      return StatusCode::kResourceExhausted;
#ifdef ECHRNG
    case ECHRNG:  // Channel number out of range
#endif
    case EFBIG:      // File too large
    case EOVERFLOW:  // Value too large to be stored in data type
    case ERANGE:     // Result too large
      return StatusCode::kOutOfRange;
#ifdef ENOPKG
    case ENOPKG:  // Package not installed
#endif
    case ENOSYS:        // Function not implemented
    case ENOTSUP:       // Operation not supported
    case EAFNOSUPPORT:  // Address family not supported
#ifdef EPFNOSUPPORT
    case EPFNOSUPPORT:  // Protocol family not supported
#endif
    case EPROTONOSUPPORT:  // Protocol not supported
#ifdef ESOCKTNOSUPPORT
    case ESOCKTNOSUPPORT:  // Socket type not supported
#endif
    case EXDEV:  // Improper link
      return StatusCode::kUnimplemented;
    case EAGAIN:  // Resource temporarily unavailable
#ifdef ECOMM
    case ECOMM:  // Communication error on send
#endif
    case ECONNREFUSED:  // Connection refused
    case ECONNABORTED:  // Connection aborted
    case ECONNRESET:    // Connection reset
    case EINTR:         // Interrupted function call
#ifdef EHOSTDOWN
    case EHOSTDOWN:  // Host is down
#endif
    case EHOSTUNREACH:  // Host is unreachable
    case ENETDOWN:      // Network is down
    case ENETRESET:     // Connection aborted by network
    case ENETUNREACH:   // Network unreachable
    case ENOLCK:        // No locks available
    case ENOLINK:       // Link has been severed
#ifdef ENONET
    case ENONET:  // Machine is not on the network
#endif
      return StatusCode::kUnavailable;
    case EDEADLK:  // Resource deadlock avoided
#ifdef ESTALE
    case ESTALE:  // Stale file handle
#endif
      return StatusCode::kAborted;
    case ECANCELED:  // Operation cancelled
      return StatusCode::kCancelled;
    default:
      return StatusCode::kUnknown;
  }
}

namespace {
ABSEIL_EXPORT std::string MessageForErrnoToStatus(int error_number,
                                    absl::string_view message) {
  return absl::StrCat(message, ": ",
                      absl::base_internal::StrError(error_number));
}
}  // namespace

ABSEIL_EXPORT Status ErrnoToStatus(int error_number, absl::string_view message) {
  return Status(ErrnoToStatusCode(error_number),
                MessageForErrnoToStatus(error_number, message));
}

absl::Nonnull<const char*> StatusMessageAsCStr(const Status& status) {
  // As an internal implementation detail, we guarantee that if status.message()
  // is non-empty, then the resulting string_view is null terminated.
  auto sv_message = status.message();
  return sv_message.empty() ? "" : sv_message.data();
}

ABSL_NAMESPACE_END
}  // namespace absl
