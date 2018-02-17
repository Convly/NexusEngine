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
		private:
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
			Layer() : _entityInfos("") {}
			Layer(std::string const& _name) : _entityInfos(_name) {}
			Layer(std::string const& _name, bool const _active) : _entityInfos(_name, _active) {}
			~Layer() {}

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _entityInfos;
				ar & _buttons;
				ar & _checkboxes;
				ar & _comboBoxes;
				ar & _images;
				ar & _progressbars;
				ar & _sprites;
				ar & _texts;
				ar & _textInputs;
			}

			template<typename T>
			bool guiIsModified(T& guiElements){
				for (auto& guiElement : guiElements){
					if (guiElement.isModified()){
						return true;
					}
				}
				return false;
			}

			bool isModified(){
				if (_entityInfos.getIsModified() || guiIsModified(_buttons)
					|| guiIsModified(_checkboxes) || guiIsModified(_comboBoxes)
					|| guiIsModified(_images) || guiIsModified(_progressbars)
					|| guiIsModified(_sprites) || guiIsModified(_texts)
					|| guiIsModified(_textInputs))
					return true;
				return false;
			}

			template<typename T>
			void guiResetModified(T& guiElements){
				for (auto& guiElement : guiElements){
					guiElement.resetModified();
				}
			}

			void resetModified(){
				_entityInfos.setIsModified(false);
				guiResetModified(_buttons);
				guiResetModified(_checkboxes);
				guiResetModified(_comboBoxes);
				guiResetModified(_images);
				guiResetModified(_progressbars);
				guiResetModified(_sprites);
				guiResetModified(_texts);
				guiResetModified(_textInputs);
			}

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

			bool	removeButton(std::string const& buttonId)
			{
				bool found = false;
				std::remove_if(this->_buttons.begin(), this->_buttons.end(),
					[&](nx::env::gui::Button button)
				{
					if (button.getGuiElementInfos().getIdentifier() == buttonId)
						found = true;
					return (button.getGuiElementInfos().getIdentifier() == buttonId);
				});
				return (found);
			}

			bool	removeCheckbox(std::string const& checkboxId)
			{
				bool found = false;
				std::remove_if(this->_checkboxes.begin(), this->_checkboxes.end(),
					[&](nx::env::gui::Checkbox checkbox)
				{
					if (checkbox.getGuiElementInfos().getIdentifier() == checkboxId)
						found = true;
					return (checkbox.getGuiElementInfos().getIdentifier() == checkboxId);
				});
				return (found);
			}

			bool	removeComboBox(std::string const& comboBoxId)
			{
				bool found = false;
				std::remove_if(this->_comboBoxes.begin(), this->_comboBoxes.end(),
					[&](nx::env::gui::ComboBox comboBox)
				{
					if (comboBox.getGuiElementInfos().getIdentifier() == comboBoxId)
						found = true;
					return (comboBox.getGuiElementInfos().getIdentifier() == comboBoxId);
				});
				return (found);
			}

			bool	removeImage(std::string const& imageId)
			{
				bool found = false;
				std::remove_if(this->_images.begin(), this->_images.end(),
					[&](nx::env::gui::Image image)
				{
					if (image.getGuiElementInfos().getIdentifier() == imageId)
						found = true;
					return (image.getGuiElementInfos().getIdentifier() == imageId);
				});
				return (found);
			}

			bool	removeProgressBar(std::string const& progressBarId)
			{
				bool found = false;
				std::remove_if(this->_progressbars.begin(), this->_progressbars.end(),
					[&](nx::env::gui::ProgressBar progressBar)
				{
					if (progressBar.getGuiElementInfos().getIdentifier() == progressBarId)
						found = true;
					return (progressBar.getGuiElementInfos().getIdentifier() == progressBarId);
				});
				return (found);
			}

			bool	removeSprite(std::string const& spriteId)
			{
				bool found = false;
				std::remove_if(this->_sprites.begin(), this->_sprites.end(),
					[&](nx::env::gui::Sprite sprite)
				{
					if (sprite.getGuiElementInfos().getIdentifier() == spriteId)
						found = true;
					return (sprite.getGuiElementInfos().getIdentifier() == spriteId);
				});
				return (found);
			}

			bool	removeText(std::string const& textId)
			{
				bool found = false;
				std::remove_if(this->_texts.begin(), this->_texts.end(),
					[&](nx::env::gui::Text text)
				{
					if (text.getGuiElementInfos().getIdentifier() == textId)
						found = true;
					return (text.getGuiElementInfos().getIdentifier() == textId);
				});
				return (found);
			}

			bool	removeTextInput(std::string const& textInputId)
			{
				bool found = false;
				std::remove_if(this->_textInputs.begin(), this->_textInputs.end(),
					[&](nx::env::gui::TextInput textInput)
				{
					if (textInput.getGuiElementInfos().getIdentifier() == textInputId)
						found = true;
					return (textInput.getGuiElementInfos().getIdentifier() == textInputId);
				});
				return (found);
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

			gui::Button &						getButtonAt(int idx)
			{
				return (this->_buttons.at(idx));
			}

			std::vector<gui::Checkbox> &		getAllCheckboxes()
			{
				return (this->_checkboxes);
			}

			gui::Checkbox &						getCheckboxAt(int idx)
			{
				return (this->_checkboxes.at(idx));
			}

			std::vector<gui::ComboBox> &		getAllComboBoxes()
			{
				return (this->_comboBoxes);
			}

			gui::ComboBox &						getComboBoxAt(int idx)
			{
				return (this->_comboBoxes.at(idx));
			}

			std::vector<gui::Image> &			getAllImages()
			{
				return (this->_images);
			}

			gui::Image &						getImageAt(int idx)
			{
				return (this->_images.at(idx));
			}

			std::vector<gui::ProgressBar> &		getAllProgressBars()
			{
				return (this->_progressbars);
			}

			gui::ProgressBar &					getProgressBarAt(int idx)
			{
				return (this->_progressbars.at(idx));
			}

			std::vector<gui::Sprite> &			getAllSprites()
			{
				return (this->_sprites);
			}

			gui::Sprite &						getSpriteAt(int idx)
			{
				return (this->_sprites.at(idx));
			}

			std::vector<gui::Text> &			getAllTexts()
			{
				return (this->_texts);
			}

			gui::Text &							getTextAt(int idx)
			{
				return (this->_texts.at(idx));
			}

			std::vector<gui::TextInput> &		getAllTextInputs()
			{
				return (this->_textInputs);
			}

			gui::TextInput &						getTextInputAt(int idx)
			{
				return (this->_textInputs.at(idx));
			}
		};
	}
}

#endif /* NEXUS_ENGINE__LAYER_HPP_ */