import re

class ChecksumError(Exception):
    pass

class EncodedState:

    def __init__(self, D={}):
        self.__magic1 = 1457849334819822135
        self.__magic2 = 9401304444795304839
        self.token = ''
        self.D = D

    def __getitem__(self, k):
        return self.D.__getitem__(k)

    def __setitem__(self, k, v):
        if k=='id' and type(v)==str:
            v = int('0x'+v, 16)
        return self.D.__setitem__(k, v)

    def to_b64(self, nb):
        if nb < 26: return chr(nb+ord('A'))
        nb -= 26
        if nb < 26: return chr(nb+ord('a'))
        nb -= 26
        if nb < 10: return chr(nb+ord('0'))
        nb -= 10
        if nb == 0: return '+'
        if nb == 1: return '/'
        return '='

    def from_b64(self, char):
        c = ord(char)
        if char == '+': return 62
        if char == '/': return 63
        c -= ord('0')
        if c < 10: return 52 + c
        c -= ord('A') - ord('0')
        if c < 26: return c
        c -= ord('a')-ord('A')
        return c + 26

    def compute_checksum(self):
        return 0

    def is_valid(self):
        if self.compute_checksum()!=self.D['checksum']:
            return False
        else:
            return True

    def from_string(self, rep):
        if not re.match(r"^[\w\d+/]{22}$", rep):
            return False

        e_s1, e_s2 = 0, 0
        for ii in range(10):
            e_s1 += self.from_b64(rep[21-2*ii-1])
            e_s1 = (e_s1*2**6)%(2**64)
            e_s2 += self.from_b64(rep[21-2*ii])
            e_s2 = (e_s2*2**6)%(2**64)
        e_s1 += self.from_b64(rep[0])
        e_s2 += self.from_b64(rep[1])

        e_s1 *= self.__magic2
        e_s2 *= self.__magic1
        e_s1 %= 2**64
        e_s2 %= 2**64

        s2 = e_s2 - e_s1
        s1 = s2 ^ e_s1

        self.state1 = s1
        self.state2 = s2

        try:
            self.D['id'] = (s1 & 0xFFFF)
            self.D['riddleparams'] = (s1 >> 16) & 0xFFFFFFFF

            self.D['faults'] = (s2 & 0x0F)
            self.D['animation'] = (s2 >> 4) & 0x1F
            self.D['sentence'] = (s2 >> 9) & 0x1F
            self.D['final_success'] = (s2 >> 14) & 0x1
            self.D['direction'] = (s2 >> 15) & 0x1
            self.D['riddle'] = (s2 >> 16) & 0xFF
            self.D['animparams'] = (s2 >> 24) & 0xFFFFFF
            self.D['checksum'] = (s2 >> 48) & 0xFFFF
        except Exception as e:
            print('Error decoding token:\n%s'%(e,))

        if self.is_valid():
            return self.D
        else:
            raise ChecksumError

    def to_string(self):
        return str(self)

    def __str__(self):
        s1, s2 = 0, 0

        try:
            if type(self.D['id'])==str:
                self.D['id'] = int('0x'+self.D['id'], 16)
            s1 |= (self.D['id'] & 0xFFFF)
            s1 |= (self.D['riddleparams'] & 0xFFFFFFFF) << 16

            s2 |= (self.D['faults'] & 0x0F)
            s2 |= (self.D['animation'] & 0x1F) << 4
            s2 |= (self.D['sentence'] & 0x1F) << 9
            s2 |= (self.D['final_success'] & 0x1) << 14
            s2 |= (self.D['direction'] & 0x1) << 15
            s2 |= (self.D['riddle'] & 0xFF) << 16
            s2 |= (self.D['animparams'] & 0xFFFFFF) << 24
        except KeyError as e:
            raise ValueError('Incomplete data structure, missing field "%s"'%(e.args[0],))

        self.D['checksum'] = self.compute_checksum()
        s2 |= (self.D['checksum'] & 0xFFFF) << 48

        e_s1 = s1 ^ s2
        e_s2 = s2 + e_s1

        e_s1 *= self.__magic1
        e_s2 *= self.__magic2

        rep = []
        for ii in range(11):
            nb = e_s1 & ((1 << 6) - 1)
            rep.append(self.to_b64(nb))
            e_s1 >>= 6
            nb = e_s2 & ((1 << 6) - 1)
            rep.append(self.to_b64(nb))
            e_s2 >>= 6
        return ''.join(rep)

    def _print_var(self):
        print('{')
        for k, v in self.D.items():
            print('%s = %s'%(k, v))
        print('}')

