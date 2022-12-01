#include "Terrain.h"
#include "Model.h"
#include <assert.h>
#include <TextureTGA.h>
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "RallyMathTools.h"


Terrain::Terrain(const char* heightmapFile, float len, float maxheight, float ytrans, Texture* tex, int RepeatU, int RepeatV)
{
	int imgWidth, imgHeight, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0); // We need square images for heightmaps



	SIDE = imgHeight;	// the image should be square
	PIXEL_WIDTH = 3;			// 3 bytes RGB per pixel
	LEN = len;
	//uint8_t h_val = hgtmap[pixel_width * (5 * side + 3)]; // the 'R' byte of the pixel at (3,5)


	// ** much work to add below **
	int nverts = SIDE * SIDE;
	int ntri = 2 * ((SIDE - 1) * (SIDE - 1));

	numCells = ntri / 2;

	cells = new Cell[numCells];


	pVerts = VertexArray(nverts, (int)len, SIDE, maxheight, ytrans, RepeatU, RepeatV, imgData, PIXEL_WIDTH);


	Normals(SIDE, pVerts);




	pTriList = TriangleArray(ntri, SIDE);


	pModel = new Model(pVerts, nverts, pTriList, ntri);



	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 600.0f, 1.0f, 1.0f);

	pGObj_Terrain = new GraphicsObject_TextureLight(pModel,
		ShaderManager::Get("textureLightRender"),
		tex,
		LightColor, LightPos);
	//Drawable::SubmitDrawRegistration();
}

VertexStride_VUN* Terrain::VertexArray(int nverts, int len, int side, float maxheight, float ytrans,
	int RepeatU, int RepeatV, const GLbyte* hgtmap, size_t pixel_width)
{
	VertexStride_VUN* pV = new VertexStride_VUN[nverts];

	int idx = 0;
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			float hgt = static_cast<unsigned char>(hgtmap[TexelIndex(side, pixel_width, i, j)]);
			float x = float((float(i) / float(side - 1))) * len - 0.5f * len;
			float y = ((hgt / 255.0f) * maxheight) + ytrans;
			float z = float((float(j) / float(side - 1))) * len - 0.5f * len;

			float u = RepeatU - float(i) / float(side - 1) * RepeatU;
			float v = RepeatV - float(j) / float(side - 1) * RepeatV;
			pV[idx].set(x, y, z, u, v, 0, 1, 0);
			//pV[idx].setNormal(Vect(0, 1.0f, 0));
			idx++;
		}
	}


	return pV;
}

void Terrain::Normals(int side, VertexStride_VUN* verts)
{
	int idx;
	for (int i = 1; i < side - 1; i++)
	{
		for (int j = 1; j < side - 1; j++)
		{
			idx = i * side + j;


			Vect v(verts[i * side + j].x, verts[i * side + j].y, verts[i * side + j].z);

			Vect normal1 = (v - Vect(verts[i * side + j - 1].x, verts[i * side + j - 1].y, verts[i * side + j - 1].z)).cross(v - Vect(verts[(i-1) * side + j].x, verts[(i - 1) * side + j].y, verts[(i - 1) * side + j].z));
			Vect normal2 = (v - Vect(verts[(i-1) * side + j].x, verts[(i-1) * side + j].y, verts[(i-1) * side + j].z)).cross(v - Vect(verts[(i-1) * side + j + 1].x, verts[(i-1) * side + j + 1].y, verts[(i-1) * side + j + 1].z));
			Vect normal3 = (v - Vect(verts[(i-1) * side + j + 1].x, verts[(i-1) * side + j + 1].y, verts[(i-1) * side + j + 1].z)).cross(v - Vect(verts[i * side + j + 1].x, verts[i * side + j + 1].y, verts[i * side + j + 1].z));
			Vect normal4 = (v - Vect(verts[i * side + j + 1].x, verts[i * side + j + 1].y, verts[i * side + j + 1].z)).cross(v - Vect(verts[(i+1) * side + j].x, verts[(i+1) * side + j].y, verts[(i+1) * side + j].z));
			Vect normal5 = (v - Vect(verts[(i+1) * side + j].x, verts[(i+1) * side + j].y, verts[(i+1) * side + j].z)).cross(v - Vect(verts[(i+1) * side + j-1].x, verts[(i+1) * side + j-1].y, verts[(i+1) * side + j-1].z));
			Vect normal6 = (v - Vect(verts[(i+1) * side + j-1].x, verts[(i+1) * side + j-1].y, verts[(i+1) * side + j-1].z)).cross(v - Vect(verts[i * side + j-1].x, verts[i * side + j-1].y, verts[i * side + j-1].z));

			Vect normal = (1.0f / 6.0f) * (normal1 + normal2 + normal3 + normal4 + normal5 + normal6);
			//AVG THEM AND THEN SET

			verts[idx].nx = normal.X();
			verts[idx].ny = normal.Y();
			verts[idx].nz = normal.Z();
		}
	}

}

