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
				ComboBox() {}
				ComboBox(GUIElementInfos const& elementInfos, GUIComboBoxInfos const& comboBoxInfos)
					: _elementInfos(elementInfos), _comboBoxInfos(comboBoxInfos) {}
				~ComboBox() {}

			public:
				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIComboBoxInfos& getGuiComboBoxInfos() { return _comboBoxInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_COMBOBOX_HPP_ */