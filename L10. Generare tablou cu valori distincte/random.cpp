/**
 *  L10. Scrieti un program care sa genereze un tablou cu primele N numere
 * naturale (N este o constanta intreaga pozitiva ce poate fi 8 sau mai mult),
 * distincte intre ele (niciun numar nu apare de doua ori), permutate aleatoriu.
 * Chiar daca N este 100, programul ar trebui sa ruleze in mai putin de o
 * secunda.
 *
 * Exemplu:
 * Daca N este 8, atunci un rezultat ar putea fi:
 * 5 7 1 4 8 2 6 3
 * Sunt afisate toate numerele de la 1 la 8 si sunt permutate aleatoriu.
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
void generate_numbers(int*, int);

// variabile globale
string separator =
	"\n "
	"*********************************************************************\n";
#pragma endregion Setup

/**
 * @brief Inceputul executiei
 */
int main() {
	// "seed" functia rand() cu timpul curent
	// N.B. srand() trebuie apelata o singura data in aplicatie!
	srand(time(0));

	int number;

	while (true) {
		print_problem();
		get_integer(&number);

		// aloca dinamic lista
		int* list = new int[number];
		if (list == NULL) {
			cout << " \nEroare: Memoria nu a fost alocata.\n";
			delete[] list;
			continue;
		}

		generate_numbers(list, number);
		print_result(list, number);

		cout << separator;

		delete[] list;
	}

	return 0;
}

#pragma region Algorithms
/**
 * @brief Genereaza o lista cu primele numere naturale nenule, pana la un numar
 * dat (inclusiv), distincte intre ele si permutate aleatoriu
 * @param list pointer la lista creata in avans
 * @param limit numarul pana la care se genereaza elementele listei
 *
 * Algoritm:
 * - se completeaza lista primita cu primele numere naturale nenule
 * consecutive pana la un numar dat;
 * - se "amesteca" elementele din lista folosind algoritmul P, de "shuffling",
 * descris in "The Art of Computer Programming" [Knuth, vol. II, ed. 3, 1997;
 * pag. 145].
 */
void generate_numbers(int* list, int limit) {
	// completeaza lista cu numerele naturale pana la limit
	int i = 0;
	for (i = 0; i < limit; i++) {
		list[i] = i + 1;
	}

	// shuffling
	i = limit - 1;	// i va fi index in lista
	while (i > 0) {
		// genereaza un numar natural aleatoriu intre 0 si i
		// dar Knuth: "k should not be computed by taking a remainder modulo j"
		// trecem peste recomandare in lipsa unei functii simple, fara <random>,
		// care sa satisfaca cerinta lui: "Generate a random number U, uniformly
		// distributed between zero and one"
		int j = rand() % (i + 1);

		// schimba intre ele (shuffle) elementele cu indexul i si j
		int temp = list[i];
		list[i] = list[j];
		list[j] = temp;

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
		if ((cin >> temp) && (temp >= 8)) {
			cin.ignore(1000, '\n');	 // 1000 e arbitrar ales
			break;
		}
		cout << " Numarul trebuie sa fie un intreg mai mare sau egal cu 8!\n"
				" Mai incearca: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	*integer = temp;
}

/**
 * @brief Afiseaza cerinta
 */
void print_problem() {
	cout << "\n Scrie un intreg (>= 8): ";	// sau cu Unicode: (\u2265 8),
											// daca e compilat cu -std=c++11
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
#pragma endregion Utils