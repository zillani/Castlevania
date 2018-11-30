#include "RangedWeapon.h"

using namespace Castlevania;

constexpr auto THROW_SPEED = 700.0f;

RangedWeapon::RangedWeapon(EntityType type) : GameObject{ type }
{
	owner = nullptr;
}

void RangedWeapon::SetOwner(GameObject *owner)
{
	this->owner = owner;
}

void RangedWeapon::Throw()
{
	if (owner == nullptr)
		return;

	body.Enabled(true);
	SetVisibility(true);
	SetFacing(owner->GetFacing());

	auto playerBbox = owner->GetBoundingBox();
	auto position = Vector2{
		playerBbox.left,
		playerBbox.top + 5
	};
	SetPosition(position);
	
	if (facing == Facing::Right)
		velocity.x = THROW_SPEED;
	else
		velocity.x = -THROW_SPEED;
}