#include "StudyPlan.h"
#include<iostream>
#include"..//Registrar.h"
using namespace std;

StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear);
	planWarning = new Warnings;
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
// This function return vector of pointers in academic year
vector<AcademicYear*> StudyPlan::getPplan() const {     
	return plan;
}
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	if (pC == nullptr)
		return false;

	plan[year - 1]->AddCourse(pC, sem);
	TotalCredits += pC->getCredits();
	if (pC != nullptr) {
		if (pC->getCourseType() == UNIVE || pC->getCourseType() == UNIVC)
			TotalUnivCredits += pC->getCredits();

		else if (pC->getCourseType() == MAJORE || pC->getCourseType() == MAJORC)
			TotalMajorCredits += pC->getCredits();

		else if (pC->getCourseType() == MINOR)
			TotalMinorCredits += pC->getCredits();

		else if (pC->getCourseType() == CONE || pC->getCourseType() == CONC)
			TotalConcentrationCredits += pC->getCredits();
		else if (pC->getCourseType() == TRACKE || pC->getCourseType() == TRACKC)
			TotalTrackCredits += pC->getCredits();
	}
	return true;
}

bool StudyPlan::DeleteCourseFromPlan(Course* pC, int year, SEMESTER sem)
{
	
	plan[year - 1]->DeleteCourse(pC, sem);
	if (pC != nullptr) {
		TotalCredits -= pC->getCredits();
		if (pC->getCourseType() == UNIVE || pC->getCourseType() == UNIVC)
			TotalUnivCredits -= pC->getCredits();

		else if (pC->getCourseType() == MAJORE || pC->getCourseType() == MAJORC)
			TotalMajorCredits -= pC->getCredits();

		else if (pC->getCourseType() == MINOR)
			TotalMinorCredits -= pC->getCredits();

		else if (pC->getCourseType() == CONE || pC->getCourseType() == CONC)
			TotalConcentrationCredits -= pC->getCredits();
		else if (pC->getCourseType() == TRACKE || pC->getCourseType() == TRACKC)
			TotalTrackCredits -= pC->getCredits();
	}

	return true;
}
void StudyPlan::SAVE(ofstream& file)
{

	for (int r = 0; r < plan.size(); r++)
	{
		AcadYear = plan[r];
		file << "year" << " " << r + 1 << ",";
		AcadYear->SAVE_FALL(file);
		file << endl;
		file << "year" << " " << r + 1 << ",";
		AcadYear->SAVE_SPRING(file);
		file << endl;
		file << "year" << " " << r + 1 << ",";
		AcadYear->SAVE_SUMMER(file);
		file << endl;

	}
	file.close();
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}

int StudyPlan::getTotalCredits() const {
	return TotalCredits;
}

void StudyPlan::setCourseCoordinate(Registrar* pReg) {
	for (int i = 0; i < plan.size(); i++) {
		plan[i]->setCourseCoordinate( pReg);
	}
}
void StudyPlan::CheckStudyPlanCredits() {
	int i = 0;
	if (TotalCredits <= 11) {
		planWarning->moderate.push_back("Plan is Empty, please construct your plan first");
	}

	else {
		for (auto ptr = plan.begin(); ptr < plan.end(); ptr++) {

			if ((*ptr)->checkFallCredits() == -1) {
				string warning = "Moderate Issue: Year " + to_string(i + 1) + " Fall semester : There is an Underload, you may need Underload petition";
				planWarning->moderate.push_back(warning);
			}
			else if ((*ptr)->checkFallCredits() == 1) {
				string warning = "Moderate Issue: Year " + to_string(i + 1) + " Fall semester : There is an Overload,you may need Overload petition";
				planWarning->moderate.push_back(warning);
			}

			if ((*ptr)->checkSpringCredits() == -1) {
				string warning = "Moderate Issue: Year " + to_string(i + 1) + " Spring semester : There is an Underload you may need Underload petition";
				planWarning->moderate.push_back(warning);
			}
			else if ((*ptr)->checkSpringCredits() == 1) {
				string warning = "Moderate Issue: Year " + to_string(i + 1) + " Spring semester : There is an Overload, you may need Overload petition ";
				planWarning->moderate.push_back(warning);
			}
			if ((*ptr)->checkSummerCredits() == 1) {
				string warning = "Moderate Issue: Year " + to_string(i + 1) + " Summer semester : There is an Overload, you may need Overload petition ";
				planWarning->moderate.push_back(warning);
			}
			++i;
		}
	}
}

