#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct nodo_s {
    int idnodo;
    int dist;
    int prec;
}nodo_t;

typedef struct classifica_s {
    int idgrafo;
    int peso;
}classifica_t;

void maxHeapify(classifica_t [], int, int);
void minHeapify(nodo_t [], int, int);
void aggiungiGrafo(int dim,int[][dim], char *);
void costruisciMaxHeap(classifica_t [], int);
void controllaClassifica(classifica_t [], int, int, int);
int dijkstra(int dim, int [][dim], nodo_t []);

//dichiarare la struttura a tre campi per i nodi, i cui campi sono il precedente, la distanza dalla sorgente (e il nodo che rappresenta).
//dichiarare la struttura a due campi
//dichiare le tre funzioni aggiungiGrafo, controllaClassifica, dijkstra (oltre a quelle per gestire gli heap) e controllaClassifica.

int main () {
    int numnodi, klen, j, z, count = 0, sum;
    //unsigned int prova;  usare %u

    //Gestione della prima riga (numnodi e klen)
    char ptr[22], *str;
    if(fgets(ptr, 22, stdin));
    str = ptr;
    numnodi = (int)strtol(str, &str, 10);
    str = str +1;
    klen = (int)strtol(str, &str, 10);

    //Allocazione delle strutture dati
    int matAd[numnodi][numnodi];
    char riga[11*numnodi];
    classifica_t maxHeap[klen];
	nodo_t minHeap[numnodi];

    //Gestione della seconda riga (TopK o AggiungiGrafo)
    if(fgets(ptr, 15, stdin) != NULL);
    if(ptr[0] == 'A') {
        printf("Aggiungi Grafo num: %d\n", count);
        aggiungiGrafo(numnodi,matAd, riga);
        sum = dijkstra(numnodi, matAd, minHeap);
        maxHeap[count].peso = sum;
        maxHeap[count].idgrafo = count;
        count++;
        for(j = 0; j < numnodi; j++) {
            for(z = 0; z < numnodi; z++) {
                printf("%d ", matAd[j][z]);
            }
            printf("\n");
        }
		printf("\n");
    } else {
		printf("\n");
	}

    //Gestione delle rimanenti richieste AggiungiGrafo o TopK
    while (fgets(riga, 11*numnodi, stdin) != NULL) {
        if(riga[0] == 'A') {
            printf("Aggiungi Grafo num: %d\n", count);
            aggiungiGrafo(numnodi,matAd, riga);
            sum = dijkstra(numnodi, matAd, minHeap);
            if(count < klen - 1) {
                maxHeap[count].idgrafo = count;
                maxHeap[count].peso = sum;
            }else if(count == klen -1){
                maxHeap[count].idgrafo = count;
                maxHeap[count].peso = sum;
                costruisciMaxHeap(maxHeap, klen);
            } else {
                controllaClassifica(maxHeap, klen, sum, count);
            }
            count++;
            for(j = 0; j < numnodi; j++) {
                for(z = 0; z < numnodi; z++) {
                    printf("%d ", matAd[j][z]);
                }
                printf("\n");
            }
			printf("\n");
        } else {
            printf("Topk\n");
            if(count < klen) {
                for(j = 0; j < count; j++) {
                    printf("%d ", j);
                }
            } else {
                for(j = 0; j < klen; j++) {
                    printf("%d-%d ", maxHeap[j].idgrafo, maxHeap[j].peso);
                }
            }
            printf("\n");
        }
    }
    //allocare con malloc min-heap di dim numnodi per gestire i nodi in dijkstra
    return 0;
}

void aggiungiGrafo(int dimnodi, int mat[][dimnodi], char *riga) {
    char *ptr;
    int i, prova, k, dimriga = 11*dimnodi;
    for(i = 0; i < dimnodi; i++) {
        if(fgets(riga, dimriga, stdin));
        ptr = riga;
        for (k = 0; k < dimnodi; k++) {
            prova = (int)strtol(ptr, &ptr, 10);
            ptr = ptr + 1;
            mat[i][k] = prova;
        }
    }
}

