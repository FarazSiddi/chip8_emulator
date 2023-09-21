#pragma once

#include "Constants.h"
#include "Mode.h"
#include "Timer.h"

#include <array>
#include <string>
#include <random>

const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_SIZE = 16;
const unsigned int FONT_SET_SIZE = 80;

class Chip8 {
public:
    explicit Chip8(Mode mode);

    void reset();

    void cycle();

    void loadRom(const std::string& filepath);

    std::array<uint8_t, KEY_COUNT>& keys();

    [[nodiscard]] const std::array<uint32_t, VIDEO_WIDTH* VIDEO_HEIGHT>& video() const;

    [[nodiscard]] bool drawFlag() const;

    void disableDrawFlag();

private:
    std::array<uint8_t, MEMORY_SIZE> memory_;
    std::array<uint8_t, REGISTER_COUNT> registers_;
    uint16_t opcode_;
    uint16_t index_;
    uint16_t pc_;

    std::array<uint16_t, STACK_SIZE> stack_;
    uint16_t sp_;

    std::array<uint32_t, VIDEO_WIDTH* VIDEO_HEIGHT> video_; 

    uint8_t delayTimer_;
    uint8_t soundTimer_;

    std::array<uint8_t, KEY_COUNT> keys_;

    bool drawFlag_;
    bool soundFlag_;

    const Mode mode_; // Specify whether to execute instructions like on the CHIP-8, CHIP-48 or SCHIP

    std::default_random_engine randEngine_;
    // std::uniform_int_distribution<uint8_t> randByte_;

    Timer timer_;

};