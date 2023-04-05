// Copyright (c) 2012 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS.  All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
#ifndef MKVPARSER_MKVPARSER_H_
#define MKVPARSER_MKVPARSER_H_

#include <cstddef>

#include <new>
#include "..\hwebmdef.h"

namespace mkvparser {

const int E_PARSE_FAILED = -1;
const int E_FILE_FORMAT_INVALID = -2;
const int E_BUFFER_NOT_FULL = -3;

class IMkvReader {
 public:
  virtual int Read(long long pos, long len, unsigned char* buf) = 0;
  virtual int Length(long long* total, long long* available) = 0;

 protected:
  virtual ~IMkvReader() {}
};

template <typename Type>
inline Type* SafeArrayAlloc( unsigned long long num_elements,
    unsigned long long element_size )
{
    if ( num_elements == 0 || element_size == 0 )
        return NULL;

    const size_t kMaxAllocSize = 0x80000000;  // 2GiB
    const unsigned long long num_bytes = num_elements * element_size;
    if ( element_size > ( kMaxAllocSize / num_elements ) )
        return NULL;
    if ( num_bytes != static_cast<size_t>( num_bytes ) )
        return NULL;

    return new ( std::nothrow ) Type[static_cast<size_t>( num_bytes )];
}

WEBM_EXPORT long long GetUIntLength(IMkvReader*, long long, long&);
WEBM_EXPORT long long ReadUInt(IMkvReader*, long long, long&);
WEBM_EXPORT long long ReadID(IMkvReader* pReader, long long pos, long& len);
WEBM_EXPORT long long UnserializeUInt(IMkvReader*, long long pos, long long size);

WEBM_EXPORT long UnserializeFloat(IMkvReader*, long long pos, long long size, double&);
WEBM_EXPORT long UnserializeInt(IMkvReader*, long long pos, long long size,
                    long long& result);

WEBM_EXPORT long UnserializeString(IMkvReader*, long long pos, long long size, char*& str);

WEBM_EXPORT long ParseElementHeader(IMkvReader* pReader,
                        long long& pos,  // consume id and size fields
                        long long stop,  // if you know size of element's parent
                        long long& id, long long& size);

WEBM_EXPORT bool Match(IMkvReader*, long long&, unsigned long, long long&);
WEBM_EXPORT bool Match(IMkvReader*, long long&, unsigned long, unsigned char*&, size_t&);

WEBM_EXPORT void GetVersion(int& major, int& minor, int& build, int& revision);

struct EBMLHeader {
  WEBM_EXPORT EBMLHeader();
  WEBM_EXPORT ~EBMLHeader();
  long long m_version;
  long long m_readVersion;
  long long m_maxIdLength;
  long long m_maxSizeLength;
  char* m_docType;
  long long m_docTypeVersion;
  long long m_docTypeReadVersion;

  WEBM_EXPORT long long Parse(IMkvReader*, long long&);
  WEBM_EXPORT void Init();
};

class Segment;
class Track;
class Cluster;

class Block {
  Block(const Block&);
  Block& operator=(const Block&);

 public:
  const long long m_start;
  const long long m_size;

  WEBM_EXPORT Block(long long start, long long size, long long discard_padding);
  WEBM_EXPORT ~Block();

  WEBM_EXPORT long Parse(const Cluster*);

  WEBM_EXPORT long long GetTrackNumber() const;
  WEBM_EXPORT long long GetTimeCode(const Cluster*) const;  // absolute, but not scaled
  WEBM_EXPORT long long GetTime(const Cluster*) const;  // absolute, and scaled (ns)
  WEBM_EXPORT bool IsKey() const;
  WEBM_EXPORT void SetKey(bool);
  WEBM_EXPORT bool IsInvisible() const;

  enum Lacing { kLacingNone, kLacingXiph, kLacingFixed, kLacingEbml };
  Lacing GetLacing() const;

  WEBM_EXPORT int GetFrameCount() const;  // to index frames: [0, count)

  struct Frame {
    long long pos;  // absolute offset
    long len;

    WEBM_EXPORT long Read(IMkvReader*, unsigned char*) const;
  };

  WEBM_EXPORT const Frame& GetFrame(int frame_index) const;

  WEBM_EXPORT long long GetDiscardPadding() const;

 private:
  long long m_track;  // Track::Number()
  short m_timecode;  // relative to cluster
  unsigned char m_flags;

  Frame* m_frames;
  int m_frame_count;

 protected:
  const long long m_discard_padding;
};

class BlockEntry {
  BlockEntry(const BlockEntry&);
  BlockEntry& operator=(const BlockEntry&);

 protected:
  WEBM_EXPORT BlockEntry(Cluster*, long index);

 public:
  WEBM_EXPORT virtual ~BlockEntry();

