#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

//dibuat oleh semua sebagai Linked List untuk setiap meja pada restoran
struct meja{
	char nama[30];	//meja atas nama
	int nomor_meja;
	struct meja *next;
};


//dibuat oleh semua sebagai Linked List untuk total pengunjung pada hari ini
struct total {
	char nama[30];
	int angkaReview;
	char review [100];
	struct total *nextTotal;
};

void menuawal(int pengunjung_sekarang, int menu_awal,struct meja *headNode,struct meja *currentNode, struct meja *temp, struct total *headNodeTotal, struct total *currentNodeTotal, struct total *tempTotal);
void menu_pengunjung(int pengunjung_sekarang, int menu_awal,struct meja *headNode,struct meja *currentNode, struct meja *temp, struct total *headNodeTotal, struct total *currentNodeTotal, struct total *tempTotal );
void menu_admin(int pengunjung_sekarang, int menu_awal,struct meja *headNode,struct meja *currentNode, struct meja *temp, struct total *headNodeTotal, struct total *currentNodeTotal, struct total *tempTotal);
void deletePengunjung(int *pengunjung_sekarang, int *nomor_meja,struct meja **headNode );
void read_from_txt(int pengunjung_sekarang,struct meja **headNode,struct meja **currentNode, struct meja **temp);
void read_from_txt_total(struct total **headNode,struct total **currentNode, struct total **temp);
void insertPengunjung (int mejaTerisi[], int *pengunjung_sekarang,struct meja **headNode,struct meja **currentNode, struct meja **temp );
void writeReview (int *nomor_meja, struct meja *headNode);
void avg_rating(struct total *headNodeTotal);
unsigned int count_lines(char namaFile[30]);

int main() {	
	int menu_awal;
	int length,i;
	char namaFileSekarang [30] = "name_list.txt";
	char namaFileTotal    [30] = "total_list.txt";
	int pengunjung_sekarang = count_lines(namaFileSekarang);
	omp_set_num_threads(4);
	struct meja *headNode = NULL;
 	struct meja *currentNode;
	struct meja *temp;
	struct total *headNodeTotal = NULL;
 	struct total *currentNodeTotal;
	struct total *tempTotal;
	read_from_txt (pengunjung_sekarang, &headNode, &currentNode, &temp);
	read_from_txt_total (&headNodeTotal, &currentNodeTotal, &tempTotal);
	temp = headNode;
	menuawal(pengunjung_sekarang, menu_awal,headNode, currentNode, temp, headNodeTotal, currentNodeTotal, tempTotal);
	return 0;
}

// dibuat oleh semua untuk menampilkan menu awal
void menuawal(int pengunjung_sekarang, int menu_awal,struct meja *headNode,struct meja *currentNode, struct meja *temp, struct total *headNodeTotal, struct total *currentNodeTotal, struct total *tempTotal){

	//interface 
	printf("\n===================================\n");
	printf("=             E-Resto             =\n");
	printf("===================================\n");
	printf("\n");
	
	printf("===================================\n");
	printf("                                   \n");
	printf("   1. Masuk sebagai pengunjung     \n"); 
	printf("   2. Masuk sebagai admin          \n");
	printf("   3. Keluar aplikasi              \n");
	printf("                                   \n");
	printf("===================================\n");
	printf("\nPilih: ");
	scanf("%d", &menu_awal); //memilih role user berdasarkan input
	switch(menu_awal){
		case 1:	//jika user memilih 1 maka akan memanggil function menu_pengunjung dan login sebagai pengunjung
			system("cls");
			menu_pengunjung(pengunjung_sekarang, menu_awal,headNode, currentNode, temp, headNodeTotal, currentNodeTotal, tempTotal); 
			break;
		case 2: //jika user memilih 2 maka akan memanggil function menu_admin dan login sebagai admin
			system("cls");
			menu_admin(pengunjung_sekarang, menu_awal,headNode, currentNode, temp, headNodeTotal, currentNodeTotal, tempTotal);
			break;

		case 3: //jika user memilih 3 maka program akan selesai
			//program selesai
			printf("\n-- Terima kasih telah menggunakan program ini --\n");
			system("pause");
			exit(0);
			break;
		default: //jika user memasukkan input yang salah maka akan memanggil function awal dan kembali ke menu awal
			printf("\n-- Input salah --\n");
			system("pause");
			system("cls");
			menuawal(pengunjung_sekarang, menu_awal,headNode, currentNode, temp, headNodeTotal, currentNodeTotal, tempTotal);
			break;
	}
}