bool StudyPlan::CheckExistanceOfCourse(Course_Code code) const {
	bool x = false;;
	for (int i = 0; i < plan.size(); i++){
      x=plan[i]->CheckExistanceOfCourse(code);
	  if (x == true)
		  return true;

}
      return x;
}

void  StudyPlan::UnselectCourses_SP(Course* pcourse)
{
	for (auto year = 0; year < plan.size(); year++)
	{
		AcadYear = plan[year];
		AcadYear->UnselectCourses_AY(pcourse);
	}
}


Warnings* StudyPlan::getWarnings()  {
	return planWarning;
}


Course* StudyPlan::Check_Course_coordinates_SP(int X_coor, int Y_coor) 
{
	AcademicYear* pYear;
	for (auto year = 0; year < plan.size(); year++)
	{
		pYear = plan[year];
		Course* pCourse = pYear->Check_Course_coordinates(X_coor, Y_coor);
		if (pCourse != nullptr)
			return pCourse;
	}
	return nullptr;
}

//###################################rodina part########################################
void StudyPlan::Check_Prereq_studyplan()
{
	bool result;
	for (auto year = 0; year < plan.size(); year++)
	{
		AcadYear = plan[year];


		if (year == 0)
		{
			vector <Course*> course_codes = AcadYear->check_Prereq();

			if (!course_codes.empty())
			{
				for (int r = 0; r < course_codes.size(); r++)
				{
					string CCode = course_codes[r]->getCode();
					planWarning->Prereqwarning.push_back(CCode);
				}
			}
		}

		if (year > 0)
		{
			vector <Course*>  vector_courses = AcadYear->check_Prereq();

			if (!vector_courses.empty())
			{
				for (int vector_course = 0; vector_course < vector_courses.size(); vector_course++)
				{
					Course* course = vector_courses[vector_course];
					vector<string> Course_codes;

					for (int YEAR = 0; YEAR < year; YEAR++)
					{
						AcadYear = plan[YEAR];
					    result= AcadYear->Check_Prereq_in_Years(course);
						if (result == true)
							break;
					}
					if (result == false) 
							planWarning->Prereqwarning.push_back(course->getCode());
				}
			}

		}
	}
}
void StudyPlan::Check_Coreq_studyplan()
{

	for (auto year = 0; year < plan.size(); year++)
	{
		AcadYear = plan[year];
		vector <string> course_codes = AcadYear->check_Coreq();

		for (int r = 0; r < course_codes.size(); r++)
		{
			planWarning->Coreqwarning.push_back(course_codes[r]);
		}

	}

}


int StudyPlan::getTotalMajorCredits() const
{
	return TotalMajorCredits;
}
int StudyPlan::getTotalTrackCredits()  const
{
	return TotalTrackCredits;
}
int StudyPlan::getTotalConcentrationCredits()  const
{
	return TotalConcentrationCredits;
}
int StudyPlan::getTotalMinorCredits()  const
{
	return TotalMinorCredits;
}
int StudyPlan::getTotalUnivCredits() const
{
	return TotalUnivCredits;
}


