#pragma once

#include "GameObject.h"

namespace MarioSample
{
	class Mario : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteBatch &spriteBatch) override;

	private:
		void UpdateInput();
		void UpdateState();
		void ResolveCollision(float deltaTime);

		void Jump();
		void Jumping();
		void Idle();
		void WalkLeft();
		void WalkRight();

		enum class State
		{
			WALKING_LEFT,
			WALKING_RIGHT,
			IDLE,
			JUMPING,
		};

		State state;
	};
}