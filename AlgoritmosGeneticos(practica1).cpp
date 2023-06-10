///Vargas Soriano Flor Arlette
/// ALgoritmos Bioinspirados

// Algoritmo genetico para maximizar la funcion |(x-5)/(2+sen(x))|
// Seleccion de padres por ruleta
/// Cruza de los padres por el metodo recombinacion de un punto
// Mutacion por inversion de bits
// Remplazo del padre mas debil
// Condicion de paro es de 10 generaciones 

// definicion de las librerias
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <ctime>

using namespace std;

// definicion de las constantes
# define TAMANO_POB 5
# define LONG_CROM 4
# define proba_Mutacion .1
# define proba_Cruza .85
# define Pi 3.1416
# define Repeticiones 10

//definicion de la estructura poblacion
struct Indivi {
	unsigned int cromosoma[LONG_CROM];
	double cantidad;
	float fx;
	float probasele;
	float probaacumulada;

};


//declaracion de variables de tipo poblacion
struct Indivi  pob[TAMANO_POB];
struct Indivi  NewPob[TAMANO_POB];
struct Indivi  hijos[2];
struct Indivi  Padres[2];


/// declaracion de las funciones a usar 
void Numeros_Ale();
int Binario_a_Decimal (Indivi &xpob);
int Evalua_Funcion(Indivi *xpob);
float Funcion(Indivi &xpob);
float Numeros_Aleatorios_Flotantes();
void  Mostrar_Datos_Poblacion(Indivi &xpob);
void Cruce (Indivi *xpob, int posicion);
void Reproduccion(int Padre1, int Padre2,int numh );
void Mutacion(int numhijo);
void Mejor(Indivi *xpob,int Padre1,int Padre2, int hijo, int newposicion);

int main(){
	int repeticiones = 0;
	int rep =TAMANO_POB / 2;
	Numeros_Ale();
while (repeticiones != Repeticiones){
	cout <<"########################################## Generacion "<< repeticiones << "##############" << endl;
	Evalua_Funcion (pob);	
	cout << "Genotipo"<< " Fenotipo" << " F(x)" << " Psel"<< " Pacum"<< endl;
	for(int j=0;j<TAMANO_POB;j++){
		Mostrar_Datos_Poblacion(pob[j])	;	
	}
	
		
	if ((TAMANO_POB % 2)  == 0 ){
		for(int j=0;j<rep;j++){
			cout <<"/////////////////////////// La cruza "<< j << endl;
			Cruce(pob,j);
			cout << "Hijos /////////////////////////////////////////////////77"<< endl;
			for(int j=0;j<2;j++){
				Mostrar_Datos_Poblacion(hijos[j]);	
			}
		}
	}else{	
			for(int j=0;j<rep +1;j++){
				cout <<"/////////////////////////// La cruza es impar "<< j << endl;
				Cruce(pob,j);
				cout << "Hijos /////////////////////////////////////////////////77"<< endl;
				Evalua_Funcion(hijos);
				for(int z=0;z<2;z++){
					Mostrar_Datos_Poblacion(hijos[z]);	
				}
			}
		}
		
	for (int i=0;i<TAMANO_POB;i++){
		for (int j=0;i<LONG_CROM;i++){
			pob[i].cromosoma[j]=  NewPob[i].cromosoma[j];
		}
	}
	repeticiones++;	
}
	return 0;
}

void Numeros_Ale(){
int i,j;
srand( (unsigned)time( NULL ) );
	for(i=0;i<TAMANO_POB;i++){
		for(j=0;j<LONG_CROM;j++){
			pob[i].cromosoma[j]=  rand() % 2;
		}
	}
}
int Binario_a_Decimal (Indivi &xpob){
	int resultado =0,sum =-1;
	
	for ( int j=LONG_CROM;j>=0;j--){
		if (xpob.cromosoma[j] ==  1){
			resultado += pow(2.0,sum);		
		}	
		sum++;	
	}	
  	return resultado;	
}
// Funcion que hace un numero aleatorio entre 0 y 1
float Numeros_Aleatorios_Flotantes(){
	 float  ale =  rand() % 100;
	float  alea = ale/100;
	return alea;	
}

