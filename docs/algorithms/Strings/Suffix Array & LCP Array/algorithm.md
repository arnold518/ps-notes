---
title: Suffix Array & LCP Array
tags:
    - string
    - suffix_array
    - ~ algorithm
---

# Suffix Array & LCP Array

## Suffix Array

접미사 배열(Suffix Array)는 문자열 $S$의 모든 접미사를 lexicographic 순서로 정렬한 배열이다.
실제 접미사를 저장하기에는 너무 많은 공간이 필요하니, 대신 접미사가 시작하는 위치를 저장한다.

예를 들어, 문자열 $S$=**"GATAGACA"**의 Suffix Array는 $SA[i]=$**[8, 6, 4, 2, 7, 5, 1, 3]**이다.

<center>

| $SA[i]$ | suffix   |
|:-------:|----------|
| 8       | A        |
| 6       | ACA      |
| 4       | AGACA    |
| 2       | ATAGACA  |
| 7       | CA       |
| 5       | GACA     |
| 1       | GATAGACA |
| 3       | TAGACA   |

</center>

### Manber-Myers Algorithm

Manber-Myers Algorithm은 총 $O(logN)$개의 단계로 구성되는데, 각 단계에서 접미사들을 앞의 $2^i$개 문자만 이용하여 정렬한다.
즉, 처음에는 $1$개의 문자만 보고 정렬한 후, 이 결과를 이용하여 $2$개, $4$개, $\cdots$의 문자에 대하여 정렬한다.

