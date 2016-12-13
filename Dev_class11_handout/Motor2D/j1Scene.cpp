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
	UI_Image lol({ 30,30 }, UI_TYPE::IMAGE, { 485, 829, 328, 103 }, true);

	banner = (UI_Image*)App->gui->CreateElement((UI_element*)&lol);


	button_image = (UI_Image*)App->gui->CreateElement((UI_element*)&(UI_Image({ 0,0 }, UI_TYPE::IMAGE, { 2,112,228,67 }, false)));
	button_over = (UI_Image*)App->gui->CreateElement((UI_element*)&(UI_Image({ 0,0 }, UI_TYPE::IMAGE, { 413,168,228,67 }, false)));
	clicked_Button = (UI_Image*)App->gui->CreateElement((UI_element*)&(UI_Image({ 0,0 }, UI_TYPE::IMAGE, { 644,168,228,67 }, false)));
	
	Button = (UI_Button*)App->gui->CreateElement((UI_element*)&(UI_Button({ 100 ,100 }, UI_TYPE::BUTTON, { 100, 100, 228, 67 }, button_image)));
	Button_1 = (UI_Button*)App->gui->CreateElement((UI_element*)&(UI_Button({ 100 ,200 }, UI_TYPE::BUTTON, { 100, 200, 228, 67 }, button_image)));
	Button_2 = (UI_Button*)App->gui->CreateElement((UI_element*)&(UI_Button({ 100 ,300 }, UI_TYPE::BUTTON, { 100, 300, 228, 67 }, button_image)));

	texto_de_ejemplo = (UI_Interactive_String*)App->gui->CreateElement((UI_element*)&(UI_Interactive_String({ 270, 400 }, UI_TYPE::INTERACTIVE_STRING, "texto de ejemplo", { 270, 400, 100, 20 })));
	*/

	screen = App->gui->CreateScreen((UI_element*)&UI_element(SCREEN, { 0, 0, 780, 600 }));

	banner = (UI_Image*)screen->AddChild((UI_element*)&UI_Image(IMAGE, { 30,30, 328,103 }, { 485, 829, 328, 103 }, true));
	texto_de_ejemplo = (UI_String*)screen->AddChild((UI_element*)&UI_String(STRING, { 30, 30, 10, 10 }, nullptr, true, NO_SCROLL));

	button_image = (UI_Image*)screen->AddChild((UI_element*)&UI_Image(IMAGE, { 0,0,0,0 }, { 2,112,228,67 }, false));
	button_over = (UI_Image*)screen->AddChild((UI_element*)&(UI_Image(IMAGE, { 0,0,0,0 }, { 413,168,228,67 }, false)));
	clicked_Button = (UI_Image*)screen->AddChild((UI_element*)&(UI_Image(IMAGE, { 0,0,0,0 }, { 644,168,228,67 }, false)));

	window = (UI_Image*)screen->AddChild((UI_element*)&(UI_Image(IMAGE, { 300, 100, 455, 497 }, { 15,512,455,497 }, true)));
	title = (UI_String*)window->AddChild((UI_element*)&UI_String(STRING, { 150, 30, 100, 100 }, "TEXTO DE EJEMPLO"));
	Button = (UI_Button*)window->AddChild((UI_element*)&(UI_Button(BUTTON, { -100, 100, 228, 67 }, button_image, true, NO_SCROLL)));
	vaya_vaya = (UI_String*)Button->AddChild((UI_element*)&UI_String(STRING, { 150, 30, 100, 100 }, "aqui no hay playa"));
	
	Button_1 = (UI_Button*)screen->AddChild((UI_element*)&(UI_Button(BUTTON, { 100, 200, 228, 67 }, button_image)));
	Button_2 = (UI_Button*)screen->AddChild((UI_element*)&(UI_Button(BUTTON, { 100, 300, 228, 67 }, button_image)));

	text_box_image = (UI_Image*)screen->AddChild((UI_element*)&(UI_Image(IMAGE, { 0,0,0,0 }, { 490,571,342,58 }, false)));
	insertar = (UI_Text_Box*)Button_1->AddChild((UI_element*)&(UI_Text_Box(TEXT_BOX, { 30,100, 342, 58 }, "Inserte algo", text_box_image)));

	slider = (UI_Image*)screen->AddChild((UI_element*)&UI_Image(IMAGE, { 0,0,17,17 }, { 1001,882,17,17 }, false, Y_SCROLL));
	scroll_image = (UI_Image*)screen->AddChild((UI_element*)&UI_Image(IMAGE, { 0,0,0,0 }, { 986,874,11,148 }, false));
	scroll = (UI_Scroll*)screen->AddChild((UI_element*)&UI_Scroll(SCROLL, { 50, 50, 11, 148 }, slider, scroll_image, true, NO_SCROLL));

	scroll->Camera_elements.add(banner);


	bool lol = slider->active;

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
	// Gui ---
	
	// -------

	if (SDL_IsTextInputActive() == false)
	{
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
			App->LoadGame("save_game.xml");

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			App->SaveGame("save_game.xml");

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			App->render->camera.y += floor(200.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->render->camera.y -= floor(200.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->render->camera.x += floor(200.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			App->render->camera.x -= floor(200.0f * dt);
	}
	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// UI FUNCIONALITY ------------------------------
	

	 App->input->GetMousePosition(x, y);

	
	 if (Button->state == INTERACTIVE_STATE::CLICK_ELEMENT) Button->Change_image_to(clicked_Button);
	 if (Button->state == INTERACTIVE_STATE::OVER_ELEMENT) Button->Change_image_to(button_over);
	 if (Button->state == INTERACTIVE_STATE::NOTHING) Button->Change_image_to(button_image);

	 
	 if (Button_1->state == INTERACTIVE_STATE::CLICK_ELEMENT) Button_1->Change_image_to(clicked_Button);
	 if (Button_1->state == INTERACTIVE_STATE::OVER_ELEMENT) Button_1->Change_image_to(button_over);
	 if (Button_1->state == INTERACTIVE_STATE::NOTHING) Button_1->Change_image_to(button_image);

	 if (Button_2->state == INTERACTIVE_STATE::CLICK_ELEMENT) Button_2->Change_image_to(clicked_Button);
	 if (Button_2->state == INTERACTIVE_STATE::OVER_ELEMENT) Button_2->Change_image_to(button_over);
	 if (Button_2->state == INTERACTIVE_STATE::NOTHING) Button_2->Change_image_to(button_image);
	
	 
	 if (texto_de_ejemplo->state == INTERACTIVE_STATE::CLICK_ELEMENT) texto_de_ejemplo->Set_String("wow me pulsan");
	 if (texto_de_ejemplo->state == INTERACTIVE_STATE::OVER_ELEMENT) texto_de_ejemplo->Set_String("en la cara no pls");
	 if (texto_de_ejemplo->state == INTERACTIVE_STATE::NOTHING) texto_de_ejemplo->Set_String("tocame_wapo");
	
	
	
	
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
