//--------------------------------------------------------------------------------------
// File: Effects.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#ifndef __DIRECTXTK_EFFECTS_H__
#define __DIRECTXTK_EFFECTS_H__

#include <HDirectXTK12Def.h>

#ifdef _GAMING_XBOX_SCARLETT
#include <d3d12_xs.h>
#elif (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
#include <d3d12_x.h>
#elif defined(USING_DIRECTX_HEADERS)
#include <directx/d3d12.h>
#include <dxguids/dxguids.h>
#else
#include <d3d12.h>
#endif

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include <DirectXMath.h>

#include "RenderTargetState.h"
#include "EffectPipelineStateDescription.h"


namespace DirectX
{
    class DescriptorHeap;
    class ResourceUploadBatch;

    inline namespace DX12
    {
        //------------------------------------------------------------------------------
        // Abstract interface representing any effect which can be applied onto a D3D device context.
        class IEffect
        {
        public:
            virtual ~IEffect() = default;

            IEffect(const IEffect&) = delete;
            IEffect& operator=(const IEffect&) = delete;

            virtual void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) = 0;

        protected:
            IEffect() = default;
            IEffect(IEffect&&) = default;
            IEffect& operator=(IEffect&&) = default;
        };


        // Abstract interface for effects with world, view, and projection matrices.
        class IEffectMatrices
        {
        public:
            virtual ~IEffectMatrices() = default;

            IEffectMatrices(const IEffectMatrices&) = delete;
            IEffectMatrices& operator=(const IEffectMatrices&) = delete;

            virtual void XM_CALLCONV SetWorld(FXMMATRIX value) = 0;
            virtual void XM_CALLCONV SetView(FXMMATRIX value) = 0;
            virtual void XM_CALLCONV SetProjection(FXMMATRIX value) = 0;
            HDXTK12_EXPORT virtual void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection);

