
#include <SDL/SDL.h>

#include "blesteme.h"

int main( void )
{
	bl_input_t i;
	int c, d;
	int x, y;

	bl_clear_input( &i );

	/* call the intialization procedure */
	bl_initialize( "DejaVuSansMono.ttf", 14, 80, 30, "Blesteme", -1 );

	c = 0;
	d = 4;

	/*	run as long as the user doesn't press escape OR
		close the window / send an exit signal */
	while(	( i.key != SDLK_ESCAPE ) &&
			( i.quit != 1 ) )
	{
		/* fill the screen with black */
		bl_background( 0, 0, 0 );
		bl_clear();
		
		/* set the background and foreground colors */
		bl_foreground( c, c, c );
		bl_background( 255-c, 255-c, 255-c );
		bl_printf( 36, 12, "Blesteme" );

		bl_background( 0, 0, 0 );
		bl_foreground( 128, 128, 128 );
		bl_printf( 0, 0, "mouse: %i, %i", i.mouse_x, i.mouse_y );

		if( i.mouse_btn == SDL_BUTTON_LEFT )
			bl_printf( 0, 1, "left click" );
		if( i.mouse_btn == SDL_BUTTON_RIGHT )
			bl_printf( 0, 1, "right click" );
		if( i.mouse_btn == SDL_BUTTON_MIDDLE )
			bl_printf( 0, 1, "middle click" );
	
		if( i.key != -1 )
			bl_addch( 0, 2, i.key );

		if( i.mod & KMOD_SHIFT )
			bl_printf( 0, 3, "shift" );
		if( i.mod & KMOD_ALT )
			bl_printf( 6, 3, "alt" );
		if( i.mod & KMOD_CTRL )
			bl_printf( 10, 3, "ctrl" );

		bl_refresh();

		/* do the fading effect */
		c += d;
		if( c > 255 ) d = -d;
		if( c <   0 ) d = -d;

		/*	get input; result is discarded because we don't care if the user
			doesn't press anything */
		bl_input( &i );

		/* delay, to conserve some power */
		bl_delay( 10 );
	}

	/* destroy the window */
	bl_terminate();
	return 0;
}
