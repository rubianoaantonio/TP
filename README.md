# Cine PDS

Sistema de venda de ingressos para um cinema de 3 salas, operado por menus numerados no terminal. Trabalho prático da disciplina Programação e Desenvolvimento de Software II (PDS II) da UFMG.

> **Vídeo de demonstração:** [PREENCHER: link do vídeo]

## Sumário

- Apresentação
- Requisitos
- Modelagem CRC
- Funcionalidades entregues e fora do escopo
- Arquitetura e organização
- Documentação (Doxygen)
- Como compilar e executar
- Instruções de uso
- Equipe

## Apresentação

O Cine PDS tem dois tipos de usuário:

- **Administrador:** monta a programação. Lança filmes informando nome, duração, sala, data de estreia, dias em cartaz e horários; o sistema cria automaticamente uma sessão para cada combinação de dia e horário e impede que duas sessões ocupem a mesma sala ao mesmo tempo. Também exclui filmes, desde que não tenham ingressos vendidos.
- **Cliente:** cria uma conta, escolhe filme, dia e horário, vê o mapa de assentos da sessão e compra um ou mais ingressos de uma vez. Na aba "Meus Ingressos", consulta e cancela suas compras.

Cada sala tem 25 assentos, em 5 fileiras (A a E) de 5 assentos. Sessões podem passar da meia-noite: um filme de 150 minutos às 23:00 termina às 01:30, e o sistema considera essa ocupação ao verificar conflitos com sessões do dia seguinte.

## Requisitos

### User Stories

**Autenticação**

| ID | User Story | Critério de aceitação |
| --- | --- | --- |
| US01 | Como visitante, quero criar uma conta informando login e senha, para poder comprar ingressos. | Logins duplicados  são recusados. |
| US02 | Como usuário cadastrado, quero entrar com meu login e senha, para acessar as funções do meu perfil. | Após a autenticação, o sistema abre o menu correspondente ao perfil. |
| US03 | Como visitante, quero ser avisado quando o login não existe ou a senha está incorreta, para saber que preciso me cadastrar ou corrigir os dados. | |
| US04 | Como dono do cinema, quero ter um login de administrador exclusivo, para que nenhum cliente consiga alterar a programação. | O administrador é criado na inicialização do sistema e não pode ser gerado pelo cadastro de novos usuários. |

**Administrador**

| ID | User Story | Critério de aceitação |
| --- | --- | --- |
| US05 | Como administrador, quero lançar um novo filme informando nome, duração, sala, data de estreia, quantidade de dias em cartaz e horários de exibição, para montar a programação do cinema. | O sistema gera automaticamente uma sessão para cada combinação de dia e horário informados. Estão dentro dos limites aceitos duração de 1 a 600 minutos, sala de 1 a 3, ano de 2000 a 2100, de 1 a 365 dias em cartaz e de 1 a 10 horários por dia. Datas inexistentes são recusadas. |
| US06 | Como administrador, quero ser impedido de agendar uma sessão que se sobreponha a outra já existente na mesma sala, para não haver dois filmes passando ao mesmo tempo no mesmo espaço. | A sobreposição considera a duração do filme mais 15 minutos de intervalo entre sessões, inclusive entre sessões do próprio filme e sessões que passam da meia-noite. Se qualquer sessão entrar em conflito, nenhuma sessão do filme é criada. |
| US07 | Como administrador, quero excluir um filme do cartaz, para retirar da programação títulos que encerraram a temporada. | Ao ser excluído, o filme libera os horários que ocupava na agenda da sala. |
| US08 | Como administrador, quero ser impedido de excluir um filme que possua ingressos vendidos, para não invalidar a compra de clientes. | |
| US09 | Como administrador, quero ver a lista de filmes em cartaz com sua duração e sala, para conferir a programação vigente. | |

**Cliente**

