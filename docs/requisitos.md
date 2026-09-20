Requisitos funcionais
Autenticação
US01 — Como visitante, quero criar uma conta informando login e senha, para poder comprar ingressos.
 Critério: logins duplicados são recusados.
US02 — Como usuário cadastrado, quero entrar com meu login e senha, para acessar as funções do meu perfil.
US03 — Como visitante, quero ser avisado quando o login não existe ou a senha está incorreta, para saber que preciso me cadastrar ou corrigir os dados.
US04 — Como dono do cinema, quero ter um login de administrador exclusivo, para que nenhum cliente consiga alterar a programação.
 Critério: o administrador é criado na inicialização do sistema e não pode ser gerado pelo cadastro de novos usuários.
Administrador
US05 — Como administrador, quero lançar um novo filme informando nome, duração, sala, data de estreia, quantidade de dias em cartaz e horários de exibição, para montar a programação do cinema.
 Critério: o sistema gera automaticamente uma sessão para cada combinação de dia e horário informados.
US06 — Como administrador, quero ser impedido de agendar uma sessão que se sobreponha a outra já existente na mesma sala, para não haver dois filmes passando ao mesmo tempo no mesmo espaço.
 Critério: a sobreposição considera a duração do filme mais 15 minutos de intervalo entre sessões.
US07 — Como administrador, quero excluir um filme do cartaz, para retirar da programação títulos que encerraram a temporada.
US08 — Como administrador, quero ser impedido de excluir um filme que possua ingressos vendidos, para não invalidar a compra de clientes.
US09 — Como administrador, quero ver a lista de filmes em cartaz com suas salas, para conferir a programação vigente.
Cliente
US10 — Como cliente, quero ver a lista de todos os filmes em cartaz, para escolher o que desejo assistir.
US11 — Como cliente, quero ver os dias disponíveis do filme escolhido, para selecionar quando vou ao cinema.
US12 — Como cliente, quero ver os horários de sessão do dia escolhido, para selecionar a que me atende.
US13 — Como cliente, quero visualizar o mapa de assentos da sessão distinguindo livres de ocupados, para escolher onde sentar.
US14 — Como cliente, quero selecionar um ou mais assentos em uma única operação, para comprar ingressos junto com meus acompanhantes.
US15 — Como cliente, quero ser impedido de selecionar um assento já reservado por outro usuário, para não haver duplicidade de lugares.
US16 — Como cliente, quero acessar a aba "Meus Ingressos" com filme, sala, data, horário e assento de cada compra, para consultar o que adquiri.
US17 — Como cliente, quero cancelar um ingresso meu, para desistir da sessão.
 Critério: o assento cancelado volta imediatamente a ficar disponível para outros usuários.
Requisitos não funcionais
RNF01 — O sistema é implementado em C++14 ou superior.
RNF02 — A interface é textual, operada por menus numerados em terminal.
RNF03 — O código é modularizado em src/ e include/, com um par .h/.cpp por 
lasse.
RNF04 — A compilação e a execução ocorrem pelos comandos make e make run.
RNF05 — O sistema não encerra abruptamente diante de entrada inválida: opções fora do intervalo, texto onde se espera número e códigos de assento inexistentes são tratados e reapresentados ao usuário.
RNF06 — Toda memória alocada dinamicamente é liberada ao término da execução.
RNF07 — A documentação da API é gerada por Doxygen a partir de comentários no código.
RNF08 — O cinema possui exatamente 3 salas, cada uma com 5 fileiras (A a E) de 5 assentos.
RNF09 — Os dados são voláteis: persistência em arquivo está fora do escopo desta versão.


