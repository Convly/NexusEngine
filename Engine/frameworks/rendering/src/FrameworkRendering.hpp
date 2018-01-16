#ifndef FRAMEWORK_RENDERING
# define FRAMEWORK_RENDERING

# include "./gui/GUIHandler.hpp"
# include "./graphics/GraphicsHandler.hpp"
# include "Nexus/engine.hpp"
# include "Nexus/frameworks/RenderingFrameworkTpl.hpp"

class FrameworkRendering : public nx::RenderingFrameworkTpl
{
public:
	FrameworkRendering(nx::Engine*);
	~FrameworkRendering();

	void InitializeWindow(int width, int height, std::string titleWin);
	void RefreshRendering();
	bool addLayer(const std::string&);
	bool addButton(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIButtonInfos& buttonsParams);
	bool addCheckbox(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUICheckboxInfos& checkboxParams);
	bool addProgressBar(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIProgressBarInfos& progressBarParams);
	bool addComboBox(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIComboBoxInfos& comboBoxParams);
	bool addTextInput(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUITextInputInfos& textInputParams);
	bool addText(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUITextInfos& textParams);
	bool addImage(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIImageInfos& imageParams);
	bool addGUISprite(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUISpriteInfos& spriteParams);

	bool addGraphicsSprite(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsSpriteInfos& spriteParams);
	bool addGraphicsCirleShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsCircleInfos& circleShapeParams);
	bool addGraphicsRectShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsRectInfos& rectShapeParams);
	bool addGraphicsConvexShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsConvexInfos& convexShapeParams);

	std::string const	getTypeFromElement(std::string const& layerId, std::string const& elemId) const;
	nx::Vector2f const	getPosFromElement(std::string const& layerId, std::string const& elemId) const;
	nx::Vector2f const	getSizeFromElement(std::string const& layerId, std::string const& elemId) const;

	//Button
	void		setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state);
	void		setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text);
	void		setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize);
	void		setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color);
	void		setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color);
	void		setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color);
	void		setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness);
	void		setPosToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& pos);
	void		setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& size);

	bool const						getStateFromButton(std::string const& layerId, std::string const& buttonId) const;
	std::string const				getTextFromButton(std::string const& layerId, std::string const& buttonId) const;
	unsigned int const				getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::rendering::RGBa const		getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::rendering::RGBa const		getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::rendering::RGBa const		getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const;
	int const						getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const;

	//Checkbox
	void		setStateToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::CheckboxState const state);
	void		setBackgroundColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::RGBa const& color);
	void		setBorderColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::RGBa const& color);
	void		setBorderThicknessToCheckbox(std::string const& layerId, std::string const& checkboxId, int const thickness);
	void		setPosToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::Vector2f const& pos);
	void		setSizeToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::Vector2f const& size);

	nx::rendering::CheckboxState const	getStateFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;
	nx::rendering::RGBa const			getBackgroundColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;
	nx::rendering::RGBa const			getBorderColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;
	int const							getBorderThicknessFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;

	//CircleShape
	void	setBackgroundColorToCircleShape(std::string const& circleShapeId, nx::rendering::RGBa const& color);
	void	setBorderColorToCircleShape(std::string const& circleShapeId, nx::rendering::RGBa const& color);
	void	setBorderThicknessToCircleShape(std::string const& circleShapeId, int const thickness);
	void	setRotationToCircleShape(std::string const& circleShapeId, float const angle);
	void	setRadiusToCircleShape(std::string const& circleShapeId, float const radius);
	void	setPosToCircleShape(std::string const& circleShapeId, nx::Vector2f const& pos);
	void	setSizeToCircleShape(std::string const& circleShapeId, nx::Vector2f const& size);

	nx::rendering::RGBa const	getBackgroundColorFromCircleShape(std::string const& circleShapeId) const;
	nx::rendering::RGBa const	getBorderColorFromCircleShape(std::string const& circleShapeId) const;
	int const					getBorderThicknessFromCircleShape(std::string const& circleShapeId) const;
	float const					getRotationFromCircleShape(std::string const& circleShapeId) const;
	float const					getRadiusFromCircleShape(std::string const& circleShapeId) const;

	//ComboBox
	void	setBackgroundColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::rendering::RGBa const& color);
	void	setBorderColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::rendering::RGBa const& color);
	void	setBorderThicknessToComboBox(std::string const& layerId, std::string const& comboBoxId, int const thickness);
	void	setFontSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, unsigned int const fontSize);
	void	addSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection);
	void	removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection, uint16_t const nbTimes);
	void	removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, uint16_t const idx, uint16_t const nbTimes);
	void	clearSelectionsToComboBox(std::string const& layerId, std::string const& comboBoxId);
	void	setPosToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::Vector2f const& pos);
	void	setSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::Vector2f const& size);

	nx::rendering::RGBa const	getBackgroundColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	nx::rendering::RGBa const	getBorderColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	int const					getBorderThicknessFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	unsigned int const			getFontSizeFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	std::string const			getSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	uint16_t const				getIdxSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	
protected:
	nx::Engine	*_engine;

public:
	static sf::Color RGBa_to_sfColor(const nx::rendering::RGBa&);

private:
	std::shared_ptr<sf::RenderWindow>		_win;
	std::shared_ptr<nx::gui::GUIHandler>	_guiHandler;
	std::shared_ptr<nx::graphics::GraphicsHandler>	_graphicsHandler;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkRendering* CObject(nx::Engine* engine)
	{
		return (new FrameworkRendering(engine));
	}

	__declspec(dllexport) void DObject(FrameworkRendering* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkRendering* CObject(nx::Engine* engine)
	{
		return (new FrameworkRendering(engine));
	}

	void DObject(FrameworkRendering* obj)
	{
		delete obj;
	}
}

#endif

#endif
