.386
.model flat, stdcall
option casemap:none

; External function prototypes
CreateFileA PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
WriteFile PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
CloseHandle PROTO :DWORD
ExitProcess PROTO :DWORD

.data
    ; Input values (simulated)
    input1      db 1      ; First input
    input2      db 1      ; Second input
    
    ; Output values
    output1     db 0      ; Result of AND operation
    counter     db 0      ; Counter value
    
    ; File handling
    fileName    db "..\ASMtoCPPinHTML\output.bin", 0
    fileHandle  dd 0
    bytesWritten dd 0
    
    ; Constants for CreateFileA
    GENERIC_WRITE       equ 40000000h
    CREATE_ALWAYS       equ 2
    FILE_ATTRIBUTE_NORMAL equ 128

.code
_start:
    ; Perform AND logic: output1 = input1 AND input2
    mov al, [input1]
    and al, [input2]
    mov [output1], al
    
    ; If output1 is ON (1), increment counter
    cmp byte ptr [output1], 1
    jne skip_increment
    inc byte ptr [counter]
    
skip_increment:
    ; Create/open the output file
    push 0                          ; hTemplateFile (NULL)
    push FILE_ATTRIBUTE_NORMAL      ; dwFlagsAndAttributes
    push CREATE_ALWAYS              ; dwCreationDisposition
    push 0                          ; lpSecurityAttributes (NULL)
    push 0                          ; dwShareMode
    push GENERIC_WRITE              ; dwDesiredAccess
    push offset fileName            ; lpFileName
    call CreateFileA
    
    ; Check if file creation was successful
    cmp eax, -1                     ; INVALID_HANDLE_VALUE
    je exit_program
    mov [fileHandle], eax           ; Store file handle
    
    ; Write output1 value to file
    push 0                          ; lpOverlapped (NULL)
    push offset bytesWritten        ; lpNumberOfBytesWritten
    push 1                          ; nNumberOfBytesToWrite
    push offset output1             ; lpBuffer
    push [fileHandle]               ; hFile
    call WriteFile
    
    ; Write counter value to file
    push 0                          ; lpOverlapped (NULL)
    push offset bytesWritten        ; lpNumberOfBytesWritten
    push 1                          ; nNumberOfBytesToWrite
    push offset counter             ; lpBuffer
    push [fileHandle]               ; hFile
    call WriteFile
    
    ; Close the file handle
    push [fileHandle]
    call CloseHandle

exit_program:
    ; Exit the program
    push 0
    call ExitProcess

END _start