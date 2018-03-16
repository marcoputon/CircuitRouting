# CircuitRouting
Repositório destinado ao meu projeto de TCC com o tema "Roteamento de Componentes de Circuitos com Grades Esparsas", no curso de Ciência da Computação da Universidade Federal da Fronteira Sul.

Os algoritmos contidos neste repositório estão relacionados ao problema B da competição ICCAD de 2017. A descrição do problema pode ser conferida neste [link](http://cad-contest-2017.el.cycu.edu.tw/Problem_B/default.html).

A linguagem de programação é C++ e também é utilizado o programa Dot(para gerar as imagens) e a biblioteca [Boost](http://www.boost.org/).

Para compilar, no diretório src/ dê o comando:
```
$ make
```
E para executar:
```
$ ./main <CASO_DE_TESTE> <GERAR_IMAGENS>
```
Onde <CASO_DE_TESTE> é o caminho para algum caso de teste e <GERAR_IMAGENS> é uma flag que quando valer "print" irá gerar alguns arquivos para gerar imagens das grades montadas.

Exemplos:
```
$ ./main ../cases/case1 no
$ ./main ../cases/case-3 print
```

Em src/cases/ há 3 casos de teste disponibilizados no contest (case1, case2 e case3) e os demais casos de teste são casos muito menores criados para ajudar no desenvolvimento.

Para gerar as imagens, utilize o comando:
```
dot -Tps out/grau1.dot -o out/grau1.ps
```
