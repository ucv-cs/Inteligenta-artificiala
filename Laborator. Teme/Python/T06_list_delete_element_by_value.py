"""
L1-6: Să se elimine un numar dat dintr-o listă dată.
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
	#obține valoarea elementului de la utilizator
	#verifică dacă numărul este în listă
	while True:
		element = lu.validate_input(
		    input(f"Scrie elementul care trebuie eliminat: "), lu.number_matcher)
		#ieși din loop numai dacă elementul este în listă
		if element in number_list:
			break
		else:
			print(f"ELementul {element:n} nu există în lista dată.")
	#afișează lista inițială
	print(f"\nLista inițială este:\n\t{lu.list_as_string(number_list)}")
	#lista inițială este modificată prin eliminarea elementului și afișată din nou
	#este eliminat doar primul element găsit (pentru duplicatele lui în listă,
	# trebuie folosit un loop...)
	number_list.remove(element)
	print(f"Noua listă este:\n\t{lu.list_as_string(number_list)}{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)