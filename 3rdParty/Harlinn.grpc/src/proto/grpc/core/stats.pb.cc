// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: stats.proto

#include "stats.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace grpc {
namespace core {
constexpr Bucket::Bucket(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : start_(0)
  , count_(uint64_t{0u}){}
struct BucketDefaultTypeInternal {
  constexpr BucketDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~BucketDefaultTypeInternal() {}
  union {
    Bucket _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT BucketDefaultTypeInternal _Bucket_default_instance_;
constexpr Histogram::Histogram(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : buckets_(){}
struct HistogramDefaultTypeInternal {
  constexpr HistogramDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~HistogramDefaultTypeInternal() {}
  union {
    Histogram _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT HistogramDefaultTypeInternal _Histogram_default_instance_;
constexpr Metric::Metric(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , _oneof_case_{}{}
struct MetricDefaultTypeInternal {
  constexpr MetricDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MetricDefaultTypeInternal() {}
  union {
    Metric _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MetricDefaultTypeInternal _Metric_default_instance_;
constexpr Stats::Stats(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : metrics_(){}
struct StatsDefaultTypeInternal {
  constexpr StatsDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~StatsDefaultTypeInternal() {}
  union {
    Stats _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT StatsDefaultTypeInternal _Stats_default_instance_;
}  // namespace core
}  // namespace grpc
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_stats_2eproto[4];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_stats_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_stats_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_stats_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Bucket, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Bucket, start_),
  PROTOBUF_FIELD_OFFSET(::grpc::core::Bucket, count_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Histogram, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Histogram, buckets_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Metric, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Metric, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Metric, name_),
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::grpc::core::Metric, value_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Stats, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::grpc::core::Stats, metrics_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::grpc::core::Bucket)},
  { 7, -1, sizeof(::grpc::core::Histogram)},
  { 13, -1, sizeof(::grpc::core::Metric)},
  { 22, -1, sizeof(::grpc::core::Stats)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::grpc::core::_Bucket_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::grpc::core::_Histogram_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::grpc::core::_Metric_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::grpc::core::_Stats_default_instance_),
};

const char descriptor_table_protodef_stats_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013stats.proto\022\tgrpc.core\"&\n\006Bucket\022\r\n\005st"
  "art\030\001 \001(\001\022\r\n\005count\030\002 \001(\004\"/\n\tHistogram\022\"\n"
  "\007buckets\030\001 \003(\0132\021.grpc.core.Bucket\"[\n\006Met"
  "ric\022\014\n\004name\030\001 \001(\t\022\017\n\005count\030\n \001(\004H\000\022)\n\thi"
  "stogram\030\013 \001(\0132\024.grpc.core.HistogramH\000B\007\n"
  "\005value\"+\n\005Stats\022\"\n\007metrics\030\001 \003(\0132\021.grpc."
  "core.Metricb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_stats_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_stats_2eproto = {
  false, false, 259, descriptor_table_protodef_stats_2eproto, "stats.proto", 
  &descriptor_table_stats_2eproto_once, nullptr, 0, 4,
  schemas, file_default_instances, TableStruct_stats_2eproto::offsets,
  file_level_metadata_stats_2eproto, file_level_enum_descriptors_stats_2eproto, file_level_service_descriptors_stats_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_stats_2eproto_getter() {
  return &descriptor_table_stats_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_stats_2eproto(&descriptor_table_stats_2eproto);
namespace grpc {
namespace core {

// ===================================================================

class Bucket::_Internal {
 public:
};

Bucket::Bucket(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:grpc.core.Bucket)
}
Bucket::Bucket(const Bucket& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&start_, &from.start_,
    static_cast<size_t>(reinterpret_cast<char*>(&count_) -
    reinterpret_cast<char*>(&start_)) + sizeof(count_));
  // @@protoc_insertion_point(copy_constructor:grpc.core.Bucket)
}

inline void Bucket::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&start_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&count_) -
    reinterpret_cast<char*>(&start_)) + sizeof(count_));
}

Bucket::~Bucket() {
  // @@protoc_insertion_point(destructor:grpc.core.Bucket)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Bucket::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Bucket::ArenaDtor(void* object) {
  Bucket* _this = reinterpret_cast< Bucket* >(object);
  (void)_this;
}
void Bucket::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Bucket::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Bucket::Clear() {
// @@protoc_insertion_point(message_clear_start:grpc.core.Bucket)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&start_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&count_) -
      reinterpret_cast<char*>(&start_)) + sizeof(count_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Bucket::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // double start = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 9)) {
          start_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // uint64 count = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          count_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Bucket::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:grpc.core.Bucket)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double start = 1;
  if (!(this->_internal_start() <= 0 && this->_internal_start() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(1, this->_internal_start(), target);
  }

  // uint64 count = 2;
  if (this->_internal_count() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_count(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:grpc.core.Bucket)
  return target;
}

size_t Bucket::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:grpc.core.Bucket)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // double start = 1;
  if (!(this->_internal_start() <= 0 && this->_internal_start() >= 0)) {
    total_size += 1 + 8;
  }

  // uint64 count = 2;
  if (this->_internal_count() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_count());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Bucket::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Bucket::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Bucket::GetClassData() const { return &_class_data_; }

void Bucket::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Bucket *>(to)->MergeFrom(
      static_cast<const Bucket &>(from));
}


void Bucket::MergeFrom(const Bucket& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:grpc.core.Bucket)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!(from._internal_start() <= 0 && from._internal_start() >= 0)) {
    _internal_set_start(from._internal_start());
  }
  if (from._internal_count() != 0) {
    _internal_set_count(from._internal_count());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Bucket::CopyFrom(const Bucket& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:grpc.core.Bucket)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Bucket::IsInitialized() const {
  return true;
}

void Bucket::InternalSwap(Bucket* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Bucket, count_)
      + sizeof(Bucket::count_)
      - PROTOBUF_FIELD_OFFSET(Bucket, start_)>(
          reinterpret_cast<char*>(&start_),
          reinterpret_cast<char*>(&other->start_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Bucket::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_stats_2eproto_getter, &descriptor_table_stats_2eproto_once,
      file_level_metadata_stats_2eproto[0]);
}

// ===================================================================

class Histogram::_Internal {
 public:
};

Histogram::Histogram(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  buckets_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:grpc.core.Histogram)
}
Histogram::Histogram(const Histogram& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      buckets_(from.buckets_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:grpc.core.Histogram)
}

inline void Histogram::SharedCtor() {
}

Histogram::~Histogram() {
  // @@protoc_insertion_point(destructor:grpc.core.Histogram)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Histogram::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Histogram::ArenaDtor(void* object) {
  Histogram* _this = reinterpret_cast< Histogram* >(object);
  (void)_this;
}
void Histogram::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Histogram::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Histogram::Clear() {
// @@protoc_insertion_point(message_clear_start:grpc.core.Histogram)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  buckets_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Histogram::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .grpc.core.Bucket buckets = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_buckets(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Histogram::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:grpc.core.Histogram)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .grpc.core.Bucket buckets = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_buckets_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_buckets(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:grpc.core.Histogram)
  return target;
}

size_t Histogram::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:grpc.core.Histogram)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .grpc.core.Bucket buckets = 1;
  total_size += 1UL * this->_internal_buckets_size();
  for (const auto& msg : this->buckets_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Histogram::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Histogram::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Histogram::GetClassData() const { return &_class_data_; }

void Histogram::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Histogram *>(to)->MergeFrom(
      static_cast<const Histogram &>(from));
}


void Histogram::MergeFrom(const Histogram& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:grpc.core.Histogram)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  buckets_.MergeFrom(from.buckets_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Histogram::CopyFrom(const Histogram& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:grpc.core.Histogram)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Histogram::IsInitialized() const {
  return true;
}

void Histogram::InternalSwap(Histogram* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  buckets_.InternalSwap(&other->buckets_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Histogram::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_stats_2eproto_getter, &descriptor_table_stats_2eproto_once,
      file_level_metadata_stats_2eproto[1]);
}

// ===================================================================

class Metric::_Internal {
 public:
  static const ::grpc::core::Histogram& histogram(const Metric* msg);
};

const ::grpc::core::Histogram&
Metric::_Internal::histogram(const Metric* msg) {
  return *msg->value_.histogram_;
}
void Metric::set_allocated_histogram(::grpc::core::Histogram* histogram) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_value();
  if (histogram) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::grpc::core::Histogram>::GetOwningArena(histogram);
    if (message_arena != submessage_arena) {
      histogram = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, histogram, submessage_arena);
    }
    set_has_histogram();
    value_.histogram_ = histogram;
  }
  // @@protoc_insertion_point(field_set_allocated:grpc.core.Metric.histogram)
}
Metric::Metric(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:grpc.core.Metric)
}
Metric::Metric(const Metric& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_name().empty()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArenaForAllocation());
  }
  clear_has_value();
  switch (from.value_case()) {
    case kCount: {
      _internal_set_count(from._internal_count());
      break;
    }
    case kHistogram: {
      _internal_mutable_histogram()->::grpc::core::Histogram::MergeFrom(from._internal_histogram());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:grpc.core.Metric)
}

