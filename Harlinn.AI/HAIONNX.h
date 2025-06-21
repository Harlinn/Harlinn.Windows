#pragma once
#ifndef HARLINN_AI_HAIONNX_H_
#define HARLINN_AI_HAIONNX_H_

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


#include "HAITensor.h"
#include "onnxruntime_cxx_api.h"

#pragma comment(lib,"Microsoft.AI.MachineLearning.lib")
#pragma comment(lib,"onnxruntime.lib")

namespace Harlinn::AI::ONNX
{
    class Session;
    class Environment;

    

    class SessionOptions
    {
        friend class Session;
        Ort::SessionOptions sessionOptions_;
    public:
        /// <summary>
        /// Create an empty SessionOptions object, must be assigned a valid one to be used
        /// </summary>
        explicit SessionOptions( std::nullptr_t ) 
            : sessionOptions_( nullptr )
        { }

        Ort::SessionOptions& Impl( )
        {
            return sessionOptions_;
        }
        const Ort::SessionOptions& Impl( ) const
        {
            return sessionOptions_;
        }

        /// <summary>
        /// Wraps OrtApi::CreateSessionOptions
        /// </summary>
        SessionOptions( )
        { }
        /// <summary>
        /// Used for interop with the C API
        /// </summary>
        explicit SessionOptions( OrtSessionOptions* ortSessionOptions )
            : sessionOptions_( ortSessionOptions )
        { }
        Ort::UnownedSessionOptions GetUnowned( ) const 
        { 
            return sessionOptions_.GetUnowned( );
        }
        Ort::ConstSessionOptions GetConst( ) const 
        { 
            return sessionOptions_.GetConst( );
        }

        /// Wraps OrtApi::SetIntraOpNumThreads
        SessionOptions& SetIntraOpNumThreads( int intra_op_num_threads )
        {                   
            sessionOptions_.SetIntraOpNumThreads( intra_op_num_threads );
            return *this;
        }
        /// Wraps OrtApi::SetInterOpNumThreads
        SessionOptions& SetInterOpNumThreads( int inter_op_num_threads )
        {
            sessionOptions_.SetInterOpNumThreads( inter_op_num_threads );
            return *this;
        }
        /// Wraps OrtApi::SetSessionGraphOptimizationLevel
        SessionOptions& SetGraphOptimizationLevel( GraphOptimizationLevel graph_optimization_level )
        {
            sessionOptions_.SetGraphOptimizationLevel( graph_optimization_level );
            return *this;
        }
        /// Wraps OrtApi::SetDeterministicCompute
        SessionOptions& SetDeterministicCompute( bool value )
        {
            sessionOptions_.SetDeterministicCompute( value );
            return *this;
        }

        /// Wraps OrtApi::EnableCpuMemArena
        SessionOptions& EnableCpuMemArena( )
        {
            sessionOptions_.EnableCpuMemArena( );
            return *this;
        }
        /// Wraps OrtApi::DisableCpuMemArena
        SessionOptions& DisableCpuMemArena( )
        {
            sessionOptions_.DisableCpuMemArena( );
            return *this;
        }

        /// Wraps OrtApi::SetOptimizedModelFilePath
        SessionOptions& SetOptimizedModelFilePath( const ORTCHAR_T* optimized_model_file )
        {
            sessionOptions_.SetOptimizedModelFilePath( optimized_model_file );
            return *this;
        }

        /// Wraps OrtApi::EnableProfiling
        SessionOptions& EnableProfiling( const ORTCHAR_T* profile_file_prefix )
        {
            sessionOptions_.EnableProfiling( profile_file_prefix );
            return *this;
        }
        /// Wraps OrtApi::DisableProfiling
        SessionOptions& DisableProfiling( )
        {
            sessionOptions_.DisableProfiling( );
            return *this;
        }

        /// Wraps OrtApi::EnableOrtCustomOps
        SessionOptions& EnableOrtCustomOps( )
        {
            sessionOptions_.EnableOrtCustomOps( );
            return *this;
        }

        /// Wraps OrtApi::EnableMemPattern
        SessionOptions& EnableMemPattern( )
        {
            sessionOptions_.EnableMemPattern( );
            return *this;
        }
        /// Wraps OrtApi::DisableMemPattern
        SessionOptions& DisableMemPattern( )
        {
            sessionOptions_.DisableMemPattern( );
            return *this;
        }

