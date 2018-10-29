#pragma once

#include <memory>
#include <string>
#include "Direct2DGame/Graphics/Texture.h"
#include "Direct2DGame/Base/Vector2.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "AbstractScene.h"

namespace Castlevania
{
	class MenuScene : public AbstractScene
	{
	public:
		MenuScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::shared_ptr<Texture> background;

		const std::string startGameText = "PUSH START KEY";
		Vector2 startGameTextPosition;
		Stopwatch transitionTimer;
	};
}