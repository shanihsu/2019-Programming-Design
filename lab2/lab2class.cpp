#include "lab2class.h"
void score::set(float Ra, float Rb, int K){
	K_p = K;
	Ra_p = Ra;
	Rb_p = Rb;
}

void score::calculate(float Sa, float Ra_p, float Rb_p, int K_p){
	float Sb;
	double Ea, Eb;
	Sb = 1 - Sa;
	Ea = 1/(1+pow(10,(Rb_p-Ra_p)/400));
	Eb = 1/(1+pow(10,(Ra_p-Rb_p)/400));
	Ra_pc =  round(Ra_p+K_p*(Sa-Ea));
	Rb_pc =  round(Rb_p+K_p*(Sb-Eb));
}

float score::getRa(){
	return Ra_pc;
}

float score::getRb(){
	return Rb_pc;
}
 
