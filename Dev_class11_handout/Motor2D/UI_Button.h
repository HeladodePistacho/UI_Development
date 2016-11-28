#ifndef _UI_BUTTON_H_
#define _UI_BUTTON_H_

#include "UI_interactive_element.h"
#include "UI_Image.h"

class UI_Button : public UI_interactive
{
public:
	UI_Image Button_image;

public:
	UI_Button(iPoint pos, UI_TYPE type, SDL_Rect set_box, const UI_Image& start_image);
	UI_Button(const UI_Button* other);

	void Change_image_to(const UI_Image& new_image);
	bool Update_Draw();

};


#endif // !_UI_BUTTON_H_
