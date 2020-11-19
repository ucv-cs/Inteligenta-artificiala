/**
 * L11.
 * 1. Pornind de la tabloul generat la tema L010 (a carei solutie o gasiti in
 * LS010), adaugati o functie de evaluare pentru reprezentarea din tabloul
 * generat.
 * Pentru a face acest lucru, urmati modelul de la cursul "Caracteristici si
 * constrangeri" (http://inf.ucv.ro/documents/cstoean/c5IA.pdf), slide-ul 53. Va
 * rog sa faceti implementarea pentru un cadru general, pentru N, nu doar pentru
 * valoarea 8.
 * Functia trebuie sa primeasca tabloul de evaluat ca parametru si sa intoarca
 * numarul de atacuri dintre dame (un intreg pozitiv). Afisati in functia main()
 * evaluarea pentru tabloul generat initial.
 *
 * 2. Al doilea punct al problemei se refera la producerea unui nou tablou
 * pornind de la primul (cel existent, generat anterior precum in LS010). Faceti
 * o copie a tabloului, fiindca avem nevoie si de cel anterior. Gasiti detalii
 * despre modul de modificare a solutiei in slide-ul 55 de la acelasi link-ul.
 * Dupa obtinerea noii solutii potentiale, o evaluati si pe aceasta si ii
 * afisati evaluarea apeland metoda de la punctul 1 de mai sus.
 * Observatie: programul trebuie sa ramana functional si daca modificam valoarea
 * constantei N (numarul de dame).
 */
#include <cstdlib>	 //! srand(), rand()
#include <ctime>	 //! time()
#include <iomanip>	 // setw()
#include <iostream>	 // cout, cin
using namespace std;

#pragma region Setup
// prototipuri de functii
void get_integer(int*);
void print_problem();
void print_result(int*, int);
int* copy_list(int*, int);
void generate_configuration(int*, int);
int evaluate_configuration(int*, int);
void perturb_configuration(int*, int);

// variabile globale
string separator =
	"\n"
	"**********************************************************************\n";
#pragma endregion Setup

/**
 * @brief Inceputul executiei
 */
int main() {
	// "seed" functia rand() cu timpul curent
	// N.B. srand() trebuie apelata o singura data in aplicatie!
	srand(time(0));

	int configuration_length;

	while (true) {
		print_problem();
		get_integer(&configuration_length);

		// aloca dinamic lista
		int* configuration = new int[configuration_length];
		if (configuration == NULL) {
			cout << "\nEroare: Memoria nu a fost alocata.\n";
			delete[] configuration;
			continue;
		}

		generate_configuration(configuration, configuration_length);
		cout << "\nConfiguratia initiala:\n";
		print_result(configuration, configuration_length);
		cout << "\nNumarul de atacuri in aceasta configuratie: "
			 << evaluate_configuration(configuration, configuration_length);

		int* new_configuration = copy_list(configuration, configuration_length);
		perturb_configuration(new_configuration, configuration_length);
		cout << "\n\nNoua configuratie:\n";
		print_result(new_configuration, configuration_length);
		cout << "\nNumarul de atacuri in aceasta configuratie: "
			 << evaluate_configuration(new_configuration, configuration_length);

		cout << separator;

		delete[] configuration;
		delete[] new_configuration;
	}

	return 0;
}

#pragma region Algorithms
/**
 * @brief Calculeaza numarul de atacuri posibile intr-o configuratie de dame si
 * il returneaza, folosind algoritmul din curs (C5IA, p. 53)
 * @param configuration
 * @param configuration_length
 * @return numarul de atacuri posibile in configuratia data
 */
int evaluate_configuration(int* configuration, int configuration_length) {
	int attacks = 0;
	for (int i = 0; i < configuration_length - 1; i++) {
		for (int j = i + 1; j < configuration_length; j++) {
			if (abs(configuration[i] - configuration[j]) == abs(i - j)) {
				attacks++;
			}
		}
	}
	return attacks;
}

/**
 * @brief Genereaza o lista cu primele numere naturale nenule, pana la un numar
 * dat (inclusiv), distincte intre ele si permutate aleatoriu
 * @param configuration pointer la lista creata in avans
 * @param configuration_length numarul pana la care se genereaza elementele
 * listei
 *
 * Algoritm:
 * - se completeaza lista primita cu primele numere naturale nenule
 * consecutive pana la un numar dat;
 * - se "amesteca" elementele din lista folosind algoritmul P, de "shuffling",
 * descris in "The Art of Computer Programming" [Knuth, vol. II, ed. 3, 1997;
 * pag. 145].
 */
void generate_configuration(int* configuration, int configuration_length) {
	// completeaza lista cu numerele naturale pana la limit
	int i = 0;
	for (i = 0; i < configuration_length; i++) {
		configuration[i] = i + 1;
	}

	// shuffling
	i = configuration_length - 1;  // i va fi index in lista
	while (i > 0) {
		// genereaza un numar natural aleatoriu intre 0 si i
		// dar Knuth: "k should not be computed by taking a remainder modulo j"
		// trecem peste recomandare in lipsa unei functii simple, fara <random>,
		// care sa satisfaca cerinta lui: "Generate a random number U, uniformly
		// distributed between zero and one"
		int j = rand() % (i + 1);

		// schimba intre ele (shuffle) elementele cu indexul i si j
		int temp = configuration[i];
		configuration[i] = configuration[j];
		configuration[j] = temp;

		i--;
	}
}

/**
 * @brief Reamesteca elementele unei liste folosind numere aleatorii, folosind
 * algoritmul din curs (C5IA, p. 55)
 * @param configuration
 * @param configuration_length
 */
void perturb_configuration(int* configuration, int configuration_length) {
	int i = rand() % configuration_length;
	int j = rand() % configuration_length;
	if (i == j) {  // while nu avea sens asa cum apare in algortimul din curs
		j = rand() % configuration_length;
	}
	int temp = configuration[i];
	configuration[i] = configuration[j];
	configuration[j] = temp;
}
#pragma endregion Algorithms

#pragma region Utils
/**
 * @brief Obtine de la utilizator un numar intreg valabil si il aloca variabilei
 * primite
 * @param integer pointer la variabila care va folosi valoarea introdusa
 */
void get_integer(int* integer) {
	int temp;

	while (true) {
		// FIXME: input de tip 8asd e validat ca 8
		if ((cin >> temp) && (temp > 0)) {
			cin.ignore(1000, '\n');	 // 1000 e arbitrar ales
			break;
		}
		cout << "Numarul trebuie sa fie un intreg mai mare sau egal cu 0!\n"
				"Mai incearca: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	*integer = temp;
}

/**
 * @brief Afiseaza cerinta
 */
void print_problem() {
	cout << "\nScrie numarul de dame (> 0): ";
}

/**
 * @brief Afiseaza rezultatul in linii de cel mult 10 elemente
 * @param list lista de afisat
 * @param list_size dimensiunea listei
 */
void print_result(int* list, int list_size) {
	for (int i = 0; i < list_size; i++) {
		cout << setw(7) << std::right << list[i];
		if (((i + 1) % 10 == 0) && (i != list_size - 1)) {
			cout << '\n';
		}
	}
}

/**
 * @brief Copiaza o lista (array)
 * @param list
 * @param list_size
 * @return pointer la noua lista (dimensiunea e deja cunoscuta)
 */
int* copy_list(int* list, int list_size) {
	int* result = new int[list_size];
	for (int i = 0; i < list_size; i++) {
		result[i] = list[i];
	}
	return result;
}
#pragma endregion Utils