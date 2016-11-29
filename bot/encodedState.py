import re

class EncodedState:

    def __init__(self):
        self._magic1 = 1457849334819822135
        self._magic2 = 9401304444795304839
        self.s1 = 0
        self.s2 = 0
        self.id = 0
        self.faults = 0
        self.riddle = 0

    def from_string(self, rep):
        if not re.match(r"^[\w\d+/]{22}$", rep):
            return False

        s1,s2 = 0,0
        for ii in range(10):
            s1 += self.from_b64(rep[21-2*ii-1])
            s1 *= 2**6
            s2 += self.from_b64(rep[21-2*ii])
            s2 *= 2**6
            s1 = s1 & (2**64-1)
            s2 = s2 & (2**64-1)
        s1 += self.from_b64(rep[0])
        s2 += self.from_b64(rep[1])

        s1 = (s1 * self._magic2)%(2**64)
        s2 = (s2 * self._magic1)%(2**64)

        self.s2 = s2 - s1
        self.s1 = self.s2 ^ s1


        self.id = (self.s1 & 0xFFFF)
        self.riddle = (self.s1 >> 16) & 0xFF
        self.faults = (self.s2 & 0x0F)

        return True

    def to_string(self):
        s1 = self.s1 ^ self.s2
        s2 = self.s2 + s1

        s1 *= self._magic1
        s2 *= self._magic2

        rep = []
        for ii in range(11):
            nb = s1 & ((1 << 6) - 1)
            rep.append(self.to_b64(nb))
            s1 >>= 6
            nb = s2 & ((1 << 6) - 1)
            rep.append(self.to_b64(nb))
            s2 >>= 6
        return ''.join(rep)

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
        if c == '+': return 62
        if c == '/': return 63
        c -= ord('0')
        if c < 10: return 52 + c
        c -= ord('A') - ord('0')
        if c < 26: return c
        c -= ord('a')-ord('A')
        return c + 26
