"""
L1-5: Să se elimine un număr aflat pe o anumită poziție într-o listă.
"""
import lib_utils as lu


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține numerele din listă de la utilizator
	number_list = lu.validate_input(
	    input("Scrie o listă de numere separate prin virgulă sau spațiu: "),
	    lu.list_matcher)
	#obține poziția elementului de la utilizator
	index = lu.validate_input(
	    input(
	        f"Scrie indexul elementului care trebuie eliminat (< {len(number_list)}!): "
	    ), lu.list_index_matcher, number_list)
	#afișează lista inițială
	print(f"\nLista inițială este:\n\t{lu.list_as_string(number_list)}")
	#lista inițială este modificată prin eliminarea elementului și afișată din nou
	number_list.pop(index)
	print(f"Noua listă este:\n\t{lu.list_as_string(number_list)}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)