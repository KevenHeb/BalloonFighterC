#include "Sprite.h"
#include "Engine.h"
#include "Entity.h"
#include "Flip.h"

homer::Sprite::Sprite(Entity* parent) : Component(parent)
{
	
}

//Assigne au sprite une ID via le service graphique.
void homer::Sprite::SetId(const std::string& name)
{
	m_TextureId = Graphics().LoadTexture(name);
}

void homer::Sprite::SetCurrentFrame(RectI frame)
{
	m_CurrentFrame = frame;
}

void homer::Sprite::SetFlip(bool h, bool v)
{
	m_Flip = { h, v };
}

bool homer::Sprite::GetFlipH() const
{
	return m_Flip.h;
}

bool homer::Sprite::GetFlipV() const
{
	return m_Flip.v;
}

//Methode qui dessine l'image de l'entité.
void homer::Sprite::Draw()
{
	Graphics().DrawTexture(m_TextureId, m_CurrentFrame, m_Entity->GetPosition(), 0.0, m_Flip, Color::WHITE);
}
