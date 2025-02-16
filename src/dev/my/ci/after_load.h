// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

sp_UpdateNow ();    // Clear buffer

    for (gpit = 0; gpit < 3; ++ gpit) {
        get_resource (splash_screens [gpit], 16384);
        espera_activa (500);
        wyz_play_sound (SFX_START);
        cortina ();
        blackout ();
    }