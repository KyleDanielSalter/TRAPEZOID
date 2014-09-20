﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RakNet;

namespace Network {
	enum Message {
		//Default message
		INVALID_MESSAGE = DefaultMessageIDTypes.ID_USER_PACKET_ENUM + 1,
		//For updating a network component. Order sensitive (Message, networkID, ...)
		NETWORK_COMPONENT_MESSAGE,
		//Message to client to create a player controlled ball (responds to input). (Message, networkID, radius, x, y, z)
		CREATE_PLAYER_BALL,
		//Message to client to create an enemy ball, or when that does not respond to input. (Message order congruent to CREATE_PLAYER_BALL)
		CREATE_ENEMY_BALL,
		//When someone disconnects or if they die (Message, networkID)
		DELETE_ENEMY_BALL,
		//When the controlling player loses
		YOU_LOST,
	}
}
