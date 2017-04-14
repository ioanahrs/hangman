#include <fstream>
#include <string.h>
#include <iostream>
#include <stdlib.h> // pentru strand
#include <time.h>

using namespace std;

typedef struct JUCATOR {
    char nume[40];
    int victorii;
    int vieti;
} JUCATOR;

//spanzuratoarea
char cuvant[50];
int  af_litera[50];


int raspuns = 0;
//x si 0

int tabla[3][3];
JUCATOR j1, j2, j3;

void afisare_cuvant(){
    int i;
    for(i=0; i<strlen(cuvant); i++)
        if(af_litera[i] == 1)
            cout<<cuvant[i]<<" ";
        else
            cout<< "_ ";
    cout<<endl;
}

int procesare_litera(char ch) {
    int i;
    int gasit = 0;
    for(i=0; i<strlen(cuvant); i++)
        if(cuvant[i] == ch){
            af_litera[i] = 1;
            gasit = 1;
        }
    return gasit;
}

void deseneaza_om(int parte_corp){
    switch(parte_corp)
    {
        case 0:
            cout<<" ____"<<endl;
            cout<<"|    |"<<endl;
            cout<<"|     "<<endl;
            cout<<"|      "<<endl;
            cout<<"|       "<<endl;
            cout<<"========"<<endl;
         break;
         case 1:
            cout<<" ____"<<endl;
            cout<<"|    |"<<endl;
            cout<<"|    O"<<endl;
            cout<<"|      "<<endl;
            cout<<"|       "<<endl;
            cout<<"========"<<endl;
         break;
         case 2:
            cout<<" ____"<<endl;
            cout<<"|    |"<<endl;
            cout<<"|    O"<<endl;
            cout<<"|   < >"<<endl;
            cout<<"|       "<<endl;
            cout<<"========"<<endl;
         break;
         case 3:
            cout<<" ____"<<endl;
            cout<<"|    |"<<endl;
            cout<<"|    O"<<endl;
            cout<<"|   < >"<<endl;
            cout<<"|   / \\"<<endl;
            cout<<"========"<<endl;
         break;
         case 4:
            cout<<" ____"<<endl;
            cout<<"|    |"<<endl;
            cout<<"|    O"<<endl;
            cout<<"|   <$>"<<endl;
            cout<<"|   / \\"<<endl;
            cout<<"========"<<endl;
         break;
    }
}

void ascunde_literele(){
    int i;
    for(i=0; i< strlen(cuvant); i++)
        af_litera[i] = 0;
}

