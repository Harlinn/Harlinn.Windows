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
#include "HCCFlags.h"

namespace Harlinn::AI::DML
{
    namespace
    {
        class TensorDataTypeConverter : public Enum<TensorDataType>
        {
        public:
            using Base = Enum<TensorDataType>;
            TensorDataTypeConverter( )
            {
                Add( L"Unknown", TensorDataType::Unknown );
                Add( L"Float32", TensorDataType::Float32 );
                Add( L"Single", TensorDataType::Single );
                Add( L"Float16", TensorDataType::Float16 );
                Add( L"Half", TensorDataType::Half );
                Add( L"UInt32", TensorDataType::UInt32 );
                Add( L"UInt16", TensorDataType::UInt16 );
                Add( L"UInt8", TensorDataType::UInt8 );
                Add( L"Int32", TensorDataType::Int32 );
                Add( L"Int16", TensorDataType::Int16 );
                Add( L"Int8", TensorDataType::Int8 );
                Add( L"Float64", TensorDataType::Float64 );
                Add( L"Double", TensorDataType::Double );
                Add( L"UInt64", TensorDataType::UInt64 );
                Add( L"Int64", TensorDataType::Int64 );
                Add( L"UInt4", TensorDataType::UInt4 );
                Add( L"Int4", TensorDataType::Int4 );

            }
        };

        TensorDataTypeConverter tensorDataTypeConverter;
    }

    namespace
    {
        class TensorDataTypeMaskConverter : public Flags<TensorDataTypeMask>
        {
        public:
            using Base = Flags<TensorDataTypeMask>;
            TensorDataTypeMaskConverter( )
            {
                Add( L"Unknown", TensorDataTypeMask::Unknown );
                Add( L"Float32", TensorDataTypeMask::Float32 );
                Add( L"Single", TensorDataTypeMask::Single );
                Add( L"Float16", TensorDataTypeMask::Float16 );
                Add( L"Half", TensorDataTypeMask::Half );
                Add( L"UInt32", TensorDataTypeMask::UInt32 );
                Add( L"UInt16", TensorDataTypeMask::UInt16 );
                Add( L"UInt8", TensorDataTypeMask::UInt8 );
                Add( L"Int32", TensorDataTypeMask::Int32 );
                Add( L"Int16", TensorDataTypeMask::Int16 );
                Add( L"Int8", TensorDataTypeMask::Int8 );
                Add( L"Float64", TensorDataTypeMask::Float64 );
                Add( L"Double", TensorDataTypeMask::Double );
                Add( L"UInt64", TensorDataTypeMask::UInt64 );
                Add( L"Int64", TensorDataTypeMask::Int64 );
                Add( L"UInt4", TensorDataTypeMask::UInt4 );
                Add( L"Int4", TensorDataTypeMask::Int4 );
                Add( L"All", TensorDataTypeMask::All );
                Add( L"AllButNibble", TensorDataTypeMask::AllButNibble );
                Add( L"AllFloat", TensorDataTypeMask::AllFloat );
                Add( L"SmallerFloats", TensorDataTypeMask::SmallerFloats );
            }
        };

        TensorDataTypeMaskConverter tensorDataTypeMaskConverter;
    }

    namespace
    {
        class TensorTypeConverter : public Enum<TensorType>
        {
        public:
            using Base = Enum<TensorType>;
            TensorTypeConverter( )
            {
                Add( L"Invalid", TensorType::Invalid );
                Add( L"Buffer", TensorType::Buffer );
            }
        };

        TensorTypeConverter tensorTypeConverter;
    }

    namespace
    {
        class TensorFlagsConverter : public Flags<TensorFlags>
        {
        public:
            using Base = Flags<TensorFlags>;
            TensorFlagsConverter( )
            {
                Add( L"None", TensorFlags::None );
                Add( L"OwnedByDML", TensorFlags::OwnedByDML );
            }
        };

        TensorFlagsConverter tensorFlagsConverter;
    }

