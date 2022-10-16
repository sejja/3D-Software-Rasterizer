//
//  Matrix4.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 07/01/21.
//  Copyright � 2021 . All rights reserved.
//

#include <cstring>
#include "Matrix4.h"
#include "MathUtilities.h"
#include <cmath>

// ------------------------------------------------------------------------
/*  Default Constructor
*
*   Default constructor should initialize to zeroes
*/ //----------------------------------------------------------------------
Matrix4::Matrix4() :
	v{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } {}

// ------------------------------------------------------------------------
/*  Copy Constructor
*
*   Copies one Matrix onto another
*/ //----------------------------------------------------------------------
Matrix4::Matrix4(const Matrix4& rhs) :
	v{ rhs.v[0], rhs.v[1], rhs.v[2], rhs.v[3], rhs.v[4], rhs.v[5], rhs.v[6], rhs.v[7],
	rhs.v[8], rhs.v[9], rhs.v[10], rhs.v[11], rhs.v[12], rhs.v[13], rhs.v[14], rhs.v[15] } {}

// ------------------------------------------------------------------------
/*  Custom Constructor
*
*   Creates a Matrix from 16 digits
*/ //----------------------------------------------------------------------
Matrix4::Matrix4(float mm00, float mm01, float mm02, float mm03,
	float mm10, float mm11, float mm12, float mm13,
	float mm20, float mm21, float mm22, float mm23,
	float mm30, float mm31, float mm32, float mm33) :
	v{ mm00, mm01, mm02, mm03, mm10, mm11, mm12, mm13, mm20, mm21, mm22, mm23,
	mm30, mm31, mm32, mm33 } {}

