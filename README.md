# Soft Body Tetris
## Demo Video
[![Watch the video](https://img.youtube.com/vi/9RKrUTAszdo/hqdefault.jpg)](https://www.youtube.com/embed/9RKrUTAszdo)

## What is a Soft Body?

연체는 형태가 바뀌지 않는 강체와 반대로 형태가 바뀔 수 있는 물체입니다. 좀 더 정확한 표현으로는 물체 안의 두 점의 상대적인 위치가 변할 수 있다고 할 수 있겠습니다. 부드러운 천, 머리카락, 푸딩, 근육, 살과 같은 것들이 대표적인 연체죠. 애니메이션, 게임에서 연체가 자주 사용되기 때문에 오래전부터 연구되어왔던 분야입니다.
<p align="center"><img src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/c9627cde-b113-4dd2-a3c4-7cb939f893d3"></p>

<p align="center">이미지 출처=https://www.reddit.com/r/gifs/comments/1zeqym/cloth_simulation/</p>

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

<p align="center">이미지 출처=https://en.wikipedia.org/wiki/Euler_method</p>

### Verlet Integration
Verlet Integration은 Euler Method의 단점을 해결한 방식입니다. 속도를 위치와 시간 간격으로 유도하여 소거하고, 위치와 힘만을 갖고 다음 시점의 위치를 계산해냅니다. 오차가 크지 않으며, 충돌시 위치만 바꿔주면 됩니다.

$$v_{n}=\frac{x_{n}-x_{n-1}}{\Delta t}$$

$$v_{n+1}=\frac{x_{n}-x_{n-1}}{\Delta t}+\frac{f_{n}}{m}\Delta t$$

을 Euler Method의 식에 대입하면

$$x_{n+1}=x_{n}+\frac{x_{n}-x_{n-1}}{\Delta t} \Delta t+\frac{f_{n}}{m}\Delta t^{2}$$

$$=2x_{n}-x_{n-1}+\frac{f_{n}}{m}\Delta t^{2}$$

으로 깔끔하게 정리됩니다. 

[구현된 코드](https://github.com/Yeonwu/SoftBodyTetris/blob/master/SoftBodyTetris/engine/physics/point/MassPoint.cpp#L49)

## Collision
그 다음은 가장 중요한 충돌입니다.
### Collision Detection
가장 먼저 충돌을 감지해야겠죠. 그림처럼 질점이 다른 물체 안에 들어가 있으면 충돌했다고 볼 수 있습니다. 질점이 다른 물체 안에 들어갔는지 알아내는 방법은 간단합니다. 바깥에 있는 임의의 점과 이은 다음에 교점의 개수가 홀수개이면 안에 들어간 것이고, 짝수개이면 밖에 있는 것입니다.
<p align="center"><img width="355" alt="스크린샷 2023-12-13 오후 10 17 07" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/d4f93351-a3e0-4c7b-a8a2-0289b54d7359"></p>
바깥에 있는 점과 도형을 이룬 선분이 교차했는지 알아내기 위해 ccw 알고리즘을 사용했습니다. ccw 알고리즘은 아래 이미지와 같이 3개의 점이 반시계 방향을 이루는지 확인하여 교차를 알아내는 알고리즘입니다. 쉽게 말해, 점 2개 중 하나는 위에, 하나는 아래에 있음을 확인하는 것입니다. 이는 외적의 오른손 법칙을 이용해 알아낼 수 있는데, 반시계/시계 방향에 따라 z축 부호가 결정되기 때문입니다.
<p align="center"><img width="427" alt="스크린샷 2023-12-13 오후 10 23 25" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/c14801a8-58c0-4502-bd60-838f3f557ab5"></p>

[구현된 코드](https://github.com/Yeonwu/SoftBodyTetris/blob/master/SoftBodyTetris/engine/physics/body/IBody.cpp#L64)

### Collision Reaction
충돌 중인 질점을 알아냈으면 이제 충돌을 처리해야합니다. 가장 가까운 선분을 알아낸 다음 수선을 내리고, 양 끝의 질점의 질량과 힘을 갖는 가상의 질점을 만듭니다. 질점과 선분의 충돌은 어렵지만, 질점과 질점의 충돌은 간단하게 해결할 수 있습니다. 저는 완전 탄성 충돌을 가정하고 계산했습니다.

<p align="center"><img width="573" alt="스크린샷 2023-12-13 오후 10 28 21" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/f3f30099-8c41-463d-88ef-d057f573afb3"></p>

마지막으로 가상의 질점에 가해진 물리적 변화를 원래 질점에 적용시키면 그림과 같이 충돌이 처리된 상태가 됩니다.

질점과 질점 사이의 충돌도 처리해주어야합니다. 질점의 위치가 겹치게되면 가장 가까운 선분 검출에 문제가 생기기 때문입니다. 일정 거리 안으로 들어올 경우 거리를 벌려주는 방식으로 처리했습니다.

[구현된 코드](https://github.com/Yeonwu/SoftBodyTetris/blob/master/SoftBodyTetris/engine/physics/body/IBody.cpp#L121)

## Shape Matching

마지막으로 모양을 유지하기 위한 처리입니다. 그냥 스프링으로 연결해도 어느 정도는 시뮬레이션이 가능하지만, 강한 힘을 받으면 모양이 깨질 수 있습니다. 그림과 같이 원래 모양과 변형된 모양의 각 점을 질량 중심을 시점으로 하는 벡터로 나타낸 뒤, 가장 차이가 적은 각도 세타를 구해 회전시킨 후 변형된 모양의 점을 원래 모양의 점과 스프링으로 연결해 모양을 유지할 수 있습니다.

<p align="center"><img width="440" alt="스크린샷 2023-12-14 오전 12 18 40" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/a5da1af5-04fd-477f-908f-b9060f8a4ed8"></p>

$i$번째 원래 모양 벡터 $O_{i}$, $i$번째 변형된 모양 벡터 $D_{i}$, 회전 행렬 $R_{\theta}$에 대해 차이 $E_{\theta}$는 다음과 같이 나타나며,  

$$E_{\theta}=\sum_{i=1}^{N}||O_{i}-R_{\theta}D_{i}||$$

이를 미분하여 최소를 찾으면 다음과 같이 정리됩니다. [출처](https://lisyarus.github.io/blog/physics/2023/05/10/soft-body-physics.html#collision-resolution)

$$ \theta=-tan^{-1}(\frac{\sum D_{i} \times O_{i}}{ \sum D_{i} \cdot O_{i} })$$

[구현된 코드](https://github.com/Yeonwu/SoftBodyTetris/blob/master/SoftBodyTetris/engine/physics/body/SoftBody.cpp#L29)






