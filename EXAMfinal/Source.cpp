#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<cstring>
using namespace std;
class Dictionary {
public:

	//Default Constructor    
	Dictionary() {}
	//opens file and assign all words into set<string> words;   
	Dictionary(string file)
	{
		fstream data;
		data.open("words.txt", ios::in | ios::binary);
		string buffer;
		data >> buffer;
		while (!data.eof())
		{
			words.insert(buffer);
			data >> buffer;
		}
		data.close();
	}
	//Destructor    
	~Dictionary() {}
	// return a random word (without repeated letters)     
	string BringValidWord()
	{
		string buffer;
		int a;
		TestLegalSecretWord();
		a = rand() % secrets.size();
		buffer = secrets[a];
		return buffer;
	}
	// check if word is in Dictionary   
	bool IsWordValid(string word)
	{
		bool flag;
		string temp;
		for (set<string>::iterator it = words.begin(); it != words.end(); ++it)
		{
			temp = *it;
			if (temp == word)
			{
				flag = 1;
				break;
			}
			else
				flag = 0;
		}
		return flag;
	}
private:
	// test if n. word has only unique letters   
	void TestLegalSecretWord()
	{
		string temp;
		int i, j;
		int k = 0;
		bool flag = 0;
		for (set<string>::iterator it = words.begin(); it != words.end(); ++it)
		{
			flag = 0;
			temp = *it;
			for (i = 0; i < temp.length(); i++)
			{
				for (j = 0; j < temp.length(); j++)
				{
					if (temp[i] == temp[j] && i != j)
					{
						flag = 1;
					}
				}

			}
			if (flag == 0)
			{
				secrets.push_back(temp);

			}

		}
	}
	set<string> words;
	vector<string> secrets;
};
class Words : public Dictionary {
public:
	 Words() {} //Default Constructor
	~Words() {} //Destructor
	// public interface to play game of Words
	//it may call from main() using followings;
	//main(){
	//}
	void playgame(Words &)
	{
		string file, tahmin, secret;
		Dictionary a(file);
		Words b;
		int yer, harf;
		bool flag1;
		secret = a.BringValidWord();
		cout << "Bilbakalim Oyununa Hosgeldiniz:" << endl << "5 harften olusan bir kelime tuttum. " << endl << endl;
		numguesses = 0;
		while (1)
		{
			cout << endl << "tahmininiz nedir?: ";
			cin >> tahmin;
			if (tahmin.size() < 5)
				cout << "Lutfen 5 harfli bir kelime giriniz!" << endl;
			else
			{
				if (tahmin == "xxxxx")
				{
					cheated = 1;
					numguesses++;
				}
				if (cheated == 1)
				{
					cout << "Ipucu: Gizli Kelime: " << secret << endl;
					cheated = 0;
				}
				else
				{
					flag1 = a.IsWordValid(tahmin);
					if (flag1 == 0)
					{
						cout << "aradiginiz kelime sozlukte yok!" << endl;
					}
					if (flag1 == 1)
					{
						harf = b.countofMatchLetters(tahmin, secret);
						yer = b.countofTruePlaceLetters(tahmin, secret);
						cout << "Eslesen harf sayisi: " << harf << endl;
						cout << "Eslesen harflerin dogru konumu: " << yer << endl;
						numguesses++;
					}

				}
				if (b.countofTruePlaceLetters(tahmin, secret) == 5)
					break;
			}
			
		}
		cout << endl << "Bildiniz! " << numguesses << " tahminde dogru sonuca ulastiniz! " << endl;
	}
private:
	// count functions compare string param with the secret word
	// find common letters in any order
	int countofMatchLetters(string tahmin, string secret)
	{
		int sayi = 0, sayi2 = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (tahmin[j] == secret[i])
				{
					sayi++;
				}
			}
			if (sayi > 0)
				sayi2++;

			sayi = 0;
		}
		return sayi2;
	}
	// find common letters in place
	int countofTruePlaceLetters(string tahmin, string secret)
	{
		int i, say = 0;
		for (i = 0; i < 5; i++)
		{
			if (tahmin[i] == secret[i])
				say++;
		}
		return say;
	}
	// track number of guesses used
	int numguesses;
	// flag set to true if cheat code is used
	bool cheated;
	// word to guess
	string secret;
};
void main()
{
	srand(time(NULL));
	Words W;
	W.playgame(W);

	system("pause");
}