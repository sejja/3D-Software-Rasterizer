//
//  FrameBuffer.cpp
//  3D Rasterizer
//
//  Created by Diego Revilla on 30/01/21.
//  Copyright � 2021 . All rights reserved.
//

#include "FrameBuffer.h"
#include <limits>

unsigned FrameBuffer::width = 0;
unsigned FrameBuffer::height = 0;
unsigned char* FrameBuffer::imageData = nullptr;
float* FrameBuffer::depthbuffer = nullptr;

// ------------------------------------------------------------------------
/*! Init
*
*   Allocates a new frameBuffer
*/ // ---------------------------------------------------------------------
void FrameBuffer::Init(int w, int h) {
	// free any data
	Free();

	width = w;
	height = h;
	imageData = new unsigned char[size_t(width) * size_t(height) * size_t(3)];
	depthbuffer = new float[size_t(width) * size_t(height)];
}

// ------------------------------------------------------------------------
/*! Free
*
*   Frees the FrameBuffer
*/ // ---------------------------------------------------------------------
void FrameBuffer::Free() {
	if (imageData)
		delete[] imageData;

	if (depthbuffer)
		delete[] depthbuffer;
}

// ------------------------------------------------------------------------
/*! Clear
*
*   Clears the Frame Buffer
*/ // ---------------------------------------------------------------------
void FrameBuffer::Clear(unsigned char r, unsigned char g, unsigned char b) {
	//iterate through the height
	for (size_t y = 0; y < height; ++y) {
		//And the width
		for (size_t x = 0; x < width; ++x) {
			size_t idx = y * width + x;
			size_t i = 3 * idx;
			imageData[i] = r;
			imageData[i + 1] = g;
			imageData[i + 2] = b;
			depthbuffer[idx] = 1;
		}
	}
}

// ------------------------------------------------------------------------
/*! Set Pixel
*
*   Sets a certain pixel on the frame buffer
*/ // ---------------------------------------------------------------------
void FrameBuffer::SetPixel(unsigned x, unsigned y, float z, unsigned char r, unsigned char g, unsigned char b) {
	//Set a pixel
	if (x < width && y < height) {
		unsigned idx = y * width + x;

		if (z < depthbuffer[idx]) {
			unsigned i = 3 * idx;
			imageData[i++] = r;
			imageData[i++] = g;
			imageData[i] = b;
			depthbuffer[idx] = z;
		}
	}
}

// ------------------------------------------------------------------------
/*! Get Pixel
*
*   Gets the pixel from the framebuffer given the coordinates
*/ // ---------------------------------------------------------------------
float FrameBuffer::GetPixel(unsigned x, unsigned y, unsigned char& r, unsigned char& g, unsigned char& b) {
	unsigned idx = y * width + x;
	unsigned i = 3 * idx;
	r = imageData[i++];
	g = imageData[i++];
	b = imageData[i];

	return depthbuffer[idx];

}