  bool EOS() const { return (GetKind() == kBlockEOS); }
  WEBM_EXPORT const Cluster* GetCluster() const;
  WEBM_EXPORT long GetIndex() const;
  virtual const Block* GetBlock() const = 0;

  enum Kind { kBlockEOS, kBlockSimple, kBlockGroup };
  virtual Kind GetKind() const = 0;

 protected:
  Cluster* const m_pCluster;
  const long m_index;
};

class SimpleBlock : public BlockEntry {
  SimpleBlock(const SimpleBlock&);
  SimpleBlock& operator=(const SimpleBlock&);

 public:
  WEBM_EXPORT SimpleBlock(Cluster*, long index, long long start, long long size);
  WEBM_EXPORT long Parse();

  WEBM_EXPORT Kind GetKind() const;
  WEBM_EXPORT const Block* GetBlock() const;

 protected:
  Block m_block;
};

class BlockGroup : public BlockEntry {
  BlockGroup(const BlockGroup&);
  BlockGroup& operator=(const BlockGroup&);

 public:
  WEBM_EXPORT BlockGroup(Cluster*, long index,
             long long block_start,  // absolute pos of block's payload
             long long block_size,  // size of block's payload
             long long prev, long long next, long long duration,
             long long discard_padding);

  WEBM_EXPORT long Parse();

  WEBM_EXPORT Kind GetKind() const;
  WEBM_EXPORT const Block* GetBlock() const;

  WEBM_EXPORT long long GetPrevTimeCode() const;  // relative to block's time
  WEBM_EXPORT long long GetNextTimeCode() const;  // as above
  WEBM_EXPORT long long GetDurationTimeCode() const;

 private:
  Block m_block;
  const long long m_prev;
  const long long m_next;
  const long long m_duration;
};

///////////////////////////////////////////////////////////////
// ContentEncoding element
// Elements used to describe if the track data has been encrypted or
// compressed with zlib or header stripping.
class ContentEncoding {
 public:
  enum { kCTR = 1 };

  WEBM_EXPORT ContentEncoding();
  WEBM_EXPORT ~ContentEncoding();

  // ContentCompression element names
  struct ContentCompression {
    WEBM_EXPORT ContentCompression();
    WEBM_EXPORT ~ContentCompression();

    unsigned long long algo;
    unsigned char* settings;
    long long settings_len;
  };

  // ContentEncAESSettings element names
  struct ContentEncAESSettings {
    ContentEncAESSettings() : cipher_mode(kCTR) {}
    ~ContentEncAESSettings() {}

    unsigned long long cipher_mode;
  };

  // ContentEncryption element names
  struct ContentEncryption {
    WEBM_EXPORT ContentEncryption();
    WEBM_EXPORT ~ContentEncryption();

    unsigned long long algo;
    unsigned char* key_id;
    long long key_id_len;
    unsigned char* signature;
    long long signature_len;
    unsigned char* sig_key_id;
    long long sig_key_id_len;
    unsigned long long sig_algo;
    unsigned long long sig_hash_algo;

    ContentEncAESSettings aes_settings;
  };

  // Returns ContentCompression represented by |idx|. Returns NULL if |idx|
  // is out of bounds.
  WEBM_EXPORT const ContentCompression* GetCompressionByIndex(unsigned long idx) const;

  // Returns number of ContentCompression elements in this ContentEncoding
  // element.
  WEBM_EXPORT unsigned long GetCompressionCount() const;

  // Parses the ContentCompression element from |pReader|. |start| is the
  // starting offset of the ContentCompression payload. |size| is the size in
  // bytes of the ContentCompression payload. |compression| is where the parsed
  // values will be stored.
  WEBM_EXPORT long ParseCompressionEntry(long long start, long long size,
                             IMkvReader* pReader,
                             ContentCompression* compression);

  // Returns ContentEncryption represented by |idx|. Returns NULL if |idx|
  // is out of bounds.
  WEBM_EXPORT const ContentEncryption* GetEncryptionByIndex(unsigned long idx) const;

  // Returns number of ContentEncryption elements in this ContentEncoding
  // element.
  WEBM_EXPORT unsigned long GetEncryptionCount() const;

  // Parses the ContentEncAESSettings element from |pReader|. |start| is the
  // starting offset of the ContentEncAESSettings payload. |size| is the
  // size in bytes of the ContentEncAESSettings payload. |encryption| is
  // where the parsed values will be stored.
  WEBM_EXPORT long ParseContentEncAESSettingsEntry(long long start, long long size,
                                       IMkvReader* pReader,
                                       ContentEncAESSettings* aes);

  // Parses the ContentEncoding element from |pReader|. |start| is the
  // starting offset of the ContentEncoding payload. |size| is the size in
  // bytes of the ContentEncoding payload. Returns true on success.
  WEBM_EXPORT long ParseContentEncodingEntry(long long start, long long size,
                                 IMkvReader* pReader);

