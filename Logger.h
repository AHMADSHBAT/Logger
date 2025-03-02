#pragma once

#include <chrono>
#include <cstdarg>
#include <cstdint>
#include <Windows.h>
#include <iostream>


#ifdef _DEBUG
#define LOG(severity, msg, ...) CLogger::print(__FUNCTION__, severity, msg, ##__VA_ARGS__)
#else
#define LOG(severity, msg, ...)
#endif

enum ESeverity
{
	INFO = 0,
	ERR = 1,
	WARN = 2,
	DEBUG = 3,
	CRITICAL = 4,
	MAX = 5
};

/* class-like namespace */
namespace CLogger {
	inline void print(const char* func, const ESeverity severity, const char* msg, ...);
	inline void printToConsole(const char* func, const ESeverity severity, const char* msg, va_list args);
	inline void setSeverityLevel(const ESeverity severity, const bool level) noexcept;
	inline void setSeverityLevel(const uint8_t levels);
	inline bool isSeverityPrintable(const ESeverity& severity) noexcept;
	inline const char* severityToString(const ESeverity& severity);


	/* All logs are active by default */
	static uint8_t m_severityBitField = 0xFF;

	inline void print(const char* func, const ESeverity severity, const char* msg, ...) {
		if (CLogger::isSeverityPrintable(severity) == FALSE)
		{
			return;
		}

		va_list args;
		va_start(args, msg);

		CLogger::printToConsole(func, severity, msg, args);
		//printToFile(func, severity, msg, args);
		va_end(args); // Clean up the variable argument list

	}

	inline void printToConsole(const char* func, const ESeverity severity, const char* msg, va_list args) {

		char timeBuffer[20] = "NNNNNNN";
		//getTime(timeBuffer, sizeof(timeBuffer));

		const char* severityStr = severityToString(severity);

		printf("[%s] [%s] [%s] ", timeBuffer, func, severityStr);

		vprintf(msg, args);
		printf("\n");
	}


	inline void setSeverityLevel(const ESeverity severity, const bool level) noexcept {
		if (level) {
			m_severityBitField |= (1 << static_cast<uint8_t>(severity));  // Set bit
		}
		else {
			m_severityBitField &= ~(1 << static_cast<uint8_t>(severity)); // Clear bit
		}
	}

	inline void setSeverityLevel(const uint8_t levels) {
		m_severityBitField = levels;
	}

	inline void getTime(char* buffer, const uint8_t& size) {
		auto now = std::chrono::system_clock::now();
	
		// Convert time point to time_t (system time)
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	
		// Convert to local time
		std::tm* localTime = std::localtime(&now_c);
	
		std::strftime(buffer, size, "%Y-%m-%d %H:%M:%S", localTime);
	
	}

	inline bool isSeverityPrintable(const ESeverity& severity) noexcept {
		return static_cast<bool>((severity < ESeverity::MAX) && (m_severityBitField & (1 << static_cast<uint8_t>(severity))));
	}

	inline const char* severityToString(const ESeverity& severity) {
		switch (severity)
		{
		case ESeverity::INFO:
			return "INFO";
		case ESeverity::ERR:
			return "ERR";
		case ESeverity::DEBUG:
			return "DEBUG";
		case ESeverity::WARN:
			return "WARN";
		case ESeverity::CRITICAL:
			return "CRITICAL";
		case ESeverity::MAX:
			return "MAX";
		default:
			return "UNKNOWN";
		}
	}
};
