#include "gameobject.h"
#include "handlemanager.h"
#include "component.h"

GameObject::GameObject(HandleManager &handleManager) : 
	messenger(handleManager), 
	handle(handleManager.add(this, GAME_OBJECT)) {}

bool GameObject::hasComponents(const GameObjectFilter filter) const {
	//if there is an handle type in the filter that is not in the map, return false
	XLib::Vector<HandleType> filterList = filter.getFilterList();
	for (auto iter = filterList.begin(); iter != filterList.end(); iter++) {
		if (components.count(*iter) == 0)
			return false;
	}
	return true;
}

bool GameObject::addComponent(HandleManager &handleManager, const Handle handle) {
	auto got = components.find(handle.type);
	if (got != components.end()) {
		got->second.addHandle(handle);
		makeParent(handleManager, handle);
		return true;
	} else if (got == components.end()) {
		components.insert(std::make_pair(handle.type, ComponentTypeHandle(handle)));
		makeParent(handleManager, handle);
		return true;
	}
	return false;
}

ComponentTypeHandle* GameObject::getComponentTypeHandle(const HandleType type) {
	auto got = components.find(type);
	if (got != components.end())
		return &got->second;
	return NULL;
}

bool GameObject::removeComponent(HandleManager &handleManager, const Handle handle) {
	auto got = components.find(handle.type);
	if (got != components.end()) {
		got->second.removeComponent(handleManager, handle);
		return true;
	}
	return false;
}

bool GameObject::removeComponents(HandleManager &handleManager, const HandleType type) {
	auto got = components.find(handle.type);
	if (got != components.end()) {
		got->second.removeAllComponents(handleManager);
		return true;
	}
	return false;
}

void GameObject::removeSelf(HandleManager &handleManager) {
	handleManager.remove(handle);
	for (auto iter = components.begin(); iter != components.end(); iter++)
		iter->second.removeAllComponents(handleManager);
}

void GameObject::makeParent(HandleManager &handleManager, const Handle childHandle) {
	Component* baseComponent = (Component*)handleManager.get(childHandle);
	if (baseComponent)
		baseComponent->setParent(handle);
}

Handle GameObject::getHandle() const {
	return handle;
}

Messenger* GameObject::getMessenger() {
	return &messenger;
}