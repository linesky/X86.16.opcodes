#include "string.bi"
color 15,0
dim shared s(250) as string
dim liness as string
dim counter as integer
dim filenames as string=command(1)
dim f as integer=1
dim numbers as string=command(2)
dim nn as integer
dim  keywords as string=command(3)
dim shared kn as integer
'max recordes
dim g as integer=200000000
dim m as integer
dim shared fff as double=0.0
if filenames = "" or numbers = "" then
    print "use  colum <filename csv> <colum number>"
    system()
end if 
nn=val(numbers)
kn=0
function split(lines as string)as integer
    dim n as integer=0
    dim nnn as integer=0
    dim counts as integer=0
    dim p as integer=1
    dim l as integer=len(lines)
    
    for n=0 to 249
        counts=n+1
        nnn=instr(p,lines,",")
        if nnn<1 then
            s(n)=mid(lines,p,l-p+1)
            n=1000
            
        else
           
           s(n)=mid(lines,p,nnn-p) 
           p=nnn+1
           
        end if
    next
    return counts
end function
sub lists(counters as integer)
    dim n as integer
    print counters 
    for n = 0 to counters
        print s(n)
    next  
    
end sub
sub forss(counters as integer,c as integer)
    dim n as integer
    dim ffff as double=0.0
    
    dim ssss as string

    if c<=counters then 
        print s(c);
        if c<>counters then print ",";
    end if
    for n=0 to counters-1 
        if n<>c then
            print s(n);

            if n<>counters-1 and(c<>counters-1 and n<>c)  then print ",";
            
            if n=c-2 and c=counters-1 then print ",";
        end if          
        
    next
    print 
end sub
fff=0.0
open filenames for input as f
print nn
for m =0 to 200000000
    line input  #f ,liness
    counter=split(liness)
    if trim(liness)<>"" then
        forss(counter,nn)
    
    end if
    if eof(f) then m=g+20
next