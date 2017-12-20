#ifndef GUIHANDLER_HPP_
# define GUIHANDLER_HPP_
    
# include <vector>
# include <memory>
# include "GUILayer.hpp"
    
class GUIHandler
{
    std::vector<std::shared_ptr<GUILayer>> _guiLayers;

public:
	GUIHandler();
	~GUIHandler();

	void	addLayer(std::shared_ptr<GUILayer> elem);

	// Display
	void	drawLayers();

	// Getters
	std::vector<std::shared_ptr<GUILayer>>	getLayers() const;
};

#endif /* GUIHANDLER_HPP_ */