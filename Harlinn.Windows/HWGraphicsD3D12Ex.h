#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12EX_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12EX_H_

#include <HWDef.h>
#include <HWDXGIFormat.h>
#include <HWDXGI.h>
#include <HWCommon.h>

namespace Harlinn::Windows::Graphics::D3D12
{
    /// <summary>
    /// Specifies the type of a command list.
    /// </summary>
    enum class CommandListType : Int32
    {
        /// <summary>
        /// Specifies a command buffer that the GPU can execute. A direct command 
        /// list doesn't inherit any GPU state.
        /// </summary>
        Direct = D3D12_COMMAND_LIST_TYPE_DIRECT,
        /// <summary>
        /// Specifies a command buffer that can be executed only directly via a 
        /// direct command list. A bundle command list inherits all GPU state (except for the currently set pipeline state object and primitive topology).
        /// </summary>
        Bundle = D3D12_COMMAND_LIST_TYPE_BUNDLE,
        /// <summary>
        /// Specifies a command buffer for computing.
        /// </summary>
        Compute = D3D12_COMMAND_LIST_TYPE_COMPUTE,
        /// <summary>
        /// Specifies a command buffer for copying.
        /// </summary>
        Copy = D3D12_COMMAND_LIST_TYPE_COPY,
        /// <summary>
        /// Specifies a command buffer for video decoding.
        /// </summary>
        VideoDecode = D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE,
        /// <summary>
        /// Specifies a command buffer for video processing.
        /// </summary>
        VideoProcess = D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS,
        /// <summary>
        /// Specifies a command buffer for video encoding.
        /// </summary>
        VideoEncode = D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE
    };

    /// <summary>
    /// Specifies flags to be used when creating a command queue.
    /// </summary>
    enum class CommandQueueFlags : Int32
    {
        /// <summary>
        /// Indicates a default command queue.
        /// </summary>
        None = D3D12_COMMAND_QUEUE_FLAG_NONE,
        /// <summary>
        /// Indicates that the GPU timeout should be disabled for this command queue.
        /// </summary>
        DisableGpuTimeout = D3D12_COMMAND_QUEUE_FLAG_DISABLE_GPU_TIMEOUT
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommandQueueFlags, Int32 );


    /// <summary>
    /// Defines priority levels for a command queue.
    /// </summary>
    /// <remarks>
    /// An application must be sufficiently privileged in order to create a command 
    /// queue that has global realtime priority. If the application is not sufficiently 
    /// privileged or if neither the adapter or driver can provide the necessary preemption, 
    /// then requests to create a global realtime priority queue fail; such a failure 
    /// could be due to a lack of hardware support or due to conflicts with other command 
    /// queue parameters. Requests to create a global realtime command queue won't silently 
    /// downgrade the priority when it can't be supported; the request succeeds or fails 
    /// as-is to indicate to the application whether or not the command queue is guaranteed 
    /// to execute before any other queue.
    /// </remarks>
    enum class CommandQueuePriority : Int32
    {
        /// <summary>
        /// Normal priority.
        /// </summary>
        Normal = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
        /// <summary>
        /// High priority.
        /// </summary>
        High = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
        /// <summary>
        /// Global realtime priority.
        /// </summary>
        Realtime = D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME
    };

    /// <summary>
    /// Describes a command queue.
    /// </summary>
    struct CommandQueueDesc
    {
        CommandListType Type = CommandListType::Direct;
        union
        {
            CommandQueuePriority Priority = CommandQueuePriority::Normal;
            Int32 PriorityValue;
        };
        CommandQueueFlags Flags = CommandQueueFlags::None;
        UInt32 NodeMask = 0;
    };

    static_assert( sizeof( D3D12_COMMAND_QUEUE_DESC ) == sizeof( CommandQueueDesc ) );

    /// <summary>
    /// Specifies how the pipeline interprets geometry or hull shader input primitives.
    /// </summary>
    enum class PrimitiveTopologyType : Int32
    {
        /// <summary>
        /// The shader has not been initialized with an input primitive type.
        /// </summary>
        Undefined = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
        /// <summary>
        /// Interpret the input primitive as a point.
        /// </summary>
        Point = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
        /// <summary>
        /// Interpret the input primitive as a line.
        /// </summary>
        Line = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
        /// <summary>
        /// Interpret the input primitive as a triangle.
        /// </summary>
        Triangle = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
        /// <summary>
        /// Interpret the input primitive as a control point patch.
        /// </summary>
        Patch = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH
    };


    enum class InputClassification : Int32
    {
        PerVertexData = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        PerInstanceData = D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA
    };

