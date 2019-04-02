import sys
import math
# sys.path.append('/Users/williamcruz/aima-python')
sys.path.append('/home/william.cruz/aima-python')

from search import *
from notebook import *

goal = (50, 50)
board = [[0 for col in range(60)] for row in range (60)]

# Limites laterais
for i in range(60):
    board[i][0] = 2
    board[0][i] = 2
    board[i][len(board) - 1] = 2
    board[len(board) - 1][i] = 2

# Parades no meio
for i in range(40):
    board[20][i] = 2
    board[40][20 + i] = 2

def go_up(state):
    (x, y) = state
    return (x, y + 1)

def go_down(state):
    (x, y) = state
    return (x, y - 1)

def go_left(state):
    (x, y) = state
    return (x - 1, y)

def go_right(state):
    (x, y) = state
    return (x + 1, y)

class RobotProblem(Problem):
    def actions(self, state):
        possible = []
        (x, y) = state

        if x + 1 < len(board) and board[x + 1][y] < 1:
            board[x + 1][y] = 1
            possible.append(go_right)

        if x - 1 > 0 and board[x - 1][y] < 1:
            board[x - 1][y] = 1
            possible.append(go_left)

        if y + 1 < len(board) and board[x][y + 1] < 1:
            board[x][y + 1] = 1
            possible.append(go_up)

        if y - 1 > 0 and board[x][y - 1] < 1:
            board[x][y - 1] = 1
            possible.append(go_down)

        return possible

    def result(self, state, action):
        (x, y) = state
        return action(state)

    def goal_test(self, state):
        (x, y) = state
        (goal_x, goal_y) = goal
        return x == goal_x and y == goal_y

    def path_cost(self, c, state1, action, state2):
        return c + 1

    def h(self, node):
        """ Manhattan distance """
        (x, y) = node.state
        (goal_x, goal_y) = goal
        return abs(x - goal_x) + abs(y - goal_y)

    def h2(self, node):
        """ Euclidian distance """
        (x, y) = node.state
        (goal_x, goal_y) = goal
        return int(math.sqrt((x - goal_x)**2 + (y - goal_y)**2))