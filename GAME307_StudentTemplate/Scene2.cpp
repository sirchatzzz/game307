#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

}

Scene2::~Scene2(){

}


bool Scene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
	
	background = IMG_Load("assets/dead.png");

	texture = SDL_CreateTextureFromSurface(renderer, background);


	return true;
}

void Scene2::OnDestroy() {

	SDL_FreeSurface(background);
	SDL_DestroyTexture(texture);
	delete this;

}


void Scene2::Update(const float deltaTime) {
	
	static float time = 0;

	time++;

	if (time > 300)
	{
		game->LoadScene(1);
		time = 0;
	}


}

void Scene2::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render the background
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);

	SDL_RenderPresent(renderer);



}

void Scene2::HandleEvents(const SDL_Event& event)
{
}

