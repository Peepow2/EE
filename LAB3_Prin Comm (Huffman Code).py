# เตรียมข้อมูล สร้างอาเรย์ (ตัวอักษร, ความน่าจะเป็น)
def Data_Preparation(S): 
    char_freq = sorted([(c, NAME.count(c)/len(S)) for c in set(S)], \
                       key = lambda x: (x[1], x[0]), reverse = True)
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

    Binary_code = list()
    Huffman_Code = ""

    return Huffman_Code, Binary_code


# Driver Code (MAIN)
NAME = "peerawichsodsuay" #"A" * 30 + "B" * 25 + "C" * 20 + "D" * 12 + "E" * 8 + "F" * 5
Huffman_Code, Binary_code = Huffman_Encoding(NAME)
show_result(Huffman_Code, Binary_code) # แสดงผลลัพธ์
