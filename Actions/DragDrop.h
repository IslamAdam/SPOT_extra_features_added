#pragma once
#include "Action.h"
#include "..\StudyPlan\StudyPlan.h"
#include "../GUI/GUI.h"

//Class responsible for adding course action

class AcademicYear;
class Course;

class DragDrop : public Action
{
public:
	DragDrop(Registrar*);
	bool virtual Execute();
	virtual ~DragDrop();
};

