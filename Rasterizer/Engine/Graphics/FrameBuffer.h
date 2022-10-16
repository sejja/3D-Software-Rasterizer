//
//  FrameBuffer.h
//  3D Rasterizer
//
//  Created by Diego Revilla on 12/03/21.
//  Copyright � 2021 . All rights reserved.
//

#ifndef _FRAME_BUFFER__H_
#define _FRAME_BUFFER__H_

class FrameBuffer {
public:
	static void Init(int w, int h);
	static void Free();

	static void Clear(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
	static void SetPixel(unsigned x, unsigned y, float z, unsigned char r, unsigned char g, unsigned char b);
	static float GetPixel(unsigned x, unsigned y, unsigned char& r, unsigned char& g, unsigned char& b);
	static int  GetWidth() { return width; }
	static int  GetHeight() { return height; }

private:
	static unsigned width;
	static unsigned height;
	static unsigned char* imageData;
	static float* depthbuffer;
};

#endif