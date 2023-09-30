#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdio> 
#include "Functions.h"
#pragma warning(disable : 4996)//for function strftime

void addTask(std::vector<Task>& tasks, const std::string& title, const std::string& description, const std::string& date)
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
		std::cout << "Description: " << description << std::endl;
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
void exportTasks(std::vector<Task>& tasks, const std::string& path)
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

void importFromFile(const std::string& path)
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
