//
//  DrawTriangle.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 30/01/21.
//  Copyright � 2021 . All rights reserved.
//

#include "DrawTriangle.h"
#include "../FrameBuffer.h"
#include <cmath>

namespace Graphics {
	namespace Rasterizer {
		// ------------------------------------------------------------------------
		/*! Vertex Inf
		*
		*   Determines the case in which the vertices are ordered
		*/ // ---------------------------------------------------------------------
		struct VertexInf {
			Point4* Top, * Middle, * Bottom;
			bool MiddleIsLeft;

			// ------------------------------------------------------------------------
			/*! Custom Constructor
			*
			*   Constructs a Default Vertex information (For AEVec2)
			*/ // --------------------------------------------------------------------
			VertexInf(const Point4& a, const Point4& b, const Point4& c) noexcept {
				//If the vertex 0 greater than 1
				if (a.y > b.y) {
					//If the vertex 1 greater than 2
					if (b.y > c.y) {
						Top = const_cast<Point4*>(&a);
						Middle = const_cast<Point4*>(&b);
						Bottom = const_cast<Point4*>(&c);
						MiddleIsLeft = true;
					}
					else if (a.y > c.y) {
						Top = const_cast<Point4*>(&a);
						Middle = const_cast<Point4*>(&c);
						Bottom = const_cast<Point4*>(&b);
						MiddleIsLeft = false;
					}
					else {
						Top = const_cast<Point4*>(&c);
						Middle = const_cast<Point4*>(&a);
						Bottom = const_cast<Point4*>(&b);
						MiddleIsLeft = true;
					}
				}
				else {
					//If the vertex 0 greater than 2
					if (a.y > c.y) {
						Top = const_cast<Point4*>(&b);
						Middle = const_cast<Point4*>(&a);
						Bottom = const_cast<Point4*>(&c);
						MiddleIsLeft = false;
					}
					else if (b.y > c.y) {
						Top = const_cast<Point4*>(&b);
						Middle = const_cast<Point4*>(&c);
						Bottom = const_cast<Point4*>(&a);
						MiddleIsLeft = true;
					}
					else {
						Top = const_cast<Point4*>(&c);
						Middle = const_cast<Point4*>(&b);
						Bottom = const_cast<Point4*>(&a);
						MiddleIsLeft = false;
					}
				}
			}
		};

#define LERP(a, b, c, d) (a - b) / (c - d)

		// ------------------------------------------------------------------------
		/*! Draw Triangle Plane Normal
		*
		*   Draws a Triangle using the Plane Normal method
		*/ // --------------------------------------------------------------------
		void DrawTriangle(const Point4& v0, const Point4& v1, const Point4& v2,
			const Color& c) noexcept {
			//Get the Vertex information
			const VertexInf vinf_(v0, v1, v2);
			const unsigned char col[3] = { static_cast<unsigned char>(c.r),
				static_cast<unsigned char>(c.g), static_cast<unsigned char>(c.b) };

			//find the Ending Y and the Starting Y
			int yEnd_ = static_cast<int>(ceilf(vinf_.Middle->y)),
				y_ = static_cast<int>(ceilf(vinf_.Top->y)), cXR_;

			/*Calculate the triangle's borders, as well as it's current slopes and
			it's pixel gradient steps and some precomputed data*/
			float xL_ = vinf_.Top->x, xR_ = xL_,
				SlopeLeft_ = vinf_.MiddleIsLeft ?
				LERP(vinf_.Middle->x, vinf_.Top->x,
					vinf_.Middle->y, vinf_.Top->y)
				: LERP(vinf_.Bottom->x, vinf_.Top->x,
					vinf_.Bottom->y, vinf_.Top->y),
				SlopeRight_ = vinf_.MiddleIsLeft ?
				LERP(vinf_.Bottom->x, vinf_.Top->x,
					vinf_.Bottom->y, vinf_.Top->y)
				: LERP(vinf_.Middle->x, vinf_.Top->x,
					vinf_.Middle->y, vinf_.Top->y);

			//Calculate Plane Vertices (Z axis correspond to each color)
			const Vector4 VertexT_ = { Vector4(v0.x - v1.x,
				v0.y - v1.y, v0.z - v1.z).
				Cross(Vector4(v0.x - v2.x, v0.y -
				v2.y, v0.z - v2.z)) };

			//Calculate Increments
			const float dx_ = { (-VertexT_.x) / VertexT_.z },
				dy_ = { (-VertexT_.y) / VertexT_.z };

			//Declare the Left and Right interpolant colors as well as it's gradient
			float ColL_ = vinf_.Top->z, Gradient_ = vinf_.Top->z;

			//Calcualte steps
			float Step = { dy_ + SlopeLeft_ * dx_ };

			//traverse through the first part of the triangle
			for (; y_ > yEnd_; y_--) {
				//Round the Right Boundary
				cXR_ = static_cast<int>(floorf(xR_));

				//Set the gradient initial value to the left color
				Gradient_ = ColL_;

				//Draw a line
				for (int x = static_cast<int>(floorf(xL_)); x <= cXR_; x++) {
					//Set the pixel
					FrameBuffer::SetPixel(x, y_, Gradient_, col[0], col[1], col[2]);

					//Increment the gradient (Red)
					Gradient_ += dx_;
				}

				//Update the Red Channel
				ColL_ -= Step;

				//Extend the Boundaries (Left)
				xL_ -= SlopeLeft_;

				//Extend the Boundaries (Right)
				xR_ -= SlopeRight_;
			}

			//If the middle is on the left
			if (vinf_.MiddleIsLeft) {
				//Update the Left Boundaries
				xL_ = vinf_.Middle->x;

				//Adjust the new slope
				SlopeLeft_ = (vinf_.Bottom->x - vinf_.Middle->x)
					/ (vinf_.Bottom->y - vinf_.Middle->y);

				//Update the Color
				ColL_ = vinf_.Middle->z;

				//else
			}
			else {
				//Update the Right Boundaries
				xR_ = vinf_.Middle->x;

				//Adjust the new slope
				SlopeRight_ = (vinf_.Bottom->x - vinf_.Middle->x)
					/ (vinf_.Bottom->y - vinf_.Middle->y);
			}

			//Set the new color increment(Red)
			Step = dy_ + SlopeLeft_ * dx_;

			//Set the new ending
			yEnd_ = static_cast<int>(ceilf(vinf_.Bottom->y)) + 1;

			//Traverse through the second part of the triangle
			for (; y_ >= yEnd_; y_--) {
				//Round the Right Boundaries
				cXR_ = static_cast<int>(floorf(xR_));

				//Copy the Left color to the gradient
				Gradient_ = ColL_;

				//Draw a line
				for (int x = static_cast<int>(floorf(xL_)); x <= cXR_; x++) {
					//Set the pixel
					FrameBuffer::SetPixel(x, y_, Gradient_, col[0], col[1], col[2]);

					//Increment the gradient (Red)
					Gradient_ += dx_;
				}

				//Update the Red Channel
				ColL_ -= Step;

				//Extend the Boundaries (Left)
				xL_ -= SlopeLeft_;

				//Extend the Boundaries (Right)
				xR_ -= SlopeRight_;
			}
		}

