#pragma once
#include <thread>
#include <memory>
#include <list>
#include <algorithm>

#include "Interfaces.h"

namespace async_core{

	class Main_Bus : public async_core::Async_Core {
	private:

		bool run_flag = true;		
		std::unique_ptr<Task_Manager> task_manager;

		using sensor_ptr = std::unique_ptr<Sensor>;
		std::list<sensor_ptr> list_of_sensors;

	public:

		void run() override;
		Task_Manager* get_task_manager() override;
		void add_sensor(Sensor*) override;

		void set_task_manager(Task_Manager*&& new_task_manager);

	};
}

