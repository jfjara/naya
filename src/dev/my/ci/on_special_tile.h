// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

_t = qtile(p_tx, p_ty);

if (_t == 28 || _t == 27) {
    // gpx = 255;
    // gpy = 255;
    // p_tx = 255;
    // p_ty = 255;
    clear_sprites();
    do_not_move = 1;
    if (stage_clear_animation == 0) animate_dog = 1;
}

if (_t == 34 || _t == 37) {
    get_object(50);
    total_candies++;
    draw_candy_level();
    if (total_candies != 20) PLAY_SOUND(8);
}
if (_t == 35) {
    get_object(100);
    total_candies++;
    draw_candy_level();
    if (total_candies != 20) PLAY_SOUND(8);
}
if (_t == 36) {
    get_object(100); //invencibility
    p_estado = EST_PARP;
	p_ct_estado = 200;
    inmutable = 1;
    PLAY_MUSIC(14);
}
if (_t == 38) {
    get_object(100);
    timer_t = timer_t + 15;
    if (timer_t > 99) timer_t = 99;
    PLAY_SOUND(9);
}

if (total_candies == 20) {
    max_shoots = 2;
    PLAY_SOUND(11);
}