    /// <summary>
    /// Describes a single element for the input-assembler stage of the graphics pipeline.
    /// </summary>
    struct InputElementDesc
    {
        /// <summary>
        /// The HLSL semantic associated with this element in a shader input-signature. 
        /// See <see href="https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics">HLSL Semantics for more info</see>.
        /// </summary>
        LPCSTR SemanticName = nullptr;
        /// <summary>
        /// The semantic index for the element. A semantic index modifies a semantic, 
        /// with an integer index number. A semantic index is only needed in a case 
        /// where there is more than one element with the same semantic. For example, 
        /// a 4x4 matrix would have four components each with the semantic name matrix, 
        /// however each of the four component would have different semantic indices (0, 1, 2, and 3).
        /// </summary>
        UInt32 SemanticIndex = 0;
        /// <summary>
        /// A <see cref="DXGI::Format">DXGI::Format</see>-typed value that specifies the format of the element data.
        /// </summary>
        DXGI::Format Format = DXGI::Format::Unknown;
        /// <summary>
        /// An integer value that identifies the input-assembler. For more info, see 
        /// <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/d3d10-graphics-programming-guide-input-assembler-stage-getting-started">Input Slots</see>. 
        /// Valid values are between 0 and 15.
        /// </summary>
        UInt32 InputSlot = 0;
        /// <summary>
        /// Optional. Offset, in bytes, to this element from the start of the vertex. 
        /// Use D3D12_APPEND_ALIGNED_ELEMENT (0xffffffff) for convenience to define 
        /// the current element directly after the previous one, including any packing 
        /// if necessary.
        /// </summary>
        UInt32 AlignedByteOffset = 0;
        /// <summary>
        /// A value that identifies the input data class for a single input slot.
        /// </summary>
        InputClassification InputSlotClass = InputClassification::PerVertexData;
        /// <summary>
        /// The number of instances to draw using the same per-instance data before 
        /// advancing in the buffer by one element. This value must be 0 for an element 
        /// that contains per-vertex data (the slot class is set to the 
        /// PerVertexData member of InputClassification).
        /// </summary>
        UINT InstanceDataStepRate = 0;
    }; 
    static_assert( sizeof( D3D12_INPUT_ELEMENT_DESC ) == sizeof( InputElementDesc ) );

    /// <summary>
    /// Specifies the fill mode to use when rendering triangles.
    /// </summary>
    enum class FillMode : Int32
    {
        Unknown = 0,
        /// <summary>
        /// Draw lines connecting the vertices. Adjacent vertices are not drawn.
        /// </summary>
        Wireframe = D3D12_FILL_MODE_WIREFRAME,
        /// <summary>
        /// Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
        /// </summary>
        Solid = D3D12_FILL_MODE_SOLID
    };


    /// <summary>
    /// Specifies triangles facing a particular direction are not drawn.
    /// </summary>
    enum class CullMode : Int32
    {
        /// <summary>
        /// Always draw all triangles.
        /// </summary>
        None = D3D12_CULL_MODE_NONE,
        /// <summary>
        /// Do not draw triangles that are front-facing.
        /// </summary>
        Front = D3D12_CULL_MODE_FRONT,
        /// <summary>
        /// Do not draw triangles that are back-facing.
        /// </summary>
        Back = D3D12_CULL_MODE_BACK
    };

    /// <summary>
    /// Describes a vertex element in a vertex buffer in an output slot.
    /// </summary>
    struct StreamOutputDeclarationEntry
    {
        /// <summary>
        /// Zero-based, stream number.
        /// </summary>
        UInt32 Stream = 0;
        /// <summary>
        /// Type of output element; possible values include: "POSITION", "NORMAL", or "TEXCOORD0". 
        /// Note that if SemanticName is NULL then ComponentCount can be greater than 4 and the 
        /// described entry will be a gap in the stream out where no data will be written.
        /// </summary>
        LPCSTR SemanticName = nullptr;
        /// <summary>
        /// Output element's zero-based index. Use, for example, if you have more than one texture 
        /// coordinate stored in each vertex.
        /// </summary>
        UInt32 SemanticIndex = 0;
        /// <summary>
        /// The component of the entry to begin writing out to. Valid values are 0 to 3. For example, 
        /// if you only wish to output to the y and z components of a position, StartComponent is 1 
        /// and ComponentCount is 2.
        /// </summary>
        Byte StartComponent = 0;
        /// <summary>
        /// The number of components of the entry to write out to. Valid values are 1 to 4. For example, 
        /// if you only wish to output to the y and z components of a position, StartComponent is 1 and 
        /// ComponentCount is 2. Note that if SemanticName is NULL then ComponentCount can be greater 
        /// than 4 and the described entry will be a gap in the stream out where no data will be written.
        /// </summary>
        Byte ComponentCount = 0;
        /// <summary>
        /// The associated stream output buffer that is bound to the pipeline. The valid range for 
        /// OutputSlot is 0 to 3.
        /// </summary>
        Byte OutputSlot = 0;
    };
    static_assert( sizeof( D3D12_SO_DECLARATION_ENTRY ) == sizeof( StreamOutputDeclarationEntry ) );

    /// <summary>
    /// Describes the dimensions of a viewport.
    /// </summary>
    struct Viewport
    {
        /// <summary>
        /// X position of the left hand side of the viewport.
        /// </summary>
        FLOAT TopLeftX = 0.0f;
        /// <summary>
        /// Y position of the top of the viewport.
        /// </summary>
        FLOAT TopLeftY = 0.0f;
        /// <summary>
        /// Width of the viewport.
        /// </summary>
        FLOAT Width = 0.0f;
        /// <summary>
        /// Height of the viewport.
        /// </summary>
        FLOAT Height = 0.0f;
        /// <summary>
        /// Minimum depth of the viewport. Ranges between 0 and 1.
        /// </summary>
        FLOAT MinDepth = 0.0f;
        /// <summary>
        /// Maximum depth of the viewport. Ranges between 0 and 1.
        /// </summary>
        FLOAT MaxDepth = 0.0f;
    };
    static_assert( sizeof( D3D12_VIEWPORT ) == sizeof( Viewport ) );

