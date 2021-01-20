#include "stdafx.h"
#include "util.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip> // necessary for setprecision
using namespace std;
#include "..\Rules.h"
#include "Import.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <sstream>


Import::Import(Registrar* p) :Action(p)
{
}

bool Import::Execute()
{
	Rules Rules_S;
	GUI* pGUI = pReg->getGUI();
	string line;
	vector<string> lines;
	string item;
	vector<string> items;

	ActionData actData = pGUI->GetUserAction("Importing");

	if ((actData.actType == LOAD))
	{
		int xs = 80;
		int ys = 30;

		pGUI->PrintMsg("Importing Study Plan");
		ifstream inFile;
		pGUI->PrintMsg("Choose Major to load its study plan: NAN or CIE ");
		string mjr = pGUI->GetSrting();
		//////////////////////////////////////////////////////////////////
		if (mjr == "CIE")
		{
			inFile.open("E:\\CIE-StudyPlan.txt");
		}
		else if (mjr == "NAN")
		{
			inFile.open("E:\\NAN_StudyPlan.txt");
		}

		cout << " line " << endl;      /////////////
		while (getline(inFile, line, '\n'))
		{
			lines.push_back(line);
			lines.push_back("end");
			cout << line << endl;  //////////////
		}
		cout << " end line " << endl;  //////////////


		for (const auto& in : lines)
		{
			auto it = std::begin(in);
			while (true)
			{
				auto commaPosition = std::find(it, std::end(in), ',');
				items.emplace_back(it, commaPosition);
				if (commaPosition == std::end(in))
				{
					break;
				}
				it = std::next(commaPosition);
			}
		}
		cout << " items " << endl;      /////////////
		for (const auto& out : items)
		{
			std::cout << out << std::endl;
		}
		cout << " end items " << endl;      /////////////

		vector<int> boundary;
		for (int i = 0; i < items.size(); i++)
		{
			if ((items[i] == "Year 1") || (items[i] == "Year 2") || (items[i] == "Year 3") || (items[i] == "Year 4") || (items[i] == "Year 5") || (items[i] == "Fall") || (items[i] == "Spring") || (items[i] == "Summer") || (items[i] == "end")) {
				boundary.push_back(i);
				cout << items[i] << endl;   ////////////////////
				cout << " boundary " << i << endl; ////////////
			}

		}
		/////////////////////////////
		int crd = 0;
		string Title = "DUMMY";
		int x = 40;

		int ys_s = 27;
		/// /////////////////////////////////////////////////////////////////////////////////////////////
		/// /////////////////////////////////////////////////////////////////////////////////////////////
		for (int j = 0; j < boundary.size(); j = j + 3)
		{
			if ((items[boundary[j]] == "Year 1") && (items[boundary[j + 1]] == "Fall"))
			{

				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 1 * ys_s; ///
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 1, FALL);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}

			}

			else if ((items[boundary[j]] == "Year 1") && (items[boundary[j + 1]] == "Spring"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 2 * ys_s; //
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 1, SPRING);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 1") && (items[boundary[j + 1]] == "Summer"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 3 * ys_s; //
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 1, SUMMER);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 2") && (items[boundary[j + 1]] == "Fall"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 4 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 2, FALL);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 2") && (items[boundary[j + 1]] == "Spring"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 5 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 2, SPRING);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 2") && (items[boundary[j + 1]] == "Summer"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 6 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 2, SUMMER);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 3") && (items[boundary[j + 1]] == "Fall"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 7 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 3, FALL);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 3") && (items[boundary[j + 1]] == "Spring"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 8 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 3, SPRING);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 3") && (items[boundary[j + 1]] == "Summer"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 9 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 3, SUMMER);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 4") && (items[boundary[j + 1]] == "Fall"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 10 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 4, FALL);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 4") && (items[boundary[j + 1]] == "Spring"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 11 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 4, SPRING);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 4") && (items[boundary[j + 1]] == "Summer"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 12 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 4, SUMMER);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 5") && (items[boundary[j + 1]] == "Fall"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 13 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 5, FALL);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}
			else if ((items[boundary[j]] == "Year 5") && (items[boundary[j + 1]] == "Spring"))
			{
				x = 40;
				for (int i = boundary[j + 1] + 1; i < boundary[j + 2]; i++) {
					Course_Code code = items[i];
					CourseInfo mycourse = pReg->getCourseInfo(code);
					StudyPlan* pS = pReg->getStudyPlay();
					if ((mycourse.Code != "000") && (pS->CheckExistanceOfCourse(code) != true)) {
						Course* pC = new Course(code, mycourse.Title, mycourse.Credits);
						x = x + xs;
						int y = 600 - 60 - 14 * ys;
						graphicsInfo gInfo{ x, y };
						pC->setGfxInfo(gInfo);
						pC->setY(y);
						pS->AddCourse(pC, 5, SPRING);
						pReg->setCourseType(pC);
						pC->setCoReq(mycourse.CoReqList);
						pC->setPreReq(mycourse.PreReqList);
						pC->setCredits(mycourse.Credits);
					}
				}
			}

		}

		pGUI->PrintMsg("Importing Study Plan Done Successfully");
		inFile.close();
		return true;
	}

	///////////////////////////////////
	/* else if (actData.actType == ADD_MINOR)
	{
		pGUI->PrintMsg("Declaring Minor");
		ifstream inFile;
		inFile.open("E:\\NANENG-Requirements.txt");
		while (getline(inFile, line, '\n'))
		{
			lines.push_back(line);
		}
		inFile.close();

		pGUI->PrintMsg("Enter the total MINOR Credites");
		int Minor_Credites = stoi(pGUI->GetSrting());
		int Total_Credites = stoi(lines[0]);
		int new_Total_Credites = Minor_Credites + Total_Credites;
		lines[0] = to_string(new_Total_Credites);

		pGUI->PrintMsg("Enter the number of Minor Courses");
		int number = stoi(pGUI->GetSrting());
		string minor_courses = "";
		for (int i = 0; i < number; i++)
		{
			pGUI->PrintMsg("Enter course number " + to_string(i + 1));
			string course = pGUI->GetSrting();
			Rules_S.Minor_Courses.push_back(course);

			if (i == (number - 1))
				minor_courses = minor_courses + course;
			else
				minor_courses = minor_courses + course + ",";
		}
		//lines[18] = minor_courses;
		lines.push_back(minor_courses);
		ofstream outFile;
		outFile.open("E:\\NANENG-Requirements.txt");
		for (int i = 0; i < lines.size(); i++)
		{
			if (i == (lines.size() - 1))
				outFile << lines[i];
			else
				outFile << lines[i] << "\n";
		}
		outFile.close();
	}
	////////////////////////////////////////////////////////////////////////////////////
	  else if (actData.actType == LOAD_RULES2)  // second major
	{
		string line3;
		vector<string> lines3;
		string item3;
		vector<string> items3;

		pGUI->PrintMsg("Importing Rules");
		ifstream inFile;
		pGUI->PrintMsg("Choose your 2nd Major: NAN or CIE ");
		string mjr = pGUI->GetSrting();
		//////////////////////////////////////////////////////////////////
		if (mjr == "CIE")
		{
			inFile.open("E:\\CIE-Requirements.txt");
		}
		else if (mjr == "NAN")
		{
			inFile.open("E:\\NANENG-Requirements.txt");
		}
		while (getline(inFile, line3, '\n'))
		{
			lines3.push_back(line3);
		}
		inFile.close();
		//////////////////////////////////////////////////////////////////

		stringstream s6(lines3[6]);
		while (s6.good())
		{
			string substr;
			getline(s6, substr, ',');
			for (int i = 0; i < Rules_S.UnivCompulsory.size(); i++)
			{
				if (substr != Rules_S.UnivCompulsory[i])
				{
					Rules_S.UnivCompulsory.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.ReqUnivCredits = Rules_S.ReqUnivCredits + mycourse.Credits;
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
		}
		stringstream s7(lines3[7]);
		while (s7.good())
		{
			string substr;
			getline(s7, substr, ',');
			for (int i = 0; i < Rules_S.UnivElective.size(); i++)
			{
				if (substr != Rules_S.UnivElective[i])
				{
					Rules_S.UnivElective.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.ElectiveUnivCredits = Rules_S.ElectiveUnivCredits + mycourse.Credits;
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
		}
		stringstream s8(lines3[8]);
		while (s8.good())
		{
			string substr;
			getline(s8, substr, ',');
			for (int i = 0; i < Rules_S.TrackCompulsory.size(); i++)
			{
				if (substr != Rules_S.TrackCompulsory[i])
				{
					Rules_S.TrackCompulsory.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.ReqTrackCredits = Rules_S.ReqTrackCredits + mycourse.Credits;
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
		}
		stringstream s9(lines3[9]);
		while (s9.good())
		{
			string substr;
			getline(s9, substr, ',');
			for (int i = 0; i < Rules_S.MajorCompulsory.size(); i++)
			{
				if (substr != Rules_S.MajorCompulsory[i])
				{
					Rules_S.MajorCompulsory.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.ReqMajorCredits = Rules_S.ReqMajorCredits + mycourse.Credits;
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
		}
		stringstream s10(lines3[10]);
		while (s10.good())
		{
			string substr;
			getline(s10, substr, ',');
			for (int i = 0; i < Rules_S.MajorElective.size(); i++)
			{
				if (substr != Rules_S.MajorElective[i])
				{
					Rules_S.MajorElective.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.ElectiveMajorCredits = Rules_S.ElectiveMajorCredits + mycourse.Credits;
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
		}

		if (mjr == "NAN")
		{
			pGUI->PrintMsg("Choose your Concentration: V => VLSI , M => MEMS , P => Photonics");
			string conc = pGUI->GetSrting();
			if (conc == "V")
			{
				stringstream s11(lines3[11]);
				while (s11.good())
				{
					string substr;
					getline(s11, substr, ',');
					Rules_S.Concentration.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
			else if (conc == "M")
			{
				stringstream s13(lines3[13]);
				while (s13.good())
				{
					string substr;
					getline(s13, substr, ',');
					Rules_S.Concentration.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
			else if (conc == "P")
			{
				stringstream s15(lines3[15]);
				while (s15.good())
				{
					string substr;
					getline(s15, substr, ',');
					Rules_S.Concentration.push_back(substr);
					CourseInfo mycourse = pReg->getCourseInfo(substr);
					Rules_S.TotalCredits = Rules_S.TotalCredits + mycourse.Credits;
				}
			}
			pGUI->PrintMsg("Importing Rules Done Successfully");
			//pReg->setRegRules(Rules_S);
			for (int i = 0; i < Rules_S.MajorCompulsory.size(); i++)
			{
				cout << Rules_S.MajorCompulsory[i] << endl;
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////
	// concentration 2 // 
else if (actData.actType == LOAD_CONCENTRATION)  // second major
	{
	string line3;
	vector<string> lines3;
	string item3;
	vector<string> items3;

	pGUI->PrintMsg("Importing Concentration 2");
	ifstream inFile;
	inFile.open("E:\\NANENG-Requirements.txt");
	while (getline(inFile, line3, '\n'))
	{
		lines3.push_back(line3);
	}
	inFile.close();
	//////////////////////////////////////////////////////
	pGUI->PrintMsg("Choose your 2nd Concentration: V => VLSI , M => MEMS , P => Photonics ");
	string conc = pGUI->GetSrting();
	stringstream s5(lines3[5]);
	items3.clear();
	while (s5.good())
	{
		string substr;
		getline(s5, substr, ',');
		items.push_back(substr);
	}
	int Conc_1_Comp, Conc_1_Elec, Conc_2_Comp, Conc_2_Elec, Conc_3_Comp, Conc_3_Elec;

	Conc_1_Comp = stoi(items[0]);
	Conc_1_Elec = stoi(items[1]);
	Conc_2_Comp = stoi(items[2]);
	Conc_2_Elec = stoi(items[3]);
	Conc_3_Comp = stoi(items[4]);
	Conc_3_Elec = stoi(items[5]);

	if (conc == "V")
	{
		stringstream s11(lines3[11]);
		while (s11.good())
		{
			string substr;
			getline(s11, substr, ',');
			Rules_S.Concentration.push_back(substr);
			Rules_S.TotalCredits = Rules_S.TotalCredits + Conc_1_Comp + Conc_1_Elec;
		}
	}
	else if (conc == "M")
	{
		stringstream s13(lines3[13]);
		while (s13.good())
		{
			string substr;
			getline(s13, substr, ',');
			Rules_S.Concentration.push_back(substr);
			Rules_S.TotalCredits = Rules_S.TotalCredits + Conc_2_Comp + Conc_2_Elec;
		}
	}
	else if (conc == "P")
	{
		stringstream s15(lines3[15]);
		while (s15.good())
		{
			string substr;
			getline(s15, substr, ',');
			Rules_S.Concentration.push_back(substr);
			Rules_S.TotalCredits = Rules_S.TotalCredits + Conc_3_Comp + Conc_3_Elec;
			}
		}
		pGUI->PrintMsg("Importing 2nd Concentration Done Successfully");
	}
	*/
}
Import::~Import()
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

