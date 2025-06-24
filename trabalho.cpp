#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

struct banda
{
    int id;
    char nome[50];
    int numAlbuns;
    bool ativa;
    float numVendas;
    int numMembrosFund;
    char genero[50];
    bool excluido;
};

banda *aumentarVetor(banda vetor[], int &qtd)
{
    int tamAntigo = qtd;
    qtd = qtd + 10;
    banda *temp = new banda[qtd];
    copy(vetor, &vetor[tamAntigo-1], temp);
    delete[] vetor;
    return temp;
};

void main_menu()
{
    cout << "\n1 - Listar\n";
    cout << "2 - Inserir\n";
    cout << "3 - Pesquisar\n";
    cout << "4 - Ordenar\n";
    cout << "5 - Excluir\n";
    cout << "6 - Importar dados de um arquivo .csv\n"; // precisa??
    cout << "7 - Exportar dados para um arquivo .csv\n";
    cout << "8 - Salvar alterações no arquivo binário\n";
    cout << "0 - Encerrar\n";
};

string menu_pesquisa(int &op)
{ //
    string escolhido;
    do
    {
        cout << "Você deseja pesquisar uma banda por: \n";
        cout << "1 - Nome\n";
        cout << "2 - ID\n";
        cout << "0 - Cancelar\n";
        cin >> op;

        switch (op)
        {
        case 0:
            return escolhido;
            break;
        case 1:
            cout << "Informe o nome que deseja pesquisar: " << endl;
            cin >> escolhido;
            return escolhido;
            break;
        case 2:
            cout << "Informe o ID que deseja pesquisar: " << endl;
            cin >> escolhido;
            return escolhido;
            break;
        default:
            cout << "Opção inválida! >:(\n";
        }
    } while (op != 0);
    return "Erro inesperado\n";
}

int menu_ordena()
{
    int op;

    cout << "\nVocê deseja ordenar por: \n";
    cout << "1 - Álbuns\n";
    cout << "2 - ID\n";
    cout << "3 - Nome\n";
    cout << "0 - Cancelar\n";
    cin >> op;

    return op;
}

void inserir(banda vetor[], int &qtd, int &tam)
{
    if (tam == qtd)
    {
        vetor = aumentarVetor(vetor, tam);
    }
    char nome[50], genero[50];
    int albuns, numMembrosFund;
    int ativa;
    float vendas;

    cout << "Nome da banda?" << endl;
    cin.ignore(); // Ignora o \n deixado pelo cin anterior
    cin.getline(nome, 50);

    cout << "Numero de albuns?" << endl;
    cin >> albuns;
    while (albuns < 0)
    {
        cout << "So numeros maiores ou iguais a 0" << endl;
        cout << "Numero de albuns?" << endl;
        cin >> albuns;
    }

    cout << "Quantos albuns vendeu? (em milhões)" << endl;
    cin >> vendas;
    while (vendas < 0)
    {
        cout << "So numeros maiores ou iguais a 0" << endl;
        cout << "Quantos albuns vendeu? (em milhões)" << endl;
        cin >> vendas;
    }

    cout << "Esta ativa? 0 - Não  1 - Sim" << endl;
    cin >> ativa;
    while (ativa != 0 && ativa != 1)
    {
        cout << "Apenas 1 ou 0" << endl;
        cout << "Esta ativa? 0 - Não  1 - Sim" << endl;
        cin >> ativa;
    }

    cout << "Quantos membros fundadores?" << endl;
    cin >> numMembrosFund;
    while (numMembrosFund < 0)
    {
        cout << "So numeros maiores que 0" << endl;
        cout << "Quantos membros fundadores?" << endl;
        cin >> numMembrosFund;
    }

    cout << "Qual o genero da banda? (Pode conter espaços)" << endl;
    cin.ignore(); // Ignora o \n deixado pelo cin anterior
    cin.getline(genero, 50);
    vetor[qtd].id = qtd;
    strcpy(vetor[qtd].nome, nome);
    vetor[qtd].numAlbuns = albuns;
    vetor[qtd].ativa = (ativa == 1);
    vetor[qtd].numVendas = vendas;
    vetor[qtd].numMembrosFund = numMembrosFund;
    strcpy(vetor[qtd].genero, genero);
    vetor[qtd].excluido = false;

    qtd++;
};

