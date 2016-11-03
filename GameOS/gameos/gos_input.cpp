#include <SDL2/SDL.h>
#include <string.h> // memset
#include <assert.h>
#include "gos_input.h"

namespace input {

MouseInfo::MouseInfo()
    : x_(0), y_(0), rel_x_(0), rel_y_(0),
     wheel_vert_(0), wheel_hor_(0)
{
    memset(button_state_, 0 ,sizeof(button_state_));
}

static int sdl2idx(int button) {
    switch(button) {
        case SDL_BUTTON_LEFT: return 0;
        case SDL_BUTTON_MIDDLE: return 1;
        case SDL_BUTTON_RIGHT: return 2;
        case SDL_BUTTON_X1: return 3;
        case SDL_BUTTON_X2: return 4;
        default: return -1;
    }
}

void handleMouseMotion(const SDL_Event* event, MouseInfo* mi) {
    assert(event && mi);

    mi->x_ = event->motion.x;
    mi->y_ = event->motion.y;
    mi->rel_x_ = event->motion.xrel;
    mi->rel_y_ = event->motion.yrel;
}

void handleMouseButton(const SDL_Event* event, MouseInfo* mi) {
    assert(event && mi);

    int idx = sdl2idx(event->button.button);
    if(idx != -1 && idx < MouseInfo::NUM_BUTTONS) {
        mi->button_state_[idx] = event->type == SDL_MOUSEBUTTONUP ? KS_PRESSED : KS_RELEASED;
    }
}

void handleMouseWheel(const SDL_Event* event, MouseInfo* mi) {
    assert(event && mi);
    
    mi->wheel_vert_ = event->wheel.y;
    mi->wheel_hor_ = event->wheel.x;

    /* not in my SDL, apparenty >= SDL 2.0.4
    if(event->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
        mi->wheel_vert_ *= -1;
        mi->wheel_hor_ *= -1;
    }
    */
}

void updateMouseState(MouseInfo* mi) {
    assert(mi);

    Uint32 button_state = SDL_GetMouseState(NULL, NULL);
    int buttons[] = {SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT, SDL_BUTTON_X1, SDL_BUTTON_X2 };

    for(unsigned int b=0; b < sizeof(buttons)/sizeof(buttons[0]); ++b) {

        int idx = sdl2idx(buttons[b]);
        if(idx == -1 || idx >= MouseInfo::NUM_BUTTONS)
            continue;

        KeyState prev_ks = mi->button_state_[idx];

        if(button_state & SDL_BUTTON(buttons[b])) {
            mi->button_state_[idx] = prev_ks==KS_FREE ? KS_PRESSED : KS_HELD;
        } else {
            mi->button_state_[idx] = prev_ks==KS_HELD ? KS_RELEASED : KS_FREE;
        }

        if(mi->button_state_[idx] == KS_PRESSED)
            printf("%d pressed\n", idx);
        if(mi->button_state_[idx] == KS_RELEASED)
            printf("%d released\n", idx);
    }
}

} // namespace