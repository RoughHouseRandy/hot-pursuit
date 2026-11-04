#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"
#include "bn_random.h"
#include "create_bounding_box.h"
#include "Player.h"
#include "Enemy.h"
#include "methods.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
static constexpr int MAX_SCORE_CHARS = 22;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// Player start location
static constexpr int START_X = 44;
static constexpr int START_Y = 22;

// Enemy start location
static constexpr int ENEMY_X = 0;
static constexpr int ENEMY_Y = 0;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

// Max amount of enemies
static constexpr int MAX_ENEMY = 5;



/**
 * Displays a score and high score.
 *
 * Score starts a 0 and is increased each time update is called, and reset to 0 when resetScore is
 * called. High score tracks the highest score ever reached.
 */
class ScoreDisplay
{
public:
    ScoreDisplay() : score(0),                                                                 // Start score at 0
                     high_score(0),                                                            // Start high score at 0
                     score_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()),             // Start with empty vector for score sprites
                     text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)) // Use a new text generator
    {
    }

    /**
     * Increases score by 1 and updates high score if needed. Displays score and high score.
     */
    void update()
    {
        // increase score and update high score if this is the new highest
        score++;
        if (score > high_score)
        {
            high_score = score;
        }

        // Stop displaying previous scores
        score_sprites.clear();

        // Display new scores
        show_number(SCORE_X, SCORE_Y, score);
        show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score);
    }

    /**
     * Displays a number at the given position
     */
    void show_number(int x, int y, int number)
    {
        // Convert number to a string and then display it
        bn::string<MAX_SCORE_CHARS> number_string = bn::to_string<MAX_SCORE_CHARS>(number);
        text_generator.generate(x, y, number_string, score_sprites);
    }

    /**
     * Sets score back to 0. Does NOT reset high score.
     */
    void resetScore()
    {
        score = 0;
    }

    int score;                                                 // current score
    int high_score;                                            // best core
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
    bn::sprite_text_generator text_generator;                  // Text generator for scores
};

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(START_X, START_Y);

    bn::vector<Enemy, MAX_ENEMY> enemies = {};

    // Spawn the first enemy
    enemies.push_back(Enemy(random_x_gen(), random_y_gen()));

    int enemySpawner = 0;

    while (true)
    {
        player.update();

        // For each enemy in the enemies vector, call the update function to add pursuit behavior.
        for (Enemy &enemy : enemies)
        {
            enemy.update(player);
            // Reset the current score and player position if the player collides with enemy
        }

        // For each enemy in the enemies vector, call the update function to add pursuit behavior.
        for (Enemy &enemy : enemies)
        {
            // Reset the current score and player position if the player collides with enemy
            if (enemy.bounding_box.intersects(player.bounding_box))
            {
                scoreDisplay.resetScore();
                player.sprite.set_x(START_X);
                player.sprite.set_y(START_Y);

                if (enemies.size() == 1)
                {
                    enemy.enemy_sprite.set_x(random_x_gen());
                    enemy.enemy_sprite.set_y(random_y_gen());
                    enemySpawner = 0;
                }
                else if (enemies.size() > 1)
                {
                    enemies.clear();
                    enemySpawner = 0;
                    enemies.push_back(Enemy(random_x_gen(), random_y_gen()));
                    enemy.enemy_sprite.set_x(random_x_gen());
                    enemy.enemy_sprite.set_y(random_y_gen());
                }
            }
        }

        if (enemySpawner == 300)
        {
            if (enemies.size() < MAX_ENEMY)
            {
                enemies.push_back(Enemy(random_x_gen(), random_y_gen()));
            }
            enemySpawner = 0;
        }

        // Update the scores and display them
        scoreDisplay.update();
        enemySpawner++;
        bn::core::update();
    }
}