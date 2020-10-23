#pragma once

#include <iostream> // std::cout

#include <statemachine/StateMachine.h>

class Grounded : public BaseState {
public:
    virtual OnEntry() override final {
        std::cout << "Welcome to the super fancy grounded state" << std::endl;
    }
    virtual Update() override final {
        bool start_input = true; // GetStartInput();

        // Check for arming condition.
        if (start_input) {
            state_machine.SetState(State::READY);
        }
    }
}

class Ready : public BaseState {
public:
    virtual OnEntry() override final {
        std::cout << "Bayes is armed and ready to receive flight commands" << std::endl;
    }
    virtual Update() override final {
        bool flight_command = true; // GetFlightCommand();

        // Check for flight start condition.
        if (flight_command) {
            state_machine.SetState(State::ASCENDING)
        }
    }
}

class Ascending : public BaseState {
public:
    virtual OnEntry() override final {
        std::cout << "Setting up ascent related variables" << std::endl;
    }
    virtual Update() override final {
        // Update control loop here
        bool begin_descent = true;

        // Check for descent condition.
        if (begin_descent) {
            state_machine.SetState(State::DESCENDING);
        }
    }
    virtual OnExit() override final {
        std::cout << "Exiting ascent" << std::endl;
    }
}

class Descending : public BaseState {
public:
    virtual OnEntry() override final {
        std::cout << "Beginning descent phase" << std::endl;
    }
    virtual Update() override final {
        std::cout << "Checking where ground is" << std::endl;
        bool hit_ground = true;

        // Check for ground collision condition.
        if (hit_ground) {
            state_machine.SetState(State::LANDED);
        }
    }
}

class Landed : public BaseState {
public:
    virtual OnEntry() override final {
        std::cout << "Bayes has landed" << std::endl;
        
        // Do full Bayes reset.
        
        std::cout << "Switching off data logging" << std::endl;
        
        // Transition back to state which listens to ground inputs and is not autonomous.
        
        //state_machine.SetState(State::GROUNDED);
    }
}

