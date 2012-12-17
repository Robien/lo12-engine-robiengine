#include "Outil.h"

int Outil::getHauteurFenetre()
{
	GLint m_viewport[4];
	glGetIntegerv( GL_VIEWPORT, m_viewport );
	return m_viewport[3];
}

int Outil::getLargeurFenetre()
{
	GLint m_viewport[4];

	glGetIntegerv( GL_VIEWPORT, m_viewport );
	return m_viewport[2];
}