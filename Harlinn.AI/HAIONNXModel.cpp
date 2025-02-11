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
#include "HAIONNX.h"

namespace Harlinn::AI::ONNX
{   
    namespace
    { 
        template <typename T>
        void CopyTensorToPixelsByte( Byte* src, Byte* dst, UInt32 height, UInt32 width, UInt32 channels )
        {
            std::span<const T> srcT( reinterpret_cast< const T* >( src ), height * width / sizeof( T ) );
            size_t count = static_cast< size_t >( height ) * static_cast< size_t >( width );
            for ( size_t pixelIndex = 0; pixelIndex < count; pixelIndex++ )
            {
                dst[ pixelIndex * channels ] = static_cast<Byte>( srcT[ pixelIndex ] );
            }
        }

        // Converts an NCHW tensor buffer (batch size 1) to a pixel buffer.
        // Source: buffer of RGB planes (CHW) using float32/float16 components.
        // Target: buffer of RGB pixels (HWC) using uint8 components.
        template <typename T>
        void CopyTensorToPixels( const uint8_t* src, uint8_t* dst, uint32_t height, uint32_t width, uint32_t channels )
        {
            std::span<const T> srcT( reinterpret_cast< const T* >( src ), ( height * width ) / sizeof( T ) );

            for ( size_t pixelIndex = 0; pixelIndex < height * width; pixelIndex++ )
            {
                BYTE r = static_cast< BYTE >( std::max( 0.0f, std::min( 1.0f, ( float )srcT[ pixelIndex + 0 * height * width ] ) ) * 255.0f );
                BYTE g = static_cast< BYTE >( std::max( 0.0f, std::min( 1.0f, ( float )srcT[ pixelIndex + 1 * height * width ] ) ) * 255.0f );
                BYTE b = static_cast< BYTE >( std::max( 0.0f, std::min( 1.0f, ( float )srcT[ pixelIndex + 2 * height * width ] ) ) * 255.0f );

                dst[ pixelIndex * channels + 0 ] = b;
                dst[ pixelIndex * channels + 1 ] = g;
                dst[ pixelIndex * channels + 2 ] = r;
                dst[ pixelIndex * channels + 3 ] = 128;
            }
        }

        inline unsigned char* pixel( unsigned char* Img, int i, int j, int width, int height, int bpp )
        {
            return ( Img + ( ( i * width + j ) * bpp ) );
        }


        // Converts a pixel buffer to an NCHW tensor (batch size 1).
        // Source: buffer of RGB pixels (HWC) using uint8 components.
        // Target: buffer of RGB planes (CHW) using float32/float16 components.
        template <typename T>
        void CopyPixelsToTensor(
            std::byte* src,
            uint32_t srcWidth, uint32_t srcHeight, uint32_t rowPitch,
            std::span<std::byte> dst,
            uint32_t height,
            uint32_t width,
            uint32_t channels )
        {
            uint32_t srcChannels = rowPitch / srcWidth;
            uint32_t rowWidth = rowPitch / srcChannels;
            std::span<T> dstT( reinterpret_cast< T* >( dst.data( ) ), dst.size_bytes( ) / sizeof( T ) );

            if ( srcWidth != width || srcHeight != height )
            {
                unsigned char* Img = ( uint8_t* )src;
                float ScaledWidthRatio = srcWidth / ( float )width;
                float ScaledHeightRatio = srcHeight / ( float )height;
                uint32_t pixelIndex = 0;

                for ( int i = 0; i < height; i++ )
                {
                    for ( int j = 0; j < width; j++ )
                    {
                        // rf
                        float mappedheight = i * ScaledHeightRatio;
                        // cf
                        float mappedwidth = j * ScaledWidthRatio;
                        // ro
                        int   OriginalPosHeight = ( int )mappedheight;
                        // co
                        int   OriginalPosWidth = ( int )mappedwidth;
                        // delta r
                        float deltaheight = mappedheight - OriginalPosHeight;
                        //delta c
                        float deltawidth = mappedwidth - OriginalPosWidth;

                        unsigned char* temp1 = pixel( Img, OriginalPosHeight, OriginalPosWidth, rowWidth, srcHeight, srcChannels );
                        unsigned char* temp2 = pixel( Img, ( ( OriginalPosHeight + 1 ) >= height ? OriginalPosHeight : OriginalPosHeight + 1 ),
                            OriginalPosWidth, rowWidth, srcHeight, srcChannels );
                        unsigned char* temp3 = pixel( Img, OriginalPosHeight, OriginalPosWidth + 1, rowWidth, srcHeight, srcChannels );
                        unsigned char* temp4 = pixel( Img, ( ( OriginalPosHeight + 1 ) >= srcHeight ? OriginalPosHeight : OriginalPosHeight + 1 ),
                            ( OriginalPosWidth + 1 ) >= rowWidth ? OriginalPosWidth : ( OriginalPosWidth + 1 ), rowWidth, srcHeight, srcChannels );

                        float b =
                            ( *( temp1 + 0 ) * ( 1 - deltaheight ) * ( 1 - deltawidth )
                                + *( temp2 + 0 ) * ( deltaheight ) * ( 1 - deltawidth )
                                + *( temp3 + 0 ) * ( 1 - deltaheight ) * ( deltawidth )
                                +*( temp4 + 0 ) * ( deltaheight ) * ( deltawidth ) ) / 255.0f;

                        float g =
                            ( *( temp1 + 1 ) * ( 1 - deltaheight ) * ( 1 - deltawidth )
                                + *( temp2 + 1 ) * ( deltaheight ) * ( 1 - deltawidth )
                                + *( temp3 + 1 ) * ( 1 - deltaheight ) * ( deltawidth )
                                +*( temp4 + 1 ) * ( deltaheight ) * ( deltawidth ) ) / 255.0f;

                        float r =
                            ( *( temp1 + 2 ) * ( 1 - deltaheight ) * ( 1 - deltawidth )
                                + *( temp2 + 2 ) * ( deltaheight ) * ( 1 - deltawidth )
                                + *( temp3 + 2 ) * ( 1 - deltaheight ) * ( deltawidth )
                                +*( temp4 + 2 ) * ( deltaheight ) * ( deltawidth ) ) / 255.0f;


                        dstT[ pixelIndex + 0 * height * width ] = r;
                        dstT[ pixelIndex + 1 * height * width ] = g;
                        dstT[ pixelIndex + 2 * height * width ] = b;
                        pixelIndex++;
                    }
                }
            }
            else
            {
                size_t pixelIndex = 0;
                for ( size_t line = 0; line < height; line++ )
                {
                    auto _src = src + line * rowPitch;
                    for ( size_t x = 0; x < width; x++ )
                    {
                        float b = static_cast< float >( _src[ x * srcChannels + 0 ] ) / 255.0f;
                        float g = static_cast< float >( _src[ x * srcChannels + 1 ] ) / 255.0f;
                        float r = static_cast< float >( _src[ x * srcChannels + 2 ] ) / 255.0f;

                        dstT[ pixelIndex + 0 * height * width ] = r;
                        dstT[ pixelIndex + 1 * height * width ] = g;
                        dstT[ pixelIndex + 2 * height * width ] = b;

                        pixelIndex++;
                    }
                }
            }
        }
    }


