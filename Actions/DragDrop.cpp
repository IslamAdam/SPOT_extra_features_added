#include "DragDrop.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "../Courses/Course.h"
#include <iostream>

//class Course;
//class AcademicYear;

DragDrop::DragDrop(Registrar* p) :Action(p)
{
}

bool DragDrop::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Drage and Drop any Course");
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		x = actData.x;
		y = actData.y;

		StudyPlan* pS = pReg->getStudyPlay();

		for (int i = 1; i <= 5; i++)
		{
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				SEMESTER sem2 = static_cast<SEMESTER>(sem);
				list<Course*> courses = pS->getCourses(i, sem2);
				for (auto it = courses.begin(); it != courses.end(); ++it)
				{
					graphicsInfo gInfo = (*it)->getGfxInfo();
					if (((x > gInfo.x) && (x < (gInfo.x + CRS_WIDTH))) && ((y > gInfo.y) && (y < (gInfo.y + CRS_HEIGHT))))
					{
						graphicsInfo gInfo2 = pGUI->DragCourse(*it);
						//x_y_year_semester st;
						//st = pS->co_ordinates(gInfo2.x, gInfo2.y);
						MyYearAndSemester* YandS = pReg->GetYearAndSem(gInfo2.y);
						if ((i == YandS->Year) && (sem2 == YandS->sem))
						{
							break;
						}
						else
						{
							Course_Code code = (*it)->getCode();
							string Title = (*it)->getTitle();
							int crd = (*it)->getCredits();
							pS->DeleteCourseFromPlan((*it), i, sem2);

							Course* pC = new Course(code, Title, crd);
							pS->AddCourse(pC, YandS->Year, YandS->sem);
							graphicsInfo* CrsGfx = pReg->getNewCoordinates(YandS->Year, YandS->sem, pC);
							pC->setY(CrsGfx->y);
							pReg->setCourseType(pC);
							CourseInfo mycourse = pReg->getCourseInfo(code);
							pC->setCoReq(mycourse.CoReqList);
							pC->setPreReq(mycourse.PreReqList);
							pC->setCredits(mycourse.Credits);

							for (auto itt = courses.begin(); itt != courses.end(); ++itt)
							{
								graphicsInfo gInfo3 = (*itt)->getGfxInfo();
								if (gInfo3.x > gInfo.x)
								{
									(*itt)->setGfxInfo({ gInfo3.x - 120 , gInfo3.y });
									(*itt)->setY(gInfo3.y);
								}
									
							}

							break;
						}
					}
				}
			}
		}
	}
	return true;
}


DragDrop::~DragDrop()
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
