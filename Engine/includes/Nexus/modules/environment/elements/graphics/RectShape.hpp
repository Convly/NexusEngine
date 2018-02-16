#ifndef NEXUS_ENGINE__GRAPHICS_RECTSHAPE_HPP_
#define NEXUS_ENGINE__GRAPHICS_RECTSHAPE_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace graphics
		{
			class RectShape
			{
				GraphicsElementInfos	_elementInfos;
				GraphicsRectInfos		_rectShapeInfos;

			public:
				RectShape(GraphicsElementInfos const& elementInfos, GraphicsRectInfos const& rectShapeInfos)
					: _elementInfos(elementInfos), _rectShapeInfos(rectShapeInfos) {}
				~RectShape() {}

			public:
				template <typename Archive>
				void serialize(Archive& ar, unsigned int version)
				{
					ar & _elementInfos;
					ar & _rectShapeInfos;
				}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GRAPHICS_RECTSHAPE_HPP_ */