#ifndef _VisualizerFactory
#define _VisualizerFactory

#include <list>
#include "VisualizeBSphereCommand.h"
#include "VisualizeAABBCommand.h"
#include "VisualizeOBBCommand.h"
#include "VisualizeMinMaxCommand.h"

class VisualizerFactory
{
private:
	static VisualizerFactory* ptrInstance;



	VisualizerFactory() = default;
	VisualizerFactory(const VisualizerFactory&) = delete;
	VisualizerFactory& operator=(const VisualizerFactory&) = delete;
	~VisualizerFactory();

	static VisualizerFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new VisualizerFactory;
		return *ptrInstance;
	};

	std::list<VisualizeCommand*> recycledVisualizers;
	std::list<VisualizeCommand*> activeVisualizers;

	VisualizeCommand* privCreateVisualizer(const CollisionVolumeBSphere& S, const Vect& col);
	VisualizeCommand* privCreateVisualizer(const CollisionVolumeAABB& AABB, const Vect& col);
	VisualizeCommand* privCreateVisualizer(Vect Min, Vect Max, const Vect& col);
	VisualizeCommand* privCreateVisualizer(const CollisionVolumeOBB& OBB, const Vect& col);
	void privRecycleVisualizer(VisualizeCommand* b);

public:

	static VisualizeCommand* CreateVisualizer(const CollisionVolumeBSphere& S, const Vect& col) { return Instance().privCreateVisualizer(S, col); };
	static VisualizeCommand* CreateVisualizer(const CollisionVolumeAABB& AABB, const Vect& col) { return Instance().privCreateVisualizer(AABB, col); };
	static VisualizeCommand* CreateVisualizer(Vect min, Vect max, const Vect& col) { return Instance().privCreateVisualizer(min, max, col); };
	static VisualizeCommand* CreateVisualizer(const CollisionVolumeOBB& OBB, const Vect& col) { return Instance().privCreateVisualizer(OBB, col); };
	static void VisualizerReturn(VisualizeCommand* b) { Instance().privRecycleVisualizer(b); };


	static void Terminate();
};


#endif _VisualizerFactory