#include "Chip8.h"

#include <fstream>
#include <cstddef>
#include <cstring>
#include <vector>
#include <iostream>
#include <limits>

const unsigned int SPRITE_WIDTH = 8;
const unsigned int FONT_SET_START_ADDRESS = 0x50;
const unsigned int ROM_START_ADDRESS = 0x200;
const unsigned int CHARACTER_SPRITE_WIDTH = 0x5;


const std::array<uint8_t, FONT_SET_SIZE> FONT_SET{
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

// Timers should run at 60 hertz
const double TIMER_DELAY = (1.0 / 60.0) * 1000000000;

Chip8::Chip8(Mode mode) : mode_{ mode },
randEngine_(chrono::system_clock::now().time_since_epoch().count()),
    timer_{ TIMER_DELAY } {
    // reset();

    for (unsigned int i = 0; i < FONT_SET_SIZE; i++) {
        memory_[i + FONT_SET_START_ADDRESS] = FONT_SET[i];
    }

}

void Chip8::loadRom(const std::string& filepath) {
    std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);
    if (!ifs) {
        throw std::runtime_error("Can't open file: " + filepath + ". " + std::strerror(errno));
    }

    auto end = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    auto size = std::size_t(end - ifs.tellg());
    if (size == 0) {
        throw std::runtime_error("Specified ROM has a size of 0.");
    }
    else if (size > MEMORY_SIZE - ROM_START_ADDRESS) {
        throw std::runtime_error("ROM too big for memory");
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    for (long long unsigned int i = 0; i < size; i++) {
        memory_[i + ROM_START_ADDRESS] = buffer[i];
    }

    ifs.close();
}

void Chip8::reset() {
    opcode_ = 0;
    index_ = 0;
    pc_ = 0x200;
    sp_ = 0;
    delayTimer_ = 0;
    soundTimer_ = 0;
    drawFlag_ = true;
    soundFlag_ = false;
    stack_.fill(0);
    registers_.fill(0);
    keys_.fill(0);

    std::fill(std::begin(memory_), std::begin(memory_) + FONT_SET_START_ADDRESS, 0);
    std::fill(std::begin(memory_) + FONT_SET_START_ADDRESS + FONT_SET_SIZE, std::end(memory_), 0);

    // clearScreen();
}