#include <SFML/Graphics.hpp>
#include "../Graphics/FrameBuffer.h"
#include "../Graphics/Rasterizer/DrawTriangle.h"
#include "../Math/Vertex.h"
#include "../../Source/Scene.h"
#include "../System/GFXSystem.h"
// Convert the custom framebuffer to SFML format
void ConvertFrameBufferToSFMLImage(sf::Image& image)
{
	int w = FrameBuffer::GetWidth();
	int h = FrameBuffer::GetHeight();

	Graphics::PostProcess* post_ = GFX->GetPostProcess();

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			unsigned char r, b, g;
			float z = FrameBuffer::GetPixel(x, y, r, g, b);
			Graphics::Color c = post_->process({ static_cast<float>(r),
				static_cast<float>(g), static_cast<float>(b) }, z);
			image.setPixel(x, h - y - 1, sf::Color(static_cast<unsigned char>(c.r),
				static_cast<unsigned char>(c.g), static_cast<unsigned char>(c.b)));

		}
	}
}

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D Rasterizer");

	FrameBuffer::Init(WIDTH, HEIGHT);

	// Generate image and texture to display
	sf::Image   image;
	sf::Texture texture;
	sf::Sprite  sprite;
	texture.create(WIDTH, HEIGHT);
	image.create(WIDTH, HEIGHT, sf::Color::White);

	Scene::Init();

	// Init the clock
	sf::Clock clock;
	while (window.isOpen())
	{
		// Handle input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		Scene::Update();
		// Show image on screen
		ConvertFrameBufferToSFMLImage(image);

		texture.update(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();
		FrameBuffer::Clear(255, 255, 255);
	}

	Scene::Shutdown();
	FrameBuffer::Free();

	return 0;
}