#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include "mysql.h"
// IP ADDRESS: 192.168.8.101
using namespace std;

struct node
{
	int    SerialKey;
	int    LectureRoomNo;
	int    Semester;
	char   Section;
	string TeacherName;;
	string CourseName;
	string FromTime;
	string ToTime;
	string Day;
	node* next;

};

class TimeTable
{

public:

	int    SerialKey;
	int    LectureRoomNo;
	int    Semester;
	char   Section;
	string TeacherName;;
	string CourseName;
	string FromTime;
	string ToTime;
	string Day;

	node* head;
	node* tail;

	TimeTable()
	{
		head = NULL;
		tail = NULL;
	}

    MYSQL_RES* Perform_Query(MYSQL* connection, const char* query)
    {
    // send the query to the database
        if (mysql_query(connection, query))
        {
            cout << "MySQL query error : %s\n" << mysql_error(connection) << endl;
            exit(1);
        }

    return mysql_use_result(connection);
    }

	void SaveTimeTable(node* temp)
	{
        string mainServer="192.168.8.101";
        string mainDbUser="anas";
        string mainDbPass="anas";
        MYSQL *connect; //database connection variable

        connect=mysql_init(NULL);
        if (!connect)
        {
            cout<<"Could not Initiate Database Connector\n";
            return;
        }

        if (mysql_real_connect(connect, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(), "time table" ,0,NULL,0))
        {
            cout<<"Connection done\n";
            MYSQL_RES* res = Perform_Query(connect, "insert into time_table(Room, Lecturar_Name, Section, Course, Time, Day)values("temp->LectureRoomNo", '"temp->TeacherName"', '"temp->Semester<<" "<<temp->Section"', '"temp->CourseName"', '"temp->FromTime<<"-"<<temp->ToTime"', '"temp->Day"')");
        }

        else
        {
            cout<<mysql_error(connect)<<endl;
        }
        mysql_close (connect);

	}

	//Function to Check The Serial Key Is Unique or Not
	node* CheckSerialKey(int SerKey)
	{
		node* temp = NULL;
		node* ptr = head;

		while (ptr != NULL)
		{
			if (ptr->SerialKey == SerKey)
			{
				temp = ptr;
			}
			ptr = ptr->next;
		}
		return temp;
	}

	//Function to Generate time table
	void GenerateTimeTable(TimeTable& T)
	{
		node* temp = new node;
		temp->SerialKey = T.SerialKey;
		temp->LectureRoomNo = T.LectureRoomNo;
		temp->Semester = T.Semester;
		temp->Section = T.Section;
		temp->TeacherName = T.TeacherName;
		temp->CourseName = T.CourseName;
		temp->FromTime = T.FromTime;
		temp->ToTime = T.ToTime;
		temp->Day = T.Day;
		temp->next = NULL;

		if (head == NULL)
		{
			head = temp;
			tail = temp;
			cout << "\t\tSUCCESSFULLY TIME TABLE ADDED" << endl;
		}
		else
		{
			tail->next = temp;
			tail = tail->next;
			cout << "\t\tSUCCESSFULLY TIME TABLE ADDED" << endl;
		}

		SaveTimeTable(temp); // calling function to save data in excel file
		system("pause");
		system("cls");
	}

	//Function to display time table
	void DisplayGeneratedTimeTable()
	{
		char show[100];
		/*ifstream infile;
		infile.open("Time Table.csv", ios::in);

		if (infile.is_open())
		{
			while (infile.good())
			{
				infile.getline(show, 100, ',');
				cout << show << "   ";
			}
		}

		else
			cout << "\t\tNot Found" << endl;

        */
		cout << "\n\n\n";
		system("PAUSE");
		system("CLS");
	}

