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

#include "pch.h"
#include "yolo9.h"


#pragma comment(lib,"Microsoft.AI.MachineLearning.lib")
#pragma comment(lib,"onnxruntime.lib")


void Sample::CheckDeviceResources( std::source_location caller )
{
    const auto& device = m_deviceResources->GetD3DDevice( );
    auto hr = device.GetDeviceRemovedReason( );
    if ( FAILED( hr ) )
    {
        auto error = FormatHRESULT( hr );
        auto function = ToWideString( caller.function_name( ) );
        auto fileName = ToWideString( caller.file_name( ) );
        PrintLn( L"R Device {} - {}:{}({})", error, function, fileName, caller.line( ) );
    }
}



void Sample::InitializeDirectMLResources(const wchar_t * model_path, bool bAddModel)
{
    // wait for gpu to create new textures
    m_deviceResources->WaitForGpu();

    const wchar_t* modelfile = L"Model_Yolo_v9c_f16.onnx";
    auto home = Harlinn::Common::Core::Environment::EnvironmentVariable( L"HCC_HOME" );
    auto yoloDir = IO::Path::Combine( home, L"Share\\onnx\\models\\yolo" );
    auto yoloModel = IO::Path::Combine( yoloDir, modelfile );
    auto future = computeNode_->Load( yoloModel );
    model_ = future.get( );

}
