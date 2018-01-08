#ifndef NEXUS_ENGINE__ERROR_LAYER_NOT_FOUND
#define NEXUS_ENGINE__ERROR_LAYER_NOT_FOUND

#include <exception>
#include <string>

namespace nx {
	class LayerNotFoundException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		LayerNotFoundException(std::string const& layerName) : _msg("The layer '" + layerName + "' wasn't found.") {}

		virtual ~LayerNotFoundException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_LAYER_NOT_FOUND