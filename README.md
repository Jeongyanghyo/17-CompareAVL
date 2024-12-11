# 17-CompareAVL
# Result Code
![CompareAVL{Result Image 3}](https://github.com/user-attachments/assets/3b95d82a-aaf7-4634-928d-f4cc88663c10)
![CompareAVL{Result Image 2}](https://github.com/user-attachments/assets/44bffd40-e3a9-4ee8-b51c-43b1e2e150ea)
![CompareAVL{Result Image 1}](https://github.com/user-attachments/assets/423e78cb-e321-43cb-bf5f-e314a5828aa1)


# Code Image
# main code
![CompareAVL {main Code}](https://github.com/user-attachments/assets/ce6bb7a0-454c-4da0-8963-8fb00d0e381f)
# get Code
![CompareAVL {getCode}](https://github.com/user-attachments/assets/10549128-de2a-4c8a-b0f2-b1fa2ba81f62)
# rotate Code
![CompareAVL{rotate Code}](https://github.com/user-attachments/assets/e70de104-4916-4584-a161-c53ba292868b)
# inOrder Code
![CompareAVL{inOrder Code}](https://github.com/user-attachments/assets/d55bd69e-608d-47bd-89d1-9fb1eeca718b)
# insertNode Code
![CompareAVL {insert Node Code}](https://github.com/user-attachments/assets/ef251eac-c90c-4ded-8f43-5acf1b050fdc)
# deleteNode Code
![CompareAVL{delete Node Code}](https://github.com/user-attachments/assets/8b1d4d88-9443-4958-92fa-5e7e862fcee4)

# 탐색 비교 분석
1. AVL트리
   - 항상 O(log n)에 가깝게 동작하므로 탐색 연산에 사용되는 비교 횟수가 일정하며 효율적입니다.
   - n개의 데이터가 삽입 되었을 때 평균 비교횟수는 log n에 근접합니다.

2. 이진 탐색 트리
   - 데이터가 무작위로 삽입 된 경우 AVL과 비슷한 결과가 나올 수 있습니다.
   - 데이터가 정렬되거나 특정 패턴으로 삽입 되면 트리가 편향되어 O(n)에 가까운 비교 횟수가 나옵니다.
   - 탐색 시 더 많은 비교 연산이 필요합니다.

3. 결론
   - AVL트리는 항상 균형을 유지하기 때문에 비교 횟수가 일정하며, 특히 데이터가 많아질수록 효율성이 높아집니다.
   - 이진 탐색 트리는 데이터 삽입 순서와 트리의 구조에 따라 성능이 크게 변합니다. 데이터가 정렬되거나 편향된 경우 비교 횟수가 급격히 증가합니다.
