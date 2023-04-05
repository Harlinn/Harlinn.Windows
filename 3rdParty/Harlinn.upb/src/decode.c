/*
 * Copyright (c) 2009-2021, Google LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Google LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "upb/decode.h"

#include <setjmp.h>
#include <string.h>

#include "upb/decode_internal.h"
#include "upb/upb.h"
#include "upb/upb_internal.h"

/* Must be last. */
#include "upb/port_def.inc"

/* Maps descriptor type -> elem_size_lg2.  */
static const uint8_t desctype_to_elem_size_lg2[] = {
    -1,               /* invalid descriptor type */
    3,  /* DOUBLE */
    2,   /* FLOAT */
    3,   /* INT64 */
    3,  /* UINT64 */
    2,   /* INT32 */
    3,  /* FIXED64 */
    2,  /* FIXED32 */
    0,    /* BOOL */
    UPB_SIZE(3, 4),  /* STRING */
    UPB_SIZE(2, 3),  /* GROUP */
    UPB_SIZE(2, 3),  /* MESSAGE */
    UPB_SIZE(3, 4),  /* BYTES */
    2,  /* UINT32 */
    2,    /* ENUM */
    2,   /* SFIXED32 */
    3,   /* SFIXED64 */
    2,   /* SINT32 */
    3,   /* SINT64 */
};

/* Maps descriptor type -> upb map size.  */
static const uint8_t desctype_to_mapsize[] = {
    -1,                 /* invalid descriptor type */
    8,                  /* DOUBLE */
    4,                  /* FLOAT */
    8,                  /* INT64 */
    8,                  /* UINT64 */
    4,                  /* INT32 */
    8,                  /* FIXED64 */
    4,                  /* FIXED32 */
    1,                  /* BOOL */
    UPB_MAPTYPE_STRING, /* STRING */
    sizeof(void *),     /* GROUP */
    sizeof(void *),     /* MESSAGE */
    UPB_MAPTYPE_STRING, /* BYTES */
    4,                  /* UINT32 */
    4,                  /* ENUM */
    4,                  /* SFIXED32 */
    8,                  /* SFIXED64 */
    4,                  /* SINT32 */
    8,                  /* SINT64 */
};

static const unsigned FIXED32_OK_MASK = (1 << UPB_DTYPE_FLOAT) |
                                        (1 << UPB_DTYPE_FIXED32) |
                                        (1 << UPB_DTYPE_SFIXED32);

static const unsigned FIXED64_OK_MASK = (1 << UPB_DTYPE_DOUBLE) |
                                        (1 << UPB_DTYPE_FIXED64) |
                                        (1 << UPB_DTYPE_SFIXED64);

/* Three fake field types for MessageSet. */
#define TYPE_MSGSET_ITEM 19
#define TYPE_MSGSET_TYPE_ID 20
#define TYPE_COUNT 20

/* Op: an action to be performed for a wire-type/field-type combination. */
#define OP_UNKNOWN -1             /* Unknown field. */
#define OP_MSGSET_ITEM -2
#define OP_MSGSET_TYPEID -3
#define OP_SCALAR_LG2(n) (n)      /* n in [0, 2, 3] => op in [0, 2, 3] */
#define OP_ENUM 1
#define OP_STRING 4
#define OP_BYTES 5
#define OP_SUBMSG 6
/* Scalar fields use only ops above. Repeated fields can use any op.  */
#define OP_FIXPCK_LG2(n) (n + 5)  /* n in [2, 3] => op in [7, 8] */
#define OP_VARPCK_LG2(n) (n + 9)  /* n in [0, 2, 3] => op in [9, 11, 12] */
#define OP_PACKED_ENUM 13

static const int8_t varint_ops[] = {
    OP_UNKNOWN,       /* field not found */
    OP_UNKNOWN,       /* DOUBLE */
    OP_UNKNOWN,       /* FLOAT */
    OP_SCALAR_LG2(3), /* INT64 */
    OP_SCALAR_LG2(3), /* UINT64 */
    OP_SCALAR_LG2(2), /* INT32 */
    OP_UNKNOWN,       /* FIXED64 */
    OP_UNKNOWN,       /* FIXED32 */
    OP_SCALAR_LG2(0), /* BOOL */
    OP_UNKNOWN,       /* STRING */
    OP_UNKNOWN,       /* GROUP */
    OP_UNKNOWN,       /* MESSAGE */
    OP_UNKNOWN,       /* BYTES */
    OP_SCALAR_LG2(2), /* UINT32 */
    OP_ENUM,          /* ENUM */
    OP_UNKNOWN,       /* SFIXED32 */
    OP_UNKNOWN,       /* SFIXED64 */
    OP_SCALAR_LG2(2), /* SINT32 */
    OP_SCALAR_LG2(3), /* SINT64 */
    OP_UNKNOWN,       /* MSGSET_ITEM */
    OP_MSGSET_TYPEID, /* MSGSET TYPEID */
};

