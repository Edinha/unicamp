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
#define AMBOS 3
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

// Lê uma string e armazena no parâmetro string s
void lerString(string s) {
    scanf(" %[^\n]s", s);
}

// Lê um atributo numérico e retorna para uso
long long lerLong() {
    long long l;
    scanf("%lli", &l);
    return l;
}

// Lê a opcao atual ou o tipo de contato a ser tratado e retorna para uso 
int lerOpcao() {
    int opcao;
    scanf("%d", &opcao);
    return opcao;    
}

// Retorna o tipo de contato a partir das funcionalidades de listagem (pessoais, profissionais, ambos)
int tipoDeContatoParaListagem (int opcaoDeListagem) {
    if (opcaoDeListagem == LISTAR_PESSOAL) {
        return PESSOAL;
    }

    if (opcaoDeListagem == LISTAR_PROFISSIONAL) {
        return PROFISSIONAL;
    }

    return AMBOS;
}

// Mensagem de contato não encontrado para excluir, busca, alteração
void contatoInexistente (string nome) {
    printf("Desculpe, contato %s nao existe!\n", nome);
} 

// Manda a posicao onde o contato a ser excluido foi encontrado e retira suas informações de todos os vetores
void excluirDadosDosVetores(int posicao, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) {
    int proximo;

    // Desloca as informações que estão a frente da posição desejada para exclusão para trás, a fim de sobreescrever os dados a serem excluidos
    for (int i = posicao; i < qtdContatos - 1; i++) {
        proximo = i+1;

        strcpy(nomes[i], nomes[proximo]);
        strcpy(enderecos[i] ,enderecos[proximo]);

        telefones[i] = telefones[proximo];
        cpfs[i] = cpfs[proximo];
        celulares[i] = celulares[proximo];
    }
} 

// Lê os dados passados e altera na posíção onde o nome foi encontrado, passando-na por parâmetro
void alterarDadosDosVetores(int posicao, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[]) {

    string endereco;

    long long telefone,
              cpf,
              celular;

    cpf = lerLong();
    lerString(endereco);
    telefone = lerLong();
    celular = lerLong();
    
    // Copia o valor das variaveis lidas para o vetor na posição
    strcpy(enderecos[posicao] ,endereco);
    
    telefones[posicao] = telefone;
    cpfs[posicao] = cpf;
    celulares[posicao] = celular;
}

// Lista as informações de um contato na posicao passada por parâmetro
void listarDadosDosVetoresNaPosicao (int posicao, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[]) {
    printf("%s\n", nomes[posicao]);
    printf("%lli\n", cpfs[posicao]);
    printf("%s\n", enderecos[posicao]);
    printf("%lli\n", telefones[posicao]);
    printf("%lli\n", celulares[posicao]);
}

// Função que extrai a logica de busca da chave que é conjunta a 3 funcionalidades : excluir, alterar e buscar
// Recebe a chave buscada e o vetor de nomes com seu tamanho e retorna FALHA (-1) caso não seja encontrada ou a posição (positiva) caso seja encontrada
int validarPosicaoDaChaveNoVetor (string chave, string nomes[], int qtdContatos) {

    lerString(chave);

    for (int i = 0; i < qtdContatos; i++) {
        if (strcmp(chave, nomes[i]) == 0) {
            return i;
        }
    }

    return FALHA;
}

// Lê os contatos e insere nos vetores, retornando negativo caso agenda esteja cheia e positivo caso tenha sido inserido com sucesso
int inserir (string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) {
    string nome,
           endereco;

    long long telefone,
              cpf,
              celular;

    lerString(nome);   
    cpf = lerLong();
    lerString(endereco);
    telefone = lerLong();
    celular = lerLong();

    if (qtdContatos == TAMANHO_AGENDA) {
        return FALHA;
    }

    // Copia o valor das variaveis lidas para o vetor na posição
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
        printf("Desculpe, agenda lotada!\n");
    }

    return qtdContatos;
}

// Função que exclui um contato cujo nome se encontra na variável chave
int excluir (string chave, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) {
    int posicao = validarPosicaoDaChaveNoVetor (chave, nomes, qtdContatos); 

    if (posicao == FALHA) {
        return FALHA;
    }
    
    excluirDadosDosVetores(posicao, nomes, cpfs, enderecos, telefones, celulares, qtdContatos);
    
    return SUCESSO;
}

// Função para mostrar a mensagem após a tentativa (falha ou não) de exclusão de dados
int respostaExcluir (int resposta, int qtdContatos, string chave) {
    if (resposta == SUCESSO) {
        printf("Excluido com sucesso!\n");
        qtdContatos--;
    } else {
        contatoInexistente(chave);
    }

    return qtdContatos;
}

