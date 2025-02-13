// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins


//  _x = 5; _y = 0; _t = animate_dog; _n = 5; print_number_wan();
//  _x = 7; _y = 0; _t = _en_life; _n = 5; print_number_wan();
if (n_pant == 0) { //pantalla del boss 1. Preparar el previo
    draw_boss_life();
    play_boss();
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
    }   
}

if (stage_clear_animation == 1) {
    if (time_animation > 1) {
        print_stage_clear();
        time_animation--;
    } else {
        stage_clear_animation = 0;
        animate_dog = 0;
        time_animation = TIME_DOG_ANIMATION;
        slevel++;

        n_pant = SCR_INICIO + slevel;
        gpx = PLAYER_INI_X << 4; p_x = gpx << 6;
        gpy = PLAYER_INI_Y << 4; p_y = gpy << 6;

        for (rda = 0; rda < 80; rda++) {
			objects[rda].n_pant = 99; objects[rda].x = objects[rda].y = 255;
		}
        
        if (slevel == 3) {
            // vamos al nivel del boss
            n_pant = 0;
            timer_t = 60;
        } else if (slevel == 4) {
            n_pant = 1;
            timer_t = 10;
        } else {
            timer_t = 99;
        }
        draw_level_screen();
        timer_on = 1;
        do_not_move = 0;
            
        
    }
}
