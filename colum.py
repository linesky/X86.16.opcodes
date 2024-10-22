import sys

def main():
    # Verifica se o número de argumentos é suficiente
    #print("\033c\033[40;37m")
    if len(sys.argv) != 3:
        print("Use: python colum.py <file csv> <colum number>")
        return

    filename = sys.argv[1]
    colums=int(sys.argv[2])
    try:
        # Abre o arquivo passado como argumento
        with open(filename, 'rt') as file:
            # Lê o arquivo linha por linha e imprime na consola
            for line in file:
                line=line.strip()
                lines=line.split("|")
                counts=len(lines)
                c=0
                if counts>=colums and line!="":
                    print(lines[colums], end='')
                    if counts!=colums:
                        print("|", end='')
                
                if line!="":    
                    for cols in range(counts):
                        if cols!=colums:
                            print(lines[cols], end='')
                            if counts-2>cols or (cols==counts and counts==colums)or (counts-2==cols and 0==colums):
                                print("|", end='')
                        
                    print("")    
    except FileNotFoundError:
        print(f"Erro: file '{filename}' not find.")
    except Exception as e:
        print(f"error: {e}")

if __name__ == "__main__":
    main()

