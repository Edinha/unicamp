
class QueenProblem:
	positions = []

	def __init__(self, positions):
		self.positions = positions

	def fitness(self):
		# Inverse of atacking queens
		return 0

	def crossover(self, other):
		# Implement right crossover
		return QueenProblem(self.positions)

	def is_solution(self):
		# Returns if problem is solution to queen problem
		return False