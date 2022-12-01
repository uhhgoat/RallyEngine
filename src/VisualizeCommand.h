#pragma once
#include "CommandBase.h"
#include "AzulCore.h"
class VisualizeCommand : public CommandBase
{
public:
	virtual ~VisualizeCommand() = default;
	virtual void execute() = 0;

};