void StudyPlan::Check_Comp_Univ_Studyplan(Registrar* preg)
{
	string coursecode_UC;
	bool result = false;

	for (int i = 0; i < preg->getRegRules().UnivCompulsory.size(); i++)
	{
		coursecode_UC = preg->getRegRules().UnivCompulsory[i];

		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			 result = AcadYear->Check_Course(coursecode_UC); //function in the academic year that check if all the UnivCompulsory courses of the vector are in the study plan of the student.
			if (result == true)
				break;
		}
		if (result == false)
		{
			planWarning->uniCOMIssues.push_back(coursecode_UC);
		}

	}

}
void StudyPlan::Check_Elective_Univ_Studyplan(Registrar* preg)
{
	string coursecode_UE;
	bool result = false;

	for (int i = 0; i < preg->getRegRules().UnivElective.size(); i++)
	{
		coursecode_UE = preg->getRegRules().UnivElective[i];

		for (auto year = 0; year < plan.size(); year++)
		{

			AcadYear = plan[year];
			 result = AcadYear->Check_Course(coursecode_UE); //function in the academic year that check if all the UnivElective courses of the vector are in the study plan of the student
			if (result == true)
				break;
		}
		if (result == false)
		{
			planWarning->UNIVelectiveIssues.push_back(coursecode_UE);
		}

	}

}
void StudyPlan::Check_Comp_Track_Studyplan(Registrar* preg)
{
	string coursecode_CT;
	bool result = false;

	for (int i = 0; i < preg->getRegRules().TrackCompulsory.size(); i++)
	{
		coursecode_CT = preg->getRegRules().TrackCompulsory[i];
		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			 result = AcadYear->Check_Course(coursecode_CT); //function in the academic year that check if all the Track compulsory courses of the vector are in the study plan of the student
			if (result == true)
				break;
		}
		if (result == false)
		{
			planWarning->TrackCOMIssues.push_back(coursecode_CT);
		}

	}
}


void StudyPlan::Check_Comp_Major_Studyplan(Registrar* preg)
{
	string coursecode_CM;
	bool result = true;

	for (int i = 0; i < preg->getRegRules().MajorCompulsory.size(); i++)
	{
		coursecode_CM = preg->getRegRules().MajorCompulsory[i];

		for (auto year = 0; year < plan.size(); year++)
		{
			result = false;
			AcadYear = plan[year];
		    result = AcadYear->Check_Course(coursecode_CM); //function in the academic year that check if all the mAJOR compulsory courses of the vector are in the study plan of the student
			if (result == true)
				break;
		}
		if (result == false)
		{
			planWarning->MajorCOMIssues.push_back(coursecode_CM);
		}

	}

}
void StudyPlan::Check_Elective_Major_Studyplan(Registrar* preg)
{
	string coursecode_EM;
	bool result = true;

	for (int i = 0; i < preg->getRegRules().MajorElective.size(); i++)
	{
		coursecode_EM = preg->getRegRules().MajorElective[i];
		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			result = AcadYear->Check_Course(coursecode_EM); //function in the academic year that check if all the mAJOR compulsory courses of the vector are in the study plan of the student
			if (result == true)
				break;
		}
		if (result == false)
		{
			planWarning->MajorElectiveIssues.push_back(coursecode_EM);
		}

	}


}


list<Course*> StudyPlan::getCourses(int year, SEMESTER sem)
{
	AcademicYear* Yc = plan[year - 1];
	return Yc->getCourses(sem);

}
//ISLam
SLevel StudyPlan::get_student_level() const
{
	return student_level;
}

void StudyPlan::set_student_level(SLevel level)
{
	student_level = level;
}

