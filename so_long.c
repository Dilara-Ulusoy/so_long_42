
#include "so_long.h"

int main(int argc, char **argv)
{
    if (argc != 2)
      {
          ft_putstr("Usage: ./so_long <map_file>\n");
          return (1);
      }
    t_game    game; // s_game yapı tanımı

    // Start the MLX
    game.mlx_ptr = mlx_init(); // mlx_init starts the MLX library and returns a new mlx_ptr.

    // Load the map
    load_map(&game, argv[1]);
    check_map_validity(&game);
    setup_window(&game);
    game.win = mlx_new_window(game.mlx_ptr, game.window_width, game.window_height, "SO_LONG");

    initialize_player_position(&game);
    initialize_collectibles(&game);
    initialize_moves(&game);

    // image'lerin yuklenmesi
    load_images(&game);

     // Set up key event handling
    mlx_key_hook(game.win, handle_key_press, &game);

    // Haritayı render etme
   render_map(&game);

    // MLX döngüsünü başlatma
    mlx_loop(game.mlx_ptr);

    return (0);
}


