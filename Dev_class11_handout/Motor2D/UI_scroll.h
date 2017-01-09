#ifndef _UI_SCROLL_H_
#define _UI_SCROLL_H_

#include "UI_element.h"
#include "p2Point.h"
#include "UI_Image.h"


class UI_Scroll : public UI_element
{
private:

	UI_Image* Slider;
	UI_Image* Slide_box;
	SDL_Rect Stop_box;
	SDL_Rect Camera;
	p2List<UI_element*> Camera_elements;
	float Move_x = 0.0f;
	float Move_y = 0.0f;

	UI_element* Bottom_element;
	int Max_move_x = 0;
	int Max_move_y = 0;
	iPoint Pos;

public:

	UI_Scroll(UI_TYPE type, SDL_Rect detection_box, const UI_Image* slider, const UI_Image* slide_box, bool active = true, SCROLL_TYPE draggable = FREE_SCROLL);
	UI_Scroll(const UI_Scroll* other);
	~UI_Scroll();

	 bool Update();
	 bool Update_Draw();
	 bool Handle_input();

	 void Set_Stop_Box(SDL_Rect new_box);
	 void Set_Camera(SDL_Rect new_box);

	 void Stop();
	 void Move_elements();
	 void Move_stop_box();

	 void Add_Camera_element(UI_element* new_item);
	 SDL_Rect Get_Stop_Box() const;

	 

};


#endif // !_UI_SCROLL_H_


