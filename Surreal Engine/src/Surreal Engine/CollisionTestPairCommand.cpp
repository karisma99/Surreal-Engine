//CollisionTestPairCommand

#include "CollisionTestPairCommand.h"
#include "CollidableAttorney.h"
#include "Visualizer.h"
#include "SurrealMathTools.h"
#include "Colors.h"


CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd)
{
	pG1 = g1; 
	pG2 = g2; 
	pDispatch = pd;
}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch; 
}

void CollisionTestPairCommand::Execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();
	const CollidableGroup::CollidableCollection& Collection2 = pG2->GetColliderCollection();

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();

		for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
		{
			const CollisionVolumeBSphere& bs2 = (*it2)->GetBSphere();

			if (SurrealMathTools::Intersect(bs1, bs2))
			{
				pDispatch->ProcessCallbacks(*it1, *it2);

				Visualizer::ShowSphere(bs1, Color::Red);
				Visualizer::ShowSphere(bs2, Color::Red);
			}
			else
			{
				Visualizer::ShowSphere(bs1, Color::Blue);
				Visualizer::ShowSphere(bs2, Color::Blue);
			}
		}
	}

}