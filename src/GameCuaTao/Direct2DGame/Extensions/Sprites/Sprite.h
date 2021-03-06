#pragma once

#include <string>
#include "../TextureRegion.h"
//#include "../Transform.h"
#include "../../Base/Color.h"
#include "../../Graphics/SpriteEffects.h"

class Sprite
{
public:
	Sprite(std::shared_ptr<Texture> texture);
	Sprite(TextureRegion textureRegion);

	void SetTextureRegion(TextureRegion textureRegion);
	TextureRegion GetTextureRegion();
	
	RectF GetFrameRectangle(Vector2 position);
	RectF GetBoundingRectangle(Vector2 position);

	void SetAlpha(float alpha);
	float GetAlpha();

	void SetColor(Color color);
	Color GetColor();
	
	void SetVisibility(bool isVisible);
	bool IsVisible();
	
	void SetEffect(SpriteEffects effect);
	SpriteEffects GetEffect();

private:
	TextureRegion textureRegion;

	float alpha;
	Color color = Color::White();
	bool isVisible;
	SpriteEffects effect;
};