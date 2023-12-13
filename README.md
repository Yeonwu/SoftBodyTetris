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
<p align="center">
<img width="546" alt="스크린샷 2023-12-13 오후 9 55 32" src="https://github.com/Yeonwu/SoftBodyTetris/assets/61102178/d137d00b-94ba-40cb-b9e6-e1f768bfe77f">
</p>

## Physics
힘, 속도를 고려해 모든 질점의 위치를 계산해내는 것이 시뮬레이션의 핵심입니다. 저는 2가지 방법을 시도했고, 최종적으로 Verlet Integration을 적용했습니다.

### Euler Method
$$ x=v \cdot dt $$

$$ dv=a \cdot dt $$

$$ a=\frac{F}{m} $$

위의 간단한 뉴턴 방정식을 그대로 구현하는 것이 Euler Method입니다. 시간에 대한 미분인 $ dt $를 아주 작은 시간 조각 $ \Delta t $로 근사하여 다음 시점에서의 위치, 속도, 힘을 계산하는 것이죠.

$$ x_{n+1}=x_{n} + v_{n} \Delta t $$

$$ v_{n+1}=v_{n}+\frac{f_{n}}{m}\Delta t$$