// Função de alterar dados do vetor com retorno de sucesso ou falha para impressao da mensagem
int alterar (string chave, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) { 
    int posicao = validarPosicaoDaChaveNoVetor (chave, nomes, qtdContatos);

    if (posicao == FALHA) {
        return FALHA;
    }

    alterarDadosDosVetores(posicao, nomes, cpfs, enderecos, telefones, celulares);

    return SUCESSO;
}

// Função para mostrar a mensagem após a tentativa (falha ou não) de alteração de dados
void respostaAlterar(int resposta, string chave) {
    if (resposta == SUCESSO) {
        printf("Alterado com sucesso!\n");
    } else {
        contatoInexistente(chave);
    }
}

// Função de buscar dados do vetor a partir de uma chave (nome do contato) com retorno de sucesso ou falha para impressao da mensagem
int buscar(string chave, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) {
    int posicao = validarPosicaoDaChaveNoVetor (chave, nomes, qtdContatos);

    if (posicao == FALHA) {
        return FALHA;
    }

    listarDadosDosVetoresNaPosicao(posicao, nomes, cpfs, enderecos, telefones, celulares);
 
    return SUCESSO;   
}

// Função para mostrar a mensagem após a tentativa (falha ou não) de busca por dados
void respostaBuscar(int resposta, string chave) {
    if (resposta == SUCESSO) {
        printf("Buscado com sucesso!\n");
    } else {
        contatoInexistente(chave);
    }
}

// Função de listar os dados de todas as posições de todos os vetores
int listar(string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) {

    if (qtdContatos == 0) {
        return FALHA;
    }

    for(int i = 0; i < qtdContatos; i++) {
        listarDadosDosVetoresNaPosicao (i, nomes, cpfs, enderecos, telefones, celulares);
    }

    return SUCESSO;
}

// Resposta da tentativa de listagem dos dados
void respostaListagem(int resposta) {
    if (resposta == FALHA) {
        printf("Desculpe, agenda vazia!\n");
    } else {
        printf("Listado com sucesso!\n");
    }
}

// decidide qual funcionalidade deve ser chamada a partir da opção de entrada imprime as respostas das respectivas funcionalidades
// altera e retorna o valor da quantidade de contatos dependendo da funcionalidade de entrada
int funcionalidadesParaTipoContato(int opcao, string nomes[], long long cpfs[], string enderecos[], long long telefones[], long long celulares[], int qtdContatos) {

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
        case LISTAR_PESSOAL:
        case LISTAR_PROFISSIONAL:
            resposta = listar(nomes, cpfs, enderecos, telefones, celulares, qtdContatos);            
            respostaListagem(resposta);
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
           
   long long telefonePessoal[TAMANHO_AGENDA],
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

    while (opcao != SAIR) {

        // Caso sejam as 4 primeiras opções, é preciso ler o próximo número para definir o tipo de contato a ser tratato
        if (opcao < LISTAR_PESSOAL) {        
            tipoContato = lerOpcao();
        } else {
            // Senão for uma das 4 primeiras, é uma opção de listagem, cujo tipo de contato deve ser retornado pela função tipoDeContatoParaListagem
            tipoContato = tipoDeContatoParaListagem(opcao);
        }

        switch (tipoContato) {
            // Caso seja pessoal, passa os vetores de informações pessoais
            case PESSOAL:       
                qtdContatosPessoal = funcionalidadesParaTipoContato(opcao, 
                                                                    nomePessoal, 
                                                                    cpfPessoal, 
                                                                    enderecoPessoal,
                                                                    telefonePessoal, 
                                                                    celularPessoal, 
                                                                    qtdContatosPessoal);
                break;

            // Caso seja profissional, passa os vetores de contatos profissionais 
            case PROFISSIONAL: 
                qtdContatosProfissional = funcionalidadesParaTipoContato(opcao, 
                                                                         nomeProfissional, 
                                                                         cpfProfissional, 
                                                                         enderecoProfissional, 
                                                                         telefoneProfissional, 
                                                                         celularProfissional, 
                                                                         qtdContatosProfissional);
                break;
            
            // Caso o tipo de contato seja AMBOS devem ser chamadas as listagens para os dois tipos de contatos
            case AMBOS: 
                funcionalidadesParaTipoContato(LISTAR_PESSOAL, 
                                               nomePessoal, 
                                               cpfPessoal, 
                                               enderecoPessoal,
                                               telefonePessoal, 
                                               celularPessoal, 
                                               qtdContatosPessoal); 
            
                 funcionalidadesParaTipoContato(LISTAR_PROFISSIONAL, 
                                               nomeProfissional, 
                                               cpfProfissional, 
                                               enderecoProfissional, 
                                               telefoneProfissional, 
                                               celularProfissional, 
                                               qtdContatosProfissional); 
                break;
 
        }

        opcao = lerOpcao();
    } 

    printf("Obrigado!\n");
    return 0;
}
