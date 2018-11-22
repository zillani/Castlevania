#pragma once

#include "ObjectCollection.h"
#include "../Models/GameObject.h"
#include "../Models/Characters/Player/Player.h"
#include "../Models/Characters/Bat.h"
#include "../Models/Items/FirePit.h"
#include "../Models/Weapons/Whip.h"
#include "../Models/Items/Powerup.h"
#include "../Effects/EffectFactory.h"

namespace Castlevania
{
	using ObjectProperties = std::map<std::string, std::string>;
	using ObjectsProperties = std::vector<ObjectProperties>;

	class ObjectFactory
	{
	public:
		ObjectFactory(ContentManager &content);

		ObjectCollection CreateObjectCollection(ObjectsProperties properties);
		
		std::unique_ptr<Bat> CreateBat();
		std::unique_ptr<Player> CreatePlayer();
		std::unique_ptr<Player> CreateSimon();
		std::unique_ptr<FirePit> CreateFirePit(ObjectProperties properties);
		std::unique_ptr<Whip> CreateWhip(GameObject &gameObject);
		std::unique_ptr<Whip> CreateFlashingWhip(GameObject &gameObject);
		std::unique_ptr<RangedWeapon> CreateKnife();
		std::unique_ptr<Powerup> CreateKnifeItem();
		std::unique_ptr<Powerup> CreateHeart();
		std::unique_ptr<Powerup> CreateWhipPowerup();

		std::unique_ptr<Powerup> CreatePowerup(std::string name);

	private:
		ContentManager &content;
		std::unique_ptr<EffectFactory> effectManager;
		
		std::map<std::string, EntityType> stringToType;

		std::unique_ptr<GameObject> ConstructObject(ObjectProperties properties);
	};
}