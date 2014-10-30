#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "NetworkIDManager.h"
#include "RakNetTypes.h"
#include "HideWindowsPlatformTypes.h"
#include "Handle.h"

class HandleManager;
class NetworkObject;

class NetworkSystem {
public:
	void registerActor(HandleManager &handleManager, NetworkObject* networkObject);
	void sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, HandleManager &handleManager, TSharedPtr<RakNet::Packet> packet);
private:
	TMap<RakNet::NetworkID, Handle> registeredActors;
};