static const int8_t delim_ops[] = {
    /* For non-repeated field type. */
    OP_UNKNOWN,       /* field not found */
    OP_UNKNOWN,       /* DOUBLE */
    OP_UNKNOWN,       /* FLOAT */
    OP_UNKNOWN,       /* INT64 */
    OP_UNKNOWN,       /* UINT64 */
    OP_UNKNOWN,       /* INT32 */
    OP_UNKNOWN,       /* FIXED64 */
    OP_UNKNOWN,       /* FIXED32 */
    OP_UNKNOWN,       /* BOOL */
    OP_STRING,        /* STRING */
    OP_UNKNOWN,       /* GROUP */
    OP_SUBMSG,        /* MESSAGE */
    OP_BYTES,         /* BYTES */
    OP_UNKNOWN,       /* UINT32 */
    OP_UNKNOWN,       /* ENUM */
    OP_UNKNOWN,       /* SFIXED32 */
    OP_UNKNOWN,       /* SFIXED64 */
    OP_UNKNOWN,       /* SINT32 */
    OP_UNKNOWN,       /* SINT64 */
    OP_UNKNOWN,       /* MSGSET_ITEM */
    OP_UNKNOWN,       /* MSGSET TYPEID */
    /* For repeated field type. */
    OP_FIXPCK_LG2(3), /* REPEATED DOUBLE */
    OP_FIXPCK_LG2(2), /* REPEATED FLOAT */
    OP_VARPCK_LG2(3), /* REPEATED INT64 */
    OP_VARPCK_LG2(3), /* REPEATED UINT64 */
    OP_VARPCK_LG2(2), /* REPEATED INT32 */
    OP_FIXPCK_LG2(3), /* REPEATED FIXED64 */
    OP_FIXPCK_LG2(2), /* REPEATED FIXED32 */
    OP_VARPCK_LG2(0), /* REPEATED BOOL */
    OP_STRING,        /* REPEATED STRING */
    OP_SUBMSG,        /* REPEATED GROUP */
    OP_SUBMSG,        /* REPEATED MESSAGE */
    OP_BYTES,         /* REPEATED BYTES */
    OP_VARPCK_LG2(2), /* REPEATED UINT32 */
    OP_PACKED_ENUM,   /* REPEATED ENUM */
    OP_FIXPCK_LG2(2), /* REPEATED SFIXED32 */
    OP_FIXPCK_LG2(3), /* REPEATED SFIXED64 */
    OP_VARPCK_LG2(2), /* REPEATED SINT32 */
    OP_VARPCK_LG2(3), /* REPEATED SINT64 */
    /* Omitting MSGSET_*, because we never emit a repeated msgset type */
};

typedef union {
  bool bool_val;
  uint32_t uint32_val;
  uint64_t uint64_val;
  uint32_t size;
} wireval;

static const char *decode_msg(upb_decstate *d, const char *ptr, upb_msg *msg,
                              const upb_msglayout *layout);

UPB_NORETURN static void *decode_err(upb_decstate *d, upb_DecodeStatus status) {
  assert(status != kUpb_DecodeStatus_Ok);
  UPB_LONGJMP(d->err, status);
}

const char *fastdecode_err(upb_decstate *d, int status) {
  assert(status != kUpb_DecodeStatus_Ok);
  UPB_LONGJMP(d->err, status);
  return NULL;
}
static void decode_verifyutf8(upb_decstate *d, const char *buf, int len) {
  if (!decode_verifyutf8_inl(buf, len)) decode_err(d, kUpb_DecodeStatus_BadUtf8);
}

static bool decode_reserve(upb_decstate *d, upb_array *arr, size_t elem) {
  bool need_realloc = arr->size - arr->len < elem;
  if (need_realloc && !_upb_array_realloc(arr, arr->len + elem, &d->arena)) {
    decode_err(d, kUpb_DecodeStatus_OutOfMemory);
  }
  return need_realloc;
}

typedef struct {
  const char *ptr;
  uint64_t val;
} decode_vret;

UPB_NOINLINE
static decode_vret decode_longvarint64(const char *ptr, uint64_t val) {
  decode_vret ret = {NULL, 0};
  uint64_t byte;
  int i;
  for (i = 1; i < 10; i++) {
    byte = (uint8_t)ptr[i];
    val += (byte - 1) << (i * 7);
    if (!(byte & 0x80)) {
      ret.ptr = ptr + i + 1;
      ret.val = val;
      return ret;
    }
  }
  return ret;
}

UPB_FORCEINLINE
static const char *decode_varint64(upb_decstate *d, const char *ptr,
                                   uint64_t *val) {
  uint64_t byte = (uint8_t)*ptr;
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = byte;
    return ptr + 1;
  } else {
    decode_vret res = decode_longvarint64(ptr, byte);
    if (!res.ptr) return decode_err(d, kUpb_DecodeStatus_Malformed);
    *val = res.val;
    return res.ptr;
  }
}

UPB_FORCEINLINE
static const char *decode_tag(upb_decstate *d, const char *ptr, uint32_t *val) {
  uint64_t byte = (uint8_t)*ptr;
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = byte;
    return ptr + 1;
  } else {
    const char *start = ptr;
    decode_vret res = decode_longvarint64(ptr, byte);
    if (!res.ptr || res.ptr - start > 5 || res.val > UINT32_MAX) {
      return decode_err(d, kUpb_DecodeStatus_Malformed);
    }
    *val = res.val;
    return res.ptr;
  }
}

