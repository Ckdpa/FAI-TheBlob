import time

from client import ClientSocket
from argparse import ArgumentParser
from enum import Enum
import random
import numpy as np

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

def heuristic():
    #Determine general strategy, compute general state of the map and determine if we atk, def or cov.
    #First random strategy
    return random.choice(list(Strategy))

def generate_move(strategy, matrix, our_team):
    #Determine general strategy, compute general state of the map and determine if we atk, def or cov.
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if(matrix[i][j][0] == our_team):
                current_x = i
                current_y = j
                nb_creature = matrix[i][j][1]
                break
            elif(matrix[i][j][0] == our_team):
                current_x = i
                current_y = j
                nb_creature = matrix[i][j][1]
                break
    
    print("current position x >>> ", current_x)
    print("current position y >>> ", current_y)
    print("current nb_creature >>> ", nb_creature)
    possible_move = [0, 1, -1]
    nb_move = 1
    future_delta_x = random.choice(list(possible_move))
    future_delta_y = random.choice(list(possible_move))
    print(future_delta_x, future_delta_y)
    moves = [(current_y, current_x, nb_creature, current_y+future_delta_x, current_x+future_delta_y)]
    return nb_move, moves

def COMPUTE_NEXT_MOVE(matrix, our_team):
    #Determine the strategy
    strat = heuristic()
    print("------------------------ ")
    print(f"- strat: {strat} -")
    print("------------------------ ")

    #Determine the next moves based on the global strategy
    nb_moves, moves = generate_move(strat, matrix, our_team)

    #Return the number of moves and moves 
    return nb_moves, moves

def UPDATE_GAME_STATE(message,matrix,hme):
    cmd = message[0]
    value = message[1]
    if cmd == 'set':        
        print('UPDATING GAME STATE: ' + cmd)
        matrix = generate_matrix(value[0],value[1])
        print(matrix)
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
                print(" ----- vampire location: ")
                print('r' + str(r))
                print('c' + str(c))
            if w > 0:
                matrix[r][c] = ('werewolf', w)
                print(" ----- werewolf location: ")
                print('r' + str(r))
                print('c' + str(c))
        print (matrix)
    
        our_team = matrix[hme[1]][hme[0]][0]

        print('our team location')
        print(hme)
        print('our_team:')
        print(our_team)

        return matrix, our_team

def play_game(args):
    print("Play game")
    client_socket = ClientSocket(args.ip, args.port)
    client_socket.send_nme("DOMINATORIX")
    
    # Init matrix
    matrix = []
    hme = []

    # set message
    message = client_socket.get_message()
    print(message)
    matrix  = UPDATE_GAME_STATE(message,matrix,hme)
    # hum message
    message = client_socket.get_message()
    print(message)
    # UPDATE_GAME_STATE(message)
    # hme message
    message = client_socket.get_message()
    print(message)
    hme = UPDATE_GAME_STATE(message,matrix,hme)
    # map message
    message = client_socket.get_message()
    print(message)
    matrix, our_team = UPDATE_GAME_STATE(message,matrix,hme)
    print(matrix)
    
    # pos_x = 2
    # pos_y = 3
    # client_socket.send_mov(1, [(pos_x, pos_y, 2, pos_x, pos_y-1)])

    # start of the game
    while True:
        time.sleep(5)
        message  = client_socket.get_message()
        time_message_received = time.time()
        UPDATE_GAME_STATE(message,matrix,hme)
        if message[0] == "upd":
            nb_moves, moves = COMPUTE_NEXT_MOVE(matrix, our_team)
            print(moves)
            client_socket.send_mov(nb_moves, moves)
            pass

if __name__ == '__main__':
    parser = ArgumentParser()

    parser.add_argument(dest='ip', default='localhost', type=str, help='IP adress the connection should be made to.')
    parser.add_argument(dest='port', default='8080', type=int, help='Chosen port for the connection.')

    args = parser.parse_args()
    
    play_game(args)