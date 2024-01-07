from GameNode import GameNode
import random

def alpha_beta(node: GameNode, depth, alpha, beta, maximizingPlayer, current_moves):
    if depth == 0 or node.is_terminal():
        return node.evaluate_prev_node(), current_moves

    if maximizingPlayer:
        value = -float('inf')
        best_path = []
        for move in node.generate_moves():
            child_node = GameNode(node.matrix, node.player_turn, node.our_global_team, node.move_history, depth-1, node.heuristic)
            child_node.apply_move(move[1][0])
            new_value, path = alpha_beta(child_node, depth - 1, alpha, beta, False, current_moves + [move])
            if new_value > value or (new_value == value and len(path) < len(best_path)):
                value = new_value
                best_path = path
            alpha = max(alpha, value)
            if beta <= alpha:
                break
        return value, best_path
    else:
        value = float('inf')
        best_path = []
        for move in node.generate_moves():
            child_node = GameNode(node.matrix, node.player_turn, node.our_global_team, node.move_history, depth-1, node.heuristic)
            child_node.apply_move(move[1][0])
            new_value, path = alpha_beta(child_node, depth - 1, alpha, beta, True, current_moves + [move])
            if new_value < value or (new_value == value and len(path) < len(best_path)):
                value = new_value
                best_path = path
            beta = min(beta, value)
            if beta <= alpha:
                break
        return value, best_path

def find_best_move_shortpath(node: GameNode, depth):
    best_move = None
    best_value = -float('inf')
    best_path = None
    for move in node.generate_moves():
        child_node = GameNode(node.matrix, node.player_turn, node.our_global_team, node.move_history, depth, node.heuristic)
        child_node.apply_move(move[1][0])
        value, path = alpha_beta(child_node, depth, -float('inf'), float('inf'), False, [move])
        if value > best_value or (value == best_value and len(path) < len(best_path)):
            best_value = value
            best_path = path
            best_move = move
    print("Best move path:", best_path)
    return best_move
