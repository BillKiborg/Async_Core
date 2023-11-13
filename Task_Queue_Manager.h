#pragma once
#include <unordered_map>
#include <queue>
#include <string>

#include "Interfaces.h"

namespace async_core {

	class Task_Queue_Manager : public Task_Manager {
	private:

		std::queue<Task*> tasks;
		std::unordered_map<std::string, Task_Executor*> tasks_executors;

	public:

		void add_task(Task*) override;
		void register_task_executor(std::string task_name, Task_Executor*&&) override;
		void process_tasks() override;

	};

}

