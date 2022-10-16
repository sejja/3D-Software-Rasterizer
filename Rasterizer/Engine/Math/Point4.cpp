//
//  Point4.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 07/01/21.
//  Copyright � 2021 . All rights reserved.
//

#include <cstring>
#include "Point4.h"
#include "MathUtilities.h"

// ------------------------------------------------------------------------
/*! Default Constructor
*
*   Default constructor, sets x,y,z to zero and w to the defined value
*/ //----------------------------------------------------------------------
Point4::Point4() :
	x(0.f), y(0.f), z(0.f), w(1.f) {}

// ------------------------------------------------------------------------
/*! Copy Constructor
*
*   Copy constructor, copies every component from the other Point4
*/ //----------------------------------------------------------------------
Point4::Point4(const Point4& rhs) :
	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

// ------------------------------------------------------------------------
/*  Custom Constructor
*
*   Creates a Point 4 from 4 given floats
*/ //----------------------------------------------------------------------
Point4::Point4(float xx, float yy, float zz, float ww) :
	x(xx), y(yy), z(zz), w(ww) {}

// ------------------------------------------------------------------------
/*  Operator=
*
*   Assignment operator, copies every component from the other Point4
*/ //----------------------------------------------------------------------
Point4& Point4::operator=(const Point4& rhs) {
	memcpy(this, &rhs, sizeof(Point4));

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Unary negation operator, negates every component and returns a copy
*/ //----------------------------------------------------------------------
Point4 Point4::operator-() const {
	return Point4(-x, -y, -z, -w);
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Binary subtraction operator, Subtract two Point4s and you get a Vector4
*/ //----------------------------------------------------------------------
Vector4 Point4::operator-(const Point4& rhs) const {
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator+
*
*   Add a Vector4 to a Point4
*/ //----------------------------------------------------------------------
Point4 Point4::operator+(const Vector4& rhs) const {
	return Point4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Substract a Vector4 to a Point4
*/ //----------------------------------------------------------------------
Point4 Point4::operator-(const Vector4& rhs) const {
	return Point4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator+=
*
*   Add a Vector4 to the original Point4
*/ //----------------------------------------------------------------------
Point4& Point4::operator+=(const Vector4& rhs) {
	x += rhs.x, y += rhs.y, z += rhs.z, w += rhs.w;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator+=
*
*   Add a Vector4 to the original Point4
*/ //----------------------------------------------------------------------
Point4& Point4::operator-=(const Vector4& rhs) {
	x -= rhs.x, y -= rhs.y, z -= rhs.z, w -= rhs.w;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator==
*
*   Compares if two Points are equal
*/ //----------------------------------------------------------------------
bool Point4::operator==(const Point4& rhs) const {
	return isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z) && isEqual(w, rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator!=
*
*   Compares if two Points are not equal
*/ //----------------------------------------------------------------------
bool Point4::operator!=(const Point4& rhs) const {
	return !operator==(rhs);
}

// ------------------------------------------------------------------------
/*  Zero
*
*   Sets x,y,z to zeroes, w to defined value
*/ //----------------------------------------------------------------------
void Point4::Zero() {
	x = y = z = 0;
	w = 1;
}