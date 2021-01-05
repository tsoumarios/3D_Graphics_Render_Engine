#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include <math.h>

class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Camera(const Camera& c);
	~Camera();

	//Accessors and mutators
	Matrix GetCameraMatrix() const;
	float GetXRot() const;
	void SetXRot(const float x);
	float GetYRot() const;
	void SetYRot(const float y);
	float GetZRot() const;
	void SetZRot(const float z);
	Vertex GetPos() const;
	void SetPos(const float x, const float y, const float z, const float w);

	void SetMatrix();

	Camera& operator= (const Camera& rhs);

private:
	Matrix _cameraMatrix;
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;
};

