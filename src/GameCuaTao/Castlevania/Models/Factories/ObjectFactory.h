#pragma once

#include "../Characters/Player/Player.h"
#include "../Characters/Enemies/Zombie.h"
#include "../Characters/Enemies/Panther.h"
#include "../Characters/Enemies/Fishman.h"
#include "../Characters/Enemies/VampireBat.h"
#include "../Characters/Enemies/GiantBat.h"
#include "../Items/BreakableWall.h"
#include "../Items/Container.h"
#include "../Items/Door.h"
#include "../Weapons/HolyWater.h"
#include "../Items/MoneyBag.h"
#include "../Items/Powerup.h"
#include "../Spawners/SpawnArea.h"
#include "../Spawners/SpawnPoint.h"
#include "../Areas/WaterArea.h"
#include "../../Effects/EffectFactory.h"

namespace Castlevania
{
	constexpr auto ITEM_FALL_SPEED = 150.0f;

	class ObjectFactory
	{
	public:
		ObjectFactory(ContentManager &content);

		std::unique_ptr<GameObject> CreateRectangleObject(ObjectId type, RectF rect);
		std::unique_ptr<GameObject> CreateBlock(RectF rect);
		std::unique_ptr<WaterArea> CreateWaterArea(RectF rect);
		std::unique_ptr<SpawnPoint> CreateSpawnPoint(ObjectId type, RectF rect);
		std::unique_ptr<SpawnArea> CreateSpawnArea(ObjectId type, RectF rect);
		std::unique_ptr<Trigger> CreateTrigger(RectF rect, TriggerType triggerType);

		std::unique_ptr<GameObject> CreateBat(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateCloud(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreatePlayer(Vector2 position = Vector2::Zero());

		std::unique_ptr<Container> CreateBrazier(ObjectId itemType, Vector2 position = Vector2::Zero());
		std::unique_ptr<Container> CreateCandle(ObjectId itemType, Vector2 position = Vector2::Zero());
		std::unique_ptr<Container> CreateBreakableBlock(ObjectId itemType, std::string spritePath = "", Vector2 position = Vector2::Zero());
		std::unique_ptr<BreakableWall> CreateBreakableWall(ObjectId itemType, Vector2 position = Vector2::Zero());

		std::unique_ptr<Enemy> CreateEnemy(ObjectId type, Vector2 position = Vector2::Zero());
		std::unique_ptr<Zombie> CreateZombie(Vector2 position = Vector2::Zero());
		std::unique_ptr<Panther> CreatePanther(Vector2 position = Vector2::Zero());
		std::unique_ptr<Fishman> CreateFishman(Vector2 position = Vector2::Zero());
		std::unique_ptr<VampireBat> CreateVampireBat(Vector2 position = Vector2::Zero());
		std::unique_ptr<GiantBat> CreateGiantBat(Vector2 position = Vector2::Zero());

		std::unique_ptr<Whip> CreateWhip(Vector2 position = Vector2::Zero());
		std::unique_ptr<Whip> CreateFlashingWhip(Vector2 position = Vector2::Zero());
		std::unique_ptr<RangedWeapon> CreateSubWeapon(ObjectId type, Vector2 position = Vector2::Zero());
		std::unique_ptr<RangedWeapon> CreateAxe(Vector2 position = Vector2::Zero());
		std::unique_ptr<RangedWeapon> CreateDagger(Vector2 position = Vector2::Zero());
		std::unique_ptr<HolyWater> CreateHolyWater(Vector2 position = Vector2::Zero());
		std::unique_ptr<RangedWeapon> CreateFireball(Vector2 position = Vector2::Zero());

		std::unique_ptr<Powerup> CreatePowerup(ObjectId type, Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateMoneyBag(ObjectId type, Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateBlueMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateWhiteMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateRedMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateFlashingMoneyBag(Vector2 position = Vector2::Zero());
		
		std::unique_ptr<Powerup> CreateAxeItem(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateCross(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateDaggerItem(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateHolyWaterItem(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateLargeHeart(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateSmallHeart(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateInvisibleJar(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreatePorkChop(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateStopwatch(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateWhipPowerup(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateDoubleShot(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateCrystalBall(Vector2 position = Vector2::Zero());

		std::unique_ptr<Door> CreateDoor(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateCastle(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateBrickBlock(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateDirtBlock(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateWaterZone(Vector2 position = Vector2::Zero());

	private:
		ContentManager &content;
		std::unique_ptr<EffectFactory> effectFactory;

		void ReadEnemyConfig(Enemy &enemy, Dictionary stats);
		void ReadSubWeaponConfig(RangedWeapon &weapon, Dictionary stats);
		void ReadSpawnAreaConfig(SpawnArea &spawnArea, Dictionary stats);

		std::unique_ptr<SpawnArea> ConstructSpawnArea(ObjectId type);
	};
}