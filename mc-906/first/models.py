import sys
# sys.path.append('/Users/williamcruz/aima-python')
sys.path.append('/home/william.cruz/aima-python')

from search import *
from notebook import *

def go_up(state):
    pass

def go_down(state):
    pass

def go_left(state):
    pass

def go_right(state):
    pass

class RobotProblem(Problem):
    def actions(self, state):
        return [go_up, go_right, go_down, go_left]

    def result(self, state, action):
        return action(state)

    def goal_test(self, state):
        return super.goal_test(state)

    def path_cost(self, c, state1, action, state2):
        return super.path_cost(c, state1, action, state2)

    def value(self, state):
        return 0