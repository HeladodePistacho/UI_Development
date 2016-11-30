#ifndef _INTERACTIVE_ELEMENT_H
#define	_INTERACTIVE_ELEMENT_H


#include "UI_element.h"
#include "j1Input.h"
#include "SDL\include\SDL_rect.h"

enum INTERACTIVE_STATE
{
	NOTHING,
	OVER_ELEMENT,
	CLICK_ELEMENT
};

class UI_interactive : public UI_element
{
public:
	SDL_Rect Interactive_box;
	INTERACTIVE_STATE state = NOTHING;

public:

	UI_interactive(iPoint pos, UI_TYPE type, SDL_Rect set_box);
	bool Mouse_is_in(const iPoint& mouse_pos);

};



#endif
