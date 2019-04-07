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
solution = depth_first_tree_search(instance)
print ('ELAPSED TIME: ', time.time() - start)

print ('DFS: ', len(solution.path()))
print ('DFS NODES LISTED: ', instance.listed())
print ('DFS NODES EVALUATED: ', instance.evaluated())