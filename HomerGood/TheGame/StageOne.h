#pragma once
#include "IScene.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "Bubble.h"
#include "Spawner.h"

namespace homer
{
	//Premier stage
	class StageOne : public homer::IScene
	{
	public:
		virtual ~StageOne();
		virtual void Load() override;
		virtual void ClearSpawner() override;
	private:
		Spawner m_Spawner;
		int m_Enemies = 2;
	};
}