#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"

using namespace std;

struct SDLState
{
	SDL_Window* window; // Pointer to the SDL window
	SDL_Renderer* renderer; // Pointer to the SDL renderer
};

void cleanup(SDLState& state);

int main(int argc, char* argv[])
{
	SDLState state;

	if (!SDL_Init(SDL_INIT_VIDEO)) // Initialize the SDL video subsystem. If not, throw an message box, and returns.
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL could not initialize!", nullptr);
		return 1;
	}

	int width = 800;
	int height = 600;
	state.window = SDL_CreateWindow("Tic-Tac-Toe", width, height, 0); // Create a window with the title "Tic-Tac-Toe" and dimensions 800x600

	if (!state.window) // If the window could not be created, show an error message box and clean up resources.
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Window could not be created!", nullptr);
		cleanup(state);
		return 1;
	}

	state.renderer = SDL_CreateRenderer(state.window, nullptr); // Create a renderer for the window. The second parameter is null, meaning it will use the default renderer.
	if (!state.renderer) // If the renderer could not be created, show an error message box and clean up resources.
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Renderer could not be created!", nullptr);
		cleanup(state);
		return 1;
	}

	// load game assets
	SDL_Texture* idleTex = IMG_LoadTexture(state.renderer, "assets/background.png"); // Load an idle texture from the assets folder. This is a placeholder for your game assets.
	SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST); // Set the scale mode for the texture to linear, which is suitable for scaling textures smoothly.

	bool running = true;
	SDL_Event event; // Event structure to handle events like window close, key presses, etc.
	while (running) {
		while (SDL_PollEvent(&event)) { // Poll for events in the event queue.
			if (event.type == SDL_EVENT_QUIT) { // If the quit event is triggered (like closing the window), set running to false.
				running = false;
			}

			// Handle other events here, such as key presses or mouse clicks.
			SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255); // Set the draw color to white.
			SDL_RenderClear(state.renderer); // Clear the renderer with the current draw color.

			int windowWidth, windowHeight;
			SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);
			SDL_FRect pos;
			pos.w = windowWidth;
			pos.h = windowHeight;
			pos.x = (windowWidth - pos.w) / 2.0f;
			pos.y = (windowHeight - pos.h) / 2.0f;

			SDL_RenderTexture(state.renderer,
				idleTex, // Render the idle texture on the renderer.
				nullptr, // The second parameter is null, meaning it will use the entire texture
				&pos); // The third parameter is a pointer to an SDL_FRect structure that defines the position and size of the texture on the renderer.

			SDL_RenderPresent(state.renderer); // Present the renderer, which will display the cleared screen.
		}
	}

	SDL_DestroyTexture(idleTex); // Destroy the idle texture to free up resources.
	cleanup(state);
	return 0;

}

void cleanup(SDLState& state) // Function to clean up resources before exiting the application. It recieves SDLState by reference, to avoid copying the structure.
{
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}