  // Parses the ContentEncryption element from |pReader|. |start| is the
  // starting offset of the ContentEncryption payload. |size| is the size in
  // bytes of the ContentEncryption payload. |encryption| is where the parsed
  // values will be stored.
  WEBM_EXPORT long ParseEncryptionEntry(long long start, long long size,
                            IMkvReader* pReader, ContentEncryption* encryption);

  unsigned long long encoding_order() const { return encoding_order_; }
  unsigned long long encoding_scope() const { return encoding_scope_; }
  unsigned long long encoding_type() const { return encoding_type_; }

 private:
  // Member variables for list of ContentCompression elements.
  ContentCompression** compression_entries_;
  ContentCompression** compression_entries_end_;

  // Member variables for list of ContentEncryption elements.
  ContentEncryption** encryption_entries_;
  ContentEncryption** encryption_entries_end_;

  // ContentEncoding element names
  unsigned long long encoding_order_;
  unsigned long long encoding_scope_;
  unsigned long long encoding_type_;

  // LIBWEBM_DISALLOW_COPY_AND_ASSIGN(ContentEncoding);
  ContentEncoding(const ContentEncoding&);
  ContentEncoding& operator=(const ContentEncoding&);
};

class Track {
  Track(const Track&);
  Track& operator=(const Track&);

 public:
  class Info;
  WEBM_EXPORT static long Create(Segment*, const Info&, long long element_start,
                     long long element_size, Track*&);

  enum Type { kVideo = 1, kAudio = 2, kSubtitle = 0x11, kMetadata = 0x21 };

  Segment* const m_pSegment;
  const long long m_element_start;
  const long long m_element_size;
  WEBM_EXPORT virtual ~Track();

  WEBM_EXPORT long GetType() const;
  WEBM_EXPORT long GetNumber() const;
  WEBM_EXPORT unsigned long long GetUid() const;
  WEBM_EXPORT const char* GetNameAsUTF8() const;
  WEBM_EXPORT const char* GetLanguage() const;
  WEBM_EXPORT const char* GetCodecNameAsUTF8() const;
  WEBM_EXPORT const char* GetCodecId() const;
  WEBM_EXPORT const unsigned char* GetCodecPrivate(size_t&) const;
  WEBM_EXPORT bool GetLacing() const;
  WEBM_EXPORT unsigned long long GetDefaultDuration() const;
  WEBM_EXPORT unsigned long long GetCodecDelay() const;
  WEBM_EXPORT unsigned long long GetSeekPreRoll() const;

  WEBM_EXPORT const BlockEntry* GetEOS() const;

  struct Settings {
    long long start;
    long long size;
  };

  class Info {
   public:
    WEBM_EXPORT Info();
    WEBM_EXPORT ~Info();
    WEBM_EXPORT int Copy(Info&) const;
    WEBM_EXPORT void Clear();
    long type;
    long number;
    unsigned long long uid;
    unsigned long long defaultDuration;
    unsigned long long codecDelay;
    unsigned long long seekPreRoll;
    char* nameAsUTF8;
    char* language;
    char* codecId;
    char* codecNameAsUTF8;
    unsigned char* codecPrivate;
    size_t codecPrivateSize;
    bool lacing;
    Settings settings;

   private:
    Info(const Info&);
    Info& operator=(const Info&);
    WEBM_EXPORT int CopyStr(char* Info::*str, Info&) const;
  };

  WEBM_EXPORT long GetFirst(const BlockEntry*&) const;
  WEBM_EXPORT long GetNext(const BlockEntry* pCurr, const BlockEntry*& pNext) const;
  WEBM_EXPORT virtual bool VetEntry(const BlockEntry*) const;
  WEBM_EXPORT virtual long Seek(long long time_ns, const BlockEntry*&) const;

  WEBM_EXPORT const ContentEncoding* GetContentEncodingByIndex(unsigned long idx) const;
  WEBM_EXPORT unsigned long GetContentEncodingCount() const;

  WEBM_EXPORT long ParseContentEncodingsEntry(long long start, long long size);

 protected:
  WEBM_EXPORT Track(Segment*, long long element_start, long long element_size);

  Info m_info;

  class EOSBlock : public BlockEntry {
   public:
    WEBM_EXPORT EOSBlock();

    WEBM_EXPORT Kind GetKind() const;
    WEBM_EXPORT const Block* GetBlock() const;
  };

  EOSBlock m_eos;

 private:
  ContentEncoding** content_encoding_entries_;
  ContentEncoding** content_encoding_entries_end_;
};

struct PrimaryChromaticity {
  PrimaryChromaticity() : x(0), y(0) {}
  ~PrimaryChromaticity() {}
  WEBM_EXPORT static bool Parse(IMkvReader* reader, long long read_pos,
                    long long value_size, bool is_x,
                    PrimaryChromaticity** chromaticity);
  float x;
  float y;
};

struct MasteringMetadata {
  static const float kValueNotPresent;

