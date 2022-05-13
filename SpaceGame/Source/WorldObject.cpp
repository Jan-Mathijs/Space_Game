#include "Headers/WorldObject.h"

WorldObject::WorldObject()
{

}

WorldObject::~WorldObject()
{

}

WorldObject::WorldObject(Shader* shader, int typeobj, float mass)
{
    TheShader = shader;
    type = typeobj;
    MassObject = mass;
}

bool WorldObject::Update(float deltatime)
{
    if (MyPhysObj != NULL)

    {
        MyPhysObj->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	    //MyPhysObj->GetRigidBody()->setDamping(0.2f, 0.15f);
        btScalar transform[16]; // physics uses a 16 float matrix syste       
        btTransform Trans;
        // now get transform from Bullet which has been converted to an OpenGL matrix format
        this->MyPhysObj->GetTransform(transform);
        glm::vec3 temp;
        temp.x = transform[12];
        temp.y = transform[13];
        temp.z = transform[14]; // don't need the w.
        theTransform.SetPosition(temp);
        // printf("%f, %f, %f\n", temp.x, temp.y, temp.z);

        // work out forward and Right       
        btQuaternion orient = this->MyPhysObj->GetRigidBody()->getOrientation();
        btVector3 tempvec = btVector3(0, 0, -1);
        btVector3 tempquat = quatRotate(orient, tempvec);
        theTransform.SetLocalRotationMatrix(glm::toMat4(bulletToGlm(orient)));

        glm::mat4 Model;
        // transfer the OpenGL (rotation and position) to Model matrix and mult by scale for a full Model Matrix   
        for (int i = 0; i < 16; i++) // we now transfer our physics matrix
            Model[i / 4][i % 4] = transform[i]; // to our game matix for place and view
        theTransform.SetModel(Model);

        theTransform.SetScaleMatrix(glm::mat4(1.0f));
        theTransform.SetScaleMatrix(glm::scale(theTransform.GetScaleMatrix(), theTransform.GetScale()));
        glm::mat4 T = theTransform.GetLocalModelMatrix() * theTransform.GetScaleMatrix();       
        theTransform.SetModel(T);      
    }
    return true;
}


bool WorldObject::Draw(glm::mat4 Projection, glm::mat4 View)
{
    if (theWorldMesh == nullptr) return false;
   
    UpdateShaders(Projection, View);

    if (glGetError() != GL_NO_ERROR)
    {
        printf("Oh bugger  Draw error1\n");
        //  return false;
    }

    for (int i = 0; i < theWorldMesh->drawObjects.size(); i++)
    {


        glBindBuffer(GL_ARRAY_BUFFER, theWorldMesh->drawObjects.at(i).vb_id);
        //TheShader.use();

        glEnableVertexAttribArray(this->positionLoc);
        //load the vertex data
        glVertexAttribPointer(this->positionLoc,
            3, // write 3 values
            GL_FLOAT, // they are floats
            GL_FALSE, // not normals
            11 * sizeof(GLfloat),//now many bytes till the next
            0 // where does it start
        ); // use 3 values, but add 5 each time to get to the next
      // Load the texture coordinate
        glEnableVertexAttribArray(this->texCoordLoc);
        glVertexAttribPointer(this->texCoordLoc,
            2,
            GL_FLOAT,
            GL_FALSE,
            11 * sizeof(GLfloat),
            (GLfloat*)(9 * sizeof(GLfloat))
        );


        if (normLoc != -1)
        {
            glEnableVertexAttribArray(this->normLoc);
            glVertexAttribPointer(this->normLoc,
                3, // write 3 values
                GL_FLOAT, // they are floats
                GL_TRUE, // not normals
                11 * sizeof(GLfloat),//now many bytes till the next
                (GLfloat*)(3 * sizeof(GLfloat)) // where does it start
            ); //
        }

        //binding the texture with the object
        //bind a empty texture to the obj so it will always be displayed
        glBindTexture(GL_TEXTURE_2D, 0);

        //got these 7 lines from viewer.cc example code tiny obj loader
        //check if there is a texture so yes and is it in range and the correct name give the obj the texture
        if ((theWorldMesh->drawObjects.at(i).material_id < theWorldMesh->materials.size())) {
            std::string diffuse_texname = theWorldMesh->materials[theWorldMesh->drawObjects.at(i).material_id].diffuse_texname;
            if (theWorldMesh->textures.find(diffuse_texname) != theWorldMesh->textures.end()) {
                glBindTexture(GL_TEXTURE_2D, theWorldMesh->textures[diffuse_texname]);
            }
        }

        glDrawArrays(GL_TRIANGLES, 0, theWorldMesh->drawObjects.at(i).numTriangles * 3);
        int error = 0;
        if ((error = glGetError()) != GL_NO_ERROR)
        {
           printf("Oh bugger  Draw error %i \n", error);
            //return false;
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}


void WorldObject::UpdateShaders(glm::mat4 Projection, glm::mat4 View)
{
    TheShader->use();

#ifdef RASPBERRY
  
    
        glm::vec3 lightPosvalue(0);
        TheShader->setVec3("LightPosition", lightPosvalue);

        glm::mat3 rotationMatrixMat3 = glm::transpose(glm::inverse(theTransform.GetMatrix()));
        TheShader->setMat3("rotationMatrix", rotationMatrixMat3);

        glm::mat4 MV = theTransform.GetMatrix();
        TheShader->setMat4("MV", MV);

        glm::mat4 MVP = Projection * View * theTransform.GetMatrix(); // Remember order seems backwards
        TheShader->setMat4("MVP", MVP);

       
       // TheShader->setVec4("Ambient", Amb.x, Amb.y, Amb.z, Amb.w);
   
       
        if (changeLight == true) {
            Amb = glm::vec4(3.0f, 3.0f, 3.0f, 1.0f);
        }
        else {
            Amb = glm::vec4(1.0f);
        }
       
        TheShader->setVec4("Ambient", Amb.x, Amb.y, Amb.z, Amb.w);
    

#else
    if (TheShader->ID == 6)
    {
        glm::vec3 lightPosvalue(0);
        TheShader->setVec3("LightPosition", lightPosvalue);

        glm::mat3 rotationMatrixMat3 = glm::transpose(glm::inverse(theTransform.GetMatrix()));
        TheShader->setMat3("rotationMatrix", rotationMatrixMat3);

        glm::mat4 MV = theTransform.GetMatrix();
        TheShader->setMat4("MV", MV);
    }

    glm::mat4 MVP = Projection * View * theTransform.GetMatrix(); // Remember order seems backwards
    TheShader->setMat4("MVP", MVP);

    glm::vec4 Amb(1);
    TheShader->setVec4("Ambient", Amb);
#endif


}

