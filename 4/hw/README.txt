과제 

다음 3개 중 택 1 해서 하시면 됩니다. 

1. LOB + DREAMHACK + CyKor 과제 (alphanumeric, [Load_of_RTL] wolfman, not_isolated 제외)
2. CyKor 과제(not_isolated 제외) + alphanumeric 또는 wolfman 풀기
3. not_isolated 단 한개 풀기

과제 폴더 내에 setLibc.sh 파일이 있을텐데, 
로컬에서 libc 파일을 맞춰주니 patchelf를 깔고 과제 폴더 내부에서 
./setLibc.sh 실행하시면 동일한 환경에서 문제 푸실 수 있습니다.
과제 폴더 내부에 setLibc.sh가 없는 경우는 libc를 맞춰줄 필요가 없는 문제들입니다.

patchelf 까는 법
sudo apt-get update -y
sudo apt-get install -y patchelf