        /// Wraps OrtApi::SetSessionExecutionMode
        SessionOptions& SetExecutionMode( ExecutionMode execution_mode )
        {
            sessionOptions_.SetExecutionMode( execution_mode );
            return *this;
        }

        /// Wraps OrtApi::SetSessionLogId
        SessionOptions& SetLogId( const char* logid )
        {
            sessionOptions_.SetLogId( logid );
            return *this;
        }
        /// Wraps OrtApi::SetSessionLogSeverityLevel
        SessionOptions& SetLogSeverityLevel( int level )
        {
            sessionOptions_.SetLogSeverityLevel( level );
            return *this;
        }

        /// Wraps OrtApi::AddCustomOpDomain
        SessionOptions& Add( OrtCustomOpDomain* custom_op_domain )
        {
            sessionOptions_.Add( custom_op_domain );
            return *this;
        }

        /// Wraps OrtApi::DisablePerSessionThreads
        SessionOptions& DisablePerSessionThreads( )
        {
            sessionOptions_.DisablePerSessionThreads( );
            return *this;
        }

        /// Wraps OrtApi::AddSessionConfigEntry
        SessionOptions& AddConfigEntry( const char* config_key, const char* config_value )
        {
            sessionOptions_.AddConfigEntry( config_key, config_value );
            return *this;
        }