static void decode_munge(int type, wireval *val) {
  switch (type) {
    case UPB_DESCRIPTOR_TYPE_BOOL:
      val->bool_val = val->uint64_val != 0;
      break;
    case UPB_DESCRIPTOR_TYPE_SINT32: {
      uint32_t n = val->uint32_val;
      val->uint32_val = (n >> 1) ^ -(int32_t)(n & 1);
      break;
    }
    case UPB_DESCRIPTOR_TYPE_SINT64: {
      uint64_t n = val->uint64_val;
      val->uint64_val = (n >> 1) ^ -(int64_t)(n & 1);
      break;
    }
    case UPB_DESCRIPTOR_TYPE_INT32:
    case UPB_DESCRIPTOR_TYPE_UINT32:
      if (!_upb_isle()) {
        /* The next stage will memcpy(dst, &val, 4) */
        val->uint32_val = val->uint64_val;
      }
      break;
  }
}

static upb_msg *decode_newsubmsg(upb_decstate *d, const upb_msglayout_sub *subs,
                                 const upb_msglayout_field *field) {
  const upb_msglayout *subl = subs[field->submsg_index].submsg;
  return _upb_msg_new_inl(subl, &d->arena);
}

UPB_NOINLINE
const char *decode_isdonefallback(upb_decstate *d, const char *ptr,
                                  int overrun) {
  int status; 
  ptr = decode_isdonefallback_inl(d, ptr, overrun, &status);
  if (ptr == NULL) {
    return decode_err(d, status);
  }
  return ptr;
}

static const char *decode_readstr(upb_decstate *d, const char *ptr, int size,
                                  upb_strview *str) {
  if (d->options & kUpb_DecodeOption_AliasString) {
    str->data = ptr;
  } else {
    char *data =  upb_arena_malloc(&d->arena, size);
    if (!data) return decode_err(d, kUpb_DecodeStatus_OutOfMemory);
    memcpy(data, ptr, size);
    str->data = data;
  }
  str->size = size;
  return ptr + size;
}

UPB_FORCEINLINE
static const char *decode_tosubmsg2(upb_decstate *d, const char *ptr,
                                    upb_msg *submsg, const upb_msglayout *subl,
                                    int size) {
  int saved_delta = decode_pushlimit(d, ptr, size);
  if (--d->depth < 0) return decode_err(d, kUpb_DecodeStatus_MaxDepthExceeded);
  ptr = decode_msg(d, ptr, submsg, subl);
  if (d->end_group != DECODE_NOGROUP) return decode_err(d, kUpb_DecodeStatus_Malformed);
  decode_poplimit(d, ptr, saved_delta);
  d->depth++;
  return ptr;
}

UPB_FORCEINLINE
static const char *decode_tosubmsg(upb_decstate *d, const char *ptr,
                                   upb_msg *submsg,
                                   const upb_msglayout_sub *subs,
                                   const upb_msglayout_field *field, int size) {
  return decode_tosubmsg2(d, ptr, submsg, subs[field->submsg_index].submsg,
                          size);
}

UPB_FORCEINLINE
static const char *decode_group(upb_decstate *d, const char *ptr,
                                upb_msg *submsg, const upb_msglayout *subl,
                                uint32_t number) {
  if (--d->depth < 0) return decode_err(d, kUpb_DecodeStatus_MaxDepthExceeded);
  if (decode_isdone(d, &ptr)) {
    return decode_err(d, kUpb_DecodeStatus_Malformed);
  }
  ptr = decode_msg(d, ptr, submsg, subl);
  if (d->end_group != number) return decode_err(d, kUpb_DecodeStatus_Malformed);
  d->end_group = DECODE_NOGROUP;
  d->depth++;
  return ptr;
}

UPB_FORCEINLINE
static const char *decode_togroup(upb_decstate *d, const char *ptr,
                                  upb_msg *submsg,
                                  const upb_msglayout_sub *subs,
                                  const upb_msglayout_field *field) {
  const upb_msglayout *subl = subs[field->submsg_index].submsg;
  return decode_group(d, ptr, submsg, subl, field->number);
}

static char *encode_varint32(uint32_t val, char *ptr) {
  do {
    uint8_t byte = val & 0x7fU;
    val >>= 7;
    if (val) byte |= 0x80U;
    *(ptr++) = byte;
  } while (val);
  return ptr;
}

UPB_NOINLINE
static bool decode_checkenum_slow(upb_decstate *d, const char *ptr, upb_msg *msg,
                             const upb_enumlayout *e,
                             const upb_msglayout_field *field, uint32_t v) {
  // OPT: binary search long lists?
  int n = e->value_count;
  for (int i = 0; i < n; i++) {
    if ((uint32_t)e->values[i] == v) return true;
  }

  // Unrecognized enum goes into unknown fields.
  // For packed fields the tag could be arbitrarily far in the past, so we
  // just re-encode the tag here.
  char buf[20];
  char *end = buf;
  uint32_t tag = ((uint32_t)field->number << 3) | UPB_WIRE_TYPE_VARINT;
  end = encode_varint32(tag, end);
  end = encode_varint32(v, end);

  if (!_upb_msg_addunknown(msg, buf, end - buf, &d->arena)) {
    decode_err(d, kUpb_DecodeStatus_OutOfMemory);
  }

  return false;
}

