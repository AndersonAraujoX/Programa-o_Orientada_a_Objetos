#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <conio.h>

std::vector<double> entrada(const char* chart);
std::vector<double> media_desvio(std::vector<double>const &z);
std::vector<double> histograma(std::vector<double>const &z,int B);

int main(int argc,char *argv[]){
 int B;

 std::ofstream saida ("Saida.dat");

 std::vector<double> med_des;

 std::vector<double> histo;
 //o valor do histrograma
 B=atoi(argv[2]);

 //entrada dos dados num arquivo
 //função que íra realizar media e desvio da entrada
 med_des = media_desvio(entrada(argv[1]));

 //essa função realiza histromagrama da imagem da em função do valor que B que o usuario coloco
 histo = histograma(entrada(argv[1]),B);


 //enviar os dados para o arquivo
 for(int i=0;i<3;i++){
 saida<<med_des[i]<<"\n";
 }
 for(int i=0;i<B*3;i+=3){
 saida<<histo[i]<<" "<<histo[i+1]<<" "<<histo[i+2]<<"\n";
 }


 saida.close();

 return 0;
}

//função de entrada.
std::vector<double> entrada(const char*  chart){
std::ifstream entrada(chart);
int i{0};
double dados;
std::vector<double> valores;
while (entrada >> dados) 
{
    valores.push_back(dados);
//inseri os dados em um vetor
}
return valores;
}


std::vector<double> media_desvio(std::vector<double>const &z){
    double soma{0},media{0},desvio{0},i{0.0};
    std::vector<double>val_imp(3);
 //media
 for (auto x: z){
     //somatória de todos os dados
     soma+=x;
     //quantidade de dados
     ++i;
 }


 val_imp[0]=i;
 val_imp[1]=soma/i;
 soma=0.0;

//desvio
 for(auto x: z){
     soma+=pow((x-val_imp[1]),2.0);
 }
 val_imp[2]=pow((soma/(i-1)),0.5);
 return val_imp;
}



std::vector<double> histograma(std::vector<double>const &z,int B){

double max,min,delta,cont{0},inf,sup;
int i{0};
max=z[0];
min=z[0];
std::vector<double>imp(3*B);


//saber o valor mínimo e máximo
for (auto var:z){
    //caso tenha um valor maior substituir como max
    if(var > max){
    max=var;
    }
    //caso tenha um valor menor que o anterior substituir
    if(var<min){
    min=var;
    }
}


delta=(max-min)/B;
inf=min;
sup=min+delta;



//verifica os dados em intervalos de delta
for(int j=0;j<B;j++){
    imp[i]=inf;
    imp[i+1]=sup;
    for(auto var:z){
    //verificar se a variavel está no intervalo entre máximo e o mínimo 
    if(inf<=var  && var<=sup){
        //contador
        cont+=1;
    }

    }
    imp[i+2]=cont;
    inf+=delta;
    sup+=delta;
    cont=0;
    i+=3;
}


return imp;
}


