#include "GameObject.hpp"

GameObject::GameObject(const sf::Texture& texture, int nCurrHealth,int nMaxHealth,int nDamage, int nProjectileCooldown, float nMoveSpeed) :
Sprite(texture)
{
	currHealth = nCurrHealth;
	maxHealth = nMaxHealth;
	damage = nDamage;
	moveSpeed = nMoveSpeed;
	projectileCooldown = nProjectileCooldown;
}

GameObject::~GameObject()
{

}


int GameObject::getCurrHealth()
{
	return currHealth;
}
void GameObject::setCurrHealth(int newCurrHealth)
{
	currHealth = newCurrHealth;
}


int GameObject::getMaxHealth()
{
	return maxHealth;
}
void GameObject::setMaxHealth(int newMaxHealth)
{
	maxHealth = newMaxHealth;
}

int GameObject::getDamage()
{
	return damage;
}
void GameObject::setDamage(int newDamage)
{
	damage = newDamage;
}

float GameObject::getMoveSpeed()
{
	return moveSpeed;
}
void GameObject::setMoveSpeed(float newMoveSpeed)
{
	moveSpeed = newMoveSpeed;
}

sf::Sprite* GameObject::getSprite()
{
	return nullptr;
}
void GameObject::setSprite(std::string textureFilePath)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(textureFilePath))
	{
		std::cout << "Error loading from file" << std::endl;
	}
	this->setTexture(*texture);
}
Projectile* GameObject::shootProjectile(sf::RenderWindow* window,const sf::Texture& texture,float projectileSpeed, int nDamage, double nLifeTime)
{
	sf::Vector2f pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	float angle = atan2(pos.y - getPosition().y, pos.x - getPosition().x);
	
	Projectile* lol = new Projectile(texture, nDamage, { projectileSpeed * cos(angle),projectileSpeed * sin(angle) }, nLifeTime);
	lol->setOrigin({ 8,8 });
	lol->setPosition({ getPosition() });

	std::cout << pos.x << "," << pos.y << std::endl;
	std::cout << pos.x - getPosition().x << "," << pos.y - getPosition().y << std::endl;

	return lol;
}

void GameObject::characterMoveControls()
{
	static bool spriteInitalized = false;
	static sf::IntRect dir[4]; // static mean its only intialized first call and is local scope but its storage is global.
	if (spriteInitalized == false)
	{
		for (int i = 0; i < 4; ++i)
		{
			// says we read from sheet from starting at 0,0 then moving 16 to the right and the second bracket
			// is the size of the sprite total.
			dir[i] = sf::IntRect({ {0, 16 * i},{16,16} });
			
		}
		spriteInitalized = true;
	}
	this->setTextureRect(dir[0]); // 0 down, 1 left, 2 right , 4 up. changes based on sprite sheet.
	//movement below
	float movementVerticle = 0, movementHorizontal = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
	{
		movementVerticle = movementVerticle + moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
	{
		movementHorizontal = movementHorizontal - moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
	{
		movementHorizontal = movementHorizontal + moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
	{
		movementVerticle = movementVerticle - moveSpeed;
	}
	if (movementVerticle != 0 && movementHorizontal != 0) {
		//0.707106781187 ~ ((1+1)^(1/2))/2
		movementVerticle = movementVerticle * 0.707106781187;
		movementHorizontal = movementHorizontal * 0.707106781187;
	}

	if (movementVerticle != 0 || movementHorizontal != 0) {
		move({ movementHorizontal,movementVerticle });
	}
	if (movementVerticle > 0) { setTextureRect(dir[0]); }
	else if (movementVerticle < 0) { setTextureRect(dir[3]); }
	else if (movementHorizontal > 0) { setTextureRect(dir[1]); }
	else if (movementHorizontal < 0) { setTextureRect(dir[2]); }

	movementHorizontal = 0;
	movementVerticle = 0;
}

