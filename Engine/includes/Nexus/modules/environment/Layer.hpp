#ifndef NEXUS_ENGINE__LAYER_HPP_
#define NEXUS_ENGINE__LAYER_HPP_

# include <vector>
# include "./elements/gui/Button.hpp"
# include "./elements/gui/Checkbox.hpp"
# include "./elements/gui/ComboBox.hpp"
# include "./elements/gui/Image.hpp"
# include "./elements/gui/ProgressBar.hpp"
# include "./elements/gui/Sprite.hpp"
# include "./elements/gui/Text.hpp"
# include "./elements/gui/TextInput.hpp"

namespace nx
{
	namespace env
	{
		class Layer
		{
			EntityInfos						_entityInfos;
			std::vector<gui::Button>		_buttons;
			std::vector<gui::Checkbox>		_checkboxes;
			std::vector<gui::ComboBox>		_comboBoxes;
			std::vector<gui::Image>			_images;
			std::vector<gui::ProgressBar>	_progressbars;
			std::vector<gui::Sprite>		_sprites;
			std::vector<gui::Text>			_texts;
			std::vector<gui::TextInput>		_textInputs;

		public:
			Layer(std::string const& _name) : _entityInfos(_name) {}
			Layer(std::string const& _name, bool const _active) : _entityInfos(_name, _active) {}
			~Layer() {}

			// Setters
			void	addButton(gui::Button const& button)
			{
				this->_buttons.push_back(button);
			}

			void	addCheckbox(gui::Checkbox const& checkbox)
			{
				this->_checkboxes.push_back(checkbox);
			}

			void	addComboBox(gui::ComboBox const& comboBox)
			{
				this->_comboBoxes.push_back(comboBox);
			}

			void	addImage(gui::Image const& image)
			{
				this->_images.push_back(image);
			}

			void	addProgressBar(gui::ProgressBar const& progressBar)
			{
				this->_progressbars.push_back(progressBar);
			}

			void	addSprite(gui::Sprite const& sprite)
			{
				this->_sprites.push_back(sprite);
			}

			void	addText(gui::Text const& text)
			{
				this->_texts.push_back(text);
			}

			void	addTextInput(gui::TextInput const& textInput)
			{
				this->_textInputs.push_back(textInput);
			}

			// Getters
			EntityInfos &						getEntityInfos()
			{
				return (this->_entityInfos);
			}

			std::vector<gui::Button> &			getAllButtons()
			{
				return (this->_buttons);
			}

			std::vector<gui::Checkbox> &		getAllCheckboxes()
			{
				return (this->_checkboxes);
			}

			std::vector<gui::ComboBox> &		getAllComboBoxes()
			{
				return (this->_comboBoxes);
			}

			std::vector<gui::Image> &			getAllImages()
			{
				return (this->_images);
			}

			std::vector<gui::ProgressBar> &		getAllProgressBars()
			{
				return (this->_progressbars);
			}

			std::vector<gui::Sprite> &			getAllSprites()
			{
				return (this->_sprites);
			}

			std::vector<gui::Text> &			getAllTexts()
			{
				return (this->_texts);
			}

			std::vector<gui::TextInput> &		getAllTextInputs()
			{
				return (this->_textInputs);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__LAYER_HPP_ */