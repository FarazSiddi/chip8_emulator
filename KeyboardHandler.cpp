#include "KeyboardHandler.h"

// #include <SDL_events.h>

KeyboardHandler::KeyboardHandler(std::array<uint8_t, KEY_COUNT>& keys) : keys_{ keys } {
}

bool KeyboardHandler::handle() {
    /*
    Chip-8
    Keypad           Keyboard
    +-+-+-+-+        +-+-+-+-+
    |1|2|3|C|        |1|2|3|4|
    +-+-+-+-+        +-+-+-+-+
    |4|5|6|D|        |Q|W|E|R|
    +-+-+-+-+   =>   +-+-+-+-+
    |7|8|9|E|        |A|S|D|F|
    +-+-+-+-+        +-+-+-+-+
    |A|0|B|F|        |Z|X|C|V|
    +-+-+-+-+        +-+-+-+-+
     */

    bool quit = false;

    

    return quit;
}