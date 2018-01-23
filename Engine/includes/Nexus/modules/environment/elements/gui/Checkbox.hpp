#ifndef NEXUS_ENGINE__GUI_CHECKBOX_HPP_
#define NEXUS_ENGINE__GUI_CHECKBOX_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class Checkbox
			{
				GUIElementInfos		_elementInfos;
				GUICheckboxInfos	_checkboxInfos;

			public:
				Checkbox(GUIElementInfos const& elementInfos, GUICheckboxInfos const& checkboxInfos)
					: _elementInfos(elementInfos), _checkboxInfos(checkboxInfos) {}
				~Checkbox() {}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_CHECKBOX_HPP_ */