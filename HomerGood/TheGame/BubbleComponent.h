#pragma once
#include "Component.h"
#include "IUpdatable.h"

namespace homer
{
	class BubbleComponent : public Component, public IUpdatable
	{
	public:
		//Constructeur
		BubbleComponent(Entity* parent);
		//Update
		void Update(float dt) override;
		//M�thode appel� lorsque la bulle est touch�.
		void Hit();
	private:
		int points = 100;
		size_t m_PopSFX;
	};
}
