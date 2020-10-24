#include "FlightComputer.h"

#include <cassert> // assert
#include <sensors/SensorController.h>

std::unique_ptr<FlightComputer> FlightComputer::instance_ = nullptr;

FlightComputer& FlightComputer::Get() {
    if (!instance_) {
        instance_ = std::make_unique<FlightComputer>();
    }
    return *instance_;
}

void FlightComputer::Start() {
    running_ = true;
    // Initialize all relevant systems here.
    Loop();
}

FlightComputer::FlightComputer() {
    state_machine = std::make_unique<StateMachine>();
    state_machine->Init(State::GROUNDED);
    SensorController::Init();
}

void FlightComputer::Loop() {
    while (running_) {
        assert(state_machine != nullptr && "State machine cannot be updated if it has not been created in the flight computer's constructor");
        SensorController::Update();
        state_machine->Update();
    }
}

void FlightComputer::SetRunning(bool state) {
    running_ = state;
}

void FlightComputer::Stop() {
    Get().SetRunning(false);
}