#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Pessoa{
public:
    std::string telefone;
    std::string nome;
    Pessoa(std::string nome = "", std::string telefone = ""){
        this->telefone = telefone;
        this->nome = nome;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pessoa& p){
        os << p.nome << ":" << p.telefone;
        return os;
    }

    void setNome(std::string nome){
        this -> nome = nome;
    }
    std::string getNome() {
        return nome;
    }

    void setFone(std::string fone){
        this -> telefone = telefone;
    } 

    std::string getFone(){
        return telefone;
    }
    

};


class Cinema{
public:
    std::vector<std::shared_ptr<Pessoa>> Cadeiras;         //shared ptr é um ponteiro que meio que se deleta+-, ele tem controle do seu "proprio fechamento"
    int capacidade{0};

    Cinema(int capacidade) : Cadeiras(capacidade, nullptr){                                            //cria locais vazios para existir
        this->capacidade = capacidade;
    }


    int procurarPessoa(std::string nome){
        for (int i = 0; i < (int) Cadeiras.size(); i++)
            if (Cadeiras[i] != nullptr && Cadeiras[i] -> getNome() == nome){
                return i;
            }
        return -1;
    }

    void adicionarPessoa(std::shared_ptr<Pessoa> pessoa, int indice){
        if (indice < 0 || indice > (int) Cadeiras.size()){
            std::cout << "Cadeora inexistente" << std::endl;
            return ;
        }
        if (Cadeiras[indice] != nullptr){
            std::cout << "Cadeira ocupada" << std::endl;
            return ;
        }
        if (this->procurarPessoa(pessoa->nome) != -1){
            std::cout << "Pessoa ja esta no cinema" << std::endl;
            return ;
        }
        Cadeiras[indice] = pessoa;
    }

    std::shared_ptr<Pessoa> removerPessoa(std::string nome){
        int indice = procurarPessoa(nome);
        if (indice == -1){
            std::cout << "Pessoa inexistente";
            return nullptr;
        }
        auto temp = Cadeiras[indice];
        Cadeiras[indice] = nullptr;
        return temp;
        //OU return std::exchange(cadeiras[indice], nullptr) // ele coloca null nas cadeiras[indice] e retorna oque tinha anteriormente, faz oque está ai em cima
    }
    friend std::ostream& operator<<(std::ostream& os, const Cinema& c){
        os << "[";
        for (auto cadeira : c.Cadeiras){
            if (cadeira == nullptr){
                os << "- ";
            }
            else{
                os << *cadeira << " ";
            }
        }
        os << "]";
        return os;
    }
};

int main(){
    Cinema cinema(0);

    while (true){
        std::cout << "Digite o comando: ";
        std::string cmd;
        std::cin >> cmd;
        std::cout << "Output: \n";

        if (cmd == "init"){
            int capacidade;
            std::cin >> capacidade;
            cinema = Cinema(capacidade);
        }
        else if (cmd == "add"){
            std::string nome {};
            std::string telefone;
            int indice;
            std::cin >> nome >> telefone >> indice;
            cinema.adicionarPessoa(std::make_shared<Pessoa>(nome, telefone), indice);
        }
        else if (cmd == "remover"){
            std::string nome {};
            std::cin >> nome;
            cinema.removerPessoa(nome);
        }
        else if (cmd == "show"){
            std::cout << cinema << '\n';
        }
        else if (cmd == "end"){
            break;
        } 
        else{
            std::cout << "Comando inexistente" << "\n";
        }
    }
    return 0;
}