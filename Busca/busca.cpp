#include <iostream>
#include <vector>

class Fone{
private:
    std::string id;
    std::string numero;

public:

    Fone(std::string id, std::string numero) : id{id}, numero{numero}{}

    bool valid(std::string numero){
        std::string::iterator i; //iterator para conseguir percorrer e receber a posição, o andador
        std::string::iterator j;
        std::string ver {"0123456789()."}; 
        int aux {0};

        for (i = numero.begin(); i != numero.end(); ++i){             //loop de auteificação, percorre e verifica se o numero, string, se encaixa na string ferificadora
            for (j = ver.begin(); j != ver.end(); ++j){ //
                if (*i == *j){ //se a posição
                    aux++; 
                }
            }
            if (aux == 0){
                return false;
            } 
            aux = 0; //reset
        }
        return true; //true para ok
    }

    std::string getId(){ //para conseguir usar fora da classe, ja que é private
        return this->id;
    }

    void setId(std::string id){  //para conseguir setar algo a variavel
        this->id = id;
    }

    std::string getNumero(){
        return this->numero;
    }

    void setNumero(std::string numero){
        this->numero = numero;
    }

    std::string toString(){ 
        return this->id + " " + this->numero;
    }
};

class Contato{
private:
    std::vector<Fone> fones;
    std::string nome;

public:

    Contato(std::vector<Fone> fones, std::string nome) : fones{fones}, nome{nome}  {}

    void addFone(Fone fone){ 
        this->fones.push_back(fone);
    }

    void rmFone(int index){ 
        if(index < this->fones.size()){
            this->fones.erase(this->fones.begin() + index); 
            std::cout << "removido \n";
        } else{
            std::cout << "telefone inexistente" << std::endl;
        }
    }

    std::vector<Fone> getFones(){
        return this->fones;
    }
    
    void setFones(std::vector<Fone> fones){
        this->fones = fones;
    }
    std::string getNome(){
        return this->nome;
    }

    void setNome(std::string nome){
        this->nome = nome;
    }

    std::string toString(){
        std::string str = this->nome + " "; //inicia sttr
        for (int i = 0; i < this->fones.size(); i++){
            str += this->fones[i].toString() + " "; //add tudo a strign
        }
        return str; //retorn ela
    }
};

class Agenda {
private:
    std::vector<Contato> contato;

public:
    Agenda(){
        this->contato = std::vector<Contato>();
    }

    int search(std::string nome){
        for(int i = 0; i < this->contato.size(); i++){ // percorre todos os contato
            if(this->contato[i].getNome() == nome){ // se o nome do contato for igual ao nome passado
                return i; // retorna a posicao do contato
            }
        return -1;
        }
    }
    void addContato(Contato contato){
        this->contato.push_back(contato); // adiciona o contato na agenda
        std::cout << "Contato adicionado" << std::endl;
    }

    Contato searchContato(std::string nome){ //contato na agenda
        int pos = this->search(nome); // busca o contato na agenda
        if(pos != -1){ // se o contato existir
            return this->contato[pos]; // retorna o contato
            std::cout << "contato";
        }
        return Contato(std::vector<Fone>(), "");
        std::cout << "uhum" << std::endl;
    }

    void rmContato(std::string nome) {
        int pos = this->search(nome); // usa o search pra achar o contato na agenda
        if(pos != -1){ // if contato existe
            this->contato.erase(this->contato.begin() + pos); // apaga o contato da lista
            std::cout << "boom, apagado";
        } else { //caso nao achar
            std::cout << "contato inexistente" << std::endl;
        }
    }

    std::vector<Contato>Search(std::string nome) {
        std::vector<Contato> contato;
        for(int i = 0; i < this->contato.size(); i++) { // passa na lista de contato
            if(this->contato[i].getNome().find(nome) != std::string::npos) { // if contato_nome = nome usnado find
                contato.push_back(this->contato[i]); // add contato >> lista de contato
            }
        }
        return contato; //volta a lista de contato
    }

    std::vector<Contato> getcontato() {
        return this->contato;
    }

    void show(){
    }
};

int main() {
    Agenda agenda = Agenda();

    Contato contato1 = Contato(std::vector<Fone>(), "Jao");
    contato1.addFone(Fone("4", "12345678"));
    contato1.addFone(Fone("5", "996030087"));
    contato1.rmFone(1); //sinal de vida, fone removido
    contato1.rmFone(2); //telefone n existe, não roda remoção
    agenda.addContato(contato1);
    agenda.rmContato("Jao");  //removido
    
    return 0;
} 