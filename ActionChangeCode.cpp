#include "ActionChangeCode.h"
#include"Registrar.h"

ActionChangeCode::ActionChangeCode(Registrar* p) :Action(p) {
//	Execute();
}

bool ActionChangeCode::Execute() {
	string newCode;
	GUI * pGUI= pReg->getGUI();

	ActionData myData=pGUI->GetUserAction("Select Course to change its code");
	

	StudyPlan* pS = pReg->getStudyPlay();
	Course*myOldCourse=pS->Check_Course_coordinates_SP(myData.x, myData.y);
	if (myOldCourse == nullptr) {
		pGUI->PrintMsg("NO Course in This place ");
		return true;
	}
	if (myOldCourse != nullptr) {
		pGUI->PrintMsg("Write new Course Code :");
		string newCode = pGUI->GetSrting();
		MyYearAndSemester* yearSem=pReg->GetYearAndSem(myData.y);
		///#########################Deleting Course#########################

		pS->DeleteCourseFromPlan(myOldCourse, yearSem->Year, yearSem->sem);

		//##########################  Adding Course###########################
		CourseInfo newCourse = pReg->getCourseInfo(newCode);
		if (newCourse.Code == "000") {
			pGUI->PrintMsg(" No Course With this code");
			return true;
		}
		else {
			Course* newC = new Course(newCode, newCourse.Title, newCourse.Credits);     ///////////// new Course 
			pS->AddCourse(newC, yearSem->Year, yearSem->sem);
			newC->setGfxInfo(myOldCourse->getGfxInfo());
			newC->setX(myOldCourse->getX());
			newC->setY(myOldCourse->getY());
			pReg->setCourseType(newC);
			
			return true;
		}
	}

}
ActionChangeCode::~ActionChangeCode()
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

