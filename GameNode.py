import random

class GameNode:
    def __init__(self, matrix, player_turn):
        self.matrix = matrix  # 2D array representing the game board
        self.player_turn = player_turn  # werewolf / vampire
        # Compute the enemy
        if self.player_turn == 'werewolf':
            self.enemy = 'vampire'
        else:
            self.enemy = 'werewolf'
            
        # self.move_history = move_history if move_history is not None else []  # List of moves made in the game

    def generate_moves(self): # Returns list of legal moves using sendmov format
        # Should output a list of all legal moves for current turn and matrix state
        # Will start by considering no splits

        print("Generating moves")
        
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[i])):
                if(self.matrix[i][j][0] == self.player_turn):
                    current_x = j
                    current_y = i
                    nb_creature = self.matrix[i][j][1]
                    break

        # Define the possible moves
        # TODO add diagonals
        possible_deltas = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right

        legal_deltas = []

        # For now num moves = 1, will need to change for splits
        nb_moves = 1
 
        for dx, dy in possible_deltas:
            new_x = current_x + dx
            new_y = current_y + dy
            # Check if the new position is within the bounds of the matrix
            if 0 <= new_x < len(self.matrix[0]) and 0 <= new_y < len(self.matrix):
                legal_deltas.append((dx, dy))
                print("Legal move: ", dx, dy)

        legal_moves = []
        # Generate move messages with correct format
        for legal_delta in legal_deltas:
            future_delta_x, future_delta_y = legal_delta
            legal_move  = [(current_x, current_y, nb_creature, current_x+future_delta_x, current_y+future_delta_y)]
            legal_moves.append((nb_moves,(legal_move)))


        return legal_moves
        # Generate all legal moves for the current player in this game state
        # You'll need to implement this method based on the rules of your chess-like game.

    def apply_move(self, move): # Seems to be working correctly
        # Givem a single move, this function needs to update it's matrix to show the result
        # This function could be use sequentially when we define mutilple moves per round
        # Also need toggle the self.player turn - however would not work with multiple moves above

        # Parse move
        old_y, old_x = move[0], move[1]
        new_y, new_x = move[3], move[4] # y is top down

        # Save which entity is being moved
        entity = self.matrix[old_x][old_y]
        # Replace with empty cell
        self.matrix[old_x][old_y] = ('Empty', 0)
        # Check what is in the target cell
        target = self.matrix[new_x][new_y]
        if target[0] == 'Empty':
            # Replace the empty cell with the entity
            print("Moving to empty cell")
            self.matrix[new_x][new_y] = entity
        elif target[0] == self.player_turn:
            # Check this later when considering splitting
            print("Grouping")
            self.matrix[new_x][new_y] = (entity[0], entity[1] + target[1])
        elif target[0] == "human":
            print("Attackng Humans")
            # Check if entity has more units than the target
            if entity[1] >= target[1]:
                # Transform humans into current entity
                print("Won Battle")
                self.matrix[new_x][new_y] = (entity[0], entity[1] + target[1])
            else:
                # Perform a random battle
                print("Random Battle!")
                self.matrix[new_x][new_y] = GameNode.simulate_battle(self, entity[1],target[1],True)

        else:
            print("Attacking Opponent")
            # Check if entity has 1.5x more units than the target
            if entity[1] >= 1.5*target[1]:
                print("Won Battle - 1.5")
                self.matrix[new_x][new_y] = entity
            # Check if target has 1.5x more units than the entity
            if target[1] >= 1.5*entity[1]:
                print("Lost Battle - 1.5")
                self.matrix[new_x][new_y] = entity
            else:
                # Perform a random battle
                print("Random Battle!")
                self.matrix[new_x][new_y] = GameNode.simulate_battle(self, entity[1],target[1],False)

    def is_terminal(self):
        # Check is both teams still present
        return not GameNode.check_monsters_presence(self.matrix)
        
        # Check if the game is over (e.g., checkmate, stalemate, or other end conditions)
        # You need to implement this method based on your game's rules.

    def evaluate(self):
        pass
        # Evaluate the current game state and return a numeric score
        # This is your evaluation function, which considers factors like piece values, board control, etc.
        # You need to implement this method.

    def __str__(self):
        pass
        # Optionally, you can implement a method to print a user-friendly representation of the game state.
        # This is useful for debugging and displaying the board to users.

    # Helper functions for battles

    def calculate_probability(E1, E2): # Math seems correct
        if E1 == E2:
            return 0.5
        elif E1 < E2:
            return E1 / (2 * E2)
            # return 1 to debug
        else:
            return (E1/E2) - 0.5
    
    def battle_outcome(E1, E2): # Math seems correct
        probability = GameNode.calculate_probability(E1, E2)
        outcome = random.random()

        if outcome <= probability:
            return "Attackers Win", probability
        else:
            return "Attackers Lose", probability
    
    def simulate_battle(self, E1, E2, target_is_human):

        # Get battle winner
        outcome, proba = GameNode.battle_outcome(E1, E2)
        print("Battle outcome: " + outcome)
        # Setup
        winner = []
        final_num = 0

        # Check survival rate based on different battle types
        if outcome == "Attackers Win":
            # Survivability of each attacking monster
            for i in range(E1): 
                if not random.random() <= proba:
                    # Monster only survives if it passes proba, if not -> dies
                    E1 -= 1
            print('Number of attackers who survived: ' + str(E1))
            
            # Survivability of each human, then convert humans
            if target_is_human:
                print("Checking human survival rate")
                # Survivability of each attacked human
                for i in range(E2): 
                    if not random.random() <= proba:
                        # Human only survives if it passes proba, if not -> dies
                        E2 -= 1
                # Convert humans
                print('Number of humans who survived: ' + str(E2))
                E1 += E2
                E2 = 0
                print('Converting humans to attacker: ' + str(E1))

            else:
                # All enemies die
                E2 = 0
            
            # Set the winner as current player
            winner = self.player_turn
            # Return the amount of units in the attacking team
            final_num = E1

        # If attackers lose
        else:
            # All attackers die
            E1 = 0
            # Survivability of each enemy
            for i in range(E2):
                if not random.random() <= 1-proba:
                    # Enemy only survives if it passes 1-proba, if not -> dies
                    E2 -= 1
            
            # Set the winner as enemy or human
            if target_is_human:
                winner = 'human'
            else:
                winner = self.enemy
            # Return the amount of units in the defending team
            final_num = E2
            print('Amount of surivors in defending team: ' + str(E2))

        # Return the output entity of format ('vampire', 3)
        return (winner, final_num)
        
    # Other helper functions
    def check_monsters_presence(matrix):
        vampire_found = False
        werewolf_found = False

        for row in matrix:
            for item in row:
                if item[0] == 'vampire':
                    print("found vamp")
                    vampire_found = True
                elif item[0] == 'werewolf':
                    print("found were")
                    werewolf_found = True

        return vampire_found and werewolf_found
