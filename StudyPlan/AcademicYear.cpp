#include "AcademicYear.h"
#include<iostream>
#include "../GUI/GUI.h"
#include <iterator>
#include"..//Courses/Course.h"
#include"..//Registrar.h"
using namespace std;
AcademicYear::AcademicYear()
{
	
}



//Adds a course to this year in the spesified semester
list<Course*> AcademicYear::getYearCourses() {
	return YearCourses[SEM_CNT];
}


bool AcademicYear::AddCourse(Course* pC, SEMESTER sem) 
{ 
	if (pC != nullptr) {
		YearCourses[sem].push_back(pC);
		TotalCredits = TotalCredits+ pC->getCredits();

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
		return true;
	}
	return false;
	
}
bool AcademicYear::DeleteCourse(Course* pC, SEMESTER sem)
{
	if (pC != nullptr) {
		for (auto ptr = YearCourses[sem].begin(); ptr != YearCourses[sem].end(); ptr++) {
			if (pC == *ptr) {
				YearCourses[sem].erase(ptr);                      
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
				return true;
			}
		}
	}
	return false;
	}
bool AcademicYear::CheckExistanceOfCourse(Course_Code code) const {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (auto ptr = YearCourses[sem].begin(); ptr != YearCourses[sem].end(); ptr++) {
			if((*ptr)->getCode() == code)
			return true;
		}
	}
}
int AcademicYear::getIndex(Course* pCourse) {
	int index = 0;
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		index = 0;
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course) {
			if (pCourse == (*course)) {
				return index;
				break;
			}
			++index;

		}
	}
	return index;
}
int AcademicYear::SemesterCredits(SEMESTER semester)  {
	int semCredits = 0;
	for (auto ptr = YearCourses[semester].begin(); ptr != YearCourses[semester].end(); ++ptr) {
		semCredits += (*ptr)->getCredits();	
	}
	return semCredits;
}
int AcademicYear::checkFallCredits() {
	int semestercredits = SemesterCredits(FALL);
	if (semestercredits<MaxCrdFall && semestercredits>MinCrdFall)
		return 0;    // if no overload no underload
	if (semestercredits > MaxCrdFall)
		return 1;         // overload
	else if (semestercredits < MinCrdFall)
		return -1;        //underload 
}
int AcademicYear::checkSpringCredits()  {
	int semestercredits = SemesterCredits(SPRING);
	if (semestercredits<MaxCrdSpring && semestercredits>MinCrdSpring)
		return 0;    // if no overload no underload
	if (semestercredits > MaxCrdSpring)
		return 1;         // overload
	else if (semestercredits < MinCrdSpring)
		return -1;        //underload 

}
int AcademicYear::checkSummerCredits()  {
	int semestercredits = SemesterCredits(SUMMER);
	if (semestercredits > MaxSummer)
		return 1;
	else
		return 0;
}

Course* AcademicYear::Check_Course_coordinates(int X_coor, int Y_coor) 
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
	for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); course++)
		{
			Course* pCourse;
			pCourse = *course;
			if ((pCourse->get_Specified_Course(X_coor, Y_coor)) != nullptr)
				return pCourse;
		}

	}
	return nullptr;
}
Course* AcademicYear::Return_Course_Pointer()
{

	Course* pCOURSE;


	for (int sem = FALL; sem < SEM_CNT; sem++)
	{


		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			pCOURSE = *course;

			//coursecode = pCOURSE->getCode();

				  //return  coursecode;
			return pCOURSE;

		}

	}

}

void AcademicYear::UnselectCourses_AY(Course* pcourse)
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			if ((*course) != pcourse)
			{
				(*course)->setSelected(false);
			}
			else
				(*course)->setSelected(true);
		}

	}

}