UPB_FORCEINLINE
static bool decode_checkenum(upb_decstate *d, const char *ptr, upb_msg *msg,
                             const upb_enumlayout *e,
                             const upb_msglayout_field *field, wireval *val) {
  uint32_t v = val->uint32_val;

  if (UPB_LIKELY(v < 64) && UPB_LIKELY(((1ULL << v) & e->mask))) return true;

  return decode_checkenum_slow(d, ptr, msg, e, field, v);
}

UPB_NOINLINE
static const char *decode_enum_toarray(upb_decstate *d, const char *ptr,
                                       upb_msg *msg, upb_array *arr,
                                       const upb_msglayout_sub *subs,
                                       const upb_msglayout_field *field,
                                       wireval *val) {
  const upb_enumlayout *e = subs[field->submsg_index].subenum;
  if (!decode_checkenum(d, ptr, msg, e, field, val)) return ptr;
  void *mem = UPB_PTR_AT(_upb_array_ptr(arr), arr->len * 4, void);
  arr->len++;
  memcpy(mem, val, 4);
  return ptr;
}

UPB_FORCEINLINE
static const char *decode_fixed_packed(upb_decstate *d, const char *ptr,
                                       upb_array *arr, wireval *val,
                                       const upb_msglayout_field *field,
                                       int lg2) {
  int mask = (1 << lg2) - 1;
  size_t count = val->size >> lg2;
  if ((val->size & mask) != 0) {
    // Length isn't a round multiple of elem size.
    return decode_err(d, kUpb_DecodeStatus_Malformed);
  }
  decode_reserve(d, arr, count);
  void *mem = UPB_PTR_AT(_upb_array_ptr(arr), arr->len << lg2, void);
  arr->len += count;
  // Note: if/when the decoder supports multi-buffer input, we will need to
  // handle buffer seams here.
  memcpy(mem, ptr, val->size);
  return ptr + val->size;
}

UPB_FORCEINLINE
static const char *decode_varint_packed(upb_decstate *d, const char *ptr,
                                        upb_array *arr, wireval *val,
                                        const upb_msglayout_field *field,
                                        int lg2) {
  int scale = 1 << lg2;
  int saved_limit = decode_pushlimit(d, ptr, val->size);
  char *out = UPB_PTR_AT(_upb_array_ptr(arr), arr->len << lg2, void);
  while (!decode_isdone(d, &ptr)) {
    wireval elem;
    ptr = decode_varint64(d, ptr, &elem.uint64_val);
    decode_munge(field->descriptortype, &elem);
    if (decode_reserve(d, arr, 1)) {
      out = UPB_PTR_AT(_upb_array_ptr(arr), arr->len << lg2, void);
    }
    arr->len++;
    memcpy(out, &elem, scale);
    out += scale;
  }
  decode_poplimit(d, ptr, saved_limit);
  return ptr;
}

UPB_NOINLINE
static const char *decode_enum_packed(upb_decstate *d, const char *ptr,
                                      upb_msg *msg, upb_array *arr,
                                      const upb_msglayout_sub *subs,
                                      const upb_msglayout_field *field,
                                      wireval *val) {
  const upb_enumlayout *e = subs[field->submsg_index].subenum;
  int saved_limit = decode_pushlimit(d, ptr, val->size);
  char *out = UPB_PTR_AT(_upb_array_ptr(arr), arr->len * 4, void);
  while (!decode_isdone(d, &ptr)) {
    wireval elem;
    ptr = decode_varint64(d, ptr, &elem.uint64_val);
    if (!decode_checkenum(d, ptr, msg, e, field, &elem)) {
      continue;
    }
    if (decode_reserve(d, arr, 1)) {
      out = UPB_PTR_AT(_upb_array_ptr(arr), arr->len * 4, void);
    }
    arr->len++;
    memcpy(out, &elem, 4);
    out += 4;
  }
  decode_poplimit(d, ptr, saved_limit);
  return ptr;
}

