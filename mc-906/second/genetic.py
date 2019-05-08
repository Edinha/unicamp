from random import randint, uniform
from image import ImageWrapper, ColorPalletProblem

COLOR_PALLET_SIZE = 6
POPULATION_INITIAL_SIZE = 1000

MUTATION_CHANCE = 0.9
REPRODUCTION_CHANCE = 0.8

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

	def fitness(self, individual):
		return individual.fitness()

	def find_pair(self, individual):
		###### TODO SEE IF RANDOM WORKS OR APPLY LOGIC ######
		return self.population[randint(0, len(self.population) - 1)]

	def create_new_population(self):
		new_population = []
		for individual in self.population:
			if uniform(0, 1) < REPRODUCTION_CHANCE:
				new_population.append(individual.crossover_single(self.find_pair(individual)))

		new_population.extend(self.population)

		## SOLUCAO PALEOTATIVA DE MUTACAO POR ENQUANTO ##
		for individual in self.population:
			if uniform(0, 1) < MUTATION_CHANCE:
				individual.mutate()

		## Selection by elitism
		##new_population.sort(key=self.fitness, reverse=True)
		##return new_population[:POPULATION_INITIAL_SIZE]

		## Selection by tournament
		index_list = [] ## lista com os indices que ja foram escolhidos
		j = len(new_population) - 1 ## j eh o numero de individuos na nova populacao
		index1 = 1
		index2 = 1
		for i in range(0, POPULATION_INITIAL_SIZE):
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
		## criterio de parada
		cnt = -1
		gen_cnt = 10
		generation = 1
		new_value = 2
		while cnt != int(0.1*gen_cnt):
			generation += 1
			old_value = new_value
			self.population = self.create_new_population()
			self.population.sort(key=self.fitness, reverse=True)
			new_value = self.fitness(self.population[0])
			print("generation ", generation)
			print("new value = ", new_value)
			if generation >= 20:
				if old_value != new_value:
					cnt = 1
					gen_cnt = generation
				else:
					cnt = cnt + 1

		## TODO EXTRACT SOME DATA HERE ##
		##self.population.sort(key=self.fitness, reverse=True)
		best_individual = self.population[0]
		print(self.fitness(best_individual))
		print('BEST INDIVIDUAL: ', best_individual)

		for i in range(0, COLOR_PALLET_SIZE):
			print ('COLOR %s %d COUNT: %d' % (best_individual.pallet[i], i, self.image.count.get(best_individual.pallet[i])))

####### RUN METHODS ######

GeneticAlgorithm('equal.jpg').run()