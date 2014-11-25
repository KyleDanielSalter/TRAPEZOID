#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#ifdef CLIENT
	#undef SUBSCRIBER_H	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

#include "Handle.h"

class Subscriber {
public:

	Subscriber(const Handle newSubscriberHandle) : subscriberHandle(newSubscriberHandle) {}
	Handle getSubscriberHandle() const { return subscriberHandle; }

private:

	//Handle to the messenger that receives the messages of the owning messenger.
	Handle subscriberHandle;
};

#endif