#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#define N 100

double J=1.0, B=0.0, T=10, Z;
double res[101];

std::mt19937 ran((int)time(0));
std::uniform_real_distribution<double> distr(0,1);

double Random() {
	return distr(ran);			// Random number in [0,1]
}

bool Select() {
    return ((ran() % 2) == 1);	// Random true / false
}

void Generate(bool** s) {		// Generate a random state
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			s[i][j] = Select();
}

double H(bool** s) {			// Hamiltonian
	double E = 0.0;
	for(int i=1;i<=N;i++) {
		for(int j=1;j<=N;j++) {
			E += B, E -= B * 2 * (int)s[i][j];
			if(i > 1) E -= J, E += J * 2 * int(s[i][j] ^ s[i-1][j]);
			if(j > 1) E -= J, E += J * 2 * int(s[i][j] ^ s[i][j-1]);
			if(i < N) E -= J, E += J * 2 * int(s[i][j] ^ s[i+1][j]);
			if(j < N) E -= J, E += J * 2 * int(s[i][j] ^ s[i][j+1]);
		}
	}
	return E;
}

double Partition(bool** s, int i, int j, bool value) {
	s[i][j] = value;
	if(i == N && j == N)
		return exp(-H(s)/T);
	if(j == N)
		return Partition(s, i+1, 1, true) + Partition(s, i+1, 1, false);
	return Partition(s, i, j+1, true) + Partition(s, i, j+1, false);
}

double m(bool** s) {			// Magnetic moment
	double M = 0.0;
	for(int i=1;i<=N;i++) {
		for(int j=1;j<=N;j++) {
			double spin = -1;
			spin += 2 * int(s[i][j]);
			M += spin / N / N;
		}
	}
	return M;
}

int main() {

	bool** s = new bool* [N+1];
	for(int i=1;i<=N;i++) {
		s[i] = new bool [N+1];
	}

//	Z = Partition(s, 1, 1, true) + Partition(s, 1, 1, false);
//	printf("%f\n", Z);

	Generate(s);

	for(int t=0;t<=100;t++) {
		bool** x = new bool* [N+1];
		for(int i=1;i<=N;i++) {
			x[i] = new bool [N+1];
		}
		Generate(x);
		double p = exp((H(x) - H(s)) / T);
		double q = 1 / (1 + p);
		double d = Random();
		if(d <= q)
			s = x;
		res[t] = m(s);
	}

	freopen("ising.txt", "w", stdout);
	for(int t=0;t<=100;t++)
		printf("%7.4f\n", res[t]);

	return 0;
}


