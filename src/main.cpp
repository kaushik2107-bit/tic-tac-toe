#include <iostream>
#include "position.h"
#include "search.h"

int main() {
    // Position pos(19, 324);
    // Position pos(3, 20);
    Position pos;
    int p;
    std::cout << pos << std::endl;

    SearchData sd;
    sd.pos = &pos;

back:
    std::cout << "Tic Tac Toe Game: " << std::endl;
    std::cout << "1. Enter 1 for computer to start" << std::endl;
    std::cout << "2. Enter 0 for you to start" << std::endl;

    int turn;
    std::cin >> turn;

    if (turn != 1 && turn != 0) {
        goto back;
    }

    while (true) {
        int end = sd.pos->is_over();
        if (end == 3) {
            if (sd.pos->get_turn() == turn) {
                int best_move = search(sd);

                sd.pos->do_move(best_move);
                std::cout << *sd.pos << std::endl;
            } else {
                std::cout << "Enter your move: ";
                std::cin >> p;
                sd.pos->do_move(p);
                std::cout << *sd.pos << std::endl;
            }
        } else if (end == 2) {
            std::cout << "Game ended!!\n";
            std::cout << "Result: Draw (1/2 - 1/2)\n";
            break;
        } else if (end == 1) {
            std::cout << "Game ended!!\n";
            std::cout << "Result: Cross Wins (1 - 0)\n";
            break;
        } else if (end == 0) {
            std::cout << "Game ended!!\n";
            std::cout << "Result: Zero wins (0 - 1)\n";
            break;
        }
    }

    // while (true) {
    //     int end = pos.is_over();
    //     if (end == 3) {
    //         std::cout << "Enter move: ";
    //         std::cin >> p;
    //         pos.do_move(p);
    //         std::cout << pos << std::endl;
    //     } else if (end == 2) {
    //         std::cout << "Game ended!!\n";
    //         std::cout << "Result: Draw (1/2 - 1/2)\n";
    //         break;
    //     } else if (end == 1) {
    //         std::cout << "Game ended!!\n";
    //         std::cout << "Result: Cross Wins (1 - 0)\n";
    //         break;
    //     } else if (end == 0) {
            // std::cout << "Game ended!!\n";
            // std::cout << "Result: Zero wins (0 - 1)\n";
            // break;
    //     }
    // }
    
    return 0;
}