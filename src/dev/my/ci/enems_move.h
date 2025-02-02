// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

case 5:
    active = 1;
    if (is_lunge == 1) {
        _en_x = 255;
        _en_y = 255;
    } else if (boss_1_counter == 80) {
        _en_x =208;
        _en_y = 96;
    }
    if (boss_action == 3) { //movimiento cabeza
        if (boss_1_counter % 2 == 0) {
            circle_movement(_en_x, _en_y);
            if (vector_counter > 9) {
                vector_counter = 0;
            }
        }
        boss_1_counter--;
        
        if (boss_1_counter == 0) {
            boss_action = 4;  // aqui seria ataque de cabeza
            boss_1_counter = 10;
        }
    } else if (boss_action == 4) { //calcula posicion para lanzarse
        if (boss_1_counter == 0) {
            //recoge posicion player
            //se lanza a por el
            boss_action = 5;
            boss_aux_1 = gpx - 32;
            boss_aux_2 = gpy;
            boss_1_counter = 0;
        } 
        
        boss_1_counter--;
    } else if (boss_action == 5) { //lanza cabeza
        if (boss_aux_1 < _en_x) {
            _en_x = _en_x - 6;
        }
        if (boss_aux_1 > _en_x) {
            _en_x = _en_x + 6;
        }
        if (boss_aux_2 < _en_y) {
            _en_y = _en_y - 6;
        }
        if (boss_aux_2 > _en_y) {
            _en_y = _en_y + 6;
        }

        diff_x = _en_x - boss_aux_1;
        diff_y = _en_y - boss_aux_2;

        if (abs(diff_x) <= 6 && abs(diff_y) <= 6) {
            boss_aux_1 = 208;
            boss_aux_2 = 96;
            if (boss_1_counter == 1) {
                boss_action = 0;
                _en_x = 208;
                _en_y = 96;
            }
            boss_1_counter++;
        } 

    } 
    break;