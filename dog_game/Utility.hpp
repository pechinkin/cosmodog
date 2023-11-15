#pragma once

#include <iostream>

namespace csd
{

using float_t = float;

struct Vec
{
	float_t x;
	float_t y;
};

Vec operator+ (const Vec& lhs, const Vec& rhs)
{
	return Vec{lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec operator* (const Vec& lhs, float_t val)
{
	return Vec{lhs.x * val, lhs.y * val};
}

Vec operator* (float_t val, const Vec& rhs)
{
	return rhs * val;
}

Vec operator/ (const Vec& lhs, float_t val)
{
	return lhs * (1. / val);
}

Vec operator/ (float_t val, const Vec& rhs)
{
	return rhs / val;
}

Vec operator- (const Vec& lhs, const Vec& rhs)
{
	return lhs + (-1) * rhs;
}

std::ostream& operator<< (std::ostream& cout, const Vec& vec)
{
	return cout << '[' << vec.x << ", " << vec.y << ']';
}

enum class RotDir // rotation direction
{
	CW, // clockwise
	ACW // anticlockwise
};

Vec getUnitVec(float_t angle)
{
	return Vec{	
			cosf(angle),
			sinf(angle)
			};
}

float_t dot(const Vec& lhs, const Vec& rhs)
{
	return 	lhs.x * rhs.x +
			lhs.y * rhs.y;
}

Vec normalize(const Vec& vec)
{
	return vec * (1 / sqrt(dot(vec, vec)));
}

Vec getUnitVec(const Vec& start, const Vec& end)
{
	Vec vec = end - start;
	return normalize(vec);
}

Vec rotateVec(const Vec& vec, RotDir dir, float_t angle)
{
	angle = (dir == RotDir::ACW) ? angle : -angle;

	float_t sinAngle = sinf(angle);
	float_t cosAngle = cosf(angle);

	Vec rotatedVec{	vec.x * cosAngle + vec.y * (-sinAngle),
					vec.x * sinAngle + vec.y * cosAngle};

	return rotatedVec;
}

Vec rotateVec(const Vec& vec, float_t angle)
{
	return rotateVec(vec, RotDir::ACW, angle);
}

};