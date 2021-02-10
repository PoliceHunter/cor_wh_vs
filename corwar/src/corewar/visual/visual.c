//
// Created by Taisha Myrcella on 2/10/21.
//
#include "../../includes/corwar.h"
#include "../../includes/visual.h"

void	clear_name(char *name)
{
	size_t i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '\n' || name[i] == '\t' || name[i] == '\v')
			name[i] = ' ';
		i++;
	}
}

void		init_colors(void)
{
	init_color(COLOR_GRAY, 355, 355, 355);
	init_pair(GRAY, COLOR_GRAY, 0);
	init_pair(GREEN, COLOR_GREEN, 0);
	init_pair(YELLOW, COLOR_YELLOW, 0);
	init_pair(RED, COLOR_RED, 0);
	init_pair(CYAN, COLOR_CYAN, 0);
	init_pair(GRAY_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW_CURSOR, COLOR_BLACK, COLOR_YELLOW);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
	init_pair(CYAN_CURSOR, COLOR_BLACK, COLOR_CYAN);
	init_pair(LIVE_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(LIVE_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(LIVE_RED, COLOR_WHITE, COLOR_RED);
	init_pair(LIVE_CYAN, COLOR_WHITE, COLOR_CYAN);
}

static void	fill_map(t_cor *vm, int32_t pc, int32_t len, int32_t player_id)
{
	int32_t i;
	int32_t value;

	i = pc;
	value = ((player_id - 1) % MAX_PLAYER_ID) + 1;
	while (i < len + pc)
	{
		vm->vs->map[i].index = value;
		i++;
	}
}

static void	init_map(t_cor *vm)
{
	int32_t	pc;
	int32_t	id;

	pc = 0;
	id = 1;
	while (id <= vm->count_players)
	{
		fill_map(vm, pc, vm->player[INDEX(id)].code_size, id);
		pc += MEM_SIZE / vm->count_players;
		id++;
	}
}

static int	get_live_color(t_player *player)
{
	int32_t index;

	index = ((player->id - 1) % MAX_PLAYER_ID) + 1;
	if (index == MIN_PLAYER_ID)
		return (COLOR_PAIR(LIVE_GREEN) | A_BOLD);
	else if (index == MIN_PLAYER_ID + 1)
		return (COLOR_PAIR(LIVE_YELLOW) | A_BOLD);
	else if (index == MIN_PLAYER_ID + 2)
		return (COLOR_PAIR(LIVE_RED) | A_BOLD);
	else
		return (COLOR_PAIR(LIVE_CYAN) | A_BOLD);
}

int			get_attribute(t_cor *vm, t_attr *attribute, ssize_t cycles)
{
	if (cycles != vm->cycle
		&& vm->cycles_to_die > 0
		&& attribute->wait_cycles_live > 0)
		attribute->wait_cycles_live--;
	if (cycles != vm->cycle
		&& vm->cycles_to_die > 0
		&& attribute->wait_cycles_store > 0)
		attribute->wait_cycles_store--;
	if (attribute->wait_cycles_live)
		return (get_live_color(attribute->player_live));
	else if (attribute->wait_cycles_store)
		return (g_colors_players[attribute->index] | A_BOLD);
	else
		return (g_colors_players[attribute->index]);
}

static void	draw_arena(t_cor *vm)
{
	static ssize_t	cycles = 0;
	int				i;
	int				j;
	int				attribute;

	i = 0;
	while (i < 64)
	{
		j = 0;
		wmove(vm->vs->win_arena, i + 2, 5);
		while (j < 64)
		{
			attribute = get_attribute(vm, &vm->vs->map[i * 64 + j], cycles);
			wattron(vm->vs->win_arena, attribute);
			wprintw(vm->vs->win_arena, "%.2x", vm->map[i * 64 + j]);
			wattroff(vm->vs->win_arena, attribute);
			waddch(vm->vs->win_arena, ' ');
			j++;
		}
		wprintw(vm->vs->win_arena, "\n");
		i++;
	}
	cycles = vm->cycle;
}

static void	draw_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(GRAY));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(GRAY));
}

static void	draw_players(t_cor *vm)
{
	int32_t i;

	i = 0;
	vm->vs->cursor_pos += 1;
	while (i < vm->count_players)
	{
		mvwprintw(vm->vs->win_info,
				  vm->vs->cursor_pos += 2,
				  DEFAULT_INDENT,
				  "Player -%d : ", vm->player[i].id);
		wattron(vm->vs->win_info, g_colors_players[vm->player[i].id]);
		wprintw(vm->vs->win_info, "%.38s", vm->player[i].name);
		wattroff(vm->vs->win_info, g_colors_players[vm->player[i].id]);
		i++;
	}
}

