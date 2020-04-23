from sys import argv, exit
from cs50 import SQL

db = SQL("sqlite:///students.db")


def main():
    # 引数の数が不正なら終了
    if len(argv) is not 2:
        print("Usage: roster.py <housename>")
        exit(1)
    
    # 寮名を変数に格納
    house = argv[1]
    
    # クエリ実行用文字列
    # studentsテーブルより指定された寮名の人物を取得
    # 苗字をアルファベット順にソート，苗字が重複した場合は名前をアルファベット順に
    selectQuery = "SELECT * FROM students WHERE house = %s ORDER BY last ASC, first ASC"
    
    # クエリを実行
    result = db.execute(selectQuery, house)
    
    # 出力されたlistからdictを取得
    for row in result:
        # dictのmiddleがNodeではなければミドルネームがあるとみなし出力python roster.py Slytherin
        if row['middle'] is not None:
            print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
        else:
            print(f"{row['first']} {row['last']}, born {row['birth']}")
    
    
main()