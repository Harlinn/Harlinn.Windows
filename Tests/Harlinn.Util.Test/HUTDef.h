#pragma once
#ifndef HARLINN_UTIL_TEST_HUTDEF_H_
#define HARLINN_UTIL_TEST_HUTDEF_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HWDef.h>
#include <DirectXMath.h>
#include <pbrto/util/transform.h>
#include <pbrto/util/NewTransform.h>
#include <HCCTransformations.h>

#ifdef BUILDING_HARLINN_UTIL_TEST
#define HUT_EXPORT __declspec(dllexport)
#define HUT_TEMPLATE_EXPORT __declspec(dllexport)
#define HUT_TEMPLATE_EXPORT_DECL
#else
#define HUT_EXPORT __declspec(dllimport)
#define HUT_TEMPLATE_EXPORT __declspec(dllimport)
#define HUT_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Util.Test.lib")
#endif


#endif