    namespace
    {
        class OperatorTypeConverter : public Enum<OperatorType>
        {
        public:
            using Base = Enum<OperatorType>;
            OperatorTypeConverter( )
            {
                Add( L"Invalid", OperatorType::Invalid );
                Add( L"ElementWiseIdentity", OperatorType::ElementWiseIdentity );
                Add( L"ElementWiseAbs", OperatorType::ElementWiseAbs );
                Add( L"ElementWiseACos", OperatorType::ElementWiseACos );
                Add( L"ElementWiseAdd", OperatorType::ElementWiseAdd );
                Add( L"ElementWiseASin", OperatorType::ElementWiseASin );
                Add( L"ElementWiseATan", OperatorType::ElementWiseATan );
                Add( L"ElementWiseCeil", OperatorType::ElementWiseCeil );
                Add( L"ElementWiseClip", OperatorType::ElementWiseClip );
                Add( L"ElementWiseCos", OperatorType::ElementWiseCos );
                Add( L"ElementWiseDivide", OperatorType::ElementWiseDivide );
                Add( L"ElementWiseExp", OperatorType::ElementWiseExp );
                Add( L"ElementWiseFloor", OperatorType::ElementWiseFloor );
                Add( L"ElementWiseLog", OperatorType::ElementWiseLog );
                Add( L"ElementWiseLogicalAnd", OperatorType::ElementWiseLogicalAnd );
                Add( L"ElementWiseLogicalEquals", OperatorType::ElementWiseLogicalEquals );
                Add( L"ElementWiseLogicalGreaterThan", OperatorType::ElementWiseLogicalGreaterThan );
                Add( L"ElementWiseLogicalLessThan", OperatorType::ElementWiseLogicalLessThan );
                Add( L"ElementWiseLogicalNot", OperatorType::ElementWiseLogicalNot );
                Add( L"ElementWiseLogicalOr", OperatorType::ElementWiseLogicalOr );
                Add( L"ElementWiseLogicalXor", OperatorType::ElementWiseLogicalXor );
                Add( L"ElementWiseMax", OperatorType::ElementWiseMax );
                Add( L"ElementWiseMean", OperatorType::ElementWiseMean );
                Add( L"ElementWiseMin", OperatorType::ElementWiseMin );
                Add( L"ElementWiseMultiply", OperatorType::ElementWiseMultiply );
                Add( L"ElementWisePow", OperatorType::ElementWisePow );
                Add( L"ElementWiseConstantPow", OperatorType::ElementWiseConstantPow );
                Add( L"ElementWiseReciprocal", OperatorType::ElementWiseReciprocal );
                Add( L"ElementWiseSin", OperatorType::ElementWiseSin );
                Add( L"ElementWiseSqrt", OperatorType::ElementWiseSqrt );
                Add( L"ElementWiseSubtract", OperatorType::ElementWiseSubtract );
                Add( L"ElementWiseTan", OperatorType::ElementWiseTan );
                Add( L"ElementWiseThreshold", OperatorType::ElementWiseThreshold );
                Add( L"ElementWiseQuantizeLinear", OperatorType::ElementWiseQuantizeLinear );
                Add( L"ElementWiseDequantizeLinear", OperatorType::ElementWiseDequantizeLinear );
                Add( L"ActivationELU", OperatorType::ActivationELU );
                Add( L"ActivationHardMax", OperatorType::ActivationHardMax );
                Add( L"ActivationHardSigmoid", OperatorType::ActivationHardSigmoid );
                Add( L"ActivationIdentity", OperatorType::ActivationIdentity );
                Add( L"ActivationLeakyReLU", OperatorType::ActivationLeakyReLU );
                Add( L"ActivationLinear", OperatorType::ActivationLinear );
                Add( L"ActivationLogSoftMax", OperatorType::ActivationLogSoftMax );
                Add( L"ActivationParameterizedReLU", OperatorType::ActivationParameterizedReLU );
                Add( L"ActivationParametricSoftPlus", OperatorType::ActivationParametricSoftPlus );
                Add( L"ActivationReLU", OperatorType::ActivationReLU );
                Add( L"ActivationScaledELU", OperatorType::ActivationScaledELU );
                Add( L"ActivationScaledTanH", OperatorType::ActivationScaledTanH );
                Add( L"ActivationSigmoid", OperatorType::ActivationSigmoid );
                Add( L"ActivationSoftMax", OperatorType::ActivationSoftMax );
                Add( L"ActivationSoftPlus", OperatorType::ActivationSoftPlus );
                Add( L"ActivationSoftSign", OperatorType::ActivationSoftSign );
                Add( L"ActivationTanH", OperatorType::ActivationTanH );
                Add( L"ActivationThresholdedReLU", OperatorType::ActivationThresholdedReLU );
                Add( L"Convolution", OperatorType::Convolution );
                Add( L"GEMM", OperatorType::GEMM );
                Add( L"Reduce", OperatorType::Reduce );
                Add( L"AveragePooling", OperatorType::AveragePooling );
                Add( L"LPPooling", OperatorType::LPPooling );
                Add( L"MaxPooling", OperatorType::MaxPooling );
                Add( L"ROIPooling", OperatorType::ROIPooling );
                Add( L"Slice", OperatorType::Slice );
                Add( L"Cast", OperatorType::Cast );
                Add( L"Split", OperatorType::Split );
                Add( L"Join", OperatorType::Join );
                Add( L"Padding", OperatorType::Padding );
                Add( L"ValueScale2D", OperatorType::ValueScale2D );
                Add( L"UpSample2D", OperatorType::UpSample2D );
                Add( L"Gather", OperatorType::Gather );
                Add( L"SpaceToDepth", OperatorType::SpaceToDepth );
                Add( L"DepthToSpace", OperatorType::DepthToSpace );
                Add( L"Tile", OperatorType::Tile );
                Add( L"TopK", OperatorType::TopK );
                Add( L"BatchNormalization", OperatorType::BatchNormalization );
                Add( L"MeanVarianceNormalization", OperatorType::MeanVarianceNormalization );
                Add( L"LocalResponseNormalization", OperatorType::LocalResponseNormalization );
                Add( L"LPNormalization", OperatorType::LPNormalization );
                Add( L"RNN", OperatorType::RNN );
                Add( L"LSTM", OperatorType::LSTM );
                Add( L"GRU", OperatorType::GRU );
                Add( L"ElementWiseSign", OperatorType::ElementWiseSign );
                Add( L"ElementWiseIsNaN", OperatorType::ElementWiseIsNaN );
                Add( L"ElementWiseErf", OperatorType::ElementWiseErf );
                Add( L"ElementWiseSinH", OperatorType::ElementWiseSinH );
                Add( L"ElementWiseCosH", OperatorType::ElementWiseCosH );
                Add( L"ElementWiseTanH", OperatorType::ElementWiseTanH );
                Add( L"ElementWiseASinH", OperatorType::ElementWiseASinH );
                Add( L"ElementWiseACosH", OperatorType::ElementWiseACosH );
                Add( L"ElementWiseATanH", OperatorType::ElementWiseATanH );
                Add( L"ElementWiseIf", OperatorType::ElementWiseIf );
                Add( L"ElementWiseAdd1", OperatorType::ElementWiseAdd1 );
                Add( L"ActivationShrink", OperatorType::ActivationShrink );
                Add( L"MaxPooling1", OperatorType::MaxPooling1 );
                Add( L"MaxUnpooling", OperatorType::MaxUnpooling );
                Add( L"DiagonalMatrix", OperatorType::DiagonalMatrix );
                Add( L"ScatterElements", OperatorType::ScatterElements );
                Add( L"Scatter", OperatorType::Scatter );
                Add( L"OneHot", OperatorType::OneHot );
                Add( L"Resample", OperatorType::Resample );
                Add( L"ElementWiseBitShiftLeft", OperatorType::ElementWiseBitShiftLeft );
                Add( L"ElementWiseBitShiftRight", OperatorType::ElementWiseBitShiftRight );
                Add( L"ElementWiseRound", OperatorType::ElementWiseRound );
                Add( L"ElementWiseIsInfinity", OperatorType::ElementWiseIsInfinity );
                Add( L"ElementWiseModulusTruncate", OperatorType::ElementWiseModulusTruncate );
                Add( L"ElementWiseModulusFloor", OperatorType::ElementWiseModulusFloor );
                Add( L"FillValueConstant", OperatorType::FillValueConstant );
                Add( L"FillValueSequence", OperatorType::FillValueSequence );
                Add( L"CumulativeSummation", OperatorType::CumulativeSummation );
                Add( L"ReverseSubsequences", OperatorType::ReverseSubsequences );
                Add( L"GatherElements", OperatorType::GatherElements );
                Add( L"GatherND", OperatorType::GatherND );
                Add( L"ScatterND", OperatorType::ScatterND );
                Add( L"MaxPooling2", OperatorType::MaxPooling2 );
                Add( L"Slice1", OperatorType::Slice1 );
                Add( L"TopK1", OperatorType::TopK1 );
                Add( L"DepthToSpace1", OperatorType::DepthToSpace1 );
                Add( L"SpaceToDepth1", OperatorType::SpaceToDepth1 );
                Add( L"MeanVarianceNormalization1", OperatorType::MeanVarianceNormalization1 );
                Add( L"Resample1", OperatorType::Resample1 );
                Add( L"MatrixMultiplyInteger", OperatorType::MatrixMultiplyInteger );
                Add( L"QuantizedLinearMatrixMultiply", OperatorType::QuantizedLinearMatrixMultiply );
                Add( L"ConvolutionInteger", OperatorType::ConvolutionInteger );
                Add( L"QuantizedLinearConvolution", OperatorType::QuantizedLinearConvolution );
                Add( L"ElementWiseBitAnd", OperatorType::ElementWiseBitAnd );
                Add( L"ElementWiseBitOr", OperatorType::ElementWiseBitOr );
                Add( L"ElementWiseBitXor", OperatorType::ElementWiseBitXor );
                Add( L"ElementWiseBitNot", OperatorType::ElementWiseBitNot );
                Add( L"ElementWiseBitCount", OperatorType::ElementWiseBitCount );
                Add( L"ElementWiseLogicalGreaterThanOrEqual", OperatorType::ElementWiseLogicalGreaterThanOrEqual );
                Add( L"ElementWiseLogicalLessThanOrEqual", OperatorType::ElementWiseLogicalLessThanOrEqual );
                Add( L"ActivationCeLU", OperatorType::ActivationCeLU );
                Add( L"ActivationReLUGrad", OperatorType::ActivationReLUGrad );
                Add( L"AveragePoolingGrad", OperatorType::AveragePoolingGrad );
                Add( L"MaxPoolingGrad", OperatorType::MaxPoolingGrad );
                Add( L"RandomGenerator", OperatorType::RandomGenerator );
                Add( L"NonZeroCoordinates", OperatorType::NonZeroCoordinates );
                Add( L"ResampleGrad", OperatorType::ResampleGrad );
                Add( L"SliceGrad", OperatorType::SliceGrad );
                Add( L"AdamOptimizer", OperatorType::AdamOptimizer );
                Add( L"ArgMin", OperatorType::ArgMin );
                Add( L"ArgMax", OperatorType::ArgMax );
                Add( L"ROIAlign", OperatorType::ROIAlign );
                Add( L"GatherND1", OperatorType::GatherND1 );
                Add( L"ElementWiseATanYX", OperatorType::ElementWiseATanYX );
                Add( L"ElementWiseClipGrad", OperatorType::ElementWiseClipGrad );
                Add( L"ElementWiseDifferenceSquare", OperatorType::ElementWiseDifferenceSquare );
                Add( L"LocalResponseNormalizationGrad", OperatorType::LocalResponseNormalizationGrad );
                Add( L"CumulativeProduct", OperatorType::CumulativeProduct );
                Add( L"BatchNormalizationGrad", OperatorType::BatchNormalizationGrad );
                Add( L"ElementWiseQuantizedLinearAdd", OperatorType::ElementWiseQuantizedLinearAdd );
                Add( L"DynamicQuantizeLinear", OperatorType::DynamicQuantizeLinear );
                Add( L"ROIAlign1", OperatorType::ROIAlign1 );
                Add( L"ROIAlignGrad", OperatorType::ROIAlignGrad );
                Add( L"BatchNormalizationTraining", OperatorType::BatchNormalizationTraining );
                Add( L"BatchNormalizationTrainingGrad", OperatorType::BatchNormalizationTrainingGrad );
                Add( L"ElementWiseClip1", OperatorType::ElementWiseClip1 );
                Add( L"ElementWiseClipGrad1", OperatorType::ElementWiseClipGrad1 );
                Add( L"Padding1", OperatorType::Padding1 );
                Add( L"ElementWiseNegate", OperatorType::ElementWiseNegate );
                Add( L"ActivationGeLU", OperatorType::ActivationGeLU );
                Add( L"ActivationSoftMax1", OperatorType::ActivationSoftMax1 );
                Add( L"ActivationLogSoftMax1", OperatorType::ActivationLogSoftMax1 );
                Add( L"ActivationHardMax1", OperatorType::ActivationHardMax1 );
                Add( L"Resample2", OperatorType::Resample2 );
                Add( L"ResampleGrad1", OperatorType::ResampleGrad1 );
                Add( L"DiagonalMatrix1", OperatorType::DiagonalMatrix1 );
                Add( L"MultiheadAttention", OperatorType::MultiheadAttention );
                Add( L"LPPooling1", OperatorType::LPPooling1 );
                Add( L"AveragePooling1", OperatorType::AveragePooling1 );
                Add( L"ActivationSwish", OperatorType::ActivationSwish );
                Add( L"ActivationHardSwish", OperatorType::ActivationHardSwish );
                Add( L"QuantizedLinearAveragePooling", OperatorType::QuantizedLinearAveragePooling );
                Add( L"MatrixMultiplyIntegerToFloat", OperatorType::MatrixMultiplyIntegerToFloat );
                Add( L"MeanVarianceNormalization2", OperatorType::MeanVarianceNormalization2 );
                Add( L"MultiheadAttention1", OperatorType::MultiheadAttention1 );
                Add( L"Quantize", OperatorType::Quantize );
                Add( L"Dequantize", OperatorType::Dequantize );
                Add( L"Resample3", OperatorType::Resample3 );
                Add( L"Fold", OperatorType::Fold );
                Add( L"Unfold", OperatorType::Unfold );
            }
        };