| ID | User Story | Critério de aceitação |
| --- | --- | --- |
| US10 | Como cliente, quero ver a lista de todos os filmes em cartaz, com duração e sala, para escolher o que desejo assistir. | |
| US11 | Como cliente, quero ver os dias disponíveis do filme escolhido, para selecionar quando vou ao cinema. | |
| US12 | Como cliente, quero ver os horários de sessão do dia escolhido, para selecionar a que me atende. | |
| US13 | Como cliente, quero visualizar o mapa de assentos da sessão distinguindo livres de ocupados, para escolher onde sentar. | O mapa mostra as fileiras A a E e os assentos 1 a 5, com "." para livre e "X" para ocupado. |
| US14 | Como cliente, quero selecionar um ou mais assentos em uma única operação, para comprar ingressos junto com meus acompanhantes. | Os códigos são digitados separados por espaço e aceitam letra minúscula. Um ingresso é gerado para cada assento. Se algum código for inexistente, repetido ou já ocupado, nenhum assento é reservado. |
| US15 | Como cliente, quero ser impedido de selecionar um assento já ocupado, para não haver duplicidade de lugares. | |
| US16 | Como cliente, quero acessar a aba "Meus Ingressos" com filme, sala, data, horário de início e de término e assento de cada compra, para consultar o que adquiri. | |
| US17 | Como cliente, quero cancelar um ingresso meu, para desistir da sessão. | O ingresso é escolhido pelo número na lista de "Meus Ingressos", e o assento cancelado volta imediatamente a ficar disponível para outros usuários. |

### Requisitos não funcionais

| ID | Requisito |
| --- | --- |
| RNF01 | O sistema é implementado em C++14 ou superior. |
| RNF02 | A interface é textual, operada por menus numerados em terminal. |
| RNF03 | O código é modularizado em `src/` e `include/`, com um par `.h`/`.cpp` por classe e para o módulo auxiliar `Entrada`, além do `main.cpp`. |
| RNF04 | A compilação e a execução ocorrem pelos comandos `make` e `make run`, e `make clean` remove os arquivos gerados. |
| RNF05 | O sistema não encerra abruptamente diante de entrada inválida: opções fora do intervalo, texto onde se espera número, datas inexistentes e códigos de assento inexistentes são tratados e reapresentados ao usuário. O fim da entrada encerra o programa com mensagem, sem erro. |
| RNF06 | Toda memória alocada dinamicamente é liberada ao término da execução. |
| RNF07 | A documentação da API é gerada por Doxygen a partir de comentários no código. |
| RNF08 | O cinema possui exatamente 3 salas, cada uma com 5 fileiras (A a E) de 5 assentos. |
| RNF09 | Os dados são voláteis: persistência em arquivo está fora do escopo desta versão. |

## Modelagem CRC