inline void Metric::SharedCtor() {
name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
clear_has_value();
}

Metric::~Metric() {
  // @@protoc_insertion_point(destructor:grpc.core.Metric)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Metric::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (has_value()) {
    clear_value();
  }
}

void Metric::ArenaDtor(void* object) {
  Metric* _this = reinterpret_cast< Metric* >(object);
  (void)_this;
}
void Metric::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Metric::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Metric::clear_value() {
// @@protoc_insertion_point(one_of_clear_start:grpc.core.Metric)
  switch (value_case()) {
    case kCount: {
      // No need to clear
      break;
    }
    case kHistogram: {
      if (GetArenaForAllocation() == nullptr) {
        delete value_.histogram_;
      }
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = VALUE_NOT_SET;
}


void Metric::Clear() {
// @@protoc_insertion_point(message_clear_start:grpc.core.Metric)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  name_.ClearToEmpty();
  clear_value();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Metric::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "grpc.core.Metric.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint64 count = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 80)) {
          _internal_set_count(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .grpc.core.Histogram histogram = 11;
      case 11:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 90)) {
          ptr = ctx->ParseMessage(_internal_mutable_histogram(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Metric::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:grpc.core.Metric)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "grpc.core.Metric.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  // uint64 count = 10;
  if (_internal_has_count()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(10, this->_internal_count(), target);
  }

  // .grpc.core.Histogram histogram = 11;
  if (_internal_has_histogram()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        11, _Internal::histogram(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:grpc.core.Metric)
  return target;
}

size_t Metric::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:grpc.core.Metric)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  switch (value_case()) {
    // uint64 count = 10;
    case kCount: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
          this->_internal_count());
      break;
    }
    // .grpc.core.Histogram histogram = 11;
    case kHistogram: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *value_.histogram_);
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Metric::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Metric::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Metric::GetClassData() const { return &_class_data_; }

void Metric::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Metric *>(to)->MergeFrom(
      static_cast<const Metric &>(from));
}


