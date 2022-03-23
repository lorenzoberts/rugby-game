/**
 * miniep1 - attacker.c
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
#include "field.h"
#include "game.h"
// Main header
#include "attacker.h"


// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter


/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS HEADERS                     */
/*----------------------------------------------------------------------------*/

/**
 * Função que recebe duas posições (current e last) e devolve a direção necessária 
 *  para chegar de current para last.
 */ 
direction_t determine_direction_attacker(position_t current,position_t last);

/**
 * Função que recebe uma direção e devolve a direção oposta.
 * 
 */ 
direction_t oposite_direction_attacker(direction_t current);

/**
 * Função que recebe duas direções e verifica se são iguais.
 */ 
bool equal_directions_attacker(direction_t dir1, direction_t dir2);


/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/


direction_t execute_attacker_strategy(
position_t attacker_position, Spy defender_spy) {

    // Variável que armazena a última posição do atacante
    static position_t last_position_attacker = {.i = 0, .j = 0};
    static int rodada = 0;

    rodada++;

    // Inicializa a semente de aleatoriedade para cada jogo.
    if (last_position_attacker.i == 0 && last_position_attacker.j == 0){
        time_t t;
        srand(time(&t));  
    }

    // Se na penúltima rodada o atacante e defensor estiverem na mesma linha, o atacante é forçado a mudar de linha.
    if (rodada == 40){
        position_t defender_pos = get_spy_position(defender_spy);  
        if (defender_pos.i == attacker_position.i){
            // Última posição é atualizada
            last_position_attacker.i = attacker_position.i;
            last_position_attacker.j = attacker_position.j;

            if (attacker_position.i > 1){
                return (direction_t) DIR_UP;
            }
            else return (direction_t) DIR_DOWN;
        }
    }

    int random_direction;
    direction_t directions_to_move[11] = {DIR_RIGHT, DIR_RIGHT,DIR_RIGHT,
                                        DIR_UP, DIR_UP,
                                        DIR_DOWN, DIR_DOWN,
                                        DIR_UP_LEFT,
                                        DIR_UP_RIGHT,
                                        DIR_DOWN_LEFT,
                                        DIR_DOWN_RIGHT};


    // Quando o atacante encontra alguma barreira ele precisa escolher outra direção para andar, sem contar a última que o fez chegar na barreira. 
    if (equal_positions(attacker_position,last_position_attacker)){
        direction_t last_direction = determine_direction_attacker(attacker_position,last_position_attacker);

        random_direction = rand() % 11;
        while (equal_directions_attacker(directions_to_move[random_direction],oposite_direction_attacker(last_direction))){
            random_direction = rand() % 11;
        }

        // Última posição é atualizada
        last_position_attacker.i = attacker_position.i;
        last_position_attacker.j = attacker_position.j;
        return directions_to_move[random_direction];

    }  
    
    // O movimento do atacante é aleatório dentro da lista de direções
    random_direction = rand() % 11;
    direction_t direction = directions_to_move[random_direction];  


    // Última posição é atualizada
    last_position_attacker.i = attacker_position.i;
    last_position_attacker.j = attacker_position.j;

    return direction;
}

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/


direction_t determine_direction_attacker(position_t current,position_t last){
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

direction_t oposite_direction_attacker(direction_t current){
    if (equal_directions_attacker(current,(direction_t) DIR_DOWN)) return (direction_t) DIR_UP;
    else if (equal_directions_attacker(current,(direction_t) DIR_UP)) return (direction_t) DIR_DOWN;
    else if (equal_directions_attacker(current,(direction_t) DIR_LEFT)) return (direction_t) DIR_RIGHT;
    else if (equal_directions_attacker(current,(direction_t) DIR_RIGHT)) return (direction_t) DIR_LEFT;
    else if (equal_directions_attacker(current,(direction_t) DIR_UP_RIGHT)) return (direction_t) DIR_DOWN_LEFT;
    else if (equal_directions_attacker(current,(direction_t) DIR_DOWN_RIGHT)) return (direction_t) DIR_UP_LEFT;
    else if (equal_directions_attacker(current,(direction_t) DIR_UP_LEFT)) return (direction_t) DIR_DOWN_RIGHT;
    else if (equal_directions_attacker(current,(direction_t) DIR_DOWN_LEFT)) return (direction_t) DIR_UP_RIGHT;
    else return (direction_t) DIR_STAY;

}

/*----------------------------------------------------------------------------*/

bool equal_directions_attacker(direction_t dir1, direction_t dir2){
    if (dir1.i == dir2.i && dir1.j == dir2.j) return true;
    return false;
}


/*----------------------------------------------------------------------------*/


