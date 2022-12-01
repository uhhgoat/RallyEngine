#pragma once
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"
#include "TerrainManager.h"
#include "SceneRegistrationBroker.h"
class Scene
{
	friend class SceneManager;
	friend class Updatable;
	friend class Drawable;
	friend class Alarmable;
	friend class Inputable;
	friend class Collidable;
	friend class GameObject;
public:
	Scene();
	~Scene();
	virtual void Initialize() {};
	virtual void SceneEnd() {};
	CameraManager* GetCameraManager();
	Terrain* GetTerrain();

	virtual void NotifyClientConnect(bool success) { AZUL_UNUSED(success); };
	virtual void NotifyConnectToHost(bool success) { AZUL_UNUSED(success); };
	virtual void NotifyClientDisconnected() {  };
	virtual void NotifyHostDisconnected() {  };

private:
	CameraManager CamMgr;
	UpdatableManager UpdateMgr;
	DrawableManager DrawMgr;
	AlarmableManager AlarmMgr;
	KeyboardEventManager InputMgr;
	CollisionManager CollMgr;
	TerrainManager TerMgr;
	SceneRegistrationBroker RegistrationBrkr;
	/*! \brief Register and Deregister called when adding functionality to a GameObject.
 *         
 *
 *  \par Example:
	The following code shows an object being registered to be updated in the scene's update cycle, and then Deregistered.
	\code
	Player::Player()
	{
		Updatable::SubmitUpdateRegistration();
	}
	Player::~Player()
	{
		Updatable::SubmitUpdateDeregistration();
	}
	\endcode
 */

	void Register(Updatable* up);
	void Deregister(UpdatableManager::StorageListRef ref);
	void Register(Drawable* dr);
	void Deregister(DrawableManager::StorageListRef ref);
	void Register(float t, AlarmableManager::AlarmEvent alm);
	void Deregister(AlarmableManager::StorageListRef ref);
	void Register(Inputable* in, AZUL_KEY k, EVENT_TYPE e);
	void Deregister(SingleKeyEventManager::StorageListRef ref, AZUL_KEY k, EVENT_TYPE e);

	CollisionManager* GetCollisionMgr();

	void SubmitCommand(CommandBase* cmd);

	void Update();
	void Draw();


protected:
	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		CollMgr.SetCollisionPair<C1, C2>();
	}
	template<typename C>
	void SetCollisionSelf()
	{
		CollMgr.SetCollisionSelf<C>();
	}
	//SET COLLISION TERRAIN
	template<typename C>
	void SetCollisionTerrain()
	{
		CollMgr.SetCollisionTerrain<C>();
	}

	void SetTerrain(std::string key);


};