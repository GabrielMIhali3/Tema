#include <stdio.h>

FILE *file;

int read_int(char mesaj[]){
        // Acesta functie citeste de la tastatura un sir iar apoi veriifca daca este numar intreg
        int alege;

        while (1){
                printf("\n%s", mesaj); // afisam mesajul
                int v = scanf("%d", &alege); // citim de tastatura

                if (v == 1) // verifica daca este nr intreg
                        break; // opreste bucka infinita
                else{
                        printf("\nNu ai introdus un numar intreg!\n");
                        while (getchar() != '\n'); // testează dacă caracterul citit de la intrare nu este un newline
                }
        }

        return alege;
}

char read_char(char mesaj[], char text[]){
        printf("\n%s", mesaj); // afisam mesajul
        scanf("%s", text); // citim de la tastatura un sir de tip char
}


int isFileEmpty() {
    FILE *file = fopen("bank.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Nu s-a putut deschide fisierul\n");
        return -1; // Returnăm -1 pentru a indica o eroare la deschiderea fișierului
    }

    // Setăm indicatorul de poziție la sfârșitul fișierului
    fseek(file, 0, SEEK_END);

    // Obținem poziția curentă, care va fi 0 dacă fișierul este gol
    long file_size = ftell(file);

    fclose(file);

    // Returnăm 1 dacă fișierul este gol, altfel returnăm 0
    return (file_size == 1) ? 1 : 0;
}


int comparareDate(int zi, int luna, int an, int zi2, int luna2, int an2) {
        // functia compara doua date calendaristice returnand -1 daca primul este mai mic decat al doilea, 0 daca sunt egale si 1 daca primul este mai mare decat al doilea
        if (an == an2){
                if (luna == luna2){
                        if (zi == zi2)
                                return 0;
                        else if (zi < zi2)
                                return -1;
                        else
                                return 1;
                }
                else if (luna < luna2)
                        return -1;
                else
                        return 1;
        }
        else if (an < an2)
                return -1;
        else
                return 1;
}

int calc_sold(){
        if (isFileEmpty()){
                printf("\nNu exista tranzactii!\n");
                return 0;
        }

        file = fopen("bank.txt", "r"); // deschdem fisierul in modul de citire
        int sold = 0;
        int tip, zi, luna, an, pret;
        char descriere[100];

        while (!feof(file)){ // verifica dacă indicatorul de sfârșit de fișier a fost setat pentru un fișier deschis{
                fscanf(file, "%d", &tip); // extragem tipul din fisier
                fscanf(file, "%d", &zi); // extregem ziua din fisier
                fscanf(file, "%d", &luna); // extreagem luna din fisier
                fscanf(file, "%d", &an); // extragem anul din fisier
                fscanf(file, "%d", &pret); // extragem pretul di fisier
                fscanf(file, "%s", descriere); // extragem descrierea din fisier


                if (tip == 1)
                        sold += pret;
                else
                        sold -= pret;
        }

        fclose(file); // inchidem fisierul

        return sold;
}


int verif_cheltuiala(int pret){
        if (calc_sold() - pret < 0)
                return 0;
        return 1;
}

void adaugare_tranzactie(int tip){
        int zi = 0, luna = 0, an = 0, pret = 0;
        char descriere[100] = "";

        zi = read_int("Introduceti ziua: "); // citim de la tastatura
        luna = read_int("Introduceti luna: ");
        an = read_int("Introduceti anul: ");
        pret = read_int("Introduceti suma: ");
        read_char("Introduceti descrierea: ", descriere);

        if (verif_cheltuiala(pret) || tip == 1){
                file = fopen("bank.txt", "a"); // deschidem fisierul in modul de scriere

                fprintf(file, "%d", tip); // scriem tipul in fisier
                fprintf(file, "\n%d", zi); // scriem ziua in fisier
                fprintf(file, "\n%d", luna); // scriem luna in fisier
                fprintf(file, "\n%d", an); // scriem anul in fisier
                fprintf(file, "\n%d", pret); // scriem pretul in fisier
                fprintf(file, "\n%s", descriere); // scriem descrerea in fisier
                fclose(file); // inchidem fisierul
        }
        else
                printf("\nNu puteti adauga acesta tranzactie!\n");
}