// dibuat oleh Aidan untuk menampilkan menu pengunjung
void menu_pengunjung(int pengunjung_sekarang, int menu_awal,struct meja *headNode,struct meja *currentNode, struct meja *temp, struct total *headNodeTotal, struct total *currentNodeTotal, struct total *tempTotal){
	
	char namaFileSekarang [30] = "name_list.txt";
	struct meja *isi;
	int j;
	int isiMeja;
	int mejaTerisi[11];
	char newline;
	int pilihan_menu;
	int i = 1;
	int sentinel = 1;
	if(count_lines > 0){
		pengunjung_sekarang = count_lines(namaFileSekarang); // call function count_lines untuk menentukan jumlah pengunjung saat ini dengan metode menghitung baris
	}
	while(sentinel!=0){
		system("cls");
		printf("\n=======================================\n");
		printf("=           Menu Pengunjung           =\n");
		printf("=======================================\n");
		printf("                                      \n");
		printf("   1. Reservasi meja                  \n");
		printf("   2. Cek jumlah pengunjung saat ini  \n");
		printf("   3. Lihat rating                    \n");
		printf("   4. Kembali ke menu awal            \n");
		printf("   5. Keluar aplikasi                 \n");
		printf("     				                  \n");
		printf("======================================\n");
		printf("\nPilih: ");
		scanf("%d",&pilihan_menu); //memilih fitur program berdasarkan input
		switch(pilihan_menu){		
		
		case 1:		//jika user memilih 1 ,user dapat melakukan reservasi meja 
			system("cls");
			insertPengunjung (mejaTerisi, &pengunjung_sekarang,&headNode,&currentNode,&temp ); //program memanggil function insertPengunjung untuk melakukan reservasi
			break;
		
		case 2: //jika user memilih 2 ,user dapat melihat jumlah pengunjung yang ada di restoran saat ini
			system("cls");
			printf("\n=======================================\n");
			printf("=           Menu Pengunjung           =\n");
			printf("=======================================\n");
			printf("\nJumlah pengunjung saat ini : %d\n", count_lines(namaFileSekarang)-1);
			system("pause");
			break;
		case 3:	//jika user memilih 3 ,user dapat melihat rating rata-rata dari pengunjung restoran sebelumnya
			system("cls");
			printf("\n=======================================\n");
			printf("=           Menu Pengunjung           =\n");
			printf("=======================================\n");
			avg_rating(headNodeTotal); //program memanggil function avg_rating untuk menghitung dan menampilkan rating
			system("pause");
			break;
		case 4: //jika user memilih 4 ,user dapat kembali ke menu awal
			system("cls");
			menuawal(pengunjung_sekarang, menu_awal,headNode, currentNode, temp, headNodeTotal, currentNodeTotal, tempTotal ); //program memanggil function menuawal untuk kembali ke menu awal
			break;
		case 5://jika user memilih 5 ,program akan selesai
			system("cls");
			printf("\n-- Terima kasih telah menggunakan program ini --\n");
			exit(0);
			break;
		}
	}
}

