// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

//quitar la vida del hub

_x = p_life + 1; _y = 0; _t = 0; _gp_gen =  (unsigned char *)(" "); print_str ();
if (p_life == 0) {
    timer_on = 0;
    p_total_lifes--;

    start_dead();
} 


