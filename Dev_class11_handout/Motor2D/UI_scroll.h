#ifndef _UI_SCROLL_H_
#define _UI_SCROLL_H_

#include "UI_element.h"
#include "UI_Image.h"

class UI_Scroll : public UI_element
{
public:

	UI_Image Slider;
	SDL_Rect Camera_Scroll;
	p2List<UI_element*> Camera_elements;

public:

	UI_Scroll(UI_TYPE type, SDL_Rect detection_box, const UI_Image& slider);
	UI_Scroll(const UI_Scroll* other);

	 bool Update();
	 bool Update_Draw();
	
	 

};


#endif // !_UI_SCROLL_H_


