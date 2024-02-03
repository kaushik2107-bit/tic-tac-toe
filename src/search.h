#pragma once

#include <vector>

class Position;

struct RootMove {
    int move;
    int score;
};

struct SearchData {
    Position* pos;
    int nodes = 0;
    int ply = 0;
    std::vector<RootMove> rootmoves;
};

int negamax(SearchData& sd, int alpha, int beta, int depth);

int search(SearchData& sd);