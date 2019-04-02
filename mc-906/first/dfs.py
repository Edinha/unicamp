from models import *

import sys
# sys.path.append('/Users/williamcruz/aima-python')
sys.path.append('/home/william.cruz/aima-python')

from search import *
from notebook import *

state = (10, 10)
instance = RobotProblem(state)

print ('DFS: ', depth_first_tree_search(instance).path())