#ifndef _INTERACTIVE_ELEMENT_H
#define	_INTERACTIVE_ELEMENT_H


#include "UI_element.h"
#include "SDL\include\SDL_rect.h"

class UI_interactive : public UI_element
{
public:
	SDL_Rect Interactive_box;
	bool Mouse_in = false;

public:

	UI_interactive(SDL_Rect set_box);
	bool Mouse_is_in(const iPoint& mouse_pos);

};



#endif