static void	draw_game_params(t_cor *vm)
{
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos += 3,
			  DEFAULT_INDENT,
			  "%-32s %zd", "Cycle to die :", vm->cycles_to_die);
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT,
			  "%-32s %zu", "Cycle delta :", CYCLE_DELTA);
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT,
			  "%-32s %.6zu/%zu", "Lives :",
			  vm->count_lives, NBR_LIVE);
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT,
			  "%-32s %.6zu", "Cycles to check :", (vm->cycles_to_die > 0) ?
												  vm->cycles_to_die - vm->cycles_after_check : 0);
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT,
			  "%-32s %.6zu/%zu", "Checks :",
			  vm->count_check, MAX_CHECKS);
}

static void	draw_aff(t_cor *vm)
{
	int32_t index;

	index = ((vm->vs->aff_player->id - 1) % MAX_PLAYER_ID) + 1;
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT,
			  "%-32s ", "Aff value :");
	wattron(vm->vs->win_info, g_colors_players[index]);
	wprintw(vm->vs->win_info, "%d", vm->vs->aff_symbol);
	if (ft_isprint(vm->vs->aff_symbol))
		wprintw(vm->vs->win_info, " '%c'", vm->vs->aff_symbol);
	wattroff(vm->vs->win_info, g_colors_players[index]);
}

static void	draw_winner(t_cor *vm)
{
	vm->vs->cursor_pos = (vm->vs->cursor_pos + HEIGHT - 3) / 2;
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT,
			  "The winner is ");
	wattron(vm->vs->win_info, g_colors_players[vm->player[vm->last_live_player].id]);
	wprintw(vm->vs->win_info, "%.36s", vm->player[vm->last_live_player].name);
	wattroff(vm->vs->win_info, g_colors_players[vm->player[vm->last_live_player].id]);
}

void	draw_exec_status(t_cor *vm)
{
	vm->vs->cursor_pos = 2;
	if (vm->vs->is_running)
	{
		wattron(vm->vs->win_info, COLOR_PAIR(GREEN));
		mvwprintw(vm->vs->win_info,
				  vm->vs->cursor_pos,
				  DEFAULT_INDENT,
				  "%-10s", "RUNNING");
		wattroff(vm->vs->win_info, COLOR_PAIR(GREEN));
	}
	else
	{
		wattron(vm->vs->win_info, COLOR_PAIR(RED));
		mvwprintw(vm->vs->win_info,
				  vm->vs->cursor_pos,
				  DEFAULT_INDENT,
				  "%-10s", (vm->count_cursors) ? "PAUSED" : "STOPPED");
		wattroff(vm->vs->win_info, COLOR_PAIR(RED));
	}
}

static void	draw_main_commands(t_cor *vm)
{
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT + TAB_LEN * 10,
			  "Start/Pause - 'SPACE'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 2,
			  DEFAULT_INDENT + TAB_LEN * 10,
			  "Exit - 'ESC'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 4,
			  DEFAULT_INDENT + TAB_LEN * 10,
			  "Pass one cycle - 'S'");
}

static void	draw_additional_commands(t_cor *vm)
{
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT + TAB_LEN * 18,
			  "Default speed - 'D'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 2,
			  DEFAULT_INDENT + TAB_LEN * 18,
			  "Sounds ON/OFF - 'M'");
}

static void	draw_speed_up_commands(t_cor *vm)
{
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT + TAB_LEN * 27,
			  "Speed UP");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 2,
			  DEFAULT_INDENT + TAB_LEN * 27,
			  "* By 1 - 'R'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 4,
			  DEFAULT_INDENT + TAB_LEN * 27,
			  "* By 10 - 'T'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 6,
			  DEFAULT_INDENT + TAB_LEN * 27,
			  "* By 100 - 'Y'");
}

static void	draw_speed_down_commands(t_cor *vm)
{
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT + TAB_LEN * 33,
			  "Speed DOWN");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 2,
			  DEFAULT_INDENT + TAB_LEN * 33,
			  "* By 1 - 'E'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 4,
			  DEFAULT_INDENT + TAB_LEN * 33,
			  "* By 10 - 'W'");
	mvwprintw(vm->vs->win_help,
			  vm->vs->cursor_pos + 6,
			  DEFAULT_INDENT + TAB_LEN * 33,
			  "* By 100 - 'Q'");
}

void		draw_help(t_cor *vm)
{
	wattron(vm->vs->win_help, A_BOLD);
	vm->vs->cursor_pos = 1;
	draw_main_commands(vm);
	draw_additional_commands(vm);
	draw_speed_up_commands(vm);
	draw_speed_down_commands(vm);
	wattroff(vm->vs->win_help, A_BOLD);
}

