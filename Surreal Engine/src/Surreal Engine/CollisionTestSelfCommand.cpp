//CollisionTestSelfCommand

#include "CollisionTestSelfCommand.h"
#include "CollidableAttorney.h"
#include "SurrealMathTools.h"
#include "Colors.h"
#include "CollisionVolumeBSphere.h"
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
		const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();

		for (auto it2 = --Collection1.end(); it2 != it1; it2--)
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