// funcion donde se evalua la funcion
int Evalua_Funcion(Indivi *xpob){
	
	float sumP =0;
	for(int i=0;i<TAMANO_POB;i++){
		xpob[i].cantidad =  Binario_a_Decimal(xpob[i]);
		xpob[i].fx = Funcion(xpob[i]);
		sumP += xpob[i].fx;
	}
	for(int j=0;j<TAMANO_POB;j++){
		xpob[j].probasele = xpob[j].fx / sumP;
		if(xpob[j].probasele  == 0){
			xpob[j].probaacumulada= 0;
		}
		xpob[j].probaacumulada=xpob[j-1].probaacumulada +
			xpob[j].probasele;	
			
	}			
}
/// Funcion que vamos a maximiar 
float Funcion(Indivi &xpob){	
	float rad = (xpob.cantidad * Pi) / 180;
	float valor = abs(xpob.cantidad - 5)/(2+ sin(xpob.cantidad));
	return valor;
}

//// muestra todos los  los individuos de una poblacion 
void  Mostrar_Datos_Poblacion(Indivi &xpob){
		for(int j=0;j<LONG_CROM;j++){
			cout << xpob.cromosoma[j];
		}
		cout << " = " << xpob.cantidad << "     ;   " << setprecision(3) << xpob.fx << "   ;   "  << setprecision(3) 
		<< xpob.probasele <<"   ;   " <<xpob.probaacumulada<<endl;
			
}

void Cruce (Indivi *xpob, int posicion ){
	int bandera =1;
	while (bandera == 1){
		float p1 = Numeros_Aleatorios_Flotantes();
		cout <<"probabilidad padre 1 = "<< p1 << endl;
		float p2 = Numeros_Aleatorios_Flotantes();
		cout <<"probabilidad padre 2 = "<< p2 << endl;
		float PCruce = Numeros_Aleatorios_Flotantes();
		cout <<"probabilidad de cruza = "<< PCruce << endl;
		int Padre1, Padre2;
		if (PCruce < proba_Cruza){
			for(int i=0;i<TAMANO_POB;i++){
				if( xpob[i].probaacumulada >  p1 ){				
					Padre1 = i;
				    break;	
				}
					
			}
			for(int i=0;i<TAMANO_POB;i++){
				if( xpob[i].probaacumulada >  p2 ){				
					Padre2 = i;
				    break;	
				}					 
			}
			bandera =0;
			Reproduccion (Padre1, Padre2, posicion);
			
		} else {
			cout <<"No se reproduce otra vez" << endl;
		  }
	}
			
}
void Reproduccion(int Padre1, int Padre2, int numh ){
	float fx1=0,fx2 =0;
	int cruce = 0 + rand() % LONG_CROM;
	cout << "Punto de cruce = "<< cruce << endl;
	cout << "Padre1 "<< endl;
	for(int i = 0; i < LONG_CROM ;i++){
		cout << pob[Padre1].cromosoma[i];
	
	}
	cout << " " <<endl;
	cout << "Padre2 "<< endl;
	for(int i = 0; i < LONG_CROM ;i++){
		cout << pob[Padre2].cromosoma[i];
	
	} cout << " " <<endl;
	
		for (int i = 0; i < cruce ;i++){
			hijos[0].cromosoma[i] = pob[Padre1].cromosoma[i];
			hijos[1].cromosoma[i] = pob[Padre2].cromosoma[i];
		

		}
		for (int j = cruce; j< LONG_CROM ;j++){
			hijos[0].cromosoma[j] = pob[Padre2].cromosoma[j];
			hijos[1].cromosoma[j] = pob[Padre1].cromosoma[j];
			
		}
		
	cout << " " <<endl;
	cout << "hijo "<<numh << " antes de mutar " <<endl;
	Evalua_Funcion(hijos);
	for(int i = 0; i < LONG_CROM ;i++){
		cout << hijos[0].cromosoma[i];
	
	} cout << " " <<endl;

	cout << "hijo "<<numh+1 << " antes de mutar "<< endl;
	for(int i = 0; i < LONG_CROM ;i++){
		cout << hijos[1].cromosoma[i];
	
	} cout << " " <<endl;	

		Mutacion (0);
		Mutacion (1);
		fx1 = pob[Padre1].fx;
		fx2 = pob[Padre2].fx;
		cout << "los fx originales" <<  setprecision(3) << fx1 << " el otro " <<  setprecision(3) << fx2 << endl;
		Mejor(pob, Padre1, Padre2, 0,numh*2);
		cout << " Segundo Mejor"<<endl;
		Mejor(pob, Padre1, Padre2,1, (numh*2)+1);
		
		pob[Padre1].fx =fx1;
		pob[Padre2].fx =fx2;		
		
}
/// Funcion de la mutacion
void Mutacion(int numhijo){	
	cout << "Mutacion " <<numhijo <<  endl;	
	float ProbabilidadMutacion[LONG_CROM];	
	for (int i =0 ; i< LONG_CROM; i++ ) {
		ProbabilidadMutacion [i] = Numeros_Aleatorios_Flotantes();
		cout << " Posicion "<< i << "=" << ProbabilidadMutacion [i] << endl;
	
		if( ProbabilidadMutacion [i] <= proba_Mutacion ){
			
			if	(hijos[numhijo].cromosoma[i] == 1 ) {
				hijos[numhijo].cromosoma[i] = 0;
			
			}else{
				hijos[numhijo].cromosoma[i] = 1;
			}
			
		}else{
		}	
	}
	cout << " El hijo "<< numhijo << endl;
	for(int i=0 ; i< LONG_CROM; i++){
		cout << hijos[numhijo].cromosoma[i];
	}
	cout << "" << endl;		
}

