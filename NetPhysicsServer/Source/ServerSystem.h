#ifndef SERVER_SYSTEM_H_INCLUDED
#define SERVER_SYSTEM_H_INCLUDED

#include <iostream>
#include "System.h"
#include "XLib.h"
#include "RakPeerInterface.h"
#include "GetTime.h"
#include "packettobitstream.h"

#define DEFAULT_PORT 60000
#define DEFAULT_MAX_CLIENTS 20

namespace NetPhysics {
	/*
		Handles incoming connections and packets
	*/
	class ServerSystem : public System {
	public:

		ServerSystem() : System(NO_PARAMETERS) {}

		void init() override;
		void update() override;
		void startServer(bool userInputDetails);
		RakNet::RakPeerInterface* getRakPeerInstance();
		//Gets the packets received since the last update
		XLib::Vector<PacketToBitStream> getPackets();

	private:

		//Pointer to the generated instance of RakPeerInterface
		RakNet::RakPeerInterface *rakPeerInstance;
		//What port the server runs on, only read at init, does not change during runtime
		int port;
		//Container for storing received packets.
		XLib::Vector<PacketToBitStream> packetContainer;
		//maximum number of clients, only read at init, does not change during runtime
		int maxClients;
	};
}

#endif /* SERVER_SYSTEM_H_INCLUDED */