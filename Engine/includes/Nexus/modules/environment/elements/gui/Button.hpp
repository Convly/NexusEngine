#ifndef NEXUS_ENGINE__GUI_BUTTON_HPP_
#define NEXUS_ENGINE__GUI_BUTTON_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class Button
			{
				GUIElementInfos		_elementInfos;
				GUIButtonInfos		_buttonInfos;

			public:
				Button(GUIElementInfos const& elementInfos, GUIButtonInfos const& buttonInfos)
					: _elementInfos(elementInfos), _buttonInfos(buttonInfos) {}
				~Button() {}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_BUTTON_HPP_ */