    using Rectangle = Windows::Rectangle;

    /// <summary>
    /// Describes a 3D box.
    /// </summary>
    struct Box
    {
        /// <summary>
        /// The x position of the left hand side of the box.
        /// </summary>
        UInt32 Left = 0;
        /// <summary>
        /// The y position of the top of the box.
        /// </summary>
        UInt32 Top = 0;
        /// <summary>
        /// The z position of the front of the box.
        /// </summary>
        UInt32 Front = 0;
        /// <summary>
        /// The x position of the right hand side of the box, plus 1. This means that Right - Left equals the width of the box.
        /// </summary>
        UInt32 Right = 0;
        /// <summary>
        /// The y position of the bottom of the box, plus 1. This means that Bottom - Top equals the height of the box.
        /// </summary>
        UInt32 Bottom = 0;
        /// <summary>
        /// The z position of the back of the box, plus 1. This means that Back - Front equals the depth of the box.
        /// </summary>
        UInt32 Back = 0;
    };
    static_assert( sizeof( D3D12_BOX ) == sizeof( Box ) );

    /// <summary>
    /// Specifies comparison options. A comparison option determines how the 
    /// runtime compares source (new) data against destination (existing) data 
    /// before storing the new data. 
    /// </summary>
    enum class ComparisonFunction : Int32
    {
        Unknown = 0,
        /// <summary>
        /// Never pass the comparison.
        /// </summary>
        Never = D3D12_COMPARISON_FUNC_NEVER,
        /// <summary>
        /// If the source data is less than the destination data, the comparison passes.
        /// </summary>
        Less = D3D12_COMPARISON_FUNC_LESS,
        /// <summary>
        /// If the source data is equal to the destination data, the comparison passes.
        /// </summary>
        Equal = D3D12_COMPARISON_FUNC_EQUAL,
        /// <summary>
        /// If the source data is less than or equal to the destination data, the comparison passes.
        /// </summary>
        LessOrEqual = D3D12_COMPARISON_FUNC_LESS_EQUAL,
        /// <summary>
        /// If the source data is greater than the destination data, the comparison passes.
        /// </summary>
        Greater = D3D12_COMPARISON_FUNC_GREATER,
        /// <summary>
        /// If the source data is not equal to the destination data, the comparison passes.
        /// </summary>
        NotEqual = D3D12_COMPARISON_FUNC_NOT_EQUAL,
        /// <summary>
        /// If the source data is greater than or equal to the destination data, the comparison passes.
        /// </summary>
        GreaterOrEqual = D3D12_COMPARISON_FUNC_GREATER_EQUAL,
        /// <summary>
        /// Always pass the comparison.
        /// </summary>
        Always = D3D12_COMPARISON_FUNC_ALWAYS
    };

    /// <summary>
    /// Identifies the portion of a depth-stencil buffer for writing depth data.
    /// </summary>
    enum class DepthWriteMask : Int32
    {
        /// <summary>
        /// Turn off writes to the depth-stencil buffer.
        /// </summary>
        Zero = D3D12_DEPTH_WRITE_MASK_ZERO,
        /// <summary>
        /// Turn on writes to the depth-stencil buffer.
        /// </summary>
        All = D3D12_DEPTH_WRITE_MASK_ALL
    };

    /// <summary>
    /// Identifies the stencil operations that can be performed during depth-stencil testing.
    /// </summary>
    enum class StencilOperation : Int32
    {
        /// <summary>
        /// Keep the existing stencil data.
        /// </summary>
        Keep = D3D12_STENCIL_OP_KEEP,
        /// <summary>
        /// Set the stencil data to 0.
        /// </summary>
        Zero = D3D12_STENCIL_OP_ZERO,
        /// <summary>
        /// Set the stencil data to the reference value set by calling <see cref="GraphicsCommandList::OMSetStencilRef">GraphicsCommandList::OMSetStencilRef</see>.
        /// </summary>
        Replace = D3D12_STENCIL_OP_REPLACE,
        /// <summary>
        /// Increment the stencil value by 1, and clamp the result
        /// </summary>
        IncrementIfNotSaturated = D3D12_STENCIL_OP_INCR_SAT,
        /// <summary>
        /// Decrement the stencil value by 1, and clamp the result.
        /// </summary>
        DecrementIfNotSaturated = D3D12_STENCIL_OP_DECR_SAT,
        /// <summary>
        /// nvert the stencil data.
        /// </summary>
        Invert = D3D12_STENCIL_OP_INVERT,
        /// <summary>
        /// Increment the stencil value by 1, and wrap the result if necessary.
        /// </summary>
        Increment = D3D12_STENCIL_OP_INCR,
        /// <summary>
        /// Decrement the stencil value by 1, and wrap the result if necessary.
        /// </summary>
        Decrement = D3D12_STENCIL_OP_DECR
    };

