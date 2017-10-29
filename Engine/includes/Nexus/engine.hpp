#ifndef NEXUS_ENGINE__ENGINE_CORE_HPP_
#define NEXUS_ENGINE__ENGINE_CORE_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <functional>

#include "Nexus/gui.hpp"
#include "RunWithoutSetupException.hpp"

namespace nx {
  class Engine {
	private:
	  bool											_run;
	  bool											_debug;
	  std::vector<std::shared_ptr<nx::SystemTpl>>	_systems;

  public:
	  Engine(const bool debug = false);
    virtual ~Engine ();

  public:
    bool  ping(void) const;

  private:
	bool checkEngineIntegrity(void) const;

	public:
		void emit(const nx::Event&);
		void emit(const std::string&, const std::string&);
	  void setup(void);
	  void stop(void);
	  int run(const std::function<void(void)>&);

	public:
	  bool debug(void) const;
	  void setDebugFlag(const bool);
	  const std::vector<std::shared_ptr<nx::SystemTpl>>& getSystems(void) const;
  };
} /* nx */

#endif
