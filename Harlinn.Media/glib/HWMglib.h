#pragma once 
#ifndef HARLINN_MEDIA_GLIB_HWMGLIB_H_
#define HARLINN_MEDIA_GLIB_HWMGLIB_H_
/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <HWMDef.h>


#include "HWMgalloca.h"
#include "HWMgarray.h"
#include "HWMgasyncqueue.h"
#include "HWMgatomic.h"
#include "HWMgbacktrace.h"
#include "HWMgbase64.h"
#include "HWMgbitlock.h"
#include "HWMgbookmarkfile.h"
#include "HWMgbytes.h"
#include "HWMgcharset.h"
#include "HWMgchecksum.h"
#include "HWMgconvert.h"
#include "HWMgdataset.h"
#include "HWMgdate.h"
#include "HWMgdatetime.h"
#include "HWMgdir.h"
#include "HWMgenviron.h"
#include "HWMgerror.h"
#include "HWMgfileutils.h"
#include "HWMggettext.h"
#include "HWMghash.h"
#include "HWMghmac.h"
#include "HWMghook.h"
#include "HWMghostutils.h"
#include "HWMgiochannel.h"
#include "HWMgkeyfile.h"
#include "HWMglist.h"
#include "HWMgmain.h"
#include "HWMgmappedfile.h"
#include "HWMgmarkup.h"
#include "HWMgmem.h"
#include "HWMgmessages.h"
#include "HWMgnode.h"
#include "HWMgoption.h"
#include "HWMgpattern.h"
#include "HWMgpoll.h"
#include "HWMgprimes.h"
#include "HWMgqsort.h"
#include "HWMgquark.h"
#include "HWMgqueue.h"
#include "HWMgrand.h"
#include "HWMgrcbox.h"
#include "HWMgrefcount.h"
#include "HWMgrefstring.h"
#include "HWMgregex.h"
#include "HWMgscanner.h"
#include "HWMgsequence.h"
#include "HWMgshell.h"
#include "HWMgslice.h"
#include "HWMgslist.h"
#include "HWMgspawn.h"
#include "HWMgstrfuncs.h"
#include "HWMgstringchunk.h"
#include "HWMgstring.h"
#include "HWMgstrvbuilder.h"
#include "HWMgtestutils.h"
#include "HWMgthread.h"
#include "HWMgthreadpool.h"
#include "HWMgtimer.h"
#include "HWMgtimezone.h"
#include "HWMgtrashstack.h"
#include "HWMgtree.h"
#include "HWMgtypes.h"
#include "HWMgunicode.h"
#include "HWMguri.h"
#include "HWMgutils.h"
#include "HWMguuid.h"
#include "HWMgvariant.h"
#include "HWMgversion.h"

#ifdef G_PLATFORM_WIN32
#include "HWMgwin32.h"
#endif

#endif


