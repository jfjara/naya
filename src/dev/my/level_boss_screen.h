// MTE MK1 (la Churrera) v5.10
// Copyleft 2010-2014, 2020-2023 by the Mojon Twins

// This code is used to display the "new level" screen. You can customize it for your game:

{
	blackout_area ();
	STOP_SOUND();
	espera_activa (10);
	
	level_str [7] = 49 + level;
	level_str[12] = 49 + slevel;
	if (level == 0) {_x = 12; _y = 12; _t = 71; _gp_gen = level_boss_1_str; print_str ();}
	if (level == 1) {_x = 12; _y = 12; _t = 71; _gp_gen = level_boss_2_str; print_str ();}
	sp_UpdateNow ();
	// #ifdef MODE_128K
	// 	PLAY_SOUND (SFX_START);
	// #else			
	// 	beep_fx (1);
	// #endif

	espera_activa (300);
	PLAY_MUSIC (10);
}
