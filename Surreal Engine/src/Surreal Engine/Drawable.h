#ifndef _Drawable
#define _Drawable

#include "RegistrationState.h"
#include "DrawableManager.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

class DrawableManager;
class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
	friend class DrawableAttorney;

public:
	Drawable();
	Drawable(const Drawable& c) = delete;
	Drawable& operator = (const Drawable& t) = delete;
	virtual ~Drawable();

	void SubmitDrawRegistration();
	void SubmitDrawDeregistration();

private:
	virtual void Draw();
	virtual void Draw2D();

	void SceneRegistration();
	void SceneDegregistration();

	RegistrationState CurrState;
	DrawRegistrationCommand* pRegisterCmd; 
	DrawDeregistrationCommand* pDeregisterCmd;
	DrawableManager::StorageListRef pMyDeleteRef;

};

#endif _Drawable