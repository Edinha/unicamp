from models import *

import sys
# sys.path.append('/Users/williamcruz/aima-python')
sys.path.append('/home/william.cruz/aima-python')

from search import *
from notebook import *

state = (10, 10)
instance = RobotProblem(state)

# print ('A* using first heuristic: ', astar_search(instance, instance.h).path())
print ('A* using second heuristic: ', astar_search(instance, instance.h2).path())