#ifndef NEXUS_ENGINE__SYSTEM_TPL_HPP_
# define NEXUS_ENGINE__SYSTEM_TPL_HPP_

#include <string>

namespace nx {
	class SystemTpl
	{
	public:
		SystemTpl(const std::string& name) : _name(name) {};
		virtual ~SystemTpl() {};

	public:
		virtual void				update(void) = 0;
		virtual void				init(void) = 0;
		virtual bool				checkIntegrity(void) const = 0;
		virtual const std::string&	getName(void) const = 0;

	protected:
		const std::string			_name;
	};
}

#endif // NEXUS_ENGINE__SYSTEM_TPL_HPP_