| Classe | Responsabilidades | Colaboradores |
| --- | --- | --- |
| **Data** | Armazenar dia, mês e ano; validar se a data existe (anos de 2000 a 2100, considerando anos bissextos); informar quantos dias tem um mês e se um ano é bissexto; comparar-se com outra data; somar dias e gerar nova data; formatar-se como texto (DD/MM/AA) | nenhum |
| **Horario** | Armazenar hora e minuto; validar o intervalo (0 a 23 horas, 0 a 59 minutos); converter-se em minutos desde 00:00; comparar-se com outro horário; somar minutos e gerar o horário de término; formatar-se como texto (HH:MM) | nenhum |
| **Usuario** (abstrata) | Armazenar login e senha, recusando valores vazios; verificar se uma senha confere; informar seu login; declarar a interface de menu a ser especializada pelas subclasses | nenhum |
| **Cliente** (herda de Usuario) | Exibir o menu do cliente; exibir os filmes em cartaz; conduzir a compra (escolher filme, dia e horário, exibir o mapa e ler os assentos); solicitar à sessão a reserva dos assentos e gerar um ingresso para cada um; manter a lista de ingressos comprados e liberá-los ao ser destruído; adicionar ingresso; listar seus ingressos; cancelar um ingresso e solicitar a liberação do assento; informar se possui ingresso de uma determinada sessão; informar quantos ingressos possui | Usuario, Cinema, Filme, Sessao, Ingresso, Data, Horario, Entrada |
| **Administrador** (herda de Usuario) | Exibir o menu de administração; ler os dados de lançamento; encaminhar ao Cinema as operações de lançamento e exclusão de filmes; exibir os filmes em cartaz | Usuario, Cinema, Data, Horario, Entrada |
| **Sala** | Identificar-se pelo número; manter as sessões nela agendadas; detectar conflito de horário para uma nova sessão (duração do filme + 15 minutos); registrar sessão agendada; remover sessão da agenda quando o filme sai de cartaz | Sessao, Filme, Data, Horario |
| **Filme** | Armazenar nome, duração e sala; criar e possuir suas sessões, uma por dia e horário, consultando a sala sobre conflitos (se houver conflito, nenhuma sessão é criada); listar os dias em que está disponível; listar os horários de um determinado dia; buscar a sessão de um dia e horário; informar se possui ingressos vendidos; liberar suas sessões ao ser destruído, removendo-as da agenda da sala | Sessao, Sala, Data, Horario |
| **Sessao** | Armazenar filme, data, horário e sala; manter o mapa 5x5 de assentos; exibir o mapa distinguindo assentos livres (.) de ocupados (X); validar e converter código de assento em posição (A1 a E5, aceitando letra minúscula); reservar um ou mais assentos em uma única operação (se algum for inexistente, repetido ou ocupado, nenhum é reservado); liberar assento; informar se um assento está ocupado; informar se há assentos ocupados; calcular seu horário de término a partir da duração do filme | Filme, Sala, Data, Horario |
| **Ingresso** | Referenciar a sessão e o assento adquirido; exibir ao cliente filme, sala, data, horário de início e de término e assento; devolver o assento à sessão quando cancelado | Sessao, Filme, Sala, Data, Horario |
| **Cinema** | Criar o administrador e as três salas na inicialização do sistema; cadastrar novos clientes, recusando logins já usados (inclusive o do administrador); autenticar usuários e abrir o menu correspondente ao perfil; manter o cartaz de filmes e as três salas; buscar sala pelo número; lançar filme, descartando-o se Filme e Sala acusarem conflito de horário; excluir filme validando existência de ingressos vendidos; listar os filmes em cartaz com duração e sala; executar o laço principal do sistema (menu inicial: entrar, criar conta, sair); liberar toda a memória alocada | Usuario, Cliente, Administrador, Filme, Sala, Data, Horario, Entrada |
| **Entrada** (módulo auxiliar, não é classe) | Ler uma linha de texto, removendo espaços nas pontas; ler um número inteiro dentro de um intervalo, repetindo a pergunta até ser válido; limpar a tela do terminal; pausar até o usuário apertar Enter; sinalizar o fim da entrada (EOF) para o programa encerrar sem erro | nenhum |

Observação sobre o módulo `Entrada`: ele não é uma classe, e sim um `namespace` com as funções de leitura do teclado (`lerTexto`, `lerInteiro`, `limparTela` e `pausar`) usadas pelos menus de `Cinema`, `Cliente` e `Administrador`. Ele concentra o tratamento de entrada inválida exigido pelo RNF05, para não repetir o mesmo código nos três menus. Foi incluído na tabela porque aparece como colaborador dessas classes.

## Funcionalidades entregues e fora do escopo

**Entregues:** todas as User Stories, de US01 a US17.

Comportamentos adicionais:

- **Lançamento de filme é tudo ou nada:** se qualquer uma das sessões entrar em conflito com a agenda da sala, nenhuma sessão do filme é criada.
- **Compra de vários assentos é tudo ou nada:** se um dos códigos for inexistente, repetido ou já ocupado, nenhum assento é reservado.
- **Sessões após a meia-noite:** permitidas. O horário de término é exibido sem a data (ex.: `23:00 - 01:30`), e a verificação de conflito considera a ocupação no dia seguinte.
- **Códigos de assento** aceitam letra minúscula (`b2` equivale a `B2`).

**Fora do escopo:**

- Persistência em arquivo (RNF09): os dados são perdidos ao encerrar o programa.
- Alterar filmes ou sessões já lançados (é preciso excluir e lançar de novo).
- Preço, pagamento e meia-entrada.
- Mais de um administrador ou troca da senha do administrador.

