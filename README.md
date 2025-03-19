#  Exercícios de Programação Orientada a Objeto

Este repositório contém a resolução de exercícios de programação em C++.

##  Primeiro Exercício: Estatísticas de um arquivo de dados

Este programa em C++ calcula a média, o desvio padrão e o histograma de um conjunto de valores numéricos lidos de um arquivo de entrada.

###  Entrada

* Os dados de entrada são lidos de um arquivo cujo nome é fornecido como argumento na linha de comando. [cite: 2, 3]
* O arquivo contém uma sequência de valores de ponto flutuante separados por espaços em branco, mudanças de linha ou tabulações. [cite: 3]
* O número de caixas do histograma também é lido da linha de comando. [cite: 5]

###  Cálculos

O programa calcula os seguintes valores:

* **Número de valores (N):** O número total de valores lidos do arquivo. [cite: 4]
* **Média:** A média dos valores, calculada pela fórmula:
    
    $\overline{x}=\frac{1}{N}\sum_{i=0}^{N-1}x_{i}.$ [cite: 4]
    
* **Desvio padrão amostral:** O desvio padrão amostral, calculado por:
    
    $\sigma=\sqrt{\frac{\sum_{x=0}^{N-1}(x_{i}-\overline{x})^{2}}{N-1}}.$ [cite: 4]
    
* **Histograma:** Um histograma com B caixas. [cite: 5] O histograma é computado da seguinte forma:
    1.  O número de caixas B é lido da linha de comando. [cite: 5]
    2.  Os valores mínimo ($x_{min}$) e máximo ($x_{max}$) são encontrados. [cite: 6]
    3.  O tamanho das caixas ($\Delta$) é calculado:
        
        $\Delta=\frac{x_{max}-x_{min}}{B}.$ [cite: 7]
        
    4.  Um vetor de contadores inteiros de tamanho B é inicializado com zeros. [cite: 7]
    5.  Para cada valor lido ($x_{i}$), a caixa correspondente ($k_{i}$) é determinada:
        
        $k_{i}=\{\begin{matrix}\lfloor\frac{x_{i}-x_{min}}{\Delta}\rfloor,&x_{i}\ne x_{max}\\ B-1,&x_{i}=x_{max}\end{matrix}$ [cite: 8]
        
        onde $\lfloor y\rfloor$ é o maior inteiro menor ou igual a y. [cite: 8]
    6.  O contador da caixa $k_{i}$ é incrementado. [cite: 9]

###  Saída

Os resultados são escritos na saída padrão (`std::cout`) no seguinte formato:

1.  O número de elementos lidos (N). [cite: 9, 10]
2.  A média dos valores ($\overline{x}$). [cite: 9, 10]
3.  O desvio padrão ($\sigma$). [cite: 9, 10]
4.  Os dados do histograma em B linhas, com cada linha contendo:
    * Início da caixa. [cite: 11, 12]
    * Final da caixa. [cite: 11, 12]
    * Contador de elementos na caixa. [cite: 11, 12]

###  Organização do código

* O código está em um único arquivo .cpp. [cite: 13, 14, 15, 16, 17]
* O código é dividido nas seguintes funções:
    * Uma função para ler os dados do arquivo e retornar um vetor de `double`. [cite: 14, 15, 16, 17]
    * Uma função para calcular a média e o desvio padrão, dado o vetor de dados. [cite: 14, 15, 16, 17]
    * Uma função para calcular o histograma, dado o vetor de dados e o número de caixas. Esta função retorna o vetor de informações das caixas e o vetor de contadores. O vetor de informações das caixas contém os limites de cada caixa, e o vetor de contadores indica quantos valores caem em cada caixa. [cite: 14, 15, 16, 17, 18, 19]
    * A função `main` lê os argumentos da linha de comando, chama as funções auxiliares e imprime os resultados. [cite: 20, 21]
* O código começa com os protótipos das funções, seguido pela função `main` e depois pelas outras funções. [cite: 21]
* Nomes de variáveis e funções são descritivos. [cite: 22, 23]
* O código contém comentários para facilitar a compreensão. [cite: 22, 23]

##  Segundo Trabalho: Cálculo de velocidades com erros

Este trabalho envolve a modificação de um programa em C++ que calcula a aceleração gravitacional e as velocidades de um corpo em queda livre. O programa original lê informações de tempo e posição (altura) de um arquivo, onde as informações de tempo e altura são apresentadas com o erro experimental. O programa calcula a propagação de erros assumindo erros independentes e distribuição gaussiana.

A tarefa consiste em:

* Transformar a `struct Measurement` em uma `class Measurement` com encapsulamento de seus membros.
* Implementar as operações aritméticas sobre objetos do tipo `Measurement` por meio de sobrecarga de operadores.

##  Terceiro Trabalho: Herança e polimorfismo

Este trabalho utiliza um código que implementa uma classe para armazenar e consultar valores únicos de forma eficiente. A classe original permite inserir uma quantidade ilimitada de valores.

A tarefa é:

* Usar herança para criar uma nova classe similar, que terá um limite máximo de valores especificado no construtor.
* Lançar uma exceção quando se tentar inserir mais valores do que o permitido.
* Garantir que o código funcione com polimorfismo, se necessário.

##  Quarta Prática: Templates

Este trabalho reutiliza o código da classe do trabalho anterior.

A tarefa é:

* Transformar essa classe em um template, para que possa armazenar qualquer tipo de objeto que tenha o operador `<` sobrecarregado.
* Opcional: Transformar em templates tanto essa classe quanto a sua derivada do trabalho anterior (a sintaxe para isso é mais complexa).
