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

void aumentarVetor(banda* &vetor, int &qtd)
{
    int tamAntigo = qtd;
    qtd = qtd + 10;
    banda *temp = new banda[qtd];
    for(int i =0; i<tamAntigo; i ++){
        temp[i] = vetor[i]; 
    }
    delete[] vetor;
    vetor = temp;
};

void displayHeader(const string& title) { //para fazer o menu bonitinho
    cout << "\n\033[1;36m" << string(50, '=') << "\033[0m\n";
    cout << "\033[1;36m" << setw((50 + title.length()) / 2) << title << "\033[0m\n";
    cout << "\033[1;36m" << string(50, '=') << "\033[0m\n";
}

void displayMenuItem(int option, const string& text) { //para fazer o menu bonitinho
    cout << "\033[1;33m" << setw(2) << option << "\033[0m" << " - " << text << "\n";
}

void main_menu() {
    
    displayHeader("BEM VINDO AO PROGRAMA 'ROLLING STONE BRASIL'");
    
    displayMenuItem(1, "Listar todos os registros");
    displayMenuItem(2, "Inserir novo registro");
    displayMenuItem(3, "Pesquisar registro");
    displayMenuItem(4, "Ordenar registros");
    displayMenuItem(5, "Excluir registro");
    displayMenuItem(6, "Importar dados de arquivo CSV");
    displayMenuItem(7, "Exportar dados para arquivo CSV");
    displayMenuItem(8, "Salvar alterações no arquivo binário");
    displayMenuItem(0, "Encerrar programa");
    
    cout << "\n\033[1;36m" << string(50, '=') << "\033[0m\n";
    cout << "\033[1;32mDigite sua opção: \033[0m";
}

