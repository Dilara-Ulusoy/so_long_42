#include "so_long.h"

int handle_key_press(int keycode, t_game *game)
{
    int new_x = game->player_x;
    int new_y = game->player_y;

    //printf("Current position: (%d, %d)\n", game->player_x, game->player_y);

    if (keycode == KEY_CODE_ESC)
    {
        mlx_destroy_window(game->mlx_ptr, game->win);
        exit(0);
    }
    else if (keycode == KEY_CODE_W || keycode == KEY_CODE_UP)
        new_y -= 1; // Move up
    else if (keycode == KEY_CODE_A || keycode == KEY_CODE_LEFT)
        new_x -= 1; // Move left
    else if (keycode == KEY_CODE_S || keycode == KEY_CODE_DOWN)
        new_y += 1; // Move down
    else if (keycode == KEY_CODE_D || keycode == KEY_CODE_RIGHT)
        new_x += 1; // Move right

    // Log the new calculated position
    //printf("Calculated new position: (%d, %d)\n", new_x, new_y);

    // Ensure new_x and new_y are within valid map boundaries
    if (new_x >= 0 && new_x < game->map_width && new_y >= 0 && new_y < game->map_height)
    {
        if(game->map[new_y][new_x] == '0' || game->map[new_y][new_x] == 'C' || game->map[new_y][new_x] == 'E')
        {
            game->move_count++;
            printf("Move: %d\n", game->move_count);
        }

        if (game->map[new_y][new_x] != '1') // Check for wall collision
        {
            // Check if the player is moving to a collectible
            if (game->map[new_y][new_x] == 'C')
            {
                game->collectibles--; // Decrease the number of remaining collectibles
                printf("Collected a collectible. Remaining: %d\n", game->collectibles);
            }

            // Check if the player is moving to the exit
            if (game->map[new_y][new_x] == 'E')
            {
                if (game->collectibles == 0) // Check if all collectibles are collected
                {
                    printf("Player reached the exit. All collectibles collected!\n");
                    mlx_destroy_window(game->mlx_ptr, game->win);
                    exit(0); // Exit the game
                }
                else
                {
                    printf("Player reached the exit but hasn't collected all items.\n");
                }
            }

            // Update the map
            if(game->map[game->player_y][game->player_x] == 'E')
            {
                game->map[game->player_y][game->player_x] = 'E';
            }
            else
            {
                game->map[game->player_y][game->player_x] = '0';
            }

            // Update player position
            game->player_x = new_x;
            game->player_y = new_y;

            if (game->map[new_y][new_x] == 'E')
            {
                // If the new position is the exit, keep the exit on the map
                game->map[new_y][new_x] = 'E';
            }
            else
            {
                // Otherwise, move player to new position
                game->map[new_y][new_x] = 'P';
            }
        }
        else
        {
            printf("Collision with wall at (%d, %d)\n", new_x, new_y);
        }
        render_player_view_to_direction(game, keycode);
    }
    else
    {
        printf("New position out of bounds: (%d, %d)\n", new_x, new_y);
    }

    // Redraw the map
    render_map(game);
    return 0;
}

void render_player_view_to_direction(t_game *game, int direction)
{
    if (direction == KEY_CODE_UP || direction == KEY_CODE_W)
    {
        game->img.player_img_1 = game->img.player_img_2;
    }
    else if (direction == KEY_CODE_DOWN || direction == KEY_CODE_S)
    {
        game->img.player_img_1 = game->img.player_img_1;
    }
    else if (direction == KEY_CODE_LEFT || direction == KEY_CODE_A)
    {
        game->img.player_img_1 = game->img.player_img_3;
    }
    else if (direction == KEY_CODE_RIGHT || direction == KEY_CODE_D)
    {
        game->img.player_img_1 = game->img.player_img_4;
    }
}


