#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <time.h>
#include <math.h>
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "Polygon3d.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Vector3D.h"


class Rasteriser : public Framework
{
public:
	string ModelPath();
	bool Initialise();
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);

	void DrawWireFrame(Bitmap &bitmap); 
	void GeneratePerspectiveMatrix(float d, float aspectRatio); // Perspective Transformation function
	void GenerateViewMatrix(float d, float width, float height); // Screen Transformation function

private:
	Model _model;
	Camera _camera;
	Matrix _modelTransformA;
	Matrix _modelTransformB;	
	Matrix _modelTransformFinal;
	Matrix _perspectiveTransform;
	Matrix _screenTransform;
	string _modelpath;

	
};

