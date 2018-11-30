#pragma once

#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "IGameObject.h"
#include "EntityType.h"
#include "Facing.h"

namespace Castlevania
{
	class RectangleObject : public IGameObject
	{
	public:
		RectangleObject(RectF boundingBox, EntityType type = EntityType::Boundary);

		int GetType() override;
		Vector2 GetDistance() override;
		RectF GetBoundingBox() override;
		Vector2 Center();
		
		Facing GetFacing();
		void SetFacing(Facing facing);
		Body &GetBody() override;

		void Draw(SpriteExtensions &spriteBatch);

	private:
		EntityType identifier;
		RectF boundingBox;
		Facing facing;
		Body body;
	};
}