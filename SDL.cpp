#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"
using namespace std;
using namespace kevin;




int main(int argc, char* argv[]) {

    srand(time(NULL)); //generates new num everytime for our random num gen

    Screen screen;

    if (screen.init() == false) {
        cout << "Error" << endl;
    }

    Swarm swarm;
    
    
    while (true) { //game loop ... loops while quit(false) is false
        //updates particles

        const Particle* const pParticles = swarm.getParticles(); // to get particles

        //draws particles

        int elapsedTime = SDL_GetTicks(); //number of ms since program started

        screen.boxBlur();
        
        //screen.clearScreen();
        swarm.update(elapsedTime);

        unsigned char green = (1 + cos(elapsedTime * 0.00015)) * 128; //sin returns value in range of -1 to 1 ... smoothly change colors .. value increases as program runs ... unsigned char only store 255 just in case number go up over
        unsigned char red = (1 + sin(elapsedTime * 0.0002)) * 128;
        unsigned char blue = (1 + sin(elapsedTime * 0.0003)) * 128;

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2; //maps to screen, instead of range -1 to +1, the +1 chamnges it from 0 to 2, and then half screen width since going form 0-2
            int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT/2; //same ^ for y ... both screen width so its not oval since both ranges are da same... the end puts it halfway down the screen

            screen.setPixel(x, y, red, green, blue);
        }

        

        

        //if (green > max) max = green; check for max 


        //cout << green << endl;

        /*for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
            for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
                screen.setPixel(x, y, red, green, blue);  //x coord, y coord, rgb
            }
        }*/

        
        //draw to screen
        screen.update();

        //checks for messages/events (for ex user click)
        if (screen.proccessEvents() == false) {
            break;
        }
    }

    screen.close();

    return 0;
}