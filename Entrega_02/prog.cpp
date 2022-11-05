#include <iostream>
#include <fstream> // biblioteca para arquivos
#include <cstdlib> // biblioteca para rand
#include <vector>
#include <ctime>

#define MAX_TEXT 46

using namespace std;

struct Register{

	long long int nseq;
	string text; // foi colocado uma restrição para que essa string nao ultrapasse o tamanho 46 (MAX_TEXT)

	Register(){}
	Register(long long int nseq, string text):nseq(nseq), text(text){};

};

vector<Register> r;
fstream File; // modo para escrever ou ler o arquivo
// ofstream seria para somente escrever no arq
// ifstream seria para somente ler o arq

void create_heap_file(int n_reg);
string random_string();
void read_random(fstream &f, int nseq);
void isrt_at_end(fstream &f);
void update_random(fstream &f, int nseq, string text);
void delete_random(fstream &f, int nseq);
void sequential_reading(fstream &f, int n);
void random_access(fstream &f, int n);

int main(void){

	int op = -1;
	long long int n_register;
	bool created_register = false;
	string text;

	while(op != 0){

		cout << "[1]. Create heap file\n";
		cout << "[2]. Read random\n";
		cout << "[3]. Insert end\n";
		cout << "[4]. Update random\n";
		cout << "[5]. Delete random\n";
		cout << "[6]. Sequential reading\n";
		cout << "[7]. Random access\n";
		cout << "[0]. Exit\n";

		cout << ">> Choose an option: ";
		cin >> op;

		if(op >= 0 && op <= 5 && op != 1 && op != 0 && !created_register){
			cout << ">> Create heap file first\n\n";
		}else{

			switch(op){

				case 1:
					if(created_register){
						cout << ">> Heap file has already been created\n\n";
					}else{
						cout << ">> Numbers of records: ";
						cin >> n_register;
						create_heap_file(n_register);
						cout << ">> Heap created successfully\n\n";
						created_register = true;
					}

					break;

				case 2:
					cout << ">> Enter registration number: ";
					cin >> n_register;
					read_random(File,n_register-1);					
					
					break;

				case 3:
					isrt_at_end(File);

					break;

				case 4:
					cout << ">> Enter registration number: ";
					cin >> n_register;
					text = random_string();
					update_random(File,n_register-1,text);
					
					break;

				case 5:
					cout << ">> Enter registration number: ";
					cin >> n_register;
					delete_random(File,n_register-1);
					
					break;

				case 6:
					cout << ">> Enter registration number: ";
					cin >> n_register;
					sequential_reading(File,n_register);

					break;

				case 7:
					cout << ">> Enter registration number: ";
					cin >> n_register;
					random_access(File,n_register);

					break;

				case 0:
					r.clear();
					cout << ">> Good bye\n";
					
					break;

				default:
					cout << ">> Invalid option\n\n";

			}

		}

	}

}


void create_heap_file(int n_reg){

	// Criando e abrindo um arquivo para escrever nele (ios::out)
	// Para adicionar texto ao arquivo, devemos usar ios::out | ios::app
	File.open("file.dat", ios::out|ios::binary);

	// Escrevendo no arquivo
	for(int i = 0; i < n_reg; ++i){
		string s = random_string();
		File << s << endl;
		r.push_back(Register(i,s));		
	}

	// Fechando o arquivo
	File.close();

}

string random_string(){

	string s = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	string ans = "";

	int sizeS = s.size();

	while(ans.size() < MAX_TEXT){

		ans += s[rand() % sizeS];

	}

	return ans;

}

void read_random(fstream &f, int nseq){

	if(r.size() < nseq){
		cout << ">> Record does not exist\n\n";
		return;
	}

	// Abrindo meu arquivo no modo de entrada, ou seja, para ler ele (ios::in)
	f.open("file.dat", ios::in);
	string line;
	if(f.is_open()){

		bool ok = false;

		f.seekg((sizeof(char)*(MAX_TEXT + 2))*nseq, ios::beg);
		char a[MAX_TEXT];
		f.read(a, MAX_TEXT);

		a[MAX_TEXT] = 0;
		cout << a << endl;

		f.close();

	}else{
		cout << ">> Failed to open file for reading" << endl;
		return;
	}

}

void isrt_at_end(fstream &f){

	f.open("file.dat", ios::app);
	if(f.is_open()){

		string s = random_string();
		int n = r.size();
		r.push_back(Register(n,s));
		f << s << endl;
		f.close();

	}else{
		cout << ">> Failed to open file for reading" << endl;
		return;
	}

}

void update_random(fstream &f, int nseq, string text){

	if(r.size() < nseq){
		cout << ">> Record does not exist\n\n";
		return;
	}

	f.open("file.dat", ios::out);
	if(f.is_open()){

		for(int i = 0; i < r.size(); i++){
			if(r[i].nseq == nseq){
				r[i].text = text;
			}
			f << r[i].text << endl;
		}
		f.close();
		cout << ">> Updated successfully\n\n";
	}else{
		cout << ">> Failed to open file for reading" << endl;
		return;
	}

}

void delete_random(fstream &f, int nseq){

	if(r.size() < nseq){
		cout << ">> Record does not exist\n\n";
		return;
	}

	r[nseq].nseq = abs(r[nseq].nseq) * (-1); 

	cout << ">> Deleted successfully\n\n";

}

void sequential_reading(fstream &f, int n){


	int valid = 0;
	int pages = 0;
	int cont = 0;
	clock_t t;
	t = clock();
	for(int i = 0; i < r.size(); i++){

		if(r[i].nseq >= 0){
			valid++;
		}
		cont++;
		if(cont == n){
			pages++;
			cont = 0;
		}

	}
	t = clock() - t;
	cout << ">> " << valid << " valid records\n";
	cout << ">> " << pages << " pages\n";
	cout << ">> " << ((float)t) / CLOCKS_PER_SEC << " seconds\n\n"; 

}

void random_access(fstream &f, int n){


	clock_t t;
	t = clock();
	long long int valid = 0;
	long long int not_valid = 0;
	f.open("file.dat", ios::in);
	if(f.is_open()){

		while(n--){

			long long int key = rand() % r.size() - 1;
			if(r[key].nseq >= 0){

				string line;

				bool ok = false;

				f.seekg((sizeof(char)*(MAX_TEXT + 2))*key, ios::beg);
				char a[MAX_TEXT];
				f.read(a, MAX_TEXT);

				a[MAX_TEXT] = 0;
				cout << a << endl;
				valid++;
			}else{
				not_valid++;
			}
		}
		f.close();
	}else{
		cout << ">> Failed to open file for reading" << endl;
		return;
	}
	t = clock() - t;

	cout << ">> Valid: " << valid << endl;
	cout << ">> Not valid: " << not_valid << endl;
	cout << ">> " << ((float)t) / CLOCKS_PER_SEC << " seconds\n\n"; 

}