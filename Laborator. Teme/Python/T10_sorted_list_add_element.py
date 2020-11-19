"""
L1-10: Dându-se o listă de numere ordonate crescător, inserați un număr
 dat în această listă astfel încât ea să rămână ordonată.
"""
import lib_utils as lu


def insert_element(element, number_list):
	"""
	Inserează un număr într-o listă sortată, astfel încât să i se păstreze
	sortarea.
	 param element: numărul de inserat în listă
	 param number_list: lista de numere
	"""
	i = len(number_list) - 1
	while (i >= 0):
		if number_list[i] <= element:
			number_list.insert(i + 1, element)
			break
		i -= 1


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține numerele din listă de la utilizator
	number_list = lu.validate_input(
	    input("Scrie o listă de numere separate prin virgulă sau spațiu: "),
	    lu.list_matcher)
	#sortează lista, pentru siguranță
	number_list = sorted(number_list)
	#obține valoarea elementului de la utilizator
	element = lu.validate_input(
	    input(f"Scrie numărul de adăugat: "), lu.number_matcher)
	#afișează lista în forma inițială și în cea sortată
	print(f"\nLista inițială este:\n\t{lu.list_as_string(number_list)}")
	insert_element(element, number_list)
	print(
	    f"Lista modificată este:\n\t{lu.list_as_string(number_list)}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)