void vizualizare_tranzactii(){
        if (isFileEmpty()){
                printf("\nNu exista tranzactii!\n");
                return;
        }

        file = fopen("bank.txt", "r");

        while (!feof(file)){
                 int tip, zi, luna, an, pret;
                 char descriere[100];

                 fscanf(file, "%d", &tip); // extragem informatiile din fisier
                 fscanf(file, "%d", &zi);
                 fscanf(file, "%d", &luna);
                 fscanf(file, "%d", &an);
                 fscanf(file, "%d", &pret);
                 fscanf(file, "%s", descriere);

                 if (tip == 1)
                        printf("\n\nVenit:");
                 else
                        printf("\n\nChetuiala:");

                 printf("\nZiua: %d \nLuna: %d \nAn: %d \nPret: %d \nDescriere %s\n", zi, luna, an, pret, descriere);
        }
        fclose(file);
}

void raport_financiar(){
        if (isFileEmpty()){
                printf("\nNu exista tranzactii!\n");
                return;
        }

        int zi = read_int("Introduceti ziua: "); // citim de la tastatura
        int luna = read_int("Introduceti luna: ");
        int an = read_int("Introduceti anul: ");
        int zi2 = read_int("Introduceti ziua: ");
        int luna2 = read_int("Introduceti luna: ");
        int an2 = read_int("Introduceti anul: ");

        file = fopen("bank.txt", "r"); // dschidem fisierul in modul de citire

        int venit = 0, cheltuiala = 0;

        while (!feof(file)){
                int tip, zi_t, luna_t, an_t, pret_t;
                char descriere[100];

                fscanf(file, "%d", &tip); // extragem din fisier informariile
                fscanf(file, "%d", &zi_t);
                fscanf(file, "%d", &luna_t);
                fscanf(file, "%d", &an_t);
                fscanf(file, "%d", &pret_t);
                fscanf(file, "%s", descriere);

                int comparaData1 = comparareDate(zi, luna, an, zi_t, luna_t, an_t); // comparam cele doua date calendaristice
                int comparaData2 = comparareDate(zi_t, luna_t, an_t, zi2, luna2, an2);
                if (tip == 1 && (comparaData1 == -1 || comparaData1 == 0) && (comparaData2 == -1 || comparaData2 == 0))
                        venit += pret_t;
                else if (tip == 2 && (comparaData1 == -1 || comparaData1 == 0) && (comparaData2 == -1 || comparaData2 == 0))
                        cheltuiala += pret_t;

        }
        fclose(file);  // inchidem fisierul

        printf("\n\nRaportul financiar pentru perioada %d.%d.%d - %d.%d.%d:\n", zi, luna, an, zi2, luna2, an2);
        printf("\nVenit: %d\nCheltuila: %d\n", venit, cheltuiala);
}

int print_menu_add_tranzactie(){
        printf("\n\n1. Adaugare venit.");
        printf("\n2. Adaugare cheltuiala.");
        char text[] = "Alege optiunea: ";

        int alege = read_int(text);

        if (alege < 1 || alege > 2){
                printf("\nNu exista acesta optiune!\n");
                print_menu_add_tranzactie();
        }
        else
                return alege;
}

int print_main_menu(){
        printf("\nMANIUL PRINCIPAL\n\n");
        printf("\n1. Adaugare tranzactie.");
        printf("\n2. Vizualizare sold.");
        printf("\n3. Vizualizare tranzactii.");
        printf("\n4. Raport financiar.");
        printf("\n5. Close.");
        char text[] = "Alege optiunea: ";

        return read_int(text);
}

void main_menu(){
        int alege = print_main_menu();

        if (alege == 1){
                int alege_tranzactie = print_menu_add_tranzactie();
                adaugare_tranzactie(alege_tranzactie);

        }
        else if (alege == 2)
                printf("\nSoludul este: %d\n", calc_sold());
        else if (alege == 3)
                vizualizare_tranzactii();
        else if (alege == 4)
                raport_financiar();
        if (alege != 5){
                if (alege < 1 || alege > 5)
                        printf("\nNu ai intrdis o optiune valida!\n");
                main_menu();
        }
}

int main(){
        main_menu();
}