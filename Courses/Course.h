#pragma once
#include <string>
#include <list>
#include "../GUI/CMUgraphicsLib/colors.h"

#include "..\DEFs.h"

#include "../GUI/Drawable.h"
using namespace std;
//Base class for all types of courses
enum STATUS
{
	Done_,
	Progress,
	Pending
};


class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	CourseType type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
	int x_Coordinate;                // x coordinate
	int y_Coordinate;                // y coordinate of course
	color course_color;
	double GPA;
	STATUS status;

public:
	Course(Course_Code r_code,string r_title, int crd);
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	void setCoReq(vector<Course_Code> Co) ;
	void setPreReq(vector<Course_Code> Pre) ;
	void setX(int newx);
	void setY(int newy);
	int getX() const;
	int getY() const;
	CourseType getCourseType() const;
	void DrawMe(GUI*) const;
	Course* get_Specified_Course(int X_coor, int Y_coor) ;
	void setCredits(int crd) ;
	list<Course_Code> getPreReq() const;
	list<Course_Code> getCoReq() const;
	void  SaveMe(ofstream& file);
	virtual ~Course();
	//################################islam
	void SetCourseGPA(double newGPA);
	STATUS Get_course_STATUS() const;
	void SetCourseSTATUS(STATUS newstatus);
	color Get_course_color() const;
	void SetCourseColor(color newcolor);
	double Get_Course_GPA() const;
	void setType(CourseType t);

};
