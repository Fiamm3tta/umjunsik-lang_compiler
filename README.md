# umjunsik-lang Compiler
밈 기반 언어인 'umjunsik-lang'의 스택 기반 언어 컴파일러를 설계하여 구현했습니다.  

## Outline
'umjunsik-lang'은 인터넷 커뮤니티에서 유래한 밈 기반 언어로,  
'엄', '준', '식', '동탄', 'ㅋ', '어떻게' 등의 키워드와 제한적인 문법을 가지고 있습니다.  

이 프로젝트는 컴파일러 구조를 따라 C++로 각 단계별 구현을 통해 umjunsik-lang 만을 위한 컴파일러를 설계하는 것이 목표입니다.  

## Features
SourceCode.txt의 코드를 읽어들여 다음 과정을 통해 코드가 실행되도록 설계했습니다.  
**Scanner**: 어휘 분석기, 유니코드 기반 토큰 분석 
**Parser.cpp**: 구문 분석기, 어휘 분석 결과를 토대로 구문 트리 설계  
**Generator.cpp**: 목적 코드 생성기, 구문 트리에 따라 이후 설계할 가상머신에 맞는 목적 코드를 생성  
**VirtualMachine.cpp**: 가상 머신, 스택 기반 코드 실행기  

## Auther
**박지훈**
Unreal Engine 5 프로그래밍, 게임 플레이 프로그래밍을 하는 게임 개발자 지망생입니다.  
[GitHub](https://github.com/Fiamm3tta)

## Reference
원본 언어 umjunsik-lang  
[GitHub](https://github.com/rycont/umjunsik-lang)  

참고 코드 crafting-compiler  
[GitHub](https://github.com/AcornPublishing/crafting-compiler)