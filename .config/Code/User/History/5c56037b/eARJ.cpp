#include <iostream>
#include <fstream>

using namespace std;

struct banda{
	string nome;
	int numAlbuns;
    bool estaAtiva;
	float numVendas;
	int numMembrosFund;
	string genero;
	};



banda* aumentarVetor(banda vetor[], int &qtd){
	qtd = qtd + 10;
    banda *temp = new banda[qtd];
    copy(vetor, &vetor[qtd - 10], temp);
    delete[] vetor;
	return temp;
	};

void menu(){
    cout<<" 1 - Listar\n";
    cout<<"2 - Redimensionar\n"; 
    cout<<"0 - Encerrar\n";
};

void inserir(banda vetor[], int &qtd) {
    string nome, genero;
    int albuns, numMembrosFund;
    int ativa;
    float vendas;

    cout << "Nome da banda?" << endl;
    cin.ignore(); // Ignora o \n deixado pelo cin anterior
    getline(cin, nome);

    cout << "Numero de albuns?" << endl;
    cin >> albuns;
    while (albuns < 0) {
        cout << "So numeros maiores ou iguais a 0" << endl;
        cout << "Numero de albuns?" << endl;
        cin >> albuns;
    }

    cout << "Quantos albuns vendeu? (em milhões)" << endl;
    cin >> vendas;
    while (vendas < 0) {
        cout << "So numeros maiores ou iguais a 0" << endl;
        cout << "Quantos albuns vendeu? (em milhões)" << endl;
        cin >> vendas;
    }

    cout << "Esta ativa? 0 - Não  1 - Sim" << endl;
    cin >> ativa;
    while (ativa != 0 && ativa != 1) {
        cout << "Apenas 1 ou 0" << endl;
        cout << "Esta ativa? 0 - Não  1 - Sim" << endl;
        cin >> ativa;
    }

    cout << "Quantos membros fundadores?" << endl;
    cin >> numMembrosFund;
    while (numMembrosFund < 0) {
        cout << "So numeros maiores que 0" << endl;
        cout << "Quantos membros fundadores?" << endl;
        cin >> numMembrosFund;
    }

    cout << "Qual o genero da banda? (Pode conter espaços)" << endl;
    cin.ignore(); // Ignora o \n deixado pelo cin anterior
    getline(cin, genero);

    vetor[qtd].nome = nome;
    vetor[qtd].numAlbuns = albuns;
    vetor[qtd].estaAtiva = (ativa == 1);
    vetor[qtd].numVendas = vendas;
    vetor[qtd].numMembrosFund = numMembrosFund;
    vetor[qtd].genero = genero;

    qtd++;
};



int lerBandasDoCSV(const char* nomeArquivo, banda bandas[] ) {
    ifstream arquivocsv(nomeArquivo);
    const int maxBandas = 40;
    int i = 0;
    string cabessario;
    getline(arquivocsv, cabessario);
    
    while (i < maxBandas && !arquivocsv.eof()) { //.eof retorna true se o arquivo acabou
        getline(arquivocsv, bandas[i].nome, ',');
        char lixo;
        arquivocsv >> bandas[i].numAlbuns;
        arquivocsv >> lixo;
        arquivocsv >> bandas[i].numVendas;
        arquivocsv >> lixo;
        arquivocsv >> bandas[i].numMembrosFund;
        arquivocsv >> lixo;
        getline(arquivocsv, bandas[i].genero);
        i++;
    }

    arquivocsv.close();
    return i; //retorna a qtd de bandas gravadas
};

void listar(banda vetor[], int qtd_bandas){
	int tam = qtd_bandas;
	for(int i =0; i<tam; i++){
		cout<<vetor[i].nome<<" "<<vetor[i].numAlbuns<<" "<<vetor[i].numVendas<<" milhoes "<<vetor[i].numMembrosFund<<" "<<vetor[i].genero<<endl;
		}
	};


void ordenarPorAlbuns(banda vet[], int qtd){
     for(int i = 0; i<qtd; i++){
         Banda index = vet[i];
         int j = i -1;
         while(j>=0) and vet[j].numAlb

     }
    
};

int main(){
    int op, tam, qtd_bandas;
    tam = 50;
	banda *bandas = new banda[tam];
    qtd_bandas = lerBandasDoCSV("westview.csv", bandas);
    cout<<bandas[1].nome;
    do{
        menu();
        cin>>op;
        switch(op){
            case 0:
                cout<<"Tchau!";
                break;
            case 1:
                listar(bandas, qtd_bandas);
                break;
            default:
                cout<<"Opção inválida\n";
        }
    }while(op != 0);
    return 0;
}