        /// Wraps OrtApi::AddInitializer
        SessionOptions& AddInitializer( const char* name, const OrtValue* ort_val )
        {
            sessionOptions_.AddInitializer( name, ort_val );
            return *this;
        }
        /// Wraps OrtApi::AddExternalInitializers
        SessionOptions& AddExternalInitializers( const std::vector<std::string>& names, const std::vector<Ort::Value>& ort_values )
        {
            sessionOptions_.AddExternalInitializers( names, ort_values );
            return *this;
        }
        /// Wraps OrtApi::AddExternalInitializersFromFilesInMemory
        SessionOptions& AddExternalInitializersFromFilesInMemory( const std::vector<std::basic_string<ORTCHAR_T>>& external_initializer_file_names, const std::vector<char*>& external_initializer_file_buffer_array, const std::vector<size_t>& external_initializer_file_lengths )
        {
            sessionOptions_.AddExternalInitializersFromFilesInMemory( external_initializer_file_names, external_initializer_file_buffer_array, external_initializer_file_lengths );
            return *this;
        }

        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_CUDA
        SessionOptions& AppendExecutionProvider_CUDA( const OrtCUDAProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_CUDA( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_CUDA_V2
        SessionOptions& AppendExecutionProvider_CUDA_V2( const OrtCUDAProviderOptionsV2& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_CUDA_V2( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_ROCM
        SessionOptions& AppendExecutionProvider_ROCM( const OrtROCMProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_ROCM( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_OpenVINO
        SessionOptions& AppendExecutionProvider_OpenVINO( const OrtOpenVINOProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_OpenVINO( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_OpenVINO_V2
        SessionOptions& AppendExecutionProvider_OpenVINO_V2( const std::unordered_map<std::string, std::string>& provider_options = {} )
        {
            sessionOptions_.AppendExecutionProvider_OpenVINO_V2( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_TensorRT
        SessionOptions& AppendExecutionProvider_TensorRT( const OrtTensorRTProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_TensorRT( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_TensorRT
        SessionOptions& AppendExecutionProvider_TensorRT_V2( const OrtTensorRTProviderOptionsV2& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_TensorRT_V2( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_MIGraphX
        SessionOptions& AppendExecutionProvider_MIGraphX( const OrtMIGraphXProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_MIGraphX( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_CANN
        SessionOptions& AppendExecutionProvider_CANN( const OrtCANNProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_CANN( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_Dnnl
        SessionOptions& AppendExecutionProvider_Dnnl( const OrtDnnlProviderOptions& provider_options )
        {
            sessionOptions_.AppendExecutionProvider_Dnnl( provider_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider. Currently supports QNN, SNPE and XNNPACK.
        SessionOptions& AppendExecutionProvider( const std::string& provider_name, const std::unordered_map<std::string, std::string>& provider_options = {} )
        {
            sessionOptions_.AppendExecutionProvider( provider_name, provider_options );
            return *this;
        }

        /// Wraps OrtApi::SessionOptionsSetCustomCreateThreadFn
        SessionOptions& SetCustomCreateThreadFn( OrtCustomCreateThreadFn ort_custom_create_thread_fn )
        {
            sessionOptions_.SetCustomCreateThreadFn( ort_custom_create_thread_fn );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsSetCustomThreadCreationOptions
        SessionOptions& SetCustomThreadCreationOptions( void* ort_custom_thread_creation_options )
        {
            sessionOptions_.SetCustomThreadCreationOptions( ort_custom_thread_creation_options );
            return *this;
        }
        /// Wraps OrtApi::SessionOptionsSetCustomJoinThreadFn
        SessionOptions& SetCustomJoinThreadFn( OrtCustomJoinThreadFn ort_custom_join_thread_fn )
        {
            sessionOptions_.SetCustomJoinThreadFn( ort_custom_join_thread_fn );
            return *this;
        }

        /// Registers the custom operator from the specified shared library via OrtApi::RegisterCustomOpsLibrary_V2.
        /// The custom operator configurations are optional. If provided, custom operator configs are set via
        /// OrtApi::AddSessionConfigEntry.
        SessionOptions& RegisterCustomOpsLibrary( const ORTCHAR_T* library_name, const Ort::CustomOpConfigs& custom_op_configs = {} )
        {
            sessionOptions_.RegisterCustomOpsLibrary( library_name, custom_op_configs );
            return *this;
        }

        /// Wraps OrtApi::RegisterCustomOpsUsingFunction
        SessionOptions& RegisterCustomOpsUsingFunction( const char* function_name )
        {
            sessionOptions_.RegisterCustomOpsUsingFunction( function_name );
            return *this;
        }  

        /// Wraps OrtApi::SessionOptionsAppendExecutionProvider_VitisAI
        SessionOptions& AppendExecutionProvider_VitisAI( const std::unordered_map<std::string, std::string>& provider_options = {} )
        {
            sessionOptions_.AppendExecutionProvider_VitisAI( provider_options );
            return *this;
        }

    };

    class Session : public std::enable_shared_from_this<Session>
    {
        const std::weak_ptr<Environment>& environment_;
        Ort::Session session_;
        std::shared_ptr<Meta::Metadata> metadata_;
    public:
        /// Wraps OrtApi::CreateSession
        Session( std::shared_ptr<Environment>& environment, const ORTCHAR_T* modelPath, const SessionOptions& options );
        
        /// Wraps OrtApi::CreateSessionWithPrepackedWeightsContainer
        Session( std::shared_ptr<Environment>& environment, const ORTCHAR_T* model_path, const SessionOptions& options, OrtPrepackedWeightsContainer* prepacked_weights_container );
        /// Wraps OrtApi::CreateSessionFromArray
        Session( std::shared_ptr<Environment>& environment, const void* model_data, size_t model_data_length, const SessionOptions& options );
        /// Wraps OrtApi::CreateSessionFromArrayWithPrepackedWeightsContainer
        Session( std::shared_ptr<Environment>& environment, const void* model_data, size_t model_data_length, const SessionOptions& options, OrtPrepackedWeightsContainer* prepacked_weights_container );
    private:
        HAI_EXPORT std::shared_ptr<Meta::Metadata> CreateMetadata( );
    public:
        const std::shared_ptr<Meta::Metadata>& Metadata( ) const
        {
            return metadata_;
        }


        Ort::Session& Impl( )
        {
            return session_;
        }
        const Ort::Session& Impl( ) const
        {
            return session_;
        }

        /// Returns the number of model inputs
        size_t GetInputCount( ) const
        {
            return session_.GetInputCount( );
        }
        
        /// Returns the number of model outputs
        size_t GetOutputCount( ) const
        {
            return session_.GetOutputCount( );
        }
        
        /// Returns the number of inputs that have defaults that can be overridden
        size_t GetOverridableInitializerCount( ) const
        {
            return session_.GetOverridableInitializerCount( );
        }

        /** \brief Returns a copy of input name at the specified index.
         *
         * \param index must less than the value returned by GetInputCount()
         * \param allocator to allocate memory for the copy of the name returned
         * \return a instance of smart pointer that would deallocate the buffer when out of scope.
         *  The OrtAllocator instances must be valid at the point of memory release.
         */
        Ort::AllocatedStringPtr GetInputNameAllocated( size_t index, OrtAllocator* allocator ) const
        {
            return session_.GetInputNameAllocated( index, allocator );
        }

        /** \brief Returns a copy of output name at then specified index.
         *
         * \param index must less than the value returned by GetOutputCount()
         * \param allocator to allocate memory for the copy of the name returned
         * \return a instance of smart pointer that would deallocate the buffer when out of scope.
         *  The OrtAllocator instances must be valid at the point of memory release.
         */
        Ort::AllocatedStringPtr GetOutputNameAllocated( size_t index, OrtAllocator* allocator ) const
        {
            return session_.GetOutputNameAllocated( index, allocator );
        }

        /** \brief Returns a copy of the overridable initializer name at then specified index.
         *
         * \param index must less than the value returned by GetOverridableInitializerCount()
         * \param allocator to allocate memory for the copy of the name returned
         * \return a instance of smart pointer that would deallocate the buffer when out of scope.
         *  The OrtAllocator instances must be valid at the point of memory release.
         */
        Ort::AllocatedStringPtr GetOverridableInitializerNameAllocated( size_t index, OrtAllocator* allocator ) const
        {
            return session_.GetOverridableInitializerNameAllocated( index, allocator );
        }

        /// Wraps OrtApi::SessionGetProfilingStartTimeNs
        UInt64 GetProfilingStartTimeNs( ) const
        {
            return session_.GetProfilingStartTimeNs( );
        }
        /// Wraps OrtApi::SessionGetModelMetadata
        Ort::ModelMetadata GetModelMetadata( ) const
        {
            return session_.GetModelMetadata( );
        }

        /// Wraps OrtApi::SessionGetInputTypeInfo
        Ort::TypeInfo GetInputTypeInfo( size_t index ) const
        {
            return session_.GetInputTypeInfo( index );
        }
        /// Wraps OrtApi::SessionGetOutputTypeInfo
        Ort::TypeInfo GetOutputTypeInfo( size_t index ) const
        {
            return session_.GetOutputTypeInfo( index );
        }
        /// Wraps OrtApi::SessionGetOverridableInitializerTypeInfo
        Ort::TypeInfo GetOverridableInitializerTypeInfo( size_t index ) const
        {
            return session_.GetOverridableInitializerTypeInfo( index );
        }

        /** \brief Run the model returning results in an Ort allocated vector.
         *
         * Wraps OrtApi::Run
         *
         * The caller provides a list of inputs and a list of the desired outputs to return.
         *
         * See the output logs for more information on warnings/errors that occur while processing the model.
         * Common errors are.. (TODO)
         *
         * \param[in] run_options
         * \param[in] input_names Array of null terminated strings of length input_count that is the list of input names
         * \param[in] input_values Array of Value objects of length input_count that is the list of input values
         * \param[in] input_count Number of inputs (the size of the input_names & input_values arrays)
         * \param[in] output_names Array of C style strings of length output_count that is the list of output names
         * \param[in] output_count Number of outputs (the size of the output_names array)
         * \return A std::vector of Value objects that directly maps to the output_names array (eg. output_name[0] is the first entry of the returned vector)
         */
        std::vector<Ort::Value> Run( const Ort::RunOptions& run_options, const char* const* input_names, const Ort::Value* input_values, size_t input_count, const char* const* output_names, size_t output_count )
        {
            return session_.Run( run_options, input_names, input_values, input_count, output_names, output_count );
        }

        /** \brief Run the model returning results in user provided outputs
         * Same as Run(const RunOptions&, const char* const*, const Value*, size_t,const char* const*, size_t)
         */
        void Run( const Ort::RunOptions& run_options, const char* const* input_names, const Ort::Value* input_values, size_t input_count, const char* const* output_names, Ort::Value* output_values, size_t output_count )
        {
            session_.Run( run_options, input_names, input_values, input_count, output_names, output_values, output_count );
        }

        /// Wraps OrtApi::RunWithBinding
        void Run( const Ort::RunOptions& run_options, const Ort::IoBinding& ioBinding )
        {
            session_.Run( run_options, ioBinding );
        }

        /** \brief Run the model asynchronously in a thread owned by intra op thread pool
         *
         * Wraps OrtApi::RunAsync
         *
         * \param[in] run_options
         * \param[in] input_names Array of null terminated UTF8 encoded strings of the input names
         * \param[in] input_values Array of Value objects of length input_count
         * \param[in] input_count Number of elements in the input_names and inputs arrays
         * \param[in] output_names Array of null terminated UTF8 encoded strings of the output names
         * \param[out] output_values Array of provided Values to be filled with outputs.
         *             On calling RunAsync, output_values[i] could either be initialized by a null pointer or a preallocated OrtValue*.
         *             Later, on invoking the callback, each output_values[i] of null will be filled with an OrtValue* allocated by onnxruntime.
         *             Then, an OrtValue** pointer will be casted from output_values, and pass to the callback.
         *             NOTE: it is customer's duty to finally release output_values and each of its member,
         *             regardless of whether the member (Ort::Value) is allocated by onnxruntime or preallocated by the customer.
         * \param[in] output_count Number of elements in the output_names and outputs array
         * \param[in] callback Callback function on model run completion
         * \param[in] user_data User data that pass back to the callback
         */
        void RunAsync( const Ort::RunOptions& run_options, const char* const* input_names, const Ort::Value* input_values, size_t input_count, const char* const* output_names, Ort::Value* output_values, size_t output_count, RunAsyncCallbackFn callback, void* user_data )
        {
            session_.RunAsync( run_options, input_names, input_values, input_count, output_names, output_values, output_count, callback, user_data );
        }

        /** \brief End profiling and return a copy of the profiling file name.
         *
         * \param allocator to allocate memory for the copy of the string returned
         * \return a instance of smart pointer that would deallocate the buffer when out of scope.
         *  The OrtAllocator instances must be valid at the point of memory release.
         */
        Ort::AllocatedStringPtr EndProfilingAllocated( OrtAllocator* allocator )
        {
            return session_.EndProfilingAllocated( allocator );
        }

        /** \brief Set DynamicOptions for EPs (Execution Providers)
         *
         * Wraps OrtApi::SetEpDynamicOptions
         *
         * Valid options can be found in `include\onnxruntime\core\session\onnxruntime_session_options_config_keys.h`
         * Look for `kOrtEpDynamicOptions`
         *
         * \param[in] keys Array of null terminated UTF8 encoded strings of EP dynamic option keys
         * \param[in] values Array of null terminated UTF8 encoded string of EP dynamic option values
         * \param[in] kv_len Number of elements in the keys and values arrays
         */
        void SetEpDynamicOptions( const char* const* keys, const char* const* values, size_t kv_len )
        {
            session_.SetEpDynamicOptions( keys, values, kv_len );
        }

    };

    class Environment : public std::enable_shared_from_this<Environment>
    {
        friend class Session;
        Ort::Env environment_;
    public:
        Environment( OrtLoggingLevel loggingLevel = ORT_LOGGING_LEVEL_WARNING, _In_ const char* logid = "" )
            : environment_( loggingLevel, logid )
        { }

        /// \brief Wraps OrtApi::CreateEnvWithCustomLogger
        Environment( OrtLoggingLevel loggingLevel, const char* logid, OrtLoggingFunction loggingFunction, void* loggerParam )
            : environment_( loggingLevel, logid, loggingFunction, loggerParam )
        { }

        /// \brief Wraps OrtApi::CreateEnvWithGlobalThreadPools
        Environment( const OrtThreadingOptions* tp_options, OrtLoggingLevel logging_level = ORT_LOGGING_LEVEL_WARNING, _In_ const char* logid = "" )
            : environment_( tp_options, logging_level, logid )
        { }

        /// \brief Wraps OrtApi::CreateEnvWithCustomLoggerAndGlobalThreadPools
        Environment( const OrtThreadingOptions* tp_options, OrtLoggingFunction logging_function, void* logger_param, OrtLoggingLevel logging_level = ORT_LOGGING_LEVEL_WARNING, _In_ const char* logid = "" )
            : environment_( tp_options, logging_function, logger_param, logging_level, logid )
        { }
        /// \brief C Interop Helper
        explicit Environment( OrtEnv* p ) 
            : environment_( p ) 
        { }

        Ort::Env& Impl( )
        {
            return environment_;
        }
        const Ort::Env& Impl( ) const
        {
            return environment_;
        }

        /// Wraps OrtApi::EnableTelemetryEvents
        Environment& EnableTelemetryEvents( )
        {
            environment_.EnableTelemetryEvents( );
            return *this;
        }
        /// Wraps OrtApi::DisableTelemetryEvents
        Environment& DisableTelemetryEvents( )
        {
            environment_.DisableTelemetryEvents( );
            return *this;
        }

        /// Wraps OrtApi::UpdateEnvWithCustomLogLevel
        Environment& UpdateEnvWithCustomLogLevel( OrtLoggingLevel log_severity_level )
        {
            environment_.UpdateEnvWithCustomLogLevel( log_severity_level );
            return *this;
        }
        /// Wraps OrtApi::CreateAndRegisterAllocator
        Environment& CreateAndRegisterAllocator( const OrtMemoryInfo* mem_info, const OrtArenaCfg* arena_cfg )
        {
            environment_.CreateAndRegisterAllocator( mem_info, arena_cfg );
            return *this;
        }

        /// Wraps OrtApi::CreateAndRegisterAllocatorV2
        Environment& CreateAndRegisterAllocatorV2( const std::string& provider_type, const OrtMemoryInfo* mem_info, const std::unordered_map<std::string, std::string>& options, const OrtArenaCfg* arena_cfg )
        {
            environment_.CreateAndRegisterAllocatorV2( provider_type, mem_info, options, arena_cfg );
            return *this;
        }
    };

    inline Session::Session( std::shared_ptr<Environment>& environment, const ORTCHAR_T* modelPath, const SessionOptions& options )
        : environment_( environment ), session_( environment->environment_, modelPath, options.sessionOptions_ )
    {
        metadata_ = CreateMetadata( );
    }

    inline Session::Session( std::shared_ptr<Environment>& environment, const ORTCHAR_T* model_path, const SessionOptions& options, OrtPrepackedWeightsContainer* prepacked_weights_container )
        : environment_( environment ), session_( environment->environment_, model_path, options.sessionOptions_, prepacked_weights_container )
    {
        metadata_ = CreateMetadata( );
    }
    
    inline Session::Session( std::shared_ptr<Environment>& environment, const void* model_data, size_t model_data_length, const SessionOptions& options )
        : environment_( environment ), session_( environment->environment_, model_data, model_data_length,options.sessionOptions_ )
    {
        metadata_ = CreateMetadata( );
    }
    
    inline Session::Session( std::shared_ptr<Environment>& environment, const void* model_data, size_t model_data_length, const SessionOptions& options, OrtPrepackedWeightsContainer* prepacked_weights_container )
        : environment_( environment ), session_( environment->environment_, model_data, model_data_length, options.sessionOptions_, prepacked_weights_container )
    {
        metadata_ = CreateMetadata( );
    }


    class NodeInput : public std::enable_shared_from_this<NodeInput>
    {
    public:
        using Base = std::enable_shared_from_this<NodeInput>;
    private:
        std::shared_ptr<Meta::Metadata> metadata_;
        std::vector<std::shared_ptr<Tensors::Value>> inputs_;
        std::vector<std::shared_ptr<Tensors::Value>> overridableInitializers_;
    public:
        NodeInput( const std::shared_ptr<Meta::Metadata>& metadata )
            : metadata_( metadata )
        {
            const auto& inputsTypeInfo = metadata->Inputs( );
            inputs_.reserve( inputsTypeInfo.size() );
            for ( const auto& typeInfo : inputsTypeInfo )
            {
                inputs_.emplace_back( Tensors::CreateValue( typeInfo ) );
            }
        }

        const std::shared_ptr<Meta::Metadata>& Metadata( ) const
        {
            return metadata_;
        }

        const std::vector<std::shared_ptr<Tensors::Value>>& Inputs( ) const
        {
            return inputs_;
        }
        const std::vector<std::shared_ptr<Tensors::Value>>& OverridableInitializers( ) const
        {
            return overridableInitializers_;
        }
    };

    class NodeOutput : public std::enable_shared_from_this<NodeOutput>
    {
    public:
        using Base = std::enable_shared_from_this<NodeOutput>;
    private:
        std::shared_ptr<Meta::Metadata> metadata_;
        std::vector<std::shared_ptr<Tensors::Value>> outputs_;
    public:
        NodeOutput( const std::shared_ptr<Meta::Metadata>& metadata )
            : metadata_( metadata )
        {
            const auto& outputsTypeInfo = metadata->Outputs( );
            outputs_.reserve( outputsTypeInfo.size( ) );
            for ( const auto& typeInfo : outputsTypeInfo )
            {
                outputs_.emplace_back( Tensors::CreateValue( typeInfo ) );
            }
        }

        const std::shared_ptr<Meta::Metadata>& Metadata( ) const
        {
            return metadata_;
        }

        const std::vector<std::shared_ptr<Tensors::Value>>& Outputs( ) const
        {
            return outputs_;
        }
    };


    class ResultSink : public std::enable_shared_from_this<ResultSink>
    {
    public:
        using Base = std::enable_shared_from_this<ResultSink>;

        virtual ~ResultSink( ) = default;

        virtual void Process( TimeSpan computeTime, const std::shared_ptr<NodeOutput>& outputs ) = 0;
    };

    class EventResultSink : public ResultSink
    {
    public:
        using Base = ResultSink;
        boost::signals2::signal<void( TimeSpan, const std::shared_ptr<NodeOutput>& )> OnProcess;

        virtual void Process( TimeSpan computeTime, const std::shared_ptr<NodeOutput>& outputs ) override
        {
            OnProcess( computeTime, outputs );
        }
    };


    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        using Base = std::enable_shared_from_this<Node>;
    private:
        std::weak_ptr<ONNX::Session> session_;
        std::shared_ptr<Meta::Metadata> metadata_;
        WideString modelFilename_;
    public:
        Node( const std::shared_ptr<ONNX::Session>& session )
            : session_( session ), metadata_( session->Metadata() )
        { }
        virtual ~Node( ) = default;

        HAI_EXPORT virtual void Compute( const std::shared_ptr<NodeInput>& inputs, const std::shared_ptr<ResultSink>& resultSink );

        std::shared_ptr<ONNX::Session> Session( ) const
        {
            return session_.lock( );
        }
        const std::shared_ptr<Meta::Metadata>& Metadata( ) const
        {
            return metadata_;
        }
    };



    struct Prediction
    {
        static constexpr float Epsilon = 0.5f;
        // Bounding box coordinates
        float xmin = 0.f;
        float ymin = 0.f;
        float xmax = 0.f;
        float ymax = 0.f;
        float score = 0.f;
        Int64 predictedClass = 0;

        Prediction( ) = default;
    };

    struct NearlyEqual
    {
        bool operator( )( const Prediction& lhs, const Prediction& rhs ) const
        {
            return AreNearlyEqual( lhs.xmin, rhs.xmin, Prediction::Epsilon ) &&
                AreNearlyEqual( lhs.ymin, rhs.ymin, Prediction::Epsilon ) &&
                AreNearlyEqual( lhs.xmax, rhs.xmax, Prediction::Epsilon ) &&
                AreNearlyEqual( lhs.ymax, rhs.ymax, Prediction::Epsilon );
        }
    };

    struct PositionHash
    {
        size_t operator ()( const Prediction& prediction ) const
        {
            std::array<float, 4> array{ Math::Floor( prediction.xmin ), Math::Floor( prediction.ymin ), Math::Ceil( prediction.xmax ), Math::Ceil( prediction.ymax ) };
            XXH64Hasher hasher;
            hasher.Add( reinterpret_cast< const Byte* >( array.data( ) ), sizeof( float ) * 4 );
            return hasher.Digest( );
        }
    };
    struct PositionEqual
    {
        size_t operator ()( const Prediction& lhs, const Prediction& rhs ) const
        {
            std::array<float, 4> lhsArray{ Math::Floor( lhs.xmin ), Math::Floor( lhs.ymin ), Math::Ceil( lhs.xmax ), Math::Ceil( lhs.ymax ) };
            std::array<float, 4> rhsArray{ Math::Floor( rhs.xmin ), Math::Floor( rhs.ymin ), Math::Ceil( rhs.xmax ), Math::Ceil( rhs.ymax ) };
            return lhsArray == rhsArray;
        }
    };

    class Model : public std::enable_shared_from_this<Model>
    {
    public:
        using Base = std::enable_shared_from_this<Model>;
        using TensorElementType = Meta::TensorElementType;
    private:
        std::weak_ptr<ONNX::Session> session_;
        std::shared_ptr<Meta::Metadata> metadata_;
        WideString modelFilename_;
        Ort::Value inputTensor_{ nullptr };
        Ort::Value outputTensor_{ nullptr };
        std::vector<int64_t> inputShape_;
        std::vector<int64_t> outputShape_;
        TensorElementType inputDataType_ = TensorElementType::Undefined;
        size_t inputWidth_ = 0;
        size_t inputHeight_ = 0;
        size_t inputSize_ = 0;
        size_t inputChannels_ = 0;
        CriticalSection criticalSection_;
        std::vector<Prediction> predictions_;
        UInt64 predictionsVersion_ = 0;
        TimeSpan loadTime_;
        TimeSpan computeTime_;
    public:
        HAI_EXPORT Model( const std::shared_ptr<ONNX::Session>& session );
        
        HAI_EXPORT Binary CreateInputBuffer( std::byte* src, UInt32 Width, UInt32 height, UInt32 rowPitch ) const;
        
        HAI_EXPORT virtual void Compute(const Binary& inputTensorData, const Math::Vector2f& viewportSize );

        std::shared_ptr<ONNX::Session> Session( ) const
        {
            return session_.lock();
        }

        const std::shared_ptr<Meta::Metadata>& Metadata( ) const
        {
            return metadata_;
        }

        const WideString& ModelFilename( ) const
        {
            return modelFilename_;
        }
        void SetModelFilename( const WideString& modelFilename )
        {
            modelFilename_ = modelFilename;
        }
        const Ort::Value& InputTensor( ) const
        {
            inputTensor_;
        }
        Ort::Value& InputTensor( )
        {
            inputTensor_;
        }

        void SetInputTensor( Ort::Value&& inputTensor )
        {
            inputTensor_ = std::move(inputTensor);
        }


        const Ort::Value& OutputTensor( ) const
        {
            return outputTensor_;
        }
        Ort::Value& OutputTensor( )
        {
            return outputTensor_;
        }

        void SetOutputTensor( Ort::Value&& outputTensor )
        {
            outputTensor_ = std::move( outputTensor );
        }


        const std::vector<int64_t>& InputShape( ) const
        {
            return inputShape_;
        }
        std::vector<int64_t>& InputShape( )
        {
            return inputShape_;
        }
        void SetInputShape( const std::vector<int64_t>& inputShape )
        {
            inputShape_ = inputShape;
        }
        void SetInputShape( std::vector<int64_t>&& inputShape )
        {
            inputShape_ = std::move(inputShape);
        }


        const std::vector<int64_t>& OutputShape( ) const
        {
            return outputShape_;
        }
        std::vector<int64_t>& OutputShape( )
        {
            return outputShape_;
        }

        void SetOutputShape( const std::vector<int64_t>& outputShape )
        {
            outputShape_ = outputShape;
        }
        void SetOutputShape( std::vector<int64_t>&& outputShape )
        {
            outputShape_ = std::move(outputShape);
        }


        TensorElementType InputDataType( ) const
        {
            return inputDataType_;
        }
        size_t InputWidth( ) const
        {
            return inputWidth_;
        }
        size_t InputHeight( ) const
        {
            return inputHeight_;
        }

        size_t InputSize( ) const
        {
            return inputSize_;
        }

        size_t InputChannels( ) const
        {
            return inputChannels_;
        }

        std::vector<Prediction> Predictions( ) const
        {
            std::scoped_lock lock( criticalSection_ );
            return predictions_;
        }
        void SetPredictions( const std::vector<Prediction>& predictions )
        {
            std::scoped_lock lock( criticalSection_ );
            predictions_ = predictions;
            predictionsVersion_++;
        }
        void SetPredictions( std::vector<Prediction>&& predictions )
        {
            std::scoped_lock lock( criticalSection_ );
            predictions_ = std::move( predictions );
            predictionsVersion_++;
        }

        void GetPredictions( std::vector<Prediction>& predictions, UInt64& predictionsVersion ) const
        {
            std::scoped_lock lock( criticalSection_ );
            predictions = predictions_;
            predictionsVersion = predictionsVersion_;
        }

        bool HasNewPredictions( UInt64 predictionsVersion )
        {
            std::scoped_lock lock( criticalSection_ );
            return predictionsVersion != predictionsVersion_;
        }

        UInt64 PredictionsVersion( ) const
        {
            return predictionsVersion_;
        }

        TimeSpan LoadTime( ) const
        {
            return loadTime_;
        }
        void SetLoadTime( TimeSpan loadTime )
        {
            loadTime_ = loadTime;
        }
        TimeSpan ComputeTime( ) const
        {
            return computeTime_;
        }
        void SetComputeTime( TimeSpan computeTime )
        {
            computeTime_ = computeTime;
        }



    };


    


    struct Detection
    {
        /// @brief The x-coordinate of the top-left corner of the bounding box.
        float x;

        /// @brief The y-coordinate of the top-left corner of the bounding box.
        float y;

        /// @brief The width of the bounding box.
        float w;

        /// @brief The height of the bounding box.
        float h;

        /// @brief The index of the detected object, typically corresponding to the class index in the model.
        Int64 index;

        /// @brief The confidence level of the detection.
        float confidence;
    };
}

namespace std
{
    template<>
    struct hash<Harlinn::AI::ONNX::Prediction>
    {
        using value_type = Harlinn::AI::ONNX::Prediction;
        size_t operator()( const value_type& x ) const
        {
            using namespace Harlinn::Common;
            using namespace Harlinn::Common::Core;
            XXH64Hasher hasher;
            hasher.Add( reinterpret_cast<const Byte*>( &x ), sizeof( value_type ) );
            return hasher.Digest( );
        }
    };
}

#endif
