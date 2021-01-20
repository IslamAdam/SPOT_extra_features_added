#pragma once
#include <string>
#include <fstream>
using namespace std;
#include"Drawable.h"
#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "..//Actions/Action.h"

class Course;
class AcademicYear;
class Note;

//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course
		ITM_ADD_NOTE,
		ITM_SHOW_NOTE,
		ITM_STU_LEVEL,
	    ITM_SAVE,
		ITM_DISPLAY_INFO,
		ITM_Drag,
        ITM_DEL,
		ITM_CHANGE,
		ITM_CHECK,
		GPA_CALCULATOR,
		ITM_COURSE_STATUS,
		ITM_LOAD_PLAN,
		ITM_MINOR,		//Exit item
		ITM_LOAD_ROULES,
		ITM_LOAD_CONCENTRATION,
		ITM_CNT			//no. of menu items ==> This should be the last line in this enum

	};

	//Some constants for GUI
	const int	WindWidth = 1000, WindHeight = 600,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 60,	//Status Bar Height
		MenuBarHeight = 80,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 60,	   //Width of each item in the menu
		YearWidth = 80,
		YearHeight = 30,
		semHeight = 30;
	static const int W = 350, L = 200, Start = 100, End = 200;
	string InfowindTitle = "Course Information";

	color DrawColor = BLACK;		//Drawing color
	color FillColor = SNOW;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLUE;			//Messages color
	color infoColor= BLACK;
	color BkGrndColor = LAVENDER;	   //Background color
	color StatusBarColor = DARKGRAY;   //statusbar color
	color YearColor = BLANCHEDALMOND;
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";
	color UNIVCcolor = YELLOW;
	color UNIVEcolor = BLACK;
	color MAJOREcolor = SEAGREEN;
	color MAJORCcolor = DARKMAGENTA;
	color TRACKEcolor = YELLOW;
	color TRACKCcolor = ROYALBLUE;
	color CONCcolor = GREEN;
	color MINORcolor = DARKOLIVEGREEN;
	
	

	window* pWind;
	window* pNoteWind;
	window* pValidityWindow;
	window* p_Infowind;
	
public:
	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void DrawCourse(const Course* );
	void DrawAcademicYear(const AcademicYear*);
	void DrawNotes(vector <string> totalnotes);
	void UpdateInterface() const;
	//input functions
	ActionData GetUserAction(string msg = "") const;
	string GetSrting() const;
	void DrawStringModerate(string s ,int x,int y);
	void OpenCheckWindow();
	void CLoseCheckReport();
	void DrawStringCritical(string s, int x, int y);
	void Info_Window(Course*);
	void DrawString(string s, int x, int y);
	//##########################################islam
	void Change_Course_Color(/*const Course* pCrs*/); ///////////////////////////////
	graphicsInfo DragCourse(const Course*) const;


	

	~GUI();
};

