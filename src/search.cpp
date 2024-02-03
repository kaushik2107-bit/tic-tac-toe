#include "search.h"
#include "position.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <chrono>

int negamax(SearchData& sd, int alpha, int beta, int depth) {
    sd.nodes++;
    if (sd.pos->is_over() == 2) {
        return 0;
    } else if (sd.pos->is_over() == 1) {
        return 100 * depth * (sd.pos->get_turn() ? 1 : -1);
    } else if (sd.pos->is_over() == 0) {
        return 100 * depth * (sd.pos->get_turn() ? -1 : 1);
    }

    if (depth <= 0) return 0;

    int best_score = std::numeric_limits<int>::min();
    std::vector<int> moves = sd.pos->gen_moves();

    if (moves.size() == 0) return 0;

    int move_count = 0;

    for (int move: moves) {
        sd.pos->do_move(move);
        sd.ply++;
        move_count++;
        int score = -negamax(sd, -beta, -alpha, depth-1);
        sd.pos->undo_move();
        sd.ply--;
        
        if (sd.ply == 0) {
            sd.rootmoves[move_count-1].score = score;
        }

        if (score > best_score) {
            best_score = score;

            if (alpha > best_score) {
                alpha = best_score;
            }

            if (alpha >= beta) break;
        }
    }

    return best_score;
}

int search(SearchData& sd) {
    std::vector<int> moves = sd.pos->gen_moves();
    sd.rootmoves.clear();
    sd.nodes = 0;
    sd.ply = 0;

    for (int i=0; i<(int)moves.size(); i++) {
        RootMove rm;
        rm.score = 0;
        rm.move = moves[i];
        sd.rootmoves.push_back(rm);
    }

    auto start = std::chrono::high_resolution_clock::now();
    int score = negamax(sd, -1000, 1000, 9);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    sort(sd.rootmoves.begin(), sd.rootmoves.end(), [](RootMove r1, RootMove r2) {
        return r1.score > r2.score;
    });

    std::cout << std::endl;
    std::cout << "bestmove " << sd.rootmoves[0].move << " score " << score << " time " << duration / 1000 << std::endl;
    return sd.rootmoves[0].move;
}