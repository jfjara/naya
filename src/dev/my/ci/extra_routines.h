// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

if (slevel == 4 && stage_clear_animation == 0) {
    if (total_candies >= 12) {
        stage_clear_animation = 1;
        timer_on = 0;
        up_live(umbral_points);
    }
}

if (boss == 1) {
    draw_boss_life();
    if (level == 0) {
        play_boss1();
    } else if (level == 1) {
        play_boss2();
    }
    
}

if (animate_dog == 1 && time_animation == TIME_DOG_ANIMATION ) {
    clear_sprites();
    timer_on = 0;
    time_animation--;
}

if (animate_dog == 1) {
    if (time_animation > 1) {
        time_animation--;
        if (time_animation % 7 == 0) {
            if (tile_dog == 29) {
                tile_dog = 30;
            } else {
                tile_dog = 29;
            }
            _x = 12;
            _y = 6;
            _t = tile_dog;
            update_tile();
        }
    } else {
        
        time_animation = TIME_STAGE_CLEAR_ANIMATION;
        animate_dog = 0;
        tile_dog = 29;
        stage_clear_animation = 1;
        PLAY_MUSIC (1);
    }   
}

if (stage_clear_animation == 1) {
    if (time_animation > 1) {
        print_stage_clear();
        time_animation--;
        do_not_move = 1;
    } else {
        stage_clear_animation = 0;
        animate_dog = 0;
        time_animation = TIME_DOG_ANIMATION;
        boss = 0;
        
        if (slevel == 4) {
            slevel = 0;
            level++;
            prepare_level();
        } else {
            slevel++;
        }
        
        n_pant = SCR_INICIO + slevel;
        gpx = PLAYER_INI_X << 4; p_x = gpx << 6;
        gpy = PLAYER_INI_Y << 4; p_y = gpy << 6;

        for (rda = 0; rda < 80; rda++) {
			objects[rda].n_pant = 99; objects[rda].gpit = objects[rda].x = objects[rda].y = 255;
		}
        objects_index = 0;
        player_init();
        if (slevel == 3) {
            // vamos al nivel del boss
            boss = 1;
            n_pant = 0;
            timer_t = 60;
            #include "my/level_boss_screen.h"
            gpy = PLAYER_INI_Y << 4; p_y = gpy << 6 - 8;
        } else if (slevel == 4) {
            n_pant = 1;
            timer_t = 10;
            #include "my/level_bonus_screen.h"
            total_candies = 0;
            draw_candy_level();
            max_shoots = 1;
        } else {
            total_candies = 0;
            p_life = 2;
            max_shoots = 1;
            timer_t = 99;  
            #include "my/level_screen.h"
            total_candies = 0;
            draw_candy_level();
            draw_player_sublives();
        }
        
        timer_on = 1;
        do_not_move = 0;
         
    }
}