        protected:
            IEffectMatrices() = default;
            IEffectMatrices(IEffectMatrices&&) = default;
            IEffectMatrices& operator=(IEffectMatrices&&) = default;
        };


        // Abstract interface for effects which support directional lighting.
        class IEffectLights
        {
        public:
            virtual ~IEffectLights() = default;

            IEffectLights(const IEffectLights&) = delete;
            IEffectLights& operator=(const IEffectLights&) = delete;

            virtual void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) = 0;

            virtual void __cdecl SetLightEnabled(int whichLight, bool value) = 0;
            virtual void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) = 0;
            virtual void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) = 0;
            virtual void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) = 0;

            virtual void __cdecl EnableDefaultLighting() = 0;

            static constexpr int MaxDirectionalLights = 3;

        protected:
            IEffectLights() = default;
            IEffectLights(IEffectLights&&) = default;
            IEffectLights& operator=(IEffectLights&&) = default;
        };


        // Abstract interface for effects which support fog.
        class IEffectFog
        {
        public:
            virtual ~IEffectFog() = default;

            IEffectFog(const IEffectFog&) = delete;
            IEffectFog& operator=(const IEffectFog&) = delete;

            virtual void __cdecl SetFogStart(float value) = 0;
            virtual void __cdecl SetFogEnd(float value) = 0;
            virtual void XM_CALLCONV SetFogColor(FXMVECTOR value) = 0;

        protected:
            IEffectFog() = default;
            IEffectFog(IEffectFog&&) = default;
            IEffectFog& operator=(IEffectFog&&) = default;
        };


        // Abstract interface for effects which support skinning
        class IEffectSkinning
        {
        public:
            virtual ~IEffectSkinning() = default;

            IEffectSkinning(const IEffectSkinning&) = delete;
            IEffectSkinning& operator=(const IEffectSkinning&) = delete;

            virtual void __cdecl SetBoneTransforms(_In_reads_(count) XMMATRIX const* value, size_t count) = 0;
            virtual void __cdecl ResetBoneTransforms() = 0;

            static constexpr int MaxBones = 72;

        protected:
            IEffectSkinning() = default;
            IEffectSkinning(IEffectSkinning&&) = default;
            IEffectSkinning& operator=(IEffectSkinning&&) = default;
        };


        //------------------------------------------------------------------------------
        namespace EffectFlags
        {
            constexpr uint32_t None = 0x00;
            constexpr uint32_t Fog = 0x01;
            constexpr uint32_t Lighting = 0x02;

            constexpr uint32_t PerPixelLighting = 0x04 | Lighting;
            // per pixel lighting implies lighting enabled

            constexpr uint32_t VertexColor = 0x08;
            constexpr uint32_t Texture = 0x10;
            constexpr uint32_t Instancing = 0x20;

            constexpr uint32_t Specular = 0x100;
            // enable optional specular/specularMap feature

            constexpr uint32_t Emissive = 0x200;
            // enable optional emissive/emissiveMap feature

            constexpr uint32_t Fresnel = 0x400;
            // enable optional Fresnel feature

            constexpr uint32_t Velocity = 0x800;
            // enable optional velocity feature

            constexpr uint32_t BiasedVertexNormals = 0x10000;
            // compressed vertex normals need x2 bias
        }


        //------------------------------------------------------------------------------
        // Built-in shader supports optional texture mapping, vertex coloring, directional lighting, and fog.
        class BasicEffect : public IEffect, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
        public:
            HDXTK12_EXPORT BasicEffect(_In_ ID3D12Device* device, uint32_t effectFlags, const EffectPipelineStateDescription& pipelineDescription);

            HDXTK12_EXPORT BasicEffect(BasicEffect&&) noexcept;
            HDXTK12_EXPORT BasicEffect& operator= (BasicEffect&&) noexcept;

            BasicEffect(BasicEffect const&) = delete;
            BasicEffect& operator= (BasicEffect const&) = delete;

            HDXTK12_EXPORT ~BasicEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Material settings.
            HDXTK12_EXPORT void XM_CALLCONV SetDiffuseColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetEmissiveColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetSpecularColor(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetSpecularPower(float value);
            HDXTK12_EXPORT void __cdecl DisableSpecular();
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetColorAndAlpha(FXMVECTOR value);

            // Light settings.
            HDXTK12_EXPORT void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl SetLightEnabled(int whichLight, bool value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl EnableDefaultLighting() override;

            // Fog settings.
            HDXTK12_EXPORT void __cdecl SetFogStart(float value) override;
            HDXTK12_EXPORT void __cdecl SetFogEnd(float value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetFogColor(FXMVECTOR value) override;

            // Texture setting.
            HDXTK12_EXPORT void __cdecl SetTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };


        // Built-in shader supports per-pixel alpha testing.
        class AlphaTestEffect : public IEffect, public IEffectMatrices, public IEffectFog
        {
        public:
            HDXTK12_EXPORT AlphaTestEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription,
                D3D12_COMPARISON_FUNC alphaFunction = D3D12_COMPARISON_FUNC_GREATER);

            HDXTK12_EXPORT AlphaTestEffect(AlphaTestEffect&&) noexcept;
            HDXTK12_EXPORT AlphaTestEffect& operator= (AlphaTestEffect&&) noexcept;

            AlphaTestEffect(AlphaTestEffect const&) = delete;
            AlphaTestEffect& operator= (AlphaTestEffect const&) = delete;

            HDXTK12_EXPORT ~AlphaTestEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Material settings.
            HDXTK12_EXPORT void XM_CALLCONV SetDiffuseColor(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetColorAndAlpha(FXMVECTOR value);

            // Fog settings.
            HDXTK12_EXPORT void __cdecl SetFogStart(float value) override;
            HDXTK12_EXPORT void __cdecl SetFogEnd(float value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetFogColor(FXMVECTOR value) override;

            // Texture setting.
            HDXTK12_EXPORT void __cdecl SetTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);

            // Alpha test settings.
            HDXTK12_EXPORT void __cdecl SetReferenceAlpha(int value);

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };


        // Built-in shader supports two layer multitexturing (eg. for lightmaps or detail textures).
        class DualTextureEffect : public IEffect, public IEffectMatrices, public IEffectFog
        {
        public:
            HDXTK12_EXPORT DualTextureEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription);

            HDXTK12_EXPORT DualTextureEffect(DualTextureEffect&&) noexcept;
            HDXTK12_EXPORT DualTextureEffect& operator= (DualTextureEffect&&) noexcept;

            DualTextureEffect(DualTextureEffect const&) = delete;
            DualTextureEffect& operator= (DualTextureEffect const&) = delete;

            HDXTK12_EXPORT ~DualTextureEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Material settings.
            HDXTK12_EXPORT void XM_CALLCONV SetDiffuseColor(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetColorAndAlpha(FXMVECTOR value);

            // Fog settings.
            HDXTK12_EXPORT void __cdecl SetFogStart(float value) override;
            HDXTK12_EXPORT void __cdecl SetFogEnd(float value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetFogColor(FXMVECTOR value) override;

            // Texture settings.
            HDXTK12_EXPORT void __cdecl SetTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);
            HDXTK12_EXPORT void __cdecl SetTexture2(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };


        // Built-in shader supports cubic environment mapping.
        class EnvironmentMapEffect : public IEffect, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
        public:
            enum Mapping : uint32_t
            {
                Mapping_Cube = 0,       // Cubic environment map
                Mapping_Sphere,         // Spherical environment map
                Mapping_DualParabola,   // Dual-parabola environment map (requires Feature Level 10.0)
            };

            HDXTK12_EXPORT EnvironmentMapEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription,
                Mapping mapping = Mapping_Cube);

            HDXTK12_EXPORT EnvironmentMapEffect(EnvironmentMapEffect&&) noexcept;
            HDXTK12_EXPORT EnvironmentMapEffect& operator= (EnvironmentMapEffect&&) noexcept;

            EnvironmentMapEffect(EnvironmentMapEffect const&) = delete;
            EnvironmentMapEffect& operator= (EnvironmentMapEffect const&) = delete;

            HDXTK12_EXPORT ~EnvironmentMapEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Material settings.
            HDXTK12_EXPORT void XM_CALLCONV SetDiffuseColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetEmissiveColor(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetColorAndAlpha(FXMVECTOR value);

            // Light settings.
            HDXTK12_EXPORT void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl SetLightEnabled(int whichLight, bool value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl EnableDefaultLighting() override;

            // Fog settings.
            HDXTK12_EXPORT void __cdecl SetFogStart(float value) override;
            HDXTK12_EXPORT void __cdecl SetFogEnd(float value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetFogColor(FXMVECTOR value) override;

            // Texture setting.
            HDXTK12_EXPORT void __cdecl SetTexture(D3D12_GPU_DESCRIPTOR_HANDLE texture, D3D12_GPU_DESCRIPTOR_HANDLE sampler);

            // Environment map settings.
            HDXTK12_EXPORT void __cdecl SetEnvironmentMap(D3D12_GPU_DESCRIPTOR_HANDLE texture, D3D12_GPU_DESCRIPTOR_HANDLE sampler);
            HDXTK12_EXPORT void __cdecl SetEnvironmentMapAmount(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetEnvironmentMapSpecular(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetFresnelFactor(float value);

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;

            // Unsupported interface methods.
            HDXTK12_EXPORT void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;
        };


        // Built-in shader supports skinned animation.
        class SkinnedEffect : public IEffect, public IEffectMatrices, public IEffectLights, public IEffectFog, public IEffectSkinning
        {
        public:
            HDXTK12_EXPORT SkinnedEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription);

            HDXTK12_EXPORT SkinnedEffect(SkinnedEffect&&) noexcept;
            HDXTK12_EXPORT SkinnedEffect& operator= (SkinnedEffect&&) noexcept;

            SkinnedEffect(SkinnedEffect const&) = delete;
            SkinnedEffect& operator= (SkinnedEffect const&) = delete;

            HDXTK12_EXPORT ~SkinnedEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Material settings.
            HDXTK12_EXPORT void XM_CALLCONV SetDiffuseColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetEmissiveColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetSpecularColor(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetSpecularPower(float value);
            HDXTK12_EXPORT void __cdecl DisableSpecular();
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetColorAndAlpha(FXMVECTOR value);

            // Light settings.
            HDXTK12_EXPORT void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl SetLightEnabled(int whichLight, bool value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl EnableDefaultLighting() override;

            // Fog settings.
            HDXTK12_EXPORT void __cdecl SetFogStart(float value) override;
            HDXTK12_EXPORT void __cdecl SetFogEnd(float value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetFogColor(FXMVECTOR value) override;

            // Texture setting.
            HDXTK12_EXPORT void __cdecl SetTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);

            // Animation settings.
            HDXTK12_EXPORT void __cdecl SetBoneTransforms(_In_reads_(count) XMMATRIX const* value, size_t count) override;
            HDXTK12_EXPORT void __cdecl ResetBoneTransforms() override;

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };


        //------------------------------------------------------------------------------
        // Built-in shader extends BasicEffect with normal map and optional specular map
        class NormalMapEffect : public IEffect, public IEffectMatrices, public IEffectLights, public IEffectFog
        {
        public:
            NormalMapEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription) :
                NormalMapEffect(device, effectFlags, pipelineDescription, false)
            {
            }

            HDXTK12_EXPORT NormalMapEffect(NormalMapEffect&&) noexcept;
            HDXTK12_EXPORT NormalMapEffect& operator= (NormalMapEffect&&) noexcept;

            NormalMapEffect(NormalMapEffect const&) = delete;
            NormalMapEffect& operator= (NormalMapEffect const&) = delete;

            HDXTK12_EXPORT ~NormalMapEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Material settings.
            HDXTK12_EXPORT void XM_CALLCONV SetDiffuseColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetEmissiveColor(FXMVECTOR value);
            HDXTK12_EXPORT void XM_CALLCONV SetSpecularColor(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetSpecularPower(float value);
            HDXTK12_EXPORT void __cdecl DisableSpecular();
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetColorAndAlpha(FXMVECTOR value);

            // Light settings.
            HDXTK12_EXPORT void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl SetLightEnabled(int whichLight, bool value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl EnableDefaultLighting() override;

            // Fog settings.
            HDXTK12_EXPORT void __cdecl SetFogStart(float value) override;
            HDXTK12_EXPORT void __cdecl SetFogEnd(float value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetFogColor(FXMVECTOR value) override;

            // Texture setting - albedo, normal and specular intensity
            HDXTK12_EXPORT void __cdecl SetTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);
            HDXTK12_EXPORT void __cdecl SetNormalTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor);
            HDXTK12_EXPORT void __cdecl SetSpecularTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor);

        protected:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;

            HDXTK12_EXPORT NormalMapEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription, bool skinningEnabled);
        };

        class SkinnedNormalMapEffect : public NormalMapEffect, public IEffectSkinning
        {
        public:
            SkinnedNormalMapEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription) :
                NormalMapEffect(device, effectFlags, pipelineDescription, true)
            {
            }

            SkinnedNormalMapEffect(SkinnedNormalMapEffect&&) = default;
            SkinnedNormalMapEffect& operator= (SkinnedNormalMapEffect&&) = default;

            SkinnedNormalMapEffect(SkinnedNormalMapEffect const&) = delete;
            SkinnedNormalMapEffect& operator= (SkinnedNormalMapEffect const&) = delete;

            HDXTK12_EXPORT ~SkinnedNormalMapEffect() override;

            // Animation settings.
            HDXTK12_EXPORT void __cdecl SetBoneTransforms(_In_reads_(count) XMMATRIX const* value, size_t count) override;
            HDXTK12_EXPORT void __cdecl ResetBoneTransforms() override;
        };


        //------------------------------------------------------------------------------
        // Built-in shader for Physically-Based Rendering (Roughness/Metalness) with Image-based lighting
        class PBREffect : public IEffect, public IEffectMatrices, public IEffectLights
        {
        public:
            PBREffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription) :
                PBREffect(device, effectFlags, pipelineDescription, false)
            {
            }

            HDXTK12_EXPORT PBREffect(PBREffect&&) noexcept;
            HDXTK12_EXPORT PBREffect& operator= (PBREffect&&) noexcept;

            PBREffect(PBREffect const&) = delete;
            PBREffect& operator= (PBREffect const&) = delete;

            HDXTK12_EXPORT ~PBREffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Light settings.
            HDXTK12_EXPORT void __cdecl SetLightEnabled(int whichLight, bool value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDirection(int whichLight, FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightDiffuseColor(int whichLight, FXMVECTOR value) override;

            HDXTK12_EXPORT void __cdecl EnableDefaultLighting() override;

            // PBR Settings.
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);
            HDXTK12_EXPORT void XM_CALLCONV SetConstantAlbedo(FXMVECTOR value);
            HDXTK12_EXPORT void __cdecl SetConstantMetallic(float value);
            HDXTK12_EXPORT void __cdecl SetConstantRoughness(float value);

            // Texture settings.
            HDXTK12_EXPORT void __cdecl SetAlbedoTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE samplerDescriptor);
            HDXTK12_EXPORT void __cdecl SetNormalTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor);
            HDXTK12_EXPORT void __cdecl SetRMATexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor);

            HDXTK12_EXPORT void __cdecl SetEmissiveTexture(D3D12_GPU_DESCRIPTOR_HANDLE srvDescriptor);

            HDXTK12_EXPORT void __cdecl SetSurfaceTextures(
                D3D12_GPU_DESCRIPTOR_HANDLE albedo,
                D3D12_GPU_DESCRIPTOR_HANDLE normal,
                D3D12_GPU_DESCRIPTOR_HANDLE roughnessMetallicAmbientOcclusion,
                D3D12_GPU_DESCRIPTOR_HANDLE sampler);

            HDXTK12_EXPORT void __cdecl SetIBLTextures(
                D3D12_GPU_DESCRIPTOR_HANDLE radiance,
                int numRadianceMips,
                D3D12_GPU_DESCRIPTOR_HANDLE irradiance,
                D3D12_GPU_DESCRIPTOR_HANDLE sampler);

            // Render target size, required for velocity buffer output.
            HDXTK12_EXPORT void __cdecl SetRenderTargetSizeInPixels(int width, int height);

        protected:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;

            HDXTK12_EXPORT PBREffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription, bool skinningEnabled);

            // Unsupported interface methods.
            HDXTK12_EXPORT void XM_CALLCONV SetAmbientLightColor(FXMVECTOR value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetLightSpecularColor(int whichLight, FXMVECTOR value) override;
        };

        class SkinnedPBREffect : public PBREffect, public IEffectSkinning
        {
        public:
            SkinnedPBREffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription) :
                PBREffect(device, effectFlags, pipelineDescription, true)
            {
            }

            HDXTK12_EXPORT SkinnedPBREffect(SkinnedPBREffect&&) = default;
            HDXTK12_EXPORT SkinnedPBREffect& operator= (SkinnedPBREffect&&) = default;

            SkinnedPBREffect(SkinnedPBREffect const&) = delete;
            SkinnedPBREffect& operator= (SkinnedPBREffect const&) = delete;

            HDXTK12_EXPORT ~SkinnedPBREffect() override;

            // Animation settings.
            HDXTK12_EXPORT void __cdecl SetBoneTransforms(_In_reads_(count) XMMATRIX const* value, size_t count) override;
            HDXTK12_EXPORT void __cdecl ResetBoneTransforms() override;
        };


        //------------------------------------------------------------------------------
        // Built-in shader for debug visualization of normals, tangents, etc.
        class DebugEffect : public IEffect, public IEffectMatrices
        {
        public:
            enum Mode : uint32_t
            {
                Mode_Default = 0,   // Hemispherical ambient lighting
                Mode_Normals,       // RGB normals
                Mode_Tangents,      // RGB tangents
                Mode_BiTangents,    // RGB bi-tangents
            };

            HDXTK12_EXPORT DebugEffect(_In_ ID3D12Device* device, uint32_t effectFlags,
                const EffectPipelineStateDescription& pipelineDescription,
                Mode debugMode = Mode_Default);

            HDXTK12_EXPORT DebugEffect(DebugEffect&&) noexcept;
            HDXTK12_EXPORT DebugEffect& operator= (DebugEffect&&) noexcept;

            DebugEffect(DebugEffect const&) = delete;
            DebugEffect& operator= (DebugEffect const&) = delete;

            HDXTK12_EXPORT ~DebugEffect() override;

            // IEffect methods.
            HDXTK12_EXPORT void __cdecl Apply(_In_ ID3D12GraphicsCommandList* commandList) override;

            // Camera settings.
            HDXTK12_EXPORT void XM_CALLCONV SetWorld(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetView(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetProjection(FXMMATRIX value) override;
            HDXTK12_EXPORT void XM_CALLCONV SetMatrices(FXMMATRIX world, CXMMATRIX view, CXMMATRIX projection) override;

            // Debug Settings.
            HDXTK12_EXPORT void XM_CALLCONV SetHemisphericalAmbientColor(FXMVECTOR upper, FXMVECTOR lower);
            HDXTK12_EXPORT void __cdecl SetAlpha(float value);

        private:
            // Private implementation.
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };


        //------------------------------------------------------------------------------
        // Abstract interface to factory texture resources
        class IEffectTextureFactory
        {
        public:
            virtual ~IEffectTextureFactory() = default;

            IEffectTextureFactory(const IEffectTextureFactory&) = delete;
            IEffectTextureFactory& operator=(const IEffectTextureFactory&) = delete;

            virtual size_t __cdecl CreateTexture(_In_z_ const wchar_t* name, int descriptorIndex) = 0;

        protected:
            IEffectTextureFactory() = default;
            IEffectTextureFactory(IEffectTextureFactory&&) = default;
            IEffectTextureFactory& operator=(IEffectTextureFactory&&) = default;
        };


        // Factory for sharing texture resources
        class EffectTextureFactory : public IEffectTextureFactory
        {
        public:
            HDXTK12_EXPORT EffectTextureFactory(
                _In_ ID3D12Device* device,
                ResourceUploadBatch& resourceUploadBatch,
                _In_ ID3D12DescriptorHeap* descriptorHeap) noexcept(false);

            HDXTK12_EXPORT EffectTextureFactory(
                _In_ ID3D12Device* device,
                ResourceUploadBatch& resourceUploadBatch,
                _In_ size_t numDescriptors,
                _In_ D3D12_DESCRIPTOR_HEAP_FLAGS descriptorHeapFlags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE) noexcept(false);

            HDXTK12_EXPORT EffectTextureFactory(EffectTextureFactory&&) noexcept;
            HDXTK12_EXPORT EffectTextureFactory& operator= (EffectTextureFactory&&) noexcept;

            EffectTextureFactory(EffectTextureFactory const&) = delete;
            EffectTextureFactory& operator= (EffectTextureFactory const&) = delete;

            HDXTK12_EXPORT ~EffectTextureFactory() override;

            HDXTK12_EXPORT size_t __cdecl CreateTexture(_In_z_ const wchar_t* name, int descriptorIndex) override;

            HDXTK12_EXPORT ID3D12DescriptorHeap* __cdecl Heap() const noexcept;

            // Shorthand accessors for the descriptor heap
            HDXTK12_EXPORT D3D12_CPU_DESCRIPTOR_HANDLE __cdecl GetCpuDescriptorHandle(size_t index) const;
            HDXTK12_EXPORT D3D12_GPU_DESCRIPTOR_HANDLE __cdecl GetGpuDescriptorHandle(size_t index) const;

            // How many textures are there in this factory?
            HDXTK12_EXPORT size_t __cdecl ResourceCount() const noexcept;

            // Get a resource in a specific slot (note: increases reference count on resource)
            HDXTK12_EXPORT void __cdecl GetResource(size_t slot, _Out_ ID3D12Resource** resource, _Out_opt_ bool* isCubeMap = nullptr);

            // Settings.
            HDXTK12_EXPORT void __cdecl ReleaseCache();

            HDXTK12_EXPORT void __cdecl SetSharing(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnableForceSRGB(bool forceSRGB) noexcept;
            HDXTK12_EXPORT void __cdecl EnableAutoGenMips(bool generateMips) noexcept;

            HDXTK12_EXPORT void __cdecl SetDirectory(_In_opt_z_ const wchar_t* path) noexcept;

        private:
            // Private implementation
            class Impl;

            std::unique_ptr<Impl> pImpl;
        };


        //------------------------------------------------------------------------------
        // Abstract interface to factory for sharing effects
        class IEffectFactory
        {
        public:
            HDXTK12_EXPORT virtual ~IEffectFactory() = default;

            IEffectFactory(const IEffectFactory&) = delete;
            IEffectFactory& operator=(const IEffectFactory&) = delete;

            struct EffectInfo
            {
                std::wstring        name;
                bool                perVertexColor;
                bool                enableSkinning;
                bool                enableDualTexture;
                bool                enableNormalMaps;
                bool                biasedVertexNormals;
                float               specularPower;
                float               alphaValue;
                XMFLOAT3            ambientColor;
                XMFLOAT3            diffuseColor;
                XMFLOAT3            specularColor;
                XMFLOAT3            emissiveColor;
                int                 diffuseTextureIndex;
                int                 specularTextureIndex;
                int                 normalTextureIndex;
                int                 emissiveTextureIndex;
                int                 samplerIndex;
                int                 samplerIndex2;

                EffectInfo() noexcept
                    : perVertexColor(false)
                    , enableSkinning(false)
                    , enableDualTexture(false)
                    , enableNormalMaps(false)
                    , biasedVertexNormals(false)
                    , specularPower(0)
                    , alphaValue(0)
                    , ambientColor(0, 0, 0)
                    , diffuseColor(0, 0, 0)
                    , specularColor(0, 0, 0)
                    , emissiveColor(0, 0, 0)
                    , diffuseTextureIndex(-1)
                    , specularTextureIndex(-1)
                    , normalTextureIndex(-1)
                    , emissiveTextureIndex(-1)
                    , samplerIndex(-1)
                    , samplerIndex2(-1)
                {
                }
            };

            virtual std::shared_ptr<IEffect> __cdecl CreateEffect(
                const EffectInfo& info,
                const EffectPipelineStateDescription& opaquePipelineState,
                const EffectPipelineStateDescription& alphaPipelineState,
                const D3D12_INPUT_LAYOUT_DESC& inputLayout,
                int textureDescriptorOffset = 0,
                int samplerDescriptorOffset = 0) = 0;

        protected:
            IEffectFactory() = default;
            IEffectFactory(IEffectFactory&&) = default;
            IEffectFactory& operator=(IEffectFactory&&) = default;
        };


        // Factory for sharing effects
        class EffectFactory : public IEffectFactory
        {
        public:
            HDXTK12_EXPORT EffectFactory(_In_ ID3D12Device* device);
            HDXTK12_EXPORT EffectFactory(
                _In_ ID3D12DescriptorHeap* textureDescriptors,
                _In_ ID3D12DescriptorHeap* samplerDescriptors);

            HDXTK12_EXPORT EffectFactory(EffectFactory&&) noexcept;
            HDXTK12_EXPORT EffectFactory& operator= (EffectFactory&&) noexcept;

            EffectFactory(EffectFactory const&) = delete;
            EffectFactory& operator= (EffectFactory const&) = delete;

            HDXTK12_EXPORT ~EffectFactory() override;

            // IEffectFactory methods.
            HDXTK12_EXPORT virtual std::shared_ptr<IEffect> __cdecl CreateEffect(
                const EffectInfo& info,
                const EffectPipelineStateDescription& opaquePipelineState,
                const EffectPipelineStateDescription& alphaPipelineState,
                const D3D12_INPUT_LAYOUT_DESC& inputLayout,
                int textureDescriptorOffset = 0,
                int samplerDescriptorOffset = 0) override;

            // Settings.
            HDXTK12_EXPORT void __cdecl ReleaseCache();

            HDXTK12_EXPORT void __cdecl SetSharing(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnableLighting(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnablePerPixelLighting(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnableNormalMapEffect(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnableFogging(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnableInstancing(bool enabled) noexcept;

        private:
            // Private implementation.
            class Impl;

            std::shared_ptr<Impl> pImpl;
        };


        // Factory for Physically Based Rendering (PBR)
        class PBREffectFactory : public IEffectFactory
        {
        public:
            HDXTK12_EXPORT PBREffectFactory(_In_ ID3D12Device* device) noexcept(false);
            HDXTK12_EXPORT PBREffectFactory(
                _In_ ID3D12DescriptorHeap* textureDescriptors,
                _In_ ID3D12DescriptorHeap* samplerDescriptors) noexcept(false);

            HDXTK12_EXPORT PBREffectFactory(PBREffectFactory&&) noexcept;
            HDXTK12_EXPORT PBREffectFactory& operator= (PBREffectFactory&&) noexcept;

            PBREffectFactory(PBREffectFactory const&) = delete;
            PBREffectFactory& operator= (PBREffectFactory const&) = delete;

            ~PBREffectFactory() override;

            // IEffectFactory methods.
            HDXTK12_EXPORT virtual std::shared_ptr<IEffect> __cdecl CreateEffect(
                const EffectInfo& info,
                const EffectPipelineStateDescription& opaquePipelineState,
                const EffectPipelineStateDescription& alphaPipelineState,
                const D3D12_INPUT_LAYOUT_DESC& inputLayout,
                int textureDescriptorOffset = 0,
                int samplerDescriptorOffset = 0) override;

            // Settings.
            HDXTK12_EXPORT void __cdecl ReleaseCache();

            HDXTK12_EXPORT void __cdecl SetSharing(bool enabled) noexcept;

            HDXTK12_EXPORT void __cdecl EnableInstancing(bool enabled) noexcept;

        private:
            // Private implementation.
            class Impl;

            std::shared_ptr<Impl> pImpl;
        };
    }
}

#endif // __DIRECTXTK_EFFECTS_H__
