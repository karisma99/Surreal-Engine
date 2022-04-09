#ifndef _UpdateableManager
#define _UpdateableManager

#include <list>

class Updateable; 

class UpdateableManager
{	
private:
	using StorageList = std::list<Updateable*>;
	StorageList UpdateableList;

public:
	using StorageListRef = StorageList::iterator;

	UpdateableManager() = default;
	UpdateableManager(const UpdateableManager& c) = delete;
	UpdateableManager& operator = (const UpdateableManager& t) = delete;
	~UpdateableManager() = default;

	void ProcessElements();
	StorageListRef Register(Updateable* up, StorageListRef ref);
	void Deregister(const StorageListRef& ref);


};

#endif _UpdateableManager