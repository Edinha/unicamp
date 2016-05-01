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


char lerOpcao() {
    char opcao;

    scanf("%hhu", &opcao);

    return opcao;    
}

int main() {

    
    
    return 0;
}
