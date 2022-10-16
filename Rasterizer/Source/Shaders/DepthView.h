//
//  DepthView.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 12/02/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _DEPTH_VIEW__H_
#define _DEPTH_VIEW__H_

#include "../../Engine/Graphics/Types/PostProcess.h"

namespace Shaders {
	class DepthView : public Graphics::PostProcess {
	public:
		const Graphics::Color process(const Graphics::Color& col, const float z) noexcept;
	};
}

#endif