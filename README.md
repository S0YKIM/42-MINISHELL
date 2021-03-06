# 42-MINISHELL

C project to mimic the bash shell

![image](https://user-images.githubusercontent.com/72433681/166451673-5a690c41-e33d-44d1-9598-e9f22b277382.png)


[π sokim](https://github.com/S0YKIM) | [π heehkim](https://github.com/hhkim0729)

[π λΈμ μ λ¦¬](https://www.notion.so/microshell-b30b48455fcc434a91f4436043f95653)

## μ»€λ° λ©μμ§ κ·μΉ

`νμ λ΄μ© (#μ΄μλ²νΈ)` (μ΄μλ²νΈκ° μλ κ²½μ° μλ΅)

- λ΄μ©μ μμ΄λ‘ μμ±
- μ) Update README.md (#2)

### μ»€λ° νμ

- `Add`: μ½λ μΆκ°
- `Remove`: μ½λ μ­μ 
- `Update`: μ½λ λ° λ¬Έμ μμ 
- `Fix`: μ€λ₯ λ° μ€νμ μμ 
- `Refactor`: μ½λ λ¦¬ν©ν λ§
- `Rename`: νμΌ, λ³μλͺ λ± λ³κ²½


## μ§ν κΈ°λ‘

> π sokim | π heehkim

### 4μ 4μΌ(μ)

λ ν¬ μμ± λ° μ§ν κ³ν

- μ€κ° μ κ²
  - π μ΄μ μμ± λ° νλ‘μ νΈ μμ±
  - π README.md μμ±
- ν μΌ
  - π λΉνΈμΈ env, pwd κ΅¬ν
  - π νκ²½λ³μ νμ± κ΅¬ν

### 4μ 7μΌ(λͺ©)

λͺλ Ήμ΄ νμ± λ‘μ§μ λν λΌμ

- μ€κ° μ κ²
  - π λΉνΈμΈ env, pwd κ΅¬ν
  - π νκ²½λ³μ νμ± κ΅¬ν
- ν μΌ
  - π λΉνΈμΈ export κ΅¬ν
  - π ν ν°ν κ΅¬ν, AST μ΄ν΄νκ³  κ΅¬μ‘° κ΅¬μ

### 4μ 11μΌ(μ)

μ§ν μν© μ κ² λ° μ½λ λ¦¬λ·°

- μ€κ° μ κ²
  - π λΉνΈμΈ export, cd κ΅¬ν
  - π ν ν°ν κ΅¬ν (WIP), AST μ΄ν΄ λ° κ΅¬μ‘° κ΅¬μ
- ν μΌ
  - π λΉνΈμΈ unset, exit κ΅¬ν
  - π ν ν°ν κ΅¬ν μμ±, AST κ΅¬ν

### 4μ 17μΌ(μΌ)

μ½λ λ¦¬λ·° λ° μ°¨ν μ­ν  λΆλ΄

- μ€κ° μ κ²
  - π λΉνΈμΈ unset, echo, exit κ΅¬ν
  - π ν ν°ν κ΅¬ν μμ±, AST κ΅¬ν
- ν μΌ
  - π μκ·Έλ λ° λͺλ Ήμ΄ μ€ν κ΅¬ν
  - π μ€νμ μν λ¦¬λ€μ΄λ μ μ²λ¦¬ κ΅¬ν

### 4μ 20μΌ(μ)

μ§ν μν© μ κ² λ° μ½λ λ¦¬λ·°

- μ€κ° μ κ²
  - π λͺλ Ήμ΄ μ€ν ν¨μ κ΅¬ν, μκ·Έλ μ²λ¦¬ κ΅¬ν
  - π heredoc, λ¦¬λ€μ΄λ μ μν κ΅¬ν
- ν μΌ
  - π SIGTERM μ²λ¦¬, SIGQUIT λ²κ·Έ ν΄κ²°
  - π νμ΄ν κ΅¬ν

### 4μ 28μΌ(λͺ©)

μ§ν μν© μ κ² λ° μ½λ λ¦¬λ·°

- μ€κ° μ κ²
  - π λͺλ Ήμ΄ μ²λ¦¬μ λΉνΈμΈ ν¨μ λ¦¬ν©ν λ§
  - π νμ΄ν κ΅¬ν, νμ€νΈ λ° λ²κ·Έ ν΄κ²°
- ν μΌ
  - π heredoc μκ·Έλ λ²κ·Έ ν΄κ²°
  - π νκ²½λ³μ κ³΅λ°± νΈλ¦¬λ°, νμ€νΈ λ° νκ° μ€λΉ

### 5μ 1μΌ(μΌ)

νμ€νΈ λ° μ΅μ’ μ κ²

- μ€κ° μ κ²
  - π heredoc μκ·Έλ λ²κ·Έ ν΄κ²°, ~ νκ²½λ³μ μ²λ¦¬, μμ€ν€ μνΈ
  - π νκ²½λ³μ κ³΅λ°± νΈλ¦¬λ°, νμ€νΈ λ° λ²κ·Έ ν΄κ²°
- ν μΌ
  - π νμ€νΈ λ° λ²κ·Έ ν΄κ²°, νκ° μ€λΉ
  - π νμ€νΈ λ° λ²κ·Έ ν΄κ²°, μμ€ν€ μνΈ μλ°μ΄νΈ, νκ° μ€λΉ
