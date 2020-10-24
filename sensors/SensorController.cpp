#include "SensorController.h"

std::unique_ptr<SensorController> SensorController::instance_ = nullptr;

SensorController::SensorController() {
	bmp_ = std::make_unique<BMP388>();
}

void SensorController::UpdateData() {
	auto bmp_data = bmp_->GetData();
	data.altitude = bmp_data.altitude;
	data.pressure = bmp_data.pressure;
	data.temperature = bmp_data.temperature;
}

SensorController& SensorController::Get() {
	if (!instance_) {
		instance_ = std::make_unique<SensorController>();
	}
	return *instance_;
}

void SensorController::Init() {
	Get();
}

void SensorController::Update() {
	Get().UpdateData();
}

const Data& SensorController::GetData() {
	return Get().data;
}
