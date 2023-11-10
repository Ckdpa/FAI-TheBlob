import random

class GameState:
    def __init__(self, game_state, maximising, our_team):
        self.game_state = game_state
        self.maximising = maximising
        self.possible_moves = []
        
        # Setup the teams if we are maximising
        self.node_team = our_team
        if our_team == 'werewolf':
            self.their_team = 'vampire'
        else:
            self.their_team = 'werewolf'
        
        # Set the opposite if we are minimising
        if not maximising:
            self.our_team = self.their_team
            self.their_team = our_team

    def static_eval(self):
        score = 1
        return score
    
    def generate_all_moves(self):
        # Returns all possible moves

        # Find the position and number of our creatures
        for i in range(len(self.game_state)):
            for j in range(len(self.game_state[i])):
                if(self.game_state[i][j][0] == self.our_team):
                    current_x = j
                    current_y = i
                    nb_creature = self.game_state[i][j][1]
                    break

        # Define the possible moves
        possible_moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right

        # Generate moves
        legal_deltas = []
        for dx, dy in legal_deltas:
            new_x = current_x + dx
            new_y = current_y + dy
            # Check if the new position is within the bounds of the matrix
            if 0 <= new_x < len(self.game_state[0]) and 0 <= new_y < len(self.game_state):
                legal_deltas.append((dx, dy))

        moves = []

        if legal_deltas:
            for delta in legal_deltas:
                future_delta_x, future_delta_y = delta
                moves.append([(current_x, current_y, nb_creature, current_x+future_delta_x, current_y+future_delta_y)])
        else:
            # No legal moves available
            return 0, []
            
        # Generate the move
        for move in 
        moves = [(current_x, current_y, nb_creature, current_x+future_delta_x, current_y+future_delta_y)]
        nb_move = 1
        return nb_move, moves
    
    def apply_move(self, nb_move, moves):
        

















def minimax(game_state, depth, max_player):
    if depth == 0 or game_state.playing == False:
        return game_state.static_eval()
    
    if max_player:
        max_eval = float('-inf')
        for child in game_state.generate_children():
            eval = minimax(child, depth-1, False)
            max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = float('inf')
        for child in game_state.generate_children():
            eval = minimax(child, depth-1, True)
            min_eval = min(min_eval, eval)
        return min_eval
    
