#pragma once

struct BMPData {
	double altitude;
	double pressure;
	double temperature;
};

class BMP388 {
public:
	BMPData GetData() {
		return { GetAltitude(), GetPressure(), GetTemperature() };
	}
private:
	double GetAltitude() {
		return static_cast<double>(rand() % 10);
		//return 0;
	}
	double GetPressure() {
		return 0;
	}
	double GetTemperature() {
		return 0;
	}
};