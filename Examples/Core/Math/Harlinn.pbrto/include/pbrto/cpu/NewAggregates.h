#pragma once
#ifndef PBRTO_CPU_NEWAGGREGATES_H_
#define PBRTO_CPU_NEWAGGREGATES_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/cpu/NewPrimitive.h>
#include <pbrto/util/NewParallel.h>

#include <atomic>
#include <memory>
#include <vector>

namespace pbrto
{

    Primitive CreateAccelerator( const std::string& name, std::vector<Primitive> prims, const ParameterDictionary& parameters );

    struct BVHBuildNode;
    struct BVHPrimitive;
    struct LinearBVHNode;
    struct MortonPrimitive;

    // BVHAggregate Definition
    class BVHAggregate
    {
    public:
        // BVHAggregate Public Types
        enum class SplitMethod
        {
            SAH,
            HLBVH,
            Middle,
            EqualCounts
        };
    private:
        // BVHAggregate Private Members
        int maxPrimsInNode;
        std::vector<Primitive> primitives;
        SplitMethod splitMethod;
        LinearBVHNode* nodes = nullptr;
    public:
        // BVHAggregate Public Methods
        PBRTO_EXPORT
            BVHAggregate( std::vector<Primitive> p, int maxPrimsInNode = 1, SplitMethod splitMethod = SplitMethod::SAH );

        PBRTO_EXPORT
            static BVHAggregate* Create( std::vector<Primitive> prims, const ParameterDictionary& parameters );

        PBRTO_EXPORT
            Bounds3f Bounds( ) const;

        PBRTO_EXPORT
            pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax ) const;

        PBRTO_EXPORT
            bool IntersectP( const Ray& ray, Float tMax ) const;

    private:
        // BVHAggregate Private Methods
        BVHBuildNode* buildRecursive( ThreadLocal<Allocator>& threadAllocators, pstdo::span<BVHPrimitive> bvhPrimitives, std::atomic<int>* totalNodes, std::atomic<int>* orderedPrimsOffset, std::vector<Primitive>& orderedPrims );
        BVHBuildNode* buildHLBVH( Allocator alloc, const std::vector<BVHPrimitive>& primitiveInfo, std::atomic<int>* totalNodes, std::vector<Primitive>& orderedPrims );
        BVHBuildNode* emitLBVH( BVHBuildNode*& buildNodes, const std::vector<BVHPrimitive>& primitiveInfo, MortonPrimitive* mortonPrims, int nPrimitives, int* totalNodes, std::vector<Primitive>& orderedPrims, std::atomic<int>* orderedPrimsOffset, int bitIndex );
        BVHBuildNode* buildUpperSAH( Allocator alloc, std::vector<BVHBuildNode*>& treeletRoots, int start, int end, std::atomic<int>* totalNodes ) const;
        int flattenBVH( BVHBuildNode* node, int* offset );
    };

    struct KdTreeNode;
    struct BoundEdge;

    // KdTreeAggregate Definition
    class KdTreeAggregate
    {
        // KdTreeAggregate Private Members
        int isectCost;
        int traversalCost;
        int maxPrims;
        Float emptyBonus;
        std::vector<Primitive> primitives;
        std::vector<int> primitiveIndices;
        KdTreeNode* nodes;
        int nAllocedNodes;
        int nextFreeNode;
        Bounds3f bounds;
    public:
        // KdTreeAggregate Public Methods
        PBRTO_EXPORT
            KdTreeAggregate( std::vector<Primitive> p, int isectCost = 5, int traversalCost = 1, Float emptyBonus = 0.5, int maxPrims = 1, int maxDepth = -1 );

        PBRTO_EXPORT
            static KdTreeAggregate* Create( std::vector<Primitive> prims, const ParameterDictionary& parameters );

        PBRTO_EXPORT
            pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax ) const;

        PBRTO_EXPORT
#ifdef PBRT_USES_HCCMATH
            const Bounds3f& Bounds( ) const
#else
            Bounds3f Bounds( ) const
#endif
        {
            return bounds;
        }

        PBRTO_EXPORT bool IntersectP( const Ray& ray, Float tMax ) const;

    private:
        // KdTreeAggregate Private Methods
        void buildTree( int nodeNum, const Bounds3f& bounds, const std::vector<Bounds3f>& primBounds, pstdo::span<const int> primNums, int depth, std::vector<BoundEdge> edges[ 3 ], pstdo::span<int> prims0, pstdo::span<int> prims1, int badRefines );


    };

}


#endif
