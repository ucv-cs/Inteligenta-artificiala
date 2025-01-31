"""
L1-16: Având două liste de numere ca mai jos, se alege un punct de tăietură și
construiți două liste noi astfel:
	a. se copiază primele două părți din listele inițiale;
	b. a doua parte se completează prin inserarea de elemente de la cealaltă listă
în ordinea în care apar, începând cu punctul de după tăietură, sărind valorile
care apar deja în listă.
"""
import lib_utils as lu
import random


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține numerele din listă de la utilizator
	number_list = lu.validate_input(
	    input(
	        "Scrie o listă de numere separate prin virgulă sau spațiu (cel puțin 2):\n\t"
	    ), lu.list_matcher, {"min_length": 2})
	#realizează extragerile aleatorii și adaugă rezultatele într-o listă
	list_length = len(number_list)
	result = []
	m = 1 if list_length == 2 else random.randrange(1, list_length) # m < n
	uniques = len(set(number_list))
	print(f"    m = {m}")
	print(f"unice = {uniques} din {list_length}")
	counts = 1
	while counts <= min(m, uniques):
		index = random.randrange(0, list_length)
		value = number_list[index]
		#adaugă valoarea extrasă aleatoriu numai dacă nu există deja în lista finală
		if value not in result:
			result.append(value)
			counts += 1
	#afișează cele două liste
	print(f"Lista inițială este:\n\t{lu.list_as_string(number_list)}")
	print(f"Lista cu numerele unice extrase este:\n\t{lu.list_as_string(result)}")
	print(f"{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)