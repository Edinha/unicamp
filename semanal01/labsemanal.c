//Nome : William Gonçalves da Cruz
//RA   : 188671

/*
 *  Objetivo do programa: Calcular a data de um evento baseado na data atual e nas informações
 *  quantos dias completam um mês e quantos meses completam um ano, O número de dias até o evento na Base 6
 *
 *  Entrada: Uma data no formato dd/mm/aaaa D M X, sendo todos eles inteiros
 *      dd, mm, aaaa, M, N -> Inteiro Positivo Base decimal menor que 10000
 *      X -> Inteiro não negativo  na Base 6 de até 8 dígitos
 *  Saida  : Uma data no formata dd/mm/aaaa 
 */

#include <stdio.h>

int main(void) {
    int diaData = 0, 
        mesData = 0, 
        anoData = 0,
        diasEmUmMes = 0,
        mesesEmUmAno = 0,
        diasConvertido = 0,
        multiplicador = 1, 
        diaEvento = 0,
        mesEvento = 0, 
        anoEvento = 0,
        diasCompletaramMeses = 0,
        mesesCompletaramAnos = 0;

    unsigned int diasRestantes = 0;

    scanf("%d/%d/%d %d %d %ui", &diaData, &mesData, &anoData, &diasEmUmMes, &mesesEmUmAno, &diasRestantes);

    // Convertendo o numero base 6 de 8 casas
    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    diasConvertido += (diasRestantes % 10) * multiplicador;
    multiplicador = multiplicador * 6;
    diasRestantes = diasRestantes / 10;

    // Número de meses completos pela divisão inteira
    mesEvento = diasConvertido / diasEmUmMes;
    
    // Para conseguir a quantidade de dias a serem somados na data, aplicamos a linha abaixo
    // é o número na base 10 menos a quantidade de dias em um mês vezes o número de meses inteiros (divisao)
    // restando assim apenas dias que 'cabem' em um mês
    diaEvento = diasConvertido - diasEmUmMes * mesEvento;
 
    // As variáveis abaixo representam que a soma das datas que completam um mês e um ano, respectivamente
    // A subtração por 1 representa uma contagem convertida para ordenação  
    diasCompletaramMeses = ((diaEvento + diaData - 1) / diasEmUmMes);
    mesesCompletaramAnos = (mesEvento + mesData + diasCompletaramMeses -1 );

    // Logo, os dias que completaram meses devem ser retirados (subtraidos) assim como os meses que completaram anos
    diaEvento = (diaEvento + diaData) - (diasEmUmMes * diasCompletaramMeses );
    mesEvento = (mesEvento + mesData + diasCompletaramMeses) - (mesesEmUmAno * (mesesCompletaramAnos / mesesEmUmAno)); 
   
    // Aqui são adicionados aos anos os meses que foram completados em anos 
    anoEvento = anoData + (mesesCompletaramAnos / mesesEmUmAno);
    
    printf("%d/%d/%d\n" , diaEvento, mesEvento, anoEvento);

    return 0;
}

