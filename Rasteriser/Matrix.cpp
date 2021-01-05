#include "Matrix.h"

//Default constructor
Matrix::Matrix()
{

}

//Constructor that initialises all elements. Note that an initialiser
//list is used to pass in the values. This is a new C++ feature.
Matrix::Matrix(std::initializer_list<float> list)
{
	if (list.size() != ROWS * COLS)
	{
		throw "Insufficient values supplied";
	}

	auto iterator = list.begin();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_matrixArray[i][j] = *iterator++;
		}
	}
}

//Copy constructor
Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_matrixArray[i][j] = other.GetM(i, j);
		}
	}
}

//Destructor
Matrix::~Matrix()
{

}

//Retrieve value in matrix at specified row and column
float Matrix::GetM(const int row, const int column) const
{
	return _matrixArray[row][column];
}

//Set value in matrix at specified row and column
void Matrix::SetM(const int row, const int column, const float value)
{
	_matrixArray[row][column] = value;
}

//Copy assignment operator
Matrix& Matrix::operator= (const Matrix &rhs)
{
	//Only do the assignment if we are not assigning
	//to ourselves
	if (this != &rhs)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				_matrixArray[i][j] = rhs.GetM(i, j);
			}
		}
	}
	return *this;
}

//Multiply two matrices together
const Matrix Matrix::operator*(const Matrix &other) const
{
	Matrix temp;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			float resultValue = 0;
			for (int k = 0; k < ROWS; k++)
			{
				resultValue += _matrixArray[k][i] * other.GetM(k, j);
			}
			temp.SetM(i, j, resultValue);
		}
	}
	return temp;
}

//Multiply a matrix by a vertex, returning a vertex
const Vertex Matrix::operator*(const Vertex &other) const
{
	Vertex temp;
	temp.SetX(_matrixArray[0][0] * other.GetX() + _matrixArray[0][1] * other.GetY() + _matrixArray[0][2] * other.GetZ() + _matrixArray[0][3] * other.GetW());
	temp.SetY(_matrixArray[1][0] * other.GetX() + _matrixArray[1][1] * other.GetY() + _matrixArray[1][2] * other.GetZ() + _matrixArray[1][3] * other.GetW());
	temp.SetZ(_matrixArray[2][0] * other.GetX() + _matrixArray[2][1] * other.GetY() + _matrixArray[2][2] * other.GetZ() + _matrixArray[2][3] * other.GetW());
	temp.SetW(_matrixArray[3][0] * other.GetX() + _matrixArray[3][1] * other.GetY() + _matrixArray[3][2] * other.GetZ() + _matrixArray[3][3] * other.GetW());
	
	return temp;
}

/*static*/ Matrix Matrix::ScalingMatrix(float x, float y, float z)
{
	Matrix temp{ x, 0, 0, 0,
				 0, y, 0, 0,
				 0, 0, z, 0,
				 0, 0, 0, 1 };
	return temp;
}

/*static*/ Matrix Matrix::YRotationMatrix(float angle)
{
	Matrix temp{ float(cos(angle)), 0, float(sin(angle)), 0,
				 0, 1, 0, 0,
				 float(-sin(angle)), 0, float(cos(angle)), 0,
				 0, 0, 0, 1 };
	return temp;
}

/*static*/ Matrix Matrix::XRotationMatrix(float angle)
{
	Matrix temp{ 1, 0, 0, 0,
				 0, float(cos(angle)), float(-sin(angle)), 0,
				 0, float(sin(angle)), float(cos(angle)), 0,
				 0, 0, 0, 1 };
	return temp;
}

/*static*/ Matrix Matrix::ZRotationMatrix(float angle)
{
	Matrix temp{ float(cos(angle)), float(-sin(angle)), 0, 0,
				 float(sin(angle)), float(cos(angle)), 0, 0,
				 0, 0, 1, 0,
				 0, 0, 0, 1 };
	return temp;
}

/*static*/ Matrix Matrix::TranslationMatrix(float x, float y, float z)
{
	Matrix temp{ 1, 0, 0, x,
				 0, 1, 0, y,
				 0, 0, 1, z,
				 0, 0, 0, 1 };
	return temp;
}