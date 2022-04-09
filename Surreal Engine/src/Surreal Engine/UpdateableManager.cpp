//UpdateableManager

#include "UpdateableManager.h"
#include "UpdateableAttorney.h"

void UpdateableManager::ProcessElements()
{
	for (auto& it : UpdateableList)
	{
		UpdateableAttorney::GameLoop::Update(it);
	}
}

UpdateableManager::StorageListRef UpdateableManager::Register(Updateable* up, StorageListRef ref)
{
	ref = UpdateableList.insert(UpdateableList.end(), up);
	return ref;
}

void UpdateableManager::Deregister(const StorageListRef& ref)
{
	UpdateableList.erase(ref); 
}