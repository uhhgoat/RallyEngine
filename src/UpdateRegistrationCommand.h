#pragma once
#include "CommandBase.h"
class Updatable;
class UpdateRegistrationCommand : public CommandBase
{
public:
	Updatable* ptrUp;
	void execute();
	UpdateRegistrationCommand(Updatable* up);
private:
};