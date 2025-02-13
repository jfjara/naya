// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins


//coger aleatorio una chuche 0-5: piru 6-11: moneda 12-17: helado

rdc = rand() % 21;
if (rdc < 6) {
    _t = 34 ;
} else if (rdc < 12) {
    _t = 35;
} else if (rdc < 18) {
    _t = 37;
} else if (rdc < 19) {
    _t = 38;
} else {
    _t = 36;
}
_n = 128;
update_tile ();