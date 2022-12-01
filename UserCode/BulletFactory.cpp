#include "BulletFactory.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;


Bullet* BulletFactory::privCreateBullet(Matrix r, Vect m)
{
	Bullet* b;

	if (recycledBullets.empty())
	{

		b = new Bullet();

	}
	else
	{

		b = recycledBullets.front();
		recycledBullets.pop_front();

	}
	activeBullets.push_front(b);
	b->Initialize(r, m);
	b->SubmitEntry();
	return b;
}



void BulletFactory::privRecycleBullet(Bullet* b)
{
	recycledBullets.push_front(b);
	activeBullets.remove(b);
}


void BulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

BulletFactory::~BulletFactory()
{
	for (auto&& child : recycledBullets) {
		delete child;
	}
	for (auto&& child : activeBullets) {
		delete child;
	}
}