#include "Headers/PlayerSpace.h"

PlayerSpace::PlayerSpace(Shader* localshader, int typeplayer)
{
    theTransform.SetPosition(glm::vec3(0, 0, -25));
 
    theTransform.SetScale(glm::vec3(1));
    TheShader = localshader;

    type = typeplayer;
    BoundingBoxMin = glm::vec3(0);
    BoundingBoxMax = glm::vec3(10);
}