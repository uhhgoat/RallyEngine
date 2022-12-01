#pragma once
#include "CommandBase.h"
class Drawable;
class DrawRegistrationCommand : public CommandBase
{
public:
	Drawable* ptrUp;
	void execute();
	DrawRegistrationCommand(Drawable* up);
private:
};