# C++ConsoleProject

## [Project IDQ]

  ![Title](https://github.com/user-attachments/assets/ee87a118-44c8-4b59-a07a-cc569185c8a4)

## 1. 개요

C++의 다양한 기능과 객체지향 언어의 특징을 살려 게임을 만드는 프로젝트를 진행하고자 한다.

이 과정을 통해 객체지향 언어의 특징을 잘 파악해 활용하고, 이를 프로젝트에 적용하여 어떻게 설계할 것인지 연습해보고자 한다.

## 2. 프로젝트 목표

드래곤퀘스트1을 모티브로 하는 C++ 콘솔기반 RPG 게임 개발을 목표로 한다.

## 3. 게임 진행

캐릭터를 생성한다.

던전에서 몬스터를 잡고 경험치와 골드를 획득한다.

획득한 경험치로 레벨을 올리고, 골드는 마을 상점에서 아이템과 스킬을 구매해 캐릭터를 성장시킬 수 있다.

클리어 조건 : 던전 제일 깊은곳에 있는 보스 몬스터(투명드래곤)를 처치하는 것.

## 4. 게임 플로우 차트

![idcflowchart](https://github.com/user-attachments/assets/a6151ea3-c4f6-4304-a170-474fb7980722)


## 5. 기능 구현

### 1. 싱글톤 패턴을 이용한 Manager 구현

키보드 입력, 맵 변경 기능을 싱글톤을 활용한 매니저로 구현하였다.

또한 이 매니저를 모아서 한번에 관리하는 Manager 클래스를 만들어서 하나의 Manager로 모든 매니저에 접근할 수 있도록 설계해 보았다.

싱글톤 패턴을 사용함으로써 매니저들을 매번 새로 생성할 필요가 없이 하나씩의 객체만 사용함으로 메모리 절약에 도움이 될 것이라 기대하였다. 

### 2. 더블 버퍼링 구현

맵을 이동하는 부분과 몬스터와 전투하는 부분을 서로 다른 버퍼를 만들어 더블 버퍼링을 구현하였다.

모티브로한 드레곤퀘스트1의 경우 필드를 돌아다니다 몬스터를 마주치면 맵 위에 바로 전투UI가 뜨는 것을 참조하였다.

따라서 기존에 맵을 출력하다가 몬스터를 마주치면 화면을 멈추고, 그 위에 새로운 버퍼를 만들어 전투 장면을 덧씌우는 방법을 채택하였다.

### 3. 맵 데이터를 txt 파일로 저장

맵을 생성하기 위해 100 X 50 사이즈의 텍스트 파일을 생성하였다.

각 칸에 어떤 오브젝트가 있는지 기록하기 위해 각 칸의 숫자를 다르게 하여 만들었다. (ex. 빈공간 = 0, 벽 = 1...)

맵을 이동할 때 마다 txt 파일을 읽어 동적할당으로 생성하고, 다른 맵으로 이동할때는 기존맵을 해제하는 방식으로 구현하였다.

![맵 텍스트](https://github.com/user-attachments/assets/72307a20-91f1-47f8-86a2-fe8b99c50a01)
<맵 예시>

## + 플레이 영상(추후 추가)
