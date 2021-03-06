#pragma once

#include <map>
#include "Direct2DGame/Base/Vector2.h"
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Graphics/SpriteBatch.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"

namespace MarioSample
{
	enum class Direction
	{
		Left,
		Right,
	};

	class GameObject
	{
	public:
		GameObject();

		void SetPosition(float x, float y);
		void SetSpeed(float vx, float vy);

		virtual void LoadContent(ContentManager &content) = 0;

		virtual void Update(float deltaTime);
		void UpdateDistance(float deltaTime);

		virtual void Draw(SpriteBatch &spriteBatch);
		virtual ~GameObject();

	protected:
		Vector2 position;
		Vector2 velocity;
		Direction direction;

		std::unique_ptr<AnimatedSprite> sprite;
	};
}