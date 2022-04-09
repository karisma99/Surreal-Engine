#ifndef _DrawableManager
#define _DrawableManager

#include <list>

class Drawable;

class DrawableManager
{
private:
	using StorageList = std::list<Drawable*>;
	StorageList DrawableList;

public:
	using StorageListRef = StorageList::iterator;

	DrawableManager() = default;
	DrawableManager(const DrawableManager& c) = delete;
	DrawableManager& operator = (const DrawableManager& t) = delete;
	~DrawableManager() = default;

	void ProcessElements();
	StorageListRef Register(Drawable* up, StorageListRef ref);
	void Deregister(const StorageListRef& ref);
};

#endif _DrawableManager