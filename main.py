import time

from client import ClientSocket
from argparse import ArgumentParser
from enum import Enum
import random
import numpy as np

"""
-------------------------------------------------------------------------------------
- GENERATE MATRIX FOR INIT
-------------------------------------------------------------------------------------
"""
def generate_matrix(r, c):
    matrix = np.empty((r, c), dtype=object)
    for i in range(r):
        for j in range(c):
            matrix[i, j] = ('Empty', 0)
    return matrix

"""
-------------------------------------------------------------------------------------
- SIMULATE COMBAT
-------------------------------------------------------------------------------------
"""
def calculate_probability(E1, E2):
    if E1 == E2:
        return 0.5
    elif E1 < E2:
        return E1 / (2 * E2)
    else:
        return (E1 / E2) - 0.5

def simulate_battle(E1, E2, attacking_species):
    P = calculate_probability(E1, E2)
    if np.random.random() < P:
        survivors = np.random.binomial(E1, P)
        return (attacking_species, survivors if survivors > 0 else 0)
    else:
        survivors = np.random.binomial(E2, 1 - P)
        return ('human' if attacking_species in ['vampire', 'werewolf'] else attacking_species, survivors)

"""
-------------------------------------------------------------------------------------
- ALPHA BETA
-------------------------------------------------------------------------------------
"""
class Strategy:
    ATK = 1
    DEF = 2

SPECIES = {'vampire': 1, 'werewolf': 2, 'human': 0, 'Empty': None}

def heuristic(matrix, our_team):
    our_count = 0
    enemy_count = 0
    human_count = 0
    for y, row in enumerate(matrix):
        for x, (species, count) in enumerate(row):
            if species == our_team:
                our_count += count
            elif species == 'human':
                human_count += 100 * count
            elif species != 'Empty' and species != our_team:
                enemy_count += count

    score = our_count + human_count - enemy_count
    return score

# Implementation of the Alpha-Beta pruning algorithm
def max_value(state, alpha, beta, depth, player, start_time, time_limit, depth_reached, move_list):
    if depth == 0 or is_terminal(state) or time.time() - start_time > time_limit:
        return heuristic(state, player), depth, move_list
    value = float('-inf')
    best_path = None
    for move in generate_moves(state, player):
        if time.time() - start_time > time_limit:
            return heuristic(state, player), depth, move_list
        new_state = result(state, move)
        new_value, child_depth, path = min_value(new_state, alpha, beta, depth-1, player, start_time, time_limit, depth_reached, move_list + [move])
        if new_value > value:
            value = new_value
            best_path = path
            depth_reached = max(depth_reached, child_depth)
        if value >= beta:
            return value, depth_reached, best_path
        alpha = max(alpha, value)
    return value, depth_reached, best_path if best_path else move_list

def min_value(state, alpha, beta, depth, player, start_time, time_limit, depth_reached, move_list):
    if depth == 0 or is_terminal(state) or time.time() - start_time > time_limit:
        return -heuristic(state, player), depth, move_list
    value = float('inf')
    best_path = None
    for move in generate_moves(state, player):
        if time.time() - start_time > time_limit:
            return -heuristic(state, player), depth, move_list
        new_state = result(state, move)
        new_value, child_depth, path = max_value(new_state, alpha, beta, depth-1, player, start_time, time_limit, depth_reached, move_list + [move])
        if new_value < value:
            value = new_value
            best_path = path
            depth_reached = max(depth_reached, child_depth)
        if value <= alpha:
            return value, depth_reached, best_path
        beta = min(beta, value)
    return value, depth_reached, best_path if best_path else move_list


def alpha_beta_search(state, depth, player, time_limit):
    start_time = time.time()
    best_score = float('-inf')
    alpha = float('-inf')
    beta = float('inf')
    best_move = None
    best_path = []  # To keep track of the best path
    depth_reached = 0
    
    for move in generate_moves(state, player):
        if time.time() - start_time > time_limit:
            break
        
        value, child_depth, path = min_value(result(state, move), alpha, beta, depth-1, player, start_time, time_limit, depth_reached, [move])
        depth_reached = max(depth_reached, child_depth)
        if value > best_score:
            best_score = value
            best_move = move
            best_path = path  # Update the best path
    
    print(f"Best Path: {best_path}, Best Score: {best_score}")
    return best_move, depth_reached

def is_terminal(state):
    species_present = set()
    for row in state:
        for cell in row:
            species_present.add(cell[0])
    return len(species_present - {0}) <= 1

