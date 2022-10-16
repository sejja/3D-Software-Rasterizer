#ifndef MATRIX4_H
#define MATRIX4_H

#include <stdio.h>              // printf
#include "Vector4.h"
#include "Point4.h"

class Matrix4 {
public:

	union
	{
		float m[4][4];
		float v[16];
	};
	/*
		This union lets us access the data in multiple ways
		All of these are modifying the same location in memory
		Matrix4 mtx;
		mtx.m[2][2] = 1.0f;
		mtx.v[10] = 2.0f;
	*/

	// Default constructor should initialize to zeroes
	Matrix4(void);

	// Copy constructor, copies every entry from the other matrix.
	Matrix4(const Matrix4& rhs);

	// Non-default constructor, self-explanatory
	Matrix4(float mm00, float mm01, float mm02, float mm03,
		float mm10, float mm11, float mm12, float mm13,
		float mm20, float mm21, float mm22, float mm23,
		float mm30, float mm31, float mm32, float mm33);

	// Assignment operator, does not need to handle self-assignment
	Matrix4& operator=(const Matrix4& rhs);

	// Multiplying a Matrix4 with a Vector4 or a Point4
	Vector4 operator*(const Vector4& rhs) const;
	Point4 operator*(const Point4& rhs) const;

	// Basic Matrix arithmetic operations
	Matrix4 operator+(const Matrix4& rhs) const;
	Matrix4 operator-(const Matrix4& rhs) const;
	Matrix4 operator*(const Matrix4& rhs) const;

	// Similar to the three above except they modify the original
	Matrix4& operator+=(const Matrix4& rhs);
	Matrix4& operator-=(const Matrix4& rhs);
	Matrix4& operator*=(const Matrix4& rhs);

	// Scale/Divide the entire matrix by a float
	Matrix4 operator*(const float rhs) const;
	Matrix4 operator/(const float rhs) const;
	// Same as previous
	Matrix4& operator*=(const float rhs);
	Matrix4& operator/=(const float rhs);
	Vector4 row(unsigned idx);
	Vector4 column(unsigned idx);
	static Matrix4 Translate(const Vector4& translation);
	static Matrix4 Rotate(const Vector4& angles);
	static Matrix4 rotateX(const float angle);
	static Matrix4 rotateY(const float angle);
	static Matrix4 rotateZ(const float angle);
	static Matrix4 Scale(const Vector4& scaling);
	static Matrix4 Projection(const float focus);
	static Matrix4 Viewport(const float width, const float height,
		const float ViewportHeight, const float Vieworthwidth);
	static Matrix4 Projection(const float left, const float right, const float bottom,
		const float top, const float near, const float far, const float focal);
	static Matrix4 RotateAxis(const Vector4& vec, const float angle);
	static Matrix4 OrthogonalRotation(const Vector4& vec1,
		const Vector4& vec2, const Vector4& vec3);

	// Comparison operators which should use an epsilon defined in
	// MathUtilities.h to see if the value is within a certain range
	// in which case we say they are equivalent.
	bool operator==(const Matrix4& rhs) const;
	bool operator!=(const Matrix4& rhs) const;

	// Zeroes out the entire matrix
	void Zero(void);

	// Builds the identity matrix
	void Identity(void);
};

#endif