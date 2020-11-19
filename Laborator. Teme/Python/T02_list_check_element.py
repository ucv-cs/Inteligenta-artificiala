"""
L1-2: Se dă o listă de numere. Să se verifice dacă un anumit număr există sau nu în această listă.
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
	#obține numărul de verificat de la utilizator
	number = lu.validate_input(input("Scrie un număr: "), lu.number_matcher)
	#afișează lista și rezultatul verificării dacă numărul dat este în listă
	string_in_list = "este" if number in number_list else "nu este"
	print(f"\nLista de numere este: {lu.list_as_string(number_list)}")
	print(f"Numărul {number:n} {string_in_list} în lista dată.{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)