void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course

	
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
	}
}
//##############################33 RODINA ##################
bool AcademicYear::Check_Course(string code)
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{

			if ((*course)->getCode() == (code)) {       //situation = "course is found"
				return true;
				break;
			}
		}
	}

	//situation = "course is not found!";
	return false;

}
vector<Course*> AcademicYear::check_Prereq() const
{
	list<string>Prereq;
	int index = 0;
	string code = "";
	vector<Course*>course_codes;

	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		if (sem == FALL)
		{
			for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
			{
				if(!(*course)->getPreReq().empty())
				course_codes.push_back(*course);
			}
		}
		if (sem == SPRING || sem==SUMMER)
		{
			for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
			{
				code = (*course)->getCode();
				Prereq = (*course)->getPreReq();
				
				for (auto pre = Prereq.begin(); pre != Prereq.end(); ++pre)
				{
					index = 0;

					for (int semester = FALL; semester < sem; semester++)
					{
						for (auto COURSE = YearCourses[semester].begin(); COURSE != YearCourses[semester].end(); ++COURSE)
						{
							if ((*COURSE)->getCode() == (*pre))
							{
								index = 1;
								break;
							}
							if (index == 1)
							break;
						}
						if (index == 1)
						break;
					}
					if (index == 1)
					break;
				}
				if (!Prereq.empty()) {
					if (index != 1)
						course_codes.push_back(*course);
				}
			}
		}
	}
	return  course_codes;
}
vector<string> AcademicYear::check_Coreq() const
{
	list<string>coreq;
	int index = 0;
	string code = "";
	vector<string>course_code;

	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{

			coreq = (*course)->getCoReq();
			code = (*course)->getCode();


			for (auto cor = coreq.begin(); cor != coreq.end(); ++cor)
			{
				index = 0;

				for (auto COREQ = YearCourses[sem].begin(); COREQ != YearCourses[sem].end(); ++COREQ)
				{


					if ((*COREQ)->getCode() == (*cor))
					{
						index = 1;
						break;

					}

				}
				if (index != 1)
				{
					course_code.push_back(code);
				}
			}
		}
	}
	return  course_code;
}
void AcademicYear::setCourseCoordinate(Registrar* pReg) {
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course) {
			MyYearAndSemester* yAS= pReg->GetYearAndSem((*course)->getY());
			graphicsInfo* gFx = pReg->getNewCoordinates(yAS->Year, yAS->sem,(*course));
			(*course)->setGfxInfo((*gFx));
			(*course)->setX(gFx->x);
		}
	}
}
bool AcademicYear::Check_Prereq_in_Years(Course* Pcourse)
{
	list<string>prereq;
	vector<string>C_codes;
	string course_code = "";
	int test = 0;
	course_code = Pcourse->getCode();
	prereq = Pcourse->getPreReq();
	for (auto pre = prereq.begin(); pre != prereq.end(); ++pre)
	{

		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
			{

				string code = (*course)->getCode();

				if (code == (*pre))
				{
					test = 1;
					break;
				}
			}
		}

	}
	if (test != 1)
	{
		return false;
	}
	else
	return true;
}
void AcademicYear::SAVE_FALL(ofstream& file)
{
	file << "FALL" << ",";
	for (auto course = YearCourses[FALL].begin(); course != YearCourses[FALL].end(); ++course)
	{

		(*course)->SaveMe(file);

	}
}
void AcademicYear::SAVE_SPRING(ofstream& file)
{
	file << "SPRING" << ",";

	for (auto course = YearCourses[SPRING].begin(); course != YearCourses[SPRING].end(); ++course)
	{
		(*course)->SaveMe(file);

	}

}
void AcademicYear::SAVE_SUMMER(ofstream& file)
{
	file << "SUMMER" << ",";
	for (auto course = YearCourses[SUMMER].begin(); course != YearCourses[SUMMER].end(); ++course)
	{

		(*course)->SaveMe(file);

	}

}
//#####################################islam
list<Course*> AcademicYear::getCourses(SEMESTER sem)
{
	return YearCourses[sem];
}
int AcademicYear::get_TotalCredits() const
{
	return TotalCredits;
}
void AcademicYear::set_TotalCredits(int T_Crd)
{
	TotalCredits = T_Crd;
}


AcademicYear::~AcademicYear()
{
	for (int sem = FALL; sem < SEM_CNT; sem++) {
		for (auto ptr = YearCourses[sem].begin(); ptr != YearCourses[sem].end(); ptr++)
			delete (*ptr);
	}
}