void	draw_sounds_status(t_cor *vm)
{
	vm->vs->cursor_pos = HEIGHT - 5;
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT,
			  "Sounds are ");
	wprintw(vm->vs->win_info, "%-3s", (vm->vs->sounds) ? "ON" : "OFF");
}

void	draw_help_status(t_cor *vm)
{
	vm->vs->cursor_pos = HEIGHT - 3;
	mvwprintw(vm->vs->win_info,
			  vm->vs->cursor_pos,
			  DEFAULT_INDENT,
			  "Press 'H' to %s help",
			  (vm->vs->display_help) ? "hide" : "show");
	if (!vm->vs->display_help)
	{
		delwin(vm->vs->win_help);
		vm->vs->win_help = newwin(HEIGHT / 5, WIDTH, HEIGHT + 2, 2);
	}
	else
		draw_help(vm);
}

static size_t	calc_bar_length(size_t lives, size_t sum_lives)
{
	size_t result;

	result = (lives * BAR_LENGTH) / sum_lives;
	if ((lives * BAR_LENGTH) % sum_lives >= sum_lives / 2)
		result++;
	return (result);
}

static void		draw_empty_bar(t_cor *vm)
{
	int i;

	i = 0;
	wattron(vm->vs->win_info, COLOR_PAIR(GRAY));
	while (i < BAR_LENGTH)
	{
		mvwprintw(vm->vs->win_info,
				  vm->vs->cursor_pos + 1,
				  DEFAULT_INDENT + i,
				  "-");
		i++;
	}
	wattroff(vm->vs->win_info, COLOR_PAIR(GRAY));
}

static void		draw_bar(t_cor *vm, size_t len, size_t pos, int index)
{
	size_t i;

	i = pos;
	wattron(vm->vs->win_info, g_colors_players[index + 1]);
	while (i <= pos + len && i < BAR_LENGTH)
	{
		mvwprintw(vm->vs->win_info,
				  vm->vs->cursor_pos + 1,
				  (int)(DEFAULT_INDENT + i),
				  "-");
		i++;
	}
	wattroff(vm->vs->win_info, g_colors_players[index + 1]);
}

void			draw_lives_bar(t_cor *vm, t_bool current)
{
	int		i;
	size_t	sum_lives;
	size_t	pos;
	size_t	len;

	i = 0;
	sum_lives = 0;
	while (i < vm->count_players)
		if (current)
			sum_lives += vm->player[i++].current_lives_num;
		else
			sum_lives += vm->player[i++].previous_lives_num;
	i = 0;
	pos = 0;
	if (!sum_lives)
		draw_empty_bar(vm);
	else
		while (i < vm->count_players)
		{
			len = calc_bar_length((current) ? vm->player[i].current_lives_num
											: vm->player[i].previous_lives_num, sum_lives);
			draw_bar(vm, len, pos, i++);
			pos += len;
		}
	vm->vs->cursor_pos++;
}

void		draw_info(t_cor *vm)
{
	wattron(vm->vs->win_info, A_BOLD);
	draw_exec_status(vm);
	mvwprintw(vm->vs->win_info, vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT, "Cycles/second : %d", vm->vs->speed);
	mvwprintw(vm->vs->win_info, vm->vs->cursor_pos += 3,
			  DEFAULT_INDENT, "Cycle : %zd", vm->cycle);
	mvwprintw(vm->vs->win_info, vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT, "Cursors : %zu", vm->count_cursors);
	draw_players(vm);
	mvwprintw(vm->vs->win_info, vm->vs->cursor_pos += 3,
			  DEFAULT_INDENT, "Bar of lives for current period :");
	draw_lives_bar(vm, true);
	mvwprintw(vm->vs->win_info, vm->vs->cursor_pos += 2,
			  DEFAULT_INDENT, "Bar of lives for previous period :");
	draw_lives_bar(vm, false);
	draw_game_params(vm);
	if (vm->vs->aff_player)
		draw_aff(vm);
	if (!vm->count_cursors)
		draw_winner(vm);
	draw_sounds_status(vm);
	draw_help_status(vm);
	wattroff(vm->vs->win_info, A_BOLD);
}

void		draw(t_cor *vm)
{
	werase(vm->vs->win_arena);
	werase(vm->vs->win_info);
	werase(vm->vs->win_help);
	draw_arena(vm);
	draw_info(vm);
	draw_border(vm->vs->win_arena);
	wrefresh(vm->vs->win_info);
	wrefresh(vm->vs->win_arena);
	wrefresh(vm->vs->win_help);
}

