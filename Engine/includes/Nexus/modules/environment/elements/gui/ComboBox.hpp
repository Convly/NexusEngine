#ifndef NEXUS_ENGINE__GUI_COMBOBOX_HPP_
#define NEXUS_ENGINE__GUI_COMBOBOX_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class ComboBox
			{
				GUIElementInfos		_elementInfos;
				GUIComboBoxInfos	_comboBoxInfos;

			public:
				template <typename Archive>
				void serialize(Archive& ar, unsigned int version)
				{
					ar & _elementInfos;
					ar & _comboBoxInfos;
				}

			public:
				ComboBox() {}
				ComboBox(GUIElementInfos const& elementInfos, GUIComboBoxInfos const& comboBoxInfos)
					: _elementInfos(elementInfos), _comboBoxInfos(comboBoxInfos) {}
				~ComboBox() {}

			public:
				bool isModified(){
					if (_elementInfos.getIsModified() || _comboBoxInfos.getIsModified()){
						return true;
					}
					return false;
				}

				void resetModified(){
					_elementInfos.setIsModified(false);
					_comboBoxInfos.setIsModified(false);
				}

				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIComboBoxInfos& getGuiComboBoxInfos() { return _comboBoxInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_COMBOBOX_HPP_ */