#pragma once
#ifndef HARLINN_WINDOWS_HAIDIRECTML_H_
#define HARLINN_WINDOWS_HAIDIRECTML_H_

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

#include "HAIDef.h"

#pragma comment(lib, "DirectML.lib")

namespace Harlinn::AI::DML
{
    
#define DML_IMPLEMENT_CONVERSIONS_TO( name ) HWD3D12_IMPLEMENT_CONVERSIONS_TO( name )


    constexpr UInt32 TensorDimensionCountMax = DML_TENSOR_DIMENSION_COUNT_MAX;
#if DML_TARGET_VERSION >= 0x3000
    constexpr UInt32 TensorDimensionCountMax1 = DML_TENSOR_DIMENSION_COUNT_MAX1;
#endif

    constexpr UInt32 TemporaryBufferAlignment = DML_TEMPORARY_BUFFER_ALIGNMENT;
    constexpr UInt32 PersistentBufferAlignment = DML_PERSISTENT_BUFFER_ALIGNMENT;

    constexpr UInt32 MinimumBufferTensorAlignment = DML_MINIMUM_BUFFER_TENSOR_ALIGNMENT;


    class Object;
    class Device;
    class DeviceChild;
    class Pageable;
    class Dispatchable;
    class Operator;
    class CompiledOperator;
    class OperatorInitializer;
    class BindingTable;
    class CommandRecorder;

    /// <summary>
    /// <para>
    /// Alias for DML_TENSOR_DATA_TYPE
    /// </para>
    /// </summary>
    enum class TensorDataType
    {
        Unknown = DML_TENSOR_DATA_TYPE_UNKNOWN,
        Float32 = DML_TENSOR_DATA_TYPE_FLOAT32,
        Single = Float32,
        Float16 = DML_TENSOR_DATA_TYPE_FLOAT16,
        Half = Float16,
        UInt32 = DML_TENSOR_DATA_TYPE_UINT32,
        UInt16 = DML_TENSOR_DATA_TYPE_UINT16,
        UInt8 = DML_TENSOR_DATA_TYPE_UINT8,
        Int32 = DML_TENSOR_DATA_TYPE_INT32,
        Int16 = DML_TENSOR_DATA_TYPE_INT16,
        Int8 = DML_TENSOR_DATA_TYPE_INT8,
        Float64 = DML_TENSOR_DATA_TYPE_FLOAT64,
        Double = Float64,
        UInt64 = DML_TENSOR_DATA_TYPE_UINT64,
        Int64 = DML_TENSOR_DATA_TYPE_INT64,
#if DML_TARGET_VERSION >= 0x6300
        UInt4 = DML_TENSOR_DATA_TYPE_UINT4,
        Int4 = DML_TENSOR_DATA_TYPE_INT4,
#endif
    };

    namespace Internal
    {
        template<typename T>
        struct TensorTraits : public std::false_type
        {
        };

        struct TensorTraitsBase : public std::true_type
        {
        };

