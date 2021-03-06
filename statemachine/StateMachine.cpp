#include "StateMachine.h"

#include <statemachine/States.h>

void StateMachine::Init(State initial_state) {
    states[static_cast<int>(State::GROUNDED)] = std::make_unique<Grounded>();
    states[static_cast<int>(State::READY)] = std::make_unique<Ready>();
    states[static_cast<int>(State::ASCENDING)] = std::make_unique<Ascending>();
    states[static_cast<int>(State::DESCENDING)] = std::make_unique<Descending>();
    states[static_cast<int>(State::ABORT)] = std::make_unique<Abort>();
    states[static_cast<int>(State::LANDED)] = std::make_unique<Landed>();
    for (auto& state : states) {
        assert(state != nullptr && "State not set before adding parent state machine");
        state->SetMachine(this);
    }
    current_state_ = initial_state;
    states[static_cast<int>(current_state_)]->OnEntry();
}

void StateMachine::Update() {
    auto& state = states[static_cast<int>(current_state_)];
    assert(state != nullptr && "StateMachine has not been initialized properly, state cannot be nullptr");
    state->Update();
}

void StateMachine::SetState(State state) {
    auto& previous_state = states[static_cast<int>(current_state_)];
    assert(previous_state != nullptr && "StateMachine has not been initialized properly, state cannot be nullptr");
    // Exit previous state.
    previous_state->OnExit();
    current_state_ = state;
    auto& new_state = states[static_cast<int>(current_state_)];
    assert(new_state != nullptr && "StateMachine has not been initialized properly, state cannot be nullptr");
    // Enter new state.
    new_state->OnEntry();
}

State StateMachine::GetCurrentState() {
    return current_state_;
}