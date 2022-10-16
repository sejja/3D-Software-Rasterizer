//
//  PostProcess.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 12/02/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _POST_PROCESS__H_
#define _POST_PROCESS__H_

#include "../Color.h"

namespace Graphics {
	class PostProcess {
	public:
		const virtual Color process(const Color& col, const float z) noexcept = 0;
	};
}

#endif