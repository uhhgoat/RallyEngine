#include "VisualizerFactory.h"

VisualizerFactory* VisualizerFactory::ptrInstance = nullptr;


VisualizeCommand* VisualizerFactory::privCreateVisualizer(const CollisionVolumeBSphere& S, const Vect& col)
{
	VisualizeCommand* b;
	/*
	if (recycledVisualizers.empty())
	{

		b = new VisualizeBSphereCommand(S, col);

	}
	else
	{

		b = recycledVisualizers.front();
		recycledVisualizers.pop_front();

	}
	activeVisualizers.push_front(b);
	//*/
	b = new VisualizeBSphereCommand(S, col);
	return b;
}

VisualizeCommand* VisualizerFactory::privCreateVisualizer(const CollisionVolumeAABB& AABB, const Vect& col)
{
	VisualizeCommand* b;
	/*
	if (recycledVisualizers.empty())
	{

		b = new VisualizeAABBCommand(AABB, col);

	}
	else
	{

		b = recycledVisualizers.front();
		recycledVisualizers.pop_front();

	}
	activeVisualizers.push_front(b);
	//*/
	b = new VisualizeAABBCommand(AABB, col);
	return b;
}

VisualizeCommand* VisualizerFactory::privCreateVisualizer(Vect Min, Vect Max, const Vect& col)
{
	VisualizeCommand* b;
	b = new VisualizeMinMaxCommand(Min, Max, col);
	return b;
}

VisualizeCommand* VisualizerFactory::privCreateVisualizer(const CollisionVolumeOBB& OBB, const Vect& col)
{
	VisualizeCommand* b;
	/*
	if (recycledVisualizers.empty())
	{

		b = new VisualizeOBBCommand(OBB, col);

	}
	else
	{

		b = recycledVisualizers.front();
		recycledVisualizers.pop_front();

	}
	activeVisualizers.push_front(b);
	//*/
	b = new VisualizeOBBCommand(OBB, col);
	return b;
}



void VisualizerFactory::privRecycleVisualizer(VisualizeCommand* b)
{
	/*
	recycledVisualizers.push_front(b);
	activeVisualizers.remove(b);
	//*/
	delete b;
}


void VisualizerFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

VisualizerFactory::~VisualizerFactory()
{

	while (!recycledVisualizers.empty())
	{
		delete recycledVisualizers.front();
		recycledVisualizers.pop_front();
	}
	while (!activeVisualizers.empty())
	{
		delete activeVisualizers.front();
		activeVisualizers.pop_front();
	}
}