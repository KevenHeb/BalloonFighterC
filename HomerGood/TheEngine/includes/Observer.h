#pragma once

namespace homer
{
	//Class template. Utiliser pour permettre a des classes observers d'appeler la m�thode OnNotify en �vitant le couplage.
	//T repr�sente le type de donn�es � recevoir en parametre.
	template<typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const T& value) = 0;
	};
}