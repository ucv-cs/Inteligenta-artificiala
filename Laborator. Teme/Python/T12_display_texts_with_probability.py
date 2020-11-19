"""
L1-12: Afișați cu o probabilitate de 0.5 (50% șanse) textul „Inteligența Artificială”.
În celălalt caz afișați „Limbajul C”.
"""
import lib_utils as lu
import random


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#afișează textul selectat aleator
	text = ["Inteligența Artificială", "Limbajul C"]
	index = random.randrange(0, 2)
	print(text[index])
	feedback = input(
	    "Încercăm din nou? "
	    "Apasă [y] și [ENTER] pentru da, altă tastă și [ENTER] pentru nu: ")
	if feedback.lower() != "y":
		exit()


#aplicația
lu.run(__doc__, display_results)