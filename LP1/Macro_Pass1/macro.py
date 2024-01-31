import json
import re as regex

pntab={}
kpdtab={}
mnt={}
# mnt=open('assignment3/MNT.txt','a')
mdt=open('MDT.txt','a')
kpd_cnt=1
pn_cnt=1
prev=""
instruct=""
op1code=""
op1=""
op2=""
op2code=""
ln_cnt=1
name=""

ipfile=open('code.txt','r')
for line in ipfile:
    if line=='/n': continue
    line=line.strip()
    print(line)
    ln_cnt+=1
    flag=0
    pattern=r'\s+'
    words=regex.split(pattern,line.rstrip())
    # print(words[0])
    if prev=='MACRO':
        kpd_cnt=1
        pn_cnt=1
        # print(words)
        for word in words:
            if '&' not in word:
                name=word
            if '=' in word:
                kpdtab[word.split('=')[0].split('&')[1]]=[kpd_cnt,word.split('=')[0],word.split('=')[1]]
                kpd_cnt+=1
            if '&' in word:
                if '=' in word:
                    word=word.split('=')[0]
                    pntab[word.split('&')[1]]=[pn_cnt,word.split('&')[1]]
                else:
                    pntab[word.split('&')[1]]=[pn_cnt,word.split('&')[1]]
                pn_cnt+=1
        # print(pn_cnt)
        mnt[name]=[name,pn_cnt-kpd_cnt,kpd_cnt-1]
        instruct=""
        # print(pntab.get('MEM_VAL')[0])
    

    elif len(words)==3:
        instruct=words[0]
        op1=words[1].split('&')[1]
        op1code=f"(P,{pntab.get(op1)[0]})"
        if '=' in words[2]:
            op2code=words[2]
        else:
            op2=words[2].split('&')[1]
            op2code=f"(P,{pntab.get(op2)[0]})"
        
        
    elif len(words)==1 and words[0]=='MARCO':
        instruct=words[0]
        continue
    elif len(words)==1 and words[0]=='MEND':
        print("HI")
        instruct=words[0]
        op1code=""
        op2code=""
        flag=0
        continue

   
    # print(instruct," ",op1code," ",op2code,"\n")
    if instruct!='MARCO' and instruct!='MEND':
        mdt.write(f"{instruct} {op1code} {op2code}\n")
    elif instruct=='MEND' and flag==0:
        print("HELLO")
        mdt.write(f"{instruct} {op1code} {op2code}\n")
        flag=1
    prev=line
mdt.write(f"MEND")

    

with open('PNTAB.json','w') as json_file:
    json.dump(pntab,json_file,indent=4)

with open('kpdtab.json','w') as json_file:
    json.dump(kpdtab,json_file,indent=4)

with open('MNT.json','w') as json_file:
    json.dump(mnt,json_file,indent=4)