        template<>
        struct TensorTraits<float> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Float32;
        };
        template<>
        struct TensorTraits<double> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Float32;
        };
        template<>
        struct TensorTraits<char> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Int8;
        };
        template<>
        struct TensorTraits<signed char> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Int8;
        };
        template<>
        struct TensorTraits<unsigned char> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::UInt8;
        };
        template<>
        struct TensorTraits<Int16> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Int16;
        };
        template<>
        struct TensorTraits<UInt16> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::UInt16;
        };
        template<>
        struct TensorTraits<Int32> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Int32;
        };
        template<>
        struct TensorTraits<UInt32> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::UInt32;
        };
        template<>
        struct TensorTraits<Int64> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::Int64;
        };
        template<>
        struct TensorTraits<UInt64> : public TensorTraitsBase
        {
            constexpr static TensorDataType DataType = TensorDataType::UInt64;
        };

    }


    /// <summary>
    /// <para>
    /// Alias for DML_TENSOR_TYPE
    /// </para>
    /// </summary>
    enum class TensorType
    {
        Invalid = DML_TENSOR_TYPE_INVALID,
        Buffer = DML_TENSOR_TYPE_BUFFER,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_TENSOR_FLAGS
    /// </para>
    /// </summary>
    enum class TensorFlags : UInt32
    {
        None = DML_TENSOR_FLAG_NONE,
        OwnedByDML = DML_TENSOR_FLAG_OWNED_BY_DML,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( TensorFlags, UInt32 );

    inline constexpr UInt64 CalcBufferTensorSize( TensorDataType dataType, UInt32 dimensionCount, _In_reads_( dimensionCount ) const UInt32* sizes, _In_reads_opt_( dimensionCount ) const UInt32* strides )
    {
        UInt32 elementSizeInBits = 0;
        switch ( dataType )
        {
            case TensorDataType::Float64:
            case TensorDataType::UInt64:
            case TensorDataType::Int64:
                elementSizeInBits = 64;
                break;
            case TensorDataType::Float32:
            case TensorDataType::UInt32:
            case TensorDataType::Int32:
                elementSizeInBits = 32;
                break;

            case TensorDataType::Float16:
            case TensorDataType::UInt16:
            case TensorDataType::Int16:
                elementSizeInBits = 16;
                break;

            case TensorDataType::UInt8:
            case TensorDataType::Int8:
                elementSizeInBits = 8;
                break;

#if DML_TARGET_VERSION >= 0x6300
            case TensorDataType::UInt4:
            case TensorDataType::Int4:
                elementSizeInBits = 4;
                break;
#endif
            default:
                return 0; // Invalid data type
        }

        UInt64 minimumImpliedSizeInBits = 0;
        if ( !strides )
        {
            minimumImpliedSizeInBits = sizes[ 0 ];
            for ( UInt32 i = 1; i < dimensionCount; ++i )
            {
                minimumImpliedSizeInBits *= sizes[ i ];
            }
            minimumImpliedSizeInBits *= elementSizeInBits;
        }
        else
        {
            UInt32 indexOfLastElement = 0;
            for ( UInt32 i = 0; i < dimensionCount; ++i )
            {
                indexOfLastElement += ( sizes[ i ] - 1 ) * strides[ i ];
            }

            minimumImpliedSizeInBits = ( static_cast< UINT64 >( indexOfLastElement ) + 1 ) * elementSizeInBits;
        }

        UInt64 minimumImpliedSizeInBytes = ( minimumImpliedSizeInBits + 7 ) / 8;

        // Round up to the nearest 4 bytes.
        minimumImpliedSizeInBytes = ( minimumImpliedSizeInBytes + 3 ) & ~3ull;

        return minimumImpliedSizeInBytes;
    }



    /// <summary>
    /// <para>
    /// Alias for DML_BUFFER_TENSOR_DESC
    /// </para>
    /// </summary>
    struct BufferTensorDesc
    {
        TensorDataType DataType = TensorDataType::Unknown;
        TensorFlags Flags = TensorFlags::None;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Sizes = nullptr;
        _Field_size_opt_( DimensionCount ) const UInt32* Strides = nullptr;
        UInt64 TotalTensorSizeInBytes = 0;
        UInt32 GuaranteedBaseOffsetAlignment = 0;

        BufferTensorDesc( ) noexcept = default;

        BufferTensorDesc( TensorDataType dataType, TensorFlags flags, UInt32 dimensionCount = 0, const UInt32* sizes = nullptr, const UInt32* strides = nullptr )
            : DataType( dataType ), Flags( flags ), DimensionCount( dimensionCount ), Sizes( sizes ), Strides( strides )
        {
            TotalTensorSizeInBytes = CalcBufferTensorSize( dataType, dimensionCount, sizes, strides );
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, UInt32>
        BufferTensorDesc( TensorDataType dataType, const T& sizes, TensorFlags flags = TensorFlags::None )
            : BufferTensorDesc( dataType, flags, static_cast< UInt32 >( sizes.size( ) ), sizes.data( ) )
        {
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, UInt32>
        BufferTensorDesc( TensorDataType dataType, const T& sizes, const T& strides, TensorFlags flags = TensorFlags::None )
            : BufferTensorDesc( dataType, flags, static_cast< UInt32 >( sizes.size( ) ), sizes.data( ), strides.data( ) )
        {
            assert( sizes.size( ) == strides.size( ) );
        }

        template<size_t N>
        BufferTensorDesc( TensorDataType dataType, const UInt32( &sizes )[ N ], TensorFlags flags = TensorFlags::None )
            : BufferTensorDesc( dataType, flags, static_cast< UInt32 >( N ), sizes )
        {
        }
        template<size_t N>
        BufferTensorDesc( TensorDataType dataType, const UInt32( &sizes )[ N ], const UInt32( &strides )[ N ], TensorFlags flags = TensorFlags::None )
            : BufferTensorDesc( dataType, flags, static_cast< UInt32 >( N ), sizes, strides )
        {
        }

        template<size_t N>
        BufferTensorDesc( TensorDataType dataType, const std::array<UInt32, N>& sizes, TensorFlags flags = TensorFlags::None )
            : BufferTensorDesc( dataType, flags, static_cast< UInt32 >( N ), sizes.data( ) )
        {
        }
        template<size_t N>
        BufferTensorDesc( TensorDataType dataType, const std::array<UInt32, N>& sizes, const std::array<UInt32, N>& strides, TensorFlags flags = TensorFlags::None )
            : BufferTensorDesc( dataType, flags, static_cast< UInt32 >( N ), sizes.data( ), strides.data( ) )
        {
        }

        BufferTensorDesc( TensorDataType dataType, TensorFlags flags, UInt32 dimensionCount, const UInt32* sizes, const UInt32* strides, UInt64 totalTensorSizeInBytes, UInt32 guaranteedBaseOffsetAlignment = 0 )
            : DataType( dataType ), Flags( flags ), DimensionCount( dimensionCount ), Sizes( sizes ), Strides( strides ), TotalTensorSizeInBytes( totalTensorSizeInBytes ), GuaranteedBaseOffsetAlignment( guaranteedBaseOffsetAlignment )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BUFFER_TENSOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_TENSOR_DESC
    /// </para>
    /// </summary>
    struct TensorDesc
    {
        TensorType Type = TensorType::Invalid;
        _Field_size_( _Inexpressible_( "Dependent on tensor type" ) ) const void* Desc = nullptr;

        TensorDesc( ) noexcept = default;
        TensorDesc( TensorType type, const void* desc )
            : Type( type ), Desc( desc )
        {
        }

        TensorDesc( const BufferTensorDesc* desc )
            : Type( TensorType::Buffer ), Desc( reinterpret_cast< const void* >( desc ) )
        {
        }

        TensorDesc& operator = ( const BufferTensorDesc* desc )
        {
            Type = TensorType::Buffer;
            Desc = reinterpret_cast< const void* >( desc );
            return *this;
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_TENSOR_DESC );
    };

    // ===================================================================================================================
    //   Operator types
    // ===================================================================================================================

    /// <summary>
    /// <para>
    /// Alias for DML_OPERATOR_TYPE
    /// </para>
    /// </summary>
    enum class OperatorType
    {
        Invalid = DML_OPERATOR_INVALID,
        ElementWiseIdentity = DML_OPERATOR_ELEMENT_WISE_IDENTITY,
        ElementWiseAbs = DML_OPERATOR_ELEMENT_WISE_ABS,
        ElementWiseACos = DML_OPERATOR_ELEMENT_WISE_ACOS,
        ElementWiseAdd = DML_OPERATOR_ELEMENT_WISE_ADD,
        ElementWiseASin = DML_OPERATOR_ELEMENT_WISE_ASIN,
        ElementWiseATan = DML_OPERATOR_ELEMENT_WISE_ATAN,
        ElementWiseCeil = DML_OPERATOR_ELEMENT_WISE_CEIL,
        ElementWiseClip = DML_OPERATOR_ELEMENT_WISE_CLIP,
        ElementWiseCos = DML_OPERATOR_ELEMENT_WISE_COS,
        ElementWiseDivide = DML_OPERATOR_ELEMENT_WISE_DIVIDE,
        ElementWiseExp = DML_OPERATOR_ELEMENT_WISE_EXP,
        ElementWiseFloor = DML_OPERATOR_ELEMENT_WISE_FLOOR,
        ElementWiseLog = DML_OPERATOR_ELEMENT_WISE_LOG,
        ElementWiseLogicalAnd = DML_OPERATOR_ELEMENT_WISE_LOGICAL_AND,
        ElementWiseLogicalEquals = DML_OPERATOR_ELEMENT_WISE_LOGICAL_EQUALS,
        ElementWiseLogicalGreaterThan = DML_OPERATOR_ELEMENT_WISE_LOGICAL_GREATER_THAN,
        ElementWiseLogicalLessThan = DML_OPERATOR_ELEMENT_WISE_LOGICAL_LESS_THAN,
        ElementWiseLogicalNot = DML_OPERATOR_ELEMENT_WISE_LOGICAL_NOT,
        ElementWiseLogicalOr = DML_OPERATOR_ELEMENT_WISE_LOGICAL_OR,
        ElementWiseLogicalXor = DML_OPERATOR_ELEMENT_WISE_LOGICAL_XOR,
        ElementWiseMax = DML_OPERATOR_ELEMENT_WISE_MAX,
        ElementWiseMean = DML_OPERATOR_ELEMENT_WISE_MEAN,
        ElementWiseMin = DML_OPERATOR_ELEMENT_WISE_MIN,
        ElementWiseMultiply = DML_OPERATOR_ELEMENT_WISE_MULTIPLY,
        ElementWisePow = DML_OPERATOR_ELEMENT_WISE_POW,
        ElementWiseConstantPow = DML_OPERATOR_ELEMENT_WISE_CONSTANT_POW,
        ElementWiseReciprocal = DML_OPERATOR_ELEMENT_WISE_RECIP,
        ElementWiseSin = DML_OPERATOR_ELEMENT_WISE_SIN,
        ElementWiseSqrt = DML_OPERATOR_ELEMENT_WISE_SQRT,
        ElementWiseSubtract = DML_OPERATOR_ELEMENT_WISE_SUBTRACT,
        ElementWiseTan = DML_OPERATOR_ELEMENT_WISE_TAN,
        ElementWiseThreshold = DML_OPERATOR_ELEMENT_WISE_THRESHOLD,
        ElementWiseQuantizeLinear = DML_OPERATOR_ELEMENT_WISE_QUANTIZE_LINEAR,
        ElementWiseDequantizeLinear = DML_OPERATOR_ELEMENT_WISE_DEQUANTIZE_LINEAR,
        ActivationELU = DML_OPERATOR_ACTIVATION_ELU,
        ActivationHardMax = DML_OPERATOR_ACTIVATION_HARDMAX,
        ActivationHardSigmoid = DML_OPERATOR_ACTIVATION_HARD_SIGMOID,
        ActivationIdentity = DML_OPERATOR_ACTIVATION_IDENTITY,
        ActivationLeakyReLU = DML_OPERATOR_ACTIVATION_LEAKY_RELU,
        ActivationLinear = DML_OPERATOR_ACTIVATION_LINEAR,
        ActivationLogSoftMax = DML_OPERATOR_ACTIVATION_LOG_SOFTMAX,
        ActivationParameterizedReLU = DML_OPERATOR_ACTIVATION_PARAMETERIZED_RELU,
        ActivationParametricSoftPlus = DML_OPERATOR_ACTIVATION_PARAMETRIC_SOFTPLUS,
        ActivationReLU = DML_OPERATOR_ACTIVATION_RELU,
        ActivationScaledELU = DML_OPERATOR_ACTIVATION_SCALED_ELU,
        ActivationScaledTanH = DML_OPERATOR_ACTIVATION_SCALED_TANH,
        ActivationSigmoid = DML_OPERATOR_ACTIVATION_SIGMOID,
        ActivationSoftMax = DML_OPERATOR_ACTIVATION_SOFTMAX,
        ActivationSoftPlus = DML_OPERATOR_ACTIVATION_SOFTPLUS,
        ActivationSoftSign = DML_OPERATOR_ACTIVATION_SOFTSIGN,
        ActivationTanH = DML_OPERATOR_ACTIVATION_TANH,
        ActivationThresholdedReLU = DML_OPERATOR_ACTIVATION_THRESHOLDED_RELU,
        Convolution = DML_OPERATOR_CONVOLUTION,
        GEMM = DML_OPERATOR_GEMM,
        Reduce = DML_OPERATOR_REDUCE,
        AveragePooling = DML_OPERATOR_AVERAGE_POOLING,
        LPPooling = DML_OPERATOR_LP_POOLING,
        MaxPooling = DML_OPERATOR_MAX_POOLING,
        ROIPooling = DML_OPERATOR_ROI_POOLING,
        Slice = DML_OPERATOR_SLICE,
        Cast = DML_OPERATOR_CAST,
        Split = DML_OPERATOR_SPLIT,
        Join = DML_OPERATOR_JOIN,
        Padding = DML_OPERATOR_PADDING,
        ValueScale2D = DML_OPERATOR_VALUE_SCALE_2D,
        UpSample2D = DML_OPERATOR_UPSAMPLE_2D,
        Gather = DML_OPERATOR_GATHER,
        SpaceToDepth = DML_OPERATOR_SPACE_TO_DEPTH,
        DepthToSpace = DML_OPERATOR_DEPTH_TO_SPACE,
        Tile = DML_OPERATOR_TILE,
        TopK = DML_OPERATOR_TOP_K,
        BatchNormalization = DML_OPERATOR_BATCH_NORMALIZATION,
        MeanVarianceNormalization = DML_OPERATOR_MEAN_VARIANCE_NORMALIZATION,
        LocalResponseNormalization = DML_OPERATOR_LOCAL_RESPONSE_NORMALIZATION,
        LPNormalization = DML_OPERATOR_LP_NORMALIZATION,
        RNN = DML_OPERATOR_RNN,
        LSTM = DML_OPERATOR_LSTM,
        GRU = DML_OPERATOR_GRU,

#if DML_TARGET_VERSION >= 0x2000
        ElementWiseSign = DML_OPERATOR_ELEMENT_WISE_SIGN,
        ElementWiseIsNaN = DML_OPERATOR_ELEMENT_WISE_IS_NAN,
        ElementWiseErf = DML_OPERATOR_ELEMENT_WISE_ERF,
        ElementWiseSinH = DML_OPERATOR_ELEMENT_WISE_SINH,
        ElementWiseCosH = DML_OPERATOR_ELEMENT_WISE_COSH,
        ElementWiseTanH = DML_OPERATOR_ELEMENT_WISE_TANH,
        ElementWiseASinH = DML_OPERATOR_ELEMENT_WISE_ASINH,
        ElementWiseACosH = DML_OPERATOR_ELEMENT_WISE_ACOSH,
        ElementWiseATanH = DML_OPERATOR_ELEMENT_WISE_ATANH,
        ElementWiseIf = DML_OPERATOR_ELEMENT_WISE_IF,
        ElementWiseAdd1 = DML_OPERATOR_ELEMENT_WISE_ADD1,
        ActivationShrink = DML_OPERATOR_ACTIVATION_SHRINK,
        MaxPooling1 = DML_OPERATOR_MAX_POOLING1,
        MaxUnpooling = DML_OPERATOR_MAX_UNPOOLING,
        DiagonalMatrix = DML_OPERATOR_DIAGONAL_MATRIX,
        ScatterElements = DML_OPERATOR_SCATTER_ELEMENTS,
        Scatter = DML_OPERATOR_SCATTER,
        OneHot = DML_OPERATOR_ONE_HOT,
        Resample = DML_OPERATOR_RESAMPLE,
#endif // DML_TARGET_VERSION >= 0x2000

#if DML_TARGET_VERSION >= 0x2100
        ElementWiseBitShiftLeft = DML_OPERATOR_ELEMENT_WISE_BIT_SHIFT_LEFT,
        ElementWiseBitShiftRight = DML_OPERATOR_ELEMENT_WISE_BIT_SHIFT_RIGHT,
        ElementWiseRound = DML_OPERATOR_ELEMENT_WISE_ROUND,
        ElementWiseIsInfinity = DML_OPERATOR_ELEMENT_WISE_IS_INFINITY,
        ElementWiseModulusTruncate = DML_OPERATOR_ELEMENT_WISE_MODULUS_TRUNCATE,
        ElementWiseModulusFloor = DML_OPERATOR_ELEMENT_WISE_MODULUS_FLOOR,
        FillValueConstant = DML_OPERATOR_FILL_VALUE_CONSTANT,
        FillValueSequence = DML_OPERATOR_FILL_VALUE_SEQUENCE,
        CumulativeSummation = DML_OPERATOR_CUMULATIVE_SUMMATION,
        ReverseSubsequences = DML_OPERATOR_REVERSE_SUBSEQUENCES,
        GatherElements = DML_OPERATOR_GATHER_ELEMENTS,
        GatherND = DML_OPERATOR_GATHER_ND,
        ScatterND = DML_OPERATOR_SCATTER_ND,
        MaxPooling2 = DML_OPERATOR_MAX_POOLING2,
        Slice1 = DML_OPERATOR_SLICE1,
        TopK1 = DML_OPERATOR_TOP_K1,
        DepthToSpace1 = DML_OPERATOR_DEPTH_TO_SPACE1,
        SpaceToDepth1 = DML_OPERATOR_SPACE_TO_DEPTH1,
        MeanVarianceNormalization1 = DML_OPERATOR_MEAN_VARIANCE_NORMALIZATION1,
        Resample1 = DML_OPERATOR_RESAMPLE1,
        MatrixMultiplyInteger = DML_OPERATOR_MATRIX_MULTIPLY_INTEGER,
        QuantizedLinearMatrixMultiply = DML_OPERATOR_QUANTIZED_LINEAR_MATRIX_MULTIPLY,
        ConvolutionInteger = DML_OPERATOR_CONVOLUTION_INTEGER,
        QuantizedLinearConvolution = DML_OPERATOR_QUANTIZED_LINEAR_CONVOLUTION,
#endif // DML_TARGET_VERSION >= 0x2100

#if DML_TARGET_VERSION >= 0x3000
        ElementWiseBitAnd = DML_OPERATOR_ELEMENT_WISE_BIT_AND,
        ElementWiseBitOr = DML_OPERATOR_ELEMENT_WISE_BIT_OR,
        ElementWiseBitXor = DML_OPERATOR_ELEMENT_WISE_BIT_XOR,
        ElementWiseBitNot = DML_OPERATOR_ELEMENT_WISE_BIT_NOT,
        ElementWiseBitCount = DML_OPERATOR_ELEMENT_WISE_BIT_COUNT,
        ElementWiseLogicalGreaterThanOrEqual = DML_OPERATOR_ELEMENT_WISE_LOGICAL_GREATER_THAN_OR_EQUAL,
        ElementWiseLogicalLessThanOrEqual = DML_OPERATOR_ELEMENT_WISE_LOGICAL_LESS_THAN_OR_EQUAL,
        ActivationCeLU = DML_OPERATOR_ACTIVATION_CELU,
        ActivationReLUGrad = DML_OPERATOR_ACTIVATION_RELU_GRAD,
        AveragePoolingGrad = DML_OPERATOR_AVERAGE_POOLING_GRAD,
        MaxPoolingGrad = DML_OPERATOR_MAX_POOLING_GRAD,
        RandomGenerator = DML_OPERATOR_RANDOM_GENERATOR,
        NonZeroCoordinates = DML_OPERATOR_NONZERO_COORDINATES,
        ResampleGrad = DML_OPERATOR_RESAMPLE_GRAD,
        SliceGrad = DML_OPERATOR_SLICE_GRAD,
        AdamOptimizer = DML_OPERATOR_ADAM_OPTIMIZER,
        ArgMin = DML_OPERATOR_ARGMIN,
        ArgMax = DML_OPERATOR_ARGMAX,
        ROIAlign = DML_OPERATOR_ROI_ALIGN,
        GatherND1 = DML_OPERATOR_GATHER_ND1,
#endif // DML_TARGET_VERSION >= 0x3000

#if DML_TARGET_VERSION >= 0x3100
        ElementWiseATanYX = DML_OPERATOR_ELEMENT_WISE_ATAN_YX,
        ElementWiseClipGrad = DML_OPERATOR_ELEMENT_WISE_CLIP_GRAD,
        ElementWiseDifferenceSquare = DML_OPERATOR_ELEMENT_WISE_DIFFERENCE_SQUARE,
        LocalResponseNormalizationGrad = DML_OPERATOR_LOCAL_RESPONSE_NORMALIZATION_GRAD,
        CumulativeProduct = DML_OPERATOR_CUMULATIVE_PRODUCT,
        BatchNormalizationGrad = DML_OPERATOR_BATCH_NORMALIZATION_GRAD,
#endif // DML_TARGET_VERSION >= 0x3100

#if DML_TARGET_VERSION >= 0x4000
        ElementWiseQuantizedLinearAdd = DML_OPERATOR_ELEMENT_WISE_QUANTIZED_LINEAR_ADD,
        DynamicQuantizeLinear = DML_OPERATOR_DYNAMIC_QUANTIZE_LINEAR,
        ROIAlign1 = DML_OPERATOR_ROI_ALIGN1,
#endif // DML_TARGET_VERSION >= 0x4000

#if DML_TARGET_VERSION >= 0x4100
        ROIAlignGrad = DML_OPERATOR_ROI_ALIGN_GRAD,
        BatchNormalizationTraining = DML_OPERATOR_BATCH_NORMALIZATION_TRAINING,
        BatchNormalizationTrainingGrad = DML_OPERATOR_BATCH_NORMALIZATION_TRAINING_GRAD,
#endif // DML_TARGET_VERSION >= 0x4100

#if DML_TARGET_VERSION >= 0x5000
        ElementWiseClip1 = DML_OPERATOR_ELEMENT_WISE_CLIP1,
        ElementWiseClipGrad1 = DML_OPERATOR_ELEMENT_WISE_CLIP_GRAD1,
        Padding1 = DML_OPERATOR_PADDING1,
        ElementWiseNegate = DML_OPERATOR_ELEMENT_WISE_NEGATE,
#endif // DML_TARGET_VERSION >= 0x5000

#if DML_TARGET_VERSION >= 0x5100
        ActivationGeLU = DML_OPERATOR_ACTIVATION_GELU,
        ActivationSoftMax1 = DML_OPERATOR_ACTIVATION_SOFTMAX1,
        ActivationLogSoftMax1 = DML_OPERATOR_ACTIVATION_LOG_SOFTMAX1,
        ActivationHardMax1 = DML_OPERATOR_ACTIVATION_HARDMAX1,
        Resample2 = DML_OPERATOR_RESAMPLE2,
        ResampleGrad1 = DML_OPERATOR_RESAMPLE_GRAD1,
        DiagonalMatrix1 = DML_OPERATOR_DIAGONAL_MATRIX1,
#endif // DML_TARGET_VERSION >= 0x5100

#if DML_TARGET_VERSION >= 0x6100
        MultiheadAttention = DML_OPERATOR_MULTIHEAD_ATTENTION,
#endif // DML_TARGET_VERSION >= 0x6100

#if DML_TARGET_VERSION >= 0x6200
        LPPooling1 = DML_OPERATOR_LP_POOLING1,
        AveragePooling1 = DML_OPERATOR_AVERAGE_POOLING1,
        ActivationSwish = DML_OPERATOR_ACTIVATION_SWISH,
        ActivationHardSwish = DML_OPERATOR_ACTIVATION_HARD_SWISH,
        QuantizedLinearAveragePooling = DML_OPERATOR_QUANTIZED_LINEAR_AVERAGE_POOLING,
        MatrixMultiplyIntegerToFloat = DML_OPERATOR_MATRIX_MULTIPLY_INTEGER_TO_FLOAT,
#endif // DML_TARGET_VERSION >= 0x6200
#if DML_TARGET_VERSION >= 0x6300
        MeanVarianceNormalization2 = DML_OPERATOR_MEAN_VARIANCE_NORMALIZATION2,
        MultiheadAttention1 = DML_OPERATOR_MULTIHEAD_ATTENTION1,
        Quantize = DML_OPERATOR_QUANTIZE,
        Dequantize = DML_OPERATOR_DEQUANTIZE,
#endif // DML_TARGET_VERSION >= 0x6300

#if DML_TARGET_VERSION >= 0x6400
        Resample3 = DML_OPERATOR_RESAMPLE3,
        Fold = DML_OPERATOR_FOLD,
        Unfold = DML_OPERATOR_UNFOLD,
#endif // DML_TARGET_VERSION >= 0x6400

    };

    // ===================================================================================================================
    //   Operator enumerations and structures
    // ===================================================================================================================

    /// <summary>
    /// <para>
    /// Alias for DML_REDUCE_FUNCTION
    /// </para>
    /// </summary>
    enum class ReduceFunction
    {
        ArgMax,
        ArgMin,
        Average,
        L1,
        L2,
        LogSum,
        LogSumExp,
        Max,
        Min,
        Multiply,
        Sum,
        SumSquare,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MATRIX_TRANSFORM
    /// </para>
    /// </summary>
    enum class MatrixTransform
    {
        None,
        Transpose,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CONVOLUTION_MODE
    /// </para>
    /// </summary>
    enum class ConvolutionMode
    {
        Convolution,
        CrossCorrelation,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CONVOLUTION_DIRECTION
    /// </para>
    /// </summary>
    enum class ConvolutionDirection
    {
        Forward,
        Backward,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_PADDING_MODE
    /// </para>
    /// </summary>
    enum class PaddingMode
    {
        Constant,
        Edge,
        Reflection,

#if DML_TARGET_VERSION >= 0x3000
        Symmetric,
#endif
#if DML_TARGET_VERSION >= 0x6400
        Wrap = DML_PADDING_MODE_WRAP,
#endif
    };

    /// <summary>
    /// <para>
    /// Alias for DML_INTERPOLATION_MODE
    /// </para>
    /// </summary>
    enum class InterpolationMode
    {
        NearestNeighbor,
        Linear,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SCALE_BIAS
    /// </para>
    /// </summary>
    struct ScaleBias
    {
        FLOAT Scale = 0;
        FLOAT Bias = 0;

        ScaleBias( ) noexcept = default;
        ScaleBias( FLOAT scale, FLOAT bias ) noexcept
            : Scale( scale ), Bias( bias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCALE_BIAS );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SIZE_2D
    /// </para>
    /// </summary>
    struct Size2D
    {
        UInt32 Width = 0;
        UInt32 Height = 0;

        Size2D( ) noexcept = default;
        Size2D( UInt32 width, UInt32 height ) noexcept
            : Width( width ), Height( height )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SIZE_2D );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RECURRENT_NETWORK_DIRECTION
    /// </para>
    /// </summary>
    enum class RecurrentNetworkDirection
    {
        Forward,
        Backward,
        Bidirectional,
    };

#if DML_TARGET_VERSION >= 0x2100

    /// <summary>
    /// <para>
    /// Alias for DML_ROUNDING_MODE
    /// </para>
    /// </summary>
    enum class RoundingMode
    {
        HalvesToNearestEven,
        TowardZero,
        TowardInfinity,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_IS_INFINITY_MODE
    /// </para>
    /// </summary>
    enum class IsInfinityMode
    {
        Either = 0,
        Positive = 1,
        Negative = 2,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_AXIS_DIRECTION
    /// </para>
    /// </summary>
    enum class AxisDirection
    {
        Increasing = 0,
        Decreasing = 1,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_DEPTH_SPACE_ORDER
    /// </para>
    /// </summary>
    enum class DepthSpaceOrder
    {
        DepthColumnRow,
        ColumnRowDepth,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SCALAR_UNION
    /// </para>
    /// </summary>
    union ScalarUnion
    {
        BYTE   Bytes[ 8 ];
        INT8   Int8;
        UINT8  UInt8;
        INT16  Int16;
        UINT16 UInt16;
        INT32  Int32;
        UINT32 UInt32;
        INT64  Int64;
        UINT64 UInt64;
        FLOAT  Float32;
        DOUBLE Float64;

        ScalarUnion( )
            : UInt64( 0 )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCALAR_UNION );
    };

#endif // DML_TARGET_VERSION >= 0x2100

#if DML_TARGET_VERSION >= 0x3000

    /// <summary>
    /// <para>
    /// Alias for DML_RANDOM_GENERATOR_TYPE
    /// </para>
    /// </summary>
    enum class RandomGeneratorType
    {
        Philox4x32_10
    };

#endif // DML_TARGET_VERSION >= 0x3000

#if DML_TARGET_VERSION >= 0x6100

    /// <summary>
    /// <para>
    /// Alias for DML_MULTIHEAD_ATTENTION_MASK_TYPE
    /// </para>
    /// </summary>
    enum class MultiheadAttentionMaskType
    {
        None,
        KeySequenceLength,
        KeySequenceEndStart,
        KeyQuerySequenceLengthStartEnd,
        Boolean,
    };

#endif // DML_TARGET_VERSION >= 0x6100

#if DML_TARGET_VERSION >= 0x6300

    enum class QuantizationType
    {
        None = DML_QUANTIZATION_TYPE_NONE,
        Scale = DML_QUANTIZATION_TYPE_SCALE,
        ScaleZeroPoint = DML_QUANTIZATION_TYPE_SCALE_ZERO_POINT,
    };

#endif // DML_TARGET_VERSION >= 0x6300

    // ===================================================================================================================
    //   Operator descriptions
    // ===================================================================================================================

    struct BaseOperatorDesc abstract
    {
    };

    struct UnaryOperatorDesc  abstract : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        UnaryOperatorDesc( ) noexcept = default;
        UnaryOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : InputTensor( inputTensor ), OutputTensor( outputTensor )
        {
        }
    };

    struct BinaryOperatorDesc abstract : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        const TensorDesc* ATensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        BinaryOperatorDesc( ) noexcept = default;
        BinaryOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : ATensor( inputTensorA ), BTensor( inputTensorB ), OutputTensor( outputTensor )
        {
        }

    };

    struct UnaryOperatorWithScaleBiasDesc abstract : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        _Maybenull_ const ScaleBias* ScaleBias = nullptr;

        UnaryOperatorWithScaleBiasDesc( ) noexcept = default;
        UnaryOperatorWithScaleBiasDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor ), ScaleBias( scaleBias )
        {
        }
    };

    /// <summary>
    /// <para>
    /// Alias for DML_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct OperatorDesc
    {
        OperatorType Type = OperatorType::Invalid;
        _Field_size_( _Inexpressible_( "Dependent on operator type" ) ) const void* Desc = nullptr;

        OperatorDesc( ) noexcept = default;

        OperatorDesc( OperatorType type, const void* desc ) noexcept
            : Type( type ), Desc( desc )
        {
        }

        template<typename T>
            requires std::is_base_of_v<BaseOperatorDesc, T>
        OperatorDesc( const T* desc ) noexcept
            : Type( T::OperatorType ), Desc( reinterpret_cast< const void* >( desc ) )
        {
        }

        template<typename T>
            requires std::is_base_of_v<BaseOperatorDesc, T>
        OperatorDesc& operator = ( const T* desc ) noexcept
        {
            Type = T::OperatorType;
            Desc = reinterpret_cast< const void* >( desc );
            return *this;
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_OPERATOR_DESC );
    };




    /// <summary>
    /// <para>
    /// Computes the identity for each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(x) = x$$
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IDENTITY_OPERATOR_DESC
    /// </para>
    /// </summary>
    /// <remarks>
    /// <para>
    /// The identity operation is often used to copy a tensor.
    /// </para>
    /// <para>
    /// It can also be used to transform the layout of tensors by manipulating strides
    /// </para>
    /// </remarks>
    struct ElementWiseIdentityOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIdentity;

        /// <summary>
        /// Default constructor
        /// </summary>
        ElementWiseIdentityOperatorDesc( ) noexcept = default;
        /// <summary>
        /// Initializes the ElementWiseIdentityOperatorDesc
        /// </summary>
        /// <param name="inputTensor">
        /// Describes the input tensor to read from.
        /// </param>
        /// <param name="outputTensor">
        /// The output tensor to write the results to.
        /// </param>
        /// <param name="scaleBias">
        /// An optional scale and bias to apply to the input. If present, 
        /// this has the effect of applying the function 
        /// $$g(x) = x * scale + bias$$ to each input element 
        /// prior to computing this operator.
        /// </param>
        ElementWiseIdentityOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IDENTITY_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseIdentityOperatorDesc ) == sizeof( DML_ELEMENT_WISE_IDENTITY_OPERATOR_DESC ) );


    /// <summary>
    /// <para>
    /// Computes the absolute value for each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(x)=|x|$$
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ABS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseAbsOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseAbs;

        ElementWiseAbsOperatorDesc( ) noexcept = default;
        ElementWiseAbsOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ABS_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseAbsOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ABS_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the arccosine for each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(x)=cos^{-1}(x)$$
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ACOS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseACosOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseACos;

        ElementWiseACosOperatorDesc( ) noexcept = default;
        ElementWiseACosOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ACOS_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseACosOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ACOS_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Adds every element in ATensor to its corresponding element in BTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ADD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseAddOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseAdd;

        ElementWiseAddOperatorDesc( ) noexcept = default;
        ElementWiseAddOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor = nullptr ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ADD_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseAddOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ADD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Adds every element in ATensor to its corresponding element 
    /// in BTensor and places the result into the corresponding element 
    /// of OutputTensor, with the option for fused activation.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ADD1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseAdd1OperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseAdd1;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        ElementWiseAdd1OperatorDesc( ) noexcept = default;
        ElementWiseAdd1OperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor = nullptr, const OperatorDesc* fusedActivation = nullptr ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor ), FusedActivation( fusedActivation )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ADD1_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseAdd1OperatorDesc ) == sizeof( DML_ELEMENT_WISE_ADD1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the arcsine for each element of InputTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ASIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseASinOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseASin;

        ElementWiseASinOperatorDesc( ) noexcept = default;
        ElementWiseASinOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ASIN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseASinOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ASIN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the arctangent for each element of InputTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ATAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseATanOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseATan;

        ElementWiseATanOperatorDesc( ) noexcept = default;
        ElementWiseATanOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ATAN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseATanOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ATAN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the ceiling for each element of InputTensor, placing the result into the corresponding element of OutputTensor. The ceiling of x is the smallest integer that is greater than or equal to x.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CEIL_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseCeilOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseCeil;

        ElementWiseCeilOperatorDesc( ) noexcept = default;
        ElementWiseCeilOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CEIL_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseCeilOperatorDesc ) == sizeof( DML_ELEMENT_WISE_CEIL_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the following operation for each element of InputTensor, placing the result into the corresponding element of OutputTensor. This operator clamps (or limits) every element in the input within the closed interval [Min, Max].
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClipOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClip;
        FLOAT Min = std::numeric_limits<float>::lowest( );
        FLOAT Max = std::numeric_limits<float>::max( );

        ElementWiseClipOperatorDesc( ) noexcept = default;
        ElementWiseClipOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr, float min = std::numeric_limits<float>::lowest( ), float max = std::numeric_limits<float>::max( ) ) noexcept
            : Base( inputTensor, outputTensor, scaleBias ), Min( min ), Max( max )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseClipOperatorDesc ) == sizeof( DML_ELEMENT_WISE_CLIP_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the trigonometric cosine of each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_COS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseCosOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseCos;

        ElementWiseCosOperatorDesc( ) noexcept = default;
        ElementWiseCosOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_COS_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseCosOperatorDesc ) == sizeof( DML_ELEMENT_WISE_COS_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the quotient of each element of ATensor over the corresponding 
    /// element of BTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_DIVIDE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseDivideOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseDivide;

        ElementWiseDivideOperatorDesc( ) noexcept = default;
        ElementWiseDivideOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_DIVIDE_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseDivideOperatorDesc ) == sizeof( DML_ELEMENT_WISE_DIVIDE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Applies the natural exponentiation function to each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_EXP_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseExpOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseExp;

        ElementWiseExpOperatorDesc( ) noexcept = default;
        ElementWiseExpOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_EXP_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseExpOperatorDesc ) == sizeof( DML_ELEMENT_WISE_EXP_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the floor for each element of InputTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_FLOOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseFloorOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseFloor;

        ElementWiseFloorOperatorDesc( ) noexcept = default;
        ElementWiseFloorOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_FLOOR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseFloorOperatorDesc ) == sizeof( DML_ELEMENT_WISE_FLOOR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the base-e (natural) logarithm of each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOG_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLog;

        ElementWiseLogOperatorDesc( ) noexcept = default;
        ElementWiseLogOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOG_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOG_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical AND on each pair of corresponding elements of 
    /// the input tensors, placing the result (1 for true, 0 for false) 
    /// into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_AND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalAndOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalAnd;

        ElementWiseLogicalAndOperatorDesc( ) noexcept = default;
        ElementWiseLogicalAndOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_AND_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalAndOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_AND_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical equals on each pair of corresponding elements of the 
    /// input tensors, placing the result (1 for true, 0 for false) into the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_EQUALS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalEqualsOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalEquals;

        ElementWiseLogicalEqualsOperatorDesc( ) noexcept = default;
        ElementWiseLogicalEqualsOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_EQUALS_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalEqualsOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_EQUALS_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical greater than on each pair of corresponding elements of the 
    /// input tensors, placing the result (1 for true, 0 for false) into the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalGreaterThanOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalGreaterThan;

        ElementWiseLogicalGreaterThanOperatorDesc( ) noexcept = default;
        ElementWiseLogicalGreaterThanOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalGreaterThanOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical less than on each pair of corresponding elements 
    /// of the input tensors, placing the result (1 for true, 0 for false) 
    /// into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalLessThanOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalLessThan;

        ElementWiseLogicalLessThanOperatorDesc( ) noexcept = default;
        ElementWiseLogicalLessThanOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalLessThanOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical NOT on each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_NOT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalNotOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalNot;

        ElementWiseLogicalNotOperatorDesc( ) noexcept = default;
        ElementWiseLogicalNotOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_NOT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalNotOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_NOT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical OR on each pair of corresponding elements of the 
    /// input tensors, placing the result into the corresponding element of 
    /// OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_OR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalOrOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalOr;

        ElementWiseLogicalOrOperatorDesc( ) noexcept = default;
        ElementWiseLogicalOrOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_OR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalOrOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_OR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a logical XOR (exclusive or) on each pair of corresponding 
    /// elements of the input tensors, placing the result into the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_XOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalXorOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalXor;

        ElementWiseLogicalXorOperatorDesc( ) noexcept = default;
        ElementWiseLogicalXorOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_XOR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalXorOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_XOR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Takes the greater of two corresponding elements from the input tensors, and places the result into the corresponding element of the output tensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMaxOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMax;

        ElementWiseMaxOperatorDesc( ) noexcept = default;
        ElementWiseMaxOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MAX_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseMaxOperatorDesc ) == sizeof( DML_ELEMENT_WISE_MAX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Averages each pair of corresponding elements of the input tensors, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MEAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMeanOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMean;

        ElementWiseMeanOperatorDesc( ) noexcept = default;
        ElementWiseMeanOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MEAN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseMeanOperatorDesc ) == sizeof( DML_ELEMENT_WISE_MEAN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Takes the lesser of two corresponding elements from the input tensors, 
    /// and places the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMinOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMin;

        ElementWiseMinOperatorDesc( ) noexcept = default;
        ElementWiseMinOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MIN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseMinOperatorDesc ) == sizeof( DML_ELEMENT_WISE_MIN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the product of each pair of corresponding elements of 
    /// the input tensors, placing the result into the corresponding 
    /// element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MULTIPLY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMultiplyOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMultiply;

        ElementWiseMultiplyOperatorDesc( ) noexcept = default;
        ElementWiseMultiplyOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MULTIPLY_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseMultiplyOperatorDesc ) == sizeof( DML_ELEMENT_WISE_MULTIPLY_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes each element of InputTensor raised to the power of the 
    /// corresponding element of ExponentTensor, placing the result into 
    /// the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Negative bases are supported for exponents with integral values 
    /// (though datatype can still be float), otherwise this operator returns NaN.
    /// </para>
    /// <para>
    /// When the input tensor and exponent tensor both have integral data type, 
    /// this operator guarantees exact results.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_POW_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWisePowOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWisePow;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ExponentTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        _Maybenull_ const ScaleBias* ScaleBias = nullptr;

        ElementWisePowOperatorDesc( ) noexcept = default;
        ElementWisePowOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* exponentTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr )
            : InputTensor( inputTensor ), ExponentTensor( exponentTensor ), OutputTensor( outputTensor ), ScaleBias( scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_POW_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWisePowOperatorDesc ) == sizeof( DML_ELEMENT_WISE_POW_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Raises each element of InputTensor to the power of Exponent, placing the 
    /// result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Negative bases are supported for integral exponents, otherwise 
    /// this operator returns NaN.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CONSTANT_POW_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseConstantPowOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseConstantPow;

        FLOAT Exponent = 0.f;

        ElementWiseConstantPowOperatorDesc( ) noexcept = default;
        ElementWiseConstantPowOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr, FLOAT exponent = 0.f ) noexcept
            : Base( inputTensor, outputTensor, scaleBias ), Exponent( exponent )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CONSTANT_POW_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseConstantPowOperatorDesc ) == sizeof( DML_ELEMENT_WISE_CONSTANT_POW_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the reciprocal for each element of the input tensor, placing the result 
    /// into the corresponding element of the output tensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_RECIP_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseReciprocalOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseReciprocal;

        ElementWiseReciprocalOperatorDesc( ) noexcept = default;
        ElementWiseReciprocalOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_RECIP_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseReciprocalOperatorDesc ) == sizeof( DML_ELEMENT_WISE_RECIP_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the trigonometric sine of each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSinOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSin;

        ElementWiseSinOperatorDesc( ) noexcept = default;
        ElementWiseSinOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SIN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseSinOperatorDesc ) == sizeof( DML_ELEMENT_WISE_SIN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the square root of each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SQRT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSqrtOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSqrt;

        ElementWiseSqrtOperatorDesc( ) noexcept = default;
        ElementWiseSqrtOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SQRT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseSqrtOperatorDesc ) == sizeof( DML_ELEMENT_WISE_SQRT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Subtracts each element of BTensor from the corresponding element 
    /// of ATensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SUBTRACT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSubtractOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSubtract;

        ElementWiseSubtractOperatorDesc( ) noexcept = default;
        ElementWiseSubtractOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SUBTRACT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseSubtractOperatorDesc ) == sizeof( DML_ELEMENT_WISE_SUBTRACT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the trigonometric tangent of each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_TAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseTanOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseTan;

        ElementWiseTanOperatorDesc( ) noexcept = default;
        ElementWiseTanOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_TAN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseTanOperatorDesc ) == sizeof( DML_ELEMENT_WISE_TAN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Replaces all elements of InputTensor below the given threshold, Min, with Min. 
    /// Results are placed into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_THRESHOLD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseThresholdOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseThreshold;
        FLOAT Min = 0.f;

        ElementWiseThresholdOperatorDesc( ) noexcept = default;
        ElementWiseThresholdOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr, FLOAT min = 0.f ) noexcept
            : Base( inputTensor, outputTensor, scaleBias ), Min( min )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_THRESHOLD_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseThresholdOperatorDesc ) == sizeof( DML_ELEMENT_WISE_THRESHOLD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the following linear quantization function on every element 
    /// in InputTensor with respect to its corresponding element in ScaleTensor 
    /// and ZeroPointTensor, placing the results in the corresponding element 
    /// of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(input, scale, zero_point) = clamp(round(input / scale) + zero_point, Min, Max)$$
    /// </para>
    /// <para>
    /// Where Min is 0 and Max is 255 for UInt8 output, and Min is -128 and Max is 127 for Int8 output.
    /// </para>
    /// <para>
    /// Quantizing involves converting to a lower-precision data type in order 
    /// to accelerate arithmetic. It's a common way to increase performance at 
    /// the cost of precision. A group of 8-bit values can be computed faster 
    /// than a group of 32-bit values can.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_QUANTIZE_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseQuantizeLinearOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseQuantizeLinear;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* ZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        ElementWiseQuantizeLinearOperatorDesc( ) noexcept = default;
        ElementWiseQuantizeLinearOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* scaleTensor = nullptr, const TensorDesc* zeroPointTensor = nullptr ) noexcept
            : InputTensor( inputTensor ), ScaleTensor( scaleTensor ), ZeroPointTensor( zeroPointTensor ), OutputTensor( outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_QUANTIZE_LINEAR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseQuantizeLinearOperatorDesc ) == sizeof( DML_ELEMENT_WISE_QUANTIZE_LINEAR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the following linear dequantization function on every 
    /// element in InputTensor with respect to its corresponding element 
    /// in ScaleTensor and ZeroPointTensor, placing the results in the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(input, scale, zero_point) = (input - zero_point) \times scale$$
    /// </para>
    /// <para>
    /// Quantization is a common way to increase performance at the cost of precision. 
    /// A group of 8-bit int values can be computed faster than a group of 32-bit 
    /// float values can. Dequantizing converts the encoded data back to its domain.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_DEQUANTIZE_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseDequantizeLinearOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseDequantizeLinear;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* ZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        ElementWiseDequantizeLinearOperatorDesc( ) noexcept = default;
        ElementWiseDequantizeLinearOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* scaleTensor = nullptr, const TensorDesc* zeroPointTensor = nullptr ) noexcept
            : InputTensor( inputTensor ), ScaleTensor( scaleTensor ), ZeroPointTensor( zeroPointTensor ), OutputTensor( outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_DEQUANTIZE_LINEAR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseDequantizeLinearOperatorDesc ) == sizeof( DML_ELEMENT_WISE_DEQUANTIZE_LINEAR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs an exponential linear unit (ELU) activation function on 
    /// every element in InputTensor, placing the result into the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_ELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationELUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationELU;

        FLOAT Alpha = 0.f;

        ActivationELUOperatorDesc( ) noexcept = default;
        ActivationELUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 1.f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_ELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationELUOperatorDesc ) == sizeof( DML_ACTIVATION_ELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a hardmax function on each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// The operator computes the hardmax (1 for the first occurrence of the 
    /// largest value in the layer, and 0 for all other values) of each row 
    /// in the given input.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_HARDMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    /// <remarks>
    /// The operator computes the hardmax (1 for the first maximum value, 
    /// and 0 for all others) values for each layer in the batch of the 
    /// given input. The input is a 2-D tensor of size (batch_size x input_feature_dimensions). 
    /// The output tensor has the same shape and contains the hardmax values of 
    /// the corresponding input.
    /// </remarks>
    struct ActivationHardMaxOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardMax;

        ActivationHardMaxOperatorDesc( ) noexcept = default;
        /// <summary>
        /// Constructs a new instance of an ActivationHardMaxOperatorDesc object.
        /// </summary>
        /// <param name="inputTensor">
        /// The tensor to read from for the input. This tensor must have an 
        /// effective rank no greater than 2. The effective rank of a tensor 
        /// is the DimensionCount of the tensor, excluding leftmost dimensions of 
        /// size 1. For example a tensor size of [ 1, 1, BatchCount, Width ] is valid, 
        /// and is equivalent to a tensor of sizes [ BatchCount, Width ].
        /// </param>
        /// <param name="outputTensor">
        /// The output tensor to write the results to.
        /// </param>
        ActivationHardMaxOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARDMAX_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationHardMaxOperatorDesc ) == sizeof( DML_ACTIVATION_HARDMAX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a hard sigmoid function on every element in InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(x) = max(0, min(Alpha \times x + Beta, 1))$$
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_HARD_SIGMOID_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardSigmoidOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardSigmoid;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        ActivationHardSigmoidOperatorDesc( ) noexcept = default;
        ActivationHardSigmoidOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 0.2f, float beta = 0.5f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha ), Beta( beta )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARD_SIGMOID_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationHardSigmoidOperatorDesc ) == sizeof( DML_ACTIVATION_HARD_SIGMOID_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the identity activation, effectively copying every element 
    /// of InputTensor to the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_IDENTITY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationIdentityOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationIdentity;

        ActivationIdentityOperatorDesc( ) noexcept = default;
        ActivationIdentityOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_IDENTITY_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationIdentityOperatorDesc ) == sizeof( DML_ACTIVATION_IDENTITY_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a leaky rectified linear unit (ReLU) activation function 
    /// on every element in InputTensor, placing the result into the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_LEAKY_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLeakyReLUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLeakyReLU;
        FLOAT Alpha = 0.f;

        ActivationLeakyReLUOperatorDesc( ) noexcept = default;
        ActivationLeakyReLUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 0.01f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LEAKY_RELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationLeakyReLUOperatorDesc ) == sizeof( DML_ACTIVATION_LEAKY_RELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the linear activation function on every element in InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLinearOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLinear;

        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;
        ActivationLinearOperatorDesc( ) noexcept = default;
        ActivationLinearOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 1.0f, float beta = 0.f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha ), Beta( beta )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LINEAR_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationLinearOperatorDesc ) == sizeof( DML_ACTIVATION_LINEAR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a natural log-of-softmax activation function on 
    /// each element of InputTensor, placing the result into the 
    /// corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_LOG_SOFTMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLogSoftMaxOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLogSoftMax;

        ActivationLogSoftMaxOperatorDesc( ) noexcept = default;
        ActivationLogSoftMaxOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LOG_SOFTMAX_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationLogSoftMaxOperatorDesc ) == sizeof( DML_ACTIVATION_LOG_SOFTMAX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a parameterized rectified linear unit (ReLU) activation 
    /// function on every element in InputTensor, placing the result into 
    /// the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_PARAMETERIZED_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationParameterizedReLUOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationParameterizedReLU;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* SlopeTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        ActivationParameterizedReLUOperatorDesc( ) noexcept = default;
        ActivationParameterizedReLUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* slopeTensor = nullptr ) noexcept
            : InputTensor( inputTensor ), SlopeTensor( slopeTensor ), OutputTensor( outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_PARAMETERIZED_RELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationParameterizedReLUOperatorDesc ) == sizeof( DML_ACTIVATION_PARAMETERIZED_RELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a parametric softplus activation function on every element in 
    /// InputTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_PARAMETRIC_SOFTPLUS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationParametricSoftPlusOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationParametricSoftPlus;

        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        ActivationParametricSoftPlusOperatorDesc( ) noexcept = default;
        ActivationParametricSoftPlusOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha, float beta ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha ), Beta( beta )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_PARAMETRIC_SOFTPLUS_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationParametricSoftPlusOperatorDesc ) == sizeof( DML_ACTIVATION_PARAMETRIC_SOFTPLUS_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a rectified linear unit (ReLU) activation function on every element 
    /// in InputTensor, placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationReLUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationReLU;

        ActivationReLUOperatorDesc( ) noexcept = default;
        ActivationReLUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_RELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationReLUOperatorDesc ) == sizeof( DML_ACTIVATION_RELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a scaled exponential linear unit (ELU) activation function on 
    /// every element in InputTensor, placing the result into the corresponding 
    /// element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SCALED_ELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationScaledELUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationScaledELU;

        FLOAT Alpha = 0.f;
        FLOAT Gamma = 0.f;

        ActivationScaledELUOperatorDesc( ) noexcept = default;
        ActivationScaledELUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 1.67326319217681884765625f, float gamma = 1.05070102214813232421875f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha ), Gamma( gamma )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SCALED_ELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationScaledELUOperatorDesc ) == sizeof( DML_ACTIVATION_SCALED_ELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a scaled hyperbolic tangent activation function on every 
    /// element in InputTensor, placing the result into the corresponding 
    /// element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SCALED_TANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationScaledTanHOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationScaledTanH;

        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        ActivationScaledTanHOperatorDesc( ) noexcept = default;
        ActivationScaledTanHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 1.f, float beta = 0.5f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha ), Beta( beta )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SCALED_TANH_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationScaledTanHOperatorDesc ) == sizeof( DML_ACTIVATION_SCALED_TANH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the sigmoid function on every element in InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SIGMOID_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSigmoidOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSigmoid;

        ActivationSigmoidOperatorDesc( ) noexcept = default;
        ActivationSigmoidOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SIGMOID_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationSigmoidOperatorDesc ) == sizeof( DML_ACTIVATION_SIGMOID_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a softmax activation function on InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftMaxOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftMax;

        ActivationSoftMaxOperatorDesc( ) noexcept = default;
        ActivationSoftMaxOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTMAX_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationSoftMaxOperatorDesc ) == sizeof( DML_ACTIVATION_SOFTMAX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a parametric softplus activation function on every 
    /// element in InputTensor, placing the result into the corresponding 
    /// element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTPLUS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftPlusOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftPlus;

        FLOAT Steepness = 0.f;

        ActivationSoftPlusOperatorDesc( ) noexcept = default;
        ActivationSoftPlusOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float steepness = 1.f ) noexcept
            : Base( inputTensor, outputTensor ), Steepness( steepness )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTPLUS_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationSoftPlusOperatorDesc ) == sizeof( DML_ACTIVATION_SOFTPLUS_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the softsign function on every element in InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(x) = \frac{x}{1+|x|}$$
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTSIGN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftSignOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftSign;

        ActivationSoftSignOperatorDesc( ) noexcept = default;
        ActivationSoftSignOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }


        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTSIGN_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationSoftSignOperatorDesc ) == sizeof( DML_ACTIVATION_SOFTSIGN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a hyperbolic tangent activation function on 
    /// every element in InputTensor, placing the result into 
    /// the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// $$f(x) = \frac{1 - e^{-2 \times x}}{1 + e^{-2 \times x}}$$
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_TANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationTanHOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationTanH;

        ActivationTanHOperatorDesc( ) noexcept = default;
        ActivationTanHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_TANH_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationTanHOperatorDesc ) == sizeof( DML_ACTIVATION_TANH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a thresholded rectified linear unit (ReLU) 
    /// activation function on every element in InputTensor, 
    /// placing the result into the corresponding element of 
    /// OutputTensor.
    /// </para>
    /// $$f(x) = \begin{cases}
    ///            x, & \text{ if } x > \alpha\\
    ///            0, & \text{ if } x \leq \alpha
    ///          \end{cases}$$
    /// <para>
    /// Alias for DML_ACTIVATION_THRESHOLDED_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationThresholdedReLUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationThresholdedReLU;
        FLOAT Alpha = 1.f;

        ActivationThresholdedReLUOperatorDesc( ) noexcept = default;
        ActivationThresholdedReLUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 1.0f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_THRESHOLDED_RELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationThresholdedReLUOperatorDesc ) == sizeof( DML_ACTIVATION_THRESHOLDED_RELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a convolution of the FilterTensor with the InputTensor. This operator 
    /// supports a number of standard convolution configurations. These standard 
    /// configurations include forward and backward (transposed) convolution by setting 
    /// the Direction and Mode fields, as well as depth-wise convolution by setting the 
    /// GroupCount field.
    /// </para>
    /// <para>
    /// A summary of the steps involved: 
    /// </para>
    /// <list type="number">
    /// <item>
    /// Perform the convolution into the output tensor. 
    /// </item>
    /// <item>
    /// Reshape the bias to the same dimension sizes as the output tensor.
    /// </item>
    /// <item>
    /// Add the reshaped bias tensor to the output tensor.
    /// </item>
    /// </list>
    /// <para>
    /// Alias for DML_CONVOLUTION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ConvolutionOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Convolution;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* FilterTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        ConvolutionMode Mode = ConvolutionMode::Convolution;
        ConvolutionDirection Direction = ConvolutionDirection::Forward;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* OutputPadding = nullptr;
        UInt32 GroupCount = 0;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        ConvolutionOperatorDesc( ) noexcept = default;
        ConvolutionOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* filterTensor, const TensorDesc* biasTensor = nullptr,
            ConvolutionMode mode = ConvolutionMode::CrossCorrelation, ConvolutionDirection direction = ConvolutionDirection::Forward, UInt32 dimensionCount = 0,
            const UInt32* strides = nullptr, const UInt32* dilations = nullptr, const UInt32* startPadding = nullptr, const UInt32* endPadding = nullptr, const UInt32* outputPadding = nullptr,
            UInt32 groupCount = 0, const OperatorDesc* fusedActivation = nullptr ) noexcept
            : InputTensor( inputTensor ), OutputTensor( outputTensor ), FilterTensor( filterTensor ), BiasTensor( biasTensor ),
            Mode( mode ), Direction( direction ), DimensionCount( dimensionCount ),
            Strides( strides ), Dilations( dilations ), StartPadding( startPadding ), EndPadding( endPadding ), OutputPadding( outputPadding ),
            GroupCount( groupCount ), FusedActivation( fusedActivation )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CONVOLUTION_OPERATOR_DESC );
    };
    static_assert( sizeof( ConvolutionOperatorDesc ) == sizeof( DML_CONVOLUTION_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a general matrix multiplication function of the form 
    /// Output = FusedActivation(Alpha * TransA(A) x TransB(B) + Beta * C), 
    /// where x denotes matrix multiplication, and * denotes multiplication with a scalar
    /// </para>
    /// <para>
    /// This operator requires 4D tensors with layout [ BatchCount, ChannelCount, Height, Width ], 
    /// and it will perform BatchCount * ChannelCount number of independent matrix multiplications.
    /// </para>
    /// <para>
    /// For example, if ATensor has Sizes of [ BatchCount, ChannelCount, M, K ], 
    /// and BTensor has Sizes of [ BatchCount, ChannelCount, K, N ], and OutputTensor 
    /// has Sizes of [ BatchCount, ChannelCount, M, N ], then this operator 
    /// performs BatchCount * ChannelCount independent matrix multiplications 
    /// of dimensions [M,K] x [K,N] = [M,N].
    /// </para>
    /// <para>
    /// Alias for DML_GEMM_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GEMMOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GEMM;

        const TensorDesc* ATensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        _Maybenull_ const TensorDesc* CTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        MatrixTransform TransA = MatrixTransform::None;
        MatrixTransform TransB = MatrixTransform::None;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        GEMMOperatorDesc( ) noexcept = default;
        GEMMOperatorDesc( const TensorDesc* aTensor, const TensorDesc* bTensor, const TensorDesc* outputTensor, const TensorDesc* cTensor, FLOAT alpha = 1.f, FLOAT beta = 1.f,
            MatrixTransform transA = MatrixTransform::None, MatrixTransform transB = MatrixTransform::None, const OperatorDesc* fusedActivation = nullptr ) noexcept
            : ATensor( aTensor ), BTensor( bTensor ), CTensor( cTensor ), OutputTensor( outputTensor ), TransA( transA ), TransB( transB ), Alpha( alpha ), Beta( beta ), FusedActivation( fusedActivation )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GEMM_OPERATOR_DESC );
    };
    static_assert( sizeof( GEMMOperatorDesc ) == sizeof( DML_GEMM_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Outputs the reduction of elements (sum, product, minimum, and so on) 
    /// within one or more dimensions of the input tensor.
    /// </para>
    /// <para>
    /// Each output element is the result of applying a reduction function on a 
    /// subset of the input tensor. A reduction function, such as <em>sum</em>, 
    /// maps N input elements to a single output element. The input elements 
    /// involved in each reduction are determined by the provided input axes: 
    /// N is equal to the product of the sizes of the reduced axes. If all 
    /// input axes are specified, then the operator performs a reduction on the 
    /// entire input tensor and produces a single output element.
    /// </para>
    /// <para>
    /// Alias for DML_REDUCE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ReduceOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Reduce;

        ReduceFunction Function = ReduceFunction::ArgMax;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;

        ReduceOperatorDesc( ) noexcept = default;
        ReduceOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, ReduceFunction function = ReduceFunction::ArgMax, UInt32 axisCount = 0, const UInt32* axes = nullptr ) noexcept
            : Function( function ), InputTensor( inputTensor ), OutputTensor( outputTensor ), AxisCount( axisCount ), Axes( axes )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_REDUCE_OPERATOR_DESC );
    };
    static_assert( sizeof( ReduceOperatorDesc ) == sizeof( DML_REDUCE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Averages values across the elements within the sliding window over the input tensor.
    /// </para>
    /// <para>
    /// Alias for DML_AVERAGE_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AveragePoolingOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AveragePooling;

        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        BOOL IncludePadding = FALSE;

        AveragePoolingOperatorDesc( ) noexcept = default;
        AveragePoolingOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount = 0,
            const UInt32* strides = nullptr, const UInt32* windowSize = nullptr, const UInt32* startPadding = nullptr, const UInt32* endPadding = nullptr, bool includePadding = false ) noexcept
            : Base( inputTensor, outputTensor ), DimensionCount( dimensionCount ), Strides( strides ), WindowSize( windowSize ), StartPadding( startPadding ), EndPadding( endPadding ), IncludePadding( includePadding )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_AVERAGE_POOLING_OPERATOR_DESC );
    };
    static_assert( sizeof( AveragePoolingOperatorDesc ) == sizeof( DML_AVERAGE_POOLING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the Lp-normalized value across the elements within 
    /// the sliding window over the input tensor.
    /// </para>
    /// <para>
    /// Alias for DML_LP_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LPPoolingOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LPPooling;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        UInt32 P = 0;

        LPPoolingOperatorDesc( ) noexcept = default;
        LPPoolingOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount = 0,
            const UInt32* strides = nullptr, const UInt32* windowSize = nullptr, const UInt32* startPadding = nullptr, const UInt32* endPadding = nullptr, UInt32 p = 0 ) noexcept
            : Base( inputTensor, outputTensor ), DimensionCount( dimensionCount ), Strides( strides ), WindowSize( windowSize ), StartPadding( startPadding ), EndPadding( endPadding ), P( p )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LP_POOLING_OPERATOR_DESC );
    };
    static_assert( sizeof( LPPoolingOperatorDesc ) == sizeof( DML_LP_POOLING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the maximum value across the elements within the sliding 
    /// window over the input tensor.
    /// </para>
    /// <para>
    /// Alias for DML_MAX_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPoolingOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPooling;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;

        MaxPoolingOperatorDesc( ) noexcept = default;
        MaxPoolingOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount = 0,
            const UInt32* strides = nullptr, const UInt32* windowSize = nullptr, const UInt32* startPadding = nullptr, const UInt32* endPadding = nullptr ) noexcept
            : Base( inputTensor, outputTensor ), DimensionCount( dimensionCount ), Strides( strides ), WindowSize( windowSize ), StartPadding( startPadding ), EndPadding( endPadding )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING_OPERATOR_DESC );
    };
    static_assert( sizeof( MaxPoolingOperatorDesc ) == sizeof( DML_MAX_POOLING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a MaxPool function across the input tensor according to regions of interest.
    /// </para>
    /// <para>
    /// Alias for DML_ROI_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIPoolingOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ROIPooling;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ROITensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        FLOAT SpatialScale = 0.f;
        Size2D PooledSize;

        ROIPoolingOperatorDesc( ) noexcept = default;
        ROIPoolingOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* roiTensor = nullptr, FLOAT spatialScale = 0.f, Size2D pooledSize = {} ) noexcept
            : InputTensor( inputTensor ), ROITensor( roiTensor ), OutputTensor( outputTensor ), SpatialScale( spatialScale ), PooledSize( pooledSize )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_POOLING_OPERATOR_DESC );
    };
    static_assert( sizeof( ROIPoolingOperatorDesc ) == sizeof( DML_ROI_POOLING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Extracts a single subregion (a "slice") of an input tensor.
    /// </para>
    /// <para>
    /// The elements copied in the slice are determined using three values for each dimension.
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     The offset marks the first element to copy in a dimension.
    ///   </item>
    ///   <item>
    ///     The size marks the number of elements to copy in a dimension.
    ///   </item>
    ///   <item>
    ///     The stride indicates the element increment or step in a dimension.
    ///   </item>
    /// </list>
    /// <para>
    /// The provided Offsets, Sizes, and Strides must only copy elements that are 
    /// within the bounds of the input tensor (out-of-bounds reads are not permitted). 
    /// The Sizes of the slice must exactly match the output tensor sizes. 
    /// In general, the elements copied are calculated as follows.
    /// </para>
    /// <para>
    /// $$OutputTensor[OutputCoordinates] = InputTensor[Offsets + Strides \times OutputCoordinates]$$
    /// </para>
    /// <para>
    /// Alias for DML_SLICE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SliceOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Slice;

        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Offsets = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Sizes = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;

        SliceOperatorDesc( ) noexcept = default;
        SliceOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount = 0, const UInt32* offsets = nullptr, const UInt32* sizes = nullptr, const UInt32* strides = nullptr ) noexcept
            : Base( inputTensor, outputTensor ), DimensionCount( dimensionCount ), Offsets( offsets ), Sizes( sizes ), Strides( strides )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SLICE_OPERATOR_DESC );
    };
    static_assert( sizeof( SliceOperatorDesc ) == sizeof( DML_SLICE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Casts each element in the input to the data type of the output tensor, 
    /// and stores the result in the corresponding element of the output.
    /// </para>
    /// <para>
    /// Alias for DML_CAST_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct CastOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Cast;

        CastOperatorDesc( ) noexcept = default;
        CastOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CAST_OPERATOR_DESC );
    };
    static_assert( sizeof( CastOperatorDesc ) == sizeof( DML_CAST_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Splits an input tensor along an axis into multiple output tensors.
    /// </para>
    /// <para>
    /// All input and output tensors must have the same sizes, except for the split axis. 
    /// The size of input tensor in the split axis determines the possible splits. For example, 
    /// if the input tensor's split axis has size 3, then there are these potential splits: 
    /// 1+1+1 (3 outputs), 1+2 (2 outputs), 2+1 (2 outputs), or 3 (1 output, which is simply a copy of the input tensor). 
    /// The output tensors' split axis sizes must sum up to exactly the input tensor's 
    /// split axis size.
    /// </para>
    /// <para>
    /// Alias for DML_SPLIT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SplitOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Split;

        const TensorDesc* InputTensor = nullptr;
        UInt32 OutputCount = 0;
        _Field_size_( OutputCount ) const TensorDesc* OutputTensors = nullptr;
        UInt32 Axis = 0;

        SplitOperatorDesc( ) noexcept = default;
        SplitOperatorDesc( const TensorDesc* inputTensor, UInt32 outputTensorCount, const TensorDesc* outputTensors, UInt32 axis = 0 ) noexcept
            : InputTensor( inputTensor ), OutputCount( outputTensorCount ), OutputTensors( outputTensors ), Axis( axis )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SPLIT_OPERATOR_DESC );
    };
    static_assert( sizeof( SplitOperatorDesc ) == sizeof( DML_SPLIT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Concatenates an array of input tensors along a specified axis.
    /// </para>
    /// <para>
    /// Input tensors may only be joined if their sizes are identical in all 
    /// dimensions except for the join axis, which may contain any non-zero 
    /// size. The output sizes are equal to the input sizes except for the 
    /// join axis, which is the sum of all inputs' join axis size.
    /// </para>
    /// <para>
    /// Alias for DML_JOIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct JoinOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Join;

        UInt32 InputCount = 0;
        _Field_size_( InputCount ) const TensorDesc* InputTensors = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 Axis = 0;

        JoinOperatorDesc( ) noexcept = default;
        JoinOperatorDesc( UInt32 inputTensorCount, const TensorDesc* inputTensors, const TensorDesc* outputTensor, UInt32 axis = 0 ) noexcept
            : InputCount( inputTensorCount ), InputTensors( inputTensors ), OutputTensor( outputTensor ), Axis( axis )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_JOIN_OPERATOR_DESC );
    };
    static_assert( sizeof( JoinOperatorDesc ) == sizeof( DML_JOIN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Inflates the input tensor with constant or mirrored values on 
    /// the edges, and writes the result to the output.
    /// </para>
    /// <para>
    /// Alias for DML_PADDING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct PaddingOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Padding;

        DML::PaddingMode PaddingMode = DML::PaddingMode::Constant;
        FLOAT PaddingValue = 0.f;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;

        PaddingOperatorDesc( ) noexcept = default;
        PaddingOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount = 0, const UInt32* startPadding = nullptr, const UInt32* endPadding = nullptr, FLOAT paddingValue = 0.f, DML::PaddingMode paddingMode = DML::PaddingMode::Constant ) noexcept
            : Base( inputTensor, outputTensor ), PaddingMode( paddingMode ), PaddingValue( paddingValue ), DimensionCount( dimensionCount ), StartPadding( startPadding ), EndPadding( endPadding )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_PADDING_OPERATOR_DESC );
    };
    static_assert( sizeof( PaddingOperatorDesc ) == sizeof( DML_PADDING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs an element-wise scale-and-bias function
    /// </para>
    /// <para>
    /// Output = Scale * Input + Bias. 
    /// </para>
    /// <para>
    /// This operator is similar to using an ElementWiseIdentityOperatorDesc 
    /// with a scale and bias, except that ValueScale2DOperatorDesc applies a 
    /// different bias for each channel, rather than a single bias for the entire tensor.
    /// </para>
    /// <para>
    /// Alias for DML_VALUE_SCALE_2D_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ValueScale2DOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ValueScale2D;

        FLOAT Scale = 0.f;
        UInt32 ChannelCount = 0;
        _Field_size_( ChannelCount ) const FLOAT* Bias = nullptr;

        ValueScale2DOperatorDesc( ) noexcept = default;
        ValueScale2DOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, FLOAT scale = 0.f, UInt32 channelCount = 0, const FLOAT* bias = nullptr ) noexcept
            : Base( inputTensor, outputTensor ), Scale( scale ), ChannelCount( channelCount ), Bias( bias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_VALUE_SCALE_2D_OPERATOR_DESC );
    };
    static_assert( sizeof( ValueScale2DOperatorDesc ) == sizeof( DML_VALUE_SCALE_2D_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Upsamples the input image, writing the result into the output 
    /// tensor. The order of the dimensions should be NCHW 
    /// (BatchSize, ChannelCount, Height, Width) or NCDHW (BatchSize, 
    /// ChannelCount, Depth, Height, Width), but strides can be 
    /// used if the data is stored in a different format. 
    /// Unlike ResampleOperatorDesc, only the last 2 dimensions 
    /// (height and width) can be upsampled.
    /// </para>
    /// <para>
    /// Alias for DML_UPSAMPLE_2D_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct UpSample2DOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::UpSample2D;

        Size2D ScaleSize;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;

        UpSample2DOperatorDesc( ) noexcept = default;
        UpSample2DOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, Size2D scaleSize = {}, DML::InterpolationMode interpolationMode = DML::InterpolationMode::NearestNeighbor ) noexcept
            : Base( inputTensor, outputTensor ), ScaleSize( scaleSize ), InterpolationMode( interpolationMode )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_UPSAMPLE_2D_OPERATOR_DESC );
    };
    static_assert( sizeof( UpSample2DOperatorDesc ) == sizeof( DML_UPSAMPLE_2D_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Gathers elements from the input tensor along Axis, using IndicesTensor to remap indices. 
    /// </para>
    /// <para>
    /// Alias for DML_GATHER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Gather;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 Axis = 0;
        UInt32 IndexDimensions = 0;

        GatherOperatorDesc( ) noexcept = default;
        GatherOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* indicesTensor = nullptr, UInt32 axis = 0, UInt32 indexDimensions = 0 ) noexcept
            : InputTensor( inputTensor ), IndicesTensor( indicesTensor ), OutputTensor( outputTensor ), Axis( axis ), IndexDimensions( indexDimensions )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_OPERATOR_DESC );
    };
    static_assert( sizeof( GatherOperatorDesc ) == sizeof( DML_GATHER_OPERATOR_DESC ) );


    /// <summary>
    /// <para>
    /// Rearranges blocks of spatial data into depth. The operator outputs a 
    /// copy of the input tensor where values from the height and width 
    /// dimensions are moved to the depth dimension.
    /// </para>
    /// <para>
    /// Alias for DML_SPACE_TO_DEPTH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SpaceToDepthOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::SpaceToDepth;
        UInt32 BlockSize = 0;

        SpaceToDepthOperatorDesc( ) noexcept = default;
        SpaceToDepthOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 blockSize = 0 ) noexcept
            : Base( inputTensor, outputTensor ), BlockSize( blockSize )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SPACE_TO_DEPTH_OPERATOR_DESC );
    };
    static_assert( sizeof( SpaceToDepthOperatorDesc ) == sizeof( DML_SPACE_TO_DEPTH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Rearranges (permutes) data from depth into blocks of spatial 
    /// data. The operator outputs a copy of the input tensor where 
    /// values from the depth dimension are moved in spatial blocks to 
    /// the height and width dimensions.
    /// </para>
    /// <para>
    /// Alias for DML_DEPTH_TO_SPACE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DepthToSpaceOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DepthToSpace;
        UInt32 BlockSize = 0;

        DepthToSpaceOperatorDesc( ) noexcept = default;
        DepthToSpaceOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 blockSize = 0 ) noexcept
            : Base( inputTensor, outputTensor ), BlockSize( blockSize )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DEPTH_TO_SPACE_OPERATOR_DESC );
    };
    static_assert( sizeof( DepthToSpaceOperatorDesc ) == sizeof( DML_DEPTH_TO_SPACE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Constructs an output tensor by tiling the input tensor. The 
    /// elements in each dimension of the input tensor are repeated 
    /// by a multiple in the Repeats array.
    /// </para>
    /// <para>
    /// Alias for DML_TILE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct TileOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Tile;
        UInt32 RepeatsCount = 0;
        _Field_size_( RepeatsCount ) const UInt32* Repeats = nullptr;

        TileOperatorDesc( ) noexcept = default;
        TileOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 repeatsCount = 0, const UInt32* repeats = nullptr ) noexcept
            : Base( inputTensor, outputTensor ), RepeatsCount( repeatsCount ), Repeats( repeats )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_TILE_OPERATOR_DESC );
    };
    static_assert( sizeof( TileOperatorDesc ) == sizeof( DML_TILE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Selects the largest K elements from each sequence along an axis of the 
    /// InputTensor, and returns the values and indices of those elements in 
    /// the OutputValueTensor and OutputIndexTensor, respectively. A sequence 
    /// refers to one of the sets of elements that exist along the Axis 
    /// dimension of the InputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_TOP_K_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct TopKOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::TopK;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputValueTensor = nullptr;
        const TensorDesc* OutputIndexTensor = nullptr;
        UInt32 Axis = 0;
        UInt32 K = 0;

        TopKOperatorDesc( ) noexcept = default;
        TopKOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputValueTensor, const TensorDesc* outputIndexTensor, UInt32 axis = 0, UInt32 k = 0 ) noexcept
            : InputTensor( inputTensor ), OutputValueTensor( outputValueTensor ), OutputIndexTensor( outputIndexTensor ), Axis( axis ), K( k )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_TOP_K_OPERATOR_DESC );
    };
    static_assert( sizeof( TopKOperatorDesc ) == sizeof( DML_TOP_K_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a batch normalization on the input. This operator performs the following computation: 
    /// </para>
    /// <para>
    /// $$Output = FusedActivation(Scale \times \frac{Input - Mean}{ \sqrt{Variance + Epsilon} } + Bias)$$
    /// </para>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::BatchNormalization;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* MeanTensor = nullptr;
        const TensorDesc* VarianceTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        BOOL Spatial = FALSE;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        BatchNormalizationOperatorDesc( ) noexcept = default;
        BatchNormalizationOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor,
            const TensorDesc* meanTensor = nullptr, const TensorDesc* varianceTensor = nullptr, const TensorDesc* scaleTensor = nullptr,
            const TensorDesc* biasTensor = nullptr, float epsilon = 0.f, const OperatorDesc* fusedActivation = nullptr ) noexcept
            : InputTensor( inputTensor ), MeanTensor( meanTensor ), VarianceTensor( varianceTensor ), ScaleTensor( scaleTensor ),
            BiasTensor( biasTensor ), OutputTensor( outputTensor ), Epsilon( epsilon ), FusedActivation( fusedActivation )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BATCH_NORMALIZATION_OPERATOR_DESC );
    };
    static_assert( sizeof( BatchNormalizationOperatorDesc ) == sizeof( DML_BATCH_NORMALIZATION_OPERATOR_DESC ) );


    /// <summary>
    /// <para>
    /// Performs a mean variance normalization function on the 
    /// input tensor. This operator will calculate the mean 
    /// and variance of the input tensor to perform normalization. 
    /// This operator performs the following computation:
    /// </para>
    /// <para>
    /// $$Output = FusedActivation(Scale \times \frac{Input - Mean}{ \sqrt{Variance + Epsilon} } + Bias)$$
    /// </para>
    /// <para>
    /// Alias for DML_MEAN_VARIANCE_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MeanVarianceNormalizationOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MeanVarianceNormalization;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        BOOL CrossChannel = FALSE;
        BOOL NormalizeVariance = FALSE;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        MeanVarianceNormalizationOperatorDesc( ) noexcept = default;

        MeanVarianceNormalizationOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* scaleTensor = nullptr, const TensorDesc* biasTensor = nullptr, bool crossChannel = false, bool normalizeVariance = false, float epsilon = 0.f, const OperatorDesc* fusedActivation = nullptr ) noexcept
            : InputTensor( inputTensor ), ScaleTensor( scaleTensor ), BiasTensor( biasTensor ), OutputTensor( outputTensor ), CrossChannel( crossChannel ), NormalizeVariance( normalizeVariance ), Epsilon( epsilon ), FusedActivation( fusedActivation )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MEAN_VARIANCE_NORMALIZATION_OPERATOR_DESC );
    };
    static_assert( sizeof( MeanVarianceNormalizationOperatorDesc ) == sizeof( DML_MEAN_VARIANCE_NORMALIZATION_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a local response normalization (LRN) function on the input. This operator performs the following computation:
    /// </para>
    /// <para>
    /// $$b_{c} = a_{c}\left(k + \frac{\alpha}{n}\sum_{c'=\max(0, c-n/2)}^{\min(N-1,c+n/2)}a_{c'}^2\right)^{-\beta}$$
    /// </para>
    /// <para>
    /// Alias for DML_LOCAL_RESPONSE_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LocalResponseNormalizationOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LocalResponseNormalization;

        BOOL CrossChannel = FALSE;
        UInt32 LocalSize = 0;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;
        FLOAT Bias = 0.f;

        LocalResponseNormalizationOperatorDesc( ) noexcept = default;
        LocalResponseNormalizationOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, bool crossChannel, UInt32 localSize, float alpha = 0.0001f, float beta = 0.75f, float bias = 1.f ) noexcept
            : Base( inputTensor, outputTensor ), CrossChannel( crossChannel ), LocalSize( localSize ), Alpha( alpha ), Beta( beta ), Bias( bias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LOCAL_RESPONSE_NORMALIZATION_OPERATOR_DESC );
    };
    static_assert( sizeof( LocalResponseNormalizationOperatorDesc ) == sizeof( DML_LOCAL_RESPONSE_NORMALIZATION_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs an Lp-normalization function along the specified axis of the input tensor.
    /// </para>
    /// <para>
    /// Alias for DML_LP_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LPNormalizationOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LPNormalization;

        UInt32 Axis = 0;
        FLOAT Epsilon = 0.f;
        UInt32 P = 0;

        LPNormalizationOperatorDesc( ) noexcept = default;
        LPNormalizationOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 axis = 0, float epsilon = 0.00001f, UInt32 p = 1 ) noexcept
            : Base( inputTensor, outputTensor ), Axis( axis ), Epsilon( epsilon ), P( p )
        { }


        DML_IMPLEMENT_CONVERSIONS_TO( DML_LP_NORMALIZATION_OPERATOR_DESC );
    };
    static_assert( sizeof( LPNormalizationOperatorDesc ) == sizeof( DML_LP_NORMALIZATION_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a one-layer simple recurrent neural network (RNN) function 
    /// on the input. This function is often referred to as the Input Gate. 
    /// This operator performs this function multiple times in a loop, dictated by 
    /// the sequence length dimension and the SequenceLengthsTensor.
    /// </para>
    /// <para>
    /// Alias for DML_RNN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct RNNOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::RNN;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* WeightTensor = nullptr;
        const TensorDesc* RecurrenceTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* HiddenInitTensor = nullptr;
        _Maybenull_ const TensorDesc* SequenceLengthsTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSequenceTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSingleTensor = nullptr;
        UInt32 ActivationDescCount = 0;
        _Field_size_( ActivationDescCount ) const OperatorDesc* ActivationDescs = nullptr;
        RecurrentNetworkDirection Direction = RecurrentNetworkDirection::Forward;

        RNNOperatorDesc( ) noexcept = default;
        RNNOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* weightTensor, const TensorDesc* recurrenceTensor, const TensorDesc* biasTensor, const TensorDesc* hiddenInitTensor, const TensorDesc* sequenceLengthsTensor, const TensorDesc* outputSequenceTensor, const TensorDesc* outputSingleTensor, UInt32 activationDescCount, const OperatorDesc* activationDescs, RecurrentNetworkDirection direction ) noexcept
            : InputTensor( inputTensor ), WeightTensor( weightTensor ), RecurrenceTensor( recurrenceTensor ), BiasTensor( biasTensor ), HiddenInitTensor( hiddenInitTensor ), SequenceLengthsTensor( sequenceLengthsTensor ), OutputSequenceTensor( outputSequenceTensor ), OutputSingleTensor( outputSingleTensor ), ActivationDescCount( activationDescCount ), ActivationDescs( activationDescs ), Direction( direction )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RNN_OPERATOR_DESC );
    };
    static_assert( sizeof( RNNOperatorDesc ) == sizeof( DML_RNN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a one-layer long short term memory (LSTM) function on the input. 
    /// This operator uses multiple gates to perform this layer. These gates are 
    /// performed multiple times in a loop, dictated by the sequence length dimension 
    /// and the SequenceLengthsTensor.
    /// </para>
    /// <para>
    /// Alias for DML_LSTM_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LSTMOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LSTM;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* WeightTensor = nullptr;
        const TensorDesc* RecurrenceTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* HiddenInitTensor = nullptr;
        _Maybenull_ const TensorDesc* CellMemInitTensor = nullptr;
        _Maybenull_ const TensorDesc* SequenceLengthsTensor = nullptr;
        _Maybenull_ const TensorDesc* PeepholeTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSequenceTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSingleTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputCellSingleTensor = nullptr;
        UInt32 ActivationDescCount = 0;
        _Field_size_( ActivationDescCount ) const OperatorDesc* ActivationDescs = nullptr;
        RecurrentNetworkDirection Direction = RecurrentNetworkDirection::Forward;
        float ClipThreshold = 0.f;
        BOOL UseClipThreshold = FALSE;
        BOOL CoupleInputForget = FALSE;

        LSTMOperatorDesc( ) noexcept = default;
        LSTMOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* weightTensor, const TensorDesc* recurrenceTensor, const TensorDesc* biasTensor, const TensorDesc* hiddenInitTensor, const TensorDesc* cellMemInitTensor, const TensorDesc* sequenceLengthsTensor, const TensorDesc* peepholeTensor, const TensorDesc* outputSequenceTensor, const TensorDesc* outputSingleTensor, const TensorDesc* outputCellSingleTensor, UInt32 activationDescCount, const OperatorDesc* activationDescs, RecurrentNetworkDirection direction, float clipThreshold, bool useClipThreshold, bool coupleInputForget ) noexcept
            : InputTensor( inputTensor ), WeightTensor( weightTensor ), RecurrenceTensor( recurrenceTensor ), BiasTensor( biasTensor ), HiddenInitTensor( hiddenInitTensor ), CellMemInitTensor( cellMemInitTensor ), SequenceLengthsTensor( sequenceLengthsTensor ), PeepholeTensor( peepholeTensor ), OutputSequenceTensor( outputSequenceTensor ), OutputSingleTensor( outputSingleTensor ), OutputCellSingleTensor( outputCellSingleTensor ), ActivationDescCount( activationDescCount ), ActivationDescs( activationDescs ), Direction( direction ), ClipThreshold( clipThreshold ), UseClipThreshold( useClipThreshold ), CoupleInputForget( coupleInputForget )
        {}


        DML_IMPLEMENT_CONVERSIONS_TO( DML_LSTM_OPERATOR_DESC );
    };
    static_assert( sizeof( LSTMOperatorDesc ) == sizeof( DML_LSTM_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs a (standard layers) one-layer gated recurrent 
    /// unit (GRU) function on the input. This operator uses multiple 
    /// gates to perform this layer. These gates are performed multiple 
    /// times in a loop dictated by the sequence length dimension and 
    /// the SequenceLengthsTensor.
    /// </para>
    /// <para>
    /// Alias for DML_GRU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GRUOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GRU;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* WeightTensor = nullptr;
        const TensorDesc* RecurrenceTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* HiddenInitTensor = nullptr;
        _Maybenull_ const TensorDesc* SequenceLengthsTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSequenceTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSingleTensor = nullptr;
        UInt32 ActivationDescCount = 0;
        _Field_size_( ActivationDescCount ) const OperatorDesc* ActivationDescs = nullptr;
        RecurrentNetworkDirection Direction = RecurrentNetworkDirection::Forward;
        BOOL LinearBeforeReset = FALSE;

        GRUOperatorDesc( ) noexcept = default;
        GRUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* weightTensor, const TensorDesc* recurrenceTensor, const TensorDesc* biasTensor, const TensorDesc* hiddenInitTensor, const TensorDesc* sequenceLengthsTensor, const TensorDesc* outputSequenceTensor, const TensorDesc* outputSingleTensor, UInt32 activationDescCount, const OperatorDesc* activationDescs, RecurrentNetworkDirection direction, bool linearBeforeReset ) noexcept
            : InputTensor( inputTensor ), WeightTensor( weightTensor ), RecurrenceTensor( recurrenceTensor ), BiasTensor( biasTensor ), HiddenInitTensor( hiddenInitTensor ), SequenceLengthsTensor( sequenceLengthsTensor ), OutputSequenceTensor( outputSequenceTensor ), OutputSingleTensor( outputSingleTensor ), ActivationDescCount( activationDescCount ), ActivationDescs( activationDescs ), Direction( direction ), LinearBeforeReset( linearBeforeReset )
        { }
        DML_IMPLEMENT_CONVERSIONS_TO( DML_GRU_OPERATOR_DESC );
    };
    static_assert( sizeof( GRUOperatorDesc ) == sizeof( DML_GRU_OPERATOR_DESC ) );

