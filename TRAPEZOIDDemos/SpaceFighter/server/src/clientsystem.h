#ifndef CLIENT_SYSTEM_H_INCLUDED
#define CLIENT_SYSTEM_H_INCLUDED

#include "NetworkHandleManager.h"
#include "RakNetTypes.h"
#include "GameObjectFilter.h"

class EngineRegister;

class ClientSystem {
public:
	ClientSystem();
	/*
	Creates a GameObject with a client component containing
	the client's, effectively adding him to the system.
	@param clientSystemAddress the clients systemAddress.
	*/
	void initializeClient(EngineRegister &engineRegister, RakNet::RakNetGUID guid);

	/*
	TEMP: removes the owning clients game object
	*/
	void removeClient(EngineRegister &engineRegister, NetworkKey networkID);

private:
	GameObjectFilter filter;
};


#endif