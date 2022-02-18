#include <iostream>
#include <list> // lista
#include <memory> //shared ptr
#include <sstream> // os


class Kid{
    int idade;
    std::string nome;

public:
    Kid(std::string nome = "", int idade = 0){
        this->idade = idade;
        this->nome = nome;
    }

    void setNome(std::string nome){
        this->nome = nome;
    }

    std::string getNome(){
        return this->nome;
    }

    void setIdade(int idade){
        this->idade = idade;
    }

    int getIdade(){
        return this->idade;
    }

    std::string toString(){
        std::string texto {this->nome + ":" + std::to_string(this->idade)};
        
        return texto;
    }
};

class Trampolim{
public:
    std::list <std::shared_ptr<Kid>> entrada_trampolim; //aula 05 pont. inteli
    std::list <std::shared_ptr<Kid>> entra_fila;

    static bool empty(std::list<std::shared_ptr<Kid>> entra_fila){
        if (entra_fila.empty()){
            return true;            //check bool
        }else{
            return false;
        }
    }

    static int search(std::string nome, std::list<std::shared_ptr<Kid>>& vet){
        int i = 0;
        for (auto& it : vet){
            if (it->getNome() == nome){             //se o nome for igual nome recebe 1(i)
                return i;
            }
            i++;
        }
        return (-1);
    }

    static std::string toString(std::list<std::shared_ptr<Kid>> vet){
        std::string texto;
        if (!(empty(vet))){
            for (int it {(int)vet.size() - 1}; it >= 0; it--){
                auto x = std::next(vet.begin(), it);
                texto += (*x)->toString() + " ";
            }
        }
        return texto;
    }

    Trampolim(){
    }

    void arrive(std::shared_ptr<Kid> kid){
        entra_fila.push_back(kid);
    }

    void join(){
        if (empty(this->entra_fila)){
            std::cout << "Nao ha ninguem na entra_fila \n";
        }
        else{
            this->entrada_trampolim.push_back(*(this->entra_fila.begin()));
            this->entra_fila.pop_front();
        }
    }

    void out(){
        if (empty(this->entrada_trampolim)){
            std::cout << "Nao ha ninguem no tramoplin tramoplin \n";
        }
        else{
            this->entra_fila.push_back(*(this->entrada_trampolim.begin()));
            this->entrada_trampolim.pop_front();
        }
    }

    std::shared_ptr<Kid> remove(std::string nome){
        int x = search(nome, this->entra_fila);
        int y = search(nome, this->entrada_trampolim);

        if (x != -1){
            auto aux = std::next(entra_fila.begin(), x);
            entra_fila.erase(std::next(entra_fila.begin(), x));
            return (*aux);
        }
        else if (y != -1){
            auto aux = std::next(entrada_trampolim.begin(), y);
            entrada_trampolim.erase(std::next(entrada_trampolim.begin(), y));
            return (*aux);
        }
       return nullptr;
    }

    void clear(){
        entra_fila.clear();
        entrada_trampolim.clear();
    }

    std::string toString(){
        std::string texto {"- "};
       
        texto += toString(this->entra_fila);

        texto += "[";

        texto += toString(this->entrada_trampolim);

        texto += "]\n";

        return texto;
    }

};

int main(){
    std::shared_ptr<Trampolim> tramoplin (new Trampolim ());

    while (true){
        std::string cmd{""};
        std::string linha{""};

        std::cin >> cmd;
        getline(std::cin, linha);

        std::stringstream ss(linha);

        if (cmd == "new"){
            std::string nome;
            int idade;
            ss >> nome >> idade;
            std::shared_ptr<Kid> temp ( new Kid(nome, idade));

            tramoplin->arrive(temp);
        }
        else if (cmd == "join"){
            tramoplin->join();
        }
        else if(cmd == "out"){
            tramoplin->out();
        }
        else if(cmd == "show"){
            std::cout << tramoplin->toString();
        } 
        else if (cmd == "rm"){
            std::string nome;
            ss >> nome;
            tramoplin->remove(nome);
        }
        else if (cmd == "clear"){
            tramoplin->clear();
        }
        else if (cmd == "end"){
            break;
        }
        else 
            std::cout << "Comando inexistente" << "\n";
    }
    
    return 0;
}