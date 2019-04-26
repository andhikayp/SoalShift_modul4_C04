# SoalShift_modul4_C04

##  No. 1
Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

```
qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0
```

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

Penjelasan :

- Untuk melakukan Enkripsi dengan Caesar Cipher, maka karakter pada character list akan digeser ke kanan sebanyak sekian (dalam kasus ini sebanyak 17 karakter). Hal tersebut dilakukan dengan mencari indeks pada character list yang menyimpan karakter yang akan di encrypt. metode tersebut dapat diselesaikan dengan loop menggunakan 2 for. Dengan i sebagai indeks dari karakter yang dicari, dan j sebagai indeks karakter tersebut pada character list. kecuali untuk karakter "/" karakternya tidak akan berubah untuk menyatakan path. Adapun dapat diselesaikan menggunakan kodingan berikut :

```
void caesarCipherEnc(char text[])
{
	int i, j;
	char charlist[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	for(i=0; i<strlen(text); i++)
	{
		if(text[i]=='/')
			text[i]=text[i];
		else
		{
			for(j=0; j<94; j++)
			{
				if(text[i] == charlist[j])
				{
					text[i] = charlist[(j+17)%94];				
					break;
				}
			}
		}
	}
}
```

- Untuk melakukan Decrypt, sama seperti Encrypt namun digeser kembali ke kiri sebanyak 17 karakter pada character list. adapun caranya seperti berikut:

```
void caesarCipherDec(char text[])
{
	int i, j;
	char charlist[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	for(i=0; i<strlen(text); i++)
	{
		if(text[i]=='/')
			text[i]=text[i];
		else
		{
			for(j=0; j<94; j++)
			{
				if(text[i] == charlist[j])
				{
					text[i] = charlist[(j+94-17)%94];				
					break;
				}
			}
		}
	}
}
```

- Untuk pembuatan File System tersebut menggunakan Fuse, kami menggunakan template pada sesi lab modul4.