  MasteringMetadata()
      : r(NULL),
        g(NULL),
        b(NULL),
        white_point(NULL),
        luminance_max(kValueNotPresent),
        luminance_min(kValueNotPresent) {}
  ~MasteringMetadata() {
    delete r;
    delete g;
    delete b;
    delete white_point;
  }

  WEBM_EXPORT static bool Parse(IMkvReader* reader, long long element_start,
                    long long element_size,
                    MasteringMetadata** mastering_metadata);

  PrimaryChromaticity* r;
  PrimaryChromaticity* g;
  PrimaryChromaticity* b;
  PrimaryChromaticity* white_point;
  float luminance_max;
  float luminance_min;
};

struct Colour {
  static const long long kValueNotPresent;

  // Unless otherwise noted all values assigned upon construction are the
  // equivalent of unspecified/default.
  Colour()
      : matrix_coefficients(kValueNotPresent),
        bits_per_channel(kValueNotPresent),
        chroma_subsampling_horz(kValueNotPresent),
        chroma_subsampling_vert(kValueNotPresent),
        cb_subsampling_horz(kValueNotPresent),
        cb_subsampling_vert(kValueNotPresent),
        chroma_siting_horz(kValueNotPresent),
        chroma_siting_vert(kValueNotPresent),
        range(kValueNotPresent),
        transfer_characteristics(kValueNotPresent),
        primaries(kValueNotPresent),
        max_cll(kValueNotPresent),
        max_fall(kValueNotPresent),
        mastering_metadata(NULL) {}
  ~Colour() {
    delete mastering_metadata;
    mastering_metadata = NULL;
  }

  WEBM_EXPORT static bool Parse(IMkvReader* reader, long long element_start,
                    long long element_size, Colour** colour);

  long long matrix_coefficients;
  long long bits_per_channel;
  long long chroma_subsampling_horz;
  long long chroma_subsampling_vert;
  long long cb_subsampling_horz;
  long long cb_subsampling_vert;
  long long chroma_siting_horz;
  long long chroma_siting_vert;
  long long range;
  long long transfer_characteristics;
  long long primaries;
  long long max_cll;
  long long max_fall;

  MasteringMetadata* mastering_metadata;
};

struct Projection {
  enum ProjectionType {
    kTypeNotPresent = -1,
    kRectangular = 0,
    kEquirectangular = 1,
    kCubeMap = 2,
    kMesh = 3,
  };
  static const float kValueNotPresent;
  Projection()
      : type(kTypeNotPresent),
        private_data(NULL),
        private_data_length(0),
        pose_yaw(kValueNotPresent),
        pose_pitch(kValueNotPresent),
        pose_roll(kValueNotPresent) {}
  ~Projection() { delete[] private_data; }
  WEBM_EXPORT static bool Parse(IMkvReader* reader, long long element_start,
                    long long element_size, Projection** projection);

  ProjectionType type;
  unsigned char* private_data;
  size_t private_data_length;
  float pose_yaw;
  float pose_pitch;
  float pose_roll;
};

class VideoTrack : public Track {
  VideoTrack(const VideoTrack&);
  VideoTrack& operator=(const VideoTrack&);

  WEBM_EXPORT VideoTrack(Segment*, long long element_start, long long element_size);

 public:
  WEBM_EXPORT virtual ~VideoTrack();
  WEBM_EXPORT static long Parse(Segment*, const Info&, long long element_start,
                    long long element_size, VideoTrack*&);

  WEBM_EXPORT long long GetWidth() const;
  WEBM_EXPORT long long GetHeight() const;
  WEBM_EXPORT long long GetDisplayWidth() const;
  WEBM_EXPORT long long GetDisplayHeight() const;
  WEBM_EXPORT long long GetDisplayUnit() const;
  WEBM_EXPORT long long GetStereoMode() const;
  WEBM_EXPORT double GetFrameRate() const;

  WEBM_EXPORT bool VetEntry(const BlockEntry*) const;
  WEBM_EXPORT long Seek(long long time_ns, const BlockEntry*&) const;

  WEBM_EXPORT Colour* GetColour() const;

  WEBM_EXPORT Projection* GetProjection() const;

  const char* GetColourSpace() const { return m_colour_space; }

 private:
  long long m_width;
  long long m_height;
  long long m_display_width;
  long long m_display_height;
  long long m_display_unit;
  long long m_stereo_mode;
  char* m_colour_space;
  double m_rate;

  Colour* m_colour;
  Projection* m_projection;
};

class AudioTrack : public Track {
  AudioTrack(const AudioTrack&);
  AudioTrack& operator=(const AudioTrack&);

  WEBM_EXPORT AudioTrack(Segment*, long long element_start, long long element_size);

 public:
  WEBM_EXPORT static long Parse(Segment*, const Info&, long long element_start,
                    long long element_size, AudioTrack*&);

