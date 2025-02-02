// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// custom_animation.h

// If you define PLAYER_CUSTOM_ANIMATION you have to add code here
// You should end up giving a value to p_next_frame.

// You can use the array player_cells [] which contains pointers to the 8
// frames for the main player in your spriteset.

if (p_direction == 0) {  //parado derecha
    
    if (faps % 12 == 0) {
        if (last_direction == 2) {
            if (tick_frame == 7) {
                tick_frame = 0;
            } else {
                tick_frame = 7;
            }
        } else if (last_direction == 1) {
            if (tick_frame == 6) {
                tick_frame = 1;
            } else {
                tick_frame = 6;
            }
        }
        
    }
} else if (p_direction == 2) {  
    if (faps % 4 == 0) {
        if (cont_frame == 0) {
            tick_frame = 2;
        } else if (cont_frame == 1) {
            tick_frame = 0;
        } else if (cont_frame == 2) {
            tick_frame = 3;
        } else if (cont_frame == 3) {
            tick_frame = 0;
        } 
        cont_frame++;
        if (cont_frame == 4) {
            cont_frame = 0;
        }
    }
} else if (p_direction == 1) {
    if (faps % 4 == 0) {
        if (cont_frame == 0) {
            tick_frame = 5;
        } else if (cont_frame == 1) {
            tick_frame = 6;
        } else if (cont_frame == 2) {
            tick_frame = 4;
        } else if (cont_frame == 3) {
            tick_frame = 6;
        }
        cont_frame++;
        if (cont_frame == 4) {
            cont_frame = 0;
        }
    }
} else if (p_direction == 3) {
    if (last_direction == 2) {
        tick_frame = 2;  
    } else {
        tick_frame = 5;
    }
} else if (p_direction == 4 && fire_count_animation > 0) {
    
    if (last_direction == 2) {
        tick_frame = 2;
    } else {
        tick_frame = 5;
    }
    fire_count_animation--;
}

if (fire_count_animation == 0) {
    fire_count_animation = 4;
    p_direction = last_direction;
}


if (dead_animation == 1) {
    if (tick_frame < 4) {
        p_next_frame = extra_sprite_23_a;
    } else {
        p_next_frame = extra_sprite_24_a;
    }
    tick_frame++;
    if (tick_frame == 8) {
        tick_frame = 0;
    }
} else {
    p_next_frame = (unsigned char *) (player_cells [tick_frame]);
}


    