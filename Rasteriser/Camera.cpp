#include "Camera.h"

Camera::Camera()
{
	_xRotation = 0;
	_yRotation = 0;
	_zRotation = 0;
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	Matrix xRotate { 1, 0, 0, 0, 0, float(cos(xRotation)), float(sin(xRotation)), 0, 0, float(-sin(xRotation)), float(cos(xRotation)), 0, 0, 0, 0, 1 };
	Matrix yRotate { float(cos(yRotation)), 0, float(-sin(yRotation)), 0, 0, 1, 0, 0, float(sin(yRotation)), 0, float(cos(yRotation)), 0, 0, 0, 0, 1 };
	Matrix zRotate { float(cos(zRotation)), float(sin(zRotation)), 0, 0, float(-sin(zRotation)), float(cos(zRotation)), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	Matrix cameraPosition{ 1, 0, 0, -position.GetX(), 0, 1, 0, -position.GetY(), 0, 0, 1, -position.GetZ(), 0, 0, 0, 1};

	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;
	_cameraMatrix = xRotate * yRotate * zRotate * cameraPosition;
}

//Copy Constructor
Camera::Camera(const Camera& c)
{
	_cameraMatrix = c.GetCameraMatrix();
	_xRotation = c.GetXRot();
	_yRotation = c.GetYRot();
	_zRotation = c.GetZRot();
	_position = c.GetPos();
}

Camera::~Camera()
{

}

//Accessors and mutators
Matrix Camera::GetCameraMatrix() const
{
	return _cameraMatrix;
}

float Camera::GetXRot() const
{
	return _xRotation;
}

void Camera::SetXRot(const float x)
{
	_xRotation = x;
}

float Camera::GetYRot() const
{
	return _yRotation;
}

void Camera::SetYRot(const float y)
{
	_yRotation = y;
}

float Camera::GetZRot() const
{
	return _zRotation;
}

void Camera::SetZRot(const float z)
{
	_zRotation = z;
}

Vertex Camera::GetPos() const
{
	return _position;
}

void Camera::SetPos(const float x, const float y, const float z, const float w)
{
	_position.SetX(x);
	_position.SetY(y);
	_position.SetZ(z);
	_position.SetW(w);
}

//Sets the matrix if the values are not set by the constructor
void Camera::SetMatrix()
{
		Matrix xRotate{ 1, 0, 0, 0, 0, float(cos(_xRotation)), float(sin(_xRotation)), 0, 0, float(-sin(_xRotation)), float(cos(_xRotation)), 0, 0, 0, 0, 1 };
		Matrix yRotate{ float(cos(_yRotation)), 0, float(-sin(_yRotation)), 0, 0, 1, 0, 0, float(sin(_yRotation)), 0, float(cos(_yRotation)), 0, 0, 0, 0, 1 };
		Matrix zRotate{ float(cos(_zRotation)), float(sin(_zRotation)), 0, 0, float(-sin(_zRotation)), float(cos(_zRotation)), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		Matrix cameraPosition{ 1, 0, 0, -_position.GetX(), 0, 1, 0, -_position.GetY(), 0, 0, 1, -_position.GetZ(), 0, 0, 0, 1 };

		_cameraMatrix = xRotate * yRotate * zRotate * cameraPosition;
}

Camera& Camera::operator= (const Camera& rhs)
{
	//Only do the assignment if we are not assigning
	//to ourselves
	if (this != &rhs)
	{
		_cameraMatrix = rhs.GetCameraMatrix();
		_xRotation = rhs.GetXRot();
		_yRotation = rhs.GetYRot();
		_zRotation = rhs.GetZRot();
		_position = rhs.GetPos();
	}
	return *this;
}