        OperatorTypeConverter operatorTypeConverter;
    }

    namespace
    {
        class ReduceFunctionConverter : public Enum<ReduceFunction>
        {
        public:
            using Base = Enum<ReduceFunction>;
            ReduceFunctionConverter( )
            {
                Add( L"ArgMax", ReduceFunction::ArgMax );
                Add( L"ArgMin", ReduceFunction::ArgMin );
                Add( L"Average", ReduceFunction::Average );
                Add( L"L1", ReduceFunction::L1 );
                Add( L"L2", ReduceFunction::L2 );
                Add( L"LogSum", ReduceFunction::LogSum );
                Add( L"LogSumExp", ReduceFunction::LogSumExp );
                Add( L"Max", ReduceFunction::Max );
                Add( L"Min", ReduceFunction::Min );
                Add( L"Multiply", ReduceFunction::Multiply );
                Add( L"Sum", ReduceFunction::Sum );
                Add( L"SumSquare", ReduceFunction::SumSquare );
            }
        };

        ReduceFunctionConverter reduceFunctionConverter;
    }

    namespace
    {
        class MatrixTransformConverter : public Enum<MatrixTransform>
        {
        public:
            using Base = Enum<MatrixTransform>;
            MatrixTransformConverter( )
            {
                Add( L"None", MatrixTransform::None);
                Add( L"Transpose", MatrixTransform::Transpose );
            }
        };

