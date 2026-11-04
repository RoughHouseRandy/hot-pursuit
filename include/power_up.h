#include <bn_sprite_ptr.h>
#include "methods.h"
#include <bn_display.h>
#include "bn_rect.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

class Power_Up {
    public:
        bn::sprite_ptr sprite;
        bn::size size;
        bn::rect boudning_box;

    Power_Up(int start_x, int start_y);
    bn::fixed get_x_coordinate();
    bn::fixed get_y_coordinate();
    bn::fixed random_x_gen();
    bn::fixed random_y_gen();
};
