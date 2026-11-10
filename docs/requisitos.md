## User Stories

### Autenticação

**US01** — Como visitante, quero criar uma conta informando login e senha, para poder comprar ingressos.
*Critério: logins duplicados são recusados.*

**US02** — Como usuário cadastrado, quero entrar com meu login e senha, para acessar as funções do meu perfil.
*Critério: após a autenticação, o sistema abre o menu correspondente ao perfil*

**US03** — Como visitante, quero ser avisado quando o login não existe ou a senha está incorreta, para saber que preciso me cadastrar ou corrigir os dados.

**US04** — Como dono do cinema, quero ter um login de administrador exclusivo, para que nenhum cliente consiga alterar a programação.
*Critério: o administrador é criado na inicialização do sistema e não pode ser gerado pelo cadastro de novos usuários.*

### Administrador

**US05** — Como administrador, quero lançar um novo filme informando nome, duração, sala, data de estreia, quantidade de dias em cartaz e horários de exibição, para montar a programação do cinema.
*Critério: o sistema gera automaticamente uma sessão para cada combinação de dia e horário informados. Limites aceitos: duração de 1 a 600 minutos, sala de 1 a 3, ano de 2000 a 2100, de 1 a 365 dias em cartaz e de 1 a 10 horários por dia. Datas inexistentes são recusadas.*

**US06** — Como administrador, quero ser impedido de agendar uma sessão que se sobreponha a outra já existente na mesma sala, para não haver dois filmes passando ao mesmo tempo no mesmo espaço.
*Critério: a sobreposição considera a duração do filme mais 15 minutos de intervalo entre sessões, inclusive entre sessões do próprio filme e sessões que passam da meia-noite. Se qualquer sessão entrar em conflito, nenhuma sessão do filme é criada.*

**US07** — Como administrador, quero excluir um filme do cartaz, para retirar da programação títulos que encerraram a temporada.
*Critério: ao ser excluído, o filme libera os horários que ocupava na agenda da sala.*

**US08** — Como administrador, quero ser impedido de excluir um filme que possua ingressos vendidos, para não invalidar a compra de clientes.

**US09** — Como administrador, quero ver a lista de filmes em cartaz com sua duração e sala, para conferir a programação vigente.

### Cliente

**US10** — Como cliente, quero ver a lista de todos os filmes em cartaz, com duração e sala, para escolher o que desejo assistir.

**US11** — Como cliente, quero ver os dias disponíveis do filme escolhido, para selecionar quando vou ao cinema.

**US12** — Como cliente, quero ver os horários de sessão do dia escolhido, para selecionar a que me atende.

**US13** — Como cliente, quero visualizar o mapa de assentos da sessão distinguindo livres de ocupados, para escolher onde sentar.
*Critério: o mapa mostra as fileiras A a E e os assentos 1 a 5, com "." para livre e "X" para ocupado.*

**US14** — Como cliente, quero selecionar um ou mais assentos em uma única operação, para comprar ingressos junto com meus acompanhantes.
*Critério: os códigos são digitados separados por espaço e aceitam letra minúscula (b2 equivale a B2). Um ingresso é gerado para cada assento. Se algum código for inexistente, repetido ou já ocupado, nenhum assento é reservado.*

**US15** — Como cliente, quero ser impedido de selecionar um assento já ocupado, para não haver duplicidade de lugares.

**US16** — Como cliente, quero acessar a aba "Meus Ingressos" com filme, sala, data, horário de início e de término e assento de cada compra, para consultar o que adquiri.

**US17** — Como cliente, quero cancelar um ingresso meu, para desistir da sessão.
*Critério: o ingresso é escolhido pelo número na lista de "Meus Ingressos", e o assento cancelado volta imediatamente a ficar disponível para outros usuários.*

### Requisitos não funcionais

**RNF01** — O sistema é implementado em C++14 ou superior.

**RNF02** — A interface é textual, operada por menus numerados em terminal.

**RNF03** — O código é modularizado em `src/` e `include/`, com um par `.h`/`.cpp` por classe e para o módulo auxiliar `Entrada`, além do `main.cpp`.

**RNF04** — A compilação e a execução ocorrem pelos comandos `make` e `make run`, e `make clean` remove os arquivos gerados.

**RNF05** — O sistema não encerra abruptamente diante de entrada inválida: opções fora do intervalo, texto onde se espera número, datas inexistentes e códigos de assento inexistentes são tratados e reapresentados ao usuário. O fim da entrada (EOF) encerra o programa com mensagem, sem erro.

**RNF06** — Toda memória alocada dinamicamente é liberada ao término da execução.

**RNF07** — A documentação da API é gerada por Doxygen a partir de comentários no código.

**RNF08** — O cinema possui exatamente 3 salas, cada uma com 5 fileiras (A a E) de 5 assentos.

**RNF09** — Os dados são voláteis: persistência em arquivo está fora do escopo desta versão.



## Cartões CRC

### Data

