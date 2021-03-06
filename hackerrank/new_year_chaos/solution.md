### Introduction
O(n^2)은 timeout. O(nlogn) 또는 O(n)이 필요하다.
생각해본 결과 O(n) incremental algorithm으로 해결할 수 있었다.
한 사람에게 주어진 최대 bribe 수가 제한되어 있어서 가능한 알고리즘이다.


### Time complexity
O(N)


### Idea
bribe는 상대방과 자신의 순서를 바꾸는 일이다. 즉 정렬되어있던 상태에서
한 쌍의 '순서 불일치'가 생기게 된다. 이런 개념을 바탕으로, 최소 bribe의 수는
queue안에서 찾을 수 있는, '순서 불일치' 쌍의 수와 같다.

여기까지는 어렵지 않게 생각해낼 수 있다. 하지만 모든 쌍을 찾기 위해서는 O(n^2)
의 시간 복잡도가 필요하다. 여기에서 좀 더 생각을 해보면 다음과 같은 사실을
관찰할 수 있다.

첫 k개 안에는 1 ~ (k + 2)의 숫자만 등장할 수 있다. 따라서 그 중 두 개는
등장하지 않을 것이다.


### Algorithm
첫 k개 안에서 '순서 불일치' 쌍의 수를 알고 있다고 가정하자. 또, 등장하지 않은
숫자 두 개를 알고 있다고 하자.

이제 (k + 1)번째 숫자를 보자. 우리는 앞에서 어떤 숫자들이 등장하지 않았는지
알고 있기 때문에, 이 숫자와 앞 k 사이의 '순서 불일치' 쌍의 수를 O(1) 시간에
계산할 수 있다. 그리고 이 숫자와 앞에서 등장하지 않았던 숫자 두 개와 비교해서
등장하지 않은 숫자 두 개를 O(1)에 업데이트 한다.

방금 우리는 k -> (k + 1)로 확장했고, 여기에 O(1)의 시간이 걸렸다. 따라서 이
알고리즘의 시간 복잡도는 O(n)이다.