string menu_pesquisa(int &op) //exibe as opções caso o usuario queira pesquisar
{ 
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

int menu_ordena() //exibe as opções caso o usuario queira ordenar
{
    int op;

    cout << "\nVocê deseja ordenar por: \n";
    cout << "1 - Vendas\n";
    cout << "2 - ID\n";
    cout << "3 - Nome\n";
    cout << "0 - Cancelar\n";
    cin >> op;

    return op;
}

void inserir(banda* &vetor, int &qtd, int &tam) //adiciona mais uma banda 
{
    if (tam == qtd)
    {
        aumentarVetor(vetor, tam);
    }
    char nome[50], genero[50];
    int albuns, numMembrosFund;
    int ativa;
    float vendas;
    int max_id = 0;
    for (int i = 0; i < qtd; i++) {
        if (vetor[i].id > max_id) {
            max_id = vetor[i].id;
        }
    }

    cout << "Nome da banda?" << endl;
    cin.ignore(); // Ignora o \n deixado pelo cin anterior
    cin.getline(nome, 50);

    cout << "Número de albuns?" << endl;
    cin >> albuns;
    while (albuns < 0)
    {
        cout << "Somente números maiores ou iguais a 0" << endl;
        cout << "Número de álbuns?" << endl;
        cin >> albuns;
    }

    cout << "Quantos álbuns vendeu? (em milhões)" << endl;
    cin >> vendas;
    while (vendas < 0)
    {
        cout << "Somente números maiores ou iguais a 0" << endl;
        cout << "Quantos álbuns vendeu? (em milhões)" << endl;
        cin >> vendas;
    }

    cout << "Está ativa? Digite 0 para NÃO ou 1 para SIM" << endl;
    cin >> ativa;
    while (ativa != 0 && ativa != 1)
    {
        cout << "Apenas 1 ou 0!" << endl;
        cout << "Está ativa? 0 - Não  1 - Sim" << endl;
        cin >> ativa;
    }

    cout << "Quantos membros fundadores?" << endl;
    cin >> numMembrosFund;
    while (numMembrosFund < 0)
    {
        cout << "Somente números maiores que 0" << endl;
        cout << "Quantos membros fundadores?" << endl;
        cin >> numMembrosFund;
    }

    cout << "Qual o gênero da banda?" << endl;
    cin.ignore(); // Ignora o \n deixado pelo cin anterior
    cin.getline(genero, 50);
    vetor[qtd].id = max_id;
    strcpy(vetor[qtd].nome, nome);
    vetor[qtd].numAlbuns = albuns;
    vetor[qtd].ativa = (ativa == 1);
    vetor[qtd].numVendas = vendas;
    vetor[qtd].numMembrosFund = numMembrosFund;
    strcpy(vetor[qtd].genero, genero);
    vetor[qtd].excluido = false;

    qtd++;
};

void salvarBinario(banda* &bandas, int qtdBandas) //salva os dados no arquivo bandas.bin
{
    ofstream arquivo("bandas.bin", ios::binary| ios::trunc);

    if (!arquivo.is_open())
    {
        cerr << "Erro ao criar arquivo binário!" << endl;
        return;
    }

    for (int i = 0; i < qtdBandas; i++)
    {
        if(bandas[i].excluido == false){
            arquivo.write((char *)&bandas[i], sizeof(banda));
        }
    }

    arquivo.close();
    cout << "Dados salvos no arquivo binário com sucesso!" << endl;
}

int lerBandasDoCSV(const char *nomeArquivo, banda* &bandas, int &tam) //importa os dados do arquivo westview.csv no inicio da execução
{
    ifstream arquivocsv(nomeArquivo);
    if (!arquivocsv.is_open())
    {
        cerr << "Erro: Não foi possivel abrir o arquivo " << nomeArquivo << endl;
        return 0;
    }

    int i = 0;
    string linha;
    getline(arquivocsv, linha); // Pula o cabeçalho

    // Registra a linha atual para mensagens de erro mais claras
    int numeroLinha = 1; 

    while (getline(arquivocsv, linha))
    {
        numeroLinha++;

        if (i == tam)
        {
           aumentarVetor(bandas, tam);
        }

        stringstream ss(linha);
        string campo;

        getline(ss, campo, ',');
        try {
            if (!campo.empty()) {
                bandas[i].id = stoi(campo);
            } else {
                bandas[i].id = i; 
            }
        } catch (const std::invalid_argument& e) {
            cerr << "AVISO: ID invalido na linha " << numeroLinha << " do CSV." << endl;
            bandas[i].id = i;
        }

        
        ss.getline(bandas[i].nome, sizeof(bandas[i].nome), ',');
        
        
        getline(ss, campo, ',');
        bandas[i].ativa = (campo == "1");

        
        getline(ss, campo, ',');
        try {
            bandas[i].numAlbuns = !campo.empty() ? stoi(campo) : 0;
        } catch (const std::invalid_argument& e) {
            cerr << "AVISO: Numero de albuns invalido na linha " << numeroLinha << endl;
            bandas[i].numAlbuns = 0; 
        }
        
        
        getline(ss, campo, ',');
        try {
            bandas[i].numVendas = !campo.empty() ? stof(campo) : 0.0f;
        } catch (const std::invalid_argument& e) {
            cerr << "AVISO: Numero de vendas invalido na linha " << numeroLinha << endl;
            bandas[i].numVendas = 0.0f; 
        }
        
        
        getline(ss, campo, ',');
        try {
            bandas[i].numMembrosFund = !campo.empty() ? stoi(campo) : 0;
        } catch (const std::invalid_argument& e) {
            cerr << "AVISO: Numero de membros invalido na linha " << numeroLinha << endl;
            bandas[i].numMembrosFund = 0; 
        }

        
        ss.getline(bandas[i].genero, sizeof(bandas[i].genero), ',');
        
        bandas[i].excluido = false;
        i++;
    }

    arquivocsv.close();
    return i;
}


int importarBinario(banda* &bandas, int &tam)
{ // importa os dados do arquivo bandas.bin

    int qtdBandas = 0;  // o tanto que já foi carregado
    ifstream arquivo("bandas.bin", ios::binary);
    if (!arquivo)
    { // se não existe arquivo binário, ele carrega do csv e então salva o binário

        qtdBandas = lerBandasDoCSV("westview.csv", bandas, tam);
        salvarBinario(bandas, qtdBandas);
        cout<<"Arquivo binário criado. Dados importados de 'westview.csv'\n";
    }
    else
    { // se existe, ele importa do binario pro vetor

        if (!arquivo.is_open())
        {
            cerr << "Não foi possível abrir o arquivo";
            return 0;
        }

        banda temp;
        while (arquivo.read((char *)&temp, sizeof(banda)))
        {
            if (qtdBandas == tam)
            {
                aumentarVetor(bandas, tam);
            }
            bandas[qtdBandas] = temp;
            qtdBandas++;
        }
        cout << "Dados carregados";
    }

    arquivo.close();
    return qtdBandas;
}

void listar(banda vetor[], int qtd_bandas) //mostra as bandas
{
    const int nomeWidth = 25;
    const int albunsWidth = 10;
    const int vendasWidth = 20;
    const int membrosWidth = 10;
    const int generoWidth = 20;

    // Cabeçalho

    cout << "Voce deseja listar: 1 - TUDO  2 - UMA PARTE \n";
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
            if (strcmp(vet[j].nome, vet[menor].nome) < 0)
            {
                menor = j;
            }
        }
        if (menor != i)
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
        int comparacao = strcmp(pesquisa.c_str(), vet[meio].nome);
        if (comparacao == 0)
        {
            posicao = meio;
            pos_inicial = pos_final + 1;
        }
        else
        {
            if (comparacao >0)
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
        cout << "Nome: " << vet[posicao].nome << " Numero de Albuns: " << vet[posicao].numAlbuns << " Numero de vendas: " << vet[posicao].numVendas <<" Numero de Vendas: "<<vet[posicao].genero<< endl;
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
        cout << "Nome: " << vet[posicao].nome << " Numero de Albuns: " << vet[posicao].numAlbuns << " Numero de vendas: " << vet[posicao].numVendas << endl;
    }
    else
    {
        cout << "Não existe banda com esse ID aqui :(";
    }
}

