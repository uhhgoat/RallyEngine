#ifndef _Terrain
#define _Terrain

#include "GameObject.h"
#include "Matrix.h"
#include <tuple>
#include "Model.h"
#include <Texture.h>
#include "GpuVertTypes.h"
#include <GraphicsObject_TextureLight.h>

struct Cell
{
	Vect Min;
	Vect Max;
	void set(Vect min, Vect max)
	{
		Min = min;
		Max = max;
	}
};
struct CellIndex
{
	int i;
	int j;
	CellIndex() {};
	CellIndex(int _i, int _j)
	{
		i = _i, j = _j;
	};
};

class Terrain :  public Align16
{

private:
	friend class TerrainAttorney;
	Model* pModel;
	GraphicsObject_TextureLight* pGObj_Terrain;
	
	size_t SIDE;
	size_t PIXEL_WIDTH;
	float LEN;
	int numCells;

	VertexStride_VUN* pVerts;
	TriangleIndex* pTriList;
	Cell* cells;

	int TexelIndex(int side, int pixWidth, int i, int j) const;
	VertexStride_VUN* VertexArray(int nverts, int len, int side, float maxheight, float ytrans, int RepeatU, int RepeatV, const GLbyte* hgtmap, size_t pixel_width);
	TriangleIndex* TriangleArray(int ntri, int side);
	void Normals(int side, VertexStride_VUN* verts);

	void ShowCellRange(Vect Min, Vect Max);

	//int GetCellIndex(Vect Pos);
	CellIndex GetCellInd(Vect Pos);

	int GetTriangleIndex(Vect Pos);

	void ShowCell(int i, Vect& COLOR);

	int GetVertexInd(int i, int j);

	Cell GetCell(CellIndex ind);


public:
	Terrain(const char* heightmapFile, float len, float maxheight, float ytrans, Texture* tex, int RepeatU, int RepeatV);
	Terrain() = delete;
	~Terrain();
	Terrain(const Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;


	void Draw();

	/*!
	\brief Called to get the normal vector of the terrain at a given point
	*/
	Vect GetNormal(Vect Pos);
	/*!
	\brief Called to get the height of the terrain at a given point
	*/
	float GetHeight(Vect Pos);

	/*!
	\brief Called when wanting to see the terrain cells under an object's collision volume
	*/
	void Intersect(Collidable* col);


};



#endif _Terrain