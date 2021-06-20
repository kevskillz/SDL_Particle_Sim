#pragma once
#include "Screen.h"
namespace kevin {

struct Particle // members are public by default in struct... only diff from class and strcut
{
//breaks encapsulation for effenciey 
	double m_x;
	double m_y; //change pixel positions gradually (thats why double and not int)
	double m_speed;
	double m_direction;
private:
	void Init();
	
public:
	Particle();
	void update(int interval);
};

}