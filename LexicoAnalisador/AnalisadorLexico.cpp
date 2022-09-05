
#include <iostream>
#include <fstream>

#include "FuncoesCompostas.cpp"
#include "FuncoesSimples.cpp"

int main(){ 
    char separators[]{',', ':','_', '(', ')', '[', ']'};
    std::string BracketComp[]{"begin", "end"};
    std::string compSeparators[]{":=", "step", "until", "while", "comment"}; //:= pode ser : ou :=
    char opArithmetic[]{'+', '-', '*', '/'};
    char opRelational[]{'<', '=', '>'};
    std::string opCompRelational[]{"<=", "!=", ">="};
    std::string declarator[]{"own", "integer", "array", "procedure"};

    std::string opSequential[] {"goto", "if", "then", "else", "for", "do"}; //'e' pode ser end ou else
    
    char Letters[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char Digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    int validBegin{-1};       
    int validEnd{-1};
    int validAssigment{-1};
    int validStep{-1};
    int validUntil{-1};
    int validWhile{-1};
    int validComment{-1};
    int validMenorIgual{-1};
    int validDiferente{-1};
    int validMaiorIgual{-1};
    int validOwn{-1};
    int validInt{-1};
    int validArray{-1};
    int validProcedure{-1};
    int validGoto{-1};
    int validIf{-1};
    int validThen{-1};
    int validElse{-1};
    int validFor{-1};
    int validDo{-1};

    std::list<std::string> TokensClasses; //Lista final do output,,,,
    
    std::fstream File;    //Criando o objeto (arquivo)
    File.open("algol.txt", std::ios_base::in);

    if(File.is_open()){
        char character;

        while(!File.eof()){
            File.get(character);
            // Verificação dos caracteres Compostos
            if(character == 'b' || validBegin >=0){
                TokensClasses=SeekBegin(validBegin, BracketComp,character, TokensClasses);
            }
            if(character == 'e' || validEnd >=0){
                TokensClasses=SeekEnd(validEnd, BracketComp, character, TokensClasses);
            }
            if(character == ':' || validAssigment >= 0){
                TokensClasses=SeekAssigment(validAssigment, compSeparators, character, TokensClasses);
            }
            if(character == 's' || validStep >= 0){
                TokensClasses=SeekStep(validStep, compSeparators, character, TokensClasses);
            }
            if(character == 'u' || validUntil >=0){
                TokensClasses=Seekuntil(validUntil, compSeparators, character, TokensClasses);
            }
            if(character=='w' || validWhile>=0){
                TokensClasses=SeekWhile(validWhile,compSeparators, character, TokensClasses);
            }
            if(character=='c' || validComment>=0){
                TokensClasses=SeekComment(validComment, compSeparators, character, TokensClasses);
            }
            if(character=='<' || validMenorIgual>=0){
                TokensClasses=SeekMenorIgual(validMenorIgual, opCompRelational, character, TokensClasses);
            }
            if(character=='!' || validDiferente>=0){
                TokensClasses=SeekDiferente(validDiferente, opCompRelational, character, TokensClasses);
            }
            if(character=='>' || validMaiorIgual>=0){
                TokensClasses=SeekMaiorIgual(validMaiorIgual, opCompRelational, character, TokensClasses);
            }
            if(character=='o' || validOwn>=0){
                TokensClasses=SeekOwn(validOwn, declarator, character, TokensClasses);
            }
            if(character=='i' || validInt >=0){
                TokensClasses=SeekInteger(validInt, declarator, character, TokensClasses);
            }
            if(character=='a' || validArray >=0){
                TokensClasses=SeekArray(validArray, declarator, character, TokensClasses);
            }
            if(character=='p' || validProcedure >=0){
                TokensClasses=SeekProcedure(validProcedure, declarator, character, TokensClasses);
            }
            if(character=='g' || validGoto >=0){
                TokensClasses=SeekGoto(validGoto, opSequential, character, TokensClasses);
            }
            if(character=='i' || validIf >=0){
                TokensClasses=SeekIf(validIf, opSequential, character, TokensClasses);
            }
            if(character=='t' || validThen >=0){
                TokensClasses=SeekThen(validThen, opSequential, character, TokensClasses);
            }
            if(character=='e' || validElse >=0){
                TokensClasses=SeekElse(validElse, opSequential, character, TokensClasses);
            }
            if(character=='f' || validFor >=0){
                TokensClasses=SeekFor(validFor, opSequential, character, TokensClasses);
            }
            if(character=='d' || validDo >=0){
                TokensClasses=SeekDo(validDo, opSequential, character, TokensClasses);
            }


            // Verificação dos caracteres simples
            TokensClasses=SeekLetters(0, Letters, (sizeof(Letters)/sizeof(Letters[0])), character, TokensClasses);
            TokensClasses=SeekSeparators(separators, (sizeof(separators)/sizeof(separators[0])), character, TokensClasses);
            TokensClasses=SeekArithmetic(opArithmetic, (sizeof(opArithmetic)/sizeof(opArithmetic[0])), character, TokensClasses);
            TokensClasses=SeekRelational(opRelational, (sizeof(opRelational)/sizeof(opRelational[0])), character, TokensClasses);
        }
        //Verificar pq não está funcionando 
        File.close();
        if(File.is_open()){
            std::cout << "Não foi possivel fechar o arquivo\n";
        }
    }
    
    //Imprimindo lista com os tokens Finais
    for (auto i: TokensClasses)
    {
        std::cout << i << std::endl;
    }

    return 0;
}