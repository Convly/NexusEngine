/**
*	@file DLLoader.hpp
*	@author Marc-Antoine Leconte
*
*	This file must be include when using the DLLoader class on Windows
*/

#ifndef DL_LOADER_WIN_HPP_
# define DL_LOADER_WIN_HPP_

#include "Nexus/errors/DLLoaderException.hpp"
#include <unordered_map>
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

/**
*	@class	DLLoader
*
*	This class deserve to load a dynamic Library
*/

template <typename T, typename U>
class DLLoader
{
private:
	std::unordered_map<std::string, HMODULE>			_handlers;		/**< This param is uses to stock the handlers by file name.*/
	std::vector<std::string>							_libs;			/**< This param is uses to stock the lib's names.*/
	std::unordered_map<std::string, T*>					_instances;		/**< This param stock the instances of each librarys opened.*/
	std::string											_name;			/**< This param is the name of the DLLoader.*/
	bool												_debug;			/**< This param allow debug prints.*/
	std::string											_dylibext; /**< This param indicate the extension for dynamic libraries */	

public:
	/**
	*	Constructor.
	*	@param	libName	Set the name of the DLLoader.
	*	@param	debug	Allow or not the debug prints.
	*/
	DLLoader(const std::string& libName = "anonymous", int debug = false) :
		_name(libName),
		_debug(debug),
		_dylibext(".dll")
	{
		if (_debug)
			std::cerr << "_> Construction of DLLoader (" << this->_name << ")" << std::endl;
	}

	/**
	*	Destructor.
	*/
	virtual ~DLLoader()
	{
		this->destroyLibs();
	}

	/**
	*	@return	This method return the dynamic library extension used on this DLLoader
	*/
public:
	const std::string& getDylibExt()
	{
		return this->_dylibext;
	}

public:
	/**
	*	Add a dynamic library to the DLLoader.
	*	Load the library into memory.
	*	@param	path	Indicate the path of te library to load.
	*/
	//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
	std::string GetLastErrorAsString()
	{
		//Get the error message, if any.
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return std::string(); //No error message has been recorded

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);

