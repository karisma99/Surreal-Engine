#ifndef _Updateable
#define _Updateable

#include "RegistrationState.h"
#include "UpdateableManager.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

class UpdateableManager;
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updateable
{
	friend class UpdateableAttorney;
public:
	Updateable();
	Updateable(const Updateable& c) = delete;
	Updateable& operator = (const Updateable& t) = delete;
	virtual ~Updateable();
	
	void SubmitUpdateRegistration();
	void SubmitUpdateDeregistration();

private:
	virtual void Update();

	void SceneRegistration();
	void SceneDegregistration();

	RegistrationState CurrState; 
	UpdateRegistrationCommand* pRegisterCmd;
	UpdateDeregistrationCommand* pDeregisterCmd;
	UpdateableManager::StorageListRef pMyDeleteRef;
};

#endif _Updateable