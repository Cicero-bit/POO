#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class FONE {
public:
    std::string chip;
    std::string numero;

    FONE(std::string chip = "", std::string numero = "") : chip{chip}, numero{numero} {} 

    bool isValid(std::string numero){
        std::string::iterator i; //it para conseguir percorrer
        std::string::iterator j;
        std::string temp {"0123456789()."}; //string com numeros para auxificar o numero
        int aux {0};

        for (i = numero.begin(); i != numero.end(); ++i){             //loop de auxificação, percorre e verifica se o numero, string, se encaixa na string ferificadora
            for (j = temp.begin(); j != temp.end(); ++j){
                if (*i == *j){ 
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

    std::string getChip(){
        return this->chip;
    }

    void setChip(std::string id){
        this->chip = id; 
    }

    std::string getNumero(){
         return this->numero;
    }

    void setNumero(std::string numero){
        if (isValid(numero) == true){
            this->numero = numero;
        }else{
            std::cout << "Digite um numero valido" << std::endl;
        }
    }
    std::string toString(){
        std::string os {chip + ":" + numero};
        return os;
    }
};

class CONTATO {
public:
    std::string nome;
    std::vector<FONE> contatos;
    std::string prefixo = "-";

    CONTATO(std::string nome = "") : nome{nome} {}

    void addFone(FONE telefone){
        if (telefone.isValid(telefone.getNumero()) == true){ //verifica com a função isVlaid
            contatos.push_back(telefone); //add o tele
        }
        else{
            std::cout << "Digite um numero valido" << std::endl;
        }
    }

    std::string getNome(){ 
        return this->nome; 
    }
    void setChip(std::string nome){ 
        this->nome = nome; 
    }

    std::string show(){
        std::string out {"-> " + nome + " "};
        for (int i = 0; i < (int)contatos.size(); i++){
            out += "[" + std::to_string(i) + ":" + contatos[i].toString() + "] ";
        }
        return out;
    }

    void rmTelefone(int contato){
        if (contato > (int)contatos.size())
            std::cout << "Contato não encontrado" << std::endl;
        else
            contatos.erase(contatos.begin() + contato);
    }
};

int main(){
    CONTATO contatos;

    while (true){
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "init"){
            std::string nome {};
            ss >> nome;
            contatos.setChip(nome);
        }
        else if (cmd == "add"){
            std::string chip {};
            std::string numero {};
            ss >> chip >> numero;
            FONE temp(chip, numero);
            contatos.addFone(temp);
        }
        else if (cmd == "rm"){
            int contato {};
            ss >> contato;
            contatos.rmTelefone(contato);
        }
        else if (cmd == "show"){
            std::cout << contatos.show() << std::endl;
        }
        else if (cmd == "end"){
            break;
        }
        else{
            std::cout << "Comando inexistente" << std::endl;
        }
    }

    return 0;
}