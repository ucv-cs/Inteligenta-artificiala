"""
L1-3: Se dă o listă de numere. Să se schimbe valorile dintre două poziții date din această listă.
"""
import lib_utils as lu


def switch_elements(pair, list):
	"""
	Schimbă între ele două elemente dintr-o listă și returnează noua listă.
	 param pair: tuple cu indecșii elemntelor de schimbat între ele
	 param list: lista dată
	 return: lista rezultată
	 rtype: list
	"""
	(list[pair[0]], list[pair[1]]) = (list[pair[1]], list[pair[0]])
	#sau, mai puțin pythonic
	#temp = list[pair[0]]
	#list[pair[0]] = list[pair[1]]
	#list[pair[1]] = temp
	return list


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține numerele din listă de la utilizator
	number_list = lu.validate_input(
	    input("Scrie o listă de numere separate prin virgulă sau spațiu: "),
	    lu.list_matcher)
	#obține pozițiile elementelor de la utilizator
	pair = lu.validate_input(
	    input("Scrie cei doi indecși ai "
	          "elementelor din listă, care trebuie schimbate între ele: "),
	    lu.list_indices_matcher, number_list)
	#afișează lista și rezultatul verificării dacă numărul dat este în listă
	print(f"\nLista inițială este:\n\t{lu.list_as_string(number_list)}")
	#lista inițială este modificată prin switch_elements()!
	print(
	    f"Noua listă este:\n\t{lu.list_as_string(switch_elements(pair, number_list))}{lu.dashes}"
	)


#aplicația
lu.run(__doc__, display_results)