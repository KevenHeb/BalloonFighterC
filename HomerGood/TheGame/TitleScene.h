#pragma once
#include "IScene.h"
#include "PlayerController.h"

namespace homer
{
	//Scene de début.
	class TitleScene : public homer::IScene
	{
	public:
		virtual ~TitleScene();
		virtual void Load() override;
		void ClearSpawner() override;
	};
}