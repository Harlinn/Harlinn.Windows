/****************************************************************************
** libebml : parse EBML files, see http://embl.sourceforge.net/
**
** <file/class description>
**
** Copyright (C) 2014 Moritz Bunkus.  All rights reserved.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** See http://www.matroska.org/license/lgpl/ for LGPL licensing information.
**
** Contact license@matroska.org if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

/*!
  \file
  \author Moritz Bunkus <moritz@bunkus.org>
*/
#ifndef LIBEBML_MEMREADIOCALLBACK_H
#define LIBEBML_MEMREADIOCALLBACK_H

#include "EbmlBinary.h"
#include "IOCallback.h"

namespace libebml {

class EBML_DLL_API MemReadIOCallback : public IOCallback {
protected:
  uint8 const *mStart, *mEnd, *mPtr;

public:
  EBML_EXPORT MemReadIOCallback(void const *Ptr, size_t Size);
  EBML_EXPORT MemReadIOCallback(EbmlBinary const &Binary);
  EBML_EXPORT MemReadIOCallback(MemReadIOCallback const &Mem);
  EBML_EXPORT ~MemReadIOCallback() override = default;

  EBML_EXPORT uint32 read(void *Buffer, size_t Size) override;
  EBML_EXPORT void setFilePointer(int64 Offset, seek_mode Mode = seek_beginning) override;
  size_t write(void const *, size_t) override { return 0; }
  uint64 getFilePointer() override { return mPtr - mStart; }
  void close() override {}
  binary const *GetDataBuffer() const { return mPtr; }
  uint64 GetDataBufferSize() const { return mEnd - mStart; }

protected:
  EBML_EXPORT void Init(void const *Ptr, size_t Size);
};

} // namespace libebml

#endif // LIBEBML_MEMREADIOCALLBACK_H
