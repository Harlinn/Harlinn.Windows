#include "pch.h"
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

#include "HAIDirectMLX.h"

namespace Harlinn::AI::DML
{
    namespace
    {
        

        std::unique_ptr<OperatorTypeInfo> MakeUnary( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            return result;
        }
        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnary( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
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

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
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

        std::unique_ptr<OperatorTypeInfo> MakeInplaceBinary( const char* name, TensorDataTypeMask inputATypes, TensorDataTypeMask inputBTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputATypes );
            result->AddInputTensor( "BTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputBTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
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

            return result;
        }

        
    }

    HAI_EXPORT OperatorTypeInfoMap Device::GetOperatorTypeInfo( ) const
    {
        return InitializeOperatorTypeInfoMap( *this );
    }


}
