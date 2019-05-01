from random import randint
from queens import QueenProblem

BOARD_SIZE = 8
POPULATION_INITIAL_SIZE = 1000

class GeneticAlgorithm:
	population = []

	def __init__(self):
		for i in range(0, POPULATION_INITIAL_SIZE):
			positions = self.random_init()
			self.population.append(QueenProblem(positions))

	def random_init(self):
		return [ randint(1, BOARD_SIZE) for i in range(0, BOARD_SIZE) ]

	def has_solution(self):
		# IMplement has solution
		return True

	def generate_new_population(self):
		## Implement rules of reproduction
		return self.population

	def run(self):
		while not self.has_solution():
			self.population = self.generate_new_population()


####### RUN METHODS ######

g = GeneticAlgorithm()
g.run()