#ifndef _BulletFactory
#define _BulletFactory

#include <list>
#include "Bullet.h"

class BulletFactory
{
private:
	static BulletFactory* ptrInstance;



	BulletFactory() = default;
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory();

	static BulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory;
		return *ptrInstance;
	};

	std::list<Bullet*> recycledBullets;
	std::list<Bullet*> activeBullets;

	Bullet* privCreateBullet(Matrix r, Vect m);
	void privRecycleBullet(Bullet* b);

public:

	static Bullet* CreateBullet(Matrix r, Vect m) { return Instance().privCreateBullet(r, m); };
	static void BulletReturn(Bullet* b) { Instance().privRecycleBullet(b); };


	static void Terminate();
};


#endif _BulletFactory