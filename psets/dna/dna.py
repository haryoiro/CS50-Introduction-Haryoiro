from csv import reader, DictReader
from sys import argv, exit
import re


def main():
    nm, l, tx = 0, 0, 0
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    
    # ヘッダのSTR(Short Tandem Repeats)を取得
    try:
        with open(argv[1]) as ptr:
            if (argv[1].count(".csv") is 1) and ptr is not None:
                csread = reader(ptr)
                nm = next(csread)
                del nm[0]
            else:
                print("Usage: python dna.py data.csv sequence.txt")
                ptr.close()
                exit(1)
    except FileNotFoundError as e:
        print("Usage: python dna.py data.csv sequence.txt")
        ptr.close()
        exit(2)
    except Exception as e:
        print("Usage: python dna.py data.csv sequence.txt")
        ptr.close()
        exit(2)

    # 辞書としてcsvを読み込み
    with open(argv[1]) as dict:
        csdict = DictReader(dict)
        l = [row for row in csdict]

    # DNAをテキストとして取得
    # .txt以外受け取らない。
    try:
        with open(argv[2]) as txt:
            if (argv[2].count(".txt") is 1):
                txread = reader(txt)
                for row in txread:
                    tx = row
            else:
                print("Usage: python dna.py data.csv sequence.txt")
                txt.close()
                exit(1)
    except FileNotFoundError as e:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(2)
    except Exception as e:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(2)

    sc, co = [0] * len(l), 0

    # ヘッダのSTRが読みこんだDNAにいくつ含まれて居るか記録
    for str in nm:
        st_regex = r"((" + re.escape(str) + r")+)+?"
        a = re.findall(st_regex, tx[0])
        lsp = sorted(a, reverse=True)
        tmp = tuple(lsp)
        sc[co] = int(lsp[0][0].count(str))
        co += 1

    flag = 0
    for i in range(len(l)):  # l 縦軸
        mat = 0
        for j in nm:        # STRを保持する配列
            for k in sc:    # マッチする中で最大の文字列c
                if k == int(l[i][j]):
                    mat += 1
        if mat >= len(nm):
            flag = 1
            print(l[i]['name'])
    if flag == 0:
        print("No match")


main()