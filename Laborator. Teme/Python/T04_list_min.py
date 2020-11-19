"""
L1-4: Găsiți valoarea minimă dintr-o listă de numere.
"""
import lib_utils as lu


def list_min(number_list):
	"""
	Calculează valoarea minimă a numerelor dintr-o listă.
	 param number_list: lista de numere
	 return: minim
	 rtype: [numeric]
	"""
	result = number_list[0]
	list_length = len(number_list)
	for index in range(1, list_length):
		if number_list[index] < result:
			result = number_list[index]
	return result


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține numerele din listă de la utilizator
	number_list = lu.validate_input(
	    input("Scrie o listă de numere separate prin virgulă sau spațiu: "),
	    lu.list_matcher)
	#afișează lista și suma numerelor din listă
	print(f"\nLista introdusă este: {lu.list_as_string(number_list)}")
	print(f"Minimul listei este: {list_min(number_list):n}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)