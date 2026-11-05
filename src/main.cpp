#include <bn_core.h>
#include <bn_display.h>

#include "create_bounding_box.h"
#include "Player.h"
#include "Enemy.h"
#include "methods.h"
#include "score_display.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Player start location
static constexpr int START_X = 44;
static constexpr int START_Y = 22;

// Enemy start location
static constexpr int ENEMY_X = 0;
static constexpr int ENEMY_Y = 0;

// Max amount of enemies
static constexpr int MAX_ENEMY = 5;

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