#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "Player.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "Module_entites_manager.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "UI_element.h"
#include "UI_Image.h"
#include "UI_Text_Box.h"
#include "UI_scroll.h"
#include "UI_Button.h"
#include "UI_String.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the image (rect {485, 829, 328, 103}) and the text "Hello World" as UI elements
	//App->gui->CreateElement({ 0, 0 }, UI_TYPE::IMAGE_NOT_IN_ATLAS, { 0, 0, 1920, 1080 }, 0);


	
	//Exam

	//Exercise 1 -> Setting all the elements
	Background = new UI_Image(IMAGE, { 0,0,0,0 }, { 0, 1600, 1024, 576 }, true, NO_SCROLL);
	Background->setmodule(this);

	window = new UI_Image(IMAGE, { 50, 60, 455, 497 }, { 15,512,455,497 }, true);
	window->setmodule(this);
	title = new UI_String(STRING, { 120,50,0,0 }, "Select Your Character");
	title->Load_text_texture();
	title->setmodule(this);

	button_over = new UI_Image(IMAGE, { 0,0,0,0 }, { 2,112,228,67 }, false);
	button_over->setmodule(this);
	clicked_Button = new UI_Image(IMAGE, { 0,0,0,0 }, { 413,168,228,67 }, false);
	clicked_Button->setmodule(this);
	button_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 644,168,228,67 }, false);
	button_image->setmodule(this);

	Button = new UI_Button(BUTTON, { 120, 380, 228, 67 }, button_image, true, NO_SCROLL);
	Button_Label = new UI_String(STRING, { 50, 20, 0, 0 }, "Continue");
	Button_Label->setmodule(this);
	Button_Label->Load_text_texture();

	Big_heroe_image = new UI_Image(IMAGE, { 0,0,1025,574 }, { 0, 1024, 1025, 574 }, true, NO_SCROLL);
	Slider_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 900, 314, 68, 54 } , false);
	Heroe_images = new UI_Image(IMAGE, { 0, 0, 0,0 }, { 0, 290, 300, 169 }, false);
	Heroe_selector = new UI_Scroll(SCROLL, { 130, 200, 68, 54 }, Slider_image, Heroe_images, true);

	Big_heroe_image->setmodule(this);
	Slider_image->setmodule(this);
	Heroe_images->setmodule(this);
	Heroe_selector->setmodule(this);


	Exam_screen = App->gui->CreateScreen(&UI_element(SCREEN, { 0, 0, 1024, 576 }));

	Exam_screen->AddChild(Background);
	Exam_screen->AddChild(window);
	Exam_screen->AddChild(button_image);
	Exam_screen->AddChild(button_over);
	Exam_screen->AddChild(clicked_Button);

	window->AddChild(title);
	window->AddChild(Button);
	window->AddChild(Heroe_selector);

	Button->AddChild(Button_Label);

	Button->setmodule(this);
	Exam_screen->setmodule(this);

	//Exercise 2 Setting the scroll elements
	Heroe_selector->Set_Stop_Box({ 130, 200, 300, 169 });
	Heroe_selector->Set_Camera({ 592, 151, 339, 271 });
	Heroe_selector->Add_Camera_element(Big_heroe_image);

	lol = new UI_Image(UI_TYPE::IMAGE, { 0, 700, 300, 169 }, { 0, 290, 300, 169 }, true);
	UI_String*	lol2 = new UI_String(STRING, { 0, 900, 0, 20 }, "Select Your Character");
	lol2->Load_text_texture();

	Heroe_selector->Add_Camera_element(lol);
	Heroe_selector->Add_Camera_element(lol2);
	/**/

	soldier0 = (Player*)App->entity_manager->create({ 15, 5 });
	soldier0->Set_texture({ 3, 2, 28, 36 });

	soldier1 = (Player*)App->entity_manager->create({ 24,0 });
	soldier1->Set_texture({ 3, 2, 28, 36 });

	soldier2 = (Player*)App->entity_manager->create({ 20,6 });
	soldier2->Set_texture({ 3, 2, 28, 36 });

	soldier3 = (Player*)App->entity_manager->create({ 24,10 });
	soldier3->Set_texture({ 3, 2, 28, 36 });

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x--;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y--;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x++;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y++;

	App->map->Draw();
	
	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::On_GUI_Callback(UI_element* elem, GUI_INPUT gui_input)
{
	if (active)
	{
		switch (gui_input)
		{
		case MOUSE_IN:
			if (elem == Button)
				Button->Change_image_to(button_over);
			break;

		case MOUSE_OUT:
			if (elem == Button)
				Button->Change_image_to(button_image);
			break;

		case LEFT_MOUSE_DOWN:
			if (elem == Button)
				Button->Change_image_to(clicked_Button);
			break;

		case LEFT_MOUSE_REPEAT:
			if (elem == Button)
				Button->Change_image_to(clicked_Button);
			break;
		}

	}
	return true;
}
