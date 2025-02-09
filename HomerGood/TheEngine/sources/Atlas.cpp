#include "Atlas.h"

homer::Atlas::Atlas(Entity* parent) : Sprite(parent)
{
}

//Ajoute un "frame" dans l'atlas de l'entité.
void homer::Atlas::AddFrame(const std::string& name, int x, int y, int w, int h)
{
	if (m_FrameSheet.count(name) == 0)
	{
		m_FrameSheet.emplace(name, RectI{ x,y,w,h });
	}
}

//Assigne une frame a utiliser pour dessiner l'entité.
void homer::Atlas::SetFrame(const std::string& name)
{
	if (m_FrameSheet.count(name) > 0)
	{
		m_CurrentFrame = m_FrameSheet[name];
	}
}