    /// <summary>
    /// Describes stencil operations that can be performed based on the results of stencil test.
    /// </summary>
    struct StencilOperationsDesc
    {
        /// <summary>
        /// Identifies the stencil operation to perform when stencil testing fails.
        /// </summary>
        StencilOperation StencilFailOp = StencilOperation::Keep;
        /// <summary>
        /// Identifies the stencil operation to perform when stencil testing passes and depth testing fails.
        /// </summary>
        StencilOperation StencilDepthFailOp = StencilOperation::Keep;
        /// <summary>
        /// Identifies the stencil operation to perform when stencil testing and depth testing both pass.
        /// </summary>
        StencilOperation StencilPassOp = StencilOperation::Keep;
        /// <summary>
        /// Identifies the function that compares stencil data against existing stencil data.
        /// </summary>
        ComparisonFunction StencilFunc = ComparisonFunction::Always;
    };
    static_assert( sizeof( D3D12_DEPTH_STENCILOP_DESC ) == sizeof( StencilOperationsDesc ) );


    /// <summary>
    /// Describes depth-stencil state.
    /// </summary>
    struct DepthStencilDesc
    {
        /// <summary>
        /// Specifies whether to enable depth testing. Set this member to TRUE to enable depth testing.
        /// </summary>
        BOOL DepthEnable = TRUE;
        /// <summary>
        /// Identifies a portion of the depth-stencil buffer that can be modified by depth data.
        /// </summary>
        D3D12::DepthWriteMask DepthWriteMask = D3D12::DepthWriteMask::All;
        /// <summary>
        /// Identifies a function that compares depth data against existing depth data.
        /// </summary>
        ComparisonFunction DepthFunc = ComparisonFunction::Less;
        /// <summary>
        /// Specifies whether to enable stencil testing. Set this member to TRUE to enable stencil testing.
        /// </summary>
        BOOL StencilEnable = FALSE;
        /// <summary>
        /// Identify a portion of the depth-stencil buffer for reading stencil data
        /// </summary>
        UINT8 StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
        /// <summary>
        /// Identify a portion of the depth-stencil buffer for writing stencil data.
        /// </summary>
        UINT8 StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
        /// <summary>
        /// Describes how to use the results of the depth test and the stencil test 
        /// for pixels whose surface normal is facing towards the camera.
        /// </summary>
        StencilOperationsDesc FrontFace;
        /// <summary>
        /// Describes how to use the results of the depth test and the stencil test 
        /// for pixels whose surface normal is facing away from the camera.
        /// </summary>
        StencilOperationsDesc BackFace;
    };
    static_assert( sizeof( D3D12_DEPTH_STENCIL_DESC ) == sizeof( DepthStencilDesc ) );

    /// <summary>
    /// Describes depth-stencil state.
    /// </summary>
    struct DepthStencilDesc1 : public DepthStencilDesc
    {
        using Base = DepthStencilDesc;
        /// <summary>
        /// TRUE to enable depth-bounds testing; otherwise, FALSE. The default value is FALSE.
        /// </summary>
        BOOL DepthBoundsTestEnable = FALSE;
    };
    static_assert( sizeof( D3D12_DEPTH_STENCIL_DESC1 ) == sizeof( DepthStencilDesc1 ) );

