#include "ActionDeleteCourse.h"
#include <vector>
using namespace std;

bool ActionDeleteCourse::Execute() {
	SEMESTER Mysem;
	GUI* pGUI = pReg->getGUI();
	int i = 0;
	 StudyPlan *ps = pReg->getStudyPlay();
	ActionData myData = pGUI->GetUserAction("Select Course to delete from study plan:");
	int x = myData.x;
	int y = myData.y;
	Course* pCourse= ps->Check_Course_coordinates_SP(x, y);
	
	if (pCourse != nullptr) {
		MyYearAndSemester* yANdS = pReg->GetYearAndSem(pCourse->getGfxInfo().y);
		ps->DeleteCourseFromPlan(pCourse, yANdS->Year,yANdS->sem);
		pGUI->PrintMsg("Cousre has been deleted successfully");

			return true;
	}
	else {
		pGUI->PrintMsg("No Course in this place");
		return false;
	} 
}
ActionDeleteCourse::~ActionDeleteCourse()
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