  WEBM_EXPORT double GetSamplingRate() const;
  WEBM_EXPORT long long GetChannels() const;
  WEBM_EXPORT long long GetBitDepth() const;

 private:
  double m_rate;
  long long m_channels;
  long long m_bitDepth;
};

class Tracks {
  Tracks(const Tracks&);
  Tracks& operator=(const Tracks&);

 public:
  Segment* const m_pSegment;
  const long long m_start;
  const long long m_size;
  const long long m_element_start;
  const long long m_element_size;

  WEBM_EXPORT Tracks(Segment*, long long start, long long size, long long element_start,
         long long element_size);

  WEBM_EXPORT ~Tracks();

  WEBM_EXPORT long Parse();

  WEBM_EXPORT unsigned long GetTracksCount() const;

  WEBM_EXPORT const Track* GetTrackByNumber(long tn) const;
  WEBM_EXPORT const Track* GetTrackByIndex(unsigned long idx) const;

 private:
  Track** m_trackEntries;
  Track** m_trackEntriesEnd;

  WEBM_EXPORT long ParseTrackEntry(long long payload_start, long long payload_size,
                       long long element_start, long long element_size,
                       Track*&) const;
};

class Chapters {
  Chapters(const Chapters&);
  Chapters& operator=(const Chapters&);

 public:
  Segment* const m_pSegment;
  const long long m_start;
  const long long m_size;
  const long long m_element_start;
  const long long m_element_size;

  WEBM_EXPORT Chapters(Segment*, long long payload_start, long long payload_size,
           long long element_start, long long element_size);

  WEBM_EXPORT ~Chapters();

  WEBM_EXPORT long Parse();

  class Atom;
  class Edition;

  class Display {
    friend class Atom;
    WEBM_EXPORT Display();
    Display(const Display&);
    WEBM_EXPORT ~Display();
    Display& operator=(const Display&);

   public:
    WEBM_EXPORT const char* GetString() const;
    WEBM_EXPORT const char* GetLanguage() const;
    WEBM_EXPORT const char* GetCountry() const;

   private:
    WEBM_EXPORT void Init();
    WEBM_EXPORT void ShallowCopy(Display&) const;
    WEBM_EXPORT void Clear();
    WEBM_EXPORT long Parse(IMkvReader*, long long pos, long long size);

    char* m_string;
    char* m_language;
    char* m_country;
  };

  class Atom {
    friend class Edition;
    WEBM_EXPORT Atom();
    Atom(const Atom&);
    WEBM_EXPORT ~Atom();
    Atom& operator=(const Atom&);

   public:
    WEBM_EXPORT unsigned long long GetUID() const;
    WEBM_EXPORT const char* GetStringUID() const;

    WEBM_EXPORT long long GetStartTimecode() const;
    WEBM_EXPORT long long GetStopTimecode() const;

    WEBM_EXPORT long long GetStartTime(const Chapters*) const;
    WEBM_EXPORT long long GetStopTime(const Chapters*) const;

    WEBM_EXPORT int GetDisplayCount() const;
    WEBM_EXPORT const Display* GetDisplay(int index) const;

   private:
    WEBM_EXPORT void Init();
    WEBM_EXPORT void ShallowCopy(Atom&) const;
    WEBM_EXPORT void Clear();
    WEBM_EXPORT long Parse(IMkvReader*, long long pos, long long size);
    WEBM_EXPORT static long long GetTime(const Chapters*, long long timecode);

    WEBM_EXPORT long ParseDisplay(IMkvReader*, long long pos, long long size);
    WEBM_EXPORT bool ExpandDisplaysArray();

    char* m_string_uid;
    unsigned long long m_uid;
    long long m_start_timecode;
    long long m_stop_timecode;

    Display* m_displays;
    int m_displays_size;
    int m_displays_count;
  };

  class Edition {
    friend class Chapters;
    WEBM_EXPORT Edition();
    Edition(const Edition&);
    WEBM_EXPORT ~Edition();
    Edition& operator=(const Edition&);

   public:
    WEBM_EXPORT int GetAtomCount() const;
    WEBM_EXPORT const Atom* GetAtom(int index) const;

   private:
    WEBM_EXPORT void Init();
    WEBM_EXPORT void ShallowCopy(Edition&) const;
    WEBM_EXPORT void Clear();
    WEBM_EXPORT long Parse(IMkvReader*, long long pos, long long size);

    WEBM_EXPORT long ParseAtom(IMkvReader*, long long pos, long long size);
    WEBM_EXPORT bool ExpandAtomsArray();

    Atom* m_atoms;
    int m_atoms_size;
    int m_atoms_count;
  };

  WEBM_EXPORT int GetEditionCount() const;
  WEBM_EXPORT const Edition* GetEdition(int index) const;

