#include <iostream>
#include <fstream> // biblioteca para arquivos
#include <cstdlib> // biblioteca para rand

#define MAX_TEXT 46

using namespace std;

fstream File; // modo para escrever ou ler o arquivo
// ofstream seria para somente escrever no arq
// ifstream seria para somente ler o arq

struct Register{

	int nseq;
	string text; // foi colocado uma restrição para que essa string nao ultrapasse o tamanho 46 (MAX_TEXT)

};

Register * create_heap_file(int n_reg);
string random_string();
void read_random(fstream &f, int nseq);

int main(void){

	Register * r;
	r = create_heap_file(10);

	//File.open("file.txt", ios::app); // ios::app posiciona o cursor no final do arquivo e insere o conteúdo sem substituir oq já possui lá

	read_random(File, 11);

}


Register * create_heap_file(int n_reg){

	Register * r = (Register *) malloc(n_reg * sizeof(Register));
	if(r == NULL){
		cout << "Erro ao criar heap file!" << endl;
		exit(1);
	}

	// Criando e abrindo um arquivo para escrever nele (ios::out)
	// Para adicionar texto ao arquivo, devemos usar ios::out | ios::app
	File.open("file.txt", ios::out);

	// Escrevendo no arquivo
	for(int i = 0; i < n_reg; ++i){
		File << i << " " << random_string() << endl;
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
	f.open("file.txt", ios::in);
	string line;
	if(f.is_open()){

		bool ok = false;

		while(getline(f,line)){

			string aux = "";
			aux += line[0];
			int compare;
			compare = stoi(aux); // função para converter string para int
			if(compare == nseq){
				cout << line << endl;
				ok = true;
				break;
			}
			
		}

		if(!ok){
			cout << "NSEQ nao encontrado!" << endl;
		}

		f.close();

	}else{
		cout << "Falha ao abrir arquivo para leitura!" << endl;
		return;
	}

}