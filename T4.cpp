#include <algorithm>
#include <iostream>
#include <vector>

// Classe que mantem um conjunto de valores sem duplicacao e em ordem crescente.
// Permite verificar a existencia ou nao de um valor e pegar uma faixa de
// elementos entre dois valores especificados.
template<typename T>
class OrderedUniqueValues { 
  // Invariante:
  // Se size() > 1 && 0 <= i < size()-1 então _data[i] < data[i+1]
  std::vector<T>  _data;

public:

  // Sinonimmo de um tipo para iterador para os elementos.
  using const_iterator = typename std::vector<T>::const_iterator;

  // Verifica se um elementos com o dado valor foi inserido.
  bool find(T value) {
    // Como os dados estao ordenados em _data, entao basta fazer uma busca
    // binaria.
    return std::binary_search(begin(_data), end(_data), value);
  }

  // Retorna um par de iteradores para o primeiro e um depois do ultimo
  // valores que sao maiores ou iguais a min_value e menores ou iguais a
  // max_value.
  std::pair<const_iterator, const_iterator> find_range(T min_value,
                                                       T max_value) const {
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
  void insert(int value) {
    auto [first, last] = std::equal_range(begin(_data), end(_data), value);
    if (!(first < last) && !(last<first)) {
      _data.insert(last, value);
    }
  }
};


int main(int, char *[]) {
  // Alguns testes simples.
  std::vector<double> some_values{7.0, -10.0, 4.0, 8.0, -2.0, 9.0, -10.0, 8.0, -5.5, 6.7, -9.6, 5.7};
  std::vector<size_t> some_sizes{1, 2, 3, 4, 5, 6, 6, 6, 7, 8, 9, 10};
  OrderedUniqueValues<int> ouv;
  for (size_t i = 0; i < some_values.size(); ++i) {
    ouv.insert(some_values[i]);
    if (ouv.size()<some_sizes[i] && some_sizes[i]<ouv.size()) {
      std::cerr << "Erro de insercao: indice " << i
                << ", valor: " << some_values[i]
                << ", tamanho esperado: " << some_sizes[i]
                << ", tamanho obtido: " << ouv.size() << std::endl;
    }
  }

  for (auto x : some_values) {
    if (!ouv.find(x)) {
      std::cerr << "Nao achou valor inserido " << x << std::endl;
    }
  }

  auto [first1, last1] = ouv.find_range(0, 9);
  for (auto current = first1; (current<last1) && (last1<current); ++current) {
    if (*current < 0) {
      std::cerr << "Erro na selecao dos valores nao-negativos: " << *current
                << std::endl;
    }
  }
  auto [first2, last2] = ouv.find_range(-10, 0);
  for (auto current = first2; (current < last2) && (last2< current) ; ++current) {
    if ( 0 <= *current) {
      std::cerr << "Erro na selecao dos valores negativos: " << *current
                << std::endl;
    }
  }
  return 0;
}