## Arquitetura e organização

```
TP/
├── Makefile          # make, make run, make clean
├── Doxyfile          # configuração do Doxygen
├── README.md
├── include/          # um .h por classe e para o módulo Entrada (contratos)
├── src/              # um .cpp por classe, Entrada.cpp e main.cpp
├── tests/            # testes isolados (não entram no executável)
├── docs/             # requisitos e documentação gerada pelo Doxygen
├── build/            # arquivos .o gerados pelo make (ignorados pelo git)
└── bin/              # executável gerado pelo make (ignorado pelo git)
```

**Dependências entre as classes** (de forma geral, cada camada usa as que estão antes):

```
Data, Horario, Entrada → Sala, Sessao, Filme → Ingresso → Usuario → Cliente, Administrador → Cinema → main
```

`Sala`, `Sessao` e `Filme` se referenciam mutuamente (a sessão conhece seu filme e sua sala; a sala consulta o filme de cada sessão para saber a duração; o filme cria as sessões e as registra na sala). Por isso os `.h` usam *forward declaration* (`class Sessao;`, `class Filme;`, `class Sala;`) em vez de incluir um ao outro.

**Conceitos de orientação a objetos aplicados:**

| Conceito | Onde |
| --- | --- |
| Abstração e herança | `Usuario` é abstrata; `Cliente` e `Administrador` herdam dela |
| Polimorfismo | `Usuario::exibirMenu` é virtual pura; `Cinema` chama `usuario->exibirMenu(*this)` sem saber se é cliente ou administrador |
| Encapsulamento | Todos os atributos são privados; o acesso é feito só por métodos públicos |
| Sobrecarga de operadores | `Data` e `Horario` definem `==`, `!=`, `<`, `<=`, `>`, `>=` |
| Alocação dinâmica | `Cinema` é dono de clientes, administrador, salas e filmes; `Filme` é dono de suas sessões; `Cliente` é dono de seus ingressos. Cada dono libera a memória no destrutor (RNF06) |
| Programação defensiva | As classes lançam exceções (`std::invalid_argument`, `std::out_of_range`, `std::logic_error`) e os menus as capturam e reapresentam a opção (RNF05) |

## Documentação (Doxygen)

Todas as classes e métodos públicos têm comentários no formato Doxygen (`/** @brief ... @param ... @return ... */`) nos arquivos `.h`.

Para gerar a documentação, na raiz do repositório:

```bash
sudo apt install doxygen
doxygen Doxyfile
```

A documentação é gerada em `docs/doxygen/html/`. Para abrir, acesse o arquivo `docs/doxygen/html/index.html` no navegador.

## Como compilar e executar

**Requisitos:** Linux ou WSL (Ubuntu), `g++` com suporte a C++14 e `make`.

```bash
sudo apt install g++ make
git clone https://github.com/rubianoaantonio/TP.git
cd TP
make
make run
```

| Comando | O que faz |
| --- | --- |
| `make` | Compila o projeto e gera o executável em `bin/cinema` |
| `make run` | Compila, se necessário, e executa o sistema |
| `make clean` | Apaga os arquivos gerados (`build/*.o`, `build/*.d` e `bin/`) |

**Verificação de memória (RNF06):**

```bash
sudo apt install valgrind
valgrind --leak-check=full ./bin/cinema
```

Ao final da execução, o valgrind deve informar `All heap blocks were freed -- no leaks are possible`.

**Vídeo de demonstração:** [PREENCHER: link do vídeo]

## Instruções de uso

O administrador é criado automaticamente ao iniciar o sistema:

| Login | Senha |
| --- | --- |
| `admin` | `admin123` |

Em todos os menus, digite o número da opção e aperte Enter. A opção `0` volta ou sai.

### Exemplo 1: administrador lança um filme

Lançando "Duna", de 150 minutos, na sala 1, por 2 dias a partir de 20/11/2026, às 19:00 e às 23:00. O sistema cria 4 sessões (2 dias × 2 horários).

