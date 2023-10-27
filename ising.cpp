#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#define N 4
#define L 1000

double J=1.0, B=0.0, T=0.2, Z;
double* res = new double [L+1];
double M;
bool map[31][201];

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
			E -= 0.5 * J, E += J * ((i > 1) ? int(s[i][j] ^ s[i-1][j]) : int(s[i][j] ^ s[i+N-1][j]));
			E -= 0.5 * J, E += J * ((j > 1) ? int(s[i][j] ^ s[i][j-1]) : int(s[i][j] ^ s[i][j+N-1]));
			E -= 0.5 * J, E += J * ((i < N) ? int(s[i][j] ^ s[i+1][j]) : int(s[i][j] ^ s[i-N+1][j]));
			E -= 0.5 * J, E += J * ((j < N) ? int(s[i][j] ^ s[i][j+1]) : int(s[i][j] ^ s[i][j-N+1]));
		}						// Each bond has been calculated twice, thus 0.5 is multiplied.
	}
	return E;
}

double Partition(bool** s, int i, int j, bool value) {
	bool** x = new bool* [N+1];
	for(int a=1;a<=N;a++) {
		x[a] = new bool [N+1];
		for(int b=1;b<=N;b++)
			x[a][b] = s[a][b];
	}
	x[i][j] = value;
	if(i == N && j == N)
		return exp(-H(x)/T);
	if(j == N)
		return Partition(x, i+1, 1, true) + Partition(x, i+1, 1, false);
	return Partition(x, i, j+1, true) + Partition(x, i, j+1, false);
}

double m(bool** s) {			// Magnetic moment
	double MM = 0.0;
	for(int i=1;i<=N;i++) {
		for(int j=1;j<=N;j++) {
			double spin = -1;
			spin += 2 * int(s[i][j]);
			MM += double(spin) / N / N;
		}
	}
	return abs(MM);
}

double Expectation(bool** s, int i, int j, bool value) {
	bool** x = new bool* [N+1];
	for(int a=1;a<=N;a++) {
		x[a] = new bool [N+1];
		for(int b=1;b<=N;b++)
			x[a][b] = s[a][b];
	}
	x[i][j] = value;
	if(i == N && j == N)
		return m(x) * exp(-H(x)/T) / Z;
	if(j == N)
		return Expectation(x, i+1, 1, true) + Expectation(x, i+1, 1, false);
	return Expectation(x, i, j+1, true) + Expectation(x, i, j+1, false);
}

int main() {

	bool** s = new bool* [N+1];
	for(int i=1;i<=N;i++) {
		s[i] = new bool [N+1];
	}

	freopen("ising.txt", "w", stdout);

	int a = 1;
	while(T <= 20) {
		Z = Partition(s, 1, 1, true) + Partition(s, 1, 1, false);
		M = Expectation(s, 1, 1, true) + Expectation(s, 1, 1, false);
        printf("%4.0f            Z = %f            <m> = %f\n", T, Z, M);
		T += 0.2;
        map[int(M*30)][a++] = true;
	}

	for(int i=30;i>=0;i--) {
        for(int j=1;j<=100;j++) {
            if(map[i][j])
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }

	return 0;
}