		return message;
	}

	void									addLib(const std::string & path)
	{
		HMODULE								handler;

		if (std::find(this->_libs.begin(), this->_libs.end(), path) != this->_libs.end())
		{
			if (this->_debug)
				std::cerr << "_> \"" << path << "\" is already loaded in this context" << std::endl;
			return;
		}

		if (this->_debug)
			std::cerr << "_> Adding new lib in (" << this->_name << ") [" << path << "]" << std::endl;

		if ((handler = LoadLibrary(path.c_str())) == nullptr)
		{
			std::cout << GetLastErrorAsString() << std::endl;
			throw nx::DLLoaderException("Can't load " + path + ".");
		}
		else
		{
			this->_handlers[path] = handler;
			this->_instances[path] = nullptr;
			this->_libs.push_back(path);
		}
	}

	/**
	*	Permit to reset the instance of the library ist.
	*	@param	ist	The name of the instance to reset.
	*	@return Return an instance newly created of the ist library.
	*/
	T*									resetLib(const std::string & ist)
	{
		T*								nIst = nullptr;
		std::unordered_map<std::string, T*> ists = this->_instances;

		if (_debug)
			std::cerr << "_> " << ist << " is being reset..." << '\n';

		this->deleteInstance(ist);
		nIst = this->getInstance(ist);

		if (_debug)
			std::cerr << "<_ " << ((nIst == nullptr) ? "ERROR" : "SUCCESS") << '\n';

		return (nIst);
	}

	/**
	*	Display the content of the librarys stocked in memory.
	*/
	void									dump() const
	{
		int									paddingVar_name, currSize, idx;

		if (this->_debug)
		{
			paddingVar_name = idx = currSize = 0;

			std::cerr << "_> Dumping libraries for the current context:" << std::endl;
			std::cerr << "_> There is " << this->_libs.size() << " library in (" << this->_name << ")" << std::endl;
			for (auto it = this->_libs.begin(); it != this->_libs.end(); it++)
			{
				currSize = (*it).size();
				if (currSize > paddingVar_name)
					paddingVar_name = currSize;
			}
			for (int i = 0; i < paddingVar_name + 17; i++) std::cerr << "-";
			std::cerr << "|" << std::endl << "|  " << std::setw(10) << "ID" << " | " << std::setw(paddingVar_name) << " Path" << " |" << std::endl;
			for (int i = 0; i < paddingVar_name + 17; i++) std::cerr << "-";
			std::cerr << "|" << std::endl;
			for (auto it = this->_libs.begin(); it != this->_libs.end(); it++)
			{
				std::cerr << "|  " << std::setw(10) << idx << " | " << std::setw(paddingVar_name) << (*it) << " |" << std::endl;
				idx += 1;
			}
			for (int i = 0; i < paddingVar_name + 17; i++) std::cerr << "-";
			std::cerr << "|" << std::endl;
		}
		else
			std::cerr << "Please activate the verbose mode in order to dump context" << std::endl;
	}

	/**
	*	Delete the instance of the path passed in paramater.
	*	@param	path	The path of the instance to delete.
	*/
	void									deleteInstance(const std::string & path)
	{
		HMODULE								handler;
		T*									(*symbol)(T*);

		if (_debug)
			std::cerr << "_> About to delete instance of [" << path << "]" << std::endl;

		if (this->_handlers.find(path) == this->_handlers.end())
			return;
		else
			handler = this->_handlers.at(path);

		if (this->_instances[path] == nullptr)
		{
			if (_debug)
				std::cerr << "_> No instance of [" << path << "] found, skipping..." << std::endl;
			return;
		}

		if ((symbol = reinterpret_cast<T*(*)(T*)>(GetProcAddress(handler, "DObject"))) == nullptr)
			throw nx::DLLoaderException("Error when loading DObject from dll file " + path + ".");

		symbol(this->_instances.at(path));
		this->_instances[path] = nullptr;

		if (_debug)
			std::cerr << "_> instance of [" << path << "] successfully destroyed" << std::endl;
	}

	/**
	*	Delete the instance and the library stocked in memory at path.
	*	@param	path	The path of the library to erase in memory.
	*/
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
	}

	/**
	*	Destroy all the librarys and their instances stocked in memory.
	*/
	void									destroyLibs(void)
	{
		if (this->_debug)
			std::cerr << "_> Destruction of DLLoader (" << this->_name << ")" << std::endl;

		for (auto it = this->_libs.begin(); it != this->_libs.end(); it++)
		{
			this->deleteInstance((*it));

			if (this->_handlers.find((*it)) == this->_handlers.end())
				return;
			if (FreeLibrary(this->_handlers.at((*it))))
				std::cerr << "Error when using FreeLibrary." << std::endl;
		}

		if (this->_debug)
			std::cerr << "_> DLLoader (" << this->_name << ") successfully destroyed" << std::endl;
	}

	/**
	*	Get the names of the libs stocked in memory.
	*	@return Return a std::vector<std::string> containing all the names of the libs.
	*/
	std::vector<std::string>				getPaths(void) const
	{
		return (this->_libs);
	}

	/**
	*	Get the instances of the libs stocked in memory order by name.
	*	@return Return a std::unordered_map<std::string, T*> containing all the names and the instances of the libs.
	*/
	std::unordered_map<std::string, T>		getInstances(void) const
	{
		return (this->_instances);
	}

	/**
	*	Get the path of a lib from his instance.
	*	@return Return the name of the instance's lib.
	*/
	std::string								getPathByInstance(T* ist) const
	{
		std::string                         res = "";
		std::unordered_map<std::string, T> ists = this->_instances;

		for (auto it = ists.begin(); it != ists.end(); it++)
		{
			if (it->second == ist)
				res = it->first;
		}
		return (res);
	}

	/**
	*	Get the instance of a lib stored in memory fromo the parame path.
	*	@param	path	Design the path of the library to get instance of.
	*	@return An instance of the library design by the param path.
	*/
	T*										getInstance(const std::string & path)
	{
		HMODULE								handler;
		T*									(*symbol)(U*);

		if (this->_instances[path])
			return (this->_instances.at(path));

		handler = this->_handlers.at(path);

		if (this->_debug)
			std::cerr << "_> Creating new instance of [" << path << "] in (" << this->_name << ")..." << std::endl;

		if ((symbol = reinterpret_cast<T*(*)(U*)>(GetProcAddress(handler, "CObject"))) == nullptr)
		{
			this->_handlers.erase(path);
			std::cerr << "Error when loading CObject from dll file " << path.c_str() << std::endl;
			return (nullptr);
		}

		this->_instances[path] = symbol(&U::Instance());

		if (this->_debug)
			std::cerr << "_> Instance successfully created!" << std::endl;

		return (this->_instances.at(path));
	}

};

#endif
