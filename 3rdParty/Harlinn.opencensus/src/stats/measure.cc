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

#include "opencensus/stats/measure.h"

#include "absl/strings/string_view.h"
#include "opencensus/stats/internal/measure_registry_impl.h"
#include "opencensus/stats/measure_registry.h"

namespace opencensus {
namespace stats {

/*
// static
template <typename MeasureT>
Measure<MeasureT> Measure<MeasureT>::Register(absl::string_view name,
                                              absl::string_view description,
                                              absl::string_view units) {
  return MeasureRegistryImpl::Get()->Register<MeasureT>(name, description,
                                                        units);
}

template <typename MeasureT>
const MeasureDescriptor& Measure<MeasureT>::GetDescriptor() const {
  return MeasureRegistryImpl::Get()->GetDescriptor(*this);
}
*/

template<>
OPENCENSUS_EXPORT Measure<double> Measure<double>::Register(absl::string_view name,
                                              absl::string_view description,
                                              absl::string_view units) {
  return MeasureRegistryImpl::Get()->Register<double>(name, description,
                                                        units);
}

template<>
OPENCENSUS_EXPORT const MeasureDescriptor& Measure<double>::GetDescriptor() const {
  return MeasureRegistryImpl::Get()->GetDescriptor(*this);
}

template<>
OPENCENSUS_EXPORT Measure<int64_t> Measure<int64_t>::Register( absl::string_view name,
    absl::string_view description,
    absl::string_view units )
{
    return MeasureRegistryImpl::Get( )->Register<int64_t>( name, description,
        units );
}

template<>
OPENCENSUS_EXPORT const MeasureDescriptor& Measure<int64_t>::GetDescriptor( ) const
{
    return MeasureRegistryImpl::Get( )->GetDescriptor( *this );
}



// This is specialized so that we can also check whether the type matches the
// template type, in case an otherwise-valid measure in a union is being
// accessed via the wrong type.
template <>
OPENCENSUS_EXPORT bool Measure<double>::IsValid() const {
  return MeasureRegistryImpl::IdValid(id_) &&
         MeasureRegistryImpl::IdToType(id_) == MeasureDescriptor::Type::kDouble;
}

template <>
OPENCENSUS_EXPORT bool MeasureInt64::IsValid() const {
  return MeasureRegistryImpl::IdValid(id_) &&
         MeasureRegistryImpl::IdToType(id_) == MeasureDescriptor::Type::kInt64;
}




}  // namespace stats
}  // namespace opencensus
