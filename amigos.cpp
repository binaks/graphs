#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// funcao auxiliar que checa se um numero esta em um vetor
bool isMember (vector<int> a, int b) {
    for (auto i = 0u; i != a.size(); ++i) {
        if (a[i] == b) {
            return true;
        }
    }
    
    return false;
}

// funcao auxiliar que retorna os elementos do primeiro vetor que nao estao no segundo
// sem duplicados
vector<int> apagarAmigosEmComumCom (vector<int> a, vector<int> b, int c) {
    vector<int> output;

    for (auto i = 0u; i != a.size(); ++i) {
        if (!isMember(b, a[i]) and !isMember(output, a[i]) and a[i] != c) {
            output.push_back(a[i]);
        }
    }

    return output;
} 

vector<int> amigosDeAmigos (map<int,vector<int>>& amizades, int pessoa) {
    vector<int> output;

    // encontra os amigos da pessoa que foi dada como entrada no map
    auto amigosPessoa = amizades.find(pessoa)->second;

    // adiciona os amigos dos amigos da pessoa ao output
    for (auto i = 0u; i != amigosPessoa.size(); ++i) {
        auto amigosDoAmigoI = amizades.find(amigosPessoa[i])->second;
        
        for (auto j = 0u; j != amigosDoAmigoI.size(); ++j) {
            output.push_back(amigosDoAmigoI[j]);
        }
    }

    // exclui os amigos em comum, os duplicados e o proprio numero
    output = apagarAmigosEmComumCom(output, amigosPessoa, pessoa);

    return output;
}

int main () {
    map<int,vector<int>> amizades;
    vector<int> ada; // amigos de amigos

    vector<int> friends_1{2,3,4,5,6};
    vector<int> friends_2{1,3};
    vector<int> friends_3{2,1,4,5};
    vector<int> friends_4{3,1,5};
    vector<int> friends_5{4,1,3,6};
    vector<int> friends_6{5,1};

    amizades.insert ({1,friends_1});
    amizades.insert ({2,friends_2});
    amizades.insert ({3,friends_3});
    amizades.insert ({4,friends_4});
    amizades.insert ({5,friends_5});
    amizades.insert ({6,friends_6});

    cout << "AMIZADES:" << endl;
    cout << "--------------------------" << endl;

    for (auto i = amizades.begin(); i != amizades.end(); ++i) {
        cout << "(" << i->first << ", {"; 

        for (auto j = 0u; j != i->second.size(); ++j) { 
            cout << i->second[j];
            if (j != i->second.size() - 1) {
                cout << ", ";
            }
        }  

        cout << "})" << endl;
    }

    cout << "--------------------------" << endl << endl;

    int n;

    cout << "Entre com um numero (1-6): " << endl;
    cin >> n;
    cout << "Os amigos dos amigos de " << n << " (excluindo os amigos em comum com " << n << ") sao: "<< endl;
   
    ada = amigosDeAmigos(amizades, n); 
    
    for (auto i = 0u; i < ada.size(); ++i) {
        cout << ada[i] << " ";
    }

    cout << endl;

    return 0;
}
