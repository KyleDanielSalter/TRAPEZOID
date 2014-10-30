#include "playerstatecomponent.h"
#include "handlemanager.h"

PlayerStateComponent::PlayerStateComponent(HandleManager &handleManager, PlayerState initialState) : 
	handle(handleManager.add(this, PLAYER_STATE_COMPONENT)),
	state(initialState) {}

PlayerState PlayerStateComponent::getState() const {
	return state;
}

void PlayerStateComponent::setState(const PlayerState newState) {
	state = newState;
}

Handle PlayerStateComponent::getHandle() const {
	return handle;
}