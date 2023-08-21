import json
 
mnemonics=json.load(open('mnemonics.json'))
registers=json.load(open('registers.json'))
directives=json.load(open('directives.json'))
condition=json.load(open('conditions.json'))
# pool=json.load(open('pooltable.json'))
ipfile=open('code.nasm','r')
opfile=open('ic.txt','a')

label=instruct=ope1=op2=op1code=op2code=var=""
curr=0
prev=0
symboltable={}
literaltable={}
# symboltable=open('symboltable.txt','a')
# literaltable=open('literaltable.txt','a')
rel_add=[]
IC=[]
flag=0
stcnt=1
ltcnt=1
ptcnt=1
for line in ipfile:
    label=instruct=ope1=op2=op1code=op2code=""
    # print(line)
    if line=='\n':
        continue
    line=line.strip()
    ipwords=line.split(' ')
    # ipwords=regex.split(pattern,line.rstrip())
    ipwords=list(x.upper() for x in ipwords)
    if len(ipwords)==4: #label is present
        label=ipwords[0]
        instruct=ipwords[1]
        op1=ipwords[2]
        op2=ipwords[3]
    elif len(ipwords)==3:
        # print(ipwords)
        ind=-1
        for word in ipwords:
            if word in mnemonics:
                if word=='DC' or word=='DS':
                    var=ipwords[0]
                    ind=1
                    op1=ipwords[2]
                    flag=1
                    break
                else:
                    ind=ipwords.index(word)
                    break
            if word in directives:
                ind=ipwords.index(word)
                break

        instruct=ipwords[ind]
        if ind==0:
            op1=ipwords[1]
            op2=ipwords[2]
        
        elif flag==0:
            op1=ipwords[ind-1]
            op2=ipwords[ind+1]
            
    elif len(ipwords)==2:
        ind=-1
        for word in ipwords: 
            if word in directives:  
                ind=ipwords.index(word)
                break
            if word in mnemonics:
                ind=ipwords.index(word)
                break
        instruct=ipwords[ind]
        if ind==0:
            op1=ipwords[1]
        else:
            label=ipwords[0]

    else:
        
        instruct=ipwords[0]

    if instruct in directives:
        if instruct== 'START':
            curr=int(ipwords[1])
            opcode=directives.get(instruct)
            op1code=f"(C,{curr})"
            opfile.write(f"    {opcode} {op1code}\n")
            continue
        elif instruct=='END':
            opcode=directives.get(instruct)
            opfile.write(f"    {opcode}\n")
            break
            
        elif instruct=='ORIGIN':
            opcode=directives.get(instruct)
            op1=ipwords[1]
            if '+' in op1:
                address=op1.split('+')[0]
                offset=op1.split('+')[1]
                op1code=f"(S,{symboltable.get(address)[0]})+{offset}"
                prev=curr
                curr=symboltable.get(address)[2]+int(offset)
                rel_add.append(prev)
                opfile.write(f"    {opcode} {op1code}\n")

            elif '-' in op1:
                address=op1.split('-')[0]
                offset=op1.split('-')[1]
                op1code=f"(S,{symboltable.get(address)[0]})-{offset}"
                prev=curr
                curr=symboltable.get(address)[2]-int(offset)
                rel_add.append(prev)
                opfile.write(f"    {opcode} {op1code}\n")
            else:
                op1code=f"(S,{symboltable.get(op1)[0]})"
                prev=curr
                rel_add.append(prev)
                opfile.write(f"    {opcode} {op1code}\n")
        elif instruct=='EQU':
            op1=ipwords[0]
            op2=ipwords[2]
            symboltable[op1][2]=symboltable[op2][2]
        elif instruct=='LTORG':
            # pool[ptcnt]=[literaltable.keys()[0],prev]
            for literal,[index,lit,val] in literaltable.items():
                if val==-1: #which means memory is not allocated
                    prev=curr
                    curr+=1
                    rel_add.append(prev)
                    literaltable[literal][2]=prev
                    opcode=f"(DL,01)"
                    op1code=f"(C,{lit})"
                    opfile.write(f"{prev} {opcode} {op1code}\n")
                else:
                    pass
    if instruct in mnemonics:
        if instruct=='DC':
            op1code=f"(C,{op1[1]})"
            op2code=f""
        opcode=mnemonics.get(instruct)
        prev=curr
        curr+=1
        rel_add.append(prev)   
        if label:
            if label in symboltable: #check if label is already present in the symbol table
                if symboltable[label][2]==-1:
                    symboltable[label][2]=prev
                else:
                    pass
            
            else: #if not present add to the symbol table
                symboltable[label]=[stcnt,label,prev]
                stcnt+=1
        
        if instruct=='BC':
            op1code=f"({condition.get(op1)})"
           
        
        elif op1.isdigit() and instruct!='DC':
            op1code=f"(C,{op1})"
            # print(op1code,"\n")
        elif op1 in registers:
            op1code=f"({registers.get(op1)})"
        elif "=" in op1: #literal 
            literal=op1.split('=')[1][1] 
            #op1.split('=')[1] will give '1' but we want integer value
            if op1 in literaltable:
                op1code=f"(L,{literaltable.get(op1)[0]})"
            else:
                literaltable[ltcnt]=[ltcnt,literal,-1] #as memory is allocated only after LTORG
                op1code=f"(L,{ltcnt})"
                ltcnt+=1
        elif instruct=='DS' or instruct=='DC': 
            symboltable[var][2]=prev
        elif op1 not in condition:
            if op1 in symboltable:
                op1code=f"(S,{symboltable.get(op1)[0]})"

            elif op1:
                symboltable[op1]=[stcnt,op1,-1]
                op1code=f"(S,{stcnt})"
                stcnt+=1
        
        if op2.isdigit():
            op2code=f"(C,{op2})"
            # print(op2code)
        elif instruct=='DS' or instruct=='DC': 
            symboltable[var][2]=prev
       
        elif op2 in registers:
            op2code=f"({registers.get(op2)})"
        elif "=" in op2: #literal 
            literal=op2.split('=')[1][1]
            #op2.split('=')[1] will give '1' but we want integer value
            if op2 in literaltable:
                op2code=f"(L,{literaltable.get(op2)[0]})"
            else:
                literaltable[ltcnt]=[ltcnt,literal,-1] #as memory is allocated only after LTORG
                op2code=f"(L,{ltcnt})"
                ltcnt+=1
        else:
            if op2 in symboltable:
                op2code=f"(S,{symboltable.get(op2)[0]})"
            elif op2 and instruct!='DC':
                symboltable[op2]=[stcnt,op2,-1]
                op2code=f"(S,{stcnt})"
                stcnt+=1
        if instruct!='STOP':
            IC.append((opcode,op1code,op2code))
            opfile.write(f"{prev} {opcode} {op1code} {op2code}\n")
        else:
            IC.append((opcode))
            opfile.write(f"{prev} {opcode}\n")
for literal,[index,lit,val] in literaltable.items():
    if val==-1: #which means memory is not allocated
        # print("hello")     
        prev=curr
        curr+=1
        rel_add.append(prev)
        literaltable[literal][2]=prev 
        opcode=f"(DL,01)"
        op1code=f"(C,{lit})"
        opfile.write(f"{prev} {opcode} {op1code}\n")



with open('symboltable.json', 'w') as json_file:
    json.dump(symboltable, json_file, indent=4)

with open('literaltable.json', 'w') as json_file:
    json.dump(literaltable, json_file, indent=4)

