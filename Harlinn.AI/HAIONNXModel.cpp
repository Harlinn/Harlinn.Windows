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
#include "Internal/half.hpp"

#include <mdspan>

namespace Harlinn::AI::ONNX
{   
    using namespace Meta;
    using namespace Tensors;
    namespace
    { 
        template <typename T>
        struct Vec1
        {
            const T* data;
            Int64 x;
            Vec1( const T* data, Int64 x ) 
                : data( data ), x( x ) 
            { }
            const T& operator[]( Int64 i ) const 
            { 
                return data[ i ]; 
            }
        };
        template <typename T>
        struct Vec2
        {
            const T* data;
            Int64 y, x;
            Vec2( const T* data, Int64 y, Int64 x ) 
                : data( data ), y( y ), x( x ) 
            { }
            Vec1<T> operator[]( Int64 i ) const 
            { 
                return Vec1<T>( data + i * x, x ); 
            }
        };

        template <typename T>
        struct Vec3
        {
            const T* data;
            Int64 z, y, x;
            Vec3( const T* data, Int64 z, Int64 y, Int64 x ) 
                : data( data ), z( z ), y( y ), x( x ) 
            { }
            Vec2<T> operator[]( Int64 i ) const 
            { 
                return Vec2<T>( data + i * y * x, y, x ); 
            }
        };

        template <typename T>
        struct Vec4
        {
            const T* data;
            Int64 w, z, y, x;
            Vec4( const T* data, Int64 w, Int64 z, Int64 y, Int64 x ) 
                : data( data ), w( w ), z( z ), y( y ), x( x ) 
            { }
            Vec3<T> operator[]( Int64 i ) const 
            { 
                return Vec3<T>( data + i * z * y * x, z, y, x ); 
            }
        };


        // Returns true if any of the supplied floats are inf or NaN, false otherwise.
        static bool IsInfOrNan( float arg )
        {
            if ( std::isinf( arg ) || std::isnan( arg ) )
            {
                return true;
            }
            return false;
        }
        template<typename ... Args>
        static bool IsInfOrNan( float arg, Args&& ... args )
        {
            if ( std::isinf( arg ) || std::isnan( arg ) )
            {
                return true;
            }

            return IsInfOrNan( args ... );
        }

        // Given two axis-aligned bounding boxes, computes the area of intersection divided by the area of the union of
        // the two boxes.
        static float ComputeIntersectionOverUnion( const Prediction& a, const Prediction& b )
        {
            float aArea = ( a.xmax - a.xmin ) * ( a.ymax - a.ymin );
            float bArea = ( b.xmax - b.xmin ) * ( b.ymax - b.ymin );

            // Determine the bounds of the intersection rectangle
            float interXMin = std::max( a.xmin, b.xmin );
            float interYMin = std::max( a.ymin, b.ymin );
            float interXMax = std::min( a.xmax, b.xmax );
            float interYMax = std::min( a.ymax, b.ymax );

            float intersectionArea = std::max( 0.0f, interXMax - interXMin ) * std::max( 0.0f, interYMax - interYMin );
            float unionArea = aArea + bArea - intersectionArea;

            return ( intersectionArea / unionArea );
        }

