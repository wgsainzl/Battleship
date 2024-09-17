#include <iostream>
#include "rlutil.h"
#include <stdlib.h>
using namespace rlutil;
using namespace std;


//Pantalla de inicio
void pantallainicio(){
    cls();
    setBackgroundColor (BLACK);
    cout<<" _           _   _   _           _     _"<<endl;
    setColor (BLUE); cout<<"| |         | | | | | |         | |   (_)"<<endl;
    setColor (GREEN); cout<<"| |__   __ _| |_| |_| | ___  ___| |__  _ _ __"<<endl;
    setColor (RED); cout<<"| '_ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\" <<endl;
    setColor (MAGENTA); cout<<"| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |"<<endl;
    setColor (BROWN); cout<<"|_.__/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/"<<endl;
    setColor (CYAN); cout<<"                                        | |   "<<endl;
    setColor (GREEN); cout<<"                                        |_|   "<<endl;
    setColor (WHITE);
    cout<<"Presione cualquier tecla para empezar"<<endl;
    getkey();
    cout<<endl;
    cls();
}

class Jugador{
private:
    string nombre;
    int barcos_vivos;
public:
    Jugador(string nombre, int barcos_vivos){
        this->nombre=nombre;
        this->barcos_vivos=barcos_vivos;
    };
    void setnombre(string nuevo_nombre){
        nombre=nuevo_nombre;
    };
    void setbarcos_vivos(int nuevo_barcos_vivos){
        barcos_vivos=nuevo_barcos_vivos;
    };
    string getnombre(){
        return nombre;
    };
    int getbarcos_vivos(){
        return barcos_vivos;
    };
};


//Tablero
class Tablero{
protected:
    //Tablero 10x10
    char mar[10][10];
public:
    //Constructor
    Tablero(char nuevoMar[10][10]){
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                mar[i][j] = nuevoMar[i][j];
            }
        }
    };
    //Imprimir tablero
    void mostrar_original(Jugador &J1){
        cls();
        cout<<"Tablero de "<<J1.getnombre()<<endl;
        char letra='A';
        cout << "  1 2 3 4 5 6 7 8 9 10" << endl;
        for (int i = 0; i<10; i++){
            cout << letra << " ";
            for(int j = 0; j<10;j++){
                if (mar[i][j] == '-' || mar[i][j] == '|')setColor(BLUE);
                if (mar[i][j] == '/')setColor(GREEN);
                if(mar[i][j] == '$')setColor(YELLOW);
                cout<<mar[i][j]<<" ";
                setColor(WHITE);
            }
            cout<<endl;
            letra++;
        }
    };
    //Modificar matriz para posicionar en un principio
    void modificar_original(char cambio, int posicion[2]){
        mar[posicion[1]][posicion[0]]=cambio;
    };
    char getPos(int x, int y){
        return mar[y][x];
    }
};

class TableroOculto: public Tablero{
private:
    char mar_oculto[10][10];
public:
    TableroOculto(char nuevoMar[10][10]) : Tablero(nuevoMar) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                mar_oculto[i][j] = '+';
            }
        }
    };
    //Mostrar tablero al atacante
    void mostrar_oculto(){
        cls();
        char letra='A';
        cout << "  1 2 3 4 5 6 7 8 9 10" << endl;
        for (int i = 0; i<10; i++){
            cout << letra << " ";
            for(int j = 0; j<10;j++){
                if (mar[i][j] == '*')setColor(RED);
                cout<<mar_oculto[i][j]<<" ";
                setColor(WHITE);
            }
            cout<<endl;
            letra++;
        }
    };
    //Modificar tablero que ve el atacante
    void modificar_oculto(char cambio, int posicion[2]){
        mar_oculto[posicion[1]][posicion[0]]=cambio;
    };
};


