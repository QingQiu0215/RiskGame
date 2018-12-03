# RiskGame
Risk Game
- A Random Computer Player Strategy that reinforces random a random country, attacks a random number
of times a random country, and fortifies a random country, all following the standard rules for each phase,
- A Cheater Computer Player Strategy whose reinforce() method doubles the number of armies on all
its countries, whose attack() method automatically conquers all the neighbors of all its countries, and
whose fortify() method doubles the number of armies on its countries that have neighbors that belong
to other players.
- an aggressive computer player that focuses on attack (reinforces its strongest
country, then always attack with it until it cannot attack anymore, then fortifies in order to maximize aggregation of
forces in one country)
- a benevolent computer player that focuses on protecting its weak countries (reinforces
its weakest countries, never attacks, then fortifies in order to move armies to weaker countries)

DESIGN PATTERNS:

1. Using the Strategy design pattern, implement different kinds of players that make different decisions during the
reinforcement, attack, and fortification phases. 

2. Using the Observer design pattern, implement a view that displays information happening in the current phase. It
should first display a header showing what player and what phase is currently being played

3. Using the Observer design pattern, implement a view that displays some useful statistics about the game, the
minimum being a “players world domination view” that shows using some kind of graph or table depicting what
percentage of the world is currently being controlled by each player. 