void	clear_cursor(t_cor *vm, t_process *cursor)
{
	if (vm->vs->map[cursor->pos].index >= INDEX_CURSOR(0)
		&& vm->vs->map[cursor->pos].index <= INDEX_CURSOR(MAX_PLAYER_ID))
		vm->vs->map[cursor->pos].index =
				INDEX_PLAYER(vm->vs->map[cursor->pos].index);
}

void	draw_cursor(t_cor *vm, t_process *cursor)
{
	if (vm->vs->map[cursor->pos].index >= 0
		&& vm->vs->map[cursor->pos].index <= MAX_PLAYER_ID)
		vm->vs->map[cursor->pos].index =
				INDEX_CURSOR(vm->vs->map[cursor->pos].index);
}

static void	init_cursors(t_cor *vm)
{
	t_process *proc;
	int			index;

	index = -1;
	while (++index != vm->process.size - 1)
	{
		proc = get_from_vec(&vm->process, index);
		draw_cursor(vm, proc);
	}
}

void		configure_vs(t_cor *cor)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_colors();
	init_map(cor);
	cor->vs->win_arena = newwin(HEIGHT, WIDTH + 4, 1, 2);
	cor->vs->win_info = newwin(HEIGHT, WIDTH / 4 + 10, 1, WIDTH + 6);
	cor->vs->win_help = newwin(HEIGHT / 5, WIDTH, HEIGHT + 2, 2);
	init_cursors(cor);
}

void	play_victory_sound(t_cor *vm)
{
	if (vm->vs->sounds)
	{
		system("pkill afplay");
		system("afplay sounds/victory.mp3 &> /dev/null &");
	}
}

void	play_death_sound(t_cor *vm)
{
	if (vm->vs->sounds)
	{
		system("pkill afplay");
		system("afplay sounds/blaster.mp3 &> /dev/null &");
	}
}

static void	exec_cycle_vs(t_cor *vm)
{
	size_t cursors_num;

	if (vm->count_players)
	{
		process_game_logic(vm);
		if (vm->cycles_to_die == vm->cycles_after_check
			|| vm->cycles_to_die <= 0)
		{
			cursors_num = vm->count_players;
			make_check(vm);
			if (cursors_num != vm->count_players && vm->count_cursors)
				play_death_sound(vm);
		}
		if (!vm->count_cursors)
		{
			play_victory_sound(vm);
			vm->vs->is_running = false;
		}
	}
}

static void	handle_buttons(t_cor *vm)
{
	if (vm->vs->button == SPACE)
		vm->vs->is_running = !(vm->vs->is_running);
	else if (vm->vs->button == MUSIC)
		vm->vs->sounds = !(vm->vs->sounds);
	else if (vm->vs->button == DISPLAY_HELP)
		vm->vs->display_help = !(vm->vs->display_help);
	else if (vm->vs->button == SPEED_UP_1)
		vm->vs->speed++;
	else if (vm->vs->button == SPEED_UP_10)
		vm->vs->speed += 10;
	else if (vm->vs->button == SPEED_UP_100)
		vm->vs->speed += 100;
	else if (vm->vs->button == SPEED_DOWN_1)
		vm->vs->speed--;
	else if (vm->vs->button == SPEED_DOWN_10)
		vm->vs->speed -= 10;
	else if (vm->vs->button == SPEED_DOWN_100)
		vm->vs->speed -= 100;
	else if (vm->vs->button == SPEED_DEFAULT)
		vm->vs->speed = DEFAULT_SPEED;
	vm->vs->is_running = (!vm->count_cursors) ? false : vm->vs->is_running;
	vm->vs->speed = (vm->vs->speed < 1) ? 1 : vm->vs->speed;
	vm->vs->speed = (vm->vs->speed > 1000) ? 1000 : vm->vs->speed;
}

clock_t	calc_time_delay(t_cor *vm)
{
	return (vm->vs->time + CLOCKS_PER_SEC / vm->vs->speed);
}

void	free_vs(t_vs **vs)
{
	delwin((*vs)->win_info);
	delwin((*vs)->win_arena);
	delwin((*vs)->win_help);
	ft_memdel((void *)vs);
	endwin();
}

int visual(t_cor *cor)
{
	int32_t i;

	i = 0;
	while (i < cor->count_players)
		clear_name(cor->player[i++].name);
	configure_vs(cor);
	while ((cor->vs->button = getch()) != ESC)
	{
		handle_buttons(cor);
		if (cor->vs->button == PASS_ONE_CYCLE)
			exec_cycle_vs(cor);
		else if (cor->vs->is_running && (clock() >= calc_time_delay(cor)))
		{
			cor->vs->time = clock();
			exec_cycle_vs(cor);
		}
		draw(cor);
	}
	free_vs(&(cor->vs));
	return 1;
}