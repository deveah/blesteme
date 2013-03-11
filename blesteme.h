
/*
	blesteme.h
	blesteme - curses-like library intended for use in roguelikes

	This tiny library is built in order to simplify the work one has to do when
	working with SDL and SDL_ttf. In other words, it's just a roguelike-
	specific wrapper. Due to the size of the library, it's intended to be
	statically-linked. So, if you'll need it in your project, you only need to
	mention 'blesteme.c' among the input files and link against SDL and SDL_ttf.

	This project is public domain, and has no warranty. Use it at your own risk
	and feel free to contribute if you feel like it.
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifndef _BLESTEME_H_
#define _BLESTEME_H_

typedef struct
{
	int key;
	int mod;
} bl_input_t;

extern int bl_initialized;

char *bl_fontFile;
int bl_fontSize;
int bl_cols;
int bl_rows;
char *bl_windowTitle;
int bl_deltax;

int bl_charHeight;
int bl_charWidth;

float bl_fg[3], bl_bg[3];

SDL_Surface *bl_screen;
TTF_Font *bl_font;

/*	initialization procedure for blesteme;
	most arguments are self-explanatory;
	deltax specifies a width offset for each char, to avoid visual artifacts
	that are dependant on the font
*/
int bl_initialize( char* fontFile, int fontSize, int cols, int rows, char* windowTitle, int deltax );

/*	termination procedure for blesteme;
	must be called
*/
int bl_terminate( void );

/*	writes a string to the screen at position (x,y);
	the function expects a UTF8-encoded string
*/
int bl_write( int x, int y, char* string );

/*	reads from the keyboard;
	if a key is pressed, it will fill the bl_input_t structure pointed to with
	the corresponding data;
	if no key is being pressed at the time of being called, it returns -1.
*/
int bl_input( bl_input_t *i );

/*	functions for setting the background and foreground colors;
	arguments are in 0 ... 1 range
*/
int bl_background( float r, float g, float b );
int bl_foreground( float r, float g, float b );

/*	clears the screen, filling it with the current background color */
int bl_clear( void );

/*	updates the screen */
int bl_refresh( void );

/*	delay; time is expressed in milliseconds */
int bl_delay( int ms );

#endif