    /// <summary>
    /// Specifies blend factors, which modulate values for the pixel shader and render target.
    /// </summary>
    enum class Blend : Int32
    {
        /// <summary>
        /// The blend factor is (0, 0, 0, 0). No pre-blend operation.
        /// </summary>
        Zero = D3D12_BLEND_ZERO,
        /// <summary>
        /// The blend factor is (1, 1, 1, 1). No pre-blend operation.
        /// </summary>
        One = D3D12_BLEND_ONE,
        /// <summary>
        /// The blend factor is (Rₛ, Gₛ, Bₛ, Aₛ), that is color data (RGB) from a pixel shader. No pre-blend operation.
        /// </summary>
        SourceColor = D3D12_BLEND_SRC_COLOR,
        /// <summary>
        /// The blend factor is (1 - Rₛ, 1 - Gₛ, 1 - Bₛ, 1 - Aₛ), that is color data (RGB) from a pixel shader. The pre-blend operation inverts the data, generating 1 - RGB.
        /// </summary>
        InvertSourceColor = D3D12_BLEND_INV_SRC_COLOR,
        /// <summary>
        /// The blend factor is (Aₛ, Aₛ, Aₛ, Aₛ), that is alpha data (A) from a pixel shader. No pre-blend operation.
        /// </summary>
        SourceAlpha = D3D12_BLEND_SRC_ALPHA,
        /// <summary>
        /// The blend factor is ( 1 - Aₛ, 1 - Aₛ, 1 - Aₛ, 1 - Aₛ), that is alpha data (A) from a pixel shader. 
        /// The pre-blend operation inverts the data, generating 1 - A.
        /// </summary>
        InvertSourceAlpha = D3D12_BLEND_INV_SRC_ALPHA,
        /// <summary>
        /// The blend factor is (Ad Ad Ad Ad), that is alpha data from a render target. No pre-blend operation.
        /// </summary>
        DestinationAlpha = D3D12_BLEND_DEST_ALPHA,
        /// <summary>
        /// The blend factor is (1 - Ad 1 - Ad 1 - Ad 1 - Ad), that is alpha data from a render target. The pre-blend operation inverts the data, generating 1 - A.
        /// </summary>
        InvertDestinationAlpha = D3D12_BLEND_INV_DEST_ALPHA,
        /// <summary>
        /// The blend factor is (Rd, Gd, Bd, Ad), that is color data from a render target. No pre-blend operation.
        /// </summary>
        DestinationColor = D3D12_BLEND_DEST_COLOR,
        /// <summary>
        /// The blend factor is (1 - Rd, 1 - Gd, 1 - Bd, 1 - Ad), that is color data from a render target. The pre-blend operation inverts the data, generating 1 - RGB.
        /// </summary>
        InvertDestinationColor = D3D12_BLEND_INV_DEST_COLOR,
        /// <summary>
        /// The blend factor is (f, f, f, 1); where f = min(Aₛ, 1 - Ad). The pre-blend operation clamps the data to 1 or less.
        /// </summary>
        SourceAlphaSaturate = D3D12_BLEND_SRC_ALPHA_SAT,
        /// <summary>
        /// The blend factor is the blend factor set with <see cref="GraphicsCommandList::OMSetBlendFactor">GraphicsCommandList::OMSetBlendFactor</see>. No pre-blend operation.
        /// </summary>
        BlendFactor = D3D12_BLEND_BLEND_FACTOR,
        /// <summary>
        /// The blend factor is the blend factor set with <see cref="GraphicsCommandList::OMSetBlendFactor">GraphicsCommandList::OMSetBlendFactor</see>. 
        /// The pre-blend operation inverts the blend factor, generating 1 - blend_factor.
        /// </summary>
        InvertBlendFactor = D3D12_BLEND_INV_BLEND_FACTOR,
        /// <summary>
        /// The blend factor is data sources both as color data output by a pixel shader. 
        /// There is no pre-blend operation. This blend factor supports dual-source color blending.
        /// </summary>
        Source1Color = D3D12_BLEND_SRC1_COLOR,
        /// <summary>
        /// The blend factor is data sources both as color data output by a pixel shader. The 
        /// pre-blend operation inverts the data, generating 1 - RGB. This blend factor 
        /// supports dual-source color blending.
        /// </summary>
        InvertSource1Color = D3D12_BLEND_INV_SRC1_COLOR,
        /// <summary>
        /// The blend factor is data sources as alpha data output by a pixel shader. There is 
        /// no pre-blend operation. This blend factor supports dual-source color blending.
        /// </summary>
        Source1Alpha = D3D12_BLEND_SRC1_ALPHA,
        /// <summary>
        /// The blend factor is data sources as alpha data output by a pixel shader. 
        /// The pre-blend operation inverts the data, generating 1 - A. This blend 
        /// factor supports dual-source color blending.
        /// </summary>
        InvertSource1Alpha = D3D12_BLEND_INV_SRC1_ALPHA,
        /// <summary>
        /// <para>
        /// The blend factor is (A, A, A, A), where the constant, A, is taken from the blend factor set with OMSetBlendFactor.
        /// </para>
        /// </summary>
        AlphaFactor = D3D12_BLEND_ALPHA_FACTOR,
        /// <summary>
        /// <para>
        /// The blend factor is (1 – A, 1 – A, 1 – A, 1 – A), where the constant, A, is taken from the blend factor set with OMSetBlendFactor.
        /// </para>
        /// </summary>
        InvertAlphaFactor = D3D12_BLEND_INV_ALPHA_FACTOR
    };

    /// <summary>
    /// Specifies RGB or alpha blending operations.
    /// </summary>
    /// <remarks>
    /// <para>
    /// The runtime implements RGB blending and alpha blending separately. Therefore, blend state 
    /// requires separate blend operations for RGB data and alpha data. These blend operations are 
    /// specified in a <see cref="RenderTargetBlendDesc">RenderTargetBlendDesc</see> structure. 
    /// The two sources — source 1 and source 2 — are shown in the <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/d3d10-graphics-programming-guide-output-merger-stage">blending block diagram</see>.
    /// </para>
    /// <para>
    /// Blend state is used by the output-merger stage to determine how to blend together 
    /// two RGB pixel values and two alpha values. The two RGB pixel values and two alpha 
    /// values are the RGB pixel value and alpha value that the pixel shader outputs and 
    /// the RGB pixel value and alpha value already in the output render target. 
    /// The <see cref="Blend">Blend</see> value controls the data source that the blending 
    /// stage uses to modulate values for the pixel shader, render target, or both. 
    /// The <c>BlendOperation</c> value controls how the blending stage mathematically 
    /// combines these modulated values.
    /// </para>
    /// </remarks>
    enum class BlendOperation : Int32
    {
        /// <summary>
        /// Add source 1 and source 2.
        /// </summary>
        Add = D3D12_BLEND_OP_ADD,
        /// <summary>
        /// Subtract source 1 from source 2.
        /// </summary>
        Subtract = D3D12_BLEND_OP_SUBTRACT,
        /// <summary>
        /// Subtract source 2 from source 1.
        /// </summary>
        ReverseSubtract = D3D12_BLEND_OP_REV_SUBTRACT,
        /// <summary>
        /// Find the minimum of source 1 and source 2.
        /// </summary>
        Min = D3D12_BLEND_OP_MIN,
        /// <summary>
        /// Find the maximum of source 1 and source 2.
        /// </summary>
        Max = D3D12_BLEND_OP_MAX
    };


