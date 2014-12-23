/*
Algoritmo do resto chines
OBS: Baseado no problema D da maratona UnB 2014
*/

#include <iostream>

using namespace std;

long gcd(long a, long b, long& x, long& y){

	long x1, y1, d;

	if( !b ){
		x = 1;
		y = 0;
		return a;
	}

	d = gcd(b, a%b, x1, y1);

	x = y1;
	y = x1 - (a/b)*y1;

	return d;
}

void fixModInv(long& inv, long mod){
	while( inv < 0 )
		inv += mod;
}

int main(void){

	ios::sync_with_stdio(false);

	long R1, MOD1;
	long R2, MOD2;
	long R3, MOD3;
	long RX, MODX;
	long temp, INV1, INV2, INVX, INV3, result;
	long T;

	T=1;

	while( cin >> R1 >> MOD1 ){

		cin >> R2 >> MOD2 >> R3 >> MOD3;

		gcd(MOD2, MOD1 % MOD2, temp, INV1);
		gcd(MOD1, MOD2 % MOD1, temp, INV2);

		fixModInv(INV1, MOD2);
		fixModInv(INV2, MOD1);

		MODX = MOD1 * MOD2;
		RX = (R2*INV1*MOD1 + R1*INV2*MOD2) % MODX;

		gcd(MOD3, MODX % MOD3, temp, INVX);
		gcd(MODX, MOD3 % MODX, temp, INV3);

		fixModInv(INVX, MOD3);
		fixModInv(INV3, MODX);
		
		result = (R3*INVX*MODX + RX*INV3*MOD3) % (MODX*MOD3);

		if( !result )
			result = MOD1 * MOD2 * MOD3;

		cout << "Caso #" << T++ << ": " << result << " laranja(s)" << endl;

	}

	return 0;
}
