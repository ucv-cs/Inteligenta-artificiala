"""
L1-17: Reprezentați tabla de mai jos. Știind că posibilitățile
de modificare ale tabelei sunt să se mute căsuța goală sus, jos,
la stânga sau la dreapta, alegeți în mod aleatoriu una din aceste
acțiuni și afișați ce mutare are loc și ce stare se obține.
	2 3 5
	4   1
	8 6 7
"""
import lib_utils as lu

#def switch(position_1, position_2):


def move(position, matrix, key):
	x_max = len(matrix[0]) - 1
	y_max = len(matrix) - 1
	if key == 'w':
		if position[1] > 0:
			position[1] -= 1
			#matrix(position[0], position[1])
	elif key == 's':
		if position[1] < y_max:
			position[1] += 1
	elif key == 'a':
		if position[0] > 0:
			position[0] -= 1
	elif key == 'd':
		if position[0] < x_max:
			position[0] += 1


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	matrix = [[2, 3, 5], [4, 0, 1], [8, 6, 7]]


#aplicația
lu.run(__doc__, display_results)