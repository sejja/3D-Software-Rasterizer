//
//  Box.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 10/02/21.
//  Copyright � 2021 . All rights reserved.
//

#include "Box.h"
#include "../Math/Vector4.h"
#include "../Graphics/Rasterizer/DrawTriangle.h"
#include "../IO/Parser.h"
#include "../Math/Vertex.h"
#include "../System/GFXSystem.h"
#include <utility>

struct Face {
	Point4 Points[3];
	Point4 Color;
	bool behind[3];
};

std::vector<Point4> Clip(Face& face);

// ------------------------------------------------------------------------
/*! Render
*
*   Renders a Cube and it's children
*/ //----------------------------------------------------------------------
void Box::Render(const bool solid, const Matrix4& mtr) noexcept {
	std::pair<Point4, bool> Points[8];

	const Matrix4 Transform = Matrix4::Translate(mPosition) *
		Matrix4::OrthogonalRotation(mView, mUp, -mRight);

	//Transform all the vertices
	for (size_t i = 0, size = WorldParser::vertices.size(); i < size; i++) {
		auto x = WorldParser::vertices[i];
		x = mtr * Transform * Matrix4::Scale(mScale) * x;
		if (GFX->GetCamera()->CullPointFrustrum(x))
			Points[i].second = false;
		else
			Points[i].second = true;
		Points[i].first = x;
	}

	std::vector<Face> facestorender;

	//Draw all the faces
	for (size_t i = 0, size = WorldParser::faces.size(); i < size; i++) {
		auto& face = WorldParser::faces[i].indices;
		Point4& color = WorldParser::colors[i];

		//If the face hasn't been culled
		if (Points[face[0]].second || Points[face[1]].second || Points[face[2]].second) {
			facestorender.push_back({ {Points[face[0]].first, Points[face[1]].first,
				Points[face[2]].first}, color,
					{Points[face[0]].second, Points[face[1]].second, Points[face[2]].second} });
		}
	}

	//If we should draw filled triangles
	if (solid) {
		//Render all faces
		for (auto& x : facestorender) {
			std::vector<Point4> triangulatedvertices = Clip(x);

			const auto ftransform_ = [](Point4& v) {
				v = GFX->GetCameraMatrix() * v;
				v = GFX->GetProjectionMatrix() * v;
				v.x /= v.w, v.y /= v.w, v.z /= v.w;
				v.w /= v.w;
				v = GFX->GetViewportMatrix() * v;
			};

			auto& p0 = triangulatedvertices[0];
			auto& p1 = triangulatedvertices[1];
			auto& p2 = triangulatedvertices[2];

			ftransform_(p0);
			ftransform_(p1);
			ftransform_(p2);
			if (triangulatedvertices.size() > 3) ftransform_(triangulatedvertices[3]);

			const Vector4 v0 = p1 - p0;
			const Vector4 v1 = p2 - p0;
			Vector4 FaceNormal = v1.Cross(v0);
			FaceNormal.Normalize();
			Vector4 CameraPos = GFX->GetCamera()->mViewVector;
			CameraPos.z = CameraPos.z > 0 ? -CameraPos.z : CameraPos.z;

			//If we are rendering a front face
			if (FaceNormal.Dot(CameraPos) >= 0) {
				//If we did not generate extra geometry (had Clipped)
				if (triangulatedvertices.size() == 3)
					Graphics::Rasterizer::DrawTriangle(p0, p1, p2,
						{ x.Color.x, x.Color.y, x.Color.z });
				else {
					Graphics::Rasterizer::DrawTriangle(p0, p1, p2,
						{ x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawTriangle(p0, p2, triangulatedvertices[3],
						{ x.Color.x, x.Color.y, x.Color.z });
				}
			}
		}
	}
	else {
		//Render all faces
		for (auto& x : facestorender) {
			std::vector<Point4> triangulatedvertices = Clip(x);

			const auto ftransform_ = [](Point4& v) {
				v = GFX->GetCameraMatrix() * v;
				v = GFX->GetProjectionMatrix() * v;
				v.x /= v.w, v.y /= v.w, v.z /= v.w;
				v.w /= v.w;
				v = GFX->GetViewportMatrix() * v;
			};

			auto& p0 = triangulatedvertices[0];
			auto& p1 = triangulatedvertices[1];
			auto& p2 = triangulatedvertices[2];

			ftransform_(p0);
			ftransform_(p1);
			ftransform_(p2);
			if (triangulatedvertices.size() > 3)ftransform_(triangulatedvertices[3]);

			const Vector4 v0 = p1 - p0;
			const Vector4 v1 = p2 - p0;
			Vector4 FaceNormal = v1.Cross(v0);
			FaceNormal.Normalize();
			Vector4 CameraPos = GFX->GetCamera()->mViewVector;
			CameraPos.z = CameraPos.z > 0 ? -CameraPos.z : CameraPos.z;

			//If we are rendering a front face
			if (FaceNormal.Dot(CameraPos) >= 0) {
				//If we didn't generate extra geometry
				if (triangulatedvertices.size() == 3) {
					Graphics::Rasterizer::DrawLine(p0, p1, { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(p1, p2, { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(p2, p0, { x.Color.x, x.Color.y, x.Color.z });
				}
				else {
					Graphics::Rasterizer::DrawLine(p0, p1, { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(p1, p2, { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(p2, p0, { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(p0, p2, { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(p2, triangulatedvertices[3], { x.Color.x, x.Color.y, x.Color.z });
					Graphics::Rasterizer::DrawLine(triangulatedvertices[3], p0, { x.Color.x, x.Color.y, x.Color.z });
				}
			}
		}
	}

	//Render all the components
	for (auto& x : Components)
		x->Render(solid, mtr * Transform);
}

// ------------------------------------------------------------------------
/*! Line Plane intersection
*
*   Computes the intersection of a line and a plane
*/ //----------------------------------------------------------------------
bool linePlaneIntersection(Point4& out, const Point4& begin, const Point4& end, Vector4& normal) {
	const Vector4 beginv = { begin.x, begin.y, begin.z, 0 };
	const Vector4 endv = { end.x, end.y, end.z, 0 };

	auto temp = beginv + (endv - beginv) * (-normal.Dot(beginv) - normal.w) / (normal.Dot(endv - beginv));
	out.x = temp.x;
	out.y = temp.y;
	out.z = temp.z;
	out.w = 1;

	return true;
}

// ------------------------------------------------------------------------
/*! Find Intersection With Frustrum
*
*    Finds if there is any intersesction with the frustrum
*/ //----------------------------------------------------------------------
bool FindIntersectionWithFrustrum(const Point4& begin, const Point4& end, Point4& out) {
	Point4 output;
	Vector4 line = end - begin;
	auto cam = GFX->GetCamera();
	if (cam->IsBehindLeftPlane(begin) || cam->IsBehindLeftPlane(end))
		if (linePlaneIntersection(out, begin, end, cam->mLeftPlane)) return true;
	if (cam->IsBehindRightPlane(begin) || cam->IsBehindRightPlane(end))
		if (linePlaneIntersection(out, begin, end, cam->mRightPlane)) return true;
	if (cam->IsBehindTopPlane(begin) || cam->IsBehindTopPlane(end))
		if (linePlaneIntersection(out, begin, end, cam->mTopPlane)) return true;
	if (cam->IsBehindBottomPlane(begin) || cam->IsBehindBottomPlane(end))
		if (linePlaneIntersection(out, begin, end, cam->mBottomPlane)) return true;
	if (cam->IsBehindNearPlane(begin) || cam->IsBehindNearPlane(end))
		if (linePlaneIntersection(out, begin, end, cam->mNearPlane)) return true;
	if (cam->IsBehindFarPlane(begin) || cam->IsBehindFarPlane(end))
		if (linePlaneIntersection(out, begin, end, cam->mFarPlane)) return true;
	return false;
}

// ------------------------------------------------------------------------
/*! Clip
*
*    Clips a Face to generate new geometry clipped to the view frustrum
*/ //----------------------------------------------------------------------
std::vector<Point4> Clip(Face& face) {
	std::vector<Point4> outputvertices;
	Point4 temp_;
	for (int i = 0; i < 3; i++) {
		auto& p1 = face.Points[i];
		auto& p2 = face.Points[i == 2 ? 0 : i + 1];
		bool behind1 = face.behind[i];
		bool behind2 = face.behind[i == 2 ? 0 : i + 1];
		if (behind1 && behind2)
			outputvertices.push_back(p2);
		else if (behind1 && !behind2) {
			if (FindIntersectionWithFrustrum(p1, p2, temp_))
				outputvertices.push_back(temp_);
		}
		else if (!behind1 && behind2) {
			if (FindIntersectionWithFrustrum(p1, p2, temp_))
				outputvertices.push_back(temp_);
			outputvertices.push_back(p2);
		}
	}

	return outputvertices;
}