static const char *decode_toarray(upb_decstate *d, const char *ptr,
                                  upb_msg *msg,
                                  const upb_msglayout_sub *subs,
                                  const upb_msglayout_field *field, wireval *val,
                                  int op) {
  upb_array **arrp = UPB_PTR_AT(msg, field->offset, void);
  upb_array *arr = *arrp;
  void *mem;

  if (arr) {
    decode_reserve(d, arr, 1);
  } else {
    size_t lg2 = desctype_to_elem_size_lg2[field->descriptortype];
    arr = _upb_array_new(&d->arena, 4, lg2);
    if (!arr) return decode_err(d, kUpb_DecodeStatus_OutOfMemory);
    *arrp = arr;
  }

  switch (op) {
    case OP_SCALAR_LG2(0):
    case OP_SCALAR_LG2(2):
    case OP_SCALAR_LG2(3):
      /* Append scalar value. */
      mem = UPB_PTR_AT(_upb_array_ptr(arr), arr->len << op, void);
      arr->len++;
      memcpy(mem, val, 1 << op);
      return ptr;
    case OP_STRING:
      decode_verifyutf8(d, ptr, val->size);
      /* Fallthrough. */
    case OP_BYTES: {
      /* Append bytes. */
      upb_strview *str = (upb_strview*)_upb_array_ptr(arr) + arr->len;
      arr->len++;
      return decode_readstr(d, ptr, val->size, str);
    }
    case OP_SUBMSG: {
      /* Append submessage / group. */
      upb_msg *submsg = decode_newsubmsg(d, subs, field);
      *UPB_PTR_AT(_upb_array_ptr(arr), arr->len * sizeof(void *), upb_msg *) =
          submsg;
      arr->len++;
      if (UPB_UNLIKELY(field->descriptortype == UPB_DTYPE_GROUP)) {
        return decode_togroup(d, ptr, submsg, subs, field);
      } else {
        return decode_tosubmsg(d, ptr, submsg, subs, field, val->size);
      }
    }
    case OP_FIXPCK_LG2(2):
    case OP_FIXPCK_LG2(3):
      return decode_fixed_packed(d, ptr, arr, val, field,
                                 op - OP_FIXPCK_LG2(0));
    case OP_VARPCK_LG2(0):
    case OP_VARPCK_LG2(2):
    case OP_VARPCK_LG2(3):
      return decode_varint_packed(d, ptr, arr, val, field,
                                  op - OP_VARPCK_LG2(0));
    case OP_ENUM:
      return decode_enum_toarray(d, ptr, msg, arr, subs, field, val);
    case OP_PACKED_ENUM:
      return decode_enum_packed(d, ptr, msg, arr, subs, field, val);
    default:
      UPB_UNREACHABLE();
  }
}

static const char *decode_tomap(upb_decstate *d, const char *ptr, upb_msg *msg,
                                const upb_msglayout_sub *subs,
                                const upb_msglayout_field *field,
                                wireval *val) {
  upb_map **map_p = UPB_PTR_AT(msg, field->offset, upb_map *);
  upb_map *map = *map_p;
  upb_map_entry ent;
  const upb_msglayout *entry = subs[field->submsg_index].submsg;

  if (!map) {
    /* Lazily create map. */
    const upb_msglayout_field *key_field = &entry->fields[0];
    const upb_msglayout_field *val_field = &entry->fields[1];
    char key_size = desctype_to_mapsize[key_field->descriptortype];
    char val_size = desctype_to_mapsize[val_field->descriptortype];
    UPB_ASSERT(key_field->offset == 0);
    UPB_ASSERT(val_field->offset == sizeof(upb_strview));
    map = _upb_map_new(&d->arena, key_size, val_size);
    *map_p = map;
  }

  /* Parse map entry. */
  memset(&ent, 0, sizeof(ent));

  if (entry->fields[1].descriptortype == UPB_DESCRIPTOR_TYPE_MESSAGE ||
      entry->fields[1].descriptortype == UPB_DESCRIPTOR_TYPE_GROUP) {
    /* Create proactively to handle the case where it doesn't appear. */
    ent.v.val = upb_value_ptr(_upb_msg_new(entry->subs[0].submsg, &d->arena));
  }

  ptr = decode_tosubmsg(d, ptr, &ent.k, subs, field, val->size);
  _upb_map_set(map, &ent.k, map->key_size, &ent.v, map->val_size, &d->arena);
  return ptr;
}

static const char *decode_tomsg(upb_decstate *d, const char *ptr, upb_msg *msg,
                                const upb_msglayout_sub *subs,
                                const upb_msglayout_field *field, wireval *val,
                                int op) {
  void *mem = UPB_PTR_AT(msg, field->offset, void);
  int type = field->descriptortype;

  if (UPB_UNLIKELY(op == OP_ENUM) &&
      !decode_checkenum(d, ptr, msg, subs[field->submsg_index].subenum, field,
                        val)) {
    return ptr;
  }

  /* Set presence if necessary. */
  if (field->presence > 0) {
    _upb_sethas_field(msg, field);
  } else if (field->presence < 0) {
    /* Oneof case */
    uint32_t *oneof_case = _upb_oneofcase_field(msg, field);
    if (op == OP_SUBMSG && *oneof_case != field->number) {
      memset(mem, 0, sizeof(void*));
    }
    *oneof_case = field->number;
  }

  /* Store into message. */
  switch (op) {
    case OP_SUBMSG: {
      upb_msg **submsgp = mem;
      upb_msg *submsg = *submsgp;
      if (!submsg) {
        submsg = decode_newsubmsg(d, subs, field);
        *submsgp = submsg;
      }
      if (UPB_UNLIKELY(type == UPB_DTYPE_GROUP)) {
        ptr = decode_togroup(d, ptr, submsg, subs, field);
      } else {
        ptr = decode_tosubmsg(d, ptr, submsg, subs, field, val->size);
      }
      break;
    }
    case OP_STRING:
      decode_verifyutf8(d, ptr, val->size);
      /* Fallthrough. */
    case OP_BYTES:
      return decode_readstr(d, ptr, val->size, mem);
    case OP_SCALAR_LG2(3):
      memcpy(mem, val, 8);
      break;
    case OP_ENUM:
    case OP_SCALAR_LG2(2):
      memcpy(mem, val, 4);
      break;
    case OP_SCALAR_LG2(0):
      memcpy(mem, val, 1);
      break;
    default:
      UPB_UNREACHABLE();
  }

  return ptr;
}