void salvarBinario(banda bandas[], int qtdBandas)
{
    ofstream arquivo("bandas.bin", ios::binary);

    if (!arquivo.is_open())
    {
        cerr << "Erro ao criar arquivo binário!" << endl;
        return;
    }

    for (int i = 0; i < qtdBandas; i++)
    {
        arquivo.write((char *)&bandas[i], sizeof(banda));
    }

    arquivo.close();
    cout << "Dados salvos no arquivo binário com sucesso!" << endl;
}

int lerBandasDoCSV(const char *nomeArquivo, banda bandas[], int &tam)
{ // modificar para carregar tudo
    ifstream arquivocsv(nomeArquivo);
    if (!arquivocsv.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir o arquivo " << nomeArquivo << endl;
        return 0; // Retorna 0 bandas se o arquivo não pode ser aberto
    }

    const int maxBandas = 50;
    int i = 0;
    string linha;
    getline(arquivocsv, linha);

    while (i < maxBandas && getline(arquivocsv, linha))
    {
        if (i == tam)
        {
            bandas = aumentarVetor(bandas, tam);
        }
        // Cria um stringstream com a linha lida
        stringstream ss(linha);
        string campo;

        // Lê cada campo separado por vírgula
        ss.getline(bandas[i].nome, sizeof(bandas[i].nome), ',');
        getline(ss, campo, ',');
        bandas[i].ativa = (campo == "1");
        getline(ss, campo, ',');
        bandas[i].numAlbuns = stoi(campo);
        getline(ss, campo, ',');
        bandas[i].numVendas = stof(campo);
        getline(ss, campo, ',');
        bandas[i].numMembrosFund = stoi(campo);
        ss.getline(bandas[i].genero, sizeof(bandas[i].genero), ','); // Último campo pega até o fim da linha
        bandas[i].excluido = false;
        bandas[i].id = i;
        i++;
    }

    arquivocsv.close();
    return i; // retorna a qtd de bandas gravadas
};

int importarBinario(banda bandas[], int &tam)
{ // carregamento inicial dos 40 valores

    int qtdImport = 50; // o tanto que eu quero importar
    int qtdBandas = 0;  // o tanto que já foi carregado

    ifstream arquivo("bandas.bin", ios::binary);
    if (!arquivo)
    { // se não existe arquivo binário, ele carrega do csv e então salva o binário

        qtdBandas = lerBandasDoCSV("westview.csv", bandas, tam);
        salvarBinario(bandas, qtdBandas);
    }
    else
    { // se existe, ele importa do binario pro vetor

        if (!arquivo.is_open())
        {
            cerr << "Não foi possível abrir o arquivo";
            return 0;
        }

        banda temp;
        while (qtdBandas < qtdImport && arquivo.read((char *)&temp, sizeof(banda)))
        {
            if (qtdBandas == tam)
            {
                bandas = aumentarVetor(bandas, tam);
            }
            bandas[qtdBandas] = temp;
            qtdBandas++;
        }
        cout << "Dados carregados";
    }

    arquivo.close();
    return qtdBandas;
}

