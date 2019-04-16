// header module header file for my extentions to openGL
// Author: jbr 185

#pragma once

#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../TextureManager/TextureManager.h"

using namespace std;

namespace Project
{
	constexpr float aniSpeed = 3;
	constexpr float gravity = 0.005, friction = 0.0005, cannonVel = 1, particleVel = 0.3; // physics constants
	constexpr float floorHight = -0.05; // the height (Y) of the floor
	constexpr int floorRadius = 100; // the half height/width of the floor
	constexpr float black[4] = { 0, 0, 0, 1 }; // no specular colour
	constexpr float grey[4] = { 0.2, 0.2, 0.2, 1 }; // the ambient light colour
	constexpr float white[4] = { 1, 1, 1, 1 }; // the specular and diffuse light colours

	// an interface for textured GLobjects
	class GLtextured
	{
	public:

		virtual void loadTextures(TextureManager& manager) = 0;

	};

	// an interface for objects with GL lights
	class GLlight
	{
	public:

		virtual void initialize(void) = 0;

	};

	// an interface-like class for animated objects with common variables
	class GLanimated
	{
	protected:

		char animationState = 0; // the switch state of the animation
		float animationSpeed = aniSpeed; // the speed of the animation, aka value change
		int animationCounterA = 0; // counter A
		int animationCounterB = 0; // counter B

	public:

		// Updates all the animation variables based on the current state
		virtual void updateAnimation(void) = 0;

	};

	inline double radianToDegree(double radians)
	{
		return radians * (180 / M_PI);
	}

	inline double degreeToRadian(double degrees)
	{
		return degrees * (M_PI / 180);
	}

	void drawQuad(double width, double height);

	// draws a billboard, a quad that constantly faces the camera, for the illusion of volume
	void drawBillboard(double width, double height, double locX, double locY, double locZ, double camX, double camY, double camZ);

	void drawCube(double size);

	void drawCube(double size, float textureScale);

	void drawCylinder(GLUquadric* quadric, double baseRadius, double topRadius, double height, int slices, int stacks);

	void drawHollowCylinder(GLUquadric* quadric, double baseRadius, double baseOpeningRadius, double topRadius, double topOpeningRadius, double height, int slices, int stacks);

	void drawCone(GLUquadric* quadric, double baseRadius, double height, int slices, int stacks);
}

// module headers
#include "GLobject.h"
#include "SpotLight.h"
#include "SkyBox.h"
#include "Floor.h"
#include "Camera.h"
#include "Particle.h"
#include "ParticleSource.h"