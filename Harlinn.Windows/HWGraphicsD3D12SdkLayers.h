#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12SDKLAYERS_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12SDKLAYERS_H_

#include "HWGraphicsD3D12.h"

namespace Harlinn::Windows::Graphics
{

    /// <summary>
    /// A wrapper class for the ID3D12Debug interface.
    /// This interface is used to turn on the debug layer. 
    /// </summary>
    class D3D12Debug : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug, Unknown, ID3D12Debug, IUnknown )

    public:
        /// <summary>
        /// Enables the debug layer.
        /// </summary>
        /// <remarks>
        /// To enable the debug layers using this API, it must be called before the 
        /// D3D12 device is created. Calling this API after creating the D3D12 device 
        /// will cause the D3D12 runtime to remove the device.
        /// </remarks>
        void EnableDebugLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EnableDebugLayer( );
        }
    };


    /// <summary>
    /// Adds GPU-Based Validation and Dependent Command Queue Synchronization to the debug layer.
    /// </summary>
    class D3D12Debug1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug1, Unknown, ID3D12Debug1, IUnknown )

    public:
        /// <summary>
        /// Enables the debug layer.
        /// </summary>
        /// <remarks>
        /// This method is identical to D3D12Debug::EnableDebugLayer.
        /// </remarks>
        void EnableDebugLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EnableDebugLayer( );
        }

        /// <summary>
        /// This method enables or disables GPU-Based Validation (GBV) before creating a 
        /// device with the debug layer enabled.
        /// </summary>
        /// <param name="enable">
        /// true to enable GPU-Based Validation, otherwise false.
        /// </param>
        /// <remarks>
        /// GPU-Based Validation can only be enabled/disabled prior to creating a device. 
        /// By default, GPU-Based Validation is disabled. To disable GPU-Based Validation 
        /// after initially enabling it the device must be fully released and recreated; 
        /// disabling or enabling it after device creation will cause device removal.
        /// </remarks>
        void SetEnableGPUBasedValidation( bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableGPUBasedValidation( enable );
        }

        /// <summary>
        /// Enables or disables dependent command queue synchronization when using a D3D12 
        /// device with the debug layer enabled.
        /// </summary>
        /// <param name="enable">
        /// true to enable Dependent Command Queue Synchronization, otherwise false.
        /// </param>
        /// <remarks>
        /// <p>
        /// Dependent Command Queue Synchronization is a D3D12 Debug Layer feature that gives 
        /// the debug layer the ability to track resource states more accurately when enabled. 
        /// Dependent Command Queue Synchronization is enabled by default.
        /// </p>
        /// <p>
        /// When Dependent Command Queue Synchronization is enabled, the debug layer holds back 
        /// actual submission of GPU work until all outstanding fence Wait conditions are met. 
        /// This gives the debug layer the ability to make reasonable assumptions about GPU state 
        /// (such as resource states) on the CPU-timeline when multiple command queues are 
        /// potentially doing concurrent work.
        /// </p>
        /// <p>
        /// With Dependent Command Queue Synchronization disabled, all resource states tracked by 
        /// the debug layer are cleared each time <see cref="D3D12CommandQueue::Signal">D3D12CommandQueue::Signal</see>
        /// is called. This results in significantly less useful resource state validation.
        /// </p>
        /// <p>
        /// Disabling Dependent Command Queue Synchronization may reduce some debug layer performance 
        /// overhead when using multiple command queues. However, it is suggested to leave it enabled 
        /// unless this overhead is problematic. Note that applications that use only a single command 
        /// queue will see no performance changes with Dependent Command Queue Synchronization disabled.
        /// </p>
        /// </remarks>
        void SetEnableSynchronizedCommandQueueValidation( bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableSynchronizedCommandQueueValidation( enable );
        }
    };

    /// <summary>
    /// Adds configurable levels of GPU-based validation to the debug layer.
    /// </summary>
    class D3D12Debug2 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug2, Unknown, ID3D12Debug2, IUnknown )

    public:
        /// <summary>
        /// This method configures the level of GPU-based validation that the 
        /// debug device is to perform at runtime.
        /// </summary>
        /// <param name="flags">
        /// Specifies the level of GPU-based validation to perform at runtime.
        /// </param>
        /// <remarks>
        /// This method overrides the default behavior of GPU-based validation so 
        /// it must be called before creating the Direct3D 12 device. These settings 
        /// can't be changed or cancelled after the device is created. If you want 
        /// to change the behavior of GPU-based validation at a later time, the device 
        /// must be destroyed and recreated with different parameters.
        /// </remarks>
        void SetGPUBasedValidationFlags( D3D12_GPU_BASED_VALIDATION_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGPUBasedValidationFlags( flags );
        }
    };

    /// <summary>
    /// Adds configurable levels of GPU-based validation to the debug layer.
    /// </summary>
    class D3D12Debug3 : public D3D12Debug
    {
    public:
        using Base = D3D12Debug;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug3, D3D12Debug, ID3D12Debug3, ID3D12Debug )

    public:
        /// <summary>
        /// This method enables or disables GPU-based validation (GBV) before creating 
        /// a device with the debug layer enabled.
        /// </summary>
        /// <param name="enable">
        /// true to enable GPU-based validation, otherwise false.
        /// </param>
        /// <remarks>
        /// GPU-based validation can be enabled/disabled only prior to creating a device. 
        /// By default, GPU-based validation is disabled. To disable GPU-based validation 
        /// after initially enabling it, the device must be fully released and recreated.
        /// </remarks>
        void SetEnableGPUBasedValidation( bool enable = true )  const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableGPUBasedValidation( enable );
        }

        /// <summary>
        /// Enables or disables dependent command queue synchronization when using a 
        /// Direct3D 12 device with the debug layer enabled.
        /// </summary>
        /// <param name="enable">
        /// true to enable Dependent Command Queue Synchronization, otherwise false.
        /// </param>
        /// <remarks>
        /// <p>
        /// Dependent Command Queue Synchronization is a D3D12 Debug Layer feature 
        /// that gives the debug layer the ability to track resource states more 
        /// accurately when enabled. Dependent Command Queue Synchronization is enabled 
        /// by default.
        /// </p>
        /// <p>
        /// When Dependent Command Queue Synchronization is enabled, the debug layer 
        /// holds back actual submission of GPU work until all outstanding fence Wait 
        /// conditions are met. This gives the debug layer the ability to make reasonable 
        /// assumptions about GPU state (such as resource states) on the CPU-timeline 
        /// when multiple command queues are potentially doing concurrent work.
        /// </p>
        /// <p>
        /// With Dependent Command Queue Synchronization disabled, all resource states 
        /// tracked by the debug layer are cleared each time <see cref="D3D12CommandQueue::Signal">D3D12CommandQueue::Signal</see> 
        /// is called. This results in significantly less useful resource state validation.
        /// </p>
        /// <p>
        /// Disabling Dependent Command Queue Synchronization may reduce some debug layer 
        /// performance overhead when using multiple command queues. However, it is 
        /// suggested to leave it enabled unless this overhead is problematic. Note that 
        /// applications that use only a single command queue will see no performance 
        /// changes with Dependent Command Queue Synchronization disabled.
        /// </p>
        /// </remarks>
        void SetEnableSynchronizedCommandQueueValidation( bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableSynchronizedCommandQueueValidation( enable = true );
        }

        /// <summary>
        /// This method configures the level of GPU-based validation that the debug 
        /// device is to perform at runtime.
        /// </summary>
        /// <param name="flags">
        /// Specifies the level of GPU-based validation to perform at runtime.
        /// </param>
        /// <remarks>
        /// This method overrides the default behavior of GPU-based validation so it must 
        /// be called before creating the D3D12 Device. These settings can't be changed or 
        /// cancelled after the device is created. If you want to change the behavior of 
        /// GPU-based validation at a later time, the device must be destroyed and recreated 
        /// with different parameters.
        /// </remarks>
        void SetGPUBasedValidationFlags( D3D12_GPU_BASED_VALIDATION_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGPUBasedValidationFlags( flags );
        }

    };

    /// <summary>
    /// Adds the ability to disable the debug layer.
    /// </summary>
    class D3D12Debug4 : public D3D12Debug3
    {
    public:
        using Base = D3D12Debug3;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug4, D3D12Debug3, ID3D12Debug4, ID3D12Debug3 )

    public:
        /// <summary>
        /// Disables the debug layer.
        /// </summary>
        /// <remarks>
        /// DisableDebugLayer takes effect only when all ID3D12Device objects 
        /// (for a given adapter) have been released. 
        /// </remarks>
        void DisableDebugLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DisableDebugLayer( );
        }
    };


    /// <summary>
    /// Adds to the debug layer the ability to configure the auto-naming of objects.
    /// </summary>
    class D3D12Debug5 : public D3D12Debug4
    {
    public:
        using Base = D3D12Debug4;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug5, D3D12Debug4, ID3D12Debug5, ID3D12Debug4 )

    public:
        /// <summary>
        /// Configures the auto-naming of objects.
        /// </summary>
        /// <param name="enable">
        /// true to enable auto-naming; false to disable auto-naming.
        /// </param>
        /// <remarks>
        /// <para>
        /// By default, objects are not named unless you use ID3D12Object::SetName 
        /// or ID3D12Object::SetPrivateData to assign a name.
        /// </para>
        /// <para>
        /// It's a best practice to name all of your Direct3D 12 objects; at least 
        /// in debug builds. Failing that, you might find it convenient to allow 
        /// automatic name assignment in order to cover the gaps. Direct3D 12 objects 
        /// created with auto-name enabled are automatically assigned a name, which 
        /// is used for debug layer output and for DRED page fault data.
        /// </para>
        /// <para>
        /// So as not to create a dependency on a specific auto-naming format, you 
        /// can't retrieve the auto-name strings by using ID3D12Object::GetName or 
        /// ID3D12Object::GetPrivateData. But, to generate a unique name string, 
        /// Direct3D 12 uses the locally-unique identifier (LUID) assigned to every 
        /// ID3D12DeviceChild object at create time. You can retrieve that LUID by 
        /// using ID3D12Object::GetPrivateData with the REFGUID value 
        /// WKPDID_D3D12UniqueObjectId. You might find that useful for your own 
        /// object-naming schemas.
        /// </para>
        /// <para>
        /// When debugging existing software, you can control auto-naming by using 
        /// the D3DConfig graphics tools utility and the command 
        /// <c>d3dconfig.exe device auto-debug-name=forced-on.</c>
        /// </para>
        /// <para>
        /// Any object given a name using ID3D12Object::SetName or ID3D12Object::SetPrivateData 
        /// uses the assigned name instead of the auto-name.
        /// </para>
        /// </remarks>
        void SetEnableAutoName( bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableAutoName( enable );
        }
    };

    /// <summary>
    /// A debug interface controls debug settings.
    /// </summary>
    /// <remarks>
    /// Requires the DirectX 12 Agility SDK 1.7 or later.
    /// </remarks>
    class D3D12Debug6 : public D3D12Debug5
    {
    public:
        using Base = D3D12Debug5;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug6, D3D12Debug5, ID3D12Debug6, ID3D12Debug5 )

    public:
        /// <summary>
        /// Configures legacy barrier validation.
        /// </summary>
        /// <param name="enable">
        /// true to enable, otherwise false.
        /// </param>
        /// <remarks>
        /// Legacy barrier validation is a feature that helps developers identify and fix 
        /// issues related to resource state transitions and synchronization between command 
        /// lists 2. When enabled, it causes the Direct3D runtime to validate all resource 
        /// barriers against the legacy rules, which are less flexible than the enhanced rules 
        /// introduced in Direct3D 12.1
        /// </remarks>
        void SetForceLegacyBarrierValidation( bool enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetForceLegacyBarrierValidation( enable );
        }
    };


    /// <summary>
    /// Specifies device-wide debug layer settings.
    /// </summary>
    class D3D12DebugDevice1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice1, Unknown, ID3D12DebugDevice1, IUnknown )

    public:
        /// <summary>
        /// Modifies the D3D12 optional device-wide Debug Layer settings.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_DEVICE_PARAMETER_TYPE value that indicates which debug parameter data to get.
        /// </param>
        /// <param name="data">
        /// Debug parameter data to set.
        /// </param>
        /// <param name="dataSize">
        /// Size in bytes of the data pointed to by <paramref>data</paramref>.
        /// </param>
        void SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _In_reads_bytes_( dataSize ) const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDebugParameter( D3D12_DEBUG_FEATURE features ) const
        {
            SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_FEATURE_FLAGS, &features, sizeof( D3D12_DEBUG_FEATURE ) );
        }

        void SetDebugParameter( const D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS& gpuBasedValidationSettings ) const
        {
            SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &gpuBasedValidationSettings, sizeof( D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS ) );
        }

        void SetDebugParameter( const D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR& gpuSlowdownPerformanceFactor ) const
        {
            SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_SLOWDOWN_PERFORMANCE_FACTOR, &gpuSlowdownPerformanceFactor, sizeof( D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR ) );
        }


        /// <summary>
        /// Gets optional device-wide Debug Layer settings.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_DEVICE_PARAMETER_TYPE value that indicates which debug parameter data to set.
        /// </param>
        /// <param name="data">
        /// Points to the memory that will be filled with a copy of the debug parameter data. The interpretation 
        /// of this data depends on the D3D12_DEBUG_DEVICE_PARAMETER_TYPE given in the <paramref>type</paramref> parameter.
        /// </param>
        /// <param name="dataSize">
        /// Size in bytes of the memory buffer pointed to by <paramref>data</paramref>.
        /// </param>
        void GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<typename T>
        T GetDebugParameter( ) const
        {
            static_assert( false, "Unsupported parameter type" );
        }
        template<>
        D3D12_DEBUG_FEATURE GetDebugParameter<D3D12_DEBUG_FEATURE>( ) const
        {
            D3D12_DEBUG_FEATURE result{};
            GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_FEATURE_FLAGS, &result, sizeof( D3D12_DEBUG_FEATURE ) );
            return result;
        }
        template<>
        D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS GetDebugParameter<D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS>( ) const
        {
            D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS result{};
            GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &result, sizeof( D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS ) );
            return result;
        }
        template<>
        D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR GetDebugParameter<D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR>( ) const
        {
            D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR result{};
            GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_SLOWDOWN_PERFORMANCE_FACTOR, &result, sizeof( D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR ) );
            return result;
        }



        /// <summary>
        /// Specifies the amount of information to report on a device object's lifetime.
        /// </summary>
        /// <param name="flags">
        /// A value from the D3D12_RLDO_FLAGS enumeration. This method uses the 
        /// value in Flags to determine the amount of information to report about 
        /// a device object's lifetime.
        /// </param>
        void ReportLiveDeviceObjects( D3D12_RLDO_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReportLiveDeviceObjects( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// This interface represents a graphics device for debugging.
    /// </summary>
    class D3D12DebugDevice : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice, Unknown, ID3D12DebugDevice, IUnknown )

    public:

        /// <summary>
        /// Set a bit field of flags that will turn debug features on and off.
        /// </summary>
        /// <param name="mask">
        /// Feature-mask flags, as a bitwise-OR'd combination of D3D12_DEBUG_FEATURE 
        /// enumeration constants. If a flag is present, that feature will be set to 
        /// on; otherwise, the feature will be set to off.
        /// </param>
        void SetFeatureMask( D3D12_DEBUG_FEATURE mask ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFeatureMask( mask );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets a bit field of flags that indicates which debug features are on or off.
        /// </summary>
        /// <returns>
        /// Mask of feature-mask flags, as a bitwise OR'ed combination of D3D12_DEBUG_FEATURE 
        /// enumeration constants. If a flag is present, then that feature will be 
        /// set to on, otherwise the feature will be set to off.
        /// </returns>
        D3D12_DEBUG_FEATURE GetFeatureMask( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFeatureMask( );
        }

        /// <summary>
        /// Specifies the amount of information to report on a device object's lifetime.
        /// </summary>
        /// <param name="flags">
        /// A value from the D3D12_RLDO_FLAGS enumeration. This method uses the 
        /// value in Flags to determine the amount of information to report about 
        /// a device object's lifetime.
        /// </param>
        void ReportLiveDeviceObjects( D3D12_RLDO_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReportLiveDeviceObjects( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12DebugDevice2 : public D3D12DebugDevice
    {
    public:
        using Base = D3D12DebugDevice;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice2, D3D12DebugDevice, ID3D12DebugDevice2, ID3D12DebugDevice )
    public:

        /// <summary>
        /// Modifies the D3D12 optional device-wide Debug Layer settings.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_DEVICE_PARAMETER_TYPE value that indicates which debug parameter data to get.
        /// </param>
        /// <param name="data">
        /// Debug parameter data to set.
        /// </param>
        /// <param name="dataSize">
        /// Size in bytes of the data pointed to by <paramref>data</paramref>.
        /// </param>
        void SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _In_reads_bytes_( dataSize ) const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDebugParameter( D3D12_DEBUG_FEATURE features ) const
        {
            SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_FEATURE_FLAGS, &features, sizeof( D3D12_DEBUG_FEATURE ) );
        }

        void SetDebugParameter( const D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS& gpuBasedValidationSettings ) const
        {
            SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &gpuBasedValidationSettings, sizeof( D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS ) );
        }

        void SetDebugParameter( const D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR& gpuSlowdownPerformanceFactor ) const
        {
            SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_SLOWDOWN_PERFORMANCE_FACTOR, &gpuSlowdownPerformanceFactor, sizeof( D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR ) );
        }


        /// <summary>
        /// Gets optional device-wide Debug Layer settings.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_DEVICE_PARAMETER_TYPE value that indicates which debug parameter data to set.
        /// </param>
        /// <param name="data">
        /// Points to the memory that will be filled with a copy of the debug parameter data. The interpretation 
        /// of this data depends on the D3D12_DEBUG_DEVICE_PARAMETER_TYPE given in the <paramref>type</paramref> parameter.
        /// </param>
        /// <param name="dataSize">
        /// Size in bytes of the memory buffer pointed to by <paramref>data</paramref>.
        /// </param>
        void GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<typename T>
        T GetDebugParameter( ) const
        {
            static_assert( false, "Unsupported parameter type" );
        }
        template<>
        D3D12_DEBUG_FEATURE GetDebugParameter<D3D12_DEBUG_FEATURE>( ) const
        {
            D3D12_DEBUG_FEATURE result{};
            GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_FEATURE_FLAGS, &result, sizeof( D3D12_DEBUG_FEATURE ) );
            return result;
        }
        template<>
        D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS GetDebugParameter<D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS>( ) const
        {
            D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS result{};
            GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &result, sizeof( D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS ) );
            return result;
        }
        template<>
        D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR GetDebugParameter<D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR>( ) const
        {
            D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR result{};
            GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE::D3D12_DEBUG_DEVICE_PARAMETER_GPU_SLOWDOWN_PERFORMANCE_FACTOR, &result, sizeof( D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR ) );
            return result;
        }
    };


    /// <summary>
    /// Provides methods to monitor and debug a command queue.
    /// </summary>
    class D3D12DebugCommandQueue : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandQueue, Unknown, ID3D12DebugCommandQueue, IUnknown )
    public:

        /// <summary>
        /// Checks whether a resource, or subresource, is in a specified state, or not.
        /// </summary>
        /// <param name="resource">
        /// Specifies the resource to check.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource to check. This can be set to an 
        /// index, or D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES.
        /// </param>
        /// <param name="state">
        /// Specifies the state to check for. This can be one or more 
        /// D3D12_RESOURCE_STATES flags Or'ed together.
        /// </param>
        /// <returns>
        /// This method returns true if the resource or subresource is in the 
        /// specified state, false otherwise.
        /// </returns>
        bool AssertResourceState( ID3D12Resource* resource, UINT subresource, UINT state ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->AssertResourceState( resource, subresource, state ) != FALSE;
        }

        /// <summary>
        /// Checks whether a resource, or subresource, is in a specified state, or not.
        /// </summary>
        /// <param name="resource">
        /// Specifies the resource to check.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource to check. This can be set to an 
        /// index, or D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES.
        /// </param>
        /// <param name="state">
        /// Specifies the state to check for. This can be one or more 
        /// D3D12_RESOURCE_STATES flags Or'ed together.
        /// </param>
        /// <returns>
        /// This method returns true if the resource or subresource is in the 
        /// specified state, false otherwise.
        /// </returns>
        bool AssertResourceState( const D3D12Resource& resource, UINT subresource, UINT state ) const
        {
            return AssertResourceState( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, state );
        }
    };


    /// <summary>
    /// Enables modification of additional command list debug layer settings.
    /// </summary>
    class D3D12DebugCommandList1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandList1, Unknown, ID3D12DebugCommandList1, IUnknown )
    public:
        /// <summary>
        /// Validates that the given state matches the state of the subresource, assuming 
        /// the state of the given subresource is known during recording of a command list 
        /// (e.g. the resource was transitioned earlier in the same command list recording). 
        /// If the state is not yet known this method sets the known state for further 
        /// validation later in the same command list recording
        /// </summary>
        /// <param name="resource">
        /// Specifies the resource to check.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource to check. This can be set to an index, or 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES.
        /// </param>
        /// <param name="state">
        /// Specifies the state to check for. This can be one or more D3D12_RESOURCE_STATES flags Or'ed together.
        /// </param>
        /// <returns>
        /// This method returns true if the tracked state of the resource or subresource matches the 
        /// specified state, false otherwise.
        /// </returns>
        /// <remarks>
        /// <para>
        /// Since execution of command lists occurs sometime after recording, the state of a 
        /// resource often cannot be known during command list recording. AssertResourceState 
        /// gives an application developer the ability to impose an assumed state on a resource 
        /// or subresource at a fixed recording point in a command list.
        /// </para>
        /// <para>
        /// Often the state of a resource or subresource can either be known due to a previous 
        /// barrier or inferred-by-use (for example, was used in an earlier call to 
        /// CopyBufferRegion) during command list recording. In such cases AssertResourceState 
        /// can produce a debug message if the given state does not match the known or assumed state.
        /// </para>
        /// <para>
        /// This API is for debug validation only and does not affect the actual runtime or GPU 
        /// state of the resource.
        /// </para>
        /// </remarks>
        bool AssertResourceState( ID3D12Resource* resource, UINT subresource, UINT state ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->AssertResourceState( resource, subresource, state ) != FALSE;
        }

        /// <summary>
        /// Validates that the given state matches the state of the subresource, assuming 
        /// the state of the given subresource is known during recording of a command list 
        /// (e.g. the resource was transitioned earlier in the same command list recording). 
        /// If the state is not yet known this method sets the known state for further 
        /// validation later in the same command list recording
        /// </summary>
        /// <param name="resource">
        /// Specifies the resource to check.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource to check. This can be set to an index, or 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES.
        /// </param>
        /// <param name="state">
        /// Specifies the state to check for. This can be one or more D3D12_RESOURCE_STATES flags Or'ed together.
        /// </param>
        /// <returns>
        /// This method returns true if the tracked state of the resource or subresource matches the 
        /// specified state, false otherwise.
        /// </returns>
        /// <remarks>
        /// <para>
        /// Since execution of command lists occurs sometime after recording, the state of a 
        /// resource often cannot be known during command list recording. AssertResourceState 
        /// gives an application developer the ability to impose an assumed state on a resource 
        /// or subresource at a fixed recording point in a command list.
        /// </para>
        /// <para>
        /// Often the state of a resource or subresource can either be known due to a previous 
        /// barrier or inferred-by-use (for example, was used in an earlier call to 
        /// CopyBufferRegion) during command list recording. In such cases AssertResourceState 
        /// can produce a debug message if the given state does not match the known or assumed state.
        /// </para>
        /// <para>
        /// This API is for debug validation only and does not affect the actual runtime or GPU 
        /// state of the resource.
        /// </para>
        /// </remarks>
        bool AssertResourceState( const D3D12Resource& resource, UINT subresource, UINT state ) const
        {
            return AssertResourceState( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, state );
        }

        /// <summary>
        /// Modifies optional Debug Layer settings of a command list.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE value that 
        /// indicates which debug parameter data to set.
        /// </param>
        /// <param name="data">
        /// Pointer to debug parameter data to set. The interpretation of this 
        /// data depends on the D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE given 
        /// in the <paramref>type</paramref> parameter.
        /// </param>
        /// <param name="dataSize">
        /// Specifies the size in bytes of the debug parameter <paramref>data</paramref>.
        /// </param>
        void SetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _In_reads_bytes_( dataSize )  const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDebugParameter( const D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS& gpuBasedValidationSettings ) const
        {
            SetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE::D3D12_DEBUG_COMMAND_LIST_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &gpuBasedValidationSettings, sizeof( D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS ) );
        }


        /// <summary>
        /// Gets optional Command List Debug Layer settings.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE value that 
        /// determines which debug parameter data to copy to the memory 
        /// pointed to by <paramref>data</paramref>.
        /// </param>
        /// <param name="data">
        /// Points to the memory that will be filled with a copy of the debug parameter 
        /// data. The interpretation of this data depends on the 
        /// D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE given in the <paramref>type</paramref> parameter.
        /// </param>
        /// <param name="dataSize">
        /// Size in bytes of the memory buffer pointed to by <paramref>data</paramref>.
        /// </param>
        void GetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        T GetDebugParameter( ) const
        {
            static_assert( false, "Unsupported parameter type" );
        }

        template<>
        D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS GetDebugParameter<D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS>( ) const
        {
            D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS result{};
            GetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE::D3D12_DEBUG_COMMAND_LIST_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &result, sizeof( D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS ) );
            return result;
        }


    };


    /// <summary>
    /// Provides methods to monitor and debug a command list.
    /// </summary>
    class D3D12DebugCommandList : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandList, Unknown, ID3D12DebugCommandList, IUnknown )
    public:
        /// <summary>
        /// Checks whether a resource, or subresource, is in a specified state, or not.
        /// </summary>
        /// <param name="resource">
        /// Specifies the resource to check.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource to check. This can be set to an index, or 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES.
        /// </param>
        /// <param name="state">
        /// Specifies the state to check for. This can be one or more 
        /// D3D12_RESOURCE_STATES flags Or'ed together.
        /// </param>
        /// <returns>
        /// This method returns true if the resource or subresource is in the 
        /// specified state, false otherwise.
        /// </returns>
        bool AssertResourceState( ID3D12Resource* resource, UINT subresource, UINT state ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->AssertResourceState( resource, subresource, state ) != FALSE;
        }

        /// <summary>
        /// Checks whether a resource, or subresource, is in a specified state, or not.
        /// </summary>
        /// <param name="resource">
        /// Specifies the resource to check.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource to check. This can be set to an index, or 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES.
        /// </param>
        /// <param name="state">
        /// Specifies the state to check for. This can be one or more 
        /// D3D12_RESOURCE_STATES flags Or'ed together.
        /// </param>
        /// <returns>
        /// This method returns true if the resource or subresource is in the 
        /// specified state, false otherwise.
        /// </returns>
        bool AssertResourceState( const D3D12Resource& resource, UINT subresource, UINT state ) const
        {
            return AssertResourceState( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, state );
        }

        /// <summary>
        /// Turns the debug features for a command list on or off.
        /// </summary>
        /// <param name="mask">
        /// A combination of feature-mask flags that are combined by using a 
        /// bitwise OR operation. If a flag is present, that feature will be 
        /// set to on, otherwise the feature will be set to off.
        /// </param>
        void SetFeatureMask( D3D12_DEBUG_FEATURE mask ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFeatureMask( mask );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the debug feature flags that have been set on a command list.
        /// </summary>
        /// <returns>
        /// A bit mask containing the set debug features.
        /// </returns>
        D3D12_DEBUG_FEATURE GetFeatureMask( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFeatureMask( );
        }
    };


    /// <summary>
    /// 
    /// </summary>
    class D3D12DebugCommandList2 : public D3D12DebugCommandList
    {
    public:
        using Base = D3D12DebugCommandList;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandList2, D3D12DebugCommandList, ID3D12DebugCommandList2, ID3D12DebugCommandList )
    public:
        /// <summary>
        /// Modifies optional Debug Layer settings of a command list.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE value that 
        /// indicates which debug parameter data to set.
        /// </param>
        /// <param name="data">
        /// Pointer to debug parameter data to set. The interpretation of this 
        /// data depends on the D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE given 
        /// in the <paramref>type</paramref> parameter.
        /// </param>
        /// <param name="dataSize">
        /// Specifies the size in bytes of the debug parameter <paramref>data</paramref>.
        /// </param>
        void SetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _In_reads_bytes_( dataSize )  const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDebugParameter( const D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS& gpuBasedValidationSettings ) const
        {
            SetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE::D3D12_DEBUG_COMMAND_LIST_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &gpuBasedValidationSettings, sizeof( D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS ) );
        }


        /// <summary>
        /// Gets optional Command List Debug Layer settings.
        /// </summary>
        /// <param name="type">
        /// Specifies a D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE value that 
        /// determines which debug parameter data to copy to the memory 
        /// pointed to by <paramref>data</paramref>.
        /// </param>
        /// <param name="data">
        /// Points to the memory that will be filled with a copy of the debug parameter 
        /// data. The interpretation of this data depends on the 
        /// D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE given in the <paramref>type</paramref> parameter.
        /// </param>
        /// <param name="dataSize">
        /// Size in bytes of the memory buffer pointed to by <paramref>data</paramref>.
        /// </param>
        void GetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        T GetDebugParameter( ) const
        {
            static_assert( false, "Unsupported parameter type" );
        }

        template<>
        D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS GetDebugParameter<D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS>( ) const
        {
            D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS result{};
            GetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE::D3D12_DEBUG_COMMAND_LIST_PARAMETER_GPU_BASED_VALIDATION_SETTINGS, &result, sizeof( D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS ) );
            return result;
        }
    };


    /// <summary>
    /// Facilitates diagnostics tools to capture information at a lower 
    /// level than the DXGI swapchain.
    /// </summary>
    /// <remarks>
    /// <para>
    /// You may want to use this class to enable diagnostic tools to capture 
    /// usage patterns that don't use DXGI swap chains for presentation. If so, 
    /// you can create and instance of this class by calling the static <see cref="">Create</see> 
    /// function passing the queue as its parameter. 
    /// </para>
    /// <para>
    /// Note that the underlying interface is not supported when there are no diagnostic 
    /// tools present, so your application mustn't rely on it existing.
    /// </para>
    /// </remarks>
    class D3D12SharingContract : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12SharingContract, Unknown, ID3D12SharingContract, IUnknown )
    public:
        /// <summary>
        /// Creates a new D3D12SharingContract object.
        /// </summary>
        /// <param name="commandQueue">
        /// The IUnknown interface of the command queue
        /// </param>
        /// <returns>
        /// The new D3D12SharingContract object.
        /// </returns>
        static D3D12SharingContract Create( IUnknown* commandQueue )
        {
            if ( commandQueue )
            {
                ID3D12SharingContract* pInterface = nullptr;
                auto hr = commandQueue->QueryInterface( &pInterface );
                if ( SUCCEEDED( hr ) )
                {
                    return D3D12SharingContract( pInterface );
                }
                return {};
            }
            else
            {
                ThrowNoInterface( );
            }
        }

        /// <summary>
        /// Creates a new D3D12SharingContract object.
        /// </summary>
        /// <param name="commandQueue">
        /// The Unknown interface wrapper of the command queue
        /// </param>
        /// <returns>
        /// The new D3D12SharingContract object.
        /// </returns>
        static D3D12SharingContract Create( const Unknown& commandQueue )
        {
            return Create( commandQueue.GetInterfacePointer<IUnknown>( ) );
        }


        /// <summary>
        /// Enables usage of tools like PIX with applications that either don't 
        /// render to a window, or that do so in non-traditional ways.
        /// </summary>
        /// <param name="resource">
        /// The resource that contains the final frame contents. This resource is 
        /// treated as the back buffer of the Present.
        /// </param>
        /// <param name="subresource">
        /// An unsigned 32bit subresource id.
        /// </param>
        /// <param name="window">
        /// If provided, indicates which window the tools should use for displaying 
        /// additional diagnostic information.
        /// </param>
        void Present( _In_ ID3D12Resource* resource, UINT subresource, _In_  HWND window = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Present( resource, subresource, window );
        }

        /// <summary>
        /// Enables usage of tools like PIX with applications that either don't 
        /// render to a window, or that do so in non-traditional ways.
        /// </summary>
        /// <param name="resource">
        /// The resource that contains the final frame contents. This resource is 
        /// treated as the back buffer of the Present.
        /// </param>
        /// <param name="subresource">
        /// An unsigned 32bit subresource id.
        /// </param>
        /// <param name="window">
        /// If provided, indicates which window the tools should use for displaying 
        /// additional diagnostic information.
        /// </param>
        void Present( const D3D12Resource& resource, UINT subresource, _In_  HWND window = nullptr ) const
        {
            Present( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, window );
        }


        /// <summary>
        /// Signals a shared fence between the D3D layers and diagnostics tools.
        /// </summary>
        /// <param name="fence">
        /// The shared fence to signal.
        /// </param>
        /// <param name="fenceValue">
        /// An unsigned 64bit value to signal the shared fence with.
        /// </param>
        void SharedFenceSignal( _In_ ID3D12Fence* fence, UINT64 fenceValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SharedFenceSignal( fence, fenceValue );
        }

        /// <summary>
        /// Signals a shared fence between the D3D layers and diagnostics tools.
        /// </summary>
        /// <param name="fence">
        /// The shared fence to signal.
        /// </param>
        /// <param name="fenceValue">
        /// An unsigned 64bit value to signal the shared fence with.
        /// </param>
        void SharedFenceSignal( const D3D12Fence& fence, UINT64 fenceValue ) const
        {
            SharedFenceSignal( fence.GetInterfacePointer<ID3D12Fence>( ), fenceValue );
        }

        /// <summary>
        /// Begins a sequence of work that can be captured and replayed later.
        /// </summary>
        /// <param name="guid">
        /// Identifies the work sequence.
        /// </param>
        void BeginCapturableWork( _In_ REFGUID guid ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginCapturableWork( guid );
        }

        /// <summary>
        /// Signals the end of a capture sequence, which is a series of operations 
        /// that are captured and replayed on another device. 
        /// </summary>
        /// <param name="guid">
        /// Identifies the capture sequence
        /// </param>
        void EndCapturableWork( _In_ REFGUID guid ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndCapturableWork( guid );
        }
        
    };


    /// <summary>
    /// An information-queue stores, retrieves, and filters debug messages. The queue consists of a 
    /// message queue, an optional storage filter stack, and a optional retrieval filter stack.
    /// </summary>
    class D3D12InfoQueue : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12InfoQueue, Unknown, ID3D12InfoQueue, IUnknown )
    public:
        /// <summary>
        /// Set the maximum number of messages that can be added to the message queue.
        /// </summary>
        /// <param name="messageCountLimit">
        /// <para>
        /// Maximum number of messages that can be added to the message queue. -1 means no limit.
        /// </para>
        /// <para>
        /// </para>
        /// When the number of messages in the message queue has reached the maximum limit, 
        /// new messages coming in will push old messages out.
        /// </param>
        void SetMessageCountLimit( _In_  UINT64 messageCountLimit ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetMessageCountLimit( messageCountLimit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Clear all messages from the message queue.
        /// </summary>
        void ClearStoredMessages( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearStoredMessages( );
        }

        /// <summary>
        /// Get a message from the message queue.
        /// </summary>
        /// <param name="messageIndex">
        /// Index into message queue after an optional retrieval filter has been 
        /// applied. This can be between 0 and the number of messages in the 
        /// message queue that pass through the retrieval filter (which can be 
        /// obtained with GetNumStoredMessagesAllowedByRetrievalFilter). 
        /// 0 is the message at the front of the message queue.
        /// </param>
        /// <param name="message">
        /// Returned message.
        /// </param>
        /// <param name="messageByteLength">
        /// Size of message in bytes.
        /// </param>
        void GetMessage( _In_  UINT64 messageIndex, _Out_writes_bytes_opt_( *messageByteLength )  D3D12_MESSAGE* message, _Inout_  SIZE_T* messageByteLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetMessage( messageIndex, message, messageByteLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get the number of messages that were allowed to pass through a storage filter.
        /// </summary>
        /// <returns>
        /// Number of messages allowed by a storage filter.
        /// </returns>
        UINT64 GetNumMessagesAllowedByStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumMessagesAllowedByStorageFilter( );
        }


        /// <summary>
        /// Get the number of messages that were denied passage through a storage filter.
        /// </summary>
        /// <returns>
        /// Number of messages denied by a storage filter.
        /// </returns>
        UINT64 GetNumMessagesDeniedByStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumMessagesDeniedByStorageFilter( );
        }

        /// <summary>
        /// Get the number of messages currently stored in the message queue.
        /// </summary>
        /// <returns>
        /// Number of messages currently stored in the message queue.
        /// </returns>
        UINT64 GetNumStoredMessages( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumStoredMessages( );
        }

        /// <summary>
        /// Get the number of messages that are able to pass through a retrieval filter.
        /// </summary>
        /// <returns>
        /// Number of messages allowed by a retrieval filter.
        /// </returns>
        UINT64 GetNumStoredMessagesAllowedByRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumStoredMessagesAllowedByRetrievalFilter( );
        }

        /// <summary>
        /// Get the number of messages that were discarded due to the message count limit.
        /// </summary>
        /// <returns>
        /// Number of messages discarded.
        /// </returns>
        UINT64 GetNumMessagesDiscardedByMessageCountLimit( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumMessagesDiscardedByMessageCountLimit( );
        }

        /// <summary>
        /// Get the maximum number of messages that can be added to the message queue.
        /// </summary>
        /// <returns>
        /// <para>
        /// Maximum number of messages that can be added to the queue. -1 means no limit. 
        /// </para>
        /// <para>
        /// When the number of messages in the message queue has reached the maximum limit, 
        /// new messages coming in will push old messages out.
        /// </para>
        /// </returns>
        UINT64 GetMessageCountLimit( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMessageCountLimit( );
        }

        /// <summary>
        /// Add storage filters to the top of the storage-filter stack.
        /// </summary>
        /// <param name="filter">
        /// Array of storage filters.
        /// </param>
        void AddStorageFilterEntries( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddStorageFilterEntries( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get the storage filter at the top of the storage-filter stack.
        /// </summary>
        /// <param name="filter">
        /// Storage filter at the top of the storage-filter stack.
        /// </param>
        /// <param name="filterByteLength">
        /// Size of the storage filter in bytes. If filter is NULL, the size 
        /// of the storage filter will be output to this parameter.
        /// </param>
        void GetStorageFilter( _Out_writes_bytes_opt_( *filterByteLength )  D3D12_INFO_QUEUE_FILTER* filter, _Inout_  SIZE_T* filterByteLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetStorageFilter( filter, filterByteLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Remove a storage filter from the top of the storage-filter stack.
        /// </summary>
        void ClearStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearStorageFilter( );
        }

        /// <summary>
        /// Push an empty storage filter onto the storage-filter stack.
        /// </summary>
        void PushEmptyStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushEmptyStorageFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Push a copy of storage filter currently on the top of the storage-filter stack onto the storage-filter stack.
        /// </summary>
        void PushCopyOfStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushCopyOfStorageFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Push a storage filter onto the storage-filter stack.
        /// </summary>
        /// <param name="filter">
        /// Pointer to a storage filter.
        /// </param>
        void PushStorageFilter( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushStorageFilter( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Pop a storage filter from the top of the storage-filter stack.
        /// </summary>
        void PopStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PopStorageFilter( );
        }

        /// <summary>
        /// Get the size of the storage-filter stack in bytes.
        /// </summary>
        /// <returns>
        /// Size of the storage-filter stack in bytes.
        /// </returns>
        UINT GetStorageFilterStackSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStorageFilterStackSize( );
        }

        /// <summary>
        /// Add storage filters to the top of the retrieval-filter stack.
        /// </summary>
        /// <param name="filter">
        /// Array of retrieval filters.
        /// </param>
        void AddRetrievalFilterEntries( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddRetrievalFilterEntries( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get the retrieval filter at the top of the retrieval-filter stack.
        /// </summary>
        /// <param name="filter">
        /// Retrieval filter at the top of the retrieval-filter stack.
        /// </param>
        /// <param name="filterByteLength">
        /// Size of the retrieval filter in bytes. If filter is NULL, the size of 
        /// the retrieval filter will be output to this parameter.
        /// </param>
        void GetRetrievalFilter( _Out_writes_bytes_opt_( *filterByteLength )  D3D12_INFO_QUEUE_FILTER* filter, _Inout_  SIZE_T* filterByteLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetRetrievalFilter( filter, filterByteLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Remove a retrieval filter from the top of the retrieval-filter stack.
        /// </summary>
        void ClearRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearRetrievalFilter( );
        }

        /// <summary>
        /// Push an empty retrieval filter onto the retrieval-filter stack.
        /// </summary>
        void PushEmptyRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushEmptyRetrievalFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Push a copy of retrieval filter currently on the top of the retrieval-filter stack onto the retrieval-filter stack.
        /// </summary>
        void PushCopyOfRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushCopyOfRetrievalFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Push a retrieval filter onto the retrieval-filter stack.
        /// </summary>
        /// <param name="filter">
        /// Pointer to a retrieval filter.
        /// </param>
        void PushRetrievalFilter( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushRetrievalFilter( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Pop a retrieval filter from the top of the retrieval-filter stack.
        /// </summary>
        void PopRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PopRetrievalFilter( );
        }

        /// <summary>
        /// Get the size of the retrieval-filter stack in bytes.
        /// </summary>
        /// <returns>
        /// Size of the retrieval-filter stack in bytes.
        /// </returns>
        UINT GetRetrievalFilterStackSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRetrievalFilterStackSize( );
        }

        /// <summary>
        /// Adds a debug message to the message queue and sends that message to debug output.
        /// </summary>
        /// <param name="category">
        /// Category of a message.
        /// </param>
        /// <param name="severity">
        /// Severity of a message.
        /// </param>
        /// <param name="id">
        /// Unique identifier of a message.
        /// </param>
        /// <param name="description">
        /// User-defined message.
        /// </param>
        /// <remarks>
        /// This method is used by the runtime's internal mechanisms to add debug messages to 
        /// the message queue and send them to debug output. For applications to add their own 
        /// custom messages to the message queue and send them to debug output, call 
        /// <see cref="D3D12InfoQueue::AddApplicationMessage">D3D12InfoQueue::AddApplicationMessage.</see>
        /// </remarks>
        void AddMessage( _In_  D3D12_MESSAGE_CATEGORY category, _In_  D3D12_MESSAGE_SEVERITY severity, _In_  D3D12_MESSAGE_ID id, _In_  LPCSTR description ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddMessage( category, severity, id, description );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Adds a user-defined message to the message queue and sends that message to debug output.
        /// </summary>
        /// <param name="severity">
        /// Severity of a message.
        /// </param>
        /// <param name="description">
        /// Specifies the message string.
        /// </param>
        void AddApplicationMessage( _In_  D3D12_MESSAGE_SEVERITY severity, _In_  LPCSTR description ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddApplicationMessage( severity, description );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Set a message category to break on when a message with that category passes through the storage filter.
        /// </summary>
        /// <param name="category">
        /// Message category to break on.
        /// </param>
        /// <param name="enable">
        /// Turns this breaking condition on or off (true for on, false for off).
        /// </param>
        void SetBreakOnCategory( _In_  D3D12_MESSAGE_CATEGORY category, _In_  bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetBreakOnCategory( category, enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Set a message severity level to break on when a message with that severity 
        /// level passes through the storage filter.
        /// </summary>
        /// <param name="severity">
        /// A message severity level to break on.
        /// </param>
        /// <param name="enable">
        /// Turns this breaking condition on or off (true for on, false for off).
        /// </param>
        void SetBreakOnSeverity( _In_  D3D12_MESSAGE_SEVERITY severity, _In_  bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetBreakOnSeverity( severity, enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Set a message identifier to break on when a message with that identifier passes through the storage filter.
        /// </summary>
        /// <param name="id">
        /// Message identifier to break on.
        /// </param>
        /// <param name="enable">
        /// Turns this breaking condition on or off (true for on, false for off).
        /// </param>
        void SetBreakOnID( _In_  D3D12_MESSAGE_ID id, _In_  bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetBreakOnID( id, enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get a message category to break on when a message with that category passes through the storage filter.
        /// </summary>
        /// <param name="category">
        /// Message category to break on.
        /// </param>
        /// <returns>
        /// Whether this breaking condition is turned on or off (true for on, false for off).
        /// </returns>
        bool GetBreakOnCategory( _In_  D3D12_MESSAGE_CATEGORY category ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBreakOnCategory( category ) != false; 
        }

        /// <summary>
        /// Get a message severity level to break on when a message with that severity 
        /// level passes through the storage filter.
        /// </summary>
        /// <param name="severity">
        /// Message severity level to break on.
        /// </param>
        /// <returns>
        /// Whether this breaking condition is turned on or off (true for on, false for off).
        /// </returns>
        bool GetBreakOnSeverity( _In_  D3D12_MESSAGE_SEVERITY severity ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBreakOnSeverity( severity ) != false;
        }

        /// <summary>
        /// Get a message identifier to break on when a message with that identifier passes through the storage filter.
        /// </summary>
        /// <param name="id">
        /// Message identifier to break on.
        /// </param>
        /// <returns>
        /// Whether this breaking condition is turned on or off (true for on, false for off).
        /// </returns>
        bool GetBreakOnID( _In_  D3D12_MESSAGE_ID id ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBreakOnID( id );
        }

        /// <summary>
        /// Set a boolean that turns the debug output on or off.
        /// </summary>
        /// <param name="mute">
        /// Disable/Enable the debug output (true to disable or mute the output, false to enable the output).
        /// </param>
        /// <remarks>
        /// This will stop messages that pass the storage filter from being printed out 
        /// in the debug output, however those messages will still be added to the message queue.
        /// </remarks>
        void SetMuteDebugOutput( _In_  bool mute = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetMuteDebugOutput( mute );
        }

        /// <summary>
        /// Get a boolean that determines if debug output is on or off.
        /// </summary>
        /// <returns>
        /// Whether the debug output is on or off (true for on, false for off).
        /// </returns>
        bool GetMuteDebugOutput( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMuteDebugOutput( );
        }
    };


    /// <summary>
    /// D3D12InfoQueue1 adds support for message callback with the 
    /// RegisterMessageCallback and UnregisterMessageCallback functions.
    /// </summary>
    class D3D12InfoQueue1 : public D3D12InfoQueue
    {
    public:
        using Base = D3D12InfoQueue;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12InfoQueue1, D3D12InfoQueue, ID3D12InfoQueue1, ID3D12InfoQueue )
    public:
        /// <summary>
        /// registers a callback that is called at the time a debug message is produced.
        /// </summary>
        /// <param name="callbackFunc">
        /// A callback function pointer which allows users to register a callback that is called at the time a debug message is produced.
        /// </param>
        /// <param name="callbackFilterFlags">
        /// If this value is set to D3D12_MESSAGE_CALLBACK_IGNORE_FILTERS, current callback is unfiltered. If 
        /// this value is set to D3D12_MESSAGE_CALLBACK_FLAG_NONE, current callback is filtered in the exact 
        /// same way as what gets logged as debug text.
        /// </param>
        /// <param name="context">
        /// Can be set to point to anything users want. They can access pContext they specified here in D3D12MessageFunc. 
        /// This allows users to attach their own additional data to the callback.
        /// </param>
        /// <param name="callbackCookie">
        /// An output parameter that uniquely identifies the registered callback, the value pointed to by 
        /// callbackCookie is set to zero if the callback registration fails.
        /// </param>
        void RegisterMessageCallback( _In_  D3D12MessageFunc callbackFunc, _In_  D3D12_MESSAGE_CALLBACK_FLAGS callbackFilterFlags, _In_  void* context, _Inout_  DWORD* callbackCookie ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->RegisterMessageCallback( callbackFunc, callbackFilterFlags, context, callbackCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Unregisters a previously registered callback.
        /// </summary>
        /// <param name="callbackCookie">
        /// The cookie that identifies the callback to unregister.
        /// </param>
        void UnregisterMessageCallback( _In_  DWORD callbackCookie ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->UnregisterMessageCallback( callbackCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

}

#endif
