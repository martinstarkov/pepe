#pragma once

#include <memory> // std::unique_ptr

#include <statemachine/StateMachine.h>

class FlightComputer {
public:
    FlightComputer();
    static FlightComputer& Get();
    static void Stop();
    void Start();
private:
    std::unique_ptr<StateMachine> state_machine = nullptr;
    void Loop();
    void SetRunning(bool state);
    bool running_ = false;
    static std::unique_ptr<FlightComputer> instance_;
};