#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include "XLib.h"
#include "Handle.h"
#include "ComponentTypeHandle.h"
#include "GameObjectFilter.h"
#include "Messenger.h"


/*
	GameObject class encapsulates handles to components.
	Access added components by using HandleManager::Get
	Handle::type denotes the type of the component.
	A GameObject cannot have multiple of the same component, or things get weird.
*/
class GameObject {

public:
	GameObject(HandleManager& handleManager);

	bool hasComponents(const GameObjectFilter filter) const;

	/*
	Adds the component that Handle points to to the game object
	@param handle the handle of the components
	@param type the type of component to be added
	*/
	bool addComponent(HandleManager &handleManager, const Handle handle);

	ComponentTypeHandle* getComponentTypeHandle(const HandleType type);

	//TODO comment
	template<class T>
	T* getComponent(HandleManager &handleManager, const Handle handle);

	//Gets the first component in the ComponentTypeHandle. Use when you only need one of the component.
	template<class T>
	T* getComponent(HandleManager &handleManager, const HandleType type);

	/*
	Returns a pointer to the handle of the component.
	@param handleManager the HandleManager containing the component
	@param type the type of component to be returned
	@return the pointer to the component. NULL if no component in this object
	*/
	template<class T>
	XLib::Vector<T*> getComponents(HandleManager &handleManager, const HandleType type);
	
	bool removeComponent(HandleManager &handleManager, const Handle handle);

	/*
	Removes the components from the GameObject and the manager
	@param handleManager the HandleManager that contains the handle
	@param type the type of component to remove.
	*/
	bool removeComponents(HandleManager &handleManager, const HandleType type);

	/*
	Remove the handle of the object and all handles of its component from the handle manager
	Note: when a GameObject of component does not have a valid handle, its manager deletes it next update.
	All subsequent calls to the data the handle pointed to will be null
	*/
	void removeSelf(HandleManager &handleManager);

	void makeParent(HandleManager &handleManager, const Handle handle);

	//Returns the handle of the object
	Handle getHandle() const;
	
	Messenger* getMessenger();
private:
	Handle handle;
	Messenger messenger;
	XLib::UnorderedMap<HandleType, ComponentTypeHandle> components;
	
};

template<class T>
T* GameObject::getComponent(HandleManager &handleManager, const Handle handle) {
	auto got = components.find(handle.type);
	if (got != components.end()) {
		int index = got->second.getHandleIndex(handle);
		if (index != -1)
			return (T*)handleManager.get(got->second.getHandles()[index]);
		else
			return NULL;
	}
	return NULL;
}

template<class T>
T* GameObject::getComponent(HandleManager &handleManager, const HandleType type) {
	auto got = components.find(type);
	if (got != components.end()) {
		return (T*)handleManager.get(got->second.getHandles()[0]);
	}
	return NULL;
}

template<class T>
XLib::Vector<T*> GameObject::getComponents(HandleManager &handleManager, const HandleType type) {
	std::vector<T*> ret;
	auto got = components.find(type);
	if (got != components.end()) {
		std::vector<Handle> handles = got->second.getHandles();
		for (auto iter = handles.begin; iter != handles.end(); iter++)
			ret.push_back((T*)handleManager.get(*iter));
	}
	return ret;
}




#endif