// Computes a bitmask in which the |n| lowest bits are set, except that we
// skip the lowest bit (because upb never uses hasbit 0).
//
// Sample output:
//    decode_requiredmask(1) => 0b10 (0x2)
//    decode_requiredmask(5) => 0b111110 (0x3e)
uint64_t decode_requiredmask(int n) {
  assert(0 < n && n < 63);
  return ((1 << n) - 1) << 1;
}

UPB_NOINLINE
const char *decode_checkrequired(upb_decstate *d, const char *ptr,
                                 const upb_msg *msg, const upb_msglayout *l) {
  assert(l->required_count);
  if (UPB_LIKELY((d->options & kUpb_DecodeOption_CheckRequired) == 0)) {
    return ptr;
  }
  uint64_t msg_head;
  memcpy(&msg_head, msg, 8);
  msg_head = _upb_be_swap64(msg_head);
  if (decode_requiredmask(l->required_count) & ~msg_head) {
    d->missing_required = true;
  }
  return ptr;
}

UPB_FORCEINLINE
static bool decode_tryfastdispatch(upb_decstate *d, const char **ptr,
                                   upb_msg *msg, const upb_msglayout *layout) {
#if UPB_FASTTABLE
  if (layout && layout->table_mask != (unsigned char)-1) {
    uint16_t tag = fastdecode_loadtag(*ptr);
    intptr_t table = decode_totable(layout);
    *ptr = fastdecode_tagdispatch(d, *ptr, msg, table, 0, tag);
    return true;
  }
#endif
  return false;
}

static const char *decode_msgset(upb_decstate *d, const char *ptr, upb_msg *msg,
                                 const upb_msglayout *layout) {
  // We create a temporary upb_msglayout here and abuse its fields as temporary
  // storage, to avoid creating lots of MessageSet-specific parsing code-paths:
  //   1. We store 'layout' in item_layout.subs.  We will need this later as
  //      a key to look up extensions for this MessageSet.
  //   2. We use item_layout.fields as temporary storage to store the extension we
  //      found when parsing the type id.
  upb_msglayout item_layout = {
      .subs = (const upb_msglayout_sub[]){{.submsg = layout}},
      .fields = NULL,
      .size = 0,
      .field_count = 0,
      .ext = _UPB_MSGEXT_MSGSET_ITEM,
      .dense_below = 0,
      .table_mask = -1};
  return decode_group(d, ptr, msg, &item_layout, 1);
}

static const upb_msglayout_field *decode_findfield(upb_decstate *d,
                                                   const upb_msglayout *l,
                                                   uint32_t field_number,
                                                   int *last_field_index) {
  static upb_msglayout_field none = {0, 0, 0, 0, 0, 0};
  if (l == NULL) return &none;

  size_t idx = ((size_t)field_number) - 1;  // 0 wraps to SIZE_MAX
  if (idx < l->dense_below) {
    /* Fastest case: index into dense fields. */
    goto found;
  }

  if (l->dense_below < l->field_count) {
    /* Linear search non-dense fields. Resume scanning from last_field_index
     * since fields are usually in order. */
    int last = *last_field_index;
    for (idx = last; idx < l->field_count; idx++) {
      if (l->fields[idx].number == field_number) {
        goto found;
      }
    }

    for (idx = l->dense_below; idx < last; idx++) {
      if (l->fields[idx].number == field_number) {
        goto found;
      }
    }
  }

  if (d->extreg) {
    switch (l->ext) {
      case _UPB_MSGEXT_EXTENDABLE: {
        const upb_msglayout_ext *ext =
            _upb_extreg_get(d->extreg, l, field_number);
        if (ext) return &ext->field;
        break;
      }
      case _UPB_MSGEXT_MSGSET:
        if (field_number == _UPB_MSGSET_ITEM) {
          static upb_msglayout_field item = {0, 0, 0, 0, TYPE_MSGSET_ITEM, 0};
          return &item;
        }
        break;
      case _UPB_MSGEXT_MSGSET_ITEM:
        switch (field_number) {
          case _UPB_MSGSET_TYPEID: {
            static upb_msglayout_field type_id = {
                0, 0, 0, 0, TYPE_MSGSET_TYPE_ID, 0};
            return &type_id;
          }
          case _UPB_MSGSET_MESSAGE:
            if (l->fields) {
              // We saw type_id previously and succeeded in looking up msg.
              return l->fields;
            } else {
              // TODO: out of order MessageSet.
              // This is a very rare case: all serializers will emit in-order
              // MessageSets.  To hit this case there has to be some kind of
              // re-ordering proxy.  We should eventually handle this case, but
              // not today.
            }
            break;
        }
    }
  }

  return &none; /* Unknown field. */

 found:
  UPB_ASSERT(l->fields[idx].number == field_number);
  *last_field_index = idx;
  return &l->fields[idx];
 }

