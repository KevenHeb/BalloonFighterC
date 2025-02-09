#pragma once
#include "Sprite.h"
#include <map>
#include <vector>

namespace homer 
{
	class Atlas : public Sprite
	{
	public:
		//Constructeur
		Atlas(Entity* parent);

		/**
		* Rajoute au atlas le frame spécifier
		* <param> name : le nom du frame
		* <params> x,y : la position frame 
		* <params> w,h : les dimensions du frame.
		*/
		void AddFrame(const std::string& name, int x, int y, int w, int h);

		/**
		* Assigne le frame nommé au sprite de l'entité parent
		* <param> name : le nom du frame a assigné.
		*/
		void SetFrame(const std::string& name);
	private:
		std::map<std::string, RectI> m_FrameSheet;
	};
}