void Metric::MergeFrom(const Metric& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:grpc.core.Metric)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _internal_set_name(from._internal_name());
  }
  switch (from.value_case()) {
    case kCount: {
      _internal_set_count(from._internal_count());
      break;
    }
    case kHistogram: {
      _internal_mutable_histogram()->::grpc::core::Histogram::MergeFrom(from._internal_histogram());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Metric::CopyFrom(const Metric& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:grpc.core.Metric)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Metric::IsInitialized() const {
  return true;
}

void Metric::InternalSwap(Metric* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &name_, GetArenaForAllocation(),
      &other->name_, other->GetArenaForAllocation()
  );
  swap(value_, other->value_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata Metric::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_stats_2eproto_getter, &descriptor_table_stats_2eproto_once,
      file_level_metadata_stats_2eproto[2]);
}

// ===================================================================

class Stats::_Internal {
 public:
};

Stats::Stats(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  metrics_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:grpc.core.Stats)
}
Stats::Stats(const Stats& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      metrics_(from.metrics_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:grpc.core.Stats)
}

inline void Stats::SharedCtor() {
}

Stats::~Stats() {
  // @@protoc_insertion_point(destructor:grpc.core.Stats)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Stats::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Stats::ArenaDtor(void* object) {
  Stats* _this = reinterpret_cast< Stats* >(object);
  (void)_this;
}
void Stats::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Stats::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Stats::Clear() {
// @@protoc_insertion_point(message_clear_start:grpc.core.Stats)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  metrics_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Stats::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .grpc.core.Metric metrics = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_metrics(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Stats::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:grpc.core.Stats)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .grpc.core.Metric metrics = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_metrics_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_metrics(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:grpc.core.Stats)
  return target;
}

size_t Stats::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:grpc.core.Stats)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .grpc.core.Metric metrics = 1;
  total_size += 1UL * this->_internal_metrics_size();
  for (const auto& msg : this->metrics_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Stats::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Stats::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Stats::GetClassData() const { return &_class_data_; }

void Stats::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Stats *>(to)->MergeFrom(
      static_cast<const Stats &>(from));
}


void Stats::MergeFrom(const Stats& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:grpc.core.Stats)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  metrics_.MergeFrom(from.metrics_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Stats::CopyFrom(const Stats& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:grpc.core.Stats)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Stats::IsInitialized() const {
  return true;
}

void Stats::InternalSwap(Stats* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  metrics_.InternalSwap(&other->metrics_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Stats::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_stats_2eproto_getter, &descriptor_table_stats_2eproto_once,
      file_level_metadata_stats_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace core
}  // namespace grpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::grpc::core::Bucket* Arena::CreateMaybeMessage< ::grpc::core::Bucket >(Arena* arena) {
  return Arena::CreateMessageInternal< ::grpc::core::Bucket >(arena);
}
template<> PROTOBUF_NOINLINE ::grpc::core::Histogram* Arena::CreateMaybeMessage< ::grpc::core::Histogram >(Arena* arena) {
  return Arena::CreateMessageInternal< ::grpc::core::Histogram >(arena);
}
template<> PROTOBUF_NOINLINE ::grpc::core::Metric* Arena::CreateMaybeMessage< ::grpc::core::Metric >(Arena* arena) {
  return Arena::CreateMessageInternal< ::grpc::core::Metric >(arena);
}
template<> PROTOBUF_NOINLINE ::grpc::core::Stats* Arena::CreateMaybeMessage< ::grpc::core::Stats >(Arena* arena) {
  return Arena::CreateMessageInternal< ::grpc::core::Stats >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>