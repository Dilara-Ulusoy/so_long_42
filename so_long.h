#ifndef S0_LONG_H
# define S0_LONG_H

# include <math.h> // Matematiksel işlemler için ex
# include "gnl/get_next_line.h"
# include <stdlib.h>        // Genel C fonksiyonları için
# include <unistd.h>        // Yazma ve okuma işlemleri için
# include <fcntl.h>         // Dosya işlemleri için ex: open
# include <stdio.h>         // Hata ayıklama için (normalde projede kullanılmaz)
# include "./minilibx/mlx.h"

# define WIN_WIDTH 768
# define WIN_HEIGHT 576
# define TILE_SIZE 64
# define KEY_CODE_ESC 53
# define KEY_CODE_W 13
# define KEY_CODE_A 0
# define KEY_CODE_S 1
# define KEY_CODE_D 2
# define KEY_CODE_UP 126
# define KEY_CODE_DOWN 125
# define KEY_CODE_LEFT 123
# define KEY_CODE_RIGHT 124

typedef struct	s_img
{
	void		*wall_img;
    void        *floor_img;
    void        *collectible_img;
    void        *exit_img;
    void        *player_img_1;
    void        *player_img_2;
    void        *player_img_3;
    void        *player_img_4;
}				t_img;

/*
 Here is my main struct containing every variables needed by the MLX.
 - mlx_ptr stores the return value of mlx_init
 - win stores the return value of mlx_new_window
 - img will store everything we need for the image part, the struct is described above.
 */
typedef struct	s_game
{
	void		*mlx_ptr;
	void		*win;
    char        **map;
    int     map_width;      // Haritanın genişliği
    int     map_height;     // Haritanın yüksekliği
    int window_width;
    int window_height;
    int player_x;
    int player_y;
    int collectibles;
    int player_count;
    int exit_count;
    int collectible_count;
    int move_count;
	t_img		img;
}				t_game;


void load_images(t_game *game);
void load_map(t_game *game, char *filename);
void ft_putstr(char *str);
void render_map_to_image(t_game *game, void *image);
void render_tile_to_image(t_game *game, char tile, int x, int y, void *image);
void render_map(t_game *game);
int handle_key_press(int keycode, t_game *game);
void initialize_player_position(t_game *game);
void initialize_collectibles(t_game *game);
void initialize_moves(t_game *game);
void setup_window(t_game *game);
void check_map_validity(t_game *game);

void count_elements(t_game *game);
void validate_counts(t_game *game);
void check_map_validity(t_game *game);
void render_player_view_to_direction(t_game *game, int direction);

#endif
