//
//  GFXSystem
//  3D Rasterizer
//
//  Created by Diego Revilla on 28/02/21.
//  Copyright � 2021 . All rights reserved.
//

#include "GFXSystem.h"

// ------------------------------------------------------------------------
/*! Get Instance
*
*   Gets an instance of the GFXSystem class (singleton)
*/ //----------------------------------------------------------------------
GFXSystem& GFXSystem::GetInstance() noexcept {

	static GFXSystem sys_;

	return sys_;

}

// ------------------------------------------------------------------------
/*! Default Constructor
*
*   EMPTY
*/ //----------------------------------------------------------------------
GFXSystem::GFXSystem() noexcept :
	mPostProcess(nullptr) {}

// ------------------------------------------------------------------------
/*! GfxViewportMatrix
*
*   Returns a reference to the viewport matrix
*/ //----------------------------------------------------------------------
Matrix4 GFXSystem::GetViewportMatrix() noexcept {
	return mViewportMatrix;
}

// ------------------------------------------------------------------------
/*! GfxProjectionMatrix
*
*   Returns a reference to the projection matrix
*/ //----------------------------------------------------------------------
Matrix4 GFXSystem::GetProjectionMatrix() noexcept {
	return mProjectionMatrix;
}

// ------------------------------------------------------------------------
/*! GfxCameraMatrix
*
*   Returns a reference to the camera matrix
*/ //----------------------------------------------------------------------
Matrix4 GFXSystem::GetCameraMatrix() noexcept {
	return mCameraMatrix;
}

// ------------------------------------------------------------------------
/*! GfxCameraMatrix
*
*   Returns a reference to the camera matrix
*/ //----------------------------------------------------------------------
Graphics::PostProcess* GFXSystem::GetPostProcess() noexcept {
	return mPostProcess;
}

// ------------------------------------------------------------------------
/*! SetCameraMatrix
*
*   Returns a reference to the camera matrix
*/ //----------------------------------------------------------------------
void GFXSystem::SetViewportMatrix(const Matrix4& mtr) noexcept {
	mViewportMatrix = mtr;
}

// ------------------------------------------------------------------------
/*! SetCameraMatrix
*
*   Returns a reference to the camera matrix
*/ //----------------------------------------------------------------------
void GFXSystem::SetProjectionMatrix(const Matrix4& mtr) noexcept {
	mProjectionMatrix = mtr;
}

// ------------------------------------------------------------------------
/*! SetCameraMatrix
*
*   Returns a reference to the camera matrix
*/ //----------------------------------------------------------------------
void GFXSystem::SetCameraMatrix(const Matrix4& mtr) noexcept {
	mCameraMatrix = mtr;
}

void GFXSystem::SetCamera(Camera* cam) noexcept {
	mCamera = cam;
}

Camera* GFXSystem::GetCamera() noexcept {
	return mCamera;
}

// ------------------------------------------------------------------------
/*! SetCameraMatrix
*
*   Returns a reference to the camera matrix
*/ //----------------------------------------------------------------------
void GFXSystem::SetPostProcess(Graphics::PostProcess* pp) noexcept {
	mPostProcess = pp;
}