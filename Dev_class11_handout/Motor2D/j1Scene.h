#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class UI_element;
class UI_Image;
class UI_Button;
class UI_Interactive_String;
class UI_String;
class GuiText;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* debug_tex;
	
	UI_element* screen;
	UI_Image* banner;
	UI_String* texto_de_ejemplo;
	

	UI_Image* button_image;
	UI_Image* button_over;
	UI_Image* clicked_Button;


	UI_Button* Button_1;
	UI_Button* Button_2;

	UI_Image* window;
	UI_String* title;
	UI_Button* Button;
	UI_String* vaya_vaya;
	
};

#endif // __j1SCENE_H__