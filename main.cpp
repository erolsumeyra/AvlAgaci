#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
using namespace std;
//Dugum sinifini tanimlariz...
class Dugum{
	public:
		int numara;
		string ad;
		string soyad;
		string bolum;
		Dugum* solDugum;
		Dugum* sagDugum;
}*kok;
//AvlAgaci sinifini tanimlariz...
class AvlAgaci{
	public:
		int yukseklik(Dugum*);
		int fark(Dugum*);
		Dugum *sag_sag(Dugum*);
		Dugum *sol_sol(Dugum*);
		Dugum *sol_sag(Dugum*);
		Dugum *sag_sol(Dugum*);
		Dugum* denge(Dugum*);
		Dugum* ekle(Dugum*,int numarasi);
		void listele(Dugum*,int);
		void oncekok(Dugum*);
		void ickok(Dugum*);
		void sonrakok(Dugum*);
		AvlAgaci(){
			kok=NULL;
		}
};
int main(int argc, char** argv) {
	int secim,eleman;
	AvlAgaci avl;
	while(1)
	{
		cout<<"\n---------------------"<<endl;
        cout<<"AVL Agaci Uygulamasi"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Agaca Eleman Ekleme"<<endl;
        cout<<"2.Dengeli Avl Agacini Listeleme"<<endl;
        cout<<"3.Ickok"<<endl;
        cout<<"4.Oncekok"<<endl;
        cout<<"5.Sonrakok"<<endl;
        cout<<"6.Cikis"<<endl;
        cout<<"Secimini gir: ";
        cin>>secim;
        switch(secim)
        {
        	case 1:
        		cout<<"Eklenecek elemani giriniz: "<<endl;
        		cin>>eleman;
        		kok=avl.ekle(kok,eleman);
        		break;
        	case 2:
        		if(kok==NULL)
        		{
        			cout<<"AVL agaci bos"<<endl;
        			continue;
				}
				cout<<"Dengeli AVL agaci:"<<endl;
					avl.listele(kok,1);
				break;
        	case 3:
        		cout<<"Ickok:"<<endl;
        		avl.ickok(kok);
        		break;
        	case 4:
        		cout<<"Oncekok:"<<endl;
        		avl.oncekok(kok);
        		break;
        	case 5:
        		cout<<"Sonrakok:"<<endl;
        		avl.sonrakok(kok);
        		cout<<endl;
        		break;
        	case 6:
        	exit(1);
			break;
			default:
			cout<<"Yanis secim yaptiniz..."<<endl;	
		}
	}
	return 0;
}
//Avl agacinin yuksekliðini kontrol etmek icin fonksiyonumuzu yaziyoruz...
int AvlAgaci::yukseklik(Dugum *gecici)
{
	int y=0;
	if(gecici!=NULL)
	{
		int sag_yukseklik=yukseklik(gecici->sagDugum);
		int sol_yukseklik=yukseklik(gecici->solDugum);
		int max_yukseklik=max(sol_yukseklik,sag_yukseklik);
		y=max_yukseklik+1;
	}
	return y;
}
//Avl agacindaki dengeyi kontrol etmek icin fonksiyonumuzu yaziyoruz...
int AvlAgaci::fark(Dugum *gecici)
{
	int sol_yukseklik=yukseklik(gecici->solDugum);
	int sag_yukseklik=yukseklik(gecici->sagDugum);
	int denge=sol_yukseklik-sag_yukseklik;
	return denge;
}
//Avl agacinin sag-sag denge problem kontrolunu yazariz...
Dugum *AvlAgaci::sag_sag(Dugum *ata)
{
	Dugum *gecici;
	gecici=ata->sagDugum;
	ata->sagDugum=gecici->solDugum;
	gecici->solDugum=ata;
}
//Avl agacinin sol-sol denge problem kontrolunu yazariz...
Dugum *AvlAgaci::sol_sol(Dugum *ata)
{
	Dugum *gecici;
	gecici=ata->sagDugum;
	ata->solDugum=gecici->sagDugum;
	gecici->sagDugum=ata;
}
//Avl agacinin sol-sag denge problem kontrolunu yazariz...
Dugum *AvlAgaci::sol_sag(Dugum *ata)
{
	Dugum *gecici;
	gecici=ata->solDugum;
	ata->solDugum=sag_sag(gecici);
	return sol_sol(ata);
}
//Avl agacinin sag-sol denge problem kontrolunu yazariz...
Dugum *AvlAgaci::sag_sol(Dugum *ata)
{
	Dugum *gecici;
	gecici=ata->sagDugum;
	ata->sagDugum=sol_sol(gecici);
	return sag_sag(ata);
}
//Avl agacinin denge durumunu yazariz...
Dugum *AvlAgaci::denge(Dugum *gecici)
{
	int dengeleme=fark(gecici);
	if(dengeleme>1)
	{
		if(fark(gecici->solDugum)>0)
		gecici=sol_sol(gecici);
		else
		gecici=sol_sag(gecici);
	}
	else if(dengeleme<-1)
	{
		if(fark(gecici->sagDugum)>0)
		gecici=sag_sol(gecici);
		else
		gecici=sag_sag(gecici);
	}
	return gecici;
}
//Avl agacina ekleme fonkiyounu yazariz...
Dugum *AvlAgaci::ekle(Dugum*,int numarasi)
{
	if(kok==NULL)
	{
		kok=new Dugum;
		kok->numara=numarasi;
		kok->sagDugum=NULL;
		kok->solDugum=NULL;
		return kok;
	}
	else if(numarasi<kok->numara)
	{
		kok->solDugum=ekle(kok->solDugum,numarasi);
		kok=denge(kok);
	}
	else if(numarasi>=kok->numara)
	{
		kok->sagDugum=ekle(kok->sagDugum,numarasi);
		kok=denge(kok);
	}
	return kok;
}
//Avl agacinda listeleme yapmak icin fonksiyonumuzu yazariz...
void AvlAgaci::listele(Dugum *goster,int seviye)
{
	int i;
	if(goster!=NULL)
	{
		listele(goster->sagDugum,seviye+1);
		cout<<"\n";
		if(goster==kok)
		cout<<"Kok-> ";
		for(i=0;i<seviye&&goster!=kok;i++)
		cout<<"	    ";
		cout<<goster->numara;
		listele(goster->solDugum,seviye+1);
	}
}
//Avl agacinda oncekok gezimi yazarýz...
void AvlAgaci::oncekok(Dugum *agac)
{
	if(agac==NULL)
	return;
	cout<<agac->numara<<" ";//<<agac->ad<<" "<<agac->soyad<<" "<<agac->bolum<<" ";
	oncekok(agac->solDugum);
	oncekok(agac->sagDugum);
}
//Avl agacinda ickok gezimi yazariz...
void AvlAgaci::ickok(Dugum *agac)
{
	if(agac==NULL)
	return;
	ickok(agac->solDugum);
	cout<<agac->numara<<" ";//<<agac->ad<<" "<<agac->soyad<<" "<<agac->bolum<<" ";
	ickok(agac->sagDugum);
}
//Avl agacinda sonrakok gezimi yazariz...
void AvlAgaci::sonrakok(Dugum *agac)
{
	if(agac==NULL)
	return;
	sonrakok(agac->solDugum);
	sonrakok(agac->sagDugum);
	cout<<agac->numara<<" ";//<<agac->ad<<" "<<agac->soyad<<" "<<agac->bolum<<" ";
}
