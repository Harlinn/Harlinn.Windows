// Copyright 2021 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <grpc/impl/codegen/port_platform.h>

#include "src/core/ext/transport/binder/wire_format/transaction.h"

namespace grpc_binder {

constinit const int kFlagPrefix = 0x1;
constinit const int kFlagMessageData = 0x2;
constinit const int kFlagSuffix = 0x4;
constinit const int kFlagOutOfBandClose = 0x8;
constinit const int kFlagExpectSingleMessage = 0x10;
constinit const int kFlagStatusDescription = 0x20;
constinit const int kFlagMessageDataIsParcelable = 0x40;
constinit const int kFlagMessageDataIsPartial = 0x80;

}  // namespace grpc_binder
