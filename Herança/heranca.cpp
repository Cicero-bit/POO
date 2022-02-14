#include <iostream>
#include <vector>

class Personagem{

    bool alive = true;
    std::string nome;
    int vida = 100, ataque = 10, speeldmg = 10, mana = 10, stamina = 10;
public:
    Personagem(){
        std::cout << "Personagem ";
    }

    std::string getNome(){
        return nome;
    }
    void setNome(std::string nome){
        this->nome = nome;
    }
    int getVida(){
        return vida;
    }
    int getMana(){
        return mana;
    }
    bool status(){
        return alive;
    }
    void morrer(){
        alive = false;
        std::cout << "Personagem morreu ;(" <<  std::endl;
    }
    void ReceberDano(int dano){
        if(status() == true && vida > dano){
            vida -= dano;
        }else{
            std::cout << "Dano d+ ";
            morrer();
            vida = 0;
        }
    }
};
class Warrior: public Personagem{
    std::string nome;
    int vida = 100, ataque = 20, speeldmg = 5, mana = 10, stamina = 150;
public:
    Warrior(std::string nome = "") : nome{nome}{
        std::cout << nome << " -> Class Warrior / VIDA: " << vida << std::endl;
    }
    void ReceberDano(int dano){
        if(status() == true && vida > dano){
            vida -= dano;
        }else{
            std::cout << "Dano d+ ";
            morrer();
            vida = 0;
        }
    }
    void atacar(Personagem* inimigo){
        if (stamina >= ataque){
            inimigo->ReceberDano(ataque);
            stamina -= ataque;
        }
    }
    void regenerar(){
        if(stamina > 10){
            vida += (stamina/2);
            stamina/2;
        }
    }
};

class Mage: public Personagem{
    std::string nome;
    int vida = 100, ataque = 10, speeldmg = 30, mana = 100, stamina = 50;
public:
    Mage(std::string nome = ""): nome{nome}{
        std::cout << nome << " -> Class Mage / VIDA: " << vida << std::endl;
    }
    void ReceberDano(int dano){
        if(status() == true && vida > dano){
            vida -= dano;
        }else{
            std::cout << "Dano d+ ";
            morrer();
            vida = 0;
        }
    }
    void lancarSpell(Personagem* inimigo){
        if(mana >= speeldmg){
            inimigo->ReceberDano(speeldmg);
            mana -= speeldmg;
        }
    }
    void manaregen(){
        if (mana < 10){
            stamina -= 10;
            mana = 100;
        }
    }
};

class Fire_Mage : public Mage{};

int main(){
  
    Mage Jao{"Jao"};
    Warrior Ze{"Ze"};

    Ze.atacar(&Jao);
    Jao.lancarSpell(&Ze);

    std::cout << "Vida Jao depois do ataque: " << Jao.getVida() << std::endl;
    std::cout << "Vida Ze depois do ataque: " << Ze.getVida() << std::endl;

    return 0;
} 