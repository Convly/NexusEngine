//
// Made by Marco
//

#ifndef DL_LOADER_WIN_HPP_
# define DL_LOADER_WIN_HPP_

#ifdef _WIN32
#include "DLLoaderException.hpp"
#include <unordered_map>
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

template <typename T>
class DLLoader
{
private:
	std::unordered_map<std::string, HMODULE>	_handlers;
	std::vector<std::string>					_libs;
	std::unordered_map<std::string, T*>			_instances;
	std::string									_name;
	bool										_noise;

public:
	DLLoader(const std::string& libName = "anonymous", int noise = false) :
		_name(libName),
		_noise(noise)
	{
		if (_noise)
			std::cerr << "_> Construction of DLLoader (" << this->_name << ")" << std::endl;
	}

	virtual ~DLLoader()
	{
		this->destroyLibs();
	}

public:
	void									addLib(const std::string & path)
	{
		HMODULE								handler;

		if (std::find(this->_libs.begin(), this->_libs.end(), path) != this->_libs.end())
		{
			if (this->_noise)
				std::cerr << "_> \"" << path << "\" is already loaded in this context" << std::endl;
			return;
		}

		if (this->_noise)
			std::cerr << "_> Adding new lib in (" << this->_name << ") [" << path << "]" << std::endl;

		if ((handler = LoadLibrary(path.c_str())) == nullptr)
			throw nx::DLLoaderException("Can't load " + path + ".");
		else
		{
			this->_handlers[path] = handler;
			this->_instances[path] = nullptr;
			this->_libs.push_back(path);
		}
	}

	T*										resetLib(const std::string & ist)
	{
		std::unordered_map<std::string, T*> ists = this->_instances;
		T*                                  nIst = nullptr;

		if (_noise)
			std::cerr << "_> " << ist << " is being reset..." << '\n';

		this->deleteInstance(ist);
		nIst = this->getInstance(ist);

		if (_noise)
			std::cerr << "<_ " << ((nIst == nullptr) ? "ERROR" : "SUCCESS") << '\n';

		return nIst;
	}

	void									dump() const
	{
		int									paddingVar_name, currSize, idx;

		if (this->_noise)
		{
			paddingVar_name = idx = currSize = 0;

			std::cerr << "_> Dumping libraries for the current context:" << std::endl;
			std::cerr << "_> There is " << this->_libs.size() << " library in (" << this->_name << ")" << std::endl;
			// Get Padding
			for (auto it = this->_libs.begin(); it != this->_libs.end(); it++)
			{
				currSize = (*it).size();
				if (currSize > paddingVar_name)
					paddingVar_name = currSize;
			}
			// Display table header
			for (int i = 0; i < paddingVar_name + 17; i++) std::cerr << "-";
			std::cerr << "|" << std::endl << "|  " << std::setw(10) << "ID" << " | " << std::setw(paddingVar_name) << " Path" << " |" << std::endl;
			// Display (header / content) separator
			for (int i = 0; i < paddingVar_name + 17; i++) std::cerr << "-";
			std::cerr << "|" << std::endl;
			// Display content
			for (auto it = this->_libs.begin(); it != this->_libs.end(); it++)
			{
				std::cerr << "|  " << std::setw(10) << idx << " | " << std::setw(paddingVar_name) << (*it) << " |" << std::endl;
				idx += 1;
			}
			// Display footer
			for (int i = 0; i < paddingVar_name + 17; i++) std::cerr << "-";
			std::cerr << "|" << std::endl;
		}
		else
			std::cerr << "Please activate the verbose mode in order to dump context" << std::endl;
	}

	void									deleteInstance(const std::string & path)
	{
		HMODULE								handler;
		T*									(*symbol)(T*);

		if (_noise)
			std::cerr << "_> About to delete instance of [" << path << "]" << std::endl;

		// If there is no handler for this path, then stop the current action
		if (this->_handlers.find(path) == this->_handlers.end())
			return;
		else
			handler = this->_handlers.at(path);

		// If there is no instance for this path, then stop the current action
		if (this->_instances[path] == nullptr)
		{
			if (_noise)
				std::cerr << "_> No instance of [" << path << "] found, skipping..." << std::endl;
			return;
		}

		if ((symbol = reinterpret_cast<T*(*)(T*)>(GetProcAddress(handler, "DObject"))) == nullptr)
			throw nx::DLLoaderException("Error when loading DObject from dll file " + path + ".");

		symbol(this->_instances.at(path));
		this->_instances[path] = nullptr;

		if (_noise)
			std::cerr << "_> instance of [" << path << "] successfully destroyed" << std::endl;
	}

	void									destroyLib(const std::string & path)
	{
		this->deleteInstance(path);
		auto it = std::find(this->_libs.begin(), this->_libs.end(), path);

		if (it != this->_libs.end())
			this->_libs.erase(it);

		if (this->_handlers.find(path) == this->_handlers.end())
			return;
		if (FreeLibrary(this->_handlers.at(path)))
			throw nx::DLLoaderException("Error when freeing library " + path + ".");

			std::cerr <<  << std::endl;
	}

	void									destroyLibs(void)
	{
		if (this->_noise)
			std::cerr << "_> Destruction of DLLoader (" << this->_name << ")" << std::endl;

		for (auto it = this->_libs.begin(); it != this->_libs.end(); it++)
		{
			this->deleteInstance((*it));

			if (this->_handlers.find((*it)) == this->_handlers.end())
				return;
			if (FreeLibrary(this->_handlers.at((*it))))
				std::cerr << "Error when using FreeLibrary." << std::endl;
		}

		if (this->_noise)
			std::cerr << "_> DLLoader (" << this->_name << ") successfully destroyed" << std::endl;
	}

	std::vector<std::string>				getPaths() const
	{
		return (this->_libs);
	}

	std::unordered_map<std::string, T*>		getInstances() const
	{
		return (this->_instances);
	}

	std::string								getPathByInstance(T* ist) const
	{
		std::unordered_map<std::string, T*> ists = this->_instances;
		std::string                         res = "";

		for (auto it = ists.begin(); it != ists.end(); it++)
		{
			if (it->second == ist)
				res = it->first;
		}
		return (res);
	}

	T*										getInstance(const std::string & path)
	{
		HMODULE								handler;
		T*									(*symbol)();

		// If there is already an instance of $path, then return it
		if (this->_instances[path])
			return (this->_instances.at(path));

		// Else, create one
		handler = this->_handlers.at(path);

		if (this->_noise)
			std::cerr << "_> Creating new instance of [" << path << "] in (" << this->_name << ")..." << std::endl;

		if ((symbol = reinterpret_cast<T*(*)()>(GetProcAddress(handler, "CObject"))) == nullptr)
		{
			this->_handlers.erase(path);
			std::cerr << "Error when loading CObject from dll file " << path.c_str() << std::endl;
			return (nullptr);
		}

		this->_instances[path] = symbol();

		if (this->_noise)
			std::cerr << "_> Instance successfully created!" << std::endl;

		// And return it
		return (this->_instances.at(path));
	}

};

#endif
#endif