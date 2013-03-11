
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "blesteme.h"

int bl_initialized = 0;

int bl_initialize(	char* fontFile,
					int fontSize,
					int cols,
					int rows,
					char* windowTitle,
					int deltax )
{
	/*	save parameters for later use */
	bl_fontFile = fontFile;
	bl_fontSize = fontSize;
	bl_cols = cols;
	bl_rows = rows;
	bl_windowTitle = windowTitle;
	bl_deltax = deltax;

	/*	initialize SDL and SDL_ttf */
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		return -1;
	
	if( TTF_Init() < 0 )
		return -1;

	/*	load the font */
	bl_font = TTF_OpenFont( fontFile, fontSize );
	if( bl_font == NULL )
		return -1;

	/*	disable the font hinting; this is just a matter of preference */
	TTF_SetFontHinting( bl_font, TTF_HINTING_NONE );

	/*	get glyph metrics;
		assuming that a monospace font is loaded, get the metrics of an
		arbitrary character */
	TTF_SizeText( bl_font, "#", &bl_charWidth, &bl_charHeight );

	/*	set the window caption */
	SDL_WM_SetCaption( windowTitle, NULL );

	/*	initialize main screen */
	bl_screen = SDL_SetVideoMode( bl_cols*bl_charWidth + ( bl_deltax*bl_cols ),
		bl_rows*bl_charHeight, 32, SDL_DOUBLEBUF|SDL_HWSURFACE );

	bl_initialized = 1;

	return 0;
}

int bl_terminate( void )
{
	if( !bl_initialized )
		return -1;
	
	TTF_CloseFont( bl_font );
	TTF_Quit();
	SDL_FreeSurface( bl_screen );
	SDL_Quit();

	return 0;
}

int bl_write( int x, int y, char* string )
{
	SDL_Color fg, bg;
	SDL_Surface *renderedText;
	SDL_Rect destRect;

	if( !bl_initialized )
		return -1;

	fg.r = bl_fg[0]*255.0f; fg.g = bl_fg[1]*255.0f; fg.b = bl_fg[2]*255.0f;
	bg.r = bl_bg[0]*255.0f; bg.g = bl_bg[1]*255.0f; bg.b = bl_bg[2]*255.0f;

	/*	you don't want to do that */
	if( string == NULL )
		return -1;
	
	renderedText = TTF_RenderUTF8_Shaded( bl_font, string, fg, bg );
	
	destRect.x = x * bl_charWidth + ( bl_deltax*x );
	destRect.y = y * bl_charHeight;
	SDL_BlitSurface( renderedText, NULL, bl_screen, &destRect );

	SDL_FreeSurface( renderedText );

	return 0;
}

int bl_refresh( void )
{
	if( !bl_initialized )
		return -1;

	SDL_Flip( bl_screen );

	return 0;
}

int bl_delay( int ms )
{
	if( !bl_initialized )
		return -1;

	SDL_Delay( ms );

	return 0;
}

int bl_background( float r, float g, float b )
{
	if( !bl_initialized )
		return -1;

	if( r > 1.0f ) r = 1.0f;
	if( r < 0.0f ) r = 0.0f;
	if( g > 1.0f ) g = 1.0f;
	if( g < 0.0f ) g = 0.0f;
	if( b > 1.0f ) b = 1.0f;
	if( b < 0.0f ) b = 0.0f;

	bl_bg[0] = r;
	bl_bg[1] = g;
	bl_bg[2] = b;

	return 0;
}

int bl_foreground( float r, float g, float b )
{
	if( !bl_initialized )
		return -1;

	if( r > 1.0f ) r = 1.0f;
	if( r < 0.0f ) r = 0.0f;
	if( g > 1.0f ) g = 1.0f;
	if( g < 0.0f ) g = 0.0f;
	if( b > 1.0f ) b = 1.0f;
	if( b < 0.0f ) b = 0.0f;

	bl_fg[0] = r;
	bl_fg[1] = g;
	bl_fg[2] = b;

	return 0;
}

int bl_clear( void )
{
	int color;

	if( !bl_initialized )
		return -1;

	color = SDL_MapRGB( bl_screen->format, bl_bg[0]*255.0f, bl_bg[1]*255.0f, bl_bg[2]*255.0f );

	SDL_FillRect( bl_screen, NULL, color );

	return 0;
}

int bl_input( bl_input_t *i )
{
	SDL_Event e;

	if( !bl_initialized )
		return -1;

	if( SDL_PollEvent( &e ) )
	{
		if( e.type == SDL_KEYDOWN )
		{
			i->key = e.key.keysym.sym;
			i->mod = e.key.keysym.mod;
		}
		else
			return -1;
	}
	else
		/*	no input */
		return -1;

	return 0;
}
