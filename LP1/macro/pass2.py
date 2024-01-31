class Pass2:
    def __init__(self) -> None:
        self.mnt={}
        self.pntab={}
        self.kpdt={}
        self.output=""
        self.aptab={}
        self.current_macro=0
        pass
    def readfiles(self):
        self.mnt={
            'M1':[2,2,1,1],
            'M2':[2,2,6,3]
        }
        self.pntab={
            'M1':['X','Y','A','B'],
            'M2':['P','Q','U','V']
        }
        self.kpdt={
            'A':'AREG',
            'B':'',
            'U': 'CREG',
            'V': 'DREG'
        }
        pass
    def process(self):
        icfile=open('macro/calls.txt','r')
        mdtfile=open('macro/mdt.txt','r')

        for line in icfile:
            word=line.replace(',','').replace('&','').split()
            if word[0] not in self.mnt.keys():
                self.output+=line
            else:
                self.current_macro+=1
                MNT=self.mnt[word[0]]
                pp=MNT[0]
                self.aptab={}
                kp=MNT[1]
                for i in range (1,pp+1):
                    self.aptab[i]=word[i]
                for i in range(pp+1,kp+pp+1):
                    if word[i].partition('=')[2]=='':
                        self.aptab[i]=self.kpdt[word[i].partition('=')[0]]
                    else:
                        self.aptab[i]=word[i].partition('=')[2]
                print(self.aptab)
                for line in mdtfile:
                    wordMDT=line.split()
                    if wordMDT[0]!='MEND':
                        self.output+=wordMDT[0]+"\t"
                        for i in range(1,len(wordMDT)):
                            if wordMDT[i].find('=')==-1:
                                paramindex=int(wordMDT[i][3])
                                
                                self.output+=self.aptab[paramindex]+"\t"
                            else:
                                self.output+=wordMDT[i]+"\t"
                        self.output+='\n'
                    else:
                        break

        print(self.output)

test=Pass2()
test.readfiles()
test.process()




            
    