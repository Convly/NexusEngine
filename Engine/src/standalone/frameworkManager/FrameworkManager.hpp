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
#include "DLLoader_Win.hpp"
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
	DLLoader<FrameworkTpl>	_loader;		/**< Contain the DLLoader. */
	nx::Crawler				_crawler;		/**< Contain a crawler @see nx::Crawler.*/
	std::string				_frameworkName;	/**< Contain the name of the Framework to load.*/
	FrameworkTpl			*_framework;	/**< Contain an instance of the framework loaded.*/

public:
	/**
	*	Constructor of the FrameworkManager class.
	*	This function init a new crawler, a new DLLoader and
	*	@param	frameworkName	The name of the framework to load.
	*	@param	debug			Allow or not debug prints.
	*/
	explicit FrameworkManager(const std::string & frameworkName, bool debug = false) :
		_loader(std::string(frameworkName), debug),
		_crawler(std::string("./frameworks/"), debug),
		_frameworkName(frameworkName),
		_framework(nullptr)
	{
		this->checkFile();
		this->loadLib();
	}

	/**
	*	Destructor.
	*/
	virtual ~FrameworkManager(void)
	{
	}

private:
	/**
	*	Function checking if the framework library is present, at the right format and the right place. Called in the constructor only.
	*/
	void							checkFile(void)
	{
		std::string					tmp;
		int							nameSize;

		this->_crawler.update();
		auto pathList = this->_crawler.getEntriesListByType(nx::Crawler::REGULAR);

		if (pathList.size() <= 0)
			throw nx::FrameworkException("Can't find dynamic librarys in ./framework");

		for (auto it : pathList)
		{
			tmp = it.string();
			nameSize = DYNAMIC_LIBRARY_EXTENSION.size() + this->_frameworkName.size();
			if (tmp.size() >= nameSize && tmp.substr(tmp.size() - nameSize) == this->_frameworkName + DYNAMIC_LIBRARY_EXTENSION)
				return;
		}
		throw nx::FrameworkException("Can't find " + this->_frameworkName + DYNAMIC_LIBRARY_EXTENSION + " in ./framework");
	}

	/**
	*	Function allowing to load the framework library. Called in constructor only.
	*/
	void			loadLib(void)
	{
		try
		{
			this->_loader.addLib(std::string(this->_frameworkName + DYNAMIC_LIBRARY_EXTENSION));
		}
		catch (const nx::DLLoaderException &err)
		{
			throw nx::FrameworkException(err.what());
		}
		if ((this->_framework = this->_loader.getInstance(std::string(this->_frameworkName + DYNAMIC_LIBRARY_EXTENSION))) == nullptr)
			throw nx::FrameworkException("Can't create an instance from the framework " + this->_frameworkName + ".");
	}

public:
	/**
	*	Function of print. Permit to display the library loaded in the FrameworkManager.
	*/
	void			dump(void) const
	{
		this->_loader.dump();
	}

	/**
	*	Get an instance of the current framework.
	*	@return Return an instance of the framework.
	*/
	FrameworkTpl	*getFramework(void) const
	{
		return (this->_framework);
	}
};

#endif /*FRAMEWORK_MANAGER_HPP_*/
