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
				template <typename Archive>
				void serialize(Archive& ar, unsigned int version)
				{
					ar & _elementInfos;
					ar & _textInputInfos;
				}

			public:
				TextInput() {}
				TextInput(GUIElementInfos const& elementInfos, GUITextInputInfos const& textInputInfos)
					: _elementInfos(elementInfos), _textInputInfos(textInputInfos) {}
				~TextInput() {}

			public:
				bool isModified(){
					if (_elementInfos.getIsModified() || _textInputInfos.getIsModified()){
						return true;
					}
					return false;
				}

				void resetModified(){
					_elementInfos.setIsModified(false);
					_textInputInfos.setIsModified(false);
				}

				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUITextInputInfos& getGuiTextInputInfos() { return _textInputInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_TEXTINPUT_HPP_ */