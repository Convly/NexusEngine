#ifndef GUILAYER_HPP_
# define GUILAYER_HPP_

# include <vector>
# include <string>
# include <memory>
# include "GUIElement.hpp"

class GUILayer
{
	std::string									_identifier;
	bool										_isVisible;
	std::vector<std::shared_ptr<GUIElement>>	_guiElements;

public:
	GUILayer(std::string const& identifier);
	~GUILayer();

	void	add(std::shared_ptr<GUIElement> elem);

	// Display
	void	draw();

	// Setters
	void										setVisible(bool const state);

	// Getters
	bool										isVisible() const;
	std::vector<std::shared_ptr<GUIElement>>	getElements() const;
};

#endif /* GUILAYER_HPP_ */