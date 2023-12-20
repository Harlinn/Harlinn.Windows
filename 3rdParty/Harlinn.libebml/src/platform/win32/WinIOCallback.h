/****************************************************************************
** libebml : parse EBML files, see http://embl.sourceforge.net/
**
** <file/class description>
**
** Copyright (C) 2002-2003 Steve Lhomme.  All rights reserved.
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
** See http://www.gnu.org/licenses/lgpl-2.1.html for LGPL licensing information.
**
** Contact license@matroska.org if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/
/*!
  \file
  \version \$Id: WinIOCallback.h 1090 2005-03-16 12:47:59Z robux4 $
  \author Steve Lhomme     <robux4 @ users.sf.net>
  \author Jory Stone       <jcsston @ toughguy.net>
  \author Cyrius           <suiryc @ users.sf.net>
*/

#ifndef LIBEBML_WINIOCALLBACK_H
#define LIBEBML_WINIOCALLBACK_H

#include <windows.h>
#include <stdexcept>
#include <string>
#include "ebml/IOCallback.h"

namespace libebml {

class WinIOCallback: public IOCallback
{
public:
  EBML_EXPORT WinIOCallback(const wchar_t* Path, const open_mode aMode, DWORD dwFlags=0);
  EBML_EXPORT WinIOCallback(const char* Path, const open_mode aMode, DWORD dwFlags=0);
  EBML_EXPORT virtual ~WinIOCallback();

  EBML_EXPORT bool open(const wchar_t* Path, const open_mode Mode, DWORD dwFlags=0);
  EBML_EXPORT bool open(const char* Path, const open_mode Mode, DWORD dwFlags=0);

  EBML_EXPORT virtual uint32 read(void*Buffer,size_t Size);
  EBML_EXPORT virtual size_t write(const void*Buffer,size_t Size);
  EBML_EXPORT virtual void setFilePointer(int64 Offset,seek_mode Mode=seek_beginning);
  EBML_EXPORT virtual uint64 getFilePointer();
  EBML_EXPORT virtual void close();

  bool IsOk() { return mOk; };
  const std::string &GetLastErrorStr() { return mLastErrorStr; };
  bool SetEOF();
protected:
  bool mOk;
  std::string mLastErrorStr;
  uint64 mCurrentPosition;

  HANDLE mFile;
};

} // namespace libebml

#endif // LIBEBML_WINIOCALLBACK_H
