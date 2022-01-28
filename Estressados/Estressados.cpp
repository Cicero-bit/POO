#include <iostream>
#include <vector> //vetores
#include <math.h> //funções matematicas
#include <algorithm> // biblioteca para usar a função reverse
#include <time.h> // biblioteca para usar a função time

using namespace std;

//Busca

bool existe (vector<int> est, int valor){

   for (int i = 0; i < est.size(); i++){
      if (est[i] == valor) return true;
   }
   return false;
}

int contar (vector<int> est, int valor){

   int cont = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] == valor) cont++;
   }
   return cont;
}

int procurar_valor (vector<int> est, int valor){

   for (int i = 0; i < est.size(); i++){
      if (est[i] == valor) return i;
   }
   return -1;
}

int procura_valor_apartir (vector<int> est, int valor, int posicao){

   for (int i = posicao; i < est.size(); i++){
      if (est[i] == valor) return i;
   }
   return -1;
}

//Melhor Caso

int procurar_menor (vector<int> est){

   int min = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] < est[min]) min = i;
   }
   return est[min];
}

int procurar_maior (vector <int> est){

   int max = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] > est[max]) max = i;
   }
   return est[max];
}

int procurar_menor_pos (vector<int> est){

   int min = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] < est[min]) min = i;
   }
   return min;
}

int procurar_menor_pos_apartir (vector<int> est, int pos){

   int menorApos = pos;

   for (int i = pos; i < est.size(); i++){
      if (est[i] < est[menorApos])
         menorApos = i;
   }
   return menorApos;
}

int procurar_melhor_pos_se (vector<int> est){

   int posHC = 0;

   for (int i = 0; i < est.size(); i++){
      if ((est[i] > 0) && (est[i] < est[posHC])) posHC = i;
   }
   if (est[posHC] > 0){
      return posHC;
   }
   return -1;
}

//Contagem

float calcular_stress_medio (vector<int> est){

   float media = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] < 0) media += est[i] * -1;
      else media += est[i];
   }
   media = media / est.size();
   return media;
}

string mais_homens_ou_mulheres (vector<int> est){

   int contM = 0;
   int contH = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] > 0) contH++;
      else contM++;
   }
   if (contH == contM) return "empate";
   else if (contH > contM) return "homens";
   else return "mulheres";
}

string qual_metade_eh_mais_estressada (vector<int> est){

   int cont1 = 0;
   int cont2 = 0;

   for (int i = 0; i < est.size(); i++){
      if (i < (est.size() / 2)) cont1 += abs(est[i]);
      else cont2 += abs(est[i]);
   }
   if (cont1 == cont2) return "empate";
   else if (cont1 > cont2) return "primeira";
   else return "segunda";
}

bool homens_sao_mais_estressados_que_mulheres(vector<int> est){

   int contM = 0;
   int contH = 0;
   float mediaM = 0;
   float mediaH = 0;

   for (int i = 0; i < est.size(); i++){
      if (est[i] > 0){
         contH++;
         mediaH += est[i];
      }
      else{
         contM++;
         mediaM += est[i] * -1;
      }
   }
   mediaM = mediaM / contM;
   mediaH = mediaH / contH;
   
   if (mediaH > mediaM) return true;
   else return false;
}

//Filter 

vector<int> clonar(const vector<int>& vetor){
   vector<int> copia;

   for (int i = 0; i < (int)vetor.size(); i++){
      copia.push_back(vetor[i]); 
}
   return copia;
}

vector<int> pegar_homens(const vector<int>& vetor){
   vector<int> lista_homens;

   for (int i = 0; i < (int)vetor.size(); i++){
        if (vetor[i] > 0){
        lista_homens.push_back(vetor[i]);
      }
   }
   return lista_homens;
}

vector<int> pegar_calmos(const vector<int>& vetor){
   vector<int> homens_calmos;

   for (int i = 0; i < (int)vetor.size();i++){
      if (vetor[i] < 10){
         homens_calmos.push_back(vetor[i]);
      }
   }
   return homens_calmos;
}

vector<int> mulheres_calmas(const vector<int>& vetor){
   vector<int> mulheres_calmas;

   for(int i = 0; i < (int)vetor.size(); i++){
      if (vetor[i] > -10 && vetor[i] <= -1){
         mulheres_calmas.push_back(vetor[i]);
      }
   }
   return mulheres_calmas;
}

//Acesso

vector<int> inverter_copia(const vector<int>& vetor){
   vector<int> copia_inversa;

   for(int i = 0; i < (int)vetor.size(); i++){
      copia_inversa.push_back(vetor[i]);
   }
   reverse(copia_inversa.begin(), copia_inversa.end());
    
   return copia_inversa;
}

