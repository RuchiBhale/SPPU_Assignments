import re as regex
import json
file=open('macro/input.txt','r')
opfile=open('macro/output.txt','a')

def get_key(val:str,dict:dict)->any:
    for key,value in dict.items():
        if val==value:
            return key


mnt={}
kpdtab={}
pntab={}
kpdindex=1
kpdloc=1
mntindex=1
mdtloc=1
macroname=""
msign=False
mdef=False
pattern=r'\s+'
for line in file:
    if line=='\n':continue
    line=line.strip()
    cmd=regex.split(pattern,line.rstrip())
    if len(cmd)==1 and cmd[0]=='MACRO':
        msign=True
        continue
    if msign:
        macroname=cmd.pop(0)
        pntab[macroname]={}
        paramcount=0
        pp=0
        kp=0
        for parameter in cmd:
            if ',' in parameter:
                parameter=parameter.replace(',','')
            if '&' in parameter and '=' not in parameter:
                paramcount+=1
                pp+=1
                paramname=parameter[1::]
                pntab[macroname][paramcount]=paramname

            elif '&' in parameter and '=' in parameter:
                paramcount+=1
                if kp==0:
                    kpdloc=kpdindex
                kp+=1
                eqindex=parameter.index('=')
                paramname=parameter[1:eqindex:]
                defval=parameter[1+eqindex::]
                pntab[macroname][paramcount]=paramname
                kpdtab[kpdindex]={
                    'index': kpdindex,
                    'name': paramname,
                    'value': defval if defval else '--',
                }
                kpdindex+=1
            else:
                pass
        msign=False
        mdef=True
        mnt[mntindex]={
            'index':mntindex,
            'name': macroname,
            'pp': pp,
            'kp' :kp,
            'mdtloc': mdtloc,
            'kpdloc':kpdloc
        }
        mntindex+=1
        continue
    if mdef:
        mdtloc+=1
        callLine=""
        for command in cmd:
            if ',' in command:
                command=command.replace(',','')
            if '&' in command:
                p1val=f'(P,{get_key(command[1::],pntab[macroname])})'
                callLine+=p1val+""
            else:
                callLine+=command+""
        opfile.write(callLine+'\n')
        continue
    if len(cmd)==1 and cmd[0]=='MEND':
        mdtloc+=1
        mdef=False
        opfile.write('MEND\n')
        continue

    

with open('kpdtab.json','w') as json_file:
    json.dump(kpdtab,json_file,indent=4)

with open('pntab.json','w') as json_file:
    json.dump(pntab,json_file,indent=4)
    
with open('mnt.json','w') as json_file:
    json.dump(mnt,json_file,indent=4)
    
        

               

