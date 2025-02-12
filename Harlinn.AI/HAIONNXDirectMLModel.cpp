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
#include "HAIONNXDirectML.h"

namespace Harlinn::AI::ONNX::DirectML
{
    HAI_EXPORT Model::Model( const std::shared_ptr<ComputeNode>& computeNode, const std::shared_ptr<ONNX::Session>& session )
        : Base( session ), computeNode_( computeNode )
    { }

    HAI_EXPORT void Model::Compute( const Binary& inputTensorData, const Math::Vector2f& viewportSize )
    {
        Base::Compute( inputTensorData, viewportSize );
        auto computeNode = computeNode_.lock( );
        computeNode->DoOnComputeDone( this );
    }

}