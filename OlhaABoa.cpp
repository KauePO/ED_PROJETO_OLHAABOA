#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <set>
#include <vector>
#include <set>
#include <fstream>
#include <windows.h>
using namespace std;


struct Cart {
    string coluna1[5];
    string coluna2[5];
    string coluna3[5];
    string coluna4[5];
    string coluna5[5];
    bool linhaMarcada[5] = { false,false,false,false,false };
    bool colunaMarcada[5] = { false,false, false, false, false };
};

struct Cads {
    int posicao;
    Cart tabela;
};

class Cartela {
public:
    Cart valores;

    Cartela() {
        srand(time(0));
        set<int> coluna1_set;
        for (int i = 0; i < 5; i++) {
            int num;
            do {
                num = (rand() % 15) + 1;
            } while (coluna1_set.find(num) != coluna1_set.end());
            coluna1_set.insert(num);
            valores.coluna1[i] = to_string(num);
        }
        set<int> coluna2_set;
        for (int i = 0; i < 5; i++) {
            int num;
            do {
                num = (rand() % 15) + 16;
            } while (coluna2_set.find(num) != coluna2_set.end());
            coluna2_set.insert(num);
            valores.coluna2[i] = to_string(num);
        }
        set<int> coluna3_set;
        for (int i = 0; i < 5; i++) {
            int num;
            do {
                num = (rand() % 15) + 31;
            } while (coluna3_set.find(num) != coluna3_set.end());
            coluna3_set.insert(num);
            valores.coluna3[i] = to_string(num);
        }
        set<int> coluna4_set;
        for (int i = 0; i < 5; i++) {
            int num;
            do {
                num = (rand() % 15) + 46;
            } while (coluna4_set.find(num) != coluna4_set.end());
            coluna4_set.insert(num);
            valores.coluna4[i] = to_string(num);
        }
        set<int> coluna5_set;
        for (int i = 0; i < 5; i++) {
            int num;
            do {
                num = (rand() % 15) + 61;
            } while (coluna5_set.find(num) != coluna5_set.end());
            coluna5_set.insert(num);
            valores.coluna5[i] = to_string(num);
        }
        valores.coluna3[2] = "FREE";

        /* cout << "Coluna 1: ";
         for (int i = 0; i < 5; i++) cout << valores.coluna1[i] << " ";
         cout << "\nColuna 2: ";
         for (int i = 0; i < 5; i++) cout << valores.coluna2[i] << " ";
         cout << "\nColuna 3: ";
         for (int i = 0; i < 5; i++) cout << valores.coluna3[i] << " ";
         cout << "\nColuna 4: ";
         for (int i = 0; i < 5; i++) cout << valores.coluna4[i] << " ";
         cout << "\nColuna 5: ";
         for (int i = 0; i < 5; i++) cout << valores.coluna5[i] << " ";*/
    }
};

bool verificarLinha(Cart& tabela, int linha) {
    return tabela.coluna1[linha] == "X" && tabela.coluna2[linha] == "X" && tabela.coluna3[linha] == "X" && tabela.coluna4[linha] == "X" && tabela.coluna5[linha] == "X";
}