    /// <summary>
    /// Identifies which components of each pixel of a render target are writable during blending.
    /// </summary>
    enum class ColorWriteEnable : UInt8
    {
        None = 0,
        /// <summary>
        /// Allow data to be stored in the red component.
        /// </summary>
        Red = D3D12_COLOR_WRITE_ENABLE_RED,
        /// <summary>
        /// Allow data to be stored in the green component.
        /// </summary>
        Green = D3D12_COLOR_WRITE_ENABLE_GREEN,
        /// <summary>
        /// Allow data to be stored in the blue component.
        /// </summary>
        Blue = D3D12_COLOR_WRITE_ENABLE_BLUE,
        /// <summary>
        /// Allow data to be stored in the alpha component.
        /// </summary>
        Alpha = D3D12_COLOR_WRITE_ENABLE_ALPHA,
        /// <summary>
        /// Allow data to be stored in all components.
        /// </summary>
        All = D3D12_COLOR_WRITE_ENABLE_ALL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ColorWriteEnable, UInt8 );

    /// <summary>
    /// Defines constants that specify logical operations to configure for a render target.
    /// </summary>
    enum LogicOperation : Int32
    {
        /// <summary>
        /// Clears the render target
        /// </summary>
        Clear = D3D12_LOGIC_OP_CLEAR,
        /// <summary>
        /// Sets the render target
        /// </summary>
        Set = D3D12_LOGIC_OP_SET,
        /// <summary>
        /// Copys the render target 
        /// </summary>
        Copy = D3D12_LOGIC_OP_COPY,
        /// <summary>
        /// Performs an inverted-copy of the render target
        /// </summary>
        Inverted = D3D12_LOGIC_OP_COPY_INVERTED,
        /// <summary>
        /// No operation is performed on the render target
        /// </summary>
        Noop = D3D12_LOGIC_OP_NOOP,
        /// <summary>
        /// Inverts the render target
        /// </summary>
        Invert = D3D12_LOGIC_OP_INVERT,
        /// <summary>
        /// Performs a logical AND operation on the render target
        /// </summary>
        And = D3D12_LOGIC_OP_AND,
        /// <summary>
        /// Performs a logical NAND operation on the render target
        /// </summary>
        NAnd = D3D12_LOGIC_OP_NAND,
        /// <summary>
        /// Performs a logical OR operation on the render target
        /// </summary>
        Or = D3D12_LOGIC_OP_OR,
        /// <summary>
        /// Performs a logical NOR operation on the render target
        /// </summary>
        NOr = D3D12_LOGIC_OP_NOR,
        /// <summary>
        /// Performs a logical XOR operation on the render target
        /// </summary>
        Xor = D3D12_LOGIC_OP_XOR,
        /// <summary>
        /// Performs a logical equal operation on the render target
        /// </summary>
        Equiv = D3D12_LOGIC_OP_EQUIV,
        /// <summary>
        /// Performs a logical AND and reverse operation on the render target
        /// </summary>
        AndReverse = D3D12_LOGIC_OP_AND_REVERSE,
        /// <summary>
        /// Performs a logical AND and invert operation on the render target
        /// </summary>
        AndInverted = D3D12_LOGIC_OP_AND_INVERTED,
        /// <summary>
        /// Performs a logical OR and reverse operation on the render target
        /// </summary>
        OrReverse = D3D12_LOGIC_OP_OR_REVERSE,
        /// <summary>
        /// Performs a logical OR and invert operation on the render target
        /// </summary>
        OrInverted = D3D12_LOGIC_OP_OR_INVERTED
    };

    /// <summary>
    /// Describes the blend state for a render target.
    /// </summary>
    /// <remarks>
    /// You specify an array of <c>RenderTargetBlendDesc</c> structures in the 
    /// RenderTarget member of the BlendDesc structure to describe the blend states 
    /// for render targets; you can bind up to eight render targets to the 
    /// <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/d3d10-graphics-programming-guide-output-merger-stage">output-merger</see> 
    /// stage at one time.
    /// </remarks>
    struct RenderTargetBlendDesc
    {
        /// <summary>
        /// Specifies whether to enable (or disable) blending. Set to TRUE to enable blending.
        /// </summary>
        BOOL BlendEnable = FALSE;
        /// <summary>
        /// Specifies whether to enable (or disable) a logical operation. Set to TRUE to enable a logical operation.
        /// </summary>
        BOOL LogicOpEnable = FALSE;
        /// <summary>
        /// Specifies the operation to perform on the RGB value that the pixel shader outputs. 
        /// The BlendOp member defines how to combine the SrcBlend and DestBlend operations.
        /// </summary>
        Blend SrcBlend = Blend::One;
        /// <summary>
        /// Specifies the operation to perform on the current RGB value in the render target. 
        /// The BlendOp member defines how to combine the SrcBlend and DestBlend operations.
        /// </summary>
        Blend DestBlend = Blend::Zero;
        /// <summary>
        /// Defines how to combine the SrcBlend and DestBlend operations.
        /// </summary>
        BlendOperation BlendOp = BlendOperation::Add;
        /// <summary>
        /// Specifies the operation to perform on the alpha value that the pixel shader outputs. 
        /// Blend options that end in <c>Color</c> are not allowed. The BlendOpAlpha member defines 
        /// how to combine the SrcBlendAlpha and DestBlendAlpha operations.
        /// </summary>
        Blend SrcBlendAlpha = Blend::One;
        /// <summary>
        /// Specifies the operation to perform on the current alpha value in the render target. 
        /// Blend options that end in <c>Color</c> are not allowed. The BlendOpAlpha member 
        /// defines how to combine the SrcBlendAlpha and DestBlendAlpha operations.
        /// </summary>
        Blend DestBlendAlpha = Blend::Zero;
        /// <summary>
        /// Defines how to combine the SrcBlendAlpha and DestBlendAlpha operations.
        /// </summary>
        BlendOperation BlendOpAlpha = BlendOperation::Add;
        /// <summary>
        /// Specifies the logical operation to configure for the render target.
        /// </summary>
        LogicOperation LogicOp = LogicOperation::Noop;
        /// <summary>
        /// Specifies the write mask.
        /// </summary>
        ColorWriteEnable RenderTargetWriteMask = ColorWriteEnable::All;
    };