void StudyPlan::set_TotalCredits(int T_Crd)
{
	TotalCredits = T_Crd;
} 
x_y_year_semester StudyPlan::co_ordinates(int x, int y) /// + year + semester 
{
	int xs = 80;
	int ys = 30;

	int x_co =0, y_co=0;
	SEMESTER semester = FALL; // initialization
	int year=1;
	/////////////////////////////////////////////////////////////////////////////
	if ((y > 600 - 60 - 3 * ys) && (y < 600 - 60 - 0 * ys))
	{
		if ((y > 600 - 60 - 1 * ys) && (y < 600 - 60 - 0 * ys))
		{
			semester = FALL;
			y_co = 600 - 60 - 1 * ys;
		}
		else if ((y > 600 - 60 - 2 * ys) && (y < 600 - 60 - 1 * ys))
		{
			semester = SPRING;
			y_co = 600 - 60 - 2 * ys;
		}
		else if ((y > 600 - 60 - 3 * ys) && (y < 600 - 60 - 2 * ys))
		{
			semester = SUMMER;
			y_co = 600 - 60 - 3 * ys;
		}
		year = 1;
	}
	else if ((y > 600 - 60 - 6 * ys) && (y < 600 - 60 - 3 * ys))
	{
		if ((y > 600 - 60 - 4 * ys) && (y < 600 - 60 - 3 * ys))
		{
			semester = FALL;
			y_co = 600 - 60 - 4 * ys;
		}
		else if ((y > 600 - 60 - 5 * ys) && (y < 600 - 60 - 4 * ys))
		{
			semester = SPRING;
			y_co = 600 - 60 - 5 * ys;
		}
		else if ((y > 600 - 60 - 6 * ys) && (y < 600 - 60 - 5 * ys))
		{
			semester = SUMMER;
			y_co = 600 - 60 - 6 * ys;
		}
		year = 2;
	}
	else if ((y > 600 - 60 - 9 * ys) && (y < 600 - 60 - 6 * ys))
	{
		if ((y > 600 - 60 - 7 * ys) && (y < 600 - 60 - 6 * ys))
		{
			semester = FALL;
			y_co = 600 - 60 - 7 * ys;
		}
		else if ((y > 600 - 60 - 8 * ys) && (y < 600 - 60 - 7 * ys))
		{
			semester = SPRING;
			y_co = 600 - 60 - 8 * ys;
		}
		else if ((y > 600 - 60 - 9 * ys) && (y < 600 - 60 - 8 * ys))
		{
			semester = SUMMER;
			y_co = 600 - 60 - 9 * ys;
		}
		year = 3;
	}
	else if ((y > 600 - 60 - 12 * ys) && (y < 600 - 60 - 9 * ys))
	{
		if ((y > 600 - 60 - 10 * ys) && (y < 600 - 60 - 9 * ys))
		{
			semester = FALL;
			y_co = 600 - 60 - 10 * ys;
		}
		else if ((y > 600 - 60 - 11 * ys) && (y < 600 - 60 - 10 * ys))
		{
			semester = SPRING;
			y_co = 600 - 60 - 11 * ys;
		}
		else if ((y > 600 - 60 - 12 * ys) && (y < 600 - 60 - 11 * ys))
		{
			semester = SUMMER;
			y_co = 600 - 60 - 12 * ys;
		}
		year = 4;
	}
	else if ((y > 600 - 60 - 14 * ys) && (y < 600 - 60 - 12 * ys))
	{
		if ((y > 600 - 60 - 13 * ys) && (y < 600 - 60 - 12 * ys))
		{
			semester = FALL;
			y_co = 600 - 60 - 13 * ys;
		}
		else if ((y > 600 - 60 - 14 * ys) && (y < 600 - 60 - 13 * ys))
		{
			semester = SPRING;
			y_co = 600 - 60 - 14 * ys;
		}
		year = 5;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	list<Course*> courses = getCourses(year, semester);
	x_co = courses.size() * xs + 120;

	x_y_year_semester  st;
	st.x_co = x_co;
	st.y_co = y_co;
	st.year = year;
	st.semester = semester;
	return st;
}
StudyPlan::~StudyPlan()
{
	delete AcadYear;
	delete planWarning;
	for (auto p = 0; p < plan.size(); ++p)
		delete plan[p];
}
