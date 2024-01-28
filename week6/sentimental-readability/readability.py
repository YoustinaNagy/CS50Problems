# TODO
from cs50 import get_string,get_int
# L=(number of letters/words) *100
# S = (number of sentences/words) *100

# index = 0.0588 * L - 0.296 * S - 15.8
def letters (text):
    letters = 0
    for i in range(len(text)):
        # if(int(text[i])> 64 and int(text[i]) < 123 ):
        if text[i].isalpha():
            letters +=1

    return letters

def words (text):
    words = 1
    for i in range(len(text)):
        if(text[i] == ' '):
            words +=1
    return words


def sentences(text):
    sentence = 0
    for i in range(len(text)):
        if(text[i] == '.'  or text[i] == '!' or text[i] == '?'):
            sentence +=1
    return sentence



text = get_string("Text: ")
L = (letters(text)/words (text))*100
S = (sentences(text)/words (text))*100

index = 0.0588 * L - 0.296 * S - 15.8
index = round(index)
if(index> 15):
    print("Grade 16+")

elif(index< 1 ):
    print("Before Grade 1")

else:
    print(f"Grade {int(index)}")
