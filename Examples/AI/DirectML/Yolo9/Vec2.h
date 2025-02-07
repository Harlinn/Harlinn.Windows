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


#include <cmath>

namespace crushedpixel {

/**
 * A two-dimensional float vector.
 * It exposes the x and y fields
 * as required by the Polyline2D functions.
 */
struct Vec2 {
	Vec2() :
			Vec2(0, 0) {}

	Vec2(float x, float y) :
			x(x), y(y) {}

	virtual ~Vec2() = default;

	float x, y;
};

namespace Vec2Maths {

template<typename Vec2>
static bool equal(const Vec2 &a, const Vec2 &b) {
	return a.x == b.x && a.y == b.y;
}

template<typename Vec2>
static Vec2 multiply(const Vec2 &a, const Vec2 &b) {
	return {a.x * b.x, a.y * b.y};
}

template<typename Vec2>
static Vec2 multiply(const Vec2 &vec, float factor) {
	return {vec.x * factor, vec.y * factor};
}

template<typename Vec2>
static Vec2 divide(const Vec2 &vec, float factor) {
	return {vec.x / factor, vec.y / factor};
}

template<typename Vec2>
static Vec2 add(const Vec2 &a, const Vec2 &b) {
	return {a.x + b.x, a.y + b.y};
}

template<typename Vec2>
static Vec2 subtract(const Vec2 &a, const Vec2 &b) {
	return {a.x - b.x, a.y - b.y};
}

template<typename Vec2>
static float magnitude(const Vec2 &vec) {
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

template<typename Vec2>
static Vec2 withLength(const Vec2 &vec, float len) {
	auto mag = magnitude(vec);
	auto factor = mag / len;
	return divide(vec, factor);
}

template<typename Vec2>
static Vec2 normalized(const Vec2 &vec) {
	return withLength(vec, 1);
}

/**
 * Calculates the dot product of two vectors.
 */
template<typename Vec2>
static float dot(const Vec2 &a, const Vec2 &b) {
	return a.x * b.x + a.y * b.y;
}

/**
 * Calculates the cross product of two vectors.
 */
template<typename Vec2>
static float cross(const Vec2 &a, const Vec2 &b) {
	return a.x * b.y - a.y * b.x;
}

/**
 * Calculates the angle between two vectors.
 */
template<typename Vec2>
static float angle(const Vec2 &a, const Vec2 &b) {
	return std::acos(dot(a, b) / (magnitude(a) * magnitude(b)));
}

} // namespace Vec2Maths

}