    static_assert( sizeof( D3D12_RENDER_TARGET_BLEND_DESC ) == sizeof( RenderTargetBlendDesc ) );

    /// <summary>
    /// Describes the blend state.
    /// </summary>
    struct BlendDesc
    {
        /// <summary>
        /// Specifies whether to use alpha-to-coverage as a multisampling 
        /// technique when setting a pixel to a render target. For more info 
        /// about using alpha-to-coverage, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/d3d10-graphics-programming-guide-blend-state">Alpha-To-Coverage</see>.
        /// </summary>
        BOOL AlphaToCoverageEnable = FALSE;
        /// <summary>
        /// <para>
        /// Specifies whether to enable independent blending in simultaneous render targets. 
        /// Set to TRUE to enable independent blending. If set to FALSE, only the 
        /// RenderTarget[0] members are used; RenderTarget[1..7] are ignored.
        /// </para>
        /// </summary>
        BOOL IndependentBlendEnable = FALSE;
        /// <summary>
        /// An array of <see cref="RenderTargetBlendDesc">RenderTargetBlendDesc</see> structures 
        /// that describe the blend states for render targets; these correspond to the 
        /// eight render targets that can be bound to the output-merger stage at one time.
        /// </summary>
        RenderTargetBlendDesc RenderTarget[ 8 ];
    };
    static_assert( sizeof( D3D12_BLEND_DESC ) == sizeof( BlendDesc ) );

    /// <summary>
    /// Identifies whether conservative rasterization is on or off.
    /// </summary>
    enum class ConservativeRasterizationMode : Int32
    {
        /// <summary>
        /// Conservative rasterization is off.
        /// </summary>
        Off = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
        /// <summary>
        /// Conservative rasterization is on.
        /// </summary>
        On = D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON
    };

    /// <summary>
    /// Describes rasterizer state.
    /// </summary>
    struct RasterizerDesc
    {
        D3D12::FillMode FillMode = D3D12::FillMode::Solid;
        D3D12::CullMode CullMode = D3D12::CullMode::Back;
        BOOL FrontCounterClockwise = FALSE;
        INT DepthBias = 0;
        FLOAT DepthBiasClamp = 0.0f;
        FLOAT SlopeScaledDepthBias = 0.0f;
        BOOL DepthClipEnable = TRUE;
        BOOL MultisampleEnable = FALSE;
        BOOL AntialiasedLineEnable = FALSE;
        UINT ForcedSampleCount = 0;
        ConservativeRasterizationMode ConservativeRaster = ConservativeRasterizationMode::Off;
    };
    static_assert( sizeof( D3D12_RASTERIZER_DESC ) == sizeof( RasterizerDesc ) );

    /// <summary>
    /// Describes shader data.
    /// </summary>
    struct ShaderBytecode
    {
        /// <summary>
        /// A pointer to a memory block that contains the shader data.
        /// </summary>
        _Field_size_bytes_full_( BytecodeLength )  const void* pShaderBytecode = nullptr;
        /// <summary>
        /// The size, in bytes, of the shader data that the pShaderBytecode member points to.
        /// </summary>
        SIZE_T BytecodeLength = 0;
    };
    static_assert( sizeof( D3D12_SHADER_BYTECODE ) == sizeof( ShaderBytecode ) );

    /// <summary>
    /// Describes a streaming output buffer.
    /// </summary>
    struct StreamOutputDesc
    {
        /// <summary>
        /// An array of <see cref="StreamOutputDeclarationEntry">StreamOutputDeclarationEntry</see> structures. Cannot be nullptr if NumEntries > 0.
        /// </summary>
        _Field_size_full_( NumEntries )  const D3D12::StreamOutputDeclarationEntry* pSODeclaration = nullptr;
        /// <summary>
        /// The number of entries in the stream output declaration array that the pSODeclaration member points to.
        /// </summary>
        UINT NumEntries = 0;
        /// <summary>
        /// An array of buffer strides; each stride is the size of an element for that buffer.
        /// </summary>
        _Field_size_full_( NumStrides )  const UINT* pBufferStrides = nullptr;
        /// <summary>
        /// The number of strides (or buffers) that the pBufferStrides member points to.
        /// </summary>
        UINT NumStrides = 0;
        /// <summary>
        /// The index number of the stream to be sent to the rasterizer stage.
        /// </summary>
        UINT RasterizedStream = 0;
    };
    static_assert( sizeof( D3D12_STREAM_OUTPUT_DESC ) == sizeof( StreamOutputDesc ) );

