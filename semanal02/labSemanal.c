// Nome : William Gonçalves da Cruz
// RA   : 188671

/*  Descrição do Problema : 
 *      Uma cidade realiza um evento sempre em seu aniversário e em toda sexta feira 13 onde enche uma 
 *  maquete de água.Assim, é preciso que calculemos quanto será gasto de dinheiro ao longo dos anos
 *  começando a contagem a partir de janeiro de 2016
 *
 *  Regras:
 *      A maquete em si possui objetos que ocupam volume, tendo que ser subtraidos do volume total
 *  para saber a quantidade de água. Se o aniversário da cidade é em dia anterior ou posterior a 
 *  sexta-feira 13, a água é reutilizada, não precisando comprar mais. 
 *
 *  Entradas:
 *      N ilhas, no formato (x ,  y) que são as coordenadas do poligono que forma a superficie da ilha
 *      A data do aniversário da cidade (dia/mes)
 *      O ultimo ano em que ocorrerá o evento
 *      F número de fornecedores
 *      F linhas, no formato capacidade galão fornecedor e o preço unitário do galão (c $p)
 */

#include <stdio.h>

int main() {
    int numIlhas,
        diaAtual,
        mesAtual,
        anoAtual, 
        diaNiver,
        mesNiver,
        diaSeguido,
        diaSemanaSeguido, 
        anoUltimo,
        qtdDiasMes,
        diaSemana,
        qtdFestival,
        numFornecedores,
        capacidadeGalao,
        qtdGaloes,
        litros,
        i;

    double precoGalao,
           menorPreco,
           precoAtual,
           xAnterior,
           yAnterior,
           xProximo,
           yProximo,
           xPrimeiro,
           yPrimeiro,
           xMaiorBorda,
           yMaiorBorda,
           xMenorBorda,
           yMenorBorda,
           areaIlha,
           areaAtual,
           areaAgua,
           volume;

    
    areaIlha  = 0.0;
    
    // Começa a lógica de calculas o volume de água necessário na maquete
    scanf("%d", &numIlhas);

    // Para calcular a aŕea de um poligono a partir de suas coordenadas, User a formula de Shoelace
    // (Laço de cadarço), que consiste na multiplicação de 1/2 pelo módulo de uma somatórias 
    // envolvendo as coordenadas
    for (i = 0; i < numIlhas; i++) { 
        scanf(" (%lf , %lf)", &xPrimeiro, &yPrimeiro);

        xAnterior = xPrimeiro;
        yAnterior = yPrimeiro;

        // Caso seja a primeira ilha, inicializa as coordenadas da borda para comparação
        if (i == 0) {
            yMenorBorda = yAnterior;
            yMaiorBorda = yAnterior;
            xMenorBorda = xAnterior;
            xMaiorBorda = xAnterior;
        }

        // Para o caso da primeira coordena ser a mais perto da borda
        if (xAnterior > xMaiorBorda)
            xMaiorBorda = xAnterior;

        if (xAnterior < xMenorBorda)
            xMenorBorda = xAnterior;

        if (yAnterior > yMaiorBorda)
            yMaiorBorda = yAnterior;

        if (yAnterior < yMenorBorda)
            yMenorBorda = yAnterior;

        // Repetição para ler as coordenadas da Ilha atual
        for(areaAtual = 0.0;;) {
            scanf(" (%lf , %lf)", &xProximo, &yProximo);

            // Para calular a area, é preciso multiplicar o X da  coordenada atual com o 
            // Y da seguinte, Subtraindo o resultado com Y da seguinte multuplicado com X da atual, 
            // até chegarem nas ultimas coordenadas, onde as ultimas coordenadas sao multiplicadas
            // de acordo com a regra acima
            
            areaAtual = areaAtual + (xAnterior * yProximo);
            areaAtual = areaAtual - (yAnterior * xProximo);

            //Sequencia de condições para saber como distanciar 50 cm do x Mais distante das Ilhas
            if (xProximo > xMaiorBorda)
                xMaiorBorda = xProximo;

            if (xProximo < xMenorBorda)
                xMenorBorda = xProximo;

            if (yProximo > yMaiorBorda)
                yMaiorBorda = yProximo;

            if (yProximo < yMenorBorda)
                yMenorBorda = yProximo;
            
            if (xProximo == xPrimeiro && yProximo == yPrimeiro) 
                break; 

            // Atualiza o valor das Coordenadas anteriores
            yAnterior = yProximo;
            xAnterior = xProximo;
        }

        if(areaAtual < 0) // Modulo da área
            areaAtual = -areaAtual;

        areaIlha += 0.5 * areaAtual;
    }

    // As bordas devem ficar a pelo menos 50 cm (0,5 metros) de distancia de todas as ilhas
    xMenorBorda -= 0.5;
    yMenorBorda -= 0.5;
    xMaiorBorda += 0.5;
    yMaiorBorda += 0.5;

    // Calculando a área do retagulo de margem  
    areaAgua = (xMaiorBorda - xMenorBorda) * (yMaiorBorda - yMenorBorda);

    // Retirando os espaços das ilhas da area q será coberta com aǵua
    areaAgua = areaAgua - areaIlha;

    // Calculo do volume, área vezes 0,5 de profundidade
    volume = areaAgua * 0.5;

    // 1 m³ de água == 1000 Litros de aǵua
    litros = volume * 1000;

    // inicialização das datas para uso no algoritmo'
    diaAtual = 1;
    mesAtual = 1;
    anoAtual = 2016;
    qtdDiasMes = 31;
    diaSemana = 0;
    qtdFestival = 0;

    // Começa a lógica de contar os dias de Festival
    scanf("%d/%d", &diaNiver, &mesNiver);
    
    // O final de um ano seria equivalente ao começo do proximo, portanto somo um para facilitar a logica
    scanf("%d", &anoUltimo);
    anoUltimo++;
    
    for (;; diaAtual++, diaSemana++) {

        // O mês chegou ao final
        if (diaAtual > qtdDiasMes) {
            diaAtual = 1;
            mesAtual++;
           
            // Caso o mes seja 0, completou um ano
            if (mesAtual > 12) {
                mesAtual = 1;
                anoAtual++;

                // Caso seja o ano descrito pelo programa, parar a contagem de festivais
                if (anoAtual == anoUltimo)
                    break;
            }

            switch (mesAtual) {
                // Para o caso de ser Fevereiro
                case 2:  
                    if (anoAtual % 400 == 0) // Bissexto
                        qtdDiasMes = 29;
                    else if (anoAtual % 100 == 0)  // Não Bissexto
                        qtdDiasMes = 28;
                    else if (anoAtual % 4 == 0) // Bissexto
                        qtdDiasMes = 29;
                    else // Não Bissexto
                        qtdDiasMes = 28;
                    
                    break;

                case 1: // Números dos Meses com 31 dias naquele Mes
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    qtdDiasMes = 31;
                    break;
                default: 
                    qtdDiasMes = 30;
            }
        } else {
            
            // É o dia do aniversário da cidade
            if (diaAtual == diaNiver && mesAtual == mesNiver) {
                qtdFestival++;
          
                diaSeguido = diaAtual + 1;
                diaSemanaSeguido = diaSemana + 1;

                // Há uma sexta feira treze no dia anterior ao dia do aniversário da cidade
                // logo, precisamos desconsiderar esse dia pois será usada a mesma água
                if (diaSeguido == 13 && diaSemanaSeguido % 7 == 0) {
                    qtdFestival--;
                }

                diaSeguido = diaAtual - 1;
                diaSemanaSeguido = diaSemana - 1;

                // Caso a sexta treze tenha sido um dia antes do Aniversário da Cidade, mesma água
                if (diaSeguido == 13 && diaSemanaSeguido % 7 == 0) {
                    qtdFestival--;
                }

            } else if (diaSemana % 7 == 0 && diaAtual == 13) {
                qtdFestival++;
            }
            // Acima qualifica sexta feira Treze, porem preve a possibilidade do aniversario da cidade
            // Cair em uma sexta feira treze, não sendo preciso gastar mais água 
        } 
    }
   
    // Começa a lógica de encontrar o melhor preço dos galões de água  
    scanf("%d", &numFornecedores);

    // Realiza o primeiro check fora do for para o menor preço começar como  o primeiro
    scanf("%d $%lf", &capacidadeGalao, &precoGalao);
    
    qtdGaloes = litros / capacidadeGalao;
   
    // Para o caso de todos os litros não terem sido suprimidos, é preciso comprar mais um galao 
    if (litros % capacidadeGalao != 0) 
        qtdGaloes++;
  
    // O preço é calculado a partir da quantidade de galoes, o preço unitario e o numero de festivais 
    precoAtual = qtdGaloes * precoGalao * qtdFestival;
    menorPreco = precoAtual;

    for (i = 1; i < numFornecedores; i++) {
        
        scanf("%d $%lf", &capacidadeGalao, &precoGalao);
        
        qtdGaloes = litros / capacidadeGalao;
      
        // Para o caso de todos os litros não ser exata, significa que faltará água a menos
        // que mais um galão seja comprado, pois não são vendidos galões sem ser cheios 
        if (litros % capacidadeGalao != 0) 
            qtdGaloes++;

        precoAtual = qtdGaloes * precoGalao * qtdFestival;

        if (precoAtual < menorPreco)
            menorPreco = precoAtual;
    }

    printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", menorPreco);
   
    return 0;
}

