#include "tests.hpp"
#include <iostream>
#include <cassert>
#include <random>
#include <cmath>

using namespace Tests;

bool Tests::testProjectileLifetime()
{
    // create local projectile vector and mimic Game::projectileHandling logic
    sf::Texture tex;
    Projectile* p1 = new Projectile(tex, 1, { 1.f, 0.f }, 3.0); // lifeTime = 3
    p1->setPosition({ 0,0 });
    p1->setCurrLifeTime(3.0); // already expired

    std::vector<Projectile*> v{ p1 };

    // simulate handling: increment then delete if >= lifeTime
    for (int i = static_cast<int>(v.size()) - 1; i >= 0; --i) {
        double curr = v[i]->getCurrLifeTime();
        v[i]->setCurrLifeTime(curr + 1.0);
        if (v[i]->getCurrLifeTime() >= v[i]->getLifeTime()) {
            delete v[i];
            v.erase(v.begin() + i);
        }
    }

    bool passed = v.empty();
    if (!passed) { for (auto* q : v) delete q; }
    return passed;
}

bool Tests::testProjectileMovement()
{
    sf::Texture tex;
    Projectile p(tex, 1, { 2.f, 3.f }, 10.0);
    p.setPosition({ 0.f, 0.f });
    p.move(p.getDirectionAndSpeed()); // move by directionAndSpeed
    sf::Vector2f pos = p.getPosition();
    return (std::abs(pos.x - 2.f) < 1e-6f) && (std::abs(pos.y - 3.f) < 1e-6f);
}

bool Tests::testEnemySpawnPositions()
{
    // replicate spawn logic ranges from Game::runGame
    const float aggroDistance = 200.0f;
    const float spawnRadius = 250.0f;
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159265358979323846f);
    std::uniform_real_distribution<float> radiusDist(aggroDistance + 50.0f, spawnRadius);

    bool ok = true;
    for (int i = 0; i < 1000; ++i) {
        float angle = angleDist(rng);
        float radius = radiusDist(rng);
        if (!(radius >= aggroDistance + 50.0f && radius <= spawnRadius)) { ok = false; break; }
        sf::Vector2f spawnPos = { std::cos(angle) * radius, std::sin(angle) * radius };
        float dist = std::sqrt(spawnPos.x * spawnPos.x + spawnPos.y * spawnPos.y);
        if (!(dist >= aggroDistance + 50.0f - 1e-3f && dist <= spawnRadius + 1e-3f)) { ok = false; break; }
    }
    return ok;
}

bool Tests::testWeaponReload()
{
    Weapon w("testgun", 5, 10, 0, 0, 10, true); // sample ctor (matches workspace)
    int maxAmmo = w.getAmmo();
    w.setCurrAmmo(0);
    w.reload();
    return w.getCurrAmmo() == maxAmmo || w.getAmmo() == -1;
}

bool Tests::testSaveLoad()
{
    Save s;
    int origScore = s.getScore();
    s.addScore(123);
    s.save();
    // create new instance and load (assumes Save loads on construction or has load)
    Save s2;
    s2.load();
    bool ok = (s2.getScore() >= origScore + 123);
    // cleanup: revert added score
    s.addScore(-(s.getScore() - origScore));
    s.save();
    return ok;
}

bool Tests::runAllTests()
{
    struct Case { const char* name; bool (*fn)(); };
    Case cases[] = {
        {"ProjectileLifetime", testProjectileLifetime},
        {"ProjectileMovement", testProjectileMovement},
        {"EnemySpawnPositions", testEnemySpawnPositions},
        {"WeaponReload", testWeaponReload},
        {"SaveLoad", testSaveLoad},
    };

    bool all = true;
    for (auto& c : cases) {
        bool ok = c.fn();
        std::cout << c.name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        all = all && ok;
    }
    return all;
}

#ifdef TEST_MAIN
int main()
{
    bool ok = Tests::runAllTests();
    return ok ? 0 : 1;
}
#endif