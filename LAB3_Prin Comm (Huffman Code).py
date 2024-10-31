# เตรียมข้อมูล สร้างอาเรย์ (ตัวอักษร, ความน่าจะเป็น)
def preparation(S): 
    char_freq = [(c, NAME.count(c)/len(S)) for c in sorted(set(S))]
    # print(char_freq)
    return char_freq

def show_result(Huffman_Code, Binary_code):
    print(Binary_code)
    print(f"Huffman_Code = {Huffman_Code} and length = {len(Huffman_Code)}")
    return 0


# เข้ารหัส Huffman_Code
def Huffman_Encoding(NAME):
    return "", []


# Driver Code (MAIN)
NAME = "peerawichsodsuay"
Huffman_Code, Binary_code = Huffman_Encoding(NAME)
show_result(Huffman_Code, Binary_code) # แสดงผลลัพธ์
