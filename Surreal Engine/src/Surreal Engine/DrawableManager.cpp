//DrawableManager

#include "DrawableManager.h"
#include "DrawableAttorney.h"

void DrawableManager::ProcessElements()
{
	for (auto& it : DrawableList)
	{
		DrawableAttorney::GameLoop::Draw(it);
	}

	//2D drawn after 3D 
	for (auto& it : DrawableList)
	{
		DrawableAttorney::GameLoop::Draw2D(it);
	}
}

DrawableManager::StorageListRef DrawableManager::Register(Drawable * up, StorageListRef ref)
{
	ref = DrawableList.insert(DrawableList.end(), up);
	return ref; 
}

void DrawableManager::Deregister(const StorageListRef& ref)
{
	DrawableList.erase(ref); 
}