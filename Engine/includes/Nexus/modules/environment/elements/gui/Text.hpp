#ifndef NEXUS_ENGINE__GUI_TEXT_HPP_
#define NEXUS_ENGINE__GUI_TEXT_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class Text
			{
				GUIElementInfos		_elementInfos;
				GUITextInfos		_textInfos;

			public:
				Text() {}
				Text(GUIElementInfos const& elementInfos, GUITextInfos const& textInfos)
					: _elementInfos(elementInfos), _textInfos(textInfos) {}
				~Text() {}

			public:
				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUITextInfos& getGuiTextInfos() { return _textInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_TEXT_HPP_ */