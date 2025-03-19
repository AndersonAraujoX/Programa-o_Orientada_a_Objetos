#include <algorithm>
#include <iostream>
#include <vector>

// Classe que mantem um conjunto de valores sem duplicacao e em ordem crescente.
// Permite verificar a existencia ou nao de um valor e pegar uma faixa de
// elementos entre dois valores especificados.

class OrderedUniqueValues {
  // Invariante:
  // Se size() > 1 && 0 <= i < size()-1 então _data[i] < data[i+1]
protected:

  std::vector<int> _data;

public:
  // Sinonimmo de um tipo para iterador para os elementos.
  using const_iterator = std::vector<int>::const_iterator;

  // Verifica se um elementos com o dado valor foi inserido.
  bool find(int value) {
    // Como os dados estao ordenados em _data, entao basta fazer uma busca
    // binaria.
    return std::binary_search(begin(_data), end(_data), value);
  }

  // Retorna um par de iteradores para o primeiro e um depois do ultimo
  // valores que sao maiores ou iguais a min_value e menores ou iguais a
  // max_value.
  std::pair<const_iterator, const_iterator> find_range(int min_value,
                                                       int max_value) const {
    // Dados ordenados em _data, entao podemos usar lower_bound e upper_bound.
    // Encontra o primeiro elemento que tem valor maior ou igual a min_value.
    auto first = std::lower_bound(begin(_data), end(_data), min_value);
    // Encontra o primeiro elemento que tem valor maior do que max_value.
    auto last = std::upper_bound(begin(_data), end(_data), max_value);
    return {first, last};
  }

  // Numero de elementos correntemente armazenados.
  size_t size() const { return _data.size(); }

  
  // Insere um novo elemento, se nao existir ainda.
  void virtual insert(int value) {

    auto [first, last] = std::equal_range(begin(_data), end(_data), value);

    if (first == last) {
      _data.insert(last, value);
    }
  }
 
};
 class limite : public OrderedUniqueValues {
    size_t _limit;
   public:
    limite(int value=0):_limit(value){
  }
   void insert(int value)override {

    auto [first, last] = std::equal_range(begin(_data), end(_data), value);

    if (first == last) {
      if(_data.size()<_limit){
        _data.insert(last, value);
      }
      else{
      std::cerr<<"Excedeu o intervalo "<<value<<" é o valor que excedeu";
      std::exit(1);
    }
    }
  }
};
int main(int, char *[]) {
  // Alguns testes simples.
  std::vector<int> some_values{7, -10, 4, 8, -2, 9, -10, 8, -5, 6, -9, 5};
  std::vector<size_t> some_sizes{1, 2, 3, 4, 5, 6, 6, 6, 7, 8, 9, 10};
  OrderedUniqueValues ouv;
  for (size_t i = 0; i < some_values.size(); ++i) {
    ouv.insert(some_values[i]);
    if (ouv.size() != some_sizes[i]) {
      std::cerr << "Erro de insercao: indice " << i
                << ", valor: " << some_values[i]
                << ", tamanho esperado: " << some_sizes[i]
                << ", tamanho obtido: " << ouv.size() << std::endl;
    }
  }
  //novo vetor
  std::vector<int>vetor2{5,7,9,10,18,-7,15,-12};
  limite tamanho(8);//limite do vetor
  for(size_t j=0;j<vetor2.size();++j){
    tamanho.insert(vetor2[j]);
  }

  for (auto x : some_values) {
    if (!ouv.find(x)) {
      std::cerr << "Nao achou valor inserido " << x << std::endl;
    }
  }

  auto [first1, last1] = ouv.find_range(0, 9);
  for (auto current = first1; current != last1; ++current) {
    if (*current < 0) {
      std::cerr << "Erro na selecao dos valores nao-negativos: " << *current
                << std::endl;
    }
  }
  auto [first2, last2] = ouv.find_range(-10, 0);
  for (auto current = first2; current != last2; ++current) {
    if (*current >= 0) {
      std::cerr << "Erro na selecao dos valores negativos: " << *current
                << std::endl;
    }
  }
  return 0;
}
