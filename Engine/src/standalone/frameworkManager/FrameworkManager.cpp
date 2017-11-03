/**
*	@file FrameworkManager.cpp
*	@author Marc-Antoine Leconte
*
*	This file contain the class FrameworkManager's functions.
*/

#include "FrameworkManager.hpp"

FrameworkManager::FrameworkManager(const std::string & frameworkName, bool debug) :
	_loader(std::string(frameworkName), debug),
	_crawler(std::string("./frameworks/"), debug),
	_frameworkName(frameworkName),
	_framework(nullptr)
{
	this->checkFile();
	this->loadLib();
}

FrameworkManager::~FrameworkManager(void)
{
}

void							FrameworkManager::checkFile(void)
{
	std::string					tmp;
	size_t						nameSize;

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

void							FrameworkManager::loadLib(void)
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

void							FrameworkManager::dump(void) const
{
	this->_loader.dump();
}

std::shared_ptr<FrameworkTpl>	FrameworkManager::getFramework(void) const
{
	return (this->_framework);
}