#include "Player.h"
#include <bn_rect.h>
#include <bn_display.h>
#include "bn_sprite_items_joey.h"
#include "create_bounding_box.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Player::Player(int start_x, int start_y) : 
sprite(bn::sprite_items::joey.create_sprite()),
speed(1.5),
size({16,16}),
bounding_box(create_bounding_box(sprite,size))

{
    sprite.set_x(start_x);
    sprite.set_y(start_y);
}

void Player::update()
{
    if (bn::keypad::right_held())
    {
        sprite.set_x(sprite.x() + speed);
    }
    if (bn::keypad::left_held())
    {
        sprite.set_x(sprite.x() - speed);
    }
    // TODO: Add logic for up and down
    if (bn::keypad::up_held())
    {
        sprite.set_y(sprite.y() - speed);
    }
    if (bn::keypad::down_held())
    {
        sprite.set_y(sprite.y() + speed);
    }

        // Add x scroll logic
    if (get_x_coordinate() > MAX_X)
    {
        sprite.set_x(MIN_X);
    }
    if (get_x_coordinate() < MIN_X)
    {
        sprite.set_x(MAX_X);
    }

        // Add y scroll logic
    if (get_y_coordinate() > MAX_Y)
    {
        sprite.set_y(MIN_Y);
    }
    if (get_y_coordinate() < MIN_Y)
    {
        sprite.set_y(MAX_Y);
    }

     bounding_box = create_bounding_box(sprite, size);
}

bn::fixed Player::get_x_coordinate()
{
    bn::fixed x_pos = sprite.x();
    return x_pos;
}

bn::fixed Player::get_y_coordinate()
{
    bn::fixed y_pos = sprite.y();
    return y_pos;    
}
