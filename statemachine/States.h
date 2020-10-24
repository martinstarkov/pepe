#pragma once

#include <iostream> // std::cout
#include <conio.h> // _kbhit, _getch

#include <statemachine/StateMachine.h>
#include <sensors/SensorController.h>

constexpr int ARM_KEY = 114; // R
constexpr int FLY_KEY = 102; // F
constexpr int ABORT_KEY = 97; // A

class Grounded : public BaseState {
public:
    virtual void OnEntry() override final {
        std::cout << "Welcome to the super fancy grounded state" << std::endl;
        assert(state_machine != nullptr && "Parent state machine of states not set");
    }
    virtual void Update() override final {
        if (_kbhit()) {
            auto ch = _getch();
            //std::cout << ch << std::endl;
            if (ch == ARM_KEY) {
                state_machine->SetState(State::READY);
            }
        }
    }
};

class Ready : public BaseState {
public:
    virtual void OnEntry() override final {
        std::cout << "Bayes is armed and ready to receive flight commands" << std::endl;
    }
    virtual void Update() override final {
        if (_kbhit()) {
            auto ch = _getch();
            if (ch == FLY_KEY) {
                state_machine->SetState(State::ASCENDING);
            } else if (ch == ABORT_KEY) {
                state_machine->SetState(State::GROUNDED);
            }
        }
    }
};

class Ascending : public BaseState {
public:
    virtual void OnEntry() override final {
        std::cout << "Setting up ascent related variables" << std::endl;
    }
    virtual void Update() override final {
        const auto& data = SensorController::GetData();
        std::cout << "Altitude: " << data.altitude << std::endl;
        //std::cout << "Pressure: " << data.pressure << std::endl;
        //std::cout << "Temperature: " << data.temperature << std::endl;
        if (_kbhit()) {
            auto ch = _getch();
            if (ch == ABORT_KEY) {
                state_machine->SetState(State::ABORT);
            }
        }
        // Update control loop here
        bool begin_descent = false;

        // Check for descent condition.
        if (begin_descent) {
            state_machine->SetState(State::DESCENDING);
        }
    }
    virtual void OnExit() override final {
        std::cout << "Exiting ascent" << std::endl;
    }
};

class Descending : public BaseState {
public:
    virtual void OnEntry() override final {
        std::cout << "Beginning descent phase" << std::endl;
    }
    virtual void Update() override final {
        std::cout << "Checking where ground is" << std::endl;
        bool hit_ground = false;

        if (_kbhit()) {
            auto ch = _getch();
            if (ch == ABORT_KEY) {
                state_machine->SetState(State::ABORT);
            }
        }

        // Check for ground collision condition.
        if (hit_ground) {
            state_machine->SetState(State::LANDED);
        }
    }
};

class Abort : public BaseState {
public:
    virtual void OnEntry() override final {

        std::cout << "Bayes abort called" << std::endl;

        // Do full abort.

        std::cout << "Switching off edf" << std::endl;

        std::cout << "Plummeting toward the surface..." << std::endl;

        bool abort_complete = false;

        if (abort_complete) {
            //state_machine->SetState(State::GROUNDED);
        }
    }
};

class Landed : public BaseState {
public:
    virtual void OnEntry() override final {
        std::cout << "Bayes has landed" << std::endl;

        // Do full Bayes reset and save all data.

        std::cout << "Switching off data logging" << std::endl;

        // Transition back to some default state.

        //state_machine->SetState(State::GROUNDED);
    }
};