// dibuat oleh Aidan untuk menampilan menu admin
void menu_admin(int pengunjung_sekarang, int menu_awal,struct meja *headNode,struct meja *currentNode, struct meja *temp, struct total *headNodeTotal, struct total *currentNodeTotal, struct total *tempTotal){
	char namaFileSekarang [30] = "name_list.txt";
	FILE *fpointer ;
	int i =0;
	int nomor_meja = 0;
	int input_menu;
	int sentinel;
	int sentinel_pass= 0, sentinel_menu = 0;
	char line[40], nama[30];
	char password_admin[] = "admin12345";
	char password[15];
	

	while(sentinel_pass!=1){
		printf("\n=======================================\n");
		printf("               Menu Admin                \n");
		printf("=======================================\n");
		
		printf("\nMasukkan password: "); 
		scanf("%s", &password); //user memasukkan password
		
		while(sentinel_menu != 1){
			system("cls");
			if(strcmp(password_admin, password)==0){ //jika password benar (dibandingkan dengan password yang telah dideklarasi sebelumnya yaitu 'admin12345'),
													 //maka akan masuk ke menu admin
				system("cls");
				printf("\n=======================================\n");
				printf("                Menu Admin               \n");
				printf("=======================================\n");
				printf("                                      \n");
				printf("   1. List Pengunjung Saat ini        \n");
				printf("   2. List Pengunjung Hari ini        \n");
				printf("   3. Update Pengunjung               \n");
				printf("   4. Kembali ke menu awal            \n");
				printf("   5. Keluar Aplikasi                 \n");
				printf("     				                  \n");
				printf("======================================\n");
				printf("\nPilih: ");
				scanf("%d", &input_menu); //user memasukkan pilihan menu admin
				switch(input_menu){
					case 1:	//jika pilihan user 1, maka program akan menampilkan pengunjung
						system("cls");
						printf("\n=======================================\n");
						printf("                Menu Admin               \n");
						printf("=======================================\n");
						fpointer = fopen("name_list.txt","r+");	
						rewind(fpointer);
						
						//menampilkan  list pengunjung	
						printf("\n  <<< list pengunjung saat ini >>>\n\n");
						printf("=======================================\n");
						temp = headNode;
						for (i=0;i<(pengunjung_sekarang)-1;i++){
							printf("\n%d. Nama: %s", i+1, temp->nama);
							printf("\n   Nomor Meja: %d", temp->nomor_meja);
							printf("\n");
							temp = temp->next;
						}
						printf("=======================================\n");
						fclose(fpointer);
						printf("\n");
						system("pause");
						system("cls");
						break;
						
					case 2: //jika pilihan user 2, maka program akan menampilkan total pengunjung hari ini
						//List Pengunjung Hari Ini
						system("cls");
						printf("\n=======================================\n");
						printf("                Menu Admin               \n");
						printf("=======================================\n");

						printf("\n  <<< list pengunjung hari ini >>>\n\n");
						printf("=======================================\n");
						read_from_txt_total (&headNodeTotal, &currentNodeTotal, &tempTotal);
						fpointer = fopen("total_list.txt","r+");	
						rewind(fpointer);
						//menampilkan list pengunjung	
						printf("\nList Pengunjung Hari Ini\n");
						tempTotal = headNodeTotal;
						int total_pengunjung = count_lines("total_list.txt");
						printf("\nTotal pengunjung = %d", total_pengunjung);
						for (i=0;i<(total_pengunjung);i++){
							printf("\n%d. Nama: %s", i+1, tempTotal->nama);
							printf("\n   Angka review: %d", tempTotal->angkaReview);
							printf("\n   Review: %s", tempTotal->review);
							printf("\n");
							tempTotal = tempTotal->nextTotal;
						}
						printf("=======================================\n");					
						fclose(fpointer);
						fclose(fpointer);
						printf("\n");
						system("pause");
						system("cls");
						break;
						
					case 3: //jika pilihan user 3, maka program akan meminta input user berupa nomor meja pengunjung yang akan keluar
						system("cls");
						printf("\n=======================================\n");
						printf("                Menu Admin               \n");
						printf("=======================================\n");
						printf ("\n\nNomor meja pengunjung yang ingin keluar: ");
						scanf ("%d", &nomor_meja);
						writeReview (&nomor_meja, headNode);
						deletePengunjung(&pengunjung_sekarang, &nomor_meja, &headNode);		
						system("pause");
						break;
					
					case 4: //jika pilihan user 4, maka program akan kembali ke menu awal
						system("pause");
						system("cls");
						menuawal(pengunjung_sekarang, menu_awal,headNode, currentNode, temp, headNodeTotal, currentNodeTotal, tempTotal);
					case 5: //jika pilihan user 5, maka program akan selesai
						system("cls");
						printf("\n-- Terima kasih telah menggunakan program ini --\n");
						exit(0);
						break;
				}
			}
			else{ //jika password salah
				printf("Password Salah\n");
				break;
			}		
		}
	}

}

