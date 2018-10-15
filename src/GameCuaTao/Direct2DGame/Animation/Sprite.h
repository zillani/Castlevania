#pragma once

#include <string>
#include "../Base/BoundingBox.h"
#include "../Base/Vector.h"
#include "../GraphicsDeviceManager.h"

class Sprite
{
public:
	Sprite();
	Sprite(std::string spriteID, BoundingBox boundingBox);
	void Draw(SpritePtr spriteHandler, Texture texture, Vector position);

private:
	std::string id;				// Sprite ID in the sprite database
	BoundingBox boundingBox;
	static GraphicsDeviceManager *graphics;
};