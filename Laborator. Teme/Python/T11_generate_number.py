"""
L1-11: Să se genereze un număr între 0 și 100 în C.

Notă: deocamdată, rezolvăm în Python :)
"""
import lib_utils as lu
import random


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#afișează numărul generat aleator
	print(
	    f"\nNumăr întreg generat aleatoriu între 0 și 100: {random.randrange(0, 101)}"
	)
	feedback = input(
	    "Încercăm din nou? "
	    "Apasă [y] și [ENTER] pentru da, altă tastă și [ENTER] pentru nu: ")
	if feedback.lower() != "y":
		exit()


#aplicația
lu.run(__doc__, display_results)