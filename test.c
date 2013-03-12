
#include <SDL/SDL.h>

#include "blesteme.h"

int main( void )
{
	bl_input_t i;
	float c, d;
	int x, y;

	/* call the intialization procedure */
	bl_initialize( "DejaVuSansMono.ttf", 24, 80, 30, "Blesteme", -1 );

	c = 0.0f;
	d = 0.01f;

	/* run as long as the user doesn't press escape */
	while( i.key != SDLK_ESCAPE )
	{
		/* write some text and refresh */
		for( x = 0; x < 80; x++ )
			for( y = 0; y < 30; y++ )
			{
				float r = (float)(rand()%100) / 100.0f;
				float g = (float)(rand()%100) / 100.0f;
				float b = (float)(rand()%100) / 100.0f;
				
				bl_foreground( r, g, b );
				bl_background( 0.0f, 0.0f, 0.0f );
				bl_write( x, y, ":" );
			}

		/* set the background and foreground colors */
		bl_foreground( c, c, c );
		bl_background( 1.0f-c, 1.0f-c, 1.0f-c );
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
