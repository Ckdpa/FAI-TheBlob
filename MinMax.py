from GameNode import GameNode
import random

def MinMax(node : GameNode, depth, maximizingPlayer):
    # Check if the game is over
    if depth == 0 or node.is_terminal():
        # if node.is_terminal():
        #     print("GAME END FOUND")
        #     print(node.matrix)
        # else:
        #     print("Max Depth")
        # print("Node Depth")
        # print(node.depth)
        # print("Node value: ")
        # print(node.evaluate_prev_node())
        return node.evaluate_prev_node()
    
    # Check if the node is a maximizing node
    if maximizingPlayer:
        value = -float('inf')
        for move in node.generate_moves():
            # Create a child by copying, then applying move
            child_node = GameNode(node.matrix, node.player_turn, node.our_global_team, node.move_history, depth-1, node.heuristic)
            child_node.apply_move(move[1][0]) #TODO ignoring nb_moves for now, change this later for splits
            value = max(value, MinMax(child_node, depth - 1, False))
        return value
    # For minimzing node (aka global enemy)
    else:
        value = float('inf')
        for move in node.generate_moves():
            child_node = GameNode(node.matrix, node.player_turn, node.our_global_team, node.move_history, depth-1, node.heuristic)
            child_node.apply_move(move[1][0])
            value = min(value, MinMax(child_node, depth - 1, True))
        return value

# Initial call
def find_best_minmax(node: GameNode, depth):
    # print("=======  Starting AB  =======")
    best_move = None
    best_value = -float('inf')
    for move in node.generate_moves():
        child_node = GameNode(node.matrix, node.player_turn, node.our_global_team, node.move_history, depth, node.heuristic)
        # print('first move:')
        # print(move)
        child_node.apply_move(move[1][0])
        value = MinMax(child_node, depth, False)
        # print('Current Move: ')
        # print(move)
        # print('Current Value: ')
        # print(value)
        if value > best_value:
            best_move = move
            best_value = value
        if value == best_value and random.randint(0,1) == 1:
            best_move = move
            best_value = value
    return best_move
