// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins
case 4:
    if (special_ene == 1) active = 1;
    en_an_base_frame [enit] = 4;
    if (boss_aux_2 == 1) {
        _en_x--;
        if (_en_x <= 8) {
            boss_aux_2 = 2;
        }
    } else {
        _en_x++;
        if (_en_x >= 192) {
            boss_aux_2 = 1;
        }
    }
    
    break;
case 9:  //hormiga disparadora
    active = 1;
    en_an_base_frame [enit] = 4;
    
    if (ene_direction == 1) {
        _en_y++;
        
        if (_en_y >= _en_y2) {
            ene_direction = 2;
        }
    } else {
        _en_y--;
        if (_en_y <= _en_y1) {
            ene_direction = 1;
        }
    }
    // si se alinea, dispara
    if (_en_y == gpy) {
        bullets_fire (2);
    }
    break;
case 5:
    active = 1;
    en_an_base_frame[enit] = 22;
    if (level == 0) {
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
                if (gpx < 33) {
                    boss_aux_1 = 0;
                } else {
                    boss_aux_1 = gpx - 32;
                }
                boss_aux_2 = gpy - 8;
                boss_1_counter = 0;
            } 
            
            boss_1_counter--;
        } else if (boss_action == 5) { //lanza cabeza
            if (boss_aux_1 < _en_x) {
                _en_x = _en_x - 8;
            }
            if (boss_aux_1 > _en_x) {
                _en_x = _en_x + 8;
            }
            if (boss_aux_2 < _en_y) {
                _en_y = _en_y - 8;
            }
            if (boss_aux_2 > _en_y) {
                _en_y = _en_y + 8;
            }
    
            diff_x = _en_x - boss_aux_1;
            diff_y = _en_y - boss_aux_2;
    
            if (abs(diff_x) <= 8 && abs(diff_y) <= 8) {
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
    }
    break;