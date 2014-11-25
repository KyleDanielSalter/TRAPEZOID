#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif /* CLIENT */
#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"

ComponentManager::ComponentManager(const ComponentType type) : managerType(type) {}

void ComponentManager::update(HandleManager &handleManager) {
#ifdef SERVER
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
#endif /* SERVER */
#ifdef CLIENT
	for (auto iter = container.CreateIterator(); iter;) {
		if (!handleManager.get((*iter)->getHandle())) {
			container.RemoveAt(iter.GetIndex());
			iter--;
		} else
			iter++;
	}
#endif  /* CLIENT */
}

ComponentHandle ComponentManager::createComponent(Component* component) {
#ifdef SERVER
	container.push_back(XLib::SharedPtr<Component>(component));
	return ComponentHandle(container.back()->getHandle(), managerType);
#endif /* SERVER */
#ifdef CLIENT
	container.Add(XLib::SharedPtr<Component>(component));
	return ComponentHandle(container.Last()->getHandle(), managerType);
#endif
}