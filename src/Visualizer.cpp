#include "Visualizer.h"
#include "VisualizeCommand.h"
#include "VisualizerFactory.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = RALLY_COLORS::YELLOW;

Visualizer::Visualizer()
{
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetPremadeModel(Model::PreMadeModels::UnitSphere),
		ShaderManager::Get("colorConstantRender"),
		Blue);
	WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::GetPremadeModel(Model::PreMadeModels::UnitBox_WF),
		ShaderManager::Get("colorConstantRender"),
		Blue);
}

Visualizer::~Visualizer()
{
	VisualizerFactory::Terminate();
	delete WFUnitSphere;
	delete WFUnitBox;
	for (auto&& child : Instance().storageList)
	{
		delete child;
	}
}

void Visualizer::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	WFUnitSphere->SetWorld(S);
	WFUnitSphere->SetColor(col);
	WFUnitSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}
void Visualizer::privRenderAABB(Matrix& S, const Vect& col)
{
	WFUnitBox->SetWorld(S);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}
void Visualizer::privRenderOBB(Matrix& S, const Vect& col)
{
	WFUnitBox->SetWorld(S);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Instance().storageList.push_back(VisualizerFactory::CreateVisualizer(S, col));
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& AABB, const Vect& col)
{
	Instance().storageList.push_back(VisualizerFactory::CreateVisualizer(AABB, col));
}

void Visualizer::ShowAABB(Vect min, Vect max, const Vect& col)
{
	Instance().storageList.push_back(VisualizerFactory::CreateVisualizer(min, max, col));
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& OBB, const Vect& col)
{
	Instance().storageList.push_back(VisualizerFactory::CreateVisualizer(OBB, col));
}

void Visualizer::ShowCollisionVolume(const CollisionVolume& c, const Vect& col)
{
	c.DebugView(col);
}

void Visualizer::privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{

	Vect scale = S.GetRadius() * Vect(1, 1, 1);
	Vect v = S.GetCenter();
	Matrix world = Matrix(SCALE, scale) * Matrix(TRANS, v);
	Instance().privRenderBSphere(world, col);
}

void Visualizer::privShowAABB(const CollisionVolumeAABB& AABB, const Vect& col)
{
	Vect scale = AABB.GetMax() - AABB.GetMin();
	Vect v = 0.5f * (AABB.GetMax() + AABB.GetMin());
	Matrix world = Matrix(SCALE, scale) * Matrix(TRANS, v);
	Instance().privRenderAABB(world, col);
}

void Visualizer::privShowAABB(Vect min, Vect max, const Vect& col)
{
	Vect scale = max - min;
	Vect v = 0.5f * (max + min);
	Matrix world = Matrix(SCALE, scale) * Matrix(TRANS, v);
	Instance().privRenderAABB(world, col);
}

void Visualizer::privShowOBB(const CollisionVolumeOBB& OBB, const Vect& col)
{
	Vect scale = OBB.GetMax() - OBB.GetMin();
	Vect v = 0.5f * (OBB.GetMax() + OBB.GetMin());
	Matrix world = Matrix(SCALE, scale) * Matrix(TRANS, v);
	world *= OBB.GetWorld();
	Instance().privRenderOBB(world, col);
}

void Visualizer::VisualizeAll()
{
	StorageList::iterator it;
	for (it = Instance().storageList.begin(); it != Instance().storageList.end(); ++it)
	{
		(*it)->execute();
		VisualizerFactory::VisualizerReturn(*it);
	}
	Instance().storageList.clear();
}

void Visualizer::Clear()
{
	StorageList::iterator it;
	for (it = Instance().storageList.begin(); it != Instance().storageList.end(); ++it)
	{
		VisualizerFactory::VisualizerReturn(*it);
	}
	Instance().storageList.clear();
}