```
=== Administrador ===
1. Lançar filme
2. Excluir filme
3. Ver filmes em cartaz
0. Sair
Opção: 1
Nome do filme: Duna
Duração (minutos): 150
Sala (1 a 3): 1
Data de estreia
  Dia: 20
  Mês: 11
  Ano (4 dígitos): 2026
Dias em cartaz: 2
Quantos horários por dia: 2
Horário 1
  Hora (0 a 23): 19
  Minuto (0 a 59): 0
Horário 2
  Hora (0 a 23): 23
  Minuto (0 a 59): 0
Filme lançado com 4 sessão(ões).
```

### Exemplo 2: cliente compra dois ingressos

Depois de criar a conta `ana` e entrar, a cliente escolhe o filme, o dia, o horário e os assentos `B2` e `B3` numa única operação:

```
=== Cliente: ana ===
1. Ver filmes em cartaz
2. Comprar ingressos
3. Meus Ingressos
4. Cancelar ingresso
0. Sair
Opção: 2
1. Duna (150 min) - Sala 1
Filme (0 para voltar): 1
1. 20/11/26
2. 21/11/26
Dia (0 para voltar): 1
1. 19:00
2. 23:00
Horário (0 para voltar): 2

    1 2 3 4 5
A   . . . . .
B   . . . . .
C   . . . . .
D   . . . . .
E   . . . . .
Legenda: . livre   X ocupado
Assentos separados por espaço (ex.: A1 A2): B2 B3
2 ingresso(s) comprado(s).
```

### Exemplo 3: Meus Ingressos

A sessão das 23:00 de um filme de 150 minutos termina à 01:30:

```
Opção: 3
1. Duna | Sala 1 | 20/11/26 | 23:00 - 01:30 | Assento B2
2. Duna | Sala 1 | 20/11/26 | 23:00 - 01:30 | Assento B3
```

### Exemplo 4: tratamento de entradas inválidas

| Entrada | Resposta do sistema |
| --- | --- |
| Letra onde se espera número (`abc`) | `Valor inválido. Digite um número entre 0 e 2.` |
| Opção fora do intervalo (`9`) | `Valor inválido. Digite um número entre 0 e 2.` |
| Assento inexistente (`F9`) | `Erro: Assento inexistente: F9` |
| Assento já ocupado (`B2`) | `Erro: Assento já reservado: B2` |
| Login já usado no cadastro | `Erro: O login "ana" já está em uso.` |
| Senha errada | `Erro: Senha incorreta.` |
| Data inexistente (31/02/2026) | `Erro: Data inexistente: 31/2/2026` |
| Sessão sobreposta na mesma sala | `Erro: Conflito na sala 1 em 21/11/26 às 00:30.` |
| Excluir filme com ingresso vendido | `Erro: O filme tem ingressos vendidos e não pode ser excluído.` |

Em todos os casos, o sistema continua rodando e reapresenta o menu.

## Equipe

| Integrante | GitHub | Responsabilidade | Classes e arquivos |
| --- | --- | --- | --- |
| Antônio Andrade Rubiano | [rubianoaantonio](https://github.com/rubianoaantonio) | Classes base de data e horário, Makefile e configuração do repositório | `Data`, `Horario`, `Makefile`, `.gitignore` |
| Lucas Fidelis Agrela | [LucasFidelisAgrela](https://github.com/LucasFidelisAgrela) | Sessões, ingressos e leitura de entrada | `Sessao`, `Ingresso`, `Entrada` |
| Gustavo Tanaka | [gustavotnk](https://github.com/gustavotnk) | Salas e filmes | `Sala`, `Filme` |
| Diego Lima | [diegollgbdi-cmd](https://github.com/diegollgbdi-cmd) | Usuários | `Usuario`, `Cliente` |
| Guilherme Gonçalo | [guigoncs](https://github.com/guigoncs) | Classe central e programa principal | `Cinema`, `Administrador`, `main.cpp` |

O histórico de commits de cada integrante pode ser consultado em: https://github.com/rubianoaantonio/TP/commits/main

Para ver só os commits de um integrante, acrescente `?author=` e o usuário do GitHub ao endereço. Exemplo: https://github.com/rubianoaantonio/TP/commits/main?author=guigoncs
