#ifndef CLIENT_SYSTEM_H_INCLUDED
#define CLIENT_SYSTEM_H_INCLUDED

#include "System.h"
#include "RakNetTypes.h"
#include "GameObjectFilter.h"
#include "NetworkHandleManager.h"

class Register;

class ClientSystem : public System {
public:
	ClientSystem();
	/*
	Creates a GameObject with a client component containing
	the client's, effectively adding him to the system.
	@param clientSystemAddress the clients systemAddress.
	*/
	void initializeClient(Register &engineRegister,
						  RakNet::RakNetGUID guid);

	/*
	TEMP: removes the owning clients game object
	*/
	void removeClient(Register &engineRegister,
					  NetworkKey networkID);

private:
	GameObjectFilter filter;
};


#endif