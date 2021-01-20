#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
#include<string>
class Registrar;
using namespace std;
enum SLevel
{
	Freshman,
	Sophomore,
	Junior,
	Senior
};

struct x_y_year_semester
{
	int x_co;
	int y_co;
	int year;
	SEMESTER semester;
};
//A full study plan for as student
struct Warnings {
	vector<string> moderate;         //Min /max crd per semester
	vector<string> credits;          // Number of credits
	vector<Course_Code> uniCOMIssues;
	vector<Course_Code> TrackCOMIssues;
	vector<Course_Code> UNIVelectiveIssues;
	vector<Course_Code> MajorCOMIssues;
	vector<Course_Code> Prereqwarning;
	vector<Course_Code> Coreqwarning;
	vector<Course_Code> MajorElectiveIssues;
};
      class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*> plan;	  //plan is a list of academic years
	string PlanNotes;
	Warnings* planWarning;
	SLevel student_level;

protected:
	AcademicYear* AcadYear;

public:
	StudyPlan();
	vector<AcademicYear*> getPplan() const; // function that return pointer on plan vector which is a vector of pointers in AcademicYear
	bool AddCourse(Course*, int year, SEMESTER);
	bool DeleteCourseFromPlan(Course*, int , SEMESTER);
	void virtual DrawMe(GUI*) const;
	void CheckStudyPlanCredits();
	bool CheckExistanceOfCourse(Course_Code code) const;
	Warnings *getWarnings();
	Course* Check_Course_coordinates_SP(int X_coor, int Y_coor);
	int getTotalCredits() const;
	//#########################rodina
	void Check_Prereq_studyplan();
	void UnselectCourses_SP(Course*);
	virtual ~StudyPlan();
	void Check_Coreq_studyplan();
	int getTotalUnivCredits() const;
	int getTotalMajorCredits() const;
	int getTotalTrackCredits()  const;
	int getTotalConcentrationCredits() const;
	int getTotalMinorCredits()  const;

	void Check_Comp_Univ_Studyplan(Registrar* preg);
	void Check_Elective_Univ_Studyplan(Registrar* preg);

	void Check_Comp_Track_Studyplan(Registrar* preg);

	void Check_Comp_Major_Studyplan(Registrar* preg);
	void Check_Elective_Major_Studyplan(Registrar* preg);

	void SAVE(ofstream& filename);
	list<Course*> getCourses(int year, SEMESTER sem);
	//#############################islam
	SLevel get_student_level() const;
	void set_student_level(SLevel level);
	void set_TotalCredits(int T_Crd);
	x_y_year_semester co_ordinates(int x, int y);
	void setCourseCoordinate(Registrar* pReg);

};

