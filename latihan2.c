#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct stuff
typedef struct staff
{
    char nama[20];
    char nim[10];
} staff;

typedef struct dosen
{
    staff dsn;
    long long int gaji;
    char matkul[20];
} dosen;

typedef struct mahasiwa
{
    staff mhs;
    char jurusan[20];
    long long int ukt;
} mahasiswa;

void menu();
void print();
// void search();
void insert();

int choice = 0;

int main()
{
    menu();
    switch (choice)
    {
    case 1:
        insert();
        break;
    case 2:
        print();
        break;
    case 3:
        // search();
        break;
    case 4:
        exit(0);
    default:
        break;
    }
    return 0;
}

void menu()
{
    puts("=================================\n");
    puts("Masukkan anggota............... 1\n");
    puts("Tampilkan anggota.............. 2\n");
    puts("Cari anggota................... 3\n");
    puts("Keluar......................... 4\n");
    printf("Masukkan pilihan : ");
    scanf("%d", &choice);
}

void insert()
{
    char nama[20], nim[10];
    int status;
    fflush(stdin);
    printf("Masukkan nama :");
    scanf("%[^\n]s", nama);
    printf("Nim :");
    scanf("%10s", nim);
    puts("\nDosen.........1\n");
    puts("Mahasiswa.....2\n");
    printf("Status :");
    scanf("%d", &status);

    if (status == 1)
    {
        FILE *fp = fopen("Dosen_kampus.txt", "a");
        if (fp == NULL)
        {
            puts("Maaf file tidak dapat diakses!\n");
        }
        dosen new_dosen;

        char matkul[20];
        long long int gaji;
        printf("Masukkan Gaji : Rp");
        scanf("%lld", &gaji);
        fflush(stdin);
        printf("Mata kuliah : ");
        scanf("%[^\n]s", matkul);

        strcpy(new_dosen.dsn.nama, nama);
        strcpy(new_dosen.dsn.nim, nim);
        strcpy(new_dosen.matkul, matkul);
        new_dosen.gaji = gaji;

        fprintf(fp, "%-20s\t%-10s\t\t%-20s\tRp%lld\n", new_dosen.dsn.nama, new_dosen.dsn.nim, new_dosen.matkul, new_dosen.gaji);

        fclose(fp);
        system("clear");
        puts("Data baru berhasil ditambahkan!\n");
    }

    else if (status == 2)
    {
        FILE *fp = fopen("mahasiswa_kampus.txt", "a");
        if (fp == NULL)
        {
            puts("Maaf file tidak dapat diakses!\n");
        }
        mahasiswa *new_mahasiswa;
        new_mahasiswa = (mahasiswa *)malloc(sizeof(mahasiswa));

        if (new_mahasiswa == NULL)
        {
            printf("Memmory tidak tersedia!\n");
            exit(0);
        }

        char jurusan[20];
        long long int ukt;
        printf("Masukkan ukt : Rp");
        scanf("%lld", &ukt);
        fflush(stdin);
        printf("Jurusan : ");
        scanf("%[^\n]s", jurusan);

        strcpy(new_mahasiswa->mhs.nama, nama);
        strcpy(new_mahasiswa->mhs.nim, nim);
        strcpy(new_mahasiswa->jurusan, jurusan);
        new_mahasiswa->ukt = ukt;

        fprintf(fp, "%-20s\t%-10s\t\t%-20s\tRp%lld\n", new_mahasiswa->mhs.nama, new_mahasiswa->mhs.nim, new_mahasiswa->jurusan, new_mahasiswa->ukt);

        fclose(fp);
        system("clear");
        puts("Data baru berhasil ditambahkan!\n");
    }
    else{
        printf("Masukkan pilihan yang benar!");
        insert();
    }
}

void print(){
    int status;
    puts("\n\nTampilkan daftar dosen ............1");
    puts("\nTampilkan daftar mahasiswa ........2");
    printf("Masukkan pilihan : ");scanf("%d",&status);

    if(status == 1){
        FILE *fp;
        fp = fopen("Dosen_kampus.txt","r");
        if(fp == NULL){
            printf("Maaf anda tidak dapat mengakses data ini!\n");
            exit(0);
        }

        dosen current_dosen;
        while (fread(&current_dosen,sizeof(dosen),1,fp) != 0)
        {
            system("clear");
            printf("Nama    : %s\n",current_dosen.dsn.nama);
            // printf("Nim     : %s\n",current_dosen.dsn.nim);
            // printf("Matkul  : %s\n",current_dosen.matkul);
            // printf("Gaji    : Rp%lld\n",current_dosen.gaji);
            printf("\n\n");
        }
        fclose(fp);
    }


}