#ifndef NEXUS_ENGINE__GUI_PROGRESSBAR_HPP_
#define NEXUS_ENGINE__GUI_PROGRESSBAR_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class ProgressBar
			{
				GUIElementInfos		_elementInfos;
				GUIProgressBarInfos	_progressBarInfos;
			
			public:
				template <typename Archive>
				void serialize(Archive& ar, unsigned int version)
				{
					ar & _elementInfos;
					ar & _progressBarInfos;
				}

			public:
				ProgressBar() {}
				ProgressBar(GUIElementInfos const& elementInfos, GUIProgressBarInfos const& progressBarInfos)
					: _elementInfos(elementInfos), _progressBarInfos(progressBarInfos) {}
				~ProgressBar() {}

			public:
				bool isModified(){
					if (_elementInfos.getIsModified() || _progressBarInfos.getIsModified()){
						return true;
					}
					return false;
				}

				void resetModified(){
					_elementInfos.setIsModified(false);
					_progressBarInfos.setIsModified(false);
				}

				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIProgressBarInfos& getGuiProgressBarInfos() { return _progressBarInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_PROGRESSBAR_HPP_ */