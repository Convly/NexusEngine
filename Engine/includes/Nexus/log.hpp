#ifndef NEXUS_ENGINE__LOG_MODULE_HPP_
#define NEXUS_ENGINE__LOG_MODULE_HPP_

#include <string>
#include <iostream>

namespace nx {
	class Log {
	public:
		Log ();
		virtual ~Log ();

		static void print(const std::string& data, bool endl = true)
		{
			std::cout << data;
			if (endl) std::cout << std::endl;
		}

		template <class T>
		static void print(const T& data, bool endl = true)
		{
			std::cout << data;
			if (endl) std::cout << std::endl;
		}

		template <class T>
		static void warning(const T& data, const std::string& warningType, bool endl = true)
		{
			std::cout << "[WARNING] - " << warningType << ": " << data;
			if (endl) std::cout << std::endl;
		}

		template <class T>
		static void error(const T& data, const std::string& errorType, const std::int32_t errorCode, bool endl = true)
		{
			std::cout << "[ERROR " << errorCode << "] - " << errorType << ": " << data;
			if (endl) std::cout << std::endl;
		}

		template <class T>
		static void inform(const T& data, bool endl = true)
		{
			std::cout << "[INFO]: " << data;
			if (endl) std::cout << std::endl;
		}

		template <class T>
		static void debug(const T& data, bool endl = true)
		{
			std::cout << "[DEBUG] " << ": " << data;
			if (endl) std::cout << std::endl;
		}
	};
}

#endif
