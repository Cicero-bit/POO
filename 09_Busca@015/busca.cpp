#include <iostream>
#include <vector>

class Fone{
private:
    std::string nome;
    std::string telefone;

public:

    Fone(std::string nome, std::string telefone) : nome{nome}, telefone{telefone}{}

    std::string getNome(){ //para conseguir usar fora da classe, ja que é private
        return this->nome;
    }

    void setNome(std::string nome){  //para conseguir setar algo a variavel
        this->nome = nome;
    }

    std::string gettelefone(){
        return this->telefone;
    }

    void settelefone(std::string telefone){
        this->telefone = telefone;
    }

    std::string toString(){ 
        return this->nome + " " + this->telefone;
    }
    
    bool isvalid(std::string telefone){
        std::string::iterator i; //iterator para conseguir percorrer e receber a posição, o andador
        std::string::iterator j;
        std::string ver {"0123456789()."}; 
        int aux {0};

        for (i = telefone.begin(); i != telefone.end(); ++i){   //loop de autenticação, percorre e verifica se o telefone, string, se encaixa na string verificadora
            for (j = ver.begin(); j != ver.end(); ++j){ //verfica com os numero do ver,char validos, caso sejam compativeis, passa com a ver do aux
                if (*i == *j){ //valor pos
                    aux++; 
                }
            }
            if (aux == 0){
                return false;
            } 
            aux = 0; //reset
        }
        return true; 
    }
};

class Contato{
private:
    std::vector<Fone> Telefone;
    std::string nome;

public:

    Contato(std::vector<Fone> Telefone, std::string nome) : Telefone{Telefone}, nome{nome}  {}

    void addFone(Fone fone){ 
        this->Telefone.push_back(fone);
    }

    void rmFone(int index){ 
        if(index < this->Telefone.size()){ //pega o telfone, linkado ao index e apaga
            this->Telefone.erase(this->Telefone.begin() + index); 
            std::cout << "removido \n";
        }else{
            std::cout << "telefone inexistente" << std::endl;
        }
    }

    std::vector<Fone> getTelefone(){
        return this->Telefone;
    }
    
    void setTelefone(std::vector<Fone> Telefone){
        this->Telefone = Telefone;
    }
    std::string getNome(){
        return this->nome;
    }

    void setNome(std::string nome){
        this->nome = nome;
    }

    std::string toString(){
        std::string str = this->nome + " "; //inicia sttr
        for (int i = 0; i < this->Telefone.size(); i++){
            str += this->Telefone[i].toString() + " "; //add tudo a strign
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

    contato1.addFone(Fone("Tim", "12345678"));
    contato1.addFone(Fone("Oi", "996030087"));
    contato1.rmFone(1); //fone removido,vida
    contato1.rmFone(2); //telefone n existe
    agenda.addContato(contato1); //add
    agenda.rmContato("Jao");  //removido
    
    return 0;
} 