        MatrixTransformConverter matrixTransformConverter;
    }

    namespace
    {
        class ConvolutionModeConverter : public Enum<ConvolutionMode>
        {
        public:
            using Base = Enum<ConvolutionMode>;
            ConvolutionModeConverter( )
            {
                Add( L"Convolution", ConvolutionMode::Convolution );
                Add( L"CrossCorrelation", ConvolutionMode::CrossCorrelation );
            }
        };

        ConvolutionModeConverter convolutionModeConverter;
    }

    namespace
    {
        class ConvolutionDirectionConverter : public Enum<ConvolutionDirection>
        {
        public:
            using Base = Enum<ConvolutionDirection>;
            ConvolutionDirectionConverter( )
            {
                Add( L"Forward", ConvolutionDirection::Forward );
                Add( L"Backward", ConvolutionDirection::Backward );
            }
        };

        ConvolutionDirectionConverter convolutionDirectionConverter;
    }

    namespace
    {
        class PaddingModeConverter : public Enum<PaddingMode>
        {
        public:
            using Base = Enum<PaddingMode>;
            PaddingModeConverter( )
            {
                Add( L"Constant",PaddingMode::Constant);
                Add( L"Edge",PaddingMode::Edge);
                Add( L"Reflection",PaddingMode::Reflection);
                Add( L"Symmetric",PaddingMode::Symmetric);
                Add( L"Wrap", PaddingMode::Wrap );
            }
        };

