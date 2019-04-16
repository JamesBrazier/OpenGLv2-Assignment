// header file for the camera class
// Author: jbr 185

#pragma once

#include "MyExtentions.h"

namespace Project
{
	// the camera mode
	enum CameraMode
	{
		THIRDPERSON = 0,
		FIRSTPERSON,
		OBJECTBIND,
		OBJECTBINDFIXEDPOINT,
		NUMMODES
	};

	// the encapsulated camera class
	class Camera
	{
	private:

		float posX = 0, posY = 0, posZ = 0; // position of the camera
		float lookX = 0, lookY = 0, lookZ = 0; // where the camera is looking
		float upVecX = 0, upVecY = 0, upVecZ = 0; // the up vector of the camera
		float angleX = 0, angleY = 0; // the two angles in the spherical movement
		float moveX = 0, moveY = 0, moveZ = 0; // the movement of the camera
		float zoom = 0; // the zoom
		CameraMode mode;

		GLobject* bindedObject; // the object the camera is following
		float offsetX, offsetY, offsetZ; // offsets for the binded object

		void recalculateMatrix(void); // rcalculates all the parameters for gluLookAt

	public:

		Camera(float upVecX, float upVecY, float upVecZ, CameraMode startingMode);

		// loads the transformations for the camera in the display callback
		void loadMatrix(void);

		// updates the camera if it is bound to an object
		void update(void);

		void setMode(CameraMode mode);

		CameraMode getMode(void);

		void setBindedObject(GLobject* object, float offsetX, float offsetY, float offsetZ);

		void setPosition(float x, float y, float z);

		void getPosition(float* x, float* y, float* z);

		void movePosition(float x, float y, float z);

		void setLookAt(float x, float y, float z);

		void getLookAt(float* x, float* y, float* z);

		void moveLookAt(float angleAroundX, float angleAroundY);

		void setZoom(float value);

		float getZoom();

		void changeZoom(float change);

	};
}