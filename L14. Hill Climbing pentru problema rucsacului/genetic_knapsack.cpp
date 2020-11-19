/**
 * L14. Avand exemplul cu problema rucsacului de la algoritmi evolutivi, sa se
 * implementeze un algoritm Hill Climbing pentru rezolvarea unei instante a
 * rucsacului. (...)
 * Va rog sa introduceti valorile in interiorul programului, nu puneti
 * utilizatorul sa le introduca de la tastatura.
 */
#include <cstdlib>	 // srand(), rand(), abs()
#include <ctime>	 // time()
#include <iomanip>	 // setw(), right, left
#include <iostream>	 // cout, cin

using namespace std;

int capacity = 368;
int items[] = {45, 40, 60, 88, 12, 69, 73, 95, 65, 46, 71, 37, 10, 66, 38,
			   83, 91, 27, 24, 22, 51, 35, 63, 51, 76, 95, 21, 11, 90, 28};
const int count = sizeof(items) / sizeof(items[0]);
int chromozome[count] = {0};
int new_chromozome[count] = {0};

const int call_limit = 1e6;
int evaluation_call_count = 0;

/**
 * @brief Genereaza aleatoriu valori de 0 sau 1 pentru toate elementele unui
 * cromozom; se cunoaste numarul de elemente (count)
 * @param chromozome pointer la cromozom
 */
void generate(int* chromozome) {
	for (int i = 0; i < count; i++) {
		chromozome[i] = rand() % 2;
	}
}

/**
 * @brief Inverseaza aleatoriu un singur bit din cromozom; se cunoaste numarul
 * de elemente (count)
 * @param chromozome pointer la cromozom
 */
void perturb(int* chromozome) {
	int i = rand() % count;
	chromozome[i] = 1 - chromozome[i];
}

/**
 * @brief Calculeaza greutatea totala a unui cromozom dat; se cunoaste numarul
 * de elemente (count) si array-ul cu greutatile obiectelor (items[])
 * @param chromozome pointer la cromozom
 */
int evaluate(int* chromozome) {
	evaluation_call_count++;
	int gene_evaluation = 0;
	for (int i = 0; i < count; i++) {
		gene_evaluation += chromozome[i] * items[i];
	}
	return abs(capacity - gene_evaluation);
}

/**
 * @brief Afiseaza o lista in linii de cel mult 10 elemente
 * @param list pointer la lista de afisat
 * @param list_size dimensiunea listei
 */
void print_array(int* list, int list_size) {
	for (int i = 0; i < list_size; i++) {
		cout << setw(7) << std::right << list[i];
		if (((i + 1) % 10 == 0) && (i != list_size - 1)) {
			cout << '\n';
		}
	}
}

/**
 * @brief Inceputul executiei
 */
int main() {
	srand(time(0));

	long start = time(0);
	int time_elapsed = 0;
	int cost;
	int iteration_count = 50;

	do {
		generate(chromozome);
		for (int i = 0; i < count; i++) {
			new_chromozome[i] = chromozome[i];
		}

		cost = evaluate(chromozome);
		for (int i = 0; i < iteration_count; i++) {
			perturb(chromozome);
			int evaluation = evaluate(chromozome);
			if (cost > evaluation) {
				cost = evaluation;
				for (int j = 0; j < count; j++) {
					new_chromozome[j] = chromozome[j];
				}
			}
		}

		time_elapsed = time(0) - start;
	} while ((cost != 0) && (time_elapsed < 3) &&
			 (evaluation_call_count < call_limit));

	cout << "Capacitatea rucsacului: " << capacity;
	cout << "\nObiectele disponibile:\n";
	print_array(items, count);

	cout << "\n\nSolutia gasita:\n";
	print_array(new_chromozome, count);

	cout << "\nCostul solutiei: " << cost;

	cout << "\nObiectele introduse in rucsac: ";
	int added_weight = 0;
	for (int i = 0; i < count; i++) {
		if (new_chromozome[i] == 1) {
			cout << items[i] << " ";
			added_weight += items[i];
		}
	}

	cout << "\nGreutatea totala a obiectelor introduse in rucsac: "
		 << added_weight;
	cout << "\nTimpul de executie: " << time_elapsed << " s";
	cout << "\nApelari ale functiei de evaluare: " << evaluation_call_count;

	cout << "\n\nApasa ENTER pentru a inchide aplicatia...";
	getchar();
}