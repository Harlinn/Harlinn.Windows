#pragma once

#ifndef HARLINN_WINDOWS_HWDIRECTML_H_
#define HARLINN_WINDOWS_HWDIRECTML_H_

#include "HWGraphicsD3D12.h"

#pragma comment(lib, "DirectML.lib")

namespace Harlinn::Windows::DML
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
    };

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

    /// <summary>
    /// <para>
    /// Alias for DML_BUFFER_TENSOR_DESC
    /// </para>
    /// </summary>
    struct BufferTensorDesc
    {
        TensorDataType DataType;
        TensorFlags Flags;
        UInt32 DimensionCount;
        _Field_size_( DimensionCount ) const UInt32* Sizes;
        _Field_size_opt_( DimensionCount ) const UInt32* Strides;
        UInt64 TotalTensorSizeInBytes;
        UInt32 GuaranteedBaseOffsetAlignment;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BUFFER_TENSOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_TENSOR_DESC
    /// </para>
    /// </summary>
    struct TensorDesc
    {
        TensorType Type;
        _Field_size_( _Inexpressible_( "Dependent on tensor type" ) ) const void* Desc;

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
        Scatter  = DML_OPERATOR_SCATTER, 
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
        FLOAT Scale;
        FLOAT Bias;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCALE_BIAS );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SIZE_2D
    /// </para>
    /// </summary>
    struct Size2D
    {
        UINT Width;
        UINT Height;

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

    // ===================================================================================================================
    //   Operator descriptions
    // ===================================================================================================================

    /// <summary>
    /// <para>
    /// Alias for DML_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct OperatorDesc
    {
        OperatorType Type;
        _Field_size_( _Inexpressible_( "Dependent on operator type" ) ) const void* Desc;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_OPERATOR_DESC );
    };

    struct UnaryOperatorDesc
    {
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
    };

    struct BinaryOperatorDesc
    {
        const TensorDesc* ATensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
    };

    struct UnaryOperatorWithScaleBiasDesc : public UnaryOperatorDesc
    {
        _Maybenull_ const ScaleBias* ScaleBias = nullptr;
    };


    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IDENTITY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIdentityOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIdentity;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IDENTITY_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ABS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseAbsOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseAbs;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ABS_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ACOS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseACosOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseACos;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ACOS_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ADD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseAddOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseAdd;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ADD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ADD1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseAdd1OperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseAdd1;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ADD1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ASIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseASinOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseASin;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ASIN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ATAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseATanOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseATan;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ATAN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CEIL_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseCeilOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseCeil;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CEIL_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClipOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClip;
        FLOAT Min = 0.f;
        FLOAT Max = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_COS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseCosOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseCos;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_COS_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_DIVIDE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseDivideOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseDivide;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_DIVIDE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_EXP_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseExpOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseExp;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_EXP_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_FLOOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseFloorOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseFloor;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_FLOOR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOG_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLog;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOG_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_AND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DML_ELEMENT_WISE_LOGICAL_AND_OPERATOR_DESC : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalAnd;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_AND_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_EQUALS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalEqualsOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalEquals;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_EQUALS_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalGreaterThanOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalGreaterThan;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalLessThanOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalLessThan;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_NOT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalNotOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalNot;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_NOT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_OR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalOrOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalOr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_OR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_XOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalXorOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalXor;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_XOR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMaxOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMax;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MAX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MEAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMeanOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMean;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MEAN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMinOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMin;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MIN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MULTIPLY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseMultiplyOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseMultiply;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MULTIPLY_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_POW_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWisePowOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWisePow;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ExponentTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        _Maybenull_ const ScaleBias* ScaleBias = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_POW_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CONSTANT_POW_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseConstantPowOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseConstantPow;

        FLOAT Exponent = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CONSTANT_POW_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_RECIP_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseReciprocalOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseReciprocal;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_RECIP_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSinOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSin;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SIN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SQRT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSqrtOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSqrt;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SQRT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SUBTRACT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSubtractOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSubtract;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SUBTRACT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_TAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseTanOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseTan;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_TAN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_THRESHOLD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseThresholdOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseThreshold;
        FLOAT Min = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_THRESHOLD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_QUANTIZE_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseQuantizeLinearOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseQuantizeLinear;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* ZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_QUANTIZE_LINEAR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_DEQUANTIZE_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseDequantizeLinearOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseDequantizeLinear;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* ZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_DEQUANTIZE_LINEAR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_ELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationELUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationELU;
        
        FLOAT Alpha = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_ELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_HARDMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardMaxOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardMax;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARDMAX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_HARD_SIGMOID_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardSigmoidOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardSigmoid;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARD_SIGMOID_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_IDENTITY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationIdentityOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationIdentity;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_IDENTITY_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_LEAKY_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLeakyReLUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLeakyReLU;
        FLOAT Alpha = 0.f;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LEAKY_RELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLinearOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLinear;
        
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LINEAR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_LOG_SOFTMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLogSoftMaxOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLogSoftMax;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LOG_SOFTMAX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_PARAMETERIZED_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationParameterizedReLUOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationParameterizedReLU;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* SlopeTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_PARAMETERIZED_RELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_PARAMETRIC_SOFTPLUS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DML_ACTIVATION_PARAMETRIC_SOFTPLUS_OPERATOR_DESC : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationParametricSoftPlus;

        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_PARAMETRIC_SOFTPLUS_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationReLUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationReLU;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_RELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SCALED_ELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationScaledELUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationScaledELU;

        FLOAT Alpha = 0.f;
        FLOAT Gamma = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SCALED_ELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SCALED_TANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationScaledTanHOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationScaledTanH;
        
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SCALED_TANH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SIGMOID_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSigmoidOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSigmoid;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SIGMOID_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftMaxOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftMax;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTMAX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTPLUS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftPlusOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftPlus;
        
        FLOAT Steepness = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTPLUS_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTSIGN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftSignOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftSign;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTSIGN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_TANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationTanHOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationTanH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_TANH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_THRESHOLDED_RELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationThresholdedReLUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationThresholdedReLU;
        FLOAT Alpha;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_THRESHOLDED_RELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CONVOLUTION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ConvolutionOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Convolution;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* FilterTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        ConvolutionMode Mode = ConvolutionMode::Convolution;
        ConvolutionDirection Direction = ConvolutionDirection::Forward;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* OutputPadding = nullptr;
        UINT GroupCount = 0;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CONVOLUTION_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GEMM_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GEMMOperatorDesc
    {
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

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GEMM_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_REDUCE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ReduceOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Reduce;

        ReduceFunction Function = ReduceFunction::ArgMax;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_REDUCE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_AVERAGE_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AveragePoolingOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AveragePooling;

        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        BOOL IncludePadding = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_AVERAGE_POOLING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_LP_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LPPoolingOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LPPooling;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        UINT P = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LP_POOLING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPoolingOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPooling;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIPoolingOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ROIPooling;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* ROITensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        FLOAT SpatialScale = 0.f;
        Size2D PooledSize;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_POOLING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SLICE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SliceOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Slice;

        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Offsets = nullptr;
        _Field_size_( DimensionCount ) const UINT* Sizes = nullptr;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SLICE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CAST_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct CastOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Cast;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_CAST_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SPLIT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SplitOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Split;

        const TensorDesc* InputTensor = nullptr;
        UINT OutputCount = 0;
        _Field_size_( OutputCount ) const TensorDesc* OutputTensors = nullptr;
        UINT Axis = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SPLIT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_JOIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct JoinOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Join;

        UINT InputCount = 0;
        _Field_size_( InputCount ) const TensorDesc* InputTensors = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT Axis = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_JOIN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_PADDING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct PaddingOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Padding;
        
        DML::PaddingMode PaddingMode = DML::PaddingMode::Constant;
        FLOAT PaddingValue = 0.f;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_PADDING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_VALUE_SCALE_2D_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ValueScale2DOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ValueScale2D;

        FLOAT Scale = 0.f;
        UINT ChannelCount = 0;
        _Field_size_( ChannelCount ) const FLOAT* Bias = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_VALUE_SCALE_2D_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_UPSAMPLE_2D_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct UpSample2DOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::UpSample2D;

        Size2D ScaleSize;
        InterpolationMode InterpolationMode;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_UPSAMPLE_2D_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Gather;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT Axis = 0;
        UINT IndexDimensions = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SPACE_TO_DEPTH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SpaceToDepthOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::SpaceToDepth;
        UINT BlockSize = 0;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SPACE_TO_DEPTH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_DEPTH_TO_SPACE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DepthToSpaceOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DepthToSpace;
        UINT BlockSize = 0;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_DEPTH_TO_SPACE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_TILE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct TileOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Tile;
        UINT RepeatsCount = 0;
        _Field_size_( RepeatsCount ) const UINT* Repeats = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_TILE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_TOP_K_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct TopKOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::TopK;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputValueTensor = nullptr;
        const TensorDesc* OutputIndexTensor = nullptr;
        UINT Axis = 0;
        UINT K = 0;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_TOP_K_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationOperatorDesc
    {
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

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BATCH_NORMALIZATION_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MEAN_VARIANCE_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MeanVarianceNormalizationOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MeanVarianceNormalization;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        BOOL CrossChannel = FALSE;
        BOOL NormalizeVariance = FALSE;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MEAN_VARIANCE_NORMALIZATION_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_LOCAL_RESPONSE_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LocalResponseNormalizationOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LocalResponseNormalization;

        BOOL CrossChannel = FALSE;
        UINT LocalSize = 0;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;
        FLOAT Bias = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LOCAL_RESPONSE_NORMALIZATION_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_LP_NORMALIZATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LPNormalizationOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LPNormalization;

        UINT Axis = 0;
        FLOAT Epsilon = 0.f;
        UINT P = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LP_NORMALIZATION_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RNN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct RNNOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::RNN;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* WeightTensor = nullptr;
        const TensorDesc* RecurrenceTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* HiddenInitTensor = nullptr;
        _Maybenull_ const TensorDesc* SequenceLengthsTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSequenceTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSingleTensor = nullptr;
        UINT ActivationDescCount = 0;
        _Field_size_( ActivationDescCount ) const OperatorDesc* ActivationDescs = nullptr;
        RecurrentNetworkDirection Direction = RecurrentNetworkDirection::Forward;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RNN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_LSTM_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LSTMOperatorDesc
    {
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
        UINT ActivationDescCount = 0;
        _Field_size_( ActivationDescCount ) const OperatorDesc* ActivationDescs = nullptr;
        RecurrentNetworkDirection Direction = RecurrentNetworkDirection::Forward;
        float ClipThreshold = 0.f;
        BOOL UseClipThreshold = FALSE;
        BOOL CoupleInputForget = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LSTM_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GRU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GRUOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GRU;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* WeightTensor = nullptr;
        const TensorDesc* RecurrenceTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        _Maybenull_ const TensorDesc* HiddenInitTensor = nullptr;
        _Maybenull_ const TensorDesc* SequenceLengthsTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSequenceTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputSingleTensor = nullptr;
        UINT ActivationDescCount = 0;
        _Field_size_( ActivationDescCount ) const OperatorDesc* ActivationDescs = nullptr;
        RecurrentNetworkDirection Direction = RecurrentNetworkDirection::Forward;
        BOOL LinearBeforeReset = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LSTM_OPERATOR_DESC );
    };

#if DML_TARGET_VERSION >= 0x2000

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SIGN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSignOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSign;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SIGN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IS_NAN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIsNaNOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIsNaN;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IS_NAN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ERF_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseErfOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseErf;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ERF_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_SINH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseSinHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseSinH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_SINH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_COSH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseCosHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseCosH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_COSH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_TANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseTanHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseTanH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_TANH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ASINH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseASinHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseASinH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ASINH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ACOSH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseACosHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseACosH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ACOSH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ATANH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseATanHOperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseATanH;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ATANH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IF_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIfOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIf;

        const TensorDesc* ConditionTensor = nullptr;
        const TensorDesc* ATensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IF_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SHRINK_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationShrinkOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationShrink;

        FLOAT Bias = 0.f;
        FLOAT Threshold = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SHRINK_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_POOLING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPooling1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPooling1;
        _Maybenull_ const TensorDesc* OutputIndicesTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_UNPOOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxUnpoolingOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxUnpooling;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_UNPOOLING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_DIAGONAL_MATRIX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DiagonalMatrixOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DiagonalMatrix;

        const TensorDesc* OutputTensor = nullptr;
        INT Offset = 0;
        FLOAT Value = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DIAGONAL_MATRIX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SCATTER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ScatterElementsOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ScatterElements;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* UpdatesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT Axis = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCATTER_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ONE_HOT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct OneHotOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::OneHot;

        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* ValuesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT Axis = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ONE_HOT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ResampleOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample;

        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        UINT ScaleCount = 0;
        _Field_size_( ScaleCount ) const FLOAT* Scales = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x2000

#if DML_TARGET_VERSION >= 0x2100

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_SHIFT_LEFT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitShiftLeftOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitShiftLeft;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_SHIFT_LEFT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_SHIFT_RIGHT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitShiftRightOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitShiftRight;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_SHIFT_RIGHT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ROUND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseRoundOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseRound;
        DML::RoundingMode RoundingMode = DML::RoundingMode::HalvesToNearestEven;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ROUND_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_IS_INFINITY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseIsInfinityOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseIsInfinity;

        IsInfinityMode InfinityMode = IsInfinityMode::Either;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_IS_INFINITY_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MODULUS_TRUNCATE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseModulusTruncateOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseModulusTruncate;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MODULUS_TRUNCATE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_MODULUS_FLOOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseModulusFloorOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseModulusFloor;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_MODULUS_FLOOR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_FILL_VALUE_CONSTANT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct FillValueConstantOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::FillValueConstant;
        const TensorDesc* OutputTensor = nullptr;
        TensorDataType ValueDataType = TensorDataType::Unknown;
        ScalarUnion Value{};
        DML_IMPLEMENT_CONVERSIONS_TO( DML_FILL_VALUE_CONSTANT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_FILL_VALUE_SEQUENCE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct FillValueSequenceOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::FillValueSequence;
        const TensorDesc* OutputTensor = nullptr;
        TensorDataType ValueDataType = TensorDataType::Unknown;
        ScalarUnion ValueStart{};
        ScalarUnion ValueDelta{};
        DML_IMPLEMENT_CONVERSIONS_TO( DML_FILL_VALUE_SEQUENCE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CUMULATIVE_SUMMATION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DML_CUMULATIVE_SUMMATION_OPERATOR_DESC : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::CumulativeSummation;

        UINT Axis = 0;
        AxisDirection AxisDirection = AxisDirection::Increasing;
        BOOL HasExclusiveSum = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CUMULATIVE_SUMMATION_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_REVERSE_SUBSEQUENCES_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ReverseSubsequencesOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ReverseSubsequences;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* SequenceLengthsTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT Axis = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_REVERSE_SUBSEQUENCES_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_ELEMENTS_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherElementsOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GatherElements;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT Axis = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_ELEMENTS_OPERATOR_DESC );
    };

    // Alias existing operator, symmetric with ScatterOperatorDesc.
    using ScatterOperatorDesc = ScatterElementsOperatorDesc;

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_ND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherNDOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GatherND;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT InputDimensionCount = 0;
        UINT IndicesDimensionCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_ND_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SCATTER_ND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ScatterNDOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ScatterND;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* UpdatesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT InputDimensionCount = 0;
        UINT IndicesDimensionCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_SCATTER_ND_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_POOLING2_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPooling2OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPooling2;

        _Maybenull_ const TensorDesc* OutputIndicesTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING2_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SLICE1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Slice1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Slice1;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* InputWindowOffsets = nullptr;
        _Field_size_( DimensionCount ) const UINT* InputWindowSizes = nullptr;
        _Field_size_( DimensionCount ) const INT* InputWindowStrides = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SLICE1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_TOP_K1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct TopK1OperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::TopK1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputValueTensor = nullptr;
        const TensorDesc* OutputIndexTensor = nullptr;
        UINT Axis = 0;
        UINT K = 0;
        AxisDirection AxisDirection = AxisDirection::Increasing;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_TOP_K1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_DEPTH_TO_SPACE1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DepthToSpace1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DepthToSpace1;
        UINT BlockSize = 0;
        DepthSpaceOrder Order = DepthSpaceOrder::DepthColumnRow;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_DEPTH_TO_SPACE1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SPACE_TO_DEPTH1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SpaceToDepth1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::SpaceToDepth1;
        UINT BlockSize = 0;
        DepthSpaceOrder Order = DepthSpaceOrder::DepthColumnRow;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SPACE_TO_DEPTH1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MEAN_VARIANCE_NORMALIZATION1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MeanVarianceNormalization1OperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MeanVarianceNormalization1;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* ScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* BiasTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;
        BOOL NormalizeVariance = FALSE;
        FLOAT Epsilon = 0.f;
        _Maybenull_ const OperatorDesc* FusedActivation = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MEAN_VARIANCE_NORMALIZATION1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Resample1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample1;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MATRIX_MULTIPLY_INTEGER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MatrixMultiplyIntegerOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MatrixMultiplyInteger;

        const TensorDesc* ATensor = nullptr;
        _Maybenull_ const TensorDesc* AZeroPointTensor = nullptr;
        const TensorDesc* BTensor = nullptr;
        _Maybenull_ const TensorDesc* BZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MATRIX_MULTIPLY_INTEGER_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_QUANTIZED_LINEAR_MATRIX_MULTIPLY_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct QuantizedLinearMatrixMultiplyOperatorDesc
    {
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

    /// <summary>
    /// <para>
    /// Alias for DML_CONVOLUTION_INTEGER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ConvolutionIntegerOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ConvolutionInteger;

        const TensorDesc* InputTensor = nullptr;
        _Maybenull_ const TensorDesc* InputZeroPointTensor = nullptr;
        const TensorDesc* FilterTensor = nullptr;
        _Maybenull_ const TensorDesc* FilterZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        UINT GroupCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_CONVOLUTION_INTEGER_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_QUANTIZED_LINEAR_CONVOLUTION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct QuantizedLinearConvolutionOperatorDesc
    {
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
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        UINT GroupCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_QUANTIZED_LINEAR_CONVOLUTION_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x2100

#if DML_TARGET_VERSION >= 0x3000

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_AND_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitAndOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitAnd;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_AND_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_OR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitOrOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitOr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_OR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_XOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitXorOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitXor;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_XOR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_NOT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitNotOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitNot;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_NOT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_BIT_COUNT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseBitCountOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseBitCount;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_BIT_COUNT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OR_EQUAL_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalGreaterThanOrEqualOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalGreaterThanOrEqual;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_GREATER_THAN_OR_EQUAL_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OR_EQUAL_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseLogicalLessThanOrEqualOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseLogicalLessThanOrEqual;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_LOGICAL_LESS_THAN_OR_EQUAL_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_CELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationCeLUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationCeLU;
        FLOAT Alpha = 0.f;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_CELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_RELU_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationReLUGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationReLUGrad;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_RELU_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_AVERAGE_POOLING_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AveragePoolingGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AveragePoolingGrad;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        BOOL IncludePadding = FALSE;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_AVERAGE_POOLING_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MAX_POOLING_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MaxPoolingGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::MaxPoolingGrad;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_MAX_POOLING_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RANDOM_GENERATOR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct RandomGeneratorOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::RandomGenerator;
        const TensorDesc* InputStateTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputStateTensor = nullptr;
        RandomGeneratorType Type = RandomGeneratorType::Philox4x32_10;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_RANDOM_GENERATOR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_NONZERO_COORDINATES_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct NonZeroCoordinatesOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::NonZeroCoordinates;
        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputCountTensor = nullptr;
        const TensorDesc* OutputCoordinatesTensor = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_NONZERO_COORDINATES_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ResampleGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ResampleGrad;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_SLICE_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct SliceGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::SliceGrad;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* InputWindowOffsets = nullptr;
        _Field_size_( DimensionCount ) const UINT* InputWindowSizes = nullptr;
        _Field_size_( DimensionCount ) const INT* InputWindowStrides = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_SLICE_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ADAM_OPTIMIZER_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct AdamOptimizerOperatorDesc
    {
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

    /// <summary>
    /// <para>
    /// Alias for DML_ARGMIN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ArgMinOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ArgMin;
        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;
        DML::AxisDirection AxisDirection = DML::AxisDirection::Increasing;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ADAM_OPTIMIZER_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ARGMAX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ArgMaxOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ArgMax;

        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;
        DML::AxisDirection AxisDirection = DML::AxisDirection::Increasing;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ARGMAX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_ALIGN_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIAlignOperatorDesc
    {
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
        UINT MinimumSamplesPerOutput = 0;
        UINT MaximumSamplesPerOutput = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_ALIGN_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GATHER_ND1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct GatherND1OperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::GatherND1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* IndicesTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT InputDimensionCount = 0;
        UINT IndicesDimensionCount = 0;
        UINT BatchDimensionCount = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_GATHER_ND1_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x3000

#if DML_TARGET_VERSION >= 0x3100

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_ATAN_YX_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseATanYXOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseATanYX;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_ATAN_YX_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClipGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClipGrad;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        FLOAT Min = 0.f;
        FLOAT Max = 0.f;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_DIFFERENCE_SQUARE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseDifferenceSquareOperatorDesc : public BinaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseDifferenceSquare;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_DIFFERENCE_SQUARE_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_LOCAL_RESPONSE_NORMALIZATION_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LocalResponseNormalizationGradOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LocalResponseNormalizationGrad;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        BOOL CrossChannel = FALSE;
        UINT LocalSize = 0;
        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;
        FLOAT Bias = 0.f;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_LOCAL_RESPONSE_NORMALIZATION_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_CUMULATIVE_PRODUCT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct CumulativeProductOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::CumulativeProduct;
        UINT Axis = 0;
        DML::AxisDirection AxisDirection = DML::AxisDirection::Increasing;
        BOOL HasExclusiveProduct = FALSE;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_CUMULATIVE_PRODUCT_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationGradOperatorDesc
    {
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

#endif // DML_TARGET_VERSION >= 0x3100

#if DML_TARGET_VERSION >= 0x4000
    
    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_QUANTIZED_LINEAR_ADD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseQuantizedLinearAddOperatorDesc
    {
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

    /// <summary>
    /// <para>
    /// Alias for DML_DYNAMIC_QUANTIZE_LINEAR_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DynamicQuantizeLinearOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DynamicQuantizeLinear;
        const TensorDesc* OutputScaleTensor = nullptr;                   // This is an output tensor
        const TensorDesc* OutputZeroPointTensor = nullptr;               // This is an output tensor

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DYNAMIC_QUANTIZE_LINEAR_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_ALIGN1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIAlign1OperatorDesc
    {
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
        UINT MinimumSamplesPerOutput = 0;
        UINT MaximumSamplesPerOutput = 0;
        BOOL AlignRegionsToCorners = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_ALIGN1_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x4000

#if DML_TARGET_VERSION >= 0x4100

    /// <summary>
    /// <para>
    /// Alias for DML_ROI_ALIGN_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ROIAlignGradOperatorDesc
    {
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
        UINT MinimumSamplesPerOutput = 0;
        UINT MaximumSamplesPerOutput = 0;
        BOOL AlignRegionsToCorners = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ROI_ALIGN_GRAD_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_TRAINING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationTrainingOperatorDesc
    {
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

    /// <summary>
    /// <para>
    /// Alias for DML_BATCH_NORMALIZATION_TRAINING_GRAD_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct BatchNormalizationTrainingGradOperatorDesc
    {
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

#endif // DML_TARGET_VERSION >= 0x4100

#if DML_TARGET_VERSION >= 0x5000

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClip1OperatorDesc : public UnaryOperatorWithScaleBiasDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClip1;

        TensorDataType MinMaxDataType = TensorDataType::Unknown;
        ScalarUnion Min{};
        ScalarUnion Max{};

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_CLIP_GRAD1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseClipGrad1OperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseClipGrad1;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputGradientTensor = nullptr;
        const TensorDesc* OutputGradientTensor = nullptr;
        TensorDataType MinMaxDataType = TensorDataType::Unknown;
        ScalarUnion Min{};
        ScalarUnion Max{};

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_CLIP_GRAD1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_PADDING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Padding1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Padding1;

        DML::PaddingMode PaddingMode = DML::PaddingMode::Constant;
        TensorDataType PaddingValueDataType = TensorDataType::Unknown;
        ScalarUnion PaddingValue{};
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_PADDING1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ELEMENT_WISE_NEGATE_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ElementWiseNegateOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ElementWiseNegate;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ELEMENT_WISE_NEGATE_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x5000

#if DML_TARGET_VERSION >= 0x5100

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_GELU_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationGeLUOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationGeLU;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_GELU_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SOFTMAX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSoftMax1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSoftMax1;
        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SOFTMAX1_OPERATOR_DESC );

    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_LOG_SOFTMAX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationLogSoftMax1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationLogSoftMax1;
        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_LOG_SOFTMAX1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_HARDMAX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardMax1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardMax1;
        UINT AxisCount = 0;
        _Field_size_( AxisCount ) const UINT* Axes = nullptr;
        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARDMAX1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE2_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct Resample2OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::Resample2;

        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        AxisDirection RoundingDirection = AxisDirection::Increasing;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE2_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_RESAMPLE_GRAD1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ResampleGrad1OperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ResampleGrad1;

        const TensorDesc* InputGradientTensor;
        const TensorDesc* OutputGradientTensor;
        DML::InterpolationMode InterpolationMode = DML::InterpolationMode::NearestNeighbor;
        AxisDirection RoundingDirection = AxisDirection::Increasing;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const FLOAT* Scales = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* InputPixelOffsets = nullptr;
        _Field_size_( DimensionCount ) const FLOAT* OutputPixelOffsets = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_RESAMPLE_GRAD1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_DIAGONAL_MATRIX1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DiagonalMatrix1OperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::DiagonalMatrix1;

        _Maybenull_ const TensorDesc* InputTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        TensorDataType ValueDataType = TensorDataType::Unknown;
        ScalarUnion Value{};
        INT DiagonalFillBegin = 0;
        INT DiagonalFillEnd = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_DIAGONAL_MATRIX1_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x5100

#if DML_TARGET_VERSION >= 0x6100

    /// <summary>
    /// <para>
    /// Alias for DML_MULTIHEAD_ATTENTION_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MultiheadAttentionOperatorDesc
    {
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
        UINT HeadCount = 0;
        MultiheadAttentionMaskType MaskType = MultiheadAttentionMaskType::None;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_MULTIHEAD_ATTENTION_OPERATOR_DESC );
    };

#endif // DML_TARGET_VERSION >= 0x6100

#if DML_TARGET_VERSION >= 0x6200

    /// <summary>
    /// <para>
    /// Alias for DML_LP_POOLING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct LPPooling1OperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::LPPooling1;

        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        UINT P = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_LP_POOLING1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_AVERAGE_POOLING1_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct DML_AVERAGE_POOLING1_OPERATOR_DESC : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::AveragePooling1;

        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        BOOL IncludePadding = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_AVERAGE_POOLING1_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_SWISH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationSwishOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationSwish;

        FLOAT SigmoidInputScale = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_SWISH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_ACTIVATION_HARD_SWISH_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct ActivationHardSwishOperatorDesc : public UnaryOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::ActivationHardSwish;

        FLOAT Alpha = 0.f;
        FLOAT Beta = 0.f;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_ACTIVATION_HARD_SWISH_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_QUANTIZED_LINEAR_AVERAGE_POOLING_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct QuantizedLinearAveragePoolingOperatorDesc
    {
        static constexpr DML::OperatorType OperatorType = DML::OperatorType::QuantizedLinearAveragePooling;

        const TensorDesc* InputTensor = nullptr;
        const TensorDesc* InputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* InputZeroPointTensor = nullptr;
        const TensorDesc* OutputScaleTensor = nullptr;
        _Maybenull_ const TensorDesc* OutputZeroPointTensor = nullptr;
        const TensorDesc* OutputTensor = nullptr;
        UINT DimensionCount = 0;
        _Field_size_( DimensionCount ) const UINT* Strides = nullptr;
        _Field_size_( DimensionCount ) const UINT* WindowSize = nullptr;
        _Field_size_( DimensionCount ) const UINT* StartPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* EndPadding = nullptr;
        _Field_size_( DimensionCount ) const UINT* Dilations = nullptr;
        BOOL IncludePadding = FALSE;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_QUANTIZED_LINEAR_AVERAGE_POOLING_OPERATOR_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_MATRIX_MULTIPLY_INTEGER_TO_FLOAT_OPERATOR_DESC
    /// </para>
    /// </summary>
    struct MatrixMultiplyIntegerToFloatOperatorDesc
    {
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

#endif // DML_TARGET_VERSION >= 0x6200

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
        UINT RequestedFeatureLevelCount = 0;
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
        void GetPrivateData( REFGUID guid, _Inout_ UINT* dataSize, _Out_writes_bytes_opt_( *dataSize ) void* data ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetPrivateData( guid, dataSize, data );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPrivateData( REFGUID guid, UINT dataSize, _In_reads_bytes_opt_( dataSize ) const void* data ) const
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
        void CheckFeatureSupport( DML_FEATURE feature, UINT featureQueryDataSize, _In_reads_bytes_opt_( featureQueryDataSize ) const void* featureQueryData, UINT featureSupportDataSize, _Out_writes_bytes_( featureSupportDataSize ) void* featureSupportData ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CheckFeatureSupport( feature, featureQueryDataSize, featureQueryData, featureSupportDataSize, featureSupportData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateOperator( const DML_OPERATOR_DESC* desc, REFIID riid,  _COM_Outptr_opt_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateOperator( desc, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CompileOperator( IDMLOperator* op, DML_EXECUTION_FLAGS flags, REFIID riid, _COM_Outptr_opt_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CompileOperator( op, flags, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateOperatorInitializer( UINT operatorCount, _In_reads_opt_( operatorCount ) IDMLCompiledOperator* const* operators, REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateOperatorInitializer( operatorCount, operators, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateCommandRecorder( REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCommandRecorder( riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateBindingTable( _In_opt_ const DML_BINDING_TABLE_DESC* desc, REFIID riid, _COM_Outptr_ void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateBindingTable( desc, riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Evict( UINT count, _In_reads_( count ) IDMLPageable* const* ppObjects ) const
        { 
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Evict( count, ppObjects );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void MakeResident( UINT count, _In_reads_( count ) IDMLPageable* const* ppObjects ) const
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

    /// <summary>
    /// <para>
    /// Alias for DML_EXECUTION_FLAGS
    /// </para>
    /// </summary>
    struct BindingProperties
    {
        UINT RequiredDescriptorCount = 0;
        UINT64 TemporaryResourceSize = 0;
        UINT64 PersistentResourceSize = 0;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BINDING_PROPERTIES );
    };


    class Dispatchable : public Pageable
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( Dispatchable, Pageable, IDMLDispatchable, IDMLPageable )

    public:
        DML_BINDING_PROPERTIES GetBindingProperties( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBindingProperties( );
        }
    };

    class CompiledOperator : public Dispatchable
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( CompiledOperator, Dispatchable, IDMLCompiledOperator, IDMLDispatchable )

    public:

    };

    class OperatorInitializer : public Dispatchable
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( OperatorInitializer, Dispatchable, IDMLOperatorInitializer, IDMLDispatchable )

    public:
        void Reset( UINT operatorCount, _In_reads_opt_( operatorCount ) IDMLCompiledOperator* const* operators ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( operatorCount, operators );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


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
    /// Alias for DML_BINDING_DESC
    /// </para>
    /// </summary>
    struct BindingDesc
    {
        BindingType Type = BindingType::None;
        _Field_size_opt_( _Inexpressible_( "Dependent on binding type" ) ) const void* Desc = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BINDING_DESC );
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

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BUFFER_BINDING );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_BUFFER_ARRAY_BINDING
    /// </para>
    /// </summary>
    struct BufferArrayBinding
    {
        UINT BindingCount = 0;
        _Field_size_( BindingCount ) const BufferBinding* Bindings = nullptr;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_BUFFER_ARRAY_BINDING );
    };


    class BindingTable : public DeviceChild
    {
    public:

        HCC_COM_STANDARD_METHODS_IMPL( BindingTable, DeviceChild, IDMLBindingTable, IDMLDeviceChild )

    public:
        void BindInputs( UINT bindingCount, _In_reads_opt_( bindingCount ) const DML_BINDING_DESC* bindings ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindInputs( bindingCount, bindings );
        }

        void BindOutputs( UINT bindingCount, _In_reads_opt_( bindingCount ) const DML_BINDING_DESC* bindings ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindOutputs( bindingCount, bindings );
        }

        void BindTemporaryResource( _In_opt_ const DML_BINDING_DESC* binding ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindTemporaryResource( binding );
        }

        void BindPersistentResource( _In_opt_ const DML_BINDING_DESC* binding ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BindPersistentResource( binding );
        }

        void Reset( _In_opt_ const DML_BINDING_TABLE_DESC* desc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( desc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

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
    };

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
        UINT GraphInputIndex;
        UINT ToNodeIndex;
        UINT ToNodeInputIndex;
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
        UINT FromNodeIndex;
        UINT FromNodeOutputIndex;
        UINT GraphOutputIndex;
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
        UINT FromNodeIndex;
        UINT FromNodeOutputIndex;
        UINT ToNodeIndex;
        UINT ToNodeInputIndex;
        _Field_z_ _Maybenull_ const char* Name;

        DML_IMPLEMENT_CONVERSIONS_TO( DML_INTERMEDIATE_GRAPH_EDGE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for DML_GRAPH_NODE_TYPE
    /// </para>
    /// </summary>
    enum GraphNodeType
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
        UINT InputCount;
        UINT OutputCount;

        UINT NodeCount;
        _Field_size_( NodeCount ) const GraphNodeDesc* Nodes;

        UINT InputEdgeCount;
        _Field_size_opt_( InputEdgeCount ) const GraphEdgeDesc* InputEdges;

        UINT OutputEdgeCount;
        _Field_size_( OutputEdgeCount ) const GraphEdgeDesc* OutputEdges;

        UINT IntermediateEdgeCount;
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
    };


    // Expected: IDMLDevice
    void CreateDevice( ID3D12Device* d3d12Device, DML_CREATE_DEVICE_FLAGS flags, REFIID riid, _COM_Outptr_opt_ void** ppv )
    {
        auto hr = DMLCreateDevice( d3d12Device, flags, riid, ppv );
        HCC_COM_CHECK_HRESULT( hr );
    }

#if DML_TARGET_VERSION >= 0x2000

    // Expected: IDMLDevice
    void CreateDevice1( ID3D12Device* d3d12Device, DML_CREATE_DEVICE_FLAGS flags, DML_FEATURE_LEVEL minimumFeatureLevel, REFIID riid, _COM_Outptr_opt_ void** ppv )
    {
        auto hr = DMLCreateDevice1( d3d12Device, flags, minimumFeatureLevel, riid, ppv );
        HCC_COM_CHECK_HRESULT( hr );
    }
#endif

}

#endif
