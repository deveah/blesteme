
#include <SDL/SDL.h>

#include "blesteme.h"

int main( void )
{
	bl_input_t i;
	float c, d;

	/* call the intialization procedure */
	bl_initialize( "DejaVuSansMono.ttf", 16, 80, 30, "Blesteme", -1 );

	c = 0.0f;
	d = 0.01f;

	/* run as long as the user doesn't press escape */
	while( i.key != SDLK_ESCAPE )
	{
		/* set the background and foreground colors */
		bl_foreground( c, c, c );
		bl_background( 1.0f-c, 1.0f-c, 1.0f-c );

		/* write some text and refresh */
		bl_write( 36, 12, "Blesteme" );
		bl_refresh();

		/* do the fading effect */
		c += d;
		if( c > 1.0f ) d = -d;
		if( c < 0.0f ) d = -d;

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
