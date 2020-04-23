from cs50 import get_string
import re


def main():
    # 適当な文字列が入力されるまで再帰呼び出し
    string = getstrings()
    
    # !, ? and . is end of a sentense
    sentence = len(re.findall(r'[\!\?\.][\s\0]', string))
    letter = len(re.findall(r'[a-z]', string.lower()))
    words = len(re.findall(r"[a-z][\!\?\.,;:']?[\s\0]", string.lower()))
    # wordsとsentenceは文字列の最後を認識しないため，その分を足した。
    # 全てのテストケースで正常動作して居るが，バグが出る可能性あり。
    cliindex(coleman(letter, words+1, sentence+1))

# coleman(float letter, float s)
# @param letter 100単語あたりの平均文字数
# @param string 100単語あたりの平均文数
# return int    コールマンリアウインデックスを適用した値


def coleman(letters, words, sentence):
    l = letters / words * 100
    s = sentence / words * 100
    return round((0.0588 * l) - (0.296 * s) - 15.8)


# getstring(void)
# return    string
#   適当な値が入力されるまで再帰的に自身を呼び出す。
def getstrings():
    string = get_string("Text: ")
    if string is None:
        return getstrings()
    else:
        return string


# cliindex(int index)
# @param int index  コールマンリアウインデックスが適用された値が入力されると
#                   それに応じたグレードを標準出力する.
def cliindex(index):
    if index >= 16:
        print("Grade 16+")
    elif index <= 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


main()