#coding utf8

import math
import romanify

def romanlol(number):
	puissance = int(math.log10(number))
	if puissance > 3:
		n_lin = puissance / 3 + 1 * (puissance % 3 != 0) - 1
	else:
		n_lin = 0
	print puissance
	print n_lin
	truc = [[ ' ' for j in xrange(0, puissance + 1)] for i in xrange(0, n_lin + 1)]
	
	chiffre = 0
	numby = number
	for i in xrange(0, min(puissance + 1,3)):
		chiffre = int(numby % 10 ** (i+1))
		numby -= chiffre
		if chiffre > 0:
			print chiffre
			truc[n_lin][i] = romanify.arabic2roman(chiffre)
		else:
			truc[n_lin][i] = ''
		for j in xrange(0, (i-1) / 3):
			truc[j][i] = '_'
			for k in xrange(0, len(truc[n_lin][i])):
				truc[j][i] = '_' + truc[j][i]
	
	for i in xrange(3, puissance + 1):
		chiffre = int(numby % 10 ** (i+1))
		numby -= chiffre
		if chiffre > 0:
			print chiffre
			chouffe = chiffre/10**(3*((i-1)/3))
			truc[n_lin][i] = romanify.arabic2roman(chouffe)
		else:
			truc[n_lin][i] = ''
		for j in xrange(0, (i-1) / 3):
			truc[j][i] = ''
			for k in xrange(0, len(truc[n_lin][i])):
				truc[j][i] = '_' + truc[j][i]

	for i in xrange(n_lin, -1, -1):
		res = ''
		for j in xrange(puissance, -1, -1):
			res += truc[i][j] 
		print res
	for i in xrange(n_lin, n_lin+1):
		res = ''
		for j in xrange(puissance, -1, -1):
			res += truc[i][j] 
		print res

	print truc
