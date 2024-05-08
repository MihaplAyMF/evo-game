#pragma once

namespace Category
{
	enum Type
	{
		None             = 0,
		SceneAirLayer    = 1 << 0,
		PlayerAircraft   = 1 << 1,
		AliedAircraft    = 1 << 2,
		EnemyAircraft    = 1 << 3,
		Pickup           = 1 << 4,
		AlliedProjectile = 1 << 5,
		EnemyProjecttile = 1 << 6,
		ParticleSystem   = 1 << 7,

		Player = PlayerAircraft | AliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjecttile,
	};
}