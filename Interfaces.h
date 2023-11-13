#pragma once
#include <string>
#include <iostream>

//--------------------------------------------------------------------

namespace async_core
{
	class Sensor;
	class Task_Manager;
	class Task;
	class Task_Executor;

	class Async_Core {
	public:
		virtual ~Async_Core() = default;
		virtual void run() = 0;
		virtual Task_Manager* get_task_manager() = 0;
		virtual void add_sensor(Sensor*) = 0;
	};

	class Sensor {
	public:
		virtual ~Sensor() = default;
		virtual void to_polling(Task_Manager*) = 0;
	};

	class Task_Manager {
	public:
		virtual ~Task_Manager() = default;
		virtual void add_task(Task*) = 0;
		virtual void register_task_executor(std::string task_name, Task_Executor*&&) = 0;
		virtual void process_tasks() = 0;
	};

	class Task {
	protected:
		Task_Executor* task_executor = nullptr;
	public:
		virtual ~Task() = default;
		virtual void execute() = 0;
		virtual void set_executor(Task_Executor* _task_executor) {
			task_executor = _task_executor;
		}
	};

	class Task_Executor {
	public:
		virtual ~Task_Executor() = default;
		virtual void execute_task() = 0;
	};

}

