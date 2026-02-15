/*
   Copyright 2024-2026 Espen Harlinn

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

#pragma once

#include "HDMCGameCore.h"
#include "HDMCCameraController.h"
#include "HDMCBufferManager.h"
#include "HDMCCamera.h"
#include "HDMCCommandContext.h"
#include "HDMCTemporalEffects.h"
#include "HDMCMotionBlur.h"
#include "HDMCDepthOfField.h"
#include "HDMCPostEffects.h"
#include "HDMCSSAO.h"
#include "HDMCFXAA.h"
#include "HDMCSystemTime.h"
#include "HDMCTextRenderer.h"
#include "HDMCParticleEffectManager.h"
#include "HDMCGameInput.h"
#include "HDMCEngineProfiling.h"
#include "Util/HDMCCommandLineArg.h"
#include "HDMMSponzaRenderer.h"
#include "HDMMglTF.h"
#include "HDMMRenderer.h"
#include "HDMMModel.h"
#include "HDMMModelLoader.h"
#include "HDMCShadowCamera.h"
#include "HDMCDisplay.h"


#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>