void Mejor(Indivi *xpob,int Padre1,int Padre2, int hijo, int newposicion){
	float mayor = 0;
	
	cout << "la posicion es " << newposicion << endl;
		if (xpob[Padre1].fx > xpob[Padre2].fx) {
			if(hijos[hijo].fx >=  xpob[Padre1].fx ){
				cout << " Mayor es el hijo" << endl;
				for (int j = 0; j< LONG_CROM ;j++){
					NewPob[newposicion].cromosoma[j] = hijos [hijo].cromosoma[j];
				}
				hijos[hijo].fx =-1;
				
			}else{
				cout << " Mayor es padre 1" << endl;
				for (int j = 0; j< LONG_CROM ;j++){
					NewPob[newposicion].cromosoma[j] = xpob[Padre1].cromosoma[j];
				}
				 xpob[Padre1].fx =-1;
			}
			
		}else {
			if(hijos[hijo].fx >=  xpob[Padre2].fx ){
				cout << "el mayor es el hijo"<< endl;
				for (int j = 0; j< LONG_CROM ;j++){
					NewPob[newposicion].cromosoma[j]= hijos [hijo].cromosoma[j];
				}
				hijos[hijo].fx =-1;
				
			}else{
				cout << " Mayor es padre 2" << endl;
				for (int j = 0; j< LONG_CROM ;j++){
					NewPob[newposicion].cromosoma[j] = xpob[Padre2].cromosoma[j];
				}
				xpob[Padre2].fx =-1;
				
				
			}
			
		}
		
	cout << "el hijo =" ;
	for (int j = 0; j< LONG_CROM ;j++){
		cout <<	hijos [hijo].cromosoma[j] ;
	} 
	cout <<"="<< hijos[hijo].fx;
	cout<<" " << endl;
	cout << "el Padre1 = " ;
	for (int j = 0; j< LONG_CROM ;j++){
		cout <<	xpob[Padre1].cromosoma[j] ;
	}
	cout << " =" << xpob[Padre1].fx;
	cout<<" " << endl;
	cout << "el Padre2" << endl;
	for (int j = 0; j< LONG_CROM ;j++){
		cout <<	xpob[Padre2].cromosoma[j] ;
	}
	cout << " =" << xpob[Padre2].fx;
	cout<<" " << endl;
	cout << "el Mejor" << endl;	
	for (int j = 0; j< LONG_CROM ;j++){
		cout <<	NewPob[newposicion].cromosoma[j] ;
	}
	cout<<" " << endl;
		
}