void inverter_inplace(vector<int>& vetor){
   reverse(vetor.begin(), vetor.end()); // função reverse, da bb
   
}

int sortear(const vector<int>& vetor){
   int k;

   srand(time(NULL)); // função rand, da bb

   k = (rand() % 100);

   return vetor[k];
}

void embaralhar(vector<int>& vetor){
   srand(time(NULL));

   int aux;

   for (int i = 0; i < vetor.size(); i++){
      int x = rand() % vetor.size();
      aux = vetor[i];
      vetor[i] = vetor[x];
      vetor[x] = aux;
    }
}

void ordenar(vector<int>& vetor){
   int aux;

   for (int i = 0; i < vetor.size(); i++){
      for (int j = i + 1; j < vetor.size(); j++){
         aux = vetor[i];
            
         if(vetor[i] > vetor[j]){
         vetor[j] = vetor[i];
         vetor[j] = aux;
         }
      }
   }   
}

//Conjuntos

vector<int> exclusivos(const vector<int>& vetor){
   vector<int> sem_repeticao;

   int cont = 0;

   for (int i = 0; i < vetor.size(); i ++){
      for(int j = 0; j < vetor.size(); j++){
         if (i != j){
            if (vetor[i] == vetor[j]){
            cont++;
            }
         }
      }
      if (cont = 0){
      sem_repeticao.push_back(vetor[i]);
      }
    }
   return sem_repeticao;
}

vector<int> diferentes(const vector<int>& vetor){
   vector<int> diferentes;

   int cont = 0;

   for (int i = 0; i < vetor.size(); i++){
      for (int j = i + 1; j < vetor.size(); j++){
         if (i != j){
               if (vetor[i] == vetor[j]){
               cont++;
            }
         }
      }
      if (cont == 0){
      diferentes.push_back(vetor[i]);
    }
   } 
   return diferentes;
}

vector<int> abandonados(const vector<int>& vetor){
   vector<int> restantes;

   for (int i = 0; i < vetor.size(); i++){
      for (int j = i + 1; j < vetor.size(); j++){
         if (i != j){
            if (vetor[i] == vetor[j]){
            restantes.push_back(vetor[i]);
         }
         }
      }
   }
   return restantes;
}

vector<int> ordenar(const vector<int>& vet){
    vector<int> vetornovo = vet;
    int aux;
    int troca = 1;
    while (troca == 1){
        troca = 0;        
        for (int i = 0; i < vetornovo.size(); i++){
            if (vetornovo[i] > vetornovo[i + 1]){
                troca = 1;
                aux = vetornovo[i];
                vetornovo[i] = vetornovo[i + 1];
                vetornovo[i + 1] = aux;
            }
        }
    }
    return vetornovo;
}

//APLICAÇÂO DO ESTRESSADOS 3


void print(vector<int> vet){
   for (int i : vet){
      cout << i << ' ';
   }
}

vector<int> sozinhos(const vector<int>& vet){
   vector<int> vetornovo = vet;
    
   for (int i = 0; i < vetornovo.size(); i++){
        if(vetornovo[i]<0)vetornovo[i]=vetornovo[i]*-1;
   }
   vector<int> vetoraux = vetornovo;

   for (int i = 0; i < vetornovo.size(); i++){
      vetoraux[i]=0;
      for (int j = 0; j < vetoraux.size(); j++){
         if(vetornovo[i]==vetornovo[j]){
         vetoraux[i]++;
         }
      }
   }
   vector<int> vetorfinal;
    
   for (int i = 0; i < vetoraux.size(); i++){
      if(vetoraux[i]==1) vetorfinal.push_back(vetornovo[i]);
   }

return vetorfinal;   
}

void ocorrencias(const vector<int>& vet){
   vector<int> vetornovo = vet;
    
   for (int i = 0; i < vetornovo.size(); i++){
      if(vetornovo[i]<0)vetornovo[i]=vetornovo[i]*-1;
   }
   vector<int> vetoraux = vetornovo;

   for (int i = 0; i < vetornovo.size(); i++){
      vetoraux[i]=0;
      for (int j = 0; j < vetoraux.size(); j++){
         if(vetornovo[i]==vetornovo[j]){
            vetoraux[i]++;
         }
      }
   }
   vector<int> vetorfinal;
   int maior = 0;
   int maiorposicao = 0;
   for (int i = 0; i < vetoraux.size(); i++){
      if(maior<vetoraux[i]){
         maior=vetoraux[i];
         maiorposicao = i;
      } 
   }
    
   cout<<vetornovo[maiorposicao];

    
}

