# 42-MINISHELL

C project to mimic the bash shell

[🍀 sokim](https://github.com/S0YKIM) | [🌙 heehkim](https://github.com/hhkim0729)

[🔗 노션 정리](https://www.notion.so/microshell-b30b48455fcc434a91f4436043f95653)

## 커밋 메시지 규칙

`타입 내용 (#이슈번호)` (이슈번호가 없는 경우 생략)

- 내용은 영어로 작성
- 예) Update README.md (#2)

### 커밋 타입

- `Add`: 코드 추가
- `Remove`: 코드 삭제
- `Fix`: 오류 및 오탈자 수정
- `Refactor`: 코드 리팩토링
- `Update`: 문서 수정

## 진행 기록

> 🍀 sokim | 🌙 heehkim

### 4월 4일(월)

레포 생성 및 진행 계획

- 중간 점검
  - 🍀 이슈 작성 및 프로젝트 생성
  - 🌙 README.md 작성
- 할일
  - 🍀 빌트인 env, pwd 구현
  - 🌙 환경변수 파싱 구현

### 4월 7일(목)

명령어 파싱 로직에 대한 논의

- 중간 점검
  - 🍀 빌트인 env, pwd 구현
  - 🌙 환경변수 파싱 구현
- 할일
  - 🍀 빌트인 export 구현
  - 🌙 토큰화 구현, AST 이해하고 구조 구상

### 4월 11일(월)

진행 상황 점검 및 코드 리뷰

- 중간 점검
  - 🍀 빌트인 export, cd 구현
  - 🌙 토큰화 구현 (WIP), AST 이해 및 구조 구상
- 할일
  - 🍀 빌트인 unset, exit 구현
  - 🌙 토큰화 구현 완성, AST 구현

### 4월 17일(일)

코드 리뷰 및 차후 역할 분담

- 중간 점검
  - 🍀 빌트인 unset, echo, exit 구현
  - 🌙 토큰화 구현 완성, AST 구현
- 할일
  - 🍀 시그널 및 명령어 실행 구현
  - 🌙 실행을 위한 리다이렉션 처리 구현

### 4월 20일(수)

진행 상황 점검 및 코드 리뷰

- 중간 점검
  - 🍀 명령어 실행 함수 구현, 시그널 처리 구현
  - 🌙 heredoc, 리다이렉션 순회 구현
- 할일
  - 🍀 SIGTERM 처리, SIGQUIT 버그 해결
  - 🌙 파이프 구현
