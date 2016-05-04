// Nome  : William Gonçalvez da Cruz
// RA    : 188671
// Turma : W

/*  Lab semanal 04 : Agenda Telefonica

    O intuito desse lab é desenvolver um programa que faça controle de contatos de uma agenda telefônica
    Os contatos podem ser dividos em dois tipos, que serão representados pelos números após os ':' :
        - Pessoal      : 1
        - Profissional : 2 

    Cada contato tem 5 atributos : 
        - Nome     (String)
        - CPF      (Inteiro 11 dígitos)
        - Endereço (String)
        - Telefone Residencial (Inteiro 10 dígitos)
        - Telefone Celular     (Inteiro 10 dígitos)

   
    O programa pode assumir 8 funcionalidades representadas pelo números de entrada, sendo que a zero, quando chamada, termina o programa : 
        1 – inserir
        2 – excluir
        3 – alterar
        4 – buscar
        5 – listar pessoais
        6 – listar profissionais
        7 – listar todos
        0 – Sair
    
    Entrada : Consiste de um número da primeira funcionalidade seguida da entrada da funcionalidade que aquele número representa.
    Saida   : O retorno das funcionalidades impresso na tela, e quando finalizado, imprime um "Obrigado!".

*/

#include <stdio.h>
#include <string.h>

#define PESSOAL 1
#define PROFISSIONAL 2
#define TAMANHO_AGENDA 10

#define SUCESSO 1
#define FALHA -1

#define INCLUIR 1
#define EXCLUIR 2
#define ALTERAR 3
#define BUSCAR 4
#define LISTAR_PESSOAL 5
#define LISTAR_PROFISSIONAL 6
#define LISTAR_TODOS 7
#define SAIR 0

typedef char string[60];

void lerString(string s) {
    scanf(" %[^\n]s", s);
}

unsigned long lerLong() {
    unsigned long l;
    scanf("%lu", &l);
    return l;
}

int lerOpcao() {
    int opcao;
    scanf("%d", &opcao);
    return opcao;    
}

int tipoDeContatoParaListagem (int opcaoDeListagem) {
    if (opcaoDeListagem == LISTAR_PESSOAL) {
        return PESSOAL;
    }

    return PROFISSIONAL;
}

void contatoInexistente (string nome) {
    printf("Desculpe, o contato %s nao existe!\n", nome);
} 

