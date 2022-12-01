#pragma once
#include "CommandBase.h"
class Updatable;
class UpdateDeregistrationCommand : public CommandBase
{
public:
	Updatable* ptrUp;
	void execute();
	UpdateDeregistrationCommand(Updatable* up);
private:
};