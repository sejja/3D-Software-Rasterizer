//
//  Scene.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 11/02/21.
//  Copyright � 2021 . All rights reserved.
//

#include "Scene.h"
#include "../Engine/IO/Parser.h"
#include "../Engine/Types/Box.h"
#include "SFML/Graphics.hpp"
#include "../Engine/Math/MathUtilities.h"
#include "../Engine/Types/Camera.h"
#include "../Engine/System/GFXSystem.h"
#include "Shaders/CpyFB.h"
#include "Shaders/DepthView.h"
#include <functional>
#include "../Engine/Graphics/Rasterizer/DrawTriangle.h"

namespace Scene {
	static bool wireframe = false;
	static Camera Cam;
	static float g_camheight = 20;
	static float g_camdistance = 100;
	static Shaders::CpyFB g_copyframebuffer_sh;
	static Shaders::DepthView g_depthview_sh;
	static std::vector<GameObject*> sceneobjects;

	enum class Scene_state : int { Fixed, ThirdPerson, FirstPerson };
	static Scene_state g_state = Scene_state::Fixed;

	// ------------------------------------------------------------------------
	/*! Get Object By Name
	*
	*   Gets an Object on the Scene by it's name
	*/ //----------------------------------------------------------------------
	GameObject* GetObjectByName(const char* str) {
		std::function<GameObject* (GameObject* b)> browseChild = [&](GameObject* b) {
			//Iterate through it's components
			for (auto& x : b->Components) {
				if (x->mName == str) return x;
				else {
					GameObject* child = browseChild(x);
					if (child) return child;
				}
			}

			return (GameObject*)nullptr;
		};

		//Iterate through all the scene objects and recursively destroy
		//them and their children
		for (auto& x : sceneobjects) {
			if (x->mName == str) return x;
			else {
				GameObject* child = browseChild(x);
				if (child) return child;
			}
		}

		return nullptr;
	}

	// ------------------------------------------------------------------------
	/*! Init
	*
	*   Init the scene
	*/ //----------------------------------------------------------------------
	void Init() {
		WorldParser::LoadDataFromFile("input.txt");

		//For every parsed object
		for (auto& x : WorldParser::sceneobjects) {

			//Create a new instance
			Box* newobject = new Box;
			newobject->mName = x.mName;

			//Set the proper transformation
			newobject->mPosition = { x.pos.x, x.pos.y, x.pos.z, x.pos.w };
			newobject->mRotation = { x.rot.x, x.rot.y, x.rot.z, x.rot.w };
			newobject->mScale = { x.sca.x, x.sca.y, x.sca.z, x.sca.w };
			newobject->mUp = { 0, 1, 0, 0 };
			newobject->mView = { 0, 0, 1, 0 };
			newobject->mRight = newobject->mView.Cross(newobject->mUp);

			//Try to find it's parent
			auto it = GetObjectByName(x.parent.c_str());

			//If we didn't find it, that means it's a new object
			if (it)
				it->Components.push_back(newobject);

			//else, push it into it's parent's child list
			else
				sceneobjects.push_back(newobject);
		}

		Cam.mUpVector = { 0, 1, 0, 0 };
		GFX->SetProjectionMatrix(Matrix4::Projection(WorldParser::left, WorldParser::right,
			WorldParser::bottom, WorldParser::top, WorldParser::nearPlane,
			WorldParser::farPlane, WorldParser::focal * 2));
		GFX->SetPostProcess(&g_copyframebuffer_sh);
		GFX->SetCamera(&Cam);
	}

	// ------------------------------------------------------------------------
	/*! Update
	*
	*   Updates the scene
	*/ //----------------------------------------------------------------------
	void Update() {
		auto body_ptr = reinterpret_cast<Box*>(GetObjectByName("body"));

		//If pressed 1
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			wireframe = true;
			GFX->SetPostProcess(reinterpret_cast<Graphics::PostProcess*>(&g_copyframebuffer_sh));
		}

