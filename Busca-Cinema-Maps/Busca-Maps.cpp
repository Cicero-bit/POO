#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

class Fone{
    private:
        std::string telefone;
        std::string nome;
    public:
        Fone(std::string telefone ="", std::string nome="") : nome{nome}, telefone{telefone}{
            this->telefone = telefone;
            this->nome = nome;
        }
        bool isvalid(std::string telefone){
            std::string::iterator i; //iterator para conseguir percorrer e receber a posição, o andador
            std::string::iterator j;
            std::string ver {"0123456789()."}; 
            int aux {0};

            for (i = telefone.begin(); i != telefone.end(); ++i){       //loop de auteificação, percorre e verifica se o telefone, string, se encaixa na string ferificadora
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
            return true; //true para ok
        }    

        void setNome(std::string nome){
            this->nome = nome;
        }

        std::string getNome(){
            return this->nome;
        }

        void settelefone(std::string telefone){
            if(isvalid(telefone)){
                this->telefone = telefone;
            }
        }

        std::string gettelefone(){
            return this->telefone;
        }
};

class Contato{
    private:
        std::string prefix="->";
        std::string nome;
    public:
        std::vector<Fone> fones;
        
        Contato(std::string nome=""){
            this->nome = nome;
        }
        bool addFone(Fone fone){
            for(Fone &f : fones){
                if(f.gettelefone() == fone.gettelefone()){
                    return false;
                }
            }
            this->fones.push_back(fone);
            return true;
        }
      
        void rmFone(int index){
            this->fones.erase(this->fones.begin()+index);
        }

        std::string getNome(){
            return this->nome;
        }

        void setNome(std::string nome){
            this->nome = nome;
        }

        std::string getFones(){
            std::stringstream ss;
            for(int i=0; i<(int)fones.size(); i++){
                ss << this->prefix << this->fones[i].gettelefone() << std::endl;
            }
            return ss.str();
        }
        
        std::string toString(){
            std::stringstream ss;
            for(int i=0; i<(int)fones.size(); i++){
                ss << i << " [ " << fones[i].getNome() << " : " << fones[i].gettelefone() << " ]" << std::endl;
            }
            return ss.str();
        }
};

class Agenda{
    private:
        std::map<std::string, Contato*> contatos;
    public:

        bool addContato(Contato& contato){
            Contato* contatoNovo = contatos[contato.getNome()];
            if(contatoNovo == nullptr){
                contatos[contato.getNome()] = &contato;
                return true;
            }
            return false;
        }
        
        bool rmContato(std::string nome){
            return this->contatos.erase(nome);
        }
        
        void searchContato(std::string nome){
            bool encontrado = false;
            for(auto& c : this->contatos){
                if(c.first.find(nome) != std::string::npos || c.second->getFones().find(nome) != std::string::npos){
                    std::cout << c.second->toString() << std::endl;
                    encontrado = true;
                }
            }
            if(!encontrado){
                std::cout << "Contato inexistente" << std::endl;
            }

        }
        
        Contato* getFirstContato(std::string nome){
            return contatos.begin()->second;
        }

        std::string toString(){
            std::stringstream ss;
            ss << "Contatos: " << std::endl;
            for(auto it = contatos.begin(); it != contatos.end(); it++){
                ss << it->second->toString() << std::endl;
            }
            return ss.str();
        }

        Contato* getContato(std::string nome){
            return contatos[nome];
        }
};

int main(){
    Contato* contatoatual = nullptr;
    Agenda agenda;
    Fone fone;
    
    while(true){
        std::string line, cmd;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> cmd;

        if(cmd == "init"){
            std::string nome, id, telefone;
            ss >> nome >> telefone >> id;
            Contato* aux = new Contato(nome);
            if(fone.isvalid(telefone)){
                if(agenda.addContato(*aux)){
                    contatoatual = aux;
                }else{
                    contatoatual = agenda.getContato(nome);
                }
                fone = Fone(telefone, id);
                if(contatoatual->addFone(fone)){
                    std::cout << "Adicionado" << std::endl;
                }else{
                    std::cout << "Contato ja existe" << std::endl;
                }
                std::cout << contatoatual->toString() << std::endl;
            }else{
                std::cout << "Numero invalido" << std::endl;
            }

        }
        else if(cmd == "rm"){
            std::string nome;
            ss >> nome;
            if(agenda.rmContato(nome)){
                std::cout << "Contato deletado" << std::endl;
                contatoatual = agenda.getFirstContato(nome);
            
            }else{
                std::cout << "Contato inexistente" << std::endl;
            }    
        }
        else if(cmd == "search"){
            std::string nome;
            ss >> nome;
            agenda.searchContato(nome);
        }
        else if(cmd == "show"){
            std::cout << agenda.toString() << std::endl;
        }
        else if(cmd == "end"){
            break;
        }else{
            std::cout << "Comando invalido" << std::endl;
        }
    }
}