void excluirDadosDosVetores(int posicao, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {
    
    for (int i = posicao; i < qtdContatos - 2; i++) {
        strcpy(nomes[i], nomes[i+1]);
        strcpy(enderecos[i] ,enderecos[i+1]);

        telefones[i] = telefones[i+1];
        cpfs[i] = cpfs[i+1];
        celulares[i] = celulares[i+1];
    }
} 

void alterarDadosDosVetores(int posicao, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[]) {

    string endereco;

    unsigned long telefone,
                  cpf,
                  celular;

    cpf = lerLong();
    lerString(endereco);
    telefone = lerLong();
    celular = lerLong();
    
    strcpy(enderecos[posicao] ,endereco);
    
    telefones[posicao] = telefone;
    cpfs[posicao] = cpf;
    celulares[posicao] = celular;
}

void listarDadosDosVetoresNaPosicao (int posicao, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[]) {
    printf("%s\n", nomes[posicao]);
    printf("%lu\n", cpfs[posicao]);
    printf("%s\n", enderecos[posicao]);
    printf("%lu\n", telefones[posicao]);
    printf("%lu\n", celulares[posicao]);
}

int validarFuncionalidadeComChave (int funcionalidade, string chave, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {

    lerString(chave);

    if (qtdContatos == 0) {
        return FALHA;
    }

    for (int i = 0; i < qtdContatos; i++) {
        if (strcmp(chave, nomes[i]) == 0) {

            switch (funcionalidade) {
                case EXCLUIR :    
                    excluirDadosDosVetores(i, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
                    break;
                case ALTERAR : 
                    alterarDadosDosVetores(i, nomes, cpfs, enderecos, telefones, celulares);
                    break;
                case BUSCAR : 
                    listarDadosDosVetoresNaPosicao(i, nomes, cpfs, enderecos, telefones, celulares);
                    break;
            }
            
            return SUCESSO;
        }
    }

    return FALHA;
}

// Lê os contatos e insere nos vetores, retornando negativo caso agenda esteja cheia e positivo caso tenha sido inserido com sucesso
int inserir (string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {
    if (qtdContatos == TAMANHO_AGENDA) {
        return FALHA;
    }

    string nome,
           endereco;

    unsigned long telefone,
                  cpf,
                  celular;

    lerString(nome);   
    cpf = lerLong();
    lerString(endereco);
    telefone = lerLong();
    celular = lerLong();

    // Copia o valor das variaveis lidas para o vetor
    strcpy(nomes[qtdContatos], nome);
    strcpy(enderecos[qtdContatos] ,endereco);
    
    telefones[qtdContatos] = telefone;
    cpfs[qtdContatos] = cpf;
    celulares[qtdContatos] = celular;

    return SUCESSO;
}

// Usa a resposta do inserir para printar a mensagem, e altera o valor da quantidade de contatos de acordo com o sucesso da inserção
int respostaInserir(int resposta, int qtdContatos) {
    if (resposta == SUCESSO) {
        printf("Inserido com sucesso!\n");
        qtdContatos++;
    } else {
        printf("Desculpe, agenda cheia!\n");
    }

    return qtdContatos;
}

int excluir (string chave, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {
    
    /* lerString(chave);

    if (qtdContatos == 0) {
        return FALHA;
    }

    for (int i = 0; i < qtdContatos; i++) {
        if (strcmp(chave, nomes[i]) == 0) {
            excluirDadosDosVetores(i, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            return SUCESSO;
        }
    }

    return FALHA; */

    return validarFuncionalidadeComChave (EXCLUIR, chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos); 
}

int respostaExcluir (int resposta, int qtdContatos, string chave) {
    if (resposta == SUCESSO) {
        printf("Excluido com sucesso!\n");
        qtdContatos--;
    } else {
        contatoInexistente(chave);
    }

    return qtdContatos;
}

int alterar (string chave, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {
    
    return validarFuncionalidadeComChave (ALTERAR, chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos); 
}

void respostaAlterar(int resposta, string chave) {
    if (resposta == SUCESSO) {
        printf("Alterado com sucesso!\n");
    } else {
        contatoInexistente(chave);
    }
}

int buscar(string chave, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {
    
    return validarFuncionalidadeComChave (BUSCAR, chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos); 
}

void respostaBuscar(int resposta, string chave) {
    if (resposta == SUCESSO) {
        printf("Buscado com sucesso!\n");
    } else {
        contatoInexistente(chave);
    }
}

int funcionalidadesParaTipoContato(int opcao, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {

    int resposta;
    string chave;

    switch (opcao) {
        case INCLUIR: 
            resposta = inserir(nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            qtdContatos = respostaInserir(resposta, qtdContatos);
            break;
        case EXCLUIR:
            resposta = excluir(chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            qtdContatos = respostaExcluir(resposta, qtdContatos, chave);
            break;
        case ALTERAR:
            resposta = alterar(chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            respostaAlterar(resposta, chave);
            break;
        case BUSCAR: 
            resposta = buscar(chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            respostaBuscar(resposta, chave);
            break;
        default:
            break; 
    }

    return qtdContatos;
}

int main() {
    
    string nomePessoal[TAMANHO_AGENDA],
           nomeProfissional[TAMANHO_AGENDA], 
           enderecoPessoal[TAMANHO_AGENDA],
           enderecoProfissional[TAMANHO_AGENDA];
           
   unsigned long telefonePessoal[TAMANHO_AGENDA],
                 telefoneProfissional[TAMANHO_AGENDA],
                 celularPessoal[TAMANHO_AGENDA],
                 celularProfissional[TAMANHO_AGENDA],
                 cpfPessoal[TAMANHO_AGENDA],
                 cpfProfissional[TAMANHO_AGENDA];
    
   int qtdContatosPessoal = 0,
       qtdContatosProfissional = 0,
       opcao,
       tipoContato;

    opcao = lerOpcao();

    while (opcao != 0) {

        if (opcao < LISTAR_PESSOAL) {        
            tipoContato = lerOpcao();
        } else {
            tipoContato = tipoDeContatoParaListagem(opcao);
        }

        if (tipoContato == PESSOAL) {
            qtdContatosPessoal = funcionalidadesParaTipoContato(opcao, 
                                                                nomePessoal, 
                                                                cpfPessoal, 
                                                                enderecoPessoal,
                                                                telefonePessoal, 
                                                                celularPessoal, 
                                                                qtdContatosPessoal); 
        } else if (tipoContato == PROFISSIONAL) {
            qtdContatosProfissional = funcionalidadesParaTipoContato(opcao, 
                                                                     nomeProfissional, 
                                                                     cpfProfissional, 
                                                                     enderecoProfissional, 
                                                                     telefoneProfissional, 
                                                                     celularProfissional, 
                                                                     qtdContatosProfissional); 
        } else {
            funcionalidadesParaTipoContato(opcao, 
                                           nomePessoal, 
                                           cpfPessoal, 
                                           enderecoPessoal,
                                           telefonePessoal, 
                                           celularPessoal, 
                                           qtdContatosPessoal); 
            
            funcionalidadesParaTipoContato(opcao, 
                                           nomeProfissional, 
                                           cpfProfissional, 
                                           enderecoProfissional, 
                                           telefoneProfissional, 
                                           celularProfissional, 
                                           qtdContatosProfissional); 

        }
        
        // TODO explodir isso aqui, 
        // opcao = lerOpcao();
        opcao = 0;
    } 

    printf("Obrigado!\n");
    return 0;
}

void printL(unsigned long vet[], int qtd) {
    for (int i = 0; i < qtd; i++)
        printf("%lu\n", vet[i]);
}

void printS(string vet[], int qtd) {
    for (int i = 0; i < qtd; i++)
        printf("%s\n", vet[i]);
}