        // Given a set of predictions, applies the non-maximal suppression (NMS) algorithm to select the "best" of
        // multiple overlapping predictions.
        static std::vector<Prediction> ApplyNonMaximalSuppression( std::span<const Prediction> allPredictions, float threshold )
        {
            std::unordered_map<Int64, std::vector<Prediction>> predsByClass;
            for ( const auto& pred : allPredictions )
            {
                predsByClass[ pred.predictedClass ].push_back( pred );
            }

            std::vector<Prediction> selected;

            for ( auto& kvp : predsByClass )
            {
                std::vector<Prediction>& proposals = kvp.second;

                while ( !proposals.empty( ) )
                {
                    // Find the proposal with the highest score
                    auto max_iter = std::max_element( proposals.begin( ), proposals.end( ), []( const Prediction& lhs, const Prediction& rhs )
                        {
                            return lhs.score < rhs.score;
                        } );

                    // Move it into the "selected" array
                    selected.push_back( *max_iter );
                    proposals.erase( max_iter );

                    // Compare this selected prediction with all the remaining propsals. Compute their IOU and remove any
                    // that are greater than the threshold.
                    for ( auto it = proposals.begin( ); it != proposals.end( ); it )
                    {
                        float iou = ComputeIntersectionOverUnion( selected.back( ), *it );

                        if ( iou > threshold )
                        {
                            // Remove this element
                            it = proposals.erase( it );
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
            }

            return selected;
        }

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
            std::span<Byte> dst,
            size_t height,
            size_t width,
            size_t channels )
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
                        UInt32 OriginalPosHeight = ( UInt32 )mappedheight;
                        // co
                        UInt32 OriginalPosWidth = ( UInt32 )mappedwidth;
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

        std::vector<Prediction> GetPredictionsFrom(const Math::Vector2f& viewport,const std::byte* outputData, std::vector<int64_t>& shape )
        {
            
            constexpr double threshold = .45;

            // Input images are rescaled to 512x288 before being fed into the model
            constexpr UInt32 c_inputWidth = 512;
            constexpr UInt32 c_inputHeight = 288;

            constexpr float c_nmsThreshold = 0.2f;

            std::vector<Prediction> predictions;

            Vec3<float> value( ( float* )outputData, shape[ 0 ], shape[ 1 ], shape[ 2 ] );
            std::span shapeSpan( shape.data( ), shape.size( ) );

            // Scale the boxes to be relative to the original image size
            
            float xScale = ( float )viewport.x / c_inputWidth;
            float yScale = ( float )viewport.y / c_inputHeight;

            float* _ptr = ( float* )outputData;
            for ( Int64 i = 0; i < value.z; ++i )
            {
                for ( Int64 j = 0; j < value.y; ++j )
                {
                    auto ptr = value[ i ][ j ];
                    Detection result;
                    if ( value.x == 85 )
                    {
                        float max = 0.0f;
                        Int64 max_loc = 0;
                        float box_confidence = ptr[ 4 ];
                        //if (box_confidence == 0.0f)
                        //    continue;
                        box_confidence = 1.0f;
                        for ( int ii = 0; ii < 80; ii++ )
                        {
                            auto class_conf = ptr[ i + 5 ] * box_confidence;
                            if ( class_conf > max )
                            {
                                max = class_conf;
                                max_loc = i;
                            }
                        }
                        result.confidence = max;
                        result.index = max_loc;

                    }
                    else
                    {
                        //float* _ptr = (float*)ptr.data();
                        if ( ptr[ 4 ] < threshold ) continue;
                        result.confidence = ( float )ptr[ 4 ];
                        result.index = ( Int64 )ptr[ 5 ];

                    }

                    result.x = ptr[ 0 ];
                    result.y = ptr[ 1 ];
                    result.w = ptr[ 2 ];
                    result.h = ptr[ 3 ];



                    // We need to do some postprocessing on the raw values before we return them

                    // Convert x,y,w,h to xmin,ymin,xmax,ymax
                    float xmin = result.x - result.w / 2;
                    float ymin = result.y - result.h / 2;
                    float xmax = result.x + result.w / 2;
                    float ymax = result.y + result.h / 2;

                    xmin *= xScale;
                    ymin *= yScale;
                    xmax *= xScale;
                    ymax *= yScale;

                    // Clip values out of range
                    xmin = std::clamp( xmin, 0.0f, ( float )viewport.x );
                    ymin = std::clamp( ymin, 0.0f, ( float )viewport.y );
                    xmax = std::clamp( xmax, 0.0f, ( float )viewport.x );
                    ymax = std::clamp( ymax, 0.0f, ( float )viewport.y );

                    // Discard invalid boxes
                    if ( xmax <= xmin || ymax <= ymin || IsInfOrNan( xmin, ymin, xmax, ymax ) )
                    {
                        continue;
                    }

                    Prediction pred = {};
                    pred.xmin = xmin;
                    pred.ymin = ymin;
                    pred.xmax = xmax;
                    pred.ymax = ymax;
                    pred.score = result.confidence;
                    pred.predictedClass = result.index;
                    predictions.push_back( pred );
                }
            }
            // Apply NMS to select the best boxes
            predictions = ApplyNonMaximalSuppression( predictions, c_nmsThreshold );
            return predictions;
        }
    }






    Model::Model( const std::shared_ptr<ONNX::Session>& session )
        : session_( session )
    {
        metadata_ = session->Metadata( );
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        Ort::Allocator allocator( session->Impl(), memoryInfo );


        auto inputName = session->GetInputNameAllocated( 0, allocator );
        auto inputTypeInfo = session->GetInputTypeInfo( 0 );
        auto inputTensorInfo = inputTypeInfo.GetTensorTypeAndShapeInfo( );
        inputShape_ = inputTensorInfo.GetShape( );


        inputDataType_ = static_cast< TensorElementType >(inputTensorInfo.GetElementType( ));
        if ( inputDataType_ != TensorElementType::Float && inputDataType_ != TensorElementType::Float16 )
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


        const size_t inputElementSize = inputDataType_ == TensorElementType::Float ? sizeof( float ) : sizeof( uint16_t );

        auto outputName = session->GetOutputNameAllocated( 0, allocator );
        auto tensors = session->GetOutputCount( );
        auto outputTypeInfo = session->GetOutputTypeInfo( 0 );
        auto outputTensorInfo = outputTypeInfo.GetTensorTypeAndShapeInfo( );
        outputShape_ = outputTensorInfo.GetShape( );
        auto outputDataType = static_cast< TensorElementType >( outputTensorInfo.GetElementType( ) );

        if ( outputDataType != TensorElementType::Float && outputDataType != TensorElementType::Float16
            && outputDataType != TensorElementType::UInt8 )
        {
            HCC_THROW( ArgumentException, L"Model output must be of type float32 or float16 or int8", L"session" );
        }
        if ( outputShape_.size( ) < 3 )
        {
            HCC_THROW( ArgumentException, L"Model output must be an image with 3 or 4 dimensions", L"session" );
        }
        inputSize_ = inputChannels_ * inputHeight_ * inputWidth_ * inputElementSize;
    }

    HAI_EXPORT Binary Model::CreateInputBuffer( std::byte* src, UInt32 Width, UInt32 height, UInt32 rowPitch ) const
    {
        Binary result;
        result.resize( InputSize( ) );
        auto inputSpan = result.ToSpan( );
        switch ( inputDataType_ )
        {
            case TensorElementType::Float:
                CopyPixelsToTensor<float>( src, Width, height, rowPitch, inputSpan, inputHeight_, inputWidth_, inputChannels_ );
                break;

            case TensorElementType::Float16:
                CopyPixelsToTensor<half_float::half>( src, Width, height, rowPitch, inputSpan, inputHeight_, inputWidth_, inputChannels_ );
                break;

            default:
                HCC_THROW( InvalidOperationException, L"Unsupported data type" );
        }
        return result;
    }


    HAI_EXPORT void Model::Compute( const Binary& inputTensorData, const Math::Vector2f& viewportSize )
    {
        auto session = Session( );
        auto inputBuffer = inputTensorData.ToSpan( );
        // Convert image to tensor format (original texture -> model input)
        const size_t inputElementSize = inputDataType_ == TensorElementType::Float ? sizeof( float ) : sizeof( uint16_t );
        
        // Record start
        auto start = std::chrono::high_resolution_clock::now( );

        // Create input tensor
        Ort::MemoryInfo memoryInfo2 = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        auto inputTensor = Ort::Value::CreateTensor( memoryInfo2, inputBuffer.data( ), inputBuffer.size( ), inputShape_.data( ), inputShape_.size( ), static_cast< ONNXTensorElementDataType >( inputDataType_ ) );

        // Bind tensors
        Ort::MemoryInfo memoryInfo0 = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        Ort::Allocator allocator0( session->Impl(), memoryInfo0 );
        auto inputName = session->GetInputNameAllocated( 0, allocator0 );
        auto bindings = Ort::IoBinding::IoBinding( session->Impl( ) );
        
        bindings.BindInput( inputName.get( ), inputTensor );
        
        // Create output tensor(s) and bind
        auto tensors = session->GetOutputCount( );
        std::vector<std::string> output_names;
        std::vector<std::vector<int64_t>> output_shapes;
        std::vector<ONNXTensorElementDataType> output_datatypes;
        for ( int i = 0; i < tensors; i++ )
        {
            auto output_name = session->GetOutputNameAllocated( i, allocator0 );
            output_names.push_back( output_name.get( ) );
            auto type_info = session->GetOutputTypeInfo( i );
            auto tensor_info = type_info.GetTensorTypeAndShapeInfo( );
            auto shape = tensor_info.GetShape( );

            output_shapes.push_back( shape );

            output_datatypes.push_back( tensor_info.GetElementType( ) );

            bindings.BindOutput( output_names.back( ).c_str( ), memoryInfo2 );
        }

        // Run the session to get inference results.
        Ort::RunOptions runOpts;
        auto stopwatch = Stopwatch::StartNew( );
        session->Run( runOpts, bindings );
        stopwatch.Stop( );
        computeTime_ = stopwatch.Elapsed( );
        bindings.SynchronizeOutputs( );


        std::vector<const std::byte*> outputData;
        int  i = 0;
        for ( int i = 0; i < tensors; i++ )
        {
            const std::byte* outputBuffer = reinterpret_cast< const std::byte* >( bindings.GetOutputValues( )[ i ].GetTensorRawData( ) );
            outputData.push_back( outputBuffer );
        }

        std::vector<Prediction> predictions;
        if ( outputData.size( ) > 0 )
        {
            predictions = GetPredictionsFrom( viewportSize, outputData[ 0 ], output_shapes[ 0 ] );
        }
        SetPredictions( std::move(predictions) );
        
    }
    

}