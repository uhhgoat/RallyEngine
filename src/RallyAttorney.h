#include "Rally.h"
class RallyAttorney
{
	friend class FreezeTime;
private:
	static float GetTime() { return Rally::GetTime(); };
};