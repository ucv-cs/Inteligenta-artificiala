"""
Modul cu diverse funcții utilitare (validarea inputului, afișare).

Notă: pentru a preveni crearea de foldere __pycache__ trebuie adăugată
variabila de sistem (environment variable): PYTHONDONTWRITEBYTECODE=1
"""
import re

#separator utilizat la afișare
dashes = f"\n{'-'*70}\n"


def validate_input(string, matcher_callback, data=None):
	"""
	Verifică dacă inputul corespunde formatului acceptat conform funcției
	matcher_callback
	 param string: text primit din input
	 param matcher_callback: nume de funcție folosită la validare
	 param data: date suplimentare necesare validatorilor cu mai mulți parametri
	 return: obiectul rezultat din matcher_callback
	"""
	NumberTypes = (int, float)
	while True:
		output = matcher_callback(string, data)
		if output or isinstance(output, NumberTypes):
			return output
		else:
			string = input("Mai încearcă: ")


def list_matcher(string, options=None):
	"""
	Verifică dacă stringul introdus reprezintă o listă de numere separate
	prin virgulă sau spațiu.
	 param string: stringul care trebuie verificat
	 param options: dicționar cu opțiuni ex. {"min_length": 2, "max_length": 4}
	 	notă: doar "min_length" este implementată
	 return: lista sau None
	 rtype: list, None
	"""
	if options == None:
		options = {"min_length": 1, "max_length": 100}
	result = []
	string_list = re.split(r"[ ,\t]", string)
	try:
		for element in string_list:
			if element != '' and isinstance(float(element), float):
				result.append(float(element))
	except:
		print("Trebuie să scrii o listă de numere separate "
		      "prin virgulă sau spațiu!")
		return None
	if len(result) < options["min_length"]:
		print(
		    f"Lista trebuie să aibă cel puțin {options['min_length']} elemente, cea introdusă are doar {len(result)}."
		)
		return None
	return result


def list_index_matcher(string, number_list):
	"""
	Verifică dacă stringul introdus reprezintă un index în listă (i.e.
	număr natural mai mic decât lungimea listei).
	 param string: stringul care trebuie verificat
	 param number_list: lista de verificat
	 return: index sau None
	 rtype: int, None
	"""
	string = string.strip()
	list_length = len(number_list)
	try:
		index = int(string)
		if index in range(0, list_length):
			return index
		else:
			print(
			    f"Indexul trebuie să fie un număr natural mai mic decât {list_length}."
			)
			return None
	except:
		print(
		    f"Trebuie să scrii un număr natural mai mic decât {list_length}, nu alte caractere."
		)
		return None


def list_indices_matcher(string, number_list):
	"""
	Verifică dacă stringul introdus reprezintă două numere naturale separate
	prin virgulă sau spațiu, apoi dacă acestea pot fi indecși în listă (i.e.
	sunt mai mici decât lungimea listei).
	 param string: stringul care trebuie verificat
	 param number_list: lista de verificat
	 return: tuple sau None
	 rtype: tuple, None
	"""
	list_length = len(number_list)
	string = string.strip()
	pattern = r"(\d*)[ ,\t]+(\d*)"
	test = re.match(pattern, string)
	if not test:
		print("Trebuie să scrii două numere naturale diferite, separate "
		      "prin virgulă sau spațiu.")
		return None
	first_number = int(test.group(1))
	second_number = int(test.group(2))
	if (first_number >= list_length) or (second_number >= list_length):
		print(f"Ambele numere trebuie să fie mai mici decât {list_length}.")
		return None
	if (first_number == second_number):
		print(f"Numerele introduse nu trebuie să fie egale.")
		return None
	return (first_number, second_number)


def number_matcher(string, number_type=None):
	"""
	Verifică dacă stringul introdus reprezintă un număr.
	 param string: stringul care trebuie verificat
	 param number_type: string ce indică tipul numărului
	 return: număr sau None
	 rtype: float, None
	"""
	try:
		#cazul implicit: număr real (float)
		if number_type == None or number_type == "float":
			return float(string)
		#număr natural
		elif number_type == "natural":
			number = int(string)
			if number >= 0:
				return number
			else:
				print("Numărul trebuie să fie natural.")
				return None
		#număr întreg
		elif number_type == "integer":
			return int(string)
		#altceva...
		else:
			return None
	except:
		print("Trebuie introdus un singur număr, potrivit cerinței.")
		return None


def list_as_string(floats_list):
	"""
	Returnează un string cu numerele dintr-o listă de floaturi într-o formă mai simplă.
	(Notă: funcționează corect doar până la 5 zecimale)
	 param floats_list: lista cu elemente de tip float
	 return: lista ca string formatat
	 rtype: string
	"""
	result = []
	for number in floats_list:
		result.append(f"{number:n}")
	return str(result).replace("'", "")


def quicksort(list, low_boundary=None, high_boundary=None):
	"""
	Implementare pentru quicksort;
	v. https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
	 param list: lista de sortat
	 param low_boundary: indexul minim de la care se sortează
	 param high_boundary: indexul maxim până la care se sortează
	"""
	#dacă nu se specifică limitele sortării, limitele implicite
	# cuprind întreaga listă
	if low_boundary == None and high_boundary == None:
		low_boundary = 0
		high_boundary = len(list) - 1
	if low_boundary < high_boundary:
		partition = _partition(list, low_boundary, high_boundary)
		quicksort(list, low_boundary, partition - 1)
		quicksort(list, partition + 1, high_boundary)


def _partition(list, low_boundary, high_boundary):
	"""
	Funcție utilitară de partiționare în cadrul algoritmului quicksort.
	 param list: lista de partiționat
	 param low_boundary: indexul minim de la care se partiționează
	 param high_boundary: indexul maxim până la care se partiționează
	 return: noul index minim al partiției
	 rtype: int
	"""
	pivot = list[high_boundary]
	i = low_boundary
	for j in range(low_boundary, high_boundary + 1):
		if list[j] < pivot:
			(list[i], list[j]) = (list[j], list[i])
			i += 1
	(list[i], list[high_boundary]) = (list[high_boundary], list[i])
	return i


def run(message=None, function=None):
	"""
	Afișează un mesaj și apoi execută într-un loop infinit o funcție.
	Utilizată pentru executarea codului din exerciții.
	 param message: mesajul afișat (de regulă, enunțul unei probleme)
	 param function: funcția care trebuie executată în loop infinit
	"""
	print(message) #afișează enunțul temei
	while True:
		function()