 private:
  WEBM_EXPORT long ParseEdition(long long pos, long long size);
  WEBM_EXPORT bool ExpandEditionsArray();

  Edition* m_editions;
  int m_editions_size;
  int m_editions_count;
};

class Tags {
  Tags(const Tags&);
  Tags& operator=(const Tags&);

 public:
  Segment* const m_pSegment;
  const long long m_start;
  const long long m_size;
  const long long m_element_start;
  const long long m_element_size;

  WEBM_EXPORT Tags(Segment*, long long payload_start, long long payload_size,
       long long element_start, long long element_size);

  WEBM_EXPORT ~Tags();

  WEBM_EXPORT long Parse();

  class Tag;
  class SimpleTag;

  class SimpleTag {
    friend class Tag;
    WEBM_EXPORT SimpleTag();
    SimpleTag(const SimpleTag&);
    WEBM_EXPORT ~SimpleTag();
    SimpleTag& operator=(const SimpleTag&);

   public:
    WEBM_EXPORT const char* GetTagName() const;
    WEBM_EXPORT const char* GetTagString() const;

   private:
    WEBM_EXPORT void Init();
    WEBM_EXPORT void ShallowCopy(SimpleTag&) const;
    WEBM_EXPORT void Clear();
    WEBM_EXPORT long Parse(IMkvReader*, long long pos, long long size);

    char* m_tag_name;
    char* m_tag_string;
  };

  class Tag {
    friend class Tags;
    WEBM_EXPORT Tag();
    Tag(const Tag&);
    WEBM_EXPORT ~Tag();
    Tag& operator=(const Tag&);

   public:
    WEBM_EXPORT int GetSimpleTagCount() const;
    WEBM_EXPORT const SimpleTag* GetSimpleTag(int index) const;

   private:
    WEBM_EXPORT void Init();
    WEBM_EXPORT void ShallowCopy(Tag&) const;
    WEBM_EXPORT void Clear();
    WEBM_EXPORT long Parse(IMkvReader*, long long pos, long long size);

    WEBM_EXPORT long ParseSimpleTag(IMkvReader*, long long pos, long long size);
    WEBM_EXPORT bool ExpandSimpleTagsArray();

    SimpleTag* m_simple_tags;
    int m_simple_tags_size;
    int m_simple_tags_count;
  };

  WEBM_EXPORT int GetTagCount() const;
  WEBM_EXPORT const Tag* GetTag(int index) const;

 private:
  WEBM_EXPORT long ParseTag(long long pos, long long size);
  WEBM_EXPORT bool ExpandTagsArray();

  Tag* m_tags;
  int m_tags_size;
  int m_tags_count;
};

class SegmentInfo {
  SegmentInfo(const SegmentInfo&);
  SegmentInfo& operator=(const SegmentInfo&);

 public:
  Segment* const m_pSegment;
  const long long m_start;
  const long long m_size;
  const long long m_element_start;
  const long long m_element_size;

  WEBM_EXPORT SegmentInfo(Segment*, long long start, long long size,
              long long element_start, long long element_size);

  WEBM_EXPORT ~SegmentInfo();

  WEBM_EXPORT long Parse();

  WEBM_EXPORT long long GetTimeCodeScale() const;
  WEBM_EXPORT long long GetDuration() const;  // scaled
  WEBM_EXPORT const char* GetMuxingAppAsUTF8() const;
  WEBM_EXPORT const char* GetWritingAppAsUTF8() const;
  WEBM_EXPORT const char* GetTitleAsUTF8() const;

 private:
  long long m_timecodeScale;
  double m_duration;
  char* m_pMuxingAppAsUTF8;
  char* m_pWritingAppAsUTF8;
  char* m_pTitleAsUTF8;
};

class SeekHead {
  SeekHead(const SeekHead&);
  SeekHead& operator=(const SeekHead&);

 public:
  Segment* const m_pSegment;
  const long long m_start;
  const long long m_size;
  const long long m_element_start;
  const long long m_element_size;

  WEBM_EXPORT SeekHead(Segment*, long long start, long long size, long long element_start,
           long long element_size);

  WEBM_EXPORT ~SeekHead();

  WEBM_EXPORT long Parse();

  struct Entry {
    WEBM_EXPORT Entry();

    // the SeekHead entry payload
    long long id;
    long long pos;

    // absolute pos of SeekEntry ID
    long long element_start;

    // SeekEntry ID size + size size + payload
    long long element_size;
  };

  WEBM_EXPORT int GetCount() const;
  WEBM_EXPORT const Entry* GetEntry(int idx) const;

  struct VoidElement {
    // absolute pos of Void ID
    long long element_start;

    // ID size + size size + payload size
    long long element_size;
  };

  WEBM_EXPORT int GetVoidElementCount() const;
  WEBM_EXPORT const VoidElement* GetVoidElement(int idx) const;

 private:
  Entry* m_entries;
  int m_entry_count;

