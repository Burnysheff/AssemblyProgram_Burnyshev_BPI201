extern Square
extern Triangle
extern Diagonal

; Среднее значение квадратной матрицы
global AverageSquare
AverageSquare:
section .text
push rbp
mov rbp, rsp

    mov eax, [rdi]
    mov rcx, eax
    mov rbx, rcx
    mov r10, 0
    mov r11, 0
.loop_first:
    cmp rbx, eax
    jge .return_first
.loop_second:
    cmp rcx, eax
    jge .return_second

    add r11, 4
    add r10, rdi, r11
    inc rcx
.return_second:
    inc rbx
.return_first:
    mov al, r10
    mov bl, r10
    mul bl
    mov bx, eax
    div bx
    cvtsi2sd    xmm0, bx

leave
ret

; Среднее значение треугольной матрицы
global AverageTriangle
AverageTriangle:
section .text
push rbp
mov rbp, rsp

    mov eax, [rdi]
    mov rcx, eax
    mov rbx, rcx
    mov r10, 0
    mov r11, 0
.loop_first:
    cmp rbx, eax
    jge .return_first
.loop_second:
    cmp rcx, eax
    jge .return_second

    add r11, 4
    add r10, rdi, r11
    inc rcx
.return_second:
    inc rbx
.return_first:
    mov al, r10
    mov bl, r10
    mul bl
    mov bx, eax
    div bx
    cvtsi2sd    xmm0, bx

leave
ret

; Среднее значение диагональной матрицы
global AverageDiagonal
AverageDiagonal:
section .text
push rbp
mov rbp, rsp

    mov eax, [rdi]
    mov rcx, eax
    mov r10, 0
    mov r11, 0
.loop:
    cmp rcx, eax
    jge .return

    add r11, 4
    add r10, rdi, r11
    inc rcx
.return:
    mov al, r10
    mov bl, r10
    mul bl
    mov bx, eax
    div bx
    cvtsi2sd    xmm0, bx

leave
ret

; Функция, откуда вызываются подсчеты среднего по ключу
global PerimeterShape
PerimeterShape:
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес фигуры
    mov eax, [rdi]
    cmp eax, Square
    je .averageSquare
    cmp eax, Triangle
    je .averageTriangle
    cmp eax, Diagonal
    je .averageDiagonal
    xor eax, eax
    cvtsi2sd    xmm0, eax
    jmp     .return
.averageSquare:
    ; Вычисление среднего значения квадратной матрицы
    add     rdi, 4
    call    AverageSquare
    jmp     .return
.averageTriangle:
    ; Вычисление среднего значения треугольной матрицы
    ; 8, так как в в треугольной мы храним как размер, так и шаг
    add     rdi, 8
    call    AverageTriangle
    jmp     .return
.averageDiagonal:
    ; Вычисление среднего значения диагональной матрицы
    add     rdi, 4
    call    AverageDiagonal
.return:
leave
ret

; Функция подсчета общего среднего значения
global AverageOverall
AverageOverall:
section .data
    .sum    dq  0.0
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес начала контейнера
    mov rbx, rsi            ; число фигур
    xor rcx, rcx            ; счетчик матриц
    movsd xmm1, .sum        ; перенос накопителя суммы в регистр 1
.loop:
    cmp rcx, rbx            ; проверка на окончание цикла
    jge .return             ; Перебрали все матрицы

    mov r10, rdi            ; сохранение начала матрицы
    call PerimeterShape     ; Получение периметра первой фигуры
    addsd xmm1, xmm0        ; накопление суммы
    inc rcx                 ; индекс следующей фигуры
    add r10, 1604           ; адрес следующей фигуры (1604 - размер матрицы, мы должны выравнивать по нему)
    mov rdi, r10            ; восстановление для передачи параметра
    jmp .loop
.return:
    movsd xmm0, xmm1
leave
ret

; Функция сортирови пузырьком
global BubbleSort
BubbleSort:
section .text
push rbp
mov rbp, rsp

        xor ecx, ecx
        push rsi
        pop ecx

cycl_1: push ecx        ; Основной цикл
        mov eax, rsi
        dec eax
        push eax
        pop ecx
        lea esi, array

cycl_2: mov eax, esi      ; Вложенный цикл
        call PerimeterShape
        movsd xmm1, xmm0
        call PerimeterShape
        cmp xmm1, xmm0
        js swap

just_:  add xmm0, 4      ; Метка для удобства после swap
        loop @2

        pop ecx
        loop @1

        ret

swap:   mov xmm1, xmm0  ; Обмен элементами
        mov xmm1 + 4, xmm0
        test ecx, ecx
        jmp @3
