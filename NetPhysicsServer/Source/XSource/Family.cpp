#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Family.h"
#include "GameObject.h"

using namespace NetPhysics;

Family::Family(Handle self) : selfHandle(self) {}

void Family::setParent(GameObject* parent, HandleManager &handleManager) {
	removeParent(handleManager);
	parentHandle = parent->getHandle();
}

bool Family::removeParent(HandleManager &handleManager) {
	if (parentHandle != Handle()) {
		GameObject* previousParent = reinterpret_cast<GameObject*>(handleManager.get(parentHandle));
		if (previousParent) {
			previousParent->getFamily()->removeChildWithHandle(selfHandle);
			parentHandle = Handle();
			return true;
		}
	}
	return false;
}

void Family::addChild(GameObject* child) {
	children.push_back(child->getHandle());
}

XLib::Vector<Handle> Family::getChildren() {
	return children;
}

bool Family::isChild(GameObject* gameObject) {
	//Adds one because findChild returns -1 on failed query.
	return findChild(gameObject->getHandle()) + 1 ? true : false;
}

bool Family::removeChildWithHandle(Handle childHandle) {
	return removeChildAtIndex(findChild(childHandle));
}

bool Family::destroyChildWithHandle(
	Handle childHandle,
	HandleManager &handleManager)
{
	if (removeChildWithHandle(childHandle)) {
		GameObject* childGameObject = reinterpret_cast<GameObject*>(handleManager.get(childHandle));
		if (childGameObject) {
			childGameObject->destroy(handleManager);
			return true;
		}
	}
	return false;
}



uint32_t Family::findChild(Handle childHandle) {
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		if (*iter == childHandle) {
#ifdef NET_PHYSICS_SERVER
			return static_cast<uint32_t>(iter - children.begin());
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			return iter.GetIndex();
#endif /* NET_PHYSICS_CLIENT */
		}
	}
	return -1;
}

bool Family::removeChildAtIndex(uint32_t index) {
	if (index != -1) {
		children.erase(children.begin() + index);
		return true;
	} else
		return false;
}