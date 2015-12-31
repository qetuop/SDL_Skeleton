//==============================================================================
#include "Texture.h"
#include "Log.h"

//==============================================================================

Texture::Texture() {
}

//------------------------------------------------------------------------------

Texture::~Texture() {
    free();
}

//==============================================================================

bool Texture::Load(SDL_Renderer* Renderer, std::string Filename) {
    if (Renderer == NULL) {
        Log("Bad SDL renderer passed");
        return false;
    }

    this->Renderer = Renderer;
    this->Filename = Filename;
//
//    SDL_Surface* TempSurface = IMG_Load(Filename.c_str());
//    if (TempSurface == NULL) {
//        Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
//        return false;
//    }
//
//    // Convert SDL surface to a texture
//    if ((SDLTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface)) == NULL) {
//        Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
//        return false;
//    }
//
//    // Grab dimensions
//    SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);
//
//    //Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);
//
//    SDL_FreeSurface(TempSurface);
    
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
        SDL_Quit();
        return 1;
    }

    //Get rid of preexisting texture
    free();

    // TODO: replace texture loading with this?
    SDLTexture = IMG_LoadTexture(this->Renderer, Filename.c_str());
    
    //Make sure they both loaded ok
    if (SDLTexture == nullptr) {
        Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
    }
    else {
        // SDL_Texture is an ?opaque struct?
        SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);
    }
    
    return true;
}

//------------------------------------------------------------------------------

void Texture::Render(int X, int Y) {
    Render(X, Y, Width, Height);
}

//------------------------------------------------------------------------------

void Texture::Render(int X, int Y, int Width, int Height) {
    SDL_Rect Destination = {X, Y, Width, Height};

    SDL_RenderCopy(Renderer, SDLTexture, NULL, &Destination);
}

//------------------------------------------------------------------------------

void Texture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight) {
    SDL_Rect Source = {SX, SY, SWidth, SHeight};
    SDL_Rect Destination = {X, Y, Width, Height};

    SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);
}

//------------------------------------------------------------------------------

void Texture::render(SDL_Renderer *renderer,
        int x, int y, SDL_Rect* clip,
        double angle, SDL_Point* center, SDL_RendererFlip flip) {
    
//    std::cout << x << " " << y << " " << mWidth << " " << mHeight << " " << angle <<  std::endl;
    
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, Width, Height};

    //Set clip rendering dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }else {
        SDL_QueryTexture(SDLTexture, NULL, NULL, &renderQuad.w, &renderQuad.h);  // TODO: what is this doing?  won't show up if not here
    }

    //Render to screen -CopyEx = rotate/flip
    SDL_RenderCopyEx(renderer, SDLTexture, clip, &renderQuad, angle, center, flip);
}

//------------------------------------------------------------------------------

int Texture::GetWidth() {
    return Width;
}

int Texture::GetHeight() {
    return Height;
}

//==============================================================================

void Texture::free() {
    //Free texture if it exists
    if (SDLTexture != nullptr) {
        SDL_DestroyTexture(SDLTexture);
        
        SDLTexture = nullptr;
        Width = 0;
        Height = 0;
    }
}