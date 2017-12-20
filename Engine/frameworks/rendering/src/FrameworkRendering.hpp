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
	
protected:
	nx::Engine	*_engine;

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
