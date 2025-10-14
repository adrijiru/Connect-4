#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4


#define ANSI_COLOR_J1    "\x1b[34m"     //BLAU
#define ANSI_COLOR_J2     "\x1b[31m"    //VERMELL
#define ANSI_COLOR_RESET   "\x1b[0m"

// JUGADOR 1: COLOR BLAU
// JUGADOR 2: COLOR VERMELL

void printTauler(char tauler[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            // COLOR DE LES FITXES
            if(tauler[i][j]=='1'){
                printf(ANSI_COLOR_J1 "O " ANSI_COLOR_RESET);
            }
            else if(tauler[i][j]=='2'){
                printf(ANSI_COLOR_J2 "O " ANSI_COLOR_RESET);
            }
            else{
            printf("%c ", tauler[i][j]); //imprimeix zeros a les caselles buides, es pot obviar
            }
        }
        printf("\n");
    }
    printf("\n");
}

int detect(char tauler[N][N], int columna, int info){
    // Detecta si la columna és buida (1a fila buida -> està disponible)
    if(tauler[0][columna]=='0'){return 1;} //si està buida deixa tirar
    else{
        if (info == 1)
            printf("Aquesta columna està ocupada, escull una altra.\n");
        return 0;
    }
    //es podria abreviar amb un return(tauler[0][col]==0), o fins i tot no cuidar-la
}

int gravity_sim(char tauler[N][N], int columna){//al revés
    for(int i=N-1; i>=0; i--){
        if(tauler[i][columna] == '0'){
            return i;
        }
    }
    return -1; // la columna està plena
}

void tirada(char tauler[N][N], int fitxa, int *fila, int *columna, int info){ //afegir paràmetre per l'animació?
    // PRINT TAULA
    printTauler(tauler);

    /*  > Jugador escull la columna on vol tirar
        > ACONSEGUIR CRIDA DES DE CONSOLA
        > detect mira si no està ocupada, en aquest cas retorna 1
        > gravity sim dona on s'ha de colocar la fitxa
        > s'actualitza tauler*/
    int aux;
    char c;
    printf("Jugador %i: Escull la columna on vols col·locar la teva fitxa (1,...,%i): ", fitxa, N);
    if (scanf("%d%c", &aux, &c) != 2 || c != '\n') {
        printf("Entrada no válida. Intenta de nuevo.\n");
        while (getchar() != '\n'); // Neteja el búfer, on guarda temporalment el que sobresurt del scanf, és a dir si poso 1 5 guarda 5 al bufer i passen coses rares
        tirada(tauler, fitxa, fila, columna, info);
        return;
    }
    if (aux>-1 && aux < N+1) *columna = --aux;
    else {
        printf("Escull una columna dins l'establert.\n");
        tirada(tauler, fitxa, fila, columna, info);
        return;
    }

    if(detect(tauler, *columna, info)){
        *fila = gravity_sim(tauler, *columna);
        tauler[*fila][*columna] = fitxa + '0';
    }
    else{
        tirada(tauler, fitxa, fila, columna, info);
    }
}

// Per la detecció del 4 en ratlla al torn del jugador X només mirem les fitxes de X
// ES POT ILUMINAR LES 4?? PER MOSTRAR QUI GUANYAAAAAAAAAAA CARAJOOO

// OPTIMITZAR: NOMÉS MIRAR L'ÚLTIMA FITXA COLOCADA, caldria que tirada retornes la posició a part!!!!!!!!!!

/* SCAN DE TOTA LA TAULA - FUNCIONA
int check_win(char tauler[N][N], char fitxa) {
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (tauler[i][j]==fitxa){
                // Horizontal (de dreta a esquerra, l'ordre del for)
                if (j+3<N && tauler[i][j+1]==fitxa && tauler[i][j+2]==fitxa && tauler[i][j+3]==fitxa)
                    return 1;

                // Vertical (de dalt a abaix, l'ordre del for)
                if (i+3<N && tauler[i+1][j]==fitxa && tauler[i+2][j]==fitxa && tauler[i+3][j]==fitxa)
                    return 1;

                // Diagonal 1 (de dalt esquerre a baix dreta)
                if (i+3<N && j+3<N && tauler[i+1][j+1]==fitxa && tauler[i+2][j+2]==fitxa && tauler[i+3][j+3]==fitxa)
                    return 1;

                // Diagonal 2 (de dalt dreta a baix esquerra)
                if (i-3>=0 && j+3<N && tauler[i-1][j+1]==fitxa && tauler[i-2][j+2]==fitxa && tauler[i-3][j+3] == fitxa)
                    return 1;
            }
        }
    }
    return 0;
}*/


