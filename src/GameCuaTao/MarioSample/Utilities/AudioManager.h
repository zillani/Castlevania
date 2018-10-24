#pragma once

#include <map>
#include <vector>
#include "Direct2DGame/Content/ContentManager.h"

namespace MarioSample
{
	class AudioManager
	{
	public:
		static void LoadContent(ContentManager &content, std::vector<std::string> sounds);

		static void Play(std::string name);
		static void PlaySong(std::string name);
		static void PlayLoop(std::string name);
		
		static void Stop(std::string name);
		static bool IsPlaying(std::string name);

	private:
		static std::map<std::string, std::shared_ptr<Sound>> soundDict;
		static float volume;
	};
}