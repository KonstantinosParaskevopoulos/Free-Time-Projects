#ifndef _MY8BIT_H
#define _MY8BIT_H

#include <iostream>
#include <fstream>
#include <cstring>

#define	R0 "0"
#define	R1 "1"
#define	R2 "2"
#define	R3 "3"
#define	R4 "4"
#define	R5 "5"
#define	R6 "6"
#define	R7 "7"
#define	R8 "8"
#define	R9 "9"
#define	R10 "a"
#define	R11 "b"
#define	R12 "c"
#define	R13 "d"
#define	R14 "e"
#define	R15 "f"
#define Rout "e"
#define Rin "f"

using namespace std;



class Program{
	public:
	ofstream file;
	int count =0;
	string filename;

	Program(){
		cout<<"Name of the Program? (no spaces PLEASE!!)"<<endl;
		cin>>filename;
		file.open(filename);
	file<<"v2.0 raw\n";
	}

void COPY(string RA, string RC);
void ADD(string RA, string RB, string RC);
void SUB(string RA, string RB, string RC);
void ADI(string RA, string RC);
void SUBR(string RA, string RB, string RC);
void LSR(string RA, string RC);
void HEX2ASC(string RA, string RC);
void NOT(string RA, string RC);
void AND(string RA, string RB, string RC);
void NAND(string RA, string RB, string RC);
void OR(string RA, string RB, string RC);
void NOTOR(string RA, string RB, string RC);
void ORNOT(string RA, string RB, string RC);
void NOR(string RA, string RB, string RC);
void XOR(string RA, string RB, string RC);
void XNOR(string RA, string RB, string RC);
void LOAD(string RA, string RB);
void LOADADR(string RA, string RB, string ADDRESS);
void LOADLIT(string RA,  string DATA);
void LSLOAD(string RA, string RC);
void RSLOAD(string RA, string RC);
void CRSLOAD(string RA, string RC);
void STORE(string RA, string RB);
void NOP();
void BRE(string D);
void BRZ(string D);
void BRC(string D);
void BRN(string D);
void BRO(string D);
void JMP(string D);
void GOTO(string D);
void MBRE(string D);
void MBRZ(string D);
void MBRC(string D);
void MBRN(string D);
void MBRO(string D);
void MJMP(string D);
void SCANCH();
void PRINTCH(string RA);
void end();
void PRINT(string s);

};

void Program::COPY(string RA, string RC){
	file<<"00"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::ADD(string RA, string RB, string RC){
	file<<"01"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::SUB(string RA, string RB, string RC){
	file<<"02"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::ADI(string RA, string RC){
	file<<"03"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::SUBR(string RA, string RB, string RC){
	file<<"04"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::LSR(string RA, string RC){
	file<<"05"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::HEX2ASC(string RA, string RC){
	file<<"06"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::NOT(string RA, string RC){
	file<<"07"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::AND(string RA, string RB, string RC){
	file<<"08"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::NAND(string RA, string RB, string RC){
	file<<"09"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::OR(string RA, string RB, string RC){
	file<<"0a"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::NOTOR(string RA, string RB, string RC){
	file<<"0b"<<RA<<RB<<RC<<"000";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::ORNOT(string RA, string RB, string RC){
	file<<"0c"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::NOR(string RA, string RB, string RC){
	file<<"0d"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::XOR(string RA, string RB, string RC){
	file<<"0e"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::XNOR(string RA, string RB, string RC){
	file<<"0f"<<RA<<RB<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::LOAD(string RA, string RB){
	file<<"10"<<RA<<RB<<"0000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::LOADADR(string RA, string RB, string ADDRESS){
	file<<"11"<<RA<<RB<<ADDRESS<<"00 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::LOADLIT(string RA,  string DATA){
	file<<"13"<<RA<<"0"<<DATA<<"00 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::LSLOAD(string RA, string RC){
	file<<"51"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::RSLOAD(string RA, string RC){
	file<<"52"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::CRSLOAD(string RA, string RC){
	file<<"53"<<RA<<"0"<<RC<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::STORE(string RA, string RB){
	file<<"40"<<RA<<RB<<"0000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::NOP(){
	file<<"7f"<<"000000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::BRE(string D){
	file<<"30"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::BRZ(string D){
	file<<"31"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::BRC(string D){
	file<<"32"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::BRN(string D){
	file<<"33"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::BRO(string D){
	file<<"34"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::JMP(string D){
	file<<"35"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::GOTO(string D){
	file<<"36"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::MBRE(string D){
	file<<"70"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::MBRZ(string D){
	file<<"71"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::MBRC(string D){
	file<<"72"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::MBRN(string D){
	file<<"73"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::MBRO(string D){
	file<<"74"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::MJMP(string D){
	file<<"75"<<"00"<<D<<" ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::SCANCH(){
	file<<"23"<<"0"<<"e"<<"0000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}

void Program::PRINTCH(string RA){
	file<<"22"<<RA<<"0"<<"f"<<"000 ";
	count++;
	if(count%8==0){
	file<<"\n";
	}
}
void Program::end(){
	file.close();
	float perc;
	perc = ((float)count/65536)*100;
	system("cls");
	cout<<"Succesful Compilation!!!\n"<<endl;
	cout<<count<<"B of total 65.536B (64KB) ["<<perc<<"%] of memory Used"<<endl;
	
}


void Program::PRINT(string s){
	
	// assigning value to string s
	int n = s.length();
	char char_array[n+1];
	
	// copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
 
    for (int i = 0; i < n; i++)
        {
		//cout << char_array[i];
    	file<<"13"<<R0<<"0"<<hex<<(int)char_array[i]<<"00 ";
		count++;
		if(count%8==0){
			file<<"\n";
			}	
		PRINTCH(R0);
		
		}
	
}




#endif
