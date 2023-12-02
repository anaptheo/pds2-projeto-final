# Sistema da Locadora PDS

## Descrição do Projeto
O Sistema da Locadora PDS é uma aplicação desenvolvida como trabalho final da disciplina de Programação e Desenvolvimento de Software II (PDS II) do curso de Sistemas de Informação na UFMG. Este projeto implementa um sistema abrangente de aluguel de filmes, proporcionando funcionalidades como cadastro de filmes e clientes, processos de locação, devolução de filmes e gerenciamento do catálogo.

## Equipe
- Victoria Flores
- Raquel Xavier
- Flávio Soriano
- Isadora Horta
- Ana Paula Theobald

## Contexto do Projeto
O Sistema da Locadora PDS visa otimizar as operações de uma locadora de filmes, oferecendo soluções para desafios comuns encontrados no gerenciamento de catálogos, controle de estoque, administração de clientes e operações de locação.

## Tecnologias Utilizadas
- **Linguagem de Programação:** C++
- **Compilação:** Makefile
- **Documentação:** Doxygen
- **Testes:** Biblioteca doctest
- **Controle de Versão:** Git e GitHub

## Estrutura do Projeto
O projeto é organizado em classes, cada uma responsável por aspectos específicos do sistema:
- `formatacao`: Implementa métodos para formatação de strings.
- `locacao`: Contém métodos e atributos relacionados às operações de locação.
- `filme`: Classe base que engloba atributos e métodos comuns a todos os tipos de filmes.
- `dvd`, `bluray`, `fita`: Classes que herdam de `filme` e implementam características específicas.
- `cliente`: Classe que gerencia informações e operações relacionadas aos clientes.
- `sistema`: Classe que administra operações do sistema, evitando sobrecarregar o arquivo principal.

## Funcionalidades Principais
1. **Cadastro de Filmes e Clientes:**
   - Permite o registro de novos filmes e clientes no sistema.

2. **Locação e Devolução de Filmes:**
   - Facilita o processo de aluguel e devolução de filmes, mantendo o controle do estoque.

3. **Listagem do Catálogo e Clientes:**
   - Apresenta informações detalhadas sobre os filmes disponíveis e a base de clientes.

## Funcionalidades Extras
As seguintes funcionalidades extras foram implementadas:
- Leitura de arquivo pode ser utilizada para qualquer operação, não apenas cadastrar filme.
- Implementação de pontuação de fidelidade, onde cada aluguel de filme vale 1 ponto e a cada 5
pontos adquiridos o cliente ganha um desconto de R$10,00 na hora da devolução.
- Implementação do aluguel de blurays.
- Implementação do aluguel de aparelho leitor de bluray.

## Diferenças de input
Para conseguirmos trabalhar com nomes compostos para filmes, mudamos a ordem dos parâmetros
nos inputs de Cadastrar Filme. A ordem é:
- CF <tipo D|B|F> (dvd, bluray ou fita) <quantidade> <codigo> <categoria> (para dvd e bluray) <nome_do_filme>
E quando se aluga um filme do tipo bluray, pode se adicionar o parâmetro ALUGAR_APARELHO entre os parâmetros 
de categoria e nome do filme para solicitar o aluguel de um aparelho (que custa R$20,00). O comando fica assim:
- CF B <quantidade> <codigo> <categoria> <ALUGAR_APARELHO> <nome_do_filme>

## Aprendizados
Este projeto foi uma oportunidade valiosa para aprimorar nossas habilidades em programação, colaboração e gerenciamento de projetos. Os principais aprendizados incluem:
- Programação orientada a objetos em C++.
- Colaboração efetiva em um projeto conjunto.
- Uso avançado de Git e GitHub para controle de versão.
- Práticas de programação defensiva e tratamento de exceções.
- Criação e manutenção de Makefile.
- Geração de documentação utilizando Doxygen.

## Documentação
A documentação detalhada do projeto, feita com a ferramenta Doxygen, pode ser encontrada na forma de página web no arquivo "index.html" e no formato PDF no arquivo "refman.pdf".

## Github da Equipe

- **[Victoria Flores](https://github.com/victoriafloresdev)**

- **[Raquel Xavier](https://github.com/Raquelxt)**

- **[Flávio Soriano](https://github.com/flaviosoriano)**

- **[Isadora Horta](https://github.com/isadorahorta)**

- **[Ana Paula Theobald](https://github.com/anaptheo)**

