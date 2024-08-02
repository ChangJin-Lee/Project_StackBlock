# 프로젝트 StackBlock

## 개요
`StackBlock`은 블럭을 스폰하고 이동시키며, 사용자 입력을 처리하여 게임을 진행하는 프로젝트입니다. 이 프로젝트에서는 C++와 블루프린트(BP)를 사용하여 다양한 기능을 구현하였습니다.

![Group 30](https://github.com/user-attachments/assets/39018666-2c9a-4499-8684-0dda344e3c72)

## 개발 기간
2024.07.22 ~ 2024.08.01

## 사용된 게임 엔진 및 버전
Unreal Engine 5.4.2

## 참여 인원
2명

## 타임라인
- **2024.07.22 ~ 2024.08.01**
    - 주요 학습 자료:
        - [YouTube Video 1](https://www.youtube.com/watch?v=Pj-3sYOZEow)
        - [YouTube Video 2](https://www.youtube.com/watch?v=K1U9mxHjX4Y)
        - [Unreal Engine Forum Discussion](https://forums.unrealengine.com/t/issue-with-dynamic-mesh-rendering/686189/2)
        - [Epic Games Tutorial](https://dev.epicgames.com/community/learning/tutorials/v0b/unreal-engine-ue5-0-geometry-script-mesh-booleans-and-patterns)

## 기능 목록

1. **블럭 삭제**
    - 충돌 지점에서 블럭 삭제
    - 레이캐스트를 사용하여 블럭 제거
    - Boolean 연산을 통한 블럭 제거

    참고 자료:
    - [Geometry Scripting User Guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/geometry-scripting-users-guide-in-unreal-engine)
    - [Boolean 연산 YouTube Video](https://www.youtube.com/watch?v=SJ0mEIHRWbE)
    - [Boolean 연산 YouTube Video 2](https://www.youtube.com/watch?v=Pj-3sYOZEow)

2. **블럭 스폰**
    - 스폰 위치를 액터로 배치하여 설정
    - 랜덤 위치에서 블럭 스폰
    - 스폰이 불가능한 위치 판단 및 이동 방향 판정

3. **블럭 이동**
    - 블럭을 일정 방향으로 이동시키는 로직 구현

![스크린샷 2024-08-02 172748](https://github.com/user-attachments/assets/94217ed7-6b0a-41de-8b45-168cd9f8bd57)



4. **사용자 입력 처리**
    - 프로젝트 세팅에서 입력 액션 및 바인드 설정
    - C++ 로직 완성 후 블루프린트에서 Key SpaceBar 로직 실행
    - UE5 향상된 입력 시스템 활용

5. **UI 만들기**
    - 인트로, 로딩, 인게임, 엔드 화면 제작
    - 위젯을 통해 층수, 남은 기회 횟수 등 표시
    - 블루프린트에 변수 선언 후 위젯에서 사용

6. **패배 조건**
    - 기회 3번 설정: 블럭을 못 쌓았을 경우 패배 처리

## 기술적인 구현 상세

### 타임라인

#### 2024.07.22 ~ 2024.08.01
- 프로젝트의 기본 구조 설정 및 학습 자료 참조

### WBP (Widget Blueprints)

1. **Intro 위젯**
    - 인트로 화면 구현
2. **Loading 위젯**
    - 로딩 화면 구현
3. **In-game 위젯**
    - 층수 표시
    - 남은 기회 횟수 표시
4. **End 화면 위젯**
    - 성공/실패 화면 구현

### 사운드

- 버튼 클릭 시 사운드 재생
- 사운드 에셋 로드 및 재생
    ```cpp
    static ConstructorHelpers::FObjectFinder<USoundBase> ClickSoundAsset(TEXT("/Script/Engine.SoundWave'/Engine/VREditor/Sounds/UI/Click_on_Button.Click_on_Button'"));
    if (ClickSoundAsset.Succeeded())
    {
        ClickSound = ClickSoundAsset.Object;
    }
    ```

### 이벤트 디스패처

- 사용자 입력 처리 및 이벤트 디스패처를 통해 로직 연결

### Spawner

- 스폰 위치를 액터로 배치하여 설정
- 랜덤 위치에서 블럭 스폰
    ```cpp
    float RandomX = FMath::FRandRange(-10.f, 10.f);
    FVector SpawnLocation = FVector(RandomX, RandomY, RandomZ);
    ```
