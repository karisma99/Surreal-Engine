#ifndef _GameObject
#define _GameObject

#include "Drawable.h"
#include "Updateable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "RegistrationState.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"

class GameObjectEntryCommand; 
class GameObjectExitCommand; 

class GameObject : public Drawable, public Updateable, public Alarmable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;

public:
	GameObject();
	GameObject(const GameObject& c) = delete;
	GameObject& operator = (const GameObject& t) = delete;
	virtual ~GameObject();

	void SubmitEntry();
	void SubmitExit();

private: 
	virtual void SceneEntry();
	virtual void SceneExit();

	void ConnectToScene(); 
	void DisconnectFromScene();

	RegistrationState CurrState;
	GameObjectEntryCommand* pEntryCmd;
	GameObjectExitCommand* pExitCmd;

};

#endif _GameObject