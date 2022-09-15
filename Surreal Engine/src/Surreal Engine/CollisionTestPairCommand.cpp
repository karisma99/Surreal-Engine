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

	// Test 1: Do G1 and G2 AABB's intersect?
	if (SurrealMathTools::Intersect(pG1->GetGroupAABB(), pG2->GetGroupAABB()))
	{
		for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
		{
			const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
			const CollisionVolumeBSphere& dv1 = (*it1)->GetDefaultVolume();

			// Does cv1 BSphere intersect G2 AABB?
			if (SurrealMathTools::Intersect(dv1, pG2->GetGroupAABB()))
			{
				for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
				{
					const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();
					const CollisionVolumeBSphere& dv2 = (*it2)->GetDefaultVolume();

					// Do cv2's and cv1's Bsphere intersect?
					if (SurrealMathTools::Intersect(dv1, dv2))
					{
						// Regular collision test
						if (SurrealMathTools::Intersect(cv1, cv2))
						{
							pDispatch->ProcessCallbacks(*it1, *it2);

							Visualizer::ShowCollisionVolume(cv1, Color::Red);
							Visualizer::ShowCollisionVolume(cv2, Color::Red);
						}
						else
						{
							Visualizer::ShowCollisionVolume(cv1, Color::Blue);
							Visualizer::ShowCollisionVolume(cv2, Color::Blue);
						}
					}

					Visualizer::ShowSphere(dv2, Color::Yellow);
				}

				Visualizer::ShowSphere(dv1, Color::Yellow);
			}

			
		}
	}

	Visualizer::ShowBox(pG1->GetGroupAABB(), Color::Green);
	Visualizer::ShowBox(pG2->GetGroupAABB(), Color::Green);

}