class Juego {
private:
    int barcos_jug1, barcos_jug2;
public:
    Juego(int barcos_jug1, int barcos_jug2){
        this ->barcos_jug1=barcos_jug1;Arely
        this ->barcos_jug2=barcos_jug2;
    };
    void setbarcos_jug1(int nuevo_barcos_jug1){
        barcos_jug1=nuevo_barcos_jug1;
    };
    void setbarcos_jug2(int nuevo_barcos_jug2){
        barcos_jug2=nuevo_barcos_jug2;
    };
    int getbarcos_jug1(){
        return barcos_jug1;
    };
    int getbarcos_jug2(){
        return barcos_jug2;
    };
    void atacar(Jugador &jugador, Tablero &tablero, TableroOculto &tablero_oculto, Jugador &jugador_rival){
        while(true){
            cls();
            if(jugador_rival.getbarcos_vivos()==0){
                break;
            }
            else{
                cout<<jugador.getnombre()<<" atacando"<<endl;
                cout<<jugador_rival.getnombre()<<" tiene "<<jugador_rival.getbarcos_vivos()<<" barcos vivos"<<endl;
                getkey();
                tablero_oculto.mostrar_oculto();
                int x, y;
                cout<<"Inserta coordenada x. ";
                cin>>x;
                x--;
                cout<<"Inserta coordenada y. ";
                cin>>y;
                y--;
                int pos[2]={x,y};
                if(tablero.getPos(x, y) != '~'){
                    cout<<"Acertaste!"<<endl;
                    getkey();
                    if(tablero.getPos(x, y) == '-' || tablero.getPos(x, y) == '|'){
                        tablero.modificar_original('X', pos);
                        tablero_oculto.modificar_oculto('X', pos);
                        jugador_rival.setbarcos_vivos(jugador_rival.getbarcos_vivos()-1);
                    }
                    if(tablero_oculto.getPos(x, y) == '/'){
                        if (tablero.getPos(x-1, y) != '/' && tablero.getPos(x+1, y) != '/' && tablero.getPos(x, y-1) != '/' && tablero.getPos(x, y+1) != '/'){
                            jugador_rival.setbarcos_vivos(jugador_rival.getbarcos_vivos()-1);
                        }
                        tablero.modificar_original('X', pos);
                        tablero_oculto.modificar_oculto('X', pos);
                    }
                    if(tablero.getPos(x, y) == '$'){
                        if (tablero.getPos(x-2, y) != '/' && tablero.getPos(x-1, y) != '/' && tablero.getPos(x+1, y) && tablero.getPos(x+2, y) != '/' != '/' && tablero.getPos(x, y-2) != '/' && tablero.getPos(x, y-1) != '/' && tablero.getPos(x, y+1) != '/' && tablero.getPos(x, y+2) != '/'){
                            jugador_rival.setbarcos_vivos(jugador_rival.getbarcos_vivos()-1);
                        }
                        tablero.modificar_original('X', pos);
                        tablero_oculto.modificar_oculto('X', pos);
                    }
                }
                else {
                    tablero_oculto.modificar_oculto('0', pos);
                    break;
                }
            }
        }
    }
};

//Falta definir orientación
class Naves{
protected:
    //Tres barcos de 1, dos de 2 y tres de 3, con sus respectivas coordenadas (x,y) de cada punto del barco
    int barcos1[3][2];
    int barcos2[2][2][2];
    int barcos3[3][2];
public:
    Naves(int nuevo_barcos1[3][2], int nuevo_barcos2[2][2][2], int nuevo_barcos3[3][2]){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                barcos1[i][j] = nuevo_barcos1[i][j];
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    barcos2[i][j][k] = nuevo_barcos2[i][j][k];
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                barcos3[i][j] = nuevo_barcos3[i][j];
            }
        }
    };
    void setBarcos1_1(int nuevo_barcos1_1[2]){
        for (int i = 0; i < 2; i++) {
            barcos1[0][i] = nuevo_barcos1_1[i];
        }
    };
    void setBarcos1_2(int nuevo_barcos1_2[2]){
        for (int i = 0; i < 2; i++) {
            barcos1[1][i] = nuevo_barcos1_2[i];
        }
    };
    void setBarcos1_3(int nuevo_barcos1_3[2]){
        for (int i = 0; i < 2; i++) {
            barcos1[2][i] = nuevo_barcos1_3[i];
        }
    };
    void setBarcos2_1(int nuevo_barcos2_1[2][2]) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                barcos2[0][i][j] = nuevo_barcos2_1[i][j];
            }
        }
    }
    void setBarcos2_2(int nuevo_barcos2_2[2][2]) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                barcos2[1][i][j] = nuevo_barcos2_2[i][j];
            }
        }
    };
    void setBarcos3_2(int nuevo_barcos3[3][2]) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                barcos3[i][j] = nuevo_barcos3[i][j];
            }
        }
    };
    int* getBarcos1_1() {
        return barcos1[0];
    };

    int* getBarcos1_2() {
        return barcos1[1];
    };

    int* getBarcos1_3() {
        return barcos1[2];
    };

    int (*getBarcos2_1())[2] {
        return barcos2[0];
    };
    int (*getBarcos2_2())[2] {
        return barcos2[1];
    };

    int (*getBarcos3())[2] {
        return barcos3;
    };
};

