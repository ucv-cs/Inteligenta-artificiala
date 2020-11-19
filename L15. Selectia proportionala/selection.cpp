/**
 * L15. Scrieti un program care sa aplice o selectie proportionala (sau Monte
 * Carlo sau Softmax) pentru a alege din o multime de (maxim 30) optiuni,
 * fiecare cu evaluarea sa data.
 * Descrierea sa (cu exemplu) o gasiti la
 * http://inf.ucv.ro/documents/cstoean/c7IA_27.pdf, slide-urile 31-35.
 * Iata un exemplu de intrare a problemei: 30 10 5 60 90 20
 * Observatii suplimentare:
 * - Setati numarul de optiuni ca si constanta in program;
 * - Introduceti evaluarile pentru fiecare actiune in parte ca si valori direct
 * in program, nu le cititi de la tastatura;
 * - Afisati la final ce actiune a fost aleasa (indexul sau) si care a fost
 * evaluarea sa.
 */
#include <cstdlib>	 // RAND_MAX, srand(), rand()
#include <ctime>	 // time()
#include <iostream>	 // cout, cin

using namespace std;

int options[] = {2, 5, 17, 90, 32, 29, 56, 72, 84, 49};
const int count = sizeof(options) / sizeof(options[0]);
float q[count] = {0};

/**
 * @brief Genereaza un numar real intre limitele date
 * @param minimum
 * @param maximum
 * @result numarul generat
 *
 * https://stackoverflow.com/questions/686353/random-float-number-generation#686373
 * Probabil ar trebui folosite metode standard in C++ (v.
 * https://isocpp.org/files/papers/n3551.pdf)
 */
float random(float minimum = 0, float maximum = 1) {
	return minimum + rand() * (maximum - minimum) / RAND_MAX;
}

/**
 * @brief Calculeaza valorile vectorului global q, cf. algoritmului din curs,
 * pag. 33
 */
void compute_q() {
	float sum = 0;
	for (int i = 0; i < count; i++) {
		sum += options[i];
	}

	float temp = 0;
	for (int i = 0; i < count; i++) {
		temp += options[i];
		q[i] = temp / sum;
	}
}

/**
 * @brief Selectie Monte Carlo, cf. algoritmului din curs, pag. 35
 * @return indexul din options selectat
 */
int roulette() {
	float r = random();
	int i = 0;
	while (q[i] < r) {
		++i;
	}
	return i;
}

/**
 * @brief Afiseaza o lista de obiecte de tip oarecare (T)
 * @param array
 */
template <typename T>
void print_array(T* array) {
	cout << "{";
	for (int i = 0; i < count - 1; i++) {
		cout << array[i] << ", ";
	}
	cout << array[count - 1] << "}";
}

/**
 * @brief Inceputul executiei
 */
int main() {
	srand(time(0));

	cout << "Optiunile sunt:\n\toptions[" << count << "] = ";
	print_array(options);

	compute_q();
	cout << "\n\n\tQ[" << count << "] = ";
	print_array(q);

	int counter = 1;
	while (true) {
		int result = roulette();
		cout << "\n\nRezultatul selectiei nr. " << counter << ":\n\toptions["
			 << result << "] = " << options[result] << " (q = " << q[result]
			 << ")";

		cout << "\n\nContinuam? (y/n) ";
		char answer;
		cin >> answer;
		if (answer != 'y') {
			break;
		}
		counter++;
	}
}