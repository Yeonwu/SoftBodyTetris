# Soft Body Tetris
## What is a Soft Body?

연체는 형태가 바뀌지 않는 강체와 반대로 형태가 바뀔 수 있는 물체입니다. 좀 더 정확한 표현으로는 물체 안의 두 점의 상대적인 위치가 변할 수 있다고 할 수 있겠습니다. 부드러운 천, 머리카락, 푸딩, 근육, 살과 같은 것들이 대표적인 연체죠. 애니메이션, 게임에서 연체가 자주 사용되기 때문에 오래전부터 연구되어왔던 분야입니다.

## Development Environment
- XCode 14.3.1
- C++
- SDL2
  
직접 구현하는 것에 의미가 있는 프로젝트이기 때문에 간단한 2D 그래픽 라이브러리인 SDL2 외에는 사용하지 않았습니다.

## Mass-Spring Model

연체를 시뮬레이션 하는 방법 중 가장 간단한 방법은 Mass-Spring 모델입니다. 질량, 위치, 속도, 힘을 갖는 질점과 두 질점을 연결하고 초기 길이와 용수철 상수를 갖는 Spring을 사용해 구성하는 것이죠. 연체 안의 두 점의 상대적 위치는 변하지만, 결국 원래 자리로 돌아오도록 스프링이 계속해서 힘을 가하여 연체를 시뮬레이션할 수 있습니다. Mass-Spring Model에서 연체는 결국 질점의 집합으로 나타낼 수 있습니다.
<p align="center"><img width="546" alt="스크린샷 2023-12-13 오후 9 55 32" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/d137d00b-94ba-40cb-b9e6-e1f768bfe77f"></p>

## Physics
힘, 속도를 고려해 모든 질점의 위치를 계산해내는 것이 시뮬레이션의 핵심입니다. 저는 2가지 방법을 시도했고, 최종적으로 Verlet Integration을 적용했습니다.

### Euler Method
$$x=v \cdot dt$$

$$dv=a \cdot dt$$

$$a=\frac{F}{m}$$

위의 간단한 뉴턴 방정식을 그대로 구현하는 것이 Euler Method입니다. 시간에 대한 미분인 $dt$를 아주 작은 시간 조각 $\Delta t$로 근사하여 다음 시점에서의 위치, 속도, 힘을 계산하는 것이죠.

$$x_{n+1}=x_{n} + v_{n+1} \Delta t$$

$$v_{n+1}=v_{n}+\frac{f_{n}}{m}\Delta t$$

하지만 Eluer Method는 아래 그래프와 같이 시간이 지날수록 오차가 누적된다는 단점이 있습니다. 또한 충돌시 위치와 속도를 모두 계산하여 바꿔주어야 한다는 단점이 있죠.

<p align="center"><img width="230" alt="스크린샷 2023-12-13 오후 10 05 56" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/72dcedf4-aac1-4468-b1e5-65218a124425"></p>

### Verlet Integration
Verlet Integration은 Euler Method의 단점을 해결한 방식입니다. 속도를 위치와 시간 간격으로 유도하여 소거하고, 위치와 힘만을 갖고 다음 시점의 위치를 계산해냅니다. 오차가 크지 않으며, 충돌시 위치만 바꿔주면 됩니다.

$$v_{n}=\frac{x_{n}-x_{n-1}}{\Delta t}$$

$$v_{n+1}=\frac{x_{n}-x_{n-1}}{\Delta t}+\frac{f_{n}}{m}\Delta t$$

을 Euler Method의 식에 대입하면

$$x_{n+1}=x_{n}+\frac{x_{n}-x_{n-1}}{\Delta t} \Delta t+\frac{f_{n}}{m}\Delta t^{2}$$

$$=2x_{n}-x_{n-1}+\frac{f_{n}}{m}\Delta t^{2}$$

으로 깔끔하게 정리됩니다.

## Collision
그 다음은 가장 중요한 충돌입니다.
### Collision Detection
가장 먼저 충돌을 감지해야겠죠. 그림처럼 질점이 다른 물체 안에 들어가 있으면 충돌했다고 볼 수 있습니다. 질점이 다른 물체 안에 들어갔는지 알아내는 방법은 간단합니다. 바깥에 있는 임의의 점과 이은 다음에 교점의 개수가 홀수개이면 안에 들어간 것이고, 짝수개이면 밖에 있는 것입니다.
<p align="center"><img width="355" alt="스크린샷 2023-12-13 오후 10 17 07" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/d4f93351-a3e0-4c7b-a8a2-0289b54d7359"></p>






