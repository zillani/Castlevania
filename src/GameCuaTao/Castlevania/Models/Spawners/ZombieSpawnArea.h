#pragma once

#include "SpawnArea.h"

namespace Castlevania
{
	class ZombieSpawnArea : public SpawnArea
	{
	public:
		ZombieSpawnArea(ObjectFactory &objectFactory);

	private:
		void SpawnObject(UpdateData &updateData) override;
	};
}