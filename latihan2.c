#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

#define EXIT 0
#define INSERT_MEMBER 1
#define SHOW_MEMBER 2
#define SEARCH_MEMBER 3

#define LECTURER 1
#define STUDENT 2

typedef struct staff
{
    char *nama;
    char *nim;
} staff_t;

typedef struct dosen
{
    staff_t dsn;
    unsigned long gaji;
    char *matkul;
} dosen_t;

typedef struct mahasiswa
{
    staff_t mhs;
    char *jurusan;
    unsigned long ukt;
} mahasiswa_t;

void show_options()
{
    puts("=================================");
    puts("Masukkan anggota............... 1");
    puts("Tampilkan anggota.............. 2");
    puts("Cari anggota................... 3");
    puts("Keluar......................... 0");
}

void select_option(int *handler)
{
    printf("Masukkan pilihan : ");
    scanf("%d", handler);
}

void insert_lecturer(const staff_t *staff)
{
    FILE *fn = fopen("Dosen_kampus.txt", "a");

    if (fn == NULL)
    {
        puts("File tidak dapat diakses");
        exit(EXIT_FAILURE);
    }

    dosen_t *dosen = (dosen_t *)calloc(sizeof(dosen_t), 1);
    dosen->dsn = *staff;
    dosen->gaji = 0;
    dosen->matkul = (char *)malloc(BUFFER_SIZE);

    printf("Masukkan gaji: Rp");
    scanf("%lu", &dosen->gaji);

    printf("Mata kuliah: ");
    scanf(" %[^\n]", dosen->matkul);

    //   fprintf(fn, "%s,%s,%s,%lu\n", dosen->dsn.nama, dosen->dsn.nim,
    //           dosen->matkul, dosen->gaji);

    fwrite(dosen, sizeof(dosen_t), 1, fn);

    fclose(fn);
    free(dosen);
    system("clear");
    puts("Data baru berhasil ditambahkan!");
    exit(EXIT_SUCCESS);
}

void insert_student(staff_t *staff)
{
    FILE *fn = fopen("Mahasiswa_Kampus.csv", "a");

    if (fn == NULL)
    {
        puts("File tidak dapat diakses");
        exit(EXIT_FAILURE);
    }

    mahasiswa_t *mahasiswa = (mahasiswa_t *)calloc(sizeof(mahasiswa_t), 1);
    mahasiswa->mhs = *staff;
    mahasiswa->ukt = 0;
    mahasiswa->jurusan = (char *)malloc(BUFFER_SIZE);

    printf("Masukkan UKT: Rp");
    scanf("%lu", &mahasiswa->ukt);

    printf("Jurusan kuliah: ");
    scanf(" %[^\n]", mahasiswa->jurusan);

    //   fprintf(fn, "%s,%s,%s,%lu\n", mahasiswa->mhs.nama, mahasiswa->mhs.nim,
    //           mahasiswa->jurusan, mahasiswa->ukt);

    fwrite(mahasiswa, sizeof(mahasiswa_t), 1, fn);

    fclose(fn);
    free(mahasiswa);
    system("clear");
    puts("Data baru berhasil ditambahkan!");
    exit(EXIT_SUCCESS);
}

void insert_member()
{
    // mengalokasi memori untuk staff
    staff_t *staff = (staff_t *)calloc(sizeof(staff_t), 1);
    staff->nama = (char *)malloc(BUFFER_SIZE);
    staff->nim = (char *)malloc(BUFFER_SIZE);

    printf("Masukkan nama: ");
    scanf(" %[^\n]", staff->nama);
    printf("NIM: ");
    scanf("%10s", staff->nim);
    while (getchar() != '\n')
        ;

    puts("");
    puts("Dosen.........1");
    puts("Mahasiswa.....2");

    while (1)
    {
        int status;
        printf("Status: ");
        scanf("%u", &status);

        switch (status)
        {
        case LECTURER:
            insert_lecturer(staff);
        case STUDENT:
            insert_student(staff);
            break;
        default:
            puts("Masukan tidak valid, coba lagi!");
            break;
        }
    }

    free(staff);
}

void print_member(){
    int status;
    puts("\n\nTampilkan daftar dosen ............1");
    puts("\nTampilkan daftar mahasiswa ........2");
    printf("Masukkan pilihan : ");scanf("%d",&status);

    if(status == LECTURER){
        FILE *fp;
        fp = fopen("Dosen_kampus.txt","r");
        if(fp == NULL){
            printf("Maaf anda tidak dapat mengakses data ini!\n");
            exit(0);
        }

        dosen_t current;

        printf("Nama    : %s\n",current.dsn.nama);
        printf("Nim     : %s\n",current.dsn.nim);
        printf("Matkul  : %s\n",current.matkul);
        printf("Gaji    : Rp%ld\n",current.gaji);
        printf("\n\n");


        // while (fread(&current,sizeof(dosen_t),1,fp))
        // {
        //     system("clear");
        //     printf("Nama    : %s\n",current.dsn.nama);
        //     printf("Nim     : %s\n",current.dsn.nim);
        //     printf("Matkul  : %s\n",current.matkul);
        //     printf("Gaji    : Rp%ld\n",current.gaji);
        //     printf("\n\n");
        // }
        fclose(fp);
    }
}

int main(int argc, char const *argv[])
{
    show_options();
    while (1)
    {
        int pilihan;
        select_option(&pilihan);

        switch (pilihan)
        {
        case INSERT_MEMBER:
            insert_member();
            break;
        case SHOW_MEMBER:
            print_member();
            break;
        case SEARCH_MEMBER:
            // search
            break;
        case EXIT:
            exit(EXIT_SUCCESS);

        default:
            printf("Input tidak valid!");
            break;
        }
    }
    return 0;
}
