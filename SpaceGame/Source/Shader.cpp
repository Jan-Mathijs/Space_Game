#include "Headers/Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// open files
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);
	std::stringstream vShaderStream, fShaderStream;
	// read file's buffer contents into streams
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();
	// close file handlers
	vShaderFile.close();
	fShaderFile.close();
	// convert stream into string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();


	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// GLenum err = gladInit;
	// vertex Shader
	// glewExperimental = GL_TRUE;


	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// similiar for Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	// glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(ID);
}

GLuint Shader::MakeShader(GLenum type, const char* shaderSrc)
{

	GLuint TheShader = glCreateShader(type);	// 1st create the shader object

	if (TheShader == 0) return FALSE; // can't allocate so stop.


	glShaderSource(TheShader, 1, &shaderSrc, NULL); // pass the shader source then compile it
	glCompileShader(TheShader);

	GLint  IsItCompiled;


	glGetShaderiv(TheShader, GL_COMPILE_STATUS, &IsItCompiled); // After the compile we need to check the status and report any errors
	if (!IsItCompiled)
	{
		GLint RetinfoLen = 0;
		glGetShaderiv(TheShader, GL_INFO_LOG_LENGTH, &RetinfoLen);
		if (RetinfoLen > 1)
		{ // standard output for errors
			char* infoLog = (char*)malloc(sizeof(char) * RetinfoLen);
			glGetShaderInfoLog(TheShader, RetinfoLen, NULL, infoLog);
			fprintf(stderr, "There was an error Error compiling shader:\n %s\n %s\n", shaderSrc, infoLog);
			free(infoLog);
		}
		glDeleteShader(TheShader);
		return FALSE;
	}
	return TheShader;
}

GLuint Shader::MakeProgramObject(const char* Vfname, const char* Ffname)
{
	GLuint vShad = LoadAndMakeShader(GL_VERTEX_SHADER, Vfname);
	GLuint fShad = LoadAndMakeShader(GL_FRAGMENT_SHADER, Ffname);

	GLuint PO = MakeProgramObject(vShad, fShad);
	// we do checks for validity in each routine so no real need to check again but leave the option open
	return PO;

}

GLuint Shader::LoadAndMakeShader(GLenum type, const char* Fname)
{
	//   const char* ShaderTxt = FH->LoadText(Fname);
	std::string vertexCode;
	// std::string fragmentCode;
	std::ifstream vShaderFile;
	// std::ifstream fShaderFile;
	 // ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	// fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	 // open files
	vShaderFile.open(Fname);
	//fShaderFile.open(fragmentPath);
	std::stringstream vShaderStream, fShaderStream;
	// read file's buffer contents into streams
	vShaderStream << vShaderFile.rdbuf();
	//  fShaderStream << fShaderFile.rdbuf();
	  // close file handlers
	vShaderFile.close();
	//  fShaderFile.close();
	  // convert stream into string
	vertexCode = vShaderStream.str();
	//  fragmentCode = fShaderStream.str();


	const char* vShaderCode = vertexCode.c_str();
	//const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex;
	int success;

	char infoLog[512];
	// print out the shader		
	printf("shader loaded from filename %s \n %s\n", Fname, vShaderCode);

	GLuint Shader = MakeShader(type, vShaderCode);

	if (Shader == 0) printf("Failed to compile Shader/n");

	return Shader; // it will return 0 if its failed so watch for that

}

GLuint Shader::MakeProgramObject(GLuint VShad, GLuint FShad)
{


	// Create the program object	
	GLuint PO = glCreateProgram();

	if (PO == 0) 	return FALSE;

	// now we have the V and F shaders  attach them to the progam object
	glAttachShader(PO, VShad);
	glAttachShader(PO, FShad);

	// Link the program
	glLinkProgram(PO);
	// Check the link status
	GLint LinkedOk;

	glGetProgramiv(PO, GL_LINK_STATUS, &LinkedOk);
	if (!LinkedOk)
	{
		GLint RetinfoLen = 0; // check and report any errors using standard system

		glGetProgramiv(PO, GL_INFO_LOG_LENGTH, &RetinfoLen);
		if (RetinfoLen > 1)
		{
			GLchar* infoLog = (GLchar*)malloc(sizeof(char) * RetinfoLen);
			glGetProgramInfoLog(PO, RetinfoLen, NULL, infoLog);
			fprintf(stderr, "Error linking program:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteProgram(PO);
		return FALSE;
	}


	return PO;
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}