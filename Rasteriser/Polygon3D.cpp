#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_cull = false;
	_averageZ = 0;
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_cull = false;
}

Polygon3D::Polygon3D(int index0, int index1, int index2, Vector3D normal, float averageZ)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_cull = false;
	_normal = normal;
	_averageZ = averageZ;
}

Polygon3D::~Polygon3D()
{

}

//Copy Constructor
Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
	_cull = p.GetCull();
	_normal = p.GetNormal();
	_averageZ = p.GetAverageZ();
	_colour = p.GetColour();
}

//Accessor to return index of specified vertex
int Polygon3D::GetIndex(int i) const
{
	return _indices[i];
}

//Accessors and mutators
bool Polygon3D::GetCull() const
{
	return _cull;
}

void Polygon3D::SetCull(const bool cull)
{
	_cull = cull;
}

Vector3D Polygon3D::GetNormal() const
{
	return _normal;
}

void Polygon3D::SetNormal(const Vector3D &other)
{
	_normal = other;
}

float Polygon3D::GetAverageZ() const
{
	return _averageZ;
}

void Polygon3D::SetAverageZ(const float averageZ)
{
	_averageZ = averageZ;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;
}

void Polygon3D::SetColour(const COLORREF colour)
{
	_colour = colour;
}

Polygon3D& Polygon3D::operator= (const Polygon3D &rhs)
{
	//Only do the assignment if we are not assigning
	//to ourselves
	if (this != &rhs)
	{
		_indices[0] = rhs.GetIndex(0);
		_indices[1] = rhs.GetIndex(1);
		_indices[2] = rhs.GetIndex(2);
		_cull = rhs.GetCull();
		_averageZ = rhs.GetAverageZ();
		_normal = rhs.GetNormal();
		_colour = rhs.GetColour();
	}
	return *this;
}