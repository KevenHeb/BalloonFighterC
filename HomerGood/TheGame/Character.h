#pragma once
#include "Atlas.h"
#include "Animation.h"
#include <map>
#include <string>
#include "Tilemap.h"

namespace homer
{
	typedef std::map<std::string, std::vector<int>> ColliderTypes;
	class Character : public Component, public IUpdatable
	{
	public:
		//Constructeur
		Character(Entity* parent) : Component(parent) {};
		//Destructeur
		virtual ~Character() = default;
		//Start
		virtual void Start() = 0;
		//Update
		virtual void Update(float dt) = 0;

		//Methode appelé lorsque le personnage est frapper.
		virtual void Hit() = 0;

		//Change le state du character.
		//<param> state : le nom de la state a assigné au personnage.
		virtual void ChangeState(const std::string& state) = 0;

		//Retourne le component animation du character
		virtual Animation* GetAnimation() = 0;
	protected:
		Tilemap* m_Tilemap = nullptr;
		Entity* m_FeetCollider = nullptr;
		Entity* m_BalloonCollider = nullptr;
		ColliderTypes m_IndexMap;
		Animation* m_Animation = nullptr;
		Atlas* m_Atlas = nullptr;
	};
}