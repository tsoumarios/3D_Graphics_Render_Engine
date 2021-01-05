#pragma once
#include "Vertex.h"
#include <initializer_list>
#include <math.h>

const int ROWS = 4;
const int COLS = 4;

class Matrix
{
public:
	//Default constructor
	Matrix();

	//Constructor that initialises all elements. Note that an initialiser
	//list is used to pass in the values. This is a new C++ feature.
	Matrix(std::initializer_list<float> list);

	//Copy constructor
	Matrix(const Matrix& other);

	//Destructor
	~Matrix();

	//Retrieve value in matrix at specified row and column
	float GetM(const int row, const int column) const;

	//Set value in matrix at specified row and column
	void SetM(const int row, const int column, const float value);

	//Copy assignment operator
	Matrix& operator= (const Matrix &rhs);

	//Multiply two matrices together
	const Matrix operator*(const Matrix &other) const;

	//Multiply a matrix by a vertex, returning a vertex
	const Vertex operator*(const Vertex &other) const;

	static Matrix ScalingMatrix(float x, float y, float z);
	static Matrix YRotationMatrix(float angle);
	static Matrix XRotationMatrix(float angle);
	static Matrix ZRotationMatrix(float angle);
	static Matrix TranslationMatrix(float x, float y, float z);

private:
	float _matrixArray[ROWS][COLS];
};
