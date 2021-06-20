#include "Particle.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
namespace kevin {

Particle::Particle(): m_x(0), m_y(0) { //starts from center

	Init();

	/*m_x = (2.0 * rand() / RAND_MAX) - 1; //random number ... defualt will be from 0 to 1... this is fro -1 to 1
	//for coordinate plane system from -1 to +1

	m_y = (2.0 * rand() / RAND_MAX) - 1;*/

	/*m_xspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1); //rand from -1 to +1
	m_yspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1); //this randomizes their speed but this initializes the particle's speed to each particle will nt chamnge speed*/

}

void Particle::Init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI * rand()) / RAND_MAX; //uses radians ... 2 pi is one circle degrees
	m_speed = (0.04 * rand()) / RAND_MAX;
	m_speed *= m_speed; //squares speed
}

void Particle::update(int interval) { //allows pixels to change position
	/*const double xspeed = 0.01 * (((2.0 * rand()) / RAND_MAX) - 1); //rand from -1 to +1
	const double yspeed = 0.01 * (((2.0 * rand()) / RAND_MAX) - 1);*///this randomizes their speed 
	/*m_x += m_xspeed;
	m_y += m_yspeed;
	*/
	m_direction += interval * 0.00035;

	double x_speed = m_speed * cos(m_direction); //xspeed is speed times cos direction
	double y_speed = m_speed * sin(m_direction); //yspeed is speed times cos direction

	m_x += x_speed * interval;  //runs consistent speed
	m_y += y_speed * interval; //runs consistent speed

	/*if (m_x < -1.0 || m_x >= 1.0) { //in a plane -1 to 1
		x_speed = -x_speed;
	}
	if (m_y < -1.0 || m_y >= 1.0) { //in a plane -1 to 1
		y_speed = -y_speed;
	}*/

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		Init();
	}
	if (rand() < RAND_MAX / 100) {
		Init();
	}
}





}