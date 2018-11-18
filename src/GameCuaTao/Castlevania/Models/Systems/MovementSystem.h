#pragma once

#include "IMovementSystem.h"

namespace Castlevania
{
	class GameObject;

	class MovementSystem : public IMovementSystem
	{
	public:
		MovementSystem(GameObject &parent);

		Vector2 GetDistance() override;
		void Update(float deltaTime) override;

	private:
		GameObject &parent;
		float deltaTime;
		Vector2 distance; // estimated distance next frame
	};
}