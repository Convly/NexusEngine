#ifndef GUIHANDLER_HPP_
# define GUIHANDLER_HPP_
    
# include <vector>
# include <memory>
# include "GUIElement.hpp"
    
class GUIHandler
{
    std::vector<std::shared_ptr<GUIElement>> _guiElements;

public:
	GUIHandler();
	~GUIHandler();

	void	addGUIElement(std::shared_ptr<GUIElement> elem);

	// Display
	void	drawGUIElements();

	// Getters
	std::vector<std::shared_ptr<GUIElement>>	getGUIElements() const;
};

#endif /* GUIHANDLER_HPP_ */