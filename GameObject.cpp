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
Projectile* GameObject::shootProjectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime, sf::Vector2f playerPosition)
{
	Projectile* lol = new Projectile(texture, nDamage, nDirectionAndSpeed, nLifeTime);
	lol->setOrigin({ 8,8 });
	lol->setPosition(playerPosition);


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
			dir[i] = sf::IntRect({ {16 * i, 0},{16,16} });
			
		}
		spriteInitalized = true;
	}
	this->setTextureRect(dir[0]); // 0 down, 1 left, 2 right , 4 up. changes based on sprite sheet.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) 
	{
		this->move({ -moveSpeed / 2,moveSpeed / 2 });
		this->setTextureRect(dir[0]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
	{
		this->move({ moveSpeed / 2,moveSpeed / 2 });
		this->setTextureRect(dir[0]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
	{
		this->move({ moveSpeed / 2,-moveSpeed / 2 });
		this->setTextureRect(dir[0]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
	{
		this->move({ -moveSpeed / 2,-moveSpeed / 2 });
		this->setTextureRect(dir[0]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
	{
		this->move({ 0,moveSpeed });
		this->setTextureRect(dir[0]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
	{
		this->move({ -moveSpeed/2,moveSpeed/2 });
		this->setTextureRect(dir[0]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
	{
		this->move({ -moveSpeed,0 });
		this->setTextureRect(dir[1]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
	{
		this->move({ moveSpeed,0 });
		this->setTextureRect(dir[2]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
	{
		this->move({ 0,-moveSpeed });
		this->setTextureRect(dir[3]);
	}
}