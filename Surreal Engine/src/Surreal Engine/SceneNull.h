#ifndef _SceneNull
#define _SceneNull

#include "../Surreal Engine/Scene.h"

class SceneNull : public Scene
{
public:

	SceneNull() = default;
	SceneNull(const SceneNull& c) = delete;
	SceneNull& operator = (const SceneNull& t) = delete;
	~SceneNull() = default;


	virtual void Initialize() { };
	virtual void SceneEnd() { };

private:

};

#endif _SceneNull