bool verificarLinha3(Cart& tabela) {
    if (tabela.coluna1[2] == "X" && tabela.coluna2[2] == "X" && tabela.coluna3[2] == "FREE" && tabela.coluna4[2] == "X" && tabela.coluna5[2] == "X") {
        return true;
    }
}
// PODERIA SER OTIMIZADO MAS VAI SERVIR
bool verificarColuna1(Cart& tabela) {
    int temp = 0;
    if (tabela.coluna1[temp] == "X" && tabela.coluna1[temp + 1] == "X" && tabela.coluna1[temp + 2] == "X" && tabela.coluna1[temp + 3] == "X" && tabela.coluna1[temp + 4] == "X") {
        return true;
    }
}
bool verificarColuna2(Cart& tabela) {
    int temp = 0;
    if (tabela.coluna2[temp] == "X" && tabela.coluna2[temp + 1] == "X" && tabela.coluna2[temp + 2] == "X" && tabela.coluna2[temp + 3] == "X" && tabela.coluna2[temp + 4] == "X") {
        return true;
    }
}
bool verificarColuna3(Cart& tabela) {
    int temp = 0;
    if (tabela.coluna3[temp] == "X" && tabela.coluna3[temp + 1] == "X" && tabela.coluna3[temp + 2] == "FREE" && tabela.coluna3[temp + 3] == "X" && tabela.coluna3[temp + 4] == "X") {
        return true;
    }
}
bool verificarColuna4(Cart& tabela) {
    int temp = 0;
    if (tabela.coluna4[temp] == "X" && tabela.coluna4[temp + 1] == "X" && tabela.coluna4[temp + 2] == "X" && tabela.coluna4[temp + 3] == "X" && tabela.coluna4[temp + 4] == "X") {
        return true;
    }
}
bool verificarColuna5(Cart& tabela) {
    int temp = 0;
    if (tabela.coluna5[temp] == "X" && tabela.coluna5[temp + 1] == "X" && tabela.coluna5[temp + 2] == "X" && tabela.coluna5[temp + 3] == "X" && tabela.coluna5[temp + 4] == "X") {
        return true;
    }
}

bool verificarBingo(Cart& tabela) {
    if (tabela.colunaMarcada[0] && tabela.colunaMarcada[1] && tabela.colunaMarcada[2] && tabela.colunaMarcada[3] && tabela.colunaMarcada[4]) {
        return true;
    }
}

bool verificaArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    return arquivo.good();
}

void adicionarCadastro(Cads*& cadastros, int& size, const Cart& novaTabela) {
    // Criar um novo array com tamanho maior
    Cads* novoArray = new Cads[size + 1];

    // Copiar os elementos antigos para o novo array
    for (int i = 0; i < size; ++i) {
        novoArray[i] = cadastros[i];
    }

    // Adicionar o novo cadastro
    novoArray[size].posicao = size;
    novoArray[size].tabela = novaTabela;

    int contador = 1;
    string nomeArquivo = "Cartela" + to_string(contador) + ".txt";

    while (verificaArquivo(nomeArquivo)) {
        contador++;
        nomeArquivo = "Cartela" + to_string(contador) + ".txt";
    }

    ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo << "BINGO" << ": \n";
        for (int i = 0; i < 5; i++) {
            arquivo << novoArray[size].tabela.coluna1[i] << " " << novoArray[size].tabela.coluna2[i] << " " << novoArray[size].tabela.coluna3[i] << " " << novoArray[size].tabela.coluna4[i] << " " << novoArray[size].tabela.coluna5[i] << endl;
        }
        arquivo.close();
    }
    else {
        cout << "Nao foi possivel criar o arquivo" << endl;
    }

    // Liberar o array antigo
    delete[] cadastros;

    // Atualizar o ponteiro e o tamanho
    cadastros = novoArray;
    ++size;

}

void olhaABoa(Cads* cadastros, int size) {
    if (cadastros == nullptr || size == 0) {
        return; // nenhuma cartela cadastrada
    }

    for (int o = 0; o < size; o++) {
        int marcados = 0;

        // contar quantos marcados
        for (int i = 0; i < 5; i++) {
            if (cadastros[o].tabela.coluna1[i] == "X") marcados++;
            if (cadastros[o].tabela.coluna2[i] == "X") marcados++;
            if (cadastros[o].tabela.coluna3[i] == "X" || (i == 2 && cadastros[o].tabela.coluna3[i] == "FREE")) marcados++;
            if (cadastros[o].tabela.coluna4[i] == "X") marcados++;
            if (cadastros[o].tabela.coluna5[i] == "X") marcados++;
        }
        if (marcados == 24) {
            cout << "Olha a boa !" << endl;
        }
    }
}

