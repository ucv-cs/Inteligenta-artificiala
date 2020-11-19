/**
 * L12.
 * Avem de la LS011 initializarea, evaluarea si perturbarea pentru problema
 * aranjarii damelor folosind Hill Climbing.
 *
 * Introduceti o bucla care sa se execute pentru un numar de iteratii (un "for")
 * in care sa se aplice perturbarea si comparati evaluarea vectorului initial
 * fata de cel perturbat. Il pastrati ca vector curent pe cel cu evaluarea mai
 * buna (cu valoare mai mica, deci mai putine atacuri).
 *
 * Apoi includeti o bucla cu while in care sa cuprindeti atat initializarea, cat
 * si bucla "for". Ca si conditii de oprire veti folosi gasirea unui vector care
 * are evaluarea 0 sau trecerea a mai mult de 3 secunde sau verificarea a mai
 * mult de un milion de apelari ale functiei de evaluare. La iesirea din while
 * veti afisa:
 * 1. Cea mai buna solutie (vectorul), cu evaluarea sa
 * 2. Cat timp a durat rularea in secunde
 * 3. De cate ori s-a apelat functia de evaluare.
 *
 * Vedeti si http://inf.ucv.ro/documents/cstoean/c5IA.pdf , slide-ul 56.
 *
 * Daca nu reusiti sa rezolvati toate punctele de la aceasta tema, va rog sa imi
 * trimiteti si rezolvarea partiala.
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
void generate(int*, int);
int evaluate(int*, int);
void perturb(int*, int);

// variabile globale
const int iteration_count = 10;
static int evaluate_call_count = 0;
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

	int count;	// dimensiunea unei configuratii (ex. 8 pentru 8 dame)

	while (true) {
		print_problem();
		get_integer(&count);

		// aloca dinamic lista initiala
		int* configuration = new int[count];

		generate(configuration, count);

		// evaluarea configuratiei initiale
		int eval_initial = evaluate(configuration, count);

		cout << "\nConfiguratia initiala:\n";
		print_result(configuration, count);
		cout << "\nNumarul de atacuri in aceasta configuratie: "
			 << eval_initial;

		// noua configuratie porneste de la cea initiala, urmand apoi sa fie
		// perturbata
		int* new_configuration = copy_list(configuration, count);

		long start = time(0);
		int time_elapsed = 0;

		int eval_new = 0;
		do {
			// bucla for in care aplicam perturbarea de un numar de ori
			for (int i = 0; i < iteration_count; i++) {
				perturb(new_configuration, count);

				// evaluarea noii configuratii
				eval_new = evaluate(new_configuration, count);

				// comparam evaluarile si pastram configuratia cu evaluarea
				// mai buna
				if (eval_initial < eval_new) {
					// pastram lista cu evaluarea cat mai mica
					new_configuration = copy_list(configuration, count);
					eval_new = eval_initial;
				}
			}
		} while (eval_new != 0 && evaluate_call_count <= 1e6 &&
				 (time_elapsed = difftime(time(0), start)) <= 3);

		cout << "\n\nConfiguratia optima  :\n";
		print_result(new_configuration, count);
		cout << "\nNumarul de atacuri in aceasta configuratie: " << eval_new;
		cout << "\nTimp: " << time_elapsed << " s";
		cout << "\nApelari ale functiei de evaluare: " << evaluate_call_count;

		cout << separator;

		// recupereaza spatiul
		delete[] configuration;
		delete[] new_configuration;

		// reseteaza contorul functiei evaluate()
		evaluate_call_count = 0;
	}

	return 0;
}

#pragma region Algorithms
/**
 * @brief Calculeaza numarul de atacuri posibile intr-o configuratie de dame si
 * il returneaza, folosind algoritmul din curs (C5IA, p. 53)
 * @param configuration
 * @param count
 * @return numarul de atacuri posibile in configuratia data
 */
int evaluate(int* configuration, int count) {
	evaluate_call_count++;

	int attacks = 0;
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (abs(configuration[i] - configuration[j]) == abs(i - j)) {
				attacks++;
			}
		}
	}
	return attacks;
}

/**
 * @brief Reamesteca elementele unei liste folosind numere aleatorii, folosind
 * algoritmul din curs (C5IA, p. 55)
 * @param configuration
 * @param count
 */
void perturb(int* configuration, int count) {
	int i = rand() % count;
	int j = rand() % count;
	if (i == j) {  // while nu avea sens asa cum apare in algortimul din curs
		j = rand() % count;
	}
	int temp = configuration[i];
	configuration[i] = configuration[j];
	configuration[j] = temp;
}

/**
 * @brief Genereaza o lista cu primele numere naturale nenule, pana la un numar
 * dat (inclusiv), distincte intre ele si permutate aleatoriu
 * @param configuration pointer la lista creata in avans
 * @param count numarul pana la care se genereaza elementele
 * listei
 *
 * Algoritm:
 * - se completeaza lista primita cu primele numere naturale nenule
 * consecutive pana la un numar dat;
 * - se "amesteca" elementele din lista folosind algoritmul P, de "shuffling",
 * descris in "The Art of Computer Programming" [Knuth, vol. II, ed. 3, 1997;
 * pag. 145].
 */
void generate(int* configuration, int count) {
	// completeaza lista cu numerele naturale pana la limit
	int i = 0;
	for (i = 0; i < count; i++) {
		configuration[i] = i + 1;
	}

	// shuffling
	i = count - 1;	// i va fi index in lista
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