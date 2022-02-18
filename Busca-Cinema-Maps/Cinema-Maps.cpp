#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

class Pessoa{
    private:
        std::string id;
        std::string phone;
    public:
        Pessoa(std::string id, std::string phone) : id{id}, phone{phone} {}

        std::string getId(){
            return this->id;
        }

        void setId(std::string id){
            this->id = id;
        }

        std::string getPhone(){
            return this->phone;
        }

        void setPhone(std::string phone){
            this->phone = phone;
        }
        std::string toString(){
            std::stringstream ss;
            ss << " "<< this->id << ":" << this->phone << " ";
            return ss.str(); //str retorna um obejeto string copiado da stream, ss ^^(get/set)
        }
};

class Cinema{
    private:
        int capacidade;
        std::map<std::string, Pessoa> cadeiras; //map de string para Pessoa
    public:
        Cinema(int capacidade = 0) : capacidade{capacidade}{}

        std::string adicionarPessoa(Pessoa pessoa, std::string posicao){
            if(cadeiras.find(posicao) != cadeiras.end()){ //se for diferente de meio que adicionar, ele não aceita pois não é o final do map, ou seja, tem alguma coisa ali
                return "Cadeira ocupada\n";
            }else{
                cadeiras.insert(std::pair<std::string, Pessoa>(posicao, pessoa)); //sua chave e msm,insert nas cadeiras, criando novos espaços no map
                return "";
            }
            //verificação
        }

        void remover(std::string id){
            for(auto it = cadeiras.begin(); it != cadeiras.end(); it++){ //vasculha
                if(it->second.getId() == id){ //verficação com a entrada
                    cadeiras.erase(it); //remove com erase na pos
                    return;
                }
            }
            std::cout << "Pessoa inexistente" << std::endl;
        }

        void toString(){
            std::cout << "[";
            for(int i=0; i<this->capacidade; i++){
                if(cadeiras.find(std::to_string(i)) != cadeiras.end()){
                    std::cout<< cadeiras.find(std::to_string(i))->second.toString();
                
                }else{
                    std::cout<< " <-> ";
                }
            }
        std::cout << "]" << std::endl;
        }



};

int main(){
    Cinema cinema(0);
    

    while (true){
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if(cmd == "init"){
            int capacidade; 
            ss >> capacidade;
            cinema = Cinema(capacidade);
        }
        else if(cmd == "add"){
            std::string id, phone, posicao;
            ss >> id >> phone >> posicao;
            Pessoa pessoa(id, phone);
            cinema.adicionarPessoa(pessoa, posicao);
        }
        else if(cmd == "rm"){
            std::string id;
            ss >> id;
            cinema.remover(id);
        }
        else if(cmd == "show"){
            cinema.toString();
        }
        else if(cmd == "end"){
            break;
        }else{
            std::cout << "Comando inexistente" << std::endl;
        }
    }
    return 0;
}