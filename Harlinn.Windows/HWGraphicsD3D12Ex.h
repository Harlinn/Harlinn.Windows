#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12EX_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12EX_H_
/*
   Copyright 2024 Espen Harlinn

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

#include <HWDef.h>
#include <HWDXGIFormat.h>
#include <HWDXGI.h>
#include <HWCommon.h>
#include "HWGraphicsD3Common.h"

namespace Harlinn::Windows::Graphics::D3D12
{
    class Resource;

#define HWD3D12_IMPLEMENT_CONVERSIONS_TO( name ) \
    operator const name* ( ) const \
    { \
        return reinterpret_cast< const name* >( this ); \
    } \
    operator name* ( ) \
    { \
        return reinterpret_cast< name* >( this ); \
    } \
    operator const name& ( ) const \
    { \
        return *reinterpret_cast< const name* >( this ); \
    } \
    operator name& ( ) \
    { \
        return *reinterpret_cast< name* >( this ); \
    } \
    using D3D12Type = name

    using GPUVirtualAddress = UInt64;

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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_COMMAND_QUEUE_DESC );
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
        UInt32 InstanceDataStepRate = 0;

        InputElementDesc( ) = default;

        InputElementDesc( const char* semanticName, UInt32 semanticIndex, DXGI::Format format, UInt32 inputSlot, UInt32 alignedByteOffset, InputClassification inputSlotClass, UInt32 instanceDataStepRate )
            : SemanticName( semanticName ), SemanticIndex( semanticIndex ), Format( format ), InputSlot( inputSlot ), AlignedByteOffset( alignedByteOffset ), InputSlotClass( inputSlotClass ), InstanceDataStepRate( instanceDataStepRate )
        { }


        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_INPUT_ELEMENT_DESC );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SO_DECLARATION_ENTRY );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_VIEWPORT );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BOX );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEPTH_STENCILOP_DESC );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEPTH_STENCIL_DESC );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEPTH_STENCIL_DESC1 );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_TARGET_BLEND_DESC );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BLEND_DESC );
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
        UInt32 ForcedSampleCount = 0;
        ConservativeRasterizationMode ConservativeRaster = ConservativeRasterizationMode::Off;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RASTERIZER_DESC );
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

        ShaderBytecode( ) = default;

        ShaderBytecode& operator = ( const D3D10Blob& blob )
        {
            pShaderBytecode = blob.GetBufferPointer( );
            BytecodeLength = blob.GetBufferSize( );
            return *this;
        }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SHADER_BYTECODE );


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
        UInt32 NumEntries = 0;
        /// <summary>
        /// An array of buffer strides; each stride is the size of an element for that buffer.
        /// </summary>
        _Field_size_full_( NumStrides )  const UInt32* pBufferStrides = nullptr;
        /// <summary>
        /// The number of strides (or buffers) that the pBufferStrides member points to.
        /// </summary>
        UInt32 NumStrides = 0;
        /// <summary>
        /// The index number of the stream to be sent to the rasterizer stage.
        /// </summary>
        UInt32 RasterizedStream = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STREAM_OUTPUT_DESC );
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
        UInt32 NumElements = 0;

        template<SimpleSpanLike T>
            requires std::is_same_v<InputElementDesc,T>
        InputLayoutDesc& operator = ( const T& elements )
        {
            NumElements = static_cast< UInt32 >( elements.size() );
            pInputElementDescs = elements.data( );
            return *this;
        }

        template<size_t N>
        InputLayoutDesc& operator = ( const std::array<InputElementDesc,N>& elements )
        {
            NumElements = static_cast< UInt32 >( N );
            pInputElementDescs = elements.data( );
            return *this;
        }

        template<size_t N>
        InputLayoutDesc& operator = ( const InputElementDesc (&elements)[N] )
        {
            NumElements = static_cast< UInt32 >( N );
            pInputElementDescs = elements;
            return *this;
        }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_INPUT_LAYOUT_DESC );
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

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_CACHED_PIPELINE_STATE );
    };
    static_assert( sizeof( D3D12_CACHED_PIPELINE_STATE ) == sizeof( CachedPipelineState ) );

    /// <summary>
    /// Flags to control pipeline state.
    /// </summary>
    enum class PipelineStateFlags : Int32
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
        /// <summary>
        /// A pointer to the <see href="">ID3D12RootSignature</see> object.
        /// </summary>
        ID3D12RootSignature* pRootSignature = nullptr;
        ShaderBytecode VS;
        ShaderBytecode PS;
        ShaderBytecode DS;
        ShaderBytecode HS;
        ShaderBytecode GS;
        StreamOutputDesc StreamOutput;
        BlendDesc BlendState;
        UInt32 SampleMask = 0;
        RasterizerDesc RasterizerState;
        DepthStencilDesc DepthStencilState;
        InputLayoutDesc InputLayout;
        IndexBufferStripCutValue IBStripCutValue = IndexBufferStripCutValue::Disabled;
        PrimitiveTopologyType PrimitiveTopologyType = PrimitiveTopologyType::Undefined;
        UInt32 NumRenderTargets = 0;
        DXGI::Format RTVFormats[ 8 ]{};
        DXGI::Format DSVFormat = DXGI::Format::Unknown;
        DXGI::SampleDesc SampleDesc;
        UInt32 NodeMask = 0;
        CachedPipelineState CachedPSO;
        PipelineStateFlags Flags = PipelineStateFlags::None;

        GraphicsPipelineStateDesc( ) = default;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GRAPHICS_PIPELINE_STATE_DESC );

    };
    static_assert( sizeof( D3D12_GRAPHICS_PIPELINE_STATE_DESC ) == sizeof( GraphicsPipelineStateDesc ) );


    struct ComputePipelineStateDesc
    {
        ID3D12RootSignature* pRootSignature = nullptr;
        ShaderBytecode CS;
        UInt32 NodeMask = 0;
        CachedPipelineState CachedPSO;
        PipelineStateFlags Flags = PipelineStateFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_COMPUTE_PIPELINE_STATE_DESC );
    };
    static_assert( sizeof( D3D12_COMPUTE_PIPELINE_STATE_DESC ) == sizeof( ComputePipelineStateDesc ) );

    /// <summary>
    /// Wraps an array of render target formats.
    /// </summary>
    /// <remarks>
    /// This structure is primarily intended to be used when creating pipeline 
    /// state stream descriptions that contain multiple contiguous render target 
    /// format descriptions.
    /// </remarks>
    struct RenderTargetFormatArray
    {
        /// <summary>
        /// Specifies a fixed-size array of DXGI::Format values that define the format of up to 8 render targets.
        /// </summary>
        DXGI::Format RTFormats[ 8 ]{};
        /// <summary>
        /// Specifies the number of render target formats stored in the array.
        /// </summary>
        UInt32 NumRenderTargets = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RT_FORMAT_ARRAY );
    };
    static_assert( sizeof( D3D12_RT_FORMAT_ARRAY ) == sizeof( RenderTargetFormatArray ) );

    /// <summary>
    /// Describes a pipeline state stream.
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    struct PipelineStateStreamDesc
    {
        /// <summary>
        /// Specifies the size of the opaque data structure pointed to by the pPipelineStateSubobjectStream member, in bytes.
        /// </summary>
        _In_  SIZE_T SizeInBytes;
        /// <summary>
        /// Specifies the address of a data structure that describes as a bytestream an arbitrary pipeline state subobject.
        /// </summary>
        _In_reads_( _Inexpressible_( "Dependent on size of subobjects" ) )  void* pPipelineStateSubobjectStream;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PIPELINE_STATE_STREAM_DESC );
    };
    static_assert( sizeof( D3D12_PIPELINE_STATE_STREAM_DESC ) == sizeof( PipelineStateStreamDesc ) );

    /// <summary>
    /// Specifies the type of a sub-object in a pipeline state stream description.
    /// </summary>
    /// <remarks>
    /// This enum is used in the creation of pipeline state objects using the 
    /// ID3D12Device1::CreatePipelineState method. The CreatePipelineState method takes a 
    /// D3D12_PIPELINE_STATE_STREAM_DESC as one of its parameters, this structure in turn 
    /// describes a bytestream made up of alternating D3D12_PIPELINE_STATE_SUBOBJECT_TYPE 
    /// enumeration values and their corresponding subobject description structs. 
    /// This bytestream description can be made a concrete type by defining a structure that 
    /// has the same alternating pattern of alternating D3D12_PIPELINE_STATE_SUBOBJECT_TYPE 
    /// enumeration values and their corresponding subobject description structs as members.
    /// </remarks>
    enum class PipelineStateSubobjectType : Int32
    {
        /// <summary>
        /// <para>
        /// Indicates a root signature subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ID3D12RootSignature.
        /// </para>
        /// </summary>
        RootSignature = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE,
        /// <summary>
        /// <para>
        /// Indicates a vertex shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Vs = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VS,
        /// <summary>
        /// <para>
        /// Indicates a pixel shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Ps = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS,
        /// <summary>
        /// <para>
        /// Indicates a domain shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Ds = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DS,
        /// <summary>
        /// <para>
        /// Indicates a hull shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Hs = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_HS,
        /// <summary>
        /// <para>
        /// Indicates a geometry shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Gs = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_GS,
        /// <summary>
        /// <para>
        /// Indicates a compute shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Cs = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CS,
        /// <summary>
        /// <para>
        /// Indicates a stream-output subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        StreamOutput = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_STREAM_OUTPUT,
        /// <summary>
        /// <para>
        /// Indicates a blend subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is BlendDesc.
        /// </para>
        /// </summary>
        Blend = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND,
        /// <summary>
        /// <para>
        /// Indicates a sample mask subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is UInt32.
        /// </para>
        /// </summary>
        SampleMask = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK,
        /// <summary>
        /// <para>
        /// Indicates indicates a rasterizer subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is RasterizerDesc.
        /// </para>
        /// </summary>
        Rasterizer = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER,
        /// <summary>
        /// <para>
        /// Indicates a depth stencil subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is DepthStencilDesc.
        /// </para>
        /// </summary>
        DepthStencil = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL,
        /// <summary>
        /// <para>
        /// Indicates an input layout subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is InputLayoutDesc.
        /// </para>
        /// </summary>
        InputLayout = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_INPUT_LAYOUT,
        /// <summary>
        /// <para>
        /// Indicates an index buffer strip cut value subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is IndexBufferStripCutValue.
        /// </para>
        /// </summary>
        IbStripCutValue = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_IB_STRIP_CUT_VALUE,
        /// <summary>
        /// <para>
        /// Indicates a primitive topology subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is PrimitiveTopologyType.
        /// </para>
        /// </summary>
        PrimitiveTopology = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PRIMITIVE_TOPOLOGY,
        /// <summary>
        /// <para>
        /// Indicates a render target formats subobject type. 
        /// </para>
        /// <para>
        /// The corresponding subobject type is RenderTargetFormatArray structure, which wraps an array of render target formats along with a count of the array elements.
        /// </para>
        /// </summary>
        RenderTargetFormats = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS,
        /// <summary>
        /// <para>
        /// Indicates a depth stencil format subobject.
        /// </para>
        /// <para>
        /// The corresponding subobject type is DXGI::Format.
        /// </para>
        /// </summary>
        DepthStencilFormat = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT,
        /// <summary>
        /// <para>
        /// Indicates a sample description subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is DXGI::SampleDesc.
        /// </para>
        /// </summary>
        SampleDesc = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC,
        /// <summary>
        /// <para>
        /// Indicates a node mask subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is D3D12_NODE_MASK or UInt32.
        /// </para>
        /// </summary>
        NodeMask = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_NODE_MASK,
        /// <summary>
        /// <para>
        /// Indicates a cached pipeline state object subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is CachedPipelineState.
        /// </para>
        /// </summary>
        CachedPipelineState = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CACHED_PSO,
        /// <summary>
        /// <para>
        /// Indicates a flags subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is PipelineStateFlags.
        /// </para>
        /// </summary>
        Flags = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS,
        /// <summary>
        /// <para>
        /// Indicates an expanded depth stencil subobject type. This expansion of the depth stencil subobject supports optional depth bounds checking.
        /// </para>
        /// <para>
        /// The corresponding subobject type is DepthStencilDesc1.
        /// </para>
        /// </summary>
        DepthStencil1 = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL1,
        /// <summary>
        /// <para>
        /// Indicates a view instancing subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is D3D12_VIEW_INSTANCING_DESC.
        /// </para>
        /// </summary>
        ViewInstancing = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VIEW_INSTANCING,
        /// <summary>
        /// <para>
        /// Indicates an amplification shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        As = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS,
        /// <summary>
        /// <para>
        /// Indicates a mesh shader subobject type.
        /// </para>
        /// <para>
        /// The corresponding subobject type is ShaderBytecode.
        /// </para>
        /// </summary>
        Ms = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS,
        /// <summary>
        /// <para>
        /// A sentinel value that marks the exclusive upper-bound of valid values this enumeration represents.
        /// </para>
        /// </summary>
        Maxvalid = D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MAX_VALID
    };

    /// <summary>
    /// Defines constants that specify a Direct3D 12 feature or feature set to query about. 
    /// When you want to query for the level to which an adapter supports a feature, 
    /// pass one of these values to ID3D12Device::CheckFeatureSupport.
    /// </summary>
    enum class Feature
    {
        /// <summary>
        /// <para>
        /// Indicates a query for the level of support for basic Direct3D 12 feature options.
        /// </para>
        /// <para>
        /// 
        /// </para>
        /// </summary>
        Options = D3D12_FEATURE_D3D12_OPTIONS,
        Architecture = D3D12_FEATURE_ARCHITECTURE,
        FeatureLevels = D3D12_FEATURE_FEATURE_LEVELS,
        FormatSupport = D3D12_FEATURE_FORMAT_SUPPORT,
        MultisampleQualityLevels = D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
        FormatInfo = D3D12_FEATURE_FORMAT_INFO,
        GpuVirtualAddressSupport = D3D12_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT,
        ShaderModel = D3D12_FEATURE_SHADER_MODEL,
        Options1 = D3D12_FEATURE_D3D12_OPTIONS1,
        ProtectedResourceSessionSupport = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_SUPPORT,
        RootSignature = D3D12_FEATURE_ROOT_SIGNATURE,
        Architecture1 = D3D12_FEATURE_ARCHITECTURE1,
        Options2 = D3D12_FEATURE_D3D12_OPTIONS2,
        ShaderCache = D3D12_FEATURE_SHADER_CACHE,
        CommandQueuePriority = D3D12_FEATURE_COMMAND_QUEUE_PRIORITY,
        Options3 = D3D12_FEATURE_D3D12_OPTIONS3,
        ExistingHeaps = D3D12_FEATURE_EXISTING_HEAPS,
        Options4 = D3D12_FEATURE_D3D12_OPTIONS4,
        Serialization = D3D12_FEATURE_SERIALIZATION,
        CrossNode = D3D12_FEATURE_CROSS_NODE,
        Options5 = D3D12_FEATURE_D3D12_OPTIONS5,
        Displayable = D3D12_FEATURE_DISPLAYABLE,
        Options6 = D3D12_FEATURE_D3D12_OPTIONS6,
        QueryMetaCommand = D3D12_FEATURE_QUERY_META_COMMAND,
        Options7 = D3D12_FEATURE_D3D12_OPTIONS7,
        ProtectedResourceSessionTypeCount = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT,
        ProtectedResourceSessionTypes = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES,
        Options8 = D3D12_FEATURE_D3D12_OPTIONS8,
        Options9 = D3D12_FEATURE_D3D12_OPTIONS9,
        Options10 = D3D12_FEATURE_D3D12_OPTIONS10,
        Options11 = D3D12_FEATURE_D3D12_OPTIONS11,
        Options12 = D3D12_FEATURE_D3D12_OPTIONS12,
        Options13 = D3D12_FEATURE_D3D12_OPTIONS13
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_MIN_PRECISION_SUPPORT
    /// </para>
    /// </summary>
    enum class ShaderMinPrecisionSupport : Int32
    {
        None = D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE,
        Small = D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT,
        Half = D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ShaderMinPrecisionSupport, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_TILED_RESOURCES_TIER
    /// </para>
    /// </summary>
    enum class TiledResourcesTier : Int32
    {
        NotSupported = D3D12_TILED_RESOURCES_TIER_NOT_SUPPORTED,
        Tier1 = D3D12_TILED_RESOURCES_TIER_1,
        Tier2 = D3D12_TILED_RESOURCES_TIER_2,
        Tier3 = D3D12_TILED_RESOURCES_TIER_3,
        Tier4 = D3D12_TILED_RESOURCES_TIER_4
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_BINDING_TIER
    /// </para>
    /// </summary>
    enum class ResourceBindingTier : Int32
    {
        Tier1 = D3D12_RESOURCE_BINDING_TIER_1,
        Tier2 = D3D12_RESOURCE_BINDING_TIER_2,
        Tier3 = D3D12_RESOURCE_BINDING_TIER_3
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_CONSERVATIVE_RASTERIZATION_TIER
    /// </para>
    /// </summary>
    enum class ConservativeRasterizationTier : Int32
    {
        NotSupported = D3D12_CONSERVATIVE_RASTERIZATION_TIER_NOT_SUPPORTED,
        Tier1 = D3D12_CONSERVATIVE_RASTERIZATION_TIER_1,
        Tier2 = D3D12_CONSERVATIVE_RASTERIZATION_TIER_2,
        Tier3 = D3D12_CONSERVATIVE_RASTERIZATION_TIER_3
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_FORMAT_SUPPORT1
    /// </para>
    /// </summary>
    enum class FormatSupport1 : Int32
    {
        None = D3D12_FORMAT_SUPPORT1_NONE,
        Buffer = D3D12_FORMAT_SUPPORT1_BUFFER,
        IAVertexBuffer = D3D12_FORMAT_SUPPORT1_IA_VERTEX_BUFFER,
        IAIndexBuffer = D3D12_FORMAT_SUPPORT1_IA_INDEX_BUFFER,
        SoBuffer = D3D12_FORMAT_SUPPORT1_SO_BUFFER,
        Texture1D = D3D12_FORMAT_SUPPORT1_TEXTURE1D,
        Texture2D = D3D12_FORMAT_SUPPORT1_TEXTURE2D,
        Texture3D = D3D12_FORMAT_SUPPORT1_TEXTURE3D,
        Texturecube = D3D12_FORMAT_SUPPORT1_TEXTURECUBE,
        ShaderLoad = D3D12_FORMAT_SUPPORT1_SHADER_LOAD,
        ShaderSample = D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE,
        ShaderSampleComparison = D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON,
        ShaderSampleMonoText = D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_MONO_TEXT,
        Mip = D3D12_FORMAT_SUPPORT1_MIP,
        RenderTarget = D3D12_FORMAT_SUPPORT1_RENDER_TARGET,
        Blendable = D3D12_FORMAT_SUPPORT1_BLENDABLE,
        DepthStencil = D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL,
        MultisampleResolve = D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RESOLVE,
        Display = D3D12_FORMAT_SUPPORT1_DISPLAY,
        CastWithinBitLayout = D3D12_FORMAT_SUPPORT1_CAST_WITHIN_BIT_LAYOUT,
        MultisampleRendertarget = D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET,
        MultisampleLoad = D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD,
        ShaderGather = D3D12_FORMAT_SUPPORT1_SHADER_GATHER,
        BackBuffer_cast = D3D12_FORMAT_SUPPORT1_BACK_BUFFER_CAST,
        TypedUnorderedAccessView = D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW,
        ShaderGatherComparison = D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON,
        DecoderOutput = D3D12_FORMAT_SUPPORT1_DECODER_OUTPUT,
        VideoProcessorOutput = D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_OUTPUT,
        VideoProcessorInput = D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_INPUT,
        VideoEncoder = D3D12_FORMAT_SUPPORT1_VIDEO_ENCODER
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FormatSupport1, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_FORMAT_SUPPORT2
    /// </para>
    /// </summary>
    enum class FormatSupport2 : Int32
    {
        None = D3D12_FORMAT_SUPPORT2_NONE,
        UavAtomicAdd = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD,
        UavAtomicBitwiseOps = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS,
        UavAtomicCompare_store_or_compare_exchange = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE,
        UavAtomicExchange = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE,
        UavAtomicSignedMinOrMax = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX,
        UavAtomicUnsignedMinOrMax = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX,
        UavTypedLoad = D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD,
        UavTypedStore = D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE,
        OutputMergerLogicOp = D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP,
        Tiled = D3D12_FORMAT_SUPPORT2_TILED,
        MultiplaneOverlay = D3D12_FORMAT_SUPPORT2_MULTIPLANE_OVERLAY,
        SamplerFeedback = D3D12_FORMAT_SUPPORT2_SAMPLER_FEEDBACK
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FormatSupport2, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS
    /// </para>
    /// </summary>
    enum class MultisampleQualityLevelFlags : Int32
    {
        None = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE,
        TiledResource = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_TILED_RESOURCE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MultisampleQualityLevelFlags, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_CROSS_NODE_SHARING_TIER
    /// </para>
    /// </summary>
    enum class CrossNodeSharingTier : Int32
    {
        NotSupported = D3D12_CROSS_NODE_SHARING_TIER_NOT_SUPPORTED,
        Tier1Emulated = D3D12_CROSS_NODE_SHARING_TIER_1_EMULATED,
        Tier1 = D3D12_CROSS_NODE_SHARING_TIER_1,
        Tier2 = D3D12_CROSS_NODE_SHARING_TIER_2,
        Tier3 = D3D12_CROSS_NODE_SHARING_TIER_3
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_HEAP_TIER
    /// </para>
    /// </summary>
    enum class ResourceHeapTier : Int32
    {
        Tier1 = D3D12_RESOURCE_HEAP_TIER_1,
        Tier2 = D3D12_RESOURCE_HEAP_TIER_2
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER
    /// </para>
    /// </summary>
    enum class ProgrammableSamplePositionsTier : Int32
    {
        NotSupported = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_NOT_SUPPORTED,
        Tier1 = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_1,
        Tier2 = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VIEW_INSTANCING_TIER
    /// </para>
    /// </summary>
    enum class ViewInstancingTier : Int32
    {
        NotSupported = D3D12_VIEW_INSTANCING_TIER_NOT_SUPPORTED,
        Tier1 = D3D12_VIEW_INSTANCING_TIER_1,
        Tier2 = D3D12_VIEW_INSTANCING_TIER_2,
        Tier3 = D3D12_VIEW_INSTANCING_TIER_3
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options
    {
        _Out_  BOOL DoublePrecisionFloatShaderOps;
        _Out_  BOOL OutputMergerLogicOp;
        _Out_  ShaderMinPrecisionSupport MinPrecisionSupport;
        _Out_  TiledResourcesTier TiledResourcesTier;
        _Out_  ResourceBindingTier ResourceBindingTier;
        _Out_  BOOL PSSpecifiedStencilRefSupported;
        _Out_  BOOL TypedUAVLoadAdditionalFormats;
        _Out_  BOOL ROVsSupported;
        _Out_  ConservativeRasterizationTier ConservativeRasterizationTier;
        _Out_  UInt32 MaxGPUVirtualAddressBitsPerResource;
        _Out_  BOOL StandardSwizzle64KBSupported;
        _Out_  D3D12::CrossNodeSharingTier CrossNodeSharingTier;
        _Out_  BOOL CrossAdapterRowMajorTextureSupported;
        _Out_  BOOL VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation;
        _Out_  D3D12::ResourceHeapTier ResourceHeapTier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS1
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options1
    {
        _Out_  BOOL WaveOps;
        _Out_  UInt32 WaveLaneCountMin;
        _Out_  UInt32 WaveLaneCountMax;
        _Out_  UInt32 TotalLaneCount;
        _Out_  BOOL ExpandedComputeResourceStates;
        _Out_  BOOL Int64ShaderOps;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS2
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options2
    {
        _Out_  BOOL DepthBoundsTestSupported;
        _Out_  D3D12::ProgrammableSamplePositionsTier ProgrammableSamplePositionsTier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS2 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D_ROOT_SIGNATURE_VERSION
    /// </para>
    /// </summary>
    enum class RootSignatureVersion : Int32
    {
        Version1 = D3D_ROOT_SIGNATURE_VERSION_1,
        Version1_0 = D3D_ROOT_SIGNATURE_VERSION_1_0,
        Version1_1 = D3D_ROOT_SIGNATURE_VERSION_1_1
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_ROOT_SIGNATURE
    /// </para>
    /// </summary>
    struct FeatureDataRootSignature
    {
        _Inout_ RootSignatureVersion HighestVersion;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_ROOT_SIGNATURE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_ARCHITECTURE
    /// </para>
    /// </summary>
    struct FeatureDataArchitecture
    {
        _In_  UInt32 NodeIndex;
        _Out_  BOOL TileBasedRenderer;
        _Out_  BOOL UMA;
        _Out_  BOOL CacheCoherentUMA;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( FeatureDataArchitecture );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_ARCHITECTURE1
    /// </para>
    /// </summary>
    struct FeatureDataArchitecture1 : public FeatureDataArchitecture
    {
        _Out_  BOOL IsolatedMMU;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_ARCHITECTURE1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_FEATURE_LEVELS
    /// </para>
    /// </summary>
    struct FeatureDataFeatureLevels
    {
        _In_  UInt32 NumFeatureLevels;
        _In_reads_( NumFeatureLevels ) const D3D_FEATURE_LEVEL* pFeatureLevelsRequested;
        _Out_  D3D_FEATURE_LEVEL MaxSupportedFeatureLevel;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_FEATURE_LEVELS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D_SHADER_MODEL
    /// </para>
    /// </summary>
    using ShaderModel = D3D_SHADER_MODEL;

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_SHADER_MODEL
    /// </para>
    /// </summary>
    using FeatureDataShaderModel = D3D12_FEATURE_DATA_SHADER_MODEL;

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_FORMAT_SUPPORT
    /// </para>
    /// </summary>
    struct FeatureDataFormatSupport
    {
        _In_  DXGI::Format Format;
        _Out_  FormatSupport1 Support1;
        _Out_  FormatSupport2 Support2;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_FORMAT_SUPPORT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS
    /// </para>
    /// </summary>
    struct FeatureDataMultiSampleQualityLevels
    {
        _In_  DXGI::Format Format;
        _In_  UInt32 SampleCount;
        _In_  MultisampleQualityLevelFlags Flags;
        _Out_  UInt32 NumQualityLevels;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_FORMAT_INFO
    /// </para>
    /// </summary>
    struct FeatureDataFormatInfo
    {
        DXGI::Format Format;
        UINT8 PlaneCount;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_FORMAT_INFO );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT
    /// </para>
    /// </summary>
    struct FeatureDataGpuVirtualAddressSupport
    {
        UInt32 MaxGPUVirtualAddressBitsPerResource;
        UInt32 MaxGPUVirtualAddressBitsPerProcess;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_CACHE_SUPPORT_FLAGS
    /// </para>
    /// </summary>
    enum class ShaderCacheSupportFlags : Int32
    {
        None = D3D12_SHADER_CACHE_SUPPORT_NONE,
        SinglePso = D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO,
        Library = D3D12_SHADER_CACHE_SUPPORT_LIBRARY,
        AutomaticInprocCache = D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE,
        AutomaticDiskCache = D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE,
        DriverManagedCache = D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE,
        ShaderControlClear = D3D12_SHADER_CACHE_SUPPORT_SHADER_CONTROL_CLEAR,
        ShaderSessionSelete = D3D12_SHADER_CACHE_SUPPORT_SHADER_SESSION_DELETE
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_SHADER_CACHE
    /// </para>
    /// </summary>
    struct FeatureDataShaderCache
    {
        _Out_  ShaderCacheSupportFlags SupportFlags;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_SHADER_CACHE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY
    /// </para>
    /// </summary>
    struct FeatureDataCommandQueuePriority
    {
        _In_  D3D12::CommandListType CommandListType;
        _In_  UInt32 Priority;
        _Out_  BOOL PriorityForTypeIsSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_COMMAND_LIST_SUPPORT_FLAGS
    /// </para>
    /// </summary>
    enum class CommandListSupportFlags : Int32
    {
        None = D3D12_COMMAND_LIST_SUPPORT_FLAG_NONE,
        Direct = D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT,
        Bundle = D3D12_COMMAND_LIST_SUPPORT_FLAG_BUNDLE,
        Compute = D3D12_COMMAND_LIST_SUPPORT_FLAG_COMPUTE,
        Copy = D3D12_COMMAND_LIST_SUPPORT_FLAG_COPY,
        VideoDecode = D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_DECODE,
        VideoProcess = D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_PROCESS,
        VideoEncode = D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_ENCODE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommandListSupportFlags, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS3
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options3
    {
        _Out_  BOOL CopyQueueTimestampQueriesSupported;
        _Out_  BOOL CastingFullyTypedFormatSupported;
        _Out_  CommandListSupportFlags WriteBufferImmediateSupportFlags;
        _Out_  D3D12::ViewInstancingTier ViewInstancingTier;
        _Out_  BOOL BarycentricsSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS3 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_EXISTING_HEAPS
    /// </para>
    /// </summary>
    struct FeatureDataExistingHeaps
    {
        _Out_  BOOL Supported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_EXISTING_HEAPS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER
    /// </para>
    /// </summary>
    enum class SharedResourceCompatibilityTier : Int32
    {
        Tier0 = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0,
        Tier1 = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1,
        Tier2 = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_2
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_DISPLAYABLE
    /// </para>
    /// </summary>
    struct FeatureDataDisplayable
    {
        _Out_  BOOL DisplayableTexture;
        _Out_  D3D12::SharedResourceCompatibilityTier SharedResourceCompatibilityTier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_DISPLAYABLE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS4
    /// </para>
    /// </summary>
    struct D3D12_FEATURE_DATA_D3D12_OPTIONS4
    {
        _Out_  BOOL MSAA64KBAlignedTextureSupported;
        _Out_  D3D12::SharedResourceCompatibilityTier SharedResourceCompatibilityTier;
        _Out_  BOOL Native16BitShaderOpsSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS4 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_HEAP_SERIALIZATION_TIER
    /// </para>
    /// </summary>
    enum class HeapSerializationTier : Int32
    {
        Tier1 = D3D12_HEAP_SERIALIZATION_TIER_0,
        Tier10 = D3D12_HEAP_SERIALIZATION_TIER_10
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_SERIALIZATION
    /// </para>
    /// </summary>
    struct FeatureDataSerialization
    {
        _In_  UInt32 NodeIndex;
        _Out_  D3D12::HeapSerializationTier HeapSerializationTier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_SERIALIZATION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_CROSS_NODE
    /// </para>
    /// </summary>
    struct FeatureDataCrossNode
    {
        CrossNodeSharingTier SharingTier;
        BOOL AtomicShaderInstructions;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_CROSS_NODE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_TIER
    /// </para>
    /// </summary>
    enum class RenderPassTier : Int32
    {
        Tier0 = D3D12_RENDER_PASS_TIER_0,
        Tier1 = D3D12_RENDER_PASS_TIER_1,
        Tier2 = D3D12_RENDER_PASS_TIER_2
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_TIER
    /// </para>
    /// </summary>
    enum class RaytracingTier : Int32
    {
        Notsupported = D3D12_RAYTRACING_TIER_NOT_SUPPORTED,
        Tier1_0 = D3D12_RAYTRACING_TIER_1_0,
        Tier1_1 = D3D12_RAYTRACING_TIER_1_1
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS5
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options5
    {
        _Out_  BOOL SRVOnlyTiledResourceTier3;
        _Out_  RenderPassTier RenderPassesTier;
        _Out_  RaytracingTier RaytracingTier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS5 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VARIABLE_SHADING_RATE_TIER
    /// </para>
    /// </summary>
    enum class VariableShadingRateTier : Int32
    {
        NotSupported = D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED,
        Tier1 = D3D12_VARIABLE_SHADING_RATE_TIER_1,
        Tier2 = D3D12_VARIABLE_SHADING_RATE_TIER_2
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS6
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options6
    {
        _Out_  BOOL AdditionalShadingRatesSupported;
        _Out_  BOOL PerPrimitiveShadingRateSupportedWithViewportIndexing;
        _Out_  VariableShadingRateTier VariableShadingRateTier;
        _Out_  UInt32 ShadingRateImageTileSize;
        _Out_  BOOL BackgroundProcessingSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS6 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MESH_SHADER_TIER
    /// </para>
    /// </summary>
    enum class MeshShaderTier : Int32
    {
        NotSupported = D3D12_MESH_SHADER_TIER_NOT_SUPPORTED,
        Tier1 = D3D12_MESH_SHADER_TIER_1
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SAMPLER_FEEDBACK_TIER
    /// </para>
    /// </summary>
    enum class SamplerFeedbackTier : Int32
    {
        NotSupported = D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED,
        Tier0_9 = D3D12_SAMPLER_FEEDBACK_TIER_0_9,
        Tier1_0 = D3D12_SAMPLER_FEEDBACK_TIER_1_0
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS7
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options7
    {
        _Out_  D3D12::MeshShaderTier MeshShaderTier;
        _Out_  D3D12::SamplerFeedbackTier SamplerFeedbackTier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS7 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_QUERY_META_COMMAND
    /// </para>
    /// </summary>
    struct FeatureDataQueryMetaCommand
    {
        _In_  Guid CommandId;
        _In_  UInt32 NodeMask;
        _Field_size_bytes_full_opt_( QueryInputDataSizeInBytes )  const void* pQueryInputData;
        _In_  SIZE_T QueryInputDataSizeInBytes;
        _Field_size_bytes_full_( QueryOutputDataSizeInBytes )  void* pQueryOutputData;
        _In_  SIZE_T QueryOutputDataSizeInBytes;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_QUERY_META_COMMAND );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS8
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options8
    {
        _Out_  BOOL UnalignedBlockTexturesSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS8 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_WAVE_MMA_TIER
    /// </para>
    /// </summary>
    enum class WaveMmaTier : Int32
    {
        NotSupported = D3D12_WAVE_MMA_TIER_NOT_SUPPORTED,
        Tier1_0 = D3D12_WAVE_MMA_TIER_1_0
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS9
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options9
    {
        _Out_  BOOL MeshShaderPipelineStatsSupported;
        _Out_  BOOL MeshShaderSupportsFullRangeRenderTargetArrayIndex;
        _Out_  BOOL AtomicInt64OnTypedResourceSupported;
        _Out_  BOOL AtomicInt64OnGroupSharedSupported;
        _Out_  BOOL DerivativesInMeshAndAmplificationShadersSupported;
        _Out_  WaveMmaTier WaveMMATier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS9 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS10
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options10
    {
        _Out_  BOOL VariableRateShadingSumCombinerSupported;
        _Out_  BOOL MeshShaderPerPrimitiveShadingRateSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS10 );

    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS11
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options11
    {
        _Out_  BOOL AtomicInt64OnDescriptorHeapResourceSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS11 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TRI_STATE
    /// </para>
    /// </summary>
    enum class TriState : Int32
    {
        Unknown = D3D12_TRI_STATE_UNKNOWN,
        False = D3D12_TRI_STATE_FALSE,
        True = D3D12_TRI_STATE_TRUE
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS12
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options12
    {
        _Out_  TriState MSPrimitivesPipelineStatisticIncludesCulledPrimitives;
        _Out_  BOOL EnhancedBarriersSupported;
        _Out_  BOOL RelaxedFormatCastingSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS12 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_D3D12_OPTIONS13
    /// </para>
    /// </summary>
    struct FeatureDataD3D12Options13
    {
        _Out_  BOOL UnrestrictedBufferTextureCopyPitchSupported;
        _Out_  BOOL UnrestrictedVertexElementAlignmentSupported;
        _Out_  BOOL InvertedViewportHeightFlipsYSupported;
        _Out_  BOOL InvertedViewportDepthFlipsZSupported;
        _Out_  BOOL TextureCopyBetweenDimensionsSupported;
        _Out_  BOOL AlphaBlendFactorSupported;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_D3D12_OPTIONS13 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_ALLOCATION_INFO
    /// </para>
    /// </summary>
    struct ResourceAllocationInfo
    {
        UInt64 SizeInBytes;
        UInt64 Alignment;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_ALLOCATION_INFO );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_ALLOCATION_INFO1
    /// </para>
    /// </summary>
    struct ResourceAllocationInfo1
    {
        UInt64 Offset;
        UInt64 Alignment;
        UInt64 SizeInBytes;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_ALLOCATION_INFO1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_HEAP_TYPE
    /// </para>
    /// </summary>
    enum class HeapType : Int32
    {
        Default = D3D12_HEAP_TYPE_DEFAULT,
        Upload = D3D12_HEAP_TYPE_UPLOAD,
        ReadBack = D3D12_HEAP_TYPE_READBACK,
        Custom = D3D12_HEAP_TYPE_CUSTOM
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_CPU_PAGE_PROPERTY
    /// </para>
    /// </summary>
    enum class CpuPageProperty : Int32
    {
        Unknown = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
        NotAvailable = D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE,
        WriteCombine = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE,
        WriteBack = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MEMORY_POOL
    /// </para>
    /// </summary>
    enum class MemoryPool : Int32
    {
        Unknown = D3D12_MEMORY_POOL_UNKNOWN,
        L0 = D3D12_MEMORY_POOL_L0,
        L1 = D3D12_MEMORY_POOL_L1
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_HEAP_PROPERTIES
    /// </para>
    /// </summary>
    struct HeapProperties
    {
        HeapType Type = HeapType::Default;
        CpuPageProperty CPUPageProperty = CpuPageProperty::Unknown;
        MemoryPool MemoryPoolPreference = MemoryPool::Unknown;
        UInt32 CreationNodeMask = 0;
        UInt32 VisibleNodeMask = 0;

        HeapProperties( ) = default;

        HeapProperties( HeapType type, UInt32 creationNodeMask = 1, UInt32 visibleNodeMask = 1 )
            : Type( type ), CreationNodeMask( creationNodeMask ), VisibleNodeMask( visibleNodeMask )
        { }

        HeapProperties( HeapType type, CpuPageProperty cpuPageProperty, MemoryPool memoryPoolPreference,UInt32 creationNodeMask = 1, UInt32 visibleNodeMask = 1 )
            : Type( type ), CPUPageProperty( cpuPageProperty ), MemoryPoolPreference( memoryPoolPreference ), CreationNodeMask( creationNodeMask ), VisibleNodeMask( visibleNodeMask )
        {
        }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_HEAP_PROPERTIES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_HEAP_PROPERTIES
    /// </para>
    /// </summary>
    enum class HeapFlags : Int32
    {
        None = D3D12_HEAP_FLAG_NONE,
        Shared = D3D12_HEAP_FLAG_SHARED,
        DenyBuffers = D3D12_HEAP_FLAG_DENY_BUFFERS,
        AllowDisplay = D3D12_HEAP_FLAG_ALLOW_DISPLAY,
        SharedCrossAdapter = D3D12_HEAP_FLAG_SHARED_CROSS_ADAPTER,
        DenyRtDsTextures = D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES,
        DenyNonRtDsTextures = D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES,
        HardwareProtected = D3D12_HEAP_FLAG_HARDWARE_PROTECTED,
        AllowWriteWatch = D3D12_HEAP_FLAG_ALLOW_WRITE_WATCH,
        AllowShaderAtomics = D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS,
        CreateNotResident = D3D12_HEAP_FLAG_CREATE_NOT_RESIDENT,
        CreateNotZeroed = D3D12_HEAP_FLAG_CREATE_NOT_ZEROED,
        AllowAllBuffersAndTextures = D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES,
        AllowOnlyBuffers = D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS,
        AllowOnlyNonRtDsTextures = D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES,
        AllowOnlyRtDsTextures = D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( HeapFlags, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_HEAP_DESC
    /// </para>
    /// </summary>
    struct HeapDesc
    {
        UInt64 SizeInBytes;
        HeapProperties Properties;
        UInt64 Alignment;
        HeapFlags Flags;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_HEAP_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_DIMENSION
    /// </para>
    /// </summary>
    enum class ResourceDimension : Int32
    {
        Unknown = D3D12_RESOURCE_DIMENSION_UNKNOWN,
        Buffer = D3D12_RESOURCE_DIMENSION_BUFFER,
        Texture1D = D3D12_RESOURCE_DIMENSION_TEXTURE1D,
        Texture2D = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        Texture3D = D3D12_RESOURCE_DIMENSION_TEXTURE3D
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXTURE_LAYOUT
    /// </para>
    /// </summary>
    enum class TextureLayout : Int32
    {
        Unknown = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        RowMajor = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        Undefined64KbSwizzle = D3D12_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE,
        Standard64KbSwizzle = D3D12_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_FLAGS
    /// </para>
    /// </summary>
    enum class ResourceFlags : Int32
    {
        None = D3D12_RESOURCE_FLAG_NONE,
        AllowRenderTarget = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET,
        AllowDepthStencil = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,
        AllowUnorderedAccess = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
        DenyShaderResource = D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE,
        AllowCrossAdapter = D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER,
        AllowSimultaneousAccess = D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS,
        VideoDecodeReferenceOnly = D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY,
        VideoEncodeReferenceOnly = D3D12_RESOURCE_FLAG_VIDEO_ENCODE_REFERENCE_ONLY,
        RaytracingAccelerationStructure = D3D12_RESOURCE_FLAG_RAYTRACING_ACCELERATION_STRUCTURE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ResourceFlags, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_MIP_REGION
    /// </para>
    /// </summary>
    struct MipRegion
    {
        UInt32 Width = 0;
        UInt32 Height = 0;
        UInt32 Depth = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_MIP_REGION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_DESC
    /// </para>
    /// </summary>
    struct ResourceDesc
    {
        ResourceDimension Dimension = ResourceDimension::Unknown;
        UInt64 Alignment = 0;
        UInt64 Width = 0;
        UInt32 Height = 0;
        UInt16 DepthOrArraySize = 0;
        UInt16 MipLevels = 0;
        DXGI::Format Format = DXGI::Format::Unknown;
        DXGI::SampleDesc SampleDesc;
        TextureLayout Layout = TextureLayout::Unknown;
        ResourceFlags Flags = ResourceFlags::None;

        ResourceDesc( ) noexcept = default;

        ResourceDesc( const D3D12_RESOURCE_DESC& other ) noexcept
            : ResourceDesc( reinterpret_cast<const ResourceDesc& >( other ) )
        { }

        ResourceDesc(
            ResourceDimension dimension,
            UInt64 alignment,
            UInt64 width,
            UInt32 height,
            UInt16 depthOrArraySize,
            UInt16 mipLevels,
            DXGI::Format format,
            UInt32 sampleCount,
            UInt32 sampleQuality,
            TextureLayout layout,
            ResourceFlags flags ) noexcept
            : Dimension( dimension ),
              Alignment( alignment ),
              Width( width ),
              Height( height ),
              DepthOrArraySize( depthOrArraySize ),
              MipLevels( mipLevels ),
              Format( format ),
              SampleDesc( sampleCount, sampleQuality ),
              Layout( layout ),
              Flags( flags )
        { }

        ResourceDesc(
            UInt64 width,
            ResourceFlags flags = ResourceFlags::None,
            UInt64 alignment = 0 ) noexcept
            : ResourceDesc( ResourceDimension::Buffer, alignment, width, 1, 1, 1,
                DXGI::Format::Unknown, 1, 0, TextureLayout::RowMajor, flags )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_DESC1
    /// </para>
    /// </summary>
    struct ResourceDesc1 : public ResourceDesc
    {
        MipRegion SamplerFeedbackMipRegion;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_DESC1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEPTH_STENCIL_VALUE
    /// </para>
    /// </summary>
    struct DepthStencilValue
    {
        FLOAT Depth;
        UINT8 Stencil;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEPTH_STENCIL_VALUE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_CLEAR_VALUE
    /// </para>
    /// </summary>
    struct ClearValue
    {
        DXGI::Format Format;
        union
        {
            FLOAT Color[ 4 ];
            DepthStencilValue DepthStencil;
        };

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_CLEAR_VALUE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RANGE
    /// </para>
    /// </summary>
    struct Range
    {
        SIZE_T Begin = 0;
        SIZE_T End = 0;

        Range( ) = default;
        Range( SIZE_T begin, SIZE_T end )
            : Begin(begin), End(end)
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RANGE );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_RANGE_UINT64
    /// </para>
    /// </summary>
    struct RangeUInt64
    {
        UInt64 Begin;
        UInt64 End;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RANGE_UINT64 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SUBRESOURCE_RANGE_UINT64
    /// </para>
    /// </summary>
    struct SubresourceRangeUInt64
    {
        UInt32 Subresource;
        RangeUInt64 Range;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SUBRESOURCE_RANGE_UINT64 );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_SUBRESOURCE_INFO
    /// </para>
    /// </summary>
    struct SubresourceInfo
    {
        UInt64 Offset;
        UInt32 RowPitch;
        UInt32 DepthPitch;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SUBRESOURCE_INFO );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TILED_RESOURCE_COORDINATE
    /// </para>
    /// </summary>
    struct TiledResourceCoordinate
    {
        UInt32 X;
        UInt32 Y;
        UInt32 Z;
        UInt32 Subresource;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TILED_RESOURCE_COORDINATE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TILE_REGION_SIZE
    /// </para>
    /// </summary>
    struct TileRegionSize
    {
        UInt32 NumTiles;
        BOOL UseBox;
        UInt32 Width;
        UINT16 Height;
        UINT16 Depth;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TILE_REGION_SIZE );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_TILE_RANGE_FLAGS
    /// </para>
    /// </summary>
    enum class TileRangeFlags : UInt32
    {
        None = D3D12_TILE_RANGE_FLAG_NONE,
        Null = D3D12_TILE_RANGE_FLAG_NULL,
        Skip = D3D12_TILE_RANGE_FLAG_SKIP,
        ReuseSingleTile = D3D12_TILE_RANGE_FLAG_REUSE_SINGLE_TILE
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SUBRESOURCE_TILING
    /// </para>
    /// </summary>
    struct SubresourceTiling
    {
        UInt32 WidthInTiles;
        UINT16 HeightInTiles;
        UINT16 DepthInTiles;
        UInt32 StartTileIndexInOverallResource;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SUBRESOURCE_TILING );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TILE_SHAPE
    /// </para>
    /// </summary>
    struct TileShape
    {
        UInt32 WidthInTexels;
        UInt32 HeightInTexels;
        UInt32 DepthInTexels;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TILE_SHAPE );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_PACKED_MIP_INFO
    /// </para>
    /// </summary>
    struct PackedMipInfo
    {
        UINT8 NumStandardMips;
        UINT8 NumPackedMips;
        UInt32 NumTilesForPackedMips;
        UInt32 StartTileIndexInOverallResource;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PACKED_MIP_INFO );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_TILE_MAPPING_FLAGS
    /// </para>
    /// </summary>
    enum class TileMappingFlags : Int32
    {
        None = D3D12_TILE_MAPPING_FLAG_NONE,
        NoHazard = D3D12_TILE_MAPPING_FLAG_NO_HAZARD
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TileMappingFlags, Int32 );


    /// <summary>
    /// <para>
    /// Alias for D3D12_TILE_COPY_FLAGS
    /// </para>
    /// </summary>
    enum class TileCopyFlags : Int32
    {
        None = D3D12_TILE_COPY_FLAG_NONE,
        NoHazard = D3D12_TILE_COPY_FLAG_NO_HAZARD,
        LinearBufferToSwizzledTiledResource = D3D12_TILE_COPY_FLAG_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE,
        SwizzledTiledResourceToLinearBuffer = D3D12_TILE_COPY_FLAG_SWIZZLED_TILED_RESOURCE_TO_LINEAR_BUFFER
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TileCopyFlags, Int32 );


    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_STATES
    /// </para>
    /// </summary>
    enum class ResourceStates : UInt32
    {
        Common = D3D12_RESOURCE_STATE_COMMON,
        VertexAndConstantBuffer = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
        IndexBuffer = D3D12_RESOURCE_STATE_INDEX_BUFFER,
        RenderTarget = D3D12_RESOURCE_STATE_RENDER_TARGET,
        UnorderedAccess = D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
        DepthWrite = D3D12_RESOURCE_STATE_DEPTH_WRITE,
        DepthRead = D3D12_RESOURCE_STATE_DEPTH_READ,
        NonPixelShaderResource = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
        PixelShaderResource = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        StreamOut = D3D12_RESOURCE_STATE_STREAM_OUT,
        IndirectArgument = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT,
        CopyDest = D3D12_RESOURCE_STATE_COPY_DEST,
        CopySource = D3D12_RESOURCE_STATE_COPY_SOURCE,
        ResolveDest = D3D12_RESOURCE_STATE_RESOLVE_DEST,
        ResolveSource = D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
        RaytracingAccelerationStructure = D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE,
        ShadingRateSource = D3D12_RESOURCE_STATE_SHADING_RATE_SOURCE,
        GenericRead = D3D12_RESOURCE_STATE_GENERIC_READ,
        AllShaderResource = D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE,
        Present = D3D12_RESOURCE_STATE_PRESENT,
        Predication = D3D12_RESOURCE_STATE_PREDICATION,
        VideoDecodeRead = D3D12_RESOURCE_STATE_VIDEO_DECODE_READ,
        VideoDecodeWrite = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
        VideoProcessRead = D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ,
        VideoProcessWrite = D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE,
        VideoEncodeRead = D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ,
        VideoEncodeWrite = D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ResourceStates, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_BARRIER_TYPE
    /// </para>
    /// </summary>
    enum class ResourceBarrierType : Int32
    {
        Transition = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        Aliasing = D3D12_RESOURCE_BARRIER_TYPE_ALIASING,
        UAV = D3D12_RESOURCE_BARRIER_TYPE_UAV,
        UnorderedAccessView = UAV
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_TRANSITION_BARRIER
    /// </para>
    /// </summary>
    struct ResourceTransitionBarrier
    {
        ID3D12Resource* pResource = nullptr;
        UInt32 Subresource = 0;
        ResourceStates StateBefore = ResourceStates::Common;
        ResourceStates StateAfter = ResourceStates::Common;

        ResourceTransitionBarrier( ) noexcept = default;

        ResourceTransitionBarrier( ID3D12Resource* resource, UInt32 subresource, ResourceStates stateBefore, ResourceStates stateAfter ) noexcept
            : pResource( resource ), Subresource( subresource ), StateBefore( stateBefore ), StateAfter( stateAfter )
        { }

        ResourceTransitionBarrier( const Resource& resource, UInt32 subresource, ResourceStates stateBefore, ResourceStates stateAfter ) noexcept;


        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_TRANSITION_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_ALIASING_BARRIER
    /// </para>
    /// </summary>
    struct ResourceAliasingBarrier
    {
        ID3D12Resource* pResourceBefore = nullptr;
        ID3D12Resource* pResourceAfter = nullptr;

        ResourceAliasingBarrier( ) noexcept = default;

        ResourceAliasingBarrier( ID3D12Resource* resourceBefore, ID3D12Resource* resourceAfter ) noexcept
            : pResourceBefore( resourceBefore ), pResourceAfter( resourceAfter )
        { }

        ResourceAliasingBarrier( const Resource& resourceBefore, const Resource& resourceAfter ) noexcept;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_ALIASING_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_UAV_BARRIER
    /// </para>
    /// </summary>
    struct ResourceUAVBarrier
    {
        ID3D12Resource* pResource = nullptr;

        ResourceUAVBarrier( ) noexcept = default;

        explicit ResourceUAVBarrier( ID3D12Resource* resource ) noexcept
            : pResource( resource )
        { }
        explicit ResourceUAVBarrier( const Resource& resource ) noexcept;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_UAV_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOURCE_BARRIER_FLAGS
    /// </para>
    /// </summary>
    enum class ResourceBarrierFlags : Int32
    {
        None = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        BeginOnly = D3D12_RESOURCE_BARRIER_FLAG_BEGIN_ONLY,
        EndOnly = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ResourceBarrierFlags, Int32 );


    /// <summary>
    /// <para>
    /// Describes a resource barrier (transition in resource use).
    /// </para>
    /// <para>
    /// Alias for D3D12_RESOURCE_BARRIER
    /// </para>
    /// </summary>
    struct ResourceBarrier
    {
        ResourceBarrierType Type = ResourceBarrierType::Transition;
        ResourceBarrierFlags Flags = ResourceBarrierFlags::None;
        union
        {
            ResourceTransitionBarrier Transition;
            ResourceAliasingBarrier Aliasing;
            ResourceUAVBarrier UAV;
        };

        ResourceBarrier() noexcept
            : Transition{}
        { }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition of subresources between different usages.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="stateBefore">
        /// The "before" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="stateAfter">
        /// The "after" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource for the transition. Defaults to the 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES flag ( 0xffffffff ) which 
        /// transitions all subresources in a resource at the same time.
        /// </param>
        ResourceBarrier( ID3D12Resource* resource, ResourceStates stateBefore, ResourceStates stateAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None, UInt32 subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES ) noexcept
            : Type( ResourceBarrierType::Transition ), Flags( flags ), Transition( resource, subresource, stateBefore, stateAfter )
        { }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition of subresources between different usages.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="stateBefore">
        /// The "before" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="stateAfter">
        /// The "after" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource for the transition. Defaults to the 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES flag ( 0xffffffff ) which 
        /// transitions all subresources in a resource at the same time.
        /// </param>
        ResourceBarrier( const Resource& resource, ResourceStates stateBefore, ResourceStates stateAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None, UInt32 subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES ) noexcept
            : Type( ResourceBarrierType::Transition ), Flags( flags ), Transition( resource, subresource, stateBefore, stateAfter )
        { }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition 
        /// between usages of two different resources that have 
        /// mappings into the same heap.
        /// </summary>
        /// <param name="resourceBefore">
        /// Represents the before resource used in the transition.
        /// </param>
        /// <param name="resourceAfter">
        /// Represents the after resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <remarks>
        /// Both the before and the after resources can be specified 
        /// or one or both resources can be NULL, which indicates that 
        /// any placed or reserved resource could cause aliasing.
        /// </remarks>
        ResourceBarrier( ID3D12Resource* resourceBefore, ID3D12Resource* resourceAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
            : Type( ResourceBarrierType::Aliasing ), Flags( flags ), Aliasing( resourceBefore, resourceAfter )
        { }
        
        /// <summary>
        /// Creates a ResourceBarrier that describes the transition 
        /// between usages of two different resources that have 
        /// mappings into the same heap.
        /// </summary>
        /// <param name="resourceBefore">
        /// Represents the before resource used in the transition.
        /// </param>
        /// <param name="resourceAfter">
        /// Represents the after resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <remarks>
        /// Both the before and the after resources can be specified 
        /// or one or both resources can be NULL, which indicates that 
        /// any placed or reserved resource could cause aliasing.
        /// </remarks>
        ResourceBarrier( const Resource& resourceBefore, const Resource& resourceAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
            : Type( ResourceBarrierType::Aliasing ), Flags( flags ), Aliasing( resourceBefore, resourceAfter )
        { }

        /// <summary>
        /// Creates a ResourceBarrier representing a resource for 
        /// which all UAV accesses must complete before any future UAV accesses can begin.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        explicit ResourceBarrier( ID3D12Resource* resource, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
            : Type( ResourceBarrierType::UAV ), Flags( flags ), UAV( resource )
        { }
        /// <summary>
        /// Creates a ResourceBarrier representing a resource for 
        /// which all UAV accesses must complete before any future UAV accesses can begin.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        explicit ResourceBarrier( const Resource& resource, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
            : Type( ResourceBarrierType::UAV ), Flags( flags ), UAV( resource )
        { }
        


        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RESOURCE_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SUBRESOURCE_FOOTPRINT
    /// </para>
    /// </summary>
    struct SubresourceFootprint
    {
        DXGI::Format Format = DXGI::Format::Unknown;
        UInt32 Width = 0;
        UInt32 Height = 0;
        UInt32 Depth = 0;
        UInt32 RowPitch = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SUBRESOURCE_FOOTPRINT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PLACED_SUBRESOURCE_FOOTPRINT
    /// </para>
    /// </summary>
    struct PlacedSubresourceFootprint
    {
        UInt64 Offset = 0;
        SubresourceFootprint Footprint;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PLACED_SUBRESOURCE_FOOTPRINT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXTURE_COPY_TYPE
    /// </para>
    /// </summary>
    enum class TextureCopyType : Int32
    {
        SubresourceIndex = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
        PlacedFootprint = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXTURE_COPY_LOCATION
    /// </para>
    /// </summary>
    struct TextureCopyLocation
    {
        ID3D12Resource* pResource = nullptr;
        TextureCopyType Type = TextureCopyType::SubresourceIndex;
        union
        {
            PlacedSubresourceFootprint PlacedFootprint;
            UInt32 SubresourceIndex;
        };

        TextureCopyLocation( )
            : PlacedFootprint{}
        { }

        explicit TextureCopyLocation( const TextureCopyLocation& other ) 
            : pResource( other.pResource ), Type( other.Type ), PlacedFootprint( other.PlacedFootprint )
        { }
        TextureCopyLocation( _In_ ID3D12Resource* resource )
            : pResource( resource ), PlacedFootprint{}
        { }
        TextureCopyLocation( const Resource& resource );

        TextureCopyLocation( _In_ ID3D12Resource* resource, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& footprint )
            : pResource( resource ), Type(TextureCopyType::PlacedFootprint), PlacedFootprint( reinterpret_cast< const PlacedSubresourceFootprint& >( footprint ) )
        { }

        TextureCopyLocation( _In_ ID3D12Resource* resource, const PlacedSubresourceFootprint& footprint )
            : pResource( resource ), Type( TextureCopyType::PlacedFootprint ), PlacedFootprint( footprint )
        { }

        TextureCopyLocation( const Resource& resource, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& footprint );

        TextureCopyLocation( const Resource& resource, const PlacedSubresourceFootprint& footprint );

        TextureCopyLocation( _In_ ID3D12Resource* resource, UINT subresourceIndex )
            : pResource( resource ), SubresourceIndex( subresourceIndex )
        { }

        TextureCopyLocation( const Resource& resource, UINT subresourceIndex );

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEXTURE_COPY_LOCATION );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_RESOLVE_MODE
    /// </para>
    /// </summary>
    enum class ResolveMode : Int32
    {
        Decompress = D3D12_RESOLVE_MODE_DECOMPRESS,
        Min = D3D12_RESOLVE_MODE_MIN,
        Max = D3D12_RESOLVE_MODE_MAX,
        Average = D3D12_RESOLVE_MODE_AVERAGE,
        EncodeSamplerFeedback = D3D12_RESOLVE_MODE_ENCODE_SAMPLER_FEEDBACK,
        DecodeSamplerFeedback = D3D12_RESOLVE_MODE_DECODE_SAMPLER_FEEDBACK
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SAMPLE_POSITION
    /// </para>
    /// </summary>
    struct SamplePosition
    {
        INT8 X;
        INT8 Y;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SAMPLE_POSITION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VIEW_INSTANCE_LOCATION
    /// </para>
    /// </summary>
    struct ViewInstanceLocation
    {
        UInt32 ViewportArrayIndex;
        UInt32 RenderTargetArrayIndex;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_VIEW_INSTANCE_LOCATION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VIEW_INSTANCING_FLAGS
    /// </para>
    /// </summary>
    enum class ViewInstancingFlags : Int32
    {
        None = D3D12_VIEW_INSTANCING_FLAG_NONE,
        EnableViewInstanceMasking = D3D12_VIEW_INSTANCING_FLAG_ENABLE_VIEW_INSTANCE_MASKING
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ViewInstancingFlags, Int32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_VIEW_INSTANCING_DESC
    /// </para>
    /// </summary>
    struct ViewInstancingDesc
    {
        UInt32 ViewInstanceCount;
        _Field_size_full_( ViewInstanceCount )  const ViewInstanceLocation* pViewInstanceLocations;
        ViewInstancingFlags Flags;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_VIEW_INSTANCING_DESC );
    };

    /// <summary>
    /// <para>
    /// Specifies how memory gets routed by a shader resource view.
    /// </para>
    /// <para>
    /// Alias for D3D12_SHADER_COMPONENT_MAPPING
    /// </para>
    /// </summary>
    /// <remarks>
    /// <para>
    /// This enum allows the SRV to select how memory gets routed to the four 
    /// return components in a shader after a memory fetch. The options for each 
    /// shader component [0..3] (corresponding to RGBA) are: component 0..3 from 
    /// the SRV fetch result or force 0 or force 1.
    /// </para>
    /// <para>
    /// The default 1:1 mapping can be indicated by specifying <c>DefaultShader4ComponentMapping</c>, 
    /// otherwise an arbitrary mapping can be specified using the <c>EncodeShader4ComponentMapping</c>
    /// function.
    /// </para>
    /// </remarks>
    enum class ShaderComponentMapping : UInt32
    {
        /// <summary>
        /// Indicates return component 0 (red).
        /// </summary>
        FromMemoryComponent0 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_0,
        /// <summary>
        /// Indicates return component 1 (green).
        /// </summary>
        FromMemoryComponent1 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_1,
        /// <summary>
        /// Indicates return component 2 (blue).
        /// </summary>
        FromMemoryComponent2 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_2,
        /// <summary>
        /// Indicates return component 3 (alpha).
        /// </summary>
        FromMemoryComponent3 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_3,
        /// <summary>
        /// Indicates forcing the resulting value to 0.
        /// </summary>
        ForceValue0 = D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_0,
        /// <summary>
        /// Indicates forcing the resulting value 1. The value of forcing 1 is either 
        /// 0x1 or 1.0f depending on the format type for that component in the source format.
        /// </summary>
        ForceValue1 = D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_1
    };


    constexpr UInt32 ShaderComponentMappingMask = D3D12_SHADER_COMPONENT_MAPPING_MASK;
    constexpr UInt32 ShaderComponentMappingShift = D3D12_SHADER_COMPONENT_MAPPING_SHIFT;
    constexpr UInt32 ShaderComponentMappingAlwaysSetBitAvoidingZeroMemMistakes = D3D12_SHADER_COMPONENT_MAPPING_ALWAYS_SET_BIT_AVOIDING_ZEROMEM_MISTAKES;
    constexpr UInt32 DefaultShader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

    constexpr inline UInt32 EncodeShader4ComponentMapping( UInt32 src0, UInt32 src1, UInt32 src2, UInt32 src3 )
    {
        return ( ( ( src0 & ShaderComponentMappingMask ) |
                ( ( src1 & ShaderComponentMappingMask ) << ShaderComponentMappingShift ) |
                ( ( src2 & ShaderComponentMappingMask ) << ( ShaderComponentMappingShift * 2 ) ) |
                ( ( src3 & ShaderComponentMappingMask ) << ( ShaderComponentMappingShift * 3 ) ) |
                ShaderComponentMappingAlwaysSetBitAvoidingZeroMemMistakes ) );
    }
    constexpr inline UInt32 EncodeShader4ComponentMapping( ShaderComponentMapping src0, ShaderComponentMapping src1, ShaderComponentMapping src2, ShaderComponentMapping src3 )
    {
        return EncodeShader4ComponentMapping( static_cast< UInt32 >( src0 ), static_cast< UInt32 >( src1 ), static_cast< UInt32 >( src2 ), static_cast< UInt32 >( src3 ) );
    }


    constexpr inline ShaderComponentMapping DecodeShader4ComponentMapping( Int32 componentToExtract, Int32 mapping )
    {
        return static_cast< ShaderComponentMapping >( mapping >> ( ShaderComponentMappingShift * componentToExtract ) & ShaderComponentMappingMask );
    }

    /// <summary>
    /// <para>
    /// Identifies how to view a buffer resource
    /// </para>
    /// <para>
    /// Alias for D3D12_BUFFER_SRV_FLAGS
    /// </para>
    /// </summary>
    enum class BufferSRVFlags : Int32
    {
        /// <summary>
        /// Indicates a default view.
        /// </summary>
        None = D3D12_BUFFER_SRV_FLAG_NONE,
        /// <summary>
        /// View the buffer as raw.
        /// </summary>
        Raw = D3D12_BUFFER_SRV_FLAG_RAW
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( BufferSRVFlags, Int32 );
    
    /// <summary>
    /// <para>
    /// Describes the elements in a buffer resource to use in a shader-resource view.
    /// </para>
    /// <para>
    /// Alias for D3D12_BUFFER_SRV
    /// </para>
    /// </summary>
    /// <remarks>
    /// This structure is used by ShaderResourceViewDesc to create a view of a buffer.
    /// </remarks>
    struct BufferSRV
    {
        /// <summary>
        /// The index of the first element to be accessed by the view.
        /// </summary>
        UInt64 FirstElement = 0;
        /// <summary>
        /// The number of elements in the resource.
        /// </summary>
        UInt32 NumElements = 0;
        /// <summary>
        /// The size of each element in the buffer structure (in bytes) when 
        /// the buffer represents a structured buffer. The size must match the 
        /// struct size declared in shaders that access the view.
        /// </summary>
        UInt32 StructureByteStride = 0;
        /// <summary>
        /// Identifies view options for the buffer. Currently, the only option is 
        /// to identify a raw view of the buffer. 
        /// </summary>
        BufferSRVFlags Flags = BufferSRVFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUFFER_SRV );
    };

    static_assert( sizeof( D3D12_BUFFER_SRV ) == sizeof( BufferSRV ) );

    /// <summary>
    /// <para>
    /// Specifies the subresource from a 1D texture to use in a shader-resource view.
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX1D_SRV
    /// </para>
    /// </summary>
    struct Tex1DSRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        float ResourceMinLODClamp = 0.f;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_SRV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX1D_ARRAY_SRV
    /// </para>
    /// </summary>
    struct Tex1DArraySRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;
        float ResourceMinLODClamp = 0.f;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_ARRAY_SRV );
    };

    /// <summary>
    /// Alias for D3D12_TEX2D_SRV
    /// </summary>
    struct Tex2DSRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        UInt32 PlaneSlice = 0;
        float ResourceMinLODClamp = 0.f;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_SRV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2D_ARRAY_SRV
    /// </para>
    /// </summary>
    struct Tex2DArraySRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;
        UInt32 PlaneSlice = 0;
        float ResourceMinLODClamp = 0.f;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_ARRAY_SRV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX3D_SRV
    /// </para>
    /// </summary>
    struct Tex3DSRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        float ResourceMinLODClamp = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX3D_SRV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXCUBE_SRV
    /// </para>
    /// </summary>
    struct TexCubeSRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        float ResourceMinLODClamp = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEXCUBE_SRV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXCUBE_ARRAY_SRV
    /// </para>
    /// </summary>
    struct TexCubeArraySRV
    {
        UInt32 MostDetailedMip = 0;
        UInt32 MipLevels = 0;
        UInt32 First2DArrayFace = 0;
        UInt32 NumCubes = 0;
        float ResourceMinLODClamp = 0.f;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEXCUBE_ARRAY_SRV );
    };

    /// <summary>
    /// Alias for D3D12_TEX2DMS_SRV
    /// </summary>
    struct Tex2DMSSRV
    {
        UInt32 UnusedField_NothingToDefine = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_SRV );
    };

    /// <summary>
    /// Alias for D3D12_TEX2DMS_ARRAY_SRV
    /// </summary>
    struct Tex2DMSArraySRV
    {
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_ARRAY_SRV );
    };

    /// <summary>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_SRV
    /// </summary>
    struct RaytracingAccelerationStructureSRV
    {
        GPUVirtualAddress Location = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_SRV );
    };

    /// <summary>
    /// Identifies the type of resource that will be viewed as a shader resource.
    /// </summary>
    enum class SRVDimension
    {
        /// <summary>
        /// The type is unknown.
        /// </summary>
        Unknown = D3D12_SRV_DIMENSION_UNKNOWN,
        /// <summary>
        /// The resource is a buffer.
        /// </summary>
        Buffer = D3D12_SRV_DIMENSION_BUFFER,
        /// <summary>
        /// The resource is a 1D texture.
        /// </summary>
        Texture1D = D3D12_SRV_DIMENSION_TEXTURE1D,
        /// <summary>
        /// The resource is an array of 1D textures.
        /// </summary>
        Texture1DArray = D3D12_SRV_DIMENSION_TEXTURE1DARRAY,
        /// <summary>
        /// The resource is a 2D texture.
        /// </summary>
        Texture2D = D3D12_SRV_DIMENSION_TEXTURE2D,
        /// <summary>
        /// The resource is an array of 2D textures.
        /// </summary>
        Texture2DArray = D3D12_SRV_DIMENSION_TEXTURE2DARRAY,
        /// <summary>
        /// The resource is a multisampling 2D texture.
        /// </summary>
        Texture2DMS = D3D12_SRV_DIMENSION_TEXTURE2DMS,
        /// <summary>
        /// The resource is an array of multisampling 2D textures.
        /// </summary>
        Texture2DMSArray = D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY,
        /// <summary>
        /// The resource is a 3D texture.
        /// </summary>
        Texture3D = D3D12_SRV_DIMENSION_TEXTURE3D,
        /// <summary>
        /// The resource is a cube texture.
        /// </summary>
        TextureCube = D3D12_SRV_DIMENSION_TEXTURECUBE,
        /// <summary>
        /// The resource is an array of cube textures.
        /// </summary>
        TextureCubeArray = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY,
        /// <summary>
        /// The resource is a raytracing acceleration structure.
        /// </summary>
        RaytracingAccelerationStructure = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE
    };

    using ShaderResourceViewType = SRVDimension;


    /// <summary>
    /// Alias for D3D12_SHADER_RESOURCE_VIEW_DESC
    /// </summary>
    struct ShaderResourceViewDesc
    {
        DXGI::Format Format = DXGI::Format::Unknown;
        ShaderResourceViewType ViewDimension = ShaderResourceViewType::Unknown;
        UInt32 Shader4ComponentMapping = DefaultShader4ComponentMapping;
        union
        {
            BufferSRV Buffer;
            Tex1DSRV Texture1D;
            Tex1DArraySRV Texture1DArray;
            Tex2DSRV Texture2D;
            Tex2DArraySRV Texture2DArray;
            Tex2DMSSRV Texture2DMS;
            Tex2DMSArraySRV Texture2DMSArray;
            Tex3DSRV Texture3D;
            TexCubeSRV TextureCube;
            TexCubeArraySRV TextureCubeArray;
            RaytracingAccelerationStructureSRV RaytracingAccelerationStructure;
        };

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SHADER_RESOURCE_VIEW_DESC );
    };
    static_assert( sizeof( ShaderResourceViewDesc ) == sizeof( D3D12_SHADER_RESOURCE_VIEW_DESC ) );

    /// <summary>
    /// Alias for D3D12_CONSTANT_BUFFER_VIEW_DESC
    /// </summary>
    struct ConstantBufferViewDesc
    {
        GPUVirtualAddress BufferLocation = 0;
        UInt32 SizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_CONSTANT_BUFFER_VIEW_DESC );
    };

    /// <summary>
    /// <para>
    /// Specifies filtering options during texture sampling.
    /// </para>
    /// <para>
    /// Alias for D3D12_FILTER
    /// </para>
    /// </summary>
    enum class Filter
    {
        Empty = 0,
        None = 0,
        /// <summary>
        /// Use point sampling for minification, magnification, and mip-level sampling.
        /// </summary>
        MinMagMIPPoint = D3D12_FILTER_MIN_MAG_MIP_POINT,
        /// <summary>
        /// Use point sampling for minification and magnification; use linear interpolation for mip-level sampling.
        /// </summary>
        MinMagPointMIPLinear = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR,
        /// <summary>
        /// Use point sampling for minification; use linear interpolation for magnification; use point sampling for mip-level sampling.
        /// </summary>
        MinPointMagLinearMIPPoint = D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
        /// <summary>
        /// Use point sampling for minification; use linear interpolation for magnification and mip-level sampling.
        /// </summary>
        MinPointMagMIPLinear = D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR,
        /// <summary>
        /// Use linear interpolation for minification; use point sampling for magnification and mip-level sampling.
        /// </summary>
        MinLinearMagMIPPoint = D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT,
        /// <summary>
        /// Use linear interpolation for minification; use point sampling for magnification; use linear interpolation for mip-level sampling.
        /// </summary>
        MinLinearMagPointMIPLinear = D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        /// <summary>
        /// Use linear interpolation for minification and magnification; use point sampling for mip-level sampling.
        /// </summary>
        MinMagLinearMIPPoint = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,
        /// <summary>
        /// Use linear interpolation for minification, magnification, and mip-level sampling.
        /// </summary>
        MinMagMIPLinear = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        /// <summary>
        /// Use point sampling for minification; use linear interpolation for magnification; 
        /// use point sampling for mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        MinMagAnisotropicMIPPoint = D3D12_FILTER_MIN_MAG_ANISOTROPIC_MIP_POINT,
        /// <summary>
        /// Use anisotropic interpolation for minification, magnification, and mip-level sampling.
        /// </summary>
        Anisotropic = D3D12_FILTER_ANISOTROPIC,
        /// <summary>
        /// Use point sampling for minification, magnification, and mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinMagMIPPoint = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
        /// <summary>
        /// Use point sampling for minification and magnification; use linear interpolation for mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinMagPointMIPLinear = D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
        /// <summary>
        /// Use point sampling for minification; use linear interpolation for magnification; use point sampling for mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinPointMagLinearMIPPoint = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
        /// <summary>
        /// Use point sampling for minification; use linear interpolation for magnification and mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinPointMagMIPLinear = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
        /// <summary>
        /// Use linear interpolation for minification; use point sampling for magnification and mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinLinearMagMIPPoint = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
        /// <summary>
        /// Use linear interpolation for minification; use point sampling for magnification; use linear interpolation for mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinLinearMagPointMIPLinear = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        /// <summary>
        /// Use linear interpolation for minification and magnification; use point sampling for mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinMagLinearMIPPoint = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
        /// <summary>
        /// Use linear interpolation for minification, magnification, and mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonMinMagMIPLinear = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
        ComparisonMinMagAnisotropicMIPPoint = D3D12_FILTER_COMPARISON_MIN_MAG_ANISOTROPIC_MIP_POINT,
        /// <summary>
        /// Use anisotropic interpolation for minification, magnification, and mip-level sampling. Compare the result to the comparison value.
        /// </summary>
        ComparisonAnisotropic = D3D12_FILTER_COMPARISON_ANISOTROPIC,
        /// <summary>
        /// Fetch the same set of texels as MinMagMIPPoint and instead of filtering them 
        /// return the minimum of the texels. Texels that are weighted 0 during filtering 
        /// aren't counted towards the minimum. You can query support for this filter type 
        /// from the MinMaxFiltering member in the D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinMAGMIPPoint = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT,
        /// <summary>
        /// Fetch the same set of texels as MinMagPointMIPLinear and instead 
        /// of filtering them return the minimum of the texels. Texels that are 
        /// weighted 0 during filtering aren't counted towards the minimum. You 
        /// can query support for this filter type from the MinMaxFiltering member 
        /// in the D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinMagPointMIPLinear = D3D12_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
        /// <summary>
        /// Fetch the same set of texels as MinPointMagLinearMIPPoint and instead 
        /// of filtering them return the minimum of the texels. Texels that are 
        /// weighted 0 during filtering aren't counted towards the minimum. You can 
        /// query support for this filter type from the MinMaxFiltering member in the 
        /// D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinPointMagLinearMIPPoint = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
        /// <summary>
        /// Fetch the same set of texels as MinPointMagMIPLinear and instead of filtering them 
        /// return the minimum of the texels. Texels that are weighted 0 during filtering aren't 
        /// counted towards the minimum. You can query support for this filter type from the 
        /// MinMaxFiltering member in the D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinPointMagMIPLinear = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
        /// <summary>
        /// Fetch the same set of texels as MinLinearMagMIPPoint and instead of filtering 
        /// them return the minimum of the texels. Texels that are weighted 0 during filtering 
        /// aren't counted towards the minimum. You can query support for this filter type 
        /// from the MinMaxFiltering member in the D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinLinearMagMIPPoint = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
        /// <summary>
        /// Fetch the same set of texels as MinLinearMagPointMIPLinear and instead 
        /// of filtering them return the minimum of the texels. Texels that are weighted 
        /// 0 during filtering aren't counted towards the minimum. You can query support 
        /// for this filter type from the MinMaxFiltering member in the 
        /// D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinLinearMagPointMIPLinear = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        /// <summary>
        /// Fetch the same set of texels as MinMagLinearMIPPoint and instead of filtering 
        /// them return the minimum of the texels. Texels that are weighted 0 during 
        /// filtering aren't counted towards the minimum. You can query support for 
        /// this filter type from the MinMaxFiltering member in the 
        /// D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinMagLinearMIPPoint = D3D12_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
        /// <summary>
        /// Fetch the same set of texels as MinMagMIPLinear and instead of filtering 
        /// them return the minimum of the texels. Texels that are weighted 0 during 
        /// filtering aren't counted towards the minimum. You can query support for 
        /// this filter type from the MinMaxFiltering member in the 
        /// D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumMinMagMIPLinear = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR,
        /// <summary>
        /// 
        /// </summary>
        MinimumMinMagAnisotropicMIPPoint = D3D12_FILTER_MINIMUM_MIN_MAG_ANISOTROPIC_MIP_POINT,
        /// <summary>
        /// Fetch the same set of texels as Anisotropic and instead of filtering them 
        /// return the minimum of the texels. Texels that are weighted 0 during filtering 
        /// aren't counted towards the minimum. You can query support for this filter type 
        /// from the MinMaxFiltering member in the D3D11::FeatureDataD3D11Options1 structure.
        /// </summary>
        MinimumAnisotropic = D3D12_FILTER_MINIMUM_ANISOTROPIC,

        MaximumMinMagMIPPoint = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_POINT,
        MaximumMinMagPointMIPLinear = D3D12_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
        MaximumMinPointMagLinearMIPPoint = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
        MaximumMinPointMagMIPLinear = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
        MaximumMinLinearMagMIPPoint = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
        MaximumMinLinearMagPointMIPLinear = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        MaximumMinMagLinearMIPPoint = D3D12_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
        MaximumMinMagMIPLinear = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR,
        MaximumMinMagAnisotropicMIPPoint = D3D12_FILTER_MAXIMUM_MIN_MAG_ANISOTROPIC_MIP_POINT,
        MaximumAnisotropic = D3D12_FILTER_MAXIMUM_ANISOTROPIC
    };

    /// <summary>
    /// <para>
    /// Specifies the type of magnification or minification sampler filters.
    /// </para>
    /// <para>
    /// Alias for D3D12_FILTER_TYPE
    /// </para>
    /// </summary>
    enum class FilterType
    {
        /// <summary>
        /// Point filtering is used as a texture magnification or minification filter. The 
        /// texel with coordinates nearest to the desired pixel value is used. The texture 
        /// filter to be used between mipmap levels is nearest-point mipmap filtering. The 
        /// rasterizer uses the color from the texel of the nearest mipmap texture.
        /// </summary>
        Point = D3D12_FILTER_TYPE_POINT,
        /// <summary>
        /// Bilinear interpolation filtering is used as a texture magnification or minification 
        /// filter. A weighted average of a 2 x 2 area of texels surrounding the desired pixel 
        /// is used. The texture filter to use between mipmap levels is trilinear mipmap 
        /// interpolation. The rasterizer linearly interpolates pixel color, using the texels 
        /// of the two nearest mipmap textures.
        /// </summary>
        Linear = D3D12_FILTER_TYPE_LINEAR
    };

    /// <summary>
    /// <para>
    /// Specifies the type of filter reduction.
    /// </para>
    /// <para>
    /// Alias for D3D12_FILTER_REDUCTION_TYPE
    /// </para>
    /// </summary>
    enum class FilterReductionType
    {
        /// <summary>
        /// The filter type is standard.
        /// </summary>
        Standard = D3D12_FILTER_REDUCTION_TYPE_STANDARD,
        /// <summary>
        /// The filter type is comparison.
        /// </summary>
        Comparison = D3D12_FILTER_REDUCTION_TYPE_COMPARISON,
        /// <summary>
        /// The filter type is minimum.
        /// </summary>
        Minimum = D3D12_FILTER_REDUCTION_TYPE_MINIMUM,
        /// <summary>
        /// The filter type is maximum.
        /// </summary>
        Maximum = D3D12_FILTER_REDUCTION_TYPE_MAXIMUM
    };

    constexpr UInt32 FilterReductionTypeMask = D3D12_FILTER_REDUCTION_TYPE_MASK;
    constexpr UInt32 FilterReductionTypeShift = D3D12_FILTER_REDUCTION_TYPE_SHIFT;
    constexpr UInt32 FilterTypeMask = D3D12_FILTER_TYPE_MASK;
    constexpr UInt32 MinFilterShift = D3D12_MIN_FILTER_SHIFT;
    constexpr UInt32 MagFilterShift = D3D12_MAG_FILTER_SHIFT;
    constexpr UInt32 MIPFilterShift = D3D12_MIP_FILTER_SHIFT;
    constexpr UInt32 AnisotropicFilteringBit = D3D12_ANISOTROPIC_FILTERING_BIT;

    constexpr Filter EncodeBasicFilter( UInt32 min, UInt32 mag, UInt32 mip, UInt32 reduction )
    {
        return static_cast< Filter >( D3D12_ENCODE_BASIC_FILTER( min, mag, mip, reduction ) );
    }

    constexpr Filter EncodeAnisotropicFilter( UInt32 reduction )
    {
        return static_cast< Filter >( D3D12_ENCODE_ANISOTROPIC_FILTER( reduction ) );
    }

    constexpr Filter EncodeMinMagAnisotropicMIPPointFilter( UInt32 reduction )
    {
        return static_cast< Filter >( D3D12_ENCODE_MIN_MAG_ANISOTROPIC_MIP_POINT_FILTER( reduction ) );
    }


    constexpr FilterType DecodeMinFilter( UInt32 filter )
    {
        return static_cast< FilterType >( D3D12_DECODE_MIN_FILTER( filter ) );
    }

    constexpr FilterType DecodeMinFilter( Filter filter )
    {
        return DecodeMinFilter( static_cast< UInt32 >( filter ) );
    }

    constexpr FilterType DecodeMagFilter( UInt32 filter )
    {
        return static_cast< FilterType >( D3D12_DECODE_MAG_FILTER( filter ) );
    }

    constexpr FilterType DecodeMagFilter( Filter filter )
    {
        return DecodeMagFilter( static_cast< UInt32 >( filter ) );
    }

    constexpr FilterType DecodeMIPFilter( UInt32 filter )
    {
        return static_cast< FilterType >( D3D12_DECODE_MIP_FILTER( filter ) );
    }

    constexpr FilterType DecodeMIPFilter( Filter filter )
    {
        return DecodeMIPFilter( static_cast< UInt32 >( filter ) );
    }

    constexpr FilterReductionType DecodeFilterReduction( UInt32 filter )
    {
        return static_cast< FilterReductionType >( D3D12_DECODE_FILTER_REDUCTION( filter ) );
    }

    constexpr FilterReductionType DecodeFilterReduction( Filter filter )
    {
        return DecodeFilterReduction( static_cast< UInt32 >( filter ) );
    }

    constexpr bool IsComparisonFilter( UInt32 filter )
    {
        return D3D12_DECODE_IS_COMPARISON_FILTER( filter );
    }

    constexpr bool IsComparisonFilter( Filter filter )
    {
        return IsComparisonFilter( static_cast< UInt32 >( filter ) );
    }

    constexpr bool IsAnisotropicFilter( UInt32 filter )
    {
        return D3D12_DECODE_IS_ANISOTROPIC_FILTER( filter );
    }

    constexpr bool IsAnisotropicFilter( Filter filter )
    {
        return IsAnisotropicFilter( static_cast< UInt32 >( filter ) );
    }

    /// <summary>
    /// <para>
    /// Identifies a technique for resolving texture coordinates that are 
    /// outside of the boundaries of a texture.
    /// </para>
    /// <para>
    /// Alias for D3D12_TEXTURE_ADDRESS_MODE
    /// </para>
    /// </summary>
    enum class TextureAddressMode
    {
        None = 0,
        /// <summary>
        /// <para>
        /// Tile the texture at every (u,v) integer junction.
        /// </para>
        /// <para>
        /// For example, for u values between 0 and 3, the texture is repeated three times.
        /// </para>
        /// </summary>
        Wrap = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        /// <summary>
        /// <para>
        /// Flip the texture at every (u,v) integer junction.
        /// </para>
        /// <para>
        /// For u values between 0 and 1, for example, the texture is 
        /// addressed normally; between 1 and 2, the texture is flipped( mirrored ); 
        /// between 2 and 3, the texture is normal again; and so on.
        /// </para>
        /// </summary>
        Mirror = D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
        /// <summary>
        /// Texture coordinates outside the range [0.0, 1.0] are set to the texture 
        /// color at 0.0 or 1.0, respectively.
        /// </summary>
        Clamp = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        /// <summary>
        /// Texture coordinates outside the range [0.0, 1.0] are set to the border 
        /// color specified in SamplerDesc or HLSL code.
        /// </summary>
        Border = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
        /// <summary>
        /// Similar to Mirror and Clamp. Takes the absolute value of the texture 
        /// coordinate (thus, mirroring around 0), and then clamps to the maximum value.
        /// </summary>
        MirrorOnce = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE
    };

    /// <summary>
    /// <para>
    /// Describes a sampler state.
    /// </para>
    /// <para>
    /// Alias for D3D12_SAMPLER_DESC
    /// </para>
    /// </summary>
    struct SamplerDesc
    {
        /// <summary>
        /// The filter value that specifies the filtering method to use when sampling a texture.
        /// </summary>
        D3D12::Filter Filter = D3D12::Filter::Empty;
        /// <summary>
        /// A TextureAddressMode value that specifies the method to use for resolving a u texture coordinate that is outside the 0 to 1 range.
        /// </summary>
        TextureAddressMode AddressU = TextureAddressMode::None;
        /// <summary>
        /// A TextureAddressMode value that specifies the method to use for resolving a v texture coordinate that is outside the 0 to 1 range.
        /// </summary>
        TextureAddressMode AddressV = TextureAddressMode::None;
        /// <summary>
        /// A TextureAddressMode value that specifies the method to use for resolving a w texture coordinate that is outside the 0 to 1 range.
        /// </summary>
        TextureAddressMode AddressW = TextureAddressMode::None;
        /// <summary>
        /// Offset from the calculated mipmap level. For example, if the runtime calculates that a texture should 
        /// be sampled at mipmap level 3 and MipLODBias is 2, the texture will be sampled at mipmap level 5.
        /// </summary>
        float MipLODBias = 0.f;
        /// <summary>
        /// Clamping value used if Filter::Anisotropic or FilterComparisonAnisotropic is
        /// specified in Filter. Valid values are between 1 and 16.
        /// </summary>
        UInt32 MaxAnisotropy = 0;
        /// <summary>
        /// A ComparisonFunction value that specifies a function that compares sampled data against existing sampled data.
        /// </summary>
        D3D12::ComparisonFunction ComparisonFunc = D3D12::ComparisonFunction::Unknown;
        /// <summary>
        /// RGBA border color to use if TextureAddressMode::Border is specified 
        /// for AddressU, AddressV, or AddressW. Range must be between 0.0 and 
        /// 1.0 inclusive.
        /// </summary>
        float BorderColor[ 4 ]{};
        /// <summary>
        /// Lower end of the mipmap range to clamp access to, where 0 is the largest and 
        /// most detailed mipmap level and any level higher than that is less detailed.
        /// </summary>
        float MinLOD = 0.f;
        /// <summary>
        /// Upper end of the mipmap range to clamp access to, where 0 is the largest and 
        /// most detailed mipmap level and any level higher than that is less detailed. 
        /// This value must be greater than or equal to MinLOD. To have no upper 
        /// limit on LOD, set this member to a large value.
        /// </summary>
        float MaxLOD = 0.f;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SAMPLER_DESC );
    };

    static_assert( sizeof( SamplerDesc ) == sizeof( D3D12_SAMPLER_DESC ) );


    /// <summary>
    /// <para>
    /// 
    /// </para>
    /// <para>
    /// Alias for D3D12_SAMPLER_FLAGS
    /// </para>
    /// </summary>
    enum class SamplerFlags : UInt32
    {
        None = D3D12_SAMPLER_FLAG_NONE,
        UInt32BorderColor = D3D12_SAMPLER_FLAG_UINT_BORDER_COLOR,
        NonNormalizedCoordinates = D3D12_SAMPLER_FLAG_NON_NORMALIZED_COORDINATES
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SamplerFlags, UInt32 );

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_SAMPLER_DESC2
    /// </para>
    /// </summary>
    struct SamplerDesc2
    {
        /// <summary>
        /// The filter value that specifies the filtering method to use when sampling a texture.
        /// </summary>
        D3D12::Filter Filter = D3D12::Filter::Empty;
        /// <summary>
        /// A TextureAddressMode value that specifies the method to use for resolving a u texture coordinate that is outside the 0 to 1 range.
        /// </summary>
        TextureAddressMode AddressU = TextureAddressMode::None;
        /// <summary>
        /// A TextureAddressMode value that specifies the method to use for resolving a v texture coordinate that is outside the 0 to 1 range.
        /// </summary>
        TextureAddressMode AddressV = TextureAddressMode::None;
        /// <summary>
        /// A TextureAddressMode value that specifies the method to use for resolving a w texture coordinate that is outside the 0 to 1 range.
        /// </summary>
        TextureAddressMode AddressW = TextureAddressMode::None;
        /// <summary>
        /// Offset from the calculated mipmap level. For example, if the runtime calculates that a texture should 
        /// be sampled at mipmap level 3 and MipLODBias is 2, the texture will be sampled at mipmap level 5.
        /// </summary>
        float MipLODBias = 0.f;
        /// <summary>
        /// Clamping value used if Filter::Anisotropic or FilterComparisonAnisotropic is
        /// specified in Filter. Valid values are between 1 and 16.
        /// </summary>
        UInt32 MaxAnisotropy = 0;
        /// <summary>
        /// A ComparisonFunction value that specifies a function that compares sampled data against existing sampled data.
        /// </summary>
        D3D12::ComparisonFunction ComparisonFunc = D3D12::ComparisonFunction::Unknown;
        union
        {
            /// <summary>
            /// RGBA border color to use if TextureAddressMode::Border is specified 
            /// for AddressU, AddressV, or AddressW. Range must be between 0.0 and 
            /// 1.0 inclusive.
            /// </summary>
            FLOAT FloatBorderColor[ 4 ];
            UInt32 UintBorderColor[ 4 ]{};
        };

        /// <summary>
        /// Lower end of the mipmap range to clamp access to, where 0 is the largest and 
        /// most detailed mipmap level and any level higher than that is less detailed.
        /// </summary>
        float MinLOD = 0.f;
        /// <summary>
        /// Upper end of the mipmap range to clamp access to, where 0 is the largest and 
        /// most detailed mipmap level and any level higher than that is less detailed. 
        /// This value must be greater than or equal to MinLOD. To have no upper 
        /// limit on LOD, set this member to a large value.
        /// </summary>
        float MaxLOD = 0.f;
        SamplerFlags Flags;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SAMPLER_DESC2 );
    };
    static_assert( sizeof( SamplerDesc2 ) == sizeof( D3D12_SAMPLER_DESC2 ) );

    /// <summary>
    /// <para>
    /// Identifies unordered-access view options for a buffer resource.
    /// </para>
    /// <para>
    /// Alias for D3D12_BUFFER_UAV_FLAGS
    /// </para>
    /// </summary>
    enum class BufferUAVFlags : UInt32
    {
        /// <summary>
        /// Indicates a default view.
        /// </summary>
        None = D3D12_BUFFER_UAV_FLAG_NONE,
        /// <summary>
        /// Resource contains raw, unstructured data. Requires the UAV format 
        /// to be DXGI::Format::R32 (DXGI_FORMAT_R32_TYPELESS).
        /// </summary>
        Raw = D3D12_BUFFER_UAV_FLAG_RAW
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( BufferUAVFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Describes the elements in a buffer to use in a unordered-access view.
    /// </para>
    /// <para>
    /// Alias for D3D12_BUFFER_UAV
    /// </para>
    /// </summary>
    /// <remarks>
    /// <para>
    /// Use this structure with a UnorderedAccessViewDesc structure 
    /// to view the resource as a buffer.
    /// </para>
    /// <para>
    /// If StructureByteStride value is not 0, a view of a structured buffer is created and the 
    /// UnorderedAccessViewDesc::Format field must be DXGI::Format::Unknown. If StructureByteStride 
    /// is 0, a typed view of a buffer is created and a format must be supplied. The specified 
    /// format for the typed view must be supported by the hardware.
    /// </para>
    /// </remarks>
    struct BufferUAV
    {
        /// <summary>
        /// The zero-based index of the first element to be accessed.
        /// </summary>
        UInt64 FirstElement = 0;
        /// <summary>
        /// The number of elements in the resource. For structured buffers, this is the number of structures in the buffer.
        /// </summary>
        UInt32 NumElements = 0;
        /// <summary>
        /// The size of each element in the buffer structure (in bytes) when the buffer represents a structured buffer.
        /// </summary>
        UInt32 StructureByteStride = 0;
        /// <summary>
        /// The counter offset, in bytes.
        /// </summary>
        UInt64 CounterOffsetInBytes = 0;
        /// <summary>
        /// BufferUAVFlags value that specifies the view options for the resource.
        /// </summary>
        BufferUAVFlags Flags = BufferUAVFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUFFER_UAV );
    };
    static_assert( sizeof( BufferUAV ) == sizeof( D3D12_BUFFER_UAV ) );

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX1D_UAV
    /// </para>
    /// </summary>
    struct Tex1DUAV
    {
        UInt32 MipSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_UAV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX1D_ARRAY_UAV
    /// </para>
    /// </summary>
    struct Tex1DArrayUAV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_ARRAY_UAV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2D_UAV
    /// </para>
    /// </summary>
    struct Tex2DUAV
    {
        UInt32 MipSlice = 0;
        UInt32 PlaneSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_UAV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2D_ARRAY_UAV
    /// </para>
    /// </summary>
    struct Tex2DArrayUAV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;
        UInt32 PlaneSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_ARRAY_UAV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2DMS_UAV
    /// </para>
    /// </summary>
    struct Tex2DMSUAV
    {
        UInt32 UnusedField_NothingToDefine = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_UAV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2DMS_ARRAY_UAV
    /// </para>
    /// </summary>
    struct Tex2DMSArrayUAV
    {
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_ARRAY_UAV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX3D_UAV
    /// </para>
    /// </summary>
    struct Tex3DUAV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstWSlice = 0;
        UInt32 WSize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX3D_UAV );
    };
    

    /// <summary>
    /// <para>
    /// Alias for D3D12_UAV_DIMENSION
    /// </para>
    /// </summary>
    enum class UAVDimension
    {
        Unknown = D3D12_UAV_DIMENSION_UNKNOWN,
        Buffer = D3D12_UAV_DIMENSION_BUFFER,
        Texture1D = D3D12_UAV_DIMENSION_TEXTURE1D,
        Texture1Darray = D3D12_UAV_DIMENSION_TEXTURE1DARRAY,
        Texture2D = D3D12_UAV_DIMENSION_TEXTURE2D,
        Texture2DArray = D3D12_UAV_DIMENSION_TEXTURE2DARRAY,
        Texture2DMS = D3D12_UAV_DIMENSION_TEXTURE2DMS,
        Texture2DMSarray = D3D12_UAV_DIMENSION_TEXTURE2DMSARRAY,
        Texture3D = D3D12_UAV_DIMENSION_TEXTURE3D
    };

    using UnorderedAccessViewType = UAVDimension;

    /// <summary>
    /// <para>
    /// Alias for D3D12_UNORDERED_ACCESS_VIEW_DESC
    /// </para>
    /// </summary>
    struct UnorderedAccessViewDesc
    {
        DXGI::Format Format = DXGI::Format::Unknown;
        UnorderedAccessViewType ViewDimension = UnorderedAccessViewType::Unknown;
        union
        {
            D3D12_BUFFER_UAV Buffer;
            D3D12_TEX1D_UAV Texture1D;
            D3D12_TEX1D_ARRAY_UAV Texture1DArray;
            D3D12_TEX2D_UAV Texture2D;
            D3D12_TEX2D_ARRAY_UAV Texture2DArray;
            D3D12_TEX2DMS_UAV Texture2DMS;
            D3D12_TEX2DMS_ARRAY_UAV Texture2DMSArray;
            D3D12_TEX3D_UAV Texture3D;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_UNORDERED_ACCESS_VIEW_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BUFFER_RTV 
    /// </para>
    /// </summary>
    struct BufferRTV
    {
        UInt64 FirstElemen = 0;
        UInt32 NumElements = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUFFER_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX1D_RTV
    /// </para>
    /// </summary>
    struct Tex1DRTV
    {
        UInt32 MipSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX1D_ARRAY_RTV
    /// </para>
    /// </summary>
    struct Tex1DArrayRTV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_ARRAY_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2D_RTV
    /// </para>
    /// </summary>
    struct Tex2DRTV
    {
        UInt32 MipSlice = 0;
        UInt32 PlaneSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2DMS_RTV
    /// </para>
    /// </summary>
    struct Tex2DMSRTV
    {
        UInt32 UnusedField_NothingToDefine = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2D_ARRAY_RTV
    /// </para>
    /// </summary>
    struct Tex2DArrayRTV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;
        UInt32 PlaneSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_ARRAY_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX2DMS_ARRAY_RTV
    /// </para>
    /// </summary>
    struct Tex2DMSArrayRTV
    {
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_ARRAY_RTV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEX3D_RTV
    /// </para>
    /// </summary>
    struct Tex3DRTV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstWSlice = 0;
        UInt32 WSize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX3D_RTV );
    };


    /// <summary>
    /// Identifies the type of resource to view as a render target.
    /// <para>
    /// Alias for D3D12_RTV_DIMENSION
    /// </para>
    /// </summary>
    enum class RTVDimension
    {
        Unknown = D3D12_RTV_DIMENSION_UNKNOWN,
        Buffer = D3D12_RTV_DIMENSION_BUFFER,
        Texture1D = D3D12_RTV_DIMENSION_TEXTURE1D,
        Texture1DArray = D3D12_RTV_DIMENSION_TEXTURE1DARRAY,
        Texture2D = D3D12_RTV_DIMENSION_TEXTURE2D,
        Texture2DArray = D3D12_RTV_DIMENSION_TEXTURE2DARRAY,
        Texture2DMS = D3D12_RTV_DIMENSION_TEXTURE2DMS,
        Texture2DMSArray = D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY,
        Texture3D = D3D12_RTV_DIMENSION_TEXTURE3D
    };

    using RenderTargetViewType = RTVDimension;

    /// <summary>
    /// <para>
    /// Describes the subresources from a resource that are accessible by using a render-target view.
    /// </para>
    /// <para>
    /// Alias for D3D12_RENDER_TARGET_VIEW_DESC
    /// </para>
    /// </summary>
    struct RenderTargetViewDesc
    {
        DXGI::Format Format = DXGI::Format::Unknown;
        RenderTargetViewType ViewDimension = RenderTargetViewType::Unknown;
        union
        {
            D3D12_BUFFER_RTV Buffer;
            D3D12_TEX1D_RTV Texture1D;
            D3D12_TEX1D_ARRAY_RTV Texture1DArray;
            D3D12_TEX2D_RTV Texture2D;
            D3D12_TEX2D_ARRAY_RTV Texture2DArray;
            D3D12_TEX2DMS_RTV Texture2DMS;
            D3D12_TEX2DMS_ARRAY_RTV Texture2DMSArray;
            D3D12_TEX3D_RTV Texture3D;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_TARGET_VIEW_DESC );
    };

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX1D_DSV
    /// </para>
    /// </summary>
    struct Tex1DDSV
    {
        UInt32 MipSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_DSV );
    };

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX1D_ARRAY_DSV
    /// </para>
    /// </summary>
    struct Tex1DArrayDSV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX1D_ARRAY_DSV );
    };

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX2D_DSV
    /// </para>
    /// </summary>
    struct Tex2DDSV
    {
        UInt32 MipSlice = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_DSV );
    };

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX2D_ARRAY_DSV
    /// </para>
    /// </summary>
    struct Tex2DArrayDSV
    {
        UInt32 MipSlice = 0;
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2D_ARRAY_DSV );
    };

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX2DMS_DSV
    /// </para>
    /// </summary>
    struct Tex2DMSDSV
    {
        UInt32 UnusedField_NothingToDefine = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_DSV );
    };

    /// <summary>
    /// <para>
    /// </para>
    /// <para>
    /// Alias for D3D12_TEX2DMS_ARRAY_DSV
    /// </para>
    /// </summary>
    struct Tex2DMSArrayDSV
    {
        UInt32 FirstArraySlice = 0;
        UInt32 ArraySize = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEX2DMS_ARRAY_DSV );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DSV_FLAGS
    /// </para>
    /// </summary>
    enum class DSVFlags : UInt32
    {
        None = D3D12_DSV_FLAG_NONE,
        ReadOnlyDepth = D3D12_DSV_FLAG_READ_ONLY_DEPTH,
        ReadOnlyStencil = D3D12_DSV_FLAG_READ_ONLY_STENCIL
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( DSVFlags, UInt32 );

    using DepthStencilViewFlags = DSVFlags;

    /// <summary>
    /// <para>
    /// Alias for D3D12_DSV_DIMENSION
    /// </para>
    /// </summary>
    enum class DSVDimension
    {
        Unknown = 0,
        Texture1D = 1,
        Texture1DArray = 2,
        Texture2D = 3,
        Texture2DArray = 4,
        Texture2DMS = 5,
        Texture2DMSArray = 6
    };

    using DepthStencilViewType = DSVDimension;

    // <summary>
    /// <para>
    /// Alias for D3D12_DEPTH_STENCIL_VIEW_DESC
    /// </para>
    /// </summary>
    struct DepthStencilViewDesc
    {
        DXGI::Format Format = DXGI::Format::Unknown;
        DepthStencilViewType ViewDimension = DepthStencilViewType::Unknown;
        DepthStencilViewFlags Flags = DepthStencilViewFlags::None;
        union
        {
            Tex1DDSV Texture1D;
            Tex1DArrayDSV Texture1DArray;
            Tex2DDSV Texture2D;
            Tex2DArrayDSV Texture2DArray;
            Tex2DMSDSV Texture2DMS;
            Tex2DMSArrayDSV Texture2DMSArray;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEPTH_STENCIL_VIEW_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_CLEAR_FLAGS
    /// </para>
    /// </summary>
    enum class ClearFlags : UInt32
    {
        Depth = D3D12_CLEAR_FLAG_DEPTH,
        Stencil = D3D12_CLEAR_FLAG_STENCIL
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ClearFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_FENCE_FLAGS
    /// </para>
    /// </summary>
    enum class FenceFlags : UInt32
    {
        D3D12_FENCE_FLAG_NONE = 0,
        D3D12_FENCE_FLAG_SHARED = 0x1,
        D3D12_FENCE_FLAG_SHARED_CROSS_ADAPTER = 0x2,
        D3D12_FENCE_FLAG_NON_MONITORED = 0x4
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( FenceFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_HEAP_TYPE
    /// </para>
    /// </summary>
    enum class DescriptorHeapType : Int32
    {
        CBV_SRV_UAV = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
        Sampler = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
        RTV = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
        DSV = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
        NumTypes = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_HEAP_FLAGS
    /// </para>
    /// </summary>
    enum class DescriptorHeapFlags : UInt32
    {
        None = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
        ShaderVisible = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( DescriptorHeapFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_HEAP_DESC
    /// </para>
    /// </summary>
    struct DescriptorHeapDesc
    {
        DescriptorHeapType Type = DescriptorHeapType::CBV_SRV_UAV;
        UInt32 NumDescriptors = 0;
        DescriptorHeapFlags Flags = DescriptorHeapFlags::None;
        UInt32 NodeMask = 0;

        DescriptorHeapDesc( ) noexcept = default;

        DescriptorHeapDesc( UInt32 numDescriptors, DescriptorHeapFlags flags, UInt32 nodeMask = 0 ) noexcept
            : NumDescriptors( numDescriptors ), Flags( flags ), NodeMask( nodeMask )
        { }

        DescriptorHeapDesc( DescriptorHeapType type, UInt32 numDescriptors, DescriptorHeapFlags flags, UInt32 nodeMask = 0 ) noexcept
            : Type( type ), NumDescriptors( numDescriptors ), Flags( flags ), NodeMask( nodeMask )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DESCRIPTOR_HEAP_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_RANGE_TYPE
    /// </para>
    /// </summary>
    enum class DescriptorRangeType
    {
        ShaderResourceView = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
        UnorderedAccessView = D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
        ConstantBufferView = D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
        Sampler = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_RANGE
    /// </para>
    /// </summary>
    struct DescriptorRange
    {
        DescriptorRangeType RangeType = DescriptorRangeType::ShaderResourceView;
        UInt32 NumDescriptors = 0;
        UInt32 BaseShaderRegister = 0;
        UInt32 RegisterSpace = 0;
        UInt32 OffsetInDescriptorsFromTableStart = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DESCRIPTOR_RANGE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_DESCRIPTOR_TABLE
    /// </para>
    /// </summary>
    struct RootDescriptorTable
    {
        UInt32 NumDescriptorRanges = 0;
        _Field_size_full_( NumDescriptorRanges )  const DescriptorRange* pDescriptorRanges = nullptr;

        RootDescriptorTable( ) = default;
        RootDescriptorTable( UInt32 numDescriptorRanges, _Field_size_full_( numDescriptorRanges )  const DescriptorRange* descriptorRanges )
            : NumDescriptorRanges( numDescriptorRanges ), pDescriptorRanges( descriptorRanges )
        { }

        template<SimpleSpanLike T>
        RootDescriptorTable( const T& descriptorRanges )
            : NumDescriptorRanges( static_cast<UInt32>( descriptorRanges.size() ) ), pDescriptorRanges( descriptorRanges.data( ) )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_DESCRIPTOR_TABLE );

    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_CONSTANTS
    /// </para>
    /// </summary>
    struct RootConstants
    {
        UInt32 ShaderRegister = 0;
        UInt32 RegisterSpace = 0;
        UInt32 Num32BitValues = 0;

        RootConstants( ) = default;
        explicit RootConstants( UInt32 shaderRegister, UInt32 registerSpace = 0, UInt32 num32BitValues = 0 )
            : ShaderRegister( shaderRegister ), RegisterSpace( registerSpace ), Num32BitValues( num32BitValues )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_CONSTANTS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_DESCRIPTOR
    /// </para>
    /// </summary>
    struct RootDescriptor
    {
        UInt32 ShaderRegister = 0;
        UInt32 RegisterSpace = 0;

        RootDescriptor( ) = default;

        explicit RootDescriptor( UInt32 shaderRegister, UInt32 registerSpace = 0 )
            : ShaderRegister( shaderRegister ), RegisterSpace( registerSpace )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_DESCRIPTOR );

    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_VISIBILITY
    /// </para>
    /// </summary>
    enum class ShaderVisibility
    {
        All = D3D12_SHADER_VISIBILITY_ALL,
        Vertex = D3D12_SHADER_VISIBILITY_VERTEX,
        Hull = D3D12_SHADER_VISIBILITY_HULL,
        Domain = D3D12_SHADER_VISIBILITY_DOMAIN,
        Geometry = D3D12_SHADER_VISIBILITY_GEOMETRY,
        Pixel = D3D12_SHADER_VISIBILITY_PIXEL,
        Amplification = D3D12_SHADER_VISIBILITY_AMPLIFICATION,
        Mesh = D3D12_SHADER_VISIBILITY_MESH
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_PARAMETER_TYPE
    /// </para>
    /// </summary>
    enum class RootParameterType
    {
        DescriptorTable = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,
        Constants = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS,
        ConstantBufferView = D3D12_ROOT_PARAMETER_TYPE_CBV,
        ShaderResourceView = D3D12_ROOT_PARAMETER_TYPE_SRV,
        UnorderedAccessView = D3D12_ROOT_PARAMETER_TYPE_UAV
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_PARAMETER
    /// </para>
    /// </summary>
    struct RootParameter
    {
        RootParameterType ParameterType = RootParameterType::DescriptorTable;
        union
        {
            RootDescriptorTable DescriptorTable;
            RootConstants Constants;
            RootDescriptor Descriptor;
        };
        D3D12::ShaderVisibility ShaderVisibility = D3D12::ShaderVisibility::All;

        RootParameter( ) = default;

        explicit RootParameter( const RootDescriptorTable& descriptorTable, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : DescriptorTable( descriptorTable ), ShaderVisibility( shaderVisibility )
        { }

        RootParameter( UInt32 numDescriptorRanges, _Field_size_full_( numDescriptorRanges )  const DescriptorRange* descriptorRanges, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : DescriptorTable( numDescriptorRanges, descriptorRanges), ShaderVisibility( shaderVisibility )
        { }

        template<SimpleSpanLike T>
        explicit RootParameter( const T& descriptorRanges, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : DescriptorTable( descriptorRanges ), ShaderVisibility( shaderVisibility )
        { }

        explicit RootParameter( RootConstants& constants, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : ParameterType( RootParameterType::Constants ), Constants( constants ), ShaderVisibility( shaderVisibility )
        { }

        RootParameter( UInt32 shaderRegister, UInt32 registerSpace, UInt32 num32BitValues, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : ParameterType( RootParameterType::Constants ), Constants( shaderRegister, registerSpace, num32BitValues ), ShaderVisibility( shaderVisibility )
        { }

        
        RootParameter( RootParameterType parameterType, const RootDescriptor& descriptor, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : ParameterType( parameterType ), Descriptor( descriptor ), ShaderVisibility( shaderVisibility )
        { }

        RootParameter( RootParameterType parameterType, UInt32 shaderRegister, UInt32 registerSpace, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
            : ParameterType( parameterType ), Descriptor( shaderRegister, registerSpace ), ShaderVisibility( shaderVisibility )
        { }

        static RootParameter AsConstantBufferView( UInt32 shaderRegister, UInt32 registerSpace, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
        {
            return RootParameter( RootParameterType::ConstantBufferView, shaderRegister, registerSpace, shaderVisibility );
        }
        static RootParameter AsShaderResourceView( UInt32 shaderRegister, UInt32 registerSpace, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
        {
            return RootParameter( RootParameterType::ShaderResourceView, shaderRegister, registerSpace, shaderVisibility );
        }
        static RootParameter AsUnorderedAccessView( UInt32 shaderRegister, UInt32 registerSpace, D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All )
        {
            return RootParameter( RootParameterType::UnorderedAccessView, shaderRegister, registerSpace, shaderVisibility );
        }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_PARAMETER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_SIGNATURE_FLAGS
    /// </para>
    /// </summary>
    enum class RootSignatureFlags : UInt32
    {
        None = D3D12_ROOT_SIGNATURE_FLAG_NONE,
        AllowInputAssemblerInputLayout = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT,
        DenyVertexShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS,
        DenyHullShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS,
        DenyDomainShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS,
        DenyGeometryShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS,
        DenyPixelShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS,
        AllowStreamOutput = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT,
        LocalRootSignature = D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE,
        DenyAmplificationShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_AMPLIFICATION_SHADER_ROOT_ACCESS,
        DenyMeshShaderRootAccess = D3D12_ROOT_SIGNATURE_FLAG_DENY_MESH_SHADER_ROOT_ACCESS,
        CBV_SRV_UAVHeapDirectlyIndexed = D3D12_ROOT_SIGNATURE_FLAG_CBV_SRV_UAV_HEAP_DIRECTLY_INDEXED,
        SamplerHeapDirectlyIndexed = D3D12_ROOT_SIGNATURE_FLAG_SAMPLER_HEAP_DIRECTLY_INDEXED
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RootSignatureFlags, UInt32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_STATIC_BORDER_COLOR
    /// </para>
    /// </summary>
    enum class StaticBorderColor
    {
        TransparentBlack = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK,
        OpaqueBlack = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK,
        OpaqueWhite = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE,
        OpaqueBlackUInt = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK_UINT,
        OpaqueWhiteUInt = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE_UINT
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STATIC_SAMPLER_DESC
    /// </para>
    /// </summary>
    struct StaticSamplerDesc
    {
        D3D12::Filter Filter = D3D12::Filter::None;
        TextureAddressMode AddressU = TextureAddressMode::None;
        TextureAddressMode AddressV = TextureAddressMode::None;
        TextureAddressMode AddressW = TextureAddressMode::None;
        float MipLODBias = 0.f;
        UInt32 MaxAnisotropy = 0;
        ComparisonFunction ComparisonFunc = ComparisonFunction::Unknown;
        StaticBorderColor BorderColor = StaticBorderColor::TransparentBlack;
        float MinLOD = 0.f;
        float MaxLOD = 0.f;
        UInt32 ShaderRegister = 0;
        UInt32 RegisterSpace = 0;
        D3D12::ShaderVisibility ShaderVisibility = D3D12::ShaderVisibility::All;

        StaticSamplerDesc( ) = default;

        StaticSamplerDesc( UInt32 shaderRegister,
                D3D12::Filter filter = D3D12::Filter::Anisotropic,
                TextureAddressMode addressU = TextureAddressMode::Wrap,
                TextureAddressMode addressV = TextureAddressMode::Wrap,
                TextureAddressMode addressW = TextureAddressMode::Wrap,
                float mipLODBias = 0,
                UInt32 maxAnisotropy = 16,
                ComparisonFunction comparisonFunc = ComparisonFunction::LessOrEqual,
                StaticBorderColor borderColor = StaticBorderColor::OpaqueWhite,
                float minLOD = 0.f,
                float maxLOD = D3D12_FLOAT32_MAX,
                D3D12::ShaderVisibility shaderVisibility = D3D12::ShaderVisibility::All,
                UInt32 registerSpace = 0 ) noexcept
            : Filter( filter ), AddressU( addressU ), AddressV( addressV ), AddressW( addressW ), MipLODBias( mipLODBias ), MaxAnisotropy( maxAnisotropy ),
              ComparisonFunc( comparisonFunc ), BorderColor( borderColor ), MinLOD( minLOD ), MaxLOD( maxLOD ), ShaderRegister( shaderRegister ), RegisterSpace( registerSpace ),
              ShaderVisibility( shaderVisibility )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STATIC_SAMPLER_DESC );

    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STATIC_SAMPLER_DESC1
    /// </para>
    /// </summary>
    struct StaticSamplerDesc1 : public StaticSamplerDesc
    {
        SamplerFlags Flags = SamplerFlags::None;
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STATIC_SAMPLER_DESC1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_SIGNATURE_DESC
    /// </para>
    /// </summary>
    struct RootSignatureDesc
    {
        UInt32 NumParameters = 0;
        _Field_size_full_( NumParameters )  const RootParameter* pParameters = nullptr;
        UInt32 NumStaticSamplers = 0;
        _Field_size_full_( NumStaticSamplers )  const StaticSamplerDesc* pStaticSamplers = nullptr;
        RootSignatureFlags Flags = RootSignatureFlags::None;

        RootSignatureDesc( ) = default;

        RootSignatureDesc( UInt32 numParameters, _Field_size_full_( numParameters )  const RootParameter* parameters, RootSignatureFlags flags = RootSignatureFlags::None )
            : NumParameters( numParameters ), pParameters( parameters ), Flags(flags)
        { }

        RootSignatureDesc( UInt32 numStaticSamplers, _Field_size_full_( numStaticSamplers )  const StaticSamplerDesc* staticSamplers, RootSignatureFlags flags = RootSignatureFlags::None )
            : NumStaticSamplers( numStaticSamplers ), pStaticSamplers( staticSamplers ), Flags( flags )
        { }

        RootSignatureDesc( UInt32 numParameters, _Field_size_full_( numParameters )  const RootParameter* parameters, 
                            UInt32 numStaticSamplers, _Field_size_full_( numStaticSamplers )  const StaticSamplerDesc* staticSamplers, 
                            RootSignatureFlags flags = RootSignatureFlags::None )
            : NumParameters( numParameters ), pParameters( parameters ), NumStaticSamplers( numStaticSamplers ), pStaticSamplers( staticSamplers ), Flags( flags )
        { }

        template<SimpleSpanLike T>
            requires std::is_same_v<RootParameter,typename T::value_type>
        RootSignatureDesc( const T& parameters, RootSignatureFlags flags = RootSignatureFlags::None )
            : NumParameters( static_cast<UInt32>( parameters.size() ) ), pParameters( parameters.data( ) ), Flags( flags )
        { }

        template<SimpleSpanLike T>
            requires std::is_same_v<StaticSamplerDesc, typename T::value_type>
        RootSignatureDesc( const T& staticSamplers, RootSignatureFlags flags = RootSignatureFlags::None )
            : NumStaticSamplers( static_cast< UInt32 >( staticSamplers.size( ) ) ), pStaticSamplers( staticSamplers.data( ) ), Flags( flags )
        { }

        template<SimpleSpanLike S, SimpleSpanLike T>
            requires std::is_same_v<RootParameter, typename S::value_type> && std::is_same_v<StaticSamplerDesc, typename T::value_type>
        RootSignatureDesc( const S& parameters, const T& staticSamplers, RootSignatureFlags flags = RootSignatureFlags::None )
            : NumParameters( static_cast< UInt32 >( parameters.size( ) ) ), pParameters( parameters.data( ) ), 
              NumStaticSamplers( static_cast< UInt32 >( staticSamplers.size( ) ) ), pStaticSamplers( staticSamplers.data( ) ), 
              Flags( flags )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_SIGNATURE_DESC );

    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_RANGE_FLAGS
    /// </para>
    /// </summary>
    enum class DescriptorRangeFlags : UInt32
    {
        None = D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
        DescriptorsVolatile = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE,
        DataVolatile = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_VOLATILE,
        DataStaticWhileSetAtExecute = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE,
        DataStatic = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC,
        DescriptorsStaticKeepingBufferBoundsChecks = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_STATIC_KEEPING_BUFFER_BOUNDS_CHECKS
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( DescriptorRangeFlags, UInt32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_DESCRIPTOR_RANGE1
    /// </para>
    /// </summary>
    struct DescriptorRange1
    {
        DescriptorRangeType RangeType = DescriptorRangeType::ConstantBufferView;
        UInt32 NumDescriptors = 0;
        UInt32 BaseShaderRegister = 0;
        UInt32 RegisterSpace = 0;
        DescriptorRangeFlags Flags = DescriptorRangeFlags::None;
        UInt32 OffsetInDescriptorsFromTableStart = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DESCRIPTOR_RANGE1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_DESCRIPTOR_TABLE1
    /// </para>
    /// </summary>
    struct RootDescriptorTable1
    {
        UInt32 NumDescriptorRanges = 0;
        _Field_size_full_( NumDescriptorRanges )  const DescriptorRange1* pDescriptorRanges = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_DESCRIPTOR_TABLE1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_DESCRIPTOR_FLAGS
    /// </para>
    /// </summary>
    enum class RootDescriptorFlags : UInt32
    {
        None = D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
        DataVolatile = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_VOLATILE,
        DataStaticWhileSetAtExecute = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE,
        DataStatic = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RootDescriptorFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_DESCRIPTOR1
    /// </para>
    /// </summary>
    struct RootDescriptor1
    {
        UInt32 ShaderRegister = 0;
        UInt32 RegisterSpace = 0;
        RootDescriptorFlags Flags = RootDescriptorFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_DESCRIPTOR1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_PARAMETER1
    /// </para>
    /// </summary>
    struct RootParameter1
    {
        RootParameterType ParameterType = RootParameterType::DescriptorTable;
        union
        {
            D3D12_ROOT_DESCRIPTOR_TABLE1 DescriptorTable;
            D3D12_ROOT_CONSTANTS Constants;
            D3D12_ROOT_DESCRIPTOR1 Descriptor;
        };
        D3D12::ShaderVisibility ShaderVisibility = D3D12::ShaderVisibility::All;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_PARAMETER1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_SIGNATURE_DESC1
    /// </para>
    /// </summary>
    struct RootSignatureDesc1
    {
        UInt32 NumParameters = 0;
        _Field_size_full_( NumParameters )  const RootParameter1* pParameters = nullptr;
        UInt32 NumStaticSamplers = 0;
        _Field_size_full_( NumStaticSamplers )  const StaticSamplerDesc* pStaticSamplers = nullptr;
        RootSignatureFlags Flags = RootSignatureFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_SIGNATURE_DESC1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ROOT_SIGNATURE_DESC2
    /// </para>
    /// </summary>
    struct RootSignatureDesc2
    {
        UInt32 NumParameters = 0;
        _Field_size_full_( NumParameters )  const RootParameter1* pParameters = nullptr;
        UInt32 NumStaticSamplers = 0;
        _Field_size_full_( NumStaticSamplers )  const StaticSamplerDesc1* pStaticSamplers = nullptr;
        RootSignatureFlags Flags = RootSignatureFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_ROOT_SIGNATURE_DESC2 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VERSIONED_ROOT_SIGNATURE_DESC
    /// </para>
    /// </summary>
    struct VersionedRootSignatureDesc
    {
        RootSignatureVersion Version = RootSignatureVersion::Version1_1;
        union
        {
            RootSignatureDesc Desc_1_0;
            RootSignatureDesc1 Desc_1_1;
            RootSignatureDesc2 Desc_1_2;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_VERSIONED_ROOT_SIGNATURE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_CPU_DESCRIPTOR_HANDLE
    /// </para>
    /// </summary>
    struct CPUDescriptorHandle
    {
        SIZE_T ptr = 0;
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_CPU_DESCRIPTOR_HANDLE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GPU_DESCRIPTOR_HANDLE
    /// </para>
    /// </summary>
    struct GPUDescriptorHandle
    {
        UInt64 ptr = 0;
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GPU_DESCRIPTOR_HANDLE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DISCARD_REGION
    /// </para>
    /// </summary>
    /// <remarks>
    /// If rects are supplied in D3D12_DISCARD_REGION, below, the resource 
    /// must have 2D subresources with all specified subresources the same dimension.
    /// </remarks>
    struct DiscardRegion
    {
        UInt32 NumRects;
        _In_reads_( NumRects )  const D3D12::Rectangle* pRects;
        UInt32 FirstSubresource;
        UInt32 NumSubresources;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DISCARD_REGION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_QUERY_HEAP_TYPE
    /// </para>
    /// </summary>
    enum class QueryHeapType
    {
        D3D12_QUERY_HEAP_TYPE_OCCLUSION = 0,
        D3D12_QUERY_HEAP_TYPE_TIMESTAMP = 1,
        D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS = 2,
        D3D12_QUERY_HEAP_TYPE_SO_STATISTICS = 3,
        D3D12_QUERY_HEAP_TYPE_VIDEO_DECODE_STATISTICS = 4,
        D3D12_QUERY_HEAP_TYPE_COPY_QUEUE_TIMESTAMP = 5,
        D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS1 = 7
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_QUERY_HEAP_DESC
    /// </para>
    /// </summary>
    struct QueryHeapDesc
    {
        QueryHeapType Type;
        UInt32 Count;
        UInt32 NodeMask;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_QUERY_HEAP_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_QUERY_TYPE
    /// </para>
    /// </summary>
    enum class QueryType
    {
        Occlusion = D3D12_QUERY_TYPE_OCCLUSION,
        BinaryOcclusion = D3D12_QUERY_TYPE_BINARY_OCCLUSION,
        Timestamp = D3D12_QUERY_TYPE_TIMESTAMP,
        PipelineStatistics = D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        StreamOutputStatisticsStream0 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM0,
        StreamOutputStatisticsStream1 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM1,
        StreamOutputStatisticsStream2 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM2,
        StreamOutputStatisticsStream3 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM3,
        VideoDecodeStatistics = D3D12_QUERY_TYPE_VIDEO_DECODE_STATISTICS,
        PipelineStatistics1 = D3D12_QUERY_TYPE_PIPELINE_STATISTICS1
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PREDICATION_OP
    /// </para>
    /// </summary>
    enum class PredicationOperation
    {
        EqualZero = D3D12_PREDICATION_OP_EQUAL_ZERO,
        NotEqualZero = D3D12_PREDICATION_OP_NOT_EQUAL_ZERO,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_QUERY_DATA_PIPELINE_STATISTICS
    /// </para>
    /// </summary>
    struct QueryDataPipelineStatistics
    {
        UInt64 IAVertices;
        UInt64 IAPrimitives;
        UInt64 VSInvocations;
        UInt64 GSInvocations;
        UInt64 GSPrimitives;
        UInt64 CInvocations;
        UInt64 CPrimitives;
        UInt64 PSInvocations;
        UInt64 HSInvocations;
        UInt64 DSInvocations;
        UInt64 CSInvocations;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_QUERY_DATA_PIPELINE_STATISTICS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_QUERY_DATA_PIPELINE_STATISTICS1
    /// </para>
    /// </summary>
    struct QueryDataPipelineStatistics1 : public QueryDataPipelineStatistics
    {
        UInt64 ASInvocations;
        UInt64 MSInvocations;
        UInt64 MSPrimitives;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_QUERY_DATA_PIPELINE_STATISTICS1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_QUERY_DATA_SO_STATISTICS
    /// </para>
    /// </summary>
    struct QueryDataStreamOutputStatistics
    {
        UInt64 NumPrimitivesWritten;
        UInt64 PrimitivesStorageNeeded;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_QUERY_DATA_SO_STATISTICS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STREAM_OUTPUT_BUFFER_VIEW
    /// </para>
    /// </summary>
    struct StreamOutputBufferView
    {
        GPUVirtualAddress BufferLocation;
        UInt64 SizeInBytes;
        GPUVirtualAddress BufferFilledSizeLocation;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STREAM_OUTPUT_BUFFER_VIEW );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRAW_ARGUMENTS
    /// </para>
    /// </summary>
    struct DrawArguments
    {
        UInt32 VertexCountPerInstance;
        UInt32 InstanceCount;
        UInt32 StartVertexLocation;
        UInt32 StartInstanceLocation;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRAW_ARGUMENTS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRAW_INDEXED_ARGUMENTS
    /// </para>
    /// </summary>
    struct DrawIndexedArguments
    {
        UInt32 IndexCountPerInstance;
        UInt32 InstanceCount;
        UInt32 StartIndexLocation;
        INT BaseVertexLocation;
        UInt32 StartInstanceLocation;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRAW_INDEXED_ARGUMENTS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DISPATCH_ARGUMENTS
    /// </para>
    /// </summary>
    struct DispatchArguments
    {
        UInt32 ThreadGroupCountX;
        UInt32 ThreadGroupCountY;
        UInt32 ThreadGroupCountZ;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DISPATCH_ARGUMENTS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VERTEX_BUFFER_VIEW
    /// </para>
    /// </summary>
    struct VertexBufferView
    {
        GPUVirtualAddress BufferLocation;
        UInt32 SizeInBytes;
        UInt32 StrideInBytes;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_VERTEX_BUFFER_VIEW );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_INDEX_BUFFER_VIEW
    /// </para>
    /// </summary>
    struct IndexBufferView
    {
        GPUVirtualAddress BufferLocation;
        UInt32 SizeInBytes;
        DXGI::Format Format;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_INDEX_BUFFER_VIEW );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_INDIRECT_ARGUMENT_TYPE
    /// </para>
    /// </summary>
    enum class IndirectArgumentType
    {
        Draw = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW,
        DrawIndexed = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED,
        Dispatch = D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH,
        VertexBuffer_view = D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW,
        IndexBuffer_view = D3D12_INDIRECT_ARGUMENT_TYPE_INDEX_BUFFER_VIEW,
        Constant = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT,
        ConstantBuffer_view = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT_BUFFER_VIEW,
        ShaderResourceView = D3D12_INDIRECT_ARGUMENT_TYPE_SHADER_RESOURCE_VIEW,
        UnorderedAccessView = D3D12_INDIRECT_ARGUMENT_TYPE_UNORDERED_ACCESS_VIEW,
        DispatchRays = D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH_RAYS,
        DispatchMesh = D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH_MESH,
        IncrementingConstant = D3D12_INDIRECT_ARGUMENT_TYPE_INCREMENTING_CONSTANT
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_INDIRECT_ARGUMENT_DESC
    /// </para>
    /// </summary>
    struct IndirectArgumentDesc
    {
        IndirectArgumentType Type;
        union
        {
            struct
            {
                UInt32 Slot;
            } 	VertexBuffer;
            struct
            {
                UInt32 RootParameterIndex;
                UInt32 DestOffsetIn32BitValues;
                UInt32 Num32BitValuesToSet;
            } 	Constant;
            struct
            {
                UInt32 RootParameterIndex;
            } 	ConstantBufferView;
            struct
            {
                UInt32 RootParameterIndex;
            } 	ShaderResourceView;
            struct
            {
                UInt32 RootParameterIndex;
            } 	UnorderedAccessView;
            struct
            {
                UInt32 RootParameterIndex;
                UInt32 DestOffsetIn32BitValues;
            } 	IncrementingConstant;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_INDIRECT_ARGUMENT_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_COMMAND_SIGNATURE_DESC
    /// </para>
    /// </summary>
    struct CommandSignatureDesc
    {
        UInt32 ByteStride;
        UInt32 NumArgumentDescs;
        _Field_size_full_( NumArgumentDescs )  const D3D12_INDIRECT_ARGUMENT_DESC* pArgumentDescs;
        UInt32 NodeMask;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_COMMAND_SIGNATURE_DESC );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_WRITEBUFFERIMMEDIATE_PARAMETER
    /// </para>
    /// </summary>
    struct WriteBufferImmediateParameter
    {
        GPUVirtualAddress Dest;
        UINT32 Value;
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_WRITEBUFFERIMMEDIATE_PARAMETER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_WRITEBUFFERIMMEDIATE_MODE
    /// </para>
    /// </summary>
    enum class WritebufferimmediateMode
    {
        Default = D3D12_WRITEBUFFERIMMEDIATE_MODE_DEFAULT,
        MarkerIn = D3D12_WRITEBUFFERIMMEDIATE_MODE_MARKER_IN,
        MarkerOut = D3D12_WRITEBUFFERIMMEDIATE_MODE_MARKER_OUT,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MULTIPLE_FENCE_WAIT_FLAGS
    /// </para>
    /// </summary>
    enum class MultipleFenceWaitFlags : UInt32
    {
        D3D12_MULTIPLE_FENCE_WAIT_FLAG_NONE = 0,
        D3D12_MULTIPLE_FENCE_WAIT_FLAG_ANY = 0x1,
        D3D12_MULTIPLE_FENCE_WAIT_FLAG_ALL = 0
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( MultipleFenceWaitFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_RESIDENCY_PRIORITY
    /// </para>
    /// </summary>
    enum class ResidencyPriority
    {
        D3D12_RESIDENCY_PRIORITY_MINIMUM = D3D12_RESIDENCY_PRIORITY_MINIMUM,
        D3D12_RESIDENCY_PRIORITY_LOW = D3D12_RESIDENCY_PRIORITY_LOW,
        D3D12_RESIDENCY_PRIORITY_NORMAL = D3D12_RESIDENCY_PRIORITY_NORMAL,
        D3D12_RESIDENCY_PRIORITY_HIGH = D3D12_RESIDENCY_PRIORITY_HIGH,
        D3D12_RESIDENCY_PRIORITY_MAXIMUM = D3D12_RESIDENCY_PRIORITY_MAXIMUM
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_RESIDENCY_FLAGS
    /// </para>
    /// </summary>
    enum class ResidencyFlags : UInt32
    {
        None = D3D12_RESIDENCY_FLAG_NONE,
        DenyOverbudget = D3D12_RESIDENCY_FLAG_DENY_OVERBUDGET,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ResidencyFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_COMMAND_LIST_FLAGS
    /// </para>
    /// </summary>
    enum class CommandListFlags : UInt32
    {
        None = D3D12_COMMAND_LIST_FLAG_NONE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommandListFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_COMMAND_POOL_FLAGS
    /// </para>
    /// </summary>
    enum class CommandPoolFlags : UInt32
    {
        None = D3D12_COMMAND_POOL_FLAG_NONE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommandPoolFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_COMMAND_RECORDER_FLAGS
    /// </para>
    /// </summary>
    enum class CommandRecorderFlags : UInt32
    {
        None = D3D12_COMMAND_RECORDER_FLAG_NONE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommandRecorderFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_PROTECTED_SESSION_STATUS
    /// </para>
    /// </summary>
    enum class ProtectedSessionStatus
    {
        Ok = D3D12_PROTECTED_SESSION_STATUS_OK,
        Invalid = D3D12_PROTECTED_SESSION_STATUS_INVALID
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAGS
    /// </para>
    /// </summary>
    enum class ProtectedResourceSessionSupportFlags : UInt32
    {
        None = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE,
        Supported = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ProtectedResourceSessionSupportFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT
    /// </para>
    /// </summary>
    struct FeatureDataProtectedResourceSessionSupport
    {
        UInt32 NodeIndex;
        ProtectedResourceSessionSupportFlags Support;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PROTECTED_RESOURCE_SESSION_FLAGS
    /// </para>
    /// </summary>
    enum class ProtectedResourceSessionFlags : UInt32
    {
        None = D3D12_PROTECTED_RESOURCE_SESSION_FLAG_NONE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ProtectedResourceSessionFlags, UInt32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_PROTECTED_RESOURCE_SESSION_DESC
    /// </para>
    /// </summary>
    struct ProtectedResourceSessionDesc
    {
        UInt32 NodeMask;
        ProtectedResourceSessionFlags Flags;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PROTECTED_RESOURCE_SESSION_DESC );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_LIFETIME_STATE
    /// </para>
    /// </summary>
    enum class LifetimeState
    {
        InUse = D3D12_LIFETIME_STATE_IN_USE,
        NotInUse = D3D12_LIFETIME_STATE_NOT_IN_USE
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_META_COMMAND_PARAMETER_TYPE
    /// </para>
    /// </summary>
    enum class MetaCommandParameterType
    {
        Float = D3D12_META_COMMAND_PARAMETER_TYPE_FLOAT,
        UInt64 = D3D12_META_COMMAND_PARAMETER_TYPE_UINT64,
        GPUVirtualAddress = D3D12_META_COMMAND_PARAMETER_TYPE_GPU_VIRTUAL_ADDRESS,
        CPUDescriptorHandleHeapTypeCBV_SRV_UAV = D3D12_META_COMMAND_PARAMETER_TYPE_CPU_DESCRIPTOR_HANDLE_HEAP_TYPE_CBV_SRV_UAV,
        GPUDescriptorHandleHeapTypeCBV_SRV_UAV = D3D12_META_COMMAND_PARAMETER_TYPE_GPU_DESCRIPTOR_HANDLE_HEAP_TYPE_CBV_SRV_UAV
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_META_COMMAND_PARAMETER_FLAGS
    /// </para>
    /// </summary>
    enum class MetaCommandParameterFlags : UInt32
    {
        None = 0,
        Input = D3D12_META_COMMAND_PARAMETER_FLAG_INPUT,
        Output = D3D12_META_COMMAND_PARAMETER_FLAG_OUTPUT
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( MetaCommandParameterFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_META_COMMAND_PARAMETER_STAGE
    /// </para>
    /// </summary>
    enum class MetaCommandParameterStage
    {
        Creation = D3D12_META_COMMAND_PARAMETER_STAGE_CREATION,
        Initialization = D3D12_META_COMMAND_PARAMETER_STAGE_INITIALIZATION,
        Execution = D3D12_META_COMMAND_PARAMETER_STAGE_EXECUTION
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_META_COMMAND_PARAMETER_DESC
    /// </para>
    /// </summary>
    struct MetaCommandParameterDesc
    {
        LPCWSTR Name = nullptr;
        MetaCommandParameterType Type = MetaCommandParameterType::Float;
        MetaCommandParameterFlags Flags = MetaCommandParameterFlags::None;
        ResourceStates RequiredResourceState = ResourceStates::Common;
        UInt32 StructureOffset = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_META_COMMAND_PARAMETER_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GRAPHICS_STATES
    /// </para>
    /// </summary>
    enum class GraphicsStates : UInt32
    {
        None = D3D12_GRAPHICS_STATE_NONE,
        IAVertexBuffers = D3D12_GRAPHICS_STATE_IA_VERTEX_BUFFERS,
        IAIndexBuffer = D3D12_GRAPHICS_STATE_IA_INDEX_BUFFER,
        IAPrimitiveTopology = D3D12_GRAPHICS_STATE_IA_PRIMITIVE_TOPOLOGY,
        DescriptorHeap = D3D12_GRAPHICS_STATE_DESCRIPTOR_HEAP,
        GraphicsRootSignature = D3D12_GRAPHICS_STATE_GRAPHICS_ROOT_SIGNATURE,
        ComputeRootSignature = D3D12_GRAPHICS_STATE_COMPUTE_ROOT_SIGNATURE,
        RSViewports = D3D12_GRAPHICS_STATE_RS_VIEWPORTS,
        RSScissorRects = D3D12_GRAPHICS_STATE_RS_SCISSOR_RECTS,
        Predication = D3D12_GRAPHICS_STATE_PREDICATION,
        OMRenderTargets = D3D12_GRAPHICS_STATE_OM_RENDER_TARGETS,
        OMStencilRef = D3D12_GRAPHICS_STATE_OM_STENCIL_REF,
        OMBlendFactor = D3D12_GRAPHICS_STATE_OM_BLEND_FACTOR,
        PipelineState = D3D12_GRAPHICS_STATE_PIPELINE_STATE,
        SOTargets = D3D12_GRAPHICS_STATE_SO_TARGETS,
        OMDepthBounds = D3D12_GRAPHICS_STATE_OM_DEPTH_BOUNDS,
        SamplePositions = D3D12_GRAPHICS_STATE_SAMPLE_POSITIONS,
        ViewInstanceMask = D3D12_GRAPHICS_STATE_VIEW_INSTANCE_MASK
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( GraphicsStates, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_META_COMMAND_DESC
    /// </para>
    /// </summary>
    struct MetaCommandDesc
    {
        Guid Id;
        LPCWSTR Name = nullptr;
        GraphicsStates InitializationDirtyState = GraphicsStates::None;
        GraphicsStates ExecutionDirtyState = GraphicsStates::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_META_COMMAND_DESC );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_PROGRAM_IDENTIFIER
    /// </para>
    /// </summary>
    struct ProgramIdentifier
    {
        UInt64 OpaqueData[ 4 ];

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PROGRAM_IDENTIFIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_ID
    /// </para>
    /// </summary>
    struct NodeId
    {
        LPCWSTR Name = nullptr;
        UInt32 ArrayIndex = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_NODE_ID );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_WORK_GRAPH_MEMORY_REQUIREMENTS
    /// </para>
    /// </summary>
    struct WorkGraphMemoryRequirements
    {
        UInt64 MinSizeInBytes;
        UInt64 MaxSizeInBytes;
        UInt32 SizeGranularityInBytes;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_WORK_GRAPH_MEMORY_REQUIREMENTS );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_STATE_SUBOBJECT_TYPE
    /// </para>
    /// </summary>
    enum class StateSubobjectType
    {
        StateObjectConfig = D3D12_STATE_SUBOBJECT_TYPE_STATE_OBJECT_CONFIG,
        GlobalRootSignature = D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE,
        LocalRootSignature = D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE,
        NodeMask = D3D12_STATE_SUBOBJECT_TYPE_NODE_MASK,
        DXILLibrary = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY,
        ExistingCollection = D3D12_STATE_SUBOBJECT_TYPE_EXISTING_COLLECTION,
        SubobjectToExportsAssociation = D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION,
        DXILSubobjectToExportsAssociation = D3D12_STATE_SUBOBJECT_TYPE_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION,
        RaytracingShaderConfig = D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_SHADER_CONFIG,
        RaytracingPipelineConfig = D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG,
        HitGroup = D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP,
        RaytracingPipelineConfig1 = D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG1,
        WorkGraph = D3D12_STATE_SUBOBJECT_TYPE_WORK_GRAPH,
        StreamOutput = D3D12_STATE_SUBOBJECT_TYPE_STREAM_OUTPUT,
        Blend = D3D12_STATE_SUBOBJECT_TYPE_BLEND,
        SampleMask = D3D12_STATE_SUBOBJECT_TYPE_SAMPLE_MASK,
        Rasterizer = D3D12_STATE_SUBOBJECT_TYPE_RASTERIZER,
        DepthStencil = D3D12_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL,
        InputLayout = D3D12_STATE_SUBOBJECT_TYPE_INPUT_LAYOUT,
        IBStripCutValue = D3D12_STATE_SUBOBJECT_TYPE_IB_STRIP_CUT_VALUE,
        PrimitiveTopology = D3D12_STATE_SUBOBJECT_TYPE_PRIMITIVE_TOPOLOGY,
        RenderTargetFormats = D3D12_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS,
        DepthStencilFormat = D3D12_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT,
        SampleDesc = D3D12_STATE_SUBOBJECT_TYPE_SAMPLE_DESC,
        Flags = D3D12_STATE_SUBOBJECT_TYPE_FLAGS,
        DepthStencil1 = D3D12_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL1,
        ViewInstancing = D3D12_STATE_SUBOBJECT_TYPE_VIEW_INSTANCING,
        GenericProgram = D3D12_STATE_SUBOBJECT_TYPE_GENERIC_PROGRAM,
        DepthStencil2 = D3D12_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL2,
        MaxValid = D3D12_STATE_SUBOBJECT_TYPE_MAX_VALID
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STATE_SUBOBJECT
    /// </para>
    /// </summary>
    struct StateSubobject
    {
        StateSubobjectType Type = StateSubobjectType::StateObjectConfig;
        const void* pDesc = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STATE_SUBOBJECT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STATE_OBJECT_FLAGS
    /// </para>
    /// </summary>
    enum class StateObjectFlags : UInt32
    {
        None = D3D12_STATE_OBJECT_FLAG_NONE,
        AllowLocalDependenciesOnExternalDefinitions = D3D12_STATE_OBJECT_FLAG_ALLOW_LOCAL_DEPENDENCIES_ON_EXTERNAL_DEFINITIONS,
        AllowExternalDependenciesOnKocalDefinitions = D3D12_STATE_OBJECT_FLAG_ALLOW_EXTERNAL_DEPENDENCIES_ON_LOCAL_DEFINITIONS,
        AllowStateObjectAdditions = D3D12_STATE_OBJECT_FLAG_ALLOW_STATE_OBJECT_ADDITIONS,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( StateObjectFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_STATE_OBJECT_CONFIG
    /// </para>
    /// </summary>
    struct StateObjectConfig
    {
        StateObjectFlags Flags = StateObjectFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STATE_OBJECT_CONFIG );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GLOBAL_ROOT_SIGNATURE
    /// </para>
    /// </summary>
    struct GlobalRootSignature
    {
        ID3D12RootSignature* pGlobalRootSignature = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GLOBAL_ROOT_SIGNATURE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_LOCAL_ROOT_SIGNATURE
    /// </para>
    /// </summary>
    struct LocalRootSignature
    {
        ID3D12RootSignature* pLocalRootSignature = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_LOCAL_ROOT_SIGNATURE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_MASK
    /// </para>
    /// </summary>
    struct NodeMask
    {
        UInt32 NodeMask_ = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_NODE_MASK );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SAMPLE_MASK
    /// </para>
    /// </summary>
    struct SampleMask
    {
        UInt32 SampleMask_ = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SAMPLE_MASK );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_IB_STRIP_CUT_VALUE
    /// </para>
    /// </summary>
    struct IBStripCutValue
    {
        D3D12::IndexBufferStripCutValue IndexBufferStripCutValue = D3D12::IndexBufferStripCutValue::Disabled;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_IB_STRIP_CUT_VALUE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PRIMITIVE_TOPOLOGY_DESC
    /// </para>
    /// </summary>
    struct PrimitiveTopologyDesc
    {
        PrimitiveTopologyType PrimitiveTopology = PrimitiveTopologyType::Undefined;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PRIMITIVE_TOPOLOGY_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEPTH_STENCIL_FORMAT
    /// </para>
    /// </summary>
    struct DepthStencilFormat
    {
        DXGI::Format DepthStencilFormat_ = DXGI::Format::Unknown;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEPTH_STENCIL_FORMAT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_EXPORT_FLAGS
    /// </para>
    /// </summary>
    enum class ExportFlags : UInt32
    {
        None = D3D12_EXPORT_FLAG_NONE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ExportFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_EXPORT_DESC
    /// </para>
    /// </summary>
    struct ExportDesc
    {
        LPCWSTR Name = nullptr;
        _In_opt_  LPCWSTR ExportToRename = nullptr;
        ExportFlags Flags = ExportFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_EXPORT_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DXIL_LIBRARY_DESC
    /// </para>
    /// </summary>
    struct DXILLibraryDesc
    {
        ShaderBytecode DXILLibrary;
        UInt32 NumExports = 0;
        _In_reads_( NumExports )  const D3D12_EXPORT_DESC* pExports = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DXIL_LIBRARY_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_EXISTING_COLLECTION_DESC
    /// </para>
    /// </summary>
    struct ExistingCollectionDesc
    {
        ID3D12StateObject* pExistingCollection = nullptr;
        UInt32 NumExports = 0;
        _In_reads_( NumExports )  const ExportDesc* pExports = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_EXISTING_COLLECTION_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION
    /// </para>
    /// </summary>
    struct SubobjectToExportsAssociation
    {
        const StateSubobject* pSubobjectToAssociate = nullptr;
        UInt32 NumExports = 0;
        _In_reads_( NumExports )  LPCWSTR* pExports = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION
    /// </para>
    /// </summary>
    struct DXILSubobjectToExportsAssociation
    {
        LPCWSTR SubobjectToAssociate = nullptr;
        UInt32 NumExports = 0;
        _In_reads_( NumExports )  LPCWSTR* pExports = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_HIT_GROUP_TYPE
    /// </para>
    /// </summary>
    enum class HitGroupType
    {
        Triangles = D3D12_HIT_GROUP_TYPE_TRIANGLES,
        ProceduralPrimitive = D3D12_HIT_GROUP_TYPE_PROCEDURAL_PRIMITIVE,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_HIT_GROUP_DESC
    /// </para>
    /// </summary>
    struct HitGroupDesc
    {
        LPCWSTR HitGroupExport = nullptr;
        HitGroupType Type = HitGroupType::Triangles;
        _In_opt_  LPCWSTR AnyHitShaderImport = nullptr;
        _In_opt_  LPCWSTR ClosestHitShaderImport = nullptr;
        _In_opt_  LPCWSTR IntersectionShaderImport = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_HIT_GROUP_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_SHADER_CONFIG
    /// </para>
    /// </summary>
    struct RaytracingShaderConfig
    {
        UInt32 MaxPayloadSizeInBytes = 0;
        UInt32 MaxAttributeSizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_SHADER_CONFIG );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_PIPELINE_CONFIG
    /// </para>
    /// </summary>
    struct RaytracingPipelineConfig
    {
        UInt32 MaxTraceRecursionDepth = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_PIPELINE_CONFIG );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_PIPELINE_FLAGS
    /// </para>
    /// </summary>
    enum class RaytracingPipelineFlags : UInt32
    {
        None = D3D12_RAYTRACING_PIPELINE_FLAG_NONE,
        SkipTriangles = D3D12_RAYTRACING_PIPELINE_FLAG_SKIP_TRIANGLES,
        SkipProceduralPrimitives = D3D12_RAYTRACING_PIPELINE_FLAG_SKIP_PROCEDURAL_PRIMITIVES,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RaytracingPipelineFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_PIPELINE_CONFIG1
    /// </para>
    /// </summary>
    struct RaytracingPipelineConfig1
    {
        UInt32 MaxTraceRecursionDepth;
        RaytracingPipelineFlags Flags;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_PIPELINE_CONFIG1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_OUTPUT_OVERRIDES
    /// </para>
    /// </summary>
    struct NodeOutputOverrides
    {
        UInt32 OutputIndex = 0;
        _In_opt_  const NodeId* pNewName = nullptr;
        _In_opt_  const BOOL* pAllowSparseNodes = nullptr;
        _In_opt_  const UInt32* pMaxRecords = nullptr;
        _In_opt_  const UInt32* pMaxRecordsSharedWithOutputIndex = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_NODE_OUTPUT_OVERRIDES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BROADCASTING_LAUNCH_OVERRIDES
    /// </para>
    /// </summary>
    struct BroadcastingLaunchOverrides
    {
        _In_opt_  const UInt32* pLocalRootArgumentsTableIndex = nullptr;
        _In_opt_  const BOOL* pProgramEntry = nullptr;
        _In_opt_  const NodeId* pNewName = nullptr;
        _In_opt_   const NodeId* pShareInputOf = nullptr;
        _In_reads_opt_( 3 )  const UInt32* pDispatchGrid = nullptr;
        _In_reads_opt_( 3 )  const UInt32* pMaxDispatchGrid = nullptr;
        UInt32 NumOutputOverrides = 0;
        _In_reads_opt_( NumOutputOverrides )  const NodeOutputOverrides* pOutputOverrides = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BROADCASTING_LAUNCH_OVERRIDES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_COALESCING_LAUNCH_OVERRIDES
    /// </para>
    /// </summary>
    struct CoalescingLaunchOverrides
    {
        _In_opt_  const UInt32* pLocalRootArgumentsTableIndex = nullptr;
        _In_opt_  const BOOL* pProgramEntry = nullptr;
        _In_opt_  const NodeId* pNewName = nullptr;
        _In_opt_  const NodeId* pShareInputOf = nullptr;
        UInt32 NumOutputOverrides = 0;
        _In_reads_opt_( NumOutputOverrides )  const NodeOutputOverrides* pOutputOverrides = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_COALESCING_LAUNCH_OVERRIDES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_THREAD_LAUNCH_OVERRIDES
    /// </para>
    /// </summary>
    struct ThreadLaunchOverrides
    {
        _In_opt_  const UInt32* pLocalRootArgumentsTableIndex = nullptr;
        _In_opt_  const BOOL* pProgramEntry = nullptr;
        _In_opt_  const NodeId* pNewName = nullptr;
        _In_opt_  const NodeId* pShareInputOf = nullptr;
        UInt32 NumOutputOverrides = 0;
        _In_reads_opt_( NumOutputOverrides )  const NodeOutputOverrides* pOutputOverrides = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_THREAD_LAUNCH_OVERRIDES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_COMMON_COMPUTE_NODE_OVERRIDES
    /// </para>
    /// </summary>
    struct CommonComputeNodeOverrides
    {
        _In_opt_  const UInt32* pLocalRootArgumentsTableIndex = nullptr;
        _In_opt_  const BOOL* pProgramEntry = nullptr;
        _In_opt_  const NodeId* pNewName = nullptr;
        _In_opt_  const NodeId* pShareInputOf = nullptr;
        UInt32 NumOutputOverrides = 0;
        _In_reads_opt_( NumOutputOverrides )  const NodeOutputOverrides* pOutputOverrides = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_COMMON_COMPUTE_NODE_OVERRIDES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_OVERRIDES_TYPE
    /// </para>
    /// </summary>
    enum class NodeOverridesType
    {
        None = D3D12_NODE_OVERRIDES_TYPE_NONE,
        BroadcastingLaunch = D3D12_NODE_OVERRIDES_TYPE_BROADCASTING_LAUNCH,
        CoalescingLaunch = D3D12_NODE_OVERRIDES_TYPE_COALESCING_LAUNCH,
        ThreadLaunch = D3D12_NODE_OVERRIDES_TYPE_THREAD_LAUNCH,
        CommonCompute = D3D12_NODE_OVERRIDES_TYPE_COMMON_COMPUTE,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_NODE
    /// </para>
    /// </summary>
    struct ShaderNode
    {
        LPCWSTR Shader = nullptr;
        NodeOverridesType OverridesType = NodeOverridesType::None;
        union
        {
            const BroadcastingLaunchOverrides* pBroadcastingLaunchOverrides;
            const CoalescingLaunchOverrides* pCoalescingLaunchOverrides;
            const ThreadLaunchOverrides* pThreadLaunchOverrides;
            const CommonComputeNodeOverrides* pCommonComputeNodeOverrides;
        };

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SHADER_NODE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_TYPE
    /// </para>
    /// </summary>
    enum class NodeType
    {
        Shader = D3D12_NODE_TYPE_SHADER
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE
    /// </para>
    /// </summary>
    struct Node
    {
        D3D12::NodeType NodeType = D3D12::NodeType::Shader;
        union
        {
            ShaderNode Shader;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_NODE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_WORK_GRAPH_FLAGS
    /// </para>
    /// </summary>
    enum class WorkGraphFlags : UInt32
    {
        None = D3D12_WORK_GRAPH_FLAG_NONE,
        IncludeAllAvailableNodes = D3D12_WORK_GRAPH_FLAG_INCLUDE_ALL_AVAILABLE_NODES,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( WorkGraphFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_WORK_GRAPH_DESC
    /// </para>
    /// </summary>
    struct WorkGraphDesc
    {
        LPCWSTR ProgramName = nullptr;
        WorkGraphFlags Flags = WorkGraphFlags::None;
        UInt32 NumEntrypoints = 0;
        _In_reads_opt_( NumEntrypoints )  const NodeId* pEntrypoints = nullptr;
        UInt32 NumExplicitlyDefinedNodes = 0;
        _In_reads_opt_( NumExplicitlyDefinedNodes )  const Node* pExplicitlyDefinedNodes = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_WORK_GRAPH_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GENERIC_PROGRAM_DESC
    /// </para>
    /// </summary>
    struct GenericProgramDesc
    {
        LPCWSTR ProgramName = nullptr;
        UInt32 NumExports = 0;
        _In_reads_( NumExports )  LPCWSTR* pExports = nullptr;
        UInt32 NumSubobjects = 0;
        _In_reads_opt_( NumSubobjects )  const StateSubobject* const* ppSubobjects = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GENERIC_PROGRAM_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STATE_OBJECT_TYPE
    /// </para>
    /// </summary>
    enum class StateObjectType
    {
        Collection = D3D12_STATE_OBJECT_TYPE_COLLECTION,
        RaytracingPipeline = D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE,
        Executable = D3D12_STATE_OBJECT_TYPE_EXECUTABLE,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_STATE_OBJECT_DESC
    /// </para>
    /// </summary>
    struct StateObjectDesc
    {
        StateObjectType Type = StateObjectType::Collection;
        UInt32 NumSubobjects = 0;
        _In_reads_( NumSubobjects )  const StateSubobject* pSubobjects = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_STATE_OBJECT_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_GEOMETRY_FLAGS
    /// </para>
    /// </summary>
    enum class RaytracingGeometryFlags : UInt32
    {
        None = D3D12_RAYTRACING_GEOMETRY_FLAG_NONE,
        Opaque = D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE,
        NoDuplicateAnyhitInvocation = D3D12_RAYTRACING_GEOMETRY_FLAG_NO_DUPLICATE_ANYHIT_INVOCATION,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RaytracingGeometryFlags, UInt32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_GEOMETRY_TYPE
    /// </para>
    /// </summary>
    enum class RaytracingGeometryType
    {
        Triangles = D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES,
        ProceduralPrimitiveAABBS = D3D12_RAYTRACING_GEOMETRY_TYPE_PROCEDURAL_PRIMITIVE_AABBS,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_INSTANCE_FLAGS
    /// </para>
    /// </summary>
    enum class RaytracingInstanceFlags : UInt32
    {
        None = D3D12_RAYTRACING_INSTANCE_FLAG_NONE,
        TriangleCullDisable = D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE,
        TriangleFrontCounterclockwise = D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_FRONT_COUNTERCLOCKWISE,
        ForceOpaque = D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE,
        ForceNonOpaque = D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RaytracingInstanceFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE
    /// </para>
    /// </summary>
    struct GPUVirtualAddressAndStride
    {
        GPUVirtualAddress StartAddress;
        UInt64 StrideInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GPU_VIRTUAL_ADDRESS_RANGE
    /// </para>
    /// </summary>
    struct GPUVirtualAddressRange
    {
        GPUVirtualAddress StartAddress;
        UInt64 SizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GPU_VIRTUAL_ADDRESS_RANGE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE
    /// </para>
    /// </summary>
    struct GPUVirtualAddressRangeAndStride
    {
        GPUVirtualAddress StartAddress;
        UInt64 SizeInBytes = 0;
        UInt64 StrideInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC
    /// </para>
    /// </summary>
    struct RaytracingGeometryTrianglesDesc
    {
        GPUVirtualAddress Transform3x4;
        DXGI::Format IndexFormat = DXGI::Format::Unknown;
        DXGI::Format VertexFormat = DXGI::Format::Unknown;
        UInt32 IndexCount = 0;
        UInt32 VertexCount = 0;
        GPUVirtualAddress IndexBuffer;
        GPUVirtualAddressRangeAndStride VertexBuffer;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_AABB
    /// </para>
    /// </summary>
    struct RaytracingAABB
    {
        FLOAT MinX;
        FLOAT MinY;
        FLOAT MinZ;
        FLOAT MaxX;
        FLOAT MaxY;
        FLOAT MaxZ;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_AABB );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_GEOMETRY_AABBS_DESC
    /// </para>
    /// </summary>
    struct RaytracingGeometryAABBsDesc
    {
        UInt64 AABBCount = 0;
        GPUVirtualAddressAndStride AABBs;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_GEOMETRY_AABBS_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS
    /// </para>
    /// </summary>
    enum class RaytracingAccelerationStructureBuildFlags : UInt32
    {
        None = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE,
        AllowUpdate = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE,
        AllowCompaction = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_COMPACTION,
        PreferFastTrace = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE,
        PreferFastBuild = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_BUILD,
        MinimizeMemory = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_MINIMIZE_MEMORY,
        PerformUpdate = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RaytracingAccelerationStructureBuildFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE
    /// </para>
    /// </summary>
    enum class RaytracingAccelerationStructureCopyMode
    {
        Clone = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_CLONE,
        Compact = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_COMPACT,
        VisualizationDecodeForTools = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_VISUALIZATION_DECODE_FOR_TOOLS,
        Serialize = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_SERIALIZE,
        Deserialize = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_DESERIALIZE,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE
    /// </para>
    /// </summary>
    enum class RaytracingAccelerationStructureType
    {
        TopLevel = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL,
        BottomLevel = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_ELEMENTS_LAYOUT
    /// </para>
    /// </summary>
    enum class ElementsLayout
    {
        Array = D3D12_ELEMENTS_LAYOUT_ARRAY,
        ArrayOfPointers = D3D12_ELEMENTS_LAYOUT_ARRAY_OF_POINTERS
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE
    /// </para>
    /// </summary>
    enum class RaytracingAccelerationStructurePostbuildInfoType
    {
        CompactedSize = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE,
        ToolsVisualization = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION,
        Serialization = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION,
        CurrentSize = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC
    /// </para>
    /// </summary>
    struct RaytracingAccelerationStructurePostbuildInfoDesc
    {
        GPUVirtualAddress DestBuffer;
        RaytracingAccelerationStructurePostbuildInfoType InfoType = RaytracingAccelerationStructurePostbuildInfoType::CompactedSize;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC
    /// </para>
    /// </summary>
    struct RaytracingAccelerationStructurePostbuildInfoCompactedSizeDesc
    {
        UInt64 CompactedSizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC
    /// </para>
    /// </summary>
    struct RaytracingAccelerationStructurePostbuildInfoToolsVisualizationDesc
    {
        UInt64 DecodedSizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER
    /// </para>
    /// </summary>
    struct BuildRaytracingAccelerationStructureToolsVisualizationHeader
    {
        RaytracingAccelerationStructureType Type = RaytracingAccelerationStructureType::TopLevel;
        UInt32 NumDescs = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC
    /// </para>
    /// </summary>
    struct RaytracingAccelerationStructurePostbuildInfoSerializationDesc
    {
        UInt64 SerializedSizeInBytes = 0;
        UInt64 NumBottomLevelAccelerationStructurePointers = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER
    /// </para>
    /// </summary>
    struct SerializedDataDriverMatchingIdentifier
    {
        Guid DriverOpaqueGUID;
        std::array<BYTE, 16> DriverOpaqueVersioningData{};

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SERIALIZED_DATA_TYPE
    /// </para>
    /// </summary>
    enum class SerializedDataType
    {
        RaytracingAccelerationStructure = D3D12_SERIALIZED_DATA_RAYTRACING_ACCELERATION_STRUCTURE
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS
    /// </para>
    /// </summary>
    enum class DriverMatchingIdentifierStatus
    {
        CompatibleWithDevice = D3D12_DRIVER_MATCHING_IDENTIFIER_COMPATIBLE_WITH_DEVICE,
        UnsupportedType = D3D12_DRIVER_MATCHING_IDENTIFIER_UNSUPPORTED_TYPE,
        Unrecognized = D3D12_DRIVER_MATCHING_IDENTIFIER_UNRECOGNIZED,
        IncompatibleVersion = D3D12_DRIVER_MATCHING_IDENTIFIER_INCOMPATIBLE_VERSION,
        IncompatibleType = D3D12_DRIVER_MATCHING_IDENTIFIER_INCOMPATIBLE_TYPE,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER
    /// </para>
    /// </summary>
    struct SerializedRaytracingAccelerationStructureHeader
    {
        SerializedDataDriverMatchingIdentifier DriverMatchingIdentifier;
        UInt64 SerializedSizeInBytesIncludingHeader = 0;
        UInt64 DeserializedSizeInBytes = 0;
        UInt64 NumBottomLevelAccelerationStructurePointersAfterHeader = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SERIALIZED_RAYTRACING_ACCELERATION_STRUCTURE_HEADER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC
    /// </para>
    /// </summary>
    struct RaytracingAccelerationStructurePostbuildInfoCurrentSizeDesc
    {
        UInt64 CurrentSizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_CURRENT_SIZE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_INSTANCE_DESC
    /// </para>
    /// </summary>
    struct RaytracingInstanceDesc
    {
        FLOAT Transform[ 3 ][ 4 ]{};
        UInt32 InstanceID : 24 = 0;
        UInt32 InstanceMask : 8 = 0;
        UInt32 InstanceContributionToHitGroupIndex : 24 = 0;
        UInt32 Flags : 8 = 0;
        GPUVirtualAddress AccelerationStructure;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_INSTANCE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_GEOMETRY_DESC
    /// </para>
    /// </summary>
    struct RaytracingGeometryDesc
    {
        RaytracingGeometryType Type;
        RaytracingGeometryFlags Flags;
        union
        {
            RaytracingGeometryTrianglesDesc Triangles;
            RaytracingGeometryAABBsDesc AABBs;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_GEOMETRY_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS
    /// </para>
    /// </summary>
    struct BuildRaytracingAccelerationStructureInputs
    {
        RaytracingAccelerationStructureType Type = RaytracingAccelerationStructureType::TopLevel;
        RaytracingAccelerationStructureBuildFlags Flags = RaytracingAccelerationStructureBuildFlags::None;
        UInt32 NumDescs = 0;
        ElementsLayout DescsLayout;
        union
        {
            GPUVirtualAddress InstanceDescs;
            const RaytracingGeometryDesc* pGeometryDescs;
            const RaytracingGeometryDesc* const* ppGeometryDescs;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC
    /// </para>
    /// </summary>
    struct BuildRaytracingAccelerationStructureDesc
    {
        GPUVirtualAddress DestAccelerationStructureData;
        BuildRaytracingAccelerationStructureInputs Inputs;
        _In_opt_  GPUVirtualAddress SourceAccelerationStructureData;
        GPUVirtualAddress ScratchAccelerationStructureData;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO
    /// </para>
    /// </summary>
    struct RaytracingAccelerationStructurePrebuildInfo
    {
        UInt64 ResultDataMaxSizeInBytes = 0;
        UInt64 ScratchDataSizeInBytes = 0;
        UInt64 UpdateScratchDataSizeInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RAY_FLAGS
    /// </para>
    /// </summary>
    enum class RayFlags : UInt32
    {
        None = D3D12_RAY_FLAG_NONE,
        ForceOpaque = D3D12_RAY_FLAG_FORCE_OPAQUE,
        ForceNonOpaque = D3D12_RAY_FLAG_FORCE_NON_OPAQUE,
        AcceptFirstHitAndEndSearch = D3D12_RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH,
        SkipClosestHitShader = D3D12_RAY_FLAG_SKIP_CLOSEST_HIT_SHADER,
        CullBackFacingTriangles = D3D12_RAY_FLAG_CULL_BACK_FACING_TRIANGLES,
        CullFrontFacingTriangles = D3D12_RAY_FLAG_CULL_FRONT_FACING_TRIANGLES,
        CullOpaque = D3D12_RAY_FLAG_CULL_OPAQUE,
        CullNonOpaque = D3D12_RAY_FLAG_CULL_NON_OPAQUE,
        SkipTriangles = D3D12_RAY_FLAG_SKIP_TRIANGLES,
        SkipProceduralPrimitives = D3D12_RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RayFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_HIT_KIND
    /// </para>
    /// </summary>
    enum class HitJind
    {
        FrontFace = D3D12_HIT_KIND_TRIANGLE_FRONT_FACE,
        BackFace = D3D12_HIT_KIND_TRIANGLE_BACK_FACE,
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_AUTO_BREADCRUMB_OP
    /// </para>
    /// </summary>
    enum class AutoBreadcrumbOperation
    {
        SetMarker = D3D12_AUTO_BREADCRUMB_OP_SETMARKER,
        BeginEvent = D3D12_AUTO_BREADCRUMB_OP_BEGINEVENT,
        EndEvent = D3D12_AUTO_BREADCRUMB_OP_ENDEVENT,
        DrawInstanced = D3D12_AUTO_BREADCRUMB_OP_DRAWINSTANCED,
        DrawIndexedInstanced = D3D12_AUTO_BREADCRUMB_OP_DRAWINDEXEDINSTANCED,
        ExecuteIndirect = D3D12_AUTO_BREADCRUMB_OP_EXECUTEINDIRECT,
        Dispatch = D3D12_AUTO_BREADCRUMB_OP_DISPATCH,
        CopyBufferRegion = D3D12_AUTO_BREADCRUMB_OP_COPYBUFFERREGION,
        CopyTextureRegion = D3D12_AUTO_BREADCRUMB_OP_COPYTEXTUREREGION,
        CopyResource = D3D12_AUTO_BREADCRUMB_OP_COPYRESOURCE,
        CopyTiles = D3D12_AUTO_BREADCRUMB_OP_COPYTILES,
        ResolveSubresource = D3D12_AUTO_BREADCRUMB_OP_RESOLVESUBRESOURCE,
        ClearRenderTargetView = D3D12_AUTO_BREADCRUMB_OP_CLEARRENDERTARGETVIEW,
        ClearUnorderedAccessView = D3D12_AUTO_BREADCRUMB_OP_CLEARUNORDEREDACCESSVIEW,
        ClearDepthStencilView = D3D12_AUTO_BREADCRUMB_OP_CLEARDEPTHSTENCILVIEW,
        ResourceBarrier = D3D12_AUTO_BREADCRUMB_OP_RESOURCEBARRIER,
        ExecuteBundle = D3D12_AUTO_BREADCRUMB_OP_EXECUTEBUNDLE,
        Present = D3D12_AUTO_BREADCRUMB_OP_PRESENT,
        ResolveQueryData = D3D12_AUTO_BREADCRUMB_OP_RESOLVEQUERYDATA,
        BeginSubmission = D3D12_AUTO_BREADCRUMB_OP_BEGINSUBMISSION,
        EndSubmission = D3D12_AUTO_BREADCRUMB_OP_ENDSUBMISSION,
        DecodeFrame = D3D12_AUTO_BREADCRUMB_OP_DECODEFRAME,
        ProcessFrames = D3D12_AUTO_BREADCRUMB_OP_PROCESSFRAMES,
        AtomiccopybufferUInt32 = D3D12_AUTO_BREADCRUMB_OP_ATOMICCOPYBUFFERUINT,
        AtomiccopybufferUInt64 = D3D12_AUTO_BREADCRUMB_OP_ATOMICCOPYBUFFERUINT64,
        ResolveSubresourceRegion = D3D12_AUTO_BREADCRUMB_OP_RESOLVESUBRESOURCEREGION,
        WriteBufferImmediate = D3D12_AUTO_BREADCRUMB_OP_WRITEBUFFERIMMEDIATE,
        DecodeFrame1 = D3D12_AUTO_BREADCRUMB_OP_DECODEFRAME1,
        SetProtectedResourceSession = D3D12_AUTO_BREADCRUMB_OP_SETPROTECTEDRESOURCESESSION,
        DecodeFrame2 = D3D12_AUTO_BREADCRUMB_OP_DECODEFRAME2,
        ProcessFrames1 = D3D12_AUTO_BREADCRUMB_OP_PROCESSFRAMES1,
        BuildRaytracingAccelerationStructure = D3D12_AUTO_BREADCRUMB_OP_BUILDRAYTRACINGACCELERATIONSTRUCTURE,
        EmitRaytracingAccelerationStructurePostbuildInfo = D3D12_AUTO_BREADCRUMB_OP_EMITRAYTRACINGACCELERATIONSTRUCTUREPOSTBUILDINFO,
        CopyRaytracingAccelerationStructure = D3D12_AUTO_BREADCRUMB_OP_COPYRAYTRACINGACCELERATIONSTRUCTURE,
        DispatchRays = D3D12_AUTO_BREADCRUMB_OP_DISPATCHRAYS,
        InitializeMetaCommand = D3D12_AUTO_BREADCRUMB_OP_INITIALIZEMETACOMMAND,
        ExecuteMetaCommand = D3D12_AUTO_BREADCRUMB_OP_EXECUTEMETACOMMAND,
        EstimateMotion = D3D12_AUTO_BREADCRUMB_OP_ESTIMATEMOTION,
        ResolveMotionVectorHeap = D3D12_AUTO_BREADCRUMB_OP_RESOLVEMOTIONVECTORHEAP,
        SetPipelineState1 = D3D12_AUTO_BREADCRUMB_OP_SETPIPELINESTATE1,
        InitializeExtensionCommand = D3D12_AUTO_BREADCRUMB_OP_INITIALIZEEXTENSIONCOMMAND,
        ExecuteExtensionCommand = D3D12_AUTO_BREADCRUMB_OP_EXECUTEEXTENSIONCOMMAND,
        DispatchMesh = D3D12_AUTO_BREADCRUMB_OP_DISPATCHMESH,
        EncodeFrame = D3D12_AUTO_BREADCRUMB_OP_ENCODEFRAME,
        ResolveEncoderOutputMetadata = D3D12_AUTO_BREADCRUMB_OP_RESOLVEENCODEROUTPUTMETADATA,
        Barrier = D3D12_AUTO_BREADCRUMB_OP_BARRIER,
        BeginCommandList = D3D12_AUTO_BREADCRUMB_OP_BEGIN_COMMAND_LIST,
        DispatchGraph = D3D12_AUTO_BREADCRUMB_OP_DISPATCHGRAPH,
        SetProgram = D3D12_AUTO_BREADCRUMB_OP_SETPROGRAM,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_AUTO_BREADCRUMB_NODE
    /// </para>
    /// </summary>
    struct AutoBreadcrumbNode
    {
        const char* pCommandListDebugNameA = nullptr;
        const wchar_t* pCommandListDebugNameW = nullptr;
        const char* pCommandQueueDebugNameA = nullptr;
        const wchar_t* pCommandQueueDebugNameW = nullptr;
        ID3D12GraphicsCommandList* pCommandList = nullptr;
        ID3D12CommandQueue* pCommandQueue = nullptr;
        UInt32 BreadcrumbCount = 0;
        const UInt32* pLastBreadcrumbValue = nullptr;
        const AutoBreadcrumbOperation* pCommandHistory = nullptr;
        const struct AutoBreadcrumbNode* pNext = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_AUTO_BREADCRUMB_NODE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_BREADCRUMB_CONTEXT
    /// </para>
    /// </summary>
    struct DREDBreadcrumbContext
    {
        UINT BreadcrumbIndex = 0;
        const wchar_t* pContextString = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_BREADCRUMB_CONTEXT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_AUTO_BREADCRUMB_NODE1
    /// </para>
    /// </summary>
    struct AutoBreadcrumbNode1
    {
        const char* pCommandListDebugNameA = nullptr;
        const wchar_t* pCommandListDebugNameW = nullptr;
        const char* pCommandQueueDebugNameA = nullptr;
        const wchar_t* pCommandQueueDebugNameW = nullptr;
        ID3D12GraphicsCommandList* pCommandList = nullptr;
        ID3D12CommandQueue* pCommandQueue = nullptr;
        UInt32 BreadcrumbCount = 0;
        const UInt32* pLastBreadcrumbValue = nullptr;
        const AutoBreadcrumbOperation* pCommandHistory = nullptr;
        const struct AutoBreadcrumbNode1* pNext = nullptr;
        UINT BreadcrumbContextsCount = 0;
        DREDBreadcrumbContext* pBreadcrumbContexts = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_AUTO_BREADCRUMB_NODE1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_VERSION
    /// </para>
    /// </summary>
    enum class DREDVersion
    {
        _1_0 = D3D12_DRED_VERSION_1_0,
        _1_1 = D3D12_DRED_VERSION_1_1,
        _1_2 = D3D12_DRED_VERSION_1_2,
        _1_3 = D3D12_DRED_VERSION_1_3,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_FLAGS
    /// </para>
    /// </summary>
    enum class DREDFlags : UInt32
    {
        None = D3D12_DRED_FLAG_NONE,
        ForceEnable = D3D12_DRED_FLAG_FORCE_ENABLE,
        DisableAutoBreadcrumbs = D3D12_DRED_FLAG_DISABLE_AUTOBREADCRUMBS,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( DREDFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_ENABLEMENT
    /// </para>
    /// </summary>
    enum class DREDEnablement
    {
        SystemControlled = D3D12_DRED_ENABLEMENT_SYSTEM_CONTROLLED,
        ForcedOff = D3D12_DRED_ENABLEMENT_FORCED_OFF,
        ForcedOn = D3D12_DRED_ENABLEMENT_FORCED_ON,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_REMOVED_EXTENDED_DATA
    /// </para>
    /// </summary>
    struct DeviceRemovedExtendedData_
    {
        _In_  DREDFlags Flags = DREDFlags::None;
        _Out_  AutoBreadcrumbNode* pHeadAutoBreadcrumbNode = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEVICE_REMOVED_EXTENDED_DATA );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_ALLOCATION_TYPE
    /// </para>
    /// </summary>
    enum class DREDAllocationType
    {
        CommandQueue = D3D12_DRED_ALLOCATION_TYPE_COMMAND_QUEUE,
        CommandAllocator = D3D12_DRED_ALLOCATION_TYPE_COMMAND_ALLOCATOR,
        PipelineState = D3D12_DRED_ALLOCATION_TYPE_PIPELINE_STATE,
        CommandList = D3D12_DRED_ALLOCATION_TYPE_COMMAND_LIST,
        Fence = D3D12_DRED_ALLOCATION_TYPE_FENCE,
        DescriptorHeap = D3D12_DRED_ALLOCATION_TYPE_DESCRIPTOR_HEAP,
        Heap = D3D12_DRED_ALLOCATION_TYPE_HEAP,
        QueryHeap = D3D12_DRED_ALLOCATION_TYPE_QUERY_HEAP,
        CommandSignature = D3D12_DRED_ALLOCATION_TYPE_COMMAND_SIGNATURE,
        PipelineLibrary = D3D12_DRED_ALLOCATION_TYPE_PIPELINE_LIBRARY,
        VideoDecoder = D3D12_DRED_ALLOCATION_TYPE_VIDEO_DECODER,
        VideoProcessor = D3D12_DRED_ALLOCATION_TYPE_VIDEO_PROCESSOR,
        Resource = D3D12_DRED_ALLOCATION_TYPE_RESOURCE,
        Pass = D3D12_DRED_ALLOCATION_TYPE_PASS,
        Cryptosession = D3D12_DRED_ALLOCATION_TYPE_CRYPTOSESSION,
        Cryptosessionpolicy = D3D12_DRED_ALLOCATION_TYPE_CRYPTOSESSIONPOLICY,
        Protectedresourcesession = D3D12_DRED_ALLOCATION_TYPE_PROTECTEDRESOURCESESSION,
        VideoDecoder_heap = D3D12_DRED_ALLOCATION_TYPE_VIDEO_DECODER_HEAP,
        CommandPool = D3D12_DRED_ALLOCATION_TYPE_COMMAND_POOL,
        CommandRecorder = D3D12_DRED_ALLOCATION_TYPE_COMMAND_RECORDER,
        StateObject = D3D12_DRED_ALLOCATION_TYPE_STATE_OBJECT,
        Metacommand = D3D12_DRED_ALLOCATION_TYPE_METACOMMAND,
        Schedulinggroup = D3D12_DRED_ALLOCATION_TYPE_SCHEDULINGGROUP,
        VideoMotionEstimator = D3D12_DRED_ALLOCATION_TYPE_VIDEO_MOTION_ESTIMATOR,
        VideoMotionVectorHeap = D3D12_DRED_ALLOCATION_TYPE_VIDEO_MOTION_VECTOR_HEAP,
        VideoExtension_command = D3D12_DRED_ALLOCATION_TYPE_VIDEO_EXTENSION_COMMAND,
        VideoEncoder = D3D12_DRED_ALLOCATION_TYPE_VIDEO_ENCODER,
        VideoEncoder_heap = D3D12_DRED_ALLOCATION_TYPE_VIDEO_ENCODER_HEAP,
        Invalid = D3D12_DRED_ALLOCATION_TYPE_INVALID,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_ALLOCATION_NODE
    /// </para>
    /// </summary>
    struct DREDAllocationNode
    {
        const char* ObjectNameA = nullptr;
        const wchar_t* ObjectNameW = nullptr;
        DREDAllocationType AllocationType = DREDAllocationType::CommandQueue;
        const struct DREDAllocationNode* pNext = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_ALLOCATION_NODE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_ALLOCATION_NODE1
    /// </para>
    /// </summary>
    struct DREDAllocationNode1
    {
        const char* ObjectNameA = nullptr;
        const wchar_t* ObjectNameW = nullptr;
        DREDAllocationType AllocationType = DREDAllocationType::CommandQueue;
        const struct DREDAllocationNode1* pNext = nullptr;
        const IUnknown* pObject = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_ALLOCATION_NODE1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT
    /// </para>
    /// </summary>
    struct DREDAutoBreadcrumbsOutput
    {
        _Out_  const AutoBreadcrumbNode* pHeadAutoBreadcrumbNode;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1
    /// </para>
    /// </summary>
    struct DREDAutoBreadcrumbsOutput1
    {
        _Out_  const AutoBreadcrumbNode1* pHeadAutoBreadcrumbNode = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_PAGE_FAULT_OUTPUT
    /// </para>
    /// </summary>
    struct DREDPageFaultOutput
    {
        GPUVirtualAddress PageFaultVA;
        _Out_  const DREDAllocationNode* pHeadExistingAllocationNode = nullptr;
        _Out_  const DREDAllocationNode* pHeadRecentFreedAllocationNode = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_PAGE_FAULT_OUTPUT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_PAGE_FAULT_OUTPUT1
    /// </para>
    /// </summary>
    struct DREDPageFaultOutput1
    {
        GPUVirtualAddress PageFaultVA;
        _Out_  const DREDAllocationNode1* pHeadExistingAllocationNode = nullptr;
        _Out_  const DREDAllocationNode1* pHeadRecentFreedAllocationNode = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_PAGE_FAULT_OUTPUT1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_PAGE_FAULT_FLAGS
    /// </para>
    /// </summary>
    enum class DREDPageFaultFlags : UInt32
    {
        None = D3D12_DRED_PAGE_FAULT_FLAGS_NONE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( DREDPageFaultFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_DEVICE_STATE
    /// </para>
    /// </summary>
    enum class DREDDeviceState
    {
        Unknown = D3D12_DRED_DEVICE_STATE_UNKNOWN,
        Hung = D3D12_DRED_DEVICE_STATE_HUNG,
        Fault = D3D12_DRED_DEVICE_STATE_FAULT,
        PageFault = D3D12_DRED_DEVICE_STATE_PAGEFAULT,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DRED_PAGE_FAULT_OUTPUT2
    /// </para>
    /// </summary>
    struct DREDPageFaultOutput2
    {
        GPUVirtualAddress PageFaultVA;
        _Out_  const DREDAllocationNode1* pHeadExistingAllocationNode = nullptr;
        _Out_  const DREDAllocationNode1* pHeadRecentFreedAllocationNode = nullptr;
        DREDPageFaultFlags PageFaultFlags = DREDPageFaultFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DRED_PAGE_FAULT_OUTPUT2 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_REMOVED_EXTENDED_DATA1
    /// </para>
    /// </summary>
    struct DeviceRemovedExtendedData1_
    {
        HRESULT DeviceRemovedReason = 0;
        DREDAutoBreadcrumbsOutput AutoBreadcrumbsOutput;
        DREDPageFaultOutput PageFaultOutput;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEVICE_REMOVED_EXTENDED_DATA1 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_REMOVED_EXTENDED_DATA2
    /// </para>
    /// </summary>
    struct DeviceRemovedExtendedData2_
    {
        HRESULT DeviceRemovedReason = 0;
        DREDAutoBreadcrumbsOutput1 AutoBreadcrumbsOutput;
        DREDPageFaultOutput1 PageFaultOutput;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEVICE_REMOVED_EXTENDED_DATA2 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_REMOVED_EXTENDED_DATA3
    /// </para>
    /// </summary>
    struct DeviceRemovedExtendedData3_
    {
        HRESULT DeviceRemovedReason = 0;
        DREDAutoBreadcrumbsOutput1 AutoBreadcrumbsOutput;
        DREDPageFaultOutput2 PageFaultOutput;
        DREDDeviceState DeviceState = DREDDeviceState::Unknown;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEVICE_REMOVED_EXTENDED_DATA3 );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_VERSIONED_DEVICE_REMOVED_EXTENDED_DATA
    /// </para>
    /// </summary>
    struct VersionedDeviceRemovedExtendedData
    {
        DREDVersion Version;
        union
        {
            DeviceRemovedExtendedData_ Dred_1_0;
            DeviceRemovedExtendedData1_ Dred_1_1;
            DeviceRemovedExtendedData2_ Dred_1_2;
            DeviceRemovedExtendedData3_ Dred_1_3;
        };
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_BACKGROUND_PROCESSING_MODE
    /// </para>
    /// </summary>
    enum class BackgroundProcessingMode
    {
        Allowed = D3D12_BACKGROUND_PROCESSING_MODE_ALLOWED,
        AllowIntrusiveMeasurements = D3D12_BACKGROUND_PROCESSING_MODE_ALLOW_INTRUSIVE_MEASUREMENTS,
        DisableBackgroundWork = D3D12_BACKGROUND_PROCESSING_MODE_DISABLE_BACKGROUND_WORK,
        DisableProfilingBySystem = D3D12_BACKGROUND_PROCESSING_MODE_DISABLE_PROFILING_BY_SYSTEM,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MEASUREMENTS_ACTION
    /// </para>
    /// </summary>
    enum class MeasurementsAction
    {
        KeepAll = D3D12_MEASUREMENTS_ACTION_KEEP_ALL,
        CommitResults = D3D12_MEASUREMENTS_ACTION_COMMIT_RESULTS,
        CommitResultsHighPriority = D3D12_MEASUREMENTS_ACTION_COMMIT_RESULTS_HIGH_PRIORITY,
        DiscardPrevious = D3D12_MEASUREMENTS_ACTION_DISCARD_PREVIOUS,
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT
    /// </para>
    /// </summary>
    struct FeatureDataProtectedResourceSessionTypeCount
    {
        UINT NodeIndex = 0;
        UINT Count = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES
    /// </para>
    /// </summary>
    struct FeatureDataProtectedResourceSessionTypes
    {
        UINT NodeIndex = 0;
        UINT Count = 0;
        Guid* pTypes = nullptr;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PROTECTED_RESOURCE_SESSION_DESC1
    /// </para>
    /// </summary>
    struct ProtectedResourceSessionDesc1
    {
        UINT NodeMask = 0;
        ProtectedResourceSessionFlags Flags = ProtectedResourceSessionFlags::None;
        Guid ProtectionType;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_PROTECTED_RESOURCE_SESSION_DESC1 );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE
    /// </para>
    /// </summary>
    enum class RenderPassBeginningAccessType
    {
        Discard = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_DISCARD,
        Preserve = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE,
        Clear = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR,
        NoAccess = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_NO_ACCESS,
        PreserveLocalRender = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE_LOCAL_RENDER,
        PreserveLocalSRV = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE_LOCAL_SRV,
        PreserveLocalUAV = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE_LOCAL_UAV,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS
    /// </para>
    /// </summary>
    struct RenderPassBeginningAccessClearParameters
    {
        D3D12::ClearValue ClearValue;
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_BEGINNING_ACCESS_PRESERVE_LOCAL_PARAMETERS
    /// </para>
    /// </summary>
    struct RenderPassBeginningAccessPreserveLocalParameters
    {
        UINT AdditionalWidth = 0;
        UINT AdditionalHeight = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_BEGINNING_ACCESS_PRESERVE_LOCAL_PARAMETERS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_BEGINNING_ACCESS
    /// </para>
    /// </summary>
    struct RenderPassBeginningAccess
    {
        RenderPassBeginningAccessType Type = RenderPassBeginningAccessType::Discard;
        union
        {
            RenderPassBeginningAccessClearParameters Clear;
            RenderPassBeginningAccessPreserveLocalParameters PreserveLocal;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_BEGINNING_ACCESS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_ENDING_ACCESS_TYPE
    /// </para>
    /// </summary>
    enum class RenderPassEndingAccessType
    {
        Discard = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD,
        Preserve = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE,
        Resolve = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_RESOLVE,
        NoAccess = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS,
        PreserveLocalRender = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE_LOCAL_RENDER,
        PreserveLocalSRV = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE_LOCAL_SRV,
        PreserveLocalUAV = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE_LOCAL_UAV,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS
    /// </para>
    /// </summary>
    struct RenderPassEndingAccessResolveSubresourceParameters
    {
        UINT SrcSubresource = 0;
        UINT DstSubresource = 0;
        UINT DstX = 0;
        UINT DstY = 0;
        Rectangle SrcRect;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_SUBRESOURCE_PARAMETERS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS
    /// </para>
    /// </summary>
    struct RenderPassEndingAccessResolveParameters
    {
        ID3D12Resource* pSrcResource = nullptr;
        ID3D12Resource* pDstResource = nullptr;
        UINT SubresourceCount = 0;
        _Field_size_full_( SubresourceCount )  const RenderPassEndingAccessResolveSubresourceParameters* pSubresourceParameters = nullptr;
        DXGI::Format Format = DXGI::Format::Unknown;
        D3D12::ResolveMode ResolveMode = D3D12::ResolveMode::Decompress;
        BOOL PreserveResolveSource = FALSE;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_ENDING_ACCESS_PRESERVE_LOCAL_PARAMETERS
    /// </para>
    /// </summary>
    struct RenderPassEndingAccessPreserveLocalParameters
    {
        UINT AdditionalWidth = 0;
        UINT AdditionalHeight = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_ENDING_ACCESS_PRESERVE_LOCAL_PARAMETERS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_ENDING_ACCESS
    /// </para>
    /// </summary>
    struct RenderPassEndingAccess
    {
        RenderPassEndingAccessType Type = RenderPassEndingAccessType::Discard;
        union
        {
            D3D12_RENDER_PASS_ENDING_ACCESS_RESOLVE_PARAMETERS Resolve;
            D3D12_RENDER_PASS_ENDING_ACCESS_PRESERVE_LOCAL_PARAMETERS PreserveLocal;
        };

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_ENDING_ACCESS );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_RENDER_TARGET_DESC
    /// </para>
    /// </summary>
    struct RenderPassRenderTargetDesc
    {
        CPUDescriptorHandle cpuDescriptor;
        RenderPassBeginningAccess BeginningAccess;
        RenderPassEndingAccess EndingAccess;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_RENDER_TARGET_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_DEPTH_STENCIL_DESC
    /// </para>
    /// </summary>
    struct RenderPassDepthStencilDesc
    {
        CPUDescriptorHandle cpuDescriptor;
        RenderPassBeginningAccess DepthBeginningAccess;
        RenderPassBeginningAccess StencilBeginningAccess;
        RenderPassEndingAccess DepthEndingAccess;
        RenderPassEndingAccess StencilEndingAccess;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_RENDER_PASS_DEPTH_STENCIL_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_RENDER_PASS_FLAGS
    /// </para>
    /// </summary>
    enum class RenderPassFlags : UInt32
    {
        None = D3D12_RENDER_PASS_FLAG_NONE,
        AllowUAVWrites = D3D12_RENDER_PASS_FLAG_ALLOW_UAV_WRITES,
        SuspendingPass = D3D12_RENDER_PASS_FLAG_SUSPENDING_PASS,
        ResumingPass = D3D12_RENDER_PASS_FLAG_RESUMING_PASS,
        BindReadOnlyDepth = D3D12_RENDER_PASS_FLAG_BIND_READ_ONLY_DEPTH,
        BindReadOnlyStencil = D3D12_RENDER_PASS_FLAG_BIND_READ_ONLY_STENCIL,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( RenderPassFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_DISPATCH_RAYS_DESC
    /// </para>
    /// </summary>
    struct DispatchRaysDesc
    {
        GPUVirtualAddressRange RayGenerationShaderRecord;
        GPUVirtualAddressRangeAndStride MissShaderTable;
        GPUVirtualAddressRangeAndStride HitGroupTable;
        GPUVirtualAddressRangeAndStride CallableShaderTable;
        UINT Width = 0;
        UINT Height = 0;
        UINT Depth = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DISPATCH_RAYS_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SET_WORK_GRAPH_FLAGS
    /// </para>
    /// </summary>
    enum class SetWorkGraphFlags : UInt32
    {
        None = D3D12_SET_WORK_GRAPH_FLAG_NONE,
        Initialize = D3D12_SET_WORK_GRAPH_FLAG_INITIALIZE,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SetWorkGraphFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_SET_WORK_GRAPH_DESC
    /// </para>
    /// </summary>
    struct SetWorkGraphDesc
    {
        ProgramIdentifier ProgramIdentifier;
        SetWorkGraphFlags Flags = SetWorkGraphFlags::None;
        GPUVirtualAddressRange BackingMemory;
        GPUVirtualAddressRangeAndStride NodeLocalRootArgumentsTable;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SET_WORK_GRAPH_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SET_RAYTRACING_PIPELINE_DESC
    /// </para>
    /// </summary>
    struct SetRaytracingPipelineDesc
    {
        D3D12_PROGRAM_IDENTIFIER ProgramIdentifier;
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SET_RAYTRACING_PIPELINE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SET_GENERIC_PIPELINE_DESC
    /// </para>
    /// </summary>
    struct SetGenericPipelineDesc
    {
        ProgramIdentifier ProgramIdentifier;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SET_GENERIC_PIPELINE_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_PROGRAM_TYPE
    /// </para>
    /// </summary>
    enum class ProgramType
    {
        GenericPipeline = D3D12_PROGRAM_TYPE_GENERIC_PIPELINE,
        RaytracingPipeline = D3D12_PROGRAM_TYPE_RAYTRACING_PIPELINE,
        WorkGraph = D3D12_PROGRAM_TYPE_WORK_GRAPH,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SET_PROGRAM_DESC
    /// </para>
    /// </summary>
    struct SetProgramDesc
    {
        ProgramType Type = ProgramType::GenericPipeline;
        union
        {
            SetGenericPipelineDesc GenericPipeline;
            SetRaytracingPipelineDesc RaytracingPipeline;
            SetWorkGraphDesc WorkGraph;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SET_PROGRAM_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DISPATCH_MODE
    /// </para>
    /// </summary>
    enum class DispatchMode
    {
        NodeCPUInput = D3D12_DISPATCH_MODE_NODE_CPU_INPUT,
        NodeGPUInput = D3D12_DISPATCH_MODE_NODE_GPU_INPUT,
        MultiNodeCPUInput = D3D12_DISPATCH_MODE_MULTI_NODE_CPU_INPUT,
        MultiNodeGPUInput = D3D12_DISPATCH_MODE_MULTI_NODE_GPU_INPUT,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_CPU_INPUT
    /// </para>
    /// </summary>
    struct NodeCPUInput
    {
        UINT EntrypointIndex = 0;
        UINT NumRecords = 0;
        void* pRecords = nullptr;
        UINT64 RecordStrideInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_NODE_CPU_INPUT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_NODE_GPU_INPUT
    /// </para>
    /// </summary>
    struct NodeGPUInput
    {
        UINT EntrypointIndex = 0;
        UINT NumRecords = 0;
        GPUVirtualAddressAndStride Records;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_NODE_GPU_INPUT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MULTI_NODE_CPU_INPUT
    /// </para>
    /// </summary>
    struct MultiNodeCPUInput
    {
        UINT NumNodeInputs = 0;
        NodeCPUInput* pNodeInputs = nullptr;
        UINT64 NodeInputStrideInBytes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_MULTI_NODE_CPU_INPUT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MULTI_NODE_GPU_INPUT
    /// </para>
    /// </summary>
    struct MultiNodeGPUInput
    {
        UINT NumNodeInputs = 0;
        GPUVirtualAddressAndStride NodeInputs;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_MULTI_NODE_GPU_INPUT );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DISPATCH_GRAPH_DESC
    /// </para>
    /// </summary>
    struct DispatchGraphDesc
    {
        DispatchMode Mode = DispatchMode::NodeCPUInput;
        union
        {
            NodeCPUInput NodeCPUInput;
            GPUVirtualAddress NodeGPUInput;
            MultiNodeCPUInput MultiNodeCPUInput;
            GPUVirtualAddress MultiNodeGPUInput;
        };
        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DISPATCH_GRAPH_DESC );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_CACHE_MODE
    /// </para>
    /// </summary>
    enum class ShaderCacheMode
    {
        Memory = D3D12_SHADER_CACHE_MODE_MEMORY,
        Disk = D3D12_SHADER_CACHE_MODE_DISK,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_CACHE_FLAGS
    /// </para>
    /// </summary>
    enum class ShaderCacheFlags
    {
        None = D3D12_SHADER_CACHE_FLAG_NONE,
        DriverVersioned = D3D12_SHADER_CACHE_FLAG_DRIVER_VERSIONED,
        UseWorkingDir = D3D12_SHADER_CACHE_FLAG_USE_WORKING_DIR,
    };

    DEFINE_ENUM_FLAG_OPERATORS( D3D12_SHADER_CACHE_FLAGS );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_CACHE_SESSION_DESC
    /// </para>
    /// </summary>
    struct ShaderCacheSessionDesc
    {
        Guid Identifier;
        ShaderCacheMode Mode = ShaderCacheMode::Memory;
        ShaderCacheFlags Flags = ShaderCacheFlags::None;
        UINT MaximumInMemoryCacheSizeBytes = 0;
        UINT MaximumInMemoryCacheEntries = 0;
        UINT MaximumValueFileSizeBytes = 0;
        UINT64 Version = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SHADER_CACHE_SESSION_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BARRIER_LAYOUT
    /// </para>
    /// </summary>
    enum class BarrierLayout
    {
        Undefined = D3D12_BARRIER_LAYOUT_UNDEFINED,
        Common = D3D12_BARRIER_LAYOUT_COMMON,
        Present = D3D12_BARRIER_LAYOUT_PRESENT,
        GenericRead = D3D12_BARRIER_LAYOUT_GENERIC_READ,
        RenderTarget = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
        UnorderedAccess = D3D12_BARRIER_LAYOUT_UNORDERED_ACCESS,
        DepthStencilWrite = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
        DepthStencilRead = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
        ShaderResource = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
        CopySource = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
        CopyDest = D3D12_BARRIER_LAYOUT_COPY_DEST,
        ResolveSource = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
        ResolveDest = D3D12_BARRIER_LAYOUT_RESOLVE_DEST,
        ShadingRate_source = D3D12_BARRIER_LAYOUT_SHADING_RATE_SOURCE,
        VideoDecodeRead = D3D12_BARRIER_LAYOUT_VIDEO_DECODE_READ,
        VideoDecodeWrite = D3D12_BARRIER_LAYOUT_VIDEO_DECODE_WRITE,
        VideoProcessRead = D3D12_BARRIER_LAYOUT_VIDEO_PROCESS_READ,
        VideoProcessWrite = D3D12_BARRIER_LAYOUT_VIDEO_PROCESS_WRITE,
        VideoEncodeRead = D3D12_BARRIER_LAYOUT_VIDEO_ENCODE_READ,
        VideoEncodeErite = D3D12_BARRIER_LAYOUT_VIDEO_ENCODE_WRITE,
        DirectQueueCommon = D3D12_BARRIER_LAYOUT_DIRECT_QUEUE_COMMON,
        DirectQueueGenericRead = D3D12_BARRIER_LAYOUT_DIRECT_QUEUE_GENERIC_READ,
        DirectQueueUnorderedAccess = D3D12_BARRIER_LAYOUT_DIRECT_QUEUE_UNORDERED_ACCESS,
        DirectQueueShaderResource = D3D12_BARRIER_LAYOUT_DIRECT_QUEUE_SHADER_RESOURCE,
        DirectQueueCopySource = D3D12_BARRIER_LAYOUT_DIRECT_QUEUE_COPY_SOURCE,
        DirectQueueCopyDest = D3D12_BARRIER_LAYOUT_DIRECT_QUEUE_COPY_DEST,
        ComputeQueueCommon = D3D12_BARRIER_LAYOUT_COMPUTE_QUEUE_COMMON,
        ComputeQueueGenericRead = D3D12_BARRIER_LAYOUT_COMPUTE_QUEUE_GENERIC_READ,
        ComputeQueueUnorderedAccess = D3D12_BARRIER_LAYOUT_COMPUTE_QUEUE_UNORDERED_ACCESS,
        ComputeQueueShaderResource = D3D12_BARRIER_LAYOUT_COMPUTE_QUEUE_SHADER_RESOURCE,
        ComputeQueueCopySource = D3D12_BARRIER_LAYOUT_COMPUTE_QUEUE_COPY_SOURCE,
        ComputeQueueCopyDest = D3D12_BARRIER_LAYOUT_COMPUTE_QUEUE_COPY_DEST,
        VideoQueueCommon = D3D12_BARRIER_LAYOUT_VIDEO_QUEUE_COMMON,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BARRIER_SYNC
    /// </para>
    /// </summary>
    enum class BarrierSync : Int32
    {
        None = D3D12_BARRIER_SYNC_NONE,
        All = D3D12_BARRIER_SYNC_ALL,
        Draw = D3D12_BARRIER_SYNC_DRAW,
        IndexInput = D3D12_BARRIER_SYNC_INDEX_INPUT,
        VertexShading = D3D12_BARRIER_SYNC_VERTEX_SHADING,
        PixelShading = D3D12_BARRIER_SYNC_PIXEL_SHADING,
        DepthStencil = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
        RenderTarget = D3D12_BARRIER_SYNC_RENDER_TARGET,
        ComputeShading = D3D12_BARRIER_SYNC_COMPUTE_SHADING,
        Raytracing = D3D12_BARRIER_SYNC_RAYTRACING,
        Copy = D3D12_BARRIER_SYNC_COPY,
        Resolve = D3D12_BARRIER_SYNC_RESOLVE,
        ExecuteIndirect = D3D12_BARRIER_SYNC_EXECUTE_INDIRECT,
        Predication = D3D12_BARRIER_SYNC_PREDICATION,
        AllShading = D3D12_BARRIER_SYNC_ALL_SHADING,
        NonPixelShading = D3D12_BARRIER_SYNC_NON_PIXEL_SHADING,
        EmitRaytracingAccelerationStructurePostbuildInfo = D3D12_BARRIER_SYNC_EMIT_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO,
        ClearUnorderedAccessView = D3D12_BARRIER_SYNC_CLEAR_UNORDERED_ACCESS_VIEW,
        VideoDecode = D3D12_BARRIER_SYNC_VIDEO_DECODE,
        VideoProcess = D3D12_BARRIER_SYNC_VIDEO_PROCESS,
        VideoEncode = D3D12_BARRIER_SYNC_VIDEO_ENCODE,
        BuildRaytracingAccelerationStructure = D3D12_BARRIER_SYNC_BUILD_RAYTRACING_ACCELERATION_STRUCTURE,
        CopyRaytracingAccelerationStructure = D3D12_BARRIER_SYNC_COPY_RAYTRACING_ACCELERATION_STRUCTURE,
        Split = D3D12_BARRIER_SYNC_SPLIT,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( BarrierSync, Int32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_BARRIER_ACCESS
    /// </para>
    /// </summary>
    enum class BarrierAccess : Int32
    {
        Common = D3D12_BARRIER_ACCESS_COMMON,
        VertexBuffer = D3D12_BARRIER_ACCESS_VERTEX_BUFFER,
        ConstantBuffer = D3D12_BARRIER_ACCESS_CONSTANT_BUFFER,
        IndexBuffer = D3D12_BARRIER_ACCESS_INDEX_BUFFER,
        RenderTarget = D3D12_BARRIER_ACCESS_RENDER_TARGET,
        UnorderedAccess = D3D12_BARRIER_ACCESS_UNORDERED_ACCESS,
        DepthStencilWrite = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
        DepthStencilRead = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_READ,
        ShaderResource = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
        StreamOutput = D3D12_BARRIER_ACCESS_STREAM_OUTPUT,
        IndirectArgument = D3D12_BARRIER_ACCESS_INDIRECT_ARGUMENT,
        Predication = D3D12_BARRIER_ACCESS_PREDICATION,
        CopyDest = D3D12_BARRIER_ACCESS_COPY_DEST,
        CopySource = D3D12_BARRIER_ACCESS_COPY_SOURCE,
        ResolveDest = D3D12_BARRIER_ACCESS_RESOLVE_DEST,
        ResolveSource = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
        RaytracingAccelerationStructureRead = D3D12_BARRIER_ACCESS_RAYTRACING_ACCELERATION_STRUCTURE_READ,
        RaytracingAccelerationStructureWrite = D3D12_BARRIER_ACCESS_RAYTRACING_ACCELERATION_STRUCTURE_WRITE,
        ShadingRateSource = D3D12_BARRIER_ACCESS_SHADING_RATE_SOURCE,
        VideoDecodeRead = D3D12_BARRIER_ACCESS_VIDEO_DECODE_READ,
        VideoDecodeWrite = D3D12_BARRIER_ACCESS_VIDEO_DECODE_WRITE,
        VideoProcessRead = D3D12_BARRIER_ACCESS_VIDEO_PROCESS_READ,
        VideoProcessWrite = D3D12_BARRIER_ACCESS_VIDEO_PROCESS_WRITE,
        VideoEncodeRead = D3D12_BARRIER_ACCESS_VIDEO_ENCODE_READ,
        VideoEncodeWrite = D3D12_BARRIER_ACCESS_VIDEO_ENCODE_WRITE,
        NoAccess = D3D12_BARRIER_ACCESS_NO_ACCESS,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( BarrierAccess, Int32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_BARRIER_TYPE
    /// </para>
    /// </summary>
    enum class BarrierType
    {
        Global = D3D12_BARRIER_TYPE_GLOBAL,
        Texture = D3D12_BARRIER_TYPE_TEXTURE,
        Buffer = D3D12_BARRIER_TYPE_BUFFER,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXTURE_BARRIER_FLAGS
    /// </para>
    /// </summary>
    enum class TextureBarrierFlags : UInt32
    {
        None = D3D12_TEXTURE_BARRIER_FLAG_NONE,
        Discard = D3D12_TEXTURE_BARRIER_FLAG_DISCARD,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( TextureBarrierFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_BARRIER_SUBRESOURCE_RANGE
    /// </para>
    /// </summary>
    struct BarrierSubresourceRange
    {
        UINT IndexOrFirstMipLevel = 0;
        UINT NumMipLevels = 0;
        UINT FirstArraySlice = 0;
        UINT NumArraySlices = 0;
        UINT FirstPlane = 0;
        UINT NumPlanes = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BARRIER_SUBRESOURCE_RANGE );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_GLOBAL_BARRIER
    /// </para>
    /// </summary>
    struct GlobalBarrier
    {
        BarrierSync SyncBefore = BarrierSync::None;
        BarrierSync SyncAfter = BarrierSync::None;
        BarrierAccess AccessBefore = BarrierAccess::Common;
        BarrierAccess AccessAfter = BarrierAccess::Common;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_GLOBAL_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_TEXTURE_BARRIER
    /// </para>
    /// </summary>
    struct TextureBarrier
    {
        BarrierSync SyncBefore = BarrierSync::None;
        BarrierSync SyncAfter = BarrierSync::None;
        BarrierAccess AccessBefore = BarrierAccess::Common;
        BarrierAccess AccessAfter = BarrierAccess::Common;
        BarrierLayout LayoutBefore = BarrierLayout::Common;
        BarrierLayout LayoutAfter = BarrierLayout::Common;
        _In_  ID3D12Resource* pResource = nullptr;
        BarrierSubresourceRange Subresources;
        TextureBarrierFlags Flags = TextureBarrierFlags::None;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_TEXTURE_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BUFFER_BARRIER
    /// </para>
    /// </summary>
    struct BufferBarrier
    {
        BarrierSync SyncBefore = BarrierSync::None;
        BarrierSync SyncAfter = BarrierSync::None;
        BarrierAccess AccessBefore = BarrierAccess::Common;
        BarrierAccess AccessAfter = BarrierAccess::Common;
        _In_  ID3D12Resource* pResource = nullptr;
        UINT64 Offset = 0;
        UINT64 Size = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BUFFER_BARRIER );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_BARRIER_GROUP
    /// </para>
    /// </summary>
    struct BarrierGroup
    {
        BarrierType Type = BarrierType::Global;
        UINT32 NumBarriers = 0;
        union
        {
            _In_reads_( NumBarriers )  const GlobalBarrier* pGlobalBarriers;
            _In_reads_( NumBarriers )  const TextureBarrier* pTextureBarriers;
            _In_reads_( NumBarriers )  const BufferBarrier* pBufferBarriers;
        };

        BarrierGroup()
            : pGlobalBarriers(nullptr)
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_BARRIER_GROUP );
    };


    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_CACHE_KIND_FLAGS
    /// </para>
    /// </summary>
    enum class ShaderCacheKindFlags : UInt32
    {
        ImplicitD3DCacheForDriver = D3D12_SHADER_CACHE_KIND_FLAG_IMPLICIT_D3D_CACHE_FOR_DRIVER,
        ImplicitD3DConversions = D3D12_SHADER_CACHE_KIND_FLAG_IMPLICIT_D3D_CONVERSIONS,
        ImplicitDriverManaged = D3D12_SHADER_CACHE_KIND_FLAG_IMPLICIT_DRIVER_MANAGED,
        ApplicationManaged = D3D12_SHADER_CACHE_KIND_FLAG_APPLICATION_MANAGED,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ShaderCacheKindFlags,UInt32 );
    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADER_CACHE_CONTROL_FLAGS
    /// </para>
    /// </summary>
    enum class ShaderCacheControlFlags : UInt32
    {
        Disable = D3D12_SHADER_CACHE_CONTROL_FLAG_DISABLE,
        Enable = D3D12_SHADER_CACHE_CONTROL_FLAG_ENABLE,
        Clear = D3D12_SHADER_CACHE_CONTROL_FLAG_CLEAR,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ShaderCacheControlFlags, UInt32 );

    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_FACTORY_FLAGS
    /// </para>
    /// </summary>
    enum class DeviceFactoryFlags : UInt32
    {
        None = D3D12_DEVICE_FACTORY_FLAG_NONE,
        AllowReturningExistingDevice = D3D12_DEVICE_FACTORY_FLAG_ALLOW_RETURNING_EXISTING_DEVICE,
        AllowReturningIncompatibleExistingDevice = D3D12_DEVICE_FACTORY_FLAG_ALLOW_RETURNING_INCOMPATIBLE_EXISTING_DEVICE,
        DisallowStoringNewDeviceAsSingleton = D3D12_DEVICE_FACTORY_FLAG_DISALLOW_STORING_NEW_DEVICE_AS_SINGLETON,
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DeviceFactoryFlags, UInt32 );


    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_FLAGS
    /// </para>
    /// </summary>
    enum class DeviceFlags : UInt32
    {
        None = D3D12_DEVICE_FLAG_NONE,
        DebugLayerEnabled = D3D12_DEVICE_FLAG_DEBUG_LAYER_ENABLED,
        GPUBasedValidationEnabled = D3D12_DEVICE_FLAG_GPU_BASED_VALIDATION_ENABLED,
        SynchronizedCommandQueueValidationDisabled = D3D12_DEVICE_FLAG_SYNCHRONIZED_COMMAND_QUEUE_VALIDATION_DISABLED,
        DREDAutoBreadcrumbsEnabled = D3D12_DEVICE_FLAG_DRED_AUTO_BREADCRUMBS_ENABLED,
        DREDPageFaultReportingEnabled = D3D12_DEVICE_FLAG_DRED_PAGE_FAULT_REPORTING_ENABLED,
        DREDWatsonReportingEnabled = D3D12_DEVICE_FLAG_DRED_WATSON_REPORTING_ENABLED,
        DREDBreadcrumbContextEnabled = D3D12_DEVICE_FLAG_DRED_BREADCRUMB_CONTEXT_ENABLED,
        DREDUseMarkersOnlyBreadcrumbs = D3D12_DEVICE_FLAG_DRED_USE_MARKERS_ONLY_BREADCRUMBS,
        ShaderInstrumentationEnabled = D3D12_DEVICE_FLAG_SHADER_INSTRUMENTATION_ENABLED,
        AutoDebugNameEnabled = D3D12_DEVICE_FLAG_AUTO_DEBUG_NAME_ENABLED,
        ForceLegacyStateValidation = D3D12_DEVICE_FLAG_FORCE_LEGACY_STATE_VALIDATION,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( DeviceFlags, UInt32 );
    
    /// <summary>
    /// <para>
    /// Alias for D3D12_DEVICE_CONFIGURATION_DESC
    /// </para>
    /// </summary>
    struct DeviceConfigurationDesc
    {
        DeviceFlags Flags;
        UINT GpuBasedValidationFlags = 0;
        UINT SDKVersion = 0;
        UINT NumEnabledExperimentalFeatures = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DEVICE_CONFIGURATION_DESC );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_AXIS_SHADING_RATE
    /// </para>
    /// </summary>
    enum class AxisShadingRate
    {
        X1 = D3D12_AXIS_SHADING_RATE_1X,
        X2 = D3D12_AXIS_SHADING_RATE_2X,
        X4 = D3D12_AXIS_SHADING_RATE_4X,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADING_RATE
    /// </para>
    /// </summary>
    enum class ShadingRate
    {
        _1X1 = D3D12_SHADING_RATE_1X1,
        _1X2 = D3D12_SHADING_RATE_1X2,
        _2X1 = D3D12_SHADING_RATE_2X1,
        _2X2 = D3D12_SHADING_RATE_2X2,
        _2X4 = D3D12_SHADING_RATE_2X4,
        _4X2 = D3D12_SHADING_RATE_4X2,
        _4X4 = D3D12_SHADING_RATE_4X4,
    };

    constexpr int ShadingRateXAxisShift = 2;
    constexpr int ShadingRateValidMask = 3;

    constexpr Int32 MakeCoarseShadingRate( Int32 x, Int32 y )
    {
        return D3D12_MAKE_COARSE_SHADING_RATE( x, y );
    }

    constexpr ShadingRate MakeCoarseShadingRate( AxisShadingRate x, AxisShadingRate y )
    {
        return static_cast< ShadingRate >( MakeCoarseShadingRate( static_cast<int>( x ), static_cast< int >( y ) ) );
    }


    constexpr Int32 GetCoarseShadingRateXAxis( Int32 x )
    {
        return D3D12_GET_COARSE_SHADING_RATE_X_AXIS( x );
    }

    constexpr AxisShadingRate GetCoarseShadingRateXAxis( ShadingRate x )
    {
        return static_cast< AxisShadingRate >( GetCoarseShadingRateXAxis( static_cast<Int32>( x ) ) );
    }

    constexpr Int32 GetCoarseShadingRateYAxis( Int32 y )
    {
        return D3D12_GET_COARSE_SHADING_RATE_Y_AXIS( y );
    }

    constexpr AxisShadingRate GetCoarseShadingRateYAxis( ShadingRate y )
    {
        return static_cast< AxisShadingRate >( GetCoarseShadingRateYAxis( static_cast< Int32 >( y ) ) );
    }

    

    /// <summary>
    /// <para>
    /// Alias for D3D12_SHADING_RATE_COMBINER
    /// </para>
    /// </summary>
    enum class ShadingRateCombiner
    {
        Passthrough = D3D12_SHADING_RATE_COMBINER_PASSTHROUGH,
        Override = D3D12_SHADING_RATE_COMBINER_OVERRIDE,
        Min = D3D12_SHADING_RATE_COMBINER_MIN,
        Max = D3D12_SHADING_RATE_COMBINER_MAX,
        Sum = D3D12_SHADING_RATE_COMBINER_SUM,
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_DISPATCH_MESH_ARGUMENTS
    /// </para>
    /// </summary>
    struct DispatchMeshArguments
    {
        UINT ThreadGroupCountX = 0;
        UINT ThreadGroupCountY = 0;
        UINT ThreadGroupCountZ = 0;

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_DISPATCH_MESH_ARGUMENTS );
    };

    
    /// <summary>
    /// <para>
    /// Alias for D3D12_SUBRESOURCE_DATA
    /// </para>
    /// </summary>
    struct SubResourceData
    {
        const void* pData = nullptr;
        LONG_PTR RowPitch = 0;
        LONG_PTR SlicePitch = 0;

        SubResourceData( ) noexcept = default;
        SubResourceData( const void* data, LONG_PTR rowPitch ) noexcept
            : pData( data ), RowPitch( rowPitch ), SlicePitch( rowPitch )
        { }
        SubResourceData( const void* data, LONG_PTR rowPitch, LONG_PTR slicePitch ) noexcept
            : pData( data ), RowPitch( rowPitch ), SlicePitch( slicePitch )
        { }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_SUBRESOURCE_DATA );
    };

    /// <summary>
    /// <para>
    /// Alias for D3D12_MEMCPY_DEST
    /// </para>
    /// </summary>
    struct MemCopyDest
    {
        void* pData = nullptr;
        SIZE_T RowPitch = 0;
        SIZE_T SlicePitch = 0;

        MemCopyDest( ) noexcept = default;

        MemCopyDest( void* data, SIZE_T rowPitch ) noexcept
            : pData( data ), RowPitch( rowPitch ), SlicePitch( rowPitch )
        {
        }
        MemCopyDest( void* data, SIZE_T rowPitch, SIZE_T slicePitch ) noexcept
            : pData( data ), RowPitch( rowPitch ), SlicePitch( slicePitch )
        {
        }

        HWD3D12_IMPLEMENT_CONVERSIONS_TO( D3D12_MEMCPY_DEST );
    };





}

#endif
 