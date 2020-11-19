"""
L1-9: Ordonarea elementelor dintr-o listă.
"""
import lib_utils as lu


def sort_list(number_list):
	"""
	Sortează o listă de numere.
	 param number_list: lista de numere
	 return: lista sortată
	 rtype: list
	"""
	#truc pythonic :)
	#return sorted(number_list)
	lu.quicksort(number_list)
	return number_list


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține numerele din listă de la utilizator
	number_list = lu.validate_input(
	    input("Scrie o listă de numere separate prin virgulă sau spațiu: "),
	    lu.list_matcher)
	#afișează lista în forma inițială și în cea sorată
	print(f"\nLista introdusă este:\n\t{lu.list_as_string(number_list)}")
	print(
	    f"Lista sortată este:\n\t{lu.list_as_string(sort_list(number_list))}{lu.dashes}"
	)


#aplicația
lu.run(__doc__, display_results)