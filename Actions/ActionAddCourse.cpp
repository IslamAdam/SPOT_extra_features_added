#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <fstream>
#include <iostream>
#include <string>
#include<sstream>
#include "..//Registrar.h"
using namespace std;
ActionAddCourse::ActionAddCourse(Registrar* p) :Action(p)
{

}

bool ActionAddCourse::Execute()
{
	int crd = 0;
	string courseTitle = "";
	GUI* pGUI = pReg->getGUI();	
	//Take Course Code from user
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();
	CourseInfo mycourse = pReg->getCourseInfo(code);
	//Check Course Code 
	if (mycourse.Code == "000") {
		pGUI->PrintMsg("There is no Course Exist with this Course Code!");
		return true;
	}

	// Check Wether Course exist or not in study plan 

	StudyPlan* pS = pReg->getStudyPlay();
	if (pS->CheckExistanceOfCourse(code) == true) {
		pGUI->PrintMsg("Course Already exist");
		return true;
	}



	    int x, y;
		ActionData actData = pGUI->GetUserAction("Select a year to add coures to:");
		x = actData.x;
		if (actData.x < 130) {
			actData.x = 130;
		}
		y = actData.y;

		if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
		{
			//get coord where user clicked
			Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
			x = actData.x;
			y = actData.y;
			pC->setCoReq(mycourse.CoReqList);
			pC->setPreReq(mycourse.PreReqList);
			pC->setCredits(mycourse.Credits);
			
			
			MyYearAndSemester* YandS = pReg->GetYearAndSem(y);
			pS->AddCourse(pC, YandS->Year, YandS->sem);
			graphicsInfo* CrsGfx = pReg->getNewCoordinates(YandS->Year, YandS->sem, pC);
			pC->setY(CrsGfx->y);
			pReg->setCourseType(pC);
			StudyPlan* pS = pReg->getStudyPlay();
		}
	return true;
}


ActionAddCourse::~ActionAddCourse()
{
	StudyPlan* pS = pReg->getStudyPlay();
	GUI* pGUI = pReg->getGUI();

	pReg->Check_Credits();
	pS->CheckStudyPlanCredits();
	pS->Check_Comp_Major_Studyplan(pReg);
	pS->Check_Comp_Track_Studyplan(pReg);
	pS->Check_Comp_Univ_Studyplan(pReg);
	pS->Check_Coreq_studyplan();
	pS->Check_Elective_Major_Studyplan(pReg);
	pS->Check_Elective_Univ_Studyplan(pReg);
	pS->Check_Prereq_studyplan();
	Warnings* planWarning = pS->getWarnings();

	if ((planWarning->uniCOMIssues.size() != 0) || (planWarning->Coreqwarning.size() != 0) || (planWarning->TrackCOMIssues.size() != 0)
		|| (planWarning->MajorCOMIssues.size() != 0) || (planWarning->Prereqwarning.size() != 0)
		|| (planWarning->MajorElectiveIssues.size() != 0))     // put condition here
	{
		pGUI->PrintMsg(" Critical Warnning! ");
		string dumy = pGUI->GetSrting();

		vector<Course_Code> bad_courses;
		bad_courses.clear();
		for (int i = 0; i < planWarning->Coreqwarning.size(); i++)
		{
			bad_courses.push_back(planWarning->Coreqwarning.at(i));
		}

		for (int i = 0; i < planWarning->Prereqwarning.size(); i++)
		{
			bad_courses.push_back(planWarning->Prereqwarning.at(i));
		}
		////////////////////////////////////////////////////////////////
		for (int i = 1; i <= 5; i++)
		{
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				SEMESTER sem2 = static_cast<SEMESTER>(sem);
				list<Course*> courses = pS->getCourses(i, sem2);
				for (auto it = courses.begin(); it != courses.end(); ++it)
				{
					(*it)->SetCourseColor(SNOW); // default colour
				}
			}
		}
		/////////////////////////////////////////////////////////////////
		for (int i = 1; i <= 5; i++)
		{
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				SEMESTER sem2 = static_cast<SEMESTER>(sem);
				list<Course*> courses = pS->getCourses(i, sem2);
				for (auto it = courses.begin(); it != courses.end(); ++it)
				{
					for (int i = 0; i < bad_courses.size(); i++)
					{
						if ((*it)->getCode() == bad_courses.at(i))
						{
							(*it)->SetCourseColor(RED);
						}

					}
				}
			}
		}
	}
	if ((planWarning->moderate.size() != 0))
	{
		pGUI->PrintMsg(" Moderate Warnning! ");
		string dumy = pGUI->GetSrting();
	}
	planWarning->Coreqwarning.clear();
	planWarning->Prereqwarning.clear();
	planWarning->MajorCOMIssues.clear();
	planWarning->MajorElectiveIssues.clear();
	planWarning->TrackCOMIssues.clear();
	planWarning->UNIVelectiveIssues.clear();
	planWarning->uniCOMIssues.clear();
	planWarning->credits.clear();
	planWarning->moderate.clear();
}

