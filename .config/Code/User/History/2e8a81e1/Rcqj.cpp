#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct banda{
	char nome[62];
	int numAlbuns;
	float numVendas;
	int numMembrosFund;
	char genero[30];
	};
	
int menu() {
    int opcao;

        cout << "Menu:\n";
        cout << "0 - Acabar\n";
        cout << "1 - Listar\n";
        cout << "2 - Redimensionar\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        


    return opcao;
}

	
banda* aumentarVetor(banda vetor[], int &qtd, int  &acresc){
	qtd = qtd + acresc;
    banda *temp = new banda[qtd];
    copy(vetor, &vetor[qtd - acresc], temp);
    delete[] vetor;
	return temp;
	}
	
void imprimir(banda vetor[]){
	int tam = sizeof(vetor);
	for(int i =0; i<tam; i++){
		cout<<vetor[i].nome<<" "<<vetor[i].numAlbuns<<" "<<vetor[i].numVendas<<" milhoes "<<vetor[i].numMembrosFund<<" "<<vetor[i].genero<<endl;
		}
	}
int main(){
	ifstream arquivocsv("westview.csv");
	
	int tam,qtd;
	arquivocsv>>tam;
	banda *bandas = new banda[tam];
	arquivocsv.ignore();
	for(int i =0; i<tam;i++){
		arquivocsv.getline(bandas[i].nome,62,',');
		char lixo;
		arquivocsv>>bandas[i].numAlbuns;
		arquivocsv>>lixo;
		arquivocsv>>bandas[i].numVendas;
		arquivocsv>>lixo;
		arquivocsv>>bandas[i].numMembrosFund;
		arquivocsv>>lixo;
		arquivocsv.getline(bandas[i].genero, 30);
		
		}
	 
	 int opcao;
	 opcao << menu();
	 switch (opcao) {
            case 0:
                cout << "Encerrando o programa...\n";
                break;
            case 1:
                imprimir(bandas);
                break;
            case 2:
                cout << "Opcao Redimensionar selecionada.\n";
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
     
	 for(int i = qtd; i<tam;i++){
		arquivocsv.getline(bandas[i].nome,62,',');
		char lixo;
		arquivocsv>>bandas[i].numAlbuns;
		arquivocsv>>lixo;
		arquivocsv>>bandas[i].numVendas;
		arquivocsv>>lixo;
		arquivocsv>>bandas[i].numMembrosFund;
		arquivocsv>>lixo;
		arquivocsv.getline(bandas[i].genero, 30);
		}
		
return 0;
}