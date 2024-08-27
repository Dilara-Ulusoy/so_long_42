#include "so_long.h"

void load_images(t_game *game)
{
    int img_width;
    int img_height;

    game->img.player_img_1 = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/player.xpm", &img_width, &img_height);
	game->img.player_img_2 = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/player2.xpm", &img_width, &img_height);
	game->img.player_img_3 = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/player3.xpm", &img_width, &img_height);
	game->img.player_img_4 = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/player4.xpm", &img_width, &img_height);
    game->img.exit_img = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/exit.xpm", &img_width, &img_height);
    game->img.collectible_img = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/collectible.xpm", &img_width, &img_height);
    game->img.wall_img = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/wall.xpm", &img_width, &img_height);
    game->img.floor_img = mlx_xpm_file_to_image(game->mlx_ptr, "game_images/floor.xpm", &img_width, &img_height);

    // Eğer görseller yüklenemezse hata mesajı verin
    if (!game->img.player_img_1 || !game->img.player_img_2 || !game->img.player_img_3 || !game->img.player_img_4 || !game->img.exit_img || !game->img.collectible_img || !game->img.wall_img || !game->img.floor_img)
	{
		ft_putstr("Error: Failed to load images.\n");
		exit(1);
	}
}
