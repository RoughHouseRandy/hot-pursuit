#pragma once

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>
#include "Player.h"
#include "create_bounding_box.h"

class Enemy
{
public:
    bn::sprite_ptr enemy_sprite;
    bn::fixed speed;  
    bn::size enemy_size; 
    bn::rect bounding_box;
    
    Enemy(bn::fixed start_x, bn::fixed start_y);

    void update(Player &player);
};