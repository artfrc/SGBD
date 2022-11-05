#include <iostream>
#include <fstream> // biblioteca para arquivos
#include <cstdlib> // biblioteca para rand
#include <vector>

#define MAX_TEXT 46

using namespace std;

struct Register{

	int nseq;
	string text; // foi colocado uma restrição para que essa string nao ultrapasse o tamanho 46 (MAX_TEXT)

	Register(){}
	Register(int nseq, string text):nseq(nseq), text(text){};

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

int main(void){

	int op = -1, n_register;
	bool created_register = false;
	string text;

	while(op != 0){

		cout << "[1]. Create heap file\n";
		cout << "[2]. Read random\n";
		cout << "[3]. Insert end\n";
		cout << "[4]. Update random\n";
		cout << "[0]. Exit\n";

		cout << ">> Choose an option: ";
		cin >> op;

		if(op >= 0 && op <= 4 && op != 1 && op != 0 && !created_register){
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
					read_random(File,n_register);					
					
					break;

				case 3:
					isrt_at_end(File);

					break;

				case 4:
					cout << ">> Enter registration number: ";
					cin >> n_register;
					text = random_string();
					update_random(File,n_register,text);
					
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



	//File.open("file.dat", ios::app); // ios::app posiciona o cursor no final do arquivo e insere o conteúdo sem substituir oq já possui lá

/*
	File.open("file.dat", ios::in|ios::ate);
	if(File.is_open()){
		cout << "Arquivo abriu\n";
		
		cout << File.tellg() << endl;

		File.close();
	}
*/
}


void create_heap_file(int n_reg){

	/*Register * r = (Register *) malloc(n_reg * sizeof(Register));
	if(r == NULL){
		return NULL;
	}*/

	// Criando e abrindo um arquivo para escrever nele (ios::out)
	// Para adicionar texto ao arquivo, devemos usar ios::out | ios::app
	File.open("file.dat", ios::out);

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

	f.open("file.dat", ios::app|ios::binary);
	if(f.is_open()){
		//f.seekg((sizeof(char)*(MAX_TEXT + 2))*nseq, ios::beg);
		f.seekp((sizeof(char)*(MAX_TEXT + 2))*nseq);
		f.write(text.data(),text.size());
		f.close();
		cout << ">> Updated successfully\n\n";
	}else{
		cout << ">> Failed to open file for reading" << endl;
		return;
	}

}