#ifndef NEXUS_ENGINE__GRAPHICS_CONVEXSHAPE_HPP_
#define NEXUS_ENGINE__GRAPHICS_CONVEXSHAPE_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace graphics
		{
			class ConvexShape
			{
				GraphicsElementInfos	_elementInfos;
				GraphicsConvexInfos		_convexShapeInfos;

			public:
				ConvexShape(GraphicsElementInfos const& elementInfos, GraphicsConvexInfos const& convexShapeInfos)
					: _elementInfos(elementInfos), _convexShapeInfos(convexShapeInfos) {}
				~ConvexShape() {}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GRAPHICS_CONVEXSHAPE_HPP_ */