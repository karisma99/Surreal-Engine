//CollisionTestSelfCommand

#include "CollisionTestSelfCommand.h"
#include "CollidableAttorney.h"
#include "SurrealMathTools.h"
#include "Colors.h"
#include "CollisionVolume.h"
#include "Visualizer.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd)
{
	pG = g;
	pDispatch = pd;
}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::Execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = pG->GetColliderCollection();

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
		const CollisionVolumeBSphere& dv1 = (*it1)->GetDefaultVolume();

		for (auto it2 = --Collection1.end(); it2 != it1; it2--)
		{
			const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();
			const CollisionVolumeBSphere& dv2 = (*it2)->GetDefaultVolume();

			//Do cv1's and cv2's Bsphere intersect? 
			if (SurrealMathTools::Intersect(dv1, dv2))
			{
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