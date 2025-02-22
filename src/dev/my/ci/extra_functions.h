// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins 39 40 41

void draw_boss(unsigned char t1, unsigned char t2, unsigned char t3) {
    _x = boss_x;_y = boss_y;    _t = t1;draw_invalidate_coloured_tile_gamearea ();
    _x = boss_x;_y = boss_y - 1;_t = t2;draw_invalidate_coloured_tile_gamearea ();
    _x = boss_x;_y = boss_y - 2;_t = t3;draw_invalidate_coloured_tile_gamearea ();
}

void move_boss(signed char increase_x, signed char increase_y, unsigned char tile, unsigned char offset) {

    draw_boss(boss_screen_buffer[0], boss_screen_buffer[1], boss_screen_buffer[2]);

    boss_x = boss_x + increase_x;
    boss_y = boss_y + increase_y;

    boss_screen_buffer[0] = qtile(boss_x, boss_y);
    boss_screen_buffer[1] = qtile(boss_x, boss_y - 1);
    boss_screen_buffer[2] = qtile(boss_x, boss_y - 2); 

    draw_boss(tile + offset + 2, tile + offset + 1, tile);

    if (p_tx == boss_x && (p_ty == boss_y || p_ty == boss_y - 1 || p_ty == boss_y - 2) && p_estado == EST_NORMAL) {
        p_killme = 1;
    }
    
}


void circle_movement() {
    _en_x+=boss_vector_path[vector_counter].x;
    _en_y+=boss_vector_path[vector_counter].y;
    vector_counter++;
}

void lunge(unsigned char increase) {
    if (boss_action_counter % 5 == 0) { 
        if (boss_animation == 0) {
            boss_animation = 1;
            move_boss(increase, 0, 39, 0);
        } else {
            boss_animation = 0;
            move_boss(increase, 0, 39, 2);
        }
    } 
    boss_action_counter--;
}

void play_boss() {

    //tipo de boss

    if (boss_action == 0) {
        boss_1_lunge--;
    }
    if (boss_action == 0 && boss_1_lunge == 0) {
        boss_action = 1;
        boss_action_counter = 60;
        boss_x = 13;
        boss_y = 8;
    }
    
    //acciones
    if (boss_action == 1) {
        //quitar la cabeza sprite
        is_lunge = 1;
        lunge(-1);
    } else if (boss_action == 2) {
        lunge(1);
    }

    // cambio de accion
    if (boss_action == 1 && boss_action_counter == 0) {
        boss_action = 2;
        boss_action_counter = 60;
    } else if (boss_action == 2 && boss_action_counter == 0) {
        boss_action = 3;
        is_lunge = 0;
        //borrar la cabeza de tile

        _x = boss_x;_y = boss_y - 2;_t = 0;draw_invalidate_coloured_tile_gamearea ();
        boss_1_counter = 80;
        boss_1_lunge = BOSS_1_TIME_LUNGE;
        boss_screen_buffer[0] = boss_screen_buffer[1] = boss_screen_buffer[2] = 0;
        vector_counter = 0;
    } else if (boss_action == 10) { //muerte
        _x = boss_x;_y = boss_y;    _t = 44;update_tile ();
        _x = boss_x;_y = boss_y - 1;_t = 44;update_tile ();
        boss_1_counter--;
        if (boss_1_counter == 0) {
            boss_action = 99;
            _x = boss_x;_y = boss_y;    _t = 0;update_tile ();
            _x = boss_x;_y = boss_y - 1;_t = 0;update_tile ();
            stage_clear_animation = 1;
        }
    }   
    
   
}

void draw_sub_boss_life() {
    if (_en_life_boss == 0) {
        _x = 31; _y = 21 - _en_life_boss; _t = 5; _gp_gen =  (unsigned char *)("$"); print_str ();
    } else {
        _x = 31; _y = 21 - _en_life_boss; _t = 5; _gp_gen =  (unsigned char *)("!"); print_str ();
    }
    
}

