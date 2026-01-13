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
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard
//

#pragma once

#include "HDMMModel.h"
#include "HDMMAnimation.h"
#include "HDMMConstantBuffers.h"
#include "Math/HDMCBoundingSphere.h"
#include "Math/HDMCBoundingBox.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    namespace glTF { class Asset; struct Mesh; }

#define CURRENT_MINI_FILE_VERSION 13

    namespace Renderer
    {
        using namespace Math;

        // Unaligned mirror of MaterialConstants
        struct MaterialConstantData
        {
            float baseColorFactor[ 4 ]; // default=[1,1,1,1]
            float emissiveFactor[ 3 ]; // default=[0,0,0]
            float normalTextureScale; // default=1
            float metallicFactor; // default=1
            float roughnessFactor; // default=1
            uint32_t flags;
        };

        // Used at load time to construct descriptor tables
        struct MaterialTextureData
        {
            uint16_t stringIdx[ kNumTextures ];
            uint32_t addressModes;
        };

        // All of the information that needs to be written to a .mini data file
        struct ModelData
        {
            BoundingSphere m_BoundingSphere;
            AxisAlignedBox m_BoundingBox;
            std::vector<Byte> m_GeometryData;
            std::vector<Byte> m_AnimationKeyFrameData;
            std::vector<AnimationCurve> m_AnimationCurves;
            std::vector<AnimationSet> m_Animations;
            std::vector<uint16_t> m_JointIndices;
            std::vector<Matrix4> m_JointIBMs;
            std::vector<MaterialTextureData> m_MaterialTextures;
            std::vector<MaterialConstantData> m_MaterialConstants;
            std::vector<Mesh*> m_Meshes;
            std::vector<GraphNode> m_SceneGraph;
            std::vector<std::string> m_TextureNames;
            std::vector<uint8_t> m_TextureOptions;
        };

        struct FileHeader
        {
            char     id[ 4 ];   // "MINI"
            uint32_t version; // CURRENT_MINI_FILE_VERSION
            uint32_t numNodes;
            uint32_t numMeshes;
            uint32_t numMaterials;
            uint32_t meshDataSize;
            uint32_t numTextures;
            uint32_t stringTableSize;
            uint32_t geometrySize;
            uint32_t keyFrameDataSize;      // Animation data
            uint32_t numAnimationCurves;
            uint32_t numAnimations;
            uint32_t numJoints;     // All joints for all skins
            float    boundingSphere[ 4 ];
            float    minPos[ 3 ];
            float    maxPos[ 3 ];
        };

        void CompileMesh(
            std::vector<Mesh*>& meshList,
            std::vector<Byte>& bufferMemory,
            glTF::Mesh& srcMesh,
            uint32_t matrixIdx,
            const Matrix4& localToObject,
            Math::BoundingSphere& boundingSphere,
            Math::AxisAlignedBox& boundingBox
        );

        HDMM_EXPORT bool BuildModel( ModelData& model, const glTF::Asset& asset, int sceneIdx = -1 );
        HDMM_EXPORT bool SaveModel( const std::wstring& filePath, const ModelData& model );

        HDMM_EXPORT std::shared_ptr<Model> LoadModel( const std::wstring& filePath, bool forceRebuild = false );
    }
}