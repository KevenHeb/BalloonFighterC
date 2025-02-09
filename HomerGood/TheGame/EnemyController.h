#pragma once
#include "Character.h"
#include "Subject.h"
#include "RectF.h"
#include "IEnemyState.h"

namespace homer
{
	//Voir Character.h pour info sur les fonctions.
	class EnemyController : public Character
	{
	public:
		//Sujet invoqué lorsque l'entité est détruites.
		Subject<RectF> OnDestroy;
		EnemyController(Entity* parent);
		virtual ~EnemyController();
		virtual void Start() override;
		virtual void Update(float dt) override;
		void Hit() override;
		void ChangeState(const std::string& state) override;
		Animation* GetAnimation() override;
	private:
		float m_Highest = 0;
		float m_Lowest = 0;
		int m_DirectionX = -1;
		int m_DirectionY = -1;
		int m_Points = 100;
		size_t m_DeathSound;

		IEnemyState* m_CurrentState = nullptr;
		std::map<std::string, IEnemyState*> m_States;
	};
}