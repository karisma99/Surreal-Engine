//CollisionTerrainCommand

#include "CollisionTerrainCommand.h"
#include "CollidableAttorney.h"
#include "SurrealMathTools.h"
#include "Colors.h"
#include "CollisionVolume.h"
#include "Visualizer.h"
#include "SceneManager.h"
#include "TerrainObject.h"

CollisionTerrainCommand::CollisionTerrainCommand(CollidableGroup* g)
{
	pG = g;
}

CollisionTerrainCommand::~CollisionTerrainCommand()
{

}

void CollisionTerrainCommand::Execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = pG->GetColliderCollection();
	TerrainObject* pTerrain = SceneManager::GetCurrentScene()->GetTerrain();

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		pTerrain->Intersect(*it1);
	}
}