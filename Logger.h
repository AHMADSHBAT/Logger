/*********************************************************************
	Rhapsody	: 9.0.2 
	Login		: uie69353
	Component	: SDDComponent 
	Configuration 	: DefaultConfig
	Model Element	: Logger
//!	Generated Date	: Fri, 1, Nov 2024  
	File Path	: SDDComponent\DefaultConfig\system\Logger.h
*********************************************************************/

#ifndef system_Logger_H
#define system_Logger_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]

//## operation getTime(char*,uint8)
#include "Platform_Types.h"
//## auto_generated
#include <chrono>
//## auto_generated
#include <cstdarg>
//## package SWDD_UwbRadarFunctions::SWDD_SwcUwbRadarSystemMgr::DetailedDesign::DesignElements::UwbSystemMgr

//## class Logger

//#[ ignore
#if defined(_MSC_VER) && !defined(_MSC_GTEST)
    #include "ManagedLogger.h"
    #include <iostream>
    using namespace System;
#endif

#define LOG(severity, msg, ...) Logger::print(__FUNCTION__, severity, msg, ##__VA_ARGS__)
//#]


class Logger {
public :

    //## type Severity
    enum Severity
    {
        INFO = 0,
        ERR = 1,
        WARN = 2,
        DEBUG = 3,
        CRITICAL = 4,
        MAX = 5
    };
    
    ////    Constructors and destructors    ////
    
    //## auto_generated
    ~Logger();
    
    ////    Operations    ////
    
    //## operation print(const char*,Severity,const char*)
    inline static void print(const char* func, const Severity severity, const char* msg, ...);
    
    //## operation printToConsole(const char*,Severity,const char*)
    inline static void printToConsole(const char* func, const Severity severity, const char* msg, ...);
    
    //## operation printToWindowsForms(const char*,Severity,const char*)
    inline static void printToWindowsForms(const char* func, const Severity severity, const char* msg, ...);
    
    //## operation setSeverityLevel(Severity,bool)
    inline static void setSeverityLevel(const Severity severity, const bool level) noexcept;
    
    //## operation setSeverityLevel(uint8)
    inline static void setSeverityLevel(const uint8 levels);

private :

    //## operation getTime(char*,uint8)
    inline static void getTime(char* buffer, const uint8& size);
    
    //## operation isSeverityPrintable(Severity)
    inline static bool isSeverityPrintable(const Severity severity) noexcept;
    
    //## operation severityToString(Severity)
    inline static const char* severityToString(const Severity& severity);
    
    ////    Attributes    ////

protected :

    static uint8 m_severityBitField;		//## attribute m_severityBitField
};

inline void Logger::print(const char* func, const Logger::Severity severity, const char* msg, ...) {
    //#[ operation print(const char*,Severity,const char*)
    //#[ operation print(const char*,Severity,const char*)
        if (Logger::isSeverityPrintable(severity) == FALSE)
        {
            return;
        }
        
        va_list args;
        va_start(args, msg);
        
    #ifdef _MSC_VER
        Logger::printToWindowsForms(func, severity, msg, args);
    #elif defined(_FILE_PRT) //TODO to be defined..
        Logger::printToFile(func, severity, msg, args);
    #else
        Logger::printToConsole(func, severity, msg, args);
    #endif
        
        va_end(args); // Clean up the variable argument list
    //#]
}

inline void Logger::printToConsole(const char* func, const Logger::Severity severity, const char* msg, ...) {
    //#[ operation printToConsole(const char*,Severity,const char*)
    #if defined(_MSC_VER) && !defined(_MSC_GTEST) 
    
        char timeBuffer[20];
        getTime(timeBuffer, sizeof(timeBuffer));
    
        const char* severityStr = severityToString(severity);
    
        printf("[%s] [%s] [%s] ", timeBuffer, func, severityStr);
    
        va_list args;
        va_start(args, msg);
        vprintf(msg, args);
        va_end(args);
        printf("\n");
    #endif
    //#]
}

inline void Logger::printToWindowsForms(const char* func, const Logger::Severity severity, const char* msg, ...) {
    //#[ operation printToWindowsForms(const char*,Severity,const char*)
    #if defined(_MSC_VER) && !defined(_MSC_GTEST) 
        
        // Call the managed function
        char messageBuffer[1024]; // Adjust size as needed
        char timeBuffer[20];
        const char* severityStr = severityToString(severity);
        getTime(timeBuffer, sizeof(timeBuffer));
        
        snprintf(messageBuffer, sizeof(messageBuffer), "[%s] [%s] [%s] ", timeBuffer, func, severityStr);
        
        // Start variable argument processing
        va_list args;
        va_start(args, msg);
        // Format the message and append it to the message buffer
        vsnprintf(messageBuffer + strlen(messageBuffer), sizeof(messageBuffer) - strlen(messageBuffer), msg, args);
        // End variable argument processing
        va_end(args);
        ManagedAddTrace(const_cast<char*>(messageBuffer));
    #endif
    //#]
}

inline void Logger::setSeverityLevel(const Logger::Severity severity, const bool level) noexcept {
    //#[ operation setSeverityLevel(Severity,bool)
    if (level) {
        m_severityBitField |= (1 << static_cast<uint8>(severity));  // Set bit
    } else {
        m_severityBitField &= ~(1 << static_cast<uint8>(severity)); // Clear bit
    }
    //#]
}

inline void Logger::setSeverityLevel(const uint8 levels) {
    //#[ operation setSeverityLevel(uint8)
    m_severityBitField = levels;
    //#]
}

inline void Logger::getTime(char* buffer, const uint8& size) {
    //#[ operation getTime(char*,uint8)
        auto now = std::chrono::system_clock::now();
    
        // Convert time point to time_t (system time)
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
        // Convert to local time
        std::tm* localTime = std::localtime(&now_c);
    
        std::strftime(buffer, size, "%Y-%m-%d %H:%M:%S", localTime);
    
    //#]
}

inline bool Logger::isSeverityPrintable(const Logger::Severity severity) noexcept {
    //#[ operation isSeverityPrintable(Severity)
     return static_cast<bool>((severity < Severity::MAX) && (m_severityBitField & ( 1 << static_cast<uint8>(severity))));
    
    //#]
}

inline const char* Logger::severityToString(const Logger::Severity& severity) {
    //#[ operation severityToString(Severity)
    switch (severity)
    {
    case Severity::INFO:
        return "INFO";
    case Severity::ERR:
        return "ERR";
    case Severity::DEBUG:
        return "DEBUG";
    case Severity::WARN:
        return "WARN";
    case Severity::CRITICAL:
        return "CRITICAL";
    case Severity::MAX:
        return "MAX";
    default:
        return "UNKNOWN";
    }
    //#]
}

#endif
/*********************************************************************
	File Path	: SDDComponent\DefaultConfig\system\Logger.h
*********************************************************************/
