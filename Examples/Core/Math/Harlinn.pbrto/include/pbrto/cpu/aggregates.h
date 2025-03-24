// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_CPU_AGGREGATES_H
#define PBRT_CPU_AGGREGATES_H

#include <pbrto/pbrt.h>

#include <pbrto/cpu/primitive.h>
#include <pbrto/util/parallel.h>

#include <atomic>
#include <memory>
#include <vector>

namespace pbrt
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
        pstd::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax ) const;

        PBRTO_EXPORT 
        bool IntersectP( const Ray& ray, Float tMax ) const;

    private:
        // BVHAggregate Private Methods
        BVHBuildNode* buildRecursive( ThreadLocal<Allocator>& threadAllocators, pstd::span<BVHPrimitive> bvhPrimitives, std::atomic<int>* totalNodes, std::atomic<int>* orderedPrimsOffset, std::vector<Primitive>& orderedPrims );
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
        pstd::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax ) const;

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
        void buildTree( int nodeNum, const Bounds3f& bounds, const std::vector<Bounds3f>& primBounds, pstd::span<const int> primNums, int depth, std::vector<BoundEdge> edges[ 3 ], pstd::span<int> prims0, pstd::span<int> prims1, int badRefines );

        
    };

}  // namespace pbrt

#endif  // PBRT_CPU_AGGREGATES_H
