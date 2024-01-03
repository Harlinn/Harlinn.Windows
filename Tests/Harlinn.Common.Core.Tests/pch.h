#pragma once
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

#include <HCCApplication.h>
#include <HCCArray.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>
#include <HCCBits.h>
#include <HCCBlocks.h>
#include <HCCComImpl.h>
#include <HCCComInterfaces.h>
#include <HCCCommDevice.h>
#include <HCCConverters.h>
#include <HCCCrypto.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HCCDateTime.h>
#include <HCCEnvironment.h>
#include <HCCEse.h>
#include <HCCIO.h>
#include <HCCIOContext.h>
#include <HCCLib.h>
#include <HCCLMDB.h>
#include <HCCLoggerLMDBSinkStorage.h>
#include <HCCMath.h>
#include <HCCMatrix.h>
#include <HCCObj.h>
#include <HCCProcess.h>
#include <HCCSecurity.h>
#include <HCCSocket.h>
#include <HCCString.h>
#include <HCCSync.h>
#include <HCCTcpClient.h>
#include <HCCTcpServer.h>
#include <HCCThread.h>
#include <HCCTraits.h>
#include <HCCTuple.h>
#include <HCCTypeDescriptorCursor.h>
#include <HCCVariant.h>
#include <HCCVector.h>
#include <HCCXml.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

