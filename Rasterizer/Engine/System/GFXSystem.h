//
//  GFXSystem
//  3D Rasterizer
//
//  Created by Diego Revilla on 28/02/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _GFX_SYSTEM__H_
#define _GFX_SYSTEM__H_

#include "../Math/Matrix4.h"
#include "../Graphics/Types/PostProcess.h"
#include "../Types/Camera.h"

class GFXSystem {
public:
	static GFXSystem& GetInstance() noexcept;
	Matrix4 GetViewportMatrix() noexcept;
	Matrix4 GetProjectionMatrix() noexcept;
	Matrix4 GetCameraMatrix() noexcept;
	Graphics::PostProcess* GetPostProcess() noexcept;
	void SetViewportMatrix(const Matrix4& mtr) noexcept;
	void SetProjectionMatrix(const Matrix4& mtr) noexcept;
	void SetCameraMatrix(const Matrix4& mtr) noexcept;
	void SetCamera(Camera* cam) noexcept;
	Camera* GetCamera() noexcept;
	void SetPostProcess(Graphics::PostProcess* pp) noexcept;

protected:
	GFXSystem() noexcept;

private:
	Matrix4 mViewportMatrix;
	Matrix4 mProjectionMatrix;
	Matrix4 mCameraMatrix;
	Camera* mCamera;
	Graphics::PostProcess* mPostProcess;

};

#define GFX (&GFXSystem::GetInstance())

#endif