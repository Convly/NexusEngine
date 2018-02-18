#ifndef NEXUS_ENGINE__ENGINE_CORE_HPP_
#define NEXUS_ENGINE__ENGINE_CORE_HPP_

# define BOOST_ALL_DYN_LINK
//#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1700)
# define BOOST_ASIO_DISABLE_BUFFER_DEBUGGING
//#endif

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

#include "Nexus/standalone/external/any.hpp"

#include "Nexus/modules/maths/maths.hpp"
#include "Nexus/modules/physics/physics.hpp"
#include "Nexus/modules/xml/Parser.hpp"
#include "Nexus/modules/environment/Environment.hpp"

#include "Nexus/systems/SystemTpl.hpp"

#include "Nexus/standalone/GameInfosParser/GameInfosParser.hpp"
#include "Nexus/standalone/thread/ScopedLock.hpp"

#include "Nexus/errors/RunWithoutSetupException.hpp"
#include "Nexus/errors/SystemNotFoundException.hpp"

#include "Nexus/rendering.hpp"
#include "Nexus/script.hpp"
#ifndef NEXUS_ENGINE_NO_BOOST
	#include "Nexus/networkclient.hpp"
	#include "Nexus/networkserver.hpp"
#endif

namespace nx {
  class Engine {
  private:
		static nx::Engine						_instance;
  public:
		static nx::Engine& 						Instance();

  private:
		bool											_run;
		bool											_debug;
		std::vector<std::shared_ptr<nx::SystemTpl>>		_systems;
		bool 											_serverOnly;
		nx::env::Environment 							_env;
		std::shared_ptr<nx::GameInfosParser>			_gameInfosParser;

	private:
		Engine(const bool debug = false);
		virtual ~Engine ();

  public:
		bool  ping(void) const;

  private:
		bool checkEngineIntegrity(void) const;

  public:
	  void emit(const nx::EVENT type, const external::any& data)
	  {
		  this->emit(nx::Event(type, data));
	  }

	  void emit(const nx::Event& event)
	  {
		  nx::Log::inform("New event catched in the Engine: {" + std::to_string(event.type) + "}");
		  std::for_each(
			  this->_systems.begin(),
			  this->_systems.end(),
			  [&](const auto system) {
			  	system->emitter(event);
		  	}
		  );
	  }

		template<typename T>
		static T* cast(const std::shared_ptr<nx::SystemTpl>& src)
		{
			auto ptr = src.get();
			if (!ptr) return nullptr;
			return dynamic_cast<T*>(ptr);
		}

  public:
		void startup(bool serverOnly = false);
		void setup(const std::string& confPath, bool serverOnly);
		void stop(void);
		int run(const std::function<void(void)>&);
		void coreLoop(const std::function<void(void)>& userCallback);
		void loadResources();

  public:
		void	fixUpdateScript(const std::string& fctName);
		

  private:
		void _fixedUpdate();
		void _update();
		void _lateUpdate();
		void _render();

  public:
		bool isSetup(void) const;
		const bool isServer(void) const;
		bool debug(void) const;
		void setDebugFlag(const bool);
		const std::vector<std::shared_ptr<nx::SystemTpl>>& getSystems(void) const;
		const std::shared_ptr<nx::SystemTpl>& getSystemByName(const std::string&) const;
		const nx::env::Environment& getEnv() const { return this->_env; }
		nx::env::Environment& getEnv() { return this->_env; }
		const std::shared_ptr<nx::GameInfosParser>& getGameInfosParser() const {return this->_gameInfosParser;}
		std::shared_ptr<nx::GameInfosParser>& getGameInfosParser() {return this->_gameInfosParser;}
  };
} /* nx */

#endif