    Model::Model( const std::shared_ptr<ONNX::Session>& session )
        : session_( session )
    {
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        Ort::Allocator allocator( session->Impl(), memoryInfo );

        auto meta = session->GetModelMetadata( );
        auto modelname = meta.GetGraphNameAllocated( allocator );

        auto inputName = session->GetInputNameAllocated( 0, allocator );
        auto inputTypeInfo = session->GetInputTypeInfo( 0 );
        auto inputTensorInfo = inputTypeInfo.GetTensorTypeAndShapeInfo( );
        inputShape_ = inputTensorInfo.GetShape( );

        for ( size_t i = 0; i < inputShape_.size( ); i++ )
        {
            if ( i == 0 && inputShape_[ i ] == -1 )
            {
                inputShape_[ i ] = 1;
            }
            if ( i > 0 && inputShape_[ i ] == -1 )
            {
                inputShape_[ i ] = 640;
            }
        }


        inputDataType_ = inputTensorInfo.GetElementType( );
        if ( inputDataType_ != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT && inputDataType_ != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16 )
        {
            HCC_THROW( ArgumentException, L"Model input must be of type float32 or float16", L"session" );
        }
        if ( inputShape_.size( ) < 3 )
        {
            HCC_THROW( ArgumentException, L"Model input must be an image with 3 or 4 dimensions", L"session" );
        }

        inputChannels_ = inputShape_[ inputShape_.size( ) - 3 ];
        inputHeight_ = inputShape_[ inputShape_.size( ) - 2 ];
        inputWidth_ = inputShape_[ inputShape_.size( ) - 1 ];


        const size_t inputElementSize = inputDataType_ == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ? sizeof( float ) : sizeof( uint16_t );

        auto outputName = session->GetOutputNameAllocated( 0, allocator );
        auto tensors = session->GetOutputCount( );
        auto outputTypeInfo = session->GetOutputTypeInfo( 0 );
        auto outputTensorInfo = outputTypeInfo.GetTensorTypeAndShapeInfo( );
        outputShape_ = outputTensorInfo.GetShape( );
        auto outputDataType = outputTensorInfo.GetElementType( );

        if ( outputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT && outputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16
            && outputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8 )
        {
            HCC_THROW( ArgumentException, L"Model output must be of type float32 or float16 or int8", L"session" );
        }
        if ( outputShape_.size( ) < 3 )
        {
            HCC_THROW( ArgumentException, L"Model output must be an image with 3 or 4 dimensions", L"session" );
        }

        inputBuffer_.resize( inputChannels_ * inputHeight_ * inputWidth_ * inputElementSize );

    }
}