class Referi{
private:
    boolean vivo_1, vivo_2;
public:
    Referi(boolean vivo_1, boolean vivo_2){
        this->vivo_1=vivo_1;
        this->vivo_2=vivo_2;
    }
    void ganar(Juego &J, Jugador &J1, Jugador &J2, Tablero &Tablero1, TableroOculto &TableroOculto1, Tablero &Tablero2, TableroOculto &TableroOculto2){
        while(J1.getbarcos_vivos()>0 && J2.getbarcos_vivos()){
            J.atacar(J1, Tablero2, TableroOculto2, J2);
            J.atacar(J2, Tablero1, TableroOculto1, J1);
        }
        if(J1.getbarcos_vivos()==0){
            cls();
            cout<< "Gana "<<J2.getnombre();
        }
        if(J2.getbarcos_vivos()==0){
            cls();
            cout<< "Gana "<<J1.getnombre();
        }
    };
};


//Colocar barco de 1 en tablero
void colocar_1(char forma, char lado, int &xpos, int &ypos, Tablero &tablero, Jugador &jugador){
    int nuevo_xpos=xpos, nuevo_ypos=ypos;
    while(lado!='x'){
        if(xpos==0 && ypos==0){
        int pos0[2]={0,0};
        tablero.modificar_original(forma, pos0);
        tablero.mostrar_original(jugador);
        }
        cout << "W(arriba), A(izquierda), S(abajo), D(derecha), X(salir)" << endl;
        lado=getkey();
        switch(lado){
            case 'w':
                if (nuevo_ypos!=0)nuevo_ypos--;
            break;
            case 'a':
                if (nuevo_xpos!=0)nuevo_xpos--;
            break;
            case 's':
                if (nuevo_ypos!=9)nuevo_ypos++;
            break;
            case 'd':
                if (nuevo_xpos!=9)nuevo_xpos++;
            break;
        }
    
        int pos[2]={xpos, ypos};
        tablero.modificar_original('~', pos);
        int nuevo_pos[2]={nuevo_xpos, nuevo_ypos};
        tablero.modificar_original(forma, nuevo_pos);
        xpos=nuevo_xpos;
        ypos=nuevo_ypos;
        tablero.mostrar_original(jugador);
    }
}