void draw_candy_level() {
    if (total_candies < 20) {
        for (rda = 0; rda <= 20; rda++) {
            if (rda < total_candies) {
                if (rda == 0) {
                    _x = 0; _y = 21; _t = 3; _gp_gen =  (unsigned char *)("%"); print_str ();
               } else {
                   _x = 0; _y = 21 - rda; _t = 3; _gp_gen =  (unsigned char *)("\""); print_str ();
               }
            } else {
                if (rda == 0) {
                    _x = 0; _y = 21; _t = 3; _gp_gen =  (unsigned char *)("$"); print_str ();
               } else {
                   _x = 0; _y = 21 - rda; _t = 3; _gp_gen =  (unsigned char *)("!"); print_str ();
               }
            }
            
        }
    }
}

void draw_boss_life(void) {
    for (rda = 0; rda < _en_life_boss; rda++) {
        if (rda == 0) {
             _x = 31; _y = 21; _t = 5; _gp_gen =  (unsigned char *)("%"); print_str ();
        } else {
            _x = 31; _y = 21 - rda; _t = 5; _gp_gen =  (unsigned char *)("\""); print_str ();
        }
    }
}

void start_dead(void) {
    fire_count_animation = 48;
    dead_animation = 1;
    tick_frame = 0;
    do_not_move = 1;
    PLAY_MUSIC(11);
}

void restart_level(void) {
    if (n_pant != 0) {
        n_pant = SCR_INICIO + slevel;
    }
    
    gpx = PLAYER_INI_X << 4; p_x = gpx << 6;
    gpy = PLAYER_INI_Y << 4; p_y = gpy << 6;
    if (n_pant == 0) {
        timer_t = 60;
    } else timer_t = 99;
    timer_on = 1;
    do_not_move = 0;

    //todo esto deberia de ir en una funcion antes de comenzar la pelea con el boss
    
    boss_action = 0;
    boss_1_lunge = BOSS_1_TIME_LUNGE;
    boss_action_counter = 60;
    boss_1_counter = 32;
    boss_x = 13;
    boss_y = 8;
    _en_life_boss = 15;
    boss_screen_buffer[0] = boss_screen_buffer[1] = boss_screen_buffer[2] = 0;
    
    clear_sprites();
    
}

void draw_player_lives(void) {
    _x = 16; _y = 23; _t = p_total_lifes; _n = 3; print_number2();
}

void save_object(void) {
    objects[objects_index].gpit = p_tx + (p_ty * 15);
    objects[objects_index].x =  p_tx;
    objects[objects_index].y =  p_ty;
    objects[objects_index].n_pant = n_pant;
    objects_index++;
}

void get_object(unsigned int p) {
    points = points + p;
    _x = p_tx; _y = p_ty; _t = 1; _n = 0; update_tile();
   save_object();
   print_points();

}

void print_points() {    
    _n = 5;
    rdc = (points / 10000);
    _x = 26; _y = 0; _t = rdc; print_number_wan ();
    rdc = (points / 1000) % 10;
    _x = 27; _y = 0; _t = rdc; print_number_wan ();
    rdc = (points / 100) % 10;
    _x = 28; _y = 0; _t = rdc; print_number_wan ();
    rdc = (points / 10) % 10;
    _x = 29; _y = 0; _t = rdc; print_number_wan ();
    rdc = points % 10;
    _x = 30; _y = 0; _t = rdc; print_number_wan ();

}

void draw_player_sublives(void) {
    _x = 1; _y = 0; _t = 7; _gp_gen =  (unsigned char *)("#"); print_str ();
    _x = 2; _y = 0; _t = 7; _gp_gen =  (unsigned char *)("#"); print_str ();
}

void clear_gamezone() {
	for (rda = 0; rda < 10; rda++) {
		for (rdb = 0; rdb < 15; rdb ++) {
			_x = rdb;
			_y = rda;
			_t = 0;
			draw_invalidate_coloured_tile_gamearea ();
			sp_UpdateNow ();
		}
	}
}