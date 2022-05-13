#include "Headers/SkyBox.h"


GLfloat TheCubeVertices2[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.33f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.33f, 0.50f,
		0.5f, 0.5f, -0.5f, 0.33f, 0.50f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.50f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.330f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.66f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.66f, 0.50f,
		0.5f, 0.5f, 0.5f, 0.66f, 0.50f,
		-0.5f, 0.5f, 0.5f, 0.330f, 0.50f,
		-0.5f, -0.5f, 0.5f, 0.330f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 01.0f, 0.50f,
		-0.5f, -0.5f, -0.5f, 0.660f, 0.50f,
		-0.5f, -0.5f, -0.5f, 0.660f, 0.50f,
		-0.5f, -0.5f, 0.5f, 0.660f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.f, 0.0f,

		0.5f, 0.5f, 0.5f, 0.330f, 0.50f,
		0.5f, 0.5f, -0.5f, 0.330f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.50f,
		0.5f, 0.5f, 0.5f, 0.330f, 0.50f,

		-0.5f, -0.5f, -0.5f, 0.33f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.66f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.66f, 0.5f,
		0.5f, -0.5f, 0.5f, 0.66f, 0.50f,
		-0.5f, -0.5f, 0.5f, 0.33f, 0.50f,
		-0.5f, -0.5f, -0.5f, 0.33f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.66f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.5f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.5f,
		-0.5f, 0.5f, 0.5f, 0.66f, 0.5f,
		-0.5f, 0.5f, -0.5f, 0.66f, 1.0f,

};

SkyBox::SkyBox()
{
	//mTranslationMatrix = glm::mat4(1.0f);
	//mRotationMatrix = glm::mat4(1.0f);
	//mScaleMatrix = glm::mat4(1.0f);
	//Model = glm::mat4(1.0f); // give the model I as an initialisation
	glm::vec3 Pos = glm::vec3(11.0f, 0.0f, 0.4f);
	theTransform.SetPosition(Pos);

	//Scales = glm::vec3(1.0f, 1.0f, 1.0f);
	//SetModelMatrix();

	///WorldPosition = glm::vec3(0, 0, 10);

}

SkyBox::SkyBox(const char* right, const char* left, const char* top, const char* bottem, const char* front, const char* back, int typeobj) : SkyBox()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(TheCubeVertices2), TheCubeVertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	MyFiles fileloader;
	int width, height;
	const char* m_cube_map_textures[6]
	{
		right,
		left,
		top,
		bottem,
		front,
		back,
	};

	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &textureID[0]);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);

	char* image;
	for (int i = 0; i < 6; i++) {

		if (image = fileloader.Load(m_cube_map_textures[i], &imageWidth, &imageHeight)) {

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(cubeMapTarget[i], 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			if (glGetError() != GL_NO_ERROR) printf("Oh bugger, Model graphic init failed\n");
		}

		fileloader.clear(image);
	}

#ifdef RASPBERRY

	std::string frag = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/SkyBoxShader.frag";
	std::string vert = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/SkyBoxShader.vert";
	TheShader = new Shader(vert.c_str(), frag.c_str());
#else
	std::string frag = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/SkyBoxShader.frag";
	std::string vert = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/SkyBoxShader.vert";
	TheShader = new Shader(vert.c_str(), frag.c_str());
#endif

	UVMapUniformLocation = glGetUniformLocation(TheShader->ID, "SkyBoxTexture");
}

SkyBox::~SkyBox()
{
	delete TheShader;
}

bool SkyBox::Update(float deltatime)
{
	if (positionCameraPTR != nullptr)
	{
		theTransform.SetPosition(*positionCameraPTR);
	}
	//mScaleMatrix = glm::mat4(1.0f);

	//mScaleMatrix = glm::scale(mScaleMatrix, theTransform.GetScale());

	//MakeTranslationMatrix();
	//MakeModelMatrix();


	return true;
}

bool SkyBox::Draw(glm::mat4 Projection, glm::mat4 View)
{

	UpdateShaders(Projection, View);

	TheShader->use();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(positionLoc,
		3, // write 3 values
		GL_FLOAT, // they are floats
		GL_FALSE, // not normals
		5 * sizeof(GLfloat),//now many bytes till the next
		0 // where does it start
	);

	glEnableVertexAttribArray(positionLoc);

	//glActiveTexture(GL_TEXTURE0);

	//4 Bind the texture object
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);

	//5. Specify the value of the UV Map uniform
	glUniform1i(UVMapUniformLocation, 0);

	glDisable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	int error = 0;
	if ((error = glGetError()) != GL_NO_ERROR)
	{
		printf("Oh bugger  Draw error\n");
		return false;
	}

	return true;

}

void SkyBox::UpdateShaders(glm::mat4 Projection, glm::mat4 View)
{
	TheShader->use();

	//glEnable(GL_DEPTH_TEST);

	//glDepthFunc(GL_LEQUAL);

	glm::mat4 MVP = Projection * View * theTransform.GetMatrix(); // Remember order seems backwards
	glm::mat4 MV = theTransform.GetMatrix() * View;
	GLuint MatrixID = glGetUniformLocation(TheShader->ID, "MVP"); //LOOK!!!!

	float Amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

}
