#include "Headers/PhysicsDraw.h"
#ifdef RASPBERRY
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif

GLuint PhysicsDraw::ProgramObject;

void PhysicsDraw::drawLine(const btVector3& from,
	const btVector3& to,
	const btVector3& color)
{
	// draws a simple line of pixels between points but stores them for later draw
	LineValues Line;
	Line.p1 = from;
	Line.p2 = to;

	TheLines.push_back(Line);
	// we don't care about colour?	

}

void PhysicsDraw::DoDebugDraw()
{// set up the line shader and then draw the buffer
			//load the vertex data info
	//glUseProgram(PhysicsDraw::ProgramObject);
	glVertexAttribPointer(this->positionLoc,
		3,	// there are 3 values xyz
		GL_FLOAT, // they a float
		GL_FALSE, // don't need to be normalised
		4 * sizeof(float),  // how many floats to the next one(be aware btVector3 uses 4 floats)
		(GLfloat*)&this->TheLines[0]  // where do they start as an index); // use 3 values, but add stride each time to get to the next
	);


	glEnableVertexAttribArray(this->positionLoc);
	glDrawArrays(GL_LINES, 0, TheLines.size() * 2);

	TheLines.clear();

}
void PhysicsDraw::drawContactPoint(const btVector3& pointOnB,
	const btVector3& normalOnB,
	btScalar distance,
	int lifeTime,
	const btVector3& color)
{
	drawLine(pointOnB, pointOnB + normalOnB * distance, color);
}


void PhysicsDraw::ToggleDebugFlag(int flag)
{
	// checks if a flag is set and enables/
	// disables it
	if (m_debugMode & flag)
		// flag is enabled, so disable it
		m_debugMode = m_debugMode & (~flag);
	else
		// flag is disabled, so enable it
		m_debugMode |= flag;
}