  VoidElement* m_void_elements;
  int m_void_element_count;

  WEBM_EXPORT static bool ParseEntry(IMkvReader*,
                         long long pos,  // payload
                         long long size, Entry*);
};

class Cues;
class CuePoint {
  friend class Cues;

  WEBM_EXPORT CuePoint(long, long long);
  WEBM_EXPORT ~CuePoint();

  CuePoint(const CuePoint&);
  CuePoint& operator=(const CuePoint&);

 public:
  long long m_element_start;
  long long m_element_size;

  WEBM_EXPORT bool Load(IMkvReader*);

  WEBM_EXPORT long long GetTimeCode() const;  // absolute but unscaled
  WEBM_EXPORT long long GetTime(const Segment*) const;  // absolute and scaled (ns units)

  struct TrackPosition {
    long long m_track;
    long long m_pos;  // of cluster
    long long m_block;
    // codec_state  //defaults to 0
    // reference = clusters containing req'd referenced blocks
    //  reftime = timecode of the referenced block

    WEBM_EXPORT bool Parse(IMkvReader*, long long, long long);
  };

  WEBM_EXPORT const TrackPosition* Find(const Track*) const;

 private:
  const long m_index;
  long long m_timecode;
  TrackPosition* m_track_positions;
  size_t m_track_positions_count;
};

class Cues {
  friend class Segment;

  WEBM_EXPORT Cues(Segment*, long long start, long long size, long long element_start,
       long long element_size);
  WEBM_EXPORT ~Cues();

  Cues(const Cues&);
  Cues& operator=(const Cues&);

 public:
  Segment* const m_pSegment;
  const long long m_start;
  const long long m_size;
  const long long m_element_start;
  const long long m_element_size;

  WEBM_EXPORT bool Find(  // lower bound of time_ns
      long long time_ns, const Track*, const CuePoint*&,
      const CuePoint::TrackPosition*&) const;

  WEBM_EXPORT const CuePoint* GetFirst() const;
  WEBM_EXPORT const CuePoint* GetLast() const;
  WEBM_EXPORT const CuePoint* GetNext(const CuePoint*) const;

  WEBM_EXPORT const BlockEntry* GetBlock(const CuePoint*,
                             const CuePoint::TrackPosition*) const;

  WEBM_EXPORT bool LoadCuePoint() const;
  WEBM_EXPORT long GetCount() const;  // loaded only
  // long GetTotal() const;  //loaded + preloaded
  WEBM_EXPORT bool DoneParsing() const;

 private:
  WEBM_EXPORT bool Init() const;
  WEBM_EXPORT bool PreloadCuePoint(long&, long long) const;

  mutable CuePoint** m_cue_points;
  mutable long m_count;
  mutable long m_preload_count;
  mutable long long m_pos;
};

class Cluster {
  friend class Segment;

  Cluster(const Cluster&);
  Cluster& operator=(const Cluster&);

 public:
  Segment* const m_pSegment;

 public:
  WEBM_EXPORT static Cluster* Create(Segment*,
                         long index,  // index in segment
                         long long off);  // offset relative to segment
  // long long element_size);

  WEBM_EXPORT Cluster();  // EndOfStream
  WEBM_EXPORT ~Cluster();

  WEBM_EXPORT bool EOS() const;

  WEBM_EXPORT long long GetTimeCode() const;  // absolute, but not scaled
  WEBM_EXPORT long long GetTime() const;  // absolute, and scaled (nanosecond units)
  WEBM_EXPORT long long GetFirstTime() const;  // time (ns) of first (earliest) block
  WEBM_EXPORT long long GetLastTime() const;  // time (ns) of last (latest) block

  WEBM_EXPORT long GetFirst(const BlockEntry*&) const;
  WEBM_EXPORT long GetLast(const BlockEntry*&) const;
  WEBM_EXPORT long GetNext(const BlockEntry* curr, const BlockEntry*& next) const;

  WEBM_EXPORT const BlockEntry* GetEntry(const Track*, long long ns = -1) const;
  WEBM_EXPORT const BlockEntry* GetEntry(const CuePoint&,
                             const CuePoint::TrackPosition&) const;
  // const BlockEntry* GetMaxKey(const VideoTrack*) const;

  //    static bool HasBlockEntries(const Segment*, long long);

  WEBM_EXPORT static long HasBlockEntries(const Segment*, long long idoff, long long& pos,
                              long& size);

  WEBM_EXPORT long GetEntryCount() const;

  WEBM_EXPORT long Load(long long& pos, long& size) const;

  WEBM_EXPORT long Parse(long long& pos, long& size) const;
  WEBM_EXPORT long GetEntry(long index, const mkvparser::BlockEntry*&) const;

 protected:
  WEBM_EXPORT Cluster(Segment*, long index, long long element_start);
  // long long element_size);