UPB_FORCEINLINE
static const char *decode_wireval(upb_decstate *d, const char *ptr,
                                  const upb_msglayout_field *field,
                                  int wire_type, wireval *val, int *op) {
  switch (wire_type) {
    case UPB_WIRE_TYPE_VARINT:
      ptr = decode_varint64(d, ptr, &val->uint64_val);
      *op = varint_ops[field->descriptortype];
      decode_munge(field->descriptortype, val);
      return ptr;
    case UPB_WIRE_TYPE_32BIT:
      memcpy(&val->uint32_val, ptr, 4);
      val->uint32_val = _upb_be_swap32(val->uint32_val);
      *op = OP_SCALAR_LG2(2);
      if (((1 << field->descriptortype) & FIXED32_OK_MASK) == 0) {
        *op = OP_UNKNOWN;
      }
      return ptr + 4;
    case UPB_WIRE_TYPE_64BIT:
      memcpy(&val->uint64_val, ptr, 8);
      val->uint64_val = _upb_be_swap64(val->uint64_val);
      *op = OP_SCALAR_LG2(3);
      if (((1 << field->descriptortype) & FIXED64_OK_MASK) == 0) {
        *op = OP_UNKNOWN;
      }
      return ptr + 8;
    case UPB_WIRE_TYPE_DELIMITED: {
      int ndx = field->descriptortype;
      uint64_t size;
      if (_upb_getmode(field) == _UPB_MODE_ARRAY) ndx += TYPE_COUNT;
      ptr = decode_varint64(d, ptr, &size);
      if (size >= INT32_MAX || ptr - d->end + (int32_t)size > d->limit) {
        break; /* Length overflow. */
      }
      *op = delim_ops[ndx];
      val->size = size;
      return ptr;
    }
    case UPB_WIRE_TYPE_START_GROUP:
      val->uint32_val = field->number;
      if (field->descriptortype == UPB_DTYPE_GROUP) {
        *op = OP_SUBMSG;
      } else if (field->descriptortype == TYPE_MSGSET_ITEM) {
        *op = OP_MSGSET_ITEM;
      } else {
        *op = OP_UNKNOWN;
      }
      return ptr;
    default:
      break;
  }
  return decode_err(d, kUpb_DecodeStatus_Malformed);
}

UPB_FORCEINLINE
static const char *decode_known(upb_decstate *d, const char *ptr, upb_msg *msg,
                                const upb_msglayout *layout,
                                const upb_msglayout_field *field, int op,
                                wireval *val) {
  const upb_msglayout_sub *subs = layout->subs;
  uint8_t mode = field->mode;

  if (UPB_UNLIKELY(mode & _UPB_MODE_IS_EXTENSION)) {
    const upb_msglayout_ext *ext_layout = (const upb_msglayout_ext*)field;
    upb_msg_ext *ext = _upb_msg_getorcreateext(msg, ext_layout, &d->arena);
        if (UPB_UNLIKELY(!ext)) return decode_err(d, kUpb_DecodeStatus_OutOfMemory);
    msg = &ext->data;
    subs = &ext->ext->sub;
  }

  switch (mode & _UPB_MODE_MASK) {
    case _UPB_MODE_ARRAY:
      return decode_toarray(d, ptr, msg, subs, field, val, op);
    case _UPB_MODE_MAP:
      return decode_tomap(d, ptr, msg, subs, field, val);
    case _UPB_MODE_SCALAR:
      return decode_tomsg(d, ptr, msg, subs, field, val, op);
    default:
      UPB_UNREACHABLE();
  }
}

static const char *decode_reverse_skip_varint(const char *ptr, uint32_t val) {
  uint32_t seen = 0;
  do {
    ptr--;
    seen <<= 7;
    seen |= *ptr & 0x7f;
  } while (seen != val);
  return ptr;
}

static const char *decode_unknown(upb_decstate *d, const char *ptr,
                                  upb_msg *msg, int field_number, int wire_type,
                                  wireval val) {
  if (field_number == 0) return decode_err(d, kUpb_DecodeStatus_Malformed);

  // Since unknown fields are the uncommon case, we do a little extra work here
  // to walk backwards through the buffer to find the field start.  This frees
  // up a register in the fast paths (when the field is known), which leads to
  // significant speedups in benchmarks.
  const char *start = ptr;

  if (wire_type == UPB_WIRE_TYPE_DELIMITED) ptr += val.size;
  if (msg) {
    switch (wire_type) {
      case UPB_WIRE_TYPE_VARINT:
      case UPB_WIRE_TYPE_DELIMITED:
        start--;
        while (start[-1] & 0x80) start--;
        break;
      case UPB_WIRE_TYPE_32BIT:
        start -= 4;
        break;
      case UPB_WIRE_TYPE_64BIT:
        start -= 8;
        break;
      default:
        break;
    }

    assert(start == d->debug_valstart);
    uint32_t tag = ((uint32_t)field_number << 3) | wire_type;
    start = decode_reverse_skip_varint(start, tag);
    assert(start == d->debug_tagstart);

    if (wire_type == UPB_WIRE_TYPE_START_GROUP) {
      d->unknown = start;
      d->unknown_msg = msg;
      ptr = decode_group(d, ptr, NULL, NULL, field_number);
      start = d->unknown;
      d->unknown_msg = NULL;
      d->unknown = NULL;
    }
    if (!_upb_msg_addunknown(msg, start, ptr - start, &d->arena)) {
      return decode_err(d, kUpb_DecodeStatus_OutOfMemory);
    }
  } else if (wire_type == UPB_WIRE_TYPE_START_GROUP) {
    ptr = decode_group(d, ptr, NULL, NULL, field_number);
  }
  return ptr;
}

