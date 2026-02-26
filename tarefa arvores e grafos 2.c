#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void gerarDecrescente(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void copiarVetor(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++)
        destino[i] = origem[i];
}


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;

        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}


void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}



void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}



int particionar(int arr[], int low, int high) {
    int pivo = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivo) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = particionar(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}



void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}



void executar(void (*sort)(int[], int), int base[], int n) {

    int *vetor = malloc(n * sizeof(int));
    copiarVetor(base, vetor, n);

    clock_t inicio = clock();
    sort(vetor, n);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao: %.6f segundos\n", tempo);

    free(vetor);
}



int main() {

    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int *base = malloc(n * sizeof(int));
    gerarDecrescente(base, n);

    int opcao;

    printf("\n=== MENU DE ORDENACAO ===\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("6 - Shell Sort\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: executar(bubbleSort, base, n); break;
        case 2: executar(selectionSort, base, n); break;
        case 3: executar(insertionSort, base, n); break;
        case 4: {
            int *vetor = malloc(n * sizeof(int));
            copiarVetor(base, vetor, n);
            clock_t inicio = clock();
            mergeSort(vetor, 0, n - 1);
            clock_t fim = clock();
            printf("\nTempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
            free(vetor);
            break;
        }
        case 5: {
            int *vetor = malloc(n * sizeof(int));
            copiarVetor(base, vetor, n);
            clock_t inicio = clock();
            quickSort(vetor, 0, n - 1);
            clock_t fim = clock();
            printf("\nTempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
            free(vetor);
            break;
        }
        case 6: executar(shellSort, base, n); break;
        default: printf("Opcao invalida.\n");
    }

    free(base);
    return 0;
}
