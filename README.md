# Jogo de cartas 21 (BlackJack)

O jogo tem como objetivo um dos jogadores chegar próximo ou bater 21.


## Regras básicas:

* Todos os jogadores no início de cada rodada receberão 2 castas com valores aleatórios, que serão somados entre si.
  
* Cada jogador terá a possibilidade de receber mais uma carta ou não.
  
* Aquele jogador que ultrapassar a número 21 na soma das cartas perderá o jogo automaticamente.
  
* Aquele jogador que chegar mais próximo de 21 ou bater 21 ao fim da rodada vence o jogo.
  
* Cartas como Valete(J), Dama(Q) e Rei(K) terão seus valores atribuídos como valor 10.


## Execução e compilação do programa:

Para compilar o programa utilize o compilador 'gcc'. Comando para a compilação: "gcc -o jogo21 jogo21.c".

Ao executar o programa aparecerá um menu com 3 opções para escolher.

1. iniciar nova rodada.
   
3. ver placar.
   
5. sair.


Ao escolher a *opção 1* o jogo iniciará, 2 cartas aleatórias serão distribuídas para as mãos dos jogadores, após isso aparecerá uma opção no terminal perguntado se algum dos jogadores tem interesse em receber mais uma carta com as seguintes representações: s(sim) ou n(não), a rodada será encerrado somando as cartas dos jogadores ganhando aquele que chegou mais próximo ou bateu 21.

Ao escolher a *opção 2* o menu irá mostrar quem ganhou a rodada.

Exemplo:
>vencedor da rodada: jogador 1

>vencedor da rodada: jogador 2

>vencedor da rodada: jogador 2

>vencedor da rodada: jogador 1

Ao escolher a *opção* 3 o programa será encerrado, assim finalizando a operação.


## Descrição da organização do código, incluindo explicação dos principais arquivos e funções:**


### Structs:

* "Carta": Representa uma carta do baralho.

* "Nodo": O nodo da lista encadeada.

* "Jogador": Representa o jogador, com as cartas que estarão em sua mão e a pontuação total da rodada.


### Funções:

* "CriarBaralho": Cria as 52 cartas do baralho e as adiciona a uma lista encadeada.

* "Embaralhar": Embaralha as cartas com o "rand()" utilizando um vetor e as adiciona novamente na lista.

* "RemoverCarta": Remove a carta no topo.
  
* "AdicionarCartaNaMao": Adiciona a carta à mão do jogador.
  
* "LimparMao": Limpa todas as cartas na mão do jogador e zera a pontuação.
  
* "ExibirMao": Imprime no terminal as cartas que estão atualmente na mão e a pontuação total do jogador.
  
* "SalvarPlacar": Adiciona o jogador vencedor da partida ao arquivo "placar.txt".
  
* "ExibirPlacar": Lê o arquivo "placar.txt" e imprime os resultados na segunda opção.
  
* "JogarRodada": Entrega duas cartas ao jogador e pergunta se o ele tem interesse em receber outra carta, pedindo a resposta de "s" ou "n" se o jogador aceitar ele adiciona mais uma carta a sua mão. Depois, imprime no terminal a mão dos dois jogadores com a pontuação total de ambos os jogadores e adiciona o vencedor (ou o empate, ou, se ambos passarem de 21, que ambos perderam) ao arquivo "placar.txt". E ao fim retorna o baralho e reembaralha.
  
* "LiberarBaralho": Libera toda a memória utilizada pelo baralho.
