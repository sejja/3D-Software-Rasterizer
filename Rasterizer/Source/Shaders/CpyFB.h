//
//  CpyFB.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 12/02/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _CPY_FB__H_
#define _CPY_FB__H

#include "../../Engine/Graphics/Types/PostProcess.h"

namespace Shaders {

	class CpyFB : public Graphics::PostProcess {
	public:
		const Graphics::Color process(const Graphics::Color& col, const float) noexcept;
	};
}

#endif