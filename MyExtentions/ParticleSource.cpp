#include "ParticleSource.h"

namespace Project
{
	extern TextureManager textureManager;

	Particle ParticleSource::genParticle(void)
	{
		float angle = (rand() % 1571 / 1000.0) + (orientation - 0.785); // get a random angle in 90 degrees around orientation
		float mag = (rand() % 30 / 100.0) + 0.1; // get a random magnitude of velocity
		float yMove = (rand() % 50 / 1000.0) + 0.01; // get a random movment upwards

		Particle part = Particle(posX, posY, posZ, cosf(angle) * mag, yMove, sinf(angle) * mag);
		part.loadTextures(textureManager);

		return part;
	}

	ParticleSource::ParticleSource(float posX, float posY, float posZ, float orientation, int amount) : GLobject(posX, posY, posZ, degreeToRadian(orientation))
	{
		this->amount = amount;
		particles = new Particle[amount];
	}

	ParticleSource::~ParticleSource()
	{ 
		delete particles;
	}

	void ParticleSource::updateAnimation(void)
	{
		switch (animationState) {
			case 0: // normally we do noithing
				break;
			case 1:
				for (int i = 0; i < amount; i++) {
					particles[i].updateAnimation(); // move all the particles
					if (particles[i].finished()) { // if one finished stop
						animationState = 0;
						return;
					}
				}
				break;
		}
	}

	void ParticleSource::fire(void)
	{
		for (int i = 0; i < amount; i++) {
			particles[i] = genParticle();
		}
		animationState = 1;
	}

	void ParticleSource::display(float shadowMatrix[16])
	{
		if (animationState != 0) { // only display if we need too
			for (int i = 0; i < amount; i++) {
				particles[i].display(shadowMatrix);
			}
		}
	}

	void ParticleSource::setOrientation(float value)
	{
		GLobject::setOrientation(degreeToRadian(value));
	}
}