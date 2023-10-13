import time

from client import ClientSocket
from argparse import ArgumentParser

def COMPUTE_NEXT_MOVE():
    #Should check the current state of the game and get the positions of player

    #Determine the next moves based on the global strategy (or set random move at the begening)
    #The move must be valid

    #Return the number of moves and moves 
    return nb_moves, moves

def UPDATE_GAME_STATE(message):
    #UPDATE THE CURRENT BOARD GAME

    return 0

def play_game(args):
    print("Play game")
    client_socket = ClientSocket(args.ip, args.port)
    client_socket.send_nme("DOMINATORIX")
    # set message
    message = client_socket.get_message()
    print("message >>> ", message)
    
    #UPDATE_GAME_STATE(message)
    # hum message
    message = client_socket.get_message()
    print("message >>> ", message)
    #UPDATE_GAME_STATE(message)
    # hme message
    message = client_socket.get_message()
    print("message >>> ", message)
    #UPDATE_GAME_STATE(message)
    # map message
    message = client_socket.get_message()
    print("message >>> ", message)
    #UPDATE_GAME_STATE(message)
    
    pos_x = 2
    pos_y = 3
    client_socket.send_mov(1, [(pos_x, pos_y, 2, pos_x, pos_y-1)])
    
    """
    #UPDATE_GAME_STATE(message)
    # hum message
    message = client_socket.get_message()
    print("message >>> ", message)
    #UPDATE_GAME_STATE(message)
    # hme message
    message = client_socket.get_message()
    print("message >>> ", message)
    #UPDATE_GAME_STATE(message)
    # map message
    message = client_socket.get_message()
    print("message >>> ", message)
    #UPDATE_GAME_STATE(message)
    """

    """
    # start of the game
    while True:
        message  = client_socket.get_message()
        time_message_received = time.time()
        #UPDATE_GAME_STATE(message)
        if message[0] == "upd":
            nb_moves, moves = COMPUTE_NEXT_MOVE()
            client_socket.send_mov(nb_moves, moves)
            pass
    """


if __name__ == '__main__':
    parser = ArgumentParser()

    parser.add_argument(dest='ip', default='localhost', type=str, help='IP adress the connection should be made to.')
    parser.add_argument(dest='port', default='8080', type=int, help='Chosen port for the connection.')

    args = parser.parse_args()
    
    play_game(args)
