#include "Headers/SceneSpace.h"

SceneSpace::SceneSpace()
{

}

SceneSpace::~SceneSpace()
{

}

void SceneSpace::Update(float deltatime, glm::mat4 projection, glm::mat4 view, bool& nextScene)
{

	CheckIntersectionsSceneSpace(nextScene, deltatime);

	for (int i = 0; i < meshVector.size(); i++)
	{
		//update the object, in this demo, we just up its position and transform data but you should consider logic
		meshVector[i]->Update(deltatime);
		// the draw routine is the responsbility of the object itself, thats not an ideal system, consider how to improve
		meshVector[i]->Draw(projection, view);
	}
}

void SceneSpace::CheckIntersectionsSceneSpace(bool& nextScene, float deltaTime)
{
	//aabb collisions for the scene
	timeWaint += deltaTime;

	if (timeWaint >= minTimeWait)
	{
		for (int i = 1; i < meshVector.size(); i++)
		{

			for (int j = meshVector.size() - 1; j >= 0; j--)
			{
				if (meshVector.at(i)->type == 4 && meshVector.at(j)->type == 5) {
					if (i != j)
					{
						glm::vec3 boundinbox1 = meshVector.at(i)->theTransform.GetPosition() + meshVector.at(i)->BoundingBoxMin;
						glm::vec3 boundinbox2 = meshVector.at(i)->BoundingBoxMax + meshVector.at(i)->theTransform.GetPosition();
						// use Point versus AABB
						if ((meshVector.at(j)->theTransform.GetPosition().x >= boundinbox1.x && meshVector.at(j)->theTransform.GetPosition().x <= boundinbox2.x) &&
							(meshVector.at(j)->theTransform.GetPosition().y >= boundinbox1.y && meshVector.at(j)->theTransform.GetPosition().y <= boundinbox2.y) &&
							(meshVector.at(j)->theTransform.GetPosition().z >= boundinbox1.z && meshVector.at(j)->theTransform.GetPosition().z <= boundinbox2.z))
						{
							printf("intersection player spacestiong");
							nextScene = true;

						}
						else {

						}
					}
				}
			}
		}
		timeWaint = 0;
	}

}