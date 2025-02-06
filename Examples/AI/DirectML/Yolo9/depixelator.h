/*
    Copyright (c) 2019, reMarkable AS <technology@remarkable.no>
    Copyright (c) 2019, Gunnar Sletta <gunnar@crimson.no>
    All rights reserved.


    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
       contributors may be used to endorse or promote products derived from
       this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <assert.h>
#include <vector>
#include <unordered_map>
#include <cmath>

#define uint uint32_t

namespace depixelator {

struct Point
{
    float x;
    float y;

    Point(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) { }
};

struct IntPoint
{
    int x;
    int y;

    IntPoint(int x_ = 0, int y_ = 0) : x(x_), y(y_) { }
};

struct Bitmap
{
    unsigned char *data = nullptr;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int stride = 0;

    //
    // Returns true if the bitmap is valid...
    //
    bool isValid() const;

    //
    // Returns true if the bit at x, y is set.
    // Will assert on invalid values of x and y.
    //
    bool checkBit(int x, int y) const;
};

using Polyline = std::vector<Point>;
using Polylines = std::vector<Polyline>;

/*
 * Runs a Marching Squares algorithm over the bitmap and forms polylines out of the result.
 *
 * The polylines are merged into closed polylines.
 */
Polylines findContours(const Bitmap &bitmap);

/*
 * Runs over the given polyline and returns a visually identical copy, but with superfluous
 * points removed.
 */
Polyline simplify(const Polyline &polyline, float threshold);
Polylines simplify(const Polylines &lines, float threshold);

/*
 * Performs a Ramer-Douglas-Peuker end-point fit algorithm.
 */
Polyline simplifyRDP(const Polyline &polyline, float epsilon);
Polylines simplifyRDP(const Polylines &lines, float epsilon);

/*
 * Trace pixel-wise slopes in the lines and recreates the desired slopes
 */
Polyline traceSlopes(const Polyline &polyline);
Polylines traceSlopes(const Polylines &polyline);


/*
 * Runs over the points and nudges them to form a slightly less ragged polyline..
 */
Polyline smoothen(const Polyline &polyline, float factor);
Polyline smoothen(const Polyline &polyline, float factor, int iterations);
Polylines smoothen(const Polylines &lines, float factor, int iterations);

/*
 * Turn tne polyline into a continuous cubic bezier path.
 *

 * First point is to be considered the 'MoveTo' element, following it will be
 * groups of three and three points, where each group of three should be
 * interpreted like this:
 *  - 0: control point 1
 *  - 1: control point 2
 *  - 2: end point
 */
Polyline convertToCubicPath(const Polyline &polyline);
Polylines convertToCubicPaths(const Polylines &lines);

} // end of namespace

namespace std
{
    template<> struct hash<depixelator::IntPoint> {
        int operator()(const depixelator::IntPoint &p) const { return (p.x << 4) + p.y; }
    };
    template<> struct equal_to<depixelator::IntPoint> {
        bool operator()(const depixelator::IntPoint &a, const depixelator::IntPoint &b) const { return a.x == b.x && a.y == b.y; }
    };
}

