#include "Course.h"
#include "../GUI/GUI.h"

Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
	course_color = SNOW; //  FillColor;
	GPA = -1; // default value to overwrite it when calculating the GPA
	status = Done_;
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}
void Course::setX(int newx) {
	x_Coordinate = newx;
}
void Course::setY(int newy) {
	y_Coordinate = newy;
}
int Course::getX() const {
	return x_Coordinate;
}
int Course::getY() const {
	return y_Coordinate;
}



//return course credits
int Course::getCredits() const
{
	return credits;
}
CourseType Course::getCourseType() const {
	return type;
}

void Course::DrawMe(GUI* pG) const
{
	
	pG->DrawCourse(this);
}
Course* Course::get_Specified_Course(int X_coor, int Y_coor) 
{

	if (((X_coor > GfxInfo.x) && (X_coor < (GfxInfo.x + CRS_WIDTH))) && ((Y_coor > GfxInfo.y) && (Y_coor < (GfxInfo.y + CRS_HEIGHT))))
	{
		return this;
	}
	else
		return nullptr;
}
void Course::setCredits(int crd) {
	credits = crd;
}
void Course::setCoReq(vector<Course_Code> Co) {
	for (int i = 0; i < Co.size(); ++i)
		CoReq.push_back(Co[i]);
}

void Course::setPreReq(vector<Course_Code> Pre) {
	for (int i = 0; i < Pre.size(); ++i)
		PreReq.push_back(Pre[i]);
}

list<Course_Code> Course::getPreReq() const {
	return PreReq;
}

list<Course_Code> Course::getCoReq() const {
	return CoReq;
}
void Course::SaveMe(ofstream& file)
{

	file << code << ",";
	
}
//##############################islam
color Course::Get_course_color() const
{
	return course_color;
}
void Course::SetCourseColor(color newcolor)
{
	course_color = newcolor;
}
double Course::Get_Course_GPA() const
{
	return GPA;
}
void Course::SetCourseGPA(double newGPA)
{
	GPA = newGPA;
}
STATUS Course::Get_course_STATUS() const
{
	return status;
}
void Course::SetCourseSTATUS(STATUS newstatus)
{
	status = newstatus;
}
void Course::setType(CourseType t) {
	type = t;
}
Course::~Course()
{
}