UPB_NOINLINE
static const char *decode_msg(upb_decstate *d, const char *ptr, upb_msg *msg,
                              const upb_msglayout *layout) {
  int last_field_index = 0;

#if UPB_FASTTABLE
  // The first time we want to skip fast dispatch, because we may have just been
  // invoked by the fast parser to handle a case that it bailed on.
  if (!decode_isdone(d, &ptr)) goto nofast;
#endif

  while (!decode_isdone(d, &ptr)) {
    uint32_t tag;
    const upb_msglayout_field *field;
    int field_number;
    int wire_type;
    wireval val;
    int op;

    if (decode_tryfastdispatch(d, &ptr, msg, layout)) break;

#if UPB_FASTTABLE
  nofast:
#endif

#ifndef NDEBUG
    d->debug_tagstart = ptr;
#endif

    UPB_ASSERT(ptr < d->limit_ptr);
    ptr = decode_tag(d, ptr, &tag);
    field_number = tag >> 3;
    wire_type = tag & 7;

#ifndef NDEBUG
    d->debug_valstart = ptr;
#endif

    if (wire_type == UPB_WIRE_TYPE_END_GROUP) {
      d->end_group = field_number;
      return ptr;
    }

    field = decode_findfield(d, layout, field_number, &last_field_index);
    ptr = decode_wireval(d, ptr, field, wire_type, &val, &op);

    if (op >= 0) {
      ptr = decode_known(d, ptr, msg, layout, field, op, &val);
    } else {
      switch (op) {
        case OP_UNKNOWN:
          ptr = decode_unknown(d, ptr, msg, field_number, wire_type, val);
          break;
        case OP_MSGSET_ITEM:
          ptr = decode_msgset(d, ptr, msg, layout);
          break;
        case OP_MSGSET_TYPEID: {
          const upb_msglayout_ext *ext = _upb_extreg_get(
              d->extreg, layout->subs[0].submsg, val.uint64_val);
          if (ext) ((upb_msglayout *)layout)->fields = &ext->field;
          break;
        }
      }
    }
  }

  return UPB_UNLIKELY(layout && layout->required_count)
             ? decode_checkrequired(d, ptr, msg, layout)
             : ptr;
}

const char *fastdecode_generic(struct upb_decstate *d, const char *ptr,
                               upb_msg *msg, intptr_t table, uint64_t hasbits,
                               uint64_t data) {
  (void)data;
  *(uint32_t*)msg |= hasbits;
  return decode_msg(d, ptr, msg, decode_totablep(table));
}

static upb_DecodeStatus decode_top(struct upb_decstate *d, const char *buf,
                                   void *msg, const upb_msglayout *l) {
  if (!decode_tryfastdispatch(d, &buf, msg, l)) {
    decode_msg(d, buf, msg, l);
  }
  if (d->end_group != DECODE_NOGROUP) return kUpb_DecodeStatus_Malformed;
  if (d->missing_required) return kUpb_DecodeStatus_MissingRequired;
  return kUpb_DecodeStatus_Ok;
}

upb_DecodeStatus _upb_decode(const char *buf, size_t size, void *msg,
                             const upb_msglayout *l, const upb_extreg *extreg,
                             int options, upb_arena *arena) {
  upb_decstate state;
  unsigned depth = (unsigned)options >> 16;

  if (size <= 16) {
    memset(&state.patch, 0, 32);
    memcpy(&state.patch, buf, size);
    buf = state.patch;
    state.end = buf + size;
    state.limit = 0;
    options &= ~kUpb_DecodeOption_AliasString;  // Can't alias patch buf.
  } else {
    state.end = buf + size - 16;
    state.limit = 16;
  }

  state.extreg = extreg;
  state.limit_ptr = state.end;
  state.unknown_msg = NULL;
  state.depth = depth ? depth : 64;
  state.end_group = DECODE_NOGROUP;
  state.options = (uint16_t)options;
  state.missing_required = false;
  state.arena.head = arena->head;
  state.arena.last_size = arena->last_size;
  state.arena.cleanup_metadata = arena->cleanup_metadata;
  state.arena.parent = arena;

  upb_DecodeStatus status = UPB_SETJMP(state.err);
  if (UPB_LIKELY(status == kUpb_DecodeStatus_Ok)) {
    status = decode_top(&state, buf, msg, l);
  }

  arena->head.ptr = state.arena.head.ptr;
  arena->head.end = state.arena.head.end;
  arena->cleanup_metadata = state.arena.cleanup_metadata;
  return status;
}

#undef OP_UNKNOWN
#undef OP_SKIP
#undef OP_SCALAR_LG2
#undef OP_FIXPCK_LG2
#undef OP_VARPCK_LG2
#undef OP_STRING
#undef OP_BYTES
#undef OP_SUBMSG