// dibuat oleh Joshevan untuk memasukkan data pengunjung baru
void insertPengunjung (int mejaTerisi[], int *pengunjung_sekarang,struct meja **headNode,struct meja **currentNode, struct meja **temp ){
	int i;
	int isiMeja;
	struct meja *isi;
	FILE *fpointer = fopen("name_list.txt","r");
	FILE *tempFile = fopen("filetemp.txt", "w");
	rewind(fpointer);
	*temp = *headNode;
	
	printf("\n=======================================\n");
	printf("=           Menu Pengunjung           =\n");
	printf("=======================================\n");
	
	printf ("\nMeja terisi = ");
				
	for (i=0;i<11;i++){
		mejaTerisi[i] = 0;
		}
		
	for (i=0;i<*(pengunjung_sekarang)-1;i++){
		mejaTerisi[(*temp)->nomor_meja] = (*temp)->nomor_meja;
		printf ("%d ",(*temp)->nomor_meja);	//menampilkan meja yang sudah diisi oleh pengunjung
		(*temp) = (*temp)->next;
	}
	
	printf ("\nMeja kosong = ");
	for (i=1;i<11;i++){
		if (mejaTerisi[i]==0){
			printf ("%d ",i); //menampilkan meja yang masih kosong
		}
	}
	
	printf ("\n\nPilih meja untuk direservasi =  ");
	scanf ("%d",&isiMeja); // user memilih nomor meja yang ingin direservasi
	
	while (mejaTerisi[isiMeja] !=0 || isiMeja > 10){ //jika user sudah memilih yang terisi, maka program akan meminta input kembali sampai user memasukkan nomor meja yang masih kosong
		if(isiMeja > 10){
			printf ("\n-- Meja yang dimasukkan salah silahkan pilih meja lain --\n");
		}else if(mejaTerisi[isiMeja] !=0 ){
			printf ("\n-- Meja tersebut sudah terisi silahkan pilih meja lain --\n");
				
		}
		printf ("\nPilih meja untuk direservasi =  ");
		scanf ("%d",&isiMeja);
	}
	isi = malloc (sizeof (struct meja)); //program mengalokasikan memori untuk user yang baru masuk
	(*pengunjung_sekarang) = (*pengunjung_sekarang) + 1;
	printf("\nMeja atas nama: "); 
	scanf("%s", &isi->nama); 
	isi->nomor_meja = isiMeja;
	*temp = *headNode;
	

	for(i = 0; i < (*pengunjung_sekarang)-3 ; i++){
		(*temp) = (*temp)->next;
	}
	if((*temp)->nomor_meja < isiMeja){
		(*temp)->next = isi;
	}else if((*temp)->nomor_meja > isiMeja){
		(*temp) = *headNode;
		while ((*temp)->next->nomor_meja < isi->nomor_meja){ //algoritma untuk insert node pengunjung baru
			(*temp) = (*temp)->next;
		}
		isi->next = (*temp)->next;
		(*temp)->next = isi;		
	}
	
	(*temp) = *headNode;
	for (i=0;i<*(pengunjung_sekarang)-1;i++){
	fprintf(tempFile,"%s %d\n",(*temp)->nama,(*temp)->nomor_meja);
	*temp = (*temp)->next;
	}
	fprintf (tempFile,"#");
	fclose (tempFile);
	fclose (fpointer);
	remove ("name_list.txt");
	rename ("filetemp.txt","name_list.txt");
	printf("\n");
	system("pause");
}

// dibuat oleh Joshevan untuk menghapus data pengunjung
void deletePengunjung (int *pengunjung_sekarang, int *nomor_meja, struct meja **headNode){
	struct meja*temp1;
	struct meja*temp2;
	int i;
    FILE *fileptr1, *fileptr2;
 	temp1 = *headNode;
 	temp2 = *headNode;
    fileptr1 = fopen("name_list.txt", "r");
    rewind(fileptr1);
    fileptr2 = fopen("filetemp.txt", "w");
    while (temp1->next->nomor_meja != *nomor_meja){ //algoritma untuk menghapus node dari pengunjung yang akan keluar
    	temp1=temp1->next; //melakukan loop dari awal sampai satu node sebelum node yang dihapus
	}
	while (temp2->nomor_meja != *nomor_meja){ 
    	temp2=temp2->next; //melakukan loop dari awal sampai node yang dihapus
	}
	temp1->next = temp2->next; //menghubungkan satu node sebelum node yang dihapus dengan satu node setelah node yang dihapus
	free (temp2); //membebaskan memori dari node yang dihapus
	(*pengunjung_sekarang) = (*pengunjung_sekarang) - 1;
	temp1 = *headNode;
	for (i=0;i<*(pengunjung_sekarang)-1;i++){ 
		fprintf(fileptr2,"%s %d\n",temp1->nama,temp1->nomor_meja);
		temp1= temp1->next;
	}
	fprintf (fileptr2,"#");
	printf("\n");
    fclose(fileptr1);
    fclose(fileptr2);
    remove ("name_list.txt");
	rename ("filetemp.txt","name_list.txt");
}

// dibuat oleh Joshevan untuk menghitung jumlah pengunjung
unsigned int count_lines(char namaFile[30]){
    unsigned int  lines = 0;
    int c = '\0';
    int pc = '\n';
	FILE *fptr = fopen (namaFile,"r");
    while (c != EOF){ //menghitung jumlah line sampai end of file
  		c = fgetc(fptr);
		if(c == '\n' && pc != '\n'){
        	 lines++;
		}         
        pc = c;
    }
    if(pc != '\n'){
    	lines++;
	} 
	fclose (fptr);
    return lines;
}

