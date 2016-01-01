//==============================================================================
#include "App.h"
#include "Log.h"
#include "Event.h"
#include "Helper.h"

App App::Instance;

//==============================================================================

App::App() {
}

//------------------------------------------------------------------------------

void App::OnEvent(SDL_Event* Event) {
    Event::OnEvent(Event);
}

//------------------------------------------------------------------------------

bool App::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Log("Unable to Init SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }

    if ((Window = SDL_CreateWindow(
            "My SDL Game",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)
            ) == NULL) {
        Log("Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

//    PrimarySurface = SDL_GetWindowSurface(Window);

    if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC)) == nullptr) {
        Log("Unable to create renderer");
        return false;
    }

    SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

    // Initialize image loading for PNGs
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Log("Unable to init SDL_image: %s", IMG_GetError());
        return false;
    }

    // Load all of our Textures (see TextureBank class for expected folder)
    if (TextureBank::Init() == false) {
        Log("Unable to init TextureBank");
        return false;
    }
    
    //Check for joysticks
    if (SDL_NumJoysticks() < 1) {
        printf("Warning: No joysticks connected!\n");
    } else {
        //Load joystick
        mJoystick = SDL_JoystickOpen(0);
        if (mJoystick == NULL) {
            logSDLError(std::cout, "CApp::OnInit");
        } else
            std::cout << "LOADED JOYSTICK" << std::endl;
    }
    
    
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            mGameController = SDL_GameControllerOpen(i);
            if (mGameController) {
                cout << "Found Controller" << endl;
                std::cout << SDL_GameControllerMapping(mGameController) << std::endl;
                break;
            } else {
                logSDLError(std::cout, "CApp::OnInit");
            }
        }
    }
    

    return true;
}

//------------------------------------------------------------------------------

void App::Loop() {
}

//------------------------------------------------------------------------------

void App::Render() {
    SDL_RenderClear(Renderer);
    
    // TODO: need to loop through textures?
    
    
    int xDir = 0;
        int yDir = 0;


    if (mGameController != nullptr && SDL_GameControllerGetAttached(mGameController)) {
        // NOTE: We have a mGameController with index ControllerIndex.

        // DPAD
        bool Up = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_DPAD_UP);
        bool Down = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        bool Left = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        bool Right = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

        bool Start = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_START);
        bool Back = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_BACK);

        bool LeftShoulder = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
        bool RightShoulder = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

        bool AButton = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_A);
        bool BButton = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_B);
        bool XButton = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_X);
        bool YButton = SDL_GameControllerGetButton(mGameController, SDL_CONTROLLER_BUTTON_Y);

        Sint16 StickX = SDL_GameControllerGetAxis(mGameController, SDL_CONTROLLER_AXIS_LEFTX);
        Sint16 StickY = SDL_GameControllerGetAxis(mGameController, SDL_CONTROLLER_AXIS_LEFTY);

        //        std::cout << "DPAD: " << std::endl
        //                << "\tUp:    " << Up << std::endl
        //                << "\tDown:  " << Down << std::endl
        //                << "\tLeft:  " << Left << std::endl
        //                << "\tRight: " << Right << std::endl;
        //
        std::cout << "StickX: " << StickX << std::endl;
        std::cout << "StickY: " << StickY << std::endl;

        //Left of dead zone
        if (StickX < -JOYSTICK_DEAD_ZONE) {
            xDir = -1;
        }//Right of dead zone
        else if (StickX > JOYSTICK_DEAD_ZONE) {
            xDir = 1;
        } else {
            xDir = 0;
        }

        //Below of dead zone
        if (StickY < -JOYSTICK_DEAD_ZONE) {
            yDir = -1;
        }//Above of dead zone
        else if (StickY > JOYSTICK_DEAD_ZONE) {
            yDir = 1;
        } else {
            yDir = 0;
        }

    } // gameController present
    //Normalized direction
    double joystickAngle = atan2((double) yDir, (double) xDir) * (180.0 / M_PI);
    
    
    
    
    

    Texture* texture = TextureBank::Get("arrow");
    if (texture != nullptr) {
        //texture->Render(0, 0); // You should really check your pointers
        
        texture->render(Renderer, (SCREEN_WIDTH - texture->GetWidth()) / 2,
            (SCREEN_HEIGHT - texture->GetHeight()) / 2,
            NULL, joystickAngle);
        
        
    }
    else {
        logSDLError(std::cout, "App::Render");
    }

    SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------

void App::Cleanup() {
    TextureBank::Cleanup();

    if (Renderer) {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
    }

    if (Window) {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}

//------------------------------------------------------------------------------

int App::Execute(int argc, char* argv[]) {
    if (!Init()) return 0;

    SDL_Event Event;

    while (Running) {
        while (SDL_PollEvent(&Event) != 0) {
            OnEvent(&Event);

            if (Event.type == SDL_QUIT)
                Running = false;
        }

        Loop();
        Render();

        SDL_Delay(1); // Breath
    }

    Cleanup();

    return 1;
}

//==============================================================================

SDL_Renderer * App::GetRenderer() {
    return Renderer;
}

//==============================================================================

App * App::GetInstance() {
    return &App::Instance;
}

int App::GetWindowWidth() {
    return SCREEN_WIDTH;
}

int App::GetWindowHeight() {
    return SCREEN_HEIGHT;
}

//==============================================================================
