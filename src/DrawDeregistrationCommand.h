#pragma once
#include "CommandBase.h"
class Drawable;
class DrawDeregistrationCommand : public CommandBase
{
public:
	Drawable* ptrUp;
	void execute();
	DrawDeregistrationCommand(Drawable* up);
private:
};