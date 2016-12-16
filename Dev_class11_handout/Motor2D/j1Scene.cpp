#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
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
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the image (rect {485, 829, 328, 103}) and the text "Hello World" as UI elements
	//App->gui->CreateElement({ 0, 0 }, UI_TYPE::IMAGE_NOT_IN_ATLAS, { 0, 0, 1920, 1080 }, 0);

	/*
	screen = App->gui->CreateScreen((UI_element*)&UI_element(SCREEN, { 0, 0, 780, 600 }));

	
	banner = new UI_Image(IMAGE, { 30, 150, 328,103 }, { 485, 829, 328, 103 }, true);
	texto_de_ejemplo = new UI_String(STRING, { 30, 70, 10, 10 }, "lol", true, NO_SCROLL);

	button_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 2,112,228,67 }, false);
	button_over = new UI_Image(IMAGE, { 0,0,0,0 }, { 413,168,228,67 }, false);
	clicked_Button = new UI_Image(IMAGE, { 0,0,0,0 }, { 644,168,228,67 }, false);

	
	title = new UI_String(STRING, { 150, 30, 100, 100 }, "TEXTO DE EJEMPLO");
	Button = new UI_Button(BUTTON, { -100, 100, 228, 67 }, button_image, true);
	vaya_vaya = new UI_String(STRING, { 150, 30, 100, 100 }, "aqui no hay playa");

	text_box_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 490,571,342,58 }, false);
	insertar = new UI_Text_Box(TEXT_BOX, { 250,100, 342, 58 }, "Inserte algo", text_box_image);
	

	slider = new UI_Image(IMAGE, { 0,0,0,0 }, { 1001,882,17,17 }, false);
	scroll_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 986,874,11,148 }, false);
	scroll = new UI_Scroll(SCROLL, { 0, 0, 17, 17 }, slider, scroll_image, true, Y_SCROLL);
	
	
	scroll->Set_Stop_Box({ 50,50,11,148 });
	scroll->Set_Camera({ 70, 50, 300, 180 });
	scroll->Add_Camera_element(banner);
	scroll->Add_Camera_element(texto_de_ejemplo);

	scroll->Add_to_Tab();
	insertar->Add_to_Tab();
	Button->Add_to_Tab();

	screen->AddChild(slider);
	screen->AddChild(scroll_image);
	screen->AddChild(scroll);
	screen->AddChild(insertar);
	screen->AddChild(text_box_image);
	screen->AddChild(button_image);
	screen->AddChild(button_over);
	screen->AddChild(clicked_Button);
	screen->AddChild(window);
	window->AddChild(title);
	window->AddChild(Button);
	Button->AddChild(vaya_vaya);
	*/
	
	//Exam

	//Exercise 1 -> Setting all the elements
	Background = new UI_Image(IMAGE, { 0,0,0,0 }, { 0, 1600, 1024, 576 }, true, NO_SCROLL);

	window = new UI_Image(IMAGE, { 50, 60, 455, 497 }, { 15,512,455,497 }, true, NO_SCROLL);
	title = new UI_String(STRING, { 120,50,0,0 }, "Select Your Character");

	button_over = new UI_Image(IMAGE, { 0,0,0,0 }, { 2,112,228,67 }, false);
	clicked_Button = new UI_Image(IMAGE, { 0,0,0,0 }, { 413,168,228,67 }, false);
	button_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 644,168,228,67 }, false);

	Button = new UI_Button(BUTTON, { 120, 380, 228, 67 }, button_image, true, NO_SCROLL);
	Button_Label = new UI_String(STRING, { 50, 20, 0, 0 }, "Continue");

	Big_heroe_image = new UI_Image(IMAGE, { 0,0,1025,574 }, { 0, 1024, 1025, 574 }, true, NO_SCROLL);
	Slider_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 900, 314, 68, 54 } , false);
	Heroe_images = new UI_Image(IMAGE, { 0, 0, 0,0 }, { 0, 290, 300, 169 }, false);
	Heroe_selector = new UI_Scroll(SCROLL, { 130, 200, 68, 54 }, Slider_image, Heroe_images, true);

	
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

	//Exercise 2 Setting the scroll elements
	Heroe_selector->Set_Stop_Box({ 130, 200, 300, 169 });
	Heroe_selector->Set_Camera({ 592, 151, 339, 271 });
	Heroe_selector->Add_Camera_element(Big_heroe_image);

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
	
	if (Button->state == INTERACTIVE_STATE::CLICK_ELEMENT) Button->Change_image_to(clicked_Button);
	if (Button->state == INTERACTIVE_STATE::OVER_ELEMENT) Button->Change_image_to(button_over);
	if (Button->state == INTERACTIVE_STATE::NOTHING) Button->Change_image_to(button_image);

	
	
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