def result(state, move):
    new_state = [list(row) for row in state]
    cur_x, cur_y, nb_creatures, new_x, new_y = move
    moving_species = new_state[cur_y][cur_x][0]
    moving_count = new_state[cur_y][cur_x][1]
    nb_creatures = min(nb_creatures, moving_count)
    new_state[cur_y][cur_x] = (moving_species, moving_count - nb_creatures)
    target_species, target_count = new_state[new_y][new_x]

    if target_species == 'human' and nb_creatures >= target_count:
        new_state[new_y][new_x] = (moving_species, target_count + nb_creatures)
    elif target_species == 'Empty':
        new_state[new_y][new_x] = (moving_species, nb_creatures)
    elif target_species != moving_species:
        victorious_species, surviving_count = simulate_battle(nb_creatures, target_count, moving_species)
        new_state[new_y][new_x] = (victorious_species, surviving_count)

    if new_state[cur_y][cur_x][1] == 0:
        new_state[cur_y][cur_x] = ('Empty', 0)

    return new_state

def generate_moves(state, our_species):
    conversion_moves = []
    other_moves = []
    for y, row in enumerate(state):
        for x, (species, count) in enumerate(row):
            if species == our_species:
                for dx in [-1, 0, 1]:
                    for dy in [-1, 0, 1]:
                        if dx == 0 and dy == 0:
                            continue
                        new_x, new_y = x + dx, y + dy
                        if 0 <= new_x < len(row) and 0 <= new_y < len(state):
                            target_species, target_count = state[new_y][new_x]
                            if target_species == 'human':
                                # Check if it's a conversion or a potential conversion move
                                if count >= target_count:
                                    conversion_moves.append((x, y, count, new_x, new_y))
                                else:
                                    # Add to other moves if it's not an immediate conversion but has potential
                                    other_moves.append((x, y, count, new_x, new_y))
                            elif target_species == 'Empty' or target_species != our_species:
                                other_moves.append((x, y, count, new_x, new_y))
    # Prioritize conversion moves
    return conversion_moves + other_moves

"""
-------------------------------------------------------------------------------------
- COMPUTE NEXT MOVE
-------------------------------------------------------------------------------------
"""
def COMPUTE_NEXT_MOVE(matrix, our_team):
    best_move, depth = alpha_beta_search(matrix, 15, our_team, 1.8)
    nb_moves = 1 if best_move else 0
    print(best_move, depth)
    return nb_moves, [best_move]

"""
-------------------------------------------------------------------------------------
- UPDATE GAME STATE
-------------------------------------------------------------------------------------
"""
def UPDATE_GAME_STATE(message,matrix,hme):
    cmd = message[0]
    value = message[1]
    if cmd == 'set':
        matrix = generate_matrix(value[0],value[1])
        return matrix
    if cmd == 'hme':
        return value

    if cmd == 'map':
        for element in value:
            c = element[0]
            r = element[1]
            h = element[2]
            v = element[3]
            w = element[4]
            if h > 0:
                matrix[r][c] = ('human', h)
            if v > 0:
                matrix[r][c] = ('vampire', v)
            if w > 0:
                matrix[r][c] = ('werewolf', w)
    
        our_team = matrix[hme[1]][hme[0]][0]
        return matrix, our_team
    
    if cmd == 'upd':
        if(value == []):
            return
        for element in value:
            c = element[0]
            r = element[1]
            h = element[2]
            v = element[3]
            w = element[4]
            if h > 0:
                matrix[r][c] = ('human', h)
            if v > 0:
                matrix[r][c] = ('vampire', v)
            if w > 0:
                matrix[r][c] = ('werewolf', w)
            if(h == 0 and v == 0 and w == 0):
                matrix[r][c] = ('Empty', 0)

        return matrix

"""
-------------------------------------------------------------------------------------
- PLAY GAME
-------------------------------------------------------------------------------------
"""
def play_game(args):
    client_socket = ClientSocket(args.ip, args.port)
    name = input("Player name:")
    client_socket.send_nme(name)
    
    # Init matrix
    matrix = []
    hme = []

    # set message
    message = client_socket.get_message()
    matrix  = UPDATE_GAME_STATE(message,matrix,hme)
    # hum message
    message = client_socket.get_message()
    # UPDATE_GAME_STATE(message)
    # hme message
    message = client_socket.get_message()
    hme = UPDATE_GAME_STATE(message,matrix,hme)
    # map message
    message = client_socket.get_message()
    matrix, our_team = UPDATE_GAME_STATE(message,matrix,hme)

    # start of the game
    while True:
        # time.sleep(0.5)
        message = client_socket.get_message()
        time_message_received = time.time()
        # upd message
        UPDATE_GAME_STATE(message,matrix,hme)
        if message[0] == "upd":
            nb_moves, moves = COMPUTE_NEXT_MOVE(matrix, our_team)
            client_socket.send_mov(nb_moves, moves)
            pass

"""
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- MAIN
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
"""
if __name__ == '__main__':
    parser = ArgumentParser()

    parser.add_argument(dest='ip', default='localhost', type=str, help='IP adress the connection should be made to.')
    parser.add_argument(dest='port', default='8080', type=int, help='Chosen port for the connection.')

    args = parser.parse_args()
    
    play_game(args)