        PaddingModeConverter paddingModeConverter;
    }

    namespace
    {
        class InterpolationModeConverter : public Enum<InterpolationMode>
        {
        public:
            using Base = Enum<InterpolationMode>;
            InterpolationModeConverter( )
            {
                Add( L"NearestNeighbor", InterpolationMode::NearestNeighbor );
                Add( L"Linear", InterpolationMode::Linear );
            }
        };

        InterpolationModeConverter interpolationModeConverter;
    }

    namespace
    {
        class RecurrentNetworkDirectionConverter : public Enum<RecurrentNetworkDirection>
        {
        public:
            using Base = Enum<RecurrentNetworkDirection>;
            RecurrentNetworkDirectionConverter( )
            {
                Add( L"Forward", RecurrentNetworkDirection::Forward );
                Add( L"Backward", RecurrentNetworkDirection::Backward );
                Add( L"Bidirectional", RecurrentNetworkDirection::Bidirectional );
            }
        };

        RecurrentNetworkDirectionConverter recurrentNetworkDirectionConverter;
    }

    namespace
    {
        class RoundingModeConverter : public Enum<RoundingMode>
        {
        public:
            using Base = Enum<RoundingMode>;
            RoundingModeConverter( )
            {
                Add( L"HalvesToNearestEven", RoundingMode::HalvesToNearestEven );
                Add( L"TowardZero", RoundingMode::TowardZero );
                Add( L"TowardInfinity", RoundingMode::TowardInfinity );
            }
        };

