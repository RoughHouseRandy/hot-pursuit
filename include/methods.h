#pragma once
#include <bn_fixed.h>
#include <bn_display.h>
#include <bn_random.h>

 int min_y = -bn::display::height() / 2;
 int max_y = bn::display::height() / 2;
 int min_x = -bn::display::width() / 2;
 int max_x = bn::display::width() / 2;
bn::random gen;

// Method to generate random x-coordinate
bn::fixed random_x_gen()
{
    bn::fixed random_x = gen.get_fixed(min_x, max_x);
    return random_x;
}

// Method to generate random y-coordinate
bn::fixed random_y_gen()
{
    bn::fixed random_y = gen.get_fixed(min_y, max_y);
    return random_y;
}
