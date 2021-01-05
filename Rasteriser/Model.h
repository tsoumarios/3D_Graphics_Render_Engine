#pragma once

#include <vector>
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Camera.h"
#include <algorithm>
#include "stdafx.h"
#include <math.h>



class Model
{
public:
	Model();
	Model(const Model& m);
	~Model();

	//Accessors and mutators
	const std::vector<Polygon3D>& GetPolygons() const;
	const std::vector<Vertex>& GetVertices()const;
	const std::vector<Vertex>& GetTransform()const;


	size_t GetPolygonCount() const; // Size of Polygons
	size_t GetVertexCount() const; // Size of Vertexes

	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	void modelTransformation(const Matrix& transform);	// Applying model transformation
	void Sort(void);									// Make Short Ordering the triangles
	void transformNewVertices(const Matrix& transform); // Using to apply projection, perspective and screen transformations 
	void Dehomogenize();								// Dehomogenize the model


	void CalculateBackfaces(Camera camera); // Applying Backface culling


	Model& operator= (const Model& rhs);  

private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transform;	
	int step = 0; // Using as step to simulate an animation
};