        RoundingModeConverter roundingModeConverter;
    }

    namespace
    {
        class IsInfinityModeConverter : public Enum<IsInfinityMode>
        {
        public:
            using Base = Enum<IsInfinityMode>;
            IsInfinityModeConverter( )
            {
                Add( L"Either", IsInfinityMode::Either );
                Add( L"Positive", IsInfinityMode::Positive );
                Add( L"Negative", IsInfinityMode::Negative );
            }
        };

        IsInfinityModeConverter isInfinityModeConverter;
    }

    namespace
    {
        class AxisDirectionConverter : public Enum<AxisDirection>
        {
        public:
            using Base = Enum<AxisDirection>;
            AxisDirectionConverter( )
            {
                Add( L"Increasing", AxisDirection::Increasing );
                Add( L"Decreasing", AxisDirection::Decreasing );
            }
        };

        AxisDirectionConverter axisDirectionConverter;
    }

    namespace
    {
        class DepthSpaceOrderConverter : public Enum<DepthSpaceOrder>
        {
        public:
            using Base = Enum<DepthSpaceOrder>;
            DepthSpaceOrderConverter( )
            {
                Add( L"DepthColumnRow", DepthSpaceOrder::DepthColumnRow );
                Add( L"ColumnRowDepth", DepthSpaceOrder::ColumnRowDepth );
            }
        };

        DepthSpaceOrderConverter depthSpaceOrderConverter;
    }

    namespace
    {
        class RandomGeneratorTypeConverter : public Enum<RandomGeneratorType>
        {
        public:
            using Base = Enum<RandomGeneratorType>;
            RandomGeneratorTypeConverter( )
            {
                Add( L"Philox4x32_10", RandomGeneratorType::Philox4x32_10 );
                Add( L"Default", RandomGeneratorType::Philox4x32_10 );
            }
        };

        RandomGeneratorTypeConverter randomGeneratorTypeConverter;
    }

    namespace
    {
        class MultiheadAttentionMaskTypeConverter : public Enum<MultiheadAttentionMaskType>
        {
        public:
            using Base = Enum<MultiheadAttentionMaskType>;
            MultiheadAttentionMaskTypeConverter( )
            {
                Add( L"None", MultiheadAttentionMaskType::None );
                Add( L"KeySequenceLength", MultiheadAttentionMaskType::KeySequenceLength );
                Add( L"KeySequenceEndStart", MultiheadAttentionMaskType::KeySequenceEndStart );
                Add( L"KeyQuerySequenceLengthStartEnd", MultiheadAttentionMaskType::KeyQuerySequenceLengthStartEnd );
                Add( L"Boolean", MultiheadAttentionMaskType::Boolean );
            }
        };

        MultiheadAttentionMaskTypeConverter multiheadAttentionMaskTypeConverter;
    }

    namespace
    {
        class QuantizationTypeConverter : public Enum<QuantizationType>
        {
        public:
            using Base = Enum<QuantizationType>;
            QuantizationTypeConverter( )
            {
                Add( L"None", QuantizationType::None );
                Add( L"Scale", QuantizationType::Scale );
                Add( L"ScaleZeroPoint", QuantizationType::ScaleZeroPoint );
            }
        };

