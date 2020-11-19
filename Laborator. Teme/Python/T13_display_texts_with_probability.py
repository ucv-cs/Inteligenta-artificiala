"""
L1-13: Oferiți șanse egale afișării unuia din cele trei texte în C:
a. Inteligența Artificială
b. Limbajul C
c. Programare Web
"""
import lib_utils as lu
import random


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#afișează textul selectat aleator
	text = ["Inteligența Artificială", "Limbajul C", "Programare Web"]
	index = random.randrange(0, 3)
	print(text[index])
	feedback = input(
	    "Încercăm din nou? "
	    "Apasă [y] și [ENTER] pentru da, altă tastă și [ENTER] pentru nu: ")
	if feedback.lower() != "y":
		exit()


#aplicația
lu.run(__doc__, display_results)