#include "AzulCore.h"
#include "Rally.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "VisualizeCommand.h"
class Visualizer : public Align16
{
private:
	friend class VizualizerAttorney;
	friend class Rally;

	Visualizer();
	~Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	static Visualizer* ptrInstance;

	static Visualizer& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Visualizer;
		return *ptrInstance;
	}


	using StorageList = std::list<VisualizeCommand*>;
	StorageList storageList;

	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;

	void privRenderBSphere(Matrix& S, const Vect& col);
	void privRenderAABB(Matrix& S, const Vect& col);
	void privRenderOBB(Matrix& S, const Vect& col);

	static void privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR);
	static void privShowAABB(const CollisionVolumeAABB& AABB, const Vect& col = DEFAULT_COLOR);
	static void privShowAABB(Vect min, Vect max, const Vect& col = DEFAULT_COLOR);
	static void privShowOBB(const CollisionVolumeOBB& OBB, const Vect& col = DEFAULT_COLOR);

	static void VisualizeAll();
	static void Clear();

	static void Delete();
public:
	/*!
	\brief Called to display the selected Collision Volume in wireframe
	*/
	static void ShowCollisionVolume(const CollisionVolume& Vol, const Vect& col = DEFAULT_COLOR);
	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR);
	static void ShowAABB(const CollisionVolumeAABB& AABB, const Vect& col = DEFAULT_COLOR);
	static void ShowAABB(Vect min, Vect max, const Vect& col = DEFAULT_COLOR);
	static void ShowOBB(const CollisionVolumeOBB& OBB, const Vect& col = DEFAULT_COLOR);

};