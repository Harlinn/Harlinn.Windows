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
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_UTIL_MIPMAP_H
#define PBRT_UTIL_MIPMAP_H

#include <pbrto/pbrt.h>

#include <pbrto/util/image.h>
#include <pbrto/util/pstd.h>
#include <pbrto/util/vecmath.h>

#include <memory>
#include <string>
#include <vector>

namespace pbrt {

// FilterFunction Definition
enum class FilterFunction { Point, Bilinear, Trilinear, EWA };

inline pstd::optional<FilterFunction> ParseFilter(const std::string &f) {
    if (f == "ewa" || f == "EWA")
        return FilterFunction::EWA;
    else if (f == "trilinear")
        return FilterFunction::Trilinear;
    else if (f == "bilinear")
        return FilterFunction::Bilinear;
    else if (f == "point")
        return FilterFunction::Point;
    else
        return {};
}

std::string ToString(FilterFunction f);

// MIPMapFilterOptions Definition
struct MIPMapFilterOptions {
    FilterFunction filter = FilterFunction::EWA;
    Float maxAnisotropy = 8.f;
    bool operator<(MIPMapFilterOptions o) const {
        return std::tie(filter, maxAnisotropy) < std::tie(o.filter, o.maxAnisotropy);
    }
    std::string ToString() const;
};

// MIPMap Definition
class MIPMap {
  public:
    // MIPMap Public Methods
    MIPMap(Image image, const RGBColorSpace *colorSpace, WrapMode wrapMode,
           Allocator alloc, const MIPMapFilterOptions &options);
    static MIPMap *CreateFromFile(const std::string &filename,
                                  const MIPMapFilterOptions &options, WrapMode wrapMode,
                                  ColorEncoding encoding, Allocator alloc);

    template <typename T>
    T Filter(Point2f st, Vector2f dstdx, Vector2f dstdy) const;

    std::string ToString() const;

    Point2i LevelResolution(int level) const {
        CHECK(level >= 0 && level < pyramid.size());
        return pyramid[level].Resolution();
    }
    int Levels() const { return int(pyramid.size()); }
    const RGBColorSpace *GetRGBColorSpace() const { return colorSpace; }
    const Image &GetLevel(int level) const { return pyramid[level]; }

  private:
    // MIPMap Private Methods
    template <typename T>
    T Texel(int level, Point2i st) const;
    template <typename T>
    T Bilerp(int level, Point2f st) const;
    template <typename T>
    T EWA(int level, Point2f st, Vector2f dst0, Vector2f dst1) const;

    // MIPMap Private Members
    pstd::vector<Image> pyramid;
    const RGBColorSpace *colorSpace;
    WrapMode wrapMode;
    MIPMapFilterOptions options;
};

}  // namespace pbrt

#endif  // PBRT_UTIL_MIPMAP_H