	//Function to delete time table
	void deleteNodeByKey(int SerKey)
	{
		if (head == NULL)
		{
			cout << "\t\tTIME TABLE IS EMPTY, CAN'T DELETE THE TIME TABLE'" << endl;
		}
		else if (head != NULL)
		{
			if (head->SerialKey == SerKey)
			{
				node* temp = head;
				head = head->next;
				delete temp;
				cout << "\t\tSUCCESSFULLY TIME TABLE DELETED WITH THE SERIAL KEY VALUE : " << SerKey << endl;
			}
			else
			{
				node* temp = NULL;
				node* prevptr = head;
				node* currentptr = head->next;
				while (currentptr != NULL)
				{
					if (currentptr->SerialKey == SerKey)
					{
						temp = currentptr;
						currentptr = NULL;
					}
					else
					{
						prevptr = prevptr->next;
						currentptr = currentptr->next;
					}
				}
				if (temp != NULL)
				{
					prevptr->next = temp->next;
					cout << "\t\tSUCCESSFULLY TIME TABLE DELETED WITH THE SERIAL KEY VALUE : " << SerKey << endl;
				}
				else
				{
					cout << "\t\tNO TIME TABLE FOUND AGAINST THE SERIAL KEY VALUE: " << SerKey << endl;
				}
			}
		}
	}

	//Function to update the time table
	void UpdateTimeTable(TimeTable& T)
	{
		node* ptr = CheckSerialKey(T.SerialKey);
		if (ptr != NULL)
		{
			ptr->LectureRoomNo = T.LectureRoomNo;
			ptr->Semester = T.Semester;
			ptr->Section = T.Section;
			ptr->TeacherName = T.TeacherName;
			ptr->CourseName = T.CourseName;
			ptr->FromTime = T.FromTime;
			ptr->ToTime = T.ToTime;
			ptr->Day = T.Day;
			cout << "\t\tTIME TABLE UPDATED SUCCESSFULLY" << endl;
		}
		else
		{
			cout << "\t\tNO TIME TABLE FOUND AGAINST THE SERIAL KEY VALUE: " << T.SerialKey << endl;
		}
	}


};

