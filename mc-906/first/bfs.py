from models import *

import sys
sys.path.append('/Users/williamcruz/aima-python')
sys.path.append('/home/william.cruz/aima-python')

from search import *
from notebook import *

state = (10, 10)
instance = RobotProblem(state)

import time
start = time.time()
solution = breadth_first_tree_search(instance)
print ('ELAPSED TIME: ', time.time() - start)

print ('BFS PATH SIZE: ', len(solution.path()))
print ('BFS NODES LISTED: ', instance.listed())
print ('BFS NODES EVALUATED: ', instance.evaluated())