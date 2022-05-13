#pragma once
#ifdef RASPBERRY
#include <glm/glm.hpp>
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#include <glm/glm.hpp>
#endif
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#define TRUE 1
#define FALSE 0

//got this code from learnopengl.com
class Shader
{
public:
	// the program ID
	unsigned int ID = -1;

	Shader() {}
	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void use();
	// utility uniform functions

	GLuint MakeShader(GLenum type, const char* shaderSrc);
	GLuint MakeProgramObject(GLuint VShad, GLuint FShad);
	GLuint MakeProgramObject(const char* Vfname, const char* Ffname);

	GLuint LoadAndMakeShader(GLenum type, const char* Fname);


	//learn open gl code
	//https://learnopengl.com/Getting-started/Shaders

	void setBool(const std::string& name, bool value);

	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value);

	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value);

	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value);

	void setVec2(const std::string& name, float x, float y);

	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value);

	void setVec3(const std::string& name, float x, float y, float z);

	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value);

	void setVec4(const std::string& name, float x, float y, float z, float w);

	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat);

	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat);

	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat);



};


