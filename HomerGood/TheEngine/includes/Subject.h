#pragma once
#include "Observer.h"
#include <list>

namespace homer
{
	//Class template. Le "sujet" des classes observers
	template<typename T>
	class Subject
	{
	public:
		//Ajoute un listener à la liste d'observers.
		//<param> listener : le listener a ajouter.
		void AddListener(Observer<T>* listener)
		{
			m_Observers.push_back(listener);
		}

		//Retire un listener de la liste d'observers.
		//<param> listener : le listener a retirer.
		void RemoveListener(Observer<T>* listener)
		{
			m_Observers.remove(listener);
		}

		//Retire tout les listeners de la liste.
		void RemoveAllListeners()
		{
			m_Observers.clear();
		}

		//Appele la fonction OnNotify des observers.
		//<param> value : la valeur a passé en parametre
		void Invoke(const T& value)
		{
			for (Observer<T>* o : m_Observers)
			{
				o->OnNotify(value);
			}
		}
	private:
		std::list<Observer<T>*> m_Observers;
	};
}