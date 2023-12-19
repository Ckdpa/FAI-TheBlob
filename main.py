import time

from client import ClientSocket
from argparse import ArgumentParser
from enum import Enum
import random
import numpy as np
import pickle
from GameNode import GameNode
from AlphaBeta import alpha_beta
from AlphaBeta import find_best_move
from MinMax import MinMax
from MinMax import find_best_minmax
from AlphaBeta_ShortPath import find_best_move_shortpath


class Strategy(Enum):
    ATK = 1
    DEF = 2
    COV = 3

def generate_matrix(r, c):
    matrix = np.empty((r, c), dtype=object)
    
    for i in range(r):
        for j in range(c):
            matrix[i, j] = ('Empty', 0)
    
    return matrix

def heuristic(matrix):
    #Determine general strategy, compute general state of the map and determine if we atk, def or cov.
    return Strategy.ATK

def generate_move(strategy, matrix, our_team):
    # Find the position and number of our creatures
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if(matrix[i][j][0] == our_team):
                current_x = j
                current_y = i
                nb_creature = matrix[i][j][1]
                break

    # Define the possible moves
    possible_moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right

    # If we are attacking, determine a legal random move
    if(strategy == Strategy.ATK):
        legal_moves = []
        for dx, dy in possible_moves:
            new_x = current_x + dx
            new_y = current_y + dy
            # Check if the new position is within the bounds of the matrix
            if 0 <= new_x < len(matrix[0]) and 0 <= new_y < len(matrix):
                legal_moves.append((dx, dy))

        # Choose a random legal move
        if legal_moves:
            future_delta_x, future_delta_y = random.choice(legal_moves)
        else:
            # No legal moves available
            return 0, []
        
    # Generate the move
    moves = [(current_x, current_y, nb_creature, current_x+future_delta_x, current_y+future_delta_y)]
    nb_move = 1
    return nb_move, moves

def COMPUTE_NEXT_MOVE(matrix, our_team):
    #Determine the strategy
    strat = heuristic(matrix)

    #Determine the next moves based on the global strategy
    nb_moves, moves = generate_move(strat, matrix, our_team)

    #Update la matrice interne avec le moves

    #Return the number of moves and moves 
    return nb_moves, moves

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

        # print("Updated matrix", matrix)
        return matrix

def save_file(matrix,file_name):
    with open(file_name, 'wb') as file:
        pickle.dump(matrix, file) 


def play_game(args):
    client_socket = ClientSocket(args.ip, args.port)
    name = input("Player name:")
    depth = int(input("Alpha Beta Depth:"))
    heuristic = int(input("Heuristic (1=monster_difference or 2=monster_difference_distance): "))
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
    # print(matrix)
    # Save matrix
    save_file(matrix,"matrix_2.pkl")
    # start of the game
    while True:
        time.sleep(1)
        message = client_socket.get_message()
        time_message_received = time.time()
        # upd message
        UPDATE_GAME_STATE(message,matrix,hme)
        if message[0] == "upd":
            # nb_moves, moves = COMPUTE_NEXT_MOVE(matrix, our_team)
            # nb_moves, moves = find_best_move(GameNode(matrix, our_team, our_team), int(depth))
            save_file(matrix,"last_matrix.pkl")
            nb_moves, moves = find_best_move(GameNode(matrix, our_team, our_team, [], 0, heuristic), depth)
            # print(nb_moves, moves, our_team)
            client_socket.send_mov(nb_moves, moves)
            # print("--MOVES")
            # print(nb_moves, moves)
            pass

if __name__ == '__main__':
    parser = ArgumentParser()

    parser.add_argument(dest='ip', default='localhost', type=str, help='IP adress the connection should be made to.')
    parser.add_argument(dest='port', default='8080', type=int, help='Chosen port for the connection.')

    args = parser.parse_args()
    
    play_game(args)