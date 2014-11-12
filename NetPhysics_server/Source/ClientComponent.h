#ifndef CLIENT_COMPONENT_H_INCLUDED
#define CLIENT_COMPONENT_H_INCLUDED

#include "Component.h"
#include "RakPeerInterface.h"
#include "handlemanager.h"
#include "handle.h"


/*
	Component encapsulating the client connection data.
*/
class ClientComponent : public Component {
public:

	/*
	@param handleManager reference to a handleManager to manage this object
	@param peer the instance of RakNetInterface the client is connected to
	@param newClientGUID the RakNetGUID of the client's system
	*/
	ClientComponent(HandleManager &handleManager, RakNet::RakPeerInterface *peer, const RakNet::RakNetGUID newClientGUID);

	//Returns the RakNetGUID of the client
	RakNet::RakNetGUID getClientGUID() const;

	//Polls and returns the connection state of the client
	RakNet::ConnectionState getConnectionState() const;

private:

	//client identifier
	RakNet::RakNetGUID clientGUID;
	//pointer to the instance of RakPeerInterface the client is connected to.
	RakNet::RakPeerInterface* RakPeerInstance;
	
	
};


#endif
