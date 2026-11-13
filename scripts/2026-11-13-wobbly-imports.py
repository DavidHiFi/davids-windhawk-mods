import struct,sys
def imps(p):
    b=open(p,'rb').read(); pe=struct.unpack_from('<I',b,0x3c)[0]
    m=struct.unpack_from('<H',b,pe+24)[0]; opt=pe+24; dd=opt+(96 if m==0x10b else 112)
    nsec=struct.unpack_from('<H',b,pe+6)[0]; so=struct.unpack_from('<H',b,pe+20)[0]; sec=opt+so
    secs=[struct.unpack_from('<IIII',b,sec+i*40+8) for i in range(nsec)]
    def off(rva):
        for vs,va,rs,ro in secs:
            if va<=rva<va+max(vs,rs): return rva-va+ro
    def name(rva):
        o=off(rva); return b[o:b.index(b'\0',o)].decode()
    out=[]
    for idx,size in ((1,20),(13,32)):
        rva,_=struct.unpack_from('<II',b,dd+idx*8)
        if not rva: continue
        o=off(rva)
        while True:
            e=b[o:o+size]
            nr=struct.unpack_from('<I',e,12 if size==20 else 4)[0]
            if not nr: break
            out.append(('imp' if size==20 else 'delay')+':'+name(nr)); o+=size
    return out
for p in sys.argv[1:]: print(p, imps(p))
