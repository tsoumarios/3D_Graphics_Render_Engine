#include "Rasteriser.h"

Rasteriser app;

string Rasteriser::ModelPath()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

bool Rasteriser::Initialise()
{
	_modelpath="";
	_modelpath = ModelPath() + "\\cube.md2";

	if (!MD2Loader::LoadModel(_modelpath.c_str(), _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}

	Camera temp(0, 0, 0, Vertex(0, 0, -50, 1));
	//Camera temp(0, 0, 0, Vertex(0, 7, -11, 1));
	_camera = temp;
	return true;
}

void Rasteriser::DrawWireFrame(Bitmap &bitmap)
{
	std::vector<Polygon3D> tempPolygon(_model.GetPolygons());
	int polygonSize = int(_model.GetPolygonCount());
	std::vector<Vertex> tempVertex(_model.GetTransform());

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);
	for (int i = 0; i < polygonSize; i++)
	{
		if (!tempPolygon[i].GetCull())
		{
			//Get the indices
			int tempIndex0 = tempPolygon[i].GetIndex(0);
			Vertex tempVertex0(tempVertex[tempIndex0]);
			int tempIndex1 = tempPolygon[i].GetIndex(1);
			Vertex tempVertex1(tempVertex[tempIndex1]);
			int tempIndex2 = tempPolygon[i].GetIndex(2);
			Vertex tempVertex2(tempVertex[tempIndex2]);

			//Draw the triangle
			MoveToEx(bitmap.GetDC(), tempVertex0.GetIntX(), tempVertex0.GetIntY(), NULL);
			LineTo(bitmap.GetDC(), tempVertex1.GetIntX(), tempVertex1.GetIntY());
			LineTo(bitmap.GetDC(), tempVertex2.GetIntX(), tempVertex2.GetIntY());
			LineTo(bitmap.GetDC(), tempVertex0.GetIntX(), tempVertex0.GetIntY());
		}
	}
	DeleteObject(hPen);
}

// Perspective Transformation Matrix
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveTransform = {
		 d / aspectRatio, 0, 0, 0,
		 0,   d, 0, 0,
		 0,  0,  d, 0,
		 0,  0,  1, 0
	}; 

}


// Screen Transformation Matrix
void Rasteriser::GenerateViewMatrix(float d, float width, float height)
{
	_screenTransform = {
		width / 2, 0, 0, width / 2,
		0, -height / 2, 0 , height / 2,
		0, 0, d / 2, d / 2,
		0, 0, 0, 1
	};
}

double step=1;
double step1 = 1;
void Rasteriser::Update(Bitmap &bitmap)
{
	
	float aspectRatio = float(float(bitmap.GetWidth()) / float(bitmap.GetHeight())); // Aspect Ratio calculation

	GeneratePerspectiveMatrix(1, aspectRatio); // Perspective Matrix 
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight()); // View Matrix

	

	step -= 0.02; // Step to make animation example

	/***************************************************************************************************/
	/***************************************** Rotate X and Y ******************************************/

	_modelTransformA = Matrix::XRotationMatrix(step); // First Transform
	_modelTransformB = Matrix::YRotationMatrix(step); // Second Transform
	_modelTransformFinal = _modelTransformA.operator*(_modelTransformB);


	/***************************************************************************************************/
	/************************************ Rotate X and Y ***********************************************/

	//_modelTransformB = Matrix::XRotationMatrix(step);
	//_modelTransformA = Matrix::ZRotationMatrix(step);
	//_modelTransformFinal = _modelTransformA.operator*(_modelTransformB);


	/***************************************************************************************************/
	/********************************* Translate and scaling *******************************************/
	//step -= 0.002; // Step to make animation example
	//step1 += 0.1;

	//_modelTransformA = Matrix::ScalingMatrix(step, step, step); // First Transform
	//_modelTransformB = Matrix::TranslationMatrix(step1, step1, 0); // Second Transform

	//_modelTransformFinal = _modelTransformA.operator*(_modelTransformB); // Multiply Mertices to get the final Matrix


				/**************************************************/
				/************** Pipeline Implementation ***********/
				/**************************************************/

	_model.modelTransformation(_modelTransformFinal);		// Model transformation
	_model.transformNewVertices(_camera.GetCameraMatrix()); // Projection transformation
	_model.Sort();											// Depth Ordering
	_model.transformNewVertices(_perspectiveTransform);		// Perspective transformation
	_model.Dehomogenize();									// Dehomogenizing
	_model.transformNewVertices(_screenTransform);			// Screen transformation

	_model.CalculateBackfaces(_camera);						// Apply Backface culling 

}

void Rasteriser::Render(Bitmap &bitmap)
{
	bitmap.Clear(RGB(0, 0, 0)); //Set a color to the bitmap

	DrawWireFrame(bitmap); //Drawing the wireframe of the cube
}