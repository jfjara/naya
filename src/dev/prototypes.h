// MTE MK1 (la Churrera) v5.10
// Copyleft 2010-2014, 2020-2023 by the Mojon Twins

// Autodefs

#if defined ENABLE_ORTHOSHOOTERS
	#define ENABLE_SIMPLE_COCOS
#endif

#ifdef MODE_128K
	#ifdef USE_ARKOS_PLAYER
		#define PLAY_MUSIC arkos_play_music
		#define PLAY_SOUND arkos_play_sound
		#define STOP_SOUND arkos_stop_sound
	#else
		#define PLAY_MUSIC wyz_play_music
		#define PLAY_SOUND wyz_play_sound
		#define STOP_SOUND wyz_stop_sound
	#endif
#endif

// Engine

// breakable.h
void break_wall (void);

// bullets.h
void bullets_init (void);
void bullets_update (void);
void bullets_fire (unsigned char who);
void bullets_move (void);

// enengine.h
void enems_init (void);
void enems_pursuers_init (void);
void enems_draw_current (void);
void enems_load (void);
void enems_kill (void);
void enems_move (void);
void play_boss1();
void play_boss2();
void move_boss(signed char increase_x, signed char increase_y, unsigned char tile, unsigned char offset);
void lunge(unsigned char increase);
void circle_movement();

// general.h
unsigned char collide (void);
unsigned char cm_two_points (void);
unsigned char rand (void);
unsigned int abs (int n);
void step (void);
void cortina (void);

// hotspots.h
void hotspots_init (void);
void hotspots_do (void);

// player.h
void player_init (void);
void player_calc_bounding_box (void);
unsigned char player_move (void);
void player_deplete (void);
void player_kill (unsigned char sound);

// simple_cocos.h
void simple_coco_init (void);
void simple_coco_shoot (void);
void simple_coco_update (void);

// Main

// 128k.h
void SetRAMBank(void);

// aplib.h
void get_resource (unsigned char n, unsigned int destination);
void unpack (unsigned int address, unsigned int destination);

// beeper.h
void beep_fx (unsigned char n);

// engine.h
void prepare_level (void);
void game_ending (void);
void game_over (void);
void time_over (void);
void pause_screen (void);
signed int addsign (signed int n, signed int value);
void espera_activa (int espera);
void locks_init (void);
char player_hidden (void);
void run_fire_script (void);
void process_tile (void);
void draw_scr_background (void);
void draw_scr_hotspots_locks (void);
void draw_scr (void);
void select_joyfunc (void);
unsigned char mons_col_sc_x (void);	
unsigned char mons_col_sc_y (void);
unsigned char distance (void);
int limit (int val, int min, int max);

// pantallas.h
void blackout (void);

// printer.h
void print_number_wan (void);
unsigned char attr (unsigned char x, unsigned char y);
unsigned char qtile (unsigned char x, unsigned char y);
void draw_coloured_tile (void);
void invalidate_tile (void);
void invalidate_viewport (void);
void draw_invalidate_coloured_tile_gamearea (void);
void draw_coloured_tile_gamearea (void);
void draw_decorations (void);
void update_tile (void);
void print_number2 (void);
void draw_objs ();
void print_str (void);
void blackout_area (void);
void clear_sprites (void);
void animate_tiles(unsigned char doble_speed);
void print_stage_clear(void);
void draw_boss_life(void);
void draw_candy_level(void);
void restart_level(void);
void draw_player_lives(void);
void move_boss(signed char increase_x, signed char increase_y, unsigned char tile, unsigned char offset);
void start_dead(void);
void draw_player_sublives(void);
void print_points(void) ;
void clear_gamezone() ;
void up_live(unsigned char flag);

// savegame.h
void mem_save (void);
void mem_load (void);
void tape_save (void);// TODO!
void tape_load (void);// TODO!
void sg_submenu (void);

// tilanim.h
void tilanims_add (void);
void tilanims_do (void);
void tilanims_reset (void);

//objects
void save_object(void);
void get_object(unsigned int p);

#ifdef MODE_128K
// wyzplayer.h / arcos_player.h
void ISR (void);
void INIT_PLAYER (void);
void PLAY_SOUND (unsigned char fx_number);
void PLAY_MUSIC (unsigned char song_number);
void STOP_SOUND (void);
#endif