TriangleIndex* Terrain::TriangleArray(int ntri, int side)
{

	TriangleIndex* pT = new TriangleIndex[ntri];

	int idx = 0;
	int idx2 = 0;

	float min;
	float max;
	VertexStride_VUN v1;
	VertexStride_VUN v2;
	VertexStride_VUN v3;
	VertexStride_VUN v4;
	for (int i = 0; i < side - 1; i++)
	{
		for (int j = 0; j < side - 1; j++)
		{
			pT[idx].set((j + side * i), (j + 1 + side * i), (j + side * (i + 1)));

			v1 = pVerts[pT[idx].v0]; //lowest x, lowest z
			v2 = pVerts[pT[idx].v1];
			v3 = pVerts[pT[idx].v2];

			idx++;

			pT[idx].set((j + 1 + side * i), (j + 1 + side * (i + 1)), (j + side * (i + 1)));

			v4 = pVerts[pT[idx].v1]; //highest x, highest z
			idx++;

			min = v1.y;
			if (min > v2.y) min = v2.y;
			if (min > v3.y) min = v3.y;
			if (min > v4.y) min = v4.y;
			max = v1.y;
			if (max < v2.y) max = v2.y;
			if (max < v3.y) max = v3.y;
			if (max < v4.y) max = v4.y;
			cells[idx2].set(Vect(v1.x, min, v1.z), Vect(v4.x, max, v4.z));
			//cells[idx2].Min = Vect(v1.x, min, v1.z);
			//cells[idx2].Max = Vect(v4.x, max, v4.z);
			idx2++;
		}
	}


	return pT;
}


int Terrain::TexelIndex(int side, int pixWidth, int i, int j) const
{
	return pixWidth * (j * side + i);
}



void Terrain::Draw()
{
	pGObj_Terrain->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	/*
	for (int i = 0; i < numCells; i++)
	{
		Visualizer::ShowAABB(cells[i].Min, cells[i].Max);
	}
	//*/
}

void Terrain::ShowCellRange(Vect Min, Vect Max)
{
	CellIndex first = GetCellInd(Min);
	CellIndex last = GetCellInd(Max);
	int iStart = first.i;
	int jStart = first.j;
	int iEnd = last.i;
	int jEnd = last.j;

	for (int k = iStart; k <= iEnd; k++)
	{
		for (int l = jStart; l <= jEnd; l++)
		{
			int idx = k * (SIDE - 1) + l;
			ShowCell(idx, RALLY_COLORS::GREEN);
		}
	}
}

/*
int Terrain::GetCellIndex(Vect Pos)
{
	float offX = Pos.X() + 0.5f * LEN;
	float offZ = Pos.Z() + 0.5f * LEN;
	int iInd = (int)((offX / LEN) * (SIDE - 1));
	int jInd = (int)((offZ / LEN) * (SIDE - 1));
	if (iInd >= (int)SIDE - 1)
		iInd = SIDE - 2;
	if (jInd >= (int)SIDE - 1)
		jInd = SIDE - 2;
	if (iInd < 0)
		iInd = 0;
	if (jInd < 0)
		jInd = 0;
	int INDEX = iInd * (SIDE - 1) + jInd;
	return INDEX;
}
*/

