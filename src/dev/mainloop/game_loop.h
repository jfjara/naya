// MTE MK1 (la Churrera) v5.10
// Copyleft 2010-2014, 2020-2023 by the Mojon Twins

// game_loop.h - Da game loop.

	#asm
		; Makes debugging easier
		._game_loop_init
	#endasm

	p_total_lifes = 3;
	playing = 1;
	player_init ();

	#ifdef OBJECT_COUNT
		flags [OBJECT_COUNT] = p_objs;
	#endif

	#ifndef COMPRESSED_LEVELS		
		hotspots_init ();
	#endif

	#ifndef COMPRESSED_LEVELS		
		#if !defined DEACTIVATE_KEYS && MAX_CERROJOS > 0
			locks_init ();
		#endif
	#endif

	#if defined(PLAYER_STEPS_ON_ENEMIES) || defined (PLAYER_CAN_FIRE)
		#ifndef COMPRESSED_LEVELS
			enems_init ();
		#endif
	#endif	

	#ifndef COMPRESSED_LEVELS	
		n_pant = SCR_INICIO;
	#endif		

	maincounter = 0;

	#ifdef ACTIVATE_SCRIPTING		
		script_result = 0;
	#endif
	
	// #ifdef MODE_128K
	// 		// Play music
	// 	#ifdef COMPRESSED_LEVELS		
	// 		PLAY_MUSIC (levels [level].music_id + slevel);
	// 	#else
	// 		PLAY_MUSIC (1);
	// 	#endif		
	// #endif

	#ifdef ACTIVATE_SCRIPTING
		// Entering game
		run_script (2 * MAP_W * MAP_H);
	#endif

	#include "my/ci/entering_game.h"
	
	#ifdef PLAYER_STEPS_ON_ENEMIES 	
		#ifdef SHOW_TOTAL
		// Show total of enemies next to the killed amount.
		_x = KILLED_Y; _y = KILLED_X; _t = BADDIES_COUNT; print_number2 ();
		#endif
	#endif

	p_killme = success = half_life = 0;
		
	objs_old = keys_old = life_old = killed_old = 0xff;
	#ifdef MAX_AMMO 	
		ammo_old = 0xff;
	#endif
	#if defined TIMER_ENABLE && TIMER_X != 99
		timer_old = 0;
	#endif

	#ifdef PLAYER_CHECK_MAP_BOUNDARIES		
		#ifdef COMPRESSED_LEVELS
			x_pant = n_pant % level_data.map_w;
			y_pant = n_pant / level_data.map_w;
		#else
			x_pant = n_pant % MAP_W; y_pant = n_pant / MAP_W;
		#endif
	#endif

	#ifdef ENABLE_CHECKPOINTS
		if (sg_do_load) {
			mem_load ();
		}
	#endif		

	#ifdef MSC_MAXITEMS
		display_items ();
	#endif

	#ifdef DIE_AND_RESPAWN
		safe_n_pant = n_pant; 
		safe_gpx = gpx;
		safe_gpy = gpy;
	#endif

	faps = 0;
	dead_animation = 0;
	timer_on = 1;

	o_pant = 0xff;
	print_points();

	while (playing) {
		#asm
			; Makes debugging easier
			._game_loop_do
		#endasm

		#ifdef DEBUG_KEYS
			if (sp_KeyPressed (KEY_M)) { ++ p_objs; beep_fx (0); }
			if (sp_KeyPressed (KEY_H)) { ++ n_pant; beep_fx (0); }
			if (sp_KeyPressed (KEY_Y)) { -- n_pant; beep_fx (0); }
		#endif

		p_kill_amt = 1;
		pad0 = (joyfunc) (&keys);

		if (o_pant != n_pant) {
			#include "my/ci/before_entering_screen.h"
			draw_scr ();
			o_pant = n_pant;
			shoots = 0;
			boss_aux_2 = 1;
			for (b_it = 0; b_it < MAX_BULLETS; b_it ++) {
				bullets_who[b_it] = 0;
			}
			#if defined DIE_AND_RESPAWN && defined PLAYER_GENITAL
				safe_gpx = gpx; safe_gpy = gpy;
			#endif
		}

		faps++;
		
		if (level == 1 && faps % 4 == 0) {
			animate_tiles(1);
		}

		if (faps == 24) {
			animate_tiles(0);
			faps = 0;
		}

		if (dead_animation == 1) {
			fire_count_animation--;
		}
		if (dead_animation == 1 && fire_count_animation == 0) {
			dead_animation = 0;
			p_total_lifes--;
			draw_player_lives();
			if (p_total_lifes == 0) {
				playing = 0;  //el game over debe de salir sl acabar la animacion
				dead_animation = 0;
				fire_count_animation = 0;
				do_not_move = 0;
				clear_sprites();
			} else {
				p_life = 2;
				p_killme = 0;
				o_pant = 99;
				clear_sprites();
				clear_gamezone();
				blackout_area();
				restart_level();
				invalidate_viewport();
				draw_player_sublives();
				
				if (slevel == 3) {
					_x = 0; _y = 0; _t = slevel; print_number_wan ();
					PLAY_MUSIC (10);
				}else {
					PLAY_MUSIC (levels [level].music_id + slevel);
					_x = 10; _y = 0; _t = slevel; print_number_wan ();
				}
				continue;
			}
		}

		#ifdef TIMER_ENABLE
			#if defined(TIMER_SCRIPT_0) && defined(ACTIVATE_SCRIPTING)
				if (timer_zero) {
					timer_zero = 0;
					#ifdef SHOW_TIMER_OVER
						clear_sprites ();
						time_over ();
					#endif
					run_script (2 * MAP_W * MAP_H + 3); 	// ON_TIMER_OFF	
				}	
			#endif

			#ifdef TIMER_KILL_0
				if (timer_zero) {
					timer_on = 0;
					if (n_pant == 1) {
						clear_sprites ();
						time_over ();
						timer_zero = 0;
						level++;
						slevel = 0;
 						prepare_level ();
						#include "my/level_screen.h";
					} else {
						#ifdef SHOW_TIMER_OVER
						#ifndef TIMER_SCRIPT_0
							//clear_sprites ();
							time_over ();
							start_dead();
							
						#endif
					#endif				
					timer_zero = 0;
					#ifdef TIMER_AUTO_RESET 			
						timer_t = TIMER_INITIAL;
					#endif
					
					#ifdef MODE_128K
						//p_killme = 7;
					#else
						p_killme = 4;
					#endif

					

					#if defined(TIMER_WARP_TO_X) && defined(TIMER_WARP_TO_Y)
						p_x = TIMER_WARP_TO_X << 10;
						p_y = TIMER_WARP_TO_Y << 10;
					#endif

					#ifdef TIMER_WARP_TO
						n_pant = TIMER_WARP_TO;
						draw_scr ();
					#endif
					}					
				}
			#endif

			// Timer
			if (timer_on) {
				timer_count ++;
				if (timer_count == timer_frames) {
					timer_count = 0;
					timer_t --;
					if (timer_t == 0) timer_zero = 1;
				}
			}
		#endif

		draw_hud ();

	/*
		maincounter ++;
		half_life = !half_life;
		*/
		#asm
				ld  hl, _maincounter
				inc (hl)
				ld  a, (_half_life)
				xor 1
				ld  (_half_life), a
		#endasm
				
		// Move player
		player_move ();
		
		// Move enemies
		enems_move ();

		#ifdef ENABLE_SIMPLE_COCOS
			// Move simple cocos
			simple_coco_update ();
		#endif

		#ifdef PLAYER_CAN_FIRE
			// Move bullets 			
			bullets_move ();
		#endif

		#ifdef ENABLE_TILANIMS
			tilanims_do ();
		#endif

		// Detect fire zone
		#if defined ACTIVATE_SCRIPTING && defined ENABLE_FIRE_ZONE
			if (f_zone_ac == 1) {
				if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
					run_fire_script ();
				}	
			}
		#endif

		// Render
		if (o_pant == n_pant) {
			#include "mainloop/update_sprites.h"

			// Limit frame rate
			
			#ifdef MIN_FAPS_PER_FRAME
				#asm
					.ml_min_faps_loop
						ld  a, (_isrc)
						cp  MIN_FAPS_PER_FRAME
						jr  nc, ml_min_faps_loop_end
						halt
						jr  ml_min_faps_loop

					.ml_min_faps_loop_end
						xor a
						ld  (_isrc), a
				#endasm
			#endif

			sp_UpdateNow();
		}

		#ifdef PLAYER_FLICKERS
			// Flickering
			if (p_estado == EST_PARP) {
				p_ct_estado --;
				if (p_ct_estado == 0) {
					p_estado = EST_NORMAL; 
					if (inmutable == 1) {
						STOP_SOUND();
						PLAY_MUSIC (levels [level].music_id + slevel);
						espera_activa(5);
						inmutable = 0;
					}
				}
			}
		#endif			
		
		// Hotspot interaction.
		hotspots_do ();

		// Kill player
		if (p_killme) {
			if (p_total_lifes > 0 && p_life > 0) {
				player_kill (p_killme);
				#include "my/ci/on_player_killed.h"
			}
		}

		// Scripting related stuff
		
		#ifdef ACTIVATE_SCRIPTING
			// Select object
			#ifdef MSC_MAXITEMS
				if (sp_KeyPressed (KEY_Z)) {
					if (!key_z_pressed) {
						#ifdef MODE_128K
							PLAY_SOUND (0);
						#else
							beep_fx (2);
						#endif
						flags [FLAG_SLOT_SELECTED] = (flags [FLAG_SLOT_SELECTED] + 1) % MSC_MAXITEMS;
						display_items ();
					}
					key_z_pressed = 1;
				} else {
					key_z_pressed = 0;
				}
			#endif			

			#ifndef SCRIPTING_KEY_NONE
				#ifdef SCRIPTING_KEY_M			
					if (sp_KeyPressed (KEY_M))
				#endif
				#ifdef SCRIPTING_DOWN
					if ((pad0 & sp_DOWN) == 0)
				#endif
				#ifdef SCRIPTING_KEY_FIRE
					if ((pad0 & sp_FIRE) == 0)
				#endif
				{
					// Any scripts to run in this screen?
					run_fire_script ();
				}
			#endif
		#endif

		#ifdef PAUSE_ABORT
			// Pause/Abort handling
			if (sp_KeyPressed (KEY_H)) {
				sp_WaitForNoKey ();
				#ifdef MODE_128K
					player_on = 0;
				#endif				
				clear_sprites ();
				pause_screen ();
				while (!sp_KeyPressed (KEY_H));
				sp_WaitForNoKey ();
				draw_scr ();
				#ifdef MODE_128K
					player_on = 1;
				#endif				
			}			
			if (sp_KeyPressed (KEY_Y)) {
				playing = 0;
			}
		#endif

		// Flick the screen ?
			
		#if defined ACTIVATE_SCRIPTING && defined COMPRESSED_LEVELS
			if (script_result != 3)
		#endif
		{
			#include "mainloop/flick_screen.h"
		}

		// Win game condition
		
		if (0
			#ifdef ACTIVATE_SCRIPTING
				|| script_result == 1 || script_result > 2
			#endif
			#ifdef PLAYER_NUM_OBJETOS
				|| p_objs == PLAYER_NUM_OBJETOS
			#endif
			#ifdef SCR_FIN
				|| (n_pant == SCR_FIN
				#if defined PLAYER_FIN_X && defined PLAYER_FIN_Y				
					&& ((gpx + 8) >> 4) == PLAYER_FIN_X && ((gpy + 8) >> 4) == PLAYER_FIN_Y
				#endif
				)
			#endif
		) {
			success = 1;
			playing = 0;
		}
		
		// Game over condition
		#if defined ACTIVATE_SCRIPTING || (defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0)) 
			if (0
			#ifdef ACTIVATE_SCRIPTING
				|| (script_result == 2)
			#endif
			#if defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0)
				|| timer_zero
			#endif
		) {
			playing = 0;				
		}
		#endif

		#include "my/ci/extra_routines.h"
	}
	
	sp_UpdateNow ();
	sp_WaitForNoKey ();

	#ifdef MODE_128K		
		STOP_SOUND ();
	#endif

	#include "my/ci/after_game_loop.h"
