#ifndef _SceneChangeCommandBase
#define _SceneChangeCommandBase

class SceneChangeCommandBase
{
public:
	SceneChangeCommandBase();
	SceneChangeCommandBase(const SceneChangeCommandBase& c) = delete;
	SceneChangeCommandBase& operator = (const SceneChangeCommandBase& t) = delete;
	virtual ~SceneChangeCommandBase();

	virtual void Execute();
private:

};

#endif _SceneChangeCommandBase
