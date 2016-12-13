#ifndef _UI_SCROLL_H_
#define _UI_SCROLL_H_

#include "UI_element.h"
#include "p2Point.h"
#include "UI_Image.h"


class UI_Scroll : public UI_element
{
public:

	UI_Image* Slider;
	UI_Image* Slide_box;
	SDL_Rect true_Slider;
	SDL_Rect Camera_Scroll;
	p2List<UI_element*> Camera_elements;
	iPoint Scroll_ant_pos;
	iPoint new_pos;

	bool lol = false;
public:

	UI_Scroll(UI_TYPE type, SDL_Rect detection_box, const UI_Image* slider, const UI_Image* slide_box, bool active = true, SCROLL_TYPE draggable = FREE_SCROLL);
	UI_Scroll(const UI_Scroll* other);

	 bool Update();
	 bool Update_Draw();
	 bool Handle_input();

	 bool Mouse_in_rect(const iPoint& mouse_pos);
	 void Drag_rect();
	 void Stop();
	 void Move_elements();

};


#endif // !_UI_SCROLL_H_


