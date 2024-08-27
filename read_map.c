
#include "so_long.h"

void ft_putstr(char *str)
{
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
}

void setup_window(t_game *game) {
    // Calculate dynamic window size based on map dimensions and tile size
    game->window_width = (game->map_width * TILE_SIZE) - TILE_SIZE;
    game->window_height = game->map_height * TILE_SIZE;

    // Setup window using a library like SDL or any other you use.
    // Example (pseudocode): create_window(game->window_width, game->window_height);
}

void load_map(t_game *game, char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int y = 0;

    if (fd < 0)
    {
        ft_putstr("Error\nFailed to open map file.");
        exit(1);
    }

    // Reset game map height and width
    game->map_height = 0;
    game->map_width = 0;

    // First pass: Determine map dimensions
    while ((line = get_next_line(fd)) != NULL)
    {
        int line_length = ft_strlen(line);
        if (game->map_width == 0)
        {
            game->map_width = line_length; // Set the width based on the first line
        }
        else if (line_length != game->map_width)
        {
            ft_putstr("Error\nInconsistent map width.\n");
            free(line);
            close(fd);
            exit(1);
        }
        game->map_height++;
        free(line);
    }

    // Allocate memory for the map
    game->map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!game->map)
    {
        ft_putstr("Error\nMemory allocation failed.");
        close(fd);
        exit(1);
    }

    // Re-open the file for a second pass to actually load the map
    close(fd);
    fd = open(filename, O_RDONLY);
    y = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        game->map[y] = line;
        y++;
    }
    game->map[y] = NULL;
    close(fd);

    // Print out the loaded map for verification
    /*
    for (int i = 0; i < game->map_height; i++)
    {
        ft_putstr("Map Line: ");
        ft_putstr(game->map[i]);
        ft_putstr("\n");
    }
    */
}

void render_tile(t_game *game, char tile, int x, int y)
{
    if (tile == '0')
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.floor_img, x * TILE_SIZE, y * TILE_SIZE);
    else if (tile == '1')
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.wall_img, x * TILE_SIZE, y * TILE_SIZE);
    else if (tile == 'P')
    {
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.floor_img, x * TILE_SIZE, y * TILE_SIZE);
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.player_img_1, x * TILE_SIZE, y * TILE_SIZE);
    }
    else if (tile == 'E')
    {
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.floor_img, x * TILE_SIZE, y * TILE_SIZE);
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.exit_img, x * TILE_SIZE, y * TILE_SIZE);
    }
    else if (tile == 'C')
    {
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.floor_img, x * TILE_SIZE, y * TILE_SIZE);
        mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.collectible_img, x * TILE_SIZE, y * TILE_SIZE);
    }
    else
    {
        ft_putstr("Unknown tile detected\n");
        exit(1);
    }
}


// Function to render the map to the window
void render_map(t_game *game)
{
    int x; // x coordinate
    int y; // y coordinate

    if (!game->map) {
        ft_putstr("Error: Map is not loaded.\n");
        return;
    }
    y = 0;
    while (y < game->map_height) {
        x = 0;
        while (x < game->map_width) {
            char tile = game->map[y][x];

            if (tile == '\n') {
                x++;
                continue;
            }
            //log_tile_rendering(tile, x, y);
            render_tile(game, tile, x, y);
            x++;
        }
        y++;
    }
}


void initialize_player_position(t_game *game)
{
    int y = 0;
    while (y < game->map_height) {
        int x = 0;
        while (x < game->map_width) {
            if (game->map[y][x] == 'P') {
                game->player_x = x;
                game->player_y = y;
                return; // Exit after finding the player's initial position
            }
            x++;
        }
        y++;
    }
    // If 'P' is not found in the map, handle the error
    ft_putstr("Error: Player start position not found in map.\n");
    exit(1);
}


void initialize_collectibles(t_game *game)
{
    game->collectibles = 0; // Initialize the collectibles count to 0

    int y = 0;
    while (y < game->map_height) {
        int x = 0;
        while (x < game->map_width) {
            if (game->map[y][x] == 'C') {
                game->collectibles++;
            }
            x++; // Move to the next column
        }
        y++; // Move to the next row
    }
}

void initialize_moves(t_game *game)
{
    game->move_count = 0;
}



