//
//  Box.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 9/02/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _GAMEOBJECT__H_
#define _GAMEOBJECT__H_

#include "GameObject.h"

class Box : public GameObject {

public:
	void Render(const bool b,
		const Matrix4& Transform = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
		noexcept override;
};

#endif