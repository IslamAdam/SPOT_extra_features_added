#pragma once
#include <list>
#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"

class Registrar;
using namespace std;

//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	 int MaxCrdFall=18;    int MinCrdFall=12; 
	 int MaxCrdSpring=18;    int MinCrdSpring=12;
	 int MaxSummer=6;
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	
public:
	AcademicYear();
	virtual ~AcademicYear();
	list<Course*> getYearCourses();      // Return 3 lists of pointers in courses for fall , spring, summer
	bool AddCourse(Course*, SEMESTER );       //Add course to one Academic year in the student's plan
	bool DeleteCourse(Course* pC, SEMESTER sem);     //Delete Course from one Academic year in the student's plan
	int SemesterCredits(SEMESTER);
	int checkFallCredits() ;
	int checkSpringCredits() ;
	Course* Check_Course_coordinates(int X_coor, int Y_coor);
	int checkSummerCredits() ;
	bool CheckExistanceOfCourse(Course_Code code) const;
	int getIndex(Course * pCourse);
	void setCourseCoordinate(Registrar* pReg);
	//############################# Rodina  #######################
	Course* Return_Course_Pointer();
	void UnselectCourses_AY(Course*);
	bool Check_Course(string code);
	vector<string> check_Coreq() const;
	vector<Course*> check_Prereq() const;
	void virtual DrawMe(GUI*) const;
	bool Check_Prereq_in_Years(Course*);
	void SAVE_FALL(ofstream& file);
	void SAVE_SPRING(ofstream& file);
	void SAVE_SUMMER(ofstream& file);
	//ISLAM################
	list<Course*> getCourses(SEMESTER sem);
	int get_TotalCredits() const;
	void set_TotalCredits(int T_Crd);
};

