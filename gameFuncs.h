#ifndef _GAMEFUNCS_H
#define _GAMEFUNCS_H


void init_light (void);

void init_texture ();

void reset ();

void write_string(void *font,char *txt);

void write_start ();

void write_points();

void write_points2();

void write_points_value();

void draw_arena ();

void draw_miner();

void locate_draw_diamond ();

bool time ();

void draw_diamond ();

bool catch_diamond ();

void cam ();

void gameDraw ();

void resize_window (GLint w, GLint h);

void get_keyboard (unsigned char key, GLint x, GLint y);

void get_keyboard_special (GLint key, GLint x, GLint y);

#endif