void excluir(banda* &vet, int qtd_bandas) //exclui logicamente. na hora de salvar as alterações, a exclusão é física
{
    char pesquisa_excluir[50];
    cout << "Digite o nome da banda que você deseja exluir: ";
    cin.ignore();
    cin.getline(pesquisa_excluir, 50);
    int i = 0;
    bool encontrada = false;
    while (encontrada != true and i < qtd_bandas)
    {
        if (strcmp(vet[i].nome, pesquisa_excluir) == 0)
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

void exportarcsv(banda bandas[], int qtd) //exporta os dados para um arquivo csv informado 
{
    string nomeArquivo;
    cout << "Informe o nome do arquivo para o qual deseja exportar: ";
    cin >> nomeArquivo;

    ofstream csv(nomeArquivo);

    csv << "#id,nome,ativo,num_albuns,num_albuns_vendidos,num_integrantes,genero\n";

    for (int i = 0; i < qtd; i++)
    {
        csv << bandas[i].id << ","
            <<bandas[i].nome<<","
            << bandas[i].ativa << ","
            << bandas[i].numAlbuns << ","
            << bandas[i].numVendas << ","
            << bandas[i].numMembrosFund << ","
            << bandas[i].genero << "\n";
    }

    csv.close();
    cout << "Dados exportados para " << nomeArquivo << " com sucesso!\n";
}

int importarcsv(banda* &bandas, int &tam) { //importa os dados de um arquivo csv informado pleo usuário
    string nomeArquivo;
    cout << "Informe o nome do arquivo .csv do qual deseja importar os dados: ";
    cin >> nomeArquivo;

    ifstream arq(nomeArquivo);
    if (!arq.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo " << nomeArquivo << endl;
        return 0;
    }

    int i = 0;
    string linha;
    getline(arq, linha); // Pula o cabeçalho

    // Registra a linha atual para mensagens de erro mais claras
    int numeroLinha = 1; 

    while (getline(arq, linha)) {
        numeroLinha++;

        // Ignora linhas vazias
        if (linha.empty()) {
            continue;
        }

        if (i == tam) {
            aumentarVetor(bandas, tam);
        }

        stringstream ss(linha);
        string campo;

        // ID
        getline(ss, campo, ',');
        try {
            bandas[i].id = !campo.empty() ? stoi(campo) : i;
        } catch (const invalid_argument& e) {
            cerr << "AVISO: ID invalido na linha " << numeroLinha << ". Usando valor padrao: " << i << endl;
            bandas[i].id = i;
        }

        // Nome
        getline(ss, campo, ',');
        strncpy(bandas[i].nome, campo.c_str(), sizeof(bandas[i].nome) - 1);
        bandas[i].nome[sizeof(bandas[i].nome) - 1] = '\0';

        // Ativa
        getline(ss, campo, ',');
        bandas[i].ativa = (campo == "1");

        // Número de Álbuns
        getline(ss, campo, ',');
        try {
            bandas[i].numAlbuns = !campo.empty() ? stoi(campo) : 0;
        } catch (const invalid_argument& e) {
            cerr << "AVISO: Numero de albuns invalido na linha " << numeroLinha << ". Usando 0." << endl;
            bandas[i].numAlbuns = 0;
        }

        // Vendas
        getline(ss, campo, ',');
        try {
            bandas[i].numVendas = !campo.empty() ? stof(campo) : 0.0f;
        } catch (const invalid_argument& e) {
            cerr << "AVISO: Numero de vendas invalido na linha " << numeroLinha << ". Usando 0.0." << endl;
            bandas[i].numVendas = 0.0f;
        }

        // Membros Fundadores
        getline(ss, campo, ',');
        try {
            bandas[i].numMembrosFund = !campo.empty() ? stoi(campo) : 0;
        } catch (const invalid_argument& e) {
            cerr << "AVISO: Numero de membros invalido na linha " << numeroLinha << ". Usando 0." << endl;
            bandas[i].numMembrosFund = 0;
        }

        // Gênero (último campo pode conter vírgulas se for entre aspas)
        getline(ss, campo);
        strncpy(bandas[i].genero, campo.c_str(), sizeof(bandas[i].genero) - 1);
        bandas[i].genero[sizeof(bandas[i].genero) - 1] = '\0';

        bandas[i].excluido = false;
        i++;
    }

    arq.close();
    cout << "Dados carregados de " << nomeArquivo << " com sucesso! Total: " << i << " bandas." << endl;
    return i;
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
        char opAux6; // será utilizado na opção 6
        char opAux0; // sera utilizado na opção 0
        switch (op)
        {
        case 0:
            cout << "Deseja salvar as alterações antes de sair? (S/N): ";
            cin >> opAux0;
            if (opAux0 == 'S' || opAux0 == 's') {
                salvarBinario(bandas, qtd_bandas);
            }
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
        do{
            cout<<"Atenção! Dados não salvos serão perdidos.\n";
            cout<<"Deseja continuar? Digite S / N\n";
            cin>>opAux6;
            if(opAux6 == 's' or opAux6 == 'S'){
                delete [] bandas;
                bandas = new banda[50];
                qtd_bandas = importarcsv(bandas, tam);
            }else if(opAux6 != 'N' and opAux6 != 'n'){
                cout<<"Opção inválida! >:[";
            }else{
                opAux6 = 's';
            }
        }while(opAux6 != 'S' and opAux6 != 's'); 
            break;
        case 7:
            exportarcsv(bandas, qtd_bandas);
            break;
        case 8:
            salvarBinario(bandas,qtd_bandas);
            break;
        default:
            cout << "Opção inválida!\n";
        }
    } while (op != 0);
    delete[] bandas;
    return 0;
}