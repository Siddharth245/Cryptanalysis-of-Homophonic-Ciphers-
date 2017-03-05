// ConsoleApplication14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<map>
#include<time.h>
#include<vector>
#include<fstream>
#include<sstream>
#define NUM_SENTENCE 10

using namespace std;

//Structure to store the position of the characters that have unique keys
struct positions {
	vector<int> bc, jc, kc, qc, vc, xc, zc;
	vector<int> posb, posj, posk, posq, posv, posx, posz;

};

class Dictionary {

	vector<string> words;

	map<int, vector<string>> length_map;

public:
	string wordar[NUM_SENTENCE][100];
	
	int countw[10];
	Dictionary(string plaintextName)
	{
		build_wordar(plaintextName);
	}

	
	//Build a dictionary based on the plaintext dile
	void build_wordar(string plaintextName)
	{
		ifstream plaintext(plaintextName); //Open the file
		string word,line;
		int count=-1,i=0,c=0;
		int no=0;
		if (!plaintext)						//Check if file is valid
			cout << "error opening file \n";

		
		int k = 0;
		while (getline(plaintext, line)) {
			stringstream linestream(line);
			count = 0;
			
			if (line.empty()) {
				continue;
			}
			else {
				while (linestream >> word)				//read it word by word and store in respective sentence
				{
					wordar[c][count] = word;
					 
					count++;
				}
				c++;
				countw[k] = count - 1;
				k++;
			}
		}
		
		
		
		plaintext.close();
		


	}
	
};

class Crypto {
	string cipher;
	vector<string> words;
	vector <vector <int>> cipherno;
	string plain_text;
	Dictionary *dict;
	vector <int> word_lengths; //list of all the word lengths of ciphertext
	float total_time;
	clock_t begin_time;

public:

	Crypto(string cipher, string file_name) {

		this->cipher = cipher;
		this->dict = new Dictionary(file_name);
		this->process_Cipher();
		

	}

	//store cipher text word by word
	void process_Cipher() {

		string str;
		int count=0;
		vector<int> cno , indexes;
		for (size_t i = 0; i < this->cipher.size(); i++) {
			if (this->cipher[i] == ' ') {

				this->words.push_back(str);
				this->word_lengths.push_back(count);
				this->cipherno.push_back(cno);
				cno.clear();
				str.clear();
				count = 0;

			}
			else if (this->cipher[i] == ',')
				continue;
			else {
				int d, num = 0;
				while (this->cipher[i] <= '9' && this->cipher[i] >= '0') {
					d = this->cipher[i] - '0'; 
					num = num * 10 + d;  //conversion
					i++;
					//cout << num;
					

				}
				str.push_back('-');
				count++;
				cno.push_back(num);
				i--;
			}
		}

		this->words.push_back(str);
		this->word_lengths.push_back(count);
		this->cipherno.push_back(cno);
		

		this->begin_time = clock();
		indexes=step_one(dict);
		step_two(dict, indexes);

		this->total_time = float(clock() - this->begin_time) / CLOCKS_PER_SEC;
		cout << "\n Total time " << total_time;
	}

	/* First step : find the length of the first cipher text and shortlist the sentences. 
	
	*/
	vector<int> step_one(Dictionary *dict) {
		vector<int> indexes;				//Indexes of shortlisted sentences
		int c = words[0].size();
		for (int i = 0; i < 10; i++)
			
				if (dict->wordar[i][0].size() == c)
					indexes.push_back(i);

		return indexes;
			
	}