//Colocar barco de 2 en tablero
void colocar_2(char forma, char lado, int &xpos_1, int &xpos_2, int &ypos_1, int &ypos_2, Tablero &tablero, Jugador &jugador){
    int nuevo_xpos_1=xpos_1, nuevo_xpos_2=xpos_2, nuevo_ypos_1=ypos_1, nuevo_ypos_2=ypos_2;
    char b2='/';
    while(lado!='x'){
        switch (forma){
            case '-':
                if(xpos_1==0 && ypos_1==0){
                    int pos0[2]={0,0};
                    int pos1[2]={1,0};
                    tablero.modificar_original(b2, pos0);
                    tablero.modificar_original(b2, pos1);
                    tablero.mostrar_original(jugador);
                }
                cout << "W(arriba), A(izquierda), S(abajo), D(derecha), X(salir)" << endl;
                lado=getkey();
                cout<<nuevo_xpos_1<<nuevo_ypos_1<<endl;
                cout<<nuevo_xpos_2<<nuevo_ypos_2<<endl;
                switch(lado){
                    case 'w':
                        if (nuevo_ypos_1!=0 && nuevo_ypos_2!=0){
                            nuevo_ypos_1--;
                            nuevo_ypos_2--;
                        }
                    break;
                    case 'a':
                        if (nuevo_xpos_1!=0){
                            nuevo_xpos_1--;
                            nuevo_xpos_2--;
                        }
                    break;
                    case 's':
                        if (nuevo_ypos_1!=9 && nuevo_ypos_2!=9){
                            nuevo_ypos_1++;
                            nuevo_ypos_2++;
                        }
                    break;
                    case 'd':
                        if (nuevo_xpos_2!=9){
                            nuevo_xpos_1++;
                            nuevo_xpos_2++;
                        }
                    break;
                }
            break;
            case '|':
                if(xpos_1==0 && ypos_1==0){
                    int pos0[2]={0,0};
                    int pos1[2]={0,1};
                    tablero.modificar_original(b2, pos0);
                    tablero.modificar_original(b2, pos1);
                    tablero.mostrar_original(jugador);
                }
                cout << "W(arriba), A(izquierda), S(abajo), D(derecha), X(salir)" << endl;
                lado=getkey();
                switch(lado){
                    case 'w':
                        if (nuevo_ypos_1!=0){
                            nuevo_ypos_1--;
                            nuevo_ypos_2--;
                        }
                    break;
                    case 'a':
                        if (nuevo_xpos_1!=0){
                            nuevo_xpos_1--;
                            nuevo_xpos_2--;
                        }
                    break;
                    case 's':
                        if (nuevo_ypos_2!=9){
                            nuevo_ypos_1++;
                            nuevo_ypos_2++;
                        }
                    break;
                    case 'd':
                        if (nuevo_xpos_2!=9){
                            nuevo_xpos_1++;
                            nuevo_xpos_2++;
                        }
                    break;
                }
            break;
        }
        
    
        int pos_1[2]={xpos_1, ypos_1};
        int pos_2[2]={xpos_2, ypos_2};
        tablero.modificar_original('~', pos_1);
        tablero.modificar_original('~', pos_2);
        int nuevo_pos_1[2]={nuevo_xpos_1, nuevo_ypos_1};
        int nuevo_pos_2[2]={nuevo_xpos_2, nuevo_ypos_2};
        tablero.modificar_original(b2, nuevo_pos_1);
        tablero.modificar_original(b2, nuevo_pos_2);
        xpos_1=nuevo_xpos_1;
        xpos_2=nuevo_xpos_2;
        ypos_1=nuevo_ypos_1;
        ypos_2=nuevo_ypos_2;
        tablero.mostrar_original(jugador);
    }
}

