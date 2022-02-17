#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

class AccountException : public std::runtime_error{
public:
    AccountException(std::string message): runtime_error(message){} //throws
};

class Account{
protected:
    int id = 0;
    float balance = 0.0;
    std::string type = "", clientId = "";;

public:
    Account(int id, std::string clientId) : id{id}, clientId{clientId}{}

    virtual ~Account(){}

    virtual void monthlyUpdate() = 0;

    float getBalance(){
        return this->balance;
    }

    std::string getClientId(){
        return this->clientId;
    }

    int getId(){
        return this->id;
    }

    void deposit(float value){
        this->balance += value;
    }

    void transfer(std::shared_ptr<Account> accountTo, float value){ //chama o accont que vai ter o seu id e vai receber o value de tranferencia, o ptr refere a uma account que for criada, uma variavel de account
        if (accountTo == nullptr){ // check se a conta que vai receber existe
            throw AccountException("Conta enviada não existe"); //excessão pra caso n existir 
        }
        if (value > this->balance){ // caso o balance de account n for > value pedido
            throw AccountException("Saldo insuficiente");
        }
        this->balance -= value; 
        accountTo->balance += value; 
    }

    void withdraw(float value){ //função para ser chamada
        if (value > this->balance){
            throw AccountException("Saldo insuficiente");
        }

        this->balance -= value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Account& account){
        os << account.id << ":" << account.clientId << ":" << account.balance << ":" << account.type;
        return os;
    }
};

class Conta_Corrente : public Account{
public:
    Conta_Corrente(int id, std::string clientId) : Account(id, clientId){ //cria uma account pra essa acount com o att diferente
        this->type = "CC";
    }

    void monthlyUpdate() override{ //override para essa classe
        this->balance -= 20;
    }
};

class ContaPoupanca : public Account{  //cria uma account pra essa acount com o att diferente
    public:
    ContaPoupanca(int id, std::string clientId) : Account(id, clientId){
        this->type = "CP";
    }

    void monthlyUpdate() override{
        this->balance += this->balance * 0.01;
    }
};

class Client{
private:
    std::vector<std::shared_ptr<Account>> accounts ={}; //vector para pooder cirar mais de um client e mais a frente atribuir mais de um valor
    std::string clientId = "";

public:
    Client(std::string clientId = "") : clientId{clientId}{}

    std::vector<std::shared_ptr<Account>> getAccounts() const{
        return this->accounts;
    }

    std::string getClientId() const{
        return this->clientId;
    }

    void addAccount(std::shared_ptr<Account> account){
        if (account == nullptr){
            throw AccountException("Conta inexistente");
        }
    this->accounts.push_back(account);
    }

    friend std::ostream& operator<<(std::ostream& os, const Client& client){
        os << "- " << client.clientId << " [";

        for (int i = 0; i < (int) client.accounts.size(); i++){
            if (i > 0){
                os << ", " << client.accounts[i]->getId();
            }else{
            os << client.accounts[i]->getId();
            } 
        }
    os << "]";
    return os;
    }
};

class Bank{
private:
    std::map<int, std::shared_ptr<Account>> accounts ={};
    std::map<std::string, std::shared_ptr<Client>> clients ={};
    int nextAccountId = 1;

    std::shared_ptr<Account> getAccount(int id){
    for (auto account : this->accounts){
        if (account.first == id){
            return account.second;
        }
    }
    return nullptr;
    }

public:
    Bank(){}

    void addClient(std::string clientId){ //recebe o nome // esse add eu fiz com ajuda de uns colege de classe
        auto [ppos, spos] = this->clients.insert(std::make_pair(clientId, std::make_shared<Client>(clientId))); //para verificar 

        if (!spos){
            throw AccountException("Cliente ja existe");
        }

        std::shared_ptr<Account> ContaCorrente = std::make_shared<Conta_Corrente>(nextAccountId, clientId); //cria a cc
        this->accounts.insert(std::make_pair(nextAccountId, ContaCorrente));//com o pair, a cc recebe esses valores como uma "nova cc", mesma coisa pra cp 
        nextAccountId += 1;
      
        std::shared_ptr<Account> Poupanca = std::make_shared<ContaPoupanca>(nextAccountId, clientId); //cria a pp
        this->accounts.insert(std::make_pair(nextAccountId, Poupanca));
        nextAccountId += 1;

        this->clients[clientId]->addAccount(ContaCorrente);//chama,atribui
        this->clients[clientId]->addAccount(Poupanca);
    }

    void deposit(int accountId, float value){ //ponteiro pra acount e logica basica
        auto account = this->getAccount(accountId);

        if (account == nullptr){
            throw AccountException("Conta inexistente");
        }

        account->deposit(value);
    }

    void withdraw(int accountId, float value){ //ponteiro pra acount e logica basica
        auto account = this->getAccount(accountId);

        if (account == nullptr){
            throw AccountException("Conta inexistente");
        }

        account->withdraw(value);
    }

    void transfer(int accountIdFrom, int accountIdTo, float value){ //recebe o ponteiro pras 2 contas e chama o transfer basico da accont
        auto accountFrom = this->getAccount(accountIdFrom);
        auto accountTo = this->getAccount(accountIdTo);

        if (accountFrom == nullptr || accountTo == nullptr){
            throw AccountException("Conta inexistente");
        }

    accountFrom->transfer(accountTo, value);
    }

    void monthlyUpdate(){ //altera alguns valores 
        for (auto& account : this->accounts){
            account.second->monthlyUpdate();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Bank& Bank){ //tostring
        for (auto client : Bank.clients){
            os << *(client.second) << "\n";
        }
        os << "---------------------------\n";
        for (auto account : Bank.accounts){
            os << *(account.second) << "\n";
        }
    return os;
    }
};

int main(){
    Bank Bank;
    while(true){
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;
    
        try{
            if(cmd == "add"){
                std::string clientName{""};
                ss >> clientName;

                Bank.addClient(clientName);
            }else if(cmd == "wid"){
                int accountId;
                float value;
                ss >> accountId >> value;
        
                Bank.withdraw(accountId, value);
            }else if(cmd == "depo"){
                int accountId;
                float value;
                ss >> accountId >> value;
        
                Bank.deposit(accountId, value);
            }else if(cmd == "trf"){
                int accountIdFrom, accountIdTo;
                float value;
                ss >> accountIdFrom >> accountIdTo >> value;
        
                Bank.transfer(accountIdFrom, accountIdTo, value);
            }else if(cmd == "att"){
                Bank.monthlyUpdate();
            }else if(cmd == "show"){
                std::cout << Bank << "\n";
            }else if(cmd == "end"){
                break;
            }else{
                std::cout << "Comando inexistente\n";
            }
        }catch (AccountException& e){
            std::cout << "Erro de : " << e.what() << "\n";
        }
    }
}