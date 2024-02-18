CC = gcc
CFLAGS = -g -Wall 

all: main main_comparaison_temps main_plusieurs_exemplaires

main_comparaison_temps: main_comparaison_temps.o biblioH.o biblioLC.o entreeSortieH.o entreeSortieLC.o 
	$(CC) $(CFLAGS) -o $@ $^ -lm

main_plusieurs_exemplaires: main_plusieurs_exemplaires.o biblioH.o biblioLC.o entreeSortieH.o entreeSortieLC.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

main: main.o biblioH.o biblioLC.o entreeSortieH.o entreeSortieLC.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

biblioLC.o: biblioLC.c
	$(CC) $(CFLAGS) -c biblioLC.c 

entreeSortieLC.o: entreeSortieLC.c
	$(CC) $(CFLAGS) -c entreeSortieLC.c  

entreeSortieH.o: entreeSortieH.c
	$(CC) $(CFLAGS) -c entreeSortieH.c 

biblioH.o: biblioH.c
	$(CC) $(CFLAGS) -c biblioH.c -lm

main_comparaison_temps.o: main_comparaison_temps.c
	$(CC) $(CFLAGS) -c main_comparaison_temps.c 

main_plusieurs_exemplaires.o: main_plusieurs_exemplaires.c
	$(CC) $(CFLAGS) -c main_plusieurs_exemplaires.c 

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

clean: 
	rm -rf main *.o