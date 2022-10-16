//
//  DepthView.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 12/02/21.
//  Copyright � 2021 . All rights reserved.
//

#include "DepthView.h"

namespace Shaders {
	const Graphics::Color DepthView::process(const Graphics::Color& col, const float z) noexcept {
		const float f_ = (z + 1) * 127;

		return { f_, f_, f_ };
	}
}