void listar(banda vetor[], int qtd_bandas)
{
    const int nomeWidth = 25;
    const int albunsWidth = 10;
    const int vendasWidth = 20;
    const int membrosWidth = 10;
    const int generoWidth = 20;

    // Cabeçalho

    cout << "Voce deseja listar: 1 - TUDO  2 - UMA PARTE ? \n";
    int op, tam;
    cin >> op;
    while (op != 1 and op != 2)
    {
        cout << "Nao eh uma opcao \n";
        cin >> op;
    }
    switch (op)
    {
        int inicio, fim;
    case 1:
        tam = qtd_bandas;
        cout << left << setw(nomeWidth) << "Nome"
             << setw(albunsWidth) << "Albuns"
             << setw(vendasWidth) << "Vendas(Em milhoes)"
             << setw(membrosWidth) << "Membros"
             << setw(generoWidth) << "Genero"
             << endl;
        for (int i = 0; i < tam; i++)
        {
            if (vetor[i].excluido == false)
            {
                cout << left << setw(nomeWidth) << vetor[i].nome
                     << setw(albunsWidth) << vetor[i].numAlbuns
                     << setw(vendasWidth) << vetor[i].numVendas
                     << setw(membrosWidth) << vetor[i].numMembrosFund
                     << setw(generoWidth) << vetor[i].genero
                     << endl;
            }
        }
        break;
    case 2:

        cout << "Voce deseja listar a partir de qual elemento? Temos " << qtd_bandas << " bandas \n";
        cin >> inicio;
        while (inicio < 0 or inicio > qtd_bandas)
        {
            cout << "Digite novamente \n";
            cin >> inicio;
        }
        cout << "Voce deseja listar ate qual elemento? Temos " << qtd_bandas << " bandas \n";
        cin >> fim;
        while (fim < inicio or fim > qtd_bandas)
        {
            cout << "Digite novamente \n";
            cin >> fim;
        }
        cout << left << setw(nomeWidth) << "Nome"
             << setw(albunsWidth) << "Albuns"
             << setw(vendasWidth) << "Vendas"
             << setw(membrosWidth) << "Membros"
             << setw(generoWidth) << "Genero"
             << endl;
        for (int i = inicio; i < fim; i++)
        {
            if (vetor[i].excluido == false)
            {
                cout << left << setw(nomeWidth) << vetor[i].nome
                     << setw(albunsWidth) << vetor[i].numAlbuns
                     << setw(vendasWidth) << vetor[i].numVendas
                     << setw(membrosWidth) << vetor[i].numMembrosFund
                     << setw(generoWidth) << vetor[i].genero
                     << endl;
            }
        }
        break;
    }
};

void ordenarPorAlbuns(banda vet[], int qtd)
{
    banda index;
    for (int i = 0; i < qtd; i++)
    {
        index = vet[i];
        int j = i - 1;
        while (j >= 0 and vet[j].numVendas > index.numVendas)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = index;
    }
};

void ordenarPorId(banda vet[], int qtd)
{
    banda index;
    for (int i = 0; i < qtd; i++)
    {
        index = vet[i];
        int j = i - 1;
        while (j >= 0 and vet[j].id > index.id)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = index;
    }
};

void ordenarPorNome(banda vet[], int qtd)
{
    int menor;
    banda aux;
    for (int i = 0; i < qtd; i++)
    {
        menor = i;
        for (int j = i + 1; j < qtd; j++)
        {
            if (vet[menor].nome > vet[j].nome)
            {
                menor = j;
            }
        }
        if (menor != 0)
        {
            aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
        }
    }
};
void buscarPorNome(banda vet[], string pesquisa, int qtd_bandas)
{
    ordenarPorNome(vet, qtd_bandas);
    int i, posicao = -1;
    int pos_inicial = 0;
    int pos_final = qtd_bandas - 1;
    int meio;
    while (pos_inicial <= pos_final)
    {
        meio = (pos_inicial + pos_final) / 2;
        if (pesquisa == vet[meio].nome)
        {
            posicao = meio;
            pos_inicial = pos_final + 1;
        }
        else
        {
            if (pesquisa > vet[meio].nome)
            {
                pos_inicial = meio + 1;
            }
            else
            {
                pos_final = meio - 1;
            }
        }
    }
    if (posicao != -1)
    {
        cout << "A banda foi encontrada!!" << endl;
        cout << "Nome: " << vet[posicao].nome << " Numero de Albuns: " << vet[posicao].numAlbuns << "Numero de vendas: " << vet[posicao].numVendas << endl;
    }
    else
    {
        cout << "Não existe banda como esse nome aqui :(";
    }
}

