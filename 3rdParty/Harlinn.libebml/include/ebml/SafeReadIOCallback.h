/****************************************************************************
** libebml : parse EBML files, see http://embl.sourceforge.net/
**
** <file/class description>
**
** Copyright (C) 2002-2014 Moritz Bunkus.  All rights reserved.
**
** This file is part of libebml.
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
  \version \$Id$
  \author Moritz Bunkus <moritz@bunkus.org>
*/
#ifndef LIBEBML_SAFEREADIOCALLBACK_H
#define LIBEBML_SAFEREADIOCALLBACK_H

#include "EbmlBinary.h"
#include "EbmlTypes.h"
#include "IOCallback.h"

namespace libebml {

class EBML_DLL_API SafeReadIOCallback {
public:
  class EBML_DLL_API EndOfStreamX {
  public:
    size_t mMissingBytes;
    EBML_EXPORT EndOfStreamX(std::size_t MissingBytes);
  };

private:
  IOCallback *mIO;
  bool mDeleteIO;
  size_t mSize;

public:
  EBML_EXPORT SafeReadIOCallback(IOCallback *IO, bool DeleteIO);
  EBML_EXPORT SafeReadIOCallback(void const *Mem, size_t Size);
  EBML_EXPORT SafeReadIOCallback(EbmlBinary const &Binary);
  EBML_EXPORT ~SafeReadIOCallback();

  EBML_EXPORT size_t GetPosition() const;
  EBML_EXPORT size_t GetSize() const;
  EBML_EXPORT size_t GetRemainingBytes() const;
  EBML_EXPORT bool IsEmpty() const;

  EBML_EXPORT uint8  GetUInt8();
  EBML_EXPORT uint64 GetUIntBE(size_t NumBytes);
  EBML_EXPORT uint16 GetUInt16BE();
  EBML_EXPORT uint32 GetUInt24BE();
  EBML_EXPORT uint32 GetUInt32BE();
  EBML_EXPORT uint64 GetUInt64BE();

  EBML_EXPORT void Read(void *Dst, size_t Count);

  EBML_EXPORT void Skip(size_t Count);
  EBML_EXPORT void Seek(size_t Position);

private:
  SafeReadIOCallback(SafeReadIOCallback const &) { }

protected:
  EBML_EXPORT void Init(IOCallback *IO, bool DeleteIO);
};

} // namespace libebml

#endif  // LIBEBML_SAFEREADIOCALLBACK_H
