//
//  Vertex.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 30/01/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _VERTEX__H_
#define _VERTEX__H_

#include "Point4.h"
#include "../Graphics/Color.h"

struct Vertex {

	Point4 mPosition;
	Graphics::Color mColor;

};

#endif