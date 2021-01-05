#pragma once
#include "Vector3D.h"
#include "stdafx.h"


class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	Polygon3D(int index0, int index1, int index2, Vector3D normal, float averageZ);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	//Accessor to return index of specified vertex
	int GetIndex(int) const;

	//Accessors and mutators
	bool GetCull() const;
	void SetCull(const bool cull);
	Vector3D GetNormal() const;
	void SetNormal(const Vector3D &other);
	float GetAverageZ() const;
	void SetAverageZ(const float averageZ);
	COLORREF GetColour() const;
	void SetColour(const COLORREF colour);

	Polygon3D& operator= (const Polygon3D &rhs);

private:
	int _indices[3];
	bool _cull; //To add or remove culling of polygons 
	Vector3D _normal; // To store the Normal polygon
	float _averageZ;
	COLORREF _colour;
};
