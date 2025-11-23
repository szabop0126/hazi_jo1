/**
 * @file game.h
 * @brief Ticket ad a játéknek, amelyekben frssíti a játék állapotát.
 */
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
extern volatile bool gameOver;

void gameTick(void);

#endif
