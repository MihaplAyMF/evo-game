#pragma once

namespace Category
{
	enum Type
	{
		None             = 0,
		SceneAirLayer    = 1 << 0,
		PlayerObject     = 1 << 1,
		EnemyObject      = 1 << 2,
		Coin             = 1 << 3,
		Pickup           = 1 << 4,

		Player = PlayerObject | EnemyObject
	};
}