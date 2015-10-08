# This file was *autogenerated* from the file Test.sage
from sage.all_cmdline import *   # import sage library
_sage_const_3 = Integer(3); _sage_const_2 = Integer(2); _sage_const_1 = Integer(1); _sage_const_0 = Integer(0)
import numpy as np

gap.load_package("grape")
gap.Read('"ziv-av.g"')

__author__ = 'tony'

input = sys.argv[_sage_const_1 ]
output = sys.argv[_sage_const_2 ]
output2 = sys.argv[_sage_const_3 ]

s = '"' + input + '"'
gap.Read(s)

fw = open(output, 'w')
fw2 = open(output2, 'w')

size = gap('Length(sol);')
rang = list(range(_sage_const_1 , size + _sage_const_1 ))
comp = []
rozklad = []

for x in range(_sage_const_1 , size+_sage_const_1 ):

    if x in rang:

        if len(rang) != _sage_const_0 :
            print x, len(rang)
        else:
            break

        newrang = set()


        for y in rang:

            pom = gap.IsIsomorphicCgr_2(gap('List(sol['+str(x)+'],ShallowCopy)'), gap('List(sol['+str(y)+'],ShallowCopy)'))

            if pom:
                newrang.add(y)

                comp.append(gap('sol['+str(y)+']'))

        rang = [x for x in rang if x not in newrang]

        if comp != []:
            rozklad.append(comp[_sage_const_0 ])
            comp = []

print "-----------------------"
print "number:", len(rozklad)

fw2.write(str(len(rozklad)))

st = ""
st += ("sol:=[")
for i in rozklad:

    st += str(i) + ","

st = st[:-_sage_const_1 ]
st += "];"
fw.write(st)

fw.close()
fw2.close()