		// ------------------------------------------------------------------------
		/*! Draw Line Bresenham
		*
		*   Draws Line using the Bresenham method
		*/ // --------------------------------------------------------------------
		void DrawLine(const Point4& p1, const Point4& p2, const Color& c) noexcept {
			//find DX and DY
			const float dx = p2.x - p1.x, dy = p2.y - p1.y;

			//stablish the Step of X and for Y
			const int stepX = dx > 0 ? 1 : -1, stepY = dy > 0 ? 1 : -1;

			//Calculate the integer versions of DX and DY
			const int Dx_ = (int)abs(floorf(dx)), Dy_ = (int)abs(floorf(dy));

			//if the slope is less than 1
			if (abs(dy / dx) < 1) {
				//Calculate the starting Error Margin
				int ErrMg_ = 2 * Dy_ - Dx_;

				//Find the Ending Point
				const int eX_ = (int)floorf(p2.x);

				//Calculate 2Dy and 2Dy - 2Dx (to avoid calculating it everytime needed)
				const int twoDiffY_ = 2 * Dy_, diffDP_ = twoDiffY_ - 2 * Dx_;

				//Until we reach the end of our line
				for (int x = (int)floorf(p1.x), y = (int)floorf(p1.y); x != eX_; x += stepX) {
					//set the corresponding pixel
					FrameBuffer::SetPixel(x, y, 0, (unsigned char)c.r,
						(unsigned char)c.g, (unsigned char)c.b);

					//if the Error Margin is greater than 0
					if (ErrMg_ > 0)
						//Update the next value of Y
						y += stepY, ErrMg_ += diffDP_;
					else

						//Update the Error Margin
						ErrMg_ += twoDiffY_;
				}

				//else
			}
			else {
				//Calculate the starting Error Margin
				int ErrMg_ = 2 * Dx_ - Dy_;

				//Calculate the Ending Point
				const int eY_ = (int)floorf(p2.y);

				//Calculate 2Dx and 2Dx - 2Dy to avoid computing it everytime is needed
				const unsigned twoDiffX_ = 2 * Dx_, diffDP_ = twoDiffX_ - 2 * Dy_;

				//Until we reach the end of the line
				for (int x = (int)floorf(p1.x), y =
					(int)floorf(p1.y); y != eY_; y += stepY) {
					//set the corresponding pixel
					FrameBuffer::SetPixel(x, y, 0, (unsigned char)c.r,
						(unsigned char)c.g, (unsigned char)c.b);

					//if the error margin is greater than 0
					if (ErrMg_ > 0)

						//Update the X coordinate
						x += stepX, ErrMg_ += diffDP_;

					//else
					else
						ErrMg_ += twoDiffX_;
				}
			}
		}
	}
}