#include"my_8_bit.h"

int main(){
	Program TEST;
	TEST.LOADLIT(R1, "0b");
	TEST.LOADLIT(R2, "0f"); 
	TEST.SUBR(R2,R1,R1);
	TEST.BRE("fa0f");
	TEST.end();
	
}
