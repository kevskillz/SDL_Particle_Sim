#pragma once
#include "Particle.h"
namespace kevin {
	
	class Swarm
	{
	public:
		const static int NPARTICLES = 5000; //# of particles

	private:
		Particle* m_pParticles; //pointer to particle class
		int lastTime;

	public:
		Swarm();
		~Swarm();
		void update(int elapsed);
		const Particle* const getParticles() { return m_pParticles; }; //const pointer to Particle thats const
	};

}