        QuantizationTypeConverter quantizationTypeConverter;
    }

    namespace
    {
        class FieldTypeConverter : public Enum<FieldType>
        {
        public:
            using Base = Enum<FieldType>;
            FieldTypeConverter( )
            {
                Add( L"Unknown", FieldType::Unknown );
                Add( L"Bool", FieldType::Bool );
                Add( L"UInt32", FieldType::UInt32 );
                Add( L"UInt64", FieldType::UInt64 );
                Add( L"Int32", FieldType::Int32 );
                Add( L"Enum", FieldType::Enum );
                Add( L"Flags", FieldType::Flags );
                Add( L"Float32", FieldType::Float32 );
                Add( L"UInt32Array", FieldType::UInt32Array );
                Add( L"Int32Array", FieldType::Int32Array );
                Add( L"Float32Array", FieldType::Float32Array );
                Add( L"ScaleBias", FieldType::ScaleBias );
                Add( L"Size", FieldType::Size );
                Add( L"Size2D", FieldType::Size2D );
                Add( L"ScalarUnion", FieldType::ScalarUnion );
                Add( L"ScalarUnionArray", FieldType::ScalarUnionArray );
                Add( L"TensorDataType", FieldType::TensorDataType );
                Add( L"TensorDesc", FieldType::TensorDesc );
                Add( L"TensorDescArray", FieldType::TensorDescArray );
                Add( L"OperatorDesc", FieldType::OperatorDesc );
                Add( L"OperatorDescArray", FieldType::OperatorDescArray );
                Add( L"FusedActivation", FieldType::FusedActivation );
            }
        };

        FieldTypeConverter fieldTypeConverter;
    }

    namespace
    {
        class FieldFlagsConverter : public Flags<FieldFlags>
        {
        public:
            using Base = Flags<FieldFlags>;
            FieldFlagsConverter( )
            {
                Add( L"None", FieldFlags::None );
                Add( L"Input", FieldFlags::Input );
                Add( L"Output", FieldFlags::Output );
                Add( L"Optional", FieldFlags::Optional );
                Add( L"InplaceExecution", FieldFlags::InplaceExecution );
            }
        };

        FieldFlagsConverter fieldFlagsConverter;
    }

    namespace
    {
        class FeatureLevelConverter : public Enum<FeatureLevel>
        {
        public:
            using Base = Enum<FeatureLevel>;
            FeatureLevelConverter( )
            {
                Add( L"1.0", FeatureLevel::_1_0 );
                Add( L"2.0", FeatureLevel::_2_0 );
                Add( L"2.1", FeatureLevel::_2_1 );
                Add( L"3.0", FeatureLevel::_3_0 );
                Add( L"3.1", FeatureLevel::_3_1 );
                Add( L"4.0", FeatureLevel::_4_0 );
                Add( L"4.1", FeatureLevel::_4_1 );
                Add( L"5.0", FeatureLevel::_5_0 );
                Add( L"5.1", FeatureLevel::_5_1 );
                Add( L"5.2", FeatureLevel::_5_2 );
                Add( L"6.0", FeatureLevel::_6_0 );
                Add( L"6.1", FeatureLevel::_6_1 );
                Add( L"6.2", FeatureLevel::_6_2 );
                Add( L"6.3", FeatureLevel::_6_3 );
                Add( L"6.4", FeatureLevel::_6_4 );
            }
        };

        FeatureLevelConverter featureLevelConverter;
    }

    namespace
    {
        class FeatureConverter : public Enum<Feature>
        {
        public:
            using Base = Enum<Feature>;
            FeatureConverter( )
            {
                Add( L"TensorDataTypeSupport", Feature::TensorDataTypeSupport );
                Add( L"FeatureLevels", Feature::FeatureLevels );
            }
        };

        FeatureConverter featureConverter;
    }

    namespace
    {
        class ExecutionFlagsConverter : public Flags<ExecutionFlags>
        {
        public:
            using Base = Flags<ExecutionFlags>;
            ExecutionFlagsConverter( )
            {
                Add( L"None", ExecutionFlags::None );
                Add( L"AllowHalfPrecisionComputation", ExecutionFlags::AllowHalfPrecisionComputation );
                Add( L"DisableMetaCommands", ExecutionFlags::DisableMetaCommands );
                Add( L"DescriptorsVolatile", ExecutionFlags::DescriptorsVolatile );
            }
        };

