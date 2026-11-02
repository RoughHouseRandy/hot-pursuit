#include "Enemy.h"
#include "bn_sprite_items_zombie.h"

Enemy::Enemy(bn::fixed start_x, bn::fixed start_y) : 
enemy_sprite(bn::sprite_items::zombie.create_sprite()),
enemy_size({16,16})
{
        enemy_sprite.set_x(start_x);
        enemy_sprite.set_y(start_y);
        speed = 0.5;
        bounding_box = create_bounding_box(enemy_sprite, enemy_size);
}

void Enemy::update(Player &player)
{
    if (player.get_x_coordinate() > enemy_sprite.x())
    {
        enemy_sprite.set_x(enemy_sprite.x() + speed);
    }

    if (player.get_x_coordinate() < enemy_sprite.x())
    {
        enemy_sprite.set_x(enemy_sprite.x() - speed);
    }

    if (player.get_y_coordinate() > enemy_sprite.y())
    {
        enemy_sprite.set_y(enemy_sprite.y() + speed);
    }

    if (player.get_y_coordinate() < enemy_sprite.y())
    {
        enemy_sprite.set_y(enemy_sprite.y() - speed);
    }

        bounding_box = create_bounding_box(enemy_sprite, enemy_size);
}
