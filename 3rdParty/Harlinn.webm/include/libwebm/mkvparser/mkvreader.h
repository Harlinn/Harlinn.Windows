// Copyright (c) 2010 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS.  All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
#ifndef MKVPARSER_MKVREADER_H_
#define MKVPARSER_MKVREADER_H_

#include <cstdio>

#include "..\mkvparser/mkvparser.h"

namespace mkvparser {

class MkvReader : public IMkvReader {
 public:
  WEBM_EXPORT MkvReader();
  WEBM_EXPORT explicit MkvReader(FILE* fp);
  WEBM_EXPORT virtual ~MkvReader();

  WEBM_EXPORT int Open(const char*);
  WEBM_EXPORT void Close();

  WEBM_EXPORT virtual int Read(long long position, long length, unsigned char* buffer);
  WEBM_EXPORT virtual int Length(long long* total, long long* available);

 private:
  MkvReader(const MkvReader&);
  MkvReader& operator=(const MkvReader&);

  // Determines the size of the file. This is called either by the constructor
  // or by the Open function depending on file ownership. Returns true on
  // success.
  WEBM_EXPORT bool GetFileSize();

  long long m_length;
  FILE* m_file;
  bool reader_owns_file_;
};

}  // namespace mkvparser

#endif  // MKVPARSER_MKVREADER_H_
