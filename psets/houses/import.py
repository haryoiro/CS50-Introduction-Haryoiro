from cs50 import SQL
from csv import DictReader
from sys import argv, exit

db = SQL("sqlite:///students.db")


def main():
    # 不正な引数が渡された場合エラー
    if len(argv) is not 2:
        print("Usage: import.py characters.csv")
        exit(1)
    
    # クエリ実行用文字列
    insertData = "INSERT INTO students(first, middle, last, house, birth) VALUES(%s, %s, %s, %s, %s);"

    # 第二引数をcsvファイルとして取得
    filename = argv[1]
    with open(filename) as data:
        # csvを辞書型で展開
        reader = DictReader(data)
        for row in reader:
            name = row["name"].split()
            house = row["house"]
            birth = row["birth"]
            if len(name) is 2:
                first = name[0]
                last = name[1]
                db.execute(insertData, first, None, last, house, birth)
            elif len(name) is 3:
                first = name[0]
                middle = name[1]
                last = name[2]
                db.execute(insertData, first, middle, last, house, birth)


main()