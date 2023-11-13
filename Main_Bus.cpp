#include "Main_Bus.h"

namespace async_core{

	void Main_Bus::run() {

		if (!task_manager) {
			throw std::runtime_error{ "Manager is not found" };
		}

		while (run_flag) {

			std::cout << "Опрос системы:\n";			

			std::for_each(list_of_sensors.begin(), list_of_sensors.end(), [this](const sensor_ptr& sensor) {
				sensor->to_polling(task_manager.get());
				});

			task_manager->process_tasks();

			std::cout << ".............\n\n";
			std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
		}

	}

	void Main_Bus::add_sensor(Sensor* sensor) {
		list_of_sensors.push_back(sensor_ptr{sensor});
	}

	Task_Manager* Main_Bus::get_task_manager() {

		if (task_manager) {
			return task_manager.get();
		}
		else {
			throw std::runtime_error{ "Manager not found" };
		}		
	}

	void Main_Bus::set_task_manager(Task_Manager*&& new_task_manager){
		task_manager = std::unique_ptr<Task_Manager>{ new_task_manager };
	}

}
