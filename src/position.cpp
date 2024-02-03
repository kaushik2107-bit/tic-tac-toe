#include <cassert>
#include <iostream>
#include "position.h"

/**
 * Position of the move
 * 
 * 0 1 2
 * 3 4 5
 * 6 7 8
*/
void Position::do_move(int8_t pos) {
    assert(pos >= 0 && pos <= 8);
    if (pos < 0 || pos > 8) {
        std::cerr << "Illegal move: " << pos << " (Position should be between 0 and 8)" << std::endl;
        return;
    }

    if (both & (1 << pos)) {
        std::cerr << "Illegal move: " << pos << " (Move already played)" << std::endl;
        return;
    }

    history.push_back(pos);

    switch(turn) {
        case 1:
            cross |= (1 << pos);
            both = cross | zero;
            break;
        case 0:
            zero |= (1 << pos);
            both = cross | zero;
            break;
        default:
            break;
    }
    turn ^= 1;
}

void Position::undo_move() {
    int last_move = history.back();
    history.pop_back();

    turn ^= 1;

    switch(turn) {
        case 1:
            cross &= ~(1 << last_move);
            both = cross | zero;
            break;
        case 0:
            zero &= ~(1 << last_move);
            both = cross | zero;
            break;
        default:
            break;
    }
}

int Position::is_over() const {
    bool x=false, o=false;
    for (const int& p: win_pos) {
        if ((p & zero) == p) { o = true; break; }
        if ((p & cross) == p) { x = true; break; }
    }
    if (x) return 1;
    else if (o) return 0;
    
    if (both == 511) return 2;
    return 3;
}

bool Position::is_draw() const {
    return is_over() == 2;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "+---+---+---+\n";
    for (int i=0; i<9; ++i) {
        os << "|";
        if (pos.get_zero() & (1 << i)) { os << " O "; }
        else if (pos.get_cross() & (1 << i)) { os << " X "; }
        else { os << "   "; }
        if (i % 3 == 2) {
            os << "| " << 3 - i/3;
            os << "\n+---+---+---+\n";
        }
    }

    os << "  a   b   c  \n";

    os << "\n";
    os << "Cross Key: " << pos.get_cross() << "\n";
    os << "Zero Key: " << pos.get_zero() << "\n";
    os << "Both Key: " << pos.get_both() << "\n";
    return os;
}

std::vector<int> Position::gen_moves() {
    std::vector<int> moves;
    if (is_over() != 3) return moves;
    
    for (int i=0; i<9; ++i) {
        if ((both & (1 << i)) == 0) {
            moves.push_back(i);
        }
    }
    return moves;
}