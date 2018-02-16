#ifndef NEXUS_ENGINE__GRAPHICS_CIRCLESHAPE_HPP_
#define NEXUS_ENGINE__GRAPHICS_CIRCLESHAPE_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace graphics
		{
			class CircleShape
			{
				GraphicsElementInfos	_elementInfos;
				GraphicsCircleInfos		_circleShapeInfos;

			public:
				template <typename Archive>
				void serialize(Archive& ar, unsigned int version)
				{
					ar & _elementInfos;
					ar & _circleShapeInfos;
				}

			public:
				CircleShape(GraphicsElementInfos const& elementInfos, GraphicsCircleInfos const& circleShapeInfos)
					: _elementInfos(elementInfos), _circleShapeInfos(circleShapeInfos) {}
				~CircleShape() {}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GRAPHICS_CIRCLESHAPE_HPP_ */