#pragma once
#include "Updatable.h"
#include "Visualizer.h"
class VizualizerAttorney
{
public:
	class GameLoop
	{
	private:
		friend class Rally;
		static void VisualizeAll() { Visualizer::VisualizeAll(); }
	};
public:
	class Show
	{
	private:
		friend class VisualizeBSphereCommand;
		friend class VisualizeAABBCommand;
		friend class VisualizeOBBCommand;
		friend class VisualizeMinMaxCommand;
		static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col) { Visualizer::privShowBSphere(S, col); }
		static void ShowAABB(const CollisionVolumeAABB& AABB, const Vect& col) { Visualizer::privShowAABB(AABB, col); }
		static void ShowAABB(Vect min, Vect max, const Vect& col) { Visualizer::privShowAABB(min, max, col); }
		static void ShowOBB(const CollisionVolumeOBB& OBB, const Vect& col) { Visualizer::privShowOBB(OBB, col); }
	};
public:
	class SceneChange
	{
	private:
		friend class SceneManager;
		static void Clear() { Visualizer::Clear(); }
	};
};