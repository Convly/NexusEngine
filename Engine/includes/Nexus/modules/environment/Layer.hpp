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

			// Getters
			EntityInfos &						getEntityInfos()
			{
				return (this->_entityInfos);
			}

			std::vector<gui::Button> &			getAllButtons()
			{
				return (this->_buttons);
			}

			unsigned long						getButtonsSize()
			{
				return _buttons.size();
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

			unsigned long						getCheckBoxesSize()
			{
				return _checkboxes.size();
			}

			std::vector<gui::ComboBox> &		getAllComboBoxes()
			{
				return (this->_comboBoxes);
			}

			gui::ComboBox &						getComboBoxAt(int idx)
			{
				return (this->_comboBoxes.at(idx));
			}

			unsigned long						getComboBoxesSize()
			{
				return _comboBoxes.size();
			}

			std::vector<gui::Image> &			getAllImages()
			{
				return (this->_images);
			}

			gui::Image &						getImageAt(int idx)
			{
				return (this->_images.at(idx));
			}

			unsigned long						getImagesSize()
			{
				return _images.size();
			}

			std::vector<gui::ProgressBar> &		getAllProgressBars()
			{
				return (this->_progressbars);
			}

			gui::ProgressBar &					getProgressBarAt(int idx)
			{
				return (this->_progressbars.at(idx));
			}

			unsigned long						getProgressBarsSize()
			{
				return _progressbars.size();
			}

			std::vector<gui::Sprite> &			getAllSprites()
			{
				return (this->_sprites);
			}

			gui::Sprite &						getSpriteAt(int idx)
			{
				return (this->_sprites.at(idx));
			}

			unsigned long						getSpritesSize()
			{
				return _sprites.size();
			}

			std::vector<gui::Text> &			getAllTexts()
			{
				return (this->_texts);
			}

			gui::Text &							getTextAt(int idx)
			{
				return (this->_texts.at(idx));
			}

			unsigned long						getTextsSize()
			{
				return _texts.size();
			}

			std::vector<gui::TextInput> &		getAllTextInputs()
			{
				return (this->_textInputs);
			}

			gui::TextInput &					getTextInputAt(int idx)
			{
				return (this->_textInputs.at(idx));
			}

			unsigned long						getTextInputsSize()
			{
				return _textInputs.size();
			}
		};
	}
}

#endif /* NEXUS_ENGINE__LAYER_HPP_ */