// ------------------------------------------------------------------------
/*  Operator=
*
*   Assignment operator, does not need to handle self-assignment
*/ //----------------------------------------------------------------------
Matrix4& Matrix4::operator=(const Matrix4& rhs) {
	memcpy(this, &rhs, sizeof(Matrix4));

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Multiplying a Matrix4 with a Vector4
*/ //----------------------------------------------------------------------
Vector4 Matrix4::operator*(const Vector4& rhs) const {
	return Vector4(m[0][0] * rhs.x + m[0][1] * rhs.y + m[0][2] * rhs.z + m[0][3] * rhs.w,
		m[1][0] * rhs.x + m[1][1] * rhs.y + m[1][2] * rhs.z + m[1][3] * rhs.w,
		m[2][0] * rhs.x + m[2][1] * rhs.y + m[2][2] * rhs.z + m[2][3] * rhs.w,
		m[3][0] * rhs.x + m[3][1] * rhs.y + m[3][2] * rhs.z + m[3][3] * rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Multiplying a Matrix4 with a Point4
*/ //----------------------------------------------------------------------
Point4 Matrix4::operator*(const Point4& rhs) const {
	return Point4(m[0][0] * rhs.x + m[0][1] * rhs.y + m[0][2] * rhs.z + m[0][3] * rhs.w,
		m[1][0] * rhs.x + m[1][1] * rhs.y + m[1][2] * rhs.z + m[1][3] * rhs.w,
		m[2][0] * rhs.x + m[2][1] * rhs.y + m[2][2] * rhs.z + m[2][3] * rhs.w,
		m[3][0] * rhs.x + m[3][1] * rhs.y + m[3][2] * rhs.z + m[3][3] * rhs.w);
}

// ------------------------------------------------------------------------
/*  Operator+
*
*   Add two Matrices
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::operator+(const Matrix4& rhs) const {
	return Matrix4(v[0] + rhs.v[0], v[1] + rhs.v[1], v[2] + rhs.v[2], v[3] + rhs.v[3],
		v[4] + rhs.v[4], v[5] + rhs.v[5], v[6] + rhs.v[6], v[7] + rhs.v[7],
		v[8] + rhs.v[8], v[9] + rhs.v[9], v[10] + rhs.v[10], v[11] + rhs.v[11],
		v[12] + rhs.v[12], v[13] + rhs.v[13], v[14] + rhs.v[14], v[15] + rhs.v[15]);
}

// ------------------------------------------------------------------------
/*  Operator-
*
*   Substracts two Matrices
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::operator-(const Matrix4& rhs) const {
	return Matrix4(v[0] - rhs.v[0], v[1] - rhs.v[1], v[2] - rhs.v[2], v[3] - rhs.v[3],
		v[4] - rhs.v[4], v[5] - rhs.v[5], v[6] - rhs.v[6], v[7] - rhs.v[7],
		v[8] - rhs.v[8], v[9] - rhs.v[9], v[10] - rhs.v[10], v[11] - rhs.v[11],
		v[12] - rhs.v[12], v[13] - rhs.v[13], v[14] - rhs.v[14], v[15] - rhs.v[15]);
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Multiplies two Matrices
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::operator*(const Matrix4& rhs) const {
	Matrix4 temp_;

	for (unsigned char row = 0; row < 4; row++)
		for (unsigned char col = 0; col < 4; col++)
			temp_.m[row][col] += m[row][0] * rhs.m[0][col] + m[row][1] * rhs.m[1][col]
			+ m[row][2] * rhs.m[2][col] + m[row][3] * rhs.m[3][col];

	return temp_;
}

// ------------------------------------------------------------------------
/*  Operator+=
*
*   Adds one Matrix to this one
*/ //----------------------------------------------------------------------
Matrix4& Matrix4::operator+=(const Matrix4& rhs) {
	v[0] += rhs.v[0], v[1] += rhs.v[1], v[2] += rhs.v[2], v[3] += rhs.v[3],
		v[4] += rhs.v[4], v[5] += rhs.v[5], v[6] += rhs.v[6], v[7] += rhs.v[7],
		v[8] += rhs.v[8], v[9] += rhs.v[9], v[10] += rhs.v[10], v[11] += rhs.v[11],
		v[12] += rhs.v[12], v[13] += rhs.v[13], v[14] += rhs.v[14], v[15] += rhs.v[15];

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator-=
*
*   Substracts one Matrix to this one
*/ //----------------------------------------------------------------------
Matrix4& Matrix4::operator-=(const Matrix4& rhs) {
	v[0] -= rhs.v[0], v[1] -= rhs.v[1], v[2] -= rhs.v[2], v[3] -= rhs.v[3],
		v[4] -= rhs.v[4], v[5] -= rhs.v[5], v[6] -= rhs.v[6], v[7] -= rhs.v[7],
		v[8] -= rhs.v[8], v[9] -= rhs.v[9], v[10] -= rhs.v[10], v[11] -= rhs.v[11],
		v[12] -= rhs.v[12], v[13] -= rhs.v[13], v[14] -= rhs.v[14], v[15] -= rhs.v[15];

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator*=
*
*   Multiplies one Matrix to this one
*/ //----------------------------------------------------------------------
Matrix4& Matrix4::operator*=(const Matrix4& rhs) {
	*this = *this * rhs;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Scale the entire matrix by a float
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::operator*(const float rhs) const {
	return Matrix4(v[0] * rhs, v[1] * rhs, v[2] * rhs, v[3] * rhs, v[4] * rhs,
		v[5] * rhs, v[6] * rhs, v[7] * rhs, v[8] * rhs, v[9] * rhs, v[10] * rhs,
		v[11] * rhs, v[12] * rhs, v[13] * rhs, v[14] * rhs, v[15] * rhs);
}

// ------------------------------------------------------------------------
/*  Operator*
*
*   Divide the entire matrix by a float
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::operator/(const float rhs) const {
	return Matrix4(v[0] / rhs, v[1] / rhs, v[2] / rhs, v[3] / rhs,
		v[4] / rhs, v[5] / rhs, v[6] / rhs, v[7] / rhs,
		v[8] / rhs, v[9] / rhs, v[10] / rhs, v[11] / rhs,
		v[12] / rhs, v[13] / rhs, v[14] / rhs, v[15] / rhs);
}

// ------------------------------------------------------------------------
/*  Operator*=
*
*   Multiply the entire matrix by a float
*/ //----------------------------------------------------------------------
Matrix4& Matrix4::operator*=(const float rhs) {
	v[0] *= rhs, v[1] *= rhs, v[2] *= rhs, v[3] *= rhs, v[4] *= rhs, v[5] *= rhs,
		v[6] *= rhs, v[7] *= rhs, v[8] *= rhs, v[9] *= rhs, v[10] *= rhs, v[11] *= rhs,
		v[12] *= rhs, v[13] *= rhs, v[14] *= rhs, v[15] *= rhs;

	return *this;
}

// ------------------------------------------------------------------------
/*  Operator*=
*
*   Multiply the entire matrix by a float
*/ //----------------------------------------------------------------------
Matrix4& Matrix4::operator/=(const float rhs) {
	v[0] /= rhs, v[1] /= rhs, v[2] /= rhs, v[3] /= rhs, v[4] /= rhs, v[5] /= rhs,
		v[6] /= rhs, v[7] /= rhs, v[8] /= rhs, v[9] /= rhs, v[10] /= rhs, v[11] /= rhs,
		v[12] /= rhs, v[13] /= rhs, v[14] /= rhs, v[15] /= rhs;

	return *this;
}

// ------------------------------------------------------------------------
/*  Row
*
*   Gets the row of the matrix
*/ //----------------------------------------------------------------------
Vector4 Matrix4::row(unsigned idx) {
	const unsigned temp_ = idx * 4;
	return Vector4(v[temp_], v[temp_ + 1], v[temp_ + 2], v[temp_ + 3]);
}

// ------------------------------------------------------------------------
/*  Column
*
*   Gets the column of the matrix
*/ //----------------------------------------------------------------------
Vector4 Matrix4::column(unsigned idx) {
	return Vector4(v[idx], v[4 + idx], v[8 + idx], v[12 + idx]);
}

// ------------------------------------------------------------------------
/*  Operator==
*
*   Is the same Matrix equal?
*/ //----------------------------------------------------------------------
bool Matrix4::operator==(const Matrix4& rhs) const {
	return isEqual(v[0], rhs.v[0]) && isEqual(v[1], rhs.v[1]) && isEqual(v[2], rhs.v[2])
		&& isEqual(v[3], rhs.v[3]) && isEqual(v[4], rhs.v[4]) && isEqual(v[5], rhs.v[5])
		&& isEqual(v[6], rhs.v[6]) && isEqual(v[7], rhs.v[7]) && isEqual(v[8], rhs.v[8])
		&& isEqual(v[9], rhs.v[9]) && isEqual(v[10], rhs.v[10]) && isEqual(v[11], rhs.v[11])
		&& isEqual(v[12], rhs.v[12]) && isEqual(v[13], rhs.v[13]) && isEqual(v[14], rhs.v[14])
		&& isEqual(v[15], rhs.v[15]);
}

// ------------------------------------------------------------------------
/*  Operator!=
*
*   Is the same Matrix not equal?
*/ //----------------------------------------------------------------------
bool Matrix4::operator!=(const Matrix4& rhs) const {
	return !operator==(rhs);
}

// ------------------------------------------------------------------------
/*  Translate
*
*   Translate the Vector
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::Translate(const Vector4& translation) {
	return { 1.f, 0.f, 0.f, translation.x, 0.f, 1.f, 0.f, translation.y, 0.f,
		0.f, 1.f, translation.z, 0.f, 0.f, 0.f, 1.f };
}

// ------------------------------------------------------------------------
/*  Rotate X
*
*   Rotates on the X axis
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::rotateX(const float angle) {
	const float cos_ = cosf(angle), sin_ = sinf(angle);

	return { 1.f, 0.f, 0.f, 0.f, 0.f, cos_, sin_, 0.f, 0.f, -sin_, cos_, 0.f,
		0.f, 0.f, 0.f, 1.f };
}

// ------------------------------------------------------------------------
/*  Rotate Y
*
*   Rotates on the Y axis
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::rotateY(const float angle) {
	const float cos_ = cosf(angle), sin_ = sinf(angle);

	return { cos_, 0.f, sin_, 0.f, 0.f, 1.f, 0.f, 0.f, -sin_, 0.f, cos_, 0.f,
		0.f, 0.f, 0.f, 1.f };
}

// ------------------------------------------------------------------------
/*  Rotate Z
*
*   Rotates on the Z axis
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::rotateZ(const float angle) {
	const float cos_ = cosf(angle), sin_ = sinf(angle);

	return { cos_, sin_, 0.f, 0.f, -sin_, cos_, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f };
}

// ------------------------------------------------------------------------
/*  Rotate
*
*   Makes a rotation matrix
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::Rotate(const Vector4& angles) {
	return rotateX(angles.x) * rotateY(angles.y) * rotateZ(angles.z);
}

// ------------------------------------------------------------------------
/*  Scale
*
*   Makes a Scale Matrix
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::Scale(const Vector4& scaling) {
	return { scaling.x, 0.f, 0.f, 0.f, 0.f, scaling.y, 0.f, 0.f, 0.f, 0.f, scaling.z, 0.f,
		0.f, 0.f, 0.f, 1.f };
}

// ------------------------------------------------------------------------
/*  Perspective
*
*   Makes a Perspective Matrix
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::Projection(const float d) {
	return { d, 0.f, 0.f, 0.f, 0.f, d, 0.f, 0.f, 0.f, 0.f, d, 0.f,
		0.f, 0.f, -1.f, 0.f };
}

// ------------------------------------------------------------------------
/*  Viewport
*
*   Viewport Matrix
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::Viewport(const float WindowWidth, const float WindowHeight,
	const float ViewportWidth, const float ViewportHeight) {
	const float LocalWidth = WindowWidth / ViewportWidth;
	const float LocalHeight = WindowHeight / ViewportHeight;

	return { LocalWidth, 0.f, 0.f, WindowWidth / 2, 0.f, LocalHeight, 0.f, WindowHeight / 2, 0.f,
		0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };
}

// ------------------------------------------------------------------------
/*  Operator!=
*
*   Zeroes out the entire matrix
*/ //----------------------------------------------------------------------
void Matrix4::Zero(void) {
	v[0] = v[1] = v[2] = v[3] = v[4] = v[5] = v[6] = v[7] = v[8] = v[9] = v[10] = v[11] =
		v[12] = v[13] = v[14] = v[15] = 0;
}

// ------------------------------------------------------------------------
/*  Operator!=
*
*   Builds the identity matrix
*/ //----------------------------------------------------------------------
void Matrix4::Identity(void) {
	m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] =
		m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0;
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

// ------------------------------------------------------------------------
/*  Rotate X
*
*   Rotates on the X axis
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::Projection(const float left, const float right, const float bottom, const float top,
	const float near, const float far, const float focal) {
	const float fminn_ = far - near;

	return { focal / (right - left), 0.f, 0.f, 0.f,
		0.f,focal / (top - bottom), 0.f, 0.f,
		0.f, 0.f, -(far + near) / fminn_, (-2.f * near * far) / fminn_,
		0.f, 0.f, -1.f, 0.f };
}

// ------------------------------------------------------------------------
/*  Rotate Axis
*
*   Rotates on a custom axis
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::RotateAxis(const Vector4& vec, const float angle) {

	const auto ftensor = [](const Vector4& p1, const Vector4& p2) {

		return Matrix4(p1.x * p2.x, p1.x * p2.y, p1.x * p2.z, 0,
			p1.y * p2.x, p1.y * p2.y, p1.y * p2.z, 0,
			p1.z * p2.x, p1.z * p2.y, p1.z * p2.z, 0,
			0, 0, 0, 1);

	};

	const auto fcross_ = [](const Vector4& p1) {

		return Matrix4(0, -p1.z, p1.y, 0,
			p1.z, 0, -p1.x, 0,
			-p1.y, p1.x, 0, 0,
			0, 0, 0, 1);

	};

	const float cos_ = cos(angle);
	const Matrix4 I = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 };

	return I * cos_ + ftensor(vec, vec) * (1 - cos_) + fcross_(vec) * sin(angle);
}

// ------------------------------------------------------------------------
/*  Orthogonal Rotation
*
*   Creates a Orthogonal Rotation Matrix with the up, right and view vector
*/ //----------------------------------------------------------------------
Matrix4 Matrix4::OrthogonalRotation(const Vector4& u, const Vector4& v,
	const Vector4& w) {

	return { w.x, v.x, u.x, 0,
				w.y, v.y, u.y, 0,
				w.z, v.z, u.z, 0,
				0, 0, 0, 1 };
}
