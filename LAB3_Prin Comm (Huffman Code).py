# เตรียมข้อมูล สร้างอาเรย์ (ตัวอักษร, ความน่าจะเป็น)
def Data_Preparation(S): 
    char_freq = sorted([(c, NAME.count(c)/len(S)) for c in set(S)], \
                       key = lambda x:x[1], reverse = True)
    # print(char_freq)
    char = [itr[0] for itr in char_freq]
    freq = [itr[1] for itr in char_freq]
    return char_freq, char, freq

def show_result(Huffman_Code, Binary_code):
    print(Binary_code)
    print(f"Huffman_Code = {Huffman_Code} and length = {len(Huffman_Code)}")
    return


def upper_bound(val, Arr):
    for i in range(len(Arr)-1, 0, -1):
        if Arr[i] >= val:
            return i + 1
    return 0

# เข้ารหัส Huffman_Code
def Huffman_Encoding(NAME):
    char_freq, char, freq = Data_Preparation(NAME)
    Code = [[""] * (len(char)-i) for i in range(len(char)-1)]

    Node = list([freq])
    for i in range(2, len(char)):
        val = sum(Node[-1][-2::])
        N = list(Node[-1][:-2:])
        idx = upper_bound(val, N)
        N.insert(idx, val)
        Node.append(N)
    
    Code[-1] = ["0", "1"]
    for i in range(len(Node) - 1, 0, -1):
        for j in range(len(Node[i]) - 1, -1, -1):
            if Node[i][j] == Node[i-1][-2] + Node[i-1][-1]:
                Code[i-1][-2] += Code[i][j] + "0"
                Code[i-1][-1] += Code[i][j] + "1"
                break

        for j in range(len(Node[i-1])-2):
            for k in range(len(Node[i])):
                if Node[i-1][j] == Node[i][k] and Code[i-1][j] == "":
                    Code[i-1][j] += Code[i][k]

    Binary_code = [(char[i], Code[0][i]) for i in range(len(char))]
    Huffman_Code = ""
    for c in NAME:
        Huffman_Code += Code[0][char.index(c)]
    return Huffman_Code, Binary_code


# Driver Code (MAIN)
NAME = "peerawichsodsuay" #"A" * 30 + "B" * 25 + "C" * 20 + "D" * 12 + "E" * 8 + "F" * 5
Huffman_Code, Binary_code = Huffman_Encoding(NAME)
show_result(Huffman_Code, Binary_code) # แสดงผลลัพธ์
