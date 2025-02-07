#pragma once

/*
   Copyright 2024 Espen Harlinn

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


#include "Vec2.h"
#include <optional>

namespace crushedpixel {

template<typename Vec2>
struct LineSegment {
	LineSegment(const Vec2 &a, const Vec2 &b) :
			a(a), b(b) {}

	Vec2 a, b;

	/**
	 * @return A copy of the line segment, offset by the given vector.
	 */
	LineSegment operator+(const Vec2 &toAdd) const {
		return {Vec2Maths::add(a, toAdd), Vec2Maths::add(b, toAdd)};
	}

	/**
	 * @return A copy of the line segment, offset by the given vector.
	 */
	LineSegment operator-(const Vec2 &toRemove) const {
		return {Vec2Maths::subtract(a, toRemove), Vec2Maths::subtract(b, toRemove)};
	}

	/**
	 * @return The line segment's normal vector.
	 */
	Vec2 normal() const {
		auto dir = direction();

		// return the direction vector
		// rotated by 90 degrees counter-clockwise
		return {-dir.y, dir.x};
	}

	/**
	 * @return The line segment's direction vector.
	 */
	Vec2 direction(bool normalized = true) const {
		auto vec = Vec2Maths::subtract(b, a);

		return normalized
		       ? Vec2Maths::normalized(vec)
		       : vec;
	}

	static std::optional<Vec2> intersection(const LineSegment &a, const LineSegment &b, bool infiniteLines) {
		// calculate un-normalized direction vectors
		auto r = a.direction(false);
		auto s = b.direction(false);

		auto originDist = Vec2Maths::subtract(b.a, a.a);

		auto uNumerator = Vec2Maths::cross(originDist, r);
		auto denominator = Vec2Maths::cross(r, s);

		if (std::abs(denominator) < 0.0001f) {
			// The lines are parallel
			return std::nullopt;
		}

		// solve the intersection positions
		auto u = uNumerator / denominator;
		auto t = Vec2Maths::cross(originDist, s) / denominator;

		if (!infiniteLines && (t < 0 || t > 1 || u < 0 || u > 1)) {
			// the intersection lies outside of the line segments
			return std::nullopt;
		}

		// calculate the intersection point
		// a.a + r * t;
		return Vec2Maths::add(a.a, Vec2Maths::multiply(r, t));
	}
};


} // namespace crushedpixel