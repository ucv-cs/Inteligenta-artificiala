"""
L1-7: Să se adauge un numar dat pe o poziție dată într-o listă.
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
	#obține valoarea și indexul elementului de la utilizator
	value = lu.validate_input(
	    input(f"Scrie numărul de adăugat: "), lu.number_matcher)
	#list.insert(pos, elem) permite orice int pentru pos, deci nu este necesară
	# validarea suplimentară a indexului, raportată la lungimea listei date;
	# totuși, inputul acceptabil aici trebuie să fie natural
	index = lu.validate_input(
	    input(f"Scrie indexul la care trebuie adăugat: "), lu.number_matcher,
	    "natural")
	#afișează lista inițială
	print(f"\nLista inițială este:\n\t{lu.list_as_string(number_list)}")
	#lista inițială este modificată prin adăugarea elementului și afișată din nou
	number_list.insert(index, value)
	print(f"Noua listă este:\n\t{lu.list_as_string(number_list)}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)