// dibuat oleh Vincent untuk membaca data pengunjung saat ini dari file txt
void read_from_txt(int pengunjung_sekarang, struct meja **headNode,struct meja **currentNode, struct meja **temp){
	int i;
	FILE *fpointer = fopen("name_list.txt","r+");
	rewind(fpointer);
	if(fpointer==NULL){
		printf("Error opening/reading from name_list.txt");
	}else{
		*headNode =malloc(sizeof (struct meja)); //algoritma untuk memasukkan data dari file ke linked list saat inisialisasi program
		if (*headNode == NULL){
			 printf ("Memory not allocated");
		}
		fscanf(fpointer, "%s %d\n", &(*headNode)->nama, &(*headNode)->nomor_meja);
		(*headNode)->next = NULL;
		*temp = *headNode;
		for(i = 1; i <=(pengunjung_sekarang-1); i++){
			*currentNode = malloc(sizeof(struct meja));
			if (*currentNode == NULL){
				 printf ("Memory not allocated");
			}
			fscanf(fpointer, "%s %d\n", &(*currentNode)->nama,  &(*currentNode)->nomor_meja);
			(*temp)->next = *currentNode;
			*temp = (*temp)->next;
		}
	}
	fclose(fpointer);
	system("cls");	
}

// dibuat oleh Vincent untuk membaca data pengunjung pada hari ini dari file txt
void read_from_txt_total(struct total **headNodeTotal,struct total **currentNodeTotal, struct total **tempTotal){
	int pengunjung_total = count_lines	("total_list.txt");
	int i;
	FILE *fpointer = fopen("total_list.txt","r+");
	rewind(fpointer);
	if(fpointer==NULL){
		printf("Error opening/reading from total_list.txt");
	}else{
		*headNodeTotal =malloc(sizeof (struct total));//algoritma untuk memasukkan data dari file ke linked list saat inisialisasi program
		if (*headNodeTotal == NULL) printf ("Memory not allocated");
		fscanf(fpointer, "%s %d %[^\n]\n", &(*headNodeTotal)->nama, &(*headNodeTotal)->angkaReview, &(*headNodeTotal)->review);
		*tempTotal = *headNodeTotal;
			for(i = 1; i <pengunjung_total; i++){
			*currentNodeTotal = malloc(sizeof(struct total));
			if (*currentNodeTotal == NULL) printf ("Memory not allocated");
			fscanf(fpointer, "%s %d %[^\n]\n", &(*currentNodeTotal)->nama, &(*currentNodeTotal)->angkaReview, &(*currentNodeTotal)->review);
			(*tempTotal)->nextTotal = *currentNodeTotal;
			*tempTotal = (*tempTotal)->nextTotal;
		}
	}
	fclose(fpointer);	
}

// dibuat oleh Vincent untuk menginput rating ke file txt
void writeReview (int *nomor_meja, struct meja *headNode ){
	FILE *fpointer = fopen ("total_list.txt","a");
	rewind(fpointer);
	struct total *tempTotal;	//menambah node yaitu pengunjung yang keluar untuk dimasukkan ke data pengunjung pada hari ini
	tempTotal = malloc (sizeof(struct total));
	struct meja  *temp = headNode;
	while (temp->nomor_meja != *nomor_meja){
			temp = temp->next;
	}
	strcpy (tempTotal->nama, temp->nama);
	printf ("\nNilai rating restoran (0-10): ");
	scanf ("%d",&tempTotal->angkaReview); //meminta input dari user berupa rating dari 1-10
	printf ("\nMasukkan review restoran: ");
	scanf (" %s", &tempTotal->review); //meminta revi
	fprintf (fpointer, "\n%s %d %s", tempTotal->nama, tempTotal->angkaReview, tempTotal->review);
	fclose (fpointer);
}

// dibuat oleh Aidan untuk mencari rata-rata dari rating yang diberikan dari pengunjung
void avg_rating(struct total *headNodeTotal){
	int i;
	float sum = 0;
	char namaFileTotal[30] = "total_list.txt";
	struct total *iter;
	iter = headNodeTotal;
	int jumlah_total_pengunjung = count_lines(namaFileTotal);
	#pragma omp parallel //program akan dijalankan untuk menghitung nilai rata-rata secara paralel
	{
		iter = headNodeTotal;
		#pragma omp master
		{
			while(iter){
				#pragma omp task firstprivate(iter)
				{
					#pragma omp critical
					sum+=iter->angkaReview;
				}
				iter = iter->nextTotal;
			}
		}
	}
	printf("\nRating Restoran = %.1f\n\n", sum/jumlah_total_pengunjung);
}


