#include "RenderSettings.h"

RenderSettings& RenderSettings::Get()
{
	static RenderSettings renderSettings;

	return renderSettings;
}
