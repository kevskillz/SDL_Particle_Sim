#pragma once
#include <SDL.h>
#include <iostream>
namespace kevin {
	class Screen
	{
	public:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;
	private:
		//member variuables prefix m_ to be clear
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		Uint32* m_buffer;
		Uint32* m_buffer2;
	public:
		Screen();
		bool init(); //false if fails true if good
		bool proccessEvents();
		void close();
		void update();
		void clearScreen();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue); //uint8 = unsigned char
		void boxBlur();
	};
}

