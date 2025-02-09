#pragma once
#include <ILogger.h>

namespace homer
{
    class ConsoleLogger : public ILogger
    {
    public:
        ConsoleLogger();
        virtual ~ConsoleLogger();

        //Affiche a la console un message recue en parametre.
        //<param> message : le message a afficher.
        virtual void LogMessage(const std::string& message) override;

        //Affiche a la console un message d'erreur.
        //<param> message : le message a afficher.
        virtual void LogError(const std::string& message) override;

        //Affiche a la console un message warning.
        //<param> message : le message a afficher.
        virtual void LogWarning(const std::string& message) override;
    };
}