        ExecutionFlagsConverter executionFlagsConverter;
    }

    namespace
    {
        class CreateDeviceFlagsConverter : public Flags<CreateDeviceFlags>
        {
        public:
            using Base = Flags<CreateDeviceFlags>;
            CreateDeviceFlagsConverter( )
            {
                Add( L"None", CreateDeviceFlags::None );
                Add( L"Debug", CreateDeviceFlags::Debug );
            }
        };

        CreateDeviceFlagsConverter createDeviceFlagsConverter;
    }

    namespace
    {
        class BindingTypeConverter : public Enum<BindingType>
        {
        public:
            using Base = Enum<BindingType>;
            BindingTypeConverter( )
            {
                Add( L"None", BindingType::None );
                Add( L"Buffer", BindingType::Buffer );
                Add( L"BufferArray", BindingType::BufferArray );
            }
        };

        BindingTypeConverter bindingTypeConverter;
    }

    namespace
    {
        class GraphEdgeTypeConverter : public Enum<GraphEdgeType>
        {
        public:
            using Base = Enum<GraphEdgeType>;
            GraphEdgeTypeConverter( )
            {
                Add( L"Invalid", GraphEdgeType::Invalid );
                Add( L"Input", GraphEdgeType::Input );
                Add( L"Output", GraphEdgeType::Output );
                Add( L"Intermediate", GraphEdgeType::Intermediate );
            }
        };

        GraphEdgeTypeConverter graphEdgeTypeConverter;
    }

    namespace
    {
        class GraphNodeTypeConverter : public Enum<GraphNodeType>
        {
        public:
            using Base = Enum<GraphNodeType>;
            GraphNodeTypeConverter( )
            {
                Add( L"Invalid", GraphNodeType::Invalid );
                Add( L"Operator", GraphNodeType::Operator );
                Add( L"Constant", GraphNodeType::Constant );
            }
        };

        GraphNodeTypeConverter graphNodeTypeConverter;
    }
}

#define HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( enumTypeName, converter ) \
namespace Harlinn::Common::Core \
{ \
    WideString ToWideString( Harlinn::AI::DML::enumTypeName value ) \
    { \
        return Harlinn::AI::DML::converter##Converter.ToString( value ); \
    } \
    WideString ToWideString( Harlinn::AI::DML::enumTypeName value, const WideString& defaultResult ) \
    { \
        return Harlinn::AI::DML::converter##Converter.ToString( value, defaultResult ); \
    } \
} \
namespace Harlinn::AI::DML \
{ \
    enumTypeName Parse##enumTypeName( const WideString& str ) \
    { \
        return converter##Converter.Parse( str ); \
    } \
    enumTypeName Parse##enumTypeName( const WideString& str, enumTypeName defaultResult ) \
    { \
        return converter##Converter.Parse( str, defaultResult ); \
    } \
    bool TryParse##enumTypeName( const WideString& str, enumTypeName& value ) \
    { \
        return converter##Converter.TryParse( str, value ); \
    } \
}


HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( TensorDataType, tensorDataType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( TensorDataTypeMask, tensorDataTypeMask )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( TensorType, tensorType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( TensorFlags, tensorFlags )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( OperatorType, operatorType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( ReduceFunction, reduceFunction )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( MatrixTransform, matrixTransform )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( ConvolutionMode, convolutionMode )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( ConvolutionDirection, convolutionDirection )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( PaddingMode, paddingMode )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( InterpolationMode, interpolationMode )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( RecurrentNetworkDirection, recurrentNetworkDirection )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( RoundingMode, roundingMode )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( IsInfinityMode, isInfinityMode )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( AxisDirection, axisDirection )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( DepthSpaceOrder, depthSpaceOrder )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( RandomGeneratorType, randomGeneratorType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( MultiheadAttentionMaskType, multiheadAttentionMaskType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( QuantizationType, quantizationType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( FieldType, fieldType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( FieldFlags, fieldFlags )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( FeatureLevel, featureLevel )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( Feature, feature )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( ExecutionFlags, executionFlags )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( CreateDeviceFlags, createDeviceFlags )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( BindingType, bindingType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( GraphEdgeType, graphEdgeType )
HAI_IMPLEMENT_ENUM_STRING_CONVERSIONS( GraphNodeType, graphNodeType )
