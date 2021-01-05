#pragma once

class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& v);
	~Vector3D();
	
	//Accessors and mutators
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);

	//Culculation of Dot Product
	float DotProduct(const Vector3D& other) const;
	
	//Culculation of Cross Product
	Vector3D CrossProduct(const Vector3D& other) const;


	Vector3D& operator+ (const Vector3D &rhs);
	Vector3D& operator/ (const float d);
	Vector3D& operator= (const Vector3D &rhs);

private:
	float _x;
	float _y;
	float _z;
};

