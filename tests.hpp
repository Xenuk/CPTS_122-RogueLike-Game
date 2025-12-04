#pragma once
#include "Header.hpp"
#include "Projectile.hpp"
#include "Weapon.hpp"
#include "Save.hpp"
#include <vector>

// All tests generated with AI
// Prompt: @workspace please create 5 unit tests for this game

namespace Tests {
	bool runAllTests();
	bool testProjectileLifetime();
	bool testProjectileMovement();
	bool testEnemySpawnPositions();
	bool testWeaponReload();
	bool testSaveLoad();
}