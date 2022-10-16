//
//  CpyFB.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 12/02/21.
//  Copyright � 2021 . All rights reserved.
//

#include "CpyFB.h"

namespace Shaders {
	const Graphics::Color CpyFB::process(const Graphics::Color& col, const float) noexcept {
		return col;
	}
}