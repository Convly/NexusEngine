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
				bool isModified(){
					if (_elementInfos.getIsModified() || _buttonInfos.getIsModified()){
						return true;
					}
					return false;
				}

				void resetModified(){
					_elementInfos.setIsModified(false);
					_buttonInfos.setIsModified(false);
				}

				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIButtonInfos& getGuiButtonInfos() { return _buttonInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_BUTTON_HPP_ */