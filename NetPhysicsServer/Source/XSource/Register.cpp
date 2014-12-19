#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
	#include "ConnectionSystem.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Register.h"
#ifdef NET_PHYSICS_SERVER
#include "ServerSystem.h"
#endif /* NET_PHYSICS_SERVER */
#include "System.h"

using namespace NetPhysics;

void Register::init() {
	//Set max size for the system container
	systemContainer.resize(NUM_SYSTEM_TYPES);

	//initialize the component managers
	for (uint32_t i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.push_back(ComponentManager((ComponentType)i));
	}
}

void Register::update(const double dt) {
	//Update component managers and systems.
	for (auto iter = componentManagerContainer.begin(); iter != componentManagerContainer.end(); iter++) {
		iter->update(handleManager);
	}
	for (auto iter = systemContainer.begin(); iter != systemContainer.end(); iter++) {
		if (*iter) {
			switch ((*iter)->mode) {
				case NO_PARAMETERS:
					(*iter)->update();
					break;
				case DELTA_TIME:
					(*iter)->update(dt);
					break;
				case REGISTER:
					(*iter)->update(*this);
					break;
				case BOTH:
					(*iter)->update(*this, dt);
					break;
			}
		}
	}

}

HandleManager* Register::getHandleManager() {
	return &handleManager;
}

NetworkHandleManager* Register::getNetworkHandleManager() {
	return &networkHandleManager;
}


GameObjectManager* Register::getGameObjectManager() {
	return &gameObjectManager;
}

#ifdef NET_PHYSICS_CLIENT
void Register::setWorld(UWorld* world) {
	world = world;
}
UWorld* Register::getWorld() {
	return world;
}
#endif /* NET_PHYSICS_CLIENT */

RakNet::RakPeerInterface* Register::getRakPeerInstance() {
#ifdef NET_PHYSICS_SERVER
	ServerSystem* serverSystem = (ServerSystem*)getSystem(SERVER_SYSTEM);
	return serverSystem->getRakPeerInstance();
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	ConnectionSystem* connectionSystem = (ConnectionSystem*)getSystem(CONNECTION_SYSTEM);
	return connectionSystem->getRakPeerInstance();
#endif /* NET_PHYSICS_CLIENT */
}

ComponentManager* Register::getComponentManager(ComponentType type) {
	return &componentManagerContainer[type];
}

System* Register::getSystem(SystemType type) {
	return systemContainer[type];
}

void Register::addSystem(System* newSystem, SystemType type) {
	newSystem->init();
	systemContainer[type] = newSystem;
}

void Register::removeSystem(SystemType type) {
	if (systemContainer[type]) {
		delete systemContainer[type];
		systemContainer[type] = nullptr;
	}
}