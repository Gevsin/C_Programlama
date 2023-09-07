#include<stdio.h>
#include<locale.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <time.h>
struct Ogrenci{
char ad[50];
char soyad[50];
char tc[12];
char telefon[12];   //sonunda /0 oldu�u i�in 1 fazla tan�mland�
int no;
};

void ekle(){

struct Ogrenci ogrenci;

	printf("\n ��renci Ad�n� Giriniz: ");
    scanf("%s",ogrenci.ad);
   
    printf("\n ��renci Soyad� Giriniz: ");
    scanf("%s",ogrenci.soyad);
   
    printf("\n ��renci TC Kimlik No Giriniz: ");
    scanf("%s",ogrenci.tc);
   
    printf("\n ��renci Telefonu Giriniz: ");
    scanf("%s", ogrenci.telefon);
   

    //--------------------------telefon kontrol--------------------------
   
    int telefonUzunluk = strlen(ogrenci.telefon);
   
    while(telefonUzunluk !=11){
    printf("\n ��renci Telefonu Hatal� Tekrar Giriniz: ");
    scanf("%s",ogrenci.telefon);
    telefonUzunluk=strlen(ogrenci.telefon);
	}

	//--------------------------tc kontrol--------------------------

	int tcUzunluk=strlen(ogrenci.tc);

	int sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';

	int ilkBasamak =ogrenci.tc[0] - '0';
	
	do{  
		if(tcUzunluk !=11){

			printf("\n Girilen TC 11 Basamakl� De�il ");
			printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
    		scanf("%s",ogrenci.tc);
    		tcUzunluk=strlen(ogrenci.tc);
    		sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    		ilkBasamak =ogrenci.tc[0] - '0';
		}
		
		if(sonBasamak %2){
			printf("\n Girilen TC nin Son Basama�� 0-2-4-6-8 de�erinde olmal�");
			printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
    		scanf("%s",ogrenci.tc);
    		tcUzunluk=strlen(ogrenci.tc);
    		sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    		ilkBasamak =ogrenci.tc[0] - '0';
		}
		
		if(ilkBasamak == 0){
			printf("\n Girilen TC nin �lk Basama�� 0 Olamaz");
			printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
			scanf("%s",ogrenci.tc);
    		tcUzunluk=strlen(ogrenci.tc);
    		sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
			ilkBasamak = ogrenci.tc[0] - '0';
		}

		
		// Ba�ka kay�tlarla kar��la�t�rma 
		
		struct Ogrenci yedek;
		char aranan_tc[12]; 
		strcpy(aranan_tc,ogrenci.tc);
		int var = 0;
	
		do{
		
			FILE *dosya1 = fopen("ogrenciKayitlari.txt", "r");
		
			while (fscanf(dosya1, "%s %s %s %s %d", yedek.ad, yedek.soyad, yedek.tc, yedek.telefon, &yedek.no) != EOF) {
   
        		if (strcmp(yedek.tc, aranan_tc) == 0) { //e�itse 0 de�erini d�nd�r�r
        
        			var =1;
        	
        			printf("\n Girilen TC Ba�ka ��renciye Ait");
					printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
    				scanf("%s",ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    				ilkBasamak =ogrenci.tc[0] - '0';
    				strcpy(aranan_tc,ogrenci.tc);	
    			}else{
    				var=0;
				}
    		}
    		
    		strcpy(ogrenci.tc,aranan_tc);
    		fclose(dosya1);
		}while(var);    
	
	
	}while(tcUzunluk !=11 || sonBasamak %2|| ilkBasamak==0);

	
	//--------------------------��renci no atama--------------------------

	ogrenci.no = numara();

	//-----------��renci bilgilerini dosyaya kay�t i�lmleri -----------------	   
	FILE *dosya;

	dosya = fopen("ogrenciKayitlari.txt","a"); //ekleme modunda a�ar
	
	if(dosya == NULL) //dosya bo�sa olu�tur ve ba�tan yaz
	{
		dosya = fopen("ogrenciKayitlari.txt","w");

		fprintf(dosya, "%s %s %s %s %d \n"
		,ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
		
	}else{ //e�er dosya varsa sonuna ekleme yazp

		fprintf(dosya, "%s %s %s %s %d \n",
		ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
	}
	
	fclose(dosya);
	
	//--------------------------Bilgilendirme--------------------------

	printf("\n---------- Kay�t Edilen ��rencinin Bilgileri---------- ");

	printf("\n ��renci Ad�: %s" , ogrenci.ad);
   
    printf("\n ��renci Soyad�: %s", ogrenci.soyad);
   
    printf("\n ��renci TC Kimlik No: %s", ogrenci.tc);
   
	printf("\n ��renci Telefon Numaras�: %s", ogrenci.telefon);

    printf("\n ��renci Numaras� : %d", ogrenci.no);
}

int numara(){

    return rand() % 100000;
}

void sil(){
	
	FILE *dosya = fopen("ogrenciKayitlari.txt", "r");
    FILE *gecici_dosya = fopen("geciciDosya.txt", "w");
   
	int bulundu=0;
	struct Ogrenci ogrenci;

	char aranan_tc[12];
	char secim;

	printf("\nKayd�n� Silmek �stedi�iniz ��rencinin TC Numaras�n� Giriniz: ");
    scanf("%s", aranan_tc);
	
	while (fscanf(dosya, "%s %s %s %s %d", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, &ogrenci.no) != EOF) {
	
		if (strcmp(ogrenci.tc, aranan_tc) == 0) { //e�itse 0 de�erini d�nd�r�r

			printf("\n---------- Kayd� Bulunan ��rencinin Bilgileri---------- ");

			printf("\n ��renci Ad�: %s" , ogrenci.ad);
   
    		printf("\n ��renci Soyad�: %s", ogrenci.soyad);
   
    		printf("\n ��renci TC Kimlik No: %s", ogrenci.tc);
   
			printf("\n ��renci Telefon Numaras�: %s", ogrenci.telefon);

			printf("\n *******************************************************");
    		
			printf("\n Kayd� Silmek �stedi�inizden Eminseniz E veya e'yi Tu�lay�n�z? ");
   
			getchar();
			scanf("%c",&secim);
   
   			if(secim=='e'|| secim=='E'){
			   bulundu = 1;  // silmek istiyorsa gecici dosyaya bu kayd� kaydetmeyecek di�er kay�tlar� oraya kopyalayacak
			   printf("\n ��rencinin Kayd� Silinmi�tir....");
			}
			
		}else{
        	fprintf(gecici_dosya, "%s %s %s %s %d\n", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
			}
    }
   	
	fclose(dosya);
    fclose(gecici_dosya);  //dosyalar kapat�l�yor.

    if (bulundu==1) {
        remove("ogrenciKayitlari.txt");  //dosyay� sil
        rename("geciciDosya.txt", "ogrenciKayitlari.txt");   //geciciyi ->  ogrenciKayitlari olarak isim de�i�tir
    } else {
        printf("\n Arad���n�z TC kimlik numaras�na sahip ��renci bulunamad�.\n");
        remove("geciciDosya.txt");
    }
}

void guncelle(){

    FILE *dosya = fopen("ogrenciKayitlari.txt", "r");
    FILE *gecici_dosya = fopen("geciciDosya.txt", "w");
   
    int bulundu = 0;
    struct Ogrenci ogrenci;
   
    char aranan_tc[12];
   
    printf("\nKayd�n� G�ncellemek �stedi�iniz ��rencinin TC Numaras�n� Giriniz: ");
    scanf("%s", aranan_tc);
   

    while (fscanf(dosya, "%s %s %s %s %d", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, &ogrenci.no) != EOF) {
   
        if (strcmp(ogrenci.tc, aranan_tc) == 0) { //e�itse 0 de�erini d�nd�r�r

			bulundu = 1;
       
        	printf("\n---------- Kayd� Bulunan  ��rencinin Bilgileri---------- ");

			printf("\n ��renci Ad�: %s" , ogrenci.ad);
   
    		printf("\n ��renci Soyad�: %s", ogrenci.soyad);
   
    		printf("\n ��renci TC Kimlik No: %s", ogrenci.tc);
   
			printf("\n ��renci Telefon Numaras�: %s", ogrenci.telefon);

    		printf("\n ��renci Numaras� : %d", ogrenci.no);
       
	//-----------------------------------------------------------------
       
			printf("\n :.....��rencinin Yeni Bilgilerini Giriniz...... \n");
           
        	printf("\n ��renci Ad�n� Giriniz: ");
    		scanf("%s",&ogrenci.ad);
   
    		printf("\n ��renci Soyad� Giriniz: ");
    		scanf("%s",&ogrenci.soyad);
   
    		printf("\n ��renci TC Kimlik No Giriniz: ");
    		scanf("%s",&ogrenci.tc);
   
    		printf("\n ��renci Telefonu Giriniz: ");
    		scanf("%s",&ogrenci.telefon);

    //--------------------------telefon kontrol--------------------------
   
    		int telefonUzunluk=strlen(ogrenci.telefon);
   
    		while(telefonUzunluk !=11){
    			printf("\n ��renci Telefonu Hatal� Tekrar Giriniz: ");
    			scanf("%s",&ogrenci.telefon);
    			telefonUzunluk=strlen(ogrenci.telefon);
			}

	//--------------------------tc kontrol--------------------------

			int tcUzunluk=strlen(ogrenci.tc);

			int sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';

			int ilkBasamak =ogrenci.tc[0] - '0';
			
			do{  
				
				if(tcUzunluk !=11){

					printf("\n Girilen TC 11 Basamakl� De�il ");
					printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
    				scanf("%s",&ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    				ilkBasamak =ogrenci.tc[0] - '0';
   
				}
				
				if(sonBasamak %2){

					printf("\n Girilen TC nin Son Basama�� 0-2-4-6-8 de�erinde olmal�");
					printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
    				scanf("%s",&ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
    				ilkBasamak =ogrenci.tc[0] - '0';
				}
				
				if(ilkBasamak == 0){

					printf("\n Girilen TC nin �lk Basama�� 0 Olamaz");
					printf("\n ��renci TC Kimlik No Tekrar Giriniz: ");
					scanf("%s",&ogrenci.tc);
    				tcUzunluk=strlen(ogrenci.tc);
    				sonBasamak = ogrenci.tc[tcUzunluk-1] - '0';
					ilkBasamak =ogrenci.tc[0] - '0';
				}  

			}while(tcUzunluk !=11 || sonBasamak %2  ||ilkBasamak!=0);

//--------------------------��renci no atama--------------------------

			// ogrenci.no = numara();   kay�t g�ncellemede numara de�i�meyecek ayn� kalacak


			printf("\n---------- Kay�t Edilen ��rencinin Bilgileri---------- ");

			printf("\n ��renci Ad�: %s" , &ogrenci.ad);
   
    		printf("\n ��renci Soyad�: %s", &ogrenci.soyad);
   
    		printf("\n ��renci TC Kimlik No: %s", &ogrenci.tc);
   
			printf("\n ��renci Telefon Numaras�: %s", &ogrenci.telefon);

    		printf("\n ��renci Numaras� : %d", &ogrenci.no);
   
    		fprintf(gecici_dosya, "%s %s %s %s %d\n", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
       
    	} else {
    		
				fprintf(gecici_dosya, "%s %s %s %s %d\n", ogrenci.ad, ogrenci.soyad, ogrenci.tc, ogrenci.telefon, ogrenci.no);
            //buray� tc bulununcaya kadar olan kay�tlar� ve bulunduktan sonras�n� gecici dosyaya kay�t etmek i�in yazd�m
        }
    }

    fclose(dosya);
    fclose(gecici_dosya);

    if (bulundu) {
        remove("ogrenciKayitlari.txt");  //dosyay� sil
        rename("geciciDosya.txt", "ogrenciKayitlari.txt");   //geciciyi ->  ogrenciKayitlari olarak isim de�i�tir
    } else {
        printf("Arad���n�z TC kimlik numaras�na sahip ��renci bulunamad�.\n");
        remove("geciciDosya.txt");
    }
}



void listele(){

	FILE *dosya = fopen("ogrenciKayitlari.txt", "r"); // okuma modunda a��l�r
   
    int i, sayac=0;

    char satir[100]; // Okunan sat�r� tutmak i�in bir tampon ol�turuldu
    
	while (fgets(satir, sizeof(satir), dosya) != NULL) {
        // Sat�r� bo�lu�a g�re b�lelim
        char *kelime = strtok(satir, " \t\n");

        // B�l�nm�� kelimeleri yazd�ral�m
        while (kelime != NULL) {
        	printf("---------- %d . ��rencinin Bilgileri ----------------\n", sayac+1);
        	for(i=0;i<5;i++){
        		if(i==0){
        			printf("Ad�: %s\n", kelime);
        			kelime = strtok(NULL, " \t\n");
				}else if(i==1){
					printf("Soyad�: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");
				}else if(i==2){
					printf("TC: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");
				}else if(i==3){
					printf("Telefon: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");
				}else if(i==4){
					printf("Numara: %s\n", kelime);
					kelime = strtok(NULL, " \t\n");							
				}
			}
        	sayac++;
    	}
    }    
    
	printf("\n-----------------------------------------------------\n Sistemde %d ��renci Kayd� Bulunmaktad�r... \n-----------------------------------------------------\n",sayac);
	
	fclose(dosya);
}

void menu(){

printf("\n!!!!!! T�rk�e Karakter Kullanmay�n�z !!!!!!");
printf("\n*------------------Men�-------------------*");
printf("\n| ��renci Eklemek     ��in 1              |");
printf("\n| ��renci Silmek      ��in 2              |");
printf("\n| ��renci G�ncellemek ��in 3              |");
printf("\n| ��renci Listesi     i�in 4'� tu�lay�n�z |");
printf("\n*-----------------------------------------*");
}

int main()
{
	setlocale(LC_ALL, "Turkish");
	srand(time(NULL));

	char secim;
	int islem;

	do{
		menu();
		printf("\n Yapmak �stedi�iniz ��lemi Se�iniz:");
    	scanf("%d",&islem);
       
		switch(islem){
        	case 1:
        		ekle();
         	   	break;
       		case 2:
     			sil();
     			break;
        	case 3:
            	guncelle();
        	    break;
        	case 4:
            	listele();
            	break;
        	default:
            	printf("Hatal� Giri� Yapt�n�z");
    	}
    
		printf("\n------------------------------------\n");

		printf("\nMen�  ��in E \n��k�� ��in H: ");
		getchar();
		scanf("%c",&secim);
	}while(secim == 'e' || secim == 'E');
	return 0;
}
