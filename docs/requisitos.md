User Stories

### Autenticação

**US01** — Como visitante, quero criar uma conta informando login e senha, para poder comprar ingressos.
*Critério: logins duplicados são recusados.*

**US02** — Como usuário cadastrado, quero entrar com meu login e senha, para acessar as funções do meu perfil.

**US03** — Como visitante, quero ser avisado quando o login não existe ou a senha está incorreta, para saber que preciso me cadastrar ou corrigir os dados.

**US04** — Como dono do cinema, quero ter um login de administrador exclusivo, para que nenhum cliente consiga alterar a programação.
*Critério: o administrador é criado na inicialização do sistema e não pode ser gerado pelo cadastro de novos usuários.*

### Administrador

**US05** — Como administrador, quero lançar um novo filme informando nome, duração, sala, data de estreia, quantidade de dias em cartaz e horários de exibição, para montar a programação do cinema.
*Critério: o sistema gera automaticamente uma sessão para cada combinação de dia e horário informados.*

**US06** — Como administrador, quero ser impedido de agendar uma sessão que se sobreponha a outra já existente na mesma sala, para não haver dois filmes passando ao mesmo tempo no mesmo espaço.
*Critério: a sobreposição considera a duração do filme mais 15 minutos de intervalo entre sessões.*

**US07** — Como administrador, quero excluir um filme do cartaz, para retirar da programação títulos que encerraram a temporada.

**US08** — Como administrador, quero ser impedido de excluir um filme que possua ingressos vendidos, para não invalidar a compra de clientes.

**US09** — Como administrador, quero ver a lista de filmes em cartaz com suas salas, para conferir a programação vigente.

### Cliente

**US10** — Como cliente, quero ver a lista de todos os filmes em cartaz, para escolher o que desejo assistir.

**US11** — Como cliente, quero ver os dias disponíveis do filme escolhido, para selecionar quando vou ao cinema.

**US12** — Como cliente, quero ver os horários de sessão do dia escolhido, para selecionar a que me atende.

**US13** — Como cliente, quero visualizar o mapa de assentos da sessão distinguindo livres de ocupados, para escolher onde sentar.

**US14** — Como cliente, quero selecionar um ou mais assentos em uma única operação, para comprar ingressos junto com meus acompanhantes.

**US15** — Como cliente, quero ser impedido de selecionar um assento já reservado por outro usuário, para não haver duplicidade de lugares.

**US16** — Como cliente, quero acessar a aba "Meus Ingressos" com filme, sala, data, horário e assento de cada compra, para consultar o que adquiri.

**US17** — Como cliente, quero cancelar um ingresso meu, para desistir da sessão.
*Critério: o assento cancelado volta imediatamente a ficar disponível para outros usuários.*

### Requisitos não funcionais

**RNF01** — O sistema é implementado em C++14 ou superior.
**RNF02** — A interface é textual, operada por menus numerados em terminal.
**RNF03** — O código é modularizado em `src/` e `include/`, com um par `.h`/`.cpp` por classe.
**RNF04** — A compilação e a execução ocorrem pelos comandos `make` e `make run`.
**RNF05** — O sistema não encerra abruptamente diante de entrada inválida: opções fora do intervalo, texto onde se espera número e códigos de assento inexistentes são tratados e reapresentados ao usuário.
**RNF06** — Toda memória alocada dinamicamente é liberada ao término da execução.
**RNF07** — A documentação da API é gerada por Doxygen a partir de comentários no código.
**RNF08** — O cinema possui exatamente 3 salas, cada uma com 5 fileiras (A a E) de 5 assentos.
**RNF09** — Os dados são voláteis: persistência em arquivo está fora do escopo desta versão.



Cartões CRC

### Data

**Responsabilidades**
- Armazenar dia, mês e ano
- Validar se a data existe
- Comparar-se com outra data
- Somar dias e gerar nova data
- Formatar-se como texto (DD/MM/AA)

**Colaboradores**: nenhum

### Horario

**Responsabilidades**
- Armazenar hora e minuto
- Validar o intervalo (0 a 23 horas, 0 a 59 minutos)
- Comparar-se com outro horário
- Somar minutos e gerar o horário de término
- Formatar-se como texto (HH:MM)

**Colaboradores**: nenhum

### Usuario (abstrata)

**Responsabilidades**
- Armazenar login e senha
- Verificar se uma senha confere
- Informar seu login
- Declarar a interface de menu a ser especializada pelas subclasses

**Colaboradores**: nenhum

### Cliente (herda de Usuario)

**Responsabilidades**
- Exibir o menu do cliente
- Manter a lista de ingressos comprados
- Adicionar ingresso
- Listar seus ingressos
- Cancelar um ingresso e solicitar a liberação do assento
- Informar se possui ingresso de uma determinada sessão

**Colaboradores**: Usuario, Ingresso, Sessao

### Administrador (herda de Usuario)

**Responsabilidades**
- Exibir o menu de administração
- Encaminhar as operações de lançamento e exclusão de filmes

**Colaboradores**: Usuario, Cinema

### Sala

**Responsabilidades**
- Identificar-se pelo número
- Manter as sessões nela agendadas
- Detectar conflito de horário para uma nova sessão
- Registrar sessão agendada

**Colaboradores**: Sessao, Data, Horario

### Filme

**Responsabilidades**
- Armazenar nome e duração
- Criar e possuir suas sessões
- Listar os dias em que está disponível
- Listar os horários de um determinado dia
- Liberar suas sessões ao ser destruído

**Colaboradores**: Sessao, Sala, Data, Horario

### Sessao

**Responsabilidades**
- Armazenar data, horário e sala
- Manter o mapa 5x5 de assentos
- Exibir o mapa distinguindo assentos livres de ocupados
- Validar e converter código de assento em posição
- Reservar assento
- Liberar assento
- Informar se há assentos ocupados
- Calcular seu horário de término

**Colaboradores**: Data, Horario, Sala

### Ingresso

**Responsabilidades**
- Referenciar a sessão e o assento adquirido
- Exibir seus dados ao cliente
- Devolver o assento à sessão quando cancelado

**Colaboradores**: Sessao

### Cinema

**Responsabilidades**
- Criar o administrador na inicialização do sistema
- Cadastrar novos clientes e autenticar usuários
- Manter o cartaz de filmes e as três salas
- Lançar filme validando conflito de sala
- Excluir filme validando existência de ingressos vendidos
- Executar o laço principal do sistema
- Liberar toda a memória alocada

**Colaboradores**: todas as demais classes