#if DML_TARGET_VERSION >= 0x2000

    /// <summary>
    /// <para>
    /// Returns a value representing the sign of each element of 
    /// InputTensor, placing the result into the corresponding 
    /// element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SIGN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSignOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSign;

        ElementWiseSignOperatorDesc( ) noexcept = default;
        ElementWiseSignOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SIGN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseSignOperatorDesc ) == sizeof( DML_ELEMENT_WISE_SIGN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// For each element of the input tensor, returns 1 if the input 
    /// is NaN (as defined by IEEE-754), and 0 otherwise. The result 
    /// is placed into the corresponding element of the output tensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IS_NAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIsNaNOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIsNaN;

        ElementWiseIsNaNOperatorDesc( ) noexcept = default;
        ElementWiseIsNaNOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IS_NAN_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseIsNaNOperatorDesc ) == sizeof( DML_ELEMENT_WISE_IS_NAN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the Gaussian error function (erf) on each element 
    /// of InputTensor, placing the result into the corresponding 
    /// element of OutputTensor.
    /// </para>
    /// $$erf(x)=\frac{2}{\sqrt{\pi}}\int_{0}^{x}e^{-t^{2}}\, dt$$
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ERF_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseErfOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseErf;

        ElementWiseErfOperatorDesc( ) noexcept = default;
        ElementWiseErfOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ERF_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseErfOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ERF_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the hyperbolic sine of each element of InputTensor, placing 
    /// the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SINH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSinHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSinH;

        ElementWiseSinHOperatorDesc( ) noexcept = default;
        ElementWiseSinHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SINH_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseSinHOperatorDesc ) == sizeof( DML_ELEMENT_WISE_SINH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the hyperbolic cosine of each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_COSH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseCosHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseCosH;

        ElementWiseCosHOperatorDesc( ) noexcept = default;
        ElementWiseCosHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_COSH_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseCosHOperatorDesc ) == sizeof( DML_ELEMENT_WISE_COSH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the hyperbolic tangent of element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_TANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseTanHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseTanH;

        ElementWiseTanHOperatorDesc( ) noexcept = default;
        ElementWiseTanHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_TANH_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseTanHOperatorDesc ) == sizeof( DML_ELEMENT_WISE_TANH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the hyperbolic arcsine for each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ASINH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseASinHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseASinH;

        ElementWiseASinHOperatorDesc( ) noexcept = default;
        ElementWiseASinHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ASINH_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseASinHOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ASINH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the hyperbolic arccosine for each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ACOSH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseACosHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseACosH;

        ElementWiseACosHOperatorDesc( ) noexcept = default;
        ElementWiseACosHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ACOSH_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseACosHOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ACOSH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Computes the hyperbolic arctangent for each element of InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ATANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseATanHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseATanH;

        ElementWiseATanHOperatorDesc( ) noexcept = default;
        ElementWiseATanHOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const DML::ScaleBias* scaleBias = nullptr ) noexcept
            : Base( inputTensor, outputTensor, scaleBias )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ATANH_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseATanHOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ATANH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Selects elements either from ATensor or BTensor, depending on the value 
    /// of the corresponding element in ConditionTensor. Non-zero elements of 
    /// ConditionTensor select from ATensor, while zero-valued elements select 
    /// from BTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IF_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIfOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIf;

        const TensorDesc* ConditionTensor = nullptr;
        const TensorDesc* ATensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        ElementWiseIfOperatorDesc( ) noexcept = default;
        ElementWiseIfOperatorDesc( const TensorDesc* conditionTensor, const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : ConditionTensor( conditionTensor ), ATensor( inputTensorA ), BTensor( inputTensorB ), OutputTensor( outputTensor )
        {
        }


        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IF_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseIfOperatorDesc ) == sizeof( DML_ELEMENT_WISE_IF_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Performs the shrink activation function on every element in InputTensor, 
    /// placing the result into the corresponding element of OutputTensor.
    /// </para>
    /// <para>
    /// Alias for DML_ACTIVATION_SHRINK_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationShrinkOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationShrink;

        float Bias = 0.f;
        float Threshold = 0.f;

        ActivationShrinkOperatorDesc( ) noexcept = default;
        ActivationShrinkOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float bias = 0.0f, float threshold = 0.5f ) noexcept
            : Base( inputTensor, outputTensor ), Bias( bias ), Threshold( threshold )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SHRINK_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationShrinkOperatorDesc ) == sizeof( DML_ACTIVATION_SHRINK_OPERATOR_DESC ) );

    /// <summary>
    /// Computes the maximum value across the elements within 
    /// the sliding window over the input tensor, and optionally 
    /// returns the indices of the maximum values selected.
    /// <para>
    /// Alias for DML_MAX_POOLING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPooling1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPooling1;

        _Maybenull_ const TensorDesc* OutputIndicesTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;

        MaxPooling1OperatorDesc( ) noexcept = default;
        MaxPooling1OperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* outputIndicesTensor, UInt32 dimensionCount, const UInt32* strides, const UInt32* windowSize, const UInt32* startPadding, const UInt32* endPadding ) noexcept
            : Base( inputTensor, outputTensor ), OutputIndicesTensor( outputIndicesTensor ), DimensionCount( dimensionCount ), Strides( strides ), WindowSize( windowSize ), StartPadding( startPadding ), EndPadding( endPadding )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING1_OPERATOR_DESC );
    };
    static_assert( sizeof( MaxPooling1OperatorDesc ) == sizeof( DML_MAX_POOLING1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Inverts a max-pooling operation (see MaxPooling1OperatorDesc for details) 
    /// by filling the output tensor OutputTensor with the values 
    /// in the input tensor InputTensor, as obtained from a max-pooling 
    /// operation, according to the index values provided in the 
    /// IndicesTensor. The elements in the output tensor untouched 
    /// by this process are left with zero values.
    /// </para>
    /// <para>
    /// Alias for DML_MAX_UNPOOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxUnpoolingOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxUnpooling;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        MaxUnpoolingOperatorDesc( ) noexcept = default;
        MaxUnpoolingOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* indicesTensor, const TensorDesc* outputTensor ) noexcept
            : InputTensor( inputTensor ), IndicesTensor( indicesTensor ), OutputTensor( outputTensor )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_UNPOOLING_OPERATOR_DESC );
    };
    static_assert( sizeof( MaxUnpoolingOperatorDesc ) == sizeof( DML_MAX_UNPOOLING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Generates an identity-like matrix with ones (or other explicit 
    /// value) on the major diagonal, and zeros everywhere else. The 
    /// diagonal ones may be shifted (via Offset) where <c>OutputTensor[i, i + Offset] = Value</c>, 
    /// meaning that an argument of Offset greater than zero shifts 
    /// all values to the right, and less than zero shifts them to 
    /// the left. This generator operator is useful for models to 
    /// avoid storing a large constant tensor. Any leading dimensions 
    /// before the last two are treated as a batch count, meaning 
    /// that the tensor is treated as stack of 2D matrices.
    /// </para>
    /// <para>
    /// Alias for DML_DIAGONAL_MATRIX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DiagonalMatrixOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DiagonalMatrix;

        const TensorDesc* OutputTensor = nullptr;
        INT Offset = 0;
        FLOAT Value = 0.f;

        DiagonalMatrixOperatorDesc( ) noexcept = default;
        DiagonalMatrixOperatorDesc( const TensorDesc* outputTensor, Int32 offset = 0, float value = 1.f ) noexcept
            : OutputTensor( outputTensor ), Offset( offset ), Value( value )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DIAGONAL_MATRIX_OPERATOR_DESC );
    };
    static_assert( sizeof( DiagonalMatrixOperatorDesc ) == sizeof( DML_DIAGONAL_MATRIX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Copies the whole input tensor to the output, then overwrites selected indices with corresponding values from the updates tensor.
    /// </para>
    /// <para>
    /// Alias for DML_SCATTER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ScatterElementsOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ScatterElements;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* UpdatesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 Axis = 0;

        ScatterElementsOperatorDesc( ) noexcept = default;
        ScatterElementsOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* indicesTensor, const TensorDesc* updatesTensor, const TensorDesc* outputTensor, UInt32 axis ) noexcept
            : InputTensor( inputTensor ), IndicesTensor( indicesTensor ), UpdatesTensor( updatesTensor ), OutputTensor( outputTensor ), Axis( axis )
        { }


        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCATTER_OPERATOR_DESC );
    };
    static_assert( sizeof( ScatterElementsOperatorDesc ) == sizeof( DML_SCATTER_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ONE_HOT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct OneHotOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::OneHot;

        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* ValuesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 Axis = 0;

        OneHotOperatorDesc( ) noexcept = default;
        OneHotOperatorDesc( const TensorDesc* indicesTensor, const TensorDesc* valuesTensor, const TensorDesc* outputTensor, UInt32 axis ) noexcept
            : IndicesTensor( indicesTensor ), ValuesTensor( valuesTensor ), OutputTensor( outputTensor ), Axis( axis )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ONE_HOT_OPERATOR_DESC );
    };
    static_assert( sizeof( OneHotOperatorDesc ) == sizeof( DML_ONE_HOT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ResampleOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample;

        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        UInt32 ScaleCount = 0;
        _Field_size_( ScaleCount ) const FLOAT* Scales = nullptr;

        ResampleOperatorDesc( ) noexcept = default;
        ResampleOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, DML::InterpolationMode interpolationMode, UInt32 scaleCount, const FLOAT* scales ) noexcept
            : Base( inputTensor, outputTensor ), InterpolationMode( interpolationMode ), ScaleCount( scaleCount ), Scales( scales )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE_OPERATOR_DESC );
    };
    static_assert( sizeof( ResampleOperatorDesc ) == sizeof( DML_RESAMPLE_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x2000

#if DML_TARGET_VERSION >= 0x2100

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_SHIFT_LEFT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitShiftLeftOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitShiftLeft;

        ElementWiseBitShiftLeftOperatorDesc( ) noexcept = default;
        ElementWiseBitShiftLeftOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_SHIFT_LEFT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitShiftLeftOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_SHIFT_LEFT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_SHIFT_RIGHT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitShiftRightOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitShiftRight;

        ElementWiseBitShiftRightOperatorDesc( ) noexcept = default;
        ElementWiseBitShiftRightOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_SHIFT_RIGHT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitShiftRightOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_SHIFT_RIGHT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ROUND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseRoundOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseRound;

        DML::RoundingMode RoundingMode = DML::RoundingMode::HalvesToNearestEven;

        ElementWiseRoundOperatorDesc( ) noexcept = default;

        ElementWiseRoundOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, DML::RoundingMode roundingMode = DML::RoundingMode::HalvesToNearestEven ) noexcept
            : Base( inputTensor, outputTensor ), RoundingMode( roundingMode )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ROUND_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseRoundOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ROUND_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IS_INFINITY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIsInfinityOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIsInfinity;

        IsInfinityMode InfinityMode = IsInfinityMode::Either;

        ElementWiseIsInfinityOperatorDesc( ) noexcept = default;

        ElementWiseIsInfinityOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, IsInfinityMode infinityMode = IsInfinityMode::Either ) noexcept
            : Base( inputTensor, outputTensor ), InfinityMode( infinityMode )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IS_INFINITY_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseIsInfinityOperatorDesc ) == sizeof( DML_ELEMENT_WISE_IS_INFINITY_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MODULUS_TRUNCATE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseModulusTruncateOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseModulusTruncate;

        ElementWiseModulusTruncateOperatorDesc( ) noexcept = default;
        ElementWiseModulusTruncateOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MODULUS_TRUNCATE_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseModulusTruncateOperatorDesc ) == sizeof( DML_ELEMENT_WISE_MODULUS_TRUNCATE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MODULUS_FLOOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseModulusFloorOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseModulusFloor;

        ElementWiseModulusFloorOperatorDesc( ) noexcept = default;
        ElementWiseModulusFloorOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MODULUS_FLOOR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseModulusFloorOperatorDesc ) == sizeof( DML_ELEMENT_WISE_MODULUS_FLOOR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_FILL_VALUE_CONSTANT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct FillValueConstantOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::FillValueConstant;

        const TensorDesc* OutputTensor = nullptr;
        TensorDataType ValueDataType = TensorDataType::Unknown;
        ScalarUnion Value{};

        FillValueConstantOperatorDesc( ) noexcept = default;
        FillValueConstantOperatorDesc( const TensorDesc* outputTensor, TensorDataType valueDataType, const ScalarUnion& value ) noexcept
            : OutputTensor( outputTensor ), ValueDataType( valueDataType ), Value( value )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FILL_VALUE_CONSTANT_OPERATOR_DESC );
    };
    static_assert( sizeof( FillValueConstantOperatorDesc ) == sizeof( DML_FILL_VALUE_CONSTANT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_FILL_VALUE_SEQUENCE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct FillValueSequenceOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::FillValueSequence;

        const TensorDesc* OutputTensor = nullptr;
        TensorDataType ValueDataType = TensorDataType::Unknown;
        ScalarUnion ValueStart{};
        ScalarUnion ValueDelta{};

        FillValueSequenceOperatorDesc( ) noexcept = default;

        FillValueSequenceOperatorDesc( const TensorDesc* outputTensor, TensorDataType valueDataType, const ScalarUnion& valueStart, const ScalarUnion& valueDelta ) noexcept
            : OutputTensor( outputTensor ), ValueDataType( valueDataType ), ValueStart( valueStart ), ValueDelta( valueDelta )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FILL_VALUE_SEQUENCE_OPERATOR_DESC );
    };
    static_assert( sizeof( FillValueSequenceOperatorDesc ) == sizeof( DML_FILL_VALUE_SEQUENCE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_CUMULATIVE_SUMMATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct CumulativeSummationOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::CumulativeSummation;

        UInt32 Axis = 0;
        AxisDirection AxisDirection = AxisDirection::Increasing;
        BOOL HasExclusiveSum = FALSE;

        CumulativeSummationOperatorDesc( ) noexcept = default;
        CumulativeSummationOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 axis, DML::AxisDirection axisDirection = AxisDirection::Increasing, bool hasExclusiveSum = false ) noexcept
            : Base( inputTensor, outputTensor ), Axis( axis ), AxisDirection( axisDirection ), HasExclusiveSum( hasExclusiveSum )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CUMULATIVE_SUMMATION_OPERATOR_DESC );
    };
    static_assert( sizeof( CumulativeSummationOperatorDesc ) == sizeof( DML_CUMULATIVE_SUMMATION_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_REVERSE_SUBSEQUENCES_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ReverseSubsequencesOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ReverseSubsequences;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* SequenceLengthsTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 Axis = 0;

        ReverseSubsequencesOperatorDesc( ) noexcept = default;
        ReverseSubsequencesOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* sequenceLengthsTensor, const TensorDesc* outputTensor, UInt32 axis ) noexcept
            : InputTensor( inputTensor ), SequenceLengthsTensor( sequenceLengthsTensor ), OutputTensor( outputTensor ), Axis( axis )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_REVERSE_SUBSEQUENCES_OPERATOR_DESC );
    };
    static_assert( sizeof( ReverseSubsequencesOperatorDesc ) == sizeof( DML_REVERSE_SUBSEQUENCES_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_ELEMENTS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherElementsOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GatherElements;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 Axis = 0;

        GatherElementsOperatorDesc( ) noexcept = default;
        GatherElementsOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* indicesTensor, const TensorDesc* outputTensor, UInt32 axis ) noexcept
            : InputTensor( inputTensor ), IndicesTensor( indicesTensor ), OutputTensor( outputTensor ), Axis( axis )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_ELEMENTS_OPERATOR_DESC );
    };
    static_assert( sizeof( GatherElementsOperatorDesc ) == sizeof( DML_GATHER_ELEMENTS_OPERATOR_DESC ) );

    // Alias existing operator, symmetric with ScatterOperatorDesc.
    using ScatterOperatorDesc = ScatterElementsOperatorDesc;

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_ND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherNDOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GatherND;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 InputDimensionCount = 0;
        UInt32 IndicesDimensionCount = 0;

        GatherNDOperatorDesc( ) noexcept = default;
        GatherNDOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* indicesTensor, const TensorDesc* outputTensor, UInt32 inputDimensionCount, UInt32 indicesDimensionCount) noexcept
            : InputTensor( inputTensor ), IndicesTensor( indicesTensor ), OutputTensor( outputTensor ), InputDimensionCount( inputDimensionCount ), IndicesDimensionCount( indicesDimensionCount )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_ND_OPERATOR_DESC );
    };
    static_assert( sizeof( GatherNDOperatorDesc ) == sizeof( DML_GATHER_ND_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_SCATTER_ND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ScatterNDOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ScatterND;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* UpdatesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 InputDimensionCount = 0;
        UInt32 IndicesDimensionCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCATTER_ND_OPERATOR_DESC );
    };
    static_assert( sizeof( ScatterNDOperatorDesc ) == sizeof( DML_SCATTER_ND_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_POOLING2_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPooling2OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPooling2;

        _Maybenull_ const TensorDesc* OutputIndicesTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING2_OPERATOR_DESC );
    };
    static_assert( sizeof( MaxPooling2OperatorDesc ) == sizeof( DML_MAX_POOLING2_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_SLICE1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Slice1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Slice1;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* InputWindowOffsets = nullptr;
        _Field_size_( DimensionCount ) const UInt32* InputWindowSizes = nullptr;
        _Field_size_( DimensionCount ) const INT* InputWindowStrides = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SLICE1_OPERATOR_DESC );
    };
    static_assert( sizeof( Slice1OperatorDesc ) == sizeof( DML_SLICE1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_TOP_K1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct TopK1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::TopK1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputValueTensor = nullptr;
        const TensorDesc* OutputIndexTensor = nullptr;
        UInt32 Axis = 0;
        UInt32 K = 0;
        AxisDirection AxisDirection = AxisDirection::Increasing;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_TOP_K1_OPERATOR_DESC );
    };
    static_assert( sizeof( TopK1OperatorDesc ) == sizeof( DML_TOP_K1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_DEPTH_TO_SPACE1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DepthToSpace1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DepthToSpace1;
        UInt32 BlockSize = 0;
        DepthSpaceOrder Order = DepthSpaceOrder::DepthColumnRow;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_DEPTH_TO_SPACE1_OPERATOR_DESC );
    };
    static_assert( sizeof( DepthToSpace1OperatorDesc ) == sizeof( DML_DEPTH_TO_SPACE1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_SPACE_TO_DEPTH1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SpaceToDepth1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::SpaceToDepth1;
        UInt32 BlockSize = 0;
        DepthSpaceOrder Order = DepthSpaceOrder::DepthColumnRow;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SPACE_TO_DEPTH1_OPERATOR_DESC );
    };
    static_assert( sizeof( SpaceToDepth1OperatorDesc ) == sizeof( DML_SPACE_TO_DEPTH1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_MEAN_VARIANCE_NORMALIZATION1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MeanVarianceNormalization1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MeanVarianceNormalization1;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;
        BOOL NormalizeVariance = FALSE;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MEAN_VARIANCE_NORMALIZATION1_OPERATOR_DESC );
    };
    static_assert( sizeof( MeanVarianceNormalization1OperatorDesc ) == sizeof( DML_MEAN_VARIANCE_NORMALIZATION1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Resample1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample1;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE1_OPERATOR_DESC );
    };
    static_assert( sizeof( Resample1OperatorDesc ) == sizeof( DML_RESAMPLE1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_MATRIX_MULTIPLY_INTEGER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MatrixMultiplyIntegerOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MatrixMultiplyInteger;

        const TensorDesc* ATensor = nullptr;
        _Maybenull_ const TensorDesc* AZeroPointTensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        _Maybenull_ const TensorDesc* BZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MATRIX_MULTIPLY_INTEGER_OPERATOR_DESC );
    };
    static_assert( sizeof( MatrixMultiplyIntegerOperatorDesc ) == sizeof( DML_MATRIX_MULTIPLY_INTEGER_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_QUANTIZED_LINEAR_MATRIX_MULTIPLY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct QuantizedLinearMatrixMultiplyOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::QuantizedLinearMatrixMultiply;

        const TensorDesc* ATensor = nullptr;
        const TensorDesc* AScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* AZeroPointTensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* BScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BZeroPointTensor = nullptr;
        const TensorDesc* OutputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_QUANTIZED_LINEAR_MATRIX_MULTIPLY_OPERATOR_DESC );
    };
    static_assert( sizeof( QuantizedLinearMatrixMultiplyOperatorDesc ) == sizeof( DML_QUANTIZED_LINEAR_MATRIX_MULTIPLY_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_CONVOLUTION_INTEGER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ConvolutionIntegerOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ConvolutionInteger;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* InputZeroPointTensor = nullptr;
        const TensorDesc* FilterTensor = nullptr;
        _Maybenull_ const TensorDesc* FilterZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        UInt32 GroupCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CONVOLUTION_INTEGER_OPERATOR_DESC );
    };
    static_assert( sizeof( ConvolutionIntegerOperatorDesc ) == sizeof( DML_CONVOLUTION_INTEGER_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_QUANTIZED_LINEAR_CONVOLUTION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct QuantizedLinearConvolutionOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::QuantizedLinearConvolution;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* InputZeroPointTensor = nullptr;
        const TensorDesc* FilterTensor = nullptr;
        const TensorDesc* FilterScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* FilterZeroPointTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        UInt32 GroupCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_QUANTIZED_LINEAR_CONVOLUTION_OPERATOR_DESC );
    };
    static_assert( sizeof( QuantizedLinearConvolutionOperatorDesc ) == sizeof( DML_QUANTIZED_LINEAR_CONVOLUTION_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x2100

#if DML_TARGET_VERSION >= 0x3000

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_AND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitAndOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitAnd;

        ElementWiseBitAndOperatorDesc( ) noexcept = default;
        ElementWiseBitAndOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_AND_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitAndOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_AND_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_OR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitOrOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitOr;

        ElementWiseBitOrOperatorDesc( ) noexcept = default;
        ElementWiseBitOrOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_OR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitOrOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_OR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_XOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitXorOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitXor;

        ElementWiseBitXorOperatorDesc( ) noexcept = default;
        ElementWiseBitXorOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_XOR_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitXorOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_XOR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_NOT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitNotOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitNot;

        ElementWiseBitNotOperatorDesc( ) noexcept = default;
        ElementWiseBitNotOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_NOT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitNotOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_NOT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_COUNT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitCountOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitCount;

        ElementWiseBitCountOperatorDesc( ) noexcept = default;
        ElementWiseBitCountOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_COUNT_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseBitCountOperatorDesc ) == sizeof( DML_ELEMENT_WISE_BIT_COUNT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OR_EQUAL_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalGreaterThanOrEqualOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalGreaterThanOrEqual;

        ElementWiseLogicalGreaterThanOrEqualOperatorDesc( ) noexcept = default;
        ElementWiseLogicalGreaterThanOrEqualOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OR_EQUAL_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalGreaterThanOrEqualOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OR_EQUAL_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OR_EQUAL_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalLessThanOrEqualOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalLessThanOrEqual;

        ElementWiseLogicalLessThanOrEqualOperatorDesc( ) noexcept = default;
        ElementWiseLogicalLessThanOrEqualOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OR_EQUAL_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseLogicalLessThanOrEqualOperatorDesc ) == sizeof( DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OR_EQUAL_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_CELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationCeLUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationCeLU;
        FLOAT Alpha = 0.f;

        ActivationCeLUOperatorDesc( ) noexcept = default;
        ActivationCeLUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, float alpha = 1.0f ) noexcept
            : Base( inputTensor, outputTensor ), Alpha( alpha )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_CELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationCeLUOperatorDesc ) == sizeof( DML_ACTIVATION_CELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_RELU_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationReLUGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationReLUGrad;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_RELU_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationReLUGradOperatorDesc ) == sizeof( DML_ACTIVATION_RELU_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_AVERAGE_POOLING_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AveragePoolingGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AveragePoolingGrad;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        BOOL IncludePadding = FALSE;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_AVERAGE_POOLING_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( AveragePoolingGradOperatorDesc ) == sizeof( DML_AVERAGE_POOLING_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_POOLING_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPoolingGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPoolingGrad;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( MaxPoolingGradOperatorDesc ) == sizeof( DML_MAX_POOLING_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_RANDOM_GENERATOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct RandomGeneratorOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::RandomGenerator;
        const TensorDesc* InputStateTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputStateTensor = nullptr;
        RandomGeneratorType Type = RandomGeneratorType::Philox4x32_10;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_RANDOM_GENERATOR_OPERATOR_DESC );
    };
    static_assert( sizeof( RandomGeneratorOperatorDesc ) == sizeof( DML_RANDOM_GENERATOR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_NONZERO_COORDINATES_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct NonZeroCoordinatesOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::NonZeroCoordinates;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputCountTensor = nullptr;
        const TensorDesc* OutputCoordinatesTensor = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_NONZERO_COORDINATES_OPERATOR_DESC );
    };
    static_assert( sizeof( NonZeroCoordinatesOperatorDesc ) == sizeof( DML_NONZERO_COORDINATES_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ResampleGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ResampleGrad;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( ResampleGradOperatorDesc ) == sizeof( DML_RESAMPLE_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_SLICE_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SliceGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::SliceGrad;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* InputWindowOffsets = nullptr;
        _Field_size_( DimensionCount ) const UInt32* InputWindowSizes = nullptr;
        _Field_size_( DimensionCount ) const INT* InputWindowStrides = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SLICE_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( SliceGradOperatorDesc ) == sizeof( DML_SLICE_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ADAM_OPTIMIZER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AdamOptimizerOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AdamOptimizer;

        const TensorDesc* InputParametersTensor = nullptr;
        const TensorDesc* InputFirstMomentTensor = nullptr;
        const TensorDesc* InputSecondMomentTensor = nullptr;
        const TensorDesc* GradientTensor = nullptr;
        const TensorDesc* TrainingStepTensor = nullptr;
        const TensorDesc* OutputParametersTensor = nullptr;
        const TensorDesc* OutputFirstMomentTensor = nullptr;
        const TensorDesc* OutputSecondMomentTensor = nullptr;
        FLOAT LearningRate = 0.f;
        FLOAT Beta1 = 0.f;
        FLOAT Beta2 = 0.f;
        FLOAT Epsilon = 0.f;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ADAM_OPTIMIZER_OPERATOR_DESC );
    };
    static_assert( sizeof( AdamOptimizerOperatorDesc ) == sizeof( DML_ADAM_OPTIMIZER_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ARGMIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ArgMinOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ArgMin;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;
        DML::AxisDirection AxisDirection = DML::AxisDirection::Increasing;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ARGMIN_OPERATOR_DESC );
    };
    static_assert( sizeof( ArgMinOperatorDesc ) == sizeof( DML_ARGMIN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ARGMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ArgMaxOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ArgMax;

        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;
        DML::AxisDirection AxisDirection = DML::AxisDirection::Increasing;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ARGMAX_OPERATOR_DESC );
    };
    static_assert( sizeof( ArgMaxOperatorDesc ) == sizeof( DML_ARGMAX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_ALIGN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIAlignOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ROIAlign;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ROITensor = nullptr;
        const TensorDesc* BatchIndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        ReduceFunction ReductionFunction = ReduceFunction::ArgMax;
        InterpolationMode InterpolationMode = InterpolationMode::NearestNeighbor;
        FLOAT SpatialScaleX = 0.f;
        FLOAT SpatialScaleY = 0.f;
        FLOAT OutOfBoundsInputValue = 0.f;
        UInt32 MinimumSamplesPerOutput = 0;
        UInt32 MaximumSamplesPerOutput = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_ALIGN_OPERATOR_DESC );
    };
    static_assert( sizeof( ROIAlignOperatorDesc ) == sizeof( DML_ROI_ALIGN_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_ND1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherND1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GatherND1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 InputDimensionCount = 0;
        UInt32 IndicesDimensionCount = 0;
        UInt32 BatchDimensionCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_ND1_OPERATOR_DESC );
    };
    static_assert( sizeof( GatherND1OperatorDesc ) == sizeof( DML_GATHER_ND1_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x3000

#if DML_TARGET_VERSION >= 0x3100

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ATAN_YX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseATanYXOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseATanYX;

        ElementWiseATanYXOperatorDesc( ) noexcept = default;
        ElementWiseATanYXOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ATAN_YX_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseATanYXOperatorDesc ) == sizeof( DML_ELEMENT_WISE_ATAN_YX_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClipGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClipGrad;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        FLOAT Min = 0.f;
        FLOAT Max = 0.f;

        ElementWiseClipGradOperatorDesc( ) noexcept = default;
        ElementWiseClipGradOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputGradientTensor, const TensorDesc* inputGradientTensor, FLOAT min = 0.f, FLOAT max = 0.f ) noexcept
            : InputTensor( inputTensor ), InputGradientTensor( inputGradientTensor ), OutputGradientTensor( outputGradientTensor ), Min( min ), Max( max )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseClipGradOperatorDesc ) == sizeof( DML_ELEMENT_WISE_CLIP_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_DIFFERENCE_SQUARE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseDifferenceSquareOperatorDesc : public BinaryOperatorDesc
    {
        using Base = BinaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseDifferenceSquare;

        ElementWiseDifferenceSquareOperatorDesc( ) noexcept = default;
        ElementWiseDifferenceSquareOperatorDesc( const TensorDesc* inputTensorA, const TensorDesc* inputTensorB, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensorA, inputTensorB, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_DIFFERENCE_SQUARE_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseDifferenceSquareOperatorDesc ) == sizeof( DML_ELEMENT_WISE_DIFFERENCE_SQUARE_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_LOCAL_RESPONSE_NORMALIZATION_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LocalResponseNormalizationGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LocalResponseNormalizationGrad;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        BOOL CrossChannel = FALSE;
        UInt32 LocalSize = 0;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;
        FLOAT Bias = 0.f;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_LOCAL_RESPONSE_NORMALIZATION_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( LocalResponseNormalizationGradOperatorDesc ) == sizeof( DML_LOCAL_RESPONSE_NORMALIZATION_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_CUMULATIVE_PRODUCT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct CumulativeProductOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::CumulativeProduct;
        UInt32 Axis = 0;
        DML::AxisDirection AxisDirection = DML::AxisDirection::Increasing;
        BOOL HasExclusiveProduct = FALSE;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_CUMULATIVE_PRODUCT_OPERATOR_DESC );
    };
    static_assert( sizeof( CumulativeProductOperatorDesc ) == sizeof( DML_CUMULATIVE_PRODUCT_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::BatchNormalizationGrad;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* MeanTensor = nullptr;
        const TensorDesc* VarianceTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;

        const TensorDesc* OutputGradientTensor = nullptr;
        const TensorDesc* OutputScaleGradientTensor = nullptr;
        const TensorDesc* OutputBiasGradientTensor = nullptr;

        FLOAT Epsilon = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BATCH_NORMALIZATION_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( BatchNormalizationGradOperatorDesc ) == sizeof( DML_BATCH_NORMALIZATION_GRAD_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x3100

#if DML_TARGET_VERSION >= 0x4000

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_QUANTIZED_LINEAR_ADD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseQuantizedLinearAddOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseQuantizedLinearAdd;

        const TensorDesc* ATensor = nullptr;
        const TensorDesc* AScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* AZeroPointTensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* BScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BZeroPointTensor = nullptr;
        const TensorDesc* OutputScaleTensor = nullptr;                   // This is an input tensor
        _Maybenull_ const TensorDesc* OutputZeroPointTensor = nullptr;   // This is an input tensor
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_QUANTIZED_LINEAR_ADD_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseQuantizedLinearAddOperatorDesc ) == sizeof( DML_ELEMENT_WISE_QUANTIZED_LINEAR_ADD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_DYNAMIC_QUANTIZE_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DynamicQuantizeLinearOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DynamicQuantizeLinear;
        const TensorDesc* OutputScaleTensor = nullptr;                   // This is an output tensor
        const TensorDesc* OutputZeroPointTensor = nullptr;               // This is an output tensor

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DYNAMIC_QUANTIZE_LINEAR_OPERATOR_DESC );
    };
    static_assert( sizeof( DynamicQuantizeLinearOperatorDesc ) == sizeof( DML_DYNAMIC_QUANTIZE_LINEAR_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_ALIGN1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIAlign1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ROIAlign1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ROITensor = nullptr;
        const TensorDesc* BatchIndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        DML::ReduceFunction ReductionFunction = DML::ReduceFunction::ArgMax;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        FLOAT SpatialScaleX = 0.f;
        FLOAT SpatialScaleY = 0.f;
        FLOAT InputPixelOffset = 0.f;
        FLOAT OutputPixelOffset = 0.f;
        FLOAT OutOfBoundsInputValue = 0.f;
        UInt32 MinimumSamplesPerOutput = 0;
        UInt32 MaximumSamplesPerOutput = 0;
        BOOL AlignRegionsToCorners = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_ALIGN1_OPERATOR_DESC );
    };
    static_assert( sizeof( ROIAlign1OperatorDesc ) == sizeof( DML_ROI_ALIGN1_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x4000

#if DML_TARGET_VERSION >= 0x4100

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_ALIGN_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIAlignGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ROIAlignGrad;

        _Maybenull_ const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* ROITensor = nullptr;
        const TensorDesc* BatchIndicesTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputGradientTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputROIGradientTensor = nullptr;
        ReduceFunction ReductionFunction = ReduceFunction::ArgMax;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        FLOAT SpatialScaleX = 0.f;
        FLOAT SpatialScaleY = 0.f;
        FLOAT InputPixelOffset = 0.f;
        FLOAT OutputPixelOffset = 0.f;
        UInt32 MinimumSamplesPerOutput = 0;
        UInt32 MaximumSamplesPerOutput = 0;
        BOOL AlignRegionsToCorners = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_ALIGN_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( ROIAlignGradOperatorDesc ) == sizeof( DML_ROI_ALIGN_GRAD_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_TRAINING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationTrainingOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::BatchNormalizationTraining;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* FusedAddTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        const TensorDesc* OutputMeanTensor = nullptr;
        const TensorDesc* OutputVarianceTensor = nullptr;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BATCH_NORMALIZATION_TRAINING_OPERATOR_DESC );
    };
    static_assert( sizeof( BatchNormalizationTrainingOperatorDesc ) == sizeof( DML_BATCH_NORMALIZATION_TRAINING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_TRAINING_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationTrainingGradOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::BatchNormalizationTrainingGrad;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* MeanTensor = nullptr;
        const TensorDesc* VarianceTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        const TensorDesc* OutputScaleGradientTensor = nullptr;
        const TensorDesc* OutputBiasGradientTensor = nullptr;
        FLOAT Epsilon = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BATCH_NORMALIZATION_TRAINING_GRAD_OPERATOR_DESC );
    };
    static_assert( sizeof( BatchNormalizationTrainingGradOperatorDesc ) == sizeof( DML_BATCH_NORMALIZATION_TRAINING_GRAD_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x4100

#if DML_TARGET_VERSION >= 0x5000

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClip1OperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        using Base = UnaryOperatorWithScaleBiasDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClip1;

        TensorDataType MinMaxDataType = TensorDataType::Unknown;
        ScalarUnion Min{};
        ScalarUnion Max{};

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP1_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseClip1OperatorDesc ) == sizeof( DML_ELEMENT_WISE_CLIP1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP_GRAD1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClipGrad1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClipGrad1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        TensorDataType MinMaxDataType = TensorDataType::Unknown;
        ScalarUnion Min{};
        ScalarUnion Max{};

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP_GRAD1_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseClipGrad1OperatorDesc ) == sizeof( DML_ELEMENT_WISE_CLIP_GRAD1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_PADDING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Padding1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Padding1;

        DML::PaddingMode PaddingMode = DML::PaddingMode::Constant;
        TensorDataType PaddingValueDataType = TensorDataType::Unknown;
        ScalarUnion PaddingValue{};
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_PADDING1_OPERATOR_DESC );
    };
    static_assert( sizeof( Padding1OperatorDesc ) == sizeof( DML_PADDING1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_NEGATE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseNegateOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseNegate;

        ElementWiseNegateOperatorDesc( ) noexcept = default;
        ElementWiseNegateOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_NEGATE_OPERATOR_DESC );
    };
    static_assert( sizeof( ElementWiseNegateOperatorDesc ) == sizeof( DML_ELEMENT_WISE_NEGATE_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x5000

#if DML_TARGET_VERSION >= 0x5100

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_GELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationGeLUOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationGeLU;

        ActivationGeLUOperatorDesc( ) noexcept = default;
        ActivationGeLUOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor ) noexcept
            : Base( inputTensor, outputTensor )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_GELU_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationGeLUOperatorDesc ) == sizeof( DML_ACTIVATION_GELU_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTMAX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftMax1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftMax1;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;

        ActivationSoftMax1OperatorDesc( ) noexcept = default;
        ActivationSoftMax1OperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 axisCount, const UInt32* axes ) noexcept
            : Base( inputTensor, outputTensor ), AxisCount( axisCount ), Axes( axes )
        {
        }
        template<SimpleSpanLike T>
            requires std::is_same_v<UInt32, typename T::value_type>
        ActivationSoftMax1OperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const T& axes ) noexcept
            : Base( inputTensor, outputTensor ), AxisCount( static_cast< UInt32 >( axes.size( ) ) ), Axes( axes.data( ) )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTMAX1_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationSoftMax1OperatorDesc ) == sizeof( DML_ACTIVATION_SOFTMAX1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_LOG_SOFTMAX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLogSoftMax1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLogSoftMax1;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LOG_SOFTMAX1_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationLogSoftMax1OperatorDesc ) == sizeof( DML_ACTIVATION_LOG_SOFTMAX1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_HARDMAX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardMax1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardMax1;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARDMAX1_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationHardMax1OperatorDesc ) == sizeof( DML_ACTIVATION_HARDMAX1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE2_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Resample2OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample2;

        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        AxisDirection RoundingDirection = AxisDirection::Increasing;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE2_OPERATOR_DESC );
    };
    static_assert( sizeof( Resample2OperatorDesc ) == sizeof( DML_RESAMPLE2_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE_GRAD1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ResampleGrad1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ResampleGrad1;

        const TensorDesc* InputGradientTensor;
        const TensorDesc* OutputGradientTensor;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        AxisDirection RoundingDirection = AxisDirection::Increasing;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE_GRAD1_OPERATOR_DESC );
    };
    static_assert( sizeof( ResampleGrad1OperatorDesc ) == sizeof( DML_RESAMPLE_GRAD1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_DIAGONAL_MATRIX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DiagonalMatrix1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DiagonalMatrix1;

        _Maybenull_ const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        TensorDataType ValueDataType = TensorDataType::Unknown;
        ScalarUnion Value{};
        INT DiagonalFillBegin = 0;
        INT DiagonalFillEnd = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DIAGONAL_MATRIX1_OPERATOR_DESC );
    };
    static_assert( sizeof( DiagonalMatrix1OperatorDesc ) == sizeof( DML_DIAGONAL_MATRIX1_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x5100

#if DML_TARGET_VERSION >= 0x6100

    /// <summary>
    /// <para>
    /// Alias for DML_MULTIHEAD_ATTENTION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MultiheadAttentionOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MultiheadAttention;

        _Maybenull_ const TensorDesc* QueryTensor = nullptr;
        _Maybenull_ const TensorDesc* KeyTensor = nullptr;
        _Maybenull_ const TensorDesc* ValueTensor = nullptr;
        _Maybenull_ const TensorDesc* StackedQueryKeyTensor = nullptr;
        _Maybenull_ const TensorDesc* StackedKeyValueTensor = nullptr;
        _Maybenull_ const TensorDesc* StackedQueryKeyValueTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* MaskTensor = nullptr;
        _Maybenull_ const TensorDesc* RelativePositionBiasTensor = nullptr;
        _Maybenull_ const TensorDesc* PastKeyTensor = nullptr;
        _Maybenull_ const TensorDesc* PastValueTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputPresentKeyTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputPresentValueTensor = nullptr;
        FLOAT Scale = 0.f;
        FLOAT MaskFilterValue = 0.f;
        UInt32 HeadCount = 0;
        MultiheadAttentionMaskType MaskType = MultiheadAttentionMaskType::None;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MULTIHEAD_ATTENTION_OPERATOR_DESC );
    };
    static_assert( sizeof( MultiheadAttentionOperatorDesc ) == sizeof( DML_MULTIHEAD_ATTENTION_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x6100

#if DML_TARGET_VERSION >= 0x6200

    /// <summary>
    /// <para>
    /// Alias for DML_LP_POOLING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LPPooling1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LPPooling1;

        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        UInt32 P = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LP_POOLING1_OPERATOR_DESC );
    };
    static_assert( sizeof( LPPooling1OperatorDesc ) == sizeof( DML_LP_POOLING1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_AVERAGE_POOLING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AveragePooling1OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AveragePooling1;

        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        BOOL IncludePadding = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_AVERAGE_POOLING1_OPERATOR_DESC );
    };
    static_assert( sizeof( AveragePooling1OperatorDesc ) == sizeof( DML_AVERAGE_POOLING1_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SWISH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSwishOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSwish;

        FLOAT SigmoidInputScale = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SWISH_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationSwishOperatorDesc ) == sizeof( DML_ACTIVATION_SWISH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_HARD_SWISH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardSwishOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardSwish;

        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARD_SWISH_OPERATOR_DESC );
    };
    static_assert( sizeof( ActivationHardSwishOperatorDesc ) == sizeof( DML_ACTIVATION_HARD_SWISH_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_QUANTIZED_LINEAR_AVERAGE_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct QuantizedLinearAveragePoolingOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::QuantizedLinearAveragePooling;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* InputZeroPointTensor = nullptr;
        const TensorDesc* OutputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr;
        _Field_size_( DimensionCount ) const UInt32* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr;
        BOOL IncludePadding = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_QUANTIZED_LINEAR_AVERAGE_POOLING_OPERATOR_DESC );
    };
    static_assert( sizeof( QuantizedLinearAveragePoolingOperatorDesc ) == sizeof( DML_QUANTIZED_LINEAR_AVERAGE_POOLING_OPERATOR_DESC ) );

    /// <summary>
    /// <para>
    /// Alias for DML_MATRIX_MULTIPLY_INTEGER_TO_FLOAT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MatrixMultiplyIntegerToFloatOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MatrixMultiplyIntegerToFloat;

        const TensorDesc* ATensor = nullptr;
        const TensorDesc* AScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* AZeroPointTensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* BScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BZeroPointTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MATRIX_MULTIPLY_INTEGER_TO_FLOAT_OPERATOR_DESC );
    };
    static_assert( sizeof( MatrixMultiplyIntegerToFloatOperatorDesc ) == sizeof( DML_MATRIX_MULTIPLY_INTEGER_TO_FLOAT_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x6200

#if DML_TARGET_VERSION >= 0x6300

    struct MeanVarianceNormalization2OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MeanVarianceNormalization2;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UInt32 AxisCount = 0;
        _Field_size_( AxisCount ) const UInt32* Axes = nullptr;
        BOOL UseMean = FALSE;
        BOOL UseVariance = FALSE;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        MeanVarianceNormalization2OperatorDesc( ) noexcept = default;

        MeanVarianceNormalization2OperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, const TensorDesc* scaleTensor, const TensorDesc* biasTensor, UInt32 axisCount, const UInt32* axes, BOOL useMean, BOOL useVariance, FLOAT epsilon, const OperatorDesc* fusedActivation) noexcept
            : InputTensor( inputTensor ), OutputTensor( outputTensor ), ScaleTensor( scaleTensor ), BiasTensor( biasTensor ), AxisCount( axisCount ), Axes( axes ), UseMean( useMean ), UseVariance( useVariance ), Epsilon( epsilon ), FusedActivation( fusedActivation )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MEAN_VARIANCE_NORMALIZATION2_OPERATOR_DESC );
    };

    static_assert( sizeof( MeanVarianceNormalization2OperatorDesc ) == sizeof( DML_MEAN_VARIANCE_NORMALIZATION2_OPERATOR_DESC ) );

    struct MultiheadAttention1OperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MultiheadAttention1;

        _Maybenull_ const TensorDesc* QueryTensor = nullptr;
        _Maybenull_ const TensorDesc* KeyTensor = nullptr;
        _Maybenull_ const TensorDesc* ValueTensor = nullptr;
        _Maybenull_ const TensorDesc* StackedQueryKeyTensor = nullptr;
        _Maybenull_ const TensorDesc* StackedKeyValueTensor = nullptr;
        _Maybenull_ const TensorDesc* StackedQueryKeyValueTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* MaskTensor = nullptr;
        _Maybenull_ const TensorDesc* RelativePositionBiasTensor = nullptr;
        _Maybenull_ const TensorDesc* PastKeyTensor = nullptr;
        _Maybenull_ const TensorDesc* PastValueTensor = nullptr;
        _Maybenull_ const TensorDesc* PastSequenceLengthsTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputPresentKeyTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputPresentValueTensor = nullptr;
        FLOAT Scale = 0.f;
        FLOAT MaskFilterValue = 0.f;
        UInt32 QueryHeadCount = 0;
        UInt32 KeyValueHeadCount = 0;
        
        MultiheadAttentionMaskType MaskType = MultiheadAttentionMaskType::None;

        MultiheadAttention1OperatorDesc( ) noexcept = default;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MULTIHEAD_ATTENTION1_OPERATOR_DESC );
    };

    static_assert( sizeof( MultiheadAttention1OperatorDesc ) == sizeof( DML_MULTIHEAD_ATTENTION1_OPERATOR_DESC ) );

    struct QuantizeOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Quantize;

        const TensorDesc* InputTensor = nullptr;
        DML::QuantizationType QuantizationType = DML::QuantizationType::None;
        UInt32 QuantizationTensorCount = 0;
        _Field_size_( QuantizationTensorCount ) const TensorDesc* QuantizationTensors = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        QuantizeOperatorDesc( ) noexcept = default;

        QuantizeOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, DML::QuantizationType quantizationType, UInt32 quantizationTensorCount, const TensorDesc* quantizationTensors ) noexcept
            : InputTensor( inputTensor ), OutputTensor( outputTensor ), QuantizationType( quantizationType ), QuantizationTensorCount( quantizationTensorCount ), QuantizationTensors( quantizationTensors )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_QUANTIZE_OPERATOR_DESC );
    };

    static_assert( sizeof( QuantizeOperatorDesc ) == sizeof( DML_QUANTIZE_OPERATOR_DESC ) );

    struct DequantizeOperatorDesc : public BaseOperatorDesc
    {
        using Base = BaseOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Dequantize;

        const TensorDesc* InputTensor = nullptr;
        DML::QuantizationType QuantizationType = DML::QuantizationType::None;
        UInt32 QuantizationTensorCount = 0;
        _Field_size_( QuantizationTensorCount ) const TensorDesc* QuantizationTensors = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DequantizeOperatorDesc( ) noexcept = default;

        DequantizeOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, DML::QuantizationType quantizationType, UInt32 quantizationTensorCount, const TensorDesc* quantizationTensors ) noexcept
            : InputTensor( inputTensor ), OutputTensor( outputTensor ), QuantizationType( quantizationType ), QuantizationTensorCount( quantizationTensorCount ), QuantizationTensors( quantizationTensors )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DEQUANTIZE_OPERATOR_DESC );
    };

    static_assert( sizeof( DequantizeOperatorDesc ) == sizeof( DML_DEQUANTIZE_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x6300

#if DML_TARGET_VERSION >= 0x6400

    struct Resample3OperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample3;

        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        AxisDirection RoundingDirection = AxisDirection::Increasing;
        UInt32 DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;
        BOOL Antialiased = FALSE;

        Resample3OperatorDesc( ) noexcept = default;
        Resample3OperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, DML::InterpolationMode interpolationMode, AxisDirection roundingDirection, UInt32 dimensionCount, const float* scales, const float* inputPixelOffsets, const float* outputPixelOffsets ) noexcept
            : Base( inputTensor, outputTensor ), InterpolationMode( interpolationMode ), RoundingDirection( roundingDirection ), DimensionCount( dimensionCount ), Scales( scales ), InputPixelOffsets( inputPixelOffsets ), OutputPixelOffsets( outputPixelOffsets )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE3_OPERATOR_DESC );
    };

    static_assert( sizeof( Resample3OperatorDesc ) == sizeof( DML_RESAMPLE3_OPERATOR_DESC ) );

    struct FoldOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Fold;

        UInt32 DimensionCount = 0;
        // Size of the extracted patch
        _Field_size_( DimensionCount ) const UInt32* WindowSizes = nullptr; 
        // Step size of the extracted patches
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr; 
        // Dialations of the extracted patch
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr; 
        // Start padding of the "source tensor"
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr; 
        // End padding of the "source tensor"
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr; 

        FoldOperatorDesc( ) noexcept = default;
        FoldOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount, const UInt32* windowSizes, const UInt32* strides, const UInt32* dilations, const UInt32* startPadding, const UInt32* endPadding ) noexcept
            : Base( inputTensor, outputTensor ), DimensionCount( dimensionCount ), WindowSizes( windowSizes ), Strides( strides ), Dilations( dilations ), StartPadding( startPadding ), EndPadding( endPadding )
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FOLD_OPERATOR_DESC );
    };

    static_assert( sizeof( FoldOperatorDesc ) == sizeof( DML_FOLD_OPERATOR_DESC ) );

    struct UnfoldOperatorDesc : public UnaryOperatorDesc
    {
        using Base = UnaryOperatorDesc;
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Unfold;

        UInt32 DimensionCount = 0;
        // Size of the extracted patch
        _Field_size_( DimensionCount ) const UInt32* WindowSizes = nullptr; 
        // Step size of the extracted patches
        _Field_size_( DimensionCount ) const UInt32* Strides = nullptr; 
        // Dialations of the extracted patch
        _Field_size_( DimensionCount ) const UInt32* Dilations = nullptr; 
        // Start padding of the "source tensor"
        _Field_size_( DimensionCount ) const UInt32* StartPadding = nullptr; 
        // End padding of the "source tensor"
        _Field_size_( DimensionCount ) const UInt32* EndPadding = nullptr; 

        UnfoldOperatorDesc( ) noexcept = default;
        UnfoldOperatorDesc( const TensorDesc* inputTensor, const TensorDesc* outputTensor, UInt32 dimensionCount, const UInt32* windowSizes, const UInt32* strides, const UInt32* dilations, const UInt32* startPadding, const UInt32* endPadding ) noexcept
            : Base( inputTensor, outputTensor), DimensionCount( dimensionCount ), WindowSizes( windowSizes ), Strides( strides ), Dilations( dilations ), StartPadding( startPadding ), EndPadding( endPadding ) 
        { }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_UNFOLD_OPERATOR_DESC );
    };

    static_assert( sizeof( UnfoldOperatorDesc ) == sizeof( DML_UNFOLD_OPERATOR_DESC ) );