void maxHeapify(classifica_t maxHeap[], int pos, int dim) {
    int left, right, posmax, tmp;
    left = 2*pos + 1;
    right = 2*pos + 2;
    if(left < dim && maxHeap[left].peso > maxHeap[pos].peso) {
        posmax = left;
    } else posmax = pos;
    if(right < dim && maxHeap[right].peso > maxHeap[posmax].peso) {
        posmax = right;
    }
    if(posmax != pos) {
        tmp = maxHeap[pos].peso;
        maxHeap[pos].peso = maxHeap[posmax].peso;
        maxHeap[posmax].peso = tmp;
        tmp = maxHeap[pos].idgrafo;
        maxHeap[pos].idgrafo = maxHeap[posmax].idgrafo;
        maxHeap[posmax].idgrafo = tmp;
        maxHeapify(maxHeap, posmax, dim);
    }
}

void minHeapify(nodo_t minHeap[], int pos, int dim) {
    int left, right, posmin, tmp;
    left = 2*pos + 1;
    right = 2*pos + 2;
    if(left < dim && minHeap[left].dist < minHeap[pos].dist) {
        posmin = left;
    } else posmin = pos;
    if(right < dim && minHeap[right].dist < minHeap[posmin].dist) {
        posmin = right;
    }
    if(posmin != pos) {
        tmp = minHeap[pos].dist;
        minHeap[pos].dist = minHeap[posmin].dist;
        minHeap[posmin].dist = tmp;
        tmp = minHeap[pos].idnodo;
        minHeap[pos].idnodo = minHeap[posmin].idnodo;
        minHeap[posmin].idnodo = tmp;
        minHeapify(minHeap, posmin, dim);
    }
}

void costruisciMaxHeap(classifica_t maxHeap[], int dim) {
    int i;
    for(i = dim/2; i >= 0; i--) {
        maxHeapify(maxHeap, i, dim);
    }
}

void controllaClassifica(classifica_t maxHeap[], int dim, int peso, int idgrafo) {
    if(peso < maxHeap[0].peso) {
        maxHeap[0].peso = peso;
        maxHeap[0].idgrafo = idgrafo;
        maxHeapify(maxHeap, 0, dim);
    }
}

int dijkstra(int dim, int mat[][dim], nodo_t minHeap[]) {
    int sum = 0, i, disttmp, base, nodoMin;
    minHeap[0].idnodo = 0;
    minHeap[0].dist = 0;
    minHeap[0].prec = -1;
    for(i = 1; i < dim; i++) {
        minHeap[i].idnodo = i;
        minHeap[i].dist = INT_MAX;
        minHeap[i].prec = -1;
    }
    while(dim > 0) {
        if(minHeap[0].dist < INT_MAX) {
            printf("nodo da eliminare: %d, conta: %d\n", minHeap[0].idnodo, dim);
            sum = sum + minHeap[0].dist;
            printf("somma: %d\n", sum);
        }
        base = minHeap[0].dist;
        nodoMin = minHeap[0].idnodo;
        for(i = 1; i < dim; i++) {
            if(mat[nodoMin][minHeap[i].idnodo] != 0) {
                disttmp = base + mat[nodoMin][minHeap[i].idnodo];
                if (minHeap[i].dist > disttmp) {
                    minHeap[i].dist = disttmp;
                    minHeap[i].prec = nodoMin;
                }
            }
        }
        dim--;
        minHeap[0].dist = minHeap[dim].dist;
        minHeap[0].prec = minHeap[dim].prec;
        minHeap[0].idnodo = minHeap[dim].idnodo;
	    for(i = dim/2; i >= 0; i--) {
			minHeapify(minHeap, i, dim);
		}
        for(i = 0; i < dim; i++) {
            printf("nodo e dist: %d-%d ", minHeap[i].idnodo, minHeap[i].dist);
        }
        printf("\n");
    }
    return sum;
}
