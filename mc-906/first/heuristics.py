from models import *

import sys
sys.path.append('/Users/williamcruz/aima-python')
sys.path.append('/home/william.cruz/aima-python')

from search import *
from notebook import *

state = (10, 10)
instance = BFSRobotProblem(state)

import time
start = time.time()
solution = astar_search(instance, instance.h2)
print ('ELAPSED TIME: ', time.time() - start)

print ('A* : ', len(solution.path()))
print ('A* NODES LISTED: ', instance.listed())
print ('A* NODES EVALUATED: ', instance.evaluated())


instance.plot(solution)