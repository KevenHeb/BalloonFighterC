#pragma once
#include "Component.h"
#include <iostream>
#include <string>
#include "IDrawable.h"
#include "RectI.h"
#include "Flip.h"

namespace homer
{
	class Entity;

	class Sprite : public Component, public IDrawable
	{
	public:
		virtual ~Sprite() = default;
		Sprite(Entity* parent);

		//Ajoute comme ID le nom du fichier au sprite.
		void SetId(const std::string& name);
		virtual void Draw() override;

		//Assigne le frame recue en parametre au sprite
		void SetCurrentFrame(RectI frame);

		//Flip le sprite sur l'horizontal et/ ou la verticale selon les parametre h et v.
		void SetFlip(bool h, bool v);

		//Retourne vrai si le sprite est à l'envers sur l'axe horizontal
		bool GetFlipH() const ;
		//Retourne vrai si le sprite est à l'envers sur l'axe vertical
		bool GetFlipV() const ;

	private:
		size_t m_TextureId = 0;
		Flip m_Flip = { false, false };
	protected:
		RectI m_CurrentFrame = {0,0,0,0} ;
	};
}
