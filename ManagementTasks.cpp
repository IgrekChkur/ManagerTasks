#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdio> 
#include "Functions.h"
#pragma warning(disable : 4996)//for function strftime



int main()
{
	using namespace std;

	vector<Task> tasks;

	int choice;
	
	Introduction();

	cin >> choice;

	if (!choice)
	{
		cout << "You must enter a number from 1 to 8! \n";
		return 1;
	}
	
	while (true)
	{
		if (choice == 1)
		{
			cin.ignore();//clean buffer
			string task = "";
			cout << "\nEnter your task: ";//add a description for a task
			getline(cin, task);

			//cin.ignore();
			string date = "";//task completion date
			cout << "Enter date in this format 'DD-MM-YY HH:MM': ";
			getline(cin, date);

			cout << "Do you want to add description to your task? 1 - YES, 2 - NO: ";
			short descr; //for add description or not
			cin >> descr;

			if (descr == 1)
			{
				cin.ignore();//clean buffer
				string description = "";
				cout << "Enter a description to your task: ";
				getline(cin, description);
				addTask(tasks, task, description, date);
			}
			else if (descr == 2)
			{
				addTask(tasks, task, "", date);
			}
			else
			{
				cout << "Something go wrong, choose another option : \n";
			}
			
			cout << "Enter next command: ";
			cin >> choice;
			if (!choice)
			{
				cout << "You must enter a number from 1 to 8! \n";
			}
		}
		else if (choice == 2)
		{
			int index; // number of a task which we want to remove
			cout << "Enter index of task which you want to remove: ";
			cin >> index;
			removeTask(tasks, index);

			cout << "Enter next command: ";
			cin >> choice;
		}
		else if (choice == 3)
		{
			int index; // number of a task which we want to mark as done or not done
			cout << "Enter index of task which you want to mark: ";
			cin >> index;
			markTask(tasks, index);

			cout << "Enter next command: ";
			cin >> choice;
		}
		else if (choice == 4)
		{
			listTask(tasks);

			cout << "Enter next command: ";
			cin >> choice;
		}
		else if (choice == 5)
		{
			cout << "\nName of the file with a list of your tasks will be in this format: 'MM-DD-YYYY_DayofWeek' ";
			exportTasks(tasks, currentDateTime() + ".txt");

			cout << "Enter next command: ";
			cin >> choice;
		}
		else if (choice == 6)
		{
			string nameImportFile; //= "09-27-2023_Wednesday.txt"
			cout << "\nEnter a name of file in this format: 'MM-DD-YYYY_DayofWeek.txt' which you wnt to look: \n";
			cin.ignore();
			getline(cin, nameImportFile);
			importFromFile(nameImportFile);

			cout << "Enter next command: ";
			cin >> choice;
		}
		else if (choice == 7)//проверить
		{
			string nameImportFile; //= "09-27-2023_Wednesday.txt"
			cout << "Enter the name of file which you want to rewrite: \n";
			cin.ignore();
			getline(cin, nameImportFile);
			importFromFile(nameImportFile);
			cout << "\nThis is your list, rewrite the task which you will want to do:\n\n ";
			
			vector<Task> newTasks;
			
			cin.ignore();//clean buffer
			string newTask = "";
			cout << "\nEnter your task: ";//add a description for a task
			getline(cin, newTask);

			string newDate = "";//task completion date
			cout << "Enter date in this format 'DD-MM-YY HH:MM': ";
			getline(cin, newDate);

			cout << "Do you want to add description to your task? 1 - YES, 2 - NO: ";
			short descr; //for add description or not
			cin >> descr;

			if (descr == 1)
			{
				cin.ignore();//clean buffer
				string newDescription = "";
				cout << "Enter a description to your task: ";
				getline(cin, newDescription);
				addTask(newTasks, newTask, newDescription, newDate);
			}
			else if (descr == 2)
			{
				addTask(newTasks, newTask, "", newDate);
			}
			else
			{
				cout << "Something go wrong, choose another option : \n";
			}

			exportTasks(newTasks, nameImportFile);

			cout << "\nEnter next command: ";
			cin >> choice;
		}
		else if (choice == 8) break;
		else
		{
			cout << "\nSomething go wrong, choose another option: " << endl;
			break;
		}

			
	}

	markIndexes(currentDateTime() + ".txt"); //indexing tasks in a file called 'MM-DD-YY_DayOfWeeknew.txt'

	return 0;
}

