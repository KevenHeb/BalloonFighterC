#define WIN32_LEAN_AND_MEAN

#include "ConsoleLogger.h"
#include <Windows.h>
#include <iostream>

HANDLE hConsole;

homer::ConsoleLogger::ConsoleLogger()
{
    AllocConsole();
    int _r = freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    if (_r != 0)
    {
        // Message d'erreur...
        std::cout << "erreur avec la console" << std::endl;
    }

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

homer::ConsoleLogger::~ConsoleLogger()
{
    //If the function fails, the return value is zero.
    int _r = FreeConsole();
    if (_r == 0)
    {
        // Fail message...
        std::cout << "erreur avec la console" << std::endl;
    }
}

void homer::ConsoleLogger::LogMessage(const std::string& message)
{
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << message << std::endl;
}

void homer::ConsoleLogger::LogError(const std::string& message)
{
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "ERROR : " << message << std::endl;
}

void homer::ConsoleLogger::LogWarning(const std::string& message)
{
    SetConsoleTextAttribute(hConsole, 14);
    std::cout << "WARNING : " << message << std::endl;
}