#pragma once
#include "IScene.h"
#include "PlayerController.h"

namespace homer
{
	//Scene de d�but.
	class TitleScene : public homer::IScene
	{
	public:
		virtual ~TitleScene();
		virtual void Load() override;
		void ClearSpawner() override;
	};
}