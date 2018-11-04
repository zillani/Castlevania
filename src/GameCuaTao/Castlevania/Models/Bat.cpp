#include "Bat.h"

using namespace Castlevania;

void Bat::LoadContent(ContentManager &content)
{
	animations = content.Load<AnimationDict>("Characters/NPCs/BatAnimationDef.xml");
	auto stats = content.Load<CharacterStats>("CharacterStats/Bat.xml");

	currentAnimation = stats->startingAnimation;
	speed = stats->speed;
	velocity = speed;
}

void Bat::Update(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);
	GetAnimation().Update();
}

void Bat::Draw(SpriteBatch &spritebatch)
{
	GetAnimation().Draw(spritebatch, position, Color::White(), SpriteEffects::None);
}