**Responsabilidades**
- Armazenar dia, mês e ano
- Validar se a data existe (anos de 2000 a 2100, considerando anos bissextos)
- Informar quantos dias tem um mês e se um ano é bissexto
- Comparar-se com outra data
- Somar dias e gerar nova data
- Formatar-se como texto (DD/MM/AA)

**Colaboradores**: nenhum

### Horario

**Responsabilidades**
- Armazenar hora e minuto
- Validar o intervalo (0 a 23 horas, 0 a 59 minutos)
- Converter-se em minutos desde 00:00
- Comparar-se com outro horário
- Somar minutos e gerar o horário de término (volta a 00:00 após 23:59)
- Formatar-se como texto (HH:MM)

**Colaboradores**: nenhum

### Usuario (abstrata)

**Responsabilidades**
- Armazenar login e senha, recusando valores vazios
- Verificar se uma senha confere
- Informar seu login
- Declarar a interface de menu a ser especializada pelas subclasses

**Colaboradores**: nenhum

### Cliente (herda de Usuario)

**Responsabilidades**
- Exibir o menu do cliente
- Exibir os filmes em cartaz
- Conduzir a compra: escolher filme, dia e horário, exibir o mapa e ler os assentos
- Solicitar à sessão a reserva dos assentos e gerar um ingresso para cada um
- Manter a lista de ingressos comprados e liberá-los ao ser destruído
- Adicionar ingresso
- Listar seus ingressos (aba "Meus Ingressos")
- Cancelar um ingresso e solicitar a liberação do assento
- Informar se possui ingresso de uma determinada sessão
- Informar quantos ingressos possui

**Colaboradores**: Usuario, Cinema, Filme, Sessao, Ingresso, Data, Horario, Entrada

### Administrador (herda de Usuario)

**Responsabilidades**
- Exibir o menu de administração
- Ler os dados de lançamento (nome, duração, sala, data de estreia, dias em cartaz e horários)
- Encaminhar ao Cinema as operações de lançamento e exclusão de filmes
- Exibir os filmes em cartaz

**Colaboradores**: Usuario, Cinema, Data, Horario, Entrada

### Sala

**Responsabilidades**
- Identificar-se pelo número
- Manter as sessões nela agendadas (sem ser dona delas)
- Detectar conflito de horário para uma nova sessão (duração do filme + 15 minutos)
- Registrar sessão agendada
- Remover sessão da agenda quando o filme sai de cartaz

**Colaboradores**: Sessao, Filme, Data, Horario

### Filme

**Responsabilidades**
- Armazenar nome, duração e sala
- Criar e possuir suas sessões, uma por dia e horário, consultando a sala sobre conflitos (se houver conflito, nenhuma sessão é criada)
- Listar os dias em que está disponível
- Listar os horários de um determinado dia
- Buscar a sessão de um dia e horário
- Informar se possui ingressos vendidos
- Liberar suas sessões ao ser destruído, removendo-as da agenda da sala

**Colaboradores**: Sessao, Sala, Data, Horario

### Sessao

**Responsabilidades**
- Armazenar filme, data, horário e sala
- Manter o mapa 5x5 de assentos
- Exibir o mapa distinguindo assentos livres (.) de ocupados (X)
- Validar e converter código de assento em posição (A1 a E5, aceitando letra minúscula)
- Reservar um ou mais assentos em uma única operação (se algum for inexistente, repetido ou ocupado, nenhum é reservado)
- Liberar assento
- Informar se um assento está ocupado
- Informar se há assentos ocupados
- Calcular seu horário de término a partir da duração do filme

**Colaboradores**: Filme, Sala, Data, Horario

### Ingresso

**Responsabilidades**
- Referenciar a sessão e o assento adquirido
- Exibir ao cliente filme, sala, data, horário de início e de término e assento
- Devolver o assento à sessão quando cancelado

**Colaboradores**: Sessao, Filme, Sala, Data, Horario

### Cinema

**Responsabilidades**
- Criar o administrador e as três salas na inicialização do sistema
- Cadastrar novos clientes, recusando logins já usados (inclusive o do administrador)
- Autenticar usuários e abrir o menu correspondente ao perfil
- Manter o cartaz de filmes e as três salas
- Buscar sala pelo número
- Lançar filme, descartando-o se Filme e Sala acusarem conflito de horário
- Excluir filme validando existência de ingressos vendidos
- Listar os filmes em cartaz com duração e sala
- Executar o laço principal do sistema (menu inicial: entrar, criar conta, sair)
- Liberar toda a memória alocada

**Colaboradores**: Usuario, Cliente, Administrador, Filme, Sala, Data, Horario, Entrada

### Entrada (módulo auxiliar, não é classe)

**Responsabilidades**
- Ler uma linha de texto, removendo espaços nas pontas
- Ler um número inteiro dentro de um intervalo, repetindo a pergunta até ser válido
- Limpar a tela do terminal
- Pausar até o usuário apertar Enter
- Sinalizar o fim da entrada (EOF) para o programa encerrar sem erro

**Colaboradores**: nenhum