int Terrain::GetTriangleIndex(Vect Pos)
{
	float offX = Pos.X() + 0.5f * LEN;
	float offZ = Pos.Z() + 0.5f * LEN;
	int iInd = (int)((offX / LEN) * (SIDE - 1));
	int jInd = (int)((offZ / LEN) * (SIDE - 1));

	if (iInd >= (int)SIDE - 1)
		iInd = SIDE - 2;
	if (jInd >= (int)SIDE - 1)
		jInd = SIDE - 2;
	if (iInd < 0)
		iInd = 0;
	if (jInd < 0)
		jInd = 0;

	VertexStride_VUN a1 = pVerts[GetVertexInd(iInd + 1, jInd)];
	Vect A = Vect(a1.x, a1.y, a1.z);

	VertexStride_VUN b1 = pVerts[GetVertexInd(iInd, jInd+1)];
	Vect B = Vect(b1.x, b1.y, b1.z);

	VertexStride_VUN c1;
	Vect C;

	Vect v2 = Pos - A;

	if (v2.X() > v2.Z())
	{
		//lower right side
		c1 = pVerts[GetVertexInd(iInd + 1, jInd + 1)];
		C = Vect(c1.x, c1.y, c1.z);
	}
	else
	{
		c1 = pVerts[GetVertexInd(iInd , jInd)];
		C = Vect(c1.x, c1.y, c1.z);
	}

	Vect v1 = C - B;
	Vect v0 = B - A;

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	float X = (d*c - b*e) / (a*c - b*b);
	float Y = (a*e - d*b) / (a*c - b*b);



	Vect NormalA = Vect(a1.nx, a1.ny, a1.nz);
	Vect NormalB = Vect(b1.nx, b1.ny, b1.nz);
	Vect NormalC = Vect(c1.nx, c1.ny, c1.nz);
	Vect NormalP = NormalA + X * (NormalB - NormalA) + Y * (NormalC - NormalB);


	return 0;
}

Vect Terrain::GetNormal(Vect Pos)
{
	float offX = Pos.X() + 0.5f * LEN;
	float offZ = Pos.Z() + 0.5f * LEN;
	int iInd = (int)((offX / LEN) * (SIDE - 1));
	int jInd = (int)((offZ / LEN) * (SIDE - 1));

	if (iInd >= (int)SIDE - 1)
		iInd = SIDE - 2;
	if (jInd >= (int)SIDE - 1)
		jInd = SIDE - 2;
	if (iInd < 0)
		iInd = 0;
	if (jInd < 0)
		jInd = 0;

	VertexStride_VUN a1 = pVerts[GetVertexInd(iInd + 1, jInd)];
	Vect A = Vect(a1.x, a1.y, a1.z);

	VertexStride_VUN b1 = pVerts[GetVertexInd(iInd, jInd + 1)];
	Vect B = Vect(b1.x, b1.y, b1.z);

	VertexStride_VUN c1;
	Vect C;

	Vect v2 = Pos - A;

	if (v2.X() > v2.Z())
	{
		//lower right side
		c1 = pVerts[GetVertexInd(iInd + 1, jInd + 1)];
		C = Vect(c1.x, c1.y, c1.z);
	}
	else
	{
		c1 = pVerts[GetVertexInd(iInd, jInd)];
		C = Vect(c1.x, c1.y, c1.z);
	}

	Vect v1 = C - B;
	Vect v0 = B - A;

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	float X = (d * c - b * e) / (a * c - b * b);
	float Y = (a * e - d * b) / (a * c - b * b);



	Vect NormalA = Vect(a1.nx, a1.ny, a1.nz);
	Vect NormalB = Vect(b1.nx, b1.ny, b1.nz);
	Vect NormalC = Vect(c1.nx, c1.ny, c1.nz);
	Vect NormalP = NormalA + X * (NormalB - NormalA) + Y * (NormalC - NormalB);


	return NormalP;
}