		//If pressed 2
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			wireframe = false;
			GFX->SetPostProcess(reinterpret_cast<Graphics::PostProcess*>(&g_copyframebuffer_sh));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
			wireframe = false;
			GFX->SetPostProcess(reinterpret_cast<Graphics::PostProcess*>(&g_depthview_sh));
		}

		//If pressed A
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			body_ptr->mUp = Matrix4::RotateAxis(body_ptr->mView, -0.1f) * body_ptr->mUp;
			body_ptr->mRight = Matrix4::RotateAxis(body_ptr->mView, -0.1f) * body_ptr->mRight;
		}

		//If pressed D
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			body_ptr->mUp = Matrix4::RotateAxis(body_ptr->mView, 0.1f) * body_ptr->mUp;
			body_ptr->mRight = Matrix4::RotateAxis(body_ptr->mView, 0.1f) * body_ptr->mRight;
		}

		//If pressed A
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			body_ptr->mView = Matrix4::RotateAxis(body_ptr->mUp, -0.1f) * body_ptr->mView;
			body_ptr->mRight = Matrix4::RotateAxis(body_ptr->mUp, -0.1f) * body_ptr->mRight;
		}

		//If pressed D
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			body_ptr->mView = Matrix4::RotateAxis(body_ptr->mUp, 0.1f) * body_ptr->mView;
			body_ptr->mRight = Matrix4::RotateAxis(body_ptr->mUp, 0.1f) * body_ptr->mRight;
		}

		//If pressed A
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			body_ptr->mView = Matrix4::RotateAxis(body_ptr->mRight, -0.1f) * body_ptr->mView;
			body_ptr->mUp = Matrix4::RotateAxis(body_ptr->mRight, -0.1f) * body_ptr->mUp;
		}

		//If pressed D
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			body_ptr->mView = Matrix4::RotateAxis(body_ptr->mRight, 0.1f) * body_ptr->mView;
			body_ptr->mUp = Matrix4::RotateAxis(body_ptr->mRight, 0.1f) * body_ptr->mUp;
		}

		//If pressed space
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			body_ptr->mPosition += body_ptr->mView;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) g_state = Scene_state::FirstPerson;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) g_state = Scene_state::ThirdPerson;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) g_state = Scene_state::Fixed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) g_camheight++;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) g_camheight--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) g_camdistance--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) g_camdistance++;

		/*FIRST VIEWPORT*/

		Cam.mPosition = body_ptr->mPosition + body_ptr->mRight * g_camdistance;
		Cam.mViewVector = -body_ptr->mRight;
		Cam.mRightVector = body_ptr->mView;
		Cam.mUpVector = body_ptr->mUp;
		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();
		GFX->SetViewportMatrix(Matrix4::Viewport(1280 / 2, 720 / 2, 2, 2));

		Graphics::Rasterizer::DrawLine({ 0, 720 / 2, 0, 0 }, { 1280, 720 / 2, 0, 0 }, { 0, 0, 0 });
		Graphics::Rasterizer::DrawLine({ 1280 / 2, 0, 0, 0 }, { 1280 / 2, 720, 0, 0 }, { 0, 0, 0 });

		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();

		//Render all body objects
		for (auto& x : sceneobjects) {
			Box* box = dynamic_cast<Box*>(x);
			if (box)
				box->Render(!wireframe);
		}

		body_ptr->Render(!wireframe);


		/*SECOND VIEWPORT*/

		Cam.mPosition = body_ptr->mPosition;
		Cam.mRightVector = body_ptr->mRight;
		Cam.mUpVector = body_ptr->mUp;
		Cam.mViewVector = body_ptr->mView;
		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();
		GFX->SetViewportMatrix(Matrix4::Viewport(1280 / 2, 720 / 2, 2, 2) * Matrix4::Translate({ 2, 0, 0, 0 }));

		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();

		//Render all body objects
		for (auto& x : sceneobjects) {
			Box* box = dynamic_cast<Box*>(x);
			if (box)
				box->Render(!wireframe);
		}

		/*THIRD VIEWPORT*/

		Cam.mPosition = body_ptr->mPosition - body_ptr->mView * g_camdistance + body_ptr->mUp *
			g_camheight;
		Cam.mViewVector = (body_ptr->mPosition - Cam.mPosition) / (body_ptr->mPosition - Cam.mPosition).Length();
		Cam.mRightVector = Cam.mViewVector.Cross(body_ptr->mUp);
		Cam.mUpVector = Cam.mRightVector.Cross(Cam.mViewVector);
		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();
		GFX->SetViewportMatrix(Matrix4::Viewport(1280 / 2, 720 / 2, 2, 2) * Matrix4::Translate({ 0, 2, 0, 0 }));

		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();

		//Render all body objects
		for (auto& x : sceneobjects) {
			Box* box = dynamic_cast<Box*>(x);
			if (box)
				box->Render(!wireframe);
		}

		/*FOURTH VIEWPORT*/

		Cam.mPosition = body_ptr->mPosition + body_ptr->mUp * g_camheight * 6;
		Cam.mViewVector = -body_ptr->mUp;
		Cam.mRightVector = body_ptr->mRight;
		Cam.mUpVector = body_ptr->mView;
		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();
		GFX->SetViewportMatrix(Matrix4::Viewport(1280 / 2, 720 / 2, 2, 2) * Matrix4::Translate({ 2, 2, 0, 0 }));

		GFX->SetCameraMatrix(Cam.ComputeViewMatrix());
		Cam.ComputeCameraFrustrum();

		//Render all body objects
		for (auto& x : sceneobjects) {
			Box* box = dynamic_cast<Box*>(x);
			if (box)
				box->Render(!wireframe);
		}
	}

	// ------------------------------------------------------------------------
	/*! Shutdown
	*
	*   Frees all the resources
	*/ //----------------------------------------------------------------------
	void Shutdown() {

	}
}