#endif // DML_TARGET_VERSION >= 0x6400



    // ===================================================================================================================
    //   DML feature support queries
    // ===================================================================================================================

#if DML_TARGET_VERSION >= 0x2000

    /// <summary>
    /// <para>
    /// Alias for DML_FEATURE_LEVEL
    /// </para>
    /// </summary>
    enum class FeatureLevel
    {
        _1_0 = 0x1000,
        _2_0 = 0x2000,
        _2_1 = 0x2100,
        _3_0 = 0x3000,
        _3_1 = 0x3100,
        _4_0 = 0x4000,
        _4_1 = 0x4100,
        _5_0 = 0x5000,
        _5_1 = 0x5100,
        _5_2 = 0x5200,
        _6_0 = 0x6000,
        _6_1 = 0x6100,
        _6_2 = 0x6200,
    };

#endif // DML_TARGET_VERSION >= 0x2000

    /// <summary>
    /// <para>
    /// Alias for DML_FEATURE
    /// </para>
    /// </summary>
    enum class Feature
    {
        TensorDataTypeSupport,

#if DML_TARGET_VERSION >= 0x2000
        FeatureLevels,
#endif // DML_TARGET_VERSION >= 0x2000
    };

    /// <summary>
    /// <para>
    /// Alias for DML_FEATURE_QUERY_TENSOR_DATA_TYPE_SUPPORT
    /// </para>
    /// </summary>
    struct FeatureQueryTensorDataTypeSupport
    {
        TensorDataType DataType = TensorDataType::Unknown;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FEATURE_QUERY_TENSOR_DATA_TYPE_SUPPORT );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_FEATURE_DATA_TENSOR_DATA_TYPE_SUPPORT
    /// </para>
    /// </summary>
    struct FeatureDataTensorDataTypeSupport
    {
        BOOL IsSupported = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FEATURE_DATA_TENSOR_DATA_TYPE_SUPPORT );
    };