void spanzuratoarea() {
    unsigned int i, litera_ochita = 0;
    char litera;
    int game_over = 0, parte_corp = 0, suma = 0, joc_nou = 1;
    raspuns = 0;

    cout<<"Nume jucator: ";
    fflush(stdin);
    cin.getline(j3.nume,40);
    j3.vieti = 3;
    srand(time(NULL)); // initializare random


   // cout<<"Cuvant gasit: "<<cuvant<<endl;

    while(!game_over){
        if(joc_nou == 1){
            ifstream f("cuvinte.txt");
            int numar_cuvant = rand() % 40451; // atatea cuvinte sunt in fisier
            for(i = 0;i < numar_cuvant; i++)
                f>>cuvant;
            f.close();

            for(i=0; i<strlen(cuvant); i++) {
                if(cuvant[i] == cuvant[0]) af_litera[i] = 1;    //verific fiecare litera cu prima litera
                if(cuvant[i] == cuvant[strlen(cuvant)-1]) af_litera[i] = 1;//verific fiecare litera cu ultima litera
            }
            joc_nou = 0;
        }
        suma = 0;
        afisare_cuvant();
        deseneaza_om(parte_corp);
        cout<<"Introdu litera: ";
        cin>>litera;

        litera_ochita = procesare_litera(tolower(litera));
        if(!litera_ochita) // ca pe Alexandra Stan
            parte_corp++;

        for(i = 0; i< strlen(cuvant); i++)
            suma += af_litera[i];
        if(suma == strlen(cuvant)){ // a nimerit toate literele
            cout<<"Bravo, "<<j3.nume<<"!"<<endl;
            j3.vieti++;
            game_over = 1;
        }
        if(parte_corp == 5) {

            cout<<endl<<endl<<endl<<"Ce-ai facut Einstein? l-ai omorat pe Superman?!"<<endl;
            cout<<"Amu' macar sa stii de ce ai pierdut - cuvantul era: "<<cuvant<<endl<<endl<<endl;
            j3.vieti--;
            game_over = 1;
        }
        if(game_over == 1)
        {
            cout<<endl<<"====== Rezultate ======"<<endl;
            if(j3.vieti != 1)
                cout<<j3.nume<< ", mai ai " <<j3.vieti<<" incercari."<<endl<<endl;
            else
                cout<<j3.nume<< ", mai ai " <<j3.vieti<<" incercare."<<endl<<endl;

            if(j3.vieti != 0){
                cout<<"Joc nou?"<<endl;
                cout<<"1.Da"<<endl;
                cout<<"2.Nu"<<endl;
                cin>>raspuns;
                if(raspuns == 1){
                    game_over = 0;
                    parte_corp = 0;
                    joc_nou = 1;
                    ascunde_literele();
                } else {
                    parte_corp = 0;
                    ascunde_literele();
                }
            } else {
                cout<<"See you on the other side :)"<<endl;
            }
        }
    }
}

void curata_tabla() {
    //un soi de pamatuf care pune praful la loc ... adica umple fix cu 0
    int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			tabla[i][j] = 0;
}

void afisare_tabla(){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(tabla[i][j] == 0)
				cout<<"* ";
			if(tabla[i][j] == 1)
				cout<<"x ";
			if(tabla[i][j] == 2)
				cout<<"0 ";
		}
		cout<<endl;
	}
}

int verificare_tabla(){
    int i;

    for(i=0; i<3; i++)  /* verificare linii */
        if(tabla[i][0] == tabla[i][1] && tabla[i][0] == tabla[i][2]) return tabla[i][0];

    for(i=0; i<3; i++)  /* verificare coloane */
        if(tabla[0][i] == tabla[1][i] && tabla[0][i] == tabla[2][i]) return tabla[0][i];

    /* diagonale */
    if(tabla[0][0] == tabla[1][1] && tabla[1][1] == tabla[2][2])  return tabla[0][0];
    if(tabla[0][2] == tabla[1][1] && tabla[1][1] == tabla[2][0])  return tabla[0][2];

    return 0;
}

