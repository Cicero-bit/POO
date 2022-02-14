#include <iostream>
#include <vector>

class Personagem{
private:    
    bool vivo = true;
    std::string nome{""};
    int vida = 0;
public:
    Personagem(std::string nome = "") : nome{nome}{}

    std::string getNome(){
        return nome;
    }
    void setNome(std::string nome){
        this->nome = nome;
    }
    int getVida(){
        return vida;
    }
    void morrer(){
        vivo = false;
        std::cout << "Personagem morreu ;(" <<  std::endl;
    }
    void ReceberDano(int dano){
        if(vivo = true && vida > dano){
            vida -= dano;
        }else{
            morrer();
        }
    }
};
class Warrior: public Personagem{
private:
    int vida = 300, ataque = 10, speeldmg = 5, mana = 10, stamina = 150;

public:
    Warrior(std::string nome = "") : Personagem{nome}{
        std::cout << nome << " vida: " << vida << std::endl;
    }
    void lancarSpell(Personagem* inimigo){
        inimigo->ReceberDano(speeldmg);
        this->mana -= 25;
    }
    void atacar(Personagem* inimigo){
        inimigo->ReceberDano(ataque);
    }
};

class Mage: public Personagem{
private:
    int vida = 100, ataque = 5, speeldmg = 30, mana = 100, stamina = 50;

public:
    Mage(std::string nome = ""): Personagem{nome}{
        std::cout << nome << " vida: " << vida << std::endl;
    }
    void lancarSpell(Personagem* inimigo){
        inimigo->ReceberDano(speeldmg);
        this->mana -= 25;
    }
    void atacar(Personagem* inimigo){
        inimigo->ReceberDano(ataque);
    }
};

int main(){
  
    Mage Jao = Mage{"Jao"};
    Warrior Ze = Warrior{"Ze"};

    Ze.atacar(&Jao);

    std::cout<< Jao.getVida() << std::endl;

    return 0;
} //este cod não está pronto ainda