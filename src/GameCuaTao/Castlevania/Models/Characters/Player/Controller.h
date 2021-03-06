#pragma once

#include "Direct2DGame/Input/IController.h"
#include "Player.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "../../../Models/Systems/Control/ControlSystem.h"

namespace Castlevania
{
	class Controller : public ControlSystem, public IController
	{
	public:
		Controller(Player &player, ObjectFactory &objectFactory);

		void OnKeyStateChanged(KeyboardState &keyboardState) override;
		void OnKeyDown(int keyCode) override;
		void OnKeyUp(int keyCode) override;

		void Update(UpdateData &updateData) override;

	private:
		Player &player;
		KeyboardState keyboardState;
		ObjectFactory &objectFactory;

		// Return true if holding both left and right key
		bool IsHoldingLeftAndRight();
		bool IsHoldingUpAndDown();

		bool PressSubweaponKeys(int keyCode);
		void UseSubweapon();
	};
}