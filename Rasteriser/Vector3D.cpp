#include "Vector3D.h"

Vector3D::Vector3D()
{

}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

//Copy Constructor
Vector3D::Vector3D(const Vector3D& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
}

Vector3D::~Vector3D()
{

}

//Accessors and mutators
float Vector3D::GetX() const
{
	return _x;
}

void Vector3D::SetX(const float x)
{
	_x = x;
}

float Vector3D::GetY() const
{
	return _y;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}

float Vector3D::GetZ() const
{
	return _z;
}

void Vector3D::SetZ(const float z)
{
	_z = z;
}


Vector3D& Vector3D::operator+ (const Vector3D &rhs)
{
	_x = _x + rhs.GetX();
	_y = _y + rhs.GetY();
	_z = _z + rhs.GetZ();
	return *this;
}

Vector3D& Vector3D::operator/ (const float d)
{
	_x = _x / d;
	_y = _x / d;
	_z = _z / d;
	return *this;
}

Vector3D& Vector3D::operator= (const Vector3D &rhs)
{
	_x = rhs.GetX();
	_y = rhs.GetY();
	_z = rhs.GetZ();
	return *this;
}

// Culculation of Dot Product
float Vector3D::DotProduct(const Vector3D& other) const
{
	float temp = _x * other.GetX() + _y * other.GetY() + _z * other.GetZ();
	return temp;
}

// Culculation of Cross Product between the two vectors
Vector3D Vector3D::CrossProduct(const Vector3D& other) const
{
	Vector3D temp;
	temp.SetX(_y * other.GetZ() - _z * other.GetY());
	temp.SetY(_z * other.GetX() - _x * other.GetZ());
	temp.SetZ(_x * other.GetY() - _y * other.GetX());
	return temp;
}
