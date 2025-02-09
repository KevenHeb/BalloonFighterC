#pragma once
#include <ILogger.h>
#include <iostream>
#include <fstream>

namespace homer
{
    class FileLogger : public ILogger
    {
    public:
        FileLogger();
        FileLogger(const std::string& filename);
        virtual ~FileLogger();

        //Écrit dans un fichier log un message recue en parametre.
        //<param> message : le message a afficher.
        virtual void LogMessage(const std::string& message) override;

        //Écrit dans un fichier log un message d'erreur.
        //<param> message : le message a afficher.
        virtual void LogError(const std::string& message) override;

        //Écrit dans un fichier log un message warning.
        //<param> message : le message a afficher.
        virtual void LogWarning(const std::string& message) override;

    private:
        std::ofstream m_LogFile;
    };
}
