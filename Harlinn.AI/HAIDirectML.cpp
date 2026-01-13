#include "pch.h"
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

#include "HAIDirectMLX.h"

namespace Harlinn::AI::DML
{
    namespace
    {
        std::vector<UInt32> Range( UInt32 first, UInt32 last )
        {
            auto count = last - first;
            std::vector<UInt32> result;
            result.reserve( count );
            for ( UInt32 i = 0; i < count; i++ )
            {
                result.emplace_back( i + first );
            }
            return result;
        }


        std::unique_ptr<OperatorTypeInfo> MakeUnary( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            return result;
        }
        std::unique_ptr<OperatorTypeInfo> MakeUnary( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes, outputDimensions );
            return result;
        }


        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnary( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnary( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes, outputDimensions );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes, outputDimensions );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes, outputDimensions );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeBinary( const char* name, TensorDataTypeMask inputATypes, TensorDataTypeMask inputBTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input, inputATypes );
            result->AddInputTensor( "BTensor", FieldFlags::Input, inputBTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            return result;
        }
        std::unique_ptr<OperatorTypeInfo> MakeBinary( const char* name, TensorDataTypeMask inputATypes, std::vector<UInt32>& inputADimensions, TensorDataTypeMask inputBTypes, std::vector<UInt32>& inputBDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input, inputATypes, inputADimensions );
            result->AddInputTensor( "BTensor", FieldFlags::Input, inputBTypes, inputBDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes, outputDimensions );
            return result;
        }


        std::unique_ptr<OperatorTypeInfo> MakeInplaceBinary( const char* name, TensorDataTypeMask inputATypes, TensorDataTypeMask inputBTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputATypes );
            result->AddInputTensor( "BTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputBTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceBinary( const char* name, TensorDataTypeMask inputATypes, std::vector<UInt32>& inputADimensions, TensorDataTypeMask inputBTypes, std::vector<UInt32>& inputBDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputATypes, inputADimensions );
            result->AddInputTensor( "BTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputBTypes, inputBDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes, outputDimensions );
            return result;
        }

        using Map = std::unordered_map<DML::OperatorType, std::unique_ptr<DML::OperatorTypeInfo>>;


        void AddElementWiseIdentity( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseIdentity", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseIdentity, std::move( typeInfo ) );
        }

        void AddElementWiseAbs( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                (TensorDataTypeMask::Float32 | 
                    TensorDataTypeMask::Float16 | 
                    TensorDataTypeMask::Int64 | 
                    TensorDataTypeMask::Int32 | 
                    TensorDataTypeMask::Int16 | 
                    TensorDataTypeMask::Int8);
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseAbs", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseAbs, std::move( typeInfo ) );
        }
        void AddElementWiseACos( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & (TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseACos", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseACos, std::move( typeInfo ) );
        }
        void AddElementWiseAdd( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                (TensorDataTypeMask::Float32 | 
                    TensorDataTypeMask::Float16 | 
                    TensorDataTypeMask::Int64 | 
                    TensorDataTypeMask::Int32 | 
                    TensorDataTypeMask::Int16 | 
                    TensorDataTypeMask::Int8 | 
                    TensorDataTypeMask::UInt64 | 
                    TensorDataTypeMask::UInt32 | 
                    TensorDataTypeMask::UInt16 | 
                    TensorDataTypeMask::UInt8);
            auto typeInfo = MakeInplaceBinary( "ElementWiseAdd", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseAdd, std::move( typeInfo ) );
        }

        void AddElementWiseAdd1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseAdd1", dataTypes, dataTypes, dataTypes );
            typeInfo->AddFusedActivation("FusedActivation", FieldFlags::Optional );
            map.emplace( OperatorType::ElementWiseAdd1, std::move( typeInfo ) );
        }

        void AddElementWiseASin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseASin", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseASin, std::move( typeInfo ) );
        }

        void AddElementWiseATan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseATan", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseATan, std::move( typeInfo ) );
        }

        void AddElementWiseCeil( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseCeil", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseCeil, std::move( typeInfo ) );
        }

        void AddElementWiseClip( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseClip", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Min" );
            typeInfo->AddFloat32( "Max" );
            map.emplace( OperatorType::ElementWiseClip, std::move( typeInfo ) );
        }

        void AddElementWiseCos( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseCos", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseCos, std::move( typeInfo ) );
        }

        void AddElementWiseDivide( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseDivide", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseDivide, std::move( typeInfo ) );
        }

        void AddElementWiseExp( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseExp", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseExp, std::move( typeInfo ) );
        }

        void AddElementWiseFloor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseFloor", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseFloor, std::move( typeInfo ) );
        }

        void AddElementWiseLog( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseLog", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLog, std::move( typeInfo ) );
        }


        void AddElementWiseLogicalAnd( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalAnd", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalAnd, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalEquals( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalEquals", inputDataTypes, inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseLogicalEquals, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalGreaterThan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalGreaterThan", inputDataTypes, inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseLogicalGreaterThan, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalLessThan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalLessThan", inputDataTypes, inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseLogicalLessThan, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalNot( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalNot", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalNot, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalOr( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalOr", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalOr, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalXor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalXor", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalXor, std::move( typeInfo ) );
        }

        void AddElementWiseMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMax", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMax, std::move( typeInfo ) );
        }

        void AddElementWiseMean( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt32 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMean", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMean, std::move( typeInfo ) );
        }

        void AddElementWiseMin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMin", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMin, std::move( typeInfo ) );
        }

        void AddElementWiseMultiply( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMultiply", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMultiply, std::move( typeInfo ) );
        }

        void AddElementWisePow( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWisePow" );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddInputTensor( "ExponentTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            map.emplace( OperatorType::ElementWisePow, std::move( typeInfo ) );
        }

        void AddElementWiseConstantPow( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseConstantPow", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Exponent" );
            map.emplace( OperatorType::ElementWiseConstantPow, std::move( typeInfo ) );
        }

        void AddElementWiseReciprocal( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseReciprocal", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseReciprocal, std::move( typeInfo ) );
        }

        void AddElementWiseSin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseSin", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSin, std::move( typeInfo ) );
        }

        void AddElementWiseSqrt( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseSqrt", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSqrt, std::move( typeInfo ) );
        }

        void AddElementWiseSubtract( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseSubtract", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSubtract, std::move( typeInfo ) );
        }

        void AddElementWiseTan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseTan", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseTan, std::move( typeInfo ) );
        }

        void AddElementWiseThreshold( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseThreshold", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Min", FieldFlags::Input );
            map.emplace( OperatorType::ElementWiseThreshold, std::move( typeInfo ) );
        }
        

        void AddElementWiseQuantizeLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32  );
            auto scaleDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto zeroPointDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseQuantizeLinear" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input , inputDataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "ZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, zeroPointDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output , outputDataTypes );
            
            map.emplace( OperatorType::ElementWiseQuantizeLinear, std::move( typeInfo ) );
        }

        void AddElementWiseDequantizeLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto scaleDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto zeroPointDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseDequantizeLinear" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "ZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, zeroPointDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes );

            map.emplace( OperatorType::ElementWiseDequantizeLinear, std::move( typeInfo ) );
        }


        void AddActivationELU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ActivationELU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            map.emplace( OperatorType::ActivationELU, std::move( typeInfo ) );
        }

        void AddActivationHardMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnaryWithScaleBias( "ActivationHardMax", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationHardMax, std::move( typeInfo ) );
        }

        void AddActivationHardSigmoid( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ActivationHardSigmoid", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationHardSigmoid, std::move( typeInfo ) );
        }

        void AddActivationIdentity( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationIdentity", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationIdentity, std::move( typeInfo ) );
        }

        void AddActivationLeakyReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationLeakyReLU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            map.emplace( OperatorType::ActivationLeakyReLU, std::move( typeInfo ) );
        }

        void AddActivationLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationLinear", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationLinear, std::move( typeInfo ) );
        }

        void AddActivationLogSoftMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnary( "ActivationLogSoftMax", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationLogSoftMax, std::move( typeInfo ) );
        }


        void AddActivationParameterizedReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8  );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ActivationParameterizedReLU" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddInputTensor( "SlopeTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, dataTypes );

            map.emplace( OperatorType::ActivationParameterizedReLU, std::move( typeInfo ) );
        }

        void AddActivationParametricSoftPlus( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationParametricSoftPlus", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationParametricSoftPlus, std::move( typeInfo ) );
        }

        void AddActivationReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationReLU", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationReLU, std::move( typeInfo ) );
        }

        void AddActivationScaledELU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationScaledELU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Gamma", FieldFlags::Input );
            map.emplace( OperatorType::ActivationScaledELU, std::move( typeInfo ) );
        }

        void AddActivationScaledTanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationScaledTanH", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationScaledTanH, std::move( typeInfo ) );
        }


        void AddActivationSigmoid( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationSigmoid", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationSigmoid, std::move( typeInfo ) );
        }

        void AddActivationSoftMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnary( "ActivationSoftMax", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationSoftMax, std::move( typeInfo ) );
        }

        void AddActivationSoftPlus( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationSoftPlus", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Steepness", FieldFlags::Input );
            map.emplace( OperatorType::ActivationSoftPlus, std::move( typeInfo ) );
        }

        void AddActivationSoftSign( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationSoftSign", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationSoftSign, std::move( typeInfo ) );
        }

        void AddActivationTanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationTanH", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationTanH, std::move( typeInfo ) );
        }


        void AddActivationThresholdedReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationThresholdedReLU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            map.emplace( OperatorType::ActivationThresholdedReLU, std::move( typeInfo ) );
        }


        void AddConvolution( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Convolution" );

            auto dimensions = Range( 3, 5 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "FilterTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddEnum( "Mode", EnumType::ConvolutionMode, FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::ConvolutionDirection, FieldFlags::Input );
            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Strides", FieldFlags::Input );
            typeInfo->AddFloat32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddFloat32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddFloat32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPadding", FieldFlags::Input );
            typeInfo->AddUInt32( "GroupCount", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::Convolution, std::move( typeInfo ) );
        }

        void AddGEMM( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GEMM" );

            auto dimensions = Range( 2, 4 );

            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "CTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddEnum( "TransA", EnumType::MatrixTransform, FieldFlags::Input );
            typeInfo->AddEnum( "TransB", EnumType::MatrixTransform, FieldFlags::Input );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::GEMM, std::move( typeInfo ) );
        }

        void AddReduce( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int64 | 
                TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Reduce" );

            typeInfo->AddEnum( "Function", EnumType::ReduceFunction, FieldFlags::Input );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );

            map.emplace( OperatorType::Reduce, std::move( typeInfo ) );
        }

        void AddAveragePooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "AveragePooling", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddBoolean( "IncludePadding", FieldFlags::Input );

            map.emplace( OperatorType::AveragePooling, std::move( typeInfo ) );
        }

        void AddLPPooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "LPPooling", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32( "P", FieldFlags::Input );

            map.emplace( OperatorType::LPPooling, std::move( typeInfo ) );
        }

        void AddMaxPooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "MaxPooling", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::MaxPooling, std::move( typeInfo ) );
        }

        void AddROIPooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ROIPooling" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ROITensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddFloat32( "SpatialScale", FieldFlags::Input );
            typeInfo->AddSize2D( "PooledSize", FieldFlags::Input );

            map.emplace( OperatorType::ROIPooling, std::move( typeInfo ) );
        }

        void AddSlice( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | 
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | 
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Slice", dataTypes, dataTypes );
            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Offsets", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Sizes", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );

            map.emplace( OperatorType::Slice, std::move( typeInfo ) );
        }

        void AddCast( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Cast", dataTypes, dataTypes );

            map.emplace( OperatorType::Cast, std::move( typeInfo ) );
        }

        void AddSplit( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Split" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddSize( "OutputCount", 1, FieldFlags::Input );
            typeInfo->AddOutputTensorArray( "OutputTensors", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::Split, std::move( typeInfo ) );
        }

        void AddJoin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Join" );

            typeInfo->AddSize( "InputCount", 1, FieldFlags::Input );
            typeInfo->AddInputTensorArray( "InputTensors", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::Join, std::move( typeInfo ) );
        }


        void AddPadding( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Padding", dataTypes, dataTypes );
            typeInfo->AddEnum( "PaddingMode", EnumType::PaddingMode, FieldFlags::Input );
            typeInfo->AddFloat32( "PaddingValue", FieldFlags::Input );
            typeInfo->AddSize( "DimensionCount", 2, FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::Padding, std::move( typeInfo ) );
        }

        void AddValueScale2D( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16  );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "ValueScale2D", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddFloat32( "Scale", FieldFlags::Input );
            typeInfo->AddSize( "ChannelCount", 1, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Bias", FieldFlags::Input );

            map.emplace( OperatorType::ValueScale2D, std::move( typeInfo ) );
        }

        void AddUpSample2D( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "UpSample2D", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddSize2D( "ScaleSize", FieldFlags::Input );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode ,FieldFlags::Input );

            map.emplace( OperatorType::UpSample2D, std::move( typeInfo ) );
        }

        void AddGather( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Gather" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddUInt32( "IndexDimensions", FieldFlags::Input );

            map.emplace( OperatorType::Join, std::move( typeInfo ) );
        }

        void AddSpaceToDepth( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "SpaceToDepth", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddUInt32( "BlockSize", FieldFlags::Input );

            map.emplace( OperatorType::SpaceToDepth, std::move( typeInfo ) );
        }

        void AddDepthToSpace( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "DepthToSpace", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddUInt32( "BlockSize", FieldFlags::Input );

            map.emplace( OperatorType::DepthToSpace, std::move( typeInfo ) );
        }

        void AddTile( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto typeInfo = MakeUnary( "Tile", dataTypes, dataTypes );

            typeInfo->AddSize( "RepeatsCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Repeats", FieldFlags::Input );

            map.emplace( OperatorType::Tile, std::move( typeInfo ) );
        }


        void AddTopK( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "TopK" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputValueTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddInputTensor( "OutputIndexTensor", FieldFlags::Output, indicesDataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddUInt32( "K", FieldFlags::Input );

            map.emplace( OperatorType::TopK, std::move( typeInfo ) );
        }


        void AddBatchNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "BatchNormalization" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "MeanTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "VarianceTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input, dataTypes );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddBoolean( "Spatial", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::BatchNormalization, std::move( typeInfo ) );
        }

        void AddMeanVarianceNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MeanVarianceNormalization" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            typeInfo->AddBoolean( "CrossChannel", FieldFlags::Input );
            typeInfo->AddBoolean( "NormalizeVariance", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::MeanVarianceNormalization, std::move( typeInfo ) );
        }

        void AddLocalResponseNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "LocalResponseNormalization", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddBoolean( "CrossChannel", FieldFlags::Input );
            typeInfo->AddUInt32( "LocalSize", FieldFlags::Input );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            typeInfo->AddFloat32( "Bias", FieldFlags::Input );

            map.emplace( OperatorType::LocalResponseNormalization, std::move( typeInfo ) );
        }

        void AddLPNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeUnary( "LPNormalization", dataTypes, dataTypes );

            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddUInt32( "P", FieldFlags::Input );

            map.emplace( OperatorType::LPNormalization, std::move( typeInfo ) );
        }


        void AddRNN( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "RNN" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "WeightTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "RecurrenceTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "HiddenInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, TensorDataTypeMask::UInt32, dimensions );
            
            typeInfo->AddOutputTensor( "OutputSequenceTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddSize( "ActivationDescCount", 1, FieldFlags::Input );
            typeInfo->AddOperatorArray( "ActivationDescs", FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::RecurrentNetworkDirection,FieldFlags::Input );
            

            map.emplace( OperatorType::RNN, std::move( typeInfo ) );
        }

        void AddLSTM( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "LSTM" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "WeightTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "RecurrenceTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "HiddenInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "CellMemInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, TensorDataTypeMask::UInt32, dimensions );
            typeInfo->AddInputTensor( "PeepholeTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputSequenceTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputCellSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddSize( "ActivationDescCount", 1, FieldFlags::Input );
            typeInfo->AddOperatorArray( "ActivationDescs", FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::RecurrentNetworkDirection, FieldFlags::Input );

            typeInfo->AddFloat32( "ClipThreshold", FieldFlags::Input );
            typeInfo->AddBoolean( "UseClipThreshold", FieldFlags::Input );
            typeInfo->AddBoolean( "CoupleInputForget", FieldFlags::Input );


            map.emplace( OperatorType::LSTM, std::move( typeInfo ) );
        }

        void AddGRU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GRU" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "WeightTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "RecurrenceTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "HiddenInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, TensorDataTypeMask::UInt32, dimensions );

            typeInfo->AddOutputTensor( "OutputSequenceTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddSize( "ActivationDescCount", 1, FieldFlags::Input );
            typeInfo->AddOperatorArray( "ActivationDescs", FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::RecurrentNetworkDirection, FieldFlags::Input );
            typeInfo->AddBoolean( "LinearBeforeReset", FieldFlags::Input );

            map.emplace( OperatorType::GRU, std::move( typeInfo ) );
        }

        void AddElementWiseSign( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceUnary( "ElementWiseSign", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSign, std::move( typeInfo ) );
        }

        void AddElementWiseIsNaN( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "ElementWiseIsNaN", inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseIsNaN, std::move( typeInfo ) );
        }

        void AddElementWiseErf( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseErf", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseErf, std::move( typeInfo ) );
        }

        void AddElementWiseSinH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseSinH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSinH, std::move( typeInfo ) );
        }

        void AddElementWiseCosH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseCosH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseCosH, std::move( typeInfo ) );
        }

        void AddElementWiseTanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseTanH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseTanH, std::move( typeInfo ) );
        }

        void AddElementWiseASinH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseASinH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseASinH, std::move( typeInfo ) );
        }

        void AddElementWiseACosH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseACosH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseACosH, std::move( typeInfo ) );
        }

        void AddElementWiseATanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseATanH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseATanH, std::move( typeInfo ) );
        }

        void AddElementWiseIf( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseIf" );

            typeInfo->AddInputTensor( "ConditionTensor", FieldFlags::Input, TensorDataTypeMask::UInt8 );
            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );

            map.emplace( OperatorType::ElementWiseIf, std::move( typeInfo ) );
        }

        void AddActivationShrink( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | 
                        TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | 
                        TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceUnary( "ActivationShrink", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Bias", FieldFlags::Input );
            typeInfo->AddFloat32( "Threshold", FieldFlags::Input );

            map.emplace( OperatorType::ActivationShrink, std::move( typeInfo ) );
        }

        void AddMaxPooling1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | 
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto outputIndicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "MaxPooling1", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputIndicesTensor", FieldFlags::Output | FieldFlags::Optional, outputIndicesDataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::MaxPooling1, std::move( typeInfo ) );
        }

        void AddMaxUnpooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MaxUnpooling" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            map.emplace( OperatorType::MaxUnpooling, std::move( typeInfo ) );
        }

        void AddDiagonalMatrix( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 2, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "DiagonalMatrix" );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddInt32( "Offset", FieldFlags::Input );
            typeInfo->AddFloat32( "Value", FieldFlags::Input );

            map.emplace( OperatorType::DiagonalMatrix, std::move( typeInfo ) );
        }


        void AddScatterElements( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ScatterElements" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes );
            typeInfo->AddInputTensor( "UpdatesTensor", FieldFlags::Input, dataTypes );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );

            map.emplace( OperatorType::ScatterElements, std::move( typeInfo ) );
        }


        void AddOneHot( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "OneHot" );

            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes );
            typeInfo->AddInputTensor( "ValuesTensor", FieldFlags::Input, dataTypes );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::OneHot, std::move( typeInfo ) );
        }

        void AddResample( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = MakeUnary( "Resample", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );

            typeInfo->AddSize( "ScaleCount", 1, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );

            map.emplace( OperatorType::Resample, std::move( typeInfo ) );
        }

        void AddElementWiseBitShiftLeft( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitShiftLeft", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitShiftLeft, std::move( typeInfo ) );
        }

        void AddElementWiseBitShiftRight( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitShiftRight", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitShiftRight, std::move( typeInfo ) );
        }

        void AddElementWiseRound( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnary( "ElementWiseRound", dataTypes, dataTypes );
            typeInfo->AddEnum( "RoundingMode", EnumType::RoundingMode, FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseRound, std::move( typeInfo ) );
        }

        void AddElementWiseIsInfinity( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto outputDataTypes = supportedDataTypes & TensorDataTypeMask::UInt8;

            auto typeInfo = MakeUnary( "ElementWiseIsInfinity", inputDataTypes, outputDataTypes );
            typeInfo->AddEnum( "InfinityMode", EnumType::IsInfinityMode, FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseIsInfinity, std::move( typeInfo ) );
        }

        void AddElementWiseModulusTruncate( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseModulusTruncate", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseModulusTruncate, std::move( typeInfo ) );
        }

        void AddElementWiseModulusFloor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseModulusFloor", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseModulusFloor, std::move( typeInfo ) );
        }


        void AddFillValueConstant( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "FillValueConstant" );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddTensorDataType( "ValueDataType", FieldFlags::Input );
            typeInfo->AddScalarUnion( "Value", FieldFlags::Input );

            map.emplace( OperatorType::FillValueConstant, std::move( typeInfo ) );
        }

        void AddFillValueSequence( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "FillValueSequence" );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddTensorDataType( "ValueDataType", FieldFlags::Input );
            typeInfo->AddScalarUnion( "ValueStart", FieldFlags::Input );
            typeInfo->AddScalarUnion( "ValueDelta", FieldFlags::Input );

            map.emplace( OperatorType::FillValueSequence, std::move( typeInfo ) );
        }

        void AddReverseSubsequences( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto sequenceLengthsDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ReverseSubsequences" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input, sequenceLengthsDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::ReverseSubsequences, std::move( typeInfo ) );
        }

        void AddGatherElements( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto indicesTensorDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GatherElements" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesTensorDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::GatherElements, std::move( typeInfo ) );
        }

        void AddGatherND( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto indicesTensorDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GatherND" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesTensorDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "InputDimensionCount", FieldFlags::Input );
            typeInfo->AddUInt32( "IndicesDimensionCount", FieldFlags::Input );

            map.emplace( OperatorType::GatherND, std::move( typeInfo ) );
        }

        void AddScatterND( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto indicesTensorDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ScatterND" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesTensorDataTypes );
            typeInfo->AddInputTensor( "UpdatesTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "InputDimensionCount", FieldFlags::Input );
            typeInfo->AddUInt32( "IndicesDimensionCount", FieldFlags::Input );

            map.emplace( OperatorType::ScatterND, std::move( typeInfo ) );
        }

        void AddMaxPooling2( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto outputIndicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "MaxPooling2", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputIndicesTensor", FieldFlags::Output | FieldFlags::Optional, outputIndicesDataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );

            map.emplace( OperatorType::MaxPooling2, std::move( typeInfo ) );
        }

        void AddSlice1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Slice1", dataTypes, dataTypes );
            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddUInt32Array( "InputWindowOffsets", FieldFlags::Input );
            typeInfo->AddUInt32Array( "InputWindowSizes", FieldFlags::Input );
            typeInfo->AddInt32Array( "InputWindowStrides", FieldFlags::Input );

            map.emplace( OperatorType::Slice1, std::move( typeInfo ) );
        }

        void AddTopK1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "TopK1" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputValueTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddInputTensor( "OutputIndexTensor", FieldFlags::Output, indicesDataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddUInt32( "K", FieldFlags::Input );
            typeInfo->AddEnum( "AxisDirection", EnumType::AxisDirection, FieldFlags::Input );

            map.emplace( OperatorType::TopK1, std::move( typeInfo ) );
        }

        void AddDepthToSpace1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "DepthToSpace1", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddUInt32( "BlockSize", FieldFlags::Input );
            typeInfo->AddEnum( "Order", EnumType::DepthSpaceOrder, FieldFlags::Input );

            map.emplace( OperatorType::DepthToSpace1, std::move( typeInfo ) );
        }

        void AddSpaceToDepth1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "SpaceToDepth1", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddUInt32( "BlockSize", FieldFlags::Input );
            typeInfo->AddEnum( "Order", EnumType::DepthSpaceOrder, FieldFlags::Input );

            map.emplace( OperatorType::SpaceToDepth1, std::move( typeInfo ) );
        }


        void AddMeanVarianceNormalization1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MeanVarianceNormalization1" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddSize( "AxisCount", 1 , FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );
            typeInfo->AddBoolean( "NormalizeVariance", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::MeanVarianceNormalization1, std::move( typeInfo ) );
        }

        void AddResample1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = MakeUnary( "Resample1", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );

            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );
            typeInfo->AddFloat32Array( "InputPixelOffsets", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPixelOffsets", FieldFlags::Input );

            map.emplace( OperatorType::Resample1, std::move( typeInfo ) );
        }

        void AddMatrixMultiplyInteger( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 );

            auto matrixDimensions = Range( 2, 4 );
            auto zeroPointDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MatrixMultiplyInteger" );

            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, inputDataTypes, matrixDimensions );
            typeInfo->AddInputTensor( "AZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, zeroPointDimensions );

            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, inputDataTypes, matrixDimensions );
            typeInfo->AddInputTensor( "BZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, zeroPointDimensions );
            
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes, matrixDimensions );

            map.emplace( OperatorType::MatrixMultiplyInteger, std::move( typeInfo ) );
        }

        void AddQuantizedLinearMatrixMultiply( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto scaleDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 );

            auto matrixDimensions = Range( 2, 4 );
            auto scaleAndZeroPointDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "QuantizedLinearMatrixMultiply" );

            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, dataTypes, matrixDimensions );
            typeInfo->AddInputTensor( "AScaleTensor", FieldFlags::Input, scaleDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "AZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, scaleAndZeroPointDimensions );

            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, dataTypes, matrixDimensions );
            typeInfo->AddInputTensor( "BScaleTensor", FieldFlags::Input, scaleDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "BZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, scaleAndZeroPointDimensions );

            typeInfo->AddInputTensor( "OutputScaleTensor", FieldFlags::Input, scaleDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "OutputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, matrixDimensions );

            map.emplace( OperatorType::QuantizedLinearMatrixMultiply, std::move( typeInfo ) );
        }

        void AddConvolutionInteger( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 );

            auto dimensions = Range( 3, 4 );
            auto zeroPointDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ConvolutionInteger" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddInputTensor( "InputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, zeroPointDimensions );

            typeInfo->AddInputTensor( "FilterTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddInputTensor( "FilterZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, zeroPointDimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes, dimensions );
            
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            typeInfo->AddUInt32( "GroupCount", FieldFlags::Input );

            map.emplace( OperatorType::ConvolutionInteger, std::move( typeInfo ) );
        }

        void AddQuantizedLinearConvolution( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 );
            auto scaleDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 );
            auto biasDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 );

            auto dimensions = Range( 3, 4 );
            auto scaleAndZeroPointDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "QuantizedLinearConvolution" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddInputTensor( "InputScaleTensor", FieldFlags::Input, scaleDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "InputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, scaleAndZeroPointDimensions );

            typeInfo->AddInputTensor( "FilterTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddInputTensor( "FilterScaleTensor", FieldFlags::Input, scaleDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "FilterZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, biasDataTypes, scaleAndZeroPointDimensions );

            typeInfo->AddInputTensor( "OutputScaleTensor", FieldFlags::Input, scaleDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "OutputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, inputDataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            typeInfo->AddUInt32( "GroupCount", FieldFlags::Input );

            map.emplace( OperatorType::QuantizedLinearConvolution, std::move( typeInfo ) );
        }

        void AddElementWiseBitAnd( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitAnd", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitAnd, std::move( typeInfo ) );
        }

        void AddElementWiseBitOr( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitOr", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitOr, std::move( typeInfo ) );
        }

        void AddElementWiseBitXor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitXor", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitXor, std::move( typeInfo ) );
        }

        void AddElementWiseBitNot( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto typeInfo = MakeInplaceUnary( "ElementWiseBitNot", dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitNot, std::move( typeInfo ) );
        }

        void AddElementWiseBitCount( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble  );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "ElementWiseBitCount", inputDataTypes, outputDataTypes );

            map.emplace( OperatorType::ElementWiseBitCount, std::move( typeInfo ) );
        }

        

        void AddElementWiseLogicalGreaterThanOrEqual( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalGreaterThanOrEqual", dataTypes, dataTypes, outputDataTypes );

            map.emplace( OperatorType::ElementWiseLogicalGreaterThanOrEqual, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalLessThanOrEqual( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalLessThanOrEqual", dataTypes, dataTypes, outputDataTypes );

            map.emplace( OperatorType::ElementWiseLogicalLessThanOrEqual, std::move( typeInfo ) );
        }

        void AddActivationCeLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16  );

            auto typeInfo = MakeInplaceUnary( "ActivationCeLU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );

            map.emplace( OperatorType::ActivationCeLU, std::move( typeInfo ) );
        }

        void AddActivationReLUGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ActivationReLUGrad" );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes );

            map.emplace( OperatorType::ActivationReLUGrad, std::move( typeInfo ) );
        }

        void AddAveragePoolingGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "AveragePoolingGrad" );

            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, outputDataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            typeInfo->AddBoolean( "IncludePadding", FieldFlags::Input );

            map.emplace( OperatorType::AveragePoolingGrad, std::move( typeInfo ) );
        }

        void AddMaxPoolingGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MaxPoolingGrad" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, inputDataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, outputDataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );

            map.emplace( OperatorType::MaxPoolingGrad, std::move( typeInfo ) );
        }

        void AddRandomGenerator( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "RandomGenerator" );

            typeInfo->AddInputTensor( "InputStateTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputStateTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddEnum( "Type", EnumType::RandomGeneratorType, FieldFlags::Input );

            map.emplace( OperatorType::RandomGenerator, std::move( typeInfo ) );
        }

        void AddNonZeroCoordinates( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | 
                TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto outputDataTypes = supportedDataTypes & TensorDataTypeMask::UInt32;

            auto coordinateDimensions = Range( 2, 8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "NonZeroCoordinates" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddOutputTensor( "OutputCountTensor", FieldFlags::Output, outputDataTypes );
            typeInfo->AddOutputTensor( "OutputCoordinatesTensor", FieldFlags::Output, outputDataTypes, coordinateDimensions );

            map.emplace( OperatorType::NonZeroCoordinates, std::move( typeInfo ) );
        }

        void AddResampleGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ResampleGrad" );

            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );
            typeInfo->AddFloat32Array( "InputPixelOffsets", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPixelOffsets", FieldFlags::Input );


            map.emplace( OperatorType::ResampleGrad, std::move( typeInfo ) );
        }

        void AddSliceGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "SliceGrad" );

            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes );

            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddUInt32Array( "InputWindowOffsets", FieldFlags::Input );
            typeInfo->AddUInt32Array( "InputWindowSizes", FieldFlags::Input );
            typeInfo->AddInt32Array( "InputWindowStrides", FieldFlags::Input );


            map.emplace( OperatorType::SliceGrad, std::move( typeInfo ) );
        }

        void AddAdamOptimizer( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto dimensions = Range( 4, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "AdamOptimizer" );

            typeInfo->AddInputTensor( "InputParametersTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "InputFirstMomentTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "InputSecondMomentTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "GradientTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "TrainingStepTensor", FieldFlags::Input, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputParametersTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputFirstMomentTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputSecondMomentTensor", FieldFlags::Output, dataTypes );

            typeInfo->AddFloat32( "LearningRate", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta1", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta2", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );

            map.emplace( OperatorType::AdamOptimizer, std::move( typeInfo ) );
        }


        void AddArgMin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "ArgMin", dataTypes, dataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );
            typeInfo->AddEnum( "AxisDirection", EnumType::AxisDirection, FieldFlags::Input );


            map.emplace( OperatorType::ArgMin, std::move( typeInfo ) );
        }

        void AddArgMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "ArgMax", dataTypes, dataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );
            typeInfo->AddEnum( "AxisDirection", EnumType::AxisDirection, FieldFlags::Input );

            map.emplace( OperatorType::ArgMax, std::move( typeInfo ) );
        }

        void AddROIAlign( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );
            auto dimensions = Range( 4, 4 );
            auto roiDimensions = Range( 2, 4 );
            auto indicesDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ROIAlign" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ROITensor", FieldFlags::Input, dataTypes, roiDimensions );
            typeInfo->AddInputTensor( "BatchIndicesTensor", FieldFlags::Input, indicesDataTypes, indicesDimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            typeInfo->AddEnum( "ReductionFunction", EnumType::ReduceFunction, FieldFlags::Input );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );
            typeInfo->AddFloat32( "SpatialScaleX", FieldFlags::Input );
            typeInfo->AddFloat32( "SpatialScaleY", FieldFlags::Input );
            typeInfo->AddFloat32( "OutOfBoundsInputValue", FieldFlags::Input );
            typeInfo->AddUInt32( "MinimumSamplesPerOutput", FieldFlags::Input );
            typeInfo->AddUInt32( "MaximumSamplesPerOutput", FieldFlags::Input );


            map.emplace( OperatorType::ROIAlign, std::move( typeInfo ) );
        }

        void AddGatherND1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto indicesTensorDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GatherND1" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesTensorDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "InputDimensionCount", FieldFlags::Input );
            typeInfo->AddUInt32( "IndicesDimensionCount", FieldFlags::Input );
            typeInfo->AddUInt32( "BatchDimensionCount", FieldFlags::Input );

            map.emplace( OperatorType::GatherND1, std::move( typeInfo ) );
        }

        void AddElementWiseATanYX( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseATanYX", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseATanYX, std::move( typeInfo ) );
        }

        void AddElementWiseClipGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseClipGrad" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddFloat32( "Min", FieldFlags::Input );
            typeInfo->AddFloat32( "Max", FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseClipGrad, std::move( typeInfo ) );
        }

        void AddElementWiseDifferenceSquare( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt32 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseDifferenceSquare", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseDifferenceSquare, std::move( typeInfo ) );
        }

        void AddLocalResponseNormalizationGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );


            auto typeInfo = std::make_unique<OperatorTypeInfo>( "LocalResponseNormalizationGrad" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddBoolean( "CrossChannel", FieldFlags::Input );
            typeInfo->AddUInt32( "LocalSize", FieldFlags::Input );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            typeInfo->AddFloat32( "Bias", FieldFlags::Input );

            map.emplace( OperatorType::LocalResponseNormalizationGrad, std::move( typeInfo ) );
        }

        void AddCumulativeProduct( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = MakeUnary( "CumulativeProduct", dataTypes, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddEnum( "AxisDirection", EnumType::AxisDirection,FieldFlags::Input );
            typeInfo->AddBoolean( "HasExclusiveProduct", FieldFlags::Input );

            map.emplace( OperatorType::CumulativeProduct, std::move( typeInfo ) );
        }

        void AddBatchNormalizationGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );


            auto typeInfo = std::make_unique<OperatorTypeInfo>( "BatchNormalizationGrad" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "MeanTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "VarianceTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputScaleGradientTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputBiasGradientTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );

            map.emplace( OperatorType::BatchNormalizationGrad, std::move( typeInfo ) );
        }

        void AddElementWiseQuantizedLinearAdd( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto scaleDataTypes = supportedDataTypes & TensorDataTypeMask::Float32;

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseQuantizedLinearAdd" );

            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "AScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "AZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );

            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "BScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "BZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );

            typeInfo->AddInputTensor( "OutputScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "OutputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );
            
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );

            map.emplace( OperatorType::ElementWiseQuantizedLinearAdd, std::move( typeInfo ) );
        }


        void AddDynamicQuantizeLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto scaleDataTypes = supportedDataTypes & TensorDataTypeMask::Float32;
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "DynamicQuantizeLinear", dataTypes, outputDataTypes );

            typeInfo->AddOutputTensor( "OutputScaleTensor", FieldFlags::Output, scaleDataTypes );
            typeInfo->AddOutputTensor( "OutputZeroPointTensor", FieldFlags::Output, outputDataTypes );

            map.emplace( OperatorType::DynamicQuantizeLinear, std::move( typeInfo ) );
        }

        void AddROIAlign1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );
            auto dimensions = Range( 4, 4 );
            auto roiDimensions = Range( 2, 4 );
            auto indicesDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ROIAlign1" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ROITensor", FieldFlags::Input, dataTypes, roiDimensions );
            typeInfo->AddInputTensor( "BatchIndicesTensor", FieldFlags::Input, indicesDataTypes, indicesDimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            typeInfo->AddEnum( "ReductionFunction", EnumType::ReduceFunction, FieldFlags::Input );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );
            typeInfo->AddFloat32( "SpatialScaleX", FieldFlags::Input );
            typeInfo->AddFloat32( "SpatialScaleY", FieldFlags::Input );
            typeInfo->AddFloat32( "InputPixelOffset", FieldFlags::Input );
            typeInfo->AddFloat32( "OutputPixelOffset", FieldFlags::Input );
            typeInfo->AddFloat32( "OutOfBoundsInputValue", FieldFlags::Input );
            typeInfo->AddUInt32( "MinimumSamplesPerOutput", FieldFlags::Input );
            typeInfo->AddUInt32( "MaximumSamplesPerOutput", FieldFlags::Input );
            typeInfo->AddBoolean( "AlignRegionsToCorners", FieldFlags::Input );


            map.emplace( OperatorType::ROIAlign1, std::move( typeInfo ) );
        }

        void AddROIAlignGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 );
            auto dimensions = Range( 4, 4 );
            auto roiDimensions = Range( 2, 4 );
            auto indicesDimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ROIAlignGrad" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ROITensor", FieldFlags::Input, dataTypes, roiDimensions );
            typeInfo->AddInputTensor( "BatchIndicesTensor", FieldFlags::Input, indicesDataTypes, indicesDimensions );

            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputROIGradientTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, roiDimensions );

            typeInfo->AddEnum( "ReductionFunction", EnumType::ReduceFunction, FieldFlags::Input );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );
            typeInfo->AddFloat32( "SpatialScaleX", FieldFlags::Input );
            typeInfo->AddFloat32( "SpatialScaleY", FieldFlags::Input );
            typeInfo->AddFloat32( "InputPixelOffset", FieldFlags::Input );
            typeInfo->AddFloat32( "OutputPixelOffset", FieldFlags::Input );
            typeInfo->AddFloat32( "OutOfBoundsInputValue", FieldFlags::Input );
            typeInfo->AddUInt32( "MinimumSamplesPerOutput", FieldFlags::Input );
            typeInfo->AddUInt32( "MaximumSamplesPerOutput", FieldFlags::Input );
            typeInfo->AddBoolean( "AlignRegionsToCorners", FieldFlags::Input );


            map.emplace( OperatorType::ROIAlignGrad, std::move( typeInfo ) );
        }

        void AddBatchNormalizationTraining( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "BatchNormalizationTraining" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "FusedAddTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );
            

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputMeanTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputVarianceTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::BatchNormalizationTraining, std::move( typeInfo ) );
        }

        void AddBatchNormalizationTrainingGrad( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "BatchNormalizationTrainingGrad" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "MeanTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "VarianceTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, dataTypes );
            


            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputScaleGradientTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddOutputTensor( "OutputBiasGradientTensor", FieldFlags::Output, dataTypes );

            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );

            map.emplace( OperatorType::BatchNormalizationTrainingGrad, std::move( typeInfo ) );
        }


        void AddElementWiseClip1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseClip1", dataTypes, dataTypes );

            typeInfo->AddTensorDataType( "MinMaxDataType", FieldFlags::Input );
            typeInfo->AddScalarUnion( "Min", FieldFlags::Input );
            typeInfo->AddScalarUnion( "Max", FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseClip1, std::move( typeInfo ) );
        }

        void AddElementWiseClipGrad1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseClipGrad1" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddTensorDataType( "MinMaxDataType", FieldFlags::Input );
            typeInfo->AddScalarUnion( "Min", FieldFlags::Input );
            typeInfo->AddScalarUnion( "Max", FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseClipGrad1, std::move( typeInfo ) );
        }

        void AddPadding1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Padding1", dataTypes, dataTypes );
            typeInfo->AddEnum( "PaddingMode", EnumType::PaddingMode, FieldFlags::Input );
            typeInfo->AddTensorDataType( "PaddingValueDataType", FieldFlags::Input );
            typeInfo->AddScalarUnion( "PaddingValue", FieldFlags::Input );
            typeInfo->AddSize( "DimensionCount", 2, FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::Padding1, std::move( typeInfo ) );
        }

        void AddElementWiseNegate( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 );

            auto typeInfo = MakeInplaceUnary( "ElementWiseNegate", dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseNegate, std::move( typeInfo ) );
        }

        void AddActivationGeLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16  );

            auto typeInfo = MakeInplaceUnary( "ActivationGeLU", dataTypes, dataTypes );

            map.emplace( OperatorType::ActivationGeLU, std::move( typeInfo ) );
        }

        void AddActivationSoftMax1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnary( "ActivationSoftMax1", dataTypes, dataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );

            map.emplace( OperatorType::ActivationSoftMax1, std::move( typeInfo ) );
        }

        void AddActivationLogSoftMax1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnary( "ActivationLogSoftMax1", dataTypes, dataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );

            map.emplace( OperatorType::ActivationLogSoftMax1, std::move( typeInfo ) );
        }

        void AddActivationHardMax1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnaryWithScaleBias( "ActivationHardMax1", dataTypes, dataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );

            map.emplace( OperatorType::ActivationHardMax1, std::move( typeInfo ) );
        }

        void AddResample2( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = MakeUnary( "Resample2", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );
            typeInfo->AddEnum( "RoundingDirection", EnumType::AxisDirection, FieldFlags::Input );

            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );
            typeInfo->AddFloat32Array( "InputPixelOffsets", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPixelOffsets", FieldFlags::Input );

            map.emplace( OperatorType::Resample2, std::move( typeInfo ) );
        }

        void AddResampleGrad1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ResampleGrad1" );

            typeInfo->AddInputTensor( "InputGradientTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputGradientTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );
            typeInfo->AddEnum( "RoundingDirection", EnumType::AxisDirection, FieldFlags::Input );

            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );
            typeInfo->AddFloat32Array( "InputPixelOffsets", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPixelOffsets", FieldFlags::Input );


            map.emplace( OperatorType::ResampleGrad1, std::move( typeInfo ) );
        }

        void AddDiagonalMatrix1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 2, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "DiagonalMatrix1" );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddTensorDataType( "ValueDataType", FieldFlags::Input );
            typeInfo->AddScalarUnion( "Value", FieldFlags::Input );
            typeInfo->AddInt32( "DiagonalFillBegin", FieldFlags::Input );
            typeInfo->AddInt32( "DiagonalFillEnd", FieldFlags::Input );

            map.emplace( OperatorType::DiagonalMatrix1, std::move( typeInfo ) );
        }


        void AddMultiheadAttention( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 );
            auto maskDataTypes = supportedDataTypes & TensorDataTypeMask::Int32;

            auto dimensions3_5 = Range( 3, 5 );
            auto dimensions5_5 = Range( 5, 5 );
            auto dimensions1_5 = Range( 1, 5 );
            auto dimensions4_5 = Range( 4, 5 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MultiheadAttention" );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions3_5 );
            typeInfo->AddInputTensor( "KeyTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions3_5 );
            typeInfo->AddInputTensor( "ValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions3_5 );
            typeInfo->AddInputTensor( "StackedQueryKeyTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions5_5 );
            typeInfo->AddInputTensor( "StackedKeyValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions5_5 );
            typeInfo->AddInputTensor( "StackedQueryKeyValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions5_5 );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions1_5 );
            typeInfo->AddInputTensor( "MaskTensor", FieldFlags::Input | FieldFlags::Optional, maskDataTypes, dimensions1_5 );
            typeInfo->AddInputTensor( "RelativePositionBiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddInputTensor( "PastKeyTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddInputTensor( "PastValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions4_5 );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions3_5 );
            typeInfo->AddOutputTensor( "OutputPresentKeyTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddOutputTensor( "OutputPresentValueTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions4_5 );

            typeInfo->AddFloat32( "Scale", FieldFlags::Input );
            typeInfo->AddFloat32( "MaskFilterValue", FieldFlags::Input );
            typeInfo->AddUInt32( "HeadCount", FieldFlags::Input );
            typeInfo->AddEnum( "MaskType", EnumType::MultiheadAttentionMaskType, FieldFlags::Input );

            map.emplace( OperatorType::MultiheadAttention, std::move( typeInfo ) );
        }

        void AddLPPooling1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "LPPooling1", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddUInt32( "P", FieldFlags::Input );

            map.emplace( OperatorType::LPPooling1, std::move( typeInfo ) );
        }

        void AddAveragePooling1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "AveragePooling1", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddBoolean( "IncludePadding", FieldFlags::Input );

            map.emplace( OperatorType::AveragePooling1, std::move( typeInfo ) );
        }

        void AddActivationSwish( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnary( "ActivationSwish", dataTypes, dataTypes );
            typeInfo->AddFloat32( "SigmoidInputScale", FieldFlags::Input );

            map.emplace( OperatorType::ActivationSwish, std::move( typeInfo ) );
        }

        void AddActivationHardSwish( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnary( "ActivationHardSwish", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );

            map.emplace( OperatorType::ActivationHardSwish, std::move( typeInfo ) );
        }

        void AddQuantizedLinearAveragePooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto scaleDataTypes = supportedDataTypes & TensorDataTypeMask::Float32;

            auto dimensions = Range( 4, 5 );
            auto scaleAndZeroPointDimensions = Range( 1, 5 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "QuantizedLinearAveragePooling" );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "InputScaleTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "InputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, scaleAndZeroPointDimensions );
            typeInfo->AddInputTensor( "OutputScaleTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "OutputZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, scaleAndZeroPointDimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddBoolean( "IncludePadding", FieldFlags::Input );

            map.emplace( OperatorType::QuantizedLinearAveragePooling, std::move( typeInfo ) );
        }

        void AddMatrixMultiplyIntegerToFloat( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto integralDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto floatingpointDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions2_4 = Range( 2, 4 );
            auto dimensions1_4 = Range( 1, 4 );
            

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MatrixMultiplyIntegerToFloat" );

            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, integralDataTypes, dimensions2_4 );
            typeInfo->AddInputTensor( "AScaleTensor", FieldFlags::Input, floatingpointDataTypes, dimensions1_4 );
            typeInfo->AddInputTensor( "AZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, integralDataTypes, dimensions1_4 );

            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, integralDataTypes, dimensions2_4 );
            typeInfo->AddInputTensor( "BScaleTensor", FieldFlags::Input, floatingpointDataTypes, dimensions1_4 );
            typeInfo->AddInputTensor( "BZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, integralDataTypes, dimensions1_4 );

            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, floatingpointDataTypes, dimensions2_4 );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::Optional, floatingpointDataTypes, dimensions2_4 );

            map.emplace( OperatorType::MatrixMultiplyIntegerToFloat, std::move( typeInfo ) );
        }


        void AddMeanVarianceNormalization2( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MeanVarianceNormalization2" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );

            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );
            typeInfo->AddBoolean( "UseMean", FieldFlags::Input );
            typeInfo->AddBoolean( "UseVariance", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::MeanVarianceNormalization2, std::move( typeInfo ) );
        }

        void AddMultiheadAttention1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 );
            auto maskDataTypes = supportedDataTypes & TensorDataTypeMask::Int32;

            auto dimensions3_5 = Range( 3, 5 );
            auto dimensions5_5 = Range( 5, 5 );
            auto dimensions1_5 = Range( 1, 5 );
            auto dimensions4_5 = Range( 4, 5 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MultiheadAttention1" );

            typeInfo->AddInputTensor( "QueryTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions3_5 );
            typeInfo->AddInputTensor( "KeyTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions3_5 );
            typeInfo->AddInputTensor( "ValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions3_5 );
            typeInfo->AddInputTensor( "StackedQueryKeyTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions5_5 );
            typeInfo->AddInputTensor( "StackedKeyValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions5_5 );
            typeInfo->AddInputTensor( "StackedQueryKeyValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions5_5 );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions1_5 );
            typeInfo->AddInputTensor( "MaskTensor", FieldFlags::Input | FieldFlags::Optional, maskDataTypes, dimensions1_5 );
            typeInfo->AddInputTensor( "RelativePositionBiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddInputTensor( "PastKeyTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddInputTensor( "PastValueTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddInputTensor( "PastSequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions1_5 );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions3_5 );
            typeInfo->AddOutputTensor( "OutputPresentKeyTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions4_5 );
            typeInfo->AddOutputTensor( "OutputPresentValueTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions4_5 );

            typeInfo->AddFloat32( "Scale", FieldFlags::Input );
            typeInfo->AddFloat32( "MaskFilterValue", FieldFlags::Input );
            typeInfo->AddUInt32( "QueryHeadCount", FieldFlags::Input );
            typeInfo->AddUInt32( "KeyValueHeadCount", FieldFlags::Input );
            typeInfo->AddEnum( "MaskType", EnumType::MultiheadAttentionMaskType, FieldFlags::Input );

            map.emplace( OperatorType::MultiheadAttention1, std::move( typeInfo ) );
        }


        void AddQuantize( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto quantizationDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::Int4 | TensorDataTypeMask::UInt8 | TensorDataTypeMask::UInt4 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::Int4 | TensorDataTypeMask::UInt8 | TensorDataTypeMask::UInt4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Quantize" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddEnum( "QuantizationType", EnumType::QuantizationType, FieldFlags::Input );
            typeInfo->AddSize( "QuantizationTensorCount", 1, FieldFlags::Input );
            typeInfo->AddInputTensor( "QuantizationTensors", FieldFlags::Input, quantizationDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes );

            map.emplace( OperatorType::Quantize, std::move( typeInfo ) );
        }

        void AddDequantize( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::Int4 | TensorDataTypeMask::UInt8 | TensorDataTypeMask::UInt4 );
            auto quantizationDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::Int4 | TensorDataTypeMask::UInt8 | TensorDataTypeMask::UInt4 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Dequantize" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddEnum( "QuantizationType", EnumType::QuantizationType, FieldFlags::Input );
            typeInfo->AddSize( "QuantizationTensorCount", 1, FieldFlags::Input );
            typeInfo->AddInputTensor( "QuantizationTensors", FieldFlags::Input, quantizationDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes );

            map.emplace( OperatorType::Quantize, std::move( typeInfo ) );
        }

        void AddResample3( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = MakeUnary( "Resample3", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );
            typeInfo->AddEnum( "RoundingDirection", EnumType::AxisDirection, FieldFlags::Input );

            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );
            typeInfo->AddFloat32Array( "InputPixelOffsets", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPixelOffsets", FieldFlags::Input );
            typeInfo->AddBoolean( "Antialiased", FieldFlags::Input );

            map.emplace( OperatorType::Resample3, std::move( typeInfo ) );
        }


        void AddFold( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 3, 8 );

            auto typeInfo = MakeUnary( "Fold", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddFloat32Array( "WindowSizes", FieldFlags::Input );
            typeInfo->AddFloat32Array( "Strides", FieldFlags::Input );
            typeInfo->AddFloat32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddFloat32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddFloat32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::Fold, std::move( typeInfo ) );
        }

        void AddUnfold( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 3, 8 );

            auto typeInfo = MakeUnary( "Unfold", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddFloat32Array( "WindowSizes", FieldFlags::Input );
            typeInfo->AddFloat32Array( "Strides", FieldFlags::Input );
            typeInfo->AddFloat32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddFloat32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddFloat32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::Unfold, std::move( typeInfo ) );
        }



        std::unordered_map<DML::OperatorType, std::unique_ptr<DML::OperatorTypeInfo>> InitializeOperatorTypeInfoMap( const Device& device )
        {
            std::unordered_map<DML::OperatorType, std::unique_ptr<DML::OperatorTypeInfo>> result;

            FeatureLevel featureLevel = device.SupportedFeatureLevel( );
            TensorDataTypeMask supportedDataTypes = device.SupportedTensorDataTypes( );

            AddElementWiseIdentity( featureLevel, supportedDataTypes, result );
            AddElementWiseAbs( featureLevel, supportedDataTypes, result );
            AddElementWiseACos( featureLevel, supportedDataTypes, result );
            AddElementWiseAdd( featureLevel, supportedDataTypes, result );
            AddElementWiseAdd1( featureLevel, supportedDataTypes, result );
            AddElementWiseASin( featureLevel, supportedDataTypes, result );
            AddElementWiseATan( featureLevel, supportedDataTypes, result );
            AddElementWiseCeil( featureLevel, supportedDataTypes, result );
            AddElementWiseClip( featureLevel, supportedDataTypes, result );
            AddElementWiseCos( featureLevel, supportedDataTypes, result );
            AddElementWiseDivide( featureLevel, supportedDataTypes, result );
            AddElementWiseExp( featureLevel, supportedDataTypes, result );
            AddElementWiseLog( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalAnd( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalEquals( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalGreaterThan( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalLessThan( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalNot( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalOr( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalXor( featureLevel, supportedDataTypes, result );
            AddElementWiseMax( featureLevel, supportedDataTypes, result );
            AddElementWiseMean( featureLevel, supportedDataTypes, result );
            AddElementWiseMin( featureLevel, supportedDataTypes, result );
            AddElementWiseMultiply( featureLevel, supportedDataTypes, result );
            AddElementWisePow( featureLevel, supportedDataTypes, result );
            AddElementWiseConstantPow( featureLevel, supportedDataTypes, result );
            AddElementWiseReciprocal( featureLevel, supportedDataTypes, result );
            AddElementWiseSin( featureLevel, supportedDataTypes, result );
            AddElementWiseSqrt( featureLevel, supportedDataTypes, result );
            AddElementWiseSubtract( featureLevel, supportedDataTypes, result );
            AddElementWiseTan( featureLevel, supportedDataTypes, result );
            AddElementWiseThreshold( featureLevel, supportedDataTypes, result );
            AddElementWiseQuantizeLinear( featureLevel, supportedDataTypes, result );
            AddElementWiseDequantizeLinear( featureLevel, supportedDataTypes, result );
            AddActivationELU( featureLevel, supportedDataTypes, result );
            AddActivationHardMax( featureLevel, supportedDataTypes, result );
            AddActivationHardSigmoid( featureLevel, supportedDataTypes, result );
            AddActivationIdentity( featureLevel, supportedDataTypes, result );
            AddActivationLeakyReLU( featureLevel, supportedDataTypes, result );
            AddActivationLinear( featureLevel, supportedDataTypes, result );
            AddActivationLogSoftMax( featureLevel, supportedDataTypes, result );
            AddActivationParameterizedReLU( featureLevel, supportedDataTypes, result );
            AddActivationParametricSoftPlus( featureLevel, supportedDataTypes, result );
            AddActivationReLU( featureLevel, supportedDataTypes, result );
            AddActivationScaledELU( featureLevel, supportedDataTypes, result );
            AddActivationScaledTanH( featureLevel, supportedDataTypes, result );
            AddActivationSigmoid( featureLevel, supportedDataTypes, result );
            AddActivationSoftMax( featureLevel, supportedDataTypes, result );
            AddActivationSoftPlus( featureLevel, supportedDataTypes, result );
            AddActivationSoftSign( featureLevel, supportedDataTypes, result );
            AddActivationTanH( featureLevel, supportedDataTypes, result );
            AddActivationThresholdedReLU( featureLevel, supportedDataTypes, result );
            AddConvolution( featureLevel, supportedDataTypes, result );
            AddGEMM( featureLevel, supportedDataTypes, result );
            AddReduce( featureLevel, supportedDataTypes, result );
            AddAveragePooling( featureLevel, supportedDataTypes, result );
            AddLPPooling( featureLevel, supportedDataTypes, result );
            AddROIPooling( featureLevel, supportedDataTypes, result );
            AddSlice( featureLevel, supportedDataTypes, result );
            AddCast( featureLevel, supportedDataTypes, result );
            AddSplit( featureLevel, supportedDataTypes, result );
            AddJoin( featureLevel, supportedDataTypes, result );
            AddPadding( featureLevel, supportedDataTypes, result );
            AddValueScale2D( featureLevel, supportedDataTypes, result );
            AddUpSample2D( featureLevel, supportedDataTypes, result );
            AddGather( featureLevel, supportedDataTypes, result );
            AddSpaceToDepth( featureLevel, supportedDataTypes, result );
            AddDepthToSpace( featureLevel, supportedDataTypes, result );
            AddTile( featureLevel, supportedDataTypes, result );
            AddTopK( featureLevel, supportedDataTypes, result );
            AddBatchNormalization( featureLevel, supportedDataTypes, result );
            AddMeanVarianceNormalization( featureLevel, supportedDataTypes, result );
            AddLocalResponseNormalization( featureLevel, supportedDataTypes, result );
            AddLPNormalization( featureLevel, supportedDataTypes, result );
            AddRNN( featureLevel, supportedDataTypes, result );
            AddLSTM( featureLevel, supportedDataTypes, result );
            AddGRU( featureLevel, supportedDataTypes, result );
            AddElementWiseSign( featureLevel, supportedDataTypes, result );
            AddElementWiseIsNaN( featureLevel, supportedDataTypes, result );
            AddElementWiseErf( featureLevel, supportedDataTypes, result );
            AddElementWiseSinH( featureLevel, supportedDataTypes, result );
            AddElementWiseCosH( featureLevel, supportedDataTypes, result );
            AddElementWiseTanH( featureLevel, supportedDataTypes, result );
            AddElementWiseASinH( featureLevel, supportedDataTypes, result );
            AddElementWiseACosH( featureLevel, supportedDataTypes, result );
            AddElementWiseATanH( featureLevel, supportedDataTypes, result );
            AddElementWiseIf( featureLevel, supportedDataTypes, result );
            AddActivationShrink( featureLevel, supportedDataTypes, result );
            AddMaxPooling1( featureLevel, supportedDataTypes, result );
            AddMaxUnpooling( featureLevel, supportedDataTypes, result );
            AddDiagonalMatrix( featureLevel, supportedDataTypes, result );
            AddScatterElements( featureLevel, supportedDataTypes, result );
            AddOneHot( featureLevel, supportedDataTypes, result );
            AddResample( featureLevel, supportedDataTypes, result );
            AddElementWiseBitShiftLeft( featureLevel, supportedDataTypes, result );
            AddElementWiseBitShiftRight( featureLevel, supportedDataTypes, result );
            AddElementWiseRound( featureLevel, supportedDataTypes, result );
            AddElementWiseIsInfinity( featureLevel, supportedDataTypes, result );
            AddElementWiseModulusTruncate( featureLevel, supportedDataTypes, result );
            AddElementWiseModulusFloor( featureLevel, supportedDataTypes, result );
            AddFillValueConstant( featureLevel, supportedDataTypes, result );
            AddFillValueSequence( featureLevel, supportedDataTypes, result );
            AddReverseSubsequences( featureLevel, supportedDataTypes, result );
            AddGatherElements( featureLevel, supportedDataTypes, result );
            AddGatherND( featureLevel, supportedDataTypes, result );
            AddScatterND( featureLevel, supportedDataTypes, result );
            AddMaxPooling2( featureLevel, supportedDataTypes, result );
            AddSlice1( featureLevel, supportedDataTypes, result );
            AddTopK1( featureLevel, supportedDataTypes, result );
            AddDepthToSpace1( featureLevel, supportedDataTypes, result );
            AddSpaceToDepth1( featureLevel, supportedDataTypes, result );
            AddMeanVarianceNormalization1( featureLevel, supportedDataTypes, result );
            AddResample1( featureLevel, supportedDataTypes, result );
            AddMatrixMultiplyInteger( featureLevel, supportedDataTypes, result );
            AddQuantizedLinearMatrixMultiply( featureLevel, supportedDataTypes, result );
            AddConvolutionInteger( featureLevel, supportedDataTypes, result );
            AddQuantizedLinearConvolution( featureLevel, supportedDataTypes, result );
            AddElementWiseBitAnd( featureLevel, supportedDataTypes, result );
            AddElementWiseBitOr( featureLevel, supportedDataTypes, result );
            AddElementWiseBitXor( featureLevel, supportedDataTypes, result );
            AddElementWiseBitNot( featureLevel, supportedDataTypes, result );
            AddElementWiseBitCount( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalGreaterThanOrEqual( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalLessThanOrEqual( featureLevel, supportedDataTypes, result );
            AddActivationCeLU( featureLevel, supportedDataTypes, result );
            AddActivationReLUGrad( featureLevel, supportedDataTypes, result );
            AddAveragePoolingGrad( featureLevel, supportedDataTypes, result );
            AddMaxPoolingGrad( featureLevel, supportedDataTypes, result );
            AddRandomGenerator( featureLevel, supportedDataTypes, result );
            AddNonZeroCoordinates( featureLevel, supportedDataTypes, result );
            AddResampleGrad( featureLevel, supportedDataTypes, result );
            AddSliceGrad( featureLevel, supportedDataTypes, result );
            AddAdamOptimizer( featureLevel, supportedDataTypes, result );
            AddArgMin( featureLevel, supportedDataTypes, result );
            AddArgMax( featureLevel, supportedDataTypes, result );
            AddROIAlign( featureLevel, supportedDataTypes, result );
            AddGatherND1( featureLevel, supportedDataTypes, result );
            AddElementWiseATanYX( featureLevel, supportedDataTypes, result );
            AddElementWiseClipGrad( featureLevel, supportedDataTypes, result );
            AddElementWiseDifferenceSquare( featureLevel, supportedDataTypes, result );
            AddLocalResponseNormalizationGrad( featureLevel, supportedDataTypes, result );
            AddCumulativeProduct( featureLevel, supportedDataTypes, result );
            AddBatchNormalizationGrad( featureLevel, supportedDataTypes, result );
            AddElementWiseQuantizedLinearAdd( featureLevel, supportedDataTypes, result );
            AddDynamicQuantizeLinear( featureLevel, supportedDataTypes, result );
            AddROIAlign1( featureLevel, supportedDataTypes, result );
            AddROIAlignGrad( featureLevel, supportedDataTypes, result );
            AddBatchNormalizationTraining( featureLevel, supportedDataTypes, result );
            AddBatchNormalizationTrainingGrad( featureLevel, supportedDataTypes, result );
            AddElementWiseClip1( featureLevel, supportedDataTypes, result );
            AddElementWiseClipGrad1( featureLevel, supportedDataTypes, result );
            AddPadding1( featureLevel, supportedDataTypes, result );
            AddElementWiseNegate( featureLevel, supportedDataTypes, result );
            AddActivationGeLU( featureLevel, supportedDataTypes, result );
            AddActivationSoftMax1( featureLevel, supportedDataTypes, result );
            AddActivationLogSoftMax1( featureLevel, supportedDataTypes, result );
            AddActivationHardMax1( featureLevel, supportedDataTypes, result );
            AddResample2( featureLevel, supportedDataTypes, result );
            AddResampleGrad1( featureLevel, supportedDataTypes, result );
            AddDiagonalMatrix1( featureLevel, supportedDataTypes, result );
            AddMultiheadAttention( featureLevel, supportedDataTypes, result );
            AddLPPooling1( featureLevel, supportedDataTypes, result );
            AddAveragePooling1( featureLevel, supportedDataTypes, result );
            AddActivationSwish( featureLevel, supportedDataTypes, result );
            AddActivationHardSwish( featureLevel, supportedDataTypes, result );
            AddQuantizedLinearAveragePooling( featureLevel, supportedDataTypes, result );
            AddMatrixMultiplyIntegerToFloat( featureLevel, supportedDataTypes, result );
            AddMeanVarianceNormalization2( featureLevel, supportedDataTypes, result );
            AddMultiheadAttention1( featureLevel, supportedDataTypes, result );
            AddQuantize( featureLevel, supportedDataTypes, result );
            AddDequantize( featureLevel, supportedDataTypes, result );
            AddResample3( featureLevel, supportedDataTypes, result );
            AddFold( featureLevel, supportedDataTypes, result );
            AddUnfold( featureLevel, supportedDataTypes, result );

            return result;
        }

        
    }

    HAI_EXPORT OperatorTypeInfoMap Device::GetOperatorTypeInfo( ) const
    {
        return InitializeOperatorTypeInfoMap( *this );
    }


}

