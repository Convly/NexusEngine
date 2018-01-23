#ifndef NEXUS_ENGINE__GUI_TEXTINPUT_HPP_
#define NEXUS_ENGINE__GUI_TEXTINPUT_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class TextInput
			{
				GUIElementInfos		_elementInfos;
				GUITextInputInfos	_textInputInfos;

			public:
				TextInput(GUIElementInfos const& elementInfos, GUITextInputInfos const& textInputInfos)
					: _elementInfos(elementInfos), _textInputInfos(textInputInfos) {}
				~TextInput() {}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_TEXTINPUT_HPP_ */