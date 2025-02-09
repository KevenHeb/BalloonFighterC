#pragma once

namespace homer
{
	//Class template. Utiliser pour permettre a des classes observers d'appeler la méthode OnNotify en évitant le couplage.
	//T représente le type de données à recevoir en parametre.
	template<typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const T& value) = 0;
	};
}