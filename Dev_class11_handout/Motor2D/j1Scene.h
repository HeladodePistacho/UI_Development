#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class UI_Image;
class UI_Button;
class UI_Interactive_String;
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
	UI_Image* banner;
	GuiText* text;

	UI_Image* button_image;
	UI_Image* button_over;
	UI_Image* clicked_Button;

	UI_Button* Button;
	UI_Button* Button_1;
	UI_Button* Button_2;

	UI_Interactive_String* texto_de_ejemplo;
	
};

#endif // __j1SCENE_H__