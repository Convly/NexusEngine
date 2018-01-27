#ifndef NEXUS_ENGINE__GUI_BUTTON_HPP_
#define NEXUS_ENGINE__GUI_BUTTON_HPP_

#include "Nexus/modules/environment/Environment.hpp"

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
				Button() {}
				Button(GUIElementInfos const& elementInfos, GUIButtonInfos const& buttonInfos)
					: _elementInfos(elementInfos), _buttonInfos(buttonInfos) {}
				~Button() {}

			public:
				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIButtonInfos& getGuiButtonInfos() { return _buttonInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_BUTTON_HPP_ */