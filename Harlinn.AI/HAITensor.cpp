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
#include "pch.h"
#include "HAITensor.h"


namespace Harlinn::AI::Tensors
{
    HAI_EXPORT std::shared_ptr<Value> CreateValue( std::shared_ptr<Meta::TypeInfoBase> typeInfo )
    {
        if ( typeInfo == nullptr )
        {
            HCC_THROW( ArgumentNullException, L"typeInfo", L"typeInfo cannot be nullptr." );
        }
        auto type = typeInfo->Type( );
        switch ( type )
        {
            case Meta::TypeInfoType::Tensor:
            {
                auto ti = std::static_pointer_cast< Meta::TensorTypeAndShapeInfo >( typeInfo );
                return std::make_shared<Tensor>( ti );
            }
            break;
            default:
            {
                HCC_THROW( NotImplementedException );
            }
            break;
        }

    }
}