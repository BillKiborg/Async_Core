#pragma once
#include "Interfaces.h"

#include <unordered_map>
#include <queue>
#include <string>
#include <memory>
#include <iostream>
#include <thread>

class Main_Responsible : public Task_Manager {
private:

	std::list<Worker*> workers;

	std::unordered_map<std::string, Task_Executor*> task_executors;
	std::queue<Task*> tasks;
	std::unique_ptr<Task_Queue_Manager> task_queue_manager;

	void sort_out_the_queue();

public:

	Main_Responsible() = default;

	void add_task(Task* new_task) override;
	void add_worker(Worker* new_worker) override;
	void register_task_executor(std::string task_name, Task_Executor* task_executor) override;
	void run() override;

};