vector<int> recorrentes(const vector<int>& vet){
   vector<int> vetornovo = vet;
    
   for (int i = 0; i < vetornovo.size(); i++){
      if(vetornovo[i]<0)vetornovo[i]=vetornovo[i]*-1;
   }
   vector<int> aux = ordenar(vetornovo);
   vector<int> vetornovoo = ordenar(vetornovo);

   for (int i = 0; i < vetornovoo.size(); i++){
      aux[i]=0;
      for (int j = 0; j < aux.size(); j++){
         if(vetornovoo[i]==vetornovoo[j]){
            aux[i]++;
         }
      }
   }
   vector<int> vetorfinal;
    
   for (int i = 0; i < aux.size(); i++){
      if(aux[i]>1 && vetornovoo[i] != vetornovoo[i+1]) vetorfinal.push_back(vetornovoo[i]);
   }

return vetorfinal; 
}

void briga(const vector<int>& vet){
   vector<int> vetornovo = vet;
   int total=0;
   for (int i = 1; i < vetornovo.size(); i++){
      if(vetornovo[i]>49&&vetornovo[i-1]>29&&vetornovo[i+1]>29) total++;
   }
   cout<<"Essa situação ocorreu "<<total<<" vezes";    

}

vector<int> apaziguado(const vector<int>& vet){
   vector<int> thisvet= vet;
   vector<int> vetornovo{};

   for (int i = 0; i < thisvet.size(); i++){
      if(thisvet[i]<0) thisvet[i] =thisvet[i] * -1;
   }
    
   for (int i =0; i < thisvet.size(); i++){
      if( thisvet[i]>80 &&(thisvet[i-1]<10 || thisvet[i+1]<10))vetornovo.push_back(i);
   }
   return vetornovo;
}

void quantostimes(const vector<int>& vet){
   vector<int> thisvet= vet;
   int qntd=0;
   for (int i = 0; i < thisvet.size(); i++)if((thisvet[i]<0 && thisvet[i+1]>0) || (thisvet[i]>0 && thisvet[i+1]<0))qntd++;
   cout<<qntd;

}

void timep(const vector<int>& vet){
   vector<int> thisvet= vet;
   int quantidade=0;
   int contador = 0;
   int contadormaior = 0;
   int posicao = 0;
   int posicaofinal = 0;
   for (int i = 0; i < thisvet.size(); i++){
      if((thisvet[i]<0 && thisvet[i+1]>0) || (thisvet[i]>0 && thisvet[i+1]<0)){
         quantidade++;
         contador = 0;
      }else{
         contador++;
         posicao = i;
      }

      if(contadormaior < contador){
         contadormaior = contador;
         posicaofinal = posicao;
      }

   }
   posicaofinal++;
   contadormaior++;
   int posfim = posicaofinal - contadormaior+1;
   for (int i = posicaofinal; i >=posfim; i--){
      cout<<thisvet[i]<<" ";
   }
    

}

void sozinhost(const vector<int>& vet){
   vector<int> vetornovo = vet;
   int cont=0;
   for (int i = 1; i < vetornovo.size(); i++){
      if((vetornovo[i]>0 && vetornovo[i-1]<0 && vetornovo[i+1]<0) || (vetornovo[i]<0 && vetornovo[i-1]>0 && vetornovo[i+1]>0) ){
         cont++;
      }
	}
   cout<<"Há "<<cont<<" pessoas sozinhas.";
}

vector<int> casais(const vector<int>& vet){
   vector<int> vetornovo = vet;
   vector<int> casais;
   int aux = 0;
   for (int i = 0; i < vetornovo.size(); i++){
      aux = vetornovo[i] *-1;
      for (int j = 0; j < vetornovo.size(); j++){
         if(vetornovo[j] == aux){
           casais.push_back(vetornovo[i]); 
         }
      }
   }
    
   return casais;
}

vector<int> trios(const vector<int>& vet){
   vector<int> vetornovo = vet;
   vector<int> trios;

   for (int i = 0; i <vetornovo.size(); i++){
      if(vetornovo[i]<0) vetornovo[i] = vetornovo[i] * -1; 
    }

   int aux=0;
   for (int i = 0; i < vetornovo.size(); i++){
      aux = vetornovo[i];
      int qntd = 0;
      for (int j = 0; j < vetornovo.size(); j++){
         if(vetornovo[j] == aux){
            qntd++; 
         } 
      }
   if(qntd>=3){
     trios.push_back(vetornovo[i]); 
   } 
   }
    return trios;
}

vector<int> remove(const vector<int>& vet){
   vector<int> vetornovo = vet;
   int aremover=0;
   cin >> aremover;

   for (int i = 0; i < vetornovo.size(); i++){
      if(vetornovo[i]==aremover) vetornovo.erase(vetornovo.begin()+i);
   }
   return vetornovo;       
}

