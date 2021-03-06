#ifndef MESSENGER_H_INCLUDED
#define MESSENGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef MESSENGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include <unordered_map>
#include <vector>
#include "subscriber.h"

namespace NetPhysics{
	class HandleManager;

	/*
		A message can be any struct as long as the first member is a
		integer that signifies it type as a tool of identification.
	*/
	struct Message {
		uint32_t type;
	};

	/*
		A messaging system for objects(be it managers, GameObjects, or systems)
		to communicate data to each other.
	*/
	class Messenger {
	public:

		Messenger(HandleManager& handleManager);

		/*
		Sends a message to all subscribers.
		@param handleManager a pointer to the handleManager object containing the
		program handles.
		@param msg the message being posted.
		*/
		void postMessage(HandleManager& handleManager,
			Message* msg);

		/*
		Adds the message to the inbox container.
		@param msg the message to store.
		*/
		void receiveMessage(Message* msg);

		/*
		Returns and clears the inbox container.
		@return the message container.
		*/
		std::vector<Message*> getInbox();

		/*
		Adds the messenger object described by subscriber to the subscriber list.
		Any messages posted afterwards that meet the desired type will be sent to
		the subscriber.
		@param handleManager a pointer to the handleManager object containing the
		program handles.
		@param subscriber a pointer to the messenger object that will subscribe to this object.
		@param messageType the type of message to subscribe to.
		*/
		void subscribe(Handle messengerHandle,
			const uint32_t messageType);

		Handle getHandle() const;

	private:

		Handle handle;
		//Container for received messages.
		std::vector<Message*> inbox;
		//Container for subscribers.
		std::unordered_multimap<uint32_t, Subscriber> subscribers;
	};
}

#endif