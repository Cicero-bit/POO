#include <iostream>
#include <sstream>

struct Pessoa{
    std::string nome;                                               //atributos
    int idade;

    Pessoa(std::string nome = "", int idade = 0){                   //obejto
        this->nome = nome;                                          //contrutor do objeto
        this->idade = idade;                                        //altera os atributos por causa do ponteiro
    }
    
    friend std::ostream& operator <<(std::ostream& os, const Pessoa& p){
        os << "Nome: " << p.nome << "Idade: " << p.idade;
        return os;
    }
};

struct Motoca{
    Pessoa *pessoa;
    bool tem_gente;
    int tempo;
    int potencia = 1;

    
    Motoca(){
        this->tempo = 0;
        this->pessoa = {nullptr};
    }

    friend std::ostream& operator <<(std::ostream& os, const Motoca& m){        //metodos
        os << "Tempo: " << m.tempo << "Potencia: " << m.potencia; 
        os << "[" << (m.pessoa == nullptr ? "VAZIA" : m.pessoa->nome) << "]";
        return os;
    }

    std::string buzinar(){
        std::cout << "Pem";
    }

    Pessoa * removerpessoa(){
        Pessoa *p = this->pessoa;
        this->pessoa =nullptr;  // metodos
        return p;
    }

    void comprar_tempo(int tempo){
        this->tempo += tempo;
    }

    bool dirigir(int tempo){         //metodos
        this->tempo = tempo;
        if(this->pessoa == nullptr){
            std::cout << "Não tem pessoa para dirigir" << std::endl;
            return false;
        }
        if(tempo <= this-> tempo){
            std::cout << "Dirigindo\n";
        }else{
            std::cout << "Compre tempo";
        }
    }

    bool inserirpessoa(Pessoa *p){
    if(this->pessoa != nullptr){ //metodos
        std:: cout << "Motoca cheia" << std:: endl;
        return false;
    }
    this->pessoa = p;
    return true;
    }
};


int main(){
    Pessoa pessoa(); 
    Motoca motoca1;

    while(true){
        std::string linha, cmd;
        std::getline(std::cin, linha);
        std::stringstream ss(linha);   
        int tempo;
        ss >> cmd;
        if (cmd == "init"){
            int potencia = 0;
            ss >> potencia;
            motoca1 = Motoca();
            motoca1.potencia = potencia;
        }
        else if(cmd == "status"){
            std::cout << motoca1 << "\n";
        }
        else if(cmd == "montar") {
            std::string nome{};
            int idade = 0;
            ss >> nome >> idade;
            Pessoa *pessoa = new Pessoa(nome, idade); // bloco dinamico na heap
            if(!motoca1.inserirpessoa(pessoa)){
                delete pessoa;
            }
        }
        else if(cmd == "sair") {
            Pessoa *pessoa = motoca1.removerpessoa();
            if(pessoa != nullptr){
                delete pessoa; //apaga a pessoa da memoria heap
            }
        }
        else if(cmd == "comprar"){
            ss >> tempo;
            motoca1.tempo = tempo;
        }
        else if(cmd == "dirigir"){
            motoca1.dirigir(tempo);
            tempo--;
        }
        else if(cmd == "buzinar") {
            motoca1.buzinar();
        }
        else if(cmd == "end"){
            break;
        }else{
            std::cout << "Comando inexistente\n";
        }
    }
    return 0;
}