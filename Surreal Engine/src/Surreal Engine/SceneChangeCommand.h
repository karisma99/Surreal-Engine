#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	SceneChangeCommand();
	SceneChangeCommand(Scene* s);
	SceneChangeCommand(const SceneChangeCommand& c) = delete;
	SceneChangeCommand& operator = (const SceneChangeCommand& t) = delete;
	~SceneChangeCommand() = default;

	virtual void Execute();

	void SetScene(Scene* s);

private:

	Scene* pScene;

};

#endif _SceneChangeCommand