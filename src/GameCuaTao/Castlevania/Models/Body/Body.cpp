#include <limits>
#include "Direct2DGame/MathHelper.h"
#include "Body.h"

using namespace Castlevania;

Body::Body(IGameObject &dynamicObject) : parent{ dynamicObject }
{
}

void Body::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

// Extension of original SweptAABB to deal with two moving objects
// 'moving' and 'static' prefixes in variable names refer to the moving object
// (the one that check for collision) and the static object (the one that is
// checked against). It's not neccesary one of the object has to be moving or static
// since we already calculate the relative distance the 'moving' object travel
// to the 'static' object
CollisionResult Body::PredictCollision(IGameObject &dynamicObject)
{
	// deal with moving object: m speed = original m speed - collide object speed
	auto staticVelocity = dynamicObject.GetVelocity();
	auto staticDistance = staticVelocity * deltaTime;
	auto movingVelocity = parent.GetVelocity();
	auto movingDistance = movingVelocity * deltaTime;
	auto distance = movingDistance - staticDistance;

	auto staticRect = dynamicObject.GetBoundingBox();
	auto movingRect = parent.GetBoundingBox();

	auto sweptAABBResult = SweptAABB(movingRect, distance, staticRect);

	return CollisionResult{
		sweptAABBResult.timeToCollide,
		sweptAABBResult.direction,
		dynamicObject };
}

CollisionResult Body::PredictCollision(IColliable &staticObject)
{
	auto velocity = parent.GetVelocity();
	auto distance = velocity * deltaTime;
	auto movingRect = parent.GetBoundingBox();
	auto staticRect = staticObject.GetBoundingBox();

	auto sweptAABBResult = SweptAABB(movingRect, distance, staticRect);

	return CollisionResult{
		sweptAABBResult.timeToCollide,
		sweptAABBResult.direction,
		staticObject };
}

Body::SweptAABBResult Body::SweptAABB(Rect movingRect, Vector2 distance, Rect staticRect)
{
	// Broad-phase test 
	auto broadPhase = CreateBroadPhase(movingRect, distance);
	
	if (!broadPhase.TouchesOrIntersects(staticRect))
		return SweptAABBResult::Empty();

	if (distance == Vector2::Zero())
		return SweptAABBResult::Empty();

	auto entryDistance = Vector2{};
	auto exitDistance = Vector2{};

	if (distance.x > 0)
	{
		entryDistance.x = (float)(staticRect.left - movingRect.right);
		exitDistance.x = (float)(staticRect.right - movingRect.left);
	}
	else
	{
		entryDistance.x = (float)(staticRect.right - movingRect.left);
		exitDistance.x = (float)(staticRect.left - movingRect.right);
	}

	if (distance.y > 0)
	{
		entryDistance.y = (float)(staticRect.top - movingRect.bottom);
		exitDistance.y = (float)(staticRect.bottom - movingRect.top);
	}
	else
	{
		entryDistance.y = (float)(staticRect.bottom - movingRect.top);
		exitDistance.y = (float)(staticRect.top - movingRect.bottom);
	}

	auto entryTime_x = float{};
	auto entryTime_y = float{};
	auto exitTime_x = float{};
	auto exitTime_y = float{};

	if (distance.x == 0)
	{
		entryTime_x = -std::numeric_limits<float>::infinity();
		exitTime_x = std::numeric_limits<float>::infinity();
	}
	else
	{
		entryTime_x = entryDistance.x / distance.x;
		exitTime_x = exitDistance.x / distance.x;
	}

	if (distance.y == 0)
	{
		entryTime_y = -std::numeric_limits<float>::infinity();
		exitTime_y = std::numeric_limits<float>::infinity();
	}
	else
	{
		entryTime_y = entryDistance.y / distance.y;
		exitTime_y = exitDistance.y / distance.y;
	}

	if (entryTime_x <= 0 && entryTime_y <= 0 || entryTime_x > 1 || entryTime_y > 1)
		return SweptAABBResult::Empty();

	auto entryTime = MathHelper::Max(entryTime_x, entryTime_y);
	auto exitTime = MathHelper::Min(exitTime_x, exitTime_y);

	if (entryTime > exitTime)
		return SweptAABBResult::Empty();

	auto direction = Direction{};
	if (entryTime_x > entryTime_y)
	{
		if (distance.x > 0)
			direction = Direction::Left;
		else
			direction = Direction::Right;
	}
	else
	{
		if (distance.y > 0)
			direction = Direction::Top;
		else
			direction = Direction::Bottom;
	}

	return SweptAABBResult{ entryTime, direction };
}

Body::BroadPhase Body::CreateBroadPhase(Rect rect, Vector2 distance)
{
	auto broadPhase = BroadPhase{};

	broadPhase.left   = MathHelper::Min(rect.left,   rect.left   + (long)distance.x);
	broadPhase.top    = MathHelper::Min(rect.top,    rect.top    + (long)distance.y);
	broadPhase.right  = MathHelper::Max(rect.right,  rect.right  + (long)distance.x);
	broadPhase.bottom = MathHelper::Max(rect.bottom, rect.bottom + (long)distance.y);

	return broadPhase;
}
