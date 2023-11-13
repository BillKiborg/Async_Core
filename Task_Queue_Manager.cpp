#include "Task_Queue_Manager.h"

namespace async_core {

	void Task_Queue_Manager::add_task(Task* new_task) {
		tasks.push(new_task);
	}

	void Task_Queue_Manager::register_task_executor(std::string task_name, Task_Executor*&& task_executor) {
		tasks_executors.insert(std::make_pair(task_name, task_executor));
	}

	void Task_Queue_Manager::process_tasks() {

		std::queue<Task*> unsolved_task;

		while (!tasks.empty()) {

			auto task = tasks.front();
			tasks.pop();

			try {
				if (auto executor = tasks_executors.find(typeid(*task).name());
					executor != tasks_executors.cend()) {

					task->set_executor(executor->second);
					task->execute();
					delete task;
				}
				else {
					throw std::runtime_error{ "Appropriate executor not found" };
				}
			}
			catch (std::exception& exc) {
				std::cout << "Exc: " << exc.what() << "\n";
				unsolved_task.push(task);
			}			

		}

		while (!unsolved_task.empty()) {
			tasks.push(unsolved_task.front());
			unsolved_task.pop();
		}

	}

}