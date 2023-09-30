#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdio> 
#pragma warning(disable : 4996)//for function strftime

struct Task
{
	std::string title, description, date;
	bool completed;

	Task(const std::string& t, const std::string& desc, const std::string &dat) : title(t), description(desc), date(dat), completed(false) {}
};

/*
* 1
*/
void addTask(std::vector<Task>& tasks, const std::string &title, const std::string &description, const std::string& date)
{
	tasks.push_back(Task(title, description, date));
	if (description == "")
	{
		std::cout << "\nTask: " << title << " is added" << std::endl;
		std::cout << "Deadline: " << date << '\n' << std::endl;
	}

	else
	{
		std::cout << "\nTask: " << title << " is added" << std::endl;
		std::cout << "Description: " << description  << std::endl;
		std::cout << "Deadline: " << date << '\n' << std::endl;
	}
}

/*
2
*/
void removeTask(std::vector<Task>& tasks, int index)
{
	if (index >= 0 && index < tasks.size()) {
		std::cout << "\nThe task " << tasks[index].title << " deleted " << std::endl;
		tasks.erase(tasks.begin() + index);
	}
	else {
		std::cout << "\nSomething go wrong, try another index: " << std::endl;
	}
}

/*
3
*/
void markTask(std::vector<Task>& tasks, int index)
{
	if (index >= 0 && index < tasks.size()) {
		std::cout << "\nThe task " << tasks[index].title << " is changed " << std::endl;
		if (!tasks[index].completed)
			tasks[index].completed = true;
		else tasks[index].completed = false;
	}
	else {
		std::cout << "\nSomething go wrong, try another index: " << std::endl;
	}
}

/*
4
*/
void listTask(std::vector<Task>& tasks)
{
	if (tasks.empty()) std::cout << "\nYour list is empry " << std::endl;
	else
	{
		std::cout << "\nYour tasks list: \n";
		for (int i = 0; i < tasks.size(); i++)
		{
			std::cout << i << ". ";
			if (tasks[i].completed) std::cout << " [X] ";
			else std::cout << " [] ";

			std::cout << tasks[i].title << "	Deadline: " << tasks[i].date << '\n';
			if (tasks[i].description != "") std::cout << "Description: " << tasks[i].description << '\n';
			else std::cout << "The description for this task wasn't filled in\n" << '\n';
		}
	}
}

/*
5
*/
void exportTasks(std::vector<Task>& tasks, const std::string &path)
{
	std::ofstream inFile(path, std::ios::app);
	// Проверяем, был ли файл успешно открыт
	if (!inFile.is_open()) 
		std::cerr << "\nThe file was not found " << std::endl;
	

	// Записываем вектор в файл
	for (int i = 0; i < tasks.size(); i++) {
		inFile << tasks[i].title << '	' << tasks[i].date << '	' 
				   << tasks[i].description << '	' << tasks[i].completed << "\n\n"; // Записываем элементы, разделяя пробелами
	}

	// Закрываем файл после завершения записи
	inFile.close();

	std::cout << "\nThe list of tasks was written successfully\n" << std::endl;
}

std::string currentDateTime() 
{
	std::time_t today = std::time(nullptr);
	std::tm* now = std::localtime(&today);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%m-%d-%Y_%A", now);
	return buffer;
}

void importFromFile(const std::string &path)
{
	std::ifstream outFile(path);
	if (outFile.is_open())
	{
		std::string line;
		while (getline(outFile, line))
			std::cout << line << '\n';
		outFile.close();
	}
	else
		std::cerr << "Error!\n";
}

void markIndexes(const std::string& path)
{
	remove((currentDateTime() + "new.txt").c_str());
	std::ifstream outFile(path);
	std::ofstream inFile(currentDateTime() + "new.txt", std::ios::app);

	if (!outFile) 
		std::cerr << "The file didn't open. " << std::endl;
	

	std::string line;
	std::string index;
	short count = 1;

	while (std::getline(outFile, line))
	{
		index = std::to_string(count);
		if (line != "")
		{
			line = index + ". " + line + "\n";
			count++;
		}
			
		inFile << line;
	}

	outFile.close();
	inFile.close();
}

void renameFile()
{
	std::string oldFilename = currentDateTime() + "new.txt";
	std::string newFilename = currentDateTime() + ".txt";

	if (std::rename(oldFilename.c_str(), newFilename.c_str()) == 0) {
		std::cout << "The file was renamed successful " << newFilename << "." << std::endl;
	}
	else {
		std::cerr << "Error. The file wasn't renamed " << std::endl;
	}
}

void Introduction() 
{
	std::cout << "What do you want? \n";
	std::cout << "Press 1 for add a task \n";
	std::cout << "Press 2 for remove a task \n";
	std::cout << "Press 3 for mark a task as done \n";
	std::cout << "Press 4 for look at the list of tasks \n";
	std::cout << "Press 5 for export tasks in the file \n";
	std::cout << "Press 6 for import tasks out the file \n";
	std::cout << "Press 7 for rewrite file \n";
	std::cout << "Press 8 for exit from program \n";
}

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
				continue;
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

