#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include <ctime>

#define N 100
#define L 10000000

double T = 50;
double J = 1.0, B = 0.0;
double* dH = new double [L+1];
double* mm = new double [L+1];
bool map[31][201];

std::mt19937 ran((int)time(0));
std::uniform_real_distribution<double> distr(0,1);

double Random() {
	return distr(ran);			// Random number in [0,1]
}

int Select() {
    return 1 + ran() % N;	    // Random integer from 1 to N
}

int main() {
    freopen("sample.txt","w",stdout);

    int a = 1;
    while(T <= 4000) {
        int** s = new int* [N+1];
    	for(int i=1;i<=N;i++) {
	    	s[i] = new int [N+1];
            for(int j=1;j<=N;j++) {
                s[i][j] = -1;       // Ground State
            }
    	}

        mm[0] = -1;
        for(int t=1;t<=L;t++) {
            int i = Select();
            int j = Select();
            dH[t] = dH[t-1];        // dH denotes the energy changes from the ground state to the current state.
            mm[t] = mm[t-1];        // m denotes the magnetic moment of each state.
            dH[t] += 2.0 * J * s[i][j] * ((i > 1) ? s[i-1][j] : s[i+N-1][j]);
            dH[t] += 2.0 * J * s[i][j] * ((j > 1) ? s[i][j-1] : s[i][j+N-1]);
            dH[t] += 2.0 * J * s[i][j] * ((i < N) ? s[i+1][j] : s[i-N+1][j]);
            dH[t] += 2.0 * J * s[i][j] * ((j < N) ? s[i][j+1] : s[i][j-N+1]);       // Periodic boundary conditions
            if(Random() <= exp(-dH[t] / T)) {
                s[i][j] *= -1;
                mm[t] += 2.0 * s[i][j] / N / N;
            } else {
                dH[t] = dH[t-1];
            }
        }

        double M = 0.0;
        for(int t=1;t<=L;t++) {
            M += abs(mm[t]) / L;
            /* if(t % (L/20) == 0)
                printf("%7.4f       %f\n", mm[t], dH[t]); */
        }
        printf("%4.0f            %f\n", T, M);
        T += 50;
        map[int(M*30)][a++] = true;
    }
    /* printf("\n\n\n");
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            if(s[i][j] == 1) {
                printf("+");
            } else {
                printf("-");
            }
        }
        printf("\n");
    } */

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
