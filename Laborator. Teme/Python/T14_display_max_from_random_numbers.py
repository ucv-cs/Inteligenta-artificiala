"""
L1-14: Dintr-o listă de n numere alegeți în mod aleatoriu m (m < n) numere nu neapărat unice (adică
pot fi numere din lista inițială ce pot apărea de mai multe ori), le afișați, apoi găsiți maximul
dintre aceste n numere.
"""
import lib_utils as lu
import random


def list_max(number_list):
	"""
	Calculează valoarea maximă a numerelor dintr-o listă.
	 param number_list: lista de numere
	 return: maxim
	 rtype: [numeric]
	"""
	result = number_list[0]
	list_length = len(number_list)
	for index in range(1, list_length):
		if number_list[index] > result:
			result = number_list[index]
	return result


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
	counter = 1 if list_length == 2 else random.randrange(1, list_length) # m < n
	print(f"Acum vom face {counter} extrageri aleatorii din listă:")
	for i in range(0, counter):
		index = random.randrange(0, list_length)
		value = number_list[index]
		print(f"\t{i+1}: {value:n}")
		result.append(value)
	#afișează cele două liste
	print(f"Lista inițială este: {lu.list_as_string(number_list)}")
	print(f"Lista cu numerele extrase este: {lu.list_as_string(result)}")
	print(
	    f"Maximul listei cu numere extrase este: {list_max(result):n}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)