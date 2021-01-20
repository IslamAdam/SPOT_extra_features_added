#pragma once
#include "Action.h"
//Class responsible for adding course action
class Import :
	public Action
{
public:
	Import(Registrar*);
	bool virtual Execute();
	virtual ~Import();
};