namespace depixelator {

//
// ****************************** Implementation ******************************
//

inline bool Bitmap::isValid() const
{
    return data != nullptr
           && width > 0
           && height > 0
           && stride > 0;
}

inline bool Bitmap::checkBit(int x, int y) const
{
    assert(isValid());
    if (x < 0 || y < 0  || x >= (int) width || y >= (int) height) {
        return false;
    }
   // return (data[uint(y) * stride + uint(x >> 3)] & (1<<(x&7))) != 0;
    return (data[uint(y) * stride + x]  != 0);
}

inline Polylines findContours(const Bitmap &bitmap)
{
    if (!bitmap.isValid()) {
        return {};
    }

    int xsteps = int(bitmap.width - 1);
    int ysteps = int(bitmap.height - 1);

    const unsigned int lineCount[16] = {
        0, 1, 1, 1,
        1, 2, 1, 1,
        1, 1, 2, 1,
        1, 1, 1, 0
    };

    // We want absolute equallity between points, so we're using integers * 10...
    const int precision = 10;
    const int a = precision / 2;    // 0.5
    const int b = precision;        // 1.0
    const int c = a + b;            // 1.5

    const int lines[][16] = {
        /* 0x0 */   { },
        /* 0x1 */   { b, a,   a, b },
        /* 0xb */   { c, b,   b, a },
        /* 0xc */   { c, b,   a, b },

        /* 0x4 */   { b, c,   c, b },
        /* 0x5 */   { b, a,   c, b,     b, c, a, b },
        /* 0x6 */   { b, c,   b, a },
        /* 0x7 */   { b, c,   a, b },

        /* 0x8 */   { a, b,   b, c },
        /* 0x9 */   { b, a,   b, c },
        /* 0xa */   { a, b,   b, a,     c, b, b, c },
        /* 0xb */   { c, b,   b, c },
        /* 0xc */   { a, b,   c, b },
        /* 0xd */   { b, a,   c, b },
        /* 0xe */   { a, b,   b, a },
        /* 0xf */   { }
    };

    // The algorithm guarantees a single line segment per point value, so
    // using a map is perfectly fine and helps us below, so we do that.
    std::unordered_map<IntPoint, IntPoint> segments;
    segments.reserve(size_t((xsteps * ysteps) / 3));

    for (int y=-1; y<=ysteps; ++y) {
        for (int x=-1; x<=xsteps; ++x) {
            unsigned int mask = ((unsigned int) bitmap.checkBit(x  , y  ) << 0)
                              | ((unsigned int) bitmap.checkBit(x+1, y  ) << 1)
                              | ((unsigned int) bitmap.checkBit(x+1, y+1) << 2)
                              | ((unsigned int) bitmap.checkBit(x  , y+1) << 3);


            for (unsigned char i=0; i<lineCount[mask]; ++i) {
                const int *l = lines[mask] + i * 4;
                int xp = x * precision;
                int yp = y * precision;
                segments[IntPoint(xp+l[0], yp+l[1])] = IntPoint(xp+l[2], yp+l[3]);
            }

        }
    }

    // Here endeth the marching square algorithm. At this point, we have all
    // line segments stored in 'segments' and we will traverse the unordered map
    // merging them into polylines until the map is empty.
    //
    // Since we went outside the bitmap, where the bit is guaranteed to be
    // unset, the segments are guaranteed to form closed polylines and as a
    // result we can form the polylines by starting on any given segment and
    // just following the line, segment by segment, until we're back where we
    // started. We remove each segment as we traverse it, so when we reach the
    // beginning we'll get fail to find another match for our point and the
    // poly line is complete.
    //
    // Then onto the next one, etc..

    const float invprec = 1.0f / precision;

    Polylines polylines;
    Polyline polyline;
    polyline.reserve(256);

    while (segments.size()) {

        auto it = segments.begin();
        IntPoint pa = it->first;
        IntPoint pb = it->second;
        polyline.push_back(Point(float(pa.x) * invprec, float(pa.y) * invprec));
        polyline.push_back(Point(float(pb.x) * invprec, float(pb.y) * invprec));
        segments.erase(it);
        it = segments.find(pb);

        // append to the end of the line
        while (it != segments.end()) {
            pb = it->second;
            polyline.push_back(Point(float(pb.x) * invprec, float(pb.y) * invprec));
            segments.erase(it);
            it = segments.find(pb);
        }
        polylines.push_back(polyline);
        polyline.clear();
    }
    return polylines;
}

inline Polyline simplify(const Polyline &polyline, float threshold)
{
    if (polyline.size() < 2) {
        return polyline;
    }

    Polyline result;
    result.reserve(polyline.size() / 10);

    auto it = polyline.begin();
    float lx = it->x;
    float ly = it->y;
    float ldx = 0;
    float ldy = 0;

    result.push_back(*it);
    ++it;

    while (it != polyline.end()) {
        float dx = it->x - lx;
        float dy = it->y - ly;

        if (dy != 0 && ldy != 0) {
            // If there is a non-trivial difference in slope, add the point..
            float ls = ldx / ldy;
            float s = dx / dy;
            if (std::abs(ls - s) > threshold) {
                result.push_back(*it);
            } else {
                result.back() = *it;
            }

        } else if (ldy == 0 && dy == 0) {
            // line is horizontal, add if direction is opposite, though given
            // where the lines are coming from this situation will never arise
            // in practice, so this is more for algorithmic integrity.. We could
            // technically skip it..
            if (ldx * dx < 0) {
               result.push_back(*it);
            } else {
                result.back() = *it;
            }

        } else {
            // There are differences, add the point..
            result.push_back(*it);
        }

        lx = it->x;
        ly = it->y;
        ldx = dx;
        ldy = dy;

        ++it;
    }

    if (result.front().x != result.back().x
        || result.front().y != result.back().y) {
        result.push_back(result.front());
    }

    return result;
}

inline Polyline simplifyRDP(const Polyline &polyline, float epsilon)
{
    assert(epsilon >= 0.0f);

    if (polyline.size() < 3) {
        return polyline;
    }

    std::vector<IntPoint> range;
    range.push_back(IntPoint(0, static_cast<int>(polyline.size()) - 1));

    Polyline result;
    result.reserve(polyline.size() / 10);
    result.push_back(polyline.front());

    while (range.size() > 0) {
        const int i0 = range.back().x;
        const int i1 = range.back().y;
        range.pop_back();

        float maxDist = 0;
        int imax = -1;
        Point p0 = polyline[size_t(i0)];
        Point p1 = polyline[size_t(i1)];
        float sdx = p1.x - p0.x;
        float sdy = p1.y - p0.y;
        float sc = p1.x * p0.y - p1.y * p0.x;
        float slen = std::sqrt(sdx * sdx + sdy * sdy);

        for (int i=i0+1; i<i1-1; ++i) {
            Point pt = polyline[size_t(i)];
            float dist;
            if (slen == 0) {
                float dx = pt.x - p0.x;
                float dy = pt.y - p0.y;
                dist = std::sqrt(dx * dx + dy * dy);
            } else {
                dist = std::abs(sdy * pt.x - sdx * pt.y + sc) / slen;
            }
            if (dist > maxDist) {
                imax = i;
                maxDist = dist;
            }
        }

        if (maxDist > epsilon) {
            range.push_back(IntPoint(i0, imax));
            range.push_back(IntPoint(imax, i1));
        } else {
            result.push_back(p1);
        }
    }

    return result;
}

inline Polyline smoothen(const Polyline &polyline, float factor)
{
    if (polyline.size() < 4) {
        return polyline;
    }

    Polyline result;
    result.reserve(polyline.size());

    for (unsigned int i=0; i<polyline.size(); ++i) {
        Point cur = polyline[i];
        Point last = i == 0 ? polyline[polyline.size() - 2] : polyline[i-1];
        Point next = i == polyline.size() - 1 ? polyline[1] : polyline[i+1];

        float ax = cur.x - last.x;
        float ay = cur.y - last.y;
        float bx = next.x - cur.x;
        float by = next.y - cur.y;
        float lena = std::sqrt(ax * ax + ay * ay);
        float lenb = std::sqrt(bx * bx + by * by);

        float t = lena / (lena + lenb);
        float it = 1.0f - t;

        float px = it * it * last.x + 2 * it * t * cur.x + t * t * next.x;
        float py = it * it * last.y + 2 * it * t * cur.y + t * t * next.y;

        float ifactor = 1.0f - factor;

        result.push_back(Point(px * factor + cur.x * ifactor,
                               py * factor + cur.y * ifactor));
    }

    if (result.front().x != result.back().x
        || result.front().y != result.back().y) {
        result.push_back(result.front());
    }

    return result;
}

inline Polyline smoothen(const Polyline &polyline, float factor, int iterations)
{
    if (iterations < 1) {
        return polyline;
    }

    Polyline result = smoothen(polyline, factor);
    for (int i=1; i<iterations; ++i) {
        result = smoothen(result, factor);
    }

    return result;
}

inline Polyline convertToCubicPath(const Polyline &polyline)
{
    if (polyline.size() < 4) {
        return polyline;
    }

    Polyline result;
    result.reserve(polyline.size() * 3);

    for (unsigned int i=0; i<polyline.size(); ++i) {
        Point cur = polyline[i];
        Point last = i == 0 ? polyline[polyline.size() - 2] : polyline[i-1];
        Point next = i == polyline.size() - 1 ? polyline[1] : polyline[i+1];

        // Form a tangent line based on the line last->next
        float tx = next.x - last.x;
        float ty = next.y - last.y;
        float tlen = std::sqrt(tx * tx + ty * ty);
        tx /= tlen;
        ty /= tlen;

        if (i > 0) {
            // Weight the tangent line based on the distance from 'last' to 'cur'
            float dx = cur.x - last.x;
            float dy = cur.y - last.y;
            float len = std::sqrt(dx * dx + dy * dy) / 3;
            result.push_back(Point(cur.x - tx * len, cur.y - ty * len));
        }

        result.push_back(cur);

        if (i < polyline.size() - 1) {
            // Weight the tangent line based on the distance from 'cur' to 'next'
            float dx = next.x - cur.x;
            float dy = next.y - cur.y;
            float len = std::sqrt(dx * dx + dy * dy) / 3;
            result.push_back(Point(cur.x + tx * len, cur.y + ty * len));
        }
    }

    return result;
}

/*

 * The idea of slope tracing is to identify pixel-stpes that will visually
 * look like line slopes.
 *
 * Since the data is coming from a marching squares, we know certain things
 * about the input set that helps us. For instance, we'll always have
 * +/-45 degree, horizontal or vertical slopes.
 *
 * A pixel slope like this will result in two separate segments each with
 * abs(dx) == abs(dy) == 0.5, followed by a number of horizontal/vertical
 * segments of one pixel, followed by another slope segment with identical
 * (dx,dy) to what we started with.
 *
 *  Basically:    _______/   Becomes:          *
 *               /                     *
 *
 * We do this by running over the points, and when we find a 45 slope, do a
 * search forward from that point. We look for either all horizontal or
 * all vertical and see if where we land at the end of that is another 45
 * degree slope identical to the one we started at. If so, optimize away
 * all points in between.

 * If the polyline starts in the middle of a slope, we don't try to detect
 * that currently. We could fix that by simply "rotating" the polyline a
 * bit, since the polyline is a closed loop. Find a place where we're not
 * on a slope, and start there instead.
 */

inline Polyline traceSlopes(const Polyline &polyline)
{
    if (polyline.size() < 5) {
        return polyline;
    }

    Polyline result;
    result.reserve(polyline.size() / 10);

    for (unsigned int i=0; i<polyline.size() - 1; ++i) {
        Point cur = polyline[i];
        Point next = polyline[i+1];
        float dx = next.x - cur.x;
        float dy = next.y - cur.y;

        result.push_back(cur);

        if (std::abs(dx) == 0.5 && std::abs(dy) == 0.5 && i < polyline.size() - 2) {
            // Found a 45 degree angle, search for
            unsigned int j = i+2;

            float ndx = polyline[j].x - next.x;
            float ndy = polyline[j].y - next.y;

            bool horizontal = ndy == 0;
            bool vertical = ndx == 0;

            // Follow the horizontal or vertical line
            while (j < polyline.size()
                   && ((horizontal && polyline[j].y == next.y)
                       || (vertical && polyline[j].x == next.x))) {
                ++j;
            }

            if (j < polyline.size()
                && (polyline[j].x - polyline[j-1].x == dx)
                && (polyline[j].y - polyline[j-1].y == dy)
                && (horizontal || vertical)) {
                // line segment found, simplify it..
                i = j-1; // -1 due to the ++ in the for (..) up above
            }
        }
    }

    return result;
}

inline Polylines smoothen(const Polylines &lines, float factor, int iterations)
{
    Polylines out;
    out.reserve(lines.size());
    for (const auto &in : lines) {
        out.push_back(smoothen(in, factor, iterations));
    }
    return out;
}

inline Polylines convertToCubicPaths(const Polylines &lines)
{
    Polylines out;
    out.reserve(lines.size());
    for (const auto &in : lines) {
        out.push_back(convertToCubicPath(in));
    }
    return out;
}

inline Polylines simplify(const Polylines &lines, float threshold)
{
    Polylines out;
    out.reserve(lines.size());
    for (const auto &in : lines) {
        out.push_back(simplify(in, threshold));
    }
    return out;
}

inline Polylines simplifyRDP(const Polylines &lines, float threshold)
{
    Polylines out;
    out.reserve(lines.size());
    for (const auto &in : lines) {
        out.push_back(simplifyRDP(in, threshold));
    }
    return out;
}


inline Polylines traceSlopes(const Polylines &lines)
{
    Polylines out;
    out.reserve(lines.size());
    for (const auto &in : lines) {
        out.push_back(traceSlopes(in));
    }
    return out;
}

} // end of namespace depixelator

