#include "Camera.h"

namespace Project
{
	constexpr int worldRadius = 100;
	constexpr float minZoom = 0.1, maxZoom = 100;

	void Camera::recalculateMatrix(void)
	{ 
		switch (mode) {
			case CameraMode::THIRDPERSON: // camera moves in a sphere around a moveable point
				lookX = fminf(worldRadius, fmaxf(-worldRadius, lookX - (cos(angleY) * moveX) - (sin(angleY) * moveZ)));
				lookZ = fminf(worldRadius, fmaxf(-worldRadius, lookZ + (sin(angleY) * moveX) - (cos(angleY) * moveZ)));
				lookY += moveY;
				posX = lookX + (zoom * cos(angleX) * sin(angleY));
				posZ = lookZ + (zoom * cos(angleX) * cos(angleY));
				posY = lookY + (zoom * sin(angleX));
				break;
			case CameraMode::FIRSTPERSON: // camera moves around the scene, at a fixed y, with the look point is a sphere just infront
				posX = fminf(worldRadius, fmaxf(-worldRadius, posX - (cos(angleY) * -moveX) - (sin(angleY) * -moveZ)));
				posZ = fminf(worldRadius, fmaxf(-worldRadius, posZ + (sin(angleY) * -moveX) - (cos(angleY) * -moveZ))); // bound to world size
				posY += moveY;
				lookX = posX + (zoom * cos(angleX) * sin(angleY));
				lookZ = posZ + (zoom * cos(angleX) * cos(angleY));
				lookY = posY + (zoom * sin(angleX));
				break;
			case CameraMode::OBJECTBINDFIXEDPOINT: // camera is bound to an object offset from it, and the look point is fixed to what point is set
				bindedObject->getPosition(&posX, &posY, &posZ);
				posX += offsetX;
				posY += offsetY;
				posZ += offsetZ;
				break;
			case CameraMode::OBJECTBIND: // camera is bound to an object and the look point is bound to the objects orientation
				bindedObject->getPosition(&posX, &posY, &posZ);
				posX += offsetX;
				posY += offsetY;
				posZ += offsetZ;
				bindedObject->setOrientation(bindedObject->getOrientation() + moveX);
				lookX = posX + cos(degreeToRadian(bindedObject->getOrientation()));
				lookZ = posZ - sin(degreeToRadian(bindedObject->getOrientation()));
				lookY = posY;
				break;
			default:
				break;
		}
		moveX = 0; moveY = 0; moveZ = 0; //reset the movement
	}

	Camera::Camera(float upVecX, float upVecY, float upVecZ, CameraMode startingMode)
	{
		this->upVecX = upVecX;
		this->upVecY = upVecY;
		this->upVecZ = upVecZ;
		setMode(startingMode);
		recalculateMatrix();
	}

	void Camera::loadMatrix(void)
	{ 
		gluLookAt(posX, posY, posZ, lookX, lookY, lookZ, upVecX, upVecY, upVecZ);
	}

	void Camera::update(void)
	{ 
		if (mode == CameraMode::OBJECTBIND || mode == CameraMode::OBJECTBINDFIXEDPOINT) {
			recalculateMatrix(); // we only need to do this for objects, as they may move
		}
	}

	void Camera::setMode(CameraMode mode)
	{ 
		this->mode = mode;
		switch (mode) {
			case CameraMode::THIRDPERSON:
				lookX = 0; lookY = 0; lookZ = 0;
				angleX = 0.50; angleY = 0;
				zoom = 40;
				break;
			case CameraMode::FIRSTPERSON:
				posX = 0; posY = 4; posZ = 0;		
			case CameraMode::OBJECTBINDFIXEDPOINT:
				lookX = 0; lookY = 4; lookZ = 0;
			case CameraMode::OBJECTBIND:
				angleX = 0; angleY = 0;
				break;
			default: // default camera
				posX = 0; posY = 0; posZ = 0; 
				lookX = 0; lookY = 0; lookZ = -1;
				break;
		}
		recalculateMatrix();
	}

	CameraMode Camera::getMode(void)
	{
		return mode;
	}

	void Camera::setBindedObject(GLobject* object, float offsetX, float offsetY, float offsetZ)
	{ 
		bindedObject = object;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		this->offsetZ = offsetZ;
	}

	void Camera::setPosition(float x, float y, float z)
	{ 
		posX = x; posY = y; posZ = z;

		recalculateMatrix();
	}

	void Camera::getPosition(float* x, float* y, float* z)
	{ 
		*x = posX; *y = posY; *z = posZ;
	}

	void Camera::movePosition(float x, float y, float z)
	{ 
		moveX = x; moveY = y; moveZ = z; // set the movement and recalculate

		recalculateMatrix();
	}

	void Camera::setLookAt(float x, float y, float z)
	{ 
		lookX = x; lookY = y; lookZ = z;

		recalculateMatrix();
	}

	void Camera::getLookAt(float* x, float* y, float* z)
	{ 
		*x = lookX; *y = lookY; *z = lookZ;
	}

	void Camera::moveLookAt(float deltaAngleX, float deltaAngleY)
	{ 
		angleY += deltaAngleY;
		angleX += deltaAngleX;

		// we want to bind the camera to avoid the disorientating flip when directly above, and to avoid going through the floor
		if (mode == CameraMode::THIRDPERSON) { 
			angleX = fminf(1.5707, fmaxf(0, angleX));
		} else {
			angleX = fminf(1.5707, fmaxf(-1.5707, angleX));
		}

		recalculateMatrix();
	}

	void Camera::setZoom(float value)
	{ 
		zoom = value;

		recalculateMatrix();
	}

	float Camera::getZoom()
	{
		return zoom;
	}

	void Camera::changeZoom(float change)
	{ 
		zoom = fminf(maxZoom, fmaxf(minZoom, zoom + change)); // bind the zoom so it doesn't get too far away or in the floor

		recalculateMatrix();
	}
}