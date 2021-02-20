#include<stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
struct kelimeListesi
{
    char kelime[30];
    int kelimeAdedi;
    struct kelimeListesi *sonrakiDugum;
};

struct kelimeListesi *ilk=NULL;
struct kelimeListesi *son=NULL;

void eklemeNoktasi(char ekleneceKelime[30],int adet)
{
    struct kelimeListesi *yeniDugum=(struct kelimeListesi*)malloc(sizeof(struct kelimeListesi));
    strcpy(yeniDugum->kelime,ekleneceKelime);
    yeniDugum->kelimeAdedi=adet;
    if(ilk==NULL)
        {
            ilk=yeniDugum;
            son=yeniDugum;
            son->sonrakiDugum=NULL;
        }
    else
        {
            int varMi=0;
            struct kelimeListesi *dolas=ilk;
            while(!dolas==NULL)
                {
                    if(strcmp(dolas->kelime,ekleneceKelime)==0)
                        {
                            varMi=1;
                            break;
                        }
                    dolas=dolas->sonrakiDugum;
                }
            if(varMi==0)
                {
                    if((ilk->kelimeAdedi)<=adet)
                        {
                            basaEkle(ekleneceKelime,adet);
                        }
                    else if((son->kelimeAdedi)>=adet)
                        {
                            sonaEkle(ekleneceKelime,adet);
                        }
                    else
                        {
                            arayaEkle(ekleneceKelime,adet);
                            //  sonaEkle(ekleneceKelime,adet);
                        }
                }
        }
}
void sonaEkle(char ekleneceKelime[30],int adet)
{
    struct kelimeListesi *yeniDugum=(struct kelimeListesi*)malloc(sizeof(struct kelimeListesi));
    strcpy(yeniDugum->kelime,ekleneceKelime);
    yeniDugum->kelimeAdedi=adet;
    son->sonrakiDugum=yeniDugum;
    son=yeniDugum;
    son->sonrakiDugum=NULL;
}
void basaEkle(char ekleneceKelime[30],int adet)
{
    struct kelimeListesi *yeniDugum=(struct kelimeListesi*)malloc(sizeof(struct kelimeListesi));
    strcpy(yeniDugum->kelime,ekleneceKelime);
    yeniDugum->kelimeAdedi=adet;
    yeniDugum->sonrakiDugum=ilk;
    ilk=yeniDugum;
}
void arayaEkle(char ekleneceKelime[30],int adet)
{
    struct kelimeListesi *yeniDugum=(struct kelimeListesi*)malloc(sizeof(struct kelimeListesi));
    strcpy(yeniDugum->kelime,ekleneceKelime);
    yeniDugum->kelimeAdedi=adet;
    struct kelimeListesi *onceki;
    struct kelimeListesi *kelimeler=ilk;
    while(kelimeler!=NULL)
        {

            if(adet>=(kelimeler->sonrakiDugum->kelimeAdedi))
                {

                    break;
                }
            kelimeler=kelimeler->sonrakiDugum;
        }
    onceki=kelimeler->sonrakiDugum;
    kelimeler->sonrakiDugum=yeniDugum;
    yeniDugum->sonrakiDugum=onceki;
}
void yazdir()
{
    struct kelimeListesi *kelimeler=ilk;
    while(kelimeler!=NULL)
        {
            printf("%s : %d\n",kelimeler->kelime,kelimeler->kelimeAdedi);
            kelimeler=kelimeler->sonrakiDugum;
        }
}
int main()
{
    setlocale(LC_ALL,"turkish");
    FILE *dosya=fopen("text.txt","r");
    char kelime[30];
    if(dosya==NULL)
        {
            printf("Dosya acilamadi...");
        }
    else
        {
            while(!feof(dosya))
                {
                    fscanf(dosya,"%s",&kelime);
                    int adet=adetBul(kelime);
                    eklemeNoktasi(kelime,adet);

                }
            fclose(dosya);
            yazdir();
        }
}

int adetBul(char arananKelime[30])
{
    char kelime[30];
    int say=0;
    FILE *dosya=fopen("text.txt","r");
    while(!feof(dosya))
        {
            fscanf(dosya,"%s",&kelime);
            if(strcmp(kelime,arananKelime)==0)
                {
                    say++;
                }



        }
    return say;
}
