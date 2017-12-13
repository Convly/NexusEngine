/**
*	@file FrameworkManager.hpp
*	@author Marc-Antoine Leconte
*
*	This file contain the class FrameworkManager.
*/

#ifndef FRAMEWORK_MANAGER_HPP_
# define FRAMEWORK_MANAGER_HPP_

#include "Nexus/log.hpp"
#include "Nexus/errors/FrameworkException.hpp"
#include "Nexus/crawler/Crawler.hpp"
#if defined(__GNUC__) || defined(__GNUG__)
#include "Nexus/dlLoader/Linux/DLLoader.hpp"
#elif defined(_MSC_VER)
#include "Nexus/dlLoader/Windows/DLLoader.hpp"
#endif

/**
*	@class FrameworkManager
*
*	This class permitt to load a Framework int the engine. It will load the framework according to the name given in the constructor and will search for it in the ./framework directory.
*	@see FrameworkManager()
*/
namespace nx {
	template <class T>
	class FrameworkManager
	{
	private:
		DLLoader<T, nx::Engine>			_loader;		/**< Contain the DLLoader.*/
		std::string						_frameworksRoot; /**< Contain the path to the frameworks directory. */
		nx::Crawler						_crawler;		/**< Contain a crawler @see nx::Crawler.*/
		std::string						_frameworkName;	/**< Contain the name of the Framework to load.*/
		T*								_framework;		/**< Contain an instance of the framework loaded.*/
		std::string						_dylibext; /**< Indicate the extension for the dynamic libraries */
	
	public:
		/**
		*	Constructor of the FrameworkManager class.
		*	This function init a new crawler, a new DLLoader and
		*	@param	frameworkName	The name of the framework to load.
		*	@param	debug			Allow or not debug prints.
		*/
		FrameworkManager(const std::string & frameworkName, bool debug = false)
		:
			_loader(std::string(frameworkName), debug),
			_frameworksRoot("./frameworks/" + frameworkName + "/"),
			_crawler(".", debug),
			_frameworkName(frameworkName),
			_framework(nullptr)
		{
			try
			{
				this->_crawler.setPath(this->_frameworksRoot);

				try
				{
					this->checkFile();
					this->loadLib();
				} catch (const nx::FrameworkException& e)
				{
					nx::Log::error(e.what(), "FRAMEWORK_INIT_ERROR", 2);
				}
			} catch (const nx::CrawlerInvalidPath& e)
			{
				nx::Log::error(e.what(), "CRAWLER_PATH", 3);
			}
		}
		/**
		*	Destructor.
		*/
		virtual							~FrameworkManager(void)
		{
		}
	
	private:
		/**
		*	Function checking if the framework library is present, at the right format and the right place. Called in the constructor only.
		*/
		void							checkFile(void)
		{
			std::string					tmp;
			size_t						nameSize;

			auto pathList = this->_crawler.getEntriesListByType(nx::Crawler::REGULAR);

			if (pathList.size() <= 0)
				throw nx::FrameworkException("Can't find dynamic librarys in " + this->_frameworksRoot);

			for (auto it : pathList)
			{
				tmp = it.string();
				nameSize = this->_loader.getDylibExt().size() + this->_frameworkName.size();
				if (tmp.size() >= nameSize && tmp.substr(tmp.size() - nameSize) == this->getFrameworkFullName())
					return;
			}
			throw nx::FrameworkException("Can't find " + this->_frameworkName + this->_loader.getDylibExt() + " in " + this->_frameworksRoot);
		}
	
		/**
		*	Function allowing to load the framework library. Called in constructor only.
		*/
		void							loadLib(void)
		{
			try
			{
				this->_loader.addLib(this->getFrameworkPath());
			}
			catch (const nx::DLLoaderException &err)
			{
				throw nx::FrameworkException(err.what());
			}
			if ((this->_framework = this->_loader.getInstance(this->getFrameworkPath())) == nullptr)
				throw nx::FrameworkException("Can't create an instance for " + this->_frameworkName + ".");
		}
	
	public:
		/**
		*	Function of print. Permit to display the library loaded in the FrameworkManager.
		*/
		void							dump(void) const
		{
			this->_loader.dump();
		}
	
		/**
		*	Get an instance of the current framework.
		*	@return Return an instance of the framework.
		*/
		T*						getFramework(void) const
		{
			return (this->_framework);
		}

		/**
		*	Get the full path to the framework
		*	@return Return a relative path to the wanted framework
		*/
		const std::string getFrameworkPath()
		{
			return this->_frameworksRoot + this->_frameworkName + this->_loader.getDylibExt();
		}

		/**
		*	Get the full name of the framework
		*	@return Return the full name (with the extension) for the wanted framework
		*/
		const std::string getFrameworkFullName()
		{
			return this->_frameworkName + this->_loader.getDylibExt();
		}
	};
}

#endif /*FRAMEWORK_MANAGER_HPP_*/