//Colocar barco de 3 en tablero
void colocar_3(char forma, char lado, int &xpos_1, int &xpos_2, int &xpos_3, int &ypos_1, int &ypos_2, int &ypos_3, Tablero &tablero, Jugador &jugador){
    cout<<ypos_3<<endl;
    int nuevo_xpos_1=xpos_1, nuevo_xpos_2=xpos_2, nuevo_xpos_3=xpos_3, nuevo_ypos_1=ypos_1, nuevo_ypos_2=ypos_2, nuevo_ypos_3=ypos_3;
    char b3='$';
    while(lado!='x'){
        switch (forma){
            case '-':
                if(xpos_1==0 && ypos_1==0){
                    int pos0[2]={0,0};
                    int pos1[2]={1,0};
                    int pos2[2]={2,0};
                    tablero.modificar_original(b3, pos0);
                    tablero.modificar_original(b3, pos1);
                    tablero.modificar_original(b3, pos2);
                    tablero.mostrar_original(jugador);
                }
                cout << "W(arriba), A(izquierda), S(abajo), D(derecha), X(salir)" << endl;
                lado=getkey();
                switch(lado){
                    case 'w':
                        if (nuevo_ypos_1!=0 && nuevo_ypos_2!=0){
                            nuevo_ypos_1--;
                            nuevo_ypos_2--;
                            nuevo_ypos_3--;
                        }
                    break;
                    case 'a':
                        if (nuevo_xpos_1!=0){
                            nuevo_xpos_1--;
                            nuevo_xpos_2--;
                            nuevo_xpos_3--;
                        }
                    break;
                    case 's':
                        if (nuevo_ypos_1!=9 && nuevo_ypos_2!=9){
                            nuevo_ypos_1++;
                            nuevo_ypos_2++;
                            nuevo_ypos_3++;
                        }
                    break;
                    case 'd':
                        if (nuevo_xpos_2!=9){
                            nuevo_xpos_1++;
                            nuevo_xpos_2++;
                            nuevo_xpos_3++;
                        }
                    break;
                }
            break;
            case '|':
                if(xpos_1==0 && ypos_1==0){
                    int pos0[2]={0,0};
                    int pos1[2]={0,1};
                    int pos2[2]={0,2};
                    tablero.modificar_original(b3, pos0);
                    tablero.modificar_original(b3, pos1);
                    tablero.modificar_original(b3, pos2);
                    tablero.mostrar_original(jugador);
                }
                cout << "W(arriba), A(izquierda), S(abajo), D(derecha), X(salir)" << endl;
                lado=getkey();
                switch(lado){
                    case 'w':
                        if (nuevo_ypos_1!=0){
                            cout<<nuevo_ypos_1<<" "<<nuevo_ypos_2<<" "<<nuevo_ypos_3<<endl;
                            nuevo_ypos_1--;
                            nuevo_ypos_2--;
                            nuevo_ypos_3--;
                        }
                    break;
                    case 'a':
                        if (nuevo_xpos_1!=0){
                            nuevo_xpos_1--;
                            nuevo_xpos_2--;
                            nuevo_xpos_3--;
                        }
                    break;
                    case 's':
                        if (nuevo_ypos_3!=9){
                            nuevo_ypos_1++;
                            nuevo_ypos_2++;
                            nuevo_ypos_3++;
                        }
                    break;
                    case 'd':
                        if (nuevo_xpos_2!=9){
                            nuevo_xpos_1++;
                            nuevo_xpos_2++;
                            nuevo_xpos_3++;
                        }
                    break;
                }
            break;
        }
        
    
        int pos_1[2]={xpos_1, ypos_1};
        int pos_2[2]={xpos_2, ypos_2};
        int pos_3[2]={xpos_3, ypos_3};
        tablero.modificar_original('~', pos_1);
        tablero.modificar_original('~', pos_2);
        tablero.modificar_original('~', pos_3);
        int nuevo_pos_1[2]={nuevo_xpos_1, nuevo_ypos_1};
        int nuevo_pos_2[2]={nuevo_xpos_2, nuevo_ypos_2};
        int nuevo_pos_3[2]={nuevo_xpos_3, nuevo_ypos_3};
        tablero.modificar_original(b3, nuevo_pos_1);
        tablero.modificar_original(b3, nuevo_pos_2);
        tablero.modificar_original(b3, nuevo_pos_3);
        xpos_1=nuevo_xpos_1;
        xpos_2=nuevo_xpos_2;
        xpos_3=nuevo_xpos_3;
        ypos_1=nuevo_ypos_1;
        ypos_2=nuevo_ypos_2;
        ypos_3=nuevo_ypos_3;
        tablero.mostrar_original(jugador);
    }
}

void principio_1( Jugador &J1, Tablero &T1_original, Tablero &T2_oculto){
    cls();

    for(int i = 0; i < 3; i++){
        T1_original.mostrar_original(J1);
        char x='q';
        char forma;
        int xpos=0;
        int ypos=0;
        cout<<"orientacion (h/v)"<<endl;
        char orientacion = getkey();
        if(orientacion == 'h'){
            forma='-';
            cout<<"Horizontal"<<endl;
        }
        if(orientacion == 'v'){
            forma='|';
            cout<<"Vertical"<<endl;
        }
        colocar_1(forma, x, xpos, ypos, T1_original, J1);
    }
    for(int i = 0; i < 2; i++){
        T1_original.mostrar_original(J1);
        char x='q';
        char forma;
        int xpos_1=0;
        int ypos_1=0;
        int xpos_2;
        int ypos_2;
        cout<<"orientacion (h/v)"<<endl;
        char orientacion = getkey();
        if(orientacion == 'h'){
            forma='-';
            cout<<"Horizontal"<<endl;
            xpos_2=1;
            ypos_2=0;
        }
        if(orientacion == 'v'){
            forma='|';
            cout<<"Vertical"<<endl;
            xpos_2=0;
            ypos_2=1;
        }
        colocar_2(forma, x, xpos_1, xpos_2, ypos_1, ypos_2, T1_original, J1);
    }
    T1_original.mostrar_original(J1);
    char x='q';
    char forma;
    int xpos_1=0;
    int ypos_1=0;
    int xpos_2, xpos_3;
    int ypos_2, ypos_3;
    cout<<"orientacion (h/v)"<<endl;
    char orientacion = getkey();
    if(orientacion == 'h'){
        forma='-';
        cout<<"Horizontal"<<endl;
        xpos_2=1;
        ypos_2=0;
        xpos_3=2;
        ypos_3=0;
    }
    if(orientacion == 'v'){
        forma='|';
        cout<<"Vertical"<<endl;
        xpos_2=0;
        ypos_2=1;
        xpos_3=0;
        ypos_3=2;
    }
    colocar_3(forma, x, xpos_1, xpos_2, xpos_3, ypos_1, ypos_2, ypos_3, T1_original, J1);
}

