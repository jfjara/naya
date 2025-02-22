// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins


//coger aleatorio una chuche 0-5: piru 6-11: moneda 12-17: helado

rdc = rand() % 31;
if (rdc < 16) {
    _t = 34 ;
} else if (rdc < 22) {
    _t = 35;
} else if (rdc < 28) {
    _t = 37;
} else if (rdc < 29) {
    _t = 38;
} else {
    _t = 36;
}
_n = 128;
update_tile ();