void mostrarCartelas(Cads* cadastros, int size) {
    if (cadastros == nullptr || size == 0) {
        cout << "Nenhuma cartela para mostrar.\n";
        return;
    }
    for (int o = 0; o < size; o++) {
        cout << "Cartela " << o + 1 << ": \n";
        for (int i = 0; i < 5; i++) {
            cout << cadastros[o].tabela.coluna1[i] << " " << cadastros[o].tabela.coluna2[i] << " " << cadastros[o].tabela.coluna3[i] << " " << cadastros[o].tabela.coluna4[i] << " " << cadastros[o].tabela.coluna5[i] << endl;
        }
        cout << endl;
    }


}

void gerarRelatorio(Cads* cadastros, int size, const vector<int>& numerosChamados) {
    if (cadastros == nullptr || size == 0) {
        return;
    }

    cout << "Numeros marcados:\n";

    // Criar um vetor de vetores de strings para armazenar os números presentes por tabela
    static vector< vector<string>> todosNumerosPresentes(size);

   
    for (int o = 0; o < size; o++) {
        cout << "Cartela " << o + 1 << ": ";

        
        for (int i = 0; i < 5; i++) {
            
            if (isdigit(cadastros[o].tabela.coluna1[i][0])) {
                if (find(numerosChamados.begin(), numerosChamados.end(), stoi(cadastros[o].tabela.coluna1[i])) != numerosChamados.end()) {
                    todosNumerosPresentes[o].push_back(cadastros[o].tabela.coluna1[i]);
                }
            }
            
            if (isdigit(cadastros[o].tabela.coluna2[i][0])) {
                if (find(numerosChamados.begin(), numerosChamados.end(), stoi(cadastros[o].tabela.coluna2[i])) != numerosChamados.end()) {
                    todosNumerosPresentes[o].push_back(cadastros[o].tabela.coluna2[i]);
                }
            }
            
            if (isdigit(cadastros[o].tabela.coluna3[i][0])) {
                if (find(numerosChamados.begin(), numerosChamados.end(), stoi(cadastros[o].tabela.coluna3[i])) != numerosChamados.end()) {
                    todosNumerosPresentes[o].push_back(cadastros[o].tabela.coluna3[i]);
                }
            }
            
            if (isdigit(cadastros[o].tabela.coluna4[i][0])) {
                if (find(numerosChamados.begin(), numerosChamados.end(), stoi(cadastros[o].tabela.coluna4[i])) != numerosChamados.end()) {
                    todosNumerosPresentes[o].push_back(cadastros[o].tabela.coluna4[i]);
                }
            }
            
            if (isdigit(cadastros[o].tabela.coluna5[i][0])) {
                if (find(numerosChamados.begin(), numerosChamados.end(), stoi(cadastros[o].tabela.coluna5[i])) != numerosChamados.end()) {
                    todosNumerosPresentes[o].push_back(cadastros[o].tabela.coluna5[i]);
                }
            }
        }

        
        for (const string& num : todosNumerosPresentes[o]) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void marcarNumero(Cads* cadastros, int size, int sorteado) {
    if (cadastros == nullptr || size == 0) {
        cout << "Erro: nenhuma cartela cadastrada.\n";
        return;
    }
    for (int o = 0; o < size; o++) {
        for (int i = 0; i < 5; i++) {
            if (cadastros[o].tabela.coluna1[i] == to_string(sorteado)) {
                cadastros[o].tabela.coluna1[i] = "X";
            }
            if (cadastros[o].tabela.coluna2[i] == to_string(sorteado)) {
                cadastros[o].tabela.coluna2[i] = "X";
            }
            if (cadastros[o].tabela.coluna3[i] == to_string(sorteado)) {
                cadastros[o].tabela.coluna3[i] = "X";
            }
            if (cadastros[o].tabela.coluna4[i] == to_string(sorteado)) {
                cadastros[o].tabela.coluna4[i] = "X";
            }
            if (cadastros[o].tabela.coluna5[i] == to_string(sorteado)) {
                cadastros[o].tabela.coluna5[i] = "X";
            }
        }
        // CHECAGENS
        for (int linha = 0; linha < 5; linha++) { // VERIFICAR LINHA
            if (!cadastros[o].tabela.linhaMarcada[linha] && verificarLinha(cadastros[o].tabela, linha)) {
                cout << "LINHA" << endl;
                cadastros[o].tabela.linhaMarcada[linha] = true;
            }
        }
        if (!cadastros[o].tabela.linhaMarcada[2] && verificarLinha3(cadastros[o].tabela)) { // VERIFICAÇÃO ESPECIAL PARA LINHA 3 POR CONTA DO "FREE"
            cout << "LINHA" << endl;
            cadastros[o].tabela.linhaMarcada[2] = true;
        }

        // VERIFICAR COLUNA
        if (!cadastros[o].tabela.colunaMarcada[0] && verificarColuna1(cadastros[o].tabela)) {
            cout << "COLUNA" << endl;
            cadastros[o].tabela.colunaMarcada[0] = true;
        };
        if (!cadastros[o].tabela.colunaMarcada[1] && verificarColuna2(cadastros[o].tabela)) {
            cout << "COLUNA" << endl;
            cadastros[o].tabela.colunaMarcada[1] = true;
        };
        if (!cadastros[o].tabela.colunaMarcada[2] && verificarColuna3(cadastros[o].tabela)) {
            cout << "COLUNA" << endl;
            cadastros[o].tabela.colunaMarcada[2] = true;
        };
        if (!cadastros[o].tabela.colunaMarcada[3] && verificarColuna4(cadastros[o].tabela)) {
            cout << "COLUNA" << endl;
            cadastros[o].tabela.colunaMarcada[3] = true;
        };
        if (!cadastros[o].tabela.colunaMarcada[4] && verificarColuna5(cadastros[o].tabela)) {
            cout << "COLUNA" << endl;
            cadastros[o].tabela.colunaMarcada[4] = true;
        };



        // VERIFICAR BINGO
        if (verificarBingo(cadastros[o].tabela)) {
            cout << "BINGO" << endl;
        }

    }

}

int main() {
    int cartQ = 0;
    int controle = 0;
    int size = 0;
    int sorteado = 0;
    vector<int> numerosChamados;
    Cads* cadastros = nullptr; // Ponteiro para o array de cadastros

    while (controle != 4) {
        cout << "1- Cadastrar cartela;\n";
        cout << "2- Mostrar cartelas;\n";
        cout << "3- Marcar numero;\n";
        cout << "4- Sair;\n";
        cout << "Digite sua escolha: ";
        cin >> controle;

        switch (controle) {
        case 1: {
            cout << "Quantas cartelas deseja?";
            cin >> cartQ;
            for (int i = 0; i < cartQ; i++) {
                Cartela novaCartela;
                adicionarCadastro(cadastros, size, novaCartela.valores);
                cout << "Cartela " << size << " cadastrada! \n";
                if (cartQ > 1) {
                    Sleep(1000);
                }
            }
            break;
        }
        case 2:
            mostrarCartelas(cadastros, size);
            gerarRelatorio(cadastros, size, numerosChamados);
            break;
        case 3:
            cout << "Insira o numero chamado: \n";
            cin >> sorteado;

            // Adicionar o número à lista de números chamados, se ainda não estiver presente
            if (find(numerosChamados.begin(), numerosChamados.end(), sorteado) == numerosChamados.end()) {
                numerosChamados.push_back(sorteado);
            }
            gerarRelatorio(cadastros, size, numerosChamados);
            marcarNumero(cadastros, size, sorteado);
            olhaABoa(cadastros, size);



            break;
        case 4:
            break;
        default:
            cout << "Opcao invalida!\n";
        }
    }

    // Liberar memória alocada
    delete[] cadastros;

    return 0;
}