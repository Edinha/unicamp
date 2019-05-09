from random import randint, uniform
from image import ImageWrapper, ColorPalletProblem
import time

COLOR_PALLET_SIZE = 6
POPULATION_INITIAL_SIZE = 1000

MAX_GENERATION_COUNT = 100

MUTATION_CHANCE = 0.1
REPRODUCTION_CHANCE = 0.6

class GeneticAlgorithm:
	image = None
	population = []

	def __init__(self, path):
		self.image = ImageWrapper(path)
		for i in range(0, POPULATION_INITIAL_SIZE):
			self.population.append(self.random_init())

	def random_init(self):
		# return QueenProblem([ randint(1, BOARD_SIZE) for i in range(0, BOARD_SIZE) ])

		pallet = []
		while len(pallet) < COLOR_PALLET_SIZE:
			pallet.append(self.image.random_color())
			pallet = list(set(pallet))

		return ColorPalletProblem(pallet, self.image)

	def has_reach_end(self, generation):
		# IMplement has solution
		return generation > MAX_GENERATION_COUNT

	def fitness(self, individual):
		return individual.fitness()

	def find_pair(self, individual):
		###### TODO SEE IF RANDOM WORKS OR APPLY LOGIC ######
		return self.population[randint(0, len(self.population) - 1)]

	def create_new_population(self, generation):
		new_population = []
		for individual in self.population:
			if uniform(0, 1) < REPRODUCTION_CHANCE:
				new_population.append(individual.crossover_uniform(self.find_pair(individual)))

		new_population.extend(self.population)

		## SOLUCAO PALEOTATIVA DE MUTACAO POR ENQUANTO ##
		for individual in self.population:
			if uniform(0, 1) < MUTATION_CHANCE * (1 - generation/MAX_GENERATION_COUNT):
				individual.mutate2()

		## Implement rules of reproduction
		new_population.sort(key=self.fitness, reverse=True)
		return new_population[:POPULATION_INITIAL_SIZE]

	def run(self):
		generation = 1
		while not self.has_reach_end(generation):
			generation += 1
			self.population = self.create_new_population(generation)

		## TODO EXTRACT SOME DATA HERE ##
		# self.population.sort(key=self.fitness, reverse=True)
		best_individual = self.population[0]
		print("best", self.fitness(best_individual))
		print ('BEST INDIVIDUAL: ', best_individual)
		print("generation = ", generation)
		sum = 0
		for individual in self.population:
			sum = sum + self.fitness(individual)
		print("fitness media = ", sum / len(self.population))
		for i in range(0, COLOR_PALLET_SIZE):
			print ('COLOR %s %d COUNT: %d' % (best_individual.pallet[i], i, self.image.count.get(best_individual.pallet[i])))


####### RUN METHODS ######

start_time = time.time()
GeneticAlgorithm('pq-chico-mendes-osasco.jpg').run()
print(time.time() - start_time)