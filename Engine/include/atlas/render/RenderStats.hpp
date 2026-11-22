#pragma once

#include <cstdint>

namespace atlas
{
	struct RenderStats
	{
		std::uint32_t drawCalls = 0;
		std::uint32_t sprites = 0;
		std::uint32_t triangles = 0;

		void reset()
		{
			drawCalls = 0;
			sprites = 0;
			triangles = 0;
		}
	};
}