# Dominatorix
Foundation of Artificial Intelligence Project.


# AUTHORS
Félix Wirth
Romain Mondelice
Raphaël Monges
Hugo de Rohan Willner

# TODO
Split modeling
As an assignment problem - creature group vs humans ?
- At every turn, use A* to compute distance between every group of creature together and store it in a table
- Compute the different possible splits
- Check for each split what maximizes the score at depth X
- Apply this sequence of move in priority ?

# Ideas
- Computing the distance from human groups to any cell and the required number of entity to take this path successfully \
could yield robust early moves. Use in ordering the moves for alpha beta ?
- Check if the map is symmetrical (to the diagonal) for some optimizations e.g. computing distance from humans to every cell