void principio_2(Jugador &J2, Tablero &T2_original, Tablero &T1_oculto){
    cls();

    for(int i = 0; i < 3; i++){
        T2_original.mostrar_original(J2);
        char x='q';
        char forma;
        int xpos=0;
        int ypos=0;
        cout<<"orientacion (h/v)"<<endl;
        char orientacion = getkey();
        if(orientacion == 'h'){
            forma='-';
            cout<<"Horizontal"<<endl;
        }
        if(orientacion == 'v'){
            forma='|';
            cout<<"Vertical"<<endl;
        }
        colocar_1(forma, x, xpos, ypos, T2_original, J2);
    }
    for(int i = 0; i < 2; i++){
        T2_original.mostrar_original(J2);
        char x='q';
        char forma;
        int xpos_1=0;
        int ypos_1=0;
        int xpos_2;
        int ypos_2;
        cout<<"orientacion (h/v)"<<endl;
        char orientacion = getkey();
        if(orientacion == 'h'){
            forma='-';
            cout<<"Horizontal"<<endl;
            xpos_2=1;
            ypos_2=0;
        }
        if(orientacion == 'v'){
            forma='|';
            cout<<"Vertical"<<endl;
            xpos_2=0;
            ypos_2=1;
        }
        colocar_2(forma, x, xpos_1, xpos_2, ypos_1, ypos_2, T2_original, J2);
    }
    T2_original.mostrar_original(J2);
    char x='q';
    char forma;
    int xpos_1=0;
    int ypos_1=0;
    int xpos_2, xpos_3;
    int ypos_2, ypos_3;
    cout<<"orientacion (h/v)"<<endl;
    char orientacion = getkey();
    if(orientacion == 'h'){
        forma='-';
        cout<<"Horizontal"<<endl;
        xpos_2=1;
        ypos_2=0;
        xpos_3=2;
        ypos_3=0;
    }
    if(orientacion == 'v'){
        forma='|';
        cout<<"Vertical"<<endl;
        xpos_2=0;
        ypos_2=1;
        xpos_3=0;
        ypos_3=2;
    }
    colocar_3(forma, x, xpos_1, xpos_2, xpos_3, ypos_1, ypos_2, ypos_3, T2_original, J2);
}


int main(){

    pantallainicio();
    char tab1[10][10];   
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            tab1[i][j]='~';
        }
    }
    Juego J = Juego(5,5);
    Referi R=Referi(1,1);
    string nombre1;
    cls();
    cout<<"Nombre Jugador 1: ";
    cin>>nombre1;
    Jugador J1=Jugador(nombre1, 5);
    Tablero T1_original=Tablero(tab1);

    TableroOculto T1_oculto = TableroOculto(tab1);
    principio_1(J1, T1_original, T1_oculto);

    string nombre2;
    cls();
    cout<<"Nombre Jugador 2: ";
    cin>>nombre2;
    Jugador J2=Jugador(nombre2, 5);
    Tablero T2_original=Tablero(tab1);

    TableroOculto T2_oculto = TableroOculto(tab1);
    principio_2(J2, T2_original, T2_oculto);
    cls();
    getkey();


    R.ganar(J, J1, J2, T1_original, T1_oculto, T2_original, T2_oculto);
}