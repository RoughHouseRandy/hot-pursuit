#pragma once

#include <bn_sprite_ptr.h>
#include <bn_fixed_point.h>
#include <bn_size.h>
#include <bn_rect.h> 
#include <bn_keypad.h>

class Player
{
public:
    bn::sprite_ptr sprite;
    bn::fixed speed;       
    bn::size size;         
    bn::rect bounding_box; 

    Player(int start_x, int start_y);
    void update();
    bn::fixed get_x_coordinate();
    bn::fixed get_y_coordinate();
};