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


	screen = App->gui->CreateScreen((UI_element*)&UI_element(SCREEN, { 0, 0, 780, 600 }));

	
	banner = new UI_Image(IMAGE, { 30, 150, 328,103 }, { 485, 829, 328, 103 }, true);
	texto_de_ejemplo = new UI_String(STRING, { 30, 70, 10, 10 }, "lol", true, NO_SCROLL);
	
	/*
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
	*/

	slider = new UI_Image(IMAGE, { 0,0,0,0 }, { 1001,882,17,17 }, false);
	scroll_image = new UI_Image(IMAGE, { 0,0,0,0 }, { 986,874,11,148 }, false);
	scroll = new UI_Scroll(SCROLL, { 0, 0, 17, 17 }, slider, scroll_image, true, Y_SCROLL);
	scroll->Set_Stop_Box({ 50,50,11,148 });
	scroll->Set_Camera({ 70, 50, 300, 180 });
	scroll->Add_Camera_element(banner);
	scroll->Add_Camera_element(texto_de_ejemplo);

	screen->AddChild(slider);
	screen->AddChild(scroll_image);
	screen->AddChild(scroll);

	
	
	//Exam

	/*
	screen_exam = App->gui->CreateScreen((UI_element*)&UI_element(SCREEN, { 0, 0, 788, 579 }));
	background = (UI_Image*)screen_exam->AddChild((UI_element*)&UI_Image(IMAGE, { 0, 0, 788, 579 }, { 970, 1844, 768, 579 }, true, NO_SCROLL));

	selector_p1 = (UI_Image*)screen_exam->AddChild((UI_element*)&UI_Image(IMAGE, { 239, 78, 0, 0 }, { 1485, 110, 72, 109 }, true, NO_SCROLL));
	selector_p2 = (UI_Image*)screen_exam->AddChild((UI_element*)&UI_Image(IMAGE, { 239, 78, 0, 0 }, { 1560, 110, 72, 109 }, true, NO_SCROLL));

	player_1_image = (UI_Image*)screen_exam->AddChild((UI_element*)&UI_Image(IMAGE, { 24, 61, 0, 0 }, { 925, 605, 168, 279 }));
	player_2_image = (UI_Image*)screen_exam->AddChild((UI_element*)&UI_Image(IMAGE, { 543, 61, 0, 0 }, { 925, 605, 168, 279 }));

	player = selector_p1;
	position_player_1 = { 0,0 };
	position_player_2 = { 0,0 };

	characters[0][0] = { 239, 78 };
	characters[1][0] = { 311, 78 };
	characters[2][0] = { 383, 78 };
	characters[3][0] = { 455, 78 };
	characters[0][1] = { 239, 172 };
	characters[1][1] = { 311, 172 };
	characters[2][1] = { 383, 172 };
	characters[3][1] = { 455, 172 };
	*/
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
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		
		if (player == selector_p1)
		{
			if (position_player_1.y)
			{
				position_player_1.y--;
				player->Interactive_box.y = characters[position_player_1.x][position_player_1.y].y;
				player_1_image->Image.y -= player_1_image->Image.h;
			}
		}
		else
		{
			if (position_player_2.y)
			{
				position_player_2.y--;
				player->Interactive_box.y = characters[position_player_2.x][position_player_2.y].y;
				player_2_image->Image.y -= player_2_image->Image.h;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		if (player == selector_p1)
		{
			if (!position_player_1.y)
			{
				position_player_1.y++;

				player->Interactive_box.y = characters[position_player_1.x][position_player_1.y].y;
				player_1_image->Image.y += player_1_image->Image.h;
			}
		}
		else
		{
			if (!position_player_2.y)
			{
				position_player_2.y++;

				player->Interactive_box.y = characters[position_player_2.x][position_player_2.y].y;
				player_2_image->Image.y += player_2_image->Image.h;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		if (player == selector_p1)
		{
			if (position_player_1.x < 3)
			{
				position_player_1.x++;

				player->Interactive_box.x = characters[position_player_1.x][position_player_1.y].x;
				player_1_image->Image.x += player_1_image->Image.w;
			}
		}
		else
		{
			if (position_player_2.x < 3)
			{
				position_player_2.x++;

				player->Interactive_box.x = characters[position_player_2.x][position_player_2.y].x;
				player_2_image->Image.x += player_2_image->Image.w;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		if (player == selector_p1)
		{
			if (position_player_1.x)
			{
				position_player_1.x--;

				player->Interactive_box.x = characters[position_player_1.x][position_player_1.y].x;
				player_1_image->Image.x -= player_1_image->Image.w;
			}
		}
		else
		{
			if (position_player_2.x)
			{
				position_player_2.x--;

				player->Interactive_box.x = characters[position_player_2.x][position_player_2.y].x;
				player_2_image->Image.x -= player_2_image->Image.w;
			}
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		if (player == selector_p1)
			player = selector_p2;
			
		else player = selector_p1;
	}
	



	// -------
	/*
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
	*/
	
	
	
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
