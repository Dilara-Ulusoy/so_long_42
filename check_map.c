#include "so_long.h"

// Function to count specific elements in the map
void count_elements(t_game *game)
{
    game->player_count = 0;
    game->exit_count = 0;
    game->collectible_count = 0;

    int y = 0;
    while (y < game->map_height) {
        int x = 0;
        while (x < game->map_width) {
            if (game->map[y][x] == 'P') {
                game->player_count++;
            }
            else if (game->map[y][x] == 'E') {
                game->exit_count++;
            }
            else if (game->map[y][x] == 'C') {
                game->collectible_count++;
            }
            x++;
        }
        y++;
    }
}


// Function to validate counts of player, exit, and collectibles
void validate_counts(t_game *game)
{
    if (game->player_count != 1) {
        ft_putstr("Error: Player count is not exactly 1.\n");
        exit(1);
    }

    if (game->exit_count != 1) {
        ft_putstr("Error: Exit count is not exactly 1.\n");
        exit(1);
    }

    if (game->collectible_count < 1) {
        ft_putstr("Error: Collectible count is not enough.\n");
        exit(1);
    }
}

// Main function that calls the helper functions
void check_map_validity(t_game *game)
{
	
    // Count the elements in the map
    count_elements(game);

    // Validate the counts
    validate_counts(game);
}
