# coding: utf-8
from encodedstate import EncodedState, ChecksumError
token = EncodedState({ 'id': '0000', 'riddleparams': 0, 'faults': 0, 'animation': 0, 'sentence': 0, 'final_success': 0, 'direction': 0, 'riddle': 1, 'animparams': 0, })
print(str(token))
a = str(token)
b = EncodedState()
try:
    b.from_string(a)
except ChecksumError:
    print('CheckSum Error')
b.print_var()