void buscarPorID(banda vet[], int pesquisa, int qtd_bandas)
{
    ordenarPorId(vet, qtd_bandas);
    int i, posicao = -1;
    int pos_inicial = 0;
    int pos_final = qtd_bandas - 1;
    int meio;
    while (pos_inicial <= pos_final)
    {
        meio = (pos_inicial + pos_final) / 2;
        if (pesquisa == vet[meio].id)
        {
            posicao = meio;
            pos_inicial = pos_final + 1;
        }
        else
        {
            if (pesquisa > vet[meio].id)
            {
                pos_inicial = meio + 1;
            }
            else
            {
                pos_final = meio - 1;
            }
        }
    }
    if (posicao != -1)
    {
        cout << "A banda foi encontrada!!" << endl;
        cout << "Nome: " << vet[posicao].nome << " Numero de Albuns: " << vet[posicao].numAlbuns << "Numero de vendas: " << vet[posicao].numVendas << endl;
    }
    else
    {
        cout << "Não existe banda com esse ID aqui :(";
    }
}

void excluir(banda vet[], int qtd_bandas)
{
    string pesquisa_excluir;
    cout << "Digite o nome da banda que você deseja exluir: ";
    cin >> pesquisa_excluir;
    int i = 0;
    bool encontrada = false;
    while (encontrada != true or i < qtd_bandas)
    {
        if (vet[i].nome == pesquisa_excluir)
        {
            encontrada = true;
            vet[i].excluido = true;
            cout << "Banda excluida com sucesso";
        }
        i++;
    }
    if (encontrada == false)
    {
        cout << "Banda nao foi encontrada";
    }
}

void exportarcsv(banda bandas[], int qtd){
    string nomeArquivo;
    cout << "Informe o nome do arquivo que deseja criar: ";
    cin >> nomeArquivo;

    ofstream csv(nomeArquivo);

    csv << "#nome,ativo,num_albuns,num_albuns_vendidos,num_integrantes,genero\n";

    for (int i = 0; i < qtd; i++)
    {
        csv << bandas[i].id << ","
            << bandas[i].ativa << ","
            <<bandas[i].numAlbuns << ","
            <<bandas[i].numVendas << ","
            <<bandas[i].numMembrosFund << ","
            <<bandas[i].genero << ","
             "\n";
    }

    csv.close();
    cout << "Dados exportados para " << nomeArquivo << " com sucesso!\n";
} 

int main()
{
    int op, tam, qtd_bandas;
    tam = 40;
    banda *bandas = new banda[tam];
    qtd_bandas = importarBinario(bandas, tam);
    // qtd_bandas = lerBandasDoCSV("westview.csv", bandas);
    do
    {
        main_menu();
        cin >> op;
        string escolhido; // será utilizado na opção 3
        int opAux;        // será utilizado na opção 3 e 4
        switch (op)
        {
        case 0:
            cout << "\nTchau!\n";
            break;
        case 1:
            listar(bandas, qtd_bandas);
            break;
        case 2:
            inserir(bandas, qtd_bandas, tam);
            break;
        case 3:
            escolhido = menu_pesquisa(opAux);
            if (!escolhido.empty())
            {
                if (opAux == 1)
                { // quer pesquisar por nome
                    string nomePesquisa = escolhido;
                    buscarPorNome(bandas, nomePesquisa, qtd_bandas);
                }
                else if (opAux == 2)
                { // quer pesquisar por ID
                    int ID_pesquisa = stoi(escolhido);
                    buscarPorID(bandas, ID_pesquisa, qtd_bandas);
                }
            }
            break;
        case 4:
            opAux = menu_ordena();
            switch (opAux)
            {
            case 0:
                break;
            case 1:
                ordenarPorAlbuns(bandas, qtd_bandas);
                break;
            case 2:
                ordenarPorId(bandas, qtd_bandas);
                break;
            case 3:
                ordenarPorNome(bandas, qtd_bandas);
                break;
            default:
                cout << "Opção inválida! >:(\n";
            }
            break;
        case 5:
            excluir(bandas, qtd_bandas);
            break;
        case 6:
        break;
        case 7:
            exportarcsv(bandas, qtd_bandas);
        break;
        case 8:
        break;
        default:
            cout << "Opção inválida!\n";
        }
    } while (op != 0);
    delete[] bandas;
    return 0;
}