#if DML_TARGET_VERSION >= 0x2000

    /// <summary>
    /// <para>
    /// Alias for DML_FEATURE_QUERY_FEATURE_LEVELS
    /// </para>
    /// </summary>
    struct FeatureQueryFeatureLevels
    {
        UInt32 RequestedFeatureLevelCount = 0;
        _Field_size_( RequestedFeatureLevelCount ) const FeatureLevel* RequestedFeatureLevels = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FEATURE_QUERY_FEATURE_LEVELS );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_FEATURE_DATA_FEATURE_LEVELS
    /// </para>
    /// </summary>
    struct FeatureDataFeatureLevels
    {
        FeatureLevel MaxSupportedFeatureLevel = FeatureLevel::_1_0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_FEATURE_DATA_FEATURE_LEVELS );
    };

#endif // DML_TARGET_VERSION >= 0x2000

    // ===================================================================================================================
    //   DML device functions, enumerations, and structures
    // ===================================================================================================================

    /// <summary>
    /// <para>
    /// Alias for DML_BINDING_TABLE_DESC
    /// </para>
    /// </summary>
    struct BindingTableDesc
    {
        IDMLDispatchable* Dispatchable = nullptr;
        Graphics::D3D12::CPUDescriptorHandle CPUDescriptorHandle;
        Graphics::D3D12::GPUDescriptorHandle GPUDescriptorHandle;
        UInt32 SizeInDescriptors = 0;

        BindingTableDesc( ) noexcept = default;

        BindingTableDesc( IDMLDispatchable* dispatchable, const Graphics::D3D12::CPUDescriptorHandle& cpuDescriptorHandle, const Graphics::D3D12::GPUDescriptorHandle& gpuDescriptorHandle, UInt32 sizeInDescriptors ) noexcept
            : Dispatchable( dispatchable ), CPUDescriptorHandle( cpuDescriptorHandle ), GPUDescriptorHandle( gpuDescriptorHandle ), SizeInDescriptors( sizeInDescriptors )
        {
        }

        BindingTableDesc( const DML::Dispatchable& dispatchable, const Graphics::D3D12::CPUDescriptorHandle& cpuDescriptorHandle, const Graphics::D3D12::GPUDescriptorHandle& gpuDescriptorHandle, UInt32 sizeInDescriptors ) noexcept;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BINDING_TABLE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_EXECUTION_FLAGS
    /// </para>
    /// </summary>
    enum class ExecutionFlags : UInt32
    {
        None = 0,
        AllowHalfPrecisionComputation = 0x1,
        DisableMetaCommands = 0x2,
        DescriptorsVolatile = 0x4,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ExecutionFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for DML_CREATE_DEVICE_FLAGS
    /// </para>
    /// </summary>
    enum class CreateDeviceFlags : UInt32
    {
        None = 0,
        Debug = 0x1,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( CreateDeviceFlags, UInt32 );


    class Object : public Unknown
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Object, Unknown, IDMLObject, IUnknown )

    public:
        void GetPrivateData( REFGUID guid, _Inout_ UInt32* dataSize, _Out_writes_bytes_opt_( *dataSize ) void* data ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetPrivateData( guid, dataSize, data );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPrivateData( REFGUID guid, UInt32 dataSize, _In_reads_bytes_opt_( dataSize ) const void* data ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetPrivateData( guid, dataSize, data );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPrivateDataInterface( REFGUID guid, _In_opt_ IUnknown* data ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetPrivateDataInterface( guid, data );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetName( PCWSTR name ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetName( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class Device : public Object
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Device, Object, IDMLDevice, IDMLObject )

    public:
        void CheckFeatureSupport( DML_FEATURE feature, UInt32 featureQueryDataSize, _In_reads_bytes_opt_( featureQueryDataSize ) const void* featureQueryData, UInt32 featureSupportDataSize, _Out_writes_bytes_( featureSupportDataSize ) void* featureSupportData ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CheckFeatureSupport( feature, featureQueryDataSize, featureQueryData, featureSupportDataSize, featureSupportData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateOperator( const DML_OPERATOR_DESC* desc, REFIID riid, _COM_Outptr_opt_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateOperator( desc, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Operator CreateOperator( const OperatorDesc* desc ) const;

        template<typename T>
            requires std::is_base_of_v<BaseOperatorDesc, T>
        inline Operator CreateOperator( const T& desc ) const;

        void CompileOperator( IDMLOperator* op, DML_EXECUTION_FLAGS flags, REFIID riid, _COM_Outptr_opt_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CompileOperator( op, flags, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        CompiledOperator CompileOperator( const Operator& op, DML::ExecutionFlags flags = DML::ExecutionFlags::None ) const;


        void CreateOperatorInitializer( UInt32 operatorCount, _In_reads_opt_( operatorCount ) IDMLCompiledOperator* const* operators, REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateOperatorInitializer( operatorCount, operators, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = OperatorInitializer>
            requires std::is_base_of_v<OperatorInitializer, T>
        T CreateOperatorInitializer( const CompiledOperator& compiledOperator ) const;

        template<typename T = OperatorInitializer, SimpleSpanLike S>
            requires std::is_base_of_v<OperatorInitializer, T>&& std::is_base_of_v<CompiledOperator, typename S::value_type>
        T CreateOperatorInitializer( const S& compiledOperators ) const;

        void CreateCommandRecorder( REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCommandRecorder( riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = CommandRecorder>
            requires std::is_base_of_v<CommandRecorder, T>
        T CreateCommandRecorder( ) const;

        void CreateBindingTable( _In_opt_ const DML_BINDING_TABLE_DESC* desc, REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateBindingTable( desc, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = BindingTable>
            requires std::is_base_of_v<BindingTable, T>
        T CreateBindingTable( _In_opt_ const DML::BindingTableDesc* desc ) const;

        void Evict( UInt32 count, _In_reads_( count ) IDMLPageable* const* ppObjects ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Evict( count, ppObjects );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void MakeResident( UInt32 count, _In_reads_( count ) IDMLPageable* const* ppObjects ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->MakeResident( count, ppObjects );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HRESULT GetDeviceRemovedReason( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDeviceRemovedReason( );
            return hr;
        }

        void GetParentDevice( REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetParentDevice( riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class DeviceChild : public Object
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( DeviceChild, Object, IDMLDeviceChild, IDMLObject )

    public:
        void GetDevice( REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDevice( riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class Pageable : public DeviceChild
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Pageable, DeviceChild, IDMLPageable, IDMLDeviceChild )

    public:

    };

    class Operator : public DeviceChild
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Operator, DeviceChild, IDMLOperator, IDMLDeviceChild )

    public:

    };

    inline Operator Device::CreateOperator( const OperatorDesc* desc ) const
    {
        IDMLOperator* itf = nullptr;
        CreateOperator( reinterpret_cast< const DML_OPERATOR_DESC* >( desc ), __uuidof( IDMLOperator ), reinterpret_cast< void** >( &itf ) );
        return Operator( itf );
    }
    template<typename T>
        requires std::is_base_of_v<BaseOperatorDesc, T>
    inline Operator Device::CreateOperator( const T& desc ) const
    {
        OperatorDesc operatorDesc( &desc );
        return CreateOperator( &operatorDesc );
    }



    /// <summary>
    /// <para>
    /// Alias for DML_EXECUTION_FLAGS
    /// </para>
    /// </summary>
    struct BindingProperties
    {
        UInt32 RequiredDescriptorCount = 0;
        UINT64 TemporaryResourceSize = 0;
        UINT64 PersistentResourceSize = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BINDING_PROPERTIES );
    };


    class Dispatchable : public Pageable
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Dispatchable, Pageable, IDMLDispatchable, IDMLPageable )

    public:
        DML_BINDING_PROPERTIES GetBindingProperties_( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBindingProperties( );
        }
        DML::BindingProperties GetBindingProperties( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return std::bit_cast< DML::BindingProperties >( pInterface->GetBindingProperties( ) );
        }
    };

    inline BindingTableDesc::BindingTableDesc( const DML::Dispatchable& dispatchable, const Graphics::D3D12::CPUDescriptorHandle& cpuDescriptorHandle, const Graphics::D3D12::GPUDescriptorHandle& gpuDescriptorHandle, UInt32 sizeInDescriptors ) noexcept
        : Dispatchable( dispatchable.GetInterfacePointer<IDMLDispatchable>( ) ), CPUDescriptorHandle( cpuDescriptorHandle ), GPUDescriptorHandle( gpuDescriptorHandle ), SizeInDescriptors( sizeInDescriptors )
    {
    }

    class CompiledOperator : public Dispatchable
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( CompiledOperator, Dispatchable, IDMLCompiledOperator, IDMLDispatchable )

    public:

    };

    inline CompiledOperator Device::CompileOperator( const Operator& op, DML::ExecutionFlags flags ) const
    {
        IDMLCompiledOperator* itf = nullptr;
        CompileOperator( op.GetInterfacePointer<IDMLOperator>( ), static_cast< DML_EXECUTION_FLAGS >( flags ), __uuidof( IDMLCompiledOperator ), reinterpret_cast< void** >( &itf ) );
        return CompiledOperator( itf );
    }

    class OperatorInitializer : public Dispatchable
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( OperatorInitializer, Dispatchable, IDMLOperatorInitializer, IDMLDispatchable )

    public:
        void Reset( UInt32 operatorCount, _In_reads_opt_( operatorCount ) IDMLCompiledOperator* const* operators ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( operatorCount, operators );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    template<typename T>
        requires std::is_base_of_v<OperatorInitializer, T>
    inline T Device::CreateOperatorInitializer( const CompiledOperator& compiledOperator ) const
    {
        using ItfType = typename T::InterfaceType;
        IDMLCompiledOperator* compiledOperators[ ] = { compiledOperator.GetInterfacePointer<IDMLCompiledOperator>( ) };
        ItfType* itf = nullptr;
        CreateOperatorInitializer( 1, compiledOperators, __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        return T( itf );
    }

    template<typename T, SimpleSpanLike S>
        requires std::is_base_of_v<OperatorInitializer, T>&& std::is_base_of_v<CompiledOperator, typename S::value_type>
    inline T Device::CreateOperatorInitializer( const S& compiledOperators ) const
    {
        using ItfType = typename T::InterfaceType;
        ItfType* itf = nullptr;
        CreateOperatorInitializer( static_cast< UInt32 >( compiledOperators.size( ) ), reinterpret_cast< IDMLCompiledOperator* const* >( compiledOperators.data( ) ), __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        return T( itf );
    }



    /// <summary>
    /// <para>
    /// Alias for DML_BINDING_TYPE
    /// </para>
    /// </summary>
    enum class BindingType
    {
        None,
        Buffer,
        BufferArray,
    };



    /// <summary>
    /// <para>
    /// Alias for DML_BUFFER_BINDING
    /// </para>
    /// </summary>
    struct BufferBinding
    {
        _Maybenull_ ID3D12Resource* Buffer = nullptr;
        UINT64 Offset = 0;
        UINT64 SizeInBytes = 0;

        BufferBinding( ) = default;
        BufferBinding( ID3D12Resource* buffer, UINT64 sizeInBytes, UINT64 offset = 0 )
            : Buffer( buffer ), Offset( offset ), SizeInBytes( sizeInBytes )
        {
        }
        BufferBinding( const Graphics::D3D12::Resource& buffer, UINT64 sizeInBytes, UINT64 offset = 0 )
            : Buffer( buffer.GetInterfacePointer<ID3D12Resource>( ) ), Offset( offset ), SizeInBytes( sizeInBytes )
        {
        }

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BUFFER_BINDING );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_BUFFER_ARRAY_BINDING
    /// </para>
    /// </summary>
    struct BufferArrayBinding
    {
        UInt32 BindingCount = 0;
        _Field_size_( BindingCount ) const BufferBinding* Bindings = nullptr;

        BufferArrayBinding( ) noexcept = default;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BUFFER_ARRAY_BINDING );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_BINDING_DESC
    /// </para>
    /// </summary>
    struct BindingDesc
    {
        BindingType Type = BindingType::None;
        _Field_size_opt_( _Inexpressible_( "Dependent on binding type" ) ) const void* Desc = nullptr;

        BindingDesc( ) noexcept = default;

        BindingDesc( const BufferBinding* desc ) noexcept
            : Type( BindingType::Buffer ), Desc( reinterpret_cast< const void* >( desc ) )
        {
        }
        BindingDesc( const BufferArrayBinding* desc ) noexcept
            : Type( BindingType::BufferArray ), Desc( reinterpret_cast< const void* >( desc ) )
        {
        }

        BindingDesc& operator = ( const BufferBinding* desc ) noexcept
        {
            Type = BindingType::Buffer;
            Desc = reinterpret_cast< const void* >( desc );
            return *this;
        }

        BindingDesc& operator = ( const BufferArrayBinding* desc ) noexcept
        {
            Type = BindingType::BufferArray;
            Desc = reinterpret_cast< const void* >( desc );
            return *this;
        }


        DML_IMPLEMENT_CONVERSIONS_TO( DML_BINDING_DESC );
    };


    class BindingTable : public DeviceChild
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( BindingTable, DeviceChild, IDMLBindingTable, IDMLDeviceChild )

    public:
        void BindInputs( UInt32 bindingCount, _In_reads_opt_( bindingCount ) const DML_BINDING_DESC* bindings ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindInputs( bindingCount, bindings );
        }

        void BindInputs( const Graphics::D3D12::Resource& buffer, size_t bufferSize, UINT64 offset = 0 ) const
        {
            DML::BufferBinding bufferBinding( buffer, bufferSize, offset );
            DML::BindingDesc bindingDesc( &bufferBinding );
            BindInputs( 1, bindingDesc );
        }

        void BindOutputs( UInt32 bindingCount, _In_reads_opt_( bindingCount ) const DML_BINDING_DESC* bindings ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindOutputs( bindingCount, bindings );
        }

        void BindOutputs( const Graphics::D3D12::Resource& buffer, size_t bufferSize, UINT64 offset = 0 ) const
        {
            DML::BufferBinding bufferBinding( buffer, bufferSize, offset );
            DML::BindingDesc bindingDesc( &bufferBinding );
            BindOutputs( 1, bindingDesc );
        }

        void BindTemporaryResource( _In_opt_ const DML_BINDING_DESC* binding ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindTemporaryResource( binding );
        }

        void BindTemporaryResource( const Graphics::D3D12::Resource& buffer, size_t bufferSize, UINT64 offset = 0 ) const
        {
            DML::BufferBinding bufferBinding( buffer, bufferSize, offset );
            DML::BindingDesc bindingDesc( &bufferBinding );
            BindTemporaryResource( bindingDesc );
        }


        void BindPersistentResource( _In_opt_ const DML_BINDING_DESC* binding ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindPersistentResource( binding );
        }

        void BindPersistentResource( const Graphics::D3D12::Resource& buffer, size_t bufferSize, UINT64 offset = 0 ) const
        {
            DML::BufferBinding bufferBinding( buffer, bufferSize, offset );
            DML::BindingDesc bindingDesc( &bufferBinding );
            BindPersistentResource( bindingDesc );
        }

        void Reset( _In_opt_ const DML_BINDING_TABLE_DESC* desc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( desc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Reset( _In_opt_ const DML::BindingTableDesc* desc ) const
        {
            Reset( reinterpret_cast< const DML_BINDING_TABLE_DESC* >( desc ) );
        }

    };


    template<typename T>
        requires std::is_base_of_v<BindingTable, T>
    T Device::CreateBindingTable( _In_opt_ const DML::BindingTableDesc* desc ) const
    {
        using ItfType = typename T::InterfaceType;
        ItfType* itf = nullptr;
        CreateBindingTable( reinterpret_cast< const DML_BINDING_TABLE_DESC* >( desc ), __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        return T( itf );
    }

    class CommandRecorder : public DeviceChild
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( CommandRecorder, DeviceChild, IDMLCommandRecorder, IDMLDeviceChild )

    public:
        void RecordDispatch( ID3D12CommandList* commandList, IDMLDispatchable* dispatchable, IDMLBindingTable* bindings ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RecordDispatch( commandList, dispatchable, bindings );
        }
        void RecordDispatch( const Graphics::D3D12::CommandList& commandList, const DML::Dispatchable& dispatchable, const DML::BindingTable& bindings ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RecordDispatch( commandList.GetInterfacePointer<ID3D12CommandList>( ), dispatchable.GetInterfacePointer<IDMLDispatchable>( ), bindings.GetInterfacePointer<IDMLBindingTable>( ) );
        }

    };


    template<typename T>
        requires std::is_base_of_v<CommandRecorder, T>
    inline T Device::CreateCommandRecorder( ) const
    {
        using ItfType = T::InterfaceType;
        ItfType* itf = nullptr;
        CreateCommandRecorder( __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        return T( itf );
    }


    class DebugDevice : public Unknown
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( DebugDevice, Unknown, IDMLDebugDevice, IUnknown )

    public:
        void SetMuteDebugOutput( BOOL mute ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetMuteDebugOutput( mute );
        }
    };


    /// <summary>
    /// <para>
    /// Alias for DML_GRAPH_EDGE_TYPE
    /// </para>
    /// </summary>
    enum class GraphEdgeType
    {
        Invalid = DML_GRAPH_EDGE_TYPE_INVALID,
        Input = DML_GRAPH_EDGE_TYPE_INPUT,
        Output = DML_GRAPH_EDGE_TYPE_OUTPUT,
        Intermediate = DML_GRAPH_EDGE_TYPE_INTERMEDIATE,
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GRAPH_EDGE_DESC
    /// </para>
    /// </summary>
    struct GraphEdgeDesc
    {
        GraphEdgeType Type;
        _Field_size_( _Inexpressible_( "Dependent on edge type" ) ) const void* Desc;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GRAPH_EDGE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_INPUT_GRAPH_EDGE_DESC
    /// </para>
    /// </summary>
    struct InputGraphEdgeDesc
    {
        UInt32 GraphInputIndex;
        UInt32 ToNodeIndex;
        UInt32 ToNodeInputIndex;
        _Field_z_ _Maybenull_ const char* Name;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_INPUT_GRAPH_EDGE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_OUTPUT_GRAPH_EDGE_DESC
    /// </para>
    /// </summary>
    struct OutputGraphEdgeDesc
    {
        UInt32 FromNodeIndex;
        UInt32 FromNodeOutputIndex;
        UInt32 GraphOutputIndex;
        _Field_z_ _Maybenull_ const char* Name;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_OUTPUT_GRAPH_EDGE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_INTERMEDIATE_GRAPH_EDGE_DESC
    /// </para>
    /// </summary>
    struct IntermediateGraphEdgeDesc
    {
        UInt32 FromNodeIndex;
        UInt32 FromNodeOutputIndex;
        UInt32 ToNodeIndex;
        UInt32 ToNodeInputIndex;
        _Field_z_ _Maybenull_ const char* Name;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_INTERMEDIATE_GRAPH_EDGE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GRAPH_NODE_TYPE
    /// </para>
    /// </summary>
    enum class GraphNodeType
    {
        Invalid = DML_GRAPH_NODE_TYPE_INVALID,
        Operator = DML_GRAPH_NODE_TYPE_OPERATOR,
        Constant = DML_GRAPH_NODE_TYPE_CONSTANT
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GRAPH_NODE_DESC
    /// </para>
    /// </summary>
    struct GraphNodeDesc
    {
        GraphNodeType Type;
        _Field_size_( _Inexpressible_( "Dependent on node type" ) ) const void* Desc;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GRAPH_NODE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_OPERATOR_GRAPH_NODE_DESC
    /// </para>
    /// </summary>
    struct OperatorGraphNodeDesc
    {
        IDMLOperator* Operator;
        _Field_z_ _Maybenull_ const char* Name;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_OPERATOR_GRAPH_NODE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CONSTANT_DATA_GRAPH_NODE_DESC
    /// </para>
    /// </summary>
    struct ConstantDataGraphNodeDesc
    {
        _Field_size_bytes_( DataSize ) const void* Data;
        SIZE_T DataSize;
        _Field_z_ _Maybenull_ const char* Name;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CONSTANT_DATA_GRAPH_NODE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GRAPH_DESC
    /// </para>
    /// </summary>
    struct GraphDesc
    {
        UInt32 InputCount;
        UInt32 OutputCount;

        UInt32 NodeCount;
        _Field_size_( NodeCount ) const GraphNodeDesc* Nodes;

        UInt32 InputEdgeCount;
        _Field_size_opt_( InputEdgeCount ) const GraphEdgeDesc* InputEdges;

        UInt32 OutputEdgeCount;
        _Field_size_( OutputEdgeCount ) const GraphEdgeDesc* OutputEdges;

        UInt32 IntermediateEdgeCount;
        _Field_size_opt_( IntermediateEdgeCount ) const GraphEdgeDesc* IntermediateEdges;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GRAPH_DESC );
    };


    class Device1 : public Device
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Device1, Device, IDMLDevice1, IDMLDevice )

    public:
        void CompileGraph( const DML_GRAPH_DESC* desc, DML_EXECUTION_FLAGS flags, REFIID riid, _COM_Outptr_opt_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CompileGraph( desc, flags, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        CompiledOperator CompileGraph( const GraphDesc& desc, ExecutionFlags flags ) const
        {
            IDMLCompiledOperator* itf = nullptr;
            CompileGraph( desc, static_cast< DML_EXECUTION_FLAGS >( flags ), __uuidof( IDMLCompiledOperator ), reinterpret_cast< void** >( &itf ) );
            return CompiledOperator( itf );
        }

    };


    // Expected: IDMLDevice
    inline void CreateDevice( ID3D12Device* d3d12Device, DML_CREATE_DEVICE_FLAGS flags, REFIID riid, _COM_Outptr_opt_ void** ppv )
    {
        auto hr = DMLCreateDevice( d3d12Device, flags, riid, ppv );
        HCC_COM_CHECK_HRESULT( hr );
    }

    template<typename T = Device>
        requires std::is_base_of_v<Device, T>
    inline T CreateDevice( ID3D12Device* d3d12Device, CreateDeviceFlags flags = CreateDeviceFlags::None )
    {
        using ItfType = typename T::InterfaceType;
        ItfType* itf = nullptr;
        CreateDevice( d3d12Device, static_cast< DML_CREATE_DEVICE_FLAGS >( flags ), __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        return T( itf );
    }

    template<typename T = Device>
        requires std::is_base_of_v<Device, T>
    inline T CreateDevice( const Graphics::D3D12::Device& d3d12Device, CreateDeviceFlags flags = CreateDeviceFlags::None )
    {
        return CreateDevice<T>( d3d12Device.GetInterfacePointer<ID3D12Device>( ), flags );
    }


#if DML_TARGET_VERSION >= 0x2000

    // Expected: IDMLDevice
    inline void CreateDevice1( ID3D12Device* d3d12Device, DML_CREATE_DEVICE_FLAGS flags, DML_FEATURE_LEVEL minimumFeatureLevel, REFIID riid, _COM_Outptr_opt_ void** ppv )
    {
        auto hr = DMLCreateDevice1( d3d12Device, flags, minimumFeatureLevel, riid, ppv );
        HCC_COM_CHECK_HRESULT( hr );
    }

    template<typename T = Device>
        requires std::is_base_of_v<Device, T>
    inline T CreateDevice1( ID3D12Device* d3d12Device, DML::FeatureLevel minimumFeatureLevel, CreateDeviceFlags flags = CreateDeviceFlags::None )
    {
        using ItfType = typename T::InterfaceType;
        ItfType* itf = nullptr;
        CreateDevice1( d3d12Device, static_cast< DML_CREATE_DEVICE_FLAGS >( flags ), static_cast< DML_FEATURE_LEVEL >( minimumFeatureLevel ), __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        return T( itf );
    }

    template<typename T = Device>
        requires std::is_base_of_v<Device, T>
    inline T CreateDevice1( const Graphics::D3D12::Device& d3d12Device, DML::FeatureLevel minimumFeatureLevel, CreateDeviceFlags flags = CreateDeviceFlags::None )
    {
        return CreateDevice1<T>( d3d12Device.GetInterfacePointer<ID3D12Device>( ), minimumFeatureLevel, flags );
    }

#endif

}
#endif