    /// <summary>
    /// Describes the input-buffer data for the input-assembler stage.
    /// </summary>
    struct InputLayoutDesc
    {
        /// <summary>
        /// An array of <see cref="InputElementDesc">InputElementDesc</see> structures that describe the data types of the input-assembler stage.
        /// </summary>
        _Field_size_full_( NumElements ) const D3D12::InputElementDesc* pInputElementDescs = nullptr;
        /// <summary>
        /// The number of input-data types in the array of input elements that the pInputElementDescs member points to.
        /// </summary>
        UINT NumElements = 0;
    };
    static_assert( sizeof( D3D12_INPUT_LAYOUT_DESC ) == sizeof( InputLayoutDesc ) );

    /// <summary>
    /// When using triangle strip primitive topology, vertex positions are 
    /// interpreted as vertices of a continuous triangle “strip”. There is 
    /// a special index value that represents the desire to have a discontinuity 
    /// in the strip, the cut index value. This enum lists the supported cut values.
    /// </summary>
    enum class IndexBufferStripCutValue : Int32
    {
        /// <summary>
        /// Indicates that there is no cut value.
        /// </summary>
        Disabled = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,
        /// <summary>
        /// Indicates that 0xFFFF should be used as the cut value.
        /// </summary>
        MaxUInt16 = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF,
        /// <summary>
        /// Indicates that 0xFFFFFFFF should be used as the cut value.
        /// </summary>
        MaxUInt32 = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF
    };

    /// <summary>
    /// Stores a pipeline state.
    /// </summary>
    /// <remarks>
    /// <para>
    /// This structure is used by the <see cref="GraphicsPipelineStateDesc">GraphicsPipelineStateDesc</see> structure, and the <see href="ComputePipelineStateDesc">ComputePipelineStateDesc</see> structure.
    /// </para>
    /// <para>
    /// This structure is intended to be filled with the data retrieved from 
    /// <see cref="PipelineState::GetCachedBlob">PipelineState>::GetCachedBlob</see>. 
    /// This cached PSO contains data specific to the hardware, driver, and machine 
    /// that it was retrieved from. Compilation using this data should be faster than 
    /// compilation without. The rest of the data in the PSO needs to still be valid, 
    /// and needs to match the cached PSO, otherwise an exception for E_INVALIDARG might 
    /// be thrown.
    /// </para>
    /// <para>
    /// If the driver has been upgraded to a D3D12 driver after the PSO was cached, 
    /// you might see an exception for the D3D12_ERROR_DRIVER_VERSION_MISMATCH return code, 
    /// or if you’re running on a different GPU, an exception for the D3D12_ERROR_ADAPTER_NOT_FOUND 
    /// return code.
    /// </para>
    /// </remarks>
    struct CachedPipelineState
    {
        /// <summary>
        /// Specifies pointer that references the memory location of the cache.
        /// </summary>
        _Field_size_bytes_full_( CachedBlobSizeInBytes ) const void* pCachedBlob = nullptr;
        /// <summary>
        /// Specifies the size of the cache in bytes.
        /// </summary>
        SIZE_T CachedBlobSizeInBytes = 0;
    };
    static_assert( sizeof( D3D12_CACHED_PIPELINE_STATE ) == sizeof( CachedPipelineState ) );

    /// <summary>
    /// Flags to control pipeline state.
    /// </summary>
    enum PipelineStateFlags : Int32
    {
        /// <summary>
        /// Indicates no flags.
        /// </summary>
        None = D3D12_PIPELINE_STATE_FLAG_NONE,
        /// <summary>
        /// <para>
        /// Indicates that the pipeline state should be compiled with additional information to assist debugging.
        /// </para>
        /// <para>
        /// This can only be set on WARP devices.
        /// </para>
        /// </summary>
        ToolDebug = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG
    };


    struct GraphicsPipelineStateDesc
    {
        ID3D12RootSignature* pRootSignature = nullptr;
        ShaderBytecode VS;
        ShaderBytecode PS;
        ShaderBytecode DS;
        ShaderBytecode HS;
        ShaderBytecode GS;
        StreamOutputDesc StreamOutput;
        BlendDesc BlendState;
        UINT SampleMask = 0;
        RasterizerDesc RasterizerState;
        DepthStencilDesc DepthStencilState;
        InputLayoutDesc InputLayout;
        IndexBufferStripCutValue IBStripCutValue = IndexBufferStripCutValue::Disabled;
        PrimitiveTopologyType PrimitiveTopologyType = PrimitiveTopologyType::Undefined;
        UINT NumRenderTargets = 0;
        DXGI::Format RTVFormats[ 8 ]{};
        DXGI::Format DSVFormat = DXGI::Format::Unknown;
        DXGI::SampleDesc SampleDesc;
        UINT NodeMask = 0;
        CachedPipelineState CachedPSO;
        PipelineStateFlags Flags = PipelineStateFlags::None;
    };
    static_assert( sizeof( D3D12_GRAPHICS_PIPELINE_STATE_DESC ) == sizeof( GraphicsPipelineStateDesc ) );
}

#endif
