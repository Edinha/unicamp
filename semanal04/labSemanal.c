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

void alterarDadosDosVetores(int posicao, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {

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
    
    lerString(chave);

    if (qtdContatos == 0) {
        return FALHA;
    }

    for (int i = 0; i < qtdContatos; i++) {
        if (strcmp(chave, nomes[i]) == 0) {
            excluirDadosDosVetores(i, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            return SUCESSO;
        }
    }

    return FALHA;
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
    
    lerString(chave);

    if (qtdContatos == 0) {
        return FALHA;
    }

    for (int i = 0; i < qtdContatos; i++) {
        if (strcmp(chave, nomes[i]) == 0) {
            alterarDadosDosVetores(i, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            return SUCESSO;
        }
    }

    return FALHA;

}

void respostaAlterar(int resposta, string chave) {
    if (resposta == SUCESSO) {
        printf("Alterado com sucesso!\n");
    } else {
        contatoInexistente(chave);
    }
}

int funcionalidadesParaTipoContato(int opcao, string nomes[], unsigned long cpfs[], string enderecos[], unsigned long telefones[], unsigned long celulares[], int qtdContatos) {

    int resposta;
    string chave;

    switch (opcao) {
        case 1: 
            resposta = inserir(nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            qtdContatos = respostaInserir(resposta, qtdContatos);
            break;
        case 2:
            resposta = excluir(chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            qtdContatos = respostaExcluir(resposta, qtdContatos, chave);
        case 3:
            resposta = alterar(chave, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
            respostaAlterar(resposta, chave);
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

        tipoContato = lerOpcao();

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
        }
        
        // TODO explodir isso aqui
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
