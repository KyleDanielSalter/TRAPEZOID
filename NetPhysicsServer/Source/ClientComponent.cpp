#include "ClientComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"

ClientComponent::ClientComponent(HandleManager &handleManager, RakNet::RakPeerInterface *peer, const RakNet::RakNetGUID newClientGUID) :
Component(CLIENT, handleManager.add(this, COMPONENT)),
	RakPeerInstance(peer),
	clientGUID(newClientGUID) {}

RakNet::RakNetGUID ClientComponent::getClientGUID() const {
	return clientGUID;
}

RakNet::ConnectionState ClientComponent::getConnectionState() const {
	return RakPeerInstance->GetConnectionState(clientGUID);
}