	//For each sentence in the list of indexes , find the position of the letters with unique keys
	void step_two(Dictionary *d, vector<int> indexes) {
		
		
		
		int pos;
		int count = 0, oc, flag = 0, p;
		for (int i = 0; i < indexes.size(); i++)
		{
			positions *po= new positions();
			
			p = 0;
			count = 0;
			for (int j = 0; j < d->countw[indexes[i]] ; j++) {
				p = 0;
				pos = 0;
				while (p < d->wordar[indexes[i]][j].size()) {
					if (d->wordar[indexes[i]][j][p] == 'b')
					{

						flag = 1;
						po->posb.push_back(j);
						po->bc.push_back(p);
						p++;

					}
					else if (d->wordar[indexes[i]][j][p] == 'j')
					{

						flag = 1;
						po->posj.push_back(j);
						po->jc.push_back(p);
						d->wordar[indexes[i]][j];
						p++;

					}
					else if (d->wordar[indexes[i]][j][p] == 'k')
					{

						flag = 1;
						po->posk.push_back(j);
						po->kc.push_back(p);
						d->wordar[indexes[i]][j];
						p++;

					}
					else if (d->wordar[indexes[i]][j][p] == 'q')
					{

						flag = 1;
						po->posq.push_back(j);
						po->qc.push_back(p);
						d->wordar[indexes[i]][j];
						p++;

					}
					else if (d->wordar[indexes[i]][j][p] == 'v')
					{

						flag = 1;
						po->posv.push_back(j);
						po->vc.push_back(p);
						d->wordar[indexes[i]][j];
						p++;

					}
					else if (d->wordar[indexes[i]][j][p] == 'x')
					{

						flag = 1;
						po->posx.push_back(j);
						po->xc.push_back(p);
						d->wordar[indexes[i]][j];
						p++;

					}
					else if (d->wordar[indexes[i]][j][p] == 'z')
					{

						flag = 1;
						po->posz.push_back(j);
						po->zc.push_back(p);
						d->wordar[indexes[i]][j];
						p++;

					}
					else
						p++;
				}
				
			}
			flag =step_three(d, po);
 			//check if the sentence has all the characters which have unique key in the correct position
			if (flag == 1) {
				display_sent(indexes[i], d);
				break;
			}
			
			delete po;
		}
		if (flag == 0)
		{
			cout << "Plain Text Not present in dictionary";
		}

		
	}

	//Display the selected sentence.
	void display_sent(int ind, Dictionary *d)
	{
		cout << " \n Our guess for the corresponding plain text is : ";
		for (int i = 0; i < d->countw[ind]; i++) {
			cout << d->wordar[ind][i] << " ";
		}
		cout << "\n";
	}

	//check if the sentence has all the characters which have unique key in the correct position
	int step_three(Dictionary *d,positions *po) {
		int flag = 1;
		int bn = cipherno[po->posb[0]][po->bc[0]];
		
	
		
		for (int i = 0; i < po->posb.size(); i++)
		{
			if (bn == cipherno[po->posb[i]][po->bc[i]]) continue;
			else {
				flag = 0;
				break;
			}
		}

		if (flag == 1 && !po->posj.empty()) {
			int jn = cipherno[po->posj[0]][po->jc[0]];
			for (int i = 0; i < po->posj.size(); i++)
			{
				if (jn == cipherno[po->posj[i]][po->jc[i]]) continue;
				else {
					flag = 0;
					break;
				}
			}
		}

		if (flag == 1 && !po->posk.empty()) {
			int kn = cipherno[po->posk[0]][po->kc[0]];
			for (int i = 0; i < po->posk.size(); i++)
			{
				if (kn == cipherno[po->posk[i]][po->kc[i]]) continue;
				else {
					flag = 0;
					break;
				}
			}
		}

		if (flag == 1 && !po->posq.empty()) {
			int qn = cipherno[po->posq[0]][po->qc[0]];
			for (int i = 0; i < po->posq.size(); i++)
			{
				if (qn == cipherno[po->posq[i]][po->qc[i]]) continue;
				else {
					flag = 0;
					break;
				}
			}
		}

		if (flag == 1 && !po->posv.empty()) {
			int vn = cipherno[po->posv[0]][po->vc[0]];
			for (int i = 0; i < po->posv.size(); i++)
			{
				if (vn == cipherno[po->posv[i]][po->vc[i]]) continue;
				else {
					flag = 0;
					break;
				}
			}
		}

		if (flag == 1 && !po->posx.empty()) {
			int xn = cipherno[po->posx[0]][po->xc[0]];
			for (int i = 0; i < po->posx.size(); i++)
			{
				if (xn == cipherno[po->posx[i]][po->xc[i]]) continue;
				else {
					flag = 0;
					break;
				}
			}
		}

		if (flag == 1 && !po->posz.empty()) {
			int zn = cipherno[po->posz[0]][po->zc[0]];
			for (int i = 0; i < po->posz.size(); i++)
			{
				if (zn == cipherno[po->posz[i]][po->zc[i]]) continue;
				else {
					flag = 0;
					break;
				}
			}
		}
		if (flag == 1)
		{
			return 1;
		}
		else
			return 0;
	

	}


};

int main()
{
	string ciphertext;
	string plaintextName("C:/Users/balaj/Desktop/plaintext_dictionary.txt");
	cout << "Enter cipher text : ";
	getline(cin, ciphertext);

	Crypto analyse(ciphertext, plaintextName);
	system("pause");

    return 0;
}

