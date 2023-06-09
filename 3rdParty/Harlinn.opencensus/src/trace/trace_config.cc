// Copyright 2017, OpenCensus Authors
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

#include "opencensus/trace/trace_config.h"
#include "opencensus/trace/trace_params.h"

#include "src/trace/trace_config_impl.h"


namespace opencensus {
namespace trace {

void TraceConfig::SetCurrentTraceParams(const TraceParams& params) {
  TraceConfigImpl::Get()->SetCurrentTraceParams(params);
}

}  // namespace trace
}  // namespace opencensus
