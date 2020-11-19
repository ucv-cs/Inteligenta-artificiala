"""
L1-8: Avem trei vectori cu aceeași lungime a, b și c.
Scrieți un program care să verifice dacă pentru fiecare poziție i,
avem a[i] < b[i] < c[i]. Dacă inegalitatea se verifică pentru toate
elementele, întoarceți adevărat, altfel fals.
"""
import lib_utils as lu


def match_vector_lenghts(vector_name, required_length):
	"""
	Obține elementele unui vector, care trebuie să aibă o lungime dată.
	 param vector_name: string reprezentând numele vectorului
	 param required_length: lungimea vectorului
	 return: vectorul
	 rtype: list
	"""
	vector_length = 0
	while vector_length != required_length:
		vector = lu.validate_input(
		    input(
		        f"Scrie {required_length} elemente pentru vectorul {vector_name}, "
		        "separate prin virgulă sau spațiu: "), lu.list_matcher)
		vector_length = len(vector)
		if vector_length != required_length:
			print(f"Vectorul trebuie să aibă {required_length} elemente.")
		else:
			return eval(f"{vector}")


def check_inequality(a, b, c):
	"""
	Verifică inegalitatea din enunț pentru trei vectori egali.
	 param a, b, c: vectorii (tip: list)
	 return: rezultatul verificării
	 rtype: bool
	"""
	for i in range(len(a)):
		if not ((a[i] < b[i]) and (b[i] < c[i])):
			print(
			    f"Pentru indexul {i} avem: {a[i]:n} < {b[i]:n} < {c[i]:n}, deci nu se verifică inegalitatea."
			)
			return False
	print("Inegalitatea se verifică pentru toate elementele vectorilor dați.")
	return True


def display_results():
	"""
	Afișează inputul și rezultatul
	"""
	#obține cei trei vectori de la utilizator
	a = lu.validate_input(
	    input(
	        "Scrie elementele vectorului a, separate prin virgulă sau spațiu: "),
	    lu.list_matcher)
	a_length = len(a)
	b = match_vector_lenghts("b", a_length)
	c = match_vector_lenghts("c", a_length)
	#afișează vectorii
	print("Vectorii introduși sunt:")
	print(f"\ta = {lu.list_as_string(a)}")
	print(f"\tb = {lu.list_as_string(b)}")
	print(f"\tc = {lu.list_as_string(c)}")
	#verifică inegalitatea din enunț și afișează rezultatul
	check_inequality(a, b, c)
	#adaugă delimitare în afișaj
	print(f"{lu.dashes}")


#aplicația
lu.run(__doc__, display_results)