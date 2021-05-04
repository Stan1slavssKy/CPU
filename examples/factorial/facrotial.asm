        push 1
        pop rbx  

        push 12
        pop rax

factorial:

        push rbx
        push rax 

        mul
        pop rbx

        dec rax

        push rax
        push 0
        
        cmp 
        jne factorial
        
        push rbx
        out

        end
        
