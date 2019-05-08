from random import randint, uniform
from image import ImageWrapper, ColorPalletProblem

BOARD_SIZE = 8
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
				new_population.append(individual.crossover_single(self.find_pair(individual)))

		new_population.extend(self.population)

		## SOLUCAO PALEOTATIVA DE MUTACAO POR ENQUANTO ##
		for individual in self.population:
			if uniform(0, 1) < MUTATION_CHANCE * (1 - generation/MAX_GENERATION_COUNT):
				individual.mutate()

		## Selection by elitism
		##new_population.sort(key=self.fitness, reverse=True)
		##return new_population[:POPULATION_INITIAL_SIZE]

		## Selection by tournament
		index_list = [] ## lista com os indices que ja foram escolhidos
		j = len(new_population) - 1 ## j eh o numero de individuos na nova populacao
		print(j)
		index1 = 1
		index2 = 1
		for i in range(0, int(j*0.6)):
			while index1 == index2 or index1 in index_list or index2 in index_list:	## enquanto nao forem dois individuos diferentes e que sao repetidos roda esse loop
				index1 = randint(0, j)
				index2 = randint(0, j)
			person1 = new_population[index1]
			person2 = new_population[index2]
			if self.fitness(person1) < self.fitness(person2): ## escolhe o individuo com a melhor fitness
				new_population.append(person2)
				index_list.append(index2) ## adiciona o indice desse individuo na lista
			else:
				new_population.append(person1)
				index_list.append(index1)

		return new_population[j:]

	def run(self):
		generation = 1
		while not self.has_reach_end(generation):
			generation += 1
			self.population = self.create_new_population(generation)

		## TODO EXTRACT SOME DATA HERE ##
		##self.population.sort(key=self.fitness, reverse=True)
		best_individual = self.population[0]
		print(self.fitness(best_individual))
		print('BEST INDIVIDUAL: ', best_individual)

		for i in range(0, COLOR_PALLET_SIZE):
			print ('COLOR %s %d COUNT: %d' % (best_individual.pallet[i], i, self.image.count.get(best_individual.pallet[i])))


####### RUN METHODS ######

GeneticAlgorithm('equal.jpg').run()