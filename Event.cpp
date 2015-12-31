#include "Event.h"

#include <iostream>

Event::Event() {
}

Event::~Event() {
}

void Event::OnEvent(SDL_Event* Event) {

    switch (Event->type) {
std::cout << "Event->type " << Event->type << std::endl;
        case SDL_WINDOWEVENT:
        {
            switch (Event->window.event) {
                case SDL_WINDOWEVENT_ENTER:
                {
                    OnMouseFocus();
                    break;
                }
                case SDL_WINDOWEVENT_LEAVE:
                {
                    OnMouseBlur();
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                {
                    OnInputFocus();
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_LOST:
                {
                    OnInputBlur();
                    break;
                }
                case SDL_WINDOWEVENT_SHOWN:
                {
                    std::cout << "SDL_WINDOWEVENT_SHOWN" << std::endl;
                    break;
                }
                case SDL_WINDOWEVENT_HIDDEN:
                {
                    break;
                }
                case SDL_WINDOWEVENT_EXPOSED:
                {
                    break;
                }
                case SDL_WINDOWEVENT_MOVED:
                {
                    break;
                }
                case SDL_WINDOWEVENT_RESIZED:
                {
                    OnWindowResized(Event->window.data1, Event->window.data2);
                    break;
                }
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    break;
                }
                case SDL_WINDOWEVENT_MINIMIZED:
                {
                    break;
                }
                case SDL_WINDOWEVENT_MAXIMIZED:
                {
                    break;
                }
                case SDL_WINDOWEVENT_RESTORED:
                {
                    break;
                }
                case SDL_WINDOWEVENT_CLOSE:
                {
                    break;
                }
            }
            break;

        } // SDL_WINDOWEVENT

        case SDL_QUIT:
        {
            OnExit();
            break;
        }
        case SDL_KEYDOWN:
        {
            OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
            break;
        }
        case SDL_KEYUP:
        {
            OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, (Event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (Event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (Event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT:
                {
                    OnLButtonDown(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    OnRButtonDown(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    OnMButtonDown(Event->button.x, Event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT:
                {
                    OnLButtonUp(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    OnRButtonUp(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    OnMButtonUp(Event->button.x, Event->button.y);
                    break;
                }
            }
            break;
        }

            //Star getting things from here man!
        case SDL_JOYAXISMOTION:
        {
            OnJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
            break;
        }
        case SDL_JOYBALLMOTION:
        {
            OnJoyBall(Event->jball.which, Event->jball.ball, Event->jball.xrel, Event->jball.yrel);
            break;
        }
        case SDL_JOYHATMOTION:
        {
            OnJoyHat(Event->jhat.which, Event->jhat.hat, Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN:
        {
            std::cout << "SDL_JOYBUTTONDOWN" << std::endl;
            OnJoyButtonDown(Event->jbutton.which, Event->jbutton.button);
            break;
        }
        case SDL_JOYBUTTONUP:
        {
            OnJoyButtonUp(Event->jbutton.which, Event->jbutton.button);
            break;
        }
        default:
        {
            OnUser(Event->user.type, Event->user.code, Event->user.data1, Event->user.data2);
            break;
        }
    }
}

void Event::OnExit() {
}

void Event::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode) {
    printf("keycode:%d\tmod:%ho\tscancode:%ho pressed!\n", sym, mod, scancode);
}

void Event::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode) {
    printf("keycode:%d\tmod:%ho\tscancode:%ho unpressed!\n", sym, mod, scancode);
}

void Event::OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle) {
    printf("x:%d\ty:%d\n", mx, my);
}

void Event::OnLButtonDown(int mx, int my) {
    printf("Left Click pressed in x:%d\ty:%d\n", mx, my);
}

void Event::OnLButtonUp(int mx, int my) {
    printf("Left Click unpressed in x:%d\ty:%d\n", mx, my);
}

void Event::OnRButtonDown(int mx, int my) {
    printf("Right Click pressed in x:%d\ty:%d\n", mx, my);
}

void Event::OnRButtonUp(int mx, int my) {
    printf("Right Click unpressed in x:%d\ty:%d\n", mx, my);
}

void Event::OnMButtonDown(int mx, int my) {
    printf("Middle Click pressed in x:%d\ty:%d\n", mx, my);
}

void Event::OnMButtonUp(int mx, int my) {
    printf("Middle Click unpressed in x:%d\ty:%d\n", mx, my);
}

void Event::OnMouseFocus() {
    printf("Mouse entered the window!\n");
}

void Event::OnMouseBlur() {
    printf("Mouse left the window!\n");
}

void Event::OnInputFocus() {
    printf("Keyboard Focus on the window!\n");
}

void Event::OnInputBlur() {
    printf("Keyboard lost focus on the window!\n");
}

void Event::OnWindowResized(int data1, int data2) {
    printf("Window Resized to: width:%d\theight:%d\n", data1, data2);
}

void Event::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
    printf("OnJoyAxis: which:%hho\taxis:%hho\tvalue:%d\n", which, axis, value);
}

void Event::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {
}

void Event::OnJoyHat(Uint8 which, Uint8 hat, Uint8 button) {
}

void Event::OnJoyButtonDown(Uint8 which, Uint8 button) {
}

void Event::OnJoyButtonUp(Uint8 which, Uint8 button) {
}

void Event::OnUser(Uint8 type, int code, void* data1, void* data2) {
    printf("OnUser: type:%hho\tcode:%d\n", type, code);
}
