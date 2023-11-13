#pragma once
#include <random>
#include "Interfaces.h"
#include "Tasks_and_Executors.h"

namespace async_core {

	class Worker : public Sensor {
	private:

		int rand() {

			std::random_device rd{};
			std::mt19937 gen{ rd() };
			std::discrete_distribution<int> distribution({ 0.95, 0.05 });
			return distribution(gen);
		}

	public:
		void to_polling(Task_Manager* manager) override {

			switch (this->rand()) {
			case 0:
				std::cout << "Работаем штатно.\n";
				break;
			case 1:
				manager->add_task(new Alert);
				break;
			}
			
		}
	};

}
