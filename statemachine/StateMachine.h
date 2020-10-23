#pragma once

#include <cstdlib> // std::size_t
#include <array> // std::array
#include <memory> // std::unique_ptr
#include <cassert> // assert

class BaseState {
public:
    BaseState(StateMachine& parent_state_machine) : state_machine{ parent_state_machine } {}
    virtual void Update() {}
    virtual void OnEntry() {}
    virtual void OnExit() {}
protected:
    StateMachine& state_machine;
};

enum class State {
    GROUNDED,
    READY,
    ASCENDING,
    DESCENDING,
    LANDED,
    // Do not add anything after STATE_COUNT.
    // It is used in creating the states array in the StateMachine. 
    STATE_COUNT
}

constexpr std::size_t StateCount = 5;

using StateFuncPtr = void (*)();

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
    State current_state_;
    std::array<std::unique_ptr<BaseState>, STATE_COUNT> states;
};