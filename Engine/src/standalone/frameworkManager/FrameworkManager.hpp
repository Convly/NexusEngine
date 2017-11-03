/**
*	@file FrameworkManager.hpp
*	@author Marc-Antoine Leconte
*
*	This file contain the class FrameworkManager.
*/

#ifndef FRAMEWORK_MANAGER_HPP_
# define FRAMEWORK_MANAGER_HPP_
#include "FrameworkException.hpp"
#include "FrameworkTpl.hpp"
#include "DLLoader.hpp"
#include "Crawler.hpp"

/**
*	These defines permit to find the right extension of dynamic library according to the current OS.
*/
#if defined(__GNUC__) || defined(__GNUG__)
static const std::string DYNAMIC_LIBRARY_EXTENSION = ".so";
#elif defined(_MSC_VER)
static const std::string DYNAMIC_LIBRARY_EXTENSION = ".dll";
#endif

/**
*	@class FrameworkManager
*
*	This class permitt to load a Framework int the engine. It will load the framework according to the name given in the constructor and will search for it in the ./framework directory.
*	@see FrameworkManager()
*/
class FrameworkManager
{
private:
	DLLoader<FrameworkTpl>			_loader;		/**< Contain the DLLoader.*/
	nx::Crawler						_crawler;		/**< Contain a crawler @see nx::Crawler.*/
	std::string						_frameworkName;	/**< Contain the name of the Framework to load.*/
	std::shared_ptr<FrameworkTpl>	_framework;		/**< Contain an instance of the framework loaded.*/

public:
	/**
	*	Constructor of the FrameworkManager class.
	*	This function init a new crawler, a new DLLoader and
	*	@param	frameworkName	The name of the framework to load.
	*	@param	debug			Allow or not debug prints.
	*/
	explicit						FrameworkManager(const std::string & frameworkName, bool debug = false);

	/**
	*	Destructor.
	*/
	virtual							~FrameworkManager(void);

private:
	/**
	*	Function checking if the framework library is present, at the right format and the right place. Called in the constructor only.
	*/
	void							checkFile(void);

	/**
	*	Function allowing to load the framework library. Called in constructor only.
	*/
	void							loadLib(void);

public:
	/**
	*	Function of print. Permit to display the library loaded in the FrameworkManager.
	*/
	void							dump(void) const;

	/**
	*	Get an instance of the current framework.
	*	@return Return an instance of the framework.
	*/
	std::shared_ptr<FrameworkTpl>	getFramework(void) const;
};

#endif /*FRAMEWORK_MANAGER_HPP_*/
