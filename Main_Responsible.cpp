#include "Main_Responsible.h"

void Main_Responsible::run() {
	while (true) {
		std::cout << "Опрос системы:\n";
		std::for_each(workers.cbegin(), workers.cend(), [this](Worker* worker) {
			worker->to_work(this);
			});

		sort_out_the_queue();

		std::cout << "---------------------------\n\n";
		std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
	}
}

void Main_Responsible::sort_out_the_queue(){

	std::list<Task*> not_fulfilled;
	while (!tasks.empty()) {

		auto task = tasks.front();
		tasks.pop();

		try {
			if (auto task_executor = task_executors.find(typeid(*task).name());
				task_executor != task_executors.cend()) {

				task->set_executor(task_executor->second);
				task->execute();
				delete task;
			}
			else {
				throw std::runtime_error{ "Исполнитель не найден" };
			}
		}
		catch (std::exception& exc) {
			std::cout << "Exc: " << exc.what() << "\n";
			not_fulfilled.push_back(task);
		}

	}

	std::for_each(not_fulfilled.begin(), not_fulfilled.end(), [this](Task* not_fulfilled_task) {
		tasks.push(not_fulfilled_task);
		});

}

void Main_Responsible::add_task(Task* new_task){
	tasks.push(new_task);
}

void Main_Responsible::add_worker(Worker* new_worker){
	workers.push_back(new_worker);
}

void Main_Responsible::register_task_executor(std::string task_name, Task_Executor* task_executor){
	task_executors.insert(std::make_pair(task_name, task_executor));
	std::cout
		<< "Добавлен исполнитель задачи: " << task_name << "\n"
		<< typeid(task_executor).name() << "\n"
		<< "--------------------------------\n";
}


