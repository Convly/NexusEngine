#ifndef NEXUS_ENGINE__GRAPHICS_SPRITE_HPP_
#define NEXUS_ENGINE__GRAPHICS_SPRITE_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace graphics
		{
			class Sprite
			{
				GraphicsElementInfos	_elementInfos;
				GraphicsSpriteInfos		_spriteInfos;

			public:
				Sprite(GraphicsElementInfos const& elementInfos, GraphicsSpriteInfos const& spriteInfos)
					: _elementInfos(elementInfos), _spriteInfos(spriteInfos) {}
				~Sprite() {}
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GRAPHICS_SPRITE_HPP_ */