 public:
  const long long m_element_start;
  WEBM_EXPORT long long GetPosition() const;  // offset relative to segment

  WEBM_EXPORT long GetIndex() const;
  WEBM_EXPORT long long GetElementSize() const;
  // long long GetPayloadSize() const;

  // long long Unparsed() const;

 private:
  long m_index;
  mutable long long m_pos;
  // mutable long long m_size;
  mutable long long m_element_size;
  mutable long long m_timecode;
  mutable BlockEntry** m_entries;
  mutable long m_entries_size;
  mutable long m_entries_count;

  WEBM_EXPORT long ParseSimpleBlock(long long, long long&, long&);
  WEBM_EXPORT long ParseBlockGroup(long long, long long&, long&);

  WEBM_EXPORT long CreateBlock(long long id, long long pos, long long size,
                   long long discard_padding);
  WEBM_EXPORT long CreateBlockGroup(long long start_offset, long long size,
                        long long discard_padding);
  WEBM_EXPORT long CreateSimpleBlock(long long, long long);
};

class Segment {
  friend class Cues;
  friend class Track;
  friend class VideoTrack;

  Segment(const Segment&);
  Segment& operator=(const Segment&);

 private:
  WEBM_EXPORT Segment(IMkvReader*, long long elem_start,
          // long long elem_size,
          long long pos, long long size);

 public:
  IMkvReader* const m_pReader;
  const long long m_element_start;
  // const long long m_element_size;
  const long long m_start;  // posn of segment payload
  const long long m_size;  // size of segment payload
  Cluster m_eos;  // TODO: make private?

  WEBM_EXPORT static long long CreateInstance(IMkvReader*, long long, Segment*&);
  WEBM_EXPORT ~Segment();

  WEBM_EXPORT long Load();  // loads headers and all clusters

  // for incremental loading
  // long long Unparsed() const;
  WEBM_EXPORT bool DoneParsing() const;
  WEBM_EXPORT long long ParseHeaders();  // stops when first cluster is found
  // long FindNextCluster(long long& pos, long& size) const;
  WEBM_EXPORT long LoadCluster(long long& pos, long& size);  // load one cluster
  long LoadCluster();

  WEBM_EXPORT long ParseNext(const Cluster* pCurr, const Cluster*& pNext, long long& pos,
                 long& size);

  WEBM_EXPORT const SeekHead* GetSeekHead() const;
  WEBM_EXPORT const Tracks* GetTracks() const;
  WEBM_EXPORT const SegmentInfo* GetInfo() const;
  WEBM_EXPORT const Cues* GetCues() const;
  WEBM_EXPORT const Chapters* GetChapters() const;
  WEBM_EXPORT const Tags* GetTags() const;

  WEBM_EXPORT long long GetDuration() const;

  WEBM_EXPORT unsigned long GetCount() const;
  WEBM_EXPORT const Cluster* GetFirst() const;
  WEBM_EXPORT const Cluster* GetLast() const;
  WEBM_EXPORT const Cluster* GetNext(const Cluster*);

  WEBM_EXPORT const Cluster* FindCluster(long long time_nanoseconds) const;
  // const BlockEntry* Seek(long long time_nanoseconds, const Track*) const;

  WEBM_EXPORT const Cluster* FindOrPreloadCluster(long long pos);

  WEBM_EXPORT long ParseCues(long long cues_off,  // offset relative to start of segment
                 long long& parse_pos, long& parse_len);

 private:
  long long m_pos;  // absolute file posn; what has been consumed so far
  Cluster* m_pUnknownSize;

  SeekHead* m_pSeekHead;
  SegmentInfo* m_pInfo;
  Tracks* m_pTracks;
  Cues* m_pCues;
  Chapters* m_pChapters;
  Tags* m_pTags;
  Cluster** m_clusters;
  long m_clusterCount;  // number of entries for which m_index >= 0
  long m_clusterPreloadCount;  // number of entries for which m_index < 0
  long m_clusterSize;  // array size

  WEBM_EXPORT long DoLoadCluster(long long&, long&);
  WEBM_EXPORT long DoLoadClusterUnknownSize(long long&, long&);
  WEBM_EXPORT long DoParseNext(const Cluster*&, long long&, long&);

  WEBM_EXPORT bool AppendCluster(Cluster*);
  WEBM_EXPORT bool PreloadCluster(Cluster*, ptrdiff_t);

  // void ParseSeekHead(long long pos, long long size);
  // void ParseSeekEntry(long long pos, long long size);
  // void ParseCues(long long);

  WEBM_EXPORT const BlockEntry* GetBlock(const CuePoint&, const CuePoint::TrackPosition&);
};

}  // namespace mkvparser

inline long mkvparser::Segment::LoadCluster() {
  long long pos;
  long size;

  return LoadCluster(pos, size);
}

#endif  // MKVPARSER_MKVPARSER_H_
