#include "StateMachine.h"

#include <statemachine/States.h>

void StateMachine::Init(State initial_state) {
    states[GROUNDED] = std::make_unique<Grounded>(*this);
    states[READY] = std::make_unique<Ready>(*this);
    states[ASCENDING] = std::make_unique<Ascending>(*this);
    states[DESCENDING] = std::make_unique<Descending>(*this);
    states[LANDED] = std::make_unique<Landed>(*this);
    current_state_ = initial_state;
    states[current_state_]->OnEntry();
}

void StateMachine::Update() {
    auto& state = states[current_state_];
    assert(state != nullptr && "StateMachine has not been initialized properly, state cannot be nullptr");
    state->Update();
}

void StateMachine::SetState(State state) {
    auto& previous_state = states[current_state_];
    assert(previous_state != nullptr && "StateMachine has not been initialized properly, state cannot be nullptr");
    // Exit previous state.
    previous_state->OnExit();
    current_state_ = state;
    auto& new_state = states[current_state_];
    assert(new_state != nullptr && "StateMachine has not been initialized properly, state cannot be nullptr");
    // Enter new state.
    new_state->OnEntry();
}

State StateMachine::GetCurrentState() {
    return current_state_;
}