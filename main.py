import time
import numpy as np

from client import ClientSocket
from argparse import ArgumentParser

def generate_matrix(r, c):
    matrix = np.empty((r, c), dtype=object)
    
    for i in range(r):
        for j in range(c):
            matrix[i, j] = ('Empty', 0)
    
    return matrix

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
    # print(matrix)


def play_game(args):
    client_socket = ClientSocket(args.ip, args.port)
    client_socket.send_nme("testname")

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


    # start of the game
    # while True:
    #     message  = client_socket.get_message()
    #     time_message_received = time.time()
    #     UPDATE_GAME_STATE(message)
    #     if message[0] == "upd":
    #         nb_moves, moves = COMPUTE_NEXT_MOVE(GAME_STATE)
    #         client_socket.send_mov(nb_moves, moves)


if __name__ == '__main__':
    parser = ArgumentParser()

    parser.add_argument(dest='ip', default='localhost', type=str, help='IP adress the connection should be made to.')
    parser.add_argument(dest='port', default='5555', type=int, help='Chosen port for the connection.')

    args = parser.parse_args()
    
    play_game(args)