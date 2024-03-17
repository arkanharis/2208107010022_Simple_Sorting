#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(int *array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int array[], int length)
{
    for (int step = 0; step < length - 1; step++)
    {
        int min_idx = step;
        for (int i = step + 1; i < length; i++)
        {
            if (array[i] < array[min_idx])
                min_idx = i;
        }

        int temp = array[min_idx];
        array[min_idx] = array[step];
        array[step] = temp;
    }
}

void insertionSort(int array[], int size)
{
    for (int step = 1; step < size; step++)
    {
        int key = array[step];
        int j = step - 1;

        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

int main()
{
    int pilihan;
    printf("\n======= SIMPLE SORTING =======\n");
    printf("-------- MADE BY ARKAN -------\n");
    printf("Pilihan Menu: \n");
    printf("1. Generate File 1 Juta Bilangan Acak\n");
    printf("2. Sorting dengan InsertionSort\n");
    printf("3. Sorting dengan SelectionSort\n");
    printf("4. Sorting dengan BubbleSort\n");
    printf("> ");
    scanf("%d", &pilihan);
    while(pilihan < 1 || pilihan > 4){
        printf("\nMasukkan menu dengan benar!\n");
        printf("> ");
        scanf("%d", &pilihan);
    }
    printf("\n");

    if (pilihan == 1)
    {
        // Generate File Random
        FILE *input_file;
        input_file = fopen("random.txt", "w");
        if (input_file == NULL)
        {
            printf("Error opening file.\n");
            return 1;
        }

        srand(time(NULL));
        for (int i = 0; i < 1000000; i++)
        {
            fprintf(input_file, "%d ", rand());
        }
        fclose(input_file);

        printf("File dengan 1 juta bilangan random sudah dibuat atau diperbarui!\n\n");
        return 0;
    }
    else if (pilihan > 1 && pilihan <= 4)
    {
        int ukuran;
        printf("Masukkan jumlah bilangan untuk diurutkan: ");
        scanf("%d", &ukuran);
        while (ukuran <=0 || ukuran > 1000000)
        {
            printf("\nJumlah bilangan minimal 1 (satu) dan maksimal 1000000 (satu juta)!\n");
            printf("Masukkan jumlah bilangan untuk diurutkan: ");
            scanf("%d", &ukuran);
        }
        printf("\n");

        FILE *file;
        // Buka file random.txt untuk dibaca
        file = fopen("random.txt", "r");
        if (file == NULL)
        {
            printf("Error membuka file input.\n");
            return 0;
        }

        // Baca dan tampilkan setiap bilangan satu per satu
        int *numbers = (int *)malloc(ukuran * sizeof(int));
        int count = 0;
        while (fscanf(file, "%d", numbers + count) != EOF)
        {
            count++;
            if (count == ukuran)
            {
                break;
            }
        }
        int *copiedNumbers = (int *)malloc(count * sizeof(int));
        clock_t t;
        double time_taken;

        if (pilihan == 2)
        {
            // Insertion Sort
            memcpy(copiedNumbers, numbers, count * sizeof(int));
            t = clock();
            insertionSort(copiedNumbers, count);
            t = clock() - t;
            time_taken = (((double)t) / CLOCKS_PER_SEC)*1000; // calculate the elapsed time
            printf("Algoritma Insertion Sort memakan waktu %.0fms.\n", time_taken);
            // printf("%d\n", copiedNumbers[0]);
            // printf("%d", copiedNumbers[count - 1]);
        }
        else if (pilihan == 3)
        {
            // Selection Sort
            memcpy(copiedNumbers, numbers, count * sizeof(int));
            t = clock();
            selectionSort(copiedNumbers, count);
            t = clock() - t;
            time_taken = (((double)t) / CLOCKS_PER_SEC)*1000; // calculate the elapsed time
            printf("Algoritma Selection Sort memakan waktu %.0fms.\n", time_taken);
            // printf("%d\n", copiedNumbers[0]);
            // printf("%d", copiedNumbers[count - 1]);
        }
        else
        {
            // Bubble Sort
            memcpy(copiedNumbers, numbers, count * sizeof(int));
            t = clock();
            bubbleSort(copiedNumbers, count);
            t = clock() - t;
            time_taken = (((double)t) / CLOCKS_PER_SEC)*1000; // calculate the elapsed time
            printf("Algoritma Bubble Sort memakan waktu %.0fms.\n", time_taken);
            // printf("%d\n", copiedNumbers[0]);
            // printf("%d", copiedNumbers[count - 1]);
        }
        // Tutup file setelah selesai
        fclose(file);
        free(numbers); // Jangan lupa untuk membebaskan memori yang dialokasikan

        FILE *output_file;
        output_file = fopen("sorted.txt", "w");
        if (output_file == NULL)
        {
            printf("Error membuka file hasil.\n");
            return 1;
        }

        for (int i = 0; i < count; i++)
        {
            fprintf(output_file, "%d ", copiedNumbers[i]);
        }
        fclose(output_file);

        printf("\nFile hasil sorting berhasil dibuat!");
        free(copiedNumbers);
        return 0;
    }
}
