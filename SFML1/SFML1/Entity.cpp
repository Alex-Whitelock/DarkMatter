#include "Entity.h"
#include "Game.h"

Entity::Entity(const sf::Vector2f& position, Game* game)
	: game_(game)
{
	sprite_.setPosition(position);
}