int main()
{
	system("color 3F");

	TimeTable T;

	int    options;

	do {
	main1:
		cout << "\t\t**********************************************************************************" << endl;
		cout << "\t\t__________________________________________________________________________________" << endl;
		cout << "\t\t\t\t\t\tTIME TABLE GENERATOR" << endl;
		cout << "\t\t__________________________________________________________________________________" << endl;
		cout << "\t\t**********************************************************************************" << endl;
		cout << "\t\tPRESS 1 : TO GENERATE TIME TABLE" << endl;
		cout << "\t\tPRESS 2 : TO DISPLAY THE GENERATED TIME TABLE" << endl;
		cout << "\t\tPRESS 3 : TO DELETE THE TIME TABLE" << endl;
		cout << "\t\tPRESS 4 : TO UPDATE THE TIME TABLE" << endl;
		cout << "\t\tPRESS 5 : FOR GROUP INFORMATION" << endl;
		cout << "\t\tPRESS 6 : TO CLEAR SCREEN" << endl;
		cout << "\t\tPRESS 0 : TO EXIT" << endl;
		cout << "\t\t__________________________________________________________________________________" << endl;
		cout << "\t\t**********************************************************************************" << endl;
		cout << "\t\tYOUR SELECTED OPTION : ";
		cin >> options;

		switch (options)
		{
		case 1:
		{
		up:
			cout << "\n";
			cout << "\t\tENTER SERIAL KEY      : ";
			cin >> T.SerialKey;
			if (T.CheckSerialKey(T.SerialKey) != NULL)
			{
				cout << "\t\tNOTE : REMEMBER SERIAL KEY SHOULD BE UNIQUE EVERY TIME" << endl;
				goto up;
			}
			cout << "\t\tENTER SEMESTER        : ";
			cin >> T.Semester;
			cout << "\t\tENTER SECTION         : ";
			cin >> T.Section;
			cout << "\t\tENTER COURSE NAME     : ";
			cin.ignore();
			getline(cin, T.CourseName);
			cout << "\t\tENTER COURSE TEACHER NAME    : ";
			getline(cin, T.TeacherName);
			cout << "\t\tENTER DAY : ";
			cin >> T.Day;
			cout << "\t\tENTER FROM TIME       : ";
			cin >> T.FromTime;
			cout << "\t\tENTER TO TIME         : ";
			cin >> T.ToTime;
			cout << "\t\tENTER LECTURE ROOM NO : ";
			cin >> T.LectureRoomNo;
			T.GenerateTimeTable(T);
			break;
		}
		case 2:
		{
			T.DisplayGeneratedTimeTable();
			break;
		}
		case 3:
		{
			cout << "\t\tENTER SERIAL KEY TO DELETE THE TIME TABLE : ";
			cin >> T.SerialKey;
			if (T.CheckSerialKey(T.SerialKey) == NULL)
			{
				cout << "\t\tSERIAL KEY NOT FOUND IN THE TIME TABLE RECORDS" << endl;
				goto main1;
			}
			T.deleteNodeByKey(T.SerialKey);
			break;
		}
		case 4:
		{
			cout << "\t\tENTER SERIAL TO BE UPDATE THE TIME TABLE : ";
			cin >> T.SerialKey;
			if (T.CheckSerialKey(T.SerialKey) == NULL)
			{
				cout << "\t\tSERIAL KEY NOT FOUND IN THE TIME TABLE RECORDS" << endl;
				goto main1;
			}
			cout << "\t\tENTER NEW SEMESTER        : ";
			cin >> T.Semester;
			cout << "\t\tENTER NEW SECTION         : ";
			cin >> T.Section;
			cout << "\t\tENTER NEW COURSE NAME     : ";
			cin.ignore();
			getline(cin, T.CourseName);
			cout << "\t\tENTER NEW COURSE TEACHER NAME    : ";
			getline(cin, T.TeacherName);
			cout << "\t\tENTER NEW DAY : ";
			cin >> T.Day;
			cout << "\t\tENTER NEW FROM TIME       : ";
			cin >> T.FromTime;
			cout << "\t\tENTER NEW TO TIME         : ";
			cin >> T.ToTime;
			cout << "\t\tENTER NEW LECTURE ROOM NO : ";
			cin >> T.LectureRoomNo;
			T.UpdateTimeTable(T);
			break;
		}
		case 5:
		{
			system("cls");
			cout << endl << " " << setw(100) << "====================================================================================" << endl;
			cout << setw(65) << " ABOUT US";
			cout << endl << " " << setw(100) << "====================================================================================" << endl;
			cout << endl << setw(103) << "||                               BSEM-F19-(3B)                                     ||";
			cout << endl << setw(103) << "||                           SEMESTER 3 PROJECT                                    ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||             NAME :                                     ROLL NO :                ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||         M. Muneeb Saleem                                 072                    ||";
			cout << endl << setw(103) << "||         M. Anas                                          190                    ||";
			cout << endl << setw(103) << "||         Bareerah Batool                                  095                    ||";
			cout << endl << setw(103) << "||         M. Usman Khan                                    074                    ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||        TEACHER NAME:                Ma'am Tahreem Masoood                       ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||                                                                                 ||";
			cout << endl << setw(103) << "||                     Superior University Lahore Gold Campus                      ||";
			cout << endl << setw(80) << "  <-------------------------------------->" << endl << endl << endl;
			system("pause");
			break;
		}
		case 6:
		{
			system("CLS");
			break;
		}
		case 0:
		{
			cout << "\n\t\tTHANKS FOR USING OUR PROGRAM" << endl;
			break;
		}
		default:
		{
			cout << "\n\t\tWRONG OPTION SELECTED" << endl;
			break;
		}
		}

	} while (options != 0);

	return 0;
}