int xsio(){
    int game_over = 0;
    int iteratii = 0;
    int linie, coloana;
    int pozitie_corecta = 0;

    cout<<endl;
    cout<<"Nume jucator 1: "<<endl;
    fflush(stdin);                  //trecem peste, doar stim ce face
    cin.getline (j1.nume,40);       //amu' citim si noi cu tot cu spatiu

    cout<<"Nume jucator 2: "<<endl;
    fflush(stdin);                  //acelasi principiu ca mai sus, deci idem
    cin.getline (j2.nume,40);
    cout<<endl;

    while(!game_over){

        cout<<endl;
        afisare_tabla();
        cout<<endl;
        switch(verificare_tabla())
        {
            case 0:
                if(iteratii > 8)
                {
                    cout<<endl<<endl<<"REMIZA"<<endl<<endl;
                    game_over = 1;
                }
                break;
            case 1:
                cout<<endl<<endl<<"Bravo, bre, "<<j1.nume<<" !"<<endl<<endl;
                game_over = 1;
                j1.victorii++;
                break;
            case 2:
                cout<<endl<<endl<<"Bravo, bre, "<<j2.nume<<" !"<<endl<<endl;
                game_over = 1;
                j2.victorii++;
                break;
        }
        if(!game_over)
        {
            if(iteratii % 2 == 0)
            {
                pozitie_corecta = 0;
                do
                {
                    cout<<"Joaca "<<j1.nume<<endl;
                    cout<<"Alege linia: "; cin>>linie;
                    cout<<"Alege coloana: "; cin>>coloana;

                    if(tabla[linie-1][coloana-1] == 0 && linie <=3 && coloana <= 3)
                    {
                        pozitie_corecta = 1;
                        tabla[linie-1][coloana-1] = 1;
                    }
                    else
                    {
                       if(!(linie <=3 && coloana <= 3))
                            cout<<endl<<"Haidi bre!!"<<endl<<"Unde ai vazut tu X si 0 cu mai mult de 3 linii si 3 coloane?"<<endl<<endl;
                        else
                            cout<<endl<<"Haidi bre!!"<<endl<<"Tot acolo vrei sa pui si tu!?"<<endl<<endl;
                    }
                }while(!pozitie_corecta);

            } else {
                pozitie_corecta = 0;
                do
                {
                    cout<<"Joaca "<<j2.nume<<endl;
                    cout<<"Alege linia: "; cin>>linie;
                    cout<<"Alege coloana: "; cin>>coloana;
                    if(tabla[linie-1][coloana-1] == 0 && linie <=3 && coloana <= 3)
                    {
                        pozitie_corecta = 1;
                        tabla[linie-1][coloana-1] = 2;
                    }
                    else
                    {
                        if(!(linie <=3 && coloana <= 3))
                            cout<<endl<<"Haidi bre!!"<<endl<<"Unde ai vazut tu X si 0 cu mai mult de 3 linii si 3 coloane?"<<endl<<endl;
                        else
                            cout<<endl<<"Haidi bre!!"<<endl<<"Tot acolo vrei sa pui si tu!?"<<endl<<endl;
                    }
                }while(!pozitie_corecta);

            }
        }
        iteratii++;
        if(game_over)
        {
            cout<<"===== REZULTATE ====="<<endl;
            if(j1.victorii >= 2 or j1.victorii == 0)
            {
            cout<<j1.nume<<" are "<<j1.victorii<<" victorii. "<<endl;}
            else
            if(j1.victorii == 1){
            cout<<j1.nume<<" are "<<j1.victorii<<" victorie. "<<endl;}
            if(j2.victorii >= 2 or j2.victorii == 0)
            {
            cout<<j2.nume<<" are "<<j2.victorii<<" victorii."<<endl<<endl<<endl;}
            else
            if(j2.victorii == 1){
            cout<<j2.nume<<" are "<<j2.victorii<<" victorie. "<<endl<<endl<<endl;}


            cout<<"E verzi ca $$, deci mai facem unul mic? "<<endl;
            cout <<"1. Da"<<endl<<"2. Nu"<<endl;
            cin>>raspuns;

            switch(raspuns)
            {
                case 1:
                    iteratii = 0;
                    game_over = 0;
                    curata_tabla();
                break;
                case 2:
                    iteratii = 0;
                    game_over = 1;

                    j1.victorii = 0;
                    j2.victorii = 0;
                    curata_tabla();
                break;
            }

        }
    }
}

int main(){
	char cuvant[50];
	int optiune = 0;

	cout<<"+-------------------------------+"<<endl;
	cout<<"| Proiect Programare (2015)     |"<<endl;
	cout<<"|                               |"<<endl;
	cout<<"| Student: Hristea Ioana-Adina  |"<<endl;
	cout<<"| Grupa: 102F                   |"<<endl;
	cout<<"+-------------------------------+"<<endl;

	while(1 && optiune != 3)
	{
	    cout<<endl;
		cout<<"Alege joc:"<<endl<<"1. Spanzuratoarea"<<endl<<"2. X si 0"<<endl<<"3. Iesire"<<endl;
		cin>>optiune;
		switch(optiune)
		{
			case 1:
			    spanzuratoarea();
				break;
			case 2:
			    xsio();
				break;
			case 3:
				break;
		}
	}
}

