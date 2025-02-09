#pragma once
#include <Entity.h>
#include "Tilemap.h"

namespace homer
{
	class IScene
	{
	public:
		virtual ~IScene() = default;

		//Fonction appeler pour charger la scene.
		virtual void Load() = 0;

		//Si il en existe, cette fonction retire les préfabs des spawners de la scene.
		virtual void ClearSpawner() = 0;
	};
}