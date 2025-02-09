#pragma once
#include "IScene.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "Bubble.h"
#include "Spawner.h"

namespace homer
{
	//Deuxieme stage
	class StageTwo : public homer::IScene
	{
	public:
		virtual ~StageTwo();
		virtual void Load() override;
		void ClearSpawner() override;
	private:
		Spawner m_Spawner;
		int m_Enemies = 4;
	};
}