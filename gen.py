import sys
import os

def main():
    ofile = open("out.tex", "w")
    ofile.write("\\documentclass[twocolumn]{article}\n\\usepackage{listings}\n\\usepackage[scaled]{beramono}"+
        "\\usepackage[T1]{fontenc}\\usepackage[utf8]{inputenc}\\usepackage[margin = 0.3in, top=0.6in, landscape]{geometry}\n"+
        "\\setlength{\\columnseprule}{0.4pt}\\setlength{\\columnsep}{40pt}\n\\usepackage{fancyhdr}"+
        "\n\\pagestyle{fancy}\n\\fancyhead[L]{Pumazos - Facultad de Ciencias UNAM}"+
        "\\fancyhead[C]{\\textsl{\\leftmark}}\\fancyhead[R]{\\thepage}\\begin{document}\n\\setlength{\\parindent=0pt}\n")
    for folder in os.listdir():
        if(folder.count(".") > 0):
            continue
        print(folder)
        ofile.write("\\section{" + folder +"}\n")
        for file in os.listdir("./" + folder):
            fname = file
            while fname.count('/') > 0:
                fname = fname[fname.find('/')+1:]
            name = fname[:fname.find('.')]
            ext = fname[fname.find('.')+1:]
            print(name)
            print(ext)
            if(ext != 'cpp' or name.startswith("exc")):
                continue
            ifile = open("./" + folder + "/" + file)
            doc = list(l for l in ifile.readlines())
            print(doc)
            ofile.write("\\subsection{"+name+"}\n")
            start = 0
            if(doc[0].startswith("/*INFO")):
                start = start + 1
                ofile.write("\\begin{footnotesize}")
                while(not(doc[start].startswith('*/'))):
                    ofile.write(doc[start])
                    start = start + 1
                    if(not(doc[start].startswith('*/'))):
                        ofile.write("\n\n")
                ofile.write("\\end{footnotesize}")
                start = start + 1
            ofile.write("\\lstset{basicstyle=\\footnotesize\\ttfamily,"+
                "breaklines=true,tabsize=2,language=C++,frame=leftline, numbers=left, numberstyle=\\tiny, numbersep=5pt}\n")
            ofile.write("\\begin{lstlisting}\n")
            keep = True
            for l in doc[start + 3:]:
                if(l.startswith("//ignore")):
                    keep = False
                if(l.startswith("//unignore")):
                    keep = True
                    continue
                if(keep == False):
                    continue
                if(l.startswith("int main()")):
                    break
                tabs = 0
                while(l.startswith("    ")):
                    l = l[4:]
                    tabs += 1
                ofile.write('\t'*tabs + l)
            ifile.close()
            ofile.write("\\end{lstlisting}\n")
    ofile.write("\\end{document}")
    ofile.close()
    os.system('pdflatex ' + ofile.name + ' && evince ' + ofile.name[:-3] + 'pdf')

if __name__ == '__main__':
    main()
