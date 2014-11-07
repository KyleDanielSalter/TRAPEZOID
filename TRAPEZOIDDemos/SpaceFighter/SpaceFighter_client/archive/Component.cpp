#include "SpaceFighter_client.h"
#include "Component.h"

Component::Component(Handle newHandle) : handle(newHandle) {}

Handle Component::getHandle() {
	return handle;
}

Handle Component::getParent() {
	return parent;
}

void Component::setParent(Handle parentHandle) {
	parent = parentHandle;
}
