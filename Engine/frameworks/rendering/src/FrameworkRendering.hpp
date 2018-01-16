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

	//Button
	void				setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state);
	void				setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text);
	void				setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize);
	void				setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color);
	void				setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color);
	void				setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color);
	void				setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness);
	void				setPosToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& pos);
	void				setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& size);

	bool const					getStateFromButton(std::string const& layerId, std::string const& buttonId) const;
	std::string const			getTextFromButton(std::string const& layerId, std::string const& buttonId) const;
	unsigned int const			getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::rendering::RGBa const &	getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::rendering::RGBa const &	getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::rendering::RGBa const &	getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const;
	int const					getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const;
	
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
