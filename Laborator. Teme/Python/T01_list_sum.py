"""
L1-1: Se dă o listă de numere. Să se calculeze suma acestora.
"""
import lib_utils as lu


def list_sum(number_list):
	"""
	Calculează suma numerelor dintr-o listă.
	 param number_list: lista de numere
	 return: suma
	 rtype: [numeric]
	"""
	result = 0
	for element in number_list:
		result += element
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
	print(f"\nLista de numere este: {lu.list_as_string(number_list)}")
	print(f"Suma numerelor din listă este: {list_sum(number_list):n}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)