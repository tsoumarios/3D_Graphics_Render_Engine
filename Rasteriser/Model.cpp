#include "Model.h"

Model::Model()
{
	_polygons.clear();
	_vertices.clear();
	_transform.clear();

}


//Copy Constructor
Model::Model(const Model& m)
{
	_polygons = m.GetPolygons();
	_vertices = m.GetVertices();
	_transform = m.GetTransform();

}

Model::~Model()
{

}

//Accessors and mutators
const std::vector<Polygon3D>& Model::GetPolygons() const
{
	return _polygons;
}

const std::vector<Vertex>& Model::GetVertices() const
{
	return _vertices;
}

const std::vector<Vertex>& Model::GetTransform() const
{
	return _transform;
}


size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex temp(x, y, z, 1);
	_vertices.push_back(temp);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D temp(i0, i1, i2);
	_polygons.push_back(temp);
}


Model& Model::operator=(const Model& rhs)
{
	if (this != &rhs)
	{
		_polygons = rhs.GetPolygons();
		_vertices = rhs.GetVertices();
		_transform = rhs.GetTransform();
	}
	return *this;
}

// Applying model transformation
void Model::modelTransformation(const Matrix &transform)
{
	_transform.clear();

	int vSize = int(_vertices.size());
	for (int i = 0; i < vSize; i++)
	{
		_transform.push_back(transform * _vertices[i]);
	}

}

// Triangle Benchmark: if the first polygon is bigger than the second return true
bool PolygonOrder(Polygon3D poly1, Polygon3D poly2)
{
	return poly1.GetAverageZ() > poly2.GetAverageZ();
}

// Applying depth sorting based of the z depth
void Model::Sort(void) 
{
	int sizeOfPolygons = int (_polygons.size());

	for (int i = 0; i < sizeOfPolygons; i++)
	{
		// Getting the polygon indeces

		int index_1 = _polygons[i].GetIndex(0);
		int index_2 = _polygons[i].GetIndex(1);
		int index_3 = _polygons[i].GetIndex(2);

		// Getting the polygon vertices

		Vertex vertex_1 = _transform[index_1];
		Vertex vertex_2 = _transform[index_2];
		Vertex vertex_3 = _transform[index_3];

		// Get the average from each vertex of the polygon

		_polygons[i].SetAverageZ((vertex_1.GetZ() + vertex_2.GetZ() + vertex_3.GetZ()) / 3);
	}

	// Shorting the polygons
	std::sort(_polygons.begin(), _polygons.end(), PolygonOrder);
}

// Using to apply projection, perspective and screen transformations
void Model::transformNewVertices(const Matrix &transform)
{
	int tSize = int(_transform.size());
	for (int i = 0; i < tSize; i++)
	{
		_transform[i]= transform * _transform[i];
	}
}

// Dehomogenize the model
void Model::Dehomogenize()
{
	int tSize = int(_transform.size());
	for (int i = 0; i < tSize; i++)
	{
		_transform[i].Dehomogenize();
	}
}


//Culculate backface culling
void Model::CalculateBackfaces(Camera camera)
{
	int polygonSize = int(_polygons.size());
	for (int i = 0; i < polygonSize; i++)
	{
		//Get the indices of each vertice
		int index0 = _polygons[i].GetIndex(0);
		int index1 = _polygons[i].GetIndex(1);
		int index2 = _polygons[i].GetIndex(2);

		//Get the vertices of each poligon
		Vertex vertex0 = _transform.at(index0);
		Vertex vertex1 = _transform.at(index1);
		Vertex vertex2 = _transform.at(index2);

		//Contructing vectors by subtracting vertices
		Vector3D vectorA = vertex1.subVector(vertex0);
		Vector3D vectorB = vertex2.subVector(vertex0);

		//Calculating the Cross product between the two vectors
		Vector3D normal = vectorB.CrossProduct(vectorA);

		//Creating an eye-vector by subtracting the camera position from vertex0
		Vector3D eyeVector = vertex0.subVector(camera.GetPos());

		bool cull; //Variable's use is to add or remove culling

		//Check if the Dot product < 0 to hide the polygon
		if (float dotProduct = normal.DotProduct(eyeVector) < 0)
		{
			cull = true; // Add culling
			_polygons[i].SetCull(cull);
		}
		else // Display the polygon
		{
			cull = false; //Remove culling
			_polygons[i].SetCull(cull);
		}

		//Save the polygons as normal
		_polygons[i].SetNormal(normal);
	}
}

