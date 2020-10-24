#pragma once

#include <memory> // std::unique_ptr

#include <sensors/BMP.h>

struct Data {
	double altitude = 0;
	double pressure = 0;
	double temperature = 0;
};

class SensorController {
public:
	SensorController();
	static SensorController& Get();
	static void Init();
	static void Update();
	static const Data& GetData();
private:
	void UpdateData();
	std::unique_ptr<BMP388> bmp_ = nullptr;
	Data data;
	static std::unique_ptr<SensorController> instance_;
};