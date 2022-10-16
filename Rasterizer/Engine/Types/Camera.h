//
//  Camera.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 25/02/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _CAMERA__H_
#define _CAMERA__H_

#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"

class Vector4;

class Camera {
public:
	Matrix4 ComputeViewMatrix() const;
	void ComputeCameraFrustrum();
	bool CullPointFrustrum(const Point4& point);
	bool IsBehindNearPlane(const Point4& point);
	bool IsBehindFarPlane(const Point4& point);
	bool IsBehindLeftPlane(const Point4& point);
	bool IsBehindRightPlane(const Point4& point);
	bool IsBehindTopPlane(const Point4& point);
	bool IsBehindBottomPlane(const Point4& point);
	Vector4 mPosition;
	Vector4 mViewVector;
	Vector4 mRightVector;
	Vector4 mUpVector;
	Vector4 mLeftPlane;
	Vector4 mRightPlane;
	Vector4 mBottomPlane;
	Vector4 mTopPlane;
	Vector4 mNearPlane;
	Vector4 mFarPlane;

};

#endif