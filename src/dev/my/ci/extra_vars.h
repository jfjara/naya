// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins
typedef struct 
{
   signed char x,y;
} POINT;

unsigned char boss = 1;
unsigned char boss_1_lunge = BOSS_1_TIME_LUNGE;;
unsigned char boss_1_counter = 32;
unsigned char boss_action = 0;  // 0: nada 1: embestir adelante, 2: embestir atras 3: girar cabeza
unsigned char boss_action_counter = 60;
unsigned char boss_x = 13;
unsigned char boss_y = 8;
unsigned char boss_screen_buffer[3] = {0};
unsigned char boss_animation = 0;
unsigned char is_lunge = 0;
unsigned char boss_aux_1, boss_aux_2, boss_aux_3, diff_x, diff_y;
unsigned char b_aux = 0;
unsigned char vector_counter = 0;
unsigned char ene_direction = 1; // abajo
unsigned char shoots = 0;
unsigned char max_shoots = 1;
unsigned char total_candies = 0;
unsigned char umbral_points = 0;
unsigned char special_ene = 0;

typedef struct {
    unsigned char boss_x, boss_y;
} BOSS;

unsigned char gbx, gby;

const unsigned char splash_screens [] = { LOGO_BIN, CONTROLS_BIN, DEDICADO_BIN };

POINT boss_vector_path[10] = {
    {0,-2}, {2, -2}, {2, -2}, {2,-2}, {2,0}, 
    {0,2}, {-2, 2}, {-2, 2}, {-2,2}, {-2,0}
};

const unsigned char *extra_enem_cells [] = {
        extra_sprite_17_a, extra_sprite_18_a, extra_sprite_19_a, extra_sprite_20_a,
        extra_sprite_21_a, extra_sprite_22_a, extra_sprite_23_a, extra_sprite_24_a
    };

