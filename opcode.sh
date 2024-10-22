echo "give me a opcode"
while read ln
do
    echo "give me a opcode"
    echo "org 0x100" > /tmp/out.asm
    echo $ln >> /tmp/out.asm
    nasm /tmp/out.asm -o /tmp/out
    xxd /tmp/out
done
