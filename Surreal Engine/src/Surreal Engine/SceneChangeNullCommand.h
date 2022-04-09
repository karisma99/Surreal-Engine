#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNullCommand() = default;
	SceneChangeNullCommand(const SceneChangeNullCommand& c) = delete;
	SceneChangeNullCommand& operator = (const SceneChangeNullCommand& t) = delete;
	~SceneChangeNullCommand() = default;

	virtual void Execute();
private:

};

#endif _SceneChangeNullCommand