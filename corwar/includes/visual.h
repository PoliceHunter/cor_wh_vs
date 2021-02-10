//
// Created by Taisha Myrcella on 2/10/21.
//

#ifndef CORWAR_VISUAL_H
# define CORWAR_VISUAL_H
# include "corwar.h"
# include <ncurses.h>
# include <time.h>
# define HEIGHT					(MEM_SIZE / 64 + 4)
# define WIDTH					(64 * 3 + 5)
# define TAB_LEN				4
# define BAR_LENGTH				50
# define MIN_PLAYER_ID			1
# define MAX_PLAYER_ID 4
# define DEFAULT_INDENT			5
# define INDEX(X)		((X) - 1)
# define INDEX_CURSOR(X)		((X) + 5)
# define INDEX_PLAYER(X)		((X) - 5)
# define COLOR_GRAY				8
# define GRAY					9
# define GREEN					10
# define YELLOW					11
# define RED					12
# define CYAN					13
# define GRAY_CURSOR			14
# define GREEN_CURSOR			15
# define YELLOW_CURSOR			16
# define RED_CURSOR				17
# define CYAN_CURSOR			18
# define LIVE_GREEN				19
# define LIVE_YELLOW			20
# define LIVE_RED				21
# define LIVE_CYAN				22

# define ESC					27
# define SPACE					' '
# define SPEED_UP_1				'r'
# define SPEED_UP_10			't'
# define SPEED_UP_100			'y'
# define SPEED_DOWN_1			'e'
# define SPEED_DOWN_10			'w'
# define SPEED_DOWN_100			'q'
# define SPEED_DEFAULT			'd'
# define DISPLAY_HELP			'h'
# define MUSIC					'm'
# define PASS_ONE_CYCLE			's'

# define CYCLE_TO_WAIT			50
# define DEFAULT_SPEED			50

int visual(t_cor *cor);

static int g_colors_players[15] = {
		COLOR_PAIR(GRAY),
		COLOR_PAIR(GREEN),
		COLOR_PAIR(YELLOW),
		COLOR_PAIR(RED),
		COLOR_PAIR(CYAN),
		COLOR_PAIR(GRAY_CURSOR),
		COLOR_PAIR(GREEN_CURSOR),
		COLOR_PAIR(YELLOW_CURSOR),
		COLOR_PAIR(RED_CURSOR),
		COLOR_PAIR(CYAN_CURSOR)
};

typedef struct		s_attr
{
	int32_t			index;
	ssize_t			wait_cycles_store;
	ssize_t			wait_cycles_live;
	t_player		*player_live;
}					t_attr;

typedef struct		s_vs
{
	int			is_running;
	int				speed;
	WINDOW			*win_arena;
	WINDOW			*win_info;
	WINDOW			*win_help;
	int				cursor_pos;
	t_attr			map[MEM_SIZE];
	int				button;
	clock_t			time;
	char			aff_symbol;
	t_player		*aff_player;
	int				sounds;
	int 			display_help;
}					t_vs;

#endif //CORWAR_VISUAL_H
