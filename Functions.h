#pragma once
#include <vector>
#include <string>
#ifndef FUNCTION_H
#define FUNCTION_H

struct Task
{
	std::string title, description, date;
	bool completed;

	Task(const std::string& t, const std::string& desc, const std::string& dat) : title(t), description(desc), date(dat), completed(false) {}
};

void addTask(std::vector<Task>& tasks, const std::string& title, const std::string& description, const std::string& date);
void removeTask(std::vector<Task>& tasks, int index);
void markTask(std::vector<Task>& tasks, int index);
void listTask(std::vector<Task>& tasks);
void exportTasks(std::vector<Task>& tasks, const std::string& path);
std::string currentDateTime();
void importFromFile(const std::string& path);
void markIndexes(const std::string& path);
void renameFile();
void Introduction();

#endif
