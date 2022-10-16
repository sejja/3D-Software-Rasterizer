//
//  Camera.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 25/02/21.
//  Copyright � 2021 . All rights reserved.
//

#include "../System/GFXSystem.h"
#include "Camera.h"
#include <cmath>
#include "../Math/MathUtilities.h"

// ------------------------------------------------------------------------
/*! Compute View Matrix
*
*   Computes the Camera View Matrix using the General Rotation Method
*/ //----------------------------------------------------------------------
Matrix4 Camera::ComputeViewMatrix() const {
	return { mRightVector.x, mRightVector.y, mRightVector.z, -(
			mRightVector.x * mPosition.x + mRightVector.y * mPosition.y +
			mRightVector.z * mPosition.z), mUpVector.x, mUpVector.y, mUpVector.z,
			-(mUpVector.x * mPosition.x + mUpVector.y * mPosition.y + mUpVector.z * mPosition.z),
			-mViewVector.x, -mViewVector.y, -mViewVector.z, -(-mViewVector.x * mPosition.x +
			-mViewVector.y * mPosition.y + -mViewVector.z * mPosition.z), 0, 0, 0, 1 };
}

// ------------------------------------------------------------------------
/*! Compute Camera Frustrum
*
*   Computes the Frustrum for Culling
*/ //----------------------------------------------------------------------
void Camera::ComputeCameraFrustrum() {
	Matrix4 M_ = GFX->GetProjectionMatrix() * GFX->GetCameraMatrix();
	mLeftPlane = -M_.row(0) - M_.row(3);
	mRightPlane = M_.row(0) - M_.row(3);
	mBottomPlane = -M_.row(1) - M_.row(3);
	mTopPlane = M_.row(1) - M_.row(3);
	mNearPlane = -M_.row(2) - M_.row(3);
	mFarPlane = M_.row(2) - M_.row(3);
}

// ------------------------------------------------------------------------
/*! Cull Point Frustrum
*
*   Should we render this point?
*/ //----------------------------------------------------------------------
bool Camera::CullPointFrustrum(const Point4& point) {
	if (IsBehindNearPlane(point)) return true;
	if (IsBehindFarPlane(point)) return true;
	if (IsBehindLeftPlane(point)) return true;
	if (IsBehindRightPlane(point)) return true;
	if (IsBehindTopPlane(point)) return true;
	if (IsBehindBottomPlane(point)) return true;
	return false;
}

// ------------------------------------------------------------------------
/*! Is Behing Near Plane
*
*   Tells if a point is behind the Near Plane
*/ //----------------------------------------------------------------------
bool Camera::IsBehindNearPlane(const Point4& point) {
	return mNearPlane.x * point.x + mNearPlane.y * point.y +
		mNearPlane.z * point.z + mNearPlane.w > 0;
}

// ------------------------------------------------------------------------
/*! Is Behing Far Plane
*
*   Tells if a point is behind the Far Plane
*/ //----------------------------------------------------------------------
bool Camera::IsBehindFarPlane(const Point4& point) {
	return mFarPlane.x * point.x + mFarPlane.y * point.y +
		mFarPlane.z * point.z + mFarPlane.w > 0;
}

// ------------------------------------------------------------------------
/*! Is Behing Left Plane
*
*   Tells if a point is behind the Left Plane
*/ //----------------------------------------------------------------------
bool Camera::IsBehindLeftPlane(const Point4& point) {
	return mLeftPlane.x * point.x + mLeftPlane.y * point.y +
		mLeftPlane.z * point.z + mLeftPlane.w > 0;
}

// ------------------------------------------------------------------------
/*! Is Behing Right Plane
*
*   Tells if a point is behind the Right Plane
*/ //----------------------------------------------------------------------
bool Camera::IsBehindRightPlane(const Point4& point) {
	return mRightPlane.x * point.x + mRightPlane.y * point.y +
		mRightPlane.z * point.z + mRightPlane.w > 0;
}

// ------------------------------------------------------------------------
/*! Is Behing Top Plane
*
*   Tells if a point is behind the Top Plane
*/ //----------------------------------------------------------------------
bool Camera::IsBehindTopPlane(const Point4& point) {
	return mTopPlane.x * point.x + mTopPlane.y * point.y +
		mTopPlane.z * point.z + mTopPlane.w > 0;
}

// ------------------------------------------------------------------------
/*! Is Behing Bottom Plane
*
*   Tells if a point is behind the Bottom Plane
*/ //----------------------------------------------------------------------
bool Camera::IsBehindBottomPlane(const Point4& point) {
	return mBottomPlane.x * point.x + mBottomPlane.y * point.y +
		mBottomPlane.z * point.z + mBottomPlane.w > 0;
}