#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

/**
 * @brief
 * 1 for cross turn
 * 0 for zero turn
 * first turn is always 1
*/
class Position {
private:
    int16_t cross;
    int16_t zero;
    int16_t both;

    int turn = 1; 
public:
    Position(): cross(0), zero(0), both(0) {};
    Position(int c, int z): cross(c), zero(z), both(c | z) {};
    void do_move(int8_t pos);
    void undo_move();

    int16_t get_zero() const { return zero; }
    int16_t get_cross() const { return cross; }
    int16_t get_both() const { return both; }
    int16_t get_turn() const { return turn; }

    int is_over() const; // 1 for cross win, 0 for zero win, 2 for draw and 3 for TBD
    bool is_draw() const;

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
    std::vector<int> gen_moves();

    std::vector<int> history;
};

/**
 * Position of the move
 * 
 * 0 1 2
 * 3 4 5
 * 6 7 8
 * 
 * 1 1 1   0 0 0   0 0 0   1 0 0   0 1 0   0 0 1   1 0 0   0 0 1
 * 0 0 0   1 1 1   0 0 0   1 0 0   0 1 0   0 0 1   0 1 0   0 1 0
 * 0 0 0   0 0 0   1 1 1   1 0 0   0 1 0   0 0 1   0 0 1   1 0 0
*/
static constexpr int win_pos[] = {
    7, 56, 448, 73, 146, 292, 273, 84
};