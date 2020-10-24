#pragma once

#include <cstdlib> // std::size_t
#include <array> // std::array
#include <memory> // std::unique_ptr
#include <cassert> // assert

class StateMachine;

class BaseState {
public:
    virtual void SetMachine(StateMachine* parent_state_machine) {
        state_machine = parent_state_machine;
    }
    virtual void Update() {}
    virtual void OnEntry() {}
    virtual void OnExit() {}
protected:
    StateMachine* state_machine = nullptr;
};

enum class State {
    GROUNDED,
    READY,
    ASCENDING,
    DESCENDING,
    LANDED,
    ABORT,
    // Do not add anything after STATE_COUNT.
    // It is used in creating the states array in the StateMachine. 
    STATE_COUNT
};

class StateMachine {
public:
    // Setup state array
    void Init(State initial_state);
    // Update the current state.
    void Update();
    // Used for state transitions.
    void SetState(State state);
    State GetCurrentState();
private:
    // Variable storing the current state
    State current_state_ = State::STATE_COUNT;
    std::array<std::unique_ptr<BaseState>, static_cast<std::size_t>(State::STATE_COUNT)> states;
};