vector<int> remove2(const vector<int>& vet, int aremover){
   vector<int> vetornovo = vet;
   for (int i = 0; i < vetornovo.size(); i++){
      if(vetornovo[i]==aremover){        
          vetornovo.erase(vetornovo.begin()+i);
      }
    }
 return vetornovo;       
}

vector<int> insert(const vector<int>& vet){
   vector<int> vetornovo = vet;
   int valor=0;
   int posicao=0;
   cout<<"Insira valor e posição";
   cin >> valor;
   cin >> posicao;

   vector<int>::iterator it;

   it = vetornovo.begin()+posicao;
   it = vetornovo.insert (it, valor);

return vetornovo;
}

vector<int> dance(const vector<int>& vet){
   vector<int> vetornovo = vet;
   int bol = 1;
   for (int i = 0; i < vetornovo.size(); i++){
      if(vetornovo[i]<0)vetornovo[i] = vetornovo[i]* -1;    
   }
   while(bol == 1){
      bol = 0;
      for (int i = 0; i < vetornovo.size(); i++){
         if(vetornovo[i] ==vetornovo[i+1]){
            vetornovo = remove2(vetornovo,vetornovo[i]);
            vetornovo = remove2(vetornovo,vetornovo[i+1]);
            bol = 1;
         }
      }
   }
   return vetornovo;
}

// ainda n chamei algumas funções 
int main(){
    
   //Busca

   cout << existe({-9, - 8, 3, 2, -98, 1}, 1) << "\n"; //true
   cout << existe({-9, - 8, 3, 2, -98, 1}, -1) << "\n"; //false

   cout << contar({1, 2, -98, 4, 5, 9, 12, 2, -3, 2}, 2) << "\n"; //3
   cout << contar({1, 2, -98, 4, 5, 9, 12, 2, -3}, 3) << "\n"; //0

   cout << procurar_valor({1, 3, 45, -9, -12, -99, 2, -99}, -99) << "\n"; //5
   cout << procurar_valor({1, 3, 45, -9, -12, -99, 2, -99}, -2) << "\n"; //-1

   cout << procura_valor_apartir({1, 3, 45, -9, -12, -99, 2, -99}, -99, 6) << "\n"; //7
   cout << procura_valor_apartir({1, 3, 45, -9, -12, -99, 2, -99}, 2, 5) << "\n"; //6


   //Melhor Caso

   cout << procurar_menor({1, -55, 12, 99, 87, -2, 7}) << "\n"; //-55

   cout << procurar_maior({1, -55, 12, 99, 87, -2, 7}) << "\n"; //99

   cout << procurar_menor_pos({1, -55, 12, 99, 87, -2, 7}) << "\n"; //1

   cout << procurar_menor_pos_apartir({1, -55, 12, 99, 87, -2, 7}, 3) << "\n"; //5

   cout << procurar_melhor_pos_se({5, -55, 12, 99, 87, 2, 7}) << "\n"; //5

   //Contagem 

   cout << calcular_stress_medio({5, -55, 10, 14, -20}) << "\n"; //20.8

   cout << mais_homens_ou_mulheres({5, -55, 10, 14, -20}) << "\n"; //homens
   cout << mais_homens_ou_mulheres({-55, 10, 14, -20}) << "\n"; //empate
   cout << mais_homens_ou_mulheres({5, -55, -10, 14, -20}) << "\n"; //mulheres

   cout << qual_metade_eh_mais_estressada({60, 3, -4, 9, 12, 33}) << "\n"; //primeira
   cout << qual_metade_eh_mais_estressada({66, 1, 2, 99, 5, 2}) << "\n"; //segunda
   cout << qual_metade_eh_mais_estressada({60, 2, 3, 5, 59, 1}) << "\n"; //empate

   cout << homens_sao_mais_estressados_que_mulheres({-5, -55, 70, 14}) << "\n"; //true
   cout << homens_sao_mais_estressados_que_mulheres({-55, 10, 14, -20}) << "\n";  //false

   //Parte 3

   vector<int> vetor{60, 3, -4, 9, 12, 33};

   cout << clonar(vetor);
   cout << pegar_homens(vetor);
   cout << pegar_calmos(vetor);
   cout << mulheres_calmas(vetor);
   cout << inverter_copia(vetor);
   cout << inverter_inplace(vetor);
   cout << sortear(vetor);
   cout << embaralhar(vetor);
   cout << ordenar(vetor);
   cout << exclusivos(vetor);
   cout << diferentes(vetor);
   cout <<abandonados(vetor);

   return 0;
}