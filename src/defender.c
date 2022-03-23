/**
 * miniep1 - defender.c
 * Nome: Lorenzo Bertin Salvador
 * Nusp: 11795356
 * Disciplina: MAC0218
 */ 


// Standard headers
#include <stdio.h>

// Strategy related headers
#include <stdlib.h>
#include <time.h> 

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS HEADERS                     */
/*----------------------------------------------------------------------------*/

/**
 * Função que recebe duas posições (current e last) e devolve a direção necessária 
 *  para chegar de current para last.
 */ 
direction_t determine_direction_defender(position_t current,position_t last);

/**
 * Função que recebe duas direções e verifica se são iguais.
 */ 
bool equal_directions_defender(direction_t dir1, direction_t dir2);

/**
 * Função que decide a nova direção do defensor baseado no último movimento
 */ 
direction_t defender_route(position_t current, position_t last);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

    // A estratégia não utiliza o spy.
    UNUSED(attacker_spy);

    // Variável que armazena a última posição do defensor
    static position_t last_position_defender = {.i = 0, .j = 0};

    // Inicializa a semente de aleatoriedade e movimenta o defensor para a esquerda.
    if (last_position_defender.i == 0 && last_position_defender.j == 0){
        time_t t;
        srand(time(&t));
        // Atualiza a última posição  
        last_position_defender.i = defender_position.i;
        last_position_defender.j = defender_position.j;
        return (direction_t) DIR_LEFT;
    }


    // Quando o defensor encontra uma barreira e está na rota "ideal", ele inverte o sentido de seu movimento.
    // Se ele não está na rota, escolhe aleatoriamente qualquer movimento (sem contar o movimento que o faria permanecer preso).
    if (equal_positions(defender_position,last_position_defender)){

        if (equal_directions_defender(determine_direction_defender(defender_position,last_position_defender),(direction_t) DIR_DOWN_LEFT) || equal_directions_defender(determine_direction_defender(defender_position,last_position_defender),(direction_t) DIR_DOWN_RIGHT)){
            last_position_defender.i = defender_position.i;
            last_position_defender.j = defender_position.j;
            return (direction_t) DIR_UP;
        }
        else if (equal_directions_defender(determine_direction_defender(defender_position,last_position_defender),(direction_t) DIR_UP_LEFT) || equal_directions_defender(determine_direction_defender(defender_position,last_position_defender),(direction_t) DIR_UP_RIGHT)){
            last_position_defender.i = defender_position.i;
            last_position_defender.j = defender_position.j;
            return (direction_t) DIR_DOWN;
        }
        else{
            direction_t directions_to_move[7] = {DIR_LEFT,DIR_UP,DIR_DOWN,DIR_UP_RIGHT,DIR_DOWN_RIGHT,DIR_UP_LEFT,DIR_UP_RIGHT};
            direction_t direction = directions_to_move[rand()%7];
            while (equal_directions_defender(direction,determine_direction_defender(defender_position,last_position_defender))){
                direction = directions_to_move[rand()%7];
            }
            return direction;
        }

    }

    // Determina a próxima direção
    direction_t direction = defender_route(defender_position,last_position_defender);

    // Atualiza a última posição
    last_position_defender.i = defender_position.i;
    last_position_defender.j = defender_position.j;

    return direction;
}


/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t determine_direction_defender(position_t current,position_t last){
    if (current.i > last.i && current.j == last.j) return (direction_t) DIR_DOWN;
    else if (current.i > last.i && current.j > last.j) return (direction_t) DIR_DOWN_RIGHT;
    else if (current.i > last.i && current.j < last.j) return (direction_t) DIR_DOWN_LEFT;
    else if (current.i < last.i && current.j == last.j) return (direction_t) DIR_UP;
    else if (current.i < last.i && current.j > last.j) return (direction_t) DIR_UP_RIGHT;
    else if (current.i < last.i && current.j < last.j) return (direction_t) DIR_UP_LEFT;
    else if (current.i == last.i && current.j == last.j) return (direction_t) DIR_STAY;
    else if (current.i == last.i && current.j > last.j) return (direction_t) DIR_RIGHT;
    else if (current.i == last.i && current.j < last.j) return (direction_t) DIR_LEFT;
    else return (direction_t) DIR_STAY;
    
}

/*----------------------------------------------------------------------------*/

bool equal_directions_defender(direction_t dir1, direction_t dir2){
    if (dir1.i == dir2.i && dir1.j == dir2.j) return true;
    return false;
}

/*----------------------------------------------------------------------------*/

direction_t defender_route(position_t current, position_t last){
    if (equal_directions_defender(determine_direction_defender(current,last),(direction_t) DIR_UP_LEFT)){
        return (direction_t) DIR_UP_RIGHT;
    }
    else if (equal_directions_defender(determine_direction_defender(current,last),(direction_t) DIR_UP_RIGHT)){
        return (direction_t) DIR_UP_LEFT;
    }
    else if (equal_directions_defender(determine_direction_defender(current,last),(direction_t) DIR_DOWN_LEFT)){
        return (direction_t) DIR_DOWN_RIGHT;
    }
    else if (equal_directions_defender(determine_direction_defender(current,last),(direction_t) DIR_DOWN_RIGHT)){
        return (direction_t) DIR_DOWN_LEFT;
    }
    else if (equal_directions_defender(determine_direction_defender(current,last),(direction_t) DIR_LEFT)){
        return (direction_t) DIR_UP_LEFT;
    }
    else if (equal_directions_defender(determine_direction_defender(current,last),(direction_t) DIR_DOWN)){
        if (rand() % 2 == 0){
            return (direction_t) DIR_DOWN_LEFT;
        }
        return (direction_t) DIR_DOWN_RIGHT;
    }
    return (direction_t) DIR_DOWN;
}

/*----------------------------------------------------------------------------*/

