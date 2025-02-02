// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

_t = qtile(p_tx, p_ty);

if (_t == 28 || _t == 27) {
    gpx = 255;
    gpy = 255;
    p_tx = 255;
    p_ty = 255;
    clear_sprites();
    do_not_move = 1;
    if (stage_clear_animation == 0) animate_dog = 1;
}

if (_t == 34 || _t == 37) {
    get_object(50);
}
if (_t == 35) {
    get_object(100);
}

