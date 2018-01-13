#ifndef FRAMEWORK_RENDERING
# define FRAMEWORK_RENDERING

# include "GUIHandler.hpp"
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
	bool addSprite(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUISpriteInfos& spriteParams);
	
protected:
	nx::Engine	*_engine;

public:
	static sf::Color RGBa_to_sfColor(const nx::rendering::RGBa&);

private:
	std::shared_ptr<sf::RenderWindow>	_win;
	std::shared_ptr<GUIHandler>			_handler;
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
