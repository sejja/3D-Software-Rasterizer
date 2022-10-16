//
//  Point4.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 07/01/21.
//  Copyright � 2021 . All rights reserved.
//

#include <cstring>
#include "Vector4.h"
#include "MathUtilities.h"
#include <cmath>

// ------------------------------------------------------------------------
/*  Default Constructor
*
*   Default constructor, initializes x,y,z to zeroes, w to defined value
*/ //----------------------------------------------------------------------
Vector4::Vector4() :
	x(0.f), y(0.f), z(0.f), w(0.f) {}

// ------------------------------------------------------------------------
/*  Default Constructor
*
*   Default constructor, initializes x,y,z to zeroes, w to defined value
*/ //----------------------------------------------------------------------
Vector4::Vector4(const Vector4& rhs) :
	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

// ------------------------------------------------------------------------
/*  Custom Constructor
*
*   Creates a Vector4 from 4 given floats
*/ //----------------------------------------------------------------------
Vector4::Vector4(float xx, float yy, float zz, float ww) :
	x(xx), y(yy), z(zz), w(ww) {}

// ------------------------------------------------------------------------
/*  Operator=
*
*   Assignment operator, does not need to handle self assignment
*/ //----------------------------------------------------------------------
Vector4& Vector4::operator=(const Vector4& rhs) {
	memcpy(this, &rhs, sizeof(Vector4));

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Unary negation operator, negates all components and returns a copy
*/ //----------------------------------------------------------------------
Vector4 Vector4::operator-() const {
	return Vector4(-x, -y, -z, -w);
}

// ------------------------------------------------------------------------
/*  Operator+
*
*   Add a Vector4 to a Vector4
*/ //----------------------------------------------------------------------
Vector4 Vector4::operator+(const Vector4& rhs) const {
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Substract a Vector4 to a Vector4
*/ //----------------------------------------------------------------------
Vector4 Vector4::operator-(const Vector4& rhs) const {
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Multiply a Vector4 by a scalar
*/ //----------------------------------------------------------------------
Vector4 Vector4::operator*(const float rhs) const {
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

// ------------------------------------------------------------------------
/*  Operator/
*
*   Divide a Vector4 by a scalar
*/ //----------------------------------------------------------------------
Vector4 Vector4::operator/(const float rhs) const {
	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

// ------------------------------------------------------------------------
/*  Operator+=
*
*   Add a Vector4 to the original Vector4
*/ //----------------------------------------------------------------------
Vector4& Vector4::operator+=(const Vector4& rhs) {
	x += rhs.x, y += rhs.y, z += rhs.z, w += rhs.w;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Substract a Vector4 to the original Vector4
*/ //----------------------------------------------------------------------
Vector4& Vector4::operator-=(const Vector4& rhs) {
	x -= rhs.x, y -= rhs.y, z -= rhs.z, w -= rhs.w;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Multiply the original Vector4 by a scalar
*/ //----------------------------------------------------------------------
Vector4& Vector4::operator*=(const float rhs) {
	x *= rhs, y *= rhs, z *= rhs, w *= rhs;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator/
*
*   Divide the original Vector4 by a scalar
*/ //----------------------------------------------------------------------
Vector4& Vector4::operator/=(const float rhs) {
	x /= rhs, y /= rhs, z /= rhs, w /= rhs;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator==
*
*   Compares if two Points are equal
*/ //----------------------------------------------------------------------
bool Vector4::operator==(const Vector4& rhs) const {
	return isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z) && isEqual(w, rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator!=
*
*   Compares if two Points are not equal
*/ //----------------------------------------------------------------------
bool Vector4::operator!=(const Vector4& rhs) const {
	return !operator==(rhs);
}

// ------------------------------------------------------------------------
/*  Dot
*
*   Computes the dot product with the other vector
*/ //----------------------------------------------------------------------
float Vector4::Dot(const Vector4& rhs) const {
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

// ------------------------------------------------------------------------
/*  Dot
*
*   Computes the dot product with the other vector
*/ //----------------------------------------------------------------------
Vector4 Vector4::Cross(const Vector4& rhs) const {
	return Vector4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x, 0);
}

// ------------------------------------------------------------------------
/*  Length
*
*   Computes the true length of the vector
*/ //----------------------------------------------------------------------
float Vector4::Length() const {
	return sqrtf(LengthSq());
}

// ------------------------------------------------------------------------
/*  Dot
*
*   Computes the squared length of the vector
*/ //----------------------------------------------------------------------
float Vector4::LengthSq() const {
	return x * x + y * y + z * z + w * w;
}

// ------------------------------------------------------------------------
/*  Normalize
*
*   Normalizes the vector to make the final vector be of length 1
*/ //----------------------------------------------------------------------
void Vector4::Normalize() {
	const float length_ = Length();

	//If we have a non 0 length
	if (length_)
		operator/=(length_);
}

// ------------------------------------------------------------------------
/*  Zero
*
*   Sets x,y,z to zeroes, w to defined value
*/ //----------------------------------------------------------------------
void Vector4::Zero() {
	x = y = z = w = 0;
}