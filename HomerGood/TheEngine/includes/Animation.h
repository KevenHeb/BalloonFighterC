#pragma once
#include "Component.h"
#include <iostream>
#include <map>
#include "IUpdatable.h"
#include "Clip.h"

namespace homer
{
	class Animation : public Component, public IUpdatable
	{
	public:
		//Destructeur
		virtual ~Animation() = default;
		//Constructeur
		//<param> parent:
		Animation(Entity* parent);

		//Update
		void Update(float dt);

		/**
		* Initialise les paramêtres du component Animation
		* <param> frameInRows : indique le nombre de frame maximum par ranger que l'animation a.
		* <param> framwWidth : indique la taille en longueur des frames de l'animation.
		* <param> frameHeight : indique la taille en hauteur des frames de l'animation
		*/
		void InitAnimation(int frameInRows, int frameWidth, int frameHeight);

		/**
		* Initialise les paramêtres du component Animation
		* <param> frameInRows : indique le nombre de frame maximum par ranger que l'animation possede
		* <param> framwWidth : indique la taille en longueur des frames de l'animation
		* <param> frameHeight : indique la taille en hauteur des frames de l'animation
		*/
		void AddClip(const std::string& name, int startRow, int start, int count, float delay);

		//Arrete de jouer le clip courant
		void Stop();

		//Retourne le nom du clip courant
		std::string GetCurrentClip();

		//Retourne vrai si un clip est en train de jouer
		bool GetIsPlaying();

		/**
		* Demande au component de jouer un clip
		* <param> name : le nom du clip à jouer
		* <param> loop : indique si le clip doit jouer en boucle ou non.
		*/
		void Play(const std::string& name, bool loop);

	private:
		std::string m_CurrentClip;
		size_t m_AnimationSource = 0;
		std::map<std::string, Clip> m_ClipList;

		int m_CurrentFrame = 0;
		int m_frameInRows = 0;
		int m_frameWidth = 0;
		int m_frameHeight = 0;

		float m_TimePassed = 0;

		bool m_Loop = false;
		bool m_Play = false;
	};
}