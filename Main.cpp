#include "Interfaces.h"
#include "Main_Bus.h"
#include "Task_Queue_Manager.h"
#include "Worker.h"

int main() {
	setlocale(LC_ALL, "rus");
		
	async_core::Main_Bus		main_bus;
	main_bus.set_task_manager(new async_core::Task_Queue_Manager);	
	main_bus.get_task_manager()->register_task_executor(typeid(Alert).name(), new Siren);

	main_bus.add_sensor(new async_core::Worker);
	main_bus.add_sensor(new async_core::Worker);
	main_bus.add_sensor(new async_core::Worker);
	main_bus.run();

	return 0;
}