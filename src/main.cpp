#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3_image/SDL_image.h"
#include "iostream"

using namespace std;

struct SDLState
{
	SDL_Window* window; // Pointer to the SDL window
	SDL_Renderer* renderer; // Pointer to the SDL renderer
};

enum class CellState { Empty, X, O };
CellState board[3][3] = {
	{CellState::Empty, CellState::Empty, CellState::Empty},
	{CellState::Empty, CellState::Empty, CellState::Empty},
	{CellState::Empty, CellState::Empty, CellState::Empty}
};

void cleanup(SDLState& state);

void drawBackground(SDLState& state, SDL_FRect* backgroundPosSize);


int main(int argc, char* argv[])
{
	CellState currentPlayer = CellState::X; // 1 - X, 2 - O
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


	bool running = true;
	bool redrawBackground = true; // Flag to indicate whether the background should be drawn or not.
	SDL_Event event; // Event structure to handle events like window close, key presses, etc.
	SDL_FRect backgroundPosSize = { 0, 0, 0, 0 };
	SDL_Texture* starTexture = IMG_LoadTexture(state.renderer, "assets/star.png");
	SDL_Texture* circleTexture = IMG_LoadTexture(state.renderer, "assets/circle.png");


	while (running) {
		while (SDL_PollEvent(&event)) { // Poll for events in the event queue.
			if (event.type == SDL_EVENT_QUIT) { // If the quit event is triggered (like closing the window), set running to false.
				running = false;
			}

			if (event.type == SDL_EVENT_WINDOW_RESIZED || redrawBackground) { // If the quit event is triggered (like closing the window), set running to false.
				drawBackground(state, &backgroundPosSize); // Redraw the background when the window is resized.
				redrawBackground = false;
			}

			// Draw the X or O Sprites

			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) { // If the quit event is triggered (like closing the window), set running to false.
				float cellWidth = backgroundPosSize.w / 3.0f;
				float cellHeight = backgroundPosSize.h / 3.0f;

				float mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY); // Get the current mouse position in the window.

				if (mouseX >= backgroundPosSize.x && mouseX <= backgroundPosSize.x + backgroundPosSize.w &&
					mouseY >= backgroundPosSize.y && mouseY <= backgroundPosSize.y + backgroundPosSize.h) {

					int col = (mouseX - backgroundPosSize.x) / cellWidth;
					int row = (mouseY - backgroundPosSize.y) / cellHeight;

					// Check board pos is empty
					if (board[row][col] == CellState::Empty) {
						currentPlayer = (currentPlayer == CellState::X) ? CellState::O : CellState::X; // Check Player
						board[row][col] = currentPlayer; // X or O
					}

					// Limpiar una vez
					SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
					SDL_RenderClear(state.renderer);

					// Dibujar fondo una vez
					SDL_Texture* background = IMG_LoadTexture(state.renderer, "assets/background.png");
					SDL_SetTextureScaleMode(background, SDL_SCALEMODE_NEAREST);
					SDL_RenderTexture(state.renderer, background, nullptr, &backgroundPosSize);

					// Dibujar sprites
					for (int row = 0; row < 3; row++) {
						for (int col = 0; col < 3; col++) {
							if (board[row][col] == CellState::Empty)
								continue;

							SDL_Texture* playerSprite = (board[row][col] == CellState::X) ? starTexture : circleTexture;
							SDL_SetTextureScaleMode(playerSprite, SDL_SCALEMODE_NEAREST);

							SDL_FRect dest;
							dest.w = cellWidth / 2;
							dest.h = cellHeight / 2;
							dest.x = backgroundPosSize.x + col * cellWidth + cellWidth / 4;
							dest.y = backgroundPosSize.y + row * cellHeight + cellHeight / 4;

							SDL_RenderTexture(state.renderer, playerSprite, nullptr, &dest);
						}
					}

					// Presentar todo lo dibujado
					SDL_RenderPresent(state.renderer);

				}
			}
		}
	}

	cleanup(state);
	return 0;

}

void drawBackground(SDLState& state, SDL_FRect* backgroundPosSize)
{
	SDL_Texture* background = IMG_LoadTexture(state.renderer, "assets/background.png"); // Load an idle texture from the assets folder. This is a placeholder for your game assets.
	SDL_SetTextureScaleMode(background, SDL_SCALEMODE_NEAREST); // Set the scale mode for the texture to linear, which is suitable for scaling textures smoothly.

	int windowWidth, windowHeight;
	SDL_GetWindowSize(state.window, &windowWidth, &windowHeight);
	backgroundPosSize->w = windowWidth;
	backgroundPosSize->h = windowHeight;
	backgroundPosSize->x = (windowWidth - backgroundPosSize->w) / 2.0f;
	backgroundPosSize->y = (windowHeight - backgroundPosSize->h) / 2.0f;

	// Render the background texture on the renderer.

	SDL_RenderTexture(state.renderer,
		background, // Render the idle texture on the renderer.
		nullptr, // The second parameter is null, meaning it will use the entire texture
		backgroundPosSize); // The third parameter is a pointer to an SDL_FRect structure that defines the position and size of the texture on the renderer.
	SDL_RenderPresent(state.renderer); // Present the renderer, which will display the cleared screen.
}

void cleanup(SDLState& state) // Function to clean up resources before exiting the application. It recieves SDLState by reference, to avoid copying the structure.
{
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}