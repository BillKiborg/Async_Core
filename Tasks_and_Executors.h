#pragma once

#include "Interfaces.h"

using namespace async_core;

class Alert : public async_core::Task {
public:
	void execute() override {
		task_executor->execute_task();
	}
};

class Siren : public async_core::Task_Executor {
public:
	void execute_task() override {
		std::cout << "Тестовый сигнал\n\a";
	}
};