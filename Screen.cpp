#include "Screen.h"
namespace kevin {
	Screen::Screen() :
		m_window(NULL),	m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_buffer2(NULL) {
        	
	};
	bool Screen::init() {
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        
            return false; //error code
        }

        m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // name of window, position, position, width, height, how window should be

        if (m_window == NULL) { //if window has nothing it quits
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC); //renders window with framerate vsync
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT); //rgba8888 allows all colors to be viewed with 8888 bits.. textureaccess static allows loop to write diurcetly to the texture
        //rgba = red green blue and alpha ... for 1 pix = 4 bytes ... need int size of 32 bytes to display 1 pixel
        if (m_renderer == NULL) {
           
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        if (m_texture == NULL) {
          
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //int that is 32 bytes... allocates [800*600] bytes of mem
        m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); //buffer, number of bytes set to memory (255 max for white) OR hexadecimal value, number of bytes set
        memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
   
        //m_buffer[30000] = 0xFFFFFFFF; // FF is max ... first 2 for red, next for blue, etc

        /*for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
            m_buffer[i] = 0xFFFF00FF; //8 0 = 128... half of FF
        }*/

		return true;

	}; //false if fails true if good


    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return; //prevents pixels from being plotted out of screen

        Uint32 color = 0;

        color += red;
        color <<= 8; //move values in color by 8 bits, 1 byte since 1 byte = 8 bits
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF; //alpha

        m_buffer[(y * SCREEN_WIDTH) + x] = color; //transforms x y coordinates into the buffer
    }

    void Screen::update() {
        SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32)); //texture, null to update everything, buffer pixel data, number of bytes per row... pixel width * number of bytes per pixel
        SDL_RenderClear(m_renderer); //passes buffer to m_renderer
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); //render, texture, use entire m_renderer, use entire texture
        SDL_RenderPresent(m_renderer); //presenting to window
    }

    void Screen::boxBlur() {
        Uint32* temp = m_buffer;
        m_buffer = m_buffer2;
        m_buffer2 = temp;

        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {

                /*
                 * 0 0 0
                 * 0 1 0
                 * 0 0 0
                 */

                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        int currentX = x + col;
                        int currentY = y + row;
                        
                        if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                            Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }

                Uint8 red = redTotal / 9;
                Uint8 green = greenTotal / 9;
                Uint8 blue = blueTotal / 9;

                setPixel(x, y, red, green, blue);
            }
        }
    }

    void Screen::clearScreen() {
        memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); //reinitalizes the buffer to clear screen
        memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    }

	bool Screen::proccessEvents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) { //function needs adress of event ... will keep itterating as long as there is an event to be processed and gets info about event
            if (event.type == SDL_QUIT) { //quits if user inputs for program to close
                return false;
            }
        }
		return true;
	};
	void Screen::close() {
        delete[] m_buffer;
        delete[] m_buffer2;
        SDL_DestroyTexture(m_texture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window); //destroys window
        SDL_Quit(); //quits window
	};




}