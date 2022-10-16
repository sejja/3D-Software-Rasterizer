//
//  DrawTriangle.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 30/01/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _DRAW_TRIANGLE__H_
#define _DRAW_TRIANGLE__H_

#include "../../Math/Vector4.h"
#include "../../Math/Vertex.h"
#include "../Color.h"

namespace Graphics {
	namespace Rasterizer {
		void DrawTriangle(const Point4& v0, const Point4& v1,
			const Point4& v2, const Color& c) noexcept;
		void DrawLine(const Point4& p1, const Point4& p2, const Color& c)
			noexcept;
	}
}

#endif