int victoria(char tauler[N][N], char fitxa, int fila, int columna){ //només comprobant l'última fitxa llençada
    // Només comprobem les possibilitats de victòria que inclouen la fitxa que s'acaba d'introduir!
    // Llegim només tres caselles a cada banda de la fitxa en cada una de les direccions possibles
    int comptador=1, interrupt1=1, interrupt2=1;

    // Horitzontal (--)
    for(int i=1; i<4; i++){
        // Cal fer comprovacions per a que estigui dins el tauler la casella en qüestió
        // considerem interrupt1 la dreta i interrupt2 l'esquerra, detecten quan no hi ha una fitxa a la banda que s'està mirant
        if(columna+i<N){
            if (tauler[fila][columna+i]==fitxa && interrupt1) //si s'ha interromput no estudia més aquesta banda
                comptador += 1;
            else interrupt1 = 0;
        }
        if (columna-i>-1){
            if (tauler[fila][columna-i]==fitxa && interrupt2)
                comptador += 1;
            else interrupt2 = 0;
        }
        if (!interrupt1 && !interrupt2){
            break;
        }
        else if (comptador>3){ //VICTÒRIA
            return 1;
        }
    }
    comptador = 1; interrupt1=1; interrupt2=1;

    // VERTICAL (|)
    for(int i=1; i<4; i++){
        // considerem interrupt1 abaix i interrupt2 adalt, detecten quan no hi ha una fitxa a la banda que s'està mirant
        if(fila+i<N){
            if (tauler[fila+i][columna]==fitxa && interrupt1)
                comptador += 1;
            else interrupt1 = 0;
        }
        if (fila-i>-1){
            if (tauler[fila-i][columna]==fitxa && interrupt2)
                comptador += 1;
            else interrupt2 = 0;
        }
        if (!interrupt1 && !interrupt2){
            break;
        }
        else if (comptador>3){ //VICTÒRIA
            return 1;
        }
    }
    comptador = 1; interrupt1=1; interrupt2=1;

    // DIAGONAL (\)
    for(int i=1; i<4; i++){
    // considerem interrupt1 abaix dreta i interrupt2 adalt esquerra, detecten quan no hi ha una fitxa a la banda que s'està mirant
        if(fila+i<N && columna+i<N){
            if (tauler[fila+i][columna+i]==fitxa && interrupt1)
                comptador += 1;
            else interrupt1 = 0;
        }
        if (fila-i>-1 && columna-i>-1){
            if (tauler[fila-i][columna-i]==fitxa && interrupt2)
                comptador += 1;
            else interrupt2 = 0;
        }
        if (!interrupt1 && !interrupt2){
            break;
        }
        else if (comptador>3){ //VICTÒRIA
            return 1;
        }
    }
    comptador = 1; interrupt1=1; interrupt2=1;

    // DIAGONAL (/)
    for(int i=1; i<4; i++){
    // considerem interrupt1 abaix esquerra i interrupt2 adalt dreta, detecten quan no hi ha una fitxa a la banda que s'està mirant
        if(fila+i<N && columna-i<N){
            if (tauler[fila+i][columna-i]==fitxa && interrupt1)
                comptador += 1;
            else interrupt1 = 0;
        }
        if (fila-i>-1 && columna+i>-1){
            if (tauler[fila-i][columna+i]==fitxa && interrupt2)
                comptador += 1;
            else interrupt2 = 0;
        }
        if (!interrupt1 && !interrupt2){
            break;
        }
        else if (comptador>3){ //VICTÒRIA
            return 1;
        }
    }
    return 0;
}



int main(){
    #ifdef _WIN32
        system(""); // Activa ANSI en algunas versiones de Windows
    #endif
    // INICIALITZACIÓ DEL TAULER
    char tauler_actual[N][N];
    for(int i =0; i<N; i++)
        for(int j=0; j<N; j++)
            tauler_actual[i][j]='0';


    int jugador;
    int fila, columna;
    int empat = 1;
    int info=0;

    // TORNS DE TIRADES
    for (int i=0; i<N*N; i++){
        if (i%2 == 0){jugador = 1;}
        else{jugador = 2;}

        // Actualitzem la taula amb cada tirada
        tirada(tauler_actual, jugador, &fila, &columna, info);

        if (victoria(tauler_actual, jugador + '0', fila, columna)) {
            printf("El jugador %i ha guanyat!\n", jugador);
            empat=0;
            break;
        }
    }

    if (empat)
        printf("Empat!\n");

    printf("\n-TAULER  FINAL-\n");
    printTauler(tauler_actual);

    return 0;
}

