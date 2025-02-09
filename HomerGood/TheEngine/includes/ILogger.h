#pragma once
#include <string>

namespace homer
{
    class ILogger
    {
    public:
        virtual ~ILogger() = default;
        virtual void LogMessage(const std::string& message) = 0;
        virtual void LogError(const std::string& message) = 0;
        virtual void LogWarning(const std::string& message) = 0;
    };
}