float Terrain::GetHeight(Vect Pos)
{
	float offX = Pos.X() + 0.5f * LEN;
	float offZ = Pos.Z() + 0.5f * LEN;
	int iInd = (int)((offX / LEN) * (SIDE - 1));
	int jInd = (int)((offZ / LEN) * (SIDE - 1));

	if (iInd >= (int)SIDE - 1)
		iInd = SIDE - 2;
	if (jInd >= (int)SIDE - 1)
		jInd = SIDE - 2;
	if (iInd < 0)
		iInd = 0;
	if (jInd < 0)
		jInd = 0;

	VertexStride_VUN a1 = pVerts[GetVertexInd(iInd + 1, jInd)];
	Vect A = Vect(a1.x, a1.y, a1.z);

	VertexStride_VUN b1 = pVerts[GetVertexInd(iInd, jInd + 1)];
	Vect B = Vect(b1.x, b1.y, b1.z);

	VertexStride_VUN c1;
	Vect C;

	Vect v2 = Pos - A;

	if (v2.X() > v2.Z())
	{
		//lower right side
		c1 = pVerts[GetVertexInd(iInd + 1, jInd + 1)];
		C = Vect(c1.x, c1.y, c1.z);
	}
	else
	{
		c1 = pVerts[GetVertexInd(iInd, jInd)];
		C = Vect(c1.x, c1.y, c1.z);
	}

	Vect v1 = C - B;
	Vect v0 = B - A;

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	float X = (d * c - b * e) / (a * c - b * b);
	float Y = (a * e - d * b) / (a * c - b * b);



	float HeightA = a1.y;
	float HeightB = b1.y;
	float HeightC = c1.y;
	float HeightP = HeightA + X * (HeightB - HeightA) + Y * (HeightC - HeightB);


	return HeightP;
}

void Terrain::ShowCell(int i, Vect& COLOR)
{
	Visualizer::ShowAABB(cells[i].Min, cells[i].Max, COLOR);
}

int Terrain::GetVertexInd(int i, int j)
{
	int INDEX = i * (SIDE) + j;
	return INDEX;
}
CellIndex Terrain::GetCellInd(Vect Pos)
{
	float offX = Pos.X() + 0.5f * LEN;
	float offZ = Pos.Z() + 0.5f * LEN;
	int i = (int)((offX / LEN) * (SIDE - 1));
	int j = (int)((offZ / LEN) * (SIDE - 1));
	if (i >= (int)SIDE - 1)
		i = SIDE - 2;
	if (j >= (int)SIDE - 1)
		j = SIDE - 2;
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	return CellIndex(i, j);
}
void Terrain::Intersect(Collidable* col)
{
	if(col == nullptr)
		return;
	Vect pos = col->GetDefaultBSphere().GetCenter();
	float radius = col->GetDefaultBSphere().GetRadius();

	Vect Min = Vect(pos.X() - radius, 0, pos.Z() - radius);
	Vect Max = Vect(pos.X() + radius, 0, pos.Z() + radius);
	//ShowCellRange(Vect(pos.X() - radius, 0, pos.Z() - radius), Vect(pos.X() + radius, 0, pos.Z() + radius));

	CellIndex first = GetCellInd(Min);
	CellIndex last = GetCellInd(Max);
	int iStart = first.i;
	int jStart = first.j;
	int iEnd = last.i;
	int jEnd = last.j;

	for (int k = iStart; k < iEnd; k++)
	{
		for (int l = jStart; l < jEnd; l++)
		{
			int idx = k * (SIDE - 1) + l;
			//HERE CALL COLLISION TEST FROM MATHTOOLS
			try {

				if (!RallyMathTools::Intersect(CollisionVolumeAABB(cells[idx].Min, cells[idx].Max), col->GetDefaultBSphere()))
				{
					ShowCell(idx, RALLY_COLORS::GREEN);
				}
				else
				{
					if (!RallyMathTools::Intersect(CollisionVolumeAABB(cells[idx].Min, cells[idx].Max), col->GetCollisionVolume()))
					{
						ShowCell(idx, RALLY_COLORS::YELLOW);
					}
					else
					{
						ShowCell(idx, RALLY_COLORS::RED);
					}
				}
			}
			catch (std::exception e)
			{
				DebugMsg::out("/s", e.what());
			}
		}
	}
}

Cell Terrain::GetCell(CellIndex ind)
{
	int idx = ind.i * (SIDE - 1) + ind.j;
	return cells[idx];
}

Terrain::~Terrain()
{
	delete pModel;
	delete pGObj_Terrain;
	delete[] pVerts;
	delete[] pTriList;
	delete[] cells;
}