from GameNode import GameNode

def alpha_beta(node : GameNode, depth, alpha, beta, maximizingPlayer):
    # Check if the game is over
    if depth == 0 or node.is_terminal():
        if node.is_terminal():
            print("GAME END FOUND")
        return node.evaluate()
    
    # Check if the node is a maximizing node
    if maximizingPlayer:
        value = -float('inf')
        for move in node.generate_moves():
            # Create a child by copying, then applying move
            child_node = GameNode(node.matrix, node.player_turn)
            child_node.apply_move(move[1][0]) #TODO ignoring nb_moves for now, change this later for splits
            value = max(value, alpha_beta(child_node, depth - 1, alpha, beta, False))
            alpha = max(alpha, value)
            if beta <= alpha:
                break  # Beta cut-off
        return value
    # For minimzing node (aka global enemy)
    else:
        value = float('inf')
        for move in node.generate_moves():
            child_node = GameNode(node.matrix, node.player_turn)
            child_node.apply_move(move[1][0])
            value = min(value, alpha_beta(child_node, depth - 1, alpha, beta, True))
            beta = min(beta, value)
            if beta <= alpha:
                break  # Alpha cut-off
        return value

# Initial call
def find_best_move(node: GameNode, depth):
    best_move = None
    best_value = -float('inf')
    for move in node.generate_moves():
        child_node = GameNode(node.matrix, node.player_turn)
        print('first move:')
        print(move)
        child_node.apply_move(move[1][0])
        value = alpha_beta(child_node, depth, -float('inf'), float('inf'), False)
        if value > best_value:
            best_move = move
            best_value = value
    return best_move
