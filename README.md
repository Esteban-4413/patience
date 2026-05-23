# Patience — Laboratórios de Informática II

Projeto desenvolvido no âmbito da unidade curricular **Laboratórios de Informática II** da Universidade do Minho.

**Autores:**
- Esteban Yepez (a116272)
- Fernanda Cidrim (a116274)
- Martim Sousa (a113572)

---

## Descrição

Implementação de um motor genérico de jogos de paciência em C. O programa lê a definição de qualquer paciência a partir de ficheiros de texto (DSL própria), permitindo ao utilizador escolher o jogo, jogar, desfazer jogadas, guardar e carregar partidas.

---

## Estrutura do Projeto

```text
patience/
├── paciencias/
│   ├── golf.paciencia
│   ├── simpleSimon.paciencia
│   └── freeCell.paciencia
│
├── game/
│   ├── dsl/
│   │   ├── parser.c        ← lê ficheiros .paciencia e constrói DefJogo
│   │   └── loader.c        ← lista paciências disponíveis e menu de seleção
│   │
│   ├── src/
│   │   ├── main.c          ← ponto de entrada
│   │   ├── card.c          ← carta: valor + naipe
│   │   ├── gamedef.c       ← funções auxiliares sobre DefJogo
│   │   ├── gamestate.c     ← criação e inicialização do estado do jogo
│   │   ├── game.c          ← loop principal e lógica de jogada
│   │   ├── move.c          ← validação e execução de movimentos
│   │   ├── undo.c          ← histórico de jogadas (desfazer)
│   │   ├── saveload.c      ← guardar e carregar partidas
│   │   └── utils.c         ← funções auxiliares gerais
│   │
│   ├── ui/
│   │   ├── display.c       ← interface gráfica (ncurses)
│   │   └── input.c         ← deteção de cliques do rato
│   │
│   └── include/            ← ficheiros de cabeçalho (.h)
│
└── Makefile
```

---

## Requisitos

- Compilador GCC ou Clang
- Biblioteca ncurses (`libncurses`)
- Sistema operativo: macOS ou Linux

---

## Compilação

A partir da pasta raiz do projeto (`patience/`):

**macOS:**
```bash
make mac
```

**Linux:**
```bash
make jogo
```

---

## Execução

```bash
./jogo
```

O programa irá listar as paciências disponíveis na pasta `paciencias/` e pedir ao utilizador que escolha uma.

---

## Como Jogar

- **Clique** numa carta para a selecionar
- **Clique** noutra pilha para tentar mover a carta
- **Botão UNDO** — desfaz a última jogada
- **Tecla `q`** — sair do jogo

---

## Guardar e Carregar

O formato dos ficheiros de save é o seguinte:

```
golf.paciencia
2C 7D 3H AS
10S

6D 3H
```

- A primeira linha é o nome do ficheiro da paciência
- Cada linha seguinte corresponde a uma pilha (vazia se a linha estiver em branco)
- As cartas são representadas como `<valor><naipe>` (ex: `AS`, `10C`, `KH`)

---

## DSL das Paciências

Cada paciência é descrita num ficheiro de texto com os seguintes comandos:

| Comando | Descrição |
|---|---|
| `JOGO <nome>` | Nome da paciência |
| `BARALHOS <n>` | Número de baralhos |
| `TIPO <tipo> <flags>` | Define um tipo de pilha |
| `INIT <tipo> <n>` | Cria uma pilha com n cartas iniciais |
| `MOV <orig> <dest> <flags>` | Define um movimento válido |
| `AUTO <orig> <dest> <flags>` | Define um movimento automático |
| `WIN <tipo> <n>` | Condição de vitória |

---

## Limpar

```bash
make clean
```