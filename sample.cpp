#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include <ctime>

// #define L 100000
int N, L;
double T = 0.1;
double J = 1.0, B = 0.0;
double dH;
double M[201];
bool map[31][201];

std::mt19937 ran((int)time(0));
std::uniform_real_distribution<double> distr(0,1);

double Random() {
	return distr(ran);			// Random number in [0,1]
}

int Select() {
    return 1 + ran() % N;	    // Random integer from 1 to N
}

double Abs(double x) {
	return (x >= 0) ? x : -x;
}

int main(int argc, char** argv) {

	if(argc == 1) {
		printf("N is not given! Use the following form:\n./sample <N> <order_of_L>\n");
		return 0;
	}

	if(argc == 2) {
		printf("Order of L is not given! Use the following form:\n./sample <N> <order_of_L>\n");
		return 0;
	}

	for(int i=0;argv[1][i] != '\0';i++) {
		N *= 10;
		N += argv[1][i] - '0';
	}
	
	int b = 0;
	double l = 0;
	for(int i=0;argv[2][i] != '\0';i++) {
		if(argv[2][i] == '.') {
			b = 1;
			continue;
		}
		l *= 10;
		l += argv[2][i] - '0';
		b *= 10;
	}
	if(b == 0)
		b = 1;
	L = int(pow(10.0, l / double(b)));
	double* mm = new double [L+1];

	freopen("sample.txt","w",stdout);

    int a = 0;
	int** s = new int* [N+1];
    for(int i=1;i<=N;i++) {
	    s[i] = new int [N+1];
    }
    while(T <= 8.0) {
    	for(int i=1;i<=N;i++) {
            for(int j=1;j<=N;j++) {
                s[i][j] = -1;       // Ground State
            }
    	}
		
        mm[0] = -1;
        for(int t=1;t<=L;t++) {
            int i = Select();
            int j = Select();
            dH = 0;        // dH denotes the energy changes from the last to current state.
            mm[t] = mm[t-1];        // m denotes the magnetic moment of each state.
            dH += 2.0 * J * s[i][j] * ((i > 1) ? s[i-1][j] : s[i+N-1][j]);
            dH += 2.0 * J * s[i][j] * ((j > 1) ? s[i][j-1] : s[i][j+N-1]);
            dH += 2.0 * J * s[i][j] * ((i < N) ? s[i+1][j] : s[i-N+1][j]);
            dH += 2.0 * J * s[i][j] * ((j < N) ? s[i][j+1] : s[i][j-N+1]);       // Periodic boundary conditions
            if(Random() <= exp(-dH / T)) {
                s[i][j] *= -1;
                mm[t] += 2.0 * s[i][j] / N / N;
            }
        }

        M[++a] = 0.0;
        for(int t=1;t<=L;t++) {
            M[a] += Abs(mm[t]);
        }
		M[a] /= double(L);
        T += 0.1;
        map[int(M[a]*30)][a] = true;
		if(a == 1) {
			printf("%4.1f    %f    %f\n", T, M[a], 0.0);
			continue